#include "Piece.h"

CPiece::CPiece(ePiece aPiece)
    :x(0)
    ,y(0)
    ,flagLive(false)
    ,piece(aPiece)
    ,color(WHITE)
{
}
CPiece::CPiece(int aPosX, int aPosY, eColor aColor, ePiece aPiece)
    :x(aPosX / sizeCell)
    ,y(aPosY / sizeCell)
    ,flagLive(false)
    ,piece(aPiece)
    ,color(aColor)
{
}
CPiece::~CPiece(void)
{
}

void CPiece::resetPositionPiece(int aPosX, int aPosY)
{
    if(aPosX < 50 || aPosY < 50 || aPosX > 450 || aPosY > 450)
        return;

    x = aPosX / sizeCell;
    y = aPosY / sizeCell;
};
void CPiece::setFlagLive(bool aLive)
{
    flagLive = aLive;
};
void CPiece::setColor(eColor aColor)
{
    color =aColor;
};
void CPiece::setPiece(int aI, int aJ, eColor aColor)
{
    x = aI;
    y = aJ;
    color = aColor;
}

eMove CPiece::move(int aPosX, int aPosY, vector< vector<sCell> >* aBoard)
{
    int tempX = aPosX / sizeCell;
    int tempY = aPosY / sizeCell;

    if (tempX == x && tempY == y)
        return ILLEGAL;

    return _move(tempX, tempY, aBoard);
}
