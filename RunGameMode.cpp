#include "RunGameMode.h"
#include "King.h"
#include "Rook.h"
#include "AllegroWrap.h"

CRunGameMode::CRunGameMode()
	:catchBlackPiece(-1)
    ,catchWhitePiece(-1)
	,countTurns(1)
{
    _initButtons();
}
CRunGameMode::~CRunGameMode()
{
}

//--------------------private functions---------------------------//
void CRunGameMode::_initButtons()
{
    buttons.push_back(getButton(BUTTON_NEW_GAME));
    buttons.push_back(getButton(BUTTON_SURRENDER));
    buttons.push_back(getButton(BUTTON_RETURN));
};
bool CRunGameMode::_chakOnMatMoveKing(eColor aColor)
{
	CKing* king = nullptr;
	vector<CPiece*> sameColorPieces;
	vector<CPiece*> anotherColorPieces;
	char iDColor = 0;
	if(aColor == WHITE)
	{
		sameColorPieces =  mListsPieces.getVectorWhitePieces();
		anotherColorPieces = mListsPieces.getVectorBlackPieces();
		king = (CKing *)sameColorPieces[0];
		iDColor = 0;
	}
	else
	{
		sameColorPieces =  mListsPieces.getVectorBlackPieces();
		anotherColorPieces = mListsPieces.getVectorWhitePieces();
		king = (CKing *)sameColorPieces[0];
		iDColor = 100;
	}

	int tempX = king->getX();
	int tempY = king->getY();
	for(int i = tempX - 1 ; i <= tempX + 1; i++)
	{
		for(int j = tempY - 1; j <= tempY + 1; j++)
		{
			if(i < 1 || i > 8 || j < 1 || j > 8)
				continue;
			
			if(i == tempX && j == tempY)
				continue;
			
			eMove moveKing = king->move(i * sizeCell, j * sizeCell,  board.getPtrBoard());
			
			if(moveKing == LEGAL || moveKing == SHOOT)
			{
				char tempID = board.getIDPiece(i, j);
				board.setIDPiece(i, j, iDColor);
				king->resetPositionPiece(i * sizeCell, j * sizeCell);
				
				if(king->isChack(anotherColorPieces, board.getPtrBoard()))
				{
					board.setIDPiece(i, j, tempID);
					king->resetPositionPiece(tempX * sizeCell, tempY * sizeCell);
					continue;
				}
				else
				{
					board.setIDPiece(i, j, tempID);
					king->resetPositionPiece(tempX * sizeCell, tempY * sizeCell);
					return false;
				}
				
			}	
		}
	}
return true;
};
bool CRunGameMode::_chekOnMatShootPiece(eColor aColor)
{
	CKing* king = nullptr;
	vector<CPiece*> sameColorPieces;
	vector<CPiece*> anotherColorPieces;
	char iDColor = 0;
	if(aColor == WHITE)
	{
		sameColorPieces =  mListsPieces.getVectorWhitePieces();
		anotherColorPieces = mListsPieces.getVectorBlackPieces();
		king = (CKing *)sameColorPieces[0];
		iDColor = 0;
	}
	else
	{
		sameColorPieces =  mListsPieces.getVectorBlackPieces();
		anotherColorPieces = mListsPieces.getVectorWhitePieces();
		king = (CKing *)sameColorPieces[0];
		iDColor = 100;
	}

	int tempX = king->getX();
	int tempY = king->getY();

	for(int i = 0; i < anotherColorPieces.size(); i++)
	{
		if(!anotherColorPieces[i]->getLive())
			continue;
		
		if(anotherColorPieces[i]->move(tempX * sizeCell, tempY * sizeCell, board.getPtrBoard()) == SHOOT)
		{
			int tempShootPieceX = anotherColorPieces[i]->getX();
			int tempShootPieceY = anotherColorPieces[i]->getY();

			for(int j = 1; j < sameColorPieces.size(); j++)
			{
				if(!sameColorPieces[j]->getLive())
					continue;

				if(sameColorPieces[j]->move(tempShootPieceX * sizeCell, tempShootPieceY * sizeCell, board.getPtrBoard()) == SHOOT)
					return false;
			}
		}
	}
	return true;
};
bool CRunGameMode::_chekONMatHiding(eColor aColor)
{
	CKing* king = nullptr;
	vector<CPiece*> sameColorPieces;
	vector<CPiece*> anotherColorPieces;
		
	if(aColor == WHITE)
	{
		sameColorPieces =  mListsPieces.getVectorWhitePieces();
		anotherColorPieces = mListsPieces.getVectorBlackPieces();
		king = (CKing *)sameColorPieces[0];	
	}
	else
	{
		sameColorPieces =  mListsPieces.getVectorBlackPieces();
		anotherColorPieces = mListsPieces.getVectorWhitePieces();
		king = (CKing *)sameColorPieces[0];
	}

	int tempKindX = king->getX();
	int tempKindY = king->getY();

	int countShootPieces = 0;
	int attackPieceX = 0;
	int attackPieceY = 0;
	ePiece attackPiece;

	for(int i = 0, sizeVector = anotherColorPieces.size(); i < sizeVector; ++i )
	{
		if(!anotherColorPieces[i]->getLive())
			continue;

		if(anotherColorPieces[i]->move(tempKindX * sizeCell, tempKindY * sizeCell, board.getPtrBoard()) == SHOOT)
		{
			countShootPieces++;
			attackPiece = anotherColorPieces[i]->getPiece();
			attackPieceX  = anotherColorPieces[i]->getX();
			attackPieceY	= anotherColorPieces[i]->getY();
		}
	}

	if(countShootPieces > 1)
		return true;

	if(attackPiece == KNIGHT || attackPiece == PAWN)
		return true;

	int count = 0;
	int dx = 0;
	int dy = 0;

	if(attackPieceX == tempKindX)
	{
		if(attackPieceY > tempKindY)
		{
			count = attackPieceY - tempKindY;
			dx = 0;
			dy = 1;
		}
		else
		{
			count = tempKindY - attackPieceY;
			dx = 0;
			dy = -1;
		}
	}
	else if(attackPieceY == tempKindY)
	{
		dy = 0;
		if(attackPieceX > tempKindX)
		{
			count = attackPieceX - tempKindX;
			dx = 1;
		}
		else
		{
			count = tempKindX - attackPieceX;
			dx = - 1;
		}
	}
	else if(attackPieceY - tempKindY == attackPieceX - tempKindX)
	{
		if(attackPieceY > tempKindY)
		{
			dx = 1;
			dy = 1;
			count = attackPieceY - tempKindY - 1;
		}
		else
		{
			dx = - 1;
			dy = - 1;
			count = tempKindY - attackPieceY - 1;
		}
	}
	else if(attackPieceY - tempKindY == -(attackPieceX - tempKindX))
	{
		if(attackPieceY > tempKindY)
		{
			dy = 1;
			dx = -1;
			count = attackPieceY - tempKindY - 1;
		}
		else
		{
			dy = -1;
			dx = 1;
			count = tempKindY - attackPieceY - 1;
		}
	}
	
	int i = 1;
	while(count > 0 )
	{
			
		for(int m = 1, sizeVector = sameColorPieces.size(); m < sizeVector; m++)
		{
			if(!sameColorPieces[m]->getLive())
				continue;
			
			if(sameColorPieces[m]->move((attackPieceX - (i * dx)) * sizeCell , (attackPieceY - (i * dy)) * sizeCell, board.getPtrBoard()) == LEGAL)
				return false;
		}
		count--;
		i++;
	}
	return true;
};
void CRunGameMode::_convertPawn(CPiece* aPawn, eColor aColor, int aPosX, int aPosY, bool aFlagShoot)
{
	board.deleteIDPiece(aPawn->getX(), aPawn->getY());
	aPawn->setFlagLive(false);

	char tempId = board.getIDPiece(aPosX / sizeCell, aPosY / sizeCell);

	if(aColor == WHITE)
	{
		for(int i = 1, sizeVector = mListsPieces.getVectorWhitePieces().size(); i < sizeVector; ++i)
		{
			if(mListsPieces.getVectorWhitePieces()[i]->getPiece() == QUEEN && (!mListsPieces.getVectorWhitePieces()[i]->getLive()))
			{
				mListsPieces.getVectorWhitePieces()[i]->resetPositionPiece(aPosX, aPosY);
				mListsPieces.getVectorWhitePieces()[i]->setFlagLive(true);
			
				board.setIDPiece(aPosX / sizeCell , aPosY / sizeCell, 1);
				
				if(aFlagShoot)
				{
					mListsPieces.getPtrBlackPiece(tempId - 100)->setFlagLive(false);
					noteMove.setNoteStruct(mListsPieces.getPtrWhitePiece(i), SHOOT, countTurns - 1, false);
				}
				else
					noteMove.setNoteStruct(mListsPieces.getPtrWhitePiece(i), LEGAL, countTurns - 1, false);

				return;
			}
		}
	//-------------------------- add second quuen --------------------//	
		mListsPieces.addNewPiece(1,WHITE, aPosX, aPosY);

		int lastPiece = (mListsPieces.getVectorWhitePieces().size() - 1); // ---- lastPiece is last piece in vector of Pieces ----
		board.setIDPiece(aPosX / sizeCell , aPosY / sizeCell, lastPiece);
		
		if(aFlagShoot)
		{
			mListsPieces.getPtrBlackPiece(tempId - 100)->setFlagLive(false);
			noteMove.setNoteStruct(mListsPieces.getPtrWhitePiece(lastPiece), SHOOT, countTurns - 1, false);
		}
		else
			noteMove.setNoteStruct(mListsPieces.getPtrWhitePiece(lastPiece), LEGAL, countTurns - 1, false);
	}
	else
	{
		for(int i = 1, sizeVector = mListsPieces.getVectorBlackPieces().size(); i < sizeVector; ++i)
		{
			if(mListsPieces.getVectorBlackPieces()[i]->getPiece() == QUEEN && (!mListsPieces.getVectorBlackPieces()[i]->getLive()))
			{
				mListsPieces.getVectorBlackPieces()[i]->resetPositionPiece(aPosX, aPosY);
				mListsPieces.getVectorBlackPieces()[i]->setFlagLive(true);
				board.setIDPiece(aPosX / sizeCell , aPosY / sizeCell, idBlackQueen);
				
				if(aFlagShoot)
				{
					mListsPieces.getPtrWhitePiece(tempId)->setFlagLive(false);
					noteMove.setNoteStruct(mListsPieces.getPtrBlackPiece(i), SHOOT, countTurns - 1, false);
				}
				else
					noteMove.setNoteStruct(mListsPieces.getPtrBlackPiece(i), LEGAL, countTurns - 1, false);
				
				return;
			}
		}
	//-------------------------- add second quuen --------------------//	
		mListsPieces.addNewPiece(1,BLACK, aPosX, aPosY);
		int lastPiece = (mListsPieces.getVectorBlackPieces().size() - 1) + 100;
		board.setIDPiece(aPosX / sizeCell , aPosY / sizeCell, lastPiece);
		
		if(aFlagShoot)
		{
			mListsPieces.getPtrWhitePiece(tempId)->setFlagLive(false);
			noteMove.setNoteStruct(mListsPieces.getPtrBlackPiece(lastPiece - 100), SHOOT, countTurns - 1, false);
		}
		else
			noteMove.setNoteStruct(mListsPieces.getPtrBlackPiece(lastPiece - 100), LEGAL, countTurns - 1, false);
	}

};

