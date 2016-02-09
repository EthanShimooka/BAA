#ifndef WEIGHTEDTIMEDMOVINGAVERAGE_H_INCLUDED
#define WEIGHTEDTIMEDMOVINGAVERAGE_H_INCLUDED
/**
* WeightedTimedMovingAverage is used in calculating timing
*
*/
class WeightedTimedMovingAverage
{
public:
	/// Constructor
	WeightedTimedMovingAverage(float inDuration = 5.f) :
		mDuration(inDuration),
		mValue(0.f)
	{
		mTimeLastEntryMade = Timing::sInstance.GetTimef();
	}
	/// Updates per second
	void UpdatePerSecond(float inValue)
	{
		float time = Timing::sInstance.GetTimef();
		float timeSinceLastEntry = time - mTimeLastEntryMade;

		float valueOverTime = inValue / timeSinceLastEntry;

		//now update our value by whatever amount of the duration that was..
		float fractionOfDuration = (timeSinceLastEntry / mDuration);
		if (fractionOfDuration > 1.f) { fractionOfDuration = 1.f; }

		mValue = mValue * (1.f - fractionOfDuration) + valueOverTime * fractionOfDuration;

		mTimeLastEntryMade = time;
	}
	/// Updates
	void Update(float inValue)
	{
		float time = Timing::sInstance.GetTimef();
		float timeSinceLastEntry = time - mTimeLastEntryMade;

		//now update our value by whatever amount of the duration that was..
		float fractionOfDuration = (timeSinceLastEntry / mDuration);
		if (fractionOfDuration > 1.f) { fractionOfDuration = 1.f; }

		mValue = mValue * (1.f - fractionOfDuration) + inValue * fractionOfDuration;

		mTimeLastEntryMade = time;
	}
	/// Returns value as float
	float GetValue() const { return mValue; }

private:

	float			mTimeLastEntryMade;
	float			mValue;
	float			mDuration;

};
#endif