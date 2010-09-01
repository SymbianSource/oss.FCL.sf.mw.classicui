/*
* Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:         test case
*
*/









#include <w32std.h>
#include <coecntrl.h>
#include <eikinfo.h>
#include <s32strm.h>
#include <eikenv.h>
#include <eikedwin.h>
#include <bctestappfrm.rsg>
#include "bctesteikenvcase.h"
#include "bctestappfrmcontainer.h"
#include "bctestappfrm.hrh"

// ----------------------------------------------------------------------------
// ctor, do nothing.
// ----------------------------------------------------------------------------
//
CBCTestEikenv::CBCTestEikenv( CBCTestAppFrmContainer* /*aContainer*/ )
    {
    }

// ----------------------------------------------------------------------------
// dtor, do nothing.
// ----------------------------------------------------------------------------
//
CBCTestEikenv::~CBCTestEikenv()
    {
    }

// ----------------------------------------------------------------------------
// symbian 2nd phase ctor.
// ----------------------------------------------------------------------------
//
void CBCTestEikenv::ConstructL()
    {
    BuildScriptL();
    iEikenv = CEikonEnv::Static();
    }

// ----------------------------------------------------------------------------
// symbian NewL.
// ----------------------------------------------------------------------------
//
CBCTestEikenv* CBCTestEikenv::NewL( CBCTestAppFrmContainer* aContainer )
    {
    CBCTestEikenv* self = new ( ELeave ) CBCTestEikenv( aContainer );
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;
    }

// ----------------------------------------------------------------------------
// override the CBCTestCase::RunL, only response to the related command ID.
// ----------------------------------------------------------------------------
//
void CBCTestEikenv::RunL(int aCmd)
    {
    if(aCmd != EBCTestCmdEikenv) return;
    SetupL();
    TestL();
    TearDownL();
    }

// ----------------------------------------------------------------------------
// build the test scripts for this test case.
// ----------------------------------------------------------------------------
//
void CBCTestEikenv::BuildScriptL()
    {
    const TInt scripts[] =
        {
        DELAY(1),        // delay between commands is 1*0.1 seconds = 0.1 seconds
        LeftCBA,
        REP(Down, 5),
        LeftCBA,
        LeftCBA,
        WAIT(20)
        };
    AddTestScriptL(scripts, sizeof(scripts)/sizeof(TInt));
    }

