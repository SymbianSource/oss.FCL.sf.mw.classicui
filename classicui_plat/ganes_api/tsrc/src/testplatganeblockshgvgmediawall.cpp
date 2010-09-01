/*
* Copyright (c) 2002 - 2007 Nokia Corporation and/or its subsidiary(-ies).
* All rights reserved.
* This component and the accompanying materials are made available
* under the terms of "Eclipse Public License v1.0"
* which accompanies this distribution, and is available
* at the URL "http://www.eclipse.org/legal/epl-v10.html".
*
* Initial Contributors:
* Nokia Corporation - initial contribution.
*
* Contributors:
*
* Description:  ganes_api
*
*/

// [INCLUDE FILES]
#include "testplatgane.h"



_LIT(Kctestplatgane, "CTestPlatGane");
const CHgVgMediaWall::THgVgOpeningAnimationType KDefaultSelectionAnimation(
        CHgVgMediaWall::EHgVgOpeningAnimationFlipToFront);
const CHgVgMediaWall::THgVgMediaWallStyle KDefaultStyle(
        CHgVgMediaWall::EHgVgMediaWallStyleCoverflowFullScreen);
const TBool KDefaultScrollBarState(ETrue);
const TInt KDefaultAmountOfItems(0);
const TInt KScrollBufferSize(80);

#define START_TEST(TEST_NAME, FUNCTION_NAME) \
    TInt left = 0; \
    TInt wrigth = KTest; \
    TRect rect(TPoint( left, left), TPoint( wrigth, wrigth) ); \
    CHgVgMediaWall* temp = CHgVgMediaWall::NewL ( rect, KDefaultAmountOfItems, KDefaultStyle, \
            KDefaultScrollBarState, NULL, NULL ); \
    CleanupStack::PushL( temp );
    
#define END_TEST \
    CleanupStack::PopAndDestroy( temp ); \
    return KErrNone;
    
// ============================ MEMBER FUNCTIONS =========================

// --------------------------------------------------------------------------
// CTestPlatGane::TestCHgVgGridNewL
// --------------------------------------------------------------------------
//
TInt CTestPlatGane::TestCHgVgMediaWallNewL ( CStifItemParser&  )
    {
    START_TEST(newl, TestCHgVgMediaWallNewL)
    END_TEST
    }

// --------------------------------------------------------------------------
// CTestPlatGane::TestCHgVgMediaWallInitScreenL
// --------------------------------------------------------------------------
//
TInt CTestPlatGane::TestCHgVgMediaWallInitScreenL ( CStifItemParser&  )
    {
    START_TEST(initscreenl, TestCHgVgMediaWallInitScreenL)
    temp->InitScreenL( rect );
    END_TEST
    }


// --------------------------------------------------------------------------
// CTestPlatGane::TestCHgVgMediaWallRefreshScreen
// --------------------------------------------------------------------------
//
TInt CTestPlatGane::TestCHgVgMediaWallRefreshScreen ( CStifItemParser&  )
    {
    START_TEST(refreshscreen, TestCHgVgMediaWallRefreshScreen)
    temp->RefreshScreen(0);
    END_TEST
    }

// --------------------------------------------------------------------------
// CTestPlatGane::TestCHgVgMediaWallFirstIndexOnScreen
// --------------------------------------------------------------------------
//
TInt CTestPlatGane::TestCHgVgMediaWallFirstIndexOnScreen ( CStifItemParser&  )
    {
    START_TEST(firstindexonscreen, TestCHgVgMediaWallFirstIndexOnScreen)
    temp->FirstIndexOnScreen();
    END_TEST
    }

// --------------------------------------------------------------------------
// CTestPlatGane::TestCHgVgMediaWallItemsOnScreen
// --------------------------------------------------------------------------
//
TInt CTestPlatGane::TestCHgVgMediaWallItemsOnScreen ( CStifItemParser&  )
    {
    START_TEST(itemsonscreen, TestCHgVgMediaWallItemsOnScreen)
    temp->ItemsOnScreen();
    END_TEST
    }

// --------------------------------------------------------------------------
// CTestPlatGane::TestCHgVgMediaWallItemL
// --------------------------------------------------------------------------
//
TInt CTestPlatGane::TestCHgVgMediaWallItemL ( CStifItemParser&  )
    {
    START_TEST(iteml, TestCHgVgMediaWallItemL)
    temp->AddItem(CHgVgItem::NewL());
    temp->ItemL(0);
    END_TEST
    }


