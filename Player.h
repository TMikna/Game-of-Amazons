#pragma once

#include <iostream>
#include "Board.h"

class Player
{

public:
	void makeMove() {
		moveAmazon();
		shootArrow();
	}

	//Pure Virtual function
	virtual void moveAmazon() = 0;

	virtual void shootArrow() = 0;


private:
	
};
