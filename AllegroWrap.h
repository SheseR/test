/*
This class is Singleton. It desribes an engine of game. There are variables  and function of Allegro in here.
It is initialized by void init_singltons() in top of main.cpp.
CMenuMode gMenuMode, CLocalGame	gLocalGame, CRunGameMode gRunGameMode, CSetPositionMode gSetPositionMode are objects of the classes of game modes.
bool flagSetPositionMode - It is flag which shows which position to need to initialize for run_game_mode. (false - new game, true - from set_position)
void run() - the main game loop. This function recievs allegro events and transmits it to function (throwEventUser(ALLEGRO_EVENT aEvent)) for handling
Also there is drawing at the bottom of this function.
void handleEventOnBoard(ALLEGRO_EVENT aEvent) - for handling events of run_game_mode. 
void handleEventForSetPosition(ALLEGRO_EVENT aEvent) - for handling events of set_poition_mode. Both functions receive events from throwEventUser(ALLEGRO_EVENT aEvent) 
and manage objects of game modes...
*/
#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include "source.h"

#include "GameMode.h"
#include "MenuMode.h"
#include "LocalGame.h"
#include "RunGameMode.h"
#include "ListMove.h"
#include "SetPositionMode.h"

class CAllegroWrap
{
private:   
 //---------------- for alegro --------------------//
	int display_width;	 
    int display_height; 
   
    ALLEGRO_DISPLAY		    *display	;	    
    ALLEGRO_FONT			*font_menu	;      
    ALLEGRO_FONT			*font24		;	
    ALLEGRO_EVENT_QUEUE     *event_queue;	
                                        ;
    ALLEGRO_BITMAP *imagePawnWhite		;	
    ALLEGRO_BITMAP *imageKnightWhite	;	
    ALLEGRO_BITMAP *imageBishopWhite	;	
    ALLEGRO_BITMAP *imageRookWhite		;	
    ALLEGRO_BITMAP *imageQueenWhite		;    
    ALLEGRO_BITMAP *imageKingWhite		;	
    ALLEGRO_BITMAP *imagePawnBlack		;	
    ALLEGRO_BITMAP *imageRookBlack		;	
    ALLEGRO_BITMAP *imageKnightBlack	;	
    ALLEGRO_BITMAP *imageBishopBlack	;	
    ALLEGRO_BITMAP *imageQueenBlack		;    
    ALLEGRO_BITMAP *imageKingBlack		;	

	ALLEGRO_MOUSE_CURSOR *cursorPawnWhite		;
	ALLEGRO_MOUSE_CURSOR *cursorKnightWhite		;
	ALLEGRO_MOUSE_CURSOR *cursorBishopWhite		;
	ALLEGRO_MOUSE_CURSOR *cursorRookWhite		;
	ALLEGRO_MOUSE_CURSOR *cursorQueenWhite		;
	ALLEGRO_MOUSE_CURSOR *cursorKingWhite		;
	ALLEGRO_MOUSE_CURSOR *cursorPawnBlack		;
	ALLEGRO_MOUSE_CURSOR *cursorRookBlack		;
	ALLEGRO_MOUSE_CURSOR *cursorKnightBlack		;
	ALLEGRO_MOUSE_CURSOR *cursorBishopBlack		;
	ALLEGRO_MOUSE_CURSOR *cursorQueenBlack		;
	ALLEGRO_MOUSE_CURSOR *cursorKingBlack		;

//---------------- for game modes ----------------//
	bool doneGame;
	eGameMode gameMode;
    CMenuMode			gMenuMode		;
    CLocalGame			gLocalGame		;	
    CRunGameMode		gRunGameMode	;	
    CSetPositionMode	gSetPositionMode;

    bool flagSetPositionMode; 

	bool winnerWhite;
	bool winnerBlack;

	//-------- for teh box of recording moves-----------// 
	int boxListMovePosX	;
    int boxListMovePosY	;
    int boxListMoveHeight;
    int boxListMoveWidth;
    int boxListMoveWhite;
    int boxListMoveBlack;
    int maxShowMoves	;

//------------------------Prototype function------------------------------//
private:
    CAllegroWrap();
    ~CAllegroWrap();

    void _init_box_list_move();
	void _init_cursor();
	void _loadSourses();
	void _endGame(eColor aColor);

public:
    static CAllegroWrap &instance();
	void initAllegro();

//--------------for main loop----------------------------//
	void run();
	void throwEventUser(ALLEGRO_EVENT aEvent);				//--- handles event from main loop and transmits it to next function
	void handleEventOnBoard(ALLEGRO_EVENT aEvent);			//--- event handling for RUN_GAME_MODE
    void handleEventForSetPosition(ALLEGRO_EVENT aEvent);	//--- event handling for SET_POSIT_MODE

//-------------for drawwing-------------------------------//
    void drawButtonsAllegro(std::vector<sButton>& aButtons, int aFlagButton);
    void drawCell(sCell aCell);    
    void drawPiece(const CPiece &aObj);
    void drawNote(vector<CListMove::sNote>& aNote);	
	void drawString(string aString, int aPosX, int aPosY);
	void drawRectangle(int aPosX, int aPosY, int aWidth, int aHeight);
	void drawRactangeleForNote();

//-------------for set and get ---------------------------//   
	void setFlagSetPositionMode(bool aFlag);
	void setCursor(ePiece aPiece, eColor aColor);
	void setTitleWindow();
	void setWinner(eColor eColor);

//------------for native dialog massage--------------------//  
	void blindInfo();							
	int questionChangeMode(eButton aButton);
};
//----------for init singltone in main.cpp-----------------//
void init_singltons();

