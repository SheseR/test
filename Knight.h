/*
This class is child of Piece class. 
It describes a knight.
*/
#pragma once
#include "piece.h"

class CKnight :public CPiece
{
public:
	CKnight();
	CKnight(int aPosX, int aPosY, eColor aColor);
	~CKnight();

private:
    eMove _move(int aPosX, int aPosY, vector<vector<sCell>>* aBoard);
};

