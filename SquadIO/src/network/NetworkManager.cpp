#include "include\network\NetIncludes.h"
#include "include\LogManager.h"
#include "zlib\include\zlib.h"

unique_ptr<NetworkManager> NetworkManager::sInstance;

namespace
{
	const float kTimeBetweenDelayHeartbeat = 1.f;
	const float kStartDelay = 3.0f;
	const int	kSubTurnsPerTurn = 3;
	const int	kMaxPlayerCount = 8;
}

bool NetworkManager::StaticInit()
{
	sInstance = std::make_unique< NetworkManager >();

	return sInstance->Init();
}

NetworkManager::NetworkManager() :
mBytesSentThisFrame(0),
mDropPacketChance(0.f),
mSimulatedLatency(0.f),
mBytesReceivedPerSecond(WeightedTimedMovingAverage(1.f)),
mBytesSentPerSecond(WeightedTimedMovingAverage(1.f)),
mPlayerId(0),
mLobbyId(0),
mNewNetworkId(1),
mIsMasterPeer(false),
mState(NMS_Unitialized),
mPlayerCount(0),
mReadyCount(0),
mDelayHeartbeat(kTimeBetweenDelayHeartbeat),
mTimeToStart(-1.0f),
//we always start on turn -2 b/c we need 2 frames before we can actually play
mTurnNumber(-2),
mSubTurnNumber(0)
{
	//this is enough for a 16.6 minute game...
	//so let's avoid realloc/copies and just construct all the empty maps, too
	mTurnData.resize(10000);
}


NetworkManager::~NetworkManager()
{
}

bool NetworkManager::Init()
{
	//set my player info from steam
	mPlayerId = GamerServices::sInstance->GetLocalPlayerId();
	mName = GamerServices::sInstance->GetLocalPlayerName();

	return true;
}

void NetworkManager::StartLobbySearch(){
	mState = NMS_Searching;
	GamerServices::sInstance->LobbySearchAsync();
	//update until lobby found or created
	while (GetState() != NMS_Lobby){
		GamerServices::sInstance->Update();
	}
}

void NetworkManager::ProcessIncomingPackets()
{
	ReadIncomingPacketsIntoQueue();

	ProcessQueuedPackets();

	UpdateBytesSentLastFrame();

}

void NetworkManager::SetState(NetworkManagerState state){
	mState = state;
}

void NetworkManager::SendOutgoingPackets()
{
	switch (mState)
	{
	case NMS_Starting:
		UpdateStarting();
		break;
	case NMS_Playing:
		UpdateSendTurnPacket();
		break;
	default:
		break;
	}
}

void NetworkManager::UpdateDelay()
{
	//first process incoming packets, in case that removes us from delay
	NetworkManager::sInstance->ProcessIncomingPackets();

	if (mState == NMS_Delay)
	{
		mDelayHeartbeat -= Timing::sInstance.GetDeltaTime();
		if (mDelayHeartbeat <= 0.0f)
		{
			mDelayHeartbeat = kTimeBetweenDelayHeartbeat;
		}

		//find out who's missing and send them a heartbeat
		unordered_set< uint64_t > playerSet;
		for (auto& iter : mPlayerNameMap)
		{
			playerSet.emplace(iter.first);
		}

		Int64ToTurnDataMap& turnData = mTurnData[mTurnNumber + 1];
		for (auto& iter : turnData)
		{
			playerSet.erase(iter.first);
		}

		OutputMemoryBitStream packet;
		packet.Write(kDelayCC);
		//whoever's left is who's missing
		for (auto& iter : playerSet)
		{
			SendPacket(packet, iter);
		}
	}
}

void NetworkManager::UpdateStarting()
{
	EnterPlayingState();
}

