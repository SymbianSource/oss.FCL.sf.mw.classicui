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
* Description:  test aknpopupform.h
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <aknpopupform.h>
#include <eikimage.h>
#include <eikenv.h>
#include <eikappui.h>
#include <akndef.h>
#include <w32std.h>

#include <testdompopupform.rsg>
#include "testdompopupform.h"
#include "testdompopupform.hrh"
#include "testdompopupformext.h"

// CONSTANTS
const TInt KBufSize = 16;
const TInt KTimeOut = 3;
const TInt KPopupFormWidth = 100;
const TInt KPopupFormHeight = 100;
const TInt KEventPointX = 10;
const TInt KEventPointY = 30;

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDOMPopupForm::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestDOMPopupForm::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "TestPfDefCons", CTestDOMPopupForm::TestPfDefConsL ),
        ENTRY( "TestPfDefConsWithPa", CTestDOMPopupForm::TestPfDefConsWithPaL ),
        ENTRY( "TestPfNewLCWithPa", CTestDOMPopupForm::TestPfNewLCWithPaL ),
        ENTRY( "TestPfNewLWithPa", CTestDOMPopupForm::TestPfNewLWithPaL ),
        ENTRY( "TestPfNewLC", CTestDOMPopupForm::TestPfNewLCL ),
        ENTRY( "TestPfNewL", CTestDOMPopupForm::TestPfNewL ),
        ENTRY( "TestPfConstructL", CTestDOMPopupForm::TestPfConstructL ),
        ENTRY( "TestPfSetTimeout", CTestDOMPopupForm::TestPfSetTimeoutL ),
        ENTRY( "TestPfSetTone", CTestDOMPopupForm::TestPfSetToneL ),
        ENTRY( "TestPfSetPopupFormType",
                CTestDOMPopupForm::TestPfSetPopupFormTypeL ),
        ENTRY( "TestPfPrepareLC", CTestDOMPopupForm::TestPfPrepareLCL ),
        ENTRY( "TestPfSetTitleL", CTestDOMPopupForm::TestPfSetTitleL ),
        ENTRY( "TestPfSetTextL", CTestDOMPopupForm::TestPfSetTextL ),
        ENTRY( "TestPfIncProBarAndDraw",
                CTestDOMPopupForm::TestPfIncProBarAndDrawL ),
        ENTRY( "TestPfSetProBarAndDraw",
                CTestDOMPopupForm::TestPfSetProBarAndDrawL ),
        ENTRY( "TestPfDraw", CTestDOMPopupForm::TestPfDrawL ),
        ENTRY( "TestPfGetControl", CTestDOMPopupForm::TestPfGetControL ),
        ENTRY( "TestPfProgressInfo", CTestDOMPopupForm::TestPfProgressInfoL ),
        ENTRY( "TestPfSetImageL", CTestDOMPopupForm::TestPfSetImageL ),
        ENTRY( "TestPfSetCallback", CTestDOMPopupForm::TestPfSetCallbackL ),
        ENTRY( "TestPfProcessFinishedL",
                CTestDOMPopupForm::TestPfProcessFinishedL ),
        ENTRY( "TestPfRunLD", CTestDOMPopupForm::TestPfRunLDL ),
        ENTRY( "TestPfSetSizeAndPos", CTestDOMPopupForm::TestPfSetSizeAndPosL ),
        ENTRY( "TestPfActivateL", CTestDOMPopupForm::TestPfActivateL ),
        ENTRY( "TestPfOkToExitL", CTestDOMPopupForm::TestPfOkToExitL ),
        ENTRY( "TestPfHandleResourceChange",
                CTestDOMPopupForm::TestPfHandleResourceChangeL ),
        ENTRY( "TestPfPlayTone", CTestDOMPopupForm::TestPfPlayToneL ),
        ENTRY( "TestPfStaticDeleteL", CTestDOMPopupForm::TestPfStaticDeleteL ),
        ENTRY( "TestPfSoundSystem", CTestDOMPopupForm::TestPfSoundSystemL ),
        ENTRY( "TestPfLayoutAndDraw", CTestDOMPopupForm::TestPfLayoutAndDrawL ),
        ENTRY( "TestPfPostLayoutDynInitL",
                CTestDOMPopupForm::TestPfPostLayoutDynInitL ),
        ENTRY( "TestPfSizeChanged", CTestDOMPopupForm::TestPfSizeChangedL ),
        ENTRY( "TestPfOfferKeyEventL", CTestDOMPopupForm::TestPfOfferKeyEventL ),
        ENTRY( "TestPfHandlePointerEventL",
                CTestDOMPopupForm::TestPfHandlePointerEventL ),
        ENTRY( "TestPfInsertControlL", CTestDOMPopupForm::TestPfInsertControlL ),
        ENTRY( "TestPfDeleteControlWithInt",
                CTestDOMPopupForm::TestPfDeleteControlWithIntL ),
        ENTRY( "TestPfTextIsScrollable",
                CTestDOMPopupForm::TestPfTextIsScrollableL ),
        ENTRY( "TestPfFlags", CTestDOMPopupForm::TestPfFlagsL ),
        ENTRY( "TestPfGetControlL", CTestDOMPopupForm::TestPfGetControlL ),
        ENTRY( "TestPfDeleteControlWithCtrl",
                CTestDOMPopupForm::TestPfDeleteControlWithCtrlL ),
        ENTRY( "TestPfSetWaitIndex", CTestDOMPopupForm::TestPfSetWaitIndexL ),
        ENTRY( "TestPfInsertControlWithBoolL",
                CTestDOMPopupForm::TestPfInsertControlWithBoolL ),

        // [test cases entries]

        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// CTestDOMPopupForm::TestPfDefConsL
