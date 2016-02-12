#include "Square.h"


	
	void Square::update(){

		obj->posX = x;
		obj->posY = y;

	}

	void Square::Write(OutputMemoryBitStream& outData){
		//outData.Write(ID);
		outData.Write(x);
		outData.Write(y);
	}

	void Square::Read(InputMemoryBitStream& data){
		data.Read(x);
		data.Read(y);
	}



