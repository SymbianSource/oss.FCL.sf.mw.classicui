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
* Description:  test special_character_table_api
*
*/



// [INCLUDE FILES]
#include <barsread.h>
#include <testdomspecialchartab.rsg>

#include "testdomspecialchartab.h"
#include "testdomcharmap.h"

//CONSTANT
_LIT(KGlobalNoteText,"char");
const TInt KSize = 32;

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDomSpecialCharTab::TestCMDCAknCharMapDialogL
// -----------------------------------------------------------------------------
//
TInt CTestDomSpecialCharTab::TestCMCAknCharMapL( CStifItemParser& /*aItem*/ ) 
    {
    CAknCharMap* charmap = new ( ELeave ) CAknCharMap();
    CleanupStack::PushL( charmap );
    STIF_ASSERT_NOT_NULL( charmap );
    CleanupStack::PopAndDestroy( charmap );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomSpecialCharTab::TestCMSetBufferL
// -----------------------------------------------------------------------------
//
TInt CTestDomSpecialCharTab::TestCMSetBufferL( CStifItemParser& /*aItem*/ ) 
    {
    TBuf<KSize> specialChars( KGlobalNoteText );
    CAknCharMap* charmap = new ( ELeave ) CAknCharMap();
    CleanupStack::PushL( charmap );
    charmap->SetBuffer( specialChars );
    STIF_ASSERT_NOT_NULL( charmap );
    CleanupStack::PopAndDestroy( charmap );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomSpecialCharTab::TestCMMinimumSizeL
// -----------------------------------------------------------------------------
//
TInt CTestDomSpecialCharTab::TestCMMinimumSizeL( CStifItemParser& /*aItem*/ ) 
    {
    CAknCharMap* charmap = new ( ELeave ) CAknCharMap();
    CleanupStack::PushL( charmap );
    charmap->MinimumSize();
    STIF_ASSERT_NOT_NULL( charmap );
    CleanupStack::PopAndDestroy( charmap );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomSpecialCharTab::TestCMOfferKeyEventL
// -----------------------------------------------------------------------------
//
TInt CTestDomSpecialCharTab::TestCMOfferKeyEventL( CStifItemParser& /*aItem*/ ) 
    {
    CAknCharMap* charmap = new ( ELeave ) CAknCharMap();
    CleanupStack::PushL( charmap );
  
    TKeyEvent keyEvent;
    charmap->OfferKeyEventL( keyEvent, EEventNull );
    STIF_ASSERT_NOT_NULL( charmap );
    
    CleanupStack::PopAndDestroy( charmap );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomSpecialCharTab::TestCMInputCapabilitiesL
// -----------------------------------------------------------------------------
//
TInt CTestDomSpecialCharTab::TestCMInputCapabilitiesL( CStifItemParser& /*aItem*/ ) 
    {
    CAknCharMap* charmap = new ( ELeave ) CAknCharMap();
    CleanupStack::PushL( charmap );
    charmap->InputCapabilities();
    STIF_ASSERT_NOT_NULL( charmap );
    CleanupStack::PopAndDestroy( charmap );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomSpecialCharTab::TestCMActivateL
// -----------------------------------------------------------------------------
//
TInt CTestDomSpecialCharTab::TestCMActivateL( CStifItemParser& /*aItem*/ ) 
    {
    CAknCharMap* charmap = new ( ELeave ) CAknCharMap();
    CleanupStack::PushL( charmap );
    charmap->ActivateL();
    STIF_ASSERT_NOT_NULL( charmap );
    CleanupStack::PopAndDestroy( charmap );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomSpecialCharTab::TestCMDoSizeChangedL
// -----------------------------------------------------------------------------
//
TInt CTestDomSpecialCharTab::TestCMDoSizeChangedL( CStifItemParser& /*aItem*/ ) 
    {
    CTestDomCharMap* testdomcharmap = new ( ELeave ) CTestDomCharMap();
    CleanupStack::PushL( testdomcharmap );
    testdomcharmap->DoSizeChanged();
    STIF_ASSERT_NOT_NULL( testdomcharmap );
    CleanupStack::PopAndDestroy( testdomcharmap );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomSpecialCharTab::TestCMDoHandleResourceChangeL
// -----------------------------------------------------------------------------
//
TInt CTestDomSpecialCharTab::TestCMDoHandleResourceChangeL( CStifItemParser& /*aItem*/ ) 
    {
    CTestDomCharMap* testdomcharmap = new ( ELeave ) CTestDomCharMap();
    CleanupStack::PushL( testdomcharmap );
    testdomcharmap->DoHandleResourceChange( 1 );
    STIF_ASSERT_NOT_NULL( testdomcharmap );
    CleanupStack::PopAndDestroy( testdomcharmap );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomSpecialCharTab::TestCMDoCountComponentControlsL
// -----------------------------------------------------------------------------
//
TInt CTestDomSpecialCharTab::TestCMDoCountComponentControlsL( CStifItemParser& /*aItem*/ ) 
    {
    CTestDomCharMap* testdomcharmap = new ( ELeave ) CTestDomCharMap();
    CleanupStack::PushL( testdomcharmap );
    testdomcharmap->DoCountComponentControls();
    STIF_ASSERT_NOT_NULL( testdomcharmap );
    CleanupStack::PopAndDestroy( testdomcharmap );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomSpecialCharTab::TestCMDoComponentControlL
// -----------------------------------------------------------------------------
//
TInt CTestDomSpecialCharTab::TestCMDoComponentControlL( CStifItemParser& /*aItem*/ ) 
    {
    CTestDomCharMap* testdomcharmap = new ( ELeave ) CTestDomCharMap();
    CleanupStack::PushL( testdomcharmap );
    testdomcharmap->DoComponentControl( 1 );
    STIF_ASSERT_NOT_NULL( testdomcharmap );
    CleanupStack::PopAndDestroy( testdomcharmap );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomSpecialCharTab::TestCMHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestDomSpecialCharTab::TestCMHandlePointerEventL( CStifItemParser& /*aItem*/ ) 
    {
    CAknCharMap* charmap = new ( ELeave ) CAknCharMap();
    CleanupStack::PushL( charmap );
    TPointerEvent pointerEvent;
    charmap->HandlePointerEventL( pointerEvent );
    CleanupStack::PopAndDestroy( charmap );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomSpecialCharTab::TestCMSetObserverL
// -----------------------------------------------------------------------------
//
TInt CTestDomSpecialCharTab::TestCMSetObserverL( CStifItemParser& /*aItem*/ ) 
    {
    CAknCharMap* charmap = new ( ELeave ) CAknCharMap();
    CleanupStack::PushL( charmap );
    charmap->SetObserver( NULL );
    CleanupStack::PopAndDestroy( charmap );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomSpecialCharTab::TestCMConstructMenuSctRowL
// -----------------------------------------------------------------------------
//
TInt CTestDomSpecialCharTab::TestCMConstructMenuSctRowL( CStifItemParser& /*aItem*/ ) 
    {
    CAknCharMap* charmap = new ( ELeave ) CAknCharMap();
    CleanupStack::PushL( charmap );
    charmap->ConstructMenuSctRowL();
    CleanupStack::PopAndDestroy( charmap );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomSpecialCharTab::TestCMSetMenuSctRectL
// -----------------------------------------------------------------------------
//
TInt CTestDomSpecialCharTab::TestCMSetMenuSctRectL( CStifItemParser& /*aItem*/ ) 
    {
    CAknCharMap* charmap = new ( ELeave ) CAknCharMap();
    CleanupStack::PushL( charmap );
    const TRect menuSctRect( 0, 0, 200, 200 );   
    charmap->SetMenuSctRect( menuSctRect );
    CleanupStack::PopAndDestroy( charmap );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomSpecialCharTab::TestCMConstructMenuSctRowIdL
// -----------------------------------------------------------------------------
//
TInt CTestDomSpecialCharTab::TestCMConstructMenuSctRowIdL( CStifItemParser& /*aItem*/ ) 
    {
    CAknCharMap* charmap = new ( ELeave ) CAknCharMap();
    CleanupStack::PushL( charmap );
    charmap->ConstructMenuSctRowL( R_AVKON_MENU_SCT_ROW_DEFAULT_CONTENTS_CHINESE );
    CleanupStack::PopAndDestroy( charmap );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomSpecialCharTab::TestCMHighlightSctRowL
// -----------------------------------------------------------------------------
//
TInt CTestDomSpecialCharTab::TestCMHighlightSctRowL( CStifItemParser& /*aItem*/ ) 
    {
    CAknCharMap* charmap = new ( ELeave ) CAknCharMap();
    CleanupStack::PushL( charmap );
    TPointerEvent pointerEvent; 
    charmap->HighlightSctRow( ETrue );
    CleanupStack::PopAndDestroy( charmap );
    return KErrNone;
    }

//End of File