void NetworkManager::UpdateSendTurnPacket()
{
	mSubTurnNumber++;
	if (mSubTurnNumber == kSubTurnsPerTurn)
	{
		//create our turn data
		//TO DO: code to get the command list
		/*TurnData data(mPlayerId, RandGen::sInstance->GetRandomUInt32(0, UINT32_MAX),
		ComputeGlobalCRC(), mCommandList);*/

		//we need to send a turn packet to all of our peers
		OutputMemoryBitStream packet;
		packet.Write(kTurnCC);
		//we're sending data for 2 turns from now
		packet.Write(mTurnNumber + 2);
		packet.Write(mPlayerId);
		//data.Write(packet);

		for (auto &iter : mPlayerNameMap)
		{
			if (iter.first != mPlayerId)
			{
				SendPacket(packet, iter.first);
			}
		}

		//save our turn data for turn + 2
		//mTurnData[mTurnNumber + 2].emplace(mPlayerId, data);
		//TO DO: code to clear the command list
		mCommandList.Clear();
		//InputManager::sInstance->ClearCommandList();

		if (mTurnNumber >= 0)
		{
			//TryAdvanceTurn();
		}
		else
		{
			//a negative turn means there's no possible commands yet
			mTurnNumber++;
			mSubTurnNumber = 0;
		}
	}
}

void NetworkManager::TryAdvanceTurn()
{
	//only advance the turn IF we received the data for everyone
	if (mTurnData[mTurnNumber + 1].size() == mPlayerCount)
	{
		if (mState == NMS_Delay)
		{
			//throw away any input accrued during delay
			//TO DO: code to clear the command list
			mCommandList.Clear();
			//InputManager::sInstance->ClearCommandList();
			mState = NMS_Playing;
			//wait 100ms to give the slow peer a chance to catch up
			//Temp replaced with Sleep(100)
			Sleep(100);
			//SDL_Delay(100);
		}

		mTurnNumber++;
		mSubTurnNumber = 0;

		if (CheckSync(mTurnData[mTurnNumber]))
		{
			//process all the moves for this turn
			for (auto& iter : mTurnData[mTurnNumber])
			{
				iter.second.GetCommandList().ProcessCommands(iter.first);
			}

			//since we're still in sync, let's check for achievements
			CheckForAchievements();
		}
		else
		{
			//for simplicity, just kill the game if it desyncs
			LogManager* log = LogManager::GetLogManager();
			log->logBuffer << "DESYNC: Game over. NetworkManager::TryAdvanceTurn";
			log->flush();
			//Commented out: Code to stop the engine from running anymore
			//Engine::sInstance->SetShouldKeepRunning(false);
		}
	}
	else
	{
		//don't have all player's turn data, we have to delay :(
		mState = NMS_Delay;
		LogManager* log = LogManager::GetLogManager();
		log->logBuffer << "Going into delay state, don't have all the info for turn %d\n", mTurnNumber + 1;
		log->flush();
	}
}

void NetworkManager::ProcessPacket(InputMemoryBitStream& inInputStream, uint64_t inFromPlayer)
{
	switch (mState)
	{
	case NMS_Lobby:
		ProcessPacketsLobby(inInputStream, inFromPlayer);
		break;
	case NMS_Ready:
		ProcessPacketsReady(inInputStream, inFromPlayer);
		break;
	case NMS_Starting:
		//if I'm starting and get a packet, treat this as playing
		ProcessPacketsPlaying(inInputStream, inFromPlayer);
		break;
	case NMS_Playing:
		ProcessPacketsPlaying(inInputStream, inFromPlayer);
		break;
	case NMS_Delay:
		ProcessPacketsDelay(inInputStream, inFromPlayer);
		break;
	default:
		break;
	}
}

void NetworkManager::ProcessPacketsLobby(InputMemoryBitStream& inInputStream, uint64_t inFromPlayer)
{
	//should only be a ready packet
	uint32_t	packetType;
	inInputStream.Read(packetType);

	switch (packetType)
	{
	case kSelectionCC:
		HandleSelectionPacket(inInputStream, inFromPlayer);
		break;
	case kReadyUpCC:
		handleReadyUpPacket(inInputStream, inFromPlayer);
		break;
	case kReadyCC:
		HandleReadyPacket(inInputStream, inFromPlayer);
		break;
	default:
		//ignore anything else
		break;
	}
}

void NetworkManager::handleReadyUpPacket(InputMemoryBitStream& inInputStream, uint64_t inFromPlayer)
{
	int ready;
	inInputStream.Read(ready);
	LobbyInfoMap::iterator iter = lobbyInfoMap.find(inFromPlayer);
	if (iter != lobbyInfoMap.end()){
		iter->second.ready = ready;
	}
}

