#include "Person.h"

void Person::moveAmazon() {
	bool isMoveAllowed = false;

	while (!isMoveAllowed)
	{
		//check if valid amazon (kinda done by UI according to sprites places)
		do
			oldPos = ui->pickAmazon();
		while (board->getPlayer(oldPos) != teamColor);
		//std::cout << oldPos.x;

		newPos = ui->dropAmazon();

		if (!(isMoveAllowed = board->isMoveAllowed(oldPos, newPos)))
			ui->setAmazonPosition(oldPos);
	}
	ui->setAmazonPosition(newPos);
	board->moveAmazon(oldPos, newPos);
}

void Person::shootArrow()
{
	bool isAllowed = false;

	while (!isAllowed)
	{
		arrowPos = ui->chooseArrowPlace();
		isAllowed = board->isMoveAllowed(newPos, arrowPos); //shooting arrow from new position
	}
	board->placeArrow(arrowPos);
	ui->placeArrow(arrowPos);
}