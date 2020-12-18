//UI based on chess tutorial: https://www.youtube.com/watch?v=_4EuZI8Q8cs

#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include <windows.h> // Sleep(milliseconds);

using namespace sf;

int size = 56;

Sprite f[32]; //figures
int board[8][8] =
{ -1,-2,-3,-4,-5,-3,-2,-1,
 -6,-6,-6,-6,-6,-6,-6,-6,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  6, 6, 6, 6, 6, 6, 6, 6,
  1, 2, 3, 4, 5, 3, 2, 1 };

std::string toChessNote(Vector2f p)
{
	std::string s = "";
	s += char(p.x / size + 97);
	s += char(7 - p.y / size + 49);
	return s;
}

Vector2f toCoord(char a, char b)
{
	int x = int(a) - 97;
	int y = 7 - int(b) + 49;
	return Vector2f(x * size, y * size);
}

void move(std::string str)
{
	Vector2f oldPos = toCoord(str[0], str[1]);
	Vector2f newPos = toCoord(str[2], str[3]);

	for (int i = 0; i < 32; i++)
		if (f[i].getPosition() == newPos)
			f[i].setPosition(-100, -100);

	for (int i = 0; i < 32; i++)
		if (f[i].getPosition() == oldPos)
			f[i].setPosition(newPos);
}

std::string position = "";

void loadPosition()
{
	int k = 0;
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			int n = board[i][j];
			if (!n)
				continue;
			int x = abs(n) - 1;
			int y = n > 0 ? 1 : 0;
			f[k].setTextureRect(IntRect(size * x, size * y, size, size));
			f[k].setPosition(size * j, size * i);
			k++;
		}

	for (int i = 0; i < position.length(); i += 5)
		move(position.substr(i, 4));

}

int main0()
{
	RenderWindow window(VideoMode(453, 453), "TheChess!");

	Texture t1, t2;
	t1.loadFromFile("images/queens.png");
	t2.loadFromFile("images/board0.png");

	Sprite sBoard(t2);

	for (int i = 0; i < 32; i++)
		f[i].setTexture(t1);
	loadPosition();

	bool isMove = false;
	float dx = 0, dy = 0;
	int n = 0;
	Vector2f oldPos, newPos;
	std::string str;

	while (window.isOpen())
	{
		Vector2i pos = Mouse::getPosition(window);

		Event e;
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
				window.close();
			///move back
			if (e.type == Event::KeyPressed)
				if (e.key.code == Keyboard::BackSpace)
				{
					position.erase(position.length() - 6, 5);
					loadPosition();
				}
			///drag and drop
			if (e.type == Event::MouseButtonPressed)
				if (e.key.code == Mouse::Left)
					for (int i = 0; i < 32; i++)
						if (f[i].getGlobalBounds().contains(pos.x, pos.y))
						{
							isMove = true;
							n = i;
							dx = pos.x - f[i].getPosition().x;
							dy = pos.y - f[i].getPosition().y;
							oldPos = f[i].getPosition();
						}

			if (e.type == Event::MouseButtonReleased)
				if (e.key.code == Mouse::Left)
				{
					isMove = false;
					Vector2f p = f[n].getPosition() + Vector2f(size / 2, size / 2);
					Vector2f newPos = Vector2f(size * int(p.x / size), size * int(p.y / size));
					str = toChessNote(oldPos) + toChessNote(newPos);
					move(str);
					position += str + " ";
					std::cout << str << std::endl;
					f[n].setPosition(newPos);
				}

		}

		//komp move
		if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			str = "d7d5";

			oldPos = toCoord(str[0], str[1]);
			newPos = toCoord(str[2], str[3]);

			for (int i = 0; i < 32; i++)
				if (f[i].getPosition() == oldPos)
					n = i;

			///animation
			for (int k = 0; k < 50; k++)
			{
				Sleep(10);
				Vector2f p = newPos - oldPos;
				f[n].move(p.x / 50, p.y / 50);
				window.draw(sBoard);
				for (int i = 0; i < 32; i++)
					window.draw(f[i]);
				window.draw(f[n]);
				window.display();

			}
			move(str);
			position += str + " ";
			f[n].setPosition(newPos);
		}

		if (isMove)
			f[n].setPosition(pos.x - dx, pos.y - dy);

		window.clear();
		window.draw(sBoard);
		for (int i = 0; i < 32; i++)
			window.draw(f[i]);
		window.display();
	}

	return 0;
}




//Old Main

/*


//UI based on chess tutorial: https://www.youtube.com/watch?v=_4EuZI8Q8cs
#include <iostream>
#include "Board.h"



int main()
{

	Board board;
	board.loadBoard("images/Board10x10.png", "images/queens2.png", "images/arrow.png");
	board.display();



	/*
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

		if (isMoving)
			board.setAmazonPosition(mousePos);
		board.display();
	}

	
return 0;
}

*/
