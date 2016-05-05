#ifndef TIMING_H_INCLUDED
#define TIMING_H_INCLUDED
#include <time.h>
class Timing
{
public:

	Timing();

	SQUADIO_API bool Update();

	SQUADIO_API float GetDeltaTime() const { return mDeltaTime; }

	double GetTime() const;

	float GetTimef() const{
		return static_cast< float >(GetTime());
	}

	float GetFrameStartTime() const { return mFrameStartTimef; }

	SQUADIO_API static Timing sInstance;
	/// Begins the gameclock, called when game begins
	SQUADIO_API void SetCountdownStart();
	/// Starts 
	SQUADIO_API void StartAttackCooldown();
	/// Returns the number of seconds left on the game clock, used for displaying countdown timer
	SQUADIO_API int GetTimeRemainingS();
	/// Takes the time remaining in seconds and returns the minutes to be displayed
	SQUADIO_API string GetMinutesLeftAsString(int timeRemainingInSec);
	/// Takes the time remaining in seconds and returns the seconds to be displayed alongside minutes
	SQUADIO_API string GetSecondsLeftAsString(int timeRemainingInSec);
	/// Returns true if player's attack cooldown has finished
	SQUADIO_API bool AttackCooldownEnded();
	/// Returns true if minions should be spawned
	SQUADIO_API bool SpawnMinions();
	/// Starts the lobby countdown
	SQUADIO_API void SetLobbyCountdown();
	/// Starts the ingame timer countdown
	SQUADIO_API void SetGamePlayCountdown();
	/// Starts the timer for the explosion effect
	SQUADIO_API void StartExplosionTimer();
	/// Returns true if the explosion timer's time is up and the explosion should be removed
	SQUADIO_API bool ExplosionTimerEnded();
	/// Starts timer when quail ability is triggered
	SQUADIO_API void SetQuailAbilityTimer();
	/// Returns true when the quail ability timer is over
	SQUADIO_API bool EndQuailAbilityTimer();
	/// Starts timer when chicken ability is triggered
	SQUADIO_API void SetChickenAbilityTimer();
	/// Returns true when the chicken ability timer is over
	SQUADIO_API bool EndChickenAbilityTimer();
	/// Starts timer when peacock ability is triggered
	SQUADIO_API void SetPeacockAbilityTimer();
	/// Returns true when the peacock ability timer is over
	SQUADIO_API bool EndPeacockAbilityTimer();
private:
	float			mDeltaTime;
	uint64_t		mDeltaTick;

	int				minionCounter;
	int				gameLengthInSeconds;
	time_t			startTimeInSeconds;
	time_t			attackCooldown;

	clock_t			explosionStart;
	clock_t			quailAbilityStart = 0;
	clock_t			chickenAbilityStart = 0;
	
	/* Without a Timer class, need 8 peacockAbilityStart variables
	   to account for up to 8 different fans active at once*/
	clock_t			peacockAbilityStart = 0;
	clock_t			peacockAbilityStart1 = 0;
	clock_t			peacockAbilityStart2 = 0;
	clock_t			peacockAbilityStart3 = 0;
	clock_t			peacockAbilityStart4 = 0;
	clock_t			peacockAbilityStart5 = 0;
	clock_t			peacockAbilityStart6 = 0;
	clock_t			peacockAbilityStart7 = 0;
	clock_t			peacockAbilityStart8 = 0;

	double			mLastFrameStartTime;
	float			mFrameStartTimef;
	double			mPerfCountDuration;

	unsigned int	explosionLengthInMS = 150;
	unsigned int	quailAbilityLengthInMS = 3000;
	unsigned int	chickenAbilityLengthInMS = 5500;
	unsigned int	peacockAbilityLengthInMS = 10000;
	int				playTimeLengthInSecs = 120;
};
#endif