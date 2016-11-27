/*
This class is a child of CGameMode class.
This class describes the setting position game mode. It is initialized in the CAllegroWrap class.
It includs buttons of the navigation, object of additional list piece (Pieces are used as a sourse for choice ), 
object of a  pieces list for run_gameL_mode and  object of main board. 
void _initPieces() - sets a flagLive (true) for only one different piece of additionalListPieces. 
CListsPieces getNewPosition() - return newPositionListPieces for run_game_mode in main loop when to need to initialize a game from setposition mode..
bool isCatchPiece(int aPosX, int aPosY),	void setPieceNewPosition(int aI, int aJ),  bool checkPositionPiece(int aPosX, int aPosY),
The arguments aPosX and aPosY are a position of mouse on a display. The argument of functions int aI and int aJ are position on the board(multiples of sizeCell).
void resetCatchPiece() - these functions are used for installation of a position.
eGameMode changeGameMode() - receives results from wrap engine and changes game modes. 
*/
#pragma once
#include "gamemode.h"
#include "BoardMain.h"
#include "ListsPieces.h"

class CSetPositionMode : public CGameMode
{
    vector<sButton> buttons;
    CBoardMain board;
    
    CListsPieces additionalListsPieces;  // list pieces a right top of screen
    CListsPieces newPositionListPieces;

    int catchWhitePiece;
    int catchBlackPiece;
//------------------------Prototype function------------------------------//
private:
	void _initButtons();
	void _initPieces();
public:
	CSetPositionMode();
	~CSetPositionMode();
 
	eGameMode changeGameMode();
//---------------------for moving pieces on the display-------------------//
	bool isCatchPiece(int aPosX, int aPosY);
	void setPieceNewPosition(int aI, int aJ);
    bool checkPositionPiece(int aPosX, int aPosY);
	void resetCatchPiece();
//--------------------set and get ----------------------------------------//	
	CListsPieces getNewPosition();
//--------------------for drawing-----------------------------------------//
	void draw();
	void drawButtons();
};

