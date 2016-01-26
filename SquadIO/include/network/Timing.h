class Timing
{
public:

	Timing();

	void Update();

	SQUADIO_API float GetDeltaTime() const { return mDeltaTime; }

	double GetTime() const;

	float GetTimef() const
	{
		return static_cast< float >(GetTime());
	}

	float GetFrameStartTime() const { return mFrameStartTimef; }


	SQUADIO_API static Timing sInstance;

private:
	float		mDeltaTime;
	uint64_t	mDeltaTick;

	double		mLastFrameStartTime;
	float		mFrameStartTimef;
	double		mPerfCountDuration;

};