// -----------------------------------------------------------------------------
//
TInt CTestDOMPopupForm::TestPfDefConsL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestPopupForm, "testpopupform" );
    _LIT( KTestPfDefCons, "In PfDefCons" );
    TestModuleIf().Printf( 0, KTestPopupForm, KTestPfDefCons );
    // Print to log file
    iLog->Log( KTestPfDefCons );

    CAknPopupForm* popupForm = new ( ELeave ) CAknPopupForm;
    CleanupStack::PushL( popupForm );
    STIF_ASSERT_NOT_NULL( popupForm )

    CleanupStack::PopAndDestroy( popupForm );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMPopupForm::TestPfDefConsWithPaL
// -----------------------------------------------------------------------------
//
TInt CTestDOMPopupForm::TestPfDefConsWithPaL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestPopupForm, "testpopupform" );
    _LIT( KTestPfDefConsWithPa, "In PfDefConsWithPa" );
    TestModuleIf().Printf( 0, KTestPopupForm, KTestPfDefConsWithPa );
    // Print to log file
    iLog->Log( KTestPfDefConsWithPa );

    CAknPopupForm* popupForm = new ( ELeave ) CAknPopupForm( ENoTone, 0, EAknNote);
    CleanupStack::PushL( popupForm );
    STIF_ASSERT_NOT_NULL( popupForm );

    CleanupStack::PopAndDestroy( popupForm );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMPopupForm::TestPfNewLCWithPaL
// -----------------------------------------------------------------------------
//
TInt CTestDOMPopupForm::TestPfNewLCWithPaL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestPopupForm, "testpopupform" );
    _LIT( KTestPfNewLCWithPa, "In PfNewLCWithPa" );
    TestModuleIf().Printf( 0, KTestPopupForm, KTestPfNewLCWithPa );
    // Print to log file
    iLog->Log( KTestPfNewLCWithPa );

    CAknPopupForm* popupForm = CAknPopupForm::NewLC( ENoTone );
    STIF_ASSERT_NOT_NULL( popupForm );

    CleanupStack::PopAndDestroy( popupForm );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMPopupForm::TestPfNewLWithPaL
// -----------------------------------------------------------------------------
//
TInt CTestDOMPopupForm::TestPfNewLWithPaL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestPopupForm, "testpopupform" );
    _LIT( KTestPfNewLWithPa, "In PfNewLWithPa" );
    TestModuleIf().Printf( 0, KTestPopupForm, KTestPfNewLWithPa );
    // Print to log file
    iLog->Log( KTestPfNewLWithPa );

    CAknPopupForm* popupForm = CAknPopupForm::NewL( ENoTone );
    CleanupStack::PushL( popupForm );
    STIF_ASSERT_NOT_NULL( popupForm );

    CleanupStack::PopAndDestroy( popupForm );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMPopupForm::TestPfNewLCL
// -----------------------------------------------------------------------------
//
TInt CTestDOMPopupForm::TestPfNewLCL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestPopupForm, "testpopupform" );
    _LIT( KTestPfNewLC, "In PfNewLC" );
    TestModuleIf().Printf( 0, KTestPopupForm, KTestPfNewLC );
    // Print to log file
    iLog->Log( KTestPfNewLC );

    CAknPopupForm* popupForm = CAknPopupForm::NewLC();
    STIF_ASSERT_NOT_NULL( popupForm );

    CleanupStack::PopAndDestroy( popupForm );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMPopupForm::TestPfNewL
// -----------------------------------------------------------------------------
//
TInt CTestDOMPopupForm::TestPfNewL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestPopupForm, "testpopupform" );
    _LIT( KTestPfNewL, "In PfNewL" );
    TestModuleIf().Printf( 0, KTestPopupForm, KTestPfNewL );
    // Print to log file
    iLog->Log( KTestPfNewL );

    CAknPopupForm* popupForm = CAknPopupForm::NewL();
    CleanupStack::PushL( popupForm );
    STIF_ASSERT_NOT_NULL( popupForm );

    CleanupStack::PopAndDestroy( popupForm );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMPopupForm::TestPfConstructL
