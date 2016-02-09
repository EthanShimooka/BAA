#ifndef TURNDATA_H_INCLUDED
#define TURNDATA_H_INCLUDED
/**
* Turndata class keeps track of turn information
*
*/
class TurnData
{
public:
	//default constructor exists so we can use it when reading from network
	/// Default constructor
	TurnData() :
		mPlayerId(0),
		mRandomValue(0),
		mCRC(0)
	{ }
	/// Constructor
	TurnData(uint64_t inPlayerId, uint32_t inRandomValue, uint32_t inCRC, CommandList& inCommandList) :
		mPlayerId(inPlayerId),
		mRandomValue(inRandomValue),
		mCRC(inCRC),
		mCommandList(inCommandList)
	{}
	/// Writes turndata to an outputstream
	void Write(OutputMemoryBitStream& inOutputStream);
	/// Reads turndata from an inputstream
	void Read(InputMemoryBitStream& inInputStream);
	/// Returns player Id
	uint64_t GetPlayerId() const { return mPlayerId; }
	/// Returns random value
	uint32_t GetRandomValue() const { return mRandomValue; }
	/// Returns CRC
	uint32_t GetCRC() const { return mCRC; }
	/// Returns command list
	CommandList& GetCommandList() { return mCommandList; }
private:
	uint64_t mPlayerId;
	uint32_t mRandomValue;
	uint32_t mCRC;
	CommandList mCommandList;
};
#endif