// --------------------------------------------------------------------------
// CTestPlatGane::TestCHgVgMediaWallSetItem
// --------------------------------------------------------------------------
//
TInt CTestPlatGane::TestCHgVgMediaWallSetItem ( CStifItemParser&  )
    {
    START_TEST(setitem, TestCHgVgMediaWallSetItem)
    CHgVgItem* newItem = CHgVgItem::NewL();
    temp->SetItem( newItem, 0 );
    END_TEST
    }


// --------------------------------------------------------------------------
// CTestPlatGane::TestCHgVgMediaWallAddItem
// --------------------------------------------------------------------------
//
TInt CTestPlatGane::TestCHgVgMediaWallAddItem ( CStifItemParser&  )
    {
    START_TEST(additem, TestCHgVgMediaWallAddItem)
    CHgVgItem* newItem = CHgVgItem::NewL();
    temp->AddItem( newItem );
    END_TEST
    }


// --------------------------------------------------------------------------
// CTestPlatGane::TestCHgVgMediaWallInsertItem
// --------------------------------------------------------------------------
//
TInt CTestPlatGane::TestCHgVgMediaWallInsertItem ( CStifItemParser&  )
    {
    START_TEST(insertitem, TestCHgVgMediaWallInsertItem)
    CHgVgItem* newItem = CHgVgItem::NewL();
    temp->InsertItem( newItem, 0 );
    END_TEST
    }

// --------------------------------------------------------------------------
// CTestPlatGane::TestCHgVgMediaWallRemoveItem
// --------------------------------------------------------------------------
//
TInt CTestPlatGane::TestCHgVgMediaWallRemoveItem ( CStifItemParser&  )
    {
    START_TEST(removeitem, TestCHgVgMediaWallRemoveItem)
    CHgVgItem* newItem = CHgVgItem::NewL();
    temp->AddItem( newItem );
    temp->RemoveItem(0);
    END_TEST
    }

// --------------------------------------------------------------------------
// CTestPlatGane::TestCHgVgMediaWallSelectedIndex
// --------------------------------------------------------------------------
//
TInt CTestPlatGane::TestCHgVgMediaWallSelectedIndex ( CStifItemParser&  )
    {
    START_TEST(selectedindex, TestCHgVgMediaWallSelectedIndex)
    temp->SelectedIndex();
    END_TEST
    }

// --------------------------------------------------------------------------
// CTestPlatGane::TestCHgVgMediaWallSetSelectedIndex
// --------------------------------------------------------------------------
//
TInt CTestPlatGane::TestCHgVgMediaWallSetSelectedIndex ( CStifItemParser&  )
    {
    START_TEST(setselectedindex, TestCHgVgMediaWallSetSelectedIndex)
    temp->SetSelectedIndex(0);
    END_TEST
    }


// --------------------------------------------------------------------------
// CTestPlatGane::TestCHgVgMediaWallEnableScrollBufferL
// --------------------------------------------------------------------------
//
TInt CTestPlatGane::TestCHgVgMediaWallEnableScrollBufferL ( CStifItemParser&  )
    {
    START_TEST(enablescrollbufferl, TestCHgVgMediaWallEnableScrollBufferL)
    TDummyObserver obs;
    temp->EnableScrollBufferL(obs, KScrollBufferSize, KScrollBufferSize / 4);                
    END_TEST
    }


// --------------------------------------------------------------------------
// CTestPlatGane::TestCHgVgMediaWallSetSelectionObserver
// --------------------------------------------------------------------------
//
TInt CTestPlatGane::TestCHgVgMediaWallSetSelectionObserver ( CStifItemParser&  )
    {
    START_TEST(setselectionobserver, TestCHgVgMediaWallSetSelectionObserver)
    TDummyObserver obs;
    temp->SetSelectionObserver(obs);
    END_TEST
    }


// --------------------------------------------------------------------------
// CTestPlatGane::TestCHgVgMediaWallReset
// --------------------------------------------------------------------------
//
TInt CTestPlatGane::TestCHgVgMediaWallReset ( CStifItemParser&  )
    {
    START_TEST(reset, TestCHgVgMediaWallReset)
    temp->Reset();
    END_TEST
    }


// --------------------------------------------------------------------------
// CTestPlatGane::TestCHgVgMediaWallResizeL
// --------------------------------------------------------------------------
//
TInt CTestPlatGane::TestCHgVgMediaWallResizeL ( CStifItemParser&  )
    {
    START_TEST(resizel, TestCHgVgMediaWallResizeL)
    temp->ResizeL(100);
    END_TEST
    }


