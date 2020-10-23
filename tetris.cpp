
#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include <sstream>
#include "emscripten.h"
#include <math.h>
using namespace std;

int main()
{

	return 0;

}

int gameWidth = 12;
int gameHeight = 22;

class Coordinate {
	private:
		int x;
		int y;
	public:
		int getX()
		{
			return x;
		}
		int getY()
		{
			return y;
		}
		Coordinate()
		{
			x = 0;
			y = 0;
		}
		Coordinate(int x, int y)
		{
			this->x = x;
			this->y = y;
		}
		void setX(int sX)
		{
			x = sX;
		}
		void setY(int sY)
		{
			y = sY;
		}
};



class Block {
    private:
        Coordinate points[4];
		int blockType;
		static int ID;
		int blockId;
		int** gamePtr;

		bool rotateLeft()
		{
	
			int totalX = 0;
			int totalY = 0;
			double avgX = 0;
			double avgY = 0;

			for (int i = 0; i < 4; i++)
			{
				totalX += points[i].getX();
				totalY += points[i].getY();
			}

			avgX = ceil(totalX / 4.0);
			avgY = ceil(totalY / 4.0);

			for (int i = 0; i < 4; i++)
			{
				double y = points[i].getY() - avgY + 0.5;
				double x = points[i].getX() - avgX + 0.5;

				points[i].setX((int)round(-y + avgX - 0.5));
				points[i].setY((int)round(x + avgY - 0.5));
			}

			return true;
		}
		bool rotateRight()
		{
			rotateLeft();
			rotateLeft();
			rotateLeft();

			return true;
		}

		bool moveDownOneSpace()
		{
			for (int i = 0; i < 4; i++)
			{
				int check = points[i].getY() + 1;
			
				if (check >= gameHeight)
					return false;
				points[i].setY(points[i].getY() + 1);
				
			}
			return true;
		}
		bool moveLeftOneSpace()
		{
			for (int i = 0; i < 4; i++)
			{
				int check = points[i].getX() - 1;
				if (check < 0)
					return false;
				points[i].setX(points[i].getX() - 1);
			}
			return true;
		}
		bool moveRightOneSpace()
		{
			for (int i = 0; i < 4; i++)
			{
				int check = points[i].getX() + 1;
				if (check >= gameWidth)
					return false;
				points[i].setX(points[i].getX() + 1);
			}
			return true;
		}
    public:
        Block()
        {
			blockId = ID++;
            blockType = rand() % 7 + 1;
			int startingX = gameWidth / 2 -2;
            if (blockType == 1)
			{
				points[0].setX(startingX);
				points[0].setY(0);

				points[1].setX(startingX + 0);
				points[1].setY(1);

				points[2].setX(startingX);
				points[2].setY(2);

				points[3].setX(startingX + 0);
				points[3].setY(3);
			}
			else if (blockType == 2)
			{
				points[0].setX(startingX + 0);
				points[0].setY(0);

				points[1].setX(startingX + 1);
				points[1].setY(0);

				points[2].setX(startingX + 2);
				points[2].setY(0);

				points[3].setX(startingX + 1);
				points[3].setY(1);
			}
			else if (blockType == 3)
			{
				points[0].setX(startingX + 0);
				points[0].setY(0);

				points[1].setX(startingX + 1);
				points[1].setY(0);

				points[2].setX(startingX + 0);
				points[2].setY(1);

				points[3].setX(startingX + 1);
				points[3].setY(1);
			}
			else if (blockType == 4)
			{

				points[0].setX(startingX + 2);
				points[0].setY(0);

				points[1].setX(startingX + 1);
				points[1].setY(0);

				points[2].setX(startingX + 1);
				points[2].setY(1);

				points[3].setX(startingX + 0);
				points[3].setY(1);

			}
			else if (blockType == 5)
			{
				points[0].setX(startingX + 2);
				points[0].setY(1);

				points[1].setX(startingX + 1);
				points[1].setY(1);

				points[2].setX(startingX + 1);
				points[2].setY(0);

				points[3].setX(startingX + 0);
				points[3].setY(0);
			}
			else if (blockType == 6)
			{
				points[0].setX(startingX + 1);
				points[0].setY(0);

				points[1].setX(startingX + 1);
				points[1].setY(1);

				points[2].setX(startingX + 1);
				points[2].setY(2);

				points[3].setX(startingX + 0);
				points[3].setY(2);
			}
			else if (blockType == 7)
			{
				points[0].setX(startingX + 0);
				points[0].setY(0);

				points[1].setX(startingX + 0);
				points[1].setY(1);

				points[2].setX(startingX + 0);
				points[2].setY(2);

				points[3].setX(startingX + 1);
				points[3].setY(2);
			}
			//moveRight();
        }
        
