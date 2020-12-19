//UI based on chess tutorial: https://www.youtube.com/watch?v=_4EuZI8Q8cs
#include <iostream>
#include "Board.h"
#include "UI.h"
#include "Person.h"
#include "Ai.h"


int main()
{
	Board board;
	UI ui;
	Person person1 (&board, &ui, WHITES);
	Person person2 (&board, &ui, BLACKS);
	Ai ai(&board, &ui, BLACKS);
	Ai ai0(&board, &ui, WHITES);

	ui.loadBoard(board.getAmazons(), "images/Board10x10.png", "images/queens2.png", "images/arrow.png");
	//board.findAllMoves(BLACKS);

	//auto moves = board.findAllMoves(WHITES);
	//ai.moveAmazon();

	while (ui.window.isOpen())
	{
		person1.makeMove();
		ai.makeMove();
	}

	return 0;
}
