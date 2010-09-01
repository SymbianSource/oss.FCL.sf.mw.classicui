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
* Description:  ?Description
*
*/


#include <w32std.h>
#include <e32const.h>
#include <coecntrl.h>
#include <barsread.h>
#include <badesca.h>
#include <fbs.h>
#include <aknskinnableclock.h>
#include <aknsmallindicator.h>
/*
The "class TAknWindowComponentLayout;" and "class CAknStylusActivatedItem;" 
should be added when "aknstylusactivatedpopupcontent.h" is used.
*/
class CAknStylusActivatedItem;
class TAknWindowComponentLayout;
#include <aknstylusactivatedpopupcontent.h>
#include <aknsoftnotificationparameters.h>
#include <aknnotedialog.h>
#include <aknsoftnotifier.h>
#include <aknstatuspaneutils.h>
#include <aknsyncdraw.h>
#include <akntasklist.h>
#include <akntransitionutils.h>
#include <aknvolumepopup.h>
#include <aknform.h> 
#include <aknsystemfont.h>
#include <s32file.h>
#include <s32strm.h>

#include <avkon.mbg>
#include <bctestdomavkonpsln.rsg>

#include "bctestdomakncase.h"
#include "bctestdomavkonpslncontainer.h"
#include "bctestdomavkonpslnext.h"
#include "bctestdomavkonpsln.hrh"


//CONSTANTS

const TInt KWidth = 25;
const TInt KHeight = 25;
const TInt KShareVolumeUid = 0x000000001;
const TInt KViewerUid = 0x10282D0A;
const TInt KVolumeMaxValue = 10;
const TInt KVolumeMinValue = 0;
const TInt KDesLength = 24;

_LIT( KFilePath, "C:\\bctestlog\\rest.txt" );
_LIT8( KMessage, "Message Descriptor" );
_LIT( KTitle, "Title" );
_LIT( KText, "Text" );
_LIT( KDriver, "C:" );



// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestDomAknCase* CBCTestDomAknCase::NewL( CBCTestDomAvkonPslnContainer* 
    aContainer )
    {
    CBCTestDomAknCase* self = new( ELeave ) CBCTestDomAknCase( 
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
CBCTestDomAknCase::CBCTestDomAknCase( CBCTestDomAvkonPslnContainer* 
    aContainer )
    : iContainer( aContainer )
    {    
    }
    
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestDomAknCase::~CBCTestDomAknCase()
    {  
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestDomAknCase::ConstructL()
    {    
    BuildScriptL();    
    }
    
// ---------------------------------------------------------------------------
// CBCTestDomAknCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestDomAknCase::BuildScriptL()
    { 
    // Add script as your need.   
    AddTestL( DELAY(1), LeftCBA, KeyOK, KeyOK, TEND );    
    }
    
// ---------------------------------------------------------------------------
// CBCTestDomAknCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestDomAknCase::RunL( TInt aCmd )
    {
    if ( aCmd != EBCTestCmdOutline1 )
        {
        return;
        }
    switch ( aCmd )  
        {
        case EBCTestCmdOutline1:
            TestSkinnableClockL();
            TestSmallIndicatorL();
            TestSoftNotifierL();
            TestStatuspaneUtilsL();
            #ifdef RD_SCALABLE_UI_V2
            TestPopupContentL();
            #endif
            TestTransitionL();
            TestCameraSettingPageL();
            TestAknVolumePopupL();
            TestLafSystemFontL();
            TestTaskListL();
            break;
        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// CBCTestDomAknCase::TestSkinnableClock()
// ---------------------------------------------------------------------------
//    
void CBCTestDomAknCase::TestSkinnableClockL()
    {
    // Test some API here
    _LIT( KNewL, "CAknSkinnableClock::NewL invoked" );
    _LIT( KUpdateDisplay, "CAknSkinnableClock::NewL UpdateDisplay invoked" );
    _LIT( KSetFormatL, "CAknSkinnableClock::NewL SetFormatL invoked" );
    _LIT( KDes, "CAknSkinnableClock::~CAknSkinnableClock invoked" );
    
    CAknSkinnableClock* clock = 
        CAknSkinnableClock::NewL( iContainer, ETrue, ETrue );
    CleanupStack::PushL( clock );
    AssertNotNullL( clock, KNewL );
    
    clock->UpdateDisplay();
    AssertTrueL( ETrue, KUpdateDisplay );
    
    clock->SetFormatL( EClockDigital );
    AssertTrueL( ETrue, KSetFormatL );
    
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( KWidth, KHeight );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    
    clock->HandlePointerEventL( event );
    CleanupStack::Pop( clock );
    delete clock;
    AssertTrueL( ETrue, KDes );
    
    }
 
// ---------------------------------------------------------------------------
// CBCTestDomAknCase::TestSmallIndicator
// ---------------------------------------------------------------------------
//       
void CBCTestDomAknCase::TestSmallIndicatorL()
    {
    // Test some API here
    _LIT( KNewL, "CAknSmallIndicator::NewL invoked" );
    _LIT( KDes, "CAknSmallIndicator::~CAknSmallIndicator invoked" );
    _LIT( KNewLC, "CAknSmallIndicator::NewLC invoked" );
    _LIT( KSetIndicatorStateL, 
        "CAknSmallIndicator::SetIndicatorStateL invoked" );
    _LIT( KHandleIndicatorTapL, 
        "CAknSmallIndicator::HandleIndicatorTapL invoked" );
    
    CAknSmallIndicator* indicator = 
        CAknSmallIndicator::NewL( TUid::Uid( KViewerUid ) );
    CleanupStack::PushL( indicator );
    AssertNotNullL( indicator, KNewL );
    
    CleanupStack::Pop( indicator );
    delete indicator;
    AssertTrueL( ETrue, KDes );
    
    indicator = CAknSmallIndicator::NewLC( TUid::Uid( KViewerUid ) );
    AssertNotNullL( indicator, KNewLC );
    
    indicator->SetIndicatorStateL( 0 );
    AssertTrueL( ETrue, KSetIndicatorStateL );
    
    indicator->HandleIndicatorTapL();
    AssertTrueL( ETrue, KHandleIndicatorTapL );
    
    CleanupStack::PopAndDestroy( indicator );
    
    }
 
// ---------------------------------------------------------------------------
// CBCTestDomAknCase::TestSoftNotifier
// ---------------------------------------------------------------------------
//    
void CBCTestDomAknCase::TestSoftNotifierL()
    {
    
    _LIT( KNewL, "CAknSoftNotificationParameters::NewL invoked" );
    _LIT( KDes, "CAknSoftNotificationParameters::\
        ~CAknSoftNotificationParameters invoked" );
    _LIT( KNewLOver, "CAknSoftNotificationParameters::NewL overload invoked" );
    _LIT( KNewLOverLoad, 
        "CAknSoftNotificationParameters::NewL overload invoked" );
    _LIT( KNotifierNewL, "CAknSoftNotifier::NewL invoked" );
    _LIT( KNotifierDes, "CAknSoftNotifier::~CAknSoftNotifier invoked" );
    _LIT( KNewLC, "CAknSoftNotifier::NewLC invoked" );
    _LIT( KAddNotificationL, "CAknSoftNotifier::AddNotificationL invoked" );
    _LIT( KAddNotificationLOverLoad, 
        "CAknSoftNotifier::AddNotificationL overload invoked" );
    _LIT( KSetNotificationCountL, 
        "CAknSoftNotifier::SetNotificationCountL invoked" );
    _LIT( KCancelSoftNotificationL, 
        "CAknSoftNotifier::CancelSoftNotificationL invoked" );
    _LIT( KAddCustomNotificationL, 
        "CAknSoftNotifier::AddCustomNotificationL invoked" );
    _LIT( KSetCustomNotificationCountL, 
        "CAknSoftNotifier::SetCustomNotificationCountL invoked" );
    _LIT( KCancelCustomSoftNotificationL, 
        "CAknSoftNotifier::CancelCustomSoftNotificationL invoked" );
    
                
    CAknSoftNotificationParameters* parameters =
        CAknSoftNotificationParameters::NewL();
    CleanupStack::PushL( parameters );
    AssertNotNullL( parameters, KNewL );
    
    CleanupStack::Pop( parameters );
    delete parameters;
    AssertTrueL( ETrue, KDes );
    

    parameters = CAknSoftNotificationParameters::
        NewL( KFilePath, 0, 0, 0, CAknNoteDialog::ENoTone);
    CleanupStack::PushL( parameters ); 
    AssertTrueL( ETrue, KNewLOver );
    CleanupStack::Pop( parameters );
    delete parameters;
    
    parameters = CAknSoftNotificationParameters::NewL( KDriver, 0, 0, 0,
        CAknNoteDialog::ENoTone,
        KNullViewId, KNullUid,
        0, KMessage );
    CleanupStack::PushL( parameters );
    AssertNotNullL( parameters, KNewLOverLoad );
    
    CAknSoftNotifier* notifier = CAknSoftNotifier::NewL();
    CleanupStack::PushL( notifier );
    AssertNotNullL( notifier, KNotifierNewL );
    CleanupStack::Pop( notifier );
    delete notifier;
    AssertTrueL( ETrue, KNotifierDes );
    
    notifier = CAknSoftNotifier::NewLC();
    AssertNotNullL( notifier, KNewLC );
    
    notifier->AddNotificationL( ENetworkInformationNotification );
    AssertTrueL( ETrue, KAddNotificationL );
    
    notifier->AddNotificationL( ENetworkInformationNotification, 1 );
    AssertTrueL( ETrue, KAddNotificationLOverLoad );
    
    notifier->SetNotificationCountL( ENetworkInformationNotification, 1 );
    AssertTrueL( ETrue, KSetNotificationCountL );
    
    notifier->CancelSoftNotificationL( ENetworkInformationNotification );
    AssertTrueL( ETrue, KCancelSoftNotificationL );
    
    notifier->AddCustomNotificationL( *parameters );
    AssertTrueL( ETrue, KAddCustomNotificationL );
    
    notifier->SetCustomNotificationCountL( *parameters, 1 );
    AssertTrueL( ETrue, KSetCustomNotificationCountL );
    
    notifier->CancelCustomSoftNotificationL( *parameters );
    AssertTrueL( ETrue, KCancelCustomSoftNotificationL );
    
    CleanupStack::PopAndDestroy( notifier );
    CleanupStack::PopAndDestroy( parameters );
    
    }

// ---------------------------------------------------------------------------
// CBCTestDomAknCase::TestStatuspaneUtils
// ---------------------------------------------------------------------------
//
void CBCTestDomAknCase::TestStatuspaneUtilsL()
    {
    
    _LIT( KStaconPaneActive, "AknStatuspaneUtils::StaconPaneActive invoked" );
    _LIT( KStaconSoftKeysLeft, 
        "AknStatuspaneUtils::StaconSoftKeysLeft invoked" );
    _LIT( KStaconSoftKeysRight, 
        "AknStatuspaneUtils::StaconSoftKeysRight invoked" );
    _LIT( KIdleLayoutActive, "AknStatuspaneUtils::IdleLayoutActive invoked" );
    _LIT( KFlatLayoutActive, "AknStatuspaneUtils::FlatLayoutActive invoked" );
    _LIT( KUsualLayoutActive, 
        "AknStatuspaneUtils::UsualLayoutActive invoked" );
    _LIT( KSmallLayoutActive, 
        "AknStatuspaneUtils::SmallLayoutActive invoked" );
    _LIT( KTouchPaneCompatibleLayoutActive, 
        "AknStatuspaneUtils::TouchPaneCompatibleLayoutActive invoked" );
    _LIT( KExtendedStaconPaneActive, 
        "AknStatuspaneUtils::ExtendedStaconPaneActive invoked" );
    _LIT( KExtendedFlatLayoutActive, 
        "AknStatuspaneUtils::ExtendedFlatLayoutActive invoked" );
    
    TBool val = AknStatuspaneUtils::StaconPaneActive();
    AssertTrueL( ETrue, KStaconPaneActive );
    
    val = AknStatuspaneUtils::StaconSoftKeysLeft();
    AssertTrueL( ETrue, KStaconSoftKeysLeft );
    
    val = AknStatuspaneUtils::StaconSoftKeysRight();
    AssertTrueL( ETrue, KStaconSoftKeysRight );
    
    val = AknStatuspaneUtils::IdleLayoutActive();
    AssertTrueL( ETrue, KIdleLayoutActive );
    
    val = AknStatuspaneUtils::FlatLayoutActive();
    AssertTrueL( ETrue, KFlatLayoutActive );
    
    val = AknStatuspaneUtils::UsualLayoutActive();
    AssertTrueL( ETrue, KUsualLayoutActive );
    
    val = AknStatuspaneUtils::SmallLayoutActive();
    AssertTrueL( ETrue, KSmallLayoutActive );
    
    val = AknStatuspaneUtils::TouchPaneCompatibleLayoutActive();
    AssertTrueL( ETrue, KTouchPaneCompatibleLayoutActive );
    
    val = AknStatuspaneUtils::ExtendedStaconPaneActive();
    AssertTrueL( ETrue, KExtendedStaconPaneActive );
    
    val = AknStatuspaneUtils::ExtendedFlatLayoutActive();
    AssertTrueL( ETrue, KExtendedFlatLayoutActive );
    }

// ---------------------------------------------------------------------------
// CBCTestDomAknCase::TestPopupContent()
// ---------------------------------------------------------------------------
//
void CBCTestDomAknCase::TestPopupContentL()
    {
    
    _LIT( KNewL, "CAknStylusActivatedPopUpContent::NewL invoked" );
    _LIT( KNewLOverload, "CAknStylusActivatedPopUpContent\
                         ::NewL overload invoked" );
    _LIT( KNewLRes, "CAknStylusActivatedPopUpContent\
                    ::NewL int resid overload invoked" );
    _LIT( KNewLReader, "CAknStylusActivatedPopUpContent\
                    ::NewL reader resid overload invoked" );
    _LIT( KDes, "CAknStylusActivatedPopUpContent::\
                ~CAknStylusActivatedPopUpContent invoked" );
    _LIT( KComponentControl, "CAknStylusActivatedPopUpContent::\
                              ComponentControl invoked" );
    _LIT( KCountComponentControls, 
          "CAknStylusActivatedPopUpContent::CountComponentControls invoked" );
    _LIT( KMinimumSize, 
          "CAknStylusActivatedPopUpContent::MinimumSize invoked" );
    _LIT( KHandleResourceChange, 
          "CAknStylusActivatedPopUpContent::HandleResourceChange() invoked" );
    _LIT( KSetContainerWindowL, 
          "CAknStylusActivatedPopUpContent::SetContainerWindowL() invoked" );
    _LIT( KSetCommandObserver, 
          "CAknStylusActivatedPopUpContent::SetCommandObserver invoked" );
    _LIT( KHandlePointerEventL, 
          "CAknStylusActivatedPopUpContent::HandlePointerEventL invoked" );
    _LIT( KHandleControlEventL, 
          "CAknStylusActivatedPopUpContent::HandleControlEventL invoked" );

    CAknStylusActivatedPopUpContent* content 
        = CAknStylusActivatedPopUpContent::NewL( KTitle, KText );
    CleanupStack::PushL( content );
    AssertNotNullL( content, KNewL );
    
    CleanupStack::Pop( content );
    delete content;
    AssertTrueL( ETrue, KDes );
    
    TBuf<KDesLength> linktxt( KTitle );
    RArray<TAknContentLink> array;
    TAknContentLink link;
    link.iLinkText = &linktxt;
    CleanupClosePushL( array );
    array.Append( link );
    content = CAknStylusActivatedPopUpContent::NewL( KTitle, KText, array );
    CleanupStack::PushL( content );
    AssertNotNullL( content, KNewLOverload );
    CleanupStack::Pop( content );
    delete content;
    CleanupStack::PopAndDestroy( &array );
    
    content = CAknStylusActivatedPopUpContent::
              NewL( R_BCTESTDOMAVKONPSLN_AVKON_CONTENT );
    CleanupStack::PushL( content );
    AssertNotNullL( content, KNewLRes );
    
    CAknForm* frm = new ( ELeave ) CAknForm();
    CleanupStack::PushL( frm );
    frm->ConstructL();
    
    content->SetCommandObserver( *frm );
    AssertTrueL( ETrue, KSetCommandObserver );
    
    content->HandleResourceChange( 0 );
    AssertTrueL( ETrue, KHandleResourceChange );
    
    content->SetContainerWindowL( *iContainer );
    AssertTrueL( ETrue, KSetContainerWindowL );
    
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( KWidth, KHeight );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    content->HandlePointerEventL( event );
    AssertTrueL( ETrue, KHandlePointerEventL );
    
    content->HandleControlEventL( iContainer, 
        MCoeControlObserver::EEventRequestExit );
    AssertTrueL( ETrue, KHandleControlEventL );
    
    CleanupStack::Pop( frm );
    CleanupStack::Pop( content );

    delete content;
    delete frm;
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, 
        R_BCTESTDOMAVKONPSLN_AVKON_CONTENT );
    CCoeControl* ctrl = CAknStylusActivatedPopUpContent::NewL( reader );
    CleanupStack::PushL( ctrl );
    AssertNotNullL( ctrl, KNewLReader );
    
    ctrl->ComponentControl( 0 );
    AssertTrueL( ETrue, KComponentControl );
    
    ctrl->CountComponentControls();
    AssertTrueL( ETrue, KCountComponentControls );
    
    ctrl->MinimumSize();
    AssertTrueL( ETrue, KMinimumSize );
    
    CleanupStack::PopAndDestroy( ctrl );
    CleanupStack::PopAndDestroy(); // reader
    
    }


// ---------------------------------------------------------------------------
// CBCTestDomAknCase::TestSyncDraw()
// ---------------------------------------------------------------------------
//
void CBCTestDomAknCase::TestSyncDrawL()
    {
    
    _LIT( KConstruct, "TAknSyncControlDrawer::TAknSyncControlDrawer invoked" );
    _LIT( KSetControl, "TAknSyncControlDrawer::SetControl invoked" );
    _LIT( KMasrPrepareForDraw, 
        "TAknSyncControlDrawer::MasrPrepareForDraw invoked" );
    _LIT( KMasrDraw, "TAknSyncControlDrawer::MasrDraw invoked" );
    _LIT( KMasrDeactivateGc, 
        "TAknSyncControlDrawer::MasrDeactivateGc invoked" );
    _LIT( KMasrActivateGc,
        "TAknSyncControlDrawer::MasrActivateGc invoked" );
    _LIT( KNewL, "CAknDrawSynchronizer::NewL invoked" );
    _LIT( KAddL, "CAknDrawSynchronizer::AddL invoked" ); 
    _LIT( KSignal, "CAknDrawSynchronizer::Signal invoked" );
    _LIT( KRemove, "CAknDrawSynchronizer::Remove invoked" );
    _LIT( KDes, "CAknDrawSynchronizer::~CAknDrawSynchronizer invoked" );
          
    TAknSyncControlDrawer drawer;
    AssertTrueL( ETrue, KConstruct );
    
    drawer.SetControl( iContainer );
    AssertTrueL( ETrue, KSetControl );
    
    drawer.MasrPrepareForDraw();
    AssertTrueL( ETrue, KMasrPrepareForDraw );
    
    drawer.MasrDraw();
    AssertTrueL( ETrue, KMasrDraw );
    
    drawer.MasrDeactivateGc();
    AssertTrueL( ETrue, KMasrDeactivateGc );
    
    drawer.MasrActivateGc();
    AssertTrueL( ETrue, KMasrActivateGc );
    
    CAknDrawSynchronizer* sync = CAknDrawSynchronizer::NewL();
    CleanupStack::PushL( sync );
    AssertNotNullL( sync, KNewL );

    sync->AddL( &drawer );
    AssertTrueL( ETrue, KAddL );
    
    sync->Signal( &drawer );
    AssertTrueL( ETrue, KSignal );
    
    sync->Remove( &drawer );
    AssertTrueL( ETrue, KRemove );
    
    CleanupStack::PopAndDestroy( sync );
    AssertTrueL( ETrue, KDes );
    
    }

// ---------------------------------------------------------------------------
// CBCTestDomAknCase::TestTaskListL()
// ---------------------------------------------------------------------------
//    
void CBCTestDomAknCase::TestTaskListL()
    {
    
    _LIT( KNewL, "CAknTaskList::NewL invoked" );
    _LIT( KNewLC, "CAknTaskList::NewLC invoked" );
    _LIT( KDes, "CAknTaskList::~CAknTaskList invoked" );
    _LIT( KUpdateListL, "CAknTaskList::UpdateListL invoked" );
    _LIT( KWgArray, "CAknTaskList::WgArray invoked" );
    _LIT( KFindRootApp, "CAknTaskList::FindRootApp invoked" );   
    _LIT( KIsRootWindowGroup, "CAknTaskList::IsRootWindowGroup invoked" );   
    
    CAknTaskList* tasklist = 
        CAknTaskList::NewL( CCoeEnv::Static()->WsSession() );
    CleanupStack::PushL( tasklist );
    AssertNotNullL( tasklist, KNewL );
    
    CleanupStack::Pop( tasklist );
    delete tasklist;
    AssertTrueL( ETrue, KDes );
    
    tasklist = CAknTaskList::NewLC( CCoeEnv::Static()->WsSession() );
    AssertNotNullL( tasklist, KNewLC );
    
    tasklist->UpdateListL();
    AssertTrueL( ETrue, KUpdateListL );
    
    tasklist->WgArray();
    AssertTrueL( ETrue, KWgArray );
    
    tasklist->FindRootApp( KNullUid );
    AssertTrueL( ETrue, KFindRootApp );
    
    TBool val = tasklist->IsRootWindowGroup( 0 );
    AssertTrueL( ETrue, KIsRootWindowGroup );
    
    CleanupStack::PopAndDestroy( tasklist );
    }
    
// ---------------------------------------------------------------------------
// CBCTestDomAknCase::TestTransitionL()
// ---------------------------------------------------------------------------
//    
void CBCTestDomAknCase::TestTransitionL()
    {
    
    _LIT( KCAknTransition, "CAknTransition::CAknTransition invoked" );
    _LIT( KAddObserver, "CAknTransitionUtils::AddObserver invoked" );
    _LIT( KRemoveObserver, "CAknTransitionUtils::RemoveObserver invoked" );
    _LIT( KGetState, "CAknTransitionUtils::GetState invoked" );
    _LIT( KSetData, "CAknTransitionUtils::SetData invoked" );
    _LIT( KGetData, "CAknTransitionUtils::GetData invoked" );
    _LIT( KRemoveData, "CAknTransitionUtils::RemoveData invoked" );
    _LIT( KSetAllParents, "CAknTransitionUtils::SetAllParents invoked" );
    _LIT( KTransitionsEnabled, 
        "CAknTransitionUtils::TransitionsEnabled invoked" );
    _LIT( KMakeVisibleSubComponents, 
        "CAknTransitionUtils::MakeVisibleSubComponents invoked" );
    _LIT( KGetDemarcation, "CAknTransitionUtils::GetDemarcation invoked" );
    _LIT( KDes, "CAknTransition::~CAknTransition invoked" );
    
    CAknTransitionExt* observer = new ( ELeave ) CAknTransitionExt;
    CleanupStack::PushL( observer );
    AssertNotNullL( observer, KCAknTransition );
    
    TInt res = CAknTransitionUtils::AddObserver( observer, 
        CAknTransitionUtils::EEventWsBufferRedirection );
    AssertTrueL( ETrue, KAddObserver );
    
    CAknTransitionUtils::RemoveObserver( observer, 
        CAknTransitionUtils::EEventWsBufferRedirection );
    AssertTrueL( ETrue, KRemoveObserver );
    
    TInt stat;
    CAknTransitionUtils::GetState( 
        CAknTransitionUtils::EEventWsBufferRedirection, 
        &stat );
    AssertTrueL( ETrue, KGetState );
    
    TInt skey( 0 ),sdata( 0 );
    CAknTransitionUtils::SetData( skey, &sdata );
    AssertTrueL( ETrue, KSetData );
    
    CAknTransitionUtils::GetData( skey );
    AssertTrueL( ETrue, KGetData );
    
    CAknTransitionUtils::RemoveData( skey );
    AssertTrueL( ETrue, KRemoveData );
    
    CAknTransitionUtils::SetAllParents( iContainer );
    AssertTrueL( ETrue, KSetAllParents );
    
    CAknTransitionUtils::TransitionsEnabled( sdata );
    AssertTrueL( ETrue, KTransitionsEnabled );
    
    CAknTransitionUtils::MakeVisibleSubComponents( iContainer, ETrue );
    AssertTrueL( ETrue, KMakeVisibleSubComponents );
    
    TRect rect;
    CAknTransitionUtils::GetDemarcation( 
        CAknTransitionUtils::EOptionsMenu, 
        rect );
    AssertTrueL( ETrue, KGetDemarcation );
    
    CleanupStack::PopAndDestroy( observer );
    AssertTrueL( ETrue, KDes );
    
    }
    
// ---------------------------------------------------------------------------
// CBCTestDomAknCase::TestCameralSettingPageL()
// ---------------------------------------------------------------------------
//    
void CBCTestDomAknCase::TestCameraSettingPageL()
    {
    
    _LIT( KCAknTransparentCameraSettingPage, 
        "CAknTransparentCameraSettingPage::\
        CAknTransparentCameraSettingPage invoked" );
    _LIT( KCAknTransparentCameraSettingPageDes,
        "CAknTransparentCameraSettingPage::\
        ~CAknTransparentCameraSettingPage invoked" );
    _LIT( KCAknTransparentCameraSettingPageOverload,
        "CAknTransparentCameraSettingPage::\
        CAknTransparentCameraSettingPage overload invoked" );
    _LIT( KConstructL,
        "CAknTransparentCameraSettingPage::Constructor invoked" );
    _LIT( KListBoxControl,
        "CAknTransparentCameraSettingPage::ListBoxControl invoked" );
    _LIT( KSetItemArrayAndSelectionL,
        "CAknTransparentCameraSettingPage::\
        SetItemArrayAndSelectionL invoked" );
    _LIT( KChangeBackground,
        "CAknTransparentCameraSettingPage::ChangeBackground invoked" );
    _LIT( KSetBitmapPositionAndClipRect,
        "CAknTransparentCameraSettingPage::\
        SetBitmapPositionAndClipRect invoked" );
    _LIT( KUpdateSettingL,
        "CAknTransparentCameraSettingPage::UpdateSettingL invoked" );
    _LIT( KDynamicInitL,
        "CAknTransparentCameraSettingPage::DynamicInitL invoked" );
    _LIT( KSelectCurrentItemL,
        "CAknTransparentCameraSettingPage::SelectCurrentItemL invoked" );
    _LIT( KProcessCommandL,
        "CAknTransparentCameraSettingPage::ProcessCommandL invoked" );
    _LIT( KOfferKeyEventL,
        "CAknTransparentCameraSettingPage::OfferKeyEventL invoked" );
    _LIT( KSizeChanged,
        "CAknTransparentCameraSettingPage::SizeChanged invoked" );
    _LIT( KDraw,
        "CAknTransparentCameraSettingPage::Draw invoked" );
    _LIT( KExecuteLD,
        "CAknTransparentCameraSettingPage::ExecuteLD invoked" );
    _LIT( KHandleListBoxEventL,
        "CAknTransparentCameraSettingPage::HandleListBoxEventL invoked" );
    _LIT( KHandleResourceChange,
        "CAknTransparentCameraSettingPage::HandleResourceChange invoked" );
    _LIT( KHandleControlEventL,
        "CAknTransparentCameraSettingPage::HandleControlEventL invoked" );
    _LIT( KWriteInternalStateL,
        "CAknTransparentCameraSettingPage::WriteInternalStateL invoked" );
       
    TInt index( 0 );
    CPtrCArray* array = new ( ELeave ) CPtrCArray( 1 );
    TBuf<KDesLength> txt( KTitle );
    array->AppendL( txt );
    CleanupStack::PushL( array );
    
    CAknTransparentCameraSettingPageExt* settingpage = 
        new ( ELeave ) CAknTransparentCameraSettingPageExt( 
        R_BCTESTDOMAVKONPSLN_CHECKBOX_SETTING_PAGE, 
        index, 
        array );
    CleanupStack::PushL( settingpage ); 
    AssertNotNullL( settingpage, KCAknTransparentCameraSettingPage );
    

    settingpage->ConstructL();
    CleanupStack::Pop( settingpage );
    
    TRect rect( 0, 0, 0, 0 );
    settingpage->Draw( rect );
    AssertTrueL( ETrue, KDraw );
    settingpage->ExecuteLD( CAknSettingPage::EUpdateWhenAccepted );
    AssertTrueL( ETrue, KExecuteLD );
    
    settingpage = NULL;
    AssertTrueL( ETrue, KCAknTransparentCameraSettingPageDes );

    settingpage = new ( ELeave ) CAknTransparentCameraSettingPageExt(
        &KTitle,
        0,
        0,
        0,
        R_BCTESTDOMAVKONPSLN_CHECKBOX_SETTING_PAGE,
        index,
        array );
    CleanupStack::PushL( settingpage );
    AssertNotNullL( settingpage, KCAknTransparentCameraSettingPageOverload );
    
    settingpage->ConstructL();
    AssertTrueL( ETrue, KConstructL );
    
    settingpage->ListBoxControl();
    AssertTrueL( ETrue, KListBoxControl );
    
    CEikListBox* list = new ( ELeave ) CEikListBox();
    CleanupStack::PushL( list );
    settingpage->HandleListBoxEventL( list, 
        MEikListBoxObserver::
        EEventEnterKeyPressed );
    AssertTrueL( ETrue, KHandleListBoxEventL );
    CleanupStack::PopAndDestroy( list );
    
    settingpage->SetItemArrayAndSelectionL( array, 0 );
    AssertTrueL( ETrue, KSetItemArrayAndSelectionL );
    
    TPoint point( 0, 0 );
    settingpage->SetBitmapPositionAndClipRect( point, rect );
    AssertTrueL( ETrue, KSetBitmapPositionAndClipRect );
    
    settingpage->HandleResourceChange( index );
    AssertTrueL( ETrue, KHandleResourceChange );
    
    settingpage->UpdateSettingL();
    AssertTrueL( ETrue, KUpdateSettingL );
    
    settingpage->DynamicInitL();
    AssertTrueL( ETrue, KDynamicInitL );
    
    settingpage->SelectCurrentItemL();
    AssertTrueL( ETrue, KSelectCurrentItemL );
    
    settingpage->HandleControlEventL( iContainer, 
        MCoeControlObserver::EEventRequestCancel );
    AssertTrueL( ETrue, KHandleControlEventL );
    
    TKeyEvent keyEvent = { EKeyPause, EStdKeySpace, 0, 0  };
    
    settingpage->OfferKeyEventL( keyEvent, EEventKey );
    AssertTrueL( ETrue, KOfferKeyEventL );
    
    settingpage->SizeChanged();
    AssertTrueL( ETrue, KSizeChanged );
    
    CFbsBitmap* bmp = NULL;
    bmp = AknIconUtils::CreateIconL( AknIconUtils::AvkonIconFileName(), 
        EMbmAvkonQgn_prop_nrtyp_note );
    CleanupStack::PushL( bmp );
    AssertNotNullL( bmp );
    
    settingpage->SetBitmapPositionAndClipRect( point, rect, ETrue );
    AssertTrueL( ETrue, KSetBitmapPositionAndClipRect );
    
    settingpage->ChangeBackground( bmp );
    AssertTrueL( ETrue, KChangeBackground );
    
    CCoeEnv::Static()->AppUi()->AddToStackL( settingpage );
    settingpage->ProcessCommandL( EAknSoftkeyHide );
    AssertTrueL( ETrue, KProcessCommandL );
    
    CCoeEnv::Static()->AppUi()->RemoveFromStack( settingpage );
    
    RFileWriteStream stream;
    stream.PushL();
    stream.Replace( CCoeEnv::Static()->FsSession(), KFilePath, EFileWrite );
    settingpage->WriteInternalStateL( stream );
    AssertTrueL( ETrue, KWriteInternalStateL );
    stream.Pop();
    stream.Close();
    
    CleanupStack::PopAndDestroy( bmp );
    CleanupStack::PopAndDestroy( settingpage );
    CleanupStack::PopAndDestroy( array );
    
    }
    
// ----------------------------------------------------------------------------
// Test AknVolumePopup.
// ----------------------------------------------------------------------------
//    
void CBCTestDomAknCase::TestAknVolumePopupL()
    {
    _LIT( KNewL, "CAknVolumePopup::NewL invoked" );
    _LIT( KNewLOverLoad, "CAknVolumePopup::NewL overload invoked" );
    _LIT( KConstructFromResource, 
        "CAknVolumePopup::ConstructFromResourceL invoked" );
    _LIT( KCountComponentControls, 
        "CAknVolumePopup::CountComponentControls invoked" );
    _LIT( KComponentControl, "CAknVolumePopup::ComponentControl invoked" );
    _LIT( KHandlePointerEventL, "CAknVolumePopup::HandlePointerEventL invoked" );
    _LIT( KOfferKeyEventL, "CAknVolumePopup::OfferKeyEventL invoked" );
    _LIT( KHandleControlEventL, "CAknVolumePopup::HandleControlEventL invoked" );
    _LIT( KHandleVolumeKeyEventL, 
        "CAknVolumePopup::HandleVolumeKeyEventL invoked" );
    _LIT( KSetRange, "CAknVolumePopup::SetRange invoked" );
    _LIT( KGetRange, "CAknVolumePopup::GetRange invoked" );
    _LIT( KValue, "CAknVlumePopup::Value invoked" );
    _LIT( KSetTitleTextL, "CAknVlumePopup::SetTitleTextL invoked" );
    _LIT( KShowProfileName, "CAknVlumePopup::ShowProfileName invoked" );
    _LIT( KShowVolumePopupL, "CAknVlumePopup::ShowVolumePopupL invoked" );
    _LIT( KCloseVolumePopup, "CAknVlumePopup::CloseVolumePopup invoked" );
         
    TUid uid = TUid::Uid( KShareVolumeUid );
    CAknVolumePopup* vol = CAknVolumePopup
         ::NewL( uid, KTitle, KVolumeMaxValue );
    CleanupStack::PushL( vol );
    AssertNotNullL( vol, KNewL );
    CleanupStack::Pop( vol );
    delete vol;
    vol = NULL;
   
    vol = CAknVolumePopup
        ::ConstructFromResourceL( R_AVKON_POPUP_VOLUME_INDICATOR );
    CleanupStack::PushL( vol );
    AssertNotNullL( vol, KConstructFromResource );
    CleanupStack::Pop( vol );
    delete vol;
    vol = NULL;
    
    vol = CAknVolumePopup::NewL( KVolumeMaxValue );
    CleanupStack::PushL( vol );
    AssertNotNullL( vol, KNewLOverLoad );
 
    TInt val = vol->CountComponentControls();
    AssertTrueL( ETrue, KCountComponentControls );
    
    vol->ComponentControl( val );
    AssertTrueL( ETrue, KComponentControl );
    
    TWsEvent wsEvent;
    TPointerEvent* ptEvent = wsEvent.Pointer();
    vol->HandlePointerEventL( *ptEvent );
    AssertTrueL( ETrue, KHandlePointerEventL );
    
    TKeyEvent keyEvent = { EKeyPause, EStdKeySpace, 0, 0  };
    
    vol->OfferKeyEventL( keyEvent, EEventKey );
    AssertTrueL( ETrue, KOfferKeyEventL );
    
    vol->HandleControlEventL( iContainer, 
        MCoeControlObserver::EEventRequestCancel );
    AssertTrueL( ETrue, KHandleControlEventL );
    
    vol->HandleVolumeKeyEventL( keyEvent, EEventKey );
    AssertTrueL( ETrue, KHandleVolumeKeyEventL );
    
    vol->SetRange( KVolumeMinValue, KVolumeMaxValue );
    AssertTrueL( ETrue, KSetRange );
    
    TInt maxVal, minVal;
    vol->GetRange( minVal, maxVal );
    AssertTrueL( ETrue, KGetRange );
    
    vol->Value();
    AssertTrueL( ETrue, KValue );
    
    vol->SetTitleTextL( KTitle );
    AssertTrueL( ETrue, KSetTitleTextL );
    
    vol->ShowProfileName( ETrue );
    AssertTrueL( ETrue, KShowProfileName );
    
    vol->ShowVolumePopupL();
    AssertTrueL( ETrue, KShowVolumePopupL );
    
    vol->CloseVolumePopup();
    AssertTrueL( ETrue, KCloseVolumePopup );
    
    CleanupStack::Pop( vol );//vol
    delete vol;
    
    }
    
// ----------------------------------------------------------------------------
// TestLafSystemFontL
// ----------------------------------------------------------------------------
//    
void CBCTestDomAknCase::TestLafSystemFontL()
    {
    _LIT( KNewL, "CLafSystemFont::NewL() invoked" );
    _LIT( KFont, "CLafSystemFont::Font() invoked" );
    _LIT( KUid, "CLafSystemFont::Uid() invoked" );
    _LIT( KDes, "CLafSystemFont::~CLafSystemFont() invoked" );
    CLafSystemFont* font = CLafSystemFont::NewL( KNullUid, NULL );
    CleanupStack::PushL( font );
    AssertNotNullL( font, KNewL );
    
    font->Font();
    AssertTrueL( ETrue, KFont );
    
    font->Uid();
    AssertTrueL( ETrue, KUid );
    
    CleanupStack::Pop( font );
    delete font;
    AssertTrueL( ETrue, KDes );
    }
//end of file
