/*
This class is a child of CGameMode class.
It discribe only buttons for this object.
eGameMode changeGameMode() for navigation between game modes.
*/
#pragma once
#include "gamemode.h"

class CMenuMode : public CGameMode
{
	std::vector<sButton> buttons;
//-------------prototype functions----------------//
public:
	CMenuMode();
	~CMenuMode();

	eGameMode changeGameMode();

	void drawButtons();
	void draw();

private:
	void _initButtons();
};

