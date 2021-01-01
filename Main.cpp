//UI based on chess tutorial: https://www.youtube.com/watch?v=_4EuZI8Q8cs
#include <iostream>
#include "Board.h"
#include "UI.h"
#include "Person.h"
#include "RandomAI.h"



#include <chrono>  // for high_resolution_clock
#include <algorithm>
#include "AlfaBetaAI.h"


int main()
{
	std::cout << sizeof(int);
	std::cout << std::endl;
	std::cout << sizeof(float);
	std::cout << std::endl;
	std::array<int, 4> a;
	int b[4] = {1,2,3,4};
	std::cout << sizeof(b);

	Board board;
	UI ui;
	Person personw (&board, &ui, WHITES);
	Person personb (&board, &ui, BLACKS);
	RandomAI rAIw(&board, &ui, WHITES);
	RandomAI rAIb(&board, &ui, BLACKS);
	AlfaBetaAI abAIw(&board, &ui, WHITES);
	AlfaBetaAI abAIb(&board, &ui, BLACKS);
	//Ai ai2(&board, &ui, WHITES);

	ui.loadBoard(board.getAmazons(), "images/Board10x10.png", "images/queens2.png", "images/arrow.png", "images/winMsg.png");
	//board.findAllMoves(BLACKS);

	//auto moves = board.findAllMoves(WHITES);
	//ai.moveAmazon();

	auto p1 = personw;    // player 1 (Whites)
	auto p2 = abAIb;		// player 2 (Blacks)

	while (ui.window.isOpen())
	{
		if (p1.hasPossibleMove())
		{
			p1.makeMove();
		}
		else
		{
			ui.displayWinner(p2.getTeamColor()); // p1 ran out of moves, p2 wins
			std::cout << "p2 wins" << std::endl;
			break;
		}

		if (p2.hasPossibleMove())
		{
			p2.makeMove();
		}
		else
		{
			ui.displayWinner(p1.getTeamColor()); // p2 ran out of moves, p1 wins
			std::cout << "p1 wins" << std::endl;
			break;
		}	
	}
	
	ui.waitClose();

	return 0;
}
