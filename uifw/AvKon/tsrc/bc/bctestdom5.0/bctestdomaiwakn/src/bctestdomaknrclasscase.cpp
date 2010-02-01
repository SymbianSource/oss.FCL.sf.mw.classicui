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


#include <coecntrl.h>
#include <aknenv.h>
#include <aknconsts.h>
#include <bctestdomaiwakn.rsg>
#include <avkon.rsg>
#include <ecom.h>
#include <aknlists.h>
#include <finditemmenu.rsg>
#include <akncustomcursorsupport.h> //test akncustomcursorsupport.h
#include <aknasyncdemonotify.h>   // test AknAsyncDemoNotify.h
#include <akneiksrvc.h> // test akneiksrvc.h
#include <aknnotifystd.h>  // test akncapserverclient.h
#include <aknnotifiercontrollerutilities.h> // test akncapserverclient.h
#include <akncapserverdefs.h> // test akncapserverclient.h
#include <e32property.h>// test akncapserverclient.h
#include <e32keys.h>
#include "bctestdomaknrclasscase.h"
#include "bctestdomaiwaknapp.h"
#include "bctestdomaiwakncontainer.h"
#include "bctestdomaiwakn.hrh"
#include "bctestdomaiwaknview.h"
#include "bctestdomaknanimview.h"  // test aknanimview.h
#include "bctestdomaknanimdata.h" // indirectly test aknAnimData.h
#include "bctestdomuiserverunlockmedia.h" //test RAknUiServer::UnlockMedia()
                                          //in akncapserverclient.h
#include "bctestdomuiservershutdownapps.h"//test RAknUiServer::ShutdownApps()
                                          //in akncapserverclient.h

