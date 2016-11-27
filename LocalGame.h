/*
This class is a child of CGameMode class.
It describes only  buttons for this object.
The buttons are initialized in void _initButtons().
*/

#pragma once
#include "gamemode.h"

class CLocalGame : public CGameMode
{
	vector<sButton> buttons;

//------------------prototype function ---------
public:
	CLocalGame();
	~CLocalGame();

	eGameMode changeGameMode();
	
	void drawButtons();
	void draw();
private:
	void _initButtons();
};

