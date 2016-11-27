#include "ListsPieces.h"
#include "Pawn.h"
#include "King.h"
#include "Knight.h"
#include "Rook.h"
#include "Bishop.h"
#include "Queen.h"
#include "AllegroWrap.h"

CListsPieces::CListsPieces()
{
    _init();
}
CListsPieces::~CListsPieces()
{
}
//-------------------private functions-------------------------//
void CListsPieces:: _init()
{
    whitePieces.push_back(new CKing());
    blackPieces.push_back(new CKing());
    
    whitePieces.push_back(new CQueen());
    blackPieces.push_back(new CQueen());
    
    whitePieces.push_back(new CRook());
    blackPieces.push_back(new CRook());
    whitePieces.push_back(new CRook());
    blackPieces.push_back(new CRook());

    whitePieces.push_back(new CKnight());
    blackPieces.push_back(new CKnight());
    whitePieces.push_back(new CKnight());
    blackPieces.push_back(new CKnight());

    whitePieces.push_back(new CBishop());
    blackPieces.push_back(new CBishop());
    whitePieces.push_back(new CBishop());
    blackPieces.push_back(new CBishop());

    for(int i = 0;  i < 8; i++)
    {
        whitePieces.push_back(new CPawn());
        blackPieces.push_back(new CPawn());
    }
}

