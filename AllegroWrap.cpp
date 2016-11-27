#include "AllegroWrap.h"


CAllegroWrap::CAllegroWrap()
	:display_width(800)
	,display_height(600)
	,gameMode(MENU_MODE)
	,doneGame(true)
	,flagSetPositionMode(false)
	,winnerWhite(false)
	,winnerBlack(false)
{
    initAllegro();
    _init_box_list_move();
	_init_cursor();
}
CAllegroWrap::~CAllegroWrap()
{
}

//-----------------Private functions--------------------------------//
void CAllegroWrap:: _init_box_list_move()
{
     boxListMovePosX	= 550;
     boxListMovePosY	= 50;
     boxListMoveHeight	= 300;
     boxListMoveWidth	= 150;

     boxListMoveWhite = 580;
     boxListMoveBlack = 630;

     maxShowMoves  = 14;
}
void CAllegroWrap::_init_cursor()
{
	
	cursorPawnWhite		= al_create_mouse_cursor(imagePawnWhite		 ,15, 15);
	cursorKnightWhite	= al_create_mouse_cursor(imageKnightWhite	 ,15, 15);
	cursorBishopWhite	= al_create_mouse_cursor(imageBishopWhite	 ,15, 15);
	cursorRookWhite		= al_create_mouse_cursor(imageRookWhite		 ,15, 15);
	cursorQueenWhite	= al_create_mouse_cursor(imageQueenWhite	 ,15, 15);
	cursorKingWhite		= al_create_mouse_cursor(imageKingWhite		 ,15, 15);
	cursorPawnBlack		= al_create_mouse_cursor(imagePawnBlack		 ,15, 15); 
	cursorRookBlack		= al_create_mouse_cursor(imageRookBlack		 ,15, 15); 
	cursorKnightBlack	= al_create_mouse_cursor(imageKnightBlack	 ,15, 15);
	cursorBishopBlack	= al_create_mouse_cursor(imageBishopBlack	 ,15, 15);
	cursorQueenBlack	= al_create_mouse_cursor(imageQueenBlack	 ,15, 15);
	cursorKingBlack		= al_create_mouse_cursor(imageKingBlack		 ,15, 15);
};
void CAllegroWrap:: _loadSourses()
{
    font_menu = al_load_font("source/Rasanskool.ttf",     24, 0);
    font24	  = al_load_font("source/Orbitron-Black.ttf", 14, 0);

    imageKingWhite    = al_load_bitmap("source/whiteKing.png"  );	
    imageKingBlack    = al_load_bitmap("source/blackKing.png"  );
    imagePawnWhite    = al_load_bitmap("source/whitePawn.png"  );
    imagePawnBlack    = al_load_bitmap("source/blackPawn.png"  );
    imageKnightWhite  = al_load_bitmap("source/whiteKnight.png");
    imageKnightBlack  = al_load_bitmap("source/blackKnight.png");
    imageRookWhite	  = al_load_bitmap("source/whiteRook.png"  );
    imageRookBlack	  = al_load_bitmap("source/blackRook.png"  );
    imageBishopWhite  = al_load_bitmap("source/whiteBishop.png");
    imageBishopBlack  = al_load_bitmap("source/blackBishop.png");
    imageQueenWhite   = al_load_bitmap("source/whiteQueen.png" );
    imageQueenBlack   = al_load_bitmap("source/blackQueen.png" );
};
void CAllegroWrap::_endGame(eColor aColor)
{
	if(aColor == WHITE)
	{
		 al_show_native_message_box(display,  "The game is end!", "The mat of white king", "Black is a winner?\n Go to Menu.", NULL,ALLEGRO_MESSAGEBOX_QUESTION);
	}
	else
	{
		al_show_native_message_box(display,  "The game is end!","The mat of black king", "White is a winner!\n Go to Menu.", NULL,ALLEGRO_MESSAGEBOX_QUESTION);
	}

	winnerWhite = false;
	winnerBlack = false;
};

