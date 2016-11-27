#include "Pawn.h"

CPawn::CPawn()
	:CPiece(PAWN)
{
}
//-----------------------------------------------------------------
CPawn::CPawn(int aPosX, int aPosY, eColor aColor)
	: CPiece(aPosX, aPosY, aColor,PAWN) 
{
};
//-----------------------------------------------------------------
CPawn::~CPawn()
{
}
//-----------------------------------------------------------------
eMove CPawn::_move(int tempX, int tempY,  vector<vector<sCell>>* aBoard)
{
	if(tempX == x)
	{
		if(color == WHITE)
		{
			if(tempY == 1 && (*aBoard)[tempX][tempY].idPiece == idEmpty)
				return CONVERT_PAWN;

			if(y == 7 && tempY == 5 && (*aBoard)[tempX][tempY].idPiece == idEmpty &&  (*aBoard)[tempX][tempY + 1].idPiece == idEmpty)
				return LEGAL;

			if(y - tempY == 1 &&  (*aBoard)[tempX][tempY].idPiece == idEmpty)
				return LEGAL;
		}
		else
		{
			if(tempY == 8 && (*aBoard)[tempX][tempY].idPiece == idEmpty)
				return CONVERT_PAWN;
			
			if(y == 2 && tempY == 4 && (*aBoard)[tempX][tempY].idPiece == idEmpty && (*aBoard)[tempX][tempY - 1].idPiece == idEmpty)
				return LEGAL;
			
			if(tempY - y == 1 && (*aBoard)[tempX][tempY].idPiece == idEmpty)
				return LEGAL;
		}		
	}
	else if(tempX - 1 == x || tempX + 1 == x)
	{
		if(color == WHITE)
		{
			if(y - tempY == 1)
			{
				
				if(tempY == 1 && (*aBoard)[tempX][tempY].idPiece >= idBlackKing)
					return SHOOT_CONVERT_PAWN;
						
				
				if((*aBoard)[tempX][tempY].idPiece >= idBlackKing)
					return SHOOT;
				else
					return ILLEGAL;
			}
		}
		else
		{
			if(tempY - y == 1)
			{
				if(tempY == 8 && (*aBoard)[tempX][tempY].idPiece >= idWhiteKing && (*aBoard)[tempX][tempY].idPiece < idBlackKing)
					return SHOOT_CONVERT_PAWN;
				
				if((*aBoard)[tempX][tempY].idPiece < idBlackKing && (*aBoard)[tempX][tempY].idPiece > idEmpty)
					return SHOOT;
				else
					return ILLEGAL;
			}
		}
	}
	
	return ILLEGAL;
};