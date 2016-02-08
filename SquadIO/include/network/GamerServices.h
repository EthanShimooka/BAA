#ifndef GAMERSERVICES_H_INCLUDED
#define GAMERSERVICES_H_INCLUDED
/**
* GamerServices is a base class used to incorporate multiple gamerservices. Our steamworks integration is built on top of it, but we could also use
* it as a base for Xbox, Playstation, or other integrations.
*
*/
class GamerServices
{
public:
	/// Connects to steam to initialize gamerservices
	SQUADIO_API static bool StaticInit();
	/// Access point for gamerservices
	SQUADIO_API static std::unique_ptr< GamerServices >	sInstance;

	//general player functions
	/// Returns steam player id
	uint64_t GetLocalPlayerId();
	/// Returns own steam player name
	SQUADIO_API string GetLocalPlayerName();
	/// Returns steam player name of player associated with player Id
	SQUADIO_API string GetRemotePlayerName( uint64_t inPlayerId );

	//lobby functions
	/// Attempt connection to lobby
	void LobbySearchAsync();
	/// Returns number of players in lobby
	int GetLobbyNumPlayers( uint64_t inLobbyId );
	/// Returns master peer id
	uint64_t GetMasterPeerId( uint64_t inLobbyId );
	/// Returns map of players in lobby
	void GetLobbyPlayerMap( uint64_t inLobbyId, map< uint64_t, string >& outPlayerMap );
	/// Sets lobby status to ready for the player with lobby Id
	void SetLobbyReady( uint64_t inLobbyId );
	/// Has player with lobby Id leave the lobby
	void LeaveLobby( uint64_t inLobbyId );

	//peer-to-peer networking
	/// Sends TCP packets
	bool SendP2PReliable( const OutputMemoryBitStream& inOutputStream, uint64_t inToPlayer );
	/// Checks for available packets
	bool IsP2PPacketAvailable( uint32_t& outPacketSize );
	/// Reads a network packet
	uint32_t ReadP2PPacket( void* inToReceive, uint32_t inMaxLength, uint64_t& outFromPlayer );

	/// Enum of steam statistics
	enum Stat
	{
		#define STAT(a,b) Stat_##a,
		#include "steam\Stats.def"
		#undef STAT
		MAX_STAT
	};
	/// Enum of steam statistic types
	enum class StatType
	{
		INT,
		FLOAT,
		AVGRATE
	};

	int GetStatInt( Stat inStat );
//	float GetStatFloat( Stat inStat );
//	float GetStatAvgRate( Stat inStat );

	//for int/float stats, we can just add to the stat and write to the server immediately
//	void AddToStat( Stat inStat, int inInc );
//	void AddToStat( Stat inStat, float inInc );
	//for average rate stats, we first update the locally cached values
	//then write the average rate for the interval to the server, resetting the local cache
//	void UpdateAvgRateLocal( Stat inStat, float inIncValue, float inIncSeconds );
//	void WriteAvgRate( Stat inStat );
protected:
	/// Retrieves steam player statistics
	void RetrieveStatsAsync();
public:

	/// Enum of steam achievements
	enum Achievement
	{
		#define ACH(a) a,
		#include "steam\Achieve.def"
		#undef ACH
		MAX_ACHIEVEMENT
	};
	/// Checks if achievement is unlocked
	bool IsAchievementUnlocked( Achievement inAch );
	/// Sets given achievement to unlocked for that player
	void UnlockAchievement( Achievement inAch );

	/// Enum of steam leaderboards
	enum Leaderboard
	{
		#define BOARD(a,b,c) LB_##a,
		#include "steam\Leaderboards.def"
		#undef BOARD
		MAX_LEADERBOARD
	};
	
//	void UploadLeaderboardScoreAsync( Leaderboard inLead, int inScore );
//	void DownloadLeaderboardAsync( Leaderboard inLead );
protected:
	/// Retrieves steam player leaderboards
	void RetrieveLeaderboardsAsync();
	/// Finds a leaderboard
	void FindLeaderboardAsync( Leaderboard inLead );
public:
	/// Called every frame, fires callbacks
	SQUADIO_API void Update();
	/// Destructor
	~GamerServices();
	/// Implementation struct
	struct Impl;

	/// Debugging
	void DebugResetStats( bool inResetAchieves );
private:
	/// Constructor
	GamerServices();
	
	std::unique_ptr< Impl > mImpl;
};
#endif