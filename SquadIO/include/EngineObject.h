#pragma once



/**
* Abstract base class give resource identification method and
* basic constructors.
*
*/
class EngineObject
{ 
public:

	/// Constructor
	EngineObject();

	/// Deconstructor 
    ~EngineObject(); 

	/// Resource Identifier. Singletons get "1"
	int ID; 
};

