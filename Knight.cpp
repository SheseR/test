#include "Knight.h"

CKnight::CKnight()
	:CPiece(KNIGHT)
{
}
//-----------------------------------------------------------------
CKnight::CKnight(int aPosX, int aPosY, eColor aColor)
	: CPiece(aPosX, aPosY, aColor, KNIGHT)
{
}
//-----------------------------------------------------------------
CKnight::~CKnight()
{
}
//-----------------------------------------------------------------
eMove CKnight::_move(int tempX, int tempY,  vector<vector<sCell>>* aBoard)
{
	if((tempX - x == 2 || x - tempX == 2) && (tempY - y == 1 || y - tempY == 1))
	{
		if((*aBoard)[tempX][tempY].idPiece == idEmpty)
			return LEGAL;
		else if(color == WHITE && (*aBoard)[tempX][tempY].idPiece >= idBlackKing)
			return SHOOT;
		else if(color == BLACK && (*aBoard)[tempX][tempY].idPiece < idBlackKing)
			return SHOOT;
		else 
			return ILLEGAL;
	}
	else if((tempY - y == 2 || y - tempY == 2) && (tempX - x == 1 || x - tempX == 1))
	{
		if((*aBoard)[tempX][tempY].idPiece == idEmpty)
			return LEGAL;
		else if(color == WHITE && (*aBoard)[tempX][tempY].idPiece >= idBlackKing)
			return SHOOT;
		else if(color == BLACK && (*aBoard)[tempX][tempY].idPiece < idBlackKing)
			return SHOOT;
		else 
			return ILLEGAL;
	}
	else
		return ILLEGAL;
};

