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
* Description:  test akntitle.h
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>

#include <barsread.h>
#include <eikenv.h>
#include <fbs.h>
#include <w32std.h>
#include <akndef.h>
#include <coecntrl.h>
#include <avkon.mbg>
#include <eikimage.h> 
#include <akniconutils.h> 

#include <testsdktitlepane.rsg>
#include "testsdktitlepane.h"
#include "testsdktitlepanecontrol.h"
#include "testsdktitlepaneext.h"

// CONSTANTS
const TInt KBufSize = 64;
const TInt KPointX = 10;
const TInt KPointY = 30;


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKTitlePane::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void CTestSDKTitlePane::Delete() 
    {
    }

// -----------------------------------------------------------------------------
// CTestSDKTitlePane::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestSDKTitlePane::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "testDefaultConstruct",
                CTestSDKTitlePane::TestTitlePaneDefaultConstructL ),
        ENTRY( "testConstructL", CTestSDKTitlePane::TestTitlePaneConstructL ),
        ENTRY( "testConstructFromResourceL",
                CTestSDKTitlePane::TestTitlePaneConstructFromResourceL ),
        ENTRY( "testSetTextL", CTestSDKTitlePane::TestTitlePaneSetTextL ),
        ENTRY( "testTextL", CTestSDKTitlePane::TestTitlePaneTextL ),
        ENTRY( "testSetPictureL", CTestSDKTitlePane::TestTitlePaneSetPictureL ),
        ENTRY( "testSetPictureFromFileL",
                CTestSDKTitlePane::TestTitlePaneSetPictureFromFileL ),
        ENTRY( "testSetSmallPictureL",
                CTestSDKTitlePane::TestTitlePaneSetSmallPictureL ),
        ENTRY( "testSetFromResourceL",
                CTestSDKTitlePane::TestTitlePaneSetFromResourceL ),
        ENTRY( "testSetTextToDefaultL",
                CTestSDKTitlePane::TestTitlePaneSetTextToDefaultL ),
        ENTRY( "testMaxNumberOfVisibleTextRowsL",
                CTestSDKTitlePane::TestTitlePaneMaxNumberOfVisibleTextRowsL ),
        ENTRY( "testSetNumberOfVisibleTextRowsL",
                CTestSDKTitlePane::TestTitlePaneSetNumberOfVisibleTextRowsL ),
        ENTRY( "testPrepareContextL",
                CTestSDKTitlePane::TestTitlePanePrepareContextL ),
        ENTRY( "testSizeChangedL",CTestSDKTitlePane::TestTitlePaneSizeChangedL ),
        ENTRY( "testPositionChangedL",
                CTestSDKTitlePane::TestTitlePanePositionChangedL ),
        ENTRY( "testHandleResourceChangeL",
                CTestSDKTitlePane::TestTitlePaneHandleResourceChangeL ),
        ENTRY( "testCountComponentControlsL",
                CTestSDKTitlePane::TestTitlePaneCountComponentControlsL ),
        ENTRY( "testComponentControlL",
                CTestSDKTitlePane::TestTitlePaneComponentControlL ),
        ENTRY( "testHandlePointerEventL",
                CTestSDKTitlePane::TestTitlePaneHandlePointerEventL ),
        ENTRY( "testSetTitlePaneObserverL",
                CTestSDKTitlePane::TestTitlePaneSetTitlePaneObserverL ),

        // [test cases entries]

        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// CTestSDKTitlePane::TestTitlePaneDefaultConstructL
// -----------------------------------------------------------------------------
//
TInt CTestSDKTitlePane::TestTitlePaneDefaultConstructL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestSDKTitlePane, "testsdktitlepane" );
    _LIT( KDefaultConstruct, "In DefaultConstruct" );
    TestModuleIf().Printf( 0, KTestSDKTitlePane, KDefaultConstruct );
    // Print to log file
    iLog->Log( KDefaultConstruct );

    CAknTitlePane* titlePane = new ( ELeave ) CAknTitlePane;
    CleanupStack::PushL( titlePane );
    STIF_ASSERT_NOT_NULL( titlePane );
    CleanupStack::PopAndDestroy( titlePane );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKTitlePane::TestTitlePaneConstructL
