#include "Rook.h"

CRook::CRook()
	:CPiece(ROOK)
	,flagMove(false)
{
}
//-----------------------------------------------------------------
CRook::CRook(int aPosX, int aPosY, eColor aColor)
	: CPiece(aPosX, aPosY, aColor, ROOK)
	,flagMove(false)
{
}
//-----------------------------------------------------------------
CRook::~CRook()
{
}
//-----------------------------------------------------------------
void CRook::setFlagMove(bool aMove)
{
	flagMove = aMove;
};
//-----------------------------------------------------------------
eMove CRook::_move(int tempX, int tempY,  vector<vector<sCell>>* aBoard)
{
	if(x == tempX)
	{
		int dy = (y < tempY) ? 1 : -1;

		for(int i = y + dy; i != tempY; i += dy)
		{
			if((*aBoard)[x][i].idPiece != idEmpty)
				return ILLEGAL;
		}

		if((*aBoard)[x][tempY].idPiece == idEmpty)
		{
			return LEGAL;
		}

		if(color == WHITE && (*aBoard)[x][tempY].idPiece >= idBlackKing)
		{
			return SHOOT;
		}
		else if(color == BLACK && (*aBoard)[x][tempY].idPiece < idBlackKing)
		{
			return SHOOT;
		}
		else
			return ILLEGAL;
	}
	else if(y == tempY)
	{
		int dx = (x < tempX) ? 1 : -1;

		for(int i = x + dx; i != tempX; i += dx)
		{
			if((*aBoard)[i][y].idPiece != idEmpty)
				return ILLEGAL;
		}

		if((*aBoard)[tempX][y].idPiece == idEmpty)
		{
			return LEGAL;
		}

		if(color == WHITE && (*aBoard)[tempX][y].idPiece >= idBlackKing)
		{
			return SHOOT;
		}
		else if(color == BLACK && (*aBoard)[tempX][y].idPiece < idBlackKing)
		{
			return SHOOT;
		}
		else
			return ILLEGAL;
	}
	else
		return ILLEGAL;
};

