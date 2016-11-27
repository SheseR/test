#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <cmath>
using namespace std;

//-------------------position the buttons of the display----------------//
const int gBoxButtonsPos_X = 550;
const int gBoxButtonsPos_Y = 400;
const int gBoxButtonWidth  = 150;
const int gBoxButtonHeight = 30;
enum eButton
{
     BUTTON_LOCAL_GAME
    ,BUTTON_NET_GAME
    ,BUTTON_EXIT_GAME
    ,BUTTON_NEW_GAME
    ,BUTTON_SET_POSITION
    ,BUTTON_RETURN
    ,BUTTON_HELP
    ,BUTTON_START_GAME
    ,BUTTON_SURRENDER
    ,BUTTON_FINISH
    ,BUTTON_CLEAN_POSITION
};
struct sButton 
{
    eButton eButton;
    string  strButton;
};

const int countCells = 9;
const int sizeCell	 = 50;

struct sCell
{
    int x;
    int y;
    char idPiece;
};

enum eGameMode
{
     INIT_MODE
    ,MENU_MODE
    ,LOCAL_MODE
    ,NET_MODE
    ,EXIT_MODE
    ,HELP_MODE
    ,RUN_MODE
    ,SET_POSITION_MODE
};

enum ePiece
{
     KING
    ,QUEEN
    ,ROOK
    ,BISHOP
    ,KNIGHT
    ,PAWN
    ,EMPTY
};
enum eColor
{
     WHITE
    ,BLACK
};

enum eMove
{
     ILLEGAL
    ,LEGAL
    ,SHOOT
    ,CASTLING
	,CONVERT_PAWN
	,SHOOT_CONVERT_PAWN
};

const char idEmpty				= -1;
const char idWhiteKing			= 0;
const char idWhiteQueen			= 1;
const char idWhiteRookLeft		= 2;
const char idWhiteRookRight		= 3;
const char idWhiteBishoopLeft	= 4;
const char idWhiteBishoopRight	= 5;
const char idWhiteKnightLeft	= 6;
const char idWhiteKnightRight	= 7;
const char idWhitePawnA			= 8;
const char idWhitePawnB			= 9;
const char idWhitePawnC			= 10;
const char idWhitePawnD			= 11;
const char idWhitePawnE			= 12;
const char idWhitePawnF			= 13;
const char idWhitePawnG			= 14;
const char idWhitePawnH			= 15;

const char idBlackKing			= 100;
const char idBlackQueen			= 101;
const char idBlackRookLeft		= 102;
const char idBlackRookRight		= 103;
const char idBlackBishoopLeft	= 104;
const char idBlackBishoopRight	= 105;
const char idBlackKnightLeft	= 106;
const char idBlackKnightRight	= 107;
const char idBlackPawnA			= 108;
const char idBlackPawnB			= 109;
const char idBlackPawnC			= 110;
const char idBlackPawnD			= 111;
const char idBlackPawnE			= 112;
const char idBlackPawnF			= 113;
const char idBlackPawnG			= 114;
const char idBlackPawnH			= 115;