// -----------------------------------------------------------------------------
//
TInt CTestSDKTitlePane::TestTitlePaneConstructL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestSDKTitlePane, "testsdktitlepane" );
    _LIT( KConstruct, "In Construct" );
    TestModuleIf().Printf( 0, KTestSDKTitlePane, KConstruct );
    // Print to log file
    iLog->Log( KConstruct );

    CAknTitlePane* titlePane = new ( ELeave ) CAknTitlePane;
    CleanupStack::PushL( titlePane );
    titlePane->ConstructL();
    CleanupStack::PopAndDestroy( titlePane );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKTitlePane::TestTitlePaneConstructFromResourceL
// -----------------------------------------------------------------------------
//
TInt CTestSDKTitlePane::TestTitlePaneConstructFromResourceL(
        CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestSDKTitlePane, "testsdktitlepane" );
    _LIT( KConstructFromResource, "In ConstructFromResource" );
    TestModuleIf().Printf( 0, KTestSDKTitlePane, KConstructFromResource );
    // Print to log file
    iLog->Log( KConstructFromResource );

    CAknTitlePane* titlePane = new ( ELeave ) CAknTitlePane;
    CleanupStack::PushL( titlePane );
    
    TResourceReader resourceReader;
    CEikonEnv::Static()->CreateResourceReaderLC( resourceReader,
            R_TITLEPANE );
    
    titlePane->ConstructFromResourceL( resourceReader );
    
    CleanupStack::PopAndDestroy();
    CleanupStack::PopAndDestroy( titlePane );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKTitlePane::TestTitlePaneSetTextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKTitlePane::TestTitlePaneSetTextL( CStifItemParser& aItem )
    {
    // Print to UI
    _LIT( KTestSDKTitlePane, "testsdktitlepane" );
    _LIT( KSetText, "In SetText" );
    TestModuleIf().Printf( 0, KTestSDKTitlePane, KSetText );
    // Print to log file
    iLog->Log( KSetText );

    TInt num = 0;
    TInt err = aItem.GetNextInt( num );
    if ( err != KErrNone )
        {
        return err;
        }
    
    CAknTitlePane* titlePane = new ( ELeave ) CAknTitlePane;
    CleanupStack::PushL( titlePane );
    titlePane->ConstructL();
    
    switch ( num )
        {
        //test SetTextL function with TDesC param 
        case 1:
            {
            _LIT( KText, "TDesCText" );
            TBufC<KBufSize> text( KText );
            titlePane->SetTextL( text );
            
            break;
            }
        //test SetText function with HBufC param
        case 2:
            {
            _LIT( KText, "HBufCText" );
            HBufC* text = HBufC::NewL( KBufSize );
            *text = KText;
            titlePane->SetText( text );
            
            break;
            }
            
        //test SetTextL function with TDesC param and scoll
        case 3:
            {
            _LIT( KText, "TDesCText" );
            TBufC<KBufSize> text( KText );
            titlePane->SetTextL( text, ETrue );
            
            break;
            }
        //test SetTextL function with HBufC param and scoll
        case 4:
            {
            _LIT( KText, "HBufCText" );
            HBufC* text = HBufC::NewL( KBufSize );
            *text = KText;
            titlePane->SetText( text, ETrue );
            
            break;
            }
        default:
            CleanupStack::PopAndDestroy( titlePane );
            return KErrNotSupported;
        }

    CleanupStack::PopAndDestroy( titlePane );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKTitlePane::TestTitlePaneTextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKTitlePane::TestTitlePaneTextL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestSDKTitlePane, "testsdktitlepane" );
    _LIT( KText, "In Text" );
    TestModuleIf().Printf( 0, KTestSDKTitlePane, KText );
    // Print to log file
    iLog->Log( KText );

    CAknTitlePane* titlePane = new ( ELeave ) CAknTitlePane;
    CleanupStack::PushL( titlePane );
    titlePane->ConstructL();
    
    _LIT( KTitlePaneText, "TitlePane" );
    TBufC<KBufSize> titlePaneText( KTitlePaneText );
    titlePane->SetTextL( titlePaneText );
    TBufC<KBufSize> text = *( titlePane->Text() );
    STIF_ASSERT_EQUALS( titlePaneText, text );
    
    CleanupStack::PopAndDestroy( titlePane );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKTitlePane::TestTitlePaneSetPictureL
