#include "LocalGame.h"
#include "AllegroWrap.h"

CLocalGame::CLocalGame()
{
	_initButtons();
}
//-----------------------------------------------------------------
CLocalGame::~CLocalGame()
{
}
//-----------------------------------------------------------------
void CLocalGame:: _initButtons()
{
	buttons.push_back(getButton(BUTTON_NEW_GAME));
	buttons.push_back(getButton(BUTTON_SET_POSITION));
	buttons.push_back(getButton(BUTTON_RETURN));
};
//-----------------------------------------------------------------
eGameMode CLocalGame::changeGameMode()
{
	if(getFlagCoverButton() < 0)
		return LOCAL_MODE;
	
	switch(buttons[getFlagCoverButton()].eButton)
	{
	case BUTTON_NEW_GAME:   // after init_board for new game it forvards to RUN_GAME
		return INIT_MODE;	
		break;
	case BUTTON_SET_POSITION:
		return SET_POSITION_MODE;
		break;
	case BUTTON_RETURN:
		return MENU_MODE;
		break;
	default:
		return LOCAL_MODE;
		break;
	}
};
//-----------------------------------------------------------------
void CLocalGame:: drawButtons()
{
	static CAllegroWrap & inst = CAllegroWrap::instance();
	inst.drawButtonsAllegro(buttons, getFlagCoverButton());
};
//-----------------------------------------------------------------
void CLocalGame:: draw()
{
	this->drawButtons();
};
