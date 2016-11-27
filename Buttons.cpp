#include "Buttons.h"


CButtons::CButtons(void)
{
	_init();
}


CButtons::~CButtons(void)
{
}

void CButtons:: _init(void)
{
	localGame.eButton = BUTTON_LOCAL_GAME;
	netGame.eButton   =	BUTTON_NET_GAME;
	exitGame.eButton  =	BUTTON_EXIT_GAME;

	localGame.strButton = "Local Game";
	netGame.strButton	= "Net Game";
	exitGame.strButton	= "Exit";

};