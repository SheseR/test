#include "SetPositionMode.h"
#include "AllegroWrap.h"
#include "Piece.h"

CSetPositionMode::CSetPositionMode()
	:catchWhitePiece(-1)
	,catchBlackPiece(-1)
{
    _initButtons();
    _initPieces();
}
CSetPositionMode::~CSetPositionMode()
{
}

//-----------------private function---------------------------------------//
void CSetPositionMode:: _initButtons()
{
    buttons.push_back(getButton(BUTTON_FINISH));
    buttons.push_back(getButton(BUTTON_CLEAN_POSITION));
    buttons.push_back(getButton(BUTTON_RETURN));
}
void CSetPositionMode::_initPieces()
{
    additionalListsPieces.setAditionalPosition();
}

//----------------public functions----------------------------------------//
eGameMode CSetPositionMode:: changeGameMode()
{
    if(getFlagCoverButton() < 0)
        return SET_POSITION_MODE;
    
    switch(buttons[getFlagCoverButton()].eButton)
    {
        case BUTTON_FINISH:
            CAllegroWrap::instance().setFlagSetPositionMode(true);
            return INIT_MODE;
            break;
        case BUTTON_RETURN:
			if( CAllegroWrap::instance().questionChangeMode(BUTTON_RETURN) == 1)
			{
				return MENU_MODE;
			} 
            return SET_POSITION_MODE;
        case BUTTON_CLEAN_POSITION:
			if( CAllegroWrap::instance().questionChangeMode(BUTTON_CLEAN_POSITION) == 1)
			{
				newPositionListPieces.cleanLists();
			}   
            return SET_POSITION_MODE;
            break;
		default:
			return SET_POSITION_MODE;
			break;
    }
};
//---------------------for moving pieces on the display-------------------//
bool CSetPositionMode::isCatchPiece(int aPosX, int aPosY)
{
    int tempX = aPosX / sizeCell;
    int tempY = aPosY / sizeCell;

    if(tempX < 10 || tempX > 15 || tempY < 1 || tempY > 2)
    {
        catchWhitePiece = -1;
        catchBlackPiece = -1;
        return false;
    }

    switch(tempX)
    {
    case 10:
        if(tempY == 1)
            catchWhitePiece = 0;
        else
            catchBlackPiece = 0;
        break;
    case 11:
        if(tempY == 1)
            catchWhitePiece = 1;
        else
            catchBlackPiece = 1;
        break;
    case 12:
        if(tempY == 1)
            catchWhitePiece = 2;
        else
            catchBlackPiece = 2;
        break;		
    case 13:
        if(tempY == 1)
            catchWhitePiece = 4;
        else
            catchBlackPiece = 4;
        break;
    case 14:
        if(tempY == 1)
            catchWhitePiece = 6;
        else
            catchBlackPiece = 6;
        break;
    case 15:
        if(tempY == 1)
            catchWhitePiece = 8;
        else
            catchBlackPiece = 8;
        break;
    case 16:
        if(tempY == 1)
            catchWhitePiece = 9;
        else
            catchBlackPiece = 9;
        break;
    }


	if(tempY == 1)
		CAllegroWrap::instance().setCursor(newPositionListPieces.getPtrWhitePiece(catchWhitePiece)->getPiece(), WHITE);
	else
		CAllegroWrap::instance().setCursor(newPositionListPieces.getPtrBlackPiece(catchBlackPiece)->getPiece(), BLACK);
    
	return true;
}
void CSetPositionMode::setPieceNewPosition(int aPosX, int aPosY)
{
    if(catchWhitePiece > -1)
    {
        vector <CPiece*> white = newPositionListPieces.getVectorWhitePieces();
	
        if(catchWhitePiece == 0 && white[catchWhitePiece]->getLive())
        {
            catchWhitePiece = -1;
            return;
        }

        if(catchWhitePiece == 1 && white[catchWhitePiece]->getLive())
        {
            newPositionListPieces.addNewPiece(catchWhitePiece, WHITE,  aPosX, aPosY);
        }
        else if(catchWhitePiece > 1 && catchWhitePiece < 8 && white[catchWhitePiece]->getLive())
        {
            if(!white[catchWhitePiece + 1]->getLive())
            {
                white[catchWhitePiece + 1]->setFlagLive(true);
                white[catchWhitePiece + 1]->resetPositionPiece(aPosX, aPosY);
            }
            else
            {
                newPositionListPieces.addNewPiece(catchWhitePiece, WHITE,  aPosX, aPosY);
            }
        }
        else if(catchWhitePiece == 8 && white[catchWhitePiece]->getLive())
        {
            int i = 9;
            while(white[i]->getLive())
            {
                i++;
                if(i > white.size() - 1)
                {
                    newPositionListPieces.addNewPiece(catchWhitePiece, WHITE,  aPosX, aPosY);
                    return;
                }		
            }

            white[i]->setFlagLive(true);
            white[i]->resetPositionPiece(aPosX, aPosY);
        }
        else
        {
            white[catchWhitePiece]->setFlagLive(true);
            white[catchWhitePiece]->resetPositionPiece(aPosX, aPosY);
            catchWhitePiece = - 1;
        }
    }

   if(catchBlackPiece > -1)
    {
        vector <CPiece*> black = newPositionListPieces.getVectorBlackPieces();;
        if(catchBlackPiece == 0 && black[catchBlackPiece]->getLive())
		{
            catchBlackPiece = -1;
            return;
        }

        if(catchBlackPiece == 1 &&  black[catchBlackPiece]->getLive())
        {
            newPositionListPieces.addNewPiece(catchBlackPiece, BLACK,  aPosX, aPosY);
        }
        else if(catchBlackPiece > 1 && catchBlackPiece < 8 && black[catchBlackPiece]->getLive())
        {
            if(!black[catchBlackPiece + 1]->getLive())
            {
                black[catchBlackPiece + 1]->setFlagLive(true);
				black[catchBlackPiece +1]->setColor(BLACK);
                black[catchBlackPiece + 1]->resetPositionPiece(aPosX, aPosY);
            }
            else
            {
                newPositionListPieces.addNewPiece(catchBlackPiece, BLACK,  aPosX, aPosY);
            }
        }
        else if(catchBlackPiece == 8 && black[catchBlackPiece]->getLive())
        {
            int i = 9;
            while(black[i]->getLive())
            {
                i++;
                if(i > black.size()) 
                {
                    newPositionListPieces.addNewPiece(catchWhitePiece, BLACK,  aPosX, aPosY);;
                    return;
                }
            }
            
            black[i]->setFlagLive(true);
			black[i]->setColor(BLACK);
            black[i]->resetPositionPiece(aPosX, aPosY);
        }
        else
        {
            black[catchBlackPiece]->setFlagLive(true);
			black[catchBlackPiece]->setColor(BLACK);
            black[catchBlackPiece]->resetPositionPiece(aPosX, aPosY);
            catchBlackPiece = - 1;
        }
    }

    catchWhitePiece = -1;
    catchBlackPiece = -1;
};
bool CSetPositionMode::checkPositionPiece(int aPosX, int aPosY)
{
	int x = aPosX / sizeCell;
	int y = aPosY / sizeCell;

	if(x < 1 || x > 9)
		return false;

	if(y < 1 || y > 9)
		return false;
	
	vector<CPiece*> white = newPositionListPieces.getVectorWhitePieces();
	
	for(int i = 0, size = white.size(); i < size; i++)
	{
		if(white[i]->getLive())
		{
			if(white[i]->getX() == x && white[i]->getY() == y)
				return false;
		}
	}
	
	vector<CPiece*> black = newPositionListPieces.getVectorBlackPieces();
	for(int i = 0, size = black.size(); i < size; i++)
	{
		if(black[i]->getLive())
		{
			if(black[i]->getX() == x && black[i]->getY() == y)
				return false;
		}
	}
	return true;
};
void CSetPositionMode::resetCatchPiece()
{
	catchWhitePiece = -1;
	catchBlackPiece = -1;
};
CListsPieces CSetPositionMode:: getNewPosition()
{
	return newPositionListPieces;
}
//--------------------for drawing-----------------------------------------//
void CSetPositionMode:: drawButtons()
{	
    CAllegroWrap::instance().drawButtonsAllegro(buttons, getFlagCoverButton());
};
void CSetPositionMode:: draw()
{
    drawButtons();
    board.draw();
	CAllegroWrap::instance().drawRectangle(500, 50, 300, 100);
    additionalListsPieces.draw();
    newPositionListPieces.draw();
}