        bool isCollision(int offsetX, int offsetY, int dir)
        {
			
            for (int i = 0; i < 4; i++)
			{
				if (gamePtr[points[i].getY() + offsetY][points[i].getX() +offsetX] == 9 || (gamePtr[points[i].getY() + offsetY][points[i].getX() +offsetX] != blockId && gamePtr[points[i].getY() + offsetY][points[i].getX() +offsetX] != 0))
				{
					return true;
				}
			}
			
            return false;
        }

		bool isColliding()
		{
			 for (int i = 0; i < 4; i++)
				{
					if (gamePtr[points[i].getY()][points[i].getX()] == 9 || (gamePtr[points[i].getY()][points[i].getX()] != 0 && gamePtr[points[i].getY()][points[i].getX()] != blockId))
					{
						return true;
					}
				}

			return false;
		}
		int getType()
		{
			return blockType;
		}

		int getID()
		{
			return blockId;
		}

		Coordinate* getCoordinates()
		{
			return points;
		}

		Block(Block* b)
		{
			Coordinate * p = b->getCoordinates();
			for (int i = 0; i < 4; i++)
			{
				points[i].setX(p[i].getX());
				points[i].setY(p[i].getY());
			}
			gamePtr = b->gamePtr;
			blockType = b->blockType;
			blockId = b->blockId;
		}

        bool rotate(int direction)
        {
			Block * temp = new Block(this);
			if (direction == 1)
			{
				temp->rotateRight();
				if (temp->isColliding())
				{
					delete temp;
					return false;
				}
				else
				{
					delete temp;
					this->rotateRight();
					return true;
				}
			}
			else
			{
				temp->rotateLeft();
				if (temp->isColliding())
				{
					delete temp;
					return false;
				}
				else
				{
					delete temp;
					this->rotateLeft();
					return true;
				}
					
			}
        }

		bool moveDown()
		{
			Block * temp = new Block(this);
			
			if (temp->isCollision(0, 1, 0))
			{
				
				return false;
			}

			this->moveDownOneSpace();
			delete temp;
			return true;

		}

		bool moveRight()
		{
			Block * temp = new Block(this);
			
			if (temp->isCollision(1, 0, 1))
			{
				return false;
			}

			this->moveRightOneSpace();
			delete temp;
			return true;
		}

		bool moveLeft()
		{
			Block * temp = new Block(this);
			
			if (temp->isCollision(-1, 0, 2))
			{
				return false;
			}

			this->moveLeftOneSpace();
			delete temp;
			return true;
		}

		void setGamePtr(int** ptr)
		{
			gamePtr = ptr;
		}

};

int Block::ID = 10;

class Field {
    private:
		int** gameField;
    public:
        Field()
        {
			gameField = new int*[gameHeight];
			for (int i = 0; i < gameHeight; i++)
			{
				gameField[i] = new int[gameWidth];
			}
            for (int x = 0; x < gameHeight; x++) 
                for (int y = 0; y < gameWidth; y++)
                {
                    if (y == gameWidth - 1 || y == 0 || x == gameHeight - 1)
                    {
                        gameField[x][y] = 9;
                    }
                    else
                    {
                        gameField[x][y] = 0;
                    }
                }

        }

		void updateGameState(Block* b, Block* prev)
		{
			if (prev)
			{
				Coordinate * pre = prev->getCoordinates();
				for (int i = 0; i < 4; i++)
				{
					gameField[pre[i].getY()][pre[i].getX()] = 0;
				}
			}
			

			Coordinate * curr = b->getCoordinates();
			for (int i = 0; i < 4; i++)
			{
				gameField[curr[i].getY()][curr[i].getX()] = b->getID();
			}
		}

		int** getGameField()
		{
			return gameField;
		}

		bool checkGameOver()
		{
			for (int i = 1; i < gameWidth - 1; i++)
			{
				if (gameField[0][i] != 0)
					return true;
			}

			return false;
		}

		int checkForLines()
		{
			std::vector<int> lines = {};
			for (int i = 1; i < gameHeight - 1; i++)
			{
				if (gameField[i][1] != 0)
				{
					bool isLine = true;
					for (int j = 1; j < gameWidth - 1; j++)
					{
						if (gameField[i][j] == 0)
						{
							isLine = false;
						}
					}
					if (isLine)
					{
						lines.push_back(i);
						for (int y = i; y > 0; y--)
						{
							for (int x = 1; x < gameWidth -1; x++)
							{
								gameField[y][x] = gameField[y-1][x];
							}
						}
					}
				}
			}
			int numLines = lines.size();
			int score = 0 + 200*lines.size();

			if (numLines > 0)
			{
				for (int i = 1; i < gameWidth - 1; i++)
				{
					gameField[0][i] = 0;
				}
			}

			return score;
		}

		string convertGameStateToString()
		{
			stringstream ss;
			//string game = "";
			for (int i = 0; i < gameHeight; i++)
			{
				for (int j = 0; j < gameWidth; j++)
				{
					if (gameField[i][j] == 0 || gameField[i][j] == 9)
					{
						ss << gameField[i][j];
					}
					else
					{
						
						ss << 5;
					}
					
					
				}
			}

			return ss.str();
		}

