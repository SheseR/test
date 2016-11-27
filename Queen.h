/*
This class is child of CPiece class.
It describes a queen.
*/
#pragma once
#include "piece.h"

class CQueen : public CPiece
{
//--------------prototype functiona--------------------------//
public:
	CQueen();
	CQueen(int aPosX, int aPosY, eColor aColor);
	~CQueen();

private:
    eMove _move(int aPosX, int aPosY, vector<vector<sCell>>* aBoard);
};

