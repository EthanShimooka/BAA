#include "include\network\NetIncludes.h"
#include "include\LogManager.h"

//Reads inputstream and returns commandptr of appropriate command
shared_ptr< Command > Command::StaticReadAndCreate(InputMemoryBitStream& inInputStream)
{
	CommandPtr retVal;

	int type = CM_INVALID;
	inInputStream.Read(type);
	uint32_t networkId = 0;
	inInputStream.Read(networkId);
	uint64_t playerId = 0;
	inInputStream.Read(playerId);
	
	switch (type)
	{
	case CM_ATTACK:
		retVal = std::make_shared< AttackCommand >();
		retVal->mNetworkId = networkId;
		retVal->mPlayerId = playerId;
		retVal->Read(inInputStream);
		break;
	case CM_MOVE:
		retVal = std::make_shared< MoveCommand >();
		retVal->mNetworkId = networkId;
		retVal->mPlayerId = playerId;
		retVal->Read(inInputStream);
		break;
	default:
		LogManager* log = LogManager::GetLogManager();
		log->logBuffer << "Error code 400: Read in an unknown command type: Command.cpp Command::StaticReadAndCreate\n";
		break;
	}
	
	return retVal;
}

//Writes a command to output stream
void Command::Write(OutputMemoryBitStream& inOutputStream)
{
	inOutputStream.Write(mCommandType);
	inOutputStream.Write(mNetworkId);
	inOutputStream.Write(mPlayerId);
}

AttackCommandPtr AttackCommand::StaticCreate(uint32_t inMyNetId, uint32_t inTargetNetId)
{
	AttackCommandPtr retVal;
	/*
	To implement
	*/
	return retVal;
}

void AttackCommand::Write(OutputMemoryBitStream& inOutputStream)
{
	Command::Write(inOutputStream);
	inOutputStream.Write(mTargetNetId);
}

void AttackCommand::Read(InputMemoryBitStream& inInputStream)
{
	inInputStream.Read(mTargetNetId);
}

void AttackCommand::ProcessCommand()
{
	/*
	To implement
	*/
}

MoveCommandPtr MoveCommand::StaticCreate(uint32_t inNetworkId)
{
	MoveCommandPtr retVal;
	/*
	To implement
	*/
	return retVal;
}

void MoveCommand::Write(OutputMemoryBitStream& inOutputStream)
{
	Command::Write(inOutputStream);
	//inOutputStream.Write(mTarget);
}

void MoveCommand::ProcessCommand()
{
	/*
	To implement
	*/
}

void MoveCommand::Read(InputMemoryBitStream& inInputStream)
{
	//inInputStream.Read(mTarget);
}