// -----------------------------------------------------------------------------
//
TInt CTestDOMPopupForm::TestPfConstructL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestPopupForm, "testpopupform" );
    _LIT( KTestPfConstructL, "In PfConstructL" );
    TestModuleIf().Printf( 0, KTestPopupForm, KTestPfConstructL );
    // Print to log file
    iLog->Log( KTestPfConstructL );

    CAknPopupFormExt* popupFormExt = new ( ELeave ) CAknPopupFormExt;
    CleanupStack::PushL( popupFormExt );

    popupFormExt->DoConstructL();

    CleanupStack::PopAndDestroy( popupFormExt );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMPopupForm::TestPfSetTimeoutL
// -----------------------------------------------------------------------------
//
TInt CTestDOMPopupForm::TestPfSetTimeoutL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestPopupForm, "testpopupform" );
    _LIT( KTestPfSetTimeout, "In PfSetTimeout" );
    TestModuleIf().Printf( 0, KTestPopupForm, KTestPfSetTimeout );
    // Print to log file
    iLog->Log( KTestPfSetTimeout );

    CAknPopupForm* popupForm = CAknPopupForm::NewL();
    CleanupStack::PushL( popupForm );

    popupForm->SetTimeout( KTimeOut );

    CleanupStack::PopAndDestroy( popupForm );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMPopupForm::TestPfSetToneL
// -----------------------------------------------------------------------------
//
TInt CTestDOMPopupForm::TestPfSetToneL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestPopupForm, "testpopupform" );
    _LIT( KTestPfSetTone, "In PfSetTone" );
    TestModuleIf().Printf( 0, KTestPopupForm, KTestPfSetTone );
    // Print to log file
    iLog->Log( KTestPfSetTone );

    CAknPopupForm* popupForm = CAknPopupForm::NewL();
    CleanupStack::PushL( popupForm );

    popupForm->SetTone( EConfirmationTone );

    CleanupStack::PopAndDestroy( popupForm );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMPopupForm::TestPfSetPopupFormTypeL
// -----------------------------------------------------------------------------
//
TInt CTestDOMPopupForm::TestPfSetPopupFormTypeL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestPopupForm, "testpopupform" );
    _LIT( KTestPfSetPopupFormType, "In PfSetPopupFormType" );
    TestModuleIf().Printf( 0, KTestPopupForm, KTestPfSetPopupFormType );
    // Print to log file
    iLog->Log( KTestPfSetPopupFormType );

    CAknPopupForm* popupForm = CAknPopupForm::NewL();
    CleanupStack::PushL( popupForm );

    popupForm->SetPopupFormType( EAknQuery );

    CleanupStack::PopAndDestroy( popupForm );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMPopupForm::TestPfPrepareLCL
// -----------------------------------------------------------------------------
//
TInt CTestDOMPopupForm::TestPfPrepareLCL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestPopupForm, "testpopupform" );
    _LIT( KTestPfPrepareLC, "In PfPrepareLC" );
    TestModuleIf().Printf( 0, KTestPopupForm, KTestPfPrepareLC );
    // Print to log file
    iLog->Log( KTestPfPrepareLC );

    CAknPopupForm* popupForm = CAknPopupForm::NewL();
    CleanupStack::PushL( popupForm );
    CleanupStack::Pop( popupForm );

    popupForm->PrepareLC( R_POPUPFORM_DIALOG );

    CleanupStack::PopAndDestroy( popupForm );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMPopupForm::TestPfSetTitleL
// -----------------------------------------------------------------------------
//
TInt CTestDOMPopupForm::TestPfSetTitleL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestPopupForm, "testpopupform" );
    _LIT( KTestPfSetTitleL, "In PfSetTitleL" );
    TestModuleIf().Printf( 0, KTestPopupForm, KTestPfSetTitleL );
    // Print to log file
    iLog->Log( KTestPfSetTitleL );

    CAknPopupForm* popupForm = CAknPopupForm::NewL();
    CleanupStack::PushL( popupForm );
    CleanupStack::Pop( popupForm );
    popupForm->PrepareLC( R_POPUPFORM_DIALOG );

    _LIT( KTitle, "Title" );
    popupForm->SetTitleL( KTitle );

    CleanupStack::PopAndDestroy( popupForm );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMPopupForm::TestPfSetTextL
// -----------------------------------------------------------------------------
//
TInt CTestDOMPopupForm::TestPfSetTextL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestPopupForm, "testpopupform" );
    _LIT( KTestPfSetTextL, "In PfSetTextL" );
    TestModuleIf().Printf( 0, KTestPopupForm, KTestPfSetTextL );
    // Print to log file
    iLog->Log( KTestPfSetTextL );

    CAknPopupForm* popupForm = CAknPopupForm::NewL();
    CleanupStack::PushL( popupForm );
    CleanupStack::Pop( popupForm );
    popupForm->PrepareLC( R_POPUPFORM_DIALOG );

    _LIT( KText, "Text" );
    HBufC* text = HBufC::NewL( KBufSize );
    CleanupStack::PushL( text );
    *text = KText;
    popupForm->SetTextL( text );

    CleanupStack::PopAndDestroy( text );
    CleanupStack::PopAndDestroy( popupForm );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMPopupForm::TestPfIncProBarAndDrawL
