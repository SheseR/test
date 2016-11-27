/*
This class is a child of CPiece class;
It describes a bishop;
*/
#pragma once
#include "piece.h"

class CBishop : public CPiece
{
//--------------------prototype function---------------------//
public:
    CBishop();
    CBishop(int aPosX, int aPosY, eColor aColor);
	~CBishop();

private:
    eMove _move(int aPosX, int aPosY,  vector<vector<sCell>>* aBoard);
};