// --------------------------------------------------------------------------
// CTestPlatGane::TestCHgVgMediaWallSetEmptyTextL
// --------------------------------------------------------------------------
//
TInt CTestPlatGane::TestCHgVgMediaWallSetEmptyTextL ( CStifItemParser&  )
    {
    START_TEST(setemptytextl, TestCHgVgMediaWallSetEmptyTextL)
    temp->SetEmptyTextL(_L("Empty"));
    END_TEST
    }

// --------------------------------------------------------------------------
// CTestPlatGane::TestCHgVgMediaWallItemCount
// --------------------------------------------------------------------------
//
TInt CTestPlatGane::TestCHgVgMediaWallItemCount ( CStifItemParser&  )
    {
    START_TEST(itemcount, TestCHgVgMediaWallItemCount)
    temp->ItemCount();
    END_TEST
    }

// --------------------------------------------------------------------------
// CTestPlatGane::TestCHgVgMediaWallSetDefaultIconL
// --------------------------------------------------------------------------
//
TInt CTestPlatGane::TestCHgVgMediaWallSetDefaultIconL ( CStifItemParser&  )
    {
    START_TEST(setdefaulticonl, TestCHgVgMediaWallSetDefaultIconL)
    temp->SetDefaultIconL(NULL);
    END_TEST
    }


// --------------------------------------------------------------------------
// CTestPlatGane::TestCHgVgMediaWallDisableScrollBuffer
// --------------------------------------------------------------------------
//
TInt CTestPlatGane::TestCHgVgMediaWallDisableScrollBuffer ( CStifItemParser&  )
    {
    START_TEST(disablescrollbuffer, TestCHgVgMediaWallDisableScrollBuffer)
    temp->DisableScrollBuffer();
    END_TEST
    }


// --------------------------------------------------------------------------
// CTestPlatGane::TestCHgVgMediaWallChangeStyleL
// --------------------------------------------------------------------------
//
TInt CTestPlatGane::TestCHgVgMediaWallChangeStyleL ( CStifItemParser&  )
    {
    START_TEST(changestylel, TestCHgVgMediaWallChangeStyleL)
    temp->ChangeStyleL(CHgVgMediaWall::EHgVgMediaWallStyleCoverflowTBonePortrait, 
            rect, EFalse);
    END_TEST
    }


// --------------------------------------------------------------------------
// CTestPlatGane::TestCHgVgMediaWallSetObserver
// --------------------------------------------------------------------------
//
TInt CTestPlatGane::TestCHgVgMediaWallSetObserver ( CStifItemParser&  )
    {
    START_TEST(setobserver, TestCHgVgMediaWallSetObserver)
    temp->SetObserver(NULL);
    END_TEST
    }


// --------------------------------------------------------------------------
// CTestPlatGane::TestCHgVgMediaWallSetOpeningAnimationType
// --------------------------------------------------------------------------
//
TInt CTestPlatGane::TestCHgVgMediaWallSetOpeningAnimationType ( CStifItemParser&  )
    {
    START_TEST(setopeninganimationtype, TestCHgVgMediaWallSetOpeningAnimationType)
    temp->SetOpeningAnimationType(CHgVgMediaWall::EHgVgOpeningAnimationNone);
    END_TEST
    }


// --------------------------------------------------------------------------
// CTestPlatGane::TestCHgVgMediaWallStyle
// --------------------------------------------------------------------------
//
TInt CTestPlatGane::TestCHgVgMediaWallStyle ( CStifItemParser&  )
    {
    START_TEST(setobserver, TestCHgVgMediaWallStyle)
    temp->Style();
    END_TEST
    }


// --------------------------------------------------------------------------
// CTestPlatGane::TestCHgVgMediaWallOpeningAnimationType
// --------------------------------------------------------------------------
//
TInt CTestPlatGane::TestCHgVgMediaWallOpeningAnimationType ( CStifItemParser&  )
    {
    START_TEST(openinganimationtype, TestCHgVgMediaWallOpeningAnimationType)
    temp->OpeningAnimationType();
    END_TEST
    }
  

// --------------------------------------------------------------------------
// CTestPlatGane::TestCHgVgMediaWallStartOpeningAnimationL
// --------------------------------------------------------------------------
//
TInt CTestPlatGane::TestCHgVgMediaWallStartOpeningAnimationL ( CStifItemParser&  )
    {
    START_TEST(startopeninganimationl, TestCHgVgMediaWallStartOpeningAnimationL)
    temp->StartOpeningAnimationL(ETrue);
    END_TEST
    }


