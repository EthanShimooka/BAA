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
	/// Returns the number of seconds left on the game clock, used for displaying countdown timer
	SQUADIO_API double GetTimeRemainingS();

private:
	float		mDeltaTime;
	uint64_t	mDeltaTick;

	double		gameLengthInSeconds;
	time_t		startTimeInSeconds;
	double		mLastFrameStartTime;
	float		mFrameStartTimef;
	double		mPerfCountDuration;

};
#endif