// ----------------------------------------------------------------------------
// test the volume setting page creation api.
// ----------------------------------------------------------------------------
//
void CBCTestEikenv::TestL()
    {
    // Test class CEikonEnv
    // The following are ok.
    iEikenv->Version();
    _LIT( KVersion, "CEikonEnv Version" );
    AssertNotNullL( iEikenv, KVersion );

    iEikenv->Beep();
    _LIT( KBeep, "CEikonEnv Beep." );
    AssertNotNullL( iEikenv, KBeep );

    iEikenv->InfoMsgCancel();
    _LIT( KInfoMsgCancel, "CEikonEnv InfoMsgCancel." );
    AssertNotNullL( iEikenv, KInfoMsgCancel );

    TGulAlignment alignment( EHCenterVCenter );
    TTimeIntervalMicroSeconds32 duration( 1000*1000*5 );
    _LIT( KShowMsgInfo, "Msg Info!" );
    TBuf<16> msgInfo( KShowMsgInfo );
    //VA_LIST list;

    iEikenv->InfoMsg( msgInfo );
    _LIT( KInfoMsg1, "CEikonEnv InfoMsg(&TDesC) method" );
    AssertNotNullL( iEikenv, KInfoMsg1 );

    iEikenv->InfoMsg( R_BCTESTAPPFRM_MSGINFO );
    _LIT( KInfoMsg2, "CEikonEnv InfoMsg(TInt) method" );
    AssertNotNullL( iEikenv, KInfoMsg2 );

    //iEikenv->InfoMsg( R_BCTESTAPPFRM_MSGINFO, list );
    _LIT( KInfoMsg3, "CEikonEnv InfoMsg(TInt, VA_LIST) method" );
    AssertNotNullL( iEikenv, KInfoMsg3 );

    iEikenv->InfoMsgWithDuration( msgInfo, duration );
    _LIT( KInfoMsg4, "InfoMsgWithDuration first method" );
    AssertNotNullL( iEikenv, KInfoMsg4 );

    iEikenv->InfoMsgWithDuration( R_BCTESTAPPFRM_MSGINFO, duration );
    _LIT( KInfoMsg5, "InfoMsgWithDuration second method" );
    AssertNotNullL( iEikenv, KInfoMsg5 );

    //iEikenv->InfoMsgWithDuration( R_BCTESTAPPFRM_MSGINFO, duration, list );
    _LIT( KInfoMsg6, "InfoMsgWithDuration third method" );
    AssertNotNullL( iEikenv, KInfoMsg6 );

    iEikenv->InfoMsgWithAlignment( alignment, msgInfo );
    _LIT( KInfoMsg7, "InfoMsgWithAlignment first method" );
    AssertNotNullL( iEikenv, KInfoMsg7 );

    iEikenv->InfoMsgWithAlignment( alignment, R_BCTESTAPPFRM_MSGINFO );
    _LIT( KInfoMsg8, "InfoMsgWithAlignment second method" );
    AssertNotNullL( iEikenv, KInfoMsg8 );

    //iEikenv->InfoMsgWithAlignment( alignment, R_BCTESTAPPFRM_MSGINFO, list );
    _LIT( KInfoMsg9, "InfoMsgWithAlignment third method" );
    AssertNotNullL( iEikenv, KInfoMsg9 );

    iEikenv->InfoMsgWithAlignmentAndDuration( alignment, msgInfo,duration );
    _LIT( KInfoMsg10, "InfoMsgWithAlignmentAndDuration first method" );
    AssertNotNullL( iEikenv, KInfoMsg10 );

    iEikenv->InfoMsgWithAlignmentAndDuration( alignment,
        R_BCTESTAPPFRM_MSGINFO, duration );
    _LIT( KInfoMsg11, "InfoMsgWithAlignmentAndDuration second method" );
    AssertNotNullL( iEikenv, KInfoMsg11 );

    //iEikenv->InfoMsgWithAlignmentAndDuration( alignment,
    //    R_BCTESTAPPFRM_MSGINFO, duration, list );
    _LIT( KInfoMsg12, "InfoMsgWithAlignmentAndDuration third method" );
    AssertNotNullL( iEikenv, KInfoMsg12 );

    TGulAlignment busyMsgAlignment( EHLeftVCenter );
    TTimeIntervalMicroSeconds32 delaytime( 1000*1000*5 );
    _LIT( KShowBusyMsgInfo, "Busy Msg Info!" );
    TBuf<16> busyMsgInfo( KShowBusyMsgInfo );

    iEikenv->BusyMsgL( busyMsgInfo );
    _LIT( KBusyMsg1, "CEikonEnv BusyMsgL first method." );
    AssertNotNullL( iEikenv, KBusyMsg1 );

    iEikenv->BusyMsgL( busyMsgInfo, busyMsgAlignment );
    _LIT( KBusyMsg2, "CEikonEnv BusyMsgL second method." );
    AssertNotNullL( iEikenv, KBusyMsg2 );

    iEikenv->BusyMsgL( R_BCTESTAPPFRM_BUSYMSGINFO );
    _LIT( KBusyMsg3, "CEikonEnv BusyMsgL third method." );
    AssertNotNullL( iEikenv, KBusyMsg3 );

    iEikenv->BusyMsgL( busyMsgInfo, delaytime );
    _LIT( KBusyMsg4, "CEikonEnv BusyMsgL fourth method." );
    AssertNotNullL( iEikenv, KBusyMsg4 );

    iEikenv->BusyMsgL( busyMsgInfo, busyMsgAlignment, delaytime );
    _LIT( KBusyMsg5, "CEikonEnv BusyMsgL fifth method." );
    AssertNotNullL( iEikenv, KBusyMsg5 );

    iEikenv->BusyMsgL( R_BCTESTAPPFRM_BUSYMSGINFO, delaytime );
    _LIT( KBusyMsg6, "CEikonEnv BusyMsgL sixth method." );
    AssertNotNullL( iEikenv, KBusyMsg6 );

    iEikenv->BusyMsgCancel();
    _LIT( KBusyMsgCancel, "CEikonEnv BusyMsgCancel." );
    AssertNotNullL( iEikenv, KBusyMsgCancel );

    _LIT( KChanges, "CEikonEnv ConfirmLossOfAllChangesL." );
    AssertTrueL( iEikenv->ConfirmLossOfAllChangesL(), KChanges );

    CCharFormatLayer* cLayer = iEikenv->SystemCharFormatLayerL();
    CleanupStack::PushL(cLayer);
    _LIT( KCharFormat, "CEikonEnv SystemCharFormatLayerL." );
    AssertNotNullL( cLayer, KCharFormat );
    CleanupStack::Pop(cLayer);
    cLayer = NULL;

    CParaFormatLayer* pLayer = iEikenv->SystemParaFormatLayerL();
    CleanupStack::PushL(pLayer);
    _LIT( KParaFormat, "CEikonEnv SystemParaFormatLayerL." );
    AssertNotNullL( pLayer, KParaFormat );
    CleanupStack::Pop(pLayer);
    pLayer = NULL;

    iEikenv->UpdateTaskNameL();
    _LIT( KUpdName, "CEikonEnv UpdateTaskNameL." );
    AssertNotNullL( iEikenv, KUpdName );

    //iEikenv->DisplayTaskList();
    //_LIT( KDisplayTaskList, "CEikonEnv DisplayTaskList." );
    //AssertNotNullL( iEikenv, KDisplayTaskList );

    //iEikenv->DismissTaskList();
    //_LIT( KDismissTask, "CEikonEnv DismissTaskList." );
    //AssertNotNullL( iEikenv, KDismissTask );

    CParaFormatLayer* paraLayer = iEikenv->NewDefaultParaFormatLayerL();
    CleanupStack::PushL(paraLayer);
    _LIT( KNDParaLayer, "CEikonEnv NewDefaultParaFormatLayerL." );
    AssertNotNullL( paraLayer, KNDParaLayer );
    CleanupStack::Pop(paraLayer);
    delete paraLayer;

    CCharFormatLayer* charLayer = iEikenv->NewDefaultCharFormatLayerL();
    CleanupStack::PushL(charLayer);
    _LIT( KNDCharLayer, "CEikonEnv NewDefaultCharFormatLayerL." );
    AssertNotNullL( charLayer, KNDCharLayer );
    CleanupStack::Pop(charLayer);
    delete charLayer;

    CParaFormatLayer* singlelineLayer =
        iEikenv->NewDefaultSingleLineParaFormatLayerL();
    CleanupStack::PushL(singlelineLayer);
    _LIT( KNDSParaLayer, "CEikonEnv NewDefaultSingleLineParaFormatLayerL." );
    AssertNotNullL( singlelineLayer, KNDSParaLayer );
    CleanupStack::Pop(singlelineLayer);
    delete singlelineLayer;

    iEikenv->SetBusy( ETrue );
    _LIT( KSetBusy, "CEikonEnv SetBusy." );
    AssertNotNullL( iEikenv, KSetBusy );

    _LIT( KIsBusy, "CEikonEnv IsBusy ETrue." );
    AssertTrueL( iEikenv->IsBusy(), KIsBusy );

    iEikenv->SetSystem( ETrue );
    _LIT( KSetSystem, "CEikonEnv SetSystem." );
    AssertNotNullL( iEikenv, KSetSystem );

    _LIT( KIsSystem, "CEikonEnv IsSystem ETrue." );
    AssertTrueL( iEikenv->IsSystem(), KIsSystem );

    iEikenv->SetDocNameIsAFile( ETrue );
    _LIT( KSetDocNameIsAFile, "CEikonEnv SetDocNameIsAFile ETrue." );
    AssertNotNullL( iEikenv, KSetDocNameIsAFile );

    _LIT( KDocNameIsFile, "CEikonEnv DocNameIsAFile ETrue." );
    AssertTrueL( iEikenv->DocNameIsAFile(), KDocNameIsFile );

    iEikenv->SetRespondsToShutdownEvent( ETrue );
    _LIT( KShutdownEvent, "CEikonEnv SetRespondsToShutdownEvent ETrue." );
    AssertNotNullL( iEikenv, KShutdownEvent );

    _LIT( KRespondsToShutdown, "CEikonEnv RespondsToShutdownEvent ETrue." );
    AssertTrueL( iEikenv->RespondsToShutdownEvent(), KRespondsToShutdown );

    iEikenv->SetRespondsToSwitchFilesEvent( ETrue );
    _LIT( KSwitchFilesEvent, "SetRespondsToSwitchFilesEvent ETrue." );
    AssertNotNullL( iEikenv, KSwitchFilesEvent );

    _LIT( KRespondsToSwitch, "CEikonEnv RespondsToSwitchFilesEvent ETrue." );
    AssertTrueL( iEikenv->RespondsToSwitchFilesEvent(), KRespondsToSwitch );

    _LIT( KAsServerApp, "CEikonEnv StartedAsServerApp." );
    AssertTrueL( !iEikenv->StartedAsServerApp(), KAsServerApp );

    CEikAppServer* appServer = iEikenv->AppServer();
    _LIT( KAppServer, "CEikonEnv AppServer." );
    AssertTrueL( appServer == NULL, KAppServer );
    appServer = NULL;

    iEikenv->WriteInternalStateOfStackedControlsL();
    _LIT( KWriteState, "CEikonEnv WriteInternalStateOfStackedControlsL." );
    AssertNotNullL( iEikenv, KWriteState );

    iEikenv->DoGetErrorText( msgInfo, 12 ); //12 means KErrFolderNotFound
    // Display the error text via InfoMsg() method.
    iEikenv->InfoMsg( msgInfo );

    iEikenv->HandleError(12);
    _LIT( KHandleError, "CEikonEnv HandleError." );
    AssertNotNullL( iEikenv, KHandleError );

    iEikenv->HandleErrorWithContext( 12, R_BCTESTAPPFRM_MSGINFO );
    _LIT( KHandleErrorContext, "CEikonEnv HandleErrorWithContext." );
    AssertNotNullL( iEikenv, KHandleErrorContext );

    TDisplayMode displayMode = iEikenv->DefaultDisplayMode();
    _LIT( KDisplayMode, "CEikonEnv DefaultDisplayMode." );
    AssertNotNullL( iEikenv, KDisplayMode );

    iEikenv->UpdateSystemFontsL();
    _LIT( KUpdFonts, "CEikonEnv UpdateSystemFontsL." );
    AssertNotNullL( iEikenv, KUpdFonts );

    CColorList* colorList = iEikenv->CreateSystemColorListL();
    _LIT( KcolorList, "CEikonEnv CreateSystemColorListL NULL." );
    AssertTrueL( colorList==NULL, KcolorList );
    }

// ----------------------------------------------------------------------------
// prepare for the test.
// ----------------------------------------------------------------------------
//
void CBCTestEikenv::SetupL()
    {
    }

// ----------------------------------------------------------------------------
// do release jobs.
// ----------------------------------------------------------------------------
//
void CBCTestEikenv::TearDownL()
    {
    }


