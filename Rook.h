/*
This class is child of CPiece class.
bool flagMove is initialized on false. It is used for checking on illegal castlling. If it is false then castling could be use.		
*/

#pragma once
#include "piece.h"

class CRook : public CPiece
{
	bool flagMove;

//----------------prototepy functions--------------------------//	
public:
	CRook();
	CRook(int aPosX, int aPosY, eColor aColor);
	~CRook();

	void setFlagMove(bool aMove);
	const bool &getFlagMove()const				{return flagMove;}

private:
    eMove _move(int aPosX, int aPosY, vector<vector<sCell>>* aBoard);
};

