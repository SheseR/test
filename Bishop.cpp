#include "Bishop.h"

CBishop::CBishop()
    :CPiece(BISHOP)
{
}
//-----------------------------------------------------------------
CBishop::CBishop(int aPosX, int aPosY, eColor aColor) 
    : CPiece(aPosX, aPosY, aColor, BISHOP)
{ 
}
//-----------------------------------------------------------------
CBishop::~CBishop()
{
}
//-----------------------------------------------------------------
eMove CBishop::_move(int tempX, int tempY,  vector<vector<sCell>>* aBoard)
{
    if(tempX - x == tempY - y)      // it is a diagornal (1,1 and 8,8 secondary diagonal)
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
    else if(x - tempX == tempY - y)						// it is a diagonal (1,8 adn 8 , 1)
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
    else
        return ILLEGAL;
};



