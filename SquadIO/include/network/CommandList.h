#ifndef COMMANDLIST_H_INCLUDED
#define COMMANDLIST_H_INCLUDED

/**
* CommandList is a class for encapsulating multiple command packages
*
*/
class CommandList
{
public:
	/// Constructor
	CommandList()
	{}
	/// Adds a command pointer to the deque of commands
	void			AddCommand(CommandPtr inCommand);
	/// Clears the deque of command pointers
	void			Clear()							{ mCommands.clear(); }
	/// Gets the number of command pointers in the deque
	int				GetCount()				const	{ return static_cast<int>(mCommands.size()); }
	/// Loops processing all commands in the deque
	void			ProcessCommands(uint64_t inExpectedPlayerId);
	/// Loops writing each command in deque to output stream
	void Write(OutputMemoryBitStream& inOutputStream);
	/// Loops reading each command in the input stream into the deque of command pointers
	void Read(InputMemoryBitStream& inInputStream);

private:
	/// Private deque of command pointers
	deque< CommandPtr >	mCommands;
};
#endif