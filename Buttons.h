#pragma once
#include "source.h"

class CButtons
{
	
	
public:	
	enum eButton
	{
		 BUTTON_LOCAL_GAME
		,BUTTON_NET_GAME
		,BUTTON_EXIT_GAME
	};

	struct sButton 
	{
		eButton eButton;
		std::string  strButton;
	};

private:
	sButton localGame;
	sButton netGame;
	sButton exitGame;



public:
	CButtons(void);
	void _init(void);
	~CButtons(void);

	inline sButton* getButtonLocalGame(void) { return &localGame;};

	friend class CGameMode;
};

