#include "BoardMain.h"
#include "AllegroWrap.h"

CBoardMain::CBoardMain()
{
	_init();
	_initNotification();
}
CBoardMain::~CBoardMain()
{
}

//----------------------private functions-----------------------//
void CBoardMain:: _init()
{
	board.resize(countCells);
	for(int i = 0; i < countCells; i++)
		board[i].resize(countCells);

	for(int i = 0;  i < countCells; i++)
	{
		for(int j = 0; j < countCells; j++)
		{
			board[i][j].idPiece = idEmpty;
			board[i][j].x = i;
			board[i][j].y = j;
		}
	}
};
void CBoardMain::_initNotification()
{
	wordsNotificat.resize(9);
	numbersNotificat.resize(9);

	wordsNotificat[0] = " ";
	wordsNotificat[1] = "a";
	wordsNotificat[2] = "b";
	wordsNotificat[3] = "c";
	wordsNotificat[4] = "d";
	wordsNotificat[5] = "e";
	wordsNotificat[6] = "f";
	wordsNotificat[7] = "g";
	wordsNotificat[8] = "h";

	numbersNotificat[0] = " ";
	numbersNotificat[1] = "1";
	numbersNotificat[2] = "2";
	numbersNotificat[3] = "3";
	numbersNotificat[4] = "4";
	numbersNotificat[5] = "5";
	numbersNotificat[6] = "6";
	numbersNotificat[7] = "7";
	numbersNotificat[8] = "8";
}

//----------------------public functions-----------------------//
void CBoardMain::deleteIDPiece(int aI, int aJ)
{
	board[aI][aJ].idPiece = -1;
};
void CBoardMain::clearBoard()
{
	for(int i = 1; i < countCells; i++)
	{
		for(int j = 1; j < countCells; j++)
		{
			board[i][j].idPiece = -1;
		}
	}
};
//----------------------set and get functions-----------------------//
void CBoardMain::setPieces(vector<CPiece *> aVectorPieces)
{
	int sizeVector = aVectorPieces.size();
	int indexVector = 0; 	

	int intColor = 0; // for white vector and intColor = 100 for ID of Black pieces
	
	if(aVectorPieces[0]->getColor() == WHITE)
		intColor = 0;
	else
		intColor = 100;

	int tempX = 0;
	int tempY = 0;
	for(int i = 0; i < sizeVector; i++)
	{
		if(aVectorPieces[i]->getLive())
		{
			tempX = aVectorPieces[i]->getX();
			tempY = aVectorPieces[i]->getY();
			board[tempX][tempY].idPiece = i + intColor;
		}
	}
};
const sCell &CBoardMain::getCell(int aI, int aJ)const 
{
	return  board[aI][aJ];
};
const char CBoardMain::getIDPiece( int aI, int aJ)const
{
	return board[aI][aJ].idPiece;
};
void CBoardMain:: setIDPiece(int aI, int aJ, char aID)
{
	board[aI][aJ].idPiece = aID;
};
vector<vector<sCell>>*CBoardMain:: getPtrBoard()
{
	return &board;
};
//----------------draw functions-------------------------------//
void CBoardMain:: draw()
{
	CAllegroWrap &inst = CAllegroWrap::instance();
	inst.drawRectangle(50, 50, 400, 400);
	for(int i = 0; i < countCells; i++)
		for(int j = 0; j < countCells; j++ )
		{
			if(j == 0 && i == 0)
				continue;
			
			if(i == 0)
			{
				inst.drawString(numbersNotificat[9 - j], 0 + 20, j * sizeCell + 20);
				continue;
			}

			if(j == 0)
			{
				inst.drawString(wordsNotificat[i], i * sizeCell + 20, 0 + 20);
				continue;
			}		
			
			inst.drawCell(this->getCell(i, j));
		}
}