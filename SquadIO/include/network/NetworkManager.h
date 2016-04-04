#ifndef NETWORKMANAGER_H_INCLUDED
#define NETWORKMANAGER_H_INCLUDED
/**
* NetworkManager is the overarching network class to handle sending packets. It uses MemoryBitStream to read/write into a bitstream,
* and communicates with SceneManager to send and receive packets. It communicates with GamerServices to handle the initial connection.
*
*/
class NetworkManager
{
public:
	/// Contains data for a particular turn
	static const uint32_t	kTurnCC = 'TURN';
	/// Notification used to ready up
	static const uint32_t	kReadyCC = 'REDY';
	/// Notifies peers that the game will be starting soon
	static const uint32_t	kStartCC = 'STRT';
	/// Used to ping a peer when in delay
	static const uint32_t	kDelayCC = 'DELY';

	static const uint32_t	kPosCC = 'POSI';

	static const int		kMaxPacketsPerFrameCount = 10;
	/// Enum describing different states the networkmanager can enter. Uninit, Searching, Lobby, Ready are all pre-game/lobby/connection
	enum NetworkManagerState
	{
		NMS_Unitialized,
		NMS_Searching,
		NMS_Lobby,
		NMS_Ready,
		NMS_MainMenu,
		//everything above this should be the pre-game/lobby/connection
		NMS_Starting,
		NMS_Playing,
		NMS_Delay,
		NMS_SinglePlayer,
	};


	/////////////////////////////
	
	SQUADIO_API void sendPacketToAllPeers(OutputMemoryBitStream& outData);
	SQUADIO_API void HandlePosPacket(InputMemoryBitStream& inInputStream, uint64_t inFromPlayer);
	///////////////////////

	//SQUADIO_API static NetworkManager networkManager; //local singleton instance of class


	//SQUADIO_API static NetworkManager * GetNetworkManager(); //singleton class accessor

	/// Access point for network manager
	SQUADIO_API static unique_ptr< NetworkManager >	sInstance;