// -----------------------------------------------------------------------------
//
TInt CTestSDKTitlePane::TestTitlePaneSetPictureL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestSDKTitlePane, "testsdktitlepane" );
    _LIT( KSetPicture, "In SetPicture" );
    TestModuleIf().Printf( 0, KTestSDKTitlePane, KSetPicture );
    // Print to log file
    iLog->Log( KSetPicture );

    CAknTitlePane* titlePane = new ( ELeave ) CAknTitlePane;
    CleanupStack::PushL( titlePane );
    titlePane->ConstructL();
    
    _LIT( KBitmapFile, "\\resource\\apps\\avkon2.mbm" );
    CFbsBitmap* bitmap = NULL;
    CFbsBitmap* mask = NULL;
    AknIconUtils::CreateIconL( bitmap, mask, KBitmapFile,
            EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
    
    titlePane->SetPicture( bitmap, mask );
    
    CleanupStack::PopAndDestroy( titlePane );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKTitlePane::TestTitlePaneSetPictureFromFileL
// -----------------------------------------------------------------------------
//
TInt CTestSDKTitlePane::TestTitlePaneSetPictureFromFileL(
        CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestSDKTitlePane, "testsdktitlepane" );
    _LIT( KSetPicture, "In SetPicture" );
    TestModuleIf().Printf( 0, KTestSDKTitlePane, KSetPicture );
    // Print to log file
    iLog->Log( KSetPicture );

    CAknTitlePane* titlePane = new ( ELeave ) CAknTitlePane;
    CleanupStack::PushL( titlePane );
    titlePane->ConstructL();
    
    _LIT( KBitmapPath, "\\resource\\apps\\avkon2.mbm" );
    titlePane->SetPictureFromFileL( KBitmapPath,
            EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
    
    CleanupStack::PopAndDestroy( titlePane );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKTitlePane::TestTitlePaneSetSmallPictureL
// -----------------------------------------------------------------------------
//
TInt CTestSDKTitlePane::TestTitlePaneSetSmallPictureL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestSDKTitlePane, "testsdktitlepane" );
    _LIT( KSetSmallPicture, "In SetSmallPicture" );
    TestModuleIf().Printf( 0, KTestSDKTitlePane, KSetSmallPicture );
    // Print to log file
    iLog->Log( KSetSmallPicture );

    CAknTitlePane* titlePane = new ( ELeave ) CAknTitlePane;
    CleanupStack::PushL( titlePane );
    titlePane->ConstructL();
    
    _LIT( KBitmapFile, "\\resource\\apps\\avkon2.mbm" );
    CFbsBitmap* bitmap = NULL;
    CFbsBitmap* mask = NULL;
    AknIconUtils::CreateIconL( bitmap, mask, KBitmapFile,
            EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
    
    titlePane->SetSmallPicture( bitmap, mask, ETrue );
    
    CleanupStack::PopAndDestroy( titlePane );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKTitlePane::TestTitlePaneSetFromResourceL
// -----------------------------------------------------------------------------
//
TInt CTestSDKTitlePane::TestTitlePaneSetFromResourceL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestSDKTitlePane, "testsdktitlepane" );
    _LIT( KSetFromResource, "In SetFromResource" );
    TestModuleIf().Printf( 0, KTestSDKTitlePane, KSetFromResource );
    // Print to log file
    iLog->Log( KSetFromResource );

    CAknTitlePane* titlePane = new ( ELeave ) CAknTitlePane;
    CleanupStack::PushL( titlePane );
    titlePane->ConstructL();
    
    TResourceReader resourceReader;
    CEikonEnv::Static()->CreateResourceReaderLC( resourceReader,
            R_TITLEPANE );
    titlePane->SetFromResourceL( resourceReader );
    
    CleanupStack::PopAndDestroy();
    CleanupStack::PopAndDestroy( titlePane );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKTitlePane::TestTitlePaneSetTextToDefaultL
// -----------------------------------------------------------------------------
//
TInt CTestSDKTitlePane::TestTitlePaneSetTextToDefaultL(
        CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestSDKTitlePane, "testsdktitlepane" );
    _LIT( KSetTextToDefault, "In SetTextToDefault" );
    TestModuleIf().Printf( 0, KTestSDKTitlePane, KSetTextToDefault );
    // Print to log file
    iLog->Log( KSetTextToDefault );

    CAknTitlePane* titlePane = new ( ELeave ) CAknTitlePane;
    CleanupStack::PushL( titlePane );
    titlePane->ConstructL();
    
    titlePane->SetTextToDefaultL();
    
    CleanupStack::PopAndDestroy( titlePane );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKTitlePane::TestTitlePaneMaxNumberOfVisibleTextRowsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKTitlePane::TestTitlePaneMaxNumberOfVisibleTextRowsL(
        CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestSDKTitlePane, "testsdktitlepane" );
    _LIT( KMaxNumberOfVisibleTextRows, "In MaxNumberOfVisibleTextRows" );
    TestModuleIf().Printf( 0, KTestSDKTitlePane, KMaxNumberOfVisibleTextRows );
    // Print to log file
    iLog->Log( KMaxNumberOfVisibleTextRows );

    CAknTitlePane* titlePane = new ( ELeave ) CAknTitlePane;
    CleanupStack::PushL( titlePane );
    titlePane->ConstructL();
    
    TInt rows = titlePane->MaxNumberOfVisibleTextRows();
    TInt maxRows = 1;
    STIF_ASSERT_EQUALS( maxRows, rows );
    
    CleanupStack::PopAndDestroy( titlePane );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKTitlePane::TestTitlePaneSetNumberOfVisibleTextRowsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKTitlePane::TestTitlePaneSetNumberOfVisibleTextRowsL(
        CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestSDKTitlePane, "testsdktitlepane" );
    _LIT( KSetNumberOfVisibleTextRows, "In SetNumberOfVisibleTextRows" );
    TestModuleIf().Printf( 0, KTestSDKTitlePane, KSetNumberOfVisibleTextRows );
    // Print to log file
    iLog->Log( KSetNumberOfVisibleTextRows );

    CAknTitlePane* titlePane = new ( ELeave ) CAknTitlePane;
    CleanupStack::PushL( titlePane );
    titlePane->ConstructL();
    
    TInt rows = 1;
    titlePane->SetNumberOfVisibleTextRows( rows );
    
    CleanupStack::PopAndDestroy( titlePane );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKTitlePane::TestTitlePanePrepareContextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKTitlePane::TestTitlePanePrepareContextL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestSDKTitlePane, "testsdktitlepane" );
    _LIT( KPrepareContext, "In PrepareContext" );
    TestModuleIf().Printf( 0, KTestSDKTitlePane, KPrepareContext );
    // Print to log file
    iLog->Log( KPrepareContext );

    CTestTitlePane* titlePane = new ( ELeave ) CTestTitlePane;
    CleanupStack::PushL( titlePane );
    titlePane->ConstructL();
    CTestTitlePaneControl* testControl = CTestTitlePaneControl::NewL();
    CleanupStack::PushL( testControl );
    testControl->DoActivateGc();
    titlePane->SetContainerWindowL( *testControl );

    CWindowGc& gc = testControl->SystemGc();
    titlePane->PrepareContext( gc );

    testControl->DoDeactivateGc();
    CleanupStack::PopAndDestroy( testControl );
    CleanupStack::PopAndDestroy( titlePane );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKTitlePane::TestTitlePaneSizeChangedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKTitlePane::TestTitlePaneSizeChangedL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestSDKTitlePane, "testsdktitlepane" );
    _LIT( KSizeChanged, "In SizeChanged" );
    TestModuleIf().Printf( 0, KTestSDKTitlePane, KSizeChanged );
    // Print to log file
    iLog->Log( KSizeChanged );

    CTestTitlePane* titlePane = new ( ELeave ) CTestTitlePane;
    CleanupStack::PushL( titlePane );
    titlePane->ConstructL();
    titlePane->DoSizeChanged();
    
    CleanupStack::PopAndDestroy( titlePane );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKTitlePane::TestTitlePanePositionChangedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKTitlePane::TestTitlePanePositionChangedL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestSDKTitlePane, "testsdktitlepane" );
    _LIT( KPositionChanged, "In PositionChanged" );
    TestModuleIf().Printf( 0, KTestSDKTitlePane, KPositionChanged );
    // Print to log file
    iLog->Log( KPositionChanged );

    CTestTitlePane* titlePane = new ( ELeave ) CTestTitlePane;
    CleanupStack::PushL( titlePane );
    titlePane->ConstructL();
    
    titlePane->DoPositionChanged();
    
    CleanupStack::PopAndDestroy( titlePane );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKTitlePane::TestTitlePaneHandleResourceChangeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKTitlePane::TestTitlePaneHandleResourceChangeL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestSDKTitlePane, "testsdktitlepane" );
    _LIT( KHandleResourceChange, "In HandleResourceChange" );
    TestModuleIf().Printf( 0, KTestSDKTitlePane, KHandleResourceChange );
    // Print to log file
    iLog->Log( KHandleResourceChange );

    CTestTitlePane* titlePane = new ( ELeave ) CTestTitlePane;
    CleanupStack::PushL( titlePane );
    titlePane->ConstructL();
    
    TInt type = KEikDynamicLayoutVariantSwitch;
    titlePane->DoHandleResourceChange( type );
    
    CleanupStack::PopAndDestroy( titlePane );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKTitlePane::TestTitlePaneCountComponentControlsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKTitlePane::TestTitlePaneCountComponentControlsL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestSDKTitlePane, "testsdktitlepane" );
    _LIT( KCountComponentControls, "In CountComponentControls" );
    TestModuleIf().Printf( 0, KTestSDKTitlePane, KCountComponentControls );
    // Print to log file
    iLog->Log( KCountComponentControls );

    CTestTitlePane* titlePane = new ( ELeave ) CTestTitlePane;
    CleanupStack::PushL( titlePane );
    titlePane->ConstructL();
    
    titlePane->DoCountComponentControls();
    
    CleanupStack::PopAndDestroy( titlePane );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKTitlePane::TestTitlePaneComponentControlsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKTitlePane::TestTitlePaneComponentControlL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestSDKTitlePane, "testsdktitlepane" );
    _LIT( KComponentControl, "In ComponentControl" );
    TestModuleIf().Printf( 0, KTestSDKTitlePane, KComponentControl );
    // Print to log file
    iLog->Log( KComponentControl );

    CTestTitlePane* titlePane = new ( ELeave ) CTestTitlePane;
    CleanupStack::PushL( titlePane );
    titlePane->ConstructL();
    
    TInt index = 1;
    titlePane->DoComponentControl( index );
    
    CleanupStack::PopAndDestroy( titlePane );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKTitlePane::TestTitlePaneHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKTitlePane::TestTitlePaneHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestSDKTitlePane, "testsdktitlepane" );
    _LIT( KHandlePointerEvent, "In HandlePointerEvent" );
    TestModuleIf().Printf( 0, KTestSDKTitlePane, KHandlePointerEvent );
    // Print to log file
    iLog->Log( KHandlePointerEvent );

    CAknTitlePane* titlePane = new ( ELeave ) CAknTitlePane;
    CleanupStack::PushL( titlePane );
    titlePane->ConstructL();
    
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( KPointX, KPointY );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    
    titlePane->HandlePointerEventL( event );

    CleanupStack::PopAndDestroy( titlePane );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKTitlePane::TestTitlePaneSetTitlePaneObserverL
// -----------------------------------------------------------------------------
//
TInt CTestSDKTitlePane::TestTitlePaneSetTitlePaneObserverL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestSDKTitlePane, "testsdktitlepane" );
    _LIT( KSetTitlePaneObserver, "In SetTitlePaneObserver" );
    TestModuleIf().Printf( 0, KTestSDKTitlePane, KSetTitlePaneObserver );
    // Print to log file
    iLog->Log( KSetTitlePaneObserver );

    CAknTitlePane* titlePane = new ( ELeave ) CAknTitlePane;
    CleanupStack::PushL( titlePane );
    titlePane->ConstructL();
    
    CTestTitlePaneControl* control = CTestTitlePaneControl::NewL();
    CleanupStack::PushL( control );
    titlePane->SetTitlePaneObserver( control );
    
    CleanupStack::PopAndDestroy( control );
    CleanupStack::PopAndDestroy( titlePane );
    return KErrNone;
    }


//  [End of File]