void NetworkManager::SendRdyUpPacketToPeers(int ready)
{
	LobbyInfoMap::iterator iter = lobbyInfoMap.find(mPlayerId);
	if (iter != lobbyInfoMap.end()){
		iter->second.ready = ready;
	}
	OutputMemoryBitStream outPacket;
	outPacket.Write(kReadyUpCC);
	outPacket.Write(ready);
	for (auto& iter : mPlayerNameMap)
	{
		if (iter.first != mPlayerId)
		{
			SendReliablePacket(outPacket, iter.first);
		}
	}
}

void NetworkManager::HandleSelectionPacket(InputMemoryBitStream& inInputStream, uint64_t inFromPlayer)
{
	int classType;
	inInputStream.Read(classType);
	LobbyInfoMap::iterator iter = lobbyInfoMap.find(inFromPlayer);
	if (iter != lobbyInfoMap.end()){
		iter->second.classType = classType;
	}
}

void NetworkManager::SendSelectPacketToPeers(int classType)
{
	LobbyInfoMap::iterator iter = lobbyInfoMap.find(mPlayerId);
	if (iter != lobbyInfoMap.end()){
		iter->second.classType = classType;
	}
	OutputMemoryBitStream outPacket;
	outPacket.Write(kSelectionCC);
	outPacket.Write(classType);
	for (auto& iter : mPlayerNameMap)
	{
		if (iter.first != mPlayerId)
		{
			SendReliablePacket(outPacket, iter.first);
		}
	}
}

void NetworkManager::ProcessPacketsReady(InputMemoryBitStream& inInputStream, uint64_t inFromPlayer)
{
	//could be another ready packet or a start packet
	uint32_t	packetType;
	inInputStream.Read(packetType);

	switch (packetType)
	{
	case kReadyCC:
		HandleReadyPacket(inInputStream, inFromPlayer);
		break;
	case kStartCC:
		HandleStartPacket(inInputStream, inFromPlayer);
		break;
	default:
		//ignore anything else
		break;
	}
}

void NetworkManager::HandleReadyPacket(InputMemoryBitStream& inInputStream, uint64_t inFromPlayer)
{
	//if this is my first ready packet, I need to let everyone else know I'm ready
	if (mReadyCount == 0)
	{
		//commenting the line below should stop the master peer from forcing all other peers to ready up
		SendReadyPacketsToPeers();
		//I'm ready now also, so an extra increment here
		mReadyCount++;
		mState = NMS_Ready;
	}

	mReadyCount++;

	TryStartGame();
}

void NetworkManager::SendReadyPacketsToPeers()
{
	OutputMemoryBitStream outPacket;
	outPacket.Write(kReadyCC);
	for (auto& iter : mPlayerNameMap)
	{
		if (iter.first != mPlayerId)
		{
			SendPacket(outPacket, iter.first);
		}
	}
}

void NetworkManager::SendHelloWorld(){
	OutputMemoryBitStream outPacket;
	uint32_t hello = 42;
	outPacket.Write(hello);
	for (auto& iter : mPlayerNameMap)
	{
		//if (iter.first != mPlayerId)
		//{
		SendPacket(outPacket, iter.first);
		//}
	}
}

void NetworkManager::GetAllPlayersInLobby(){
	for (auto& iter : mPlayerNameMap){
		std::cout << iter.first << " " << iter.second << std::endl;
	}
}

void NetworkManager::HandleStartPacket(InputMemoryBitStream& inInputStream, uint64_t inFromPlayer)
{
	//make sure this is the master peer, cause we don't want any funny business
	if (inFromPlayer == mMasterPeerId)
	{
		LogManager* log = LogManager::GetLogManager();
		log->logBuffer << "Got the orders to go! NetworkManager::HandleStartPacket";
		log->flush();
		//get the rng seed
		/*uint32_t seed;
		inInputStream.Read(seed);
		RandGen::sInstance->Seed(seed);*/
		//for now, assume that we're one frame off, but ideally we would RTT to adjust
		//the time to start, based on latency/jitter
		mState = NMS_Starting;
		//mTimeToStart = kStartDelay - Timing::sInstance.GetDeltaTime();
	}
}

void NetworkManager::ProcessPacketsPlaying(InputMemoryBitStream& inInputStream, uint64_t inFromPlayer)
{
	uint32_t	packetType;
	inInputStream.Read(packetType);

	switch (packetType)
	{
	case kTurnCC:
		HandleTurnPacket(inInputStream, inFromPlayer);
		break;
	case kPosCC:
		HandlePosPacket(inInputStream, inFromPlayer);
	default:
		//ignore anything else
		break;
	}
}

