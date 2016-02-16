#ifndef DELIVERYNOTIFICATIONMANAGER_H
#define DELIVERYNOTIFICATIONMANAGER_H

/**
*	DeliveryNotificationManager class is in charge of keep track of packet
*	order. For every packet that will be sent, the manager assigns an unique
*	number to the packet. On receipt of packet, the manager checks to see if
*	the packet is the next one expected or not and handles accordingly. 
*/
//in case we decide to change the type of the sequence number to use fewer or more bits
typedef uint16_t	PacketSequenceNumber;

class DeliveryNotificationManager
{
public:

	/// Constructor, initializes sequence variables to 0.
	DeliveryNotificationManager();
	/// Destructor.
	~DeliveryNotificationManager();
	/// Sends a packet to WriteSequenceNumber for packet sequence number.
	SQUADIO_API inline void WriteState(OutputMemoryBitStream& inOutputStream);
	/// Reads in packet and sends to ProcessSequenceNumber, returns false if packet is older than mNextExpectedSequenceNumber.
	SQUADIO_API inline bool ReadAndProcessState(InputMemoryBitStream& inOutputStream);

private:

	/// Writes a unique uint16_t to a packet before being sent.
	void WriteSequenceNumber(OutputMemoryBitStream& inOutputStream);

	/// Returns whether to drop the packet- if sequence number is too low.
	bool ProcessSequenceNumber(InputMemoryBitStream& inInputStream);

	/// Holds next unique uint16_t to send with a packet.
	PacketSequenceNumber mNextOutgoingSequenceNumber;
	/// Holds an unique uint16_t that is expected to see when next packet arrives.
	PacketSequenceNumber mNextExpectedSequenceNumber;

};

inline void DeliveryNotificationManager::WriteState(OutputMemoryBitStream& inOutputStream)
{
	WriteSequenceNumber(inOutputStream);
}


inline bool	DeliveryNotificationManager::ReadAndProcessState(InputMemoryBitStream& inInputStream)
{
	bool toRet = ProcessSequenceNumber(inInputStream);

	return toRet;
}
#endif