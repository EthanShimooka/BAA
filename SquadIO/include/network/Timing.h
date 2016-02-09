#ifndef TIMING_H_INCLUDED
#define TIMING_H_INCLUDED
/**
* Timing class
*
*/
class Timing
{
public:
	/// Constructor
	Timing();
	/// Updates times
	void Update();
	/// Returns delta time
	SQUADIO_API float GetDeltaTime() const { return mDeltaTime; }
	/// Returns time as double
	double GetTime() const;
	/// Returns time as float
	float GetTimef() const
	{
		return static_cast< float >(GetTime());
	}
	/// Returns frame start time
	float GetFrameStartTime() const { return mFrameStartTimef; }

	/// Access variable for Timing class
	SQUADIO_API static Timing sInstance;

private:
	float		mDeltaTime;
	uint64_t	mDeltaTick;

	double		mLastFrameStartTime;
	float		mFrameStartTimef;
	double		mPerfCountDuration;

};
#endif