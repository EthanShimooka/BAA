#ifndef MEMORYBITSTREAM_H_INCLUDED
#define MEMORYBITSTREAM_H_INCLUDED
#include <cstdint>
#include <cstdlib>
#include <string>

//class GameObject;

inline uint32_t ConvertToFixed(float inNumber, float inMin, float inPrecision)
{
	return static_cast< int > ((inNumber - inMin) / inPrecision);
}

inline float ConvertFromFixed(uint32_t inNumber, float inMin, float inPrecision)
{
	return static_cast< float >(inNumber)* inPrecision + inMin;
}

/**
* OutputMemoryBitStream is a class used to send bitstreams
*
*/
class OutputMemoryBitStream
{
public:
	/// Constructor
	OutputMemoryBitStream() :
		mBitHead(0),
		mBuffer(nullptr)
	{
		ReallocBuffer(1500 * 8);
	}
	/// Destructor
	~OutputMemoryBitStream()	{ std::free(mBuffer); }
	/// Writes bits
	void		WriteBits(uint8_t inData, size_t inBitCount);
	/// Writes bits
	void		WriteBits(const void* inData, size_t inBitCount);
	/// Returns a buffer pointer
	const 	char*	GetBufferPtr()		const	{ return mBuffer; }
	/// Returns the bitlength
	uint32_t		GetBitLength()		const	{ return mBitHead; }
	/// Returns the byte length
	uint32_t		GetByteLength()		const	{ return (mBitHead + 7) >> 3; }

	void WriteBytes(const void* inData, uint32_t inByteCount)	{ WriteBits(inData, inByteCount << 3); }

	/*
	void Write( uint32_t inData, uint32_t inBitCount = 32 )	{ WriteBits( &inData, inBitCount ); }
	void Write( int inData, uint32_t inBitCount = 32 )		{ WriteBits( &inData, inBitCount ); }
	void Write( float inData )								{ WriteBits( &inData, 32 ); }
	void Write( uint16_t inData, uint32_t inBitCount = 16 )	{ WriteBits( &inData, inBitCount ); }
	void Write( int16_t inData, uint32_t inBitCount = 16 )	{ WriteBits( &inData, inBitCount ); }
	void Write( uint8_t inData, uint32_t inBitCount = 8 )	{ WriteBits( &inData, inBitCount ); }
	*/

	template< typename T >
	void Write(T inData, uint32_t inBitCount = sizeof(T)* 8)
	{
		static_assert(std::is_arithmetic< T >::value ||
			std::is_enum< T >::value,
			"Generic Write only supports primitive data types");
		WriteBits(&inData, inBitCount);
	}

	void 		Write(bool inData)								{ WriteBits(&inData, 1); }
	/// Writes a vector to a bitstream
	void		Write(const Vector3& inVector);
	/// Writes a quaternion to a bitstream
	void		Write(const Quaternion& inQuat);
	/// Writes a string to a bitstream
	void Write(const std::string& inString)
	{
		uint32_t elementCount = static_cast< uint32_t >(inString.size());
		Write(elementCount);
		for (const auto& element : inString)
		{
			Write(element);
		}
	}

private:
	/// Reallocates the buffer to be a new size
	void		ReallocBuffer(uint32_t inNewBitCapacity);
	/// Access variable for buffer
	char*		mBuffer;
	/// Access variable for bithead
	uint32_t	mBitHead;
	/// Access variable for bitcapacity
	uint32_t	mBitCapacity;
};
/**
* InputMemoryBitStream is a class used to read bitstreams
*
*/
class InputMemoryBitStream
{
public:
	/// Constructor
	InputMemoryBitStream(char* inBuffer, uint32_t inBitCount) :
		mBuffer(inBuffer),
		mBitCapacity(inBitCount),
		mBitHead(0),
		mIsBufferOwner(false) {}
	/// Constructor
	InputMemoryBitStream(const InputMemoryBitStream& inOther) :
		mBitCapacity(inOther.mBitCapacity),
		mBitHead(inOther.mBitHead),
		mIsBufferOwner(true)
	{
		//allocate buffer of right size
		int byteCount = mBitCapacity / 8;
		mBuffer = static_cast< char* >(malloc(byteCount));
		//copy
		memcpy(mBuffer, inOther.mBuffer, byteCount);
	}
	/// Destructor
	~InputMemoryBitStream()	{ if (mIsBufferOwner) { free(mBuffer); }; }
	/// Returns a buffer pointer
	const 	char*	GetBufferPtr()		const	{ return mBuffer; }
	/// Returns the remaining number of bits to be read in
	uint32_t	GetRemainingBitCount() 	const { return mBitCapacity - mBitHead; }
	/// Reads bits
	void		ReadBits(uint8_t& outData, uint32_t inBitCount);
	/// Reads bits
	void		ReadBits(void* outData, uint32_t inBitCount);

	void		ReadBytes(void* outData, uint32_t inByteCount)		{ ReadBits(outData, inByteCount << 3); }

	template< typename T >
	void Read(T& inData, uint32_t inBitCount = sizeof(T)* 8)
	{
		static_assert(std::is_arithmetic< T >::value ||
			std::is_enum< T >::value,
			"Generic Read only supports primitive data types");
		ReadBits(&inData, inBitCount);
	}

	void		Read(uint32_t& outData, uint32_t inBitCount = 32)		{ ReadBits(&outData, inBitCount); }
	void		Read(int& outData, uint32_t inBitCount = 32)			{ ReadBits(&outData, inBitCount); }
	void		Read(float& outData)									{ ReadBits(&outData, 32); }

	void		Read(uint16_t& outData, uint32_t inBitCount = 16)		{ ReadBits(&outData, inBitCount); }
	void		Read(int16_t& outData, uint32_t inBitCount = 16)		{ ReadBits(&outData, inBitCount); }

	void		Read(uint8_t& outData, uint32_t inBitCount = 8)		{ ReadBits(&outData, inBitCount); }
	void		Read(bool& outData)									{ ReadBits(&outData, 1); }
	/// Reads a quaternion from a bitstream
	void		Read(Quaternion& outQuat);
	/// Resets the capacity
	void		ResetToCapacity(uint32_t inByteCapacity)				{ mBitCapacity = inByteCapacity << 3; mBitHead = 0; }

	/// Reads a string from a bitstream
	void Read(std::string& inString)
	{
		uint32_t elementCount;
		Read(elementCount);
		inString.resize(elementCount);
		for (auto& element : inString)
		{
			Read(element);
		}
	}
	/// Reads a vector from a bitstream
	void Read(Vector3& inVector);

private:
	/// Access variable for buffer
	char*		mBuffer;
	/// Access variable for bithead
	uint32_t	mBitHead;
	/// Access variable for bitcapacity
	uint32_t	mBitCapacity;
	/// True if owns the buffer
	bool		mIsBufferOwner;

};
#endif