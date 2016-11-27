#include "GameMode.h"

CGameMode::CGameMode()
	:flagCoverButton(-1)
{
	_initButtons();
}
//-----------------------------------------------------------------
CGameMode::~CGameMode()
{
}
//-----------------------------------------------------------------
void CGameMode::_initButtons()
{
	localGame.eButton		= BUTTON_LOCAL_GAME		;
	netGame.eButton			= BUTTON_NET_GAME		;
	exitGame.eButton		= BUTTON_EXIT_GAME		;
	newGame.eButton			= BUTTON_NEW_GAME		;
	setPosition.eButton		= BUTTON_SET_POSITION	;
	returnMenu.eButton		= BUTTON_RETURN			;
	helpGame.eButton		= BUTTON_HELP			;
	startGame.eButton		= BUTTON_START_GAME		;
	setPosition.eButton		= BUTTON_SET_POSITION	;
	surrender.eButton		= BUTTON_SURRENDER		;
	finish.eButton			= BUTTON_FINISH			;
	cleanPosition.eButton	= BUTTON_CLEAN_POSITION	;

	localGame.strButton		= "Local Game"  ;
	netGame.strButton		= "Net Game"    ;
	exitGame.strButton		= "Exit"	    ;
	newGame.strButton		= "New Game"    ;
	setPosition.strButton   = "Set Position";
	returnMenu.strButton	= "Return"		;
	helpGame.strButton		= "Help"        ;
	startGame.strButton     = "Start Game"  ;
	setPosition.strButton	= "Set Position";
	surrender.strButton		= "surrender"   ;
	finish.strButton		= "Finish set"  ;
	cleanPosition.strButton	= "Clean Position";
}
//-----------------------------------------------------------------
void CGameMode:: setCoverButton(int aX, int aY)
{
	if(aX < gBoxButtonsPos_X || aX > gBoxButtonsPos_X + gBoxButtonWidth || aY < gBoxButtonsPos_Y || aY > gBoxButtonsPos_Y + 150)
	{
		flagCoverButton = -1;	
		return;
	}

	for(int i = 0; i < 5; i++)    // 5 - maximal count buttons on the mode
		if(aY >= gBoxButtonsPos_Y + i * gBoxButtonHeight && aY <= gBoxButtonsPos_Y + gBoxButtonHeight + i * gBoxButtonHeight)
		{
			flagCoverButton = i;
			break;
		}
};
//-----------------------------------------------------------------
const sButton &CGameMode::getButton(eButton aButton)const
{
	switch(aButton)
	{
	case BUTTON_LOCAL_GAME:
		return	localGame;
		break;
	case BUTTON_NET_GAME:
		return netGame;	
		break;
	case BUTTON_EXIT_GAME:
		return exitGame;	
		break;
	case BUTTON_NEW_GAME:
		return newGame;		
		break;
	case BUTTON_SET_POSITION:
		return setPosition;	
		break;
	case BUTTON_RETURN:
		return returnMenu;		
		break;
	case BUTTON_HELP:
		return helpGame;		
		break;
	case BUTTON_START_GAME:
		return startGame;		
		break;
	case BUTTON_SURRENDER:
		return surrender;		
		break;
	case BUTTON_FINISH:
		return finish;			
		break;
	case BUTTON_CLEAN_POSITION:
		return cleanPosition;
		break;
	}
};
//-----------------------------------------------------------------
const int  &CGameMode::getFlagCoverButton()const		
{
	return flagCoverButton;
};