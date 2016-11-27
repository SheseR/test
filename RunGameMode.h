/*
This class is child of CGameMode class.
It discribes game logic on main board after creating new game or setting position...
bool isCatchPiece(int aPosX, int aPosY) sets values for catchBlackPiece and catchWhitePiece and returns the success of catching piece.
catchBlackPiece, catchWhitePiece;  - the current piece which is caught by the player... It is equal the index piece of mListsPieces;
The value of a variables are:
-1 - no Piece; 0 - King; 1 - Queen; 2,3 - Rooks; 4,5 - Bishops; 6,7 - Knights; 8,15 - Pawns; 
int countTurns - the current move in the game
The value of a variables are: if countTurns is odd then the turn of white, so if CountTurns is even then turn of black.
mListsPieces - two vectors of pieces on the main board;
it depends on what was launched initNewGame() or initGameFromSetPosition(CListsPieces &aNewPosition);
initGameFromSetPosition(CListsPieces &aNewPosition) - copies pieces from aNewPosition to mListsPieces
CListsPieces &aNewPosition - the link of the pieces list  on board in SET_POSITION_MODE;
For movine pieces on the board where int aPosX, int aPosY are the position mouse on the dispay;
bool isCatchPiece(int aPosX, int aPosY); void changePosPiece(int aPosX, int aPosY);
void changePosWitePiece(int aPosX, int aPosY);	void changePosBlackPiece(int aPosX, int aPosY);
void changePosCasling(eColor aColor, int aPosX, int aPosY);
These functions use function of checking on mat for illegal moves:
bool isChackOnMat(eColor aColor) includes the next functions:
bool _chakOnMatMoveKing(eColor aColor)		- check on illegal move kind 
bool _chekOnMatShootPiece(eColor aColor)	- check on shooting of attack piece 
bool _chekONMatHiding(eColor aColor);		- check on hedding kind of own piece
If all functions return true then isChackOnMat(eColor aColor) return true. So It is a mat kind;
*/
#pragma once
#include "gamemode.h"
#include "BoardMain.h"
#include "ListsPieces.h"
#include "ListMove.h"

class CRunGameMode : public CGameMode
{
	int catchBlackPiece;
    int catchWhitePiece;
    int countTurns;

    vector<sButton> buttons;
    CBoardMain      board;
    CListsPieces    mListsPieces;
    CListMove       noteMove;

private:
	void _initButtons();
	bool _chakOnMatMoveKing(eColor aColor);
	bool _chekOnMatShootPiece(eColor aColor);
	bool _chekONMatHiding(eColor aColor);
	void _convertPawn(CPiece* aPawn,eColor aColor, int aPosX, int aPosY, bool aFlagShoot);
public:
    CRunGameMode();
    ~CRunGameMode();
	
	void initNewGame();
    void initGameFromSetPosition(CListsPieces &aNewPosition);

	eGameMode changeGameMode(); 

	bool isCatchPiece(int aPosX, int aPosY);
	void changePosPiece(int aPosX, int aPosY);
	void changePosWitePiece(int aPosX, int aPosY);
	void changePosBlackPiece(int aPosX, int aPosY);
	void changePosCasling(eColor aColor, int aPosX, int aPosY);	
	bool isChackOnMat(eColor aColor);
	
	CListsPieces getListPieces();
	const int  &getCountTurn()const  {return countTurns;}
	
	void drawButtons();
	void draw();
};