//------------------public functions----------------------------//
eGameMode CRunGameMode::changeGameMode()
{
    if(getFlagCoverButton() < 0)
        return RUN_MODE;
    
    switch(buttons[getFlagCoverButton()].eButton)
    {
	case BUTTON_NEW_GAME:
		if( CAllegroWrap::instance().questionChangeMode(BUTTON_NEW_GAME) == 1)
		{
			CAllegroWrap::instance().setFlagSetPositionMode(false);
			return INIT_MODE;
		}
		else
			return RUN_MODE;
        break;
    case BUTTON_SURRENDER:
		if( CAllegroWrap::instance().questionChangeMode(BUTTON_SURRENDER) == 1)
			return MENU_MODE;
		return RUN_MODE;
        break;
    case BUTTON_RETURN:
		if( CAllegroWrap::instance().questionChangeMode(BUTTON_RETURN) == 1)
			return MENU_MODE;
        return RUN_MODE;
        break;
	default:
		return RUN_MODE;
		break;
    }
};
void CRunGameMode::initNewGame()
{
    mListsPieces.setNewGame();
    board.clearBoard();
    board.setPieces(mListsPieces.getVectorWhitePieces());
    board.setPieces(mListsPieces.getVectorBlackPieces());
    countTurns = 1;
    noteMove.newNoteStruct();
};
void CRunGameMode::initGameFromSetPosition(CListsPieces &aNewPosition)
{
    mListsPieces = aNewPosition;	// copy list from listPiece of setPosition to listPiece of runGame
    
    board.clearBoard();
    board.setPieces(mListsPieces.getVectorWhitePieces());	// set white pieces on the main board
   
    for(int i = 0; i < mListsPieces.getVectorBlackPieces().size(); i++) // becouse  color is only WHITE after greate pieces
        mListsPieces.getVectorBlackPieces()[i]->setColor(BLACK);

    board.setPieces(mListsPieces.getVectorBlackPieces());	// set black pieces on the main board

    countTurns = 1;
    noteMove.newNoteStruct();
};
bool CRunGameMode::isChackOnMat(eColor aColor)
{
	if(_chakOnMatMoveKing(aColor) && _chekOnMatShootPiece(aColor) && _chekONMatHiding(aColor))
		return true;
	else
		return false;
};
bool CRunGameMode::isCatchPiece(int aPosX, int aPosY)
{
    if(aPosX < 50 || aPosY < 50 || aPosX > 450 || aPosY > 450)  //It isn't  clicking mouse on the main bourd 
        return false;

    int tempX = aPosX / sizeCell;     // to translate position mouse into index on the board
    int tempY = aPosY / sizeCell;

    if(board.getIDPiece(tempX, tempY) == idEmpty)
    {
        catchWhitePiece = -1;
        catchBlackPiece = -1; 
        return false;
    }

    if(board.getIDPiece(tempX, tempY) < idBlackKing && (countTurns % 2 != 0))
    {
        catchWhitePiece = board.getIDPiece(tempX, tempY);
        catchBlackPiece = -1;
		CAllegroWrap::instance().setCursor(mListsPieces.getPtrWhitePiece(catchWhitePiece)->getPiece(), WHITE); 
        return true;
    }
    else if(board.getIDPiece(tempX, tempY) >= idBlackKing && (countTurns % 2 == 0))
    {
        catchBlackPiece = board.getIDPiece(tempX, tempY) - 100;
		CAllegroWrap::instance().setCursor(mListsPieces.getPtrBlackPiece(catchBlackPiece)->getPiece(), BLACK); 
        catchWhitePiece = -1;
        return true;
    }
    else
        return false;
};
void CRunGameMode::changePosWitePiece(int aPosX, int aPosY)
{  
    vector<CPiece*> tempBlack =  mListsPieces.getVectorBlackPieces(); // to check on a check white king
    CPiece* catchPiece = mListsPieces.getPtrWhitePiece(catchWhitePiece);
    eMove tempMove = catchPiece->move(aPosX, aPosY, board.getPtrBoard());
    CKing* tempKing = (CKing*)mListsPieces.getPtrWhitePiece(0);

	// for checking on chack of black king//
	vector<CPiece*> tempWhite = mListsPieces.getVectorWhitePieces();
	CKing* tempBlackKing = (CKing*)tempBlack[0];

    int lastX = catchPiece ->getX();
    int lastY = catchPiece ->getY();	
    
    if( tempMove == LEGAL)
    {	
        board.deleteIDPiece(catchPiece ->getX(), catchPiece ->getY());
        catchPiece ->resetPositionPiece(aPosX, aPosY);
        board.setIDPiece(aPosX / sizeCell, aPosY / sizeCell, catchWhitePiece);
            
        if(tempKing->isChack(tempBlack , board.getPtrBoard())) // return last position becouse its was check white king
        {
            board.setIDPiece(lastX, lastY, catchWhitePiece);
            board.deleteIDPiece(aPosX / sizeCell, aPosY / sizeCell);
            catchPiece ->resetPositionPiece(lastX * sizeCell, lastY * sizeCell);
            return;
        }
        else
            countTurns++;
		
		if(tempBlackKing->isChack(tempWhite, board.getPtrBoard()))
		{
			noteMove.setNoteStruct(catchPiece, LEGAL, countTurns - 1, true);
			
			if(this->isChackOnMat(BLACK))
				CAllegroWrap::instance().setWinner(BLACK);
		}
		else
			noteMove.setNoteStruct(catchPiece, LEGAL, countTurns - 1, false);
     
		catchWhitePiece = -1;
        return;
    }
    else if(tempMove == SHOOT)
    {          
        int tempIDPiece = board.getIDPiece(aPosX / sizeCell, aPosY / sizeCell);
        board.deleteIDPiece(catchPiece->getX(), catchPiece ->getY());
        catchPiece->resetPositionPiece(aPosX, aPosY);
        tempBlack[tempIDPiece - 100]->setFlagLive(false);
        board.setIDPiece(aPosX / sizeCell, aPosY / sizeCell, catchWhitePiece);
                
        if(tempKing->isChack(tempBlack , board.getPtrBoard()))
        {
            board.setIDPiece(aPosX / sizeCell, aPosY / sizeCell, tempIDPiece);
            tempBlack[tempIDPiece - 100]->setFlagLive(true);
            catchPiece->resetPositionPiece(lastX * sizeCell, lastY * sizeCell);
            board.setIDPiece(lastX , lastY,catchWhitePiece );
            return;
        }
        else
            countTurns++;
       
		if(tempBlackKing->isChack(tempWhite, board.getPtrBoard()))
		{
			noteMove.setNoteStruct(catchPiece, SHOOT, countTurns - 1, true);
			
			if(this->isChackOnMat(BLACK))
				CAllegroWrap::instance().setWinner(BLACK);
		}
		else
			noteMove.setNoteStruct(catchPiece, SHOOT, countTurns - 1, false);
        
		catchWhitePiece = -1;
        return;
    }
    else if(tempMove == CASTLING)
    {
        changePosCasling(WHITE,aPosX,aPosY);
        catchWhitePiece = -1;
    }
	else if(tempMove == SHOOT_CONVERT_PAWN)
	{
		_convertPawn(catchPiece, WHITE, aPosX, aPosY, true);
		countTurns++;
	}
	else if(tempMove == CONVERT_PAWN)
	{
		_convertPawn(catchPiece, WHITE, aPosX, aPosY, false);	
        countTurns++;
	}
    else
        catchWhitePiece = -1;
};
void CRunGameMode::changePosBlackPiece(int aPosX, int aPosY)
{
    vector<CPiece*> tempWhite =  mListsPieces.getVectorWhitePieces(); // to check on a check black king
    CPiece* catchPiece = mListsPieces.getPtrBlackPiece(catchBlackPiece);
    eMove tempMove = catchPiece->move(aPosX, aPosY, board.getPtrBoard());    
    CKing* tempKing = (CKing*)mListsPieces.getPtrBlackPiece(0);

    int lastX = catchPiece ->getX();
    int lastY = catchPiece ->getY();

	//----------------for checking on chack of white king--------------//
	vector<CPiece*> tempBlack = mListsPieces.getVectorBlackPieces();
	CKing* tempWhiteKing = (CKing*)tempWhite[0];

    if(tempMove == LEGAL)
    {
        board.deleteIDPiece(catchPiece->getX(), catchPiece->getY());
        catchPiece->resetPositionPiece(aPosX, aPosY);
        board.setIDPiece(aPosX / sizeCell, aPosY / sizeCell, catchBlackPiece + 100); // if for black pieces starts from 100;
            
        if(tempKing->isChack(tempWhite , board.getPtrBoard()))
        {
            board.setIDPiece(lastX, lastY, catchBlackPiece + 100);
            board.deleteIDPiece(aPosX / sizeCell, aPosY / sizeCell);
            catchPiece ->resetPositionPiece(lastX * sizeCell, lastY * sizeCell);
            return;
        }
        else
            countTurns++;
        
		if(tempWhiteKing->isChack(tempBlack, board.getPtrBoard()))
		{
			noteMove.setNoteStruct(catchPiece, LEGAL, countTurns - 1, true);
			if(this->isChackOnMat(WHITE))
				CAllegroWrap::instance().setWinner(WHITE);
		}
		else
			noteMove.setNoteStruct(catchPiece, LEGAL, countTurns - 1, false);
        catchBlackPiece = -1;		
    }
    else if (tempMove == SHOOT)
    {
        int tempIDPiece = board.getIDPiece(aPosX / sizeCell, aPosY / sizeCell);
        board.deleteIDPiece( catchPiece->getX(),  catchPiece->getY());

        catchPiece->resetPositionPiece(aPosX, aPosY);
        tempWhite[tempIDPiece]->setFlagLive(false);
        board.setIDPiece(aPosX / sizeCell, aPosY / sizeCell, catchBlackPiece + 100);
          
        if(tempKing->isChack(tempWhite, board.getPtrBoard()))
        {
            board.setIDPiece(aPosX / sizeCell, aPosY / sizeCell, tempIDPiece);
            tempWhite[tempIDPiece]->setFlagLive(true);
            catchPiece->resetPositionPiece(lastX * sizeCell, lastY * sizeCell);
            board.setIDPiece(lastX , lastY, catchBlackPiece + 100);
            return;
        }
        else
            countTurns++;

		if(tempWhiteKing->isChack(tempBlack, board.getPtrBoard()))
		{
			noteMove.setNoteStruct(catchPiece, SHOOT, countTurns - 1, true);
			
			if(this->isChackOnMat(WHITE))
				CAllegroWrap::instance().setWinner(WHITE);
		}
		else
			noteMove.setNoteStruct(catchPiece, SHOOT, countTurns - 1, false);     
		catchBlackPiece = -1;
    }
    else if(tempMove == CASTLING)
    {
        changePosCasling(BLACK,aPosX,aPosY);
        catchBlackPiece = -1;
    }
	else if(tempMove == SHOOT_CONVERT_PAWN)
	{
		_convertPawn(catchPiece,BLACK, aPosX, aPosY, true);
		countTurns++;
	}
	else if(tempMove == CONVERT_PAWN)
	{
		_convertPawn(catchPiece,BLACK, aPosX, aPosY, false);
		countTurns++;
	}
    else 
        catchBlackPiece = -1;
};
void CRunGameMode::changePosPiece(int aPosX, int aPosY)
{     
    if(!(aPosX >= 50 && aPosX <= 450 && aPosY >= 50 && aPosY <= 450))    // set Position only on board //
        return;
    
    if(catchWhitePiece >= 0)	
        this->changePosWitePiece(aPosX, aPosY);
    else if(catchBlackPiece >= 0)	
        this->changePosBlackPiece(aPosX, aPosY);	
}
void CRunGameMode:: changePosCasling(eColor aColor, int aPosX, int aPosY)
{
    vector<CPiece*> tempPieceOtherColor;
    CKing* tempKing       = nullptr;
    CRook* tempRightRook  = nullptr;
    CRook* tempLeftRook   = nullptr;
    int idColor			  = 0;
    int tempY             = 0;

    if(aColor == WHITE)
    {
        tempPieceOtherColor =  mListsPieces.getVectorBlackPieces(); // to check on a check white king
        tempKing = (CKing*)mListsPieces.getPtrWhitePiece(0);
        tempRightRook = (CRook*)mListsPieces.getPtrWhitePiece(3);
        tempLeftRook = (CRook*)mListsPieces.getPtrWhitePiece(2);
        tempY = 8;
        idColor = idWhiteKing;
    }
    else
    {
        tempPieceOtherColor =  mListsPieces.getVectorWhitePieces(); // to check on a check white king
        tempKing = (CKing*)mListsPieces.getPtrBlackPiece(0);
        tempRightRook = (CRook*)mListsPieces.getPtrBlackPiece(3);
        tempLeftRook = (CRook*)mListsPieces.getPtrBlackPiece(2);
        tempY = 1;
        idColor = idBlackKing;
    }
    
    if(!tempKing->isChack(tempPieceOtherColor  , board.getPtrBoard()))
    {
        if(aPosX / sizeCell == 7 && board.getIDPiece(6, tempY) == idEmpty && board.getIDPiece(7, tempY) == idEmpty && board.getIDPiece(8, tempY) == 3 + idColor)
        {		
            
            if(!tempRightRook->getFlagMove())
            {	
                board.deleteIDPiece(5, tempY);
                board.setIDPiece(6,tempY, 0 + idColor);
                tempKing->resetPositionPiece(6 * sizeCell, tempY * sizeCell);
                    
                if(tempKing->isChack(tempPieceOtherColor , board.getPtrBoard()))
                {
                    tempKing->resetPositionPiece(5* sizeCell, tempY * sizeCell);
                    board.deleteIDPiece(6,tempY);
                    board.setIDPiece(5,tempY, 0 + idColor);
                    return;
                }
                else
                {
                    board.deleteIDPiece(6, tempY);
                    board.setIDPiece(7, tempY, 0 + idColor);
                    tempKing->resetPositionPiece(7 * sizeCell, tempY * sizeCell);
                        
                    if(tempKing->isChack(tempPieceOtherColor , board.getPtrBoard()))
                    {
                        tempKing->resetPositionPiece(5* sizeCell, tempY * sizeCell);
                        board.deleteIDPiece(7, tempY);
                        board.setIDPiece(5, tempY, 0 + idColor);
                        return;
                    }
                }
                    
                tempRightRook->resetPositionPiece(6 * sizeCell, tempY * sizeCell);
                board.deleteIDPiece(8, tempY);
                board.setIDPiece(6, tempY, 3 + idColor);
                
                noteMove.setNoteStruct(tempKing, CASTLING, countTurns - 1, false);					
                countTurns++;
                return;
            }
            else
                return;
        }
        else if(aPosX / sizeCell == 3 && board.getIDPiece(3, tempY) == idEmpty && board.getIDPiece(4, tempY) == idEmpty && board.getIDPiece(1, tempY) == 2 + idColor)
        {
            if(!tempLeftRook->getFlagMove())
            {	
                board.deleteIDPiece(5, tempY);
                board.setIDPiece(4,tempY, 0 + idColor);
                tempKing->resetPositionPiece(4 * sizeCell, tempY * sizeCell);
                    
                if(tempKing->isChack(tempPieceOtherColor , board.getPtrBoard()))
                {
                    tempKing->resetPositionPiece(5* sizeCell, tempY * sizeCell);
                    board.deleteIDPiece(4,tempY);
                    board.setIDPiece(5,tempY, 0 + idColor);
                    return;
                }
                else
                {
                    board.deleteIDPiece(4, tempY);
                    board.setIDPiece(3, tempY, 0 + idColor);
                    tempKing->resetPositionPiece(3 * sizeCell, tempY * sizeCell);
                        
                    if(tempKing->isChack(tempPieceOtherColor , board.getPtrBoard()))
                    {
                        tempKing->resetPositionPiece(5* sizeCell, tempY * sizeCell);
                        board.deleteIDPiece(3, tempY);
                        board.setIDPiece(5, tempY, 0 + idColor);
                        return;
                    }
                }
                    
                tempLeftRook->resetPositionPiece(4 * sizeCell, tempY * sizeCell);
                board.deleteIDPiece(1, tempY);
                board.setIDPiece(4, tempY, 2 + idColor);
                    
                noteMove.setNoteStruct(tempKing, CASTLING, countTurns - 1, false);						
                countTurns++;          
                return;
            }
            else
                return;
        }
    }
    else
        return;
}
//-----------------get and set------------------------------------//
CListsPieces CRunGameMode::getListPieces()
{
	return mListsPieces;
}
//-----------------draw functions--------------------------------//
void CRunGameMode:: drawButtons()
{	
    CAllegroWrap::instance().drawButtonsAllegro(buttons, getFlagCoverButton());
};
void CRunGameMode:: draw()
{	
    drawButtons();
    board.draw();	
    mListsPieces.draw();	
    noteMove.draw();
};