		void clearGameState()
		{
			for (int i = 0; i < gameHeight - 1; i++)
			{
				for (int j = 1; j < gameWidth - 1; j++)
				{
					gameField[i][j] = 0;
				}
			}
		}
};

Field tetrisField;


Block* currBlock;
int score = 0;

#ifdef __cplusplus
extern "C" {
#endif


const char * EMSCRIPTEN_KEEPALIVE startGame()
{
   
   currBlock = new Block();
   score = 0;
   currBlock->setGamePtr(tetrisField.getGameField());
   srand(time(0));	

   return tetrisField.convertGameStateToString().c_str();


}

const char * EMSCRIPTEN_KEEPALIVE restartGame()
{
	tetrisField.clearGameState();
	delete currBlock;
	currBlock = new Block();
	score = 0;
	currBlock->setGamePtr(tetrisField.getGameField());

	return tetrisField.convertGameStateToString().c_str();
}

const char * EMSCRIPTEN_KEEPALIVE moveLeft()
{
	currBlock->setGamePtr(tetrisField.getGameField());
	Block * prevBlock = new Block(currBlock);
	if (!currBlock->moveLeft())
	{
		delete prevBlock;
		tetrisField.updateGameState(currBlock, NULL);
		return tetrisField.convertGameStateToString().c_str();
	}
	
	
	tetrisField.updateGameState(currBlock, prevBlock);
	delete prevBlock;

	//return the array here
	return tetrisField.convertGameStateToString().c_str();
}

const char * EMSCRIPTEN_KEEPALIVE moveRight()
{
	currBlock->setGamePtr(tetrisField.getGameField());
	Block * prevBlock = new Block(currBlock);
	if (!currBlock->moveRight())
	{
		delete prevBlock;
		tetrisField.updateGameState(currBlock, NULL);
		return tetrisField.convertGameStateToString().c_str();
	}
	
	
	tetrisField.updateGameState(currBlock, prevBlock);
	delete prevBlock;

	//return the array here
	return tetrisField.convertGameStateToString().c_str();
}

void EMSCRIPTEN_KEEPALIVE clearBoard()
{
	tetrisField.clearGameState();
	if (currBlock)
		delete currBlock;
	currBlock = NULL;
	score = 0;
}

const char * EMSCRIPTEN_KEEPALIVE rotateLeft()
{
	currBlock->setGamePtr(tetrisField.getGameField());
	Block * prevBlock = new Block(currBlock);
	if (!currBlock->rotate(0))
	{

		delete prevBlock;

		return tetrisField.convertGameStateToString().c_str();
	}
	
	
	tetrisField.updateGameState(currBlock, prevBlock);
	delete prevBlock;

	//return the array here
	return tetrisField.convertGameStateToString().c_str();
}

const char * EMSCRIPTEN_KEEPALIVE rotateRight()
{
	currBlock->setGamePtr(tetrisField.getGameField());
	Block * prevBlock = new Block(currBlock);
	if (!currBlock->rotate(1))
	{
		delete prevBlock;

		return tetrisField.convertGameStateToString().c_str();
	}
	
	
	tetrisField.updateGameState(currBlock, prevBlock);
	delete prevBlock;

	//return the array here
	return tetrisField.convertGameStateToString().c_str();
}

const char * EMSCRIPTEN_KEEPALIVE moveDown()
{
	currBlock->setGamePtr(tetrisField.getGameField());
	Block * prevBlock = new Block(currBlock);
	if (!currBlock->moveDown())
	{
		
		delete currBlock;
		tetrisField.updateGameState(currBlock, NULL);
		currBlock = new Block();
		
		return tetrisField.convertGameStateToString().c_str();
		
	}
	
	
	tetrisField.updateGameState(currBlock, prevBlock);
	score += tetrisField.checkForLines();

	delete prevBlock;

	//return the array here
	return tetrisField.convertGameStateToString().c_str();
}

int EMSCRIPTEN_KEEPALIVE getScore()
{
	return score;
}

bool EMSCRIPTEN_KEEPALIVE isGameOver()
{
	return tetrisField.checkGameOver();
}

const char * EMSCRIPTEN_KEEPALIVE getGame()
{
	return tetrisField.convertGameStateToString().c_str();
}





#ifdef __cplusplus
}
#endif







/*
emcc -o tetris.html tetris.cpp -O1 -s WASM=1 --shell-file template/html_template.html -s NO_EXIT_RUNTIME=1  -s "EXTRA_EXPORTED_RUNTIME_METHODS=['ccall']" -s EXPORTED_FUNCTIONS="['_moveDown', '_moveLeft', '_clearBoard', '_moveRight', '_startGame', '_restartGame', '_rotateLeft', '_rotateRight', '_getScore', '_isGameOver', '_getGame']"                                             */