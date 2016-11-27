/*
This class is shild of CPiece.
eMove _move(int aPosX, int aPosY, vector<vector<sCell>>* aBoard) - virtual function of CPiece class;
*/
#pragma once
#include "piece.h"

class CPawn : public CPiece
{
public:
    CPawn();
    CPawn(int aPosX, int aPosY, eColor aColor);
	~CPawn();

private:
    eMove _move(int aPosX, int aPosY, vector<vector<sCell>>* aBoard);
};

