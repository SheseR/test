#include "ListMove.h"
#include "AllegroWrap.h"

CListMove::CListMove()
	:boxPlayerPosX(550)
	,boxPlayerPosY(50)
	,boxPosX(550)
	,boxPosY(100)
	,boxHeight(350)
{
	_initVectorNoteStyle();
	_initVectorNotePosition();
	_initVectorNotePieces();
}
//-----------------------------------------------------------------
CListMove::~CListMove()
{
}

//----------------private functions------------------------------//
void CListMove::_initVectorNoteStyle()
{

	noteStyle.resize(6);
	noteStyle[EASY_MOVE]		= " ";
	noteStyle[SHOOTING]			= ":";
	noteStyle[SHORT_CASTLING]	= "0-0";
	noteStyle[LONG_CASTLING]	= "0-0-0";
	noteStyle[CHECK]			= "+";
	noteStyle[MAT]				= "X";
};
void CListMove::_initVectorNotePosition()
{
	notePosition.resize(9);

	notePosition[0] = " ";
	notePosition[1] = "a";
	notePosition[2] = "b";
	notePosition[3] = "c";
	notePosition[4] = "d";
	notePosition[5] = "e";
	notePosition[6] = "f";
	notePosition[7] = "g";
	notePosition[8] = "h";
};
void CListMove::_initVectorNotePieces()
{
	notePieces.resize(6);
	notePieces[KING]	= "K";
	notePieces[QUEEN]	= "Q";
	notePieces[ROOK]	= "R";
	notePieces[BISHOP]	= "B";
	notePieces[KNIGHT]	= "N";
	notePieces[PAWN]	= " ";
};

//---------------public functions--------------------------------//
void CListMove:: newNoteStruct()
{
	note.clear();
};
//--------------set and get functions-----------------------------//
void CListMove::setNoteStruct(CPiece * aPiece, eMove aMove, int aCountMove, bool aCheck)
{
	int noteCountMove = 1;
	
	if((aCountMove % 2 == 0))
		noteCountMove = aCountMove / 2;
	else
		noteCountMove = (aCountMove + 1) / 2;

	sNote tempNote;
	
	tempNote.piece = notePieces[aPiece->getPiece()];
	tempNote.color = aPiece->getColor();
	tempNote.notePositionX = notePosition[aPiece->getX()];
	tempNote.notePositionY = 9 - aPiece->getY();
	tempNote.move = aMove;

	switch(aMove)
	{
	case LEGAL:
		tempNote.noteStyle = noteStyle[EASY_MOVE];
		break;
	case SHOOT:
		tempNote.noteStyle = noteStyle[SHOOTING];
		break;
	case CASTLING:
		if(aPiece->getX() == 7)
			tempNote.noteStyle = noteStyle[SHORT_CASTLING];
		else
			tempNote.noteStyle = noteStyle[LONG_CASTLING];
			break;
	default:
		tempNote.noteStyle = "*";
		break;
	}

	if(aCheck)
		tempNote.noteStyle = noteStyle[CHECK];

	note.push_back(tempNote);
};
vector<CListMove::sNote>&CListMove::getVectorNote()
{
	return note;
};
//-------------draw functions----------------------------------//
void CListMove::draw()
{
	CAllegroWrap & inst = CAllegroWrap::instance();
	
	inst.drawRactangeleForNote();
	inst.drawNote(this->getVectorNote());
};


