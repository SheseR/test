/*
This class is a base class.
The childrens are: CKind, CQueen, CKind, CRook, CBishop, CKnight, CPawn.
It includs from int x , int y - the position on the board,  bool flagLive - the appearence of piece on the board; 
eMove move(int aPosX, int aPosY, vector< vector<sCell> >* aBoard) is used as a method overriding in its children...
It runs private virtual eMove _move(int aPosX, int aPosY, vector< vector<sCell> >* aBoard).
vector< vector<sCell> >* aBoard is used for simple looking for idPiece of cells.
void resetPositionPiece(int aPosX, int aPosY)  sets new position of piece afte the moving.
*/
#pragma once
#include "source.h"

class CPiece
{
protected:
    int     x;
    int     y;
    bool    flagLive;
    ePiece  piece;
    eColor  color;
//----------------prototype functions------------------------------//
private:
    virtual eMove _move(int aPosX, int aPosY, vector< vector<sCell> >* aBoard) = 0;
public:
    CPiece(ePiece aPiece = EMPTY);
    CPiece(int aPosX, int aPosY, eColor aColor, ePiece aPiece = EMPTY);
	 ~CPiece();

    void resetPositionPiece(int aPosX, int aPosY);
//---------------- GETTERS - SETTERS ----------------------------------//
	const int    &getX()const           {return x;}
    const int    &getY()const           {return y;}
    const bool   &getLive()const        {return flagLive; };
    const eColor &getColor()const       {return color;}
    const ePiece &getPiece()const       {return piece; };
	void setFlagLive(bool aLive);
    void setColor(eColor aColor);
    void setPiece(int aI, int aJ, eColor aColor);
 //----------------- function overriding------------------------------//
	eMove move(int aPosX, int aPosY, vector< vector<sCell> >* aBoard);
};

