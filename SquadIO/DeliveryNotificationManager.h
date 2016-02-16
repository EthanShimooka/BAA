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

	/// Constructor, initializes variables.
	DeliveryNotificationManager();
	/// Destructor.
	~DeliveryNotificationManager();

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

#endif