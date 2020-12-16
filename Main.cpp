//UI based on chess tutorial: https://www.youtube.com/watch?v=_4EuZI8Q8cs
#include <iostream>
#include "Board.h"



int main()
{

	/// <summary>
	/// is move in progress. Starts with prsiing on a amazon and finishes with shooting an arrow
	/// </summary>
	/// <returns></returns>
	int isMove = false;
	// is any amazon being moved at this moment
	bool isMoving = false;
	bool player = false; //false - 1st or true - 2nd

	Board board;
	board.loadBoard("images/Board10x10.png", "images/queens2.png", "images/arrow.png");
	board.display();


	while (board.window.isOpen())
	{
		Vector2i mousePos = Mouse::getPosition(board.window);

		Event e;
		while (board.window.pollEvent(e))
		{
			if (e.type == Event::Closed)
				board.window.close();

			///drag and drop
			if (e.type == Event::MouseButtonPressed)
				if (e.key.code == Mouse::Left)
					if (isMove)
					{
						bool result = board.shootArrow(mousePos);
						// if arrow shoot sucesfully - finish move, and make other player's turn
						if (result)
						{
							isMove = false;
							player = !player;
						}
					}
					else
					{
						// if sucess - player's move and moving of the amazon is started
						isMove = isMoving = board.startMove(mousePos, (int)player + 1);
					}
					

			if (e.type == Event::MouseButtonReleased)
				if (e.key.code == Mouse::Left)
					if (isMove && isMoving)
					{
						
						//true on sucess (amazon's move finished), fails when try to drop amazon in same or illegal position
						bool result = board.finishMoving();
						// if figure dropped to the same position (fail) - move is cancelled, othervise move is going one (next step - arrow shooting)
						isMove = result;
						// if move either finished or cancelled
						isMoving = false;
						
					}
						
		}
		/*we could do this in finishMove, but this way it allows drag and see where figure is at the moment*/
		if (isMoving)
			board.setAmazonPosition(mousePos);
		board.display();
	}

	
	return 0;
}