// -----------------------------------------------------------------------------
//
TInt CTestDOMPopupForm::TestPfIncProBarAndDrawL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestPopupForm, "testpopupform" );
    _LIT( KTestPfIncProBarAndDraw, "In PfIncProBarAndDraw" );
    TestModuleIf().Printf( 0, KTestPopupForm, KTestPfIncProBarAndDraw );
    // Print to log file
    iLog->Log( KTestPfIncProBarAndDraw );

    CAknPopupForm* popupForm = CAknPopupForm::NewL();
    CleanupStack::PushL( popupForm );
    CleanupStack::Pop( popupForm );
    popupForm->PrepareLC( R_POPUPFORM_DIALOG );

    TInt increment = 1;
    popupForm->IncrementProgressBarAndDraw( increment );

    CleanupStack::PopAndDestroy( popupForm );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMPopupForm::TestPfSetProBarAndDrawL
// -----------------------------------------------------------------------------
//
TInt CTestDOMPopupForm::TestPfSetProBarAndDrawL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestPopupForm, "testpopupform" );
    _LIT( KTestPfSetProBarAndDraw, "In PfSetProBarAndDraw" );
    TestModuleIf().Printf( 0, KTestPopupForm, KTestPfSetProBarAndDraw );
    // Print to log file
    iLog->Log( KTestPfSetProBarAndDraw );

    CAknPopupForm* popupForm = CAknPopupForm::NewL();
    CleanupStack::PushL( popupForm );
    CleanupStack::Pop( popupForm );
    popupForm->PrepareLC( R_POPUPFORM_DIALOG );

    TInt value = 1;
    popupForm->SetProgressBarAndDraw( value );

    CleanupStack::PopAndDestroy( popupForm );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMPopupForm::TestPfDrawL
// -----------------------------------------------------------------------------
//
TInt CTestDOMPopupForm::TestPfDrawL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestPopupForm, "testpopupform" );
    _LIT( KTestPfDraw, "In PfDraw" );
    TestModuleIf().Printf( 0, KTestPopupForm, KTestPfDraw );
    // Print to log file
    iLog->Log( KTestPfDraw );

    CAknPopupFormExt* popupForm = new ( ELeave ) CAknPopupFormExt;
    CleanupStack::PushL( popupForm );
    CleanupStack::Pop( popupForm );
    popupForm->PrepareLC( R_POPUPFORM_DIALOG );
    popupForm->DoActivateGc();

    TSize size( KPopupFormWidth, KPopupFormHeight );
    TRect rect( size );
    popupForm->Draw( rect );

    popupForm->DoDeactivateGc();
    CleanupStack::PopAndDestroy( popupForm );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMPopupForm::TestPfGetControL
// -----------------------------------------------------------------------------
//
TInt CTestDOMPopupForm::TestPfGetControL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestPopupForm, "testpopupform" );
    _LIT( KTestPfGetControl, "In PfGetControl" );
    TestModuleIf().Printf( 0, KTestPopupForm, KTestPfGetControl );
    // Print to log file
    iLog->Log( KTestPfGetControl );

    CAknPopupForm* popupForm = CAknPopupForm::NewL();
    CleanupStack::PushL( popupForm );
    CleanupStack::Pop( popupForm );
    popupForm->PrepareLC( R_POPUPFORM_DIALOG );

    TInt controlType = 1;
    CEikCaptionedControl* control = popupForm->GetControlByControlType( controlType );
    STIF_ASSERT_NULL( control );

    CleanupStack::PopAndDestroy( popupForm );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMPopupForm::TestPfProgressInfoL
// -----------------------------------------------------------------------------
//
TInt CTestDOMPopupForm::TestPfProgressInfoL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestPopupForm, "testpopupform" );
    _LIT( KTestPfProgressInfo, "In PfProgressInfo" );
    TestModuleIf().Printf( 0, KTestPopupForm, KTestPfProgressInfo );
    // Print to log file
    iLog->Log( KTestPfProgressInfo );

    CAknPopupForm* popupForm = CAknPopupForm::NewL();
    CleanupStack::PushL( popupForm );
    CleanupStack::Pop( popupForm );
    popupForm->PrepareLC( R_POPUPFORM_DIALOG );

    CEikProgressInfo* info = popupForm->ProgressInfo();
    STIF_ASSERT_NULL( info );

    CleanupStack::PopAndDestroy( popupForm );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMPopupForm::TestPfSetImageL
// -----------------------------------------------------------------------------
//
TInt CTestDOMPopupForm::TestPfSetImageL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestPopupForm, "testpopupform" );
    _LIT( KTestPfSetImageL, "In PfSetImageL" );
    TestModuleIf().Printf( 0, KTestPopupForm, KTestPfSetImageL );
    // Print to log file
    iLog->Log( KTestPfSetImageL );

    CAknPopupForm* popupForm = CAknPopupForm::NewL();
    CleanupStack::PushL( popupForm );
    CleanupStack::Pop( popupForm );
    popupForm->PrepareLC( R_POPUPFORM_DIALOG );

    CEikImage* image = new ( ELeave ) CEikImage;
    CleanupStack::PushL( image );
    popupForm->SetImageL( image );

    CleanupStack::PopAndDestroy( image );
    CleanupStack::PopAndDestroy( popupForm );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMPopupForm::TestPfSetCallbackL
