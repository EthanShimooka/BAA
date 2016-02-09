#ifndef RANDGEN_H_INCLUDED
#define RANDGEN_H_INCLUDED
/**
* Random number generator, used in synchronization
* 
*/
class RandGen
{
public:
	/// Access variable for the class
	static std::unique_ptr< RandGen > sInstance;
	/// Constructor
	RandGen();
	/// Initializes the random number generator
	static void StaticInit();
	/// Sets the seed
	void Seed(uint32_t inSeed);
	/// Returns the generator reference
	std::mt19937& GetGeneratorRef() { return mGenerator; }
	/// Returns a random float
	float GetRandomFloat();
	/// Returns a random uint32
	uint32_t GetRandomUInt32(uint32_t inMin, uint32_t inMax);
	/// Returns a random int32
	int32_t GetRandomInt(int32_t inMin, int32_t inMax);
	/// Returns a random Vector3
	Vector3 GetRandomVector(const Vector3& inMin, const Vector3& inMax);
private:
	std::mt19937 mGenerator;
	std::uniform_real_distribution< float > mFloatDistr;
};
#endif