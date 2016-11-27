/*
This class is base class for CLocalGameMode, CSetPositionMode, CMenuMode, CRunGameMode.
It describes and initializes all buttons for all classes.
int flagCoverButton - shaws which button is covered by a mouse. -1 - the buttons aren't covered by mouse 
*/
#pragma once
#include "source.h"

class CGameMode
{
	sButton localGame;
	sButton netGame;
	sButton exitGame;
	sButton newGame;
	sButton setPosition;
	sButton returnMenu;
	sButton helpGame;
	sButton startGame;
	sButton surrender;
	sButton finish;
	sButton cleanPosition;

	int flagCoverButton;    // It is an index in the vector of buttons. It shows which button is covered a cursor of the mouse

private:
	void _initButtons();

public:
	CGameMode();
	~CGameMode();
//--------------------set and get--------------------------//
	const sButton &getButton(eButton aButton)const;
	const int &getFlagCoverButton()const;
	void setCoverButton(int aX, int aY);
};