// -----------------------------------------------------------------------------
//
TInt CTestDOMPopupForm::TestPfSetCallbackL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestPopupForm, "testpopupform" );
    _LIT( KTestPfSetCallback, "In PfSetCallback" );
    TestModuleIf().Printf( 0, KTestPopupForm, KTestPfSetCallback );
    // Print to log file
    iLog->Log( KTestPfSetCallback );

    CAknPopupForm* popupForm = CAknPopupForm::NewL();
    CleanupStack::PushL( popupForm );

    CAknPopupFormExt* callback = new ( ELeave ) CAknPopupFormExt;
    CleanupStack::PushL( callback );
    popupForm->SetCallback( callback );

    CleanupStack::PopAndDestroy( callback );
    CleanupStack::PopAndDestroy( popupForm );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMPopupForm::TestPfProcessFinishedL
// -----------------------------------------------------------------------------
//
TInt CTestDOMPopupForm::TestPfProcessFinishedL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestPopupForm, "testpopupform" );
    _LIT( KTestPfProcessFinishedL, "In PfProcessFinishedL" );
    TestModuleIf().Printf( 0, KTestPopupForm, KTestPfProcessFinishedL );
    // Print to log file
    iLog->Log( KTestPfProcessFinishedL );

    CAknPopupForm* popupForm = CAknPopupForm::NewL();
    CleanupStack::PushL( popupForm );
    CleanupStack::Pop( popupForm );
    popupForm->PrepareLC( R_POPUPFORM_DIALOG );
    
    popupForm->ProcessFinishedL();

    CleanupStack::Pop( popupForm );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMPopupForm::TestPfRunLDL
// -----------------------------------------------------------------------------
//
TInt CTestDOMPopupForm::TestPfRunLDL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestPopupForm, "testpopupform" );
    _LIT( KTestPfRunLD, "In PfRunLD" );
    TestModuleIf().Printf( 0, KTestPopupForm, KTestPfRunLD );
    // Print to log file
    iLog->Log( KTestPfRunLD );

    CAknPopupForm* popupForm = CAknPopupForm::NewL();
    CleanupStack::PushL( popupForm );
    CleanupStack::Pop( popupForm );
    
    popupForm->PrepareLC( R_POPUPFORM_DIALOG );
    
    TInt butId = popupForm->RunLD();
    STIF_ASSERT_EQUALS( 0, butId );
    
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMPopupForm::TestPfSetSizeAndPosL
// -----------------------------------------------------------------------------
//
TInt CTestDOMPopupForm::TestPfSetSizeAndPosL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestPopupForm, "testpopupform" );
    _LIT( KTestPfSetSizeAndPos, "In PfSetSizeAndPos" );
    TestModuleIf().Printf( 0, KTestPopupForm, KTestPfSetSizeAndPos );
    // Print to log file
    iLog->Log( KTestPfSetSizeAndPos );

    CAknPopupForm* popupForm = CAknPopupForm::NewL();
    CleanupStack::PushL( popupForm );
    CleanupStack::Pop( popupForm );
    popupForm->PrepareLC( R_POPUPFORM_DIALOG );

    TSize size( KPopupFormWidth, KPopupFormHeight);
    popupForm->SetSizeAndPosition( size );

    CleanupStack::PopAndDestroy( popupForm );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMPopupForm::TestPfActivateL
// -----------------------------------------------------------------------------
//
TInt CTestDOMPopupForm::TestPfActivateL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestPopupForm, "testpopupform" );
    _LIT( KTestPfActivateL, "In PfActivateL" );
    TestModuleIf().Printf( 0, KTestPopupForm, KTestPfActivateL );
    // Print to log file
    iLog->Log( KTestPfActivateL );

    CAknPopupForm* popupForm = CAknPopupForm::NewL();
    CleanupStack::PushL( popupForm );
    CleanupStack::Pop( popupForm );
    popupForm->PrepareLC( R_POPUPFORM_DIALOG );

    popupForm->ActivateL();

    CEikonEnv::Static()->EikAppUi()->RemoveFromStack( popupForm );
    CleanupStack::PopAndDestroy( popupForm );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMPopupForm::TestPfOkToExitL
// -----------------------------------------------------------------------------
//
TInt CTestDOMPopupForm::TestPfOkToExitL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestPopupForm, "testpopupform" );
    _LIT( KTestPfOkToExitL, "In PfOkToExitL" );
    TestModuleIf().Printf( 0, KTestPopupForm, KTestPfOkToExitL );
    // Print to log file
    iLog->Log( KTestPfOkToExitL );

    CAknPopupForm* popupForm = CAknPopupForm::NewL();
    CleanupStack::PushL( popupForm );
    CleanupStack::Pop( popupForm );
    popupForm->PrepareLC( R_POPUPFORM_DIALOG );

    TBool exit = popupForm->OkToExitL( EAknSoftkeyEmpty );
    STIF_ASSERT_FALSE( exit );

    CleanupStack::PopAndDestroy( popupForm );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMPopupForm::TestPfHandleResourceChangeL
