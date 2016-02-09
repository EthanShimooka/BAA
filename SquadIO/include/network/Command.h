#ifndef COMMAND_H_INCLUDED
#define COMMAND_H_INCLUDED
/*
To add: class DieCommand, JumpCommand, AbilityCommand
*/

/**
* Command is the base class for sending different types of network packages
*
*/
class Command
{
public:
	/// Enumeration of command types
	enum ECommandType
	{
		CM_INVALID,
		CM_ATTACK,
		CM_MOVE,
		CM_DIE,
		CM_JUMP,
		CM_ABILITY,
	};
	/// Constructor. Defaults CommandType to Invalid, mNetworkId and mPlayerId to 0
	Command() :
		mCommandType(CM_INVALID),
		mNetworkId(0),
		mPlayerId(0),
		mPacketUID(0)
	{}
	/// Given a buffer, will construct the appropriate command subclass
	static shared_ptr< Command > StaticReadAndCreate(InputMemoryBitStream& inInputStream);
	/// Sets mNetworkId variable
	void SetNetworkId(uint32_t inId) { mNetworkId = inId; }
	/// Gets mNetworkId variable
	int GetNetworkId() const { return mNetworkId; }
	/// Sets mPlayerId variable
	void SetPlayerId(uint64_t inId) { mPlayerId = inId; }
	/// Gets mPlayerId variable
	uint64_t GetPlayerId() const { return mPlayerId; }
	/// Writes a command to output stream
	virtual void Write(OutputMemoryBitStream& inOutputStream);
	/// Virtual function for processing a command, to be overridden
	virtual void ProcessCommand() = 0;
protected:
	/// Reads a command from output stream, to be overridden
	virtual void Read(InputMemoryBitStream& inInputStream) = 0;
	/// Command type variable
	ECommandType mCommandType;
	/// Network Id variable
	uint32_t mNetworkId;
	/// Player Id variable
	uint64_t mPlayerId;
	/// Unique packet identifier
	uint32_t mPacketUID;
};
/// Shared pointer of commands
typedef shared_ptr< Command >	CommandPtr;

/**
* AttackCommand is inherited from the Command class and is used to send and read network packages
* of CommandType CM_ATTACK
*
*/

class AttackCommand : public Command
{
public:
	/// Constructor. Defaults CommandType to Attack, mNetworkId to 0
	AttackCommand() :
		mTargetNetId(0)
	{
		mCommandType = CM_ATTACK;
	}
	/// Unimplemented
	static shared_ptr< AttackCommand > StaticCreate(uint32_t inMyNetId, uint32_t inTargetNetId);
	/// Writes attack commands to an output stream
	virtual void Write(OutputMemoryBitStream& inOutputStream) override;
	/// Processes an attack command. Unimplemented
	virtual void ProcessCommand() override;
protected:
	/// Reads an attack command from an output stream
	virtual void Read(InputMemoryBitStream& inInputStream) override;

	uint32_t mTargetNetId;
};
/// Shared pointer of attack commands
typedef shared_ptr< AttackCommand > AttackCommandPtr;

/**
* MoveCommand is inherited from the Command class and is used to send and read network packages
* of CommandType CM_MOVE
*
*/

class MoveCommand : public Command
{
public:
	/// Constructor. Defaults CommandType to Move
	MoveCommand() :
		xpos(0),
		ypos(0)
	{
		mCommandType = CM_MOVE;
	}
	/// Unimplemented
	static shared_ptr< MoveCommand > StaticCreate(uint32_t inNetworkId, const Vector3& inTarget);
	/// Writes move commands to an output stream
	virtual void Write(OutputMemoryBitStream& inOutputStream) override;
	/// Processes a move command. Unimplemented
	virtual void ProcessCommand() override;
protected:
	/// Reads a move command from an output stream
	virtual void Read(InputMemoryBitStream& inInputStream) override;
	/// Int coordinates to describe player position
	uint16_t xpos, ypos;

	Vector3 mTarget;
};
/// Shared pointer of move commands
typedef shared_ptr< MoveCommand > MoveCommandPtr;
#endif