//-------------------public functions-------------------------//
void CListsPieces::addNewPiece(int aPiece, eColor aColor, int aPosX, int aPosY)
{
    switch(aPiece)
    {
    case 1:
        if(aColor == WHITE)
            whitePieces.push_back(new CQueen());
        else
            blackPieces.push_back(new CQueen());
        break;
    case 2:
        if(aColor == WHITE)
            whitePieces.push_back(new CRook());
        else
            blackPieces.push_back(new CRook());
        break;
    case 6:
        if(aColor == WHITE)
            whitePieces.push_back(new CBishop());
        else
            blackPieces.push_back(new CBishop());
        break;
    case 4:
        if(aColor == WHITE)
            whitePieces.push_back(new CKnight());
        else
            blackPieces.push_back(new CKnight());
        break;
    case 8:
        if(aColor == WHITE)
            whitePieces.push_back(new CPawn());
        else
            blackPieces.push_back(new CPawn());
        break;
    }

    if(aColor == WHITE)
    {
        int size = whitePieces.size();
        whitePieces[size - 1]->setPiece(aPosX / sizeCell, aPosY / sizeCell, WHITE);
        whitePieces[size - 1]->setFlagLive(true);
    }
    else
    {
        int size = blackPieces.size();
        blackPieces[size - 1]->setPiece(aPosX / sizeCell, aPosY / sizeCell, BLACK);
        blackPieces[size - 1]->setFlagLive(true);
    }
};
void CListsPieces::cleanLists()
{
    for(int i = 0; i < 16; i++)
    {
        whitePieces[i]->setFlagLive(false);
        blackPieces[i]->setFlagLive(false);
    }
};
//------------------set and get functions-----------------------//
void CListsPieces::setNewGame()
{
    // ---------------set KING-------------------- //	
    whitePieces[0]->setPiece(5, 8, WHITE);
    blackPieces[0]->setPiece(5, 1, BLACK);
    
    // ---------------set QUEEN-------------------- //
    whitePieces[1]->setPiece(4, 8, WHITE);
    blackPieces[1]->setPiece(4, 1, BLACK);
    
    // ---------------set ROOK-------------------- //
    whitePieces[2]->setPiece(1, 8, WHITE);
    blackPieces[2]->setPiece(1, 1, BLACK);
    whitePieces[3]->setPiece(8, 8, WHITE);
    blackPieces[3]->setPiece(8, 1, BLACK);

    // ---------------set KNINGH-------------------- //	
    whitePieces[4]->setPiece(2, 8, WHITE);
    blackPieces[4]->setPiece(2, 1, BLACK);
    whitePieces[5]->setPiece(7, 8, WHITE);
    blackPieces[5]->setPiece(7, 1, BLACK);
    
    // ---------------set BISHOP-------------------- //	
    whitePieces[6]->setPiece(3, 8, WHITE);
    blackPieces[6]->setPiece(3, 1, BLACK);
    whitePieces[7]->setPiece(6, 8, WHITE);
    blackPieces[7]->setPiece(6, 1, BLACK);

// --------------------set FLAG-------------------- //	
// --------------------set PAWN-------------------- //			
    for(int i = 0;  i < 16; i++)
    {
        if(i >= 8)
        {
            whitePieces[i]->setPiece(i - 7, 7, WHITE);
            blackPieces[i]->setPiece(i - 7, 2, BLACK);
        }
        whitePieces[i]->setFlagLive(true);
        blackPieces[i]->setFlagLive(true);
    }

	if(whitePieces.size() > 16)
	{
		cout<<"init white"<< endl;
		for(int i = 16; i < whitePieces.size(); i++)
		{
			whitePieces[i]->setFlagLive(false);
		}
	}
	
	if(blackPieces.size() > 16)
		for(int i = 16; i < blackPieces.size(); i++)
		{
			 blackPieces[i]->setFlagLive(false);
		}

};
void CListsPieces::setAditionalPosition()
{
    // ---------------set KING-------------------- //	
    whitePieces[0]->setPiece(10, 1, WHITE);
    blackPieces[0]->setPiece(10, 2, BLACK);  
    whitePieces[0]->setFlagLive(true);
    blackPieces[0]->setFlagLive(true);
   
	// ---------------set QUEEN-------------------- //
    whitePieces[1]->setPiece(11, 1, WHITE);
    blackPieces[1]->setPiece(11, 2, BLACK);
    whitePieces[1]->setFlagLive(true);
    blackPieces[1]->setFlagLive(true);
    
	// ---------------set ROOK-------------------- //
    whitePieces[2]->setPiece(12, 1, WHITE);
    blackPieces[2]->setPiece(12, 2, BLACK);
    whitePieces[2]->setFlagLive(true);
    blackPieces[2]->setFlagLive(true);
   
	// ---------------set KNINGH-------------------- //	
    whitePieces[4]->setPiece(13, 1, WHITE);
    blackPieces[4]->setPiece(13, 2, BLACK);
    whitePieces[4]->setFlagLive(true);
    blackPieces[4]->setFlagLive(true);
   
	// ---------------set BISHOP-------------------- //	
    whitePieces[6]->setPiece(14, 1, WHITE);
    blackPieces[6]->setPiece(14, 2, BLACK);
    whitePieces[6]->setFlagLive(true);
    blackPieces[6]->setFlagLive(true);

    // --------------------set PAWN-------------------- //			
    whitePieces[8]->setPiece(15, 1, WHITE);
    blackPieces[8]->setPiece(15, 2, BLACK);
    whitePieces[8]->setFlagLive(true);
    blackPieces[8]->setFlagLive(true);
};
vector<CPiece *> CListsPieces::getVectorWhitePieces()
{ 
    return whitePieces; 
}
vector<CPiece *> CListsPieces::getVectorBlackPieces() 
{ 
    return blackPieces; 
};
CPiece* CListsPieces::getPtrWhitePiece(const int &aIDPiece)
{ 
    return whitePieces[aIDPiece]; 
}
CPiece* CListsPieces::getPtrBlackPiece(const int &aIDPiece) 
{ 
    return blackPieces[aIDPiece]; 
}
const char &CListsPieces::getFlagLive(eColor aColor, const int &aID)const
{
    if(aColor == WHITE)
        return whitePieces[aID]->getLive();
    if(aColor == BLACK)
        return blackPieces[aID]->getLive();

    static char res;
    return res;
}
const ePiece &CListsPieces::getPiece(eColor aColor, const int &aID)const
{
    if (aColor == WHITE)
        return whitePieces[aID]->getPiece();

    if (aColor == BLACK)
        return blackPieces[aID]->getPiece();

    static ePiece res;
    return res;
}
//---------------------draw functions---------------------------------//
void CListsPieces::draw()
{
    static CAllegroWrap &drawer = CAllegroWrap::instance();

    for(int i = 0, sizeVector = whitePieces.size(); i < sizeVector; i++)
        drawer.drawPiece(*whitePieces[i]);

    for(int i = 0, sizeVector = blackPieces.size(); i < sizeVector; i++)
        drawer.drawPiece(*blackPieces[i]);
}