void NetworkManager::HandleTurnPacket(InputMemoryBitStream& inInputStream, uint64_t inFromPlayer)
{
	int turnNum;
	uint64_t playerId;
	inInputStream.Read(turnNum);
	inInputStream.Read(playerId);

	if (playerId != inFromPlayer)
	{
		LogManager* log = LogManager::GetLogManager();
		log->logBuffer << "Cheating attempted? We received turn data for a different playerID. NetworkManager::HandleTurnPacket";
		log->flush();
		return;
	}

	/*TurnData data;
	data.Read(inInputStream);

	mTurnData[turnNum].emplace(playerId, data);*/
}

void NetworkManager::ProcessPacketsDelay(InputMemoryBitStream& inInputStream, uint64_t inFromPlayer)
{
	//the only packet we can even consider here is an input one, since we
	//only can only enter delay after we've been playing
	uint32_t	packetType;
	inInputStream.Read(packetType);

	if (packetType == kTurnCC)
	{
		HandleTurnPacket(inInputStream, inFromPlayer);
		//if we're lucky, maybe this was the packet we were waiting on?
		TryAdvanceTurn();
	}
}

void NetworkManager::HandleConnectionReset(uint64_t inFromPlayer)
{
	//remove this player from our maps
	if (mPlayerNameMap.find(inFromPlayer) != mPlayerNameMap.end())
	{
		LogManager* log = LogManager::GetLogManager();
		log->logBuffer << "Player %llu disconnected. NetworkManager::HandleConnectionReset\n", inFromPlayer;
		log->flush();
		mPlayerNameMap.erase(inFromPlayer);
		lobbyInfoMap.erase(inFromPlayer);
		//Commented out: Code to update scoreboard
		//ScoreBoardManager::sInstance->RemoveEntry(inFromPlayer);

		mPlayerCount--;

		//if we were in delay, then let's see if we can continue now that this player DC'd?
		if (mState == NMS_Delay)
		{
			TryAdvanceTurn();
		}
	}
}

void NetworkManager::ReadIncomingPacketsIntoQueue()
{
	//should we just keep a static one?
	char packetMem[1500];
	size_t packetSize = sizeof(packetMem);
	uint32_t incomingSize = 0;
	InputMemoryBitStream inputStream(packetMem, packetSize * 8);
	uint64_t fromPlayer;

	//keep reading until we don't have anything to read ( or we hit a max number that we'll process per frame )
	int receivedPackedCount = 0;
	int totalReadByteCount = 0;

	while (GamerServices::sInstance->IsP2PPacketAvailable(incomingSize) &&
		receivedPackedCount < kMaxPacketsPerFrameCount)
	{
		if (incomingSize <= packetSize)
		{
			uint32_t readByteCount = GamerServices::sInstance->ReadP2PPacket(packetMem, packetSize, fromPlayer);
			if (readByteCount > 0)
			{
				inputStream.ResetToCapacity(readByteCount);
				++receivedPackedCount;
				totalReadByteCount += readByteCount;

				//shove the packet into the queue and we'll handle it as soon as we should...
				//we'll pretend it wasn't received until simulated latency from now
				//this doesn't sim jitter, for that we would need to.....
				float simulatedReceivedTime = Timing::sInstance.GetTimef() + mSimulatedLatency;

				mPacketQueue.emplace(simulatedReceivedTime, inputStream, fromPlayer);
			}
		}
	}

	if (totalReadByteCount > 0)
	{
		mBytesReceivedPerSecond.UpdatePerSecond(static_cast< float >(totalReadByteCount));
	}
}

void NetworkManager::ProcessQueuedPackets()
{
	//look at the front packet...
	while (!mPacketQueue.empty())
	{
		ReceivedPacket& nextPacket = mPacketQueue.front();
		if (Timing::sInstance.GetTimef() > nextPacket.GetReceivedTime())
		{
			ProcessPacket(nextPacket.GetPacketBuffer(), nextPacket.GetFromPlayer());
			mPacketQueue.pop();
		}
		else
		{
			break;
		}
	}
}

/*Most of the EnterPlayingState() code does not apply to our game!!!*/
void NetworkManager::EnterPlayingState()
{
	mState = NMS_Playing;

	//leave the lobby now that we're playing
	GamerServices::sInstance->LeaveLobby(mLobbyId);

	LogManager* log = LogManager::GetLogManager();
	log->logBuffer << "Succesfully entered EnterPlayingState!\n";
	log->flush();
}

