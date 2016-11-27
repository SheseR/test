#include "King.h"

CKing::CKing()
    :CPiece(KING)
	,flagMove(false)
{
}
//-----------------------------------------------------------------
CKing::CKing(int aPosX, int aPosY, eColor aColor) 
    : CPiece(aPosX, aPosY, aColor, KING)
	,flagMove(false)
{ 
};
//-----------------------------------------------------------------
CKing::~CKing(void)
{
}
//-----------------------------------------------------------------
void CKing::setFlagMove(bool aMove)
{
	flagMove = aMove;
}
//-----------------------------------------------------------------
bool CKing:: isChack(vector<CPiece*> & aVector, vector<vector<sCell>>* aBoard)
{
	int sizeVector = aVector.size();
	
	for(int i = 0; i < sizeVector; i ++)
	{		
		if(aVector[i]->getLive() == true && (aVector[i]->move(x * sizeCell, y * sizeCell, aBoard)) == SHOOT)
		{
			return true;
		}
	}	
	return false;
};
//-----------------------------------------------------------------
eMove CKing::_move(int tempX, int tempY,  vector<vector<sCell>>* aBoard)
{
	if(abs(x - tempX) <= 1 && abs(y - tempY) <= 1 )
	{	
		int k = tempX - 1;
		int m = tempY - 1;
		
		if((*aBoard)[tempX][tempY].idPiece ==  idEmpty)
			return LEGAL;
		
		if(color == WHITE && (*aBoard)[tempX][tempY].idPiece >= idBlackKing)
			return SHOOT;
		else if (color == BLACK && (*aBoard)[tempX][tempY].idPiece < idBlackKing)
			return SHOOT;
		else
			return ILLEGAL;			
	}
	else if(!flagMove && abs(x - tempX) == 2 && y == tempY)
	{
		return CASTLING;
	}
	else
		return ILLEGAL;
};

