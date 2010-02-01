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
#include <testdomspecialchartab.rsg>
#include <w32std.h>
#include <eikenv.h>
#include <eikaufty.h> 

#include "testdomspecialchartab.h"

//CONSTANT
_LIT( tmp,"specialchars" );
const TInt KSize = 32;

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDomSpecialCharTab::TestCMDCAknCharMapDialogL
// -----------------------------------------------------------------------------
//
TInt CTestDomSpecialCharTab::TestCMDCAknCharMapDialogL( CStifItemParser& /*aItem*/ ) 
    {
    TBuf<KSize> specialchars( tmp );
    CAknCharMapDialog* mapdlg = new ( ELeave ) CAknCharMapDialog
            ( EAknSCTLowerCase, specialchars,R_AVKON_MENU_SCT_ROW_DEFAULT_CONTENTS_CHINESE );
    CleanupStack::PushL( mapdlg );
    STIF_ASSERT_NOT_NULL( mapdlg );
    CleanupStack::PopAndDestroy( mapdlg );
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestDomSpecialCharTab::TestCMDExecuteLDL
// -----------------------------------------------------------------------------
//
TInt CTestDomSpecialCharTab::TestCMDExecuteLDL( CStifItemParser& /*aItem*/ ) 
    {
    TBuf<KSize> specialchars( tmp );
    CAknCharMapDialog* mapdlg = new ( ELeave ) CAknCharMapDialog
            ( EAknSCTLowerCase, specialchars,R_AVKON_MENU_SCT_ROW_DEFAULT_CONTENTS_CHINESE );
    CleanupStack::PushL( mapdlg );
    CCoeEnv::Static()->AppUi()->AddToStackL( mapdlg );
    mapdlg->SetEmotionMode(EAknCharMapEmotionUse);
    mapdlg->ExecuteLD( R_AVKON_URL_SPECIAL_CHARACTER_TABLE_DIALOG );
    STIF_ASSERT_NOT_NULL( mapdlg );
    CCoeEnv::Static()->AppUi()->RemoveFromStack( mapdlg );
    CleanupStack::Pop( mapdlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomSpecialCharTab::TestCMDOfferKeyEventL
// -----------------------------------------------------------------------------
//
TInt CTestDomSpecialCharTab::TestCMDOfferKeyEventL( CStifItemParser& /*aItem*/ ) 
    {
    TBuf<KSize> specialchars( tmp );
    CAknCharMapDialog* mapdlg = new ( ELeave ) CAknCharMapDialog
            ( EAknSCTLowerCase, specialchars,R_AVKON_MENU_SCT_ROW_DEFAULT_CONTENTS_CHINESE );

    mapdlg->PrepareLC( R_TEST_DIALOG ); 
    TKeyEvent keyEvent = { EKeyPause, EStdKeySpace, 0, 0 };
    mapdlg->OfferKeyEventL(keyEvent, EEventKeyUp );
    STIF_ASSERT_NOT_NULL( mapdlg );
    CleanupStack::PopAndDestroy();
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomSpecialCharTab::TestCMDHandleResourceChangeL
// -----------------------------------------------------------------------------
//
TInt CTestDomSpecialCharTab::TestCMDHandleResourceChangeL( CStifItemParser& /*aItem*/ ) 
    {
    TBuf<KSize> specialchars( tmp );
    CAknCharMapDialog* mapdlg = new ( ELeave ) CAknCharMapDialog
            ( EAknSCTLowerCase, specialchars,R_AVKON_MENU_SCT_ROW_DEFAULT_CONTENTS_CHINESE );
    CleanupStack::PushL( mapdlg );
    mapdlg->HandleResourceChange( 1 );
    STIF_ASSERT_NOT_NULL( mapdlg );
    CleanupStack::PopAndDestroy( mapdlg );
    return KErrNone;
    }


// -----------------------------------------------------------------------------
// CTestDomSpecialCharTab::TestCMDShowNoPictographsL
// -----------------------------------------------------------------------------
//
TInt CTestDomSpecialCharTab::TestCMDShowNoPictographsL( CStifItemParser& /*aItem*/ ) 
    {
    TBuf<KSize> specialchars( tmp );
    CAknCharMapDialog* mapdlg = new ( ELeave ) CAknCharMapDialog
            ( EAknSCTLowerCase, specialchars,R_AVKON_MENU_SCT_ROW_DEFAULT_CONTENTS_CHINESE );
    CleanupStack::PushL( mapdlg );

    mapdlg->ShowNoPictographs( );
    STIF_ASSERT_NOT_NULL( mapdlg );
    CleanupStack::PopAndDestroy( mapdlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomSpecialCharTab::TestCMDShowPictographsFirstL
// -----------------------------------------------------------------------------
//
TInt CTestDomSpecialCharTab::TestCMDShowPictographsFirstL( CStifItemParser& /*aItem*/ ) 
    {
    TBuf<KSize> specialchars( tmp );
    CAknCharMapDialog* mapdlg = new ( ELeave ) CAknCharMapDialog
            ( EAknSCTLowerCase, specialchars,R_AVKON_MENU_SCT_ROW_DEFAULT_CONTENTS_CHINESE );
    CleanupStack::PushL( mapdlg );

    mapdlg->ShowPictographsFirst( );
    STIF_ASSERT_NOT_NULL( mapdlg );
    CleanupStack::PopAndDestroy( mapdlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomSpecialCharTab::TestCMDShowAnotherTableL
// -----------------------------------------------------------------------------
//
TInt CTestDomSpecialCharTab::TestCMDShowAnotherTableL( CStifItemParser& /*aItem*/ ) 
    {
    TBuf<KSize> specialchars( tmp );
    CAknCharMapDialog* mapdlg = new ( ELeave ) CAknCharMapDialog
            ( EAknSCTLowerCase, specialchars,R_AVKON_MENU_SCT_ROW_DEFAULT_CONTENTS_CHINESE );
    CleanupStack::PushL( mapdlg );

    mapdlg->ShowAnotherTable( R_AVKON_SPECIAL_CHARACTER_TABLE_DIALOG );
    STIF_ASSERT_NOT_NULL( mapdlg );
    CleanupStack::PopAndDestroy( mapdlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomSpecialCharTab::TestCMDHandleControlEventL
// -----------------------------------------------------------------------------
//
TInt CTestDomSpecialCharTab::TestCMDHandleControlEventL( CStifItemParser& /*aItem*/ ) 
    {
    TBuf<KSize> specialchars( tmp );
    CAknCharMapDialog* mapdlg = new ( ELeave ) CAknCharMapDialog
            ( EAknSCTLowerCase, specialchars,R_AVKON_MENU_SCT_ROW_DEFAULT_CONTENTS_CHINESE );
    TRect rect = CEikonEnv::Static()->AppUiFactory()->ClientRect();
    CTestDomContainer *control = new( ELeave )CTestDomContainer;
    CleanupStack::PushL( control );
    CCoeEnv::Static()->AppUi()->AddToStackL( mapdlg );
    mapdlg->PrepareLC( R_TEST_DIALOG );
    mapdlg->HandleControlEventL( control, MCoeControlObserver::EEventRequestExit );
    CleanupStack::PopAndDestroy( 2 );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomSpecialCharTab::TestCMDHandleDialogPageEventL
// -----------------------------------------------------------------------------
//
TInt CTestDomSpecialCharTab::TestCMDHandleDialogPageEventL( CStifItemParser& /*aItem*/ ) 
    {
    TBuf<KSize> specialchars( tmp );
    CAknCharMapDialog* mapdlg = new ( ELeave ) CAknCharMapDialog
            ( EAknSCTLowerCase, specialchars,R_AVKON_MENU_SCT_ROW_DEFAULT_CONTENTS_CHINESE );
    CleanupStack::PushL( mapdlg );

    mapdlg->HandleDialogPageEventL( MEikDialogPageObserver::EUnknownType );
    STIF_ASSERT_NOT_NULL( mapdlg );
    CleanupStack::PopAndDestroy( mapdlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomSpecialCharTab::TestCMDLockNumericKeysL
// -----------------------------------------------------------------------------
//
TInt CTestDomSpecialCharTab::TestCMDLockNumericKeysL( CStifItemParser& /*aItem*/ ) 
    {
    TBuf<KSize> specialchars( tmp );
    CAknCharMapDialog* mapdlg = new ( ELeave ) CAknCharMapDialog
            ( EAknSCTLowerCase, specialchars,R_AVKON_MENU_SCT_ROW_DEFAULT_CONTENTS_CHINESE );
    CleanupStack::PushL( mapdlg );
    mapdlg->LockNumericKeys( ETrue );
    STIF_ASSERT_NOT_NULL( mapdlg );
    CleanupStack::PopAndDestroy( mapdlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomSpecialCharTab::TestCMDDisableRecentCharsRowL
// -----------------------------------------------------------------------------
//
TInt CTestDomSpecialCharTab::TestCMDDisableRecentCharsRowL( CStifItemParser& /*aItem*/ ) 
    {
    TBuf<KSize> specialchars( tmp );
    CAknCharMapDialog* mapdlg = new ( ELeave ) CAknCharMapDialog
            ( EAknSCTLowerCase, specialchars,R_AVKON_MENU_SCT_ROW_DEFAULT_CONTENTS_CHINESE );
    CleanupStack::PushL( mapdlg );

    mapdlg->DisableRecentCharsRow();
    STIF_ASSERT_NOT_NULL( mapdlg );
    CleanupStack::PopAndDestroy( mapdlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomSpecialCharTab::TestCMDHandlePointerEventLL
// -----------------------------------------------------------------------------
//
TInt CTestDomSpecialCharTab::TestCMDHandlePointerEventLL( CStifItemParser& /*aItem*/ ) 
    {
    TBuf<KSize> specialchars( tmp );
    CAknCharMapDialog* mapdlg = new ( ELeave ) CAknCharMapDialog
            ( EAknSCTLowerCase, specialchars,R_AVKON_MENU_SCT_ROW_DEFAULT_CONTENTS_CHINESE );
    CleanupStack::PushL( mapdlg );
    
    TPointerEvent event;
    mapdlg->HandlePointerEventL( event );
    
    STIF_ASSERT_NOT_NULL( mapdlg );
    CleanupStack::PopAndDestroy( mapdlg );
    return KErrNone;
    }

//End of File