void NetworkManager::CheckForAchievements()
{
	for (int i = 0; i < GamerServices::MAX_ACHIEVEMENT; ++i)
	{
		GamerServices::Achievement ach = static_cast< GamerServices::Achievement >(i);
		switch (ach)
		{
		case GamerServices::ACH_WIN_ONE_GAME:
			if (GamerServices::sInstance->GetStatInt(GamerServices::Stat_NumWins) > 0)
			{
				GamerServices::sInstance->UnlockAchievement(ach);
			}
			break;
		case GamerServices::ACH_WIN_100_GAMES:
			if (GamerServices::sInstance->GetStatInt(GamerServices::Stat_NumWins) >= 100)
			{
				GamerServices::sInstance->UnlockAchievement(ach);
			}
			break;
		case GamerServices::ACH_TRAVEL_FAR_ACCUM:
		case GamerServices::ACH_TRAVEL_FAR_SINGLE:
		default:
			//nothing for these
			break;
		}
	}
}

bool NetworkManager::CheckSync(Int64ToTurnDataMap& inTurnMap)
{
	auto iter = inTurnMap.begin();

	uint32_t expectedRand = iter->second.GetRandomValue();
	uint32_t expectedCRC = iter->second.GetCRC();

	++iter;
	while (iter != inTurnMap.end())
	{
		if (expectedRand != iter->second.GetRandomValue())
		{
			LogManager* log = LogManager::GetLogManager();
			log->logBuffer << "Random is out of sync for player %llu on turn %d", iter->second.GetPlayerId(), mTurnNumber;
			log->flush();
			return false;
		}

		if (expectedCRC != iter->second.GetCRC())
		{
			LogManager* log = LogManager::GetLogManager();
			log->logBuffer << "CRC is out of sync for player %llu on turn %d", iter->second.GetPlayerId(), mTurnNumber;
			log->flush();
			return false;
		}
		++iter;
	}

	return true;
}

void NetworkManager::SendPacket(const OutputMemoryBitStream& inOutputStream, uint64_t inToPlayer)
{
	GamerServices::sInstance->SendP2PUnreliable(inOutputStream, inToPlayer);
}

void NetworkManager::SendReliablePacket(const OutputMemoryBitStream& inOutputStream, uint64_t inToPlayer)
{
	GamerServices::sInstance->SendP2PReliable(inOutputStream, inToPlayer);
}

void NetworkManager::EnterLobby(uint64_t inLobbyId)
{
	mLobbyId = inLobbyId;
	mState = NMS_Lobby;
	UpdateLobbyPlayers();
}

void NetworkManager::UpdateLobbyPlayers()
{
	//we only want to update player counts in lobby before we're starting
	if (mState < NMS_Starting)
	{
		mPlayerCount = GamerServices::sInstance->GetLobbyNumPlayers(mLobbyId);
		mMasterPeerId = GamerServices::sInstance->GetMasterPeerId(mLobbyId);
		//am I the master peer now?
		if (mMasterPeerId == mPlayerId)
		{
			mIsMasterPeer = true;
		}

		GamerServices::sInstance->GetLobbyPlayerMap(mLobbyId, mPlayerNameMap);
		for (auto& iter : mPlayerNameMap)
		{
			if (lobbyInfoMap.find(iter.first) == lobbyInfoMap.end()){
				PlayerInfo pInfo;
				pInfo.classType = (int)iter.first;
				lobbyInfoMap.emplace(iter.first, pInfo);
			}
		}
		if (mPlayerNameMap.size() != lobbyInfoMap.size()){
			for (auto it = lobbyInfoMap.begin(); it != lobbyInfoMap.end();) {
				if (mPlayerNameMap.find(it->first) == mPlayerNameMap.end()) {
					it = lobbyInfoMap.erase(it);
				}
				else
					++it;
			}
		}

		//std::cout << "--------------------------------------" << std::endl;
		//for (auto& iter : lobbyInfoMap)
		//{
		//	std::cout << iter.first << " " << iter.second.classType << std::endl;
		//}
		//std::cout << "--------------------------------------" << std::endl;

		//this might allow us to start
		TryStartGame();
	}
}