const TInt KDelay = 500*1000;   //500 ms
// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestDomAknRClassCase* CBCTestDomAknRClassCase::NewL(
    CBCTestDomAiwAknContainer*  aContainer )
    {
    CBCTestDomAknRClassCase* self =
        new( ELeave ) CBCTestDomAknRClassCase( aContainer );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default constructor
// ---------------------------------------------------------------------------
//
CBCTestDomAknRClassCase::CBCTestDomAknRClassCase(
    CBCTestDomAiwAknContainer* aContainer )
    : iContainer( aContainer )
    {
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestDomAknRClassCase::~CBCTestDomAknRClassCase()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestDomAknRClassCase::ConstructL()
    {
    BuildScriptL();
    }

// ---------------------------------------------------------------------------
// CBCTestDomAknRClassCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestDomAknRClassCase::BuildScriptL()
    {
    // Add script as your need.
    AddTestL(
             //  EBCTestDomCmdOutline4
             LeftCBA,REP( Down, 3 ),LeftCBA, WAIT(2),RightCBA,

             TEND );

    }

// ---------------------------------------------------------------------------
// CBCTestDomAknRClassCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestDomAknRClassCase::RunL( TInt aCmd )
    {
    if ( aCmd != EBCTestDomCmdOutline4 )
        {
        return;
        }

    switch ( aCmd )
        {
        case EBCTestDomCmdOutline4:
            {
            // test R classes
            TestAknAsyncDemoNotify(); //Not Ctrl
            TestAknCustomCursorSupport(); //Not Ctrl

            TestAknEikSrvc();  //Rclass
            TestAknAnimation(); //ctrl

            TestAknCapServerClient();//Rclass
            


            }
            break;

        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// From class MEikMenuObserver.
// ---------------------------------------------------------------------------
//
void CBCTestDomAknRClassCase::ProcessCommandL(TInt /*aCommandId*/)
    {
    }

// ---------------------------------------------------------------------------
// From class MEikMenuObserver.
// ---------------------------------------------------------------------------
//
void CBCTestDomAknRClassCase::SetEmphasis(
    CCoeControl* /*aMenuControl*/,
    TBool /*aEmphasis*/)
    {
    }

// ---------------------------------------------------------------------------
// CBCTestDomAknRClassCase::AknAsyncDemoNotifyCallBack()
// for testing APIs in AknAsyncDemoNotify.h
//
// ---------------------------------------------------------------------------
//
//
TInt CBCTestDomAknRClassCase::AknAsyncDemoNotifyCallBack( TAny* aInstance )
    {
    return (TInt)aInstance ;
    }

// ---------------------------------------------------------------------------
// CBCTestDomAknRClassCase::TestAknAsyncDemoNotify()
// test APIs in AknAsyncDemoNotify.h
// Test Result: Finished,incompatible bynary code.
//
// ---------------------------------------------------------------------------
//
void CBCTestDomAknRClassCase::TestAknAsyncDemoNotify()
    {

    // NOTE:    link error,becase not export the APIs from AknNotifyU.DEF file,
    //      so , it is incompatible bynary code.
/*
    TCallBack demoNotifyCallBack(
        CBCTestDomAknRClassCase::AknAsyncDemoNotifyCallBack );
    CAknAsyncDemoNotify*  asyncDemoNotify =
        CAknAsyncDemoNotify::NewL( demoNotifyCallBack );
    CleanupStack::PushL( asyncDemoNotify );
    _LIT(
        KCAknAsyncDemoNotifyNewL,
        "CAknAsyncDemoNotify::NewL() test" );
    AssertTrueL( ETrue, KCAknAsyncDemoNotifyNewL);

    asyncDemoNotify->Message();
    _LIT(
        KCAknAsyncDemoNotifyMessage,
        "CAknAsyncDemoNotify::Message() test" );
    AssertTrueL( ETrue,  KCAknAsyncDemoNotifyMessage);

    CleanupStack::PopAndDestroy( asyncDemoNotify );
    _LIT(
        KDelCAknAsyncDemoNotify,
        "~CAknAsyncDemoNotify() test" );
    AssertTrueL( ETrue,  KDelCAknAsyncDemoNotify);
*/
    }

// ---------------------------------------------------------------------------
// CBCTestDomAknRClassCase::TestAknAnimation()
// test APIs in aknAnimData.h and  aknAnimView.h *
// Test Result: SKIP 3 APIs in aknAnimData.h,
//              and  3 APIs in aknAnimView.h.
//              CAknDummyListBoxView::Reserved_1() is private,can not be test
//
// ---------------------------------------------------------------------------
//
void   CBCTestDomAknRClassCase::TestAknAnimation()
    {
    // test   APIs in  aknAnimData.h and aknAnimView.h
    CBCTestDomAknAnimatedView* animView =
        CBCTestDomAknAnimatedView::NewLC();// create CAknAnimatedView
    _LIT(
        KCAknAnimatedView,
        "CAknAnimatedView() test" );
    AssertNotNullL( animView,  KCAknAnimatedView);

    // ============================================
    // test CAknAnimationData
    // ============================================

    CBCTestDomAknAnimationData*  animaData =
        CBCTestDomAknAnimationData::NewLC();//create CAknAnimationData
    _LIT(
        KCAknAnimationData,
        "CAknAnimationData() test" );
    AssertNotNullL( animaData,  KCAknAnimationData);


    animaData->ConstructL();
    _LIT(
        KAnimDataConstructL,
        "CAknAnimationData::ConstructL() test" );
    AssertTrueL( ETrue,  KAnimDataConstructL );

    //  R_BCTESTDOMAIWAKN_AKNANIMDATA_BMPANIM_DATA
    animaData->ConstructFromResourceL( R_QGN_NOTE_BATT_FULL_ANIM );
    _LIT(
        KAnimDataConstructFromResourceL,
        "CAknAnimationData::ConstructFromResourceL() test" );
    AssertTrueL( ETrue,  KAnimDataConstructFromResourceL );

    animaData->SetScreenSize( TSize( 50,50 ) );
    _LIT(
        KAnimDataSetScreenSize,
        "CAknAnimationData::SetScreenSize() test" );
    AssertTrueL( ETrue,  KAnimDataSetScreenSize );

    CFbsBitmap* viewBitmap = new ( ELeave ) CFbsBitmap( );
    CleanupStack::PushL( viewBitmap );
    TSize  viewBmpSize( 10,10 );
    viewBitmap->Create( viewBmpSize,EGray16 );
    animaData->SetViewBitmap( viewBitmap );
    _LIT(
        KAnimDataSetViewBitmap,
        "CAknAnimationData::SetViewBitmap() test" );
    AssertTrueL( ETrue,  KAnimDataSetViewBitmap );

    animaData->SetOldBitmap( viewBitmap );
    _LIT(
        KAnimDataSetOldBitmap,
        "CAknAnimationData::SetOldBitmap() test" );
    AssertTrueL( ETrue,  KAnimDataSetOldBitmap );

    animaData->SetClearOldView();
    _LIT(
        KAnimDataSetClearOldView,
        "CAknAnimationData::SetClearOldView() test" );
    AssertTrueL( ETrue,  KAnimDataSetClearOldView );

    animaData->ClearOldView();
    _LIT(
        KAnimDataClearOldView,
        "CAknAnimationData::ClearOldView() test" );
    AssertTrueL( ETrue,  KAnimDataClearOldView );

    animaData->WaitBetweenSections();
    _LIT(
        KAnimDataWaitBetweenSections,
        "CAknAnimationData::WaitBetweenSections() test" );
    AssertTrueL( ETrue,  KAnimDataWaitBetweenSections );

    animaData->SetWaitForeverAtEnd();
    _LIT(
        KAnimDataSetWaitForeverAtEnd,
        "CAknAnimationData::SetWaitForeverAtEnd() test" );
    AssertTrueL( ETrue,  KAnimDataSetWaitForeverAtEnd );

    animaData->WaitForeverAtEnd();
    _LIT(
        KAnimDataWaitForeverAtEnd,
        "CAknAnimationData::WaitForeverAtEnd() test" );
    AssertTrueL( ETrue,  KAnimDataWaitForeverAtEnd );

    animaData->Interval();
    _LIT(
        KAnimDataInterval,
        "CAknAnimationData::Interval() test" );
    AssertTrueL( ETrue,  KAnimDataInterval );


    CWindowGc& gc = CCoeEnv::Static()->SystemGc();
    //animaData->DrawNextAnimationStep( gc );  // panic
    _LIT(
        KAnimDataDrawNextAnimationStep,
        "CAknAnimationData::DrawNextAnimationStep() test" );
    AssertTrueL( ETrue,  KAnimDataDrawNextAnimationStep );


    // ============================================
    // pure panic method,need not test
    // ============================================
    //TAnimStep animStep;
    //TAnimMultiStep multiStep( animStep );
    //animaData->DrawUserAnimationStep( gc, multiStep );// pure panic method
    //_LIT(
    //    KAnimDataDrawUserAnimationStep,
    //    "CAknAnimationData::DrawUserAnimationStep() test" );
    //AssertTrueL( ETrue,  KAnimDataDrawUserAnimationStep );

    //TResourceReader resourceReader;
    //animaData->ConstructUserAnimationStepL(
    //  animStep,
    //  resourceReader);// pure panic method
    //_LIT(
    //    KAnimDataConstructUserAnimationStepL,
    //    "CAknAnimationData::ConstructUserAnimationStepL() test" );
    //AssertTrueL( ETrue,  KAnimDataConstructUserAnimationStepL );

    // ============================================
    // test CAknAnimatedView
    // ============================================
    animView->PreAnimateSetup();
    _LIT(
        KAnimViewPreAnimateSetup,
        "CAknAnimatedView::PreAnimateSetup() test" );
    AssertTrueL( ETrue,  KAnimViewPreAnimateSetup );

    animView->PostAnimateSetup();
    _LIT(
        KAnimViewPostAnimateSetup,
        "CAknAnimatedView::PostAnimateSetup() test" );
    AssertTrueL( ETrue,  KAnimViewPostAnimateSetup );

    animView->SetAnimationData( animaData );
    _LIT(
        KAnimViewSetAnimationData,
        "CAknAnimatedView::SetAnimationData() test" );
    AssertTrueL( ETrue,  KAnimViewSetAnimationData );

    // ===================================================================
    // In the function "CAknAnimatedGc::NewL()",the first
    // clause"CWsScreenDevice* screen = new(ELeave)CWsScreenDevice();"
    // should be "CWsScreenDevice* screen =
    //                  new(ELeave)CWsScreenDevice(
    //                          CEikonEnv::Static()->WsSession() );";
    // otherwise,the clause"animView->AknViewActivatedL"will have a PANIC.
    // ===================================================================

    //TVwsViewId aiwToAknView(
    //        KUidBCTestAiwAkn,
    //        KBCTestAiwAknViewId );
    //animView->AknViewActivatedL(
    //    aiwToAknView,
    //    TUid::Null(),
    //    KNullDesC8() );//panic
    //_LIT(
    //    KAnimViewAknViewActivatedL,
    //    "CAknAnimatedView::AknViewActivatedL() test" );
    //AssertTrueL( ETrue,  KAnimViewAknViewActivatedL);

    
    CEikColumnListBox* listBox = new (ELeave) CAknSingleNumberStyleListBox;
    CleanupStack::PushL( listBox );
    listBox->ConstructL( iContainer );
    CWindowGc*  oldGc =             //warning:Cause "Activate Applications"
        animView->SwapListBoxGc( listBox , &gc ); // menu to disappear.
    animView->SwapListBoxGc( listBox , oldGc );  // Swap back .
    CleanupStack::PopAndDestroy( listBox );
    _LIT(
        KAnimViewSwapListBoxGc,
        "CAknAnimatedView::SwapListBoxGc() test" );
    AssertTrueL( ETrue,  KAnimViewSwapListBoxGc );


    

    CleanupStack::PopAndDestroy( viewBitmap ); // delete viewBitmap

    CleanupStack::PopAndDestroy( animaData ); // delete animaData
    _LIT(
        KDelCAknAnimationData,
        "~CAknAnimationData() test" );
    AssertTrueL( ETrue,  KDelCAknAnimationData );

    CleanupStack::PopAndDestroy( animView ); // delete animView
    _LIT(
        KDelCAknAnimatedView,
        "~CAknAnimatedView() test" );
    AssertTrueL( ETrue,  KDelCAknAnimatedView );
    }

// ---------------------------------------------------------------------------
// CBCTestDomAknRClassCase::TestAknCapServerClient()
// test APIs in akncapserverclient.h
// Test Result:
//
// ---------------------------------------------------------------------------
//
void   CBCTestDomAknRClassCase::TestAknCapServerClient()
    {

    AknStartupApaServerProcess(); //Startup  Server Process
     _LIT(
        KAknStartupApaServerProcess,
        "AknStartupApaServerProcess() test" );
    AssertTrueL( ETrue,  KAknStartupApaServerProcess);


    // ======================================================================
    // Test asynchoronous APIs
    // ======================================================================
    CBCTestDomUiServerShutdownApps* clientShutdownApps =
        CBCTestDomUiServerShutdownApps::NewLC();
    TUid requesterUID = { 0xA00DDDDD };
    clientShutdownApps->ShutdownAppsLD( requesterUID  );
    _LIT(
        KShutdownApps,
        "RAknUiServer::ShutdownApps() test" );
    AssertTrueL( ETrue,  KShutdownApps);

    
    
 
    CBCTestDomUiServerUnlockMedia* clientUnlockMedia =
        CBCTestDomUiServerUnlockMedia::NewLC();
    clientUnlockMedia->UnlockCardLD( EFalse );// make "Activate Applications"
                                              // menu disappear;
    _LIT(
        KUnlockMedia,                       // UnlockMedia() calls
        "RAknUiServer::UnlockMedia() test" ); // ConnectAknServer()internally.
    AssertTrueL( ETrue,  KUnlockMedia);     



                
    // ====================================================================
    // Through RAknUiServer object test another APIs that have NO panics.
    // ====================================================================
    RAknUiServer uiServer;

    TInt errorCode = uiServer.Connect();//call ConnectAknServer() internally.
    if ( errorCode != KErrNone )
        {
        return;
        }
    CleanupClosePushL( uiServer );
    _LIT(
        KConnect,
        "RAknUiServer::Connect() test" );
    AssertTrueL( ETrue,  KConnect);


    TRAPD(
        errStartAknCapserver,
        uiServer.StartAknCapserverL() ;//warning:Leave
        );
    AssertIntL(errStartAknCapserver,errStartAknCapserver);
    _LIT(
        KStartAknCapserverL,
        "RAknUiServer::StartAknCapserverL() test" );
    AssertTrueL( ETrue,  KStartAknCapserverL);

    uiServer.EnableTaskList( ETrue );//call ConnectAknServer() internally.
    uiServer.ConnectAndSendAppsKeySuppress( ETrue );// call ConnectAknServer()
                                    // internally.warning:ETrue make
                                    // "Activate Applications" menu disappear,
                                    // which results in "AutoTest" deadLoop.
    uiServer.ConnectAndSendAppsKeySuppress( EFalse );//warning:Singly calling
    _LIT(                                            //this function cause
        KConnectAndSendAppsKeySuppress,             // ASSERT in server-side.
        "RAknUiServer::ConnectAndSendAppsKeySuppress() test" );
    AssertTrueL( ETrue,  KConnectAndSendAppsKeySuppress ); 
       

 

    uiServer.HideApplicationFromFsw(
        ETrue,
        KUidBCTestAiwAkn.iUid);//call ConnectAknServer() internally.
    _LIT(
        KHideApplicationFromFsw,
        "RAknUiServer::HideApplicationFromFsw() test" );
    AssertTrueL( ETrue,  KHideApplicationFromFsw);



    uiServer.CancelUnlockMedia();//call ConnectAknServer() internally.
    _LIT(
        KCancelUnlockMedia,
        "RAknUiServer::CancelUnlockMedia() test" );
    AssertTrueL( ETrue,  KCancelUnlockMedia);

    uiServer.EnableTaskList( ETrue );//call ConnectAknServer() internally.
    _LIT(
        KEnableTaskList,
        "RAknUiServer::EnableTaskList() test" );
    AssertTrueL( ETrue,  KEnableTaskList);

    uiServer.MakeTaskListVisible( EFalse );//call ConnectAknServer() internally.
    _LIT(
        KMakeTaskListVisible,
        "RAknUiServer::MakeTaskListVisible() test" );
    AssertTrueL( ETrue,  KMakeTaskListVisible);
    
    //recover task list
    uiServer.EnableTaskList( ETrue);
    uiServer.MakeTaskListVisible( ETrue );
    //recover ok.

    uiServer.UpdateTaskList();//call ConnectAknServer() internally.
    _LIT(
        KUpdateTaskList,
        "RAknUiServer::UpdateTaskList() test" );
    AssertTrueL( ETrue,  KUpdateTaskList);

	User::After(KDelay*2);
    CEikonEnv* eikEnv = CEikonEnv::Static();
	TRawEvent event;
    event.Set( TRawEvent::EKeyDown, EStdKeyDevice1 );
    eikEnv->WsSession().SimulateRawEvent( event );

    uiServer.CancelShutdownApps();//uiServer.ShutdownApps(...);
    _LIT(
        KCancelShutdownApps,
        "RAknUiServer::CancelShutdownApps() test" );
    AssertTrueL( ETrue,  KCancelShutdownApps);


    TBitFlags appFlags;
    TInt KAknAppUiBaseFlag = 4 ;
    appFlags.Assign( KAknAppUiBaseFlag, EFalse);
    TInt spLayout = 0;
    TInt spFlags = 0;
    uiServer.SetSgcParams(
      CCoeEnv::Static()->RootWin().Identifier(),
      appFlags,
      spLayout,
      spFlags);
    _LIT(
        KSetSgcParams,
        "RAknUiServer::SetSgcParams() test" );
    AssertTrueL( ETrue,  KSetSgcParams);

    TInt screenMode = KAknScreenModeUnset;
    uiServer.SetSgcParams(
      CCoeEnv::Static()->RootWin().Identifier(),
      appFlags,
      spLayout,
      screenMode);
    _LIT(
        KSetSgcParamsAppScreenMode,
        "RAknUiServer::SetSgcParams(...,aAppScreenMode) test" );
    AssertTrueL( ETrue,  KSetSgcParamsAppScreenMode );


    uiServer.BlockServerStatusPaneRedraws();
    _LIT(
        KBlockServerStatusPaneRedraws,
        "RAknUiServer::BlockServerStatusPaneRedraws() test" );
    AssertTrueL( ETrue,  KBlockServerStatusPaneRedraws);

    uiServer.RedrawServerStatusPane();//draw
    _LIT(
        KRedrawServerStatusPane,
        "RAknUiServer::RedrawServerStatusPane() test" );
    AssertTrueL( ETrue,  KRedrawServerStatusPane);


    uiServer.PrepareForAppExit( CCoeEnv::Static()->RootWin().Identifier() );
    _LIT(
        KPrepareForAppExit,
        "RAknUiServer::PrepareForAppExit() test" );
    AssertTrueL( ETrue,  KPrepareForAppExit);


    uiServer.SetSystemFaded( EFalse );
    _LIT(
        KSetSystemFaded,
        "RAknUiServer::SetSystemFaded() test" );
    AssertTrueL( ETrue,  KSetSystemFaded);

    TBool systemFade = EFalse;
    uiServer.IsSystemFaded( systemFade );
    _LIT(
        KIsSystemFaded,
        "RAknUiServer::IsSystemFaded() test" );
    AssertTrueL( ETrue,  KIsSystemFaded);


    uiServer.RelinquishPriorityToForegroundApp();
    _LIT(
        KRelinquishPriorityToForegroundApp,
        "RAknUiServer::RelinquishPriorityToForegroundApp() test" );
    AssertTrueL( ETrue,  KRelinquishPriorityToForegroundApp);


    HBufC8* packedConfig= uiServer.GetPackedConfigL();
    CleanupStack::PushL( packedConfig );
    _LIT(
        KGetPackedConfigL,
        "RAknUiServer::GetPackedConfigL() test" );
    AssertTrueL( ETrue,  KGetPackedConfigL);
    CleanupStack::PopAndDestroy( packedConfig );


    const TInt KEikStatusPaneBaseDimmedBit = 4;
    uiServer.SetStatusPaneFlags( KEikStatusPaneBaseDimmedBit ) ;
    _LIT(
        KSetStatusPaneFlags,
        "RAknUiServer::SetStatusPaneFlags() test" );
    AssertTrueL( ETrue,  KSetStatusPaneFlags);


    uiServer.SetStatusPaneLayout( R_AVKON_STATUS_PANE_LAYOUT_USUAL) ;
    _LIT(
        KSetStatusPaneLayout,
        "RAknUiServer::SetStatusPaneLayout() test" );
    AssertTrueL( ETrue,  KSetStatusPaneLayout);

    uiServer.BlankScreen();
    _LIT(
        KBlankScreen,
        "RAknUiServer::BlankScreen() test" );
    AssertTrueL( ETrue,  KBlankScreen);


    uiServer.UnblankScreen();
    _LIT(
        KUnblankScreen,
        "RAknUiServer::UnblankScreen() test" );
    AssertTrueL( ETrue,  KUnblankScreen);


    uiServer.SetKeyboardRepeatRate( EAknApplicationDefaulRepeatRate );
    _LIT(
        KSetKeyboardRepeatRate,
        "RAknUiServer::SetKeyboardRepeatRate() test" );
    AssertTrueL( ETrue,  KSetKeyboardRepeatRate);


    uiServer.SetKeyblockMode( EDisableKeyBlock );
    _LIT(
        KSetKeyblockMode,
        "RAknUiServer::SetKeyblockMode() test" );
    AssertTrueL( ETrue,  KSetKeyblockMode);



    uiServer.DoEikonServerConnect();//call ConnectAknServer() internally.
    _LIT(
        KDoEikonServerConnect,
        "RAknUiServer::DoEikonServerConnect() test" );
    AssertTrueL( ETrue,  KDoEikonServerConnect);


    TBool isKeyPadLocked = EFalse;
    uiServer.ShowKeysLockedNote( isKeyPadLocked );
    _LIT(
        KShowKeysLockedNote,
        "RAknUiServer::ShowKeysLockedNote() test" );
    AssertTrueL( ETrue,  KShowKeysLockedNote);


    uiServer.StatusPaneResourceId();//  slow function
    _LIT(
        KStatusPaneResourceId,
        "RAknUiServer::StatusPaneResourceId() test" );
    AssertTrueL( ETrue,  KStatusPaneResourceId);


    TVwsViewId idleView ;
    TInt error = uiServer.GetPhoneIdleViewId( idleView );
    _LIT(
        KGetPhoneIdleViewId,
        "RAknUiServer::GetPhoneIdleViewId() test" );
    AssertTrueL( ETrue,  KGetPhoneIdleViewId);


    TInt resourceId = uiServer.CurrentAppStatuspaneResource();//AppStatuspane
    _LIT(
        KCurrentAppStatuspaneResource,
        "RAknUiServer::CurrentAppStatuspaneResource() test" );
    AssertTrueL( ETrue,  KCurrentAppStatuspaneResource);

    uiServer.SetCurrentAppStatuspaneResource( resourceId );//AppStatuspane
    _LIT(
        KSetCurrentAppStatuspaneResource,
        "RAknUiServer::SetCurrentAppStatuspaneResource() test" );
    AssertTrueL( ETrue,  KSetCurrentAppStatuspaneResource);


    CEikAppUi* app = CEikonEnv::Static()->EikAppUi();
    if ( app )
        {
        CEikApplication* application = app->Application();
        if ( application )
            {
            TInt iSubscriberId = application->AppDllUid().iUid;
            uiServer.SetFgSpDataSubscriberId(iSubscriberId);
            _LIT(
                KSetFgSpDataSubscriberId,
                "RAknUiServer::SetFgSpDataSubscriberId() test" );
            AssertTrueL( ETrue,  KSetFgSpDataSubscriberId);
            }
        }


    uiServer.TaskSwitchingSupressed(); //call ConnectAknServer() inside.
    _LIT(
        KTaskSwitchingSupressed,
        "RAknUiServer::TaskSwitchingSupressed() test" );
    AssertTrueL( ETrue,  KTaskSwitchingSupressed);


    uiServer.HideLongTapAnimation();
    _LIT(
        KHideLongTapAnimation,
        "RAknUiServer::HideLongTapAnimation() test" );
    AssertTrueL( ETrue,  KHideLongTapAnimation);


    TUint keyCode;
    TKeyEvent keyEvent;
    uiServer.GetAliasKeyCode( keyCode, keyEvent, EEventKey );
    _LIT(
        KGetAliasKeyCode,
        "RAknUiServer::GetAliasKeyCode() test" );
    AssertTrueL( ETrue,  KGetAliasKeyCode);


    uiServer.DoNotifierControllerCommand(
        CAknNotifierControllerUtility::DoCancelAll );
    _LIT(
        KDoNotifierControllerCommand,
        "RAknUiServer::DoNotifierControllerCommand() test" );
    AssertTrueL( ETrue,  KDoNotifierControllerCommand);


    //uiServer.RotateScreen(); // Rotate screen first time.
    //uiServer.RotateScreen(); //Rotate screen back
    _LIT(
        KRotateScreen,
        "RAknUiServer::RotateScreen() test" );
    AssertTrueL( ETrue,  KRotateScreen);


    _LIT(KGlobalNoteText,"ShowGlobalNoteL");
    TBuf<20> globalNoteText( KGlobalNoteText );
    uiServer.ShowGlobalNoteL( globalNoteText, EAknCancelGlobalNote );
    _LIT(
        KShowGlobalNoteL,
        "RAknUiServer::ShowGlobalNoteL() test" );
    AssertTrueL( ETrue,  KShowGlobalNoteL);


    TPointerEvent pointerEvent ;
    pointerEvent.iType = TPointerEvent::EButton1Down;
    pointerEvent.iPosition = TPoint( 5,5) ;
    pointerEvent.iParentPosition = TPoint( 6,6) ;
    if( AknLayoutUtils::PenEnabled() )
        {
        uiServer.ShowLongTapAnimation( pointerEvent );//pen must be enabled ,
                                 // or panic ocurred in server-side
                                 //method CAknCapServer::ShowLongTapAnimationL() when
                                 // CAknLongTapAnimation::NewL() return a
                                 // NULL pointer iLongTapAnimation,
                                 //but still call
                                 // iLongTapAnimation->ShowAnimationL(..)
        _LIT(
            KShowLongTapAnimation,
            "RAknUiServer::ShowLongTapAnimation() test" );
        AssertTrueL( ETrue,  KShowLongTapAnimation);       
        }

    uiServer.HideLongTapAnimation();


    TVwsViewId aiwToAknView(
            KUidBCTestAiwAkn,
            KBCTestAiwAknViewId );
    uiServer.CreateActivateViewEventL(
            aiwToAknView,
            TUid::Null(),
            KNullDesC8() );
    _LIT(
        KCreateActivateViewEventL,
        "RAknUiServer::CreateActivateViewEventL() test" );
    AssertTrueL( ETrue,  KCreateActivateViewEventL);

    //uiServer.ServiceUid();//private API
    
      
    
    CleanupStack::Pop();//uiServer
    uiServer.Close();


    }

// ---------------------------------------------------------------------------
// CBCTestDomAknRClassCase::TestAknCustomCursorSupport()
// test APIs in AknCustomCursorSupport.h
// Test Result: OK.
//
// ---------------------------------------------------------------------------
//
void CBCTestDomAknRClassCase::TestAknCustomCursorSupport()
    {
    TRect bitmapRect( 0,0,5,5 );
    AknCustomCursorSupport::CustomBidiTextCursorId(
        EAknFontCategoryUndefined,
        bitmapRect,
        ETrue ); // static function
    _LIT(
        KCustomBidiTextCursorId,
        "AknCustomCursorSupport::CustomBidiTextCursorId() test" );
    AssertTrueL( ETrue,  KCustomBidiTextCursorId );


    TFontSpec fontSpec;
    TTextCursor  textCursor ;
    AknCustomCursorSupport::GetBidiTextCursorFromFontSpec(
        fontSpec,
        EFalse,
        textCursor );    // static function
    _LIT(
        KGetBidiTextCursorFromFontSpec,
        "AknCustomCursorSupport::GetBidiTextCursorFromFontSpec() test" );
    AssertTrueL( ETrue,  KGetBidiTextCursorFromFontSpec );
    }

// ---------------------------------------------------------------------------
// CBCTestDomAknRClassCase::TestAknEikSrvc()
// test APIs in akneiksrvc.h
// Test Result:  SKIP 2 APIs
//
// ---------------------------------------------------------------------------
//
void   CBCTestDomAknRClassCase::TestAknEikSrvc()
    {
    RAknEikAppUiSession  appUiSession;
    TInt error = appUiSession.Connect();
    if ( KErrNone != error )
        {
        return;
        }
    CleanupClosePushL( appUiSession );
    _LIT(
        KRAknEikAppUiSession,
        "RAknEikAppUiSession() test" );
    AssertTrueL( ETrue,  KRAknEikAppUiSession);


    // These functions are deprecated---- begin:

    TBitFlags appFlags;
    appUiSession.SetSgcParams( 0, appFlags,0,0);
    _LIT(KUiSessionSetSgcParams,
        "RAknEikAppUiSession::SetSgcParams() test" );
    AssertTrueL( ETrue,  KUiSessionSetSgcParams );

    appUiSession.BlockServerStatusPaneRedraws();
    _LIT(KUiSessionBlockServerStatusPaneRedraws,
        "RAknEikAppUiSession::KUiSessionBlockServerStatusPaneRedraws()test" );
    AssertTrueL( ETrue,  KUiSessionBlockServerStatusPaneRedraws );

    appUiSession.RedrawServerStatusPane();
    _LIT(KUiSessionRedrawServerStatusPane,
        "RAknEikAppUiSession::RedrawServerStatusPane() test" );
    AssertTrueL( ETrue,  KUiSessionRedrawServerStatusPane );

    appUiSession.PrepareForAppExit( 0 );
    _LIT(KUiSessionPrepareForAppExit,
        "RAknEikAppUiSession::PrepareForAppExit() test" );
    AssertTrueL( ETrue,  KUiSessionPrepareForAppExit );

    appUiSession.SetSystemFaded( EFalse );
    _LIT(KUiSessionSetSystemFaded,
        "RAknEikAppUiSession::SetSystemFaded() test" );
    AssertTrueL( ETrue,  KUiSessionSetSystemFaded );

    TBool systemFade;
    appUiSession.IsSystemFaded( systemFade );
    _LIT(KUiSessionIsSystemFaded,
        "RAknEikAppUiSession::IsSystemFaded() test" );
    AssertTrueL( ETrue,  KUiSessionIsSystemFaded );

    TUid requesterUID = { 0xA00DDDDD };
    TInt timeoutInMicroseconds = 5;
    appUiSession.ShutdownApps(//  have been called
        requesterUID ,        // by Framework. calling it here will
        timeoutInMicroseconds); //cause ASSERT at server-side
    _LIT(KUiSessionShutdownApps,
        "RAknEikAppUiSession::ShutdownApps() called by FW" );
    AssertTrueL( ETrue,  KUiSessionShutdownApps );
    // These functions are deprecated---- end.


    appUiSession.DoSynchWaitForAknCapServer();
    _LIT(
        KUiSessionDoSynchWaitForAknCapServer,
        "RAknEikAppUiSession::DoSynchWaitForAknCapServer() test" );
    AssertTrueL( ETrue,  KUiSessionDoSynchWaitForAknCapServer );


    //appUiSession.AllowNotifierAppServersToLoad();// have been called
                         // by Framework. calling it here will
                         //cause ASSERT at server
                         //-side CEikServAppUi::AknCapServerStartupComplete()
    _LIT(
        KUiSessionAllowNotifierAppServersToLoad,
        "RAknEikAppUiSession::AllowNotifierAppServersToLoad() called by FW" );
    AssertTrueL( ETrue,  KUiSessionAllowNotifierAppServersToLoad );

    CleanupStack::Pop(); // appUiSession
    appUiSession.Close();
    }

