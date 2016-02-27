#include "NetIncludes.h"
#include "include\LogManager.h"


DeliveryNotificationManager::DeliveryNotificationManager() :
//everybody starts at 0...
mNextOutgoingSequenceNumber(0),
mNextExpectedSequenceNumber(0)
{
}


//we're going away- log how well we did...
DeliveryNotificationManager::~DeliveryNotificationManager()
{
	LogManager* log = LogManager::GetLogManager();
	log->logBuffer << "DNM destructor.\n";
	log->flush();
}



void DeliveryNotificationManager::WriteSequenceNumber(OutputMemoryBitStream& inOutputStream)
{
	//write the sequence number, but also create an inflight packet for this...
	PacketSequenceNumber sequenceNumber = mNextOutgoingSequenceNumber++;
	inOutputStream.Write(sequenceNumber);

}

//returns whether to drop the packet- if sequence number is too low!
bool DeliveryNotificationManager::ProcessSequenceNumber(InputMemoryBitStream& inInputStream)
{
	PacketSequenceNumber	sequenceNumber;

	inInputStream.Read(sequenceNumber);
	if (sequenceNumber == mNextExpectedSequenceNumber)
	{
		mNextExpectedSequenceNumber = sequenceNumber + 1;

		//and let's continue processing this packet...
		return true;
	}
	//is the sequence number less than our current expected sequence? silently drop it.
	//if this is due to wrapping around, we might fail to ack some packets that we should ack, but they'll get resent, so it's not a big deal
	//note that we don't have to re-ack it because our system doesn't reuse sequence numbers
	else if (sequenceNumber < mNextExpectedSequenceNumber)
	{
		return false;
	}
	else if (sequenceNumber > mNextExpectedSequenceNumber)
	{
		//we missed a lot of packets!
		//so our next expected packet comes after this one...
		mNextExpectedSequenceNumber = sequenceNumber + 1;
		//we should nack the missing packets..this will happen automatically inside AddPendingAck because
		//we're adding an unconsequitive ack
		//and then we can ack this and process it

		return true;
	}

	//drop packet if we couldn't even read sequence number!
	return false;
}