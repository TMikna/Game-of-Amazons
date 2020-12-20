#include "Person.h"

void Person::moveAmazon() {
	bool isMoveAllowed = false;

	while (!isMoveAllowed)
	{
		do
			oldPos = ui->pickAmazon();                 // assume that UI picked existing amazon (supposed to be, othervise there is a problem with UI or board)
		while (board->getPlayer(oldPos) != teamColor); // doesn't go through if trying to move oponent amazon

		newPos = ui->dropAmazon();

		// cancel if it was not allowd move
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
		isAllowed = board->isMoveAllowed(newPos, arrowPos); //shooting arrow from new position; is shooting into allowed square
	}
	board->placeArrow(arrowPos);
	ui->placeArrow(arrowPos);
}

bool Person::hasPossibleMove()
{
	return board->hasMove(teamColor);
}