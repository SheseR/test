/*
This class is child of CPiece class.
bool flagMove is initialized on false. It is used for checking on illegal castlling. If it is false then castling could be use.
 bool isChack(vector<CPiece*> & aVector, vector<vector<sCell>>* aBoard) - checks on check of a king.
 Receive arguments of vector enother color list of pieces and main bouard. 
*/
#pragma once
#include "piece.h"

class CKing : public CPiece
{
    bool flagMove; 

// ---------prototype function------------------------//
public:
    CKing();
    ~CKing();
    CKing(int aPosX, int aPosY, eColor aColor);

    bool isChack(vector<CPiece*> & aVector, vector<vector<sCell>>* aBoard);
    void setFlagMove(bool aMove);

private:
    eMove _move(int aPosX, int aPosY, vector<vector<sCell>>* aBoard);
};

