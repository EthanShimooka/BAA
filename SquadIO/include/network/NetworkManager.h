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
	static const int		kMaxPacketsPerFrameCount = 10;
	/// Enum describing different states the networkmanager can enter. Uninit, Searching, Lobby, Ready are all pre-game/lobby/connection
	enum NetworkManagerState
	{
		NMS_Unitialized,
		NMS_Searching,
		NMS_Lobby,
		NMS_Ready,
		//everything above this should be the pre-game/lobby/connection
		NMS_Starting,
		NMS_Playing,
		NMS_Delay,
	};

	//SQUADIO_API static NetworkManager networkManager; //local singleton instance of class


	//SQUADIO_API static NetworkManager * GetNetworkManager(); //singleton class accessor

	/// Access point for network manager
	SQUADIO_API static unique_ptr< NetworkManager >	sInstance;

	/// Initializes networkmanager
	SQUADIO_API static bool	StaticInit();
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
private:
	SQUADIO_API void	UpdateSayingHello(bool inForce = false);
	SQUADIO_API void	SendHelloPacket();
	/// Updates starting time
	SQUADIO_API void	UpdateStarting();
	/// 
	SQUADIO_API void	UpdateSendTurnPacket();
	SQUADIO_API void	TryAdvanceTurn();
public:

	SQUADIO_API void	ProcessPacket(InputMemoryBitStream& inInputStream, uint64_t inFromPlayer);
private:
	SQUADIO_API void	ProcessPacketsLobby(InputMemoryBitStream& inInputStream, uint64_t inFromPlayer);
	SQUADIO_API void	ProcessPacketsReady(InputMemoryBitStream& inInputStream, uint64_t inFromPlayer);
	SQUADIO_API void	HandleReadyPacket(InputMemoryBitStream& inInputStream, uint64_t inFromPlayer);
	SQUADIO_API void	SendReadyPacketsToPeers();
	SQUADIO_API void	HandleStartPacket(InputMemoryBitStream& inInputStream, uint64_t inFromPlayer);
	SQUADIO_API void	ProcessPacketsPlaying(InputMemoryBitStream& inInputStream, uint64_t inFromPlayer);
	SQUADIO_API void	HandleTurnPacket(InputMemoryBitStream& inInputStream, uint64_t inFromPlayer);
	SQUADIO_API void	ProcessPacketsDelay(InputMemoryBitStream& inInputStream, uint64_t inFromPlayer);
	SQUADIO_API void	TryStartGame();
public:
	SQUADIO_API void	HandleConnectionReset(uint64_t inFromPlayer);

	SQUADIO_API void	SendPacket(const OutputMemoryBitStream& inOutputStream, uint64_t inToPlayer);
	SQUADIO_API void    SendHelloWorld();
	SQUADIO_API void	GetAllPlayersInLobby();

	SQUADIO_API void	EnterLobby(uint64_t inLobbyId);
	SQUADIO_API void	UpdateLobbyPlayers();
	SQUADIO_API void	TryReadyGame();

	SQUADIO_API const WeightedTimedMovingAverage& GetBytesReceivedPerSecond()	const	{ return mBytesReceivedPerSecond; }
	SQUADIO_API const WeightedTimedMovingAverage& GetBytesSentPerSecond()		const	{ return mBytesSentPerSecond; }
	SQUADIO_API void	SetDropPacketChance(float inChance)	{ mDropPacketChance = inChance; }
	SQUADIO_API float	GetDropPacketChance() const				{ return mDropPacketChance; }
	SQUADIO_API void	SetSimulatedLatency(float inLatency)	{ mSimulatedLatency = inLatency; }
	SQUADIO_API float	GetSimulatedLatency() const				{ return mSimulatedLatency; }

	SQUADIO_API bool	IsMasterPeer() const { return mIsMasterPeer; }
	SQUADIO_API float	GetTimeToStart() const { return mTimeToStart; }

//	GameObjectPtr	GetGameObject(uint32_t inNetworkId) const;
//	GameObjectPtr	RegisterAndReturn(GameObject* inGameObject);
//	void			UnregisterGameObject(GameObject* inGameObject);

	SQUADIO_API NetworkManagerState GetState() const { return mState; }
	int		GetReadyCount() const { return mReadyCount; }
	int		GetPlayerCount() const { return mPlayerCount; }
	int		GetTurnNumber() const { return mTurnNumber; }
	int		GetSubTurnNumber() const { return mSubTurnNumber; }
	uint64_t GetMyPlayerId() const { return mPlayerId; }
	bool	IsPlayerInGame(uint64_t inPlayerId);
private:
//	void	AddToNetworkIdToGameObjectMap(GameObjectPtr inGameObject);
//	void	RemoveFromNetworkIdToGameObjectMap(GameObjectPtr inGameObject);
//	void	RegisterGameObject(GameObjectPtr inGameObject);
	uint32_t GetNewNetworkId();
	uint32_t ComputeGlobalCRC();

	bool	Init();

	class ReceivedPacket
	{
	public:
		ReceivedPacket(float inReceivedTime, InputMemoryBitStream& inInputMemoryBitStream, uint64_t inFromPlayer);

		uint64_t				GetFromPlayer()		const	{ return mFromPlayer; }
		float					GetReceivedTime()	const	{ return mReceivedTime; }
		InputMemoryBitStream&	GetPacketBuffer()			{ return mPacketBuffer; }

	private:

		float					mReceivedTime;
		InputMemoryBitStream	mPacketBuffer;
		uint64_t				mFromPlayer;

	};

	void	UpdateBytesSentLastFrame();
	void	ReadIncomingPacketsIntoQueue();
	void	ProcessQueuedPackets();

	void	EnterPlayingState();
//	void	SpawnCat(uint64_t inPlayerId, const Vector3& inSpawnVec);

	void	CheckForAchievements();

	//these should stay ordered!
	typedef map< uint64_t, string > Int64ToStrMap;
	typedef map< uint64_t, TurnData > Int64ToTurnDataMap;
//	typedef map< uint32_t, GameObjectPtr > IntToGameObjectMap;

	bool	CheckSync(Int64ToTurnDataMap& inTurnMap);

	queue< ReceivedPacket, list< ReceivedPacket > >	mPacketQueue;

//	IntToGameObjectMap			mNetworkIdToGameObjectMap;
	Int64ToStrMap				mPlayerNameMap;

	//this stores all of our turn information for every turn since game start
	vector< Int64ToTurnDataMap >	mTurnData;

	WeightedTimedMovingAverage	mBytesReceivedPerSecond;
	WeightedTimedMovingAverage	mBytesSentPerSecond;
	NetworkManagerState			mState;

	int							mBytesSentThisFrame;
	std::string		mName;

	float			mDropPacketChance;
	float			mSimulatedLatency;

	float			mDelayHeartbeat;
	float			mTimeToStart;

	int				mPlayerCount;
	int				mReadyCount;

	uint32_t		mNewNetworkId;
	uint64_t		mPlayerId;
	uint64_t		mLobbyId;
	uint64_t		mMasterPeerId;

	int				mTurnNumber;
	int				mSubTurnNumber;
	bool			mIsMasterPeer;

	CommandList		mCommandList;
};
#endif