void NetworkManager::TryStartGame()
{
	//i am master peer and i have received ready's from all players
	if (mState == NMS_Ready && IsMasterPeer() && mPlayerCount == mReadyCount)
	{
		LogManager* log = LogManager::GetLogManager();
		log->logBuffer << "Starting! NetworkManager::TryStartGame";
		log->flush();
		//let everyone know
		OutputMemoryBitStream outPacket;
		outPacket.Write(kStartCC);

		//select a seed value
		/*uint32_t seed = RandGen::sInstance->GetRandomUInt32(0, UINT32_MAX);
		RandGen::sInstance->Seed(seed);
		outPacket.Write(seed);
		*/
		for (auto &iter : mPlayerNameMap)
		{
			if (iter.first != mPlayerId)
			{
				SendPacket(outPacket, iter.first);
			}
		}

		//mTimeToStart = kStartDelay;
		mState = NMS_Starting;
	}
}

void NetworkManager::TryReadyGame()
{
	// i am master peer, ready-ing up and try to start the game
	if (mState == NMS_Lobby && IsMasterPeer())
	{
		LogManager* log = LogManager::GetLogManager();
		log->logBuffer << "Master peer readying up! NetworkManager::TryReadyGame";
		log->flush();
		//let the gamer services know we're readying up
		GamerServices::sInstance->SetLobbyReady(mLobbyId);

		SendReadyPacketsToPeers();

		mReadyCount = 1;
		mState = NMS_Ready;

		//we might be ready to start
		TryStartGame();
	}
	// i am not master peeer, send ready message to other peers
	//else if(mState == NMS_Lobby) {
	//	LogManager* log = LogManager::GetLogManager();
	//	log->logBuffer << "Peer readying up! NetworkManager::TryReadyGame";
	//	log->flush();
	//	//let the gamer services know we're readying up
	//	GamerServices::sInstance->SetLobbyReady(mLobbyId);

	//	SendReadyPacketsToPeers();

	//	mState = NMS_Ready;
	//}
}

void NetworkManager::UpdateBytesSentLastFrame()
{
	if (mBytesSentThisFrame > 0)
	{
		mBytesSentPerSecond.UpdatePerSecond(static_cast< float >(mBytesSentThisFrame));

		mBytesSentThisFrame = 0;
	}

}

NetworkManager::ReceivedPacket::ReceivedPacket(float inReceivedTime, InputMemoryBitStream& ioInputMemoryBitStream, uint64_t inFromPlayer) :
mReceivedTime(inReceivedTime),
mFromPlayer(inFromPlayer),
mPacketBuffer(ioInputMemoryBitStream)
{
}


bool NetworkManager::IsPlayerInGame(uint64_t inPlayerId)
{
	if (mPlayerNameMap.find(inPlayerId) != mPlayerNameMap.end())
	{
		return true;
	}
	else
	{
		return false;
	}
}

uint32_t NetworkManager::GetNewNetworkId()
{
	uint32_t toRet = mNewNetworkId++;
	if (mNewNetworkId < toRet)
	{
		LogManager* log = LogManager::GetLogManager();
		log->logBuffer << "Network ID Wrap Around! NetworkManager::GetNewNetworkId";
		log->flush();
	}

	return toRet;
}

uint32_t NetworkManager::ComputeGlobalCRC()
{
	//save into bit stream to reduce CRC calls
	OutputMemoryBitStream crcStream;
	uint32_t crc = static_cast<uint32_t>(crc32(0, Z_NULL, 0));
	/*Commented out b/c mNetworkIdToGameObjectMap doesn't exist Still TO DO
	for (auto& iter : mNetworkIdToGameObjectMap)
	{
	iter.second->WriteForCRC(crcStream);
	}*/

	crc = static_cast<uint32_t>(crc32(crc, reinterpret_cast<const Bytef*>(crcStream.GetBufferPtr()), crcStream.GetByteLength()));
	return crc;
}

void NetworkManager::sendPacketToAllPeers(OutputMemoryBitStream& outData){
	for (auto &iter : mPlayerNameMap)
	{
		if (iter.first != mPlayerId)
		{
			SendPacket(outData, iter.first);
		}
	}
}

void NetworkManager::HandlePosPacket(InputMemoryBitStream& inInputStream, uint64_t inFromPlayer){
	test.push(inInputStream);
}

uint64_t NetworkManager::GetLobbyId(){
	return mLobbyId;
}