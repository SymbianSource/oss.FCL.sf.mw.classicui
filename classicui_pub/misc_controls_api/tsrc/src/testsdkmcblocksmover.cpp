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
#include <eikmover.h>
#include <eikenv.h>
#include <testsdkmisccontrols.rsg>
#include <s32mem.h>
#include <barsread.h>
#include "testsdkmisccontrolcontainer.h"
#include "testsdkmisccontrols.h"
#include "testsdkmoverprotectedclass.h"

// ============================ MEMBER FUNCTIONS ===============================
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestEMConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestEMConstructorL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestEMConstructorL, "In TestEMConstructorL" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestEMConstructorL );
    // Print to log file
    iLog->Log( KTestEMConstructorL );
    iMover = new (ELeave) CEikMover();
    STIF_ASSERT_NOT_NULL( iMover );
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestEMDestructor
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestEMDestructor( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestEMDestructor, "In TestEMDestructor" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestEMDestructor );
    // Print to log file
    iLog->Log( KTestEMDestructor );
    delete iMover;
    iMover = NULL;
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestEMSetTextNoL
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestEMSetTextNoL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestEMSetTextNoL, "In TestEMSetTextNoL" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestEMSetTextNoL );
    // Print to log file
    iLog->Log( KTestEMSetTextNoL );
    TBufC<20> statckbuf( KTestEMSetTextNoL );
    HBufC* heapBuf = statckbuf.AllocL();
    iMover->SetText( heapBuf );
    
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestEMSetTextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestEMSetTextL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestEMSetTextL, "In TestEMSetTextL" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestEMSetTextL );
    // Print to log file
    iLog->Log( KTestEMSetTextL );
   
    iMover->SetTextL( KTestEMSetTextL );
    
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestEMSetActive
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestEMSetActive( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestEMSetActive, "In TestEMSetActive" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestEMSetActive );
    // Print to log file
    iLog->Log( KTestEMSetActive );
   
    iMover->SetActive( ETrue );
    
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestEMActive
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestEMActive( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestEMActive, "In TestEMActive" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestEMActive );
    // Print to log file
    iLog->Log( KTestEMActive );
   
    TBool status = iMover->Active();
    
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestEMSetFontL
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestEMSetFontL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestEMSetFontL, "In TestEMSetFontL" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestEMSetFontL );
    // Print to log file
    iLog->Log( KTestEMSetFontL );
    iConsoleContainer = new (ELeave) CMiscControlsContainer(); 

    CEikonEnv* eikEnv = static_cast<CEikonEnv*> ( iConsoleContainer->GetCoeEnv() ); 
    CleanupStack::PushL( eikEnv );
    const CFont* font = eikEnv->TitleFont();
    iMover->SetFont( font );
    CleanupStack::Pop( );
    
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestEMSetTitleLeftMargin
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestEMSetTitleLeftMargin( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestEMSetTitleLeftMargin, "In TestEMSetTitleLeftMargin" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestEMSetTitleLeftMargin );
    // Print to log file
    iLog->Log( KTestEMSetTitleLeftMargin );
    TInt leftMargin = 5;

    iMover->SetTitleLeftMargin( leftMargin );
    
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestEMConstructFromResourceL
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestEMConstructFromResourceL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestEMConstructFromResourceL, "In TestEMConstructFromResourceL" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestEMConstructFromResourceL );
    // Print to log file
    iLog->Log( KTestEMConstructFromResourceL );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( 
            reader, R_EIK_MOVER_DIALOG );
    TBool err = KErrNone;
    TRAP( err, iMover->ConstructFromResourceL( reader ) );
    CleanupStack::PopAndDestroy(); 
    
    return err;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestEMMinimumSize
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestEMMinimumSize( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestEMMinimumSize, "In TestEMMinimumSize" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestEMMinimumSize );
    // Print to log file
    iLog->Log( KTestEMMinimumSize );

    TSize size = iMover->MinimumSize( );

    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestEMSetContainerWindowL
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestEMSetContainerWindowL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestEMSetContainerWindowL, "In TestEMSetContainerWindowL" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestEMSetContainerWindowL );
    // Print to log file
    iLog->Log( KTestEMSetContainerWindowL );
    TBool err = KErrNone;
    iConsoleContainer = new (ELeave) CMiscControlsContainer(); 

    TRAP( err, iMover->SetContainerWindowL( *iConsoleContainer ) );

    return err;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestEMGetColorUseListL
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestEMGetColorUseListL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestEMGetColorUseListL, "In TestEMGetColorUseListL" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestEMGetColorUseListL );
    // Print to log file
    iLog->Log( KTestEMGetColorUseListL );
    TBool err = KErrNone;
    CArrayFixFlat<TCoeColorUse>* colorUseList = new( ELeave ) 
                CArrayFixFlat<TCoeColorUse>( 4 );
    CleanupStack::PushL( colorUseList );
    TRAP( err, iMover->GetColorUseListL( *colorUseList ) );
    colorUseList->Reset();
    CleanupStack::PopAndDestroy( colorUseList );
    return err;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestEMHandleResourceChange
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestEMHandleResourceChange( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestEMHandleResourceChange, "In TestEMHandleResourceChange" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestEMHandleResourceChange );
    // Print to log file
    iLog->Log( KTestEMHandleResourceChange );
    TInt type = 0;
    iMover->HandleResourceChange( type );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestEMHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestEMHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestEMHandlePointerEventL, "In TestEMHandlePointerEventL" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestEMHandlePointerEventL );
    // Print to log file
    iLog->Log( KTestEMHandlePointerEventL );
    TBool err = KErrNone;
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    TRAP( err, iMover->HandlePointerEventL( event ) );

    return err;

    }
// -----------------------------------------------------------------------------
// CTestSDKMiscControls::TestEMWriteInternalStateL
// -----------------------------------------------------------------------------
//
TInt CTestSDKMiscControls::TestEMWriteInternalStateL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdkmisccontrols, "testsdkmisccontrols" );
    _LIT( KTestEMWriteInternalStateL, "In TestEMWriteInternalStateL" );
    TestModuleIf().Printf( 0, Ktestsdkmisccontrols, KTestEMWriteInternalStateL );
    // Print to log file
    iLog->Log( KTestEMWriteInternalStateL );
    TBool err = KErrNone;
    CBufFlat* buf = CBufFlat::NewL( 200 );
    CleanupStack::PushL( buf );
    RBufWriteStream stream;
    stream.Open( *buf );
    CTestMover* testMover = new (ELeave) CTestMover();
    CleanupStack::PushL( testMover );
    TRAP( err, testMover->WriteInternalStateL( stream ) );
    stream.Close();
    CleanupStack::PopAndDestroy( 2 );

    return err;

    }