//------------------Public functions--------------------------------//
CAllegroWrap& CAllegroWrap:: instance()
{
    static CAllegroWrap inst;
    return inst;
};
void CAllegroWrap::initAllegro()
{  
    if(!al_init())
	{
		al_show_native_message_box(NULL, NULL, NULL, "failled to initialize allegro!", NULL, NULL);
		return ;
	}

    display = al_create_display(display_width, display_height);
            
    if(!display)
    {
        al_show_native_message_box(NULL, NULL, NULL, "failled to initialize display!", NULL, NULL);
        return ;
    }

    event_queue = al_create_event_queue();
    al_init_font_addon();
    al_init_ttf_addon();
	al_init_image_addon();   
    al_init_primitives_addon();
   
	al_install_mouse();
  
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_mouse_event_source());

    _loadSourses();
}
//-------------------for main loop----------------------------//
void CAllegroWrap:: run(void)
{
    while(doneGame)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);
        
        if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            doneGame = false;
            continue;
        }
        
        throwEventUser(ev);
        
        switch(gameMode)
        {
            case INIT_MODE:
                //gameMode = MENU_MODE;
                break;
            case MENU_MODE:
                gMenuMode.draw();
                break;
            case LOCAL_MODE:
                gLocalGame.draw();
                break;
            case RUN_MODE:
                gRunGameMode.draw();
                break;
            case SET_POSITION_MODE:
                gSetPositionMode.draw();
                break;
            case NET_MODE:
                blindInfo();
                gameMode = MENU_MODE;
                break;
            case HELP_MODE:
                blindInfo();
                gameMode = MENU_MODE;
                break;
            case EXIT_MODE:
                doneGame = false;
                break;
        }
        setTitleWindow();
        al_flip_display();
		
		if(winnerWhite)
		{
			_endGame(WHITE);
			gameMode = MENU_MODE;
		}
		else if(winnerBlack)
		{
			_endGame(BLACK);
			gameMode = MENU_MODE;
		}

    }
};
void CAllegroWrap::throwEventUser(ALLEGRO_EVENT aEvent)
{
    int x = aEvent.mouse.x;
    int y = aEvent.mouse.y;
    
    switch(gameMode)
    {
        case INIT_MODE:
            if(!flagSetPositionMode)
                gRunGameMode.initNewGame(); // set new Position from new game
            else
                gRunGameMode.initGameFromSetPosition(gSetPositionMode.getNewPosition()); // set new Position from new set position
            gameMode = RUN_MODE;
            break;
        case MENU_MODE:
            gMenuMode.setCoverButton(x, y);
            if(aEvent.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && aEvent.mouse.button & 1)
                gameMode = gMenuMode.changeGameMode();
            break;
        case LOCAL_MODE:
            gLocalGame.setCoverButton(x, y);
            if(aEvent.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && aEvent.mouse.button & 1)
                gameMode = gLocalGame.changeGameMode();
            break;
        case RUN_MODE:			
            gRunGameMode.setCoverButton(x, y);												// for covering by mouse on  buttons
            if(aEvent.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && aEvent.mouse.button & 1)
                gameMode = gRunGameMode.changeGameMode();				
            
            if(gameMode == RUN_MODE)
                handleEventOnBoard(aEvent);
            else
                gRunGameMode.getListPieces().cleanLists();
            break;
        case SET_POSITION_MODE:
            gSetPositionMode.setCoverButton(x, y);
            if(aEvent.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && aEvent.mouse.button & 1)
                gameMode = gSetPositionMode.changeGameMode();	
            if(gameMode == SET_POSITION_MODE)
                handleEventForSetPosition(aEvent);		
            break;
        case NET_MODE:
            blindInfo();
            gameMode = MENU_MODE;
            break;
        case HELP_MODE:
            blindInfo();
            gameMode = MENU_MODE;
            break;
        case EXIT_MODE:
            doneGame = false;
            break;		
    }
}
void CAllegroWrap::handleEventOnBoard(ALLEGRO_EVENT aEvent)
{
    int x = aEvent.mouse.x;
    int y = aEvent.mouse.y;

    static bool isCatchPiece = false;
    if(aEvent.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && aEvent.mouse.button & 1)
    {
        if(gRunGameMode.isCatchPiece(x, y))
        {
            isCatchPiece = true;
        }
    }

    if( isCatchPiece && aEvent.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && (aEvent.mouse.button & 1))
	{
        setCursor(EMPTY, WHITE);
		gRunGameMode.changePosPiece(x, y);
	}	
};
void CAllegroWrap::handleEventForSetPosition(ALLEGRO_EVENT aEvent)
{
    int posX = aEvent.mouse.x;
    int posY = aEvent.mouse.y;

    static bool isCatchPiece = false;
    if(aEvent.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && aEvent.mouse.button & 1)
    {
        if(gSetPositionMode.isCatchPiece(posX, posY))
            isCatchPiece = true;
        else
            isCatchPiece = false;
    }

    if( isCatchPiece && aEvent.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && (aEvent.mouse.button & 1))
	{
        setCursor(EMPTY, WHITE); // kostil
		
		if(gSetPositionMode.checkPositionPiece(posX, posY))
			gSetPositionMode.setPieceNewPosition(posX, posY);
		
		gSetPositionMode.resetCatchPiece();
	}
};
//--------------------for drawwing-------------------------------//
void CAllegroWrap::drawButtonsAllegro(std::vector<sButton>& aButtons, int aFlagButton)
{
    al_clear_to_color(al_map_rgb(50,50,50));
    
    for(int i = 0; i < aButtons.size(); i++)
    {
        if(i == aFlagButton)
            al_draw_textf(font_menu, al_map_rgb(100,100,100), gBoxButtonsPos_X, gBoxButtonsPos_Y + i * gBoxButtonHeight, 0, "%s", aButtons[i].strButton.c_str());
        else
            al_draw_textf(font_menu, al_map_rgb(255,255,255), gBoxButtonsPos_X, gBoxButtonsPos_Y + i * gBoxButtonHeight, 0, "%s",aButtons[i].strButton.c_str());
    }
};
void CAllegroWrap::drawCell(sCell aCell)
{
	register int posX = aCell.x * sizeCell;
    register int posY = aCell.y * sizeCell;
    
	if((aCell.x + aCell.y) % 2  == 0)
        al_draw_filled_rectangle(posX, posY, posX + sizeCell, posY + sizeCell,  al_map_rgb(235, 235, 235));
    else
        al_draw_filled_rectangle(posX, posY, posX + sizeCell, posY + sizeCell,  al_map_rgb(20, 20, 20));
}
void CAllegroWrap::drawString(string aString, int aPosX, int aPosY)
{
	 al_draw_textf(font24, al_map_rgb(255,255,255), aPosX, aPosY, 0, "%s", aString.c_str());
};
void CAllegroWrap::drawPiece(const CPiece &aPiece)
{
    if (!aPiece.getLive())
        return;

    register int aPosX = aPiece.getX() * sizeCell;
    register int aPosY = aPiece.getY() * sizeCell;

    ALLEGRO_BITMAP *image = nullptr;
    ePiece piece = aPiece.getPiece();
    eColor color = aPiece.getColor();

    switch (color)
    {
        case WHITE:
        {
            switch (piece)
            {
                case KING:   image = imageKingWhite;   break;
                case QUEEN:  image = imageQueenWhite;  break;
                case ROOK:   image = imageRookWhite;   break;
                case BISHOP: image = imageBishopWhite; break;
                case KNIGHT: image = imageKnightWhite; break;
                case PAWN:   image = imagePawnWhite;   break;
                case EMPTY:break;
            }
            break;
        }
        case BLACK:
        {
            switch (piece)
            {
                case KING:   image = imageKingBlack;   break;
                case QUEEN:  image = imageQueenBlack;  break;
                case ROOK:   image = imageRookBlack;   break;
                case BISHOP: image = imageBishopBlack; break;
                case KNIGHT: image = imageKnightBlack; break;
                case PAWN:   image = imagePawnBlack;   break;
                case EMPTY: break;
                }
            break;
        }
    }
    al_draw_bitmap(image, aPosX, aPosY, 0);
}
void CAllegroWrap::drawNote(vector<CListMove::sNote>& aNote)
{
    int tempCountVector = aNote.size();
    int tempCounterTurn = 1;
    int tempPosColor	= 0;
    int startShowMove	= 0;

    if(tempCountVector >= maxShowMoves * 2)
    {
        startShowMove = tempCountVector -  maxShowMoves * 2;
        if(startShowMove % 2 != 0)
            startShowMove++;
    }
        
    int coefPosY = 1;
    
    for(int i = 0; i < maxShowMoves * 2; i++)
    {
        if(startShowMove + i >= tempCountVector)
            break;

        if(i == 0 || i == 1)
            coefPosY = 1;
        else if(i % 2 == 0)
            coefPosY++;

        if(tempCountVector - 1 < i)
            continue;
        
        if(aNote[startShowMove + i].color == WHITE)
            tempPosColor = boxListMoveWhite;
        else
            tempPosColor = boxListMoveBlack;

        if((startShowMove + i) == 0 && (startShowMove + i) == 1 )
            tempCounterTurn = 1;
        else if((startShowMove + i) % 2 == 0)
            tempCounterTurn = (startShowMove + i) /2 + 1;
        else
            tempCounterTurn = (startShowMove + i + 1) /2;

        if(i % 2 == 0)
            al_draw_textf(font24, al_map_rgb(255,255,255), boxListMoveWhite - 20, boxListMovePosY + coefPosY * 20, 0, "%2i",tempCounterTurn);

        if(aNote[startShowMove + i].move == CASTLING)
        {
            al_draw_textf(font24, al_map_rgb(255,255,255), tempPosColor, boxListMovePosY + coefPosY * 20, 0, " %s",aNote[startShowMove + i].noteStyle.c_str());
        }
        else
        {
            al_draw_textf(font24, al_map_rgb(255,255,255), tempPosColor, boxListMovePosY + coefPosY * 20, 0, " %s%s%i%s"
                ,aNote[startShowMove + i].piece.c_str()
                ,aNote[startShowMove + i].notePositionX.c_str()
                ,aNote[startShowMove + i].notePositionY
                ,aNote[startShowMove + i].noteStyle.c_str());	
        }
    }
};	
void CAllegroWrap::drawRactangeleForNote()
{	
	al_draw_rectangle(boxListMovePosX - 5, boxListMovePosY, boxListMovePosX + boxListMoveWidth
														, boxListMovePosY + boxListMoveHeight, al_map_rgb(40,40,40), 4);
};
void CAllegroWrap::drawRectangle(int aPosX, int aPosY, int aWidth, int aHeight)
{
	int border = 5;
	al_draw_rectangle(aPosX - border, aPosY - border, aPosX + aWidth + border, aPosY + aHeight + border, al_map_rgb(20,20,20), 5);
};
//-------------------for set and get ---------------------------//   
void CAllegroWrap:: setFlagSetPositionMode(bool aFlag)
{
    flagSetPositionMode = aFlag;
};
void CAllegroWrap::setTitleWindow()
{	
    switch(gameMode)
    {
        case MENU_MODE:
            al_set_window_title(display, "NAME GAME - MENU");
            break;
        case RUN_MODE:
            al_set_window_title(display, "NAME GAME - PLAY GAME");
            break;
        case SET_POSITION_MODE:
            al_set_window_title(display, "NAME GAME - SET POSITION GAME");
            break;
        case NET_MODE:
            al_set_window_title(display, "NAME GAME - NET GAME");
            break;
        case HELP_MODE:
            al_set_window_title(display, "NAME GAME - HELP");
            break;
        case LOCAL_MODE:
            al_set_window_title(display, "NAME GAME - LOCAL WINDOW");
            break;
        default:
            al_set_window_title(display, "NAME GAME - INIT GAME");
            break;
    }
};
void CAllegroWrap::setCursor(ePiece aPiece, eColor aColor)
{
	ALLEGRO_MOUSE_CURSOR *cursor = nullptr;
	
	if(aColor == WHITE)
	{
		switch(aPiece)
		{
			case KING:	cursor = cursorKingWhite;	break;
			case QUEEN:	cursor = cursorQueenWhite;	break;
			case ROOK:	cursor = cursorRookWhite;	break;
			case BISHOP: cursor = cursorBishopWhite;break;
			case KNIGHT: cursor = cursorKnightWhite;break;
			case PAWN:	cursor = cursorPawnWhite;	break;
			case EMPTY:
				break;
		}
	}
	else
	{
		switch(aPiece)
		{	
			case KING:	cursor = cursorKingBlack;	break;
			case QUEEN:	cursor = cursorQueenBlack;	break;
			case ROOK:	cursor = cursorRookBlack;	break;
			case BISHOP: cursor = cursorBishopBlack;break;
			case KNIGHT: cursor = cursorKnightBlack;break;
			case PAWN:	cursor = cursorPawnBlack;	break;
			case EMPTY:	
				break;
		}
	}
	al_set_mouse_cursor(display, cursor);
	if(aPiece != EMPTY)
		al_set_mouse_cursor(display, cursor);	
	else
		al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT); 

};
void CAllegroWrap::setWinner(eColor aColor)
{
	if(aColor == WHITE)
		winnerWhite = true;
	else
		winnerBlack = true;
};