// -----------------------------------------------------------------------------
//
TInt CTestDOMPopupForm::TestPfHandleResourceChangeL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestPopupForm, "testpopupform" );
    _LIT( KTestPfHandleResourceChange, "In PfHandleResourceChange" );
    TestModuleIf().Printf( 0, KTestPopupForm, KTestPfHandleResourceChange );
    // Print to log file
    iLog->Log( KTestPfHandleResourceChange );

    CAknPopupForm* popupForm = CAknPopupForm::NewL();
    CleanupStack::PushL( popupForm );
    CleanupStack::Pop( popupForm );
    popupForm->PrepareLC( R_POPUPFORM_DIALOG );

    popupForm->HandleResourceChange( KEikDynamicLayoutVariantSwitch );

    CleanupStack::PopAndDestroy( popupForm );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMPopupForm::TestPfPlayToneL
// -----------------------------------------------------------------------------
//
TInt CTestDOMPopupForm::TestPfPlayToneL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestPopupForm, "testpopupform" );
    _LIT( KTestPfPlayTone, "In PfPlayTone" );
    TestModuleIf().Printf( 0, KTestPopupForm, KTestPfPlayTone );
    // Print to log file
    iLog->Log( KTestPfPlayTone );

    CAknPopupFormExt* popupFormExt = new ( ELeave ) CAknPopupFormExt;
    CleanupStack::PushL( popupFormExt );
    CleanupStack::Pop( popupFormExt );
    popupFormExt->PrepareLC( R_POPUPFORM_DIALOG );

    popupFormExt->DoPlayTone();

    CleanupStack::PopAndDestroy( popupFormExt );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMPopupForm::TestPfStaticDeleteL
// -----------------------------------------------------------------------------
//
TInt CTestDOMPopupForm::TestPfStaticDeleteL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestPopupForm, "testpopupform" );
    _LIT( KTestPfStaticDeleteL, "In PfStaticDeleteL" );
    TestModuleIf().Printf( 0, KTestPopupForm, KTestPfStaticDeleteL );
    // Print to log file
    iLog->Log( KTestPfStaticDeleteL );

    CAknPopupFormExt* popupFormExt = new ( ELeave ) CAknPopupFormExt;
    CleanupStack::PushL( popupFormExt );
    CleanupStack::Pop( popupFormExt );

    TInt err = popupFormExt->DoStaticDeleteL( popupFormExt );
    return err;

    }

// -----------------------------------------------------------------------------
// CTestDOMPopupForm::TestPfSoundSystemL
// -----------------------------------------------------------------------------
//
TInt CTestDOMPopupForm::TestPfSoundSystemL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestPopupForm, "testpopupform" );
    _LIT( KTestPfSoundSystem, "In PfSoundSystem" );
    TestModuleIf().Printf( 0, KTestPopupForm, KTestPfSoundSystem );
    // Print to log file
    iLog->Log( KTestPfSoundSystem );

    CAknPopupFormExt* popupFormExt = new ( ELeave ) CAknPopupFormExt;
    CleanupStack::PushL( popupFormExt );

    CAknKeySoundSystem* keySoundSystem = popupFormExt->DoSoundSystem();
    STIF_ASSERT_NOT_NULL( keySoundSystem );

    CleanupStack::PopAndDestroy( popupFormExt );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMPopupForm::TestPfLayoutAndDrawL
// -----------------------------------------------------------------------------
//
TInt CTestDOMPopupForm::TestPfLayoutAndDrawL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestPopupForm, "testpopupform" );
    _LIT( KTestPfLayoutAndDraw, "In PfLayoutAndDraw" );
    TestModuleIf().Printf( 0, KTestPopupForm, KTestPfLayoutAndDraw );
    // Print to log file
    iLog->Log( KTestPfLayoutAndDraw );

    CAknPopupFormExt* popupFormExt = new ( ELeave ) CAknPopupFormExt;
    CleanupStack::PushL( popupFormExt );
    CleanupStack::Pop( popupFormExt );
    popupFormExt->PrepareLC( R_POPUPFORM_DIALOG );
    popupFormExt->DoActivateGc();

    popupFormExt->DoLayoutAndDraw();

    popupFormExt->DoDeactivateGc();
    CleanupStack::PopAndDestroy( popupFormExt );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMPopupForm::TestPfPostLayoutDynInitL
// -----------------------------------------------------------------------------
//
TInt CTestDOMPopupForm::TestPfPostLayoutDynInitL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestPopupForm, "testpopupform" );
    _LIT( KTestPfPostLayoutDynInitL, "In PfPostLayoutDynInitL" );
    TestModuleIf().Printf( 0, KTestPopupForm, KTestPfPostLayoutDynInitL );
    // Print to log file
    iLog->Log( KTestPfPostLayoutDynInitL );

    CAknPopupFormExt* popupFormExt = new ( ELeave ) CAknPopupFormExt;
    CleanupStack::PushL( popupFormExt );
    CleanupStack::Pop( popupFormExt );
    popupFormExt->PrepareLC( R_POPUPFORM_DIALOG );

    popupFormExt->DoPostLayoutDynInitL();

    CleanupStack::PopAndDestroy( popupFormExt );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMPopupForm::TestPfSizeChangedL
