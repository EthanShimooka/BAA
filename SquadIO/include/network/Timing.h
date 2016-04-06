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

	SQUADIO_API void StartCountdown();

	SQUADIO_API static Timing sInstance;

	SQUADIO_API void SetCountdownStart();

private:
	float		mDeltaTime;
	uint64_t	mDeltaTick;

	time_t		startTimeInSeconds;
	double		mLastFrameStartTime;
	float		mFrameStartTimef;
	double		mPerfCountDuration;

};
#endif