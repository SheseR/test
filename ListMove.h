/*
This class describes the recording of the move piece.
int boxPlayerPosX, 	int boxPlayerPosY, 	int boxPosX, 	int boxPosY, 	int boxHeight - these variables set position on the display the box of the recording.
It is used by run game mode.
struct sNote - stract of one half move. 
Where string notePositionX	and int notePositionY are the position piece after illegal move.(exemple Qe4 - Q - piece, e is position X, 4 - position Y )
enum eNote is enum of moves.
the note:
EASY_MOVE ----------in vector notestyle (" ");
SHOOTING -----------in vector notestyle (":");
SHORT_CASTLING -----in vector notestyle ("0-0");
LONG_CASTLING ------in vector notestyle ("0-0-0");
CHECK---------------in vector notestyle ("+");
MAT-----------------in vector notestyle ("X");
The notePieces stores string name pieces for the recording:
KING = "K", QUEEN = "Q", ROOK	= "R", BISHOP	= "B", KNIGHT = "N", PAWN = " ";
vector<sNote> note - it is all list of movies for a run game.
void newNoteStruct()  clears of vector<sNote> note for new game...
The shawing of it is described by CAllegroWrap class in  void CAllegroWrap::drawNote(vector<CListMove::sNote>& aNote).
*/
#pragma once
#include "source.h"
#include "Piece.h"

class CListMove
{	
public:
	enum eNote
	{
		 EASY_MOVE = 0
		,SHOOTING
		,SHORT_CASTLING
		,LONG_CASTLING
		,CHECK
		,MAT
	};
	struct sNote
	{
		eColor color;
		string piece;
		string notePositionX;
		int notePositionY;
		string noteStyle;
		eMove move;
	};
	
private:	
	vector<string> noteStyle;
	vector<string> notePosition;
	vector<string> notePieces;

	int boxPosX;
	int boxPosY;
	int boxHeight;
	int boxPlayerPosX;
	int boxPlayerPosY;

	vector<sNote> note;

//---------------prototype functions-----------------------//
private:
	void _initVectorNoteStyle();
	void _initVectorNotePosition();
	void _initVectorNotePieces();
public:
	CListMove();
	~CListMove();

	void newNoteStruct();
//-------------------get and set functions----------------------//
	vector<sNote>& getVectorNote();
	void setNoteStruct(CPiece * aPiece, eMove aMove, int aCountMove, bool aCheck);
	string* setNoteString(sNote);
	//-------------------draw functions-----------------------------//
	void draw();
};