// -----------------------------------------------------------------------------
//
TInt CTestDOMPopupForm::TestPfSizeChangedL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestPopupForm, "testpopupform" );
    _LIT( KTestPfSizeChanged, "In PfSizeChanged" );
    TestModuleIf().Printf( 0, KTestPopupForm, KTestPfSizeChanged );
    // Print to log file
    iLog->Log( KTestPfSizeChanged );

    CAknPopupFormExt* popupFormExt = new ( ELeave ) CAknPopupFormExt;
    CleanupStack::PushL( popupFormExt );
    CleanupStack::Pop( popupFormExt );
    popupFormExt->PrepareLC( R_POPUPFORM_DIALOG );

    popupFormExt->DoSizeChanged();

    CleanupStack::PopAndDestroy( popupFormExt );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMPopupForm::TestPfOfferKeyEventL
// -----------------------------------------------------------------------------
//
TInt CTestDOMPopupForm::TestPfOfferKeyEventL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestPopupForm, "testpopupform" );
    _LIT( KTestPfOfferKeyEventL, "In PfOfferKeyEventL" );
    TestModuleIf().Printf( 0, KTestPopupForm, KTestPfOfferKeyEventL );
    // Print to log file
    iLog->Log( KTestPfOfferKeyEventL );

    CAknPopupFormExt* popupFormExt = new ( ELeave ) CAknPopupFormExt;
    CleanupStack::PushL( popupFormExt );
    CleanupStack::Pop( popupFormExt );
    popupFormExt->PrepareLC( R_POPUPFORM_DIALOG );

    TKeyEvent keyEvent;
    keyEvent.iScanCode = EStdKeyEnter;
    TKeyResponse keyResponse = popupFormExt->DoOfferKeyEventL( keyEvent, EEventKey );
    STIF_ASSERT_TRUE( keyResponse == EKeyWasNotConsumed );

    CleanupStack::PopAndDestroy( popupFormExt );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMPopupForm::TestPfHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestDOMPopupForm::TestPfHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestPopupForm, "testpopupform" );
    _LIT( KTestPfHandlePointerEventL, "In PfHandlePointerEventL" );
    TestModuleIf().Printf( 0, KTestPopupForm, KTestPfHandlePointerEventL );
    // Print to log file
    iLog->Log( KTestPfHandlePointerEventL );

    CAknPopupFormExt* popupFormExt = new ( ELeave ) CAknPopupFormExt;
    CleanupStack::PushL( popupFormExt );
    CleanupStack::Pop( popupFormExt );
    popupFormExt->PrepareLC( R_POPUPFORM_DIALOG );

    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Up;
    event.iModifiers = 0;
    TPoint eventPos( KEventPointX, KEventPointY );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;

    popupFormExt->DoHandlePointerEventL( event );

    CleanupStack::PopAndDestroy( popupFormExt );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMPopupForm::TestPfInsertControlL
// -----------------------------------------------------------------------------
//
TInt CTestDOMPopupForm::TestPfInsertControlL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestPopupForm, "testpopupform" );
    _LIT( KTestPfInsertControlL, "In PfInsertControlL" );
    TestModuleIf().Printf( 0, KTestPopupForm, KTestPfInsertControlL );
    // Print to log file
    iLog->Log( KTestPfInsertControlL );

    CAknPopupForm* popupForm = CAknPopupForm::NewL();
    CleanupStack::PushL( popupForm );
    CleanupStack::Pop( popupForm );
    popupForm->PrepareLC( R_POPUPFORM_DIALOG );

    popupForm->InsertControlL( 0, R_POPUPFORM_DLG_LINE );

    CleanupStack::PopAndDestroy( popupForm );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMPopupForm::TestPfDeleteControlWithIntL
// -----------------------------------------------------------------------------
//
TInt CTestDOMPopupForm::TestPfDeleteControlWithIntL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestPopupForm, "testpopupform" );
    _LIT( KTestPfDeleteControlWithInt, "In PfDeleteControlWithInt" );
    TestModuleIf().Printf( 0, KTestPopupForm, KTestPfDeleteControlWithInt );
    // Print to log file
    iLog->Log( KTestPfDeleteControlWithInt );

    CAknPopupForm* popupForm = CAknPopupForm::NewL();
    CleanupStack::PushL( popupForm );
    CleanupStack::Pop( popupForm );
    popupForm->PrepareLC( R_POPUPFORM_DIALOG );

    popupForm->DeleteControl( EPopupFormUnknown );

    CleanupStack::PopAndDestroy( popupForm );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMPopupForm::TestPfTextIsScrollableL
