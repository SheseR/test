/*
This class describes main game board. It includes vector with the positions of cells (board) and vectors of notifications.
void clearBoard() is used for initialize new game. There are the idPieces on board is cleared. The object of this class is used for checking legal move of pieces. 
*/
#pragma once
#include "source.h"
#include "Piece.h"

class CBoardMain
{
	vector<vector<sCell>> board;
	
	vector<string> wordsNotificat;
	vector<string> numbersNotificat;

//-----------------prototype functions--------------------//
private:
	void _init();
	void _initNotification();

public:
	CBoardMain();
	~CBoardMain();
	
	void clearBoard();
	void deleteIDPiece(int aI, int aJ);

//-------------get and set functions-------------//
	const sCell &getCell(int aI, int aJ)const;
	const char getIDPiece(int aI, int aJ)const;
	vector<vector<sCell>>* getPtrBoard();	
	void setIDPiece(int aI, int aJ, char aID);
	void setPieces(vector<CPiece *> aVectorPieces);
//--------------draw fanctions-------------------//
	void draw();
};

