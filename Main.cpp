//UI based on chess tutorial: https://www.youtube.com/watch?v=_4EuZI8Q8cs
#include <iostream>
#include "Board.h"
#include "UI.h"
#include "Person.h"
#include "UI.h"




int main()
{

	Board board;
	UI ui;
	Person person1 (&board, &ui, WHITES);
	Person person2 (&board, &ui, BLACKS);

	ui.loadBoard(board.getAmazons(), "images/Board10x10.png", "images/queens2.png", "images/arrow.png");

	while (ui.window.isOpen())
	{
		
		person1.makeMove();
		person2.makeMove();
		
	}
	





	

	// TO stop it
	int x;
	std::cin >> x;

	return 0;
}