	/// Initializes networkmanager
	SQUADIO_API static bool	StaticInit();
	/// Initialize lobby search
	SQUADIO_API void startLobbySearch();
	/// Constructor
	SQUADIO_API NetworkManager();
	/// Destructor
	SQUADIO_API ~NetworkManager();
	/// Processes incoming packets
	SQUADIO_API void	ProcessIncomingPackets();
	/// Sends outgoing packets if state is starting or playing
	SQUADIO_API void	SendOutgoingPackets();
	/// Updates everything when state is delay
	SQUADIO_API void	UpdateDelay();
	/// Sets the current network state
	SQUADIO_API void	SetState(NetworkManagerState state);
private:
	SQUADIO_API void	UpdateSayingHello(bool inForce = false);
	SQUADIO_API void	SendHelloPacket();
	/// Updates starting time
	SQUADIO_API void	UpdateStarting();
	/// Updates send turn packets
	SQUADIO_API void	UpdateSendTurnPacket();
	/// Attempts to advance the turn
	SQUADIO_API void	TryAdvanceTurn();
public:
	/// Switches processing packets based on state
	SQUADIO_API void	ProcessPacket(InputMemoryBitStream& inInputStream, uint64_t inFromPlayer);
private:
	/// Processes packets while in lobby state
	SQUADIO_API void	ProcessPacketsLobby(InputMemoryBitStream& inInputStream, uint64_t inFromPlayer);
	/// Processes packets while in ready state
	SQUADIO_API void	ProcessPacketsReady(InputMemoryBitStream& inInputStream, uint64_t inFromPlayer);
	/// Handles transitioning to ready state
	SQUADIO_API void	HandleReadyPacket(InputMemoryBitStream& inInputStream, uint64_t inFromPlayer);
	/// Sends a ready packet to all peers
	SQUADIO_API void	SendReadyPacketsToPeers();
	/// Handles start if start packet received from master peer
	SQUADIO_API void	HandleStartPacket(InputMemoryBitStream& inInputStream, uint64_t inFromPlayer);
	/// Processes packets while in start or playing state
	SQUADIO_API void	ProcessPacketsPlaying(InputMemoryBitStream& inInputStream, uint64_t inFromPlayer);
	/// Handles packets on each turn
	SQUADIO_API void	HandleTurnPacket(InputMemoryBitStream& inInputStream, uint64_t inFromPlayer);
	/// Processes delay packets
	SQUADIO_API void	ProcessPacketsDelay(InputMemoryBitStream& inInputStream, uint64_t inFromPlayer);
	/// Attempts to start the game
	SQUADIO_API void	TryStartGame();
public:
	/// Gets Lobby Id
	SQUADIO_API uint64_t GetLobbyId();
	/// Handles player disconnecting mid-game
	SQUADIO_API void	HandleConnectionReset(uint64_t inFromPlayer);
	/// Calls Gamerservices to send reliable packet
	SQUADIO_API void	SendPacket(const OutputMemoryBitStream& inOutputStream, uint64_t inToPlayer);
	/// Sends hello world. For testing
	SQUADIO_API void    SendHelloWorld();
	/// Prints to cout all players in lobby
	SQUADIO_API void	GetAllPlayersInLobby();
	/// Attempts to enter a lobby
	SQUADIO_API void	EnterLobby(uint64_t inLobbyId);
	/// Updates the number of players in our lobby as long as game hasn't started yet
	SQUADIO_API void	UpdateLobbyPlayers();
	/// Attempts to set lobby to ready
	SQUADIO_API void	TryReadyGame();
	/// Returns bytes received per second
	SQUADIO_API const WeightedTimedMovingAverage& GetBytesReceivedPerSecond()	const	{ return mBytesReceivedPerSecond; }
	/// Returns bytes sent per second
	SQUADIO_API const WeightedTimedMovingAverage& GetBytesSentPerSecond()		const	{ return mBytesSentPerSecond; }
	/// Sets the drop packet chance
	SQUADIO_API void	SetDropPacketChance(float inChance)	{ mDropPacketChance = inChance; }
	/// Gets the drop packet chance
	SQUADIO_API float	GetDropPacketChance() const				{ return mDropPacketChance; }
	/// Sets simulated latency
	SQUADIO_API void	SetSimulatedLatency(float inLatency)	{ mSimulatedLatency = inLatency; }
	/// Gets simulated latency
	SQUADIO_API float	GetSimulatedLatency() const				{ return mSimulatedLatency; }
	/// Returns true if player is master peer
	SQUADIO_API bool	IsMasterPeer() const { return mIsMasterPeer; }
	/// Returns time to start
	SQUADIO_API float	GetTimeToStart() const { return mTimeToStart; }

	//	GameObjectPtr	GetGameObject(uint32_t inNetworkId) const;
	//	GameObjectPtr	RegisterAndReturn(GameObject* inGameObject);
	//	void			UnregisterGameObject(GameObject* inGameObject);
	SQUADIO_API map< uint64_t, string >  getLobbyMap() const { return mPlayerNameMap; }

//	GameObjectPtr	GetGameObject(uint32_t inNetworkId) const;
//	GameObjectPtr	RegisterAndReturn(GameObject* inGameObject);
//	void			UnregisterGameObject(GameObject* inGameObject);
	/// Returns networkmanager state
	SQUADIO_API NetworkManagerState GetState() const { return mState; }
	/// Returns number of players in lobby who are ready
	int		GetReadyCount() const { return mReadyCount; }
	/// Returns number of players
	int		GetPlayerCount() const { return mPlayerCount; }
	/// Returns the turn number
	int		GetTurnNumber() const { return mTurnNumber; }
	/// Returns the sub turn number
	int		GetSubTurnNumber() const { return mSubTurnNumber; }
	/// Returns our own player id
	uint64_t GetMyPlayerId() const { return mPlayerId; }
	/// Returns true if player with player Id is in game
	bool	IsPlayerInGame(uint64_t inPlayerId);


