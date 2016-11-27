#include "MenuMode.h"
#include "AllegroWrap.h"

CMenuMode::CMenuMode()
{
	_initButtons();
}
//-----------------------------------------------------------------
CMenuMode::~CMenuMode()
{
}
//-----------------------------------------------------------------
void CMenuMode:: _initButtons()
{
	buttons.push_back(getButton(BUTTON_LOCAL_GAME));
	buttons.push_back(getButton(BUTTON_NET_GAME));
//	buttons.push_back(getButton(BUTTON_HELP));
	buttons.push_back(getButton(BUTTON_EXIT_GAME));
};
//-----------------------------------------------------------------
eGameMode CMenuMode::changeGameMode()
{
	if(getFlagCoverButton() < 0)
		return MENU_MODE;
	
	switch(buttons[getFlagCoverButton()].eButton)
	{
		case BUTTON_LOCAL_GAME:	
			return LOCAL_MODE;
			break;
		case BUTTON_NET_GAME:
			return NET_MODE;
			break;
		case BUTTON_HELP:
			return HELP_MODE;
			break;
		case BUTTON_EXIT_GAME:
			return EXIT_MODE;
			break;
		default:
			return MENU_MODE;
			break;
	}
};
//-----------------------------------------------------------------
void CMenuMode:: drawButtons()
{
	CAllegroWrap::instance().drawButtonsAllegro(buttons, getFlagCoverButton());
}
//-----------------------------------------------------------------
void CMenuMode:: draw()
{
	this->drawButtons();
}