// -----------------------------------------------------------------------------
//
TInt CTestDOMPopupForm::TestPfTextIsScrollableL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestPopupForm, "testpopupform" );
    _LIT( KTestPfTextIsScrollable, "In PfTextIsScrollable" );
    TestModuleIf().Printf( 0, KTestPopupForm, KTestPfTextIsScrollable );
    // Print to log file
    iLog->Log( KTestPfTextIsScrollable );

    CAknPopupForm* popupForm = CAknPopupForm::NewL();
    CleanupStack::PushL( popupForm );
    CleanupStack::Pop( popupForm );
    popupForm->PrepareLC( R_POPUPFORM_DIALOG );

    TBool scrollable = popupForm->TextIsScrollable();
    STIF_ASSERT_FALSE( scrollable );

    CleanupStack::PopAndDestroy( popupForm );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMPopupForm::TestPfFlagsL
// -----------------------------------------------------------------------------
//
TInt CTestDOMPopupForm::TestPfFlagsL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestPopupForm, "testpopupform" );
    _LIT( KTestPfFlags, "In PfFlags" );
    TestModuleIf().Printf( 0, KTestPopupForm, KTestPfFlags );
    // Print to log file
    iLog->Log( KTestPfFlags );

    CAknPopupForm* popupForm = CAknPopupForm::NewL();
    CleanupStack::PushL( popupForm );
    CleanupStack::Pop( popupForm );
    popupForm->PrepareLC( R_POPUPFORM_DIALOG );

    TBitFlags flags = popupForm->Flags();
    TBitFlags flag;
    flag.iFlags = 0;
    STIF_ASSERT_TRUE( flag == flags );

    CleanupStack::PopAndDestroy( popupForm );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMPopupForm::TestPfGetControlL
// -----------------------------------------------------------------------------
//
TInt CTestDOMPopupForm::TestPfGetControlL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestPopupForm, "testpopupform" );
    _LIT( KTestPfGetControl, "In PfGetControl" );
    TestModuleIf().Printf( 0, KTestPopupForm, KTestPfGetControl );
    // Print to log file
    iLog->Log( KTestPfGetControl );

    CAknPopupForm* popupForm = CAknPopupForm::NewL();
    CleanupStack::PushL( popupForm );
    CleanupStack::Pop( popupForm );
    popupForm->PrepareLC( R_POPUPFORM_DIALOG );

    CEikCaptionedControl* control = popupForm->GetControlByControlTypeL( EPopupFormUnknown );
    STIF_ASSERT_NULL( control );

    CleanupStack::PopAndDestroy( popupForm );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMPopupForm::TestPfDeleteControlWithCtrlL
// -----------------------------------------------------------------------------
//
TInt CTestDOMPopupForm::TestPfDeleteControlWithCtrlL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestPopupForm, "testpopupform" );
    _LIT( KTestPfDeleteControlWithCtrl, "In PfDeleteControlWithCtrl" );
    TestModuleIf().Printf( 0, KTestPopupForm, KTestPfDeleteControlWithCtrl );
    // Print to log file
    iLog->Log( KTestPfDeleteControlWithCtrl );

    CAknPopupForm* popupForm = CAknPopupForm::NewL();
    CleanupStack::PushL( popupForm );
    CleanupStack::Pop( popupForm );
    popupForm->PrepareLC( R_POPUPFORM_DIALOG );

    popupForm->DeleteControl( EPopupFormUnknown );

    CleanupStack::PopAndDestroy( popupForm );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMPopupForm::TestPfSetWaitIndexL
// -----------------------------------------------------------------------------
//
TInt CTestDOMPopupForm::TestPfSetWaitIndexL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestPopupForm, "testpopupform" );
    _LIT( KTestPfSetWaitIndex, "In PfSetWaitIndex" );
    TestModuleIf().Printf( 0, KTestPopupForm, KTestPfSetWaitIndex );
    // Print to log file
    iLog->Log( KTestPfSetWaitIndex );

    CAknPopupForm* popupForm = CAknPopupForm::NewL();
    CleanupStack::PushL( popupForm );
    CleanupStack::Pop( popupForm );
    popupForm->PrepareLC( R_POPUPFORM_DIALOG );

    TInt index = 0;
    popupForm->SetWaitAnimationResourceIndex( index );

    CleanupStack::PopAndDestroy( popupForm );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMPopupForm::TestPfInsertControlWithBoolL
// -----------------------------------------------------------------------------
//
TInt CTestDOMPopupForm::TestPfInsertControlWithBoolL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestPopupForm, "testpopupform" );
    _LIT( KTestPfInsertControlWithBoolL, "In PfInsertControlWithBoolL" );
    TestModuleIf().Printf( 0, KTestPopupForm, KTestPfInsertControlWithBoolL );
    // Print to log file
    iLog->Log( KTestPfInsertControlWithBoolL );

    CAknPopupForm* popupForm = CAknPopupForm::NewL();
    CleanupStack::PushL( popupForm );
    CleanupStack::Pop( popupForm );
    popupForm->PrepareLC( R_POPUPFORM_DIALOG );

    popupForm->InsertControlL( 0, R_POPUPFORM_DLG_LINE, EFalse );

    CleanupStack::PopAndDestroy( popupForm );
    return KErrNone;

    }


//  [End of File]