	///////////////////////////////////
	queue<InputMemoryBitStream> test;
	///////////////////////////////////


private:
	//	void	AddToNetworkIdToGameObjectMap(GameObjectPtr inGameObject);
	//	void	RemoveFromNetworkIdToGameObjectMap(GameObjectPtr inGameObject);
	//	void	RegisterGameObject(GameObjectPtr inGameObject);
	/// Returns new network Id
	uint32_t GetNewNetworkId();
	/// Computes CRC value
	uint32_t ComputeGlobalCRC();
	/// Initializes networkmanager, called by StaticInit
	bool	Init();
	/**
	* ReceivedPacket is a class encapsulated within the NetworkManager class, used for receiving packets
	*
	*/
	class ReceivedPacket
	{
	public:
		/// Constructor
		ReceivedPacket(float inReceivedTime, InputMemoryBitStream& inInputMemoryBitStream, uint64_t inFromPlayer);
		/// Returns player packet was sent from
		uint64_t				GetFromPlayer()		const	{ return mFromPlayer; }
		/// Returns the time packet was received
		float					GetReceivedTime()	const	{ return mReceivedTime; }
		/// Returns packet buffer
		InputMemoryBitStream&	GetPacketBuffer()			{ return mPacketBuffer; }

	private:

		float					mReceivedTime;
		InputMemoryBitStream	mPacketBuffer;
		uint64_t				mFromPlayer;

	};
	/// Updates the bytes sent last frame
	void	UpdateBytesSentLastFrame();
	/// Reads incoming packets into a queue
	void	ReadIncomingPacketsIntoQueue();
	/// Processes the queued packets
	void	ProcessQueuedPackets();
	/// Enters playing state
	void	EnterPlayingState();
	//	void	SpawnCat(uint64_t inPlayerId, const Vector3& inSpawnVec);
	/// Checks for steam achievements
	void	CheckForAchievements();

	//these should stay ordered!
	/// Map of ints to strings
	typedef map< uint64_t, string > Int64ToStrMap;
	/// Map of ints to turndata
	typedef map< uint64_t, TurnData > Int64ToTurnDataMap;
	//	typedef map< uint32_t, GameObjectPtr > IntToGameObjectMap;
	//	typedef map< uint32_t, GameObjectPtr > IntToGameObjectMap;
	/// Data structure holding ints 1-8 mapped to player steam IDs
	typedef map< uint8_t, uint64_t > PlayerNumToSteamIdMap;
	/// Checks for synchronization
	bool	CheckSync(Int64ToTurnDataMap& inTurnMap);
	/// Queue of received packets
	queue< ReceivedPacket, list< ReceivedPacket > >	mPacketQueue;

	//	IntToGameObjectMap			mNetworkIdToGameObjectMap;
	Int64ToStrMap				mPlayerNameMap;

	//this stores all of our turn information for every turn since game start
	/// Vector of turndata
	vector< Int64ToTurnDataMap >	mTurnData;
	/// Bytes received per second
	WeightedTimedMovingAverage	mBytesReceivedPerSecond;
	/// Bytes sent per second
	WeightedTimedMovingAverage	mBytesSentPerSecond;
	/// Access variable of networkmanager state
	NetworkManagerState			mState;
	/// Bytes sent this frame
	int							mBytesSentThisFrame;
	/// Name
	std::string		mName;
	/// Chance of dropping a packet
	float			mDropPacketChance;
	/// Simulated latency
	float			mSimulatedLatency;
	/// Delay heartbeat
	float			mDelayHeartbeat;
	/// Time to start
	float			mTimeToStart;
	/// Player count
	int				mPlayerCount;
	/// Ready count
	int				mReadyCount;
	/// New network Id
	uint32_t		mNewNetworkId;
	/// Player Id
	uint64_t		mPlayerId;
	/// Lobby Id
	uint64_t		mLobbyId;
	/// Master peer Id
	uint64_t		mMasterPeerId;
	/// Turn number
	int				mTurnNumber;
	/// Subturn number
	int				mSubTurnNumber;
	/// isMasterPeer
	bool			mIsMasterPeer;
	/// Command list
	CommandList		mCommandList;
};
#endif