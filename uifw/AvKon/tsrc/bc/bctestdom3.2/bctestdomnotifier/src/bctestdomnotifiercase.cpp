/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  test case
*
*/


#include <aknlayoutscalable_avkon.cdl.h>
#include <AknLayout2ScalableDef.h>
#include <AknLayout2ScalableDataDef.h>
#include <AknLayout2ScalableDecode.h>
#include <eikcolib.h>

#include <badesca.h>
#include <w32std.h>
#include <coecntrl.h>
#include <eikenv.h>
#include <barsread.h>
#include <coemain.h>
#include <eikdialg.h>
#include <akndialog.h>
#include <AknOpenFileService.h>
#include <AknReadingConverter.h>
#include <aknnavi.h>
#include <eiktxlbm.h> // CTextListBoxModel
#include <eiktxlbx.h>
#include <eiklbi.h>
#include <s32file.h>
#include <f32file.h>
#include <AiwGenericParam.h>

#include <AknNotifierAppServer.h>
#include <AknNotiferAppServerApplication.h>
#include <AknNotifierAppServerSession.h>
#include <aknnotifiercontroller.h>
#include <AknNotifierControllerPlugin.h>
#include <AknNotifierControllerUtilities.h>
#include <AknNotifierWrapper.h>
#include <AknNullService.h>

#include <aknsignal.h>
#include <AknSignalNotify.h>
#include <AknSignalNotifyAddition.h>

#include <aknlongtapanimation.h>
#include <AknMarqueeControl.h>
#include <AknMediatorFacade.h>
#include <aknMemoryCardDialog.h>
#include <aknlistloadertfx.h>
#include <AknPhoneNumberGrouping.h>
#include <AknPhoneNumberTextUtils.h>
#include <AknPhoneNumberEditor.h>
#include <aknnoteattributes.h>
#include <eikdialg.h>
#include <eikmenup.h>

#include <bctestdomnotifier.rsg>
#include "bctestdomnotifiercase.h"
#include "bctestdomnotifiercontainer.h"
#include "bctestdomnotifier.hrh"
#include "bctestdomnotifierview.h"
#include "bctestdomnotifierapp.h"

_LIT( KCAknNotifierAppServerAppUi, "App server error" );

// ======== MEMBER FUNCTIONS ========
// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCDomainTestNotifierCase* CBCDomainTestNotifierCase::NewL( CBCDomainTestNotifierContainer*
    aContainer )
    {
    CBCDomainTestNotifierCase* self = new( ELeave ) CBCDomainTestNotifierCase(
        aContainer );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default constructor
// ---------------------------------------------------------------------------
//
CBCDomainTestNotifierCase::CBCDomainTestNotifierCase( CBCDomainTestNotifierContainer*
    aContainer )
    : iContainer( aContainer )
    {
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCDomainTestNotifierCase::~CBCDomainTestNotifierCase()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCDomainTestNotifierCase::ConstructL()
    {
    BuildScriptL();
    }

// ---------------------------------------------------------------------------
// CBCDomainTestNotifierCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCDomainTestNotifierCase::BuildScriptL()
    {
    // Add script as your need.
    AddTestL( DELAY(1), LeftCBA, KeyOK, LeftCBA, Down, KeyOK, LeftCBA, Down,
        Down, KeyOK, DELAY(3), RightCBA, LeftCBA, Down, Down, Down, KeyOK, DELAY(3), RightCBA,
        TEND  );
    }

// ---------------------------------------------------------------------------
// CBCDomainTestNotifierCase::RunL
// ---------------------------------------------------------------------------
//
void CBCDomainTestNotifierCase::RunL( TInt aCmd )
    {
    if ( aCmd < EBCTestCmdOutline1 || aCmd > EBCTestCmdOutline4 )
        {
        return;
        }
    // Call release before prepare to let container has time to draw the
    // control created in PrepareCaseL.
    ReleaseCaseL();
    PrepareCaseL( aCmd );
    switch ( aCmd )
        {
        case EBCTestCmdOutline1:
            TestFunctionL();
            break;
        case EBCTestCmdOutline2:
// TestSignalL() has some problem, so comment it currently.
//            TestSignalL();
            break;
        case EBCTestCmdOutline3:
            TestOtherL();
            break;
        case EBCTestCmdOutline4:
            TestPhoneL();
			break;
        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// CBCDomainTestNotifierCase::PrepareCaseL
// ---------------------------------------------------------------------------
//
void CBCDomainTestNotifierCase::PrepareCaseL( TInt aCmd )
    {
    switch ( aCmd )
        {
        case EBCTestCmdOutline1:
            // Here is a simple demo. You should create your control
            // instead of this.
            iControl = new( ELeave ) CCoeControl();
            iControl->SetContainerWindowL( *iContainer );
            iControl->MakeVisible( ETrue );
            break;
        default:
            break;
        }
    // Pass the owner of iControl to iContainer.
    iContainer->SetControl( iControl );
    }

// ---------------------------------------------------------------------------
// CBCDomainTestNotifierCase::ReleaseCaseL
// ---------------------------------------------------------------------------
//
void CBCDomainTestNotifierCase::ReleaseCaseL()
    {
    // let container delete the component control.
    iContainer->ResetControl();
    iControl = NULL;
    }

// ---------------------------------------------------------------------------
// CBCDomainTestNotifierCase::TestFunctionL
// ---------------------------------------------------------------------------
//
void CBCDomainTestNotifierCase::TestFunctionL()
    {
    //aknopenfileservice.h

    RFs& fs = CEikonEnv::Static()->FsSession();
    RFile rfile;
    _LIT( KFilePath, "c:\\BCTestLog\\test.txt" );
    rfile.Create( fs, KFilePath, EFileWrite | EFileShareAny );
    CleanupClosePushL( rfile );

//    CAiwGenericParamList* aiwparalist = CAiwGenericParamList::NewL();
//    CPslnModel* psmodel= CPslnModel::NewL();
//    MAknServerAppExitObserver* serappexit =
//        static_cast<MAknServerAppExitObserver*> ( psmodel );
//
//    CAknOpenFileService* fileserv = NULL;
//    TRAPD( err, fileserv = CAknOpenFileService::NewL(
//        KFilePath, serappexit, aiwparalist ) );
//    _LIT( KCAknOpenFileServiceNewL, "CAknOpenFileService::NewL()" );
//    AssertTrueL( ETrue, KCAknOpenFileServiceNewL );
//    delete fileserv;
//    fileserv = NULL;
//
//    TUid KUid = { 0xA0004001 };
//    TInt err1;
//    TRAP( err1, fileserv = CAknOpenFileService::NewL(
//        KUid, rfile, serappexit, aiwparalist ) );
//    _LIT( KCAknOpenFileServiceNewLOver, "CAknOpenFileService::NewL()" );
//    AssertTrueL( ETrue, KCAknOpenFileServiceNewLOver );
//
//    CleanupStack::PopAndDestroy(); // rfile 
//    delete fileserv;
//    delete psmodel;
//    delete aiwparalist;
//    _LIT( KCAknNotifierAppServerAppUi,"CAknNotifierAppServerAppUi" );
    // AknNotiferAppServerApplication.h

    CBCNotifierAppServer *notifierapp = new ( ELeave )
         CBCNotifierAppServer();
    CleanupStack::PushL( notifierapp );
    CApaDocument* tmp = notifierapp->CreateDocumentL();

    CApaAppServer* appserver = NULL;
    notifierapp->NewAppServerL( appserver );

    delete tmp;
    delete appserver;
    CleanupStack::PopAndDestroy( notifierapp );

    _LIT( KHandleCommandL, "HandleCommandL" );
    _LIT( KSetFadedL, "SetFadedL" );
    _LIT( KHandleKeyEventL, "HandleKeyEventL" );
    _LIT( KHandleError, "HandleError" );
    _LIT( KHandleSystemEventL, "HandleSystemEventL" );
    _LIT( KManager, "Manager" );
    _LIT( KSetManager, "SetManager" );
    _LIT( KEikSrvBlocked, "EikSrvBlocked" );

    CAknNotifierAppServerAppUi* notifier = static_cast<CAknNotifierAppServerAppUi*>
        ( CEikonEnv::Static()->AppUi() );

    notifier->CAknNotifierAppServerAppUi::HandleCommandL( EEikCmdCanceled );
    AssertTrueL( ETrue, KHandleCommandL );

    notifier->SetFadedL( EFalse );
    AssertTrueL( ETrue, KSetFadedL );

    TKeyEvent keyevent = { EKeyEnter, EStdKeyEnter, 0, 0  };
    notifier->HandleKeyEventL( keyevent, EEventNull );
    AssertTrueL( ETrue, KHandleKeyEventL );

    TInt handleErr = 0;
    SExtendedError exterr;
    TBuf<32> errbuf( KCAknNotifierAppServerAppUi );
    notifier->HandleError( handleErr, exterr , errbuf , errbuf );
    AssertTrueL( ETrue, KHandleError );

    TWsEvent wsevent;
    notifier->HandleSystemEventL( wsevent );
    AssertTrueL( ETrue, KHandleSystemEventL );

    MEikSrvNotifierManager* manager = notifier->Manager();
    AssertTrueL( ETrue, KManager );

    notifier->SetManager( manager );
    AssertTrueL( ETrue, KSetManager );

    notifier->EikSrvBlocked();
    AssertTrueL( ETrue, KEikSrvBlocked );

    //notifier->SuppressAppSwitching( ETrue );
    //_LIT( KSuppressAppSwitching, "SuppressAppSwitching" );
    //AssertTrueL( ETrue, KSuppressAppSwitching );

    // AknNotiferAppServer.h
    _LIT( KNotiServer, "CAknNotifierAppServer");
    _LIT( KStartNotifierL, "StartNotifierL");
    _LIT( KUpdateNotifierL, "UpdateNotifierL");
    _LIT( KCancelNotifier, "CancelNotifier");
    _LIT( KStartNotifierAndGetResponseL, "StartNotifierAndGetResponseL");
    _LIT( KAppendNotifierLibNameL, "AppendNotifierLibNameL");
    _LIT( KSetImplementationFinderL, "SetImplementationFinderL");
    _LIT( KUnbalanceReferenceCountForNotif, "UnbalanceReferenceCountForNotif");
    _LIT( KCreateServiceL, "CreateServiceL");
    _LIT( KCAknNotifierAppServerDestroy, "SCAknNotifierAppServerDestroy" );
    _LIT( KUpdateNotifierAndGetResponseL, "UpdateNotifierAndGetResponseL" );
////////////////////////////////////////////////////////////////////////////////////////////////
    CAknNotifierAppServer *notiserver = new ( ELeave ) CAknNotifierAppServer();
    CleanupStack::PushL( notiserver );
    AssertNotNullL( notiserver, KNotiServer );
    
    _LIT(KLabName, "ictsuiutilsnotif.dll");
	//_LIT(KLabName, "aknoldstylenotif.dll");
    notiserver->AppendNotifierLibNameL( KLabName );
    AssertTrueL( ETrue,KAppendNotifierLibNameL );
    
    //TRAP( err, notiserver->LoadNotifiersL() );
    //AssertTrueL( ETrue,KLoadNotifiersL );

    TBuf8<32> bf;
    TInt err;
    TRAP( err,notiserver->StartNotifierL(
        KUidBCDomainTestNotifier, bf, bf ) );
    AssertTrueL( ETrue,KStartNotifierL );

    TRAP( err, notiserver->UpdateNotifierL(
        KUidBCDomainTestNotifier, bf, bf ) );
    AssertTrueL( ETrue,KUpdateNotifierL );

    notiserver->CancelNotifier( KUidBCDomainTestNotifier );
    AssertTrueL( ETrue,KCancelNotifier );

    RMessagePtr2 msg;
    TInt replyslot = 1;
    TRAP( err, notiserver->StartNotifierAndGetResponseL(
        KUidBCDomainTestNotifier, bf, msg, replyslot ) );
    AssertTrueL( ETrue, KStartNotifierAndGetResponseL );


    MNotifLibraryOwningServer* pFinder = NULL;
    notiserver->SetImplementationFinderL( pFinder );
    AssertTrueL( ETrue, KSetImplementationFinderL );

    notiserver->UnbalanceReferenceCountForNotif(
        KUidBCDomainTestNotifier, EFalse );
    AssertTrueL( ETrue,KUnbalanceReferenceCountForNotif );

    TRAP( err, notiserver->CreateServiceL( KUidBCDomainTestNotifier ) );
    AssertTrueL( ETrue, KCreateServiceL );



    TRAP( err, notiserver->UpdateNotifierAndGetResponseL(
        KUidBCDomainTestNotifier, bf, msg, replyslot ) );
    AssertTrueL( ETrue, KUpdateNotifierAndGetResponseL );

    CleanupStack::PopAndDestroy( notiserver );
    AssertTrueL( ETrue,KCAknNotifierAppServerDestroy );
////////////////////////////////////////////////////////////////////////////////////
    // AknNotifierAppServerSession.h
    // aknnotifiercontrollerutilities.h

    CAknNotifierControllerUtility* ntf =
                    new ( ELeave )CAknNotifierControllerUtility(0);
    CleanupStack::PushL( ntf );
    ntf->DoStopNotifications();
    CleanupStack::PopAndDestroy( ntf );

    _LIT( KCAknNotifierControllerUtility,
                    "CAknNotifierControllerUtility::DoStopNotifications()" );
    AssertTrueL( ETrue, KCAknNotifierControllerUtility );

    // aknnotifiercontroller.h
    _LIT( KCancelAllNotifications, "CancelAllNotifications" );
    _LIT( KHideAllNotifications, "HideAllNotifications" );

    AknNotifierController::HideAllNotifications( EFalse );
    AssertTrueL( ETrue, KHideAllNotifications );

    AknNotifierController::CancelAllNotifications();
    AssertTrueL( ETrue, KCancelAllNotifications );

    // aknnullservice.h

    _LIT( KCAknNullService, "CAknNullService" );
    _LIT( KCAknNullServiceDestroy, "CAknNullServiceDestroy" );

    MAknServerAppExitObserver* os = new ( ELeave ) CBCserverAppExitObserver();
    TUid KUidTest = { 0xA004000 };
    CAknNullService* nullserv = NULL;
    TRAP( err, nullserv = CAknNullService::NewL( KUidTest, os ) );
    CleanupStack::PushL( nullserv );
    AssertTrueL( ETrue,KCAknNullService );
    CleanupStack::Pop();
    AssertTrueL( ETrue,KCAknNullServiceDestroy );
    delete os;
    CAknLongTapAnimation* ltAnimation = CAknLongTapAnimation::NewL();
    CleanupStack::PushL( ltAnimation );
    _LIT( KCAknLongTapAnimationNewL, "CAknLongTapAnimation::NewL()" );
    AssertTrueL( ETrue, KCAknLongTapAnimationNewL );

    if (ltAnimation)
        {
        ltAnimation->ShowAnimationL( 10, 10 );
        _LIT( KCAknLongTapAnimationShowAnimationL,
            "CAknLongTapAnimation::ShowAnimationL()" );
        AssertTrueL( ETrue, KCAknLongTapAnimationShowAnimationL );

        ltAnimation->HideAnimation();
        _LIT( KCAknLongTapAnimationHideAnimation,
            "CAknLongTapAnimation::HideAnimation()" );
        AssertTrueL( ETrue, KCAknLongTapAnimationHideAnimation );
        }

    CleanupStack::PopAndDestroy();//ltAnimation

   }

// ---------------------------------------------------------------------------
// CBCDomainTestNotifierCase::TestSignalL
// ---------------------------------------------------------------------------
//
void CBCDomainTestNotifierCase::TestSignalL()
    {
    // aknsignal.h
    _LIT( KCAknSignalPane, "CAknSignalPane" );
    _LIT( KConstructFromResourceL, "ConstructFromResourceL" );
    _LIT( KSetSignalLevel, "SetSignalLevel" );
    _LIT( KShowGprsIcon, "ShowGprsIcon" );
    _LIT( KShowCommonPacketDataIcon, "ShowCommonPacketDataIcon" );
    _LIT( KShowWcdmaIcon, "ShowWcdmaIcon" );
    _LIT( KShowHsdpaIcon, "ShowHsdpaIcon" );
    _LIT( KShowEdgeIcon, "ShowEdgeIcon" );
    _LIT( KCAknSignalPaneDestroy, "SCAknSignalPaneDestroy" );

    CAknSignalPane* signalpane = new ( ELeave ) CAknSignalPane();
    CleanupStack::PushL( signalpane );
    AssertNotNullL( signalpane, KCAknSignalPane );

    TResourceReader reader;
    CEikonEnv::Static()->CreateResourceReaderLC( reader,
        R_BCTESTDOMNOTIFIER_VIEW );

    signalpane->ConstructFromResourceL( reader );
    AssertTrueL( ETrue, KConstructFromResourceL );

    signalpane->SetSignalLevel( 5 );
    AssertTrueL( ETrue, KSetSignalLevel );

    signalpane->ShowGprsIcon( EAknSignalGprsIndicatorOff );
    AssertTrueL( ETrue, KShowGprsIcon );

    signalpane->ShowCommonPacketDataIcon(
        EAknSignalCommonPacketDataIndicatorOff );
    AssertTrueL( ETrue,KShowCommonPacketDataIcon );

    signalpane->ShowWcdmaIcon( EAknSignalWcdmaIndicatorOff );
    AssertTrueL( ETrue, KShowWcdmaIcon );

    signalpane->ShowHsdpaIcon( EAknSignalHsdpaIndicatorOff );
    AssertTrueL( ETrue, KShowHsdpaIcon );

    signalpane->ShowCdmaIcon( EAknSignalCdmaIndicatorOff );
    AssertTrueL( ETrue, KShowHsdpaIcon );

    signalpane->ShowEdgeIcon( EAknSignalEdgeIndicatorOff );
    AssertTrueL( ETrue, KShowEdgeIcon );

    signalpane->SetNaviPaneBackgroundType( EAknNaviPaneBackgroundTypeNotDefined );

    // Extension Func ExtensionInterface()
    _LIT( KPositionChanged,"PositionChanged" );

    CleanupStack::PopAndDestroy();// reader
    CleanupStack::PopAndDestroy( signalpane );
    AssertTrueL( ETrue,KCAknSignalPaneDestroy );

    CBCSignalPane* bcsinpane = new ( ELeave ) CBCSignalPane();
    CEikonEnv::Static()->CreateResourceReaderLC( reader,
         R_BCTESTDOMNOTIFIER_VIEW );
    bcsinpane->ConstructFromResourceL( reader );

    bcsinpane->PositionChanged();
    AssertTrueL( ETrue, KPositionChanged );

    CleanupStack::PopAndDestroy();//reader
    delete bcsinpane;
    AssertTrueL( ETrue,KPositionChanged );

    // AknSignalNotifyAddition.h
    _LIT( KAknSignalNotifyAddition, "AknSignalNotifyAddition" );

    CAknNavigationControlContainer* navicontrol = new ( ELeave )
         CAknNavigationControlContainer();
    navicontrol->ConstructL();
    AssertTrueL( ETrue, KAknSignalNotifyAddition );
    delete navicontrol;

    //AknNotifierWrapper.h
    _LIT( KCAknCommonNotifierWrapper, "CAknCommonNotifierWrapper" );
    _LIT( KSetCustomSecurityHandler, "SetCustomSecurityHandler" );
    _LIT( KStartNotifierL, "StartNotifierL" );
    _LIT( KCancelNotifier, "SCancelNotifier" );
    _LIT( KStartNotifierL2, "StartNotifierL2" );
    _LIT( KUpdateNotifierL1, "UpdateNotifierL1" );
    _LIT( KUpdateNotifierL2, "UpdateNotifierL2" );
    _LIT( KDoNotifierControllerCommand, "DoNotifierControllerCommand" );
    _LIT( KStartL1, "StartL1" );
    _LIT( KStartL2, "StartL2" );
    _LIT( KUpdateL, "UpdateL" );
    _LIT( KSInfo, "Info" );
    _LIT( KNotifierCapabilites, "NotifierCapabilites" );
    _LIT( KCancel, "Cancel" );
    _LIT( KNewServerRequestL, "NewServerRequestL" );
    _LIT( KAsyncMessageCompleted, "AsyncMessageCompleted" );

    TBuf<32> plibaryname;
    TUid kuid = {0xA0004000};
    TUid  channel = EAknNotifierChannelNote;

    CAknCommonNotifierWrapper* notiwrap = CAknCommonNotifierWrapper::NewL(
        kuid, channel, MEikSrvNotifierBase2::ENotifierPriorityLowest,
        KSInfo, 64, EFalse );
    CleanupStack::PushL( notiwrap );
    AssertNotNullL( notiwrap, KCAknCommonNotifierWrapper );

    TBuf8<32> bf;
    RMessagePtr2 msg;
    TInt replyslot = 1;

    TUid KUid1 = { 0xA0004001 };
    TUid KUid2 = { 0xA0004002 };


    MAknNotifierCustomSecurityCheck* handler = NULL;
    notiwrap->SetCustomSecurityHandler( handler );
    AssertTrueL( ETrue, KSetCustomSecurityHandler );
    delete handler;

    notiwrap->StartNotifierL( KUid1, bf, replyslot, msg );
    AssertTrueL( ETrue, KStartNotifierL );

    TInt err = 0;
    TRAP( err, notiwrap->StartNotifierL( KUid2, bf ) );
    AssertTrueL( ETrue, KStartNotifierL2 );

    notiwrap->CancelNotifier( KUid1 );
    notiwrap->CancelNotifier( KUid2 );
    AssertTrueL( ETrue, KCancelNotifier );

    TRAP( err, notiwrap->UpdateNotifierL( KUid1, bf ) );
    AssertTrueL( ETrue, KUpdateNotifierL1 );

    TRAP( err, notiwrap->MAknNotifierWrapper::UpdateNotifierL( KUid2, bf, replyslot,msg ) );
    AssertTrueL( ETrue, KUpdateNotifierL2 );

    notiwrap->DoNotifierControllerCommand( 1 );
    AssertTrueL( ETrue,KDoNotifierControllerCommand );

    notiwrap->StartL( bf,replyslot,msg );
    AssertTrueL( ETrue,KStartL1 );

    notiwrap->Info();
    AssertTrueL( ETrue,KSInfo );

    TRAP( err, notiwrap->UpdateL( bf ) );
    AssertTrueL( ETrue,KUpdateL );

    notiwrap->NotifierCapabilites();
    AssertTrueL( ETrue,KNotifierCapabilites );

    TRAP( err, notiwrap->StartL( bf ) );
    AssertTrueL( ETrue,KStartL2 );

    MAknNotifierWrapper* owner = NULL;
    RMessagePtr2 ptr;
    CAknNotifierMessageObserver* notimessa = CAknNotifierMessageObserver::
        NewServerRequestL( KUidBCDomainTestNotifier, owner, ptr, replyslot );
    CleanupStack::PushL( notimessa );
    AssertNotNullL( notimessa, KNewServerRequestL );

    notiwrap->AsyncMessageCompleted( notimessa );
    AssertTrueL( ETrue, KAsyncMessageCompleted );

    CleanupStack::PopAndDestroy( notimessa );

    notiwrap->Cancel();
    AssertTrueL( ETrue, KCancel );

    notiwrap->Release();
    _LIT( KRelease, "Release" );
    AssertTrueL( ETrue, KRelease );
    CleanupStack::Pop( notiwrap );    

    TUid ntfUid = { 0x10aa0d10 };
    CAknNotifierWrapper* notifierWrap =
            CAknNotifierWrapper::NewL( ntfUid , ntfUid,  0,  ntfUid, 0);
    CleanupStack::PushL( notifierWrap );

    TBuf8<10> buf;
    RMessagePtr2 message;
    notifierWrap->StartNotifierL( ntfUid, buf,  0,  message );

    TInt errno;
    TRAP( errno, notifierWrap->StartNotifierL( ntfUid, buf ) );

    CleanupStack::PopAndDestroy( notifierWrap );

    _LIT( KCAknNotifierWrapper, "CAknNotifierWrapper::StartNotifierL(4)" );
    AssertTrueL( ETrue, KCAknNotifierWrapper );
    _LIT( KCAknNotifierWrapper2, "CAknNotifierWrapper::StartNotifierL(2)" );
    AssertTrueL( ETrue, KCAknNotifierWrapper2 );

    // AknSignalNotify.h
    }

// ---------------------------------------------------------------------------
// CBCDomainTestNotifierCase::TestOtherL
// ---------------------------------------------------------------------------
//
void CBCDomainTestNotifierCase::TestOtherL()
    {

    // AknMarqueeControl.h

    _LIT( KCAknMarqueeControl, "CAknMarqueeControl" );
    _LIT( KStart, "Start" );
    _LIT( KReset, "Reset" );
    _LIT( KStop, "Stop" );
    _LIT( KIsMarqueeOn, "IsMarqueeOn" );
    _LIT( KUseLogicalToVisualConversion, "UseLogicalToVisualConversion" );
    _LIT( KSetSpeedInPixels, "SetSpeedInPixels" );
    _LIT( KSetDelay, "SetDelay" );
    _LIT( KSetInterval, "SetInterval" );
    _LIT( KSetLoops, "SetLoops" );
    _LIT( KEnableMarquee, "EnableMarquee" );
    _LIT( KSCAknMarqueeControlDestroy, "SSCAknMarqueeControlDestroy" );

    CAknMarqueeControl* marcontrol = CAknMarqueeControl::NewL();
    CleanupStack::PushL( marcontrol );
    AssertNotNullL( marcontrol, KCAknMarqueeControl );
    marcontrol->Start();
    AssertTrueL( ETrue, KStart );
    marcontrol->Reset();
    AssertTrueL( ETrue, KReset );
    marcontrol->Stop();
    AssertTrueL( ETrue, KStop );
    marcontrol->IsMarqueeOn();
    AssertTrueL( ETrue, KIsMarqueeOn );
    marcontrol->UseLogicalToVisualConversion( EFalse );
    AssertTrueL( ETrue, KUseLogicalToVisualConversion );
    marcontrol->SetSpeedInPixels( 4 );
    AssertTrueL( ETrue, KSetSpeedInPixels );
    marcontrol->SetDelay( 8 );
    AssertTrueL( ETrue, KSetDelay );
    marcontrol->SetInterval( 8 );
    AssertTrueL( ETrue, KSetInterval );
    marcontrol->SetLoops( 1 );
    AssertTrueL( ETrue, KSetLoops );
    marcontrol->EnableMarquee( EFalse );
    AssertTrueL( ETrue, KEnableMarquee );

    const TBuf<32>  txt( KStart );
    const TInt      baselineoffset = 8;
    const CGraphicsContext::TTextAlign align( CGraphicsContext::ELeft );
    TRect rect( TRect(1,1,99,99) );
    const CFont* font = CEikonEnv::Static()->NormalFont();
    TAknTextComponentLayout textlayout;

    marcontrol->SetContainerWindowL( *iContainer );
    CWindowGc& gc = marcontrol->SystemGc();

    marcontrol->DrawText( gc, rect, txt, baselineoffset, align, *font );
    //marcontrol->DrawText( gc, rect, textlayout, txt, font );

    CleanupStack::PopAndDestroy( marcontrol );
    AssertTrueL( ETrue, KSCAknMarqueeControlDestroy );

    //  AknMediatorFacade.h
    CEikDialog *dialog = new ( ELeave ) CEikDialog();
    CleanupStack::PushL( dialog );
    CAknMediatorFacade* mediatorFacade = CAknMediatorFacade::NewL( dialog );
    CleanupStack::PushL( mediatorFacade );
    _LIT( KCAknMediatorFacade, "CAknMediatorFacade::CAknMediatorFacade()" );
    AssertTrueL( ETrue, KCAknMediatorFacade );

    mediatorFacade->ResetBuffer();
    _LIT( KCMFacadeResetBuffer, "CAknMediatorFacade::ResetBuffer()" );
    AssertTrueL( ETrue, KCMFacadeResetBuffer );

    mediatorFacade->PostUpdatedDataL();
    _LIT( KCMFacadePostUpdatedDataL, "CAknMediatorFacade::PostUpdatedDataL()" );
    AssertTrueL( ETrue, KCMFacadePostUpdatedDataL );

    AknMediatorFacade( dialog );
    _LIT( KGlobalAknMediatorFacade, "Global::AknMediatorFacade" );
    AssertTrueL( ETrue, KGlobalAknMediatorFacade );


    TInt& index = mediatorFacade->DialogIndex();
    index = 1;
    mediatorFacade->IssueCommand();
    _LIT( KCMFacadeIssueCommand, "CAknMediatorFacade::IssueCommand()" );
    AssertTrueL( ETrue, KCMFacadeIssueCommand );

    mediatorFacade->CancelCommand();
    _LIT( KCMFacadeCancelCommand, "CAknMediatorFacade::CancelCommand()" );
    AssertTrueL( ETrue, KCMFacadeCancelCommand );

    mediatorFacade->SetObserver( NULL );
    _LIT( KCMFacadeSetObserver, "CAknMediatorFacade::SetObserver()" );
    AssertTrueL( ETrue, KCMFacadeSetObserver );

    CleanupStack::PopAndDestroy( mediatorFacade );
    CleanupStack::PopAndDestroy( dialog );

    //  aknlistloadertfx.h
    _LIT( KTfxApiInternal, "TfxApiInternal" );
    _LIT( KTfxApi, "TfxApi" );
    _LIT( KRemoveTfxGc, "RemoveTfxGc" );
    _LIT( KInvalidateAll, "InvalidateAll" );

    CAknListLoader::TfxApiInternal( &gc );
    AssertTrueL( ETrue, KTfxApiInternal );
    CAknListLoader::TfxApi( &gc );
    AssertTrueL( ETrue, KTfxApi );


    CAknDialog* dlg = new ( ELeave ) CAknDialog();
	CleanupStack::PushL( dlg );
    CEikMenuPane* menupane = new (ELeave) CEikMenuPane(dlg);
	CleanupStack::PushL( menupane );
    TInt topindex = 0;
    TInt itemsthatfitinview = 1;
    CAknListLoader::CreateTfxGc( *menupane, topindex, itemsthatfitinview );

	
    //CDesCArray* txtarray = new (ELeave) CDesCArraySeg(1);
	//CleanupStack::PushL( txtarray );
    //TBuf<32> item( KStart );
    //txtarray->AppendL( item );
    

    //CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();
    //CleanupStack::PushL( model );
    //model->ConstructL();
	

    //CTextListItemDrawer* drawer = new( ELeave ) CTextListItemDrawer();
    //CleanupStack::PushL( drawer );
    //drawer->ConstructL( CEikonEnv::Static()->NormalFont() );

    //CEikListBox* lstbox = new ( ELeave ) CEikListBox();
    //CleanupStack::PushL( lstbox );

    //TGulBorder tborder( TGulBorder::ESingleGray );
    //lstbox->ConstructL(  iContainer );
     //   EAknListBoxSelectionList | EAknListBoxViewerFlags );

    //CAknListLoader::CreateTfxGc( *lstbox );
    //AssertTrueL( ETrue, KCreateTfxGc );

    
       
    CAknListLoader::RemoveTfxGc( &gc );
    AssertTrueL( ETrue, KRemoveTfxGc );
    
	
    CAknListLoader::InvalidateAll();
    AssertTrueL( ETrue, KInvalidateAll );
	
	//CleanupStack::PopAndDestroy( lstbox );
	//CleanupStack::PopAndDestroy( drawer );
	//CleanupStack::PopAndDestroy( model );
	//CleanupStack::PopAndDestroy( txtarray );
	
	CleanupStack::PopAndDestroy( menupane);
	CleanupStack::PopAndDestroy( dlg );
    // AknReadingConverter.h
    _LIT( KCReadingConverter, "CReadingConverter" );
    _LIT( KHandleCompletionOfTransactionL, "HandleCompletionOfTransactionL" );
    _LIT( KMainEditor, "MainEditor" );
    _LIT( KReadingEditor, "ReadingEditor" );
    _LIT( KSetReadingEditor, "SetReadingEditor" );
    _LIT( KSetMainEditor, "SetMainEditor" );


    CReadingConverter* rdconver = CReadingConverter::NewL();
    CleanupStack::PushL( rdconver );
    AssertNotNullL( rdconver, KCReadingConverter );
    CleanupStack::PopAndDestroy();

    CEikEdwin* maineditor = NULL;
    rdconver = CReadingConverter::NewL( *maineditor, *maineditor );
    CleanupStack::PushL( rdconver );

    rdconver->HandleCompletionOfTransactionL();
    AssertTrueL( ETrue, KHandleCompletionOfTransactionL );

    rdconver->MainEditor();
    AssertTrueL( ETrue, KMainEditor );

    rdconver->ReadingEditor();
    AssertTrueL( ETrue, KReadingEditor );

    rdconver->SetReadingEditor( *maineditor );
    AssertTrueL( ETrue, KSetReadingEditor );

    rdconver->SetMainEditor( *maineditor );
    AssertTrueL( ETrue, KSetMainEditor );

    CleanupStack::PopAndDestroy( rdconver );

    //  aknMemoryCardDialog.h
    _LIT( KCAknMemoryCardDialog, "CAknMemoryCardDialog" );
    _LIT( KSetSelfPointer, "SetSelfPointer" );
    _LIT( KUnlockCardLD, "UnlockCardLD" );
    _LIT( KNotifierArray, "NotifierArray" );

    CAknMemoryCardDialog* memdlg = CAknMemoryCardDialog::NewLC();
    AssertTrueL( ETrue, KCAknMemoryCardDialog );

    CArrayPtr<MEikSrvNotifierBase2>* notifies = NotifierArray();
    AssertTrueL( ETrue, KNotifierArray );

    memdlg->SetSelfPointer( &memdlg );
    AssertTrueL( ETrue, KSetSelfPointer );
    memdlg->UnlockCardLD( EDriveE );
    AssertTrueL( ETrue, KUnlockCardLD );

    }
// ---------------------------------------------------------------------------
// CBCDomainTestNotifierCase::TestPhoneL
// ---------------------------------------------------------------------------
//
void CBCDomainTestNotifierCase::TestPhoneL()
    {
    // AknPhoneNumberGrouping.h

    _LIT( KSet, "Set" );
    _LIT( KFormattedNumber, "FormattedNumber" );
    _LIT( KCopyFormattedNumber, "CopyFormattedNumber" );
    _LIT( KGrouphonenumber, "Grouphonenumber" );
    _LIT( KCreateGroupedPhoneNumberL, "CreateGroupedPhoneNumberL" );
    _LIT( KCAknPhoneNumberGroupingDestroy, "CAknPhoneNumberGroupingDestroy" );
    _LIT( KNumberGroup, "NuberGroup::NewL" );

    TBuf<32>  num( KNumberGroup );
    CAknPhoneNumberGrouping* phonenumber = CAknPhoneNumberGrouping::NewL( 10 );
    CleanupStack::PushL( phonenumber );
    AssertNotNullL( phonenumber,KNumberGroup );

    phonenumber->Set( num );
    AssertTrueL( ETrue, KSet );
    phonenumber->FormattedNumber();
    AssertTrueL( ETrue, KFormattedNumber );

    TBuf<32>  tarea( KNumberGroup );
    phonenumber->CopyFormattedNumber( tarea );
    AssertTrueL( ETrue, KCopyFormattedNumber );
    phonenumber->GroupPhoneNumber( tarea,num );
    AssertTrueL( ETrue, KGrouphonenumber );
    phonenumber->GroupPhoneNumber( num );
    AssertTrueL( ETrue, KGrouphonenumber );
    HBufC* rturn = phonenumber->CreateGroupedPhoneNumberL( num );
    AssertTrueL( ETrue, KCreateGroupedPhoneNumberL );

    delete rturn;
    CleanupStack::PopAndDestroy();
    AssertTrueL( ETrue, KCAknPhoneNumberGroupingDestroy );

    // AknPhoneNumberTextUtils.h
    _LIT( KWrapPhonenumberToArrayL, "WrapPhonenumberToArrayL" );
    _LIT( KClipLineOnLeft, "ClipLineOnLeft" );
    _LIT( KCharsThatFitOnRight, "CharsThatFitOnRight" );

    TBuf<32> tbuf( KNumberGroup );
    const CFont *tfont = CEikonEnv::Static()->NormalFont();
    CArrayFix<TPtrC>* ary = new ( ELeave ) CArrayFixFlat<TPtrC>( 32 );
	CleanupStack::PushL( ary );
    TPtrC tptr( tbuf );

    AknPhoneNumberTextUtils::WrapPhoneNumberToArrayL(
        tarea, 2, 16, *tfont, *ary );
    AssertTrueL( ETrue, KWrapPhonenumberToArrayL );
    AknPhoneNumberTextUtils::ClipLineOnLeft( tptr, tbuf, 1, *tfont );
    AssertTrueL( ETrue, KClipLineOnLeft );
    AknPhoneNumberTextUtils::CharsThatFitOnRight( tarea, 2, *tfont );
    AssertTrueL( ETrue, KCharsThatFitOnRight );
	CleanupStack::PopAndDestroy( ary );
    //delete ary;

    // AknPhoneNumberEditor.h
    _LIT( KConstructFromResourceL, "ConstructFromResourceL" );
    _LIT( KFormat, "Format" );
    _LIT( KWouldTextFitInFormat, "WouldTextFitInFormat" );
    _LIT( KCurrentFormatIndex, "CurrentFormatIndex" );
    _LIT( KSetFormat, "SetFormat" );
    _LIT( KText, "Text" );
    _LIT( KSizeChanged, "SizeChanged" );
    _LIT( KMinimumSize, "MinimumSize" );
    _LIT( KInputCapabilities, "InputCapabilities" );
    _LIT( KTextLength, "TextLength" );
    _LIT( KCursorPos, "CursorPos" );
    _LIT( KSelectionLength, "SelectionLength" );
    _LIT( KSelection, "Selection" );
    _LIT( KClearSelectionL, "ClearSelectionL" );
    _LIT( KSetSelectionL, "SetSelectionL" );
    _LIT( KSetCursorPosL, "SetCursorPosL" );
    _LIT( KSelectAllL, "SelectAllL" );
    _LIT( KGetText, "GetText" );
    _LIT( KGetTextInHBufL, "GetTextInHBufL" );
    _LIT( KSetTextL, "SetTextL" );
    _LIT( KSetText, "SetText" );
    _LIT( KGetEditorMode, "KGetEditorMode" );
    _LIT( KCancelFepTransaction, "CancelFepTransaction" );
    _LIT( KUpdateScrollBarsL, "UpdateScrollBarsL" );
    _LIT( KCreateScrollBarFrameL, "CreateScrollBarFrameL" );
    _LIT( KLineCursorWidth, "LineCursorWidth" );
    _LIT( KMargins, "Margins" );
    _LIT( KChangeEditorMode, "ChangeEditorMode" );
    _LIT( KResetEditorToDefaultValues, "ResetEditorToDefaultValues" );
    _LIT( KOfferKeyEventL, "OfferKeyEventL" );
    _LIT( KFocusChanged, "FocusChanged" );
    _LIT( KCAknPhoneNumberEditorDestroy, "KCAknPhoneNumberEditorDestroy" );
    _LIT( KCAknPhoneNumberEditorDraw, "Draw" );

    CAknPhoneNumberEditor* phonenumeditor =
        new ( ELeave ) CAknPhoneNumberEditor;
    CleanupStack::PushL( phonenumeditor );
    //AssertNotNullL( phonenumeditor,KCAknPhoneNumberEditor  );
    phonenumeditor->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CEikonEnv::Static()->CreateResourceReaderLC( reader,
	          R_PHONEEDAPP_RESEDIT );


    phonenumeditor->ConstructFromResourceL( reader );
    AssertTrueL( ETrue,KConstructFromResourceL  );
    CleanupStack::PopAndDestroy();//reader
	
    phonenumeditor->Format( 0 );
    AssertTrueL( ETrue, KFormat );

    //Draw() function will be called.
    iContainer->SetControl( phonenumeditor ); 
    AssertTrueL( ETrue, KCAknPhoneNumberEditorDraw );

    TInt tcount = phonenumeditor->CountFormats();
    phonenumeditor->WouldTextFitInFormat( tcount-1 );
    AssertTrueL( ETrue, KWouldTextFitInFormat );
    tcount = phonenumeditor->CurrentFormatIndex();
    AssertTrueL( ETrue, KCurrentFormatIndex );
    phonenumeditor->SetFormat( tcount );
    AssertTrueL( ETrue, KSetFormat );
    phonenumeditor->Text();
    AssertTrueL( ETrue, KText );
    phonenumeditor->SizeChanged();
    AssertTrueL( ETrue, KSizeChanged );
    phonenumeditor->MinimumSize();
    AssertTrueL( ETrue, KMinimumSize );
    phonenumeditor->InputCapabilities();
    AssertTrueL( ETrue, KInputCapabilities );

    phonenumeditor->TextLength();
    AssertTrueL( ETrue, KTextLength );
    phonenumeditor->CursorPos();
    AssertTrueL( ETrue, KCursorPos );
    phonenumeditor->SelectionLength();
    AssertTrueL( ETrue, KSelectionLength );
    phonenumeditor->Selection();
    AssertTrueL( ETrue, KSelection );
    phonenumeditor->ClearSelectionL();
    AssertTrueL( ETrue, KClearSelectionL );
    phonenumeditor->SetSelectionL( 0,0 );
    AssertTrueL( ETrue, KSetSelectionL );
    phonenumeditor->SetCursorPosL( 0,0 );
    AssertTrueL( ETrue, KSetCursorPosL );
    phonenumeditor->SelectAllL();
    AssertTrueL( ETrue, KSelectAllL );
    phonenumeditor->GetText( tarea );
    AssertTrueL( ETrue, KGetText );
    HBufC* temp = phonenumeditor->GetTextInHBufL();
	CleanupStack::PushL( temp );
    AssertTrueL( ETrue, KGetTextInHBufL );
	CleanupStack::PopAndDestroy( temp );

    phonenumeditor->SetTextL( &tarea );
    AssertTrueL( ETrue, KSetTextL );

    phonenumeditor->SetText( tarea );
    AssertTrueL( ETrue, KSetText );

    phonenumeditor->CancelFepTransaction();
    AssertTrueL( ETrue, KCancelFepTransaction );

    phonenumeditor->UpdateScrollBarsL();
    AssertTrueL( ETrue, KUpdateScrollBarsL );
    CEikScrollBarFrame* pScrBar = phonenumeditor->CreateScrollBarFrameL();
	CleanupStack::PushL( pScrBar );
    AssertTrueL( ETrue, KCreateScrollBarFrameL );
    CleanupStack::PopAndDestroy( pScrBar );
    phonenumeditor->LineCursorWidth();
    AssertTrueL( ETrue, KLineCursorWidth );
    phonenumeditor->Margins();
    AssertTrueL( ETrue, KMargins );

    phonenumeditor->ChangeEditorMode();
    AssertTrueL( ETrue, KChangeEditorMode );
    phonenumeditor->GetEditorMode();
    AssertTrueL( ETrue, KGetEditorMode );
    phonenumeditor->ResetEditorToDefaultValues();
    AssertTrueL( ETrue, KResetEditorToDefaultValues );

    TKeyEvent keyevent = { EKeyEnter, EStdKeyEnter, 0, 0  };
    phonenumeditor->OfferKeyEventL( keyevent,EEventKey );
    AssertTrueL( ETrue, KOfferKeyEventL );
    phonenumeditor->FocusChanged( EDrawNow );//Draw() function will be called.
    AssertTrueL( ETrue, KFocusChanged );

    iContainer->ResetControl();
	CleanupStack::Pop();
    //CleanupStack::PopAndDestroy();
    AssertTrueL( ETrue, KCAknPhoneNumberEditorDestroy );

    TestFormatL();
    }

// ---------------------------------------------------------------------------
// CBCDomainTestNotifierCase::TestFormatL
// ---------------------------------------------------------------------------
//
void  CBCDomainTestNotifierCase::TestFormatL()
    {
    _LIT( KCAknPhoneNumberEditor, "CAknPhoneNumberEditor" );
    _LIT( KConstructL, "ConstructL" );
    _LIT( KString, "..." );
    _LIT( KTFormat, "TFormat" );
    _LIT( KAddFormat, "AddFormat" );
    _LIT( KCAknPhoneNumberEditorDestroy, "CAknPhoneNumberEditorDestroy" );
    _LIT( KCAknMemoryCardDialog, "CAknMemoryCardDialog" );
    _LIT( KGetSkinnedBitmapID, "GetSkinnedBitmapID" );
    _LIT( KUnlockCardLD, "UnlockCardLD" );

    CAknPhoneNumberEditor* phonenumeditor = new ( ELeave ) CAknPhoneNumberEditor;
    AssertNotNullL( phonenumeditor, KCAknPhoneNumberEditor );

    phonenumeditor->SetContainerWindowL( *iContainer );
    phonenumeditor->ConstructL(  30, 3, 3, KString);
    AssertTrueL( ETrue, KConstructL );

    const CFont *tfont = CEikonEnv::Static()->NormalFont();
    CAknPhoneNumberEditor::TFormat tformat( CAknPhoneNumberEditor::TFormat(
        TRect( 10, 10, 70, 55 ), 0, 3, 3, 15, tfont ) );
    AssertTrueL( ETrue, KTFormat );

    phonenumeditor->AddFormat( tformat );
    AssertTrueL( ETrue, KAddFormat );

    TResourceReader reader;
    CEikonEnv::Static()->CreateResourceReaderLC( reader,
         R_NUMBER_FIELD_FORM );
    CAknPhoneNumberEditor::TFormat readformat( reader );
    AssertTrueL( ETrue, KTFormat );

    CleanupStack::PopAndDestroy( );//reader
    delete phonenumeditor;    
    AssertTrueL( ETrue, KCAknPhoneNumberEditorDestroy  );


    CAknNoteAttributes::GetSkinnedBitmapID( 0 );
    AssertTrueL( ETrue, KGetSkinnedBitmapID  );

    //aknmemorycarddialog.h
    CAknMemoryCardDialog* memdlg = CAknMemoryCardDialog::NewLC();
    AssertNotNullL( memdlg, KCAknMemoryCardDialog );

    memdlg->UnlockCardLD( ETrue );
    AssertTrueL( ETrue, KUnlockCardLD );

    }
//end of file