//-----------------for native dialog massage--------------------//  
int CAllegroWrap::questionChangeMode(eButton aButton)
{
	int result = 0;
	
	switch(aButton)
	{
	case BUTTON_NEW_GAME:
		result = al_show_native_message_box(display,  "Change game mode", "Do you want to greate a new game?", "This game will be lost", NULL, ALLEGRO_MESSAGEBOX_YES_NO);
		break;
	case BUTTON_SURRENDER:
		result = al_show_native_message_box(display,  "Change game mode", "Do you surrender?", "Go to menu", NULL, ALLEGRO_MESSAGEBOX_YES_NO);
		break;
	case BUTTON_RETURN:
		result = al_show_native_message_box(display,  "Change game mode", "The game will be lost... Are you sure?", "Go to menu", NULL, ALLEGRO_MESSAGEBOX_YES_NO);
		break;
	case BUTTON_CLEAN_POSITION:
		result = al_show_native_message_box(display,  "Change game mode", "Are you sure to clear this position?", " ", NULL, ALLEGRO_MESSAGEBOX_YES_NO);
		break;
	}

	return result;
}
void CAllegroWrap::blindInfo()
{
    al_show_native_message_box(display, NULL, "this module is developed", "this module is developed", NULL, NULL);
};

//--------------------init singltone for main.cpp----------------//
void init_singltons()
{
    CAllegroWrap:: instance();
}




