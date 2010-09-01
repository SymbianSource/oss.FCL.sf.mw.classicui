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
* Description:  misc_controls_api
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <eiktbar.h>
#include <barsread.h>
#include <testsdkmisccontrols.rsg>
#include <eikbutb.h> 
#include <s32mem.h>
#include "testsdkmisccontrols.h"
#include "testsdktbarsubclass.h"
#include "testsdktbarprotectedclass.h"


// ============================ MEMBER FUNCTIONS ===============================


// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestTBConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestTBConstructorL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestTBConstructorL, "In TestTBConstructorL" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestTBConstructorL );
    // Print to log file
    iLog->Log( KTestTBConstructorL );

    
    iToolBar = new (ELeave) CEikToolBar();
    STIF_ASSERT_NOT_NULL( iToolBar );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestTBDestructor
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestTBDestructor( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestTBDestructor, "In TestTBDestructor" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestTBDestructor );
    // Print to log file
    iLog->Log( KTestTBDestructor );

    delete iToolBar;
    iToolBar = NULL;
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestTBConstructL
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestTBConstructL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestTBConstructL, "In TestTBConstructL" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestTBConstructL );
    // Print to log file
    iLog->Log( KTestTBConstructL );
    CTestSubToolBar* subToolBar = new ( ELeave ) CTestSubToolBar();
    CleanupStack::PushL( subToolBar );
    TRect rect( 5, 5, 50, 50 );
    TBool err = KErrNone;
    TRAP( err, iToolBar->ConstructL( subToolBar, R_EIK_TOOL_BAR, rect ) );
    CleanupStack::PopAndDestroy( subToolBar );
    return err;
    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestTBStaticConstructL
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestTBStaticConstructL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestTBStaticConstructL, "In TestTBStaticConstructL" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestTBStaticConstructL );
    // Print to log file
    iLog->Log( KTestTBStaticConstructL );
    CTestSubToolBar* subToolBar = new ( ELeave ) CTestSubToolBar();
    CleanupStack::PushL( subToolBar );

    TBool err = KErrNone;
    TRAP( err, iToolBar->StaticConstructL( subToolBar, R_EIK_TOOL_BAR ) );
    CleanupStack::PopAndDestroy( subToolBar );
    return err;
    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestTBSetCommandObserverL
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestTBSetCommandObserverL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestTBSetCommandObserverL, "In TestTBSetCommandObserverL" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestTBSetCommandObserverL );
    // Print to log file
    iLog->Log( KTestTBSetCommandObserverL );
    CTestSubToolBar* subToolBar = new ( ELeave ) CTestSubToolBar();
    CleanupStack::PushL( subToolBar );

    iToolBar->SetCommandObserver( subToolBar );
    CleanupStack::PopAndDestroy( subToolBar );
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestTBCoordinateButtons
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestTBCoordinateButtonsL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestTBCoordinateButtonsL, "In TestTBCoordinateButtonsL" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestTBCoordinateButtonsL );
    // Print to log file
    iLog->Log( KTestTBCoordinateButtonsL );

    TEikButtonCoordinator* buttonCoordinator = new( ELeave ) TEikButtonCoordinator;
    CleanupStack::PushL( buttonCoordinator );
    TInt cId = 1;
    TInt count = 0;
    iToolBar->CoordinateButtons( cId, count, buttonCoordinator );
    CleanupStack::PopAndDestroy( buttonCoordinator );
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestTBSetButtonStateOnL
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestTBSetButtonStateOnL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestTBSetButtonStateOnL, "In TestTBSetButtonStateOnL" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestTBSetButtonStateOnL );
    // Print to log file
    iLog->Log( KTestTBSetButtonStateOnL );
    CEikButtonBase* buttonBase = new( ELeave ) CEikButtonBase();
    TEikGroupControl ctrl;
    ctrl.iControl = buttonBase;
    ctrl.iId = 2;
    iToolBar->AddControlL( ctrl );
    TInt cId = 2;
    iToolBar->SetButtonStateOn( cId, EFalse );

    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestTBDelayActivation
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestTBDelayActivation( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestTBDelayActivation, "In TestTBDelayActivation" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestTBDelayActivation );
    // Print to log file
    iLog->Log( KTestTBDelayActivation );

    TBool delayActivation = iToolBar->DelayActivation();

    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestTBConstructFromResourceL
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestTBConstructFromResourceL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestTBConstructFromResourceL, "In TestTBConstructFromResourceL" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestTBConstructFromResourceL );
    // Print to log file
    iLog->Log( KTestTBConstructFromResourceL );
    TResourceReader reader;
    TBool err = KErrNone;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_EIK_TOOL_BAR );    
    TRAP( err, iToolBar->ConstructFromResourceL( reader ) );
    CleanupStack::PopAndDestroy();  

    return err;
    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestTBSetDimmed
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestTBSetDimmed( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestTBSetDimmed, "In TestTBSetDimmed" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestTBSetDimmed );
    // Print to log file
    iLog->Log( KTestTBSetDimmed );
    TBool dimmed = ETrue;

    iToolBar->SetDimmed( dimmed );

    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestTBGetColorUseListL
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestTBGetColorUseListL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestTBGetColorUseListL, "In TestTBGetColorUseListL" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestTBGetColorUseListL );
    // Print to log file
    iLog->Log( KTestTBGetColorUseListL );
    TBool err = KErrNone;
    CArrayFixFlat<TCoeColorUse>* colorUseList = new( ELeave ) 
           CArrayFixFlat<TCoeColorUse>( 4 );
    CleanupStack::PushL( colorUseList );
    TRAP( err, iToolBar->GetColorUseListL( *colorUseList ) );
    colorUseList->Reset();
    CleanupStack::PopAndDestroy( colorUseList );
    return err;
    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestTBHandleResourceChange
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestTBHandleResourceChange( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestTBHandleResourceChange, "In TestTBHandleResourceChange" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestTBHandleResourceChange );
    // Print to log file
    iLog->Log( KTestTBHandleResourceChange );
    TInt type = 0;
    iToolBar->HandleResourceChange( type );

    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestTBHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestTBHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestTBHandlePointerEventL, "In TestTBHandlePointerEventL" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestTBHandlePointerEventL );
    // Print to log file
    iLog->Log( KTestTBHandlePointerEventL );
    TPointerEvent pointEvent;
    TBool err = KErrNone;
    pointEvent.iType = TPointerEvent::EButton1Down;  
    TRAP( err, iToolBar->HandlePointerEventL( pointEvent ) );

    return err;
    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestTBAddControlL
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestTBAddControlL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestTBAddControlL, "In TestTBAddControlL" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestTBAddControlL );
    // Print to log file
    iLog->Log( KTestTBAddControlL );
    TInt cId = 1;
    TBool err = KErrNone;
    CCoeControl* coeControl = new( ELeave ) CCoeControl();
    CleanupStack::PushL( coeControl );
    TRAP( err, iToolBar->AddControlL( coeControl, cId ) );
    CleanupStack::Pop( coeControl );
    return err;
    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestTBAddControlWithGroupL
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestTBAddControlWithGroupL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestTBAddControlWithGroupL, "In TestTBAddControlWithGroupL" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestTBAddControlWithGroupL );
    // Print to log file
    iLog->Log( KTestTBAddControlWithGroupL );
    CEikButtonBase* buttonBase = new( ELeave ) CEikButtonBase();
    CleanupStack::PushL( buttonBase );
    TEikGroupControl ctrl;
    TBool err = KErrNone;
    ctrl.iControl = buttonBase;
    ctrl.iId = 2;
    TRAP( err, iToolBar->AddControlL( ctrl ) );
    CleanupStack::Pop( buttonBase );
    return err;
    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestTBSetBoundingRect
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestTBSetBoundingRect( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestTBSetBoundingRect, "In TestTBSetBoundingRect" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestTBSetBoundingRect );
    // Print to log file
    iLog->Log( KTestTBSetBoundingRect );
    TRect rect( 5, 5, 50, 50 );
    iToolBar->SetBoundingRect( rect );
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestTBReduceRect
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestTBReduceRect( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestTBReduceRect, "In TestTBReduceRect" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestTBReduceRect );
    // Print to log file
    iLog->Log( KTestTBReduceRect );
    TRect rect( 5, 5, 50, 50 );
    iToolBar->ReduceRect( rect );
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestTBWriteInternalStateL
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestTBWriteInternalStateL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestTBWriteInternalStateL, "In TestTBWriteInternalStateL" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestTBWriteInternalStateL );
    // Print to log file
    iLog->Log( KTestTBWriteInternalStateL );
    CBufFlat* buf = CBufFlat::NewL( 200 );
    CleanupStack::PushL( buf );
    
    RBufWriteStream stream;
    TBool err = KErrNone;
    stream.Open( *buf );
    CTestToolBar* toolBar = new ( ELeave ) CTestToolBar();
    CleanupStack::PushL( toolBar );
    TRect rect( 5, 5, 50, 50 );
    CTestSubToolBar* subToolBar = new ( ELeave ) CTestSubToolBar();
    CleanupStack::PushL( subToolBar );
    toolBar->ConstructL( subToolBar, R_EIK_TOOL_BAR, rect );
    TRAP( err, toolBar->WriteInternalStateL( stream ) );
    
    stream.Close();
    CleanupStack::PopAndDestroy( 3 );
    return err;
    }
