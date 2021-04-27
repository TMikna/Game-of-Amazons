//UI based on chess tutorial: https://www.youtube.com/watch?v=_4EuZI8Q8cs
#include <iostream>
#include "Board.h"
#include "UI.h"
#include "Person.h"
#include "RandomAI.h"
#include "AlfaBetaAI_ss.h"
#include "AlfaBetaAI_fs.h"


#include <chrono>  // for high_resolution_clock
#include <algorithm>
#include "AlfaBetaAI_sssi.h"
#include <thread>
#include "AlfaBetaAI_sssiie.h"



int main()
{

	//Board boardX;
	//BoardArray testBoardState =
	//{ 0, -1, 2, 2,
	//0, 1, 1, -1,
	//0, 0, 0, 0,
	//0, 0, 0, 0, };
	////{ 2, -1, -1, -1,
	////  -1, -1, -1, 0,
	////  0, 2, -1, 1,
	////  1, 0, -1, 0, };

	//{
	//	boardX.setBoardState(testBoardState);
	//	std::vector <AmazonMove> possibleMoves = boardX.findAllMoves(BLACKS);

	//	bool X = boardX.hasMove(BLACKS);
	//}

	Board board;
	UI ui;
	Person personw (&board, &ui, WHITES);
	Person personb (&board, &ui, BLACKS);
	RandomAI rAIw(&board, &ui, WHITES);
	RandomAI rAIb(&board, &ui, BLACKS);
	AlfaBetaAI_ss abAIsw(&board, &ui, WHITES);
	AlfaBetaAI_ss abAIsb(&board, &ui, BLACKS);
	AlfaBetaAI_sssi abAIssw(&board, &ui, WHITES);
	AlfaBetaAI_sssi abAIssb(&board, &ui, BLACKS);
	AlfaBetaAI_sssiie abAIssiw(&board, &ui, WHITES);
	AlfaBetaAI_sssiie abAIssib(&board, &ui, BLACKS);
	AlfaBetaAI_fs abAIfw(&board, &ui, WHITES);
	AlfaBetaAI_fs abAIfb(&board, &ui, BLACKS);
	//Ai ai2(&board, &ui, WHITES);

	ui.loadBoard(board.getAmazons(), "images/Board10x10.png", "images/queens2.png", "images/arrow.png", "images/winMsg.png");
	//board.findAllMoves(BLACKS);

	//auto moves = board.findAllMoves(WHITES);
	//ai.moveAmazon();

	auto pW = abAIssiw; // player 1 (Whites)
	auto pB = personb; 	  // player 2 (Blacks)

	//auto pW = abAIssiw; // player 1 (Whites)
	//auto pB = abAIssb;	  // player 2 (Blacks)

	std::cout << board.allPossibleDirections(WHITES) << '\n';

	auto start = std::chrono::high_resolution_clock::now();

	while (ui.window.isOpen())
	{
		if (pW.hasPossibleMove())
		{
			pW.makeMove();
		}
		else
		{
			ui.displayWinner(pB.getTeamColor()); // p1 ran out of moves, p2 wins
			std::cout << "pB wins" << std::endl;
			break;
		}

	//	std::chrono::milliseconds timespan(2000); // or whatever
	//	std::this_thread::sleep_for(timespan);

		if (pB.hasPossibleMove())
		{
			pB.makeMove();
		}
		else
		{
			ui.displayWinner(pW.getTeamColor()); // p2 ran out of moves, p1 wins
			std::cout << "pW wins" << std::endl;
			break;
		}
	//	std::this_thread::sleep_for(timespan);
	}

	auto finish = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = finish - start;
	std::cout << "Elapsed time: " << elapsed.count() << " s\n";

	ui.waitClose();


/*
	int randomCount = 0;
	int AlfaBetaCount = 0;

	for (int i = 0; i < 200; i++)
	{
		Board board;
		UI ui;
		RandomAI rAIw(&board, &ui, WHITES);
		AlfaBetaAI_ss abAIb(&board, &ui, BLACKS);
		ui.loadBoard(board.getAmazons(), "images/Board10x10.png", "images/queens2.png", "images/arrow.png", "images/winMsg.png");
		auto p1 = rAIw;    // player 1 (Whites)
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
				//std::cout << "p2 wins" << std::endl;
				AlfaBetaCount++;
				break;
			}

			if (p2.hasPossibleMove())
			{
				p2.makeMove();
			}
			else
			{
				ui.displayWinner(p1.getTeamColor()); // p2 ran out of moves, p1 wins
				//std::cout << "p1 wins" << std::endl;
				randomCount++;
				break;
			}

		}		
		
		if (i % 10 == 0)
		{		
			std::cout << "Iteration:         " << randomCount << std::endl;
			std::cout << "Random AI wins:    " << randomCount << std::endl;
			std::cout << "AlphaBeta AI wins: " << AlfaBetaCount << std::endl;
			std::cout << std::endl;
		}
		ui.closeWindow();
	}
//	ui.waitClose();
		std::cout << std::endl;
		std::cout << "Final result:      " << std::endl;
		std::cout << "Random AI wins:    " << randomCount << std::endl;
		std::cout << "AlphaBeta AI wins: " << AlfaBetaCount << std::endl;
		std::cout << std::endl;

*/
	return 0;
}
