#include "Queen.h"

CQueen::CQueen()
	:CPiece(QUEEN)
{
}
//-----------------------------------------------------------------
CQueen::CQueen(int aPosX, int aPosY, eColor aColor) 
	:CPiece(aPosX, aPosY, aColor, QUEEN)
{
}
//-----------------------------------------------------------------
CQueen::~CQueen()
{
}
//-----------------------------------------------------------------
eMove CQueen::_move(int tempX, int tempY,  vector<vector<sCell>>* aBoard)
{
	if(tempX - x == tempY - y)      // as bishop ---- it is a diagornal (1,1 and 8,8 secondary diagonal)
	{
		int delta = (tempX - x > 0) ? 1 : -1;

		for(int i = x + delta, j = y + delta; i != tempX; i += delta, j += delta)
			if((*aBoard)[i][j].idPiece != idEmpty)
				return ILLEGAL;

		if((*aBoard)[tempX][tempY].idPiece == idEmpty)
			return LEGAL;
		else if(color == WHITE && ((*aBoard)[tempX][tempY].idPiece >= idBlackKing))
			return SHOOT;
		else if(color == BLACK && ((*aBoard)[tempX][tempY].idPiece < idBlackKing))
			return SHOOT;
		else
			return ILLEGAL;
	}
	else if(x - tempX == tempY - y)					//as bishop ---  it is a diagonal (1,8 adn 8 , 1)
	{
		int dx = ((tempX - x ) > 0) ? 1 : -1;

		for(int i = x + dx, j = y - dx; i != tempX; i += dx, j -= dx)
			if((*aBoard)[i][j].idPiece != idEmpty)
				return ILLEGAL;

		if((*aBoard)[tempX][tempY].idPiece == idEmpty)
			return LEGAL;
		else if(color == WHITE && (*aBoard)[tempX][tempY].idPiece >= idBlackKing)
			return SHOOT;
		else if(color == BLACK && (*aBoard)[tempX][tempY].idPiece < idBlackKing)
			return SHOOT;
		else
			return ILLEGAL;
	}
	else if (x == tempX)				//------ as rook it is row
	{
		int dy = (y < tempY) ? 1 : -1;

		for(int i = y + dy; i != tempY; i += dy)
			if((*aBoard)[x][i].idPiece != idEmpty)
				return ILLEGAL;

		if((*aBoard)[x][tempY].idPiece == idEmpty)
			return LEGAL;

		if(color == WHITE && (*aBoard)[x][tempY].idPiece >= idBlackKing)
			return SHOOT;
		else if(color == BLACK && (*aBoard)[x][tempY].idPiece < idBlackKing)
			return SHOOT;
		else
			return ILLEGAL;
	}
	else if (y == tempY)				//------ as rook it is colomn
	{
		int dx = (x < tempX) ? 1 : -1;

		for(int i = x + dx; i != tempX; i += dx)
			if((*aBoard)[i][y].idPiece != idEmpty)
				return ILLEGAL;

		if((*aBoard)[tempX][y].idPiece == idEmpty)
			return LEGAL;

		if(color == WHITE && (*aBoard)[tempX][y].idPiece >= idBlackKing)
			return SHOOT;
		else if(color == BLACK && (*aBoard)[tempX][y].idPiece < idBlackKing)
			return SHOOT;
		else
			return ILLEGAL;
	}
	else
		return ILLEGAL;
};