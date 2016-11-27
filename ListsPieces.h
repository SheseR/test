/*
This class describes lists of pieces.
The object of this class includes two lists from white and black pieces(16 - pieces)
void setNewGame() sets flagLive in true for all pieces....
void setAditionalPosition() sets flagLive only for.....
void addNewPiece(int aPiece, eColor aColor, int aPosX, int aPosY) is used for adding piece if the same piece encountered  previously in this list 
*/
#pragma once
#include "source.h"
#include "Piece.h"

class CListsPieces
{
	vector<CPiece *> whitePieces;
	vector<CPiece *> blackPieces;

//---------------prototype of funcstions---------------------//
private:
    void _init(void);
public:
    CListsPieces();
    ~CListsPieces();
//--------------------for handling of variables--------------//
    void setNewGame();
    void setAditionalPosition();
	void addNewPiece(int aPiece, eColor aColor, int aPosX, int aPosY);
	void cleanLists();
//-------------------set and get functions-----------------------//
    const char   &getFlagLive(eColor aColor, const int &aID)const;
    const ePiece &getPiece(eColor aColor, const int &aID)const;
    vector<CPiece *> getVectorWhitePieces();
    vector<CPiece *> getVectorBlackPieces();
    CPiece* getPtrWhitePiece(const int &aIDPiece);
    CPiece* getPtrBlackPiece(const int &aIDPiece);
//----------------------draw functions--------------------------//
	void draw();
};

