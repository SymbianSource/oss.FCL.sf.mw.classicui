/*
* Copyright (c) 2002-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Control container for fastswap.
*
*/


// INCLUDE FILES
#include <gulicon.h>
#include <eikbtgpc.h>
#include <eikmop.h>
#include <AknQueryDialog.h>
#include <eiksrvui.rsg>
#include <StringLoader.h>
#include <AknsDrawUtils.h>
#include <AknsControlContext.h>
#include <avkon.mbg>
#include <AknsFrameBackgroundControlContext.h>
#include <aknlayoutscalable_avkon.cdl.h>
#include <layoutmetadata.cdl.h>
#include <AknIconUtils.h>
#include <eikfrlbd.h>
#include <apgwgnam.h>
#include <AknInfoPopupNoteController.h> // tooltip
#include <AknBidiTextUtils.h> // method ConvertToVisualAndClipL
#include <skinlayout.cdl.h>

#include <akntransitionutils.h>
#include <akntranseffect.h>
#include <gfxtranseffect/gfxtranseffect.h>
#include <featmgr.h>
#include <aknglobalpopupprioritycontroller.h>
#include <centralrepository.h>
#include <AknTasHook.h>
#include <touchfeedback.h>

#ifdef RD_UI_TRANSITION_EFFECTS_LIST
#include <aknlistloadertfx.h>
#include <aknlistboxtfxinternal.h>
#endif // RD_UI_TRANSITION_EFFECTS_LIST

#include <aknmemorycardui.rsg>
#include <aknlongtapanimation.h>
#include <aknstyluspopupmenu.h>
#include <aknpointereventsuppressor.h>
#include <pslninternalcrkeys.h>
#include <AknStatuspaneUtils.h>

#include "AknFastswapWindowControl.h"
#include "AknFastswapWindowGrid.h"
#include "AknCapServerEntry.h"
#include "akntrace.h"
void InvalidateWindows( CCoeControl* aControl )
    {
    if ( aControl )
        {
        if ( aControl->OwnsWindow() )
            {
            ( (RWindow*) aControl->DrawableWindow() )->ClearRedrawStore();
            }

        for ( TInt i = aControl->CountComponentControls() - 1; i >= 0; --i )
            {
            InvalidateWindows( aControl->ComponentControl( i ) );
            }
        }
    }

const TInt KFSWArrayGranularity = 4;
const TInt KMinimumSupportedApps = 20;

const TBool KVerticalOrientation = EFalse;
const TBool KLeftToRight = ETrue;
const TBool KRightToLeft = EFalse;
const TBool KTopToBottom = ETrue;

const TInt KTooltipTimeBefore = 600;
const TInt KTooltipTimeView = 1500;

// Values for touch mode tooltip.
const TInt KTooltipTimeBeforeTouch = 0;  
const TInt KTooltipTimeViewTouch = 0; // Shown until canceled

// Always shown applications spesified in the ui specs.
const TInt KAlwaysShownAppCount = 3;
const TUid KMenuAppUid  = {0x101F4CD2};
const TUid KSearchAppUid  = {0x0EFC346A};

// new idle from 3.2 onwards, old idle uid is 0x101FD64C
const TUid KIdleAppUid  = {0x102750F0}; 

const TInt KApplicationWithoutWG = KErrNotFound;

const TInt KWidgetWithoutWG = KErrGeneral;
// Uid of the Widget application.
const TUid KWidgetAppUid  = {0x10282822};

// Matrix Menu P&S category 
const TUid KFSWMMenuPSCat = {0x101F4CD2};
// Key that stores last used - current view (it is text value)
const TUint KFSWMMenuLastViewKey = 0x01;
// name of folder view
_LIT(KFSWMMenuFolderView, "foldersuite");

const TInt KTimeDelayBeforeAnimation = 200000;  // 0.2 seconds
const TInt KLongTapDelay = 800000;  // 0.8 seconds
const TInt KTimeNeverHappenEvent = 100000000; // 100 seconds 
const TInt KPressedDownEffectTime = 500000;//0.5 seconds
enum TAknCapServerCommands
    {
    EAknCapServerCmdOpen = 0x6100, 
    EAknCapServerCmdClose      
    };

NONSHARABLE_CLASS(CAknFastSwapData) : public CBase, 
                                      public MAknTransitionUtilsObserver
  {
  public:
      CAknFastSwapData(TInt aKey, CAknInfoPopupNoteController* aTooltip);
  
  private:
      TInt AknTransitionCallback(TInt aEvent, TInt aState = 0,
                                 const TDesC8* aParams = NULL);
    
  private:
      CAknInfoPopupNoteController* iTooltip;
      TInt iKey;
  };

CAknFastSwapData::CAknFastSwapData( TInt aKey, 
                                    CAknInfoPopupNoteController* aTooltip )
    : iTooltip( aTooltip ), iKey( aKey )
    {
    }

TInt CAknFastSwapData::AknTransitionCallback(TInt aEvent, TInt /*aState*/,
                                             const TDesC8* /*aParams*/)
    {
    _AKNTRACE_FUNC_ENTER; 
    iTooltip->ShowInfoPopupNote();

    CAknTransitionUtils::RemoveObserver( this, aEvent );
    _AKNTRACE_FUNC_EXIT; 
    return KErrNone;
    }

NONSHARABLE_CLASS(CAknAlwaysShownAppList) : public CBase
    {
    public:
       // always shown application info  
       // used in the always shown application list
       struct SAlwaysShownAppInfo
            {
            TUid iAppUid;
            TInt iWgId;
            };    
    public:
        static CAknAlwaysShownAppList* NewL( CAknFastSwapWindowControl& aParent );
        CAknAlwaysShownAppList( CAknFastSwapWindowControl& aParent );
        ~CAknAlwaysShownAppList();
        
        /**
        * Initializes the list that stores applications that are always 
        * shown in the fast swap provided they have been installed
        * in the phone rom
        * @return   -
        */        
        void InitializeAlwaysShownListL();
        
        /**
        * Add window group id to spesific appication (=uid)
        * @return   -    
        * @param    TUid aAppUid the application uid      
        * @param    TInt aWgId the window group where task resides 
        */        
        void AddWgGroupToAlwaysShownList( TUid aAppUid, TInt aWgId ); 

        /**
        * If application uid exists in the always shown application list 
        * @return   ETrue  application uid exists in the list
        *           EFalse application uid doesn't exist in the list
        * @param    TUid aAppUid the application uid
        */        
        TBool IsAlwaysShownApp( TUid aAppUid );

        /**
        * If application window group exists in the always shown application list 
        * @return   ETrue  wg exists in the list
        *           EFalse wg doesn't exist in the list
        * @param    TInt aWgId the application window group      
        */        
        TBool IsAlwaysShownApp( TInt aWgId );

        /**
        *
        * Map Tasklist application index to application Uid
        * @return   TUid application Uid
        *  
        * @param    TInt aIndex index of tasklist item arrays
        */ 
        TUid IndexToAppUid( TInt aIndex );

    public:
        RArray<SAlwaysShownAppInfo>* iAppList;
    private:
        void ConstructL();
    private:
        // the list of applications always shown in the fsw
        CAknFastSwapWindowControl& iParent;
    };

// ---------------------------------------------------------
// CAknFastSwapWindowControl::NewL
// ---------------------------------------------------------
//  
CAknAlwaysShownAppList* CAknAlwaysShownAppList::NewL( CAknFastSwapWindowControl& aParent )
    {
    _AKNTRACE_FUNC_ENTER;    
    CAknAlwaysShownAppList* self = new (ELeave) CAknAlwaysShownAppList( aParent );
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(); //self
    _AKNTRACE_FUNC_EXIT;    
    return self;
    }
    
// ---------------------------------------------------------
// CAknFastSwapWindowControl::CAknAlwaysShownAppList
// ---------------------------------------------------------
//  
CAknAlwaysShownAppList::CAknAlwaysShownAppList( CAknFastSwapWindowControl& aParent )
: iParent( aParent )
    {
    }

// ---------------------------------------------------------
// CAknFastSwapWindowControl::~CAknAlwaysShownAppList
// ---------------------------------------------------------
//
CAknAlwaysShownAppList::~CAknAlwaysShownAppList()
    {
    _AKNTRACE_FUNC_ENTER;
    if (iAppList)
        {
        iAppList->Close();
        }
    delete iAppList;
    _AKNTRACE_FUNC_EXIT;
    }

// ---------------------------------------------------------
// CAknFastSwapWindowControl::ConstructL
// ---------------------------------------------------------
//
void CAknAlwaysShownAppList::ConstructL()
    {
    // the list for always shown applications in the fast swap
    iAppList = new (ELeave) RArray<SAlwaysShownAppInfo>();    
    }

// ---------------------------------------------------------
// CAknFastSwapWindowControl::InitializeAlwaysShownListL
// Applications that are always shown in fast swap are stored 
// in different their own list whether they exist
// in the phone rom or not
// ---------------------------------------------------------
//
void CAknAlwaysShownAppList::InitializeAlwaysShownListL()
    {
    _AKNTRACE_FUNC_ENTER;
    iAppList->Close();
    // order of always shown applications
    TUid uidArray[] = {KMenuAppUid, KSearchAppUid, KIdleAppUid};
    TApaAppInfo applicationInfo;
    SAlwaysShownAppInfo fixedAppInfo;
    for ( TInt index = 0; index < KAlwaysShownAppCount; index++)
        {
        // if exists in phone rom
        if (  iParent.iAppArcSession.GetAppInfo(applicationInfo, uidArray[index]) != KErrNotFound )
            {
            fixedAppInfo.iAppUid = uidArray[index];
            // list is created without known window groups
            fixedAppInfo.iWgId = KApplicationWithoutWG;
            iAppList->AppendL( fixedAppInfo );
            }
        }
    _AKNTRACE_FUNC_EXIT;
    }

// ---------------------------------------------------------
// CAknFastSwapWindowControl::AddWgGroupToAlwaysShownList
// The window groups are stored with the application uids
// ---------------------------------------------------------
//
void CAknAlwaysShownAppList::AddWgGroupToAlwaysShownList( TUid aAppUid, TInt aWgId )
    {
    _AKNTRACE_FUNC_ENTER;
    _AKNTRACE( "[%s] aAppUid = %d aWgId = %d", 
    		   __FUNCTION__, aAppUid.iUid, aWgId );
    for ( TInt index = 0; index < iAppList->Count(); index++)
        {
        if ( (*iAppList)[index].iAppUid == aAppUid )
            {
            (*iAppList)[index].iWgId = aWgId;
            }
        }
    _AKNTRACE_FUNC_EXIT;
    }
    
// ---------------------------------------------------------
// CAknFastSwapWindowControl::IsAlwaysShownApp
// If application uid exists in the always shown application list 
// ---------------------------------------------------------
//
TBool CAknAlwaysShownAppList::IsAlwaysShownApp( TUid aAppUid )
    {
    _AKNTRACE_FUNC_ENTER;
    _AKNTRACE( "[%s] aAppUid = %d", __FUNCTION__, aAppUid.iUid );
    for ( TInt index = 0; index < iAppList->Count(); index++)
        {
        if ( (*iAppList)[index].iAppUid == aAppUid )
            {
            _AKNTRACE_FUNC_EXIT;
            return ETrue;
            }
        }
    _AKNTRACE_FUNC_EXIT;
    return EFalse;
    }

// ---------------------------------------------------------
// CAknFastSwapWindowControl::IsAlwaysShownApp
// If application window group exists in the always shown application list 
// ---------------------------------------------------------
//
TBool CAknAlwaysShownAppList::IsAlwaysShownApp( TInt aWgId )
    {
    _AKNTRACE_FUNC_ENTER;
    _AKNTRACE( "[%s] aWgId = %d", __FUNCTION__, aWgId );
    for ( TInt index = 0; index < iAppList->Count(); index++)
        {
        if ( (*iAppList)[index].iWgId == aWgId )
            {
            _AKNTRACE_FUNC_EXIT;
            return ETrue;
            }
        }
    _AKNTRACE_FUNC_EXIT;
    return EFalse;
    }

// ---------------------------------------------------------
// CAknFastSwapWindowControl::IndexToAppUid
// Map Tasklist application index to application Uid
// ---------------------------------------------------------
//
TUid CAknAlwaysShownAppList::IndexToAppUid( TInt aIndex )
    {
    _AKNTRACE( "[%s] aIndex = %d", __FUNCTION__, aIndex );
    return (*iAppList)[aIndex + iAppList->Count() - iParent.iNumberOfWGs].iAppUid;
    }


CAknGridView::TScrollingType KVerticalScrollingType = CAknGridView::EScrollFollowsItemsAndLoops;
CAknGridView::TScrollingType KHorizontalScrollingType = CAknGridView::EScrollFollowsItemsAndLoops;

_LIT(KTab,"\t");

// ================= MEMBER FUNCTIONS =======================
// C++ default constructor can NOT contain any code, that
// might leave.
//
CAknFastSwapWindowControl::CAknFastSwapWindowControl(CAknCapAppServerAppUi& aAppUi)
: iAppUi( aAppUi ), iLowMemory( EFalse ), iLowMemIcons( EFalse ), iAppArcSessionInitiated( EFalse ),
  iTooltipModeTouch( EFalse ), iTransparencyEnabled( CAknEnv::Static()->TransparencyEnabled() ), 
  iIsStylusPopupShow(EFalse), iState( EWaiting )
    { 
    AKNTASHOOK_ADD( this, "CAknFastSwapWindowControl" );
    }

// Symbian OS default constructor can leave.
void CAknFastSwapWindowControl::ConstructL()
    {
    _AKNTRACE_FUNC_ENTER; 
    GfxTransEffect::Enable();
   
    CreateWindowL();
    SetComponentsToInheritVisibility();
    Window().SetShadowDisabled( ETrue );
    Window().SetPointerGrab( ETrue );
    SetGloballyCapturing( ETrue );
    
    if( iTransparencyEnabled )
        {
        Window().SetRequiredDisplayMode( EColor16MA );
        TInt err = Window().SetTransparencyAlphaChannel();

        if ( err == KErrNone )
            {
            Window().SetBackgroundColor(~0);
            }
        }

    CreateCbaL();
    CreateGridL();
    CreateItemArraysL();
    CreateTooltipL();
    CreateLabelL();
    UpdateHeadingIconL();
    
    //create animation
    iLongTapAnimation = CAknLongTapAnimation::NewL( EFalse );
    iThemesAppRepository = CRepository::NewL( KCRUidThemes );
    //create TimeOut
    iTimeOut = CPeriodic::NewL(CActive::EPriorityStandard); 
    iToolTipTimer = CPeriodic::NewL(CActive::EPriorityStandard); 
    
    CreateComponentArrayL();
  
    // create control context
    TRect nullRect( 0, 0 , 0, 0 );
    iFrameContext = CAknsFrameBackgroundControlContext::NewL(
        KAknsIIDQsnFrPopup, nullRect, nullRect, EFalse);

    // the list for always shown applications in the fast swap
    iAlwaysShownList = CAknAlwaysShownAppList::NewL( *this );

    MakeVisible( EFalse );
    _AKNTRACE_FUNC_EXIT; 
    }
    
// Destructor
CAknFastSwapWindowControl::~CAknFastSwapWindowControl()
    {
    _AKNTRACE_FUNC_ENTER;
    AKNTASHOOK_REMOVE();
    AknGlobalPopupPriorityController::RemovePopupPriority(*this);
    GfxTransEffect::Deregister( this );
      
    iAppArcSession.Close();
    ClearItemArrays( ETrue ); 
    if ( iGrid )
        {
        AknsUtils::DeregisterControlPosition( iGrid );
        }
    delete iAlwaysShownList;
    
    FadeBackground( EFalse );
    delete iFrameContext;
    delete iGrid; // destroys also iIconArray and scrollbar frame
    delete iShownWgIds;
    if ( iAllWgIds )
        {
        iAllWgIds->Close();
        }

    CAknFastSwapData *data = 
        (CAknFastSwapData*)CAknTransitionUtils::GetData( (TInt)this );
    if ( data )
        {
        CAknTransitionUtils::RemoveObserver( data,
            CAknTransitionUtils::EEventControlTransitionFinished );
        CAknTransitionUtils::RemoveData( (TInt)this );
        delete data;
        }

    delete iItemTextArray;
    delete iAllWgIds;
    delete iDefaultAppIcon;
    delete iCba;
    delete iConfirmCloseDialog;
    delete iHeadingIcon;
    delete iTooltip;
    delete iLabel;
    delete iPopupMenu;
    delete iLongTapAnimation;
    delete iTimeOut;
    delete iToolTipTimer;
    delete iThemesAppRepository;
    _AKNTRACE_FUNC_EXIT;
    }

// ---------------------------------------------------------
// CAknFastSwapWindowControl::RunFastSwapL
// Function that is called from CEikServAppUi to launch
// task switching. Updates all relevant data (see more detailed
// description from the functions called) and brings the
// window to foreground
// ---------------------------------------------------------
//
void CAknFastSwapWindowControl::RunFastSwapL()
    {
    _AKNTRACE_FUNC_ENTER;
    if ( iIsDisplayed )
        {
        _AKNTRACE_FUNC_EXIT;
        return;
        }
    TInt effectValue( 0 );
    iThemesAppRepository->Get( KThemesTransitionEffects, effectValue );
    if ( effectValue == 0 )     /* TAT on */
        {
        MTouchFeedback* feedback = MTouchFeedback::Instance();
        if ( feedback )
            {
            feedback->InstantFeedback( ETouchFeedbackPopupOpen );
            }
        }
    
    GfxTransEffect::Register( this, KGfxTaskSwapperControlUid, EFalse );
    GfxTransEffect::Abort();
    
    TPoint dPoint( iGrid->PositionRelativeToScreen() );
    TRect dRect( iGrid->Rect() );
    dRect.Move( dPoint );
    
                

    SetPointerCapture( ETrue );

    CleanupStack::PushL( TCleanupItem( CleanupRunFastSwap, this) );

    iIsDisplayed = ETrue;
    
    AknGlobalPopupPriorityController::AddPopupToControlStackL(*this,ECoeStackPriorityDialog,0 );
    AknGlobalPopupPriorityController::AddPopupToControlStackL(*iCba->ButtonGroup()->AsControl(),
        ECoeStackPriorityCba, ECoeStackFlagRefusesFocus );
    AknGlobalPopupPriorityController::ShowPopup(*this, ETrue);
        
    TBool areWeInIdleState = CEikStatusPaneBase::Current()->PaneCapabilities(
        TUid::Uid( EEikStatusPaneUidClock ) ).IsInCurrentLayout();
         
    if (areWeInIdleState)
        { // idle state
        ( (CEikCba*) iCba->ButtonGroup() )->SetSkinBackgroundId(KAknsIIDQsnBgAreaControlIdle);
        }
    else
        {
        ( (CEikCba*) iCba->ButtonGroup() )->SetSkinBackgroundId(KAknsIIDQsnBgAreaControl);
        }

    iCba->HandleResourceChange(KEikDynamicLayoutVariantSwitch);
    iCba->MakeVisible( ETrue );

    
    SetRect( FastSwapWindowRect() );    // Causes call of SizeChanged()

    iBackgroundWgId = (*iAllWgIds)[0].iId;  // where to switch if cancel is pressed
    
    ActivateL();
    
    CleanupStack::Pop();    // clean fast swap cleanup item
    
    // if the grid creation failed, fsw closes
    if ( iGrid->Model()->NumberOfItems() == 0 )
        {
        // if memory runs out, FSW uses what it has 
        // and continues (should never happen)
        CloseFastSwap(); 
        }    
    else 
        {
        iGrid->SetTopItemIndex( 0 );
        iGrid->SetCurrentDataIndex( 0 );
        UpdateTooltipL();
        if ( !CAknTransitionUtils::TransitionsEnabled( 
                AknTransEffect::EComponentTransitionsOff ) )
            {
            iTooltip->ShowInfoPopupNote();
            }
        }    
    CAknTransitionUtils::SetAllParents( this );
    
    TBool rsWasEnabled( EFalse );

    if( !iTransparencyEnabled && Window().IsRedrawStoreEnabled() )
        {
        rsWasEnabled = ETrue;
        // disable redrawstore during transition to avoid
        // drawing problems behind FSW
        Window().EnableRedrawStore( EFalse );
        }
    
    GfxTransEffect::Begin( this, KGfxControlAppearAction );   
    GfxTransEffect::NotifyExternalState(ECaptureComponentsBegin, (const TDesC8*)this);

    // Temporarily set to nonfading to prevent a faded version
    // from appearing on screen
    Window().SetNonFading(ETrue);
    FadeBackground( ETrue );
    MakeVisible( ETrue );
    SetFocus( ETrue );

    Window().SetNonFading(EFalse);
    GfxTransEffect::SetDemarcation( this, dRect );
    CAknTransitionUtils::MakeVisibleSubComponents( this,
                                        CAknTransitionUtils::EForceVisible );

    // Delay display of tooltip until the appear animation has finished,
    // to avoid the fast swap window being drawn on top of the tooltip.
    CAknFastSwapData *data = 
        (CAknFastSwapData*)CAknTransitionUtils::GetData( (TInt)this );
    if ( !data )
        {
        data = new (ELeave) CAknFastSwapData( (TInt)this, iTooltip );
        CAknTransitionUtils::SetData( (TInt)this, data );
        }
        
    if ( CAknTransitionUtils::AddObserver( data, 
                 CAknTransitionUtils::EEventControlTransitionFinished,
                 (const TDesC8 *)this ) == KErrNone )
        {
        GfxTransEffect::NotifyExternalState(ECaptureComponentsEnd, (const TDesC8*)this);
        GfxTransEffect::End( this );
        }
    else
        {
        CAknTransitionUtils::RemoveData( (TInt)this  );
        delete data;
        GfxTransEffect::Deregister( this );
        }
    
    if( !iTransparencyEnabled && rsWasEnabled )
        {
        // if redrawstore was on before transition,
        // enable it again
        Window().EnableRedrawStore( ETrue );
        }
    _AKNTRACE_FUNC_EXIT;
    }

// ---------------------------------------------------------
// CAknFastSwapWindowControl::HandleChangeInWindowGroupListL
// Function that is called from CEikServAppUi when apps list changes.
// Resets window size and selection if FSW is displayed.
// ---------------------------------------------------------
//
void CAknFastSwapWindowControl::HandleChangeInWindowGroupListL()
    {
    _AKNTRACE_FUNC_ENTER;
    if ( !iIsDisplayed )
        {
        _AKNTRACE_FUNC_EXIT;
        return;
        }

    if ( iNumberOfWGs <= 0 )
        {
        CloseFastSwap();
        _AKNTRACE_FUNC_EXIT;
        return;
        }
        
    TInt currPos = iGrid->CurrentDataIndex();

    SetRect( FastSwapWindowRect() );    // Causes call of SizeChanged()  

    TInt iOrgWgId = iBackgroundWgId;

    TInt count = iAllWgIds->Count();
    for ( TInt ii=0; ii<count && !IsWgIdInShownList( iBackgroundWgId); ii++ )
        {
        iBackgroundWgId = (*iAllWgIds)[ii].iId;
        }

    if ( iBackgroundWgId != iOrgWgId )
        {
        // If the current application is closed when hidden
        // BeginFullScreen is called, we must abort that BeginFullScreen
        GfxTransEffect::AbortFullScreen();
        }


    if ( iConfirmCloseDialog && !IsWgIdInShownList( iConfirmCloseWgId) )
        {
        delete iConfirmCloseDialog;
        iConfirmCloseDialog = NULL;
        }
    // if the grid creation failed, fsw closes
    if ( iGrid->Model()->NumberOfItems() == 0 )
        {
        // if memory runs out, FSW uses what it has 
        // and continues 
        CloseFastSwap(); 
        }    
    else 
        {
        if (currPos >= iGrid->Model()->NumberOfItems())
            {
            currPos = iGrid->Model()->NumberOfItems()-1;
            }
        iGrid->SetCurrentDataIndex(currPos);

        ShowTooltipTouchL(EFalse);
        }
    _AKNTRACE_FUNC_EXIT;
    }

// ---------------------------------------------------------
// CAknFastSwapWindowControl::InitializeWindowGroupListL
// Accesses the window server for a list of existing window groups
// of the standard window group priority (default for an application).
// Removes all hidden window groups from the list.
// Normally an application does not have more than one window group.
// ---------------------------------------------------------
//
TBool CAknFastSwapWindowControl::InitializeWindowGroupListL( TInt aWaitForWGRemoval )
    {
    _AKNTRACE_FUNC_ENTER;
    _AKNTRACE( "[%s] aWaitForWGRemoval = %d", __FUNCTION__, aWaitForWGRemoval );
    if (!iAppArcSessionInitiated)
        {
        // Creates a session to the apparc server,
        // connection takes time, so done only once
        // no need to do it many times 
        // done here because cannot be done at the startup 
        User::LeaveIfError( iAppArcSession.Connect() );
        iAppArcSessionInitiated = ETrue;
        }
    iAppArcSession.GetAllApps();
    // create list for always shown applications    
    iAlwaysShownList->InitializeAlwaysShownListL();         
    
    //Initializes CAknFastSwapWindowControl private data ( iWgIds, iNumberOfWGs )
    RWsSession& wsSession=iEikonEnv->WsSession();
    TInt count=wsSession.NumWindowGroups( 0 );

    RArray<RWsSession::TWindowGroupChainInfo>* allWgIds = new (ELeave)
        RArray<RWsSession::TWindowGroupChainInfo>( KFSWArrayGranularity );
        
    CleanupDeletePushL( allWgIds );
    CleanupClosePushL( *allWgIds );
    User::LeaveIfError( wsSession.WindowGroupList( 0, allWgIds) );
    count = allWgIds->Count();

    CArrayFixFlat<SWindowGroupInfo>* shownWgIds = new (ELeave)
        CArrayFixFlat<SWindowGroupInfo>(KFSWArrayGranularity);
        
    CleanupStack::PushL(shownWgIds);
    CApaWindowGroupName* windowName;
    
    //
    // Running application window groups
    //
    TInt firstAppWgId = KErrNone;
    for ( TInt index=0; index < count; index++ )
        {
        RWsSession::TWindowGroupChainInfo& info = (*allWgIds)[index];
        if ( info.iParentId <= 0 )
            {
            TInt wgId=info.iId;
            windowName = CApaWindowGroupName::NewLC(wsSession, wgId);
            TUid applicationUid = windowName->AppUid();
            
            // application screen (0 = main screen, 1 = cover ui )          
            // the possible error value is omitted 
            TInt appScreen = -1; 
            TInt errId = iAppArcSession.GetDefaultScreenNumber( appScreen, applicationUid ); 
            if (  errId != KErrNone )
                {
                CleanupStack::PopAndDestroy( windowName );  //windowName
                continue;   
                }

            if ( firstAppWgId == KErrNone && ( appScreen == 0 || appScreen == -1 ) )
                {
                firstAppWgId = wgId;    
                }
            // always shown applications are appended to the end of window group list 
            if ( iAlwaysShownList->IsAlwaysShownApp( applicationUid ) )
                {
                iAlwaysShownList->AddWgGroupToAlwaysShownList( applicationUid, wgId );
                }
            
            // could't use windowName->IsAppReady(), because then java and console application
            // wouldn't be seen in FSW. Now it is possible that some system apps are seen at the
            // beginning of their start for a while in FSW (even they should be hidden all the time)
            // temporary solution since application shell is normally hidden from tasklist
            // and in the new solution it should be shown
            else if ( !windowName->Hidden() && !iAppUi.HiddenFromFSW(applicationUid.iUid) &&
                ( appScreen == 0 || appScreen == -1 ) ) // appScreen == -1 is used for console applications
                {
                SWindowGroupInfo wgInfo = { wgId, windowName->IsSystem() };
                shownWgIds->AppendL(wgInfo);
                }
            CleanupStack::PopAndDestroy();  //windowName
            }
        }

    // always shown applications are appended to the end of window group list 
    for ( TInt index = 0; index < iAlwaysShownList->iAppList->Count(); index++)
        {
        SWindowGroupInfo wgInfo = { (*iAlwaysShownList->iAppList)[index].iWgId, ETrue };
        shownWgIds->AppendL( wgInfo );
        }
   
    if ( iIsDisplayed && !iIsClosing && shownWgIds->Count() >= iShownWgIds->Count() )
    {
    if ( firstAppWgId != KErrNone && firstAppWgId != iFirstAppWgId && firstAppWgId != iBackgroundWgId ) 
        {
        CloseFastSwap();   
        }
    }
    iFirstAppWgId = firstAppWgId;  

    if ( iShownWgIds && iShownWgIds->Count() != shownWgIds->Count() )
        {
        iIsClosing = EFalse;    
        }
             
    // check if window group of deleted application has been removed
    if ( aWaitForWGRemoval && iShownWgIds )
        {
        // if not removed
        if ( shownWgIds->Count() == iShownWgIds->Count() )
            {
            // no changes are made
            TBool needReset = EFalse;
            CApaWindowGroupName* appNameInShowList = 
                                 CApaWindowGroupName::NewLC(wsSession);
            CApaWindowGroupName* appNameInIShowList =
                                 CApaWindowGroupName::NewLC(wsSession);
            for ( int i = 0; i < shownWgIds->Count(); i++ )
                 {
                 appNameInShowList->ConstructFromWgIdL(shownWgIds->At(i).iWgId);
                 appNameInIShowList->ConstructFromWgIdL(iShownWgIds->At(i).iWgId);
                 if ( appNameInShowList->AppUid() != appNameInIShowList->AppUid() )
                	 {
                	 needReset = ETrue;
                	 break;
                	 }
                 }
            CleanupStack::PopAndDestroy(2);
            if( !needReset )
            	{
                CleanupStack::PopAndDestroy(shownWgIds);
                CleanupStack::PopAndDestroy();            // pop close allWgIds
                CleanupStack::PopAndDestroy(allWgIds);    // pop delete allWgIds            
            
                _AKNTRACE_FUNC_EXIT;
                // EFalse if window group list hasn't been changed
                return EFalse;
            	}
            }
        }

    // changes are made    
    if ( iAllWgIds )
        {
        iAllWgIds->Close();
        }
    delete iAllWgIds;
    iAllWgIds = allWgIds;
    delete iShownWgIds;
    iShownWgIds=shownWgIds;
    iNumberOfWGs=shownWgIds->Count();
    
    CleanupStack::Pop(shownWgIds);
    CleanupStack::Pop();            // pop close allWgIds
    CleanupStack::Pop(allWgIds);    // pop delete allWgIds
    
    _AKNTRACE_FUNC_EXIT;
    // ETrue if window group list has changed
    return ETrue;
    }

// ---------------------------------------------------------
// CAknFastSwapWindowControl::VisibleWindowGroupsCountL
// Returns the number of visible window groups found in the system
// ---------------------------------------------------------
//
TInt CAknFastSwapWindowControl::VisibleWindowGroupsCountL()
    {
    InitializeWindowGroupListL( EFalse );
    return iNumberOfWGs;
    }

TBool CAknFastSwapWindowControl::IsDisplayed()
    {
    return iIsDisplayed;
    }

// ---------------------------------------------------------
// CAknFastSwapWindowControl::UpdateGridL
// Modifies grid extent according the parent control rect
// ---------------------------------------------------------
//
void CAknFastSwapWindowControl::UpdateGridL()
    {
    _AKNTRACE_FUNC_ENTER;
    TAknLayoutRect listScrollLayoutRect;
    TAknLayoutRect gridLayoutRect;
    
    listScrollLayoutRect.LayoutRect( 
        Rect(), 
        AknLayoutScalable_Avkon::listscroll_fast2_pane( ).LayoutLine() );

    // grid
    gridLayoutRect.LayoutRect( 
        listScrollLayoutRect.Rect(), 
        AknLayoutScalable_Avkon::grid_fast2_pane().LayoutLine() );

    TAknLayoutScalableParameterLimits cellLimits = AknLayoutScalable_Avkon::cell_fast2_pane_ParamLimits();
    TInt numberOfGridColumns = cellLimits.LastColumn() + 1;

    if ( AknLayoutUtils::LayoutMirrored() ) 
        {
        iGrid->SetLayoutL( 
            KVerticalOrientation, 
            KRightToLeft, 
            KTopToBottom, 
            numberOfGridColumns, 
            NumberOfVisibleRows(), 
            IconSize() );             
        }
    else
        {          
        iGrid->SetLayoutL(  
            KVerticalOrientation, 
            KLeftToRight, 
            KTopToBottom, 
            numberOfGridColumns, 
            NumberOfVisibleRows(), 
            IconSize() );             
        }

    iGrid->ScrollBarFrame()->SetScrollBarFrameObserver( iGrid );
    
    TRect gridArea = gridLayoutRect.Rect();
    if ( iGrid->Rect() != gridArea )
        {
        iGrid->SetRect( gridArea );
        }
    AknsUtils::RegisterControlPosition( iGrid );    
    
    // scrollbar
    AknLayoutUtils::LayoutVerticalScrollBar( 
        iGrid->ScrollBarFrame(), 
        listScrollLayoutRect.Rect(), 
        AknLayoutScalable_Avkon::scroll_pane_cp26().LayoutLine() );
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// Updates the UI components.
// ---------------------------------------------------------------------------
//
void CAknFastSwapWindowControl::UpdateViewL()
    {
    _AKNTRACE_FUNC_ENTER;
    UpdateItemArraysL();
    UpdateGridL();
    UpdateControlContext();
    iGrid->UpdateScrollBarsL();
    UpdateLabelL();
    UpdateHeadingIconL();
    

    if ( IsVisible() )
        {
        DrawDeferred();
        }

    if ( iIsStylusPopupShow )
        {
        TPoint pos = PositionRelativeToScreen();
        TInt itemIndex = iGrid->CurrentItemIndex();
        itemIndex = itemIndex < 0 ? 0 : itemIndex;
        TPoint posItem = iGrid->View()->ItemPos( itemIndex );
        pos.iY += posItem.iY;
        pos.iX += posItem.iX;
        if ( AknLayoutUtils::LayoutMirrored() )
            {
            TInt itemWidth = iGrid->View()->ItemSize( itemIndex ).iWidth;    
            pos.iX += itemWidth;
            }
        if ( iPopupMenu ) 
            {
            iPopupMenu->SetPosition( pos, CAknStylusPopUpMenu::EPositionTypeLeftBottom );       
            }
        }
    _AKNTRACE_FUNC_EXIT;
    }
        
// ---------------------------------------------------------
// CAknFastSwapWindowControl::UpdateControlContext
// ---------------------------------------------------------
//
void CAknFastSwapWindowControl::UpdateControlContext()
    {
    _AKNTRACE_FUNC_ENTER;
    TRect rectParent = Rect();
    TAknLayoutRect layoutRect;

    layoutRect.LayoutRect( 
        rectParent, 
        AknLayoutScalable_Avkon::bg_popup_window_pane_cp17().LayoutLine() );
        
    rectParent = layoutRect.Rect();
    
    layoutRect.LayoutRect( 
        rectParent, 
        AknLayoutScalable_Avkon::bg_popup_window_pane_g1(0).LayoutLine() );

    iFrameContext->SetFrame(KAknsIIDQsnFrPopup);
    iFrameContext->SetFrameRects(rectParent, layoutRect.Rect());
    iFrameContext->SetCenter(KAknsIIDQsnFrPopupCenterFswap);
    _AKNTRACE_FUNC_EXIT;
    }

// ---------------------------------------------------------
// CAknFastSwapWindowControl::Draw
// Symbian OS framework drawing function. Draws the window shadows and
// outline frame.
// ---------------------------------------------------------
//
void CAknFastSwapWindowControl::Draw(const TRect& /*aRect*/) const
    {
    _AKNTRACE_FUNC_ENTER;
    if ( iNumberOfWGs < 1 )
        {
        _AKNTRACE_FUNC_EXIT;
        return;
        }
    CWindowGc& gc = SystemGc();
        
    if( !iTransparencyEnabled )
    {
        // Should only clear the background when transparency is not enabled
        gc.Clear( Rect() );
    }
    
    if ( iLowMemIcons ) 
        {
        _AKNTRACE_FUNC_EXIT;
        return;
        }
    
    MAknsSkinInstance *skin = AknsUtils::SkinInstance();

    gc.SetPenStyle(CGraphicsContext::ENullPen);
        
    TAknLayoutRect topLeft;
    TAknLayoutRect bottomRight;
        
    topLeft.LayoutRect( Rect(), SkinLayout::Popup_windows_skin_placing__frame_general__Line_2());
    bottomRight.LayoutRect(Rect(), SkinLayout::Popup_windows_skin_placing__frame_general__Line_5());
        
    TRect innerRect = TRect(topLeft.Rect().iBr, bottomRight.Rect().iTl);

    TAknLayoutRect headingArea;
    TAknLayoutRect headingBackground;
    TAknLayoutRect headingCenter;
    TAknLayoutRect iconArea;
    
    headingArea.LayoutRect( Rect(), AknLayoutScalable_Avkon::heading_pane_cp2().LayoutLine() );
    
    headingBackground.LayoutRect( headingArea.Rect(), 
        AknLayoutScalable_Avkon::bg_popup_heading_pane(  0 ).LayoutLine() );
        
    headingCenter.LayoutRect( headingBackground.Rect(), 
        AknLayoutScalable_Avkon::bg_popup_heading_pane_g1().LayoutLine() );

    if( iTransparencyEnabled )
        {
        TRegionFix<1> dontDrawRegion;
        TRegionFix<8> drawRegion; // 8 should be enough for grid and heading clipping
        dontDrawRegion.AddRect( iGrid->Rect() );
        drawRegion.AddRect( Rect() );
        drawRegion.SubRegion( dontDrawRegion );
        gc.SetClippingRegion( drawRegion );
        AknsDrawUtils::DrawFrame( skin, gc, Rect(), innerRect, 
            KAknsIIDQsnFrPopup, KAknsIIDQsnFrPopupCenter); //KAknsIIDQsnFrPopupCenterFswap);
        gc.CancelClippingRegion();    
        }
    else
        {
        AknsDrawUtils::DrawFrame( skin, gc, Rect(), innerRect, 
            KAknsIIDQsnFrPopup, KAknsIIDQsnFrPopupCenter); //KAknsIIDQsnFrPopupCenterFswap);
        }

    AknsDrawUtils::DrawFrame( skin, gc, headingBackground.Rect(), headingCenter.Rect(),
        KAknsIIDQsnFrPopupHeading, KAknsIIDQsnFrPopupHeadingCenter);
                                         
    if ( iHeadingIcon )
        {
        iconArea.LayoutRect( 
            headingBackground.Rect(), 
            AknLayoutScalable_Avkon::heading_pane_g2().LayoutLine() );        
        
        gc.BitBltMasked( iconArea.Rect().iTl, iHeadingIcon->Bitmap(), iconArea.Rect().Size(), 
            iHeadingIcon->Mask(), ETrue );        
        }
    _AKNTRACE_FUNC_EXIT;
    }

// ---------------------------------------------------------
// CAknFastSwapWindowControl::OfferKeyEventL
// Key handling routine, forwards key events to grid
// ---------------------------------------------------------
//
TKeyResponse CAknFastSwapWindowControl::OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)
    {
    _AKNTRACE_FUNC_ENTER;
    _AKNTRACE( "[%s] scancode = %d aType = %d", __FUNCTION__, aKeyEvent.iScanCode, aType );
    // if user pressed backspace / clear key the fsw offers 
    // to close the selected application
    if (aType == EEventKey && aKeyEvent.iCode == EKeyBackspace)
        {
        TBool isShift(EFalse);
#ifdef __WINSCW__
        // secret test mode for emulator: shift-backspace sends a definite exit message
        isShift = aKeyEvent.iModifiers & (EModifierLeftShift | EModifierRightShift | EModifierShift);
#endif
        TryCloseApplicationL(iGrid->CurrentDataIndex(), isShift);
        _AKNTRACE_FUNC_EXIT;
        return EKeyWasConsumed;
        }

    if ( AknLayoutUtils::PenEnabled() )
        {
        if ( aType == EEventKeyUp && aKeyEvent.iScanCode == EStdKeyYes )
            {
            CloseFastSwap();
            _AKNTRACE_FUNC_EXIT;
            return EKeyWasNotConsumed ;    
            }
        }
    // If user pressed the end key the fastswap will close    
    if ( aType == EEventKey && ( aKeyEvent.iCode == EKeyNo || aKeyEvent.iCode == EKeyEnd )
        || (aKeyEvent.iCode == EKeyEscape ) )
        {
        
                
        CApaWindowGroupName* wgName = CApaWindowGroupName::NewL( iEikonEnv->WsSession() );
        CleanupStack::PushL( wgName );
        
        wgName->ConstructFromWgIdL( iBackgroundWgId );
        
        TBool idleIsBelow = wgName->AppUid() == KIdleAppUid;
        
        CleanupStack::PopAndDestroy( wgName );
                        
        // with end key show fullscreen effect but no
        // FSW component effect, except if the idle app
        // is below FSW
        
        if( !idleIsBelow )
            {
            GfxTransEffect::BeginFullScreen(5000,
            TRect(0,0,0,0),
            AknTransEffect::EParameterType,
            
            AknTransEffect::GfxTransParam(
                iAppUi.Application()->AppDllUid(), 
                AknTransEffect::TParameter::EActivateExplicitContinue));
            }
                
        if( !idleIsBelow )
            {
            iDisableFSWEffect = ETrue;    
            }
        CloseFastSwap();
        iDisableFSWEffect = EFalse;
        _AKNTRACE_FUNC_EXIT;
        return EKeyWasConsumed;
        }
    TInt index = iGrid->CurrentDataIndex();
    TKeyResponse keyresponse = iGrid->OfferKeyEventL(aKeyEvent, aType);
    if ( index != iGrid->CurrentDataIndex() )
        {
        UpdateTooltipL();
        iTooltip->ShowInfoPopupNote();
        }
    _AKNTRACE_FUNC_EXIT;
    return keyresponse;
    }


// ---------------------------------------------------------------------------
// Handles tooltip in touch events and long tapping. 
// CAknGrid handles changing the highlighted item and opening the application
// when tapping on a highlighted item.
// ---------------------------------------------------------------------------
//
void CAknFastSwapWindowControl::HandlePointerEventL(
    const TPointerEvent& aPointerEvent )
    {
    _AKNTRACE_FUNC_ENTER;
    _AKNTRACE( "[%s] Type = %d", __FUNCTION__, aPointerEvent.iType );
    // FSW does not handle any pointer event when stylus popup
    // menu is visible.
    if ( iIsStylusPopupShow && aPointerEvent.iType != TPointerEvent::EButton1Up  )
        {
        _AKNTRACE_FUNC_EXIT;
        return;
        }
    
    if ( AknLayoutUtils::PenEnabled() )
        {        
        if ( aPointerEvent.iType == TPointerEvent::EButton1Up )
            {
            PointerEventL( aPointerEvent );    
            }
        
        // Pointer coordinates start from the top left position of the
        // window at the coordinates (0,0).
        TRect controlArea( NULL, NULL, iSize.iWidth, iSize.iHeight );
        TInt touchedIndex = KErrNotFound;
        TBool isOverItem =
            iGrid->GridView()->XYPosToItemIndex( aPointerEvent.iPosition,
                                                 touchedIndex );
        if ( isOverItem )
            {
            touchedIndex = iGrid->GridView()->ActualDataIndex( touchedIndex );
            }

        // Cancel touch mode tooltip if pointer is not over an item.
        if ( !isOverItem && iTooltipModeTouch )
            {
            HideTooltip();
            iTooltipModeTouch = EFalse;
            }
        
        TBool eventInsideControlArea =
            controlArea.Contains( aPointerEvent.iPosition );
        TBool eventInsideGrid =
            iGrid->Rect().Contains( aPointerEvent.iPosition );

        TInt oldIndex = iGrid->CurrentDataIndex();
        
        if ( eventInsideControlArea && IsFocused() )
            {
            // Sends events to the grid and the scrollbar while FSW is focused.
            // When tapping a highlight item, the grid sends an
            // EEventItemClicked event to FSW, and FSW opens this app.
            CCoeControl::HandlePointerEventL( aPointerEvent );
            }
        else if ( eventInsideControlArea && 
                aPointerEvent.iType == TPointerEvent::EButton1Up )
            {
            // Up event needs to be always passed to the base class so that
            // grid's AknPhysics stays in sync.
            CCoeControl::HandlePointerEventL( aPointerEvent );
            }

        switch ( aPointerEvent.iType )
            {
            case TPointerEvent::EButton1Down:
                {
                if ( !eventInsideControlArea )
                    {
                    // Pointer down was received outside of the FSW.
                    iStylusDownIn = EFalse;
                    iIsPointerDownOutOfGrid = EFalse;
                    }
                else
                    {
                    // Pointer down was received inside the FSW.
                    if ( eventInsideGrid )
                        {
                        iStylusDownIn = ETrue;
                        iIsPointerDownOutOfGrid = EFalse;     
                        }
                    else
                        {
                        iStylusDownIn = EFalse;    
                        iIsPointerDownOutOfGrid = ETrue; 
                        }
                    
                    if ( isOverItem )
                        {
                        if ( eventInsideGrid )
                            {
                            // Start detecting long tap.
                            PointerEventL( aPointerEvent );
                            }

                        }
                    }
                break;
                }
            
            case TPointerEvent::EDrag:
                {
                if ( !eventInsideControlArea )
                    {
                    // Drag event was received outside of the FSW.
                    if ( iStylusDownIn )
                        {
                        // Cancel animation when dragging outside of the FSW.
                        CancelAnimationAndPressDownEffect();
                        
                        // Forward the event for scrolling.
                        CCoeControl::HandlePointerEventL( aPointerEvent );
                        }
                    }
                else
                    {
                    // Drag event was received inside the FSW.
                    if ( !iStylusDownIn )
                        {
                        _AKNTRACE_FUNC_EXIT;
                        return;
                        }
                    
                    if ( !iItemHighlighted )
                        {
                        // Highlight hasn't yet been changed so the item
                        // index isn't update yet either.
                        oldIndex = touchedIndex;
                        }
                    
                    if ( isOverItem )
                        {
                        if ( eventInsideGrid )
                            {
                            // Start detecting long tap.
                            PointerEventL( aPointerEvent );
                            }
                        
                        if ( oldIndex != touchedIndex )
                            {
                            
                            // Set this in case the listbox hasn't reported
                            // dragging actioned event in order to not to
                            // activate item which didn't receive the pointer down.
                            iItemDraggingActioned = ETrue;
                            }
                        }
                    else if ( iStylusDownIn )
                        {
                        CancelAnimationAndPressDownEffect(); 
                        }
                    }
                break;
                }
                
            case TPointerEvent::EButton1Up:
                {
                iItemHighlighted = EFalse;
                
                if ( !eventInsideControlArea )
                    {
                    // Pointer up was received outside of the FSW.
                    if ( !iStylusDownIn && !iIsPointerDownOutOfGrid )
                        {
                        // The FSW is closed if both the pointer down and
                        // pointer up events occur outside the window.
                        CloseFastSwap();
                        }

                    CCoeControl::HandlePointerEventL( aPointerEvent );
                    }
                else
                    {
                    // Pointer up was received inside the FSW.
                    if ( !iStylusDownIn )
                        {
                        _AKNTRACE_FUNC_EXIT;
                        return;
                        }
                    
                    if ( isOverItem ) 
                        {
                        // The current item is selected if pointer is
                        // lifted while in the grid / over a legimate item.
                        
                        // Cancel touch mode for tooltip.
                        iTooltipModeTouch = EFalse;
                        
                        // Open the application as before, but now change the
                        // highlighted item, so need to update tooltip.
                        if ( iItemDraggingActioned ) 
                            {
                            if ( iToolTipTimer->IsActive() )
                                {
                                iToolTipTimer->Cancel();     
                                }
    
                            // Hide tooltip, otherwise tooltip does
                            // not disappear.
                            iToolTipTimer->Start(
                                KTooltipTimeView * 1000, 
                                KTimeNeverHappenEvent,
                                TCallBack( ToolTipTimeOutCallBackL, this ) );  
                            }
                        }
                    }
                break;
                }
                
            default:
                {
                CCoeControl::HandlePointerEventL( aPointerEvent );
                break;
                }
            }
        }
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------
// CAknFastSwapWindowControl::ProcessCommandL
// Softkey event handling
// ---------------------------------------------------------
//
void CAknFastSwapWindowControl::ProcessCommandL(TInt aCommandId)
    {
    _AKNTRACE_FUNC_ENTER;
    _AKNTRACE( "[%s] aCommandId = %d", __FUNCTION__, aCommandId );
    switch (aCommandId)
        {
        case EAknSoftkeyCancel:
            SwitchToTask( iBackgroundWgId );
            break;
        case EAknSoftkeySelect:
            HandleListBoxEventL( iGrid, EEventEnterKeyPressed );
            break;
        case EAknCapServerCmdOpen: 
            SetHiddenFlag();
            SwitchToApplicationL( iGrid->CurrentDataIndex() );
            break;
        case EAknCapServerCmdClose:
            SetHiddenFlag();
            TryCloseApplicationL( iGrid->CurrentDataIndex() );
            break;
        case KErrCancel:
            SetHiddenFlag();
            break;    
        default:
        	_AKNTRACE_FUNC_EXIT;
            return;
        }
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// Handles item selection in the grid.
// ---------------------------------------------------------------------------
//
void CAknFastSwapWindowControl::HandleListBoxEventL( CEikListBox* /*aListBox*/, 
                                                     TListBoxEvent aEventType )
    {
    _AKNTRACE_FUNC_ENTER;
    _AKNTRACE( "[%s] aEventType = %d", __FUNCTION__, aEventType );
    switch ( aEventType )
        {
        case MEikListBoxObserver::EEventPenDownOnItem:
            iItemDraggingActioned = EFalse;
            iPressDownTime.HomeTime();
            break;
            
        case MEikListBoxObserver::EEventEnterKeyPressed:
            SwitchToApplicationL( iGrid->CurrentDataIndex() );    
            break;

        case MEikListBoxObserver::EEventItemClicked:
            if ( !iItemDraggingActioned && !iIsStylusPopupShow )
                {
                TTime now;
                now.HomeTime();
                TInt64 diffTime = KPressedDownEffectTime - now.MicroSecondsFrom(iPressDownTime).Int64();         
                if( diffTime > 0 )
                    {
                    // wait for the diffTime 
                    User::After( diffTime );     
                    }
                SwitchToApplicationL( iGrid->CurrentDataIndex() );
                }
            break;

        case MEikListBoxObserver::EEventPanningStarted:
        case MEikListBoxObserver::EEventFlickStarted:
        case MEikListBoxObserver::EEventItemDraggingActioned:
            HideTooltip();
            CancelAnimationAndPressDownEffect();
            break;

        default:
            break;
        }
    _AKNTRACE_FUNC_EXIT;
    }

// ---------------------------------------------------------------------------
// Handles events from grid 
// ---------------------------------------------------------------------------
//
void CAknFastSwapWindowControl::HandleControlEventL( 
    CCoeControl *aControl, TCoeEvent aEventType )
    {
    _AKNTRACE_FUNC_ENTER;
    if ( aControl == iGrid && aEventType == EEventStateChanged && iIsDisplayed )
        {
        iItemHighlighted = ETrue;
        }
    _AKNTRACE_FUNC_EXIT;
    }

// ---------------------------------------------------------
// CAknFastSwapWindowControl::FadeBackground
// Fades the underlying window group when fastswap is invoked
// ( if not already faded)
// implementation is similar to Eikon dialogs
// ---------------------------------------------------------
//
void CAknFastSwapWindowControl::FadeBackground(TBool aFade)
    {
    AknGlobalPopupPriorityController::FadeBehindPopup(*this, iPopupFader, *this, aFade);
    }
  
// ---------------------------------------------------------
// CAknFastSwapWindowControl::CreateGridL
// Grid construction
// ---------------------------------------------------------
//
void CAknFastSwapWindowControl::CreateGridL()
    {
    _AKNTRACE_FUNC_ENTER;
    ASSERT(!iGrid);
    TAknLayoutScalableParameterLimits cellLimits = AknLayoutScalable_Avkon::cell_fast2_pane_ParamLimits();
    TInt numberOfGridColumns = cellLimits.LastColumn() + 1;
    
    iGrid = new (ELeave) CAknFastSwapWindowGrid;
    iGrid->ConstructL( this, EAknListBoxSelectionGrid | EAknListBoxScrollBarSizeExcluded );    
    iGrid->SetLayoutL( KVerticalOrientation, KLeftToRight,
        KTopToBottom, numberOfGridColumns, NumberOfVisibleRows(), IconSize() );
    iGrid->SetObserver( this );
    
    // CAknGrid creates a window owning scroll bar. This causes flickering of
    // the scroll bar when fast swap window is opened. Create a non window
    // owning scroll bar and install it into the grid.
    CEikScrollBarFrame* sbFrame = new(ELeave) CEikScrollBarFrame(
        this, iGrid, ETrue);
    CleanupStack::PushL(sbFrame);
    if (AknLayoutUtils::DefaultScrollBarType(iAvkonAppUi) == CEikScrollBarFrame::EDoubleSpan)
        {
        sbFrame->CreateDoubleSpanScrollBarsL(EFalse, EFalse, ETrue, EFalse);
        }
    iGrid->SetScrollBarFrame(sbFrame, CEikListBox::ENotOwnedExternally);
    CleanupStack::Pop(); // sbFrame
    iGrid->SetPrimaryScrollingType( KHorizontalScrollingType );
    iGrid->SetSecondaryScrollingType( KVerticalScrollingType );
    iGrid->SetCurrentDataIndex( 0 );        
    iGrid->SetRect( TRect( 0, 0, 10, 10 ) ); // avoids grid panic        

    iGrid->SetContainerWindowL(*this);
    iGrid->SetListBoxObserver(this);
    // Scroll bar should be shown always when fsw visible
    iGrid->ScrollBarFrame()->SetScrollBarVisibilityL(CEikScrollBarFrame::EOff, 
        CEikScrollBarFrame::EAuto);
    if (iTransparencyEnabled)
        {
        // When fast swap window opens, scroll bar background appears to be
        // drawn twice during transition even if it is added into a clipping
        // region in CAknFastSwapWindowControl::Draw(). Therefore background
        // drawing is disabled in scroll bar and drawn by this control.
        iGrid->ScrollBarFrame()->DrawBackground(EFalse, EFalse);
        }
    _AKNTRACE_FUNC_EXIT;
    }
    
// ---------------------------------------------------------
// CAknFastSwapWindowControl::CreateGridL
// Creates CCoeControlArray for the child controls
// ---------------------------------------------------------
//
void CAknFastSwapWindowControl::CreateComponentArrayL()
    {
    _AKNTRACE_FUNC_ENTER;
    InitComponentArrayL();
    Components().AppendLC( iGrid, 0 );
    CleanupStack::Pop();
    Components().AppendLC( iLabel, 1 );
    CleanupStack::Pop();
    CEikScrollBar* scrollBar = iGrid->ScrollBarFrame()->VerticalScrollBar();
    if (scrollBar)
        {
        Components().AppendLC(scrollBar, 2);
        CleanupStack::Pop();
        }
    Components().SetControlsOwnedExternally( ETrue );
    _AKNTRACE_FUNC_EXIT;
    }

// ---------------------------------------------------------
// CAknFastSwapWindowControl::CreateTooltipL
// 
// ---------------------------------------------------------
//
void CAknFastSwapWindowControl::CreateTooltipL()
    {
    _AKNTRACE_FUNC_ENTER;
    iTooltip = CAknInfoPopupNoteController::NewL();    
    iTooltip->SetTimeDelayBeforeShow( KTooltipTimeBefore );
    iTooltip->SetTimePopupInView( KTooltipTimeView );
    iTooltip->SetTooltipModeL( ETrue );
    iTooltip->HideWhenAppFaded( EFalse );
    _AKNTRACE_FUNC_EXIT;
    }

// ---------------------------------------------------------
// CAknFastSwapWindowControl::CreateLabelL
// Creates tooltip that shows application name of highlighted application icon
// ---------------------------------------------------------
//
void CAknFastSwapWindowControl::CreateLabelL()
    {
    _AKNTRACE_FUNC_ENTER;
    // read label from resources qtn_options_task_swapper
    HBufC* labelBuffer = CCoeEnv::Static()->AllocReadResourceL( R_QTN_SELEC_TITLE_SWAPPER );
    CleanupStack::PushL( labelBuffer );
            
    // determine the width of the text
    // determining the size of the text
    TAknLayoutRect headingRect;
    headingRect.LayoutRect( FastSwapWindowRect(), 
        AknLayoutScalable_Avkon::heading_pane( 0 ).LayoutLine());
    TAknLayoutText textLayout; 
    textLayout.LayoutText( headingRect.Rect(), 
        AknLayoutScalable_Avkon::heading_pane_t1( 2 ).LayoutLine() );
    TInt width = textLayout.TextRect().Width();

    // clip the label
    TPtr clippedStringPtr = labelBuffer->Des();
    AknBidiTextUtils::ConvertToVisualAndClipL(
    clippedStringPtr, *textLayout.Font() /**iEikonEnv->NormalFont()*/, width, width );
        
    // create label        
    iLabel = new (ELeave) CEikLabel();
    iLabel->SetContainerWindowL( *this );
    iLabel->SetTextL( *labelBuffer );
    iLabel->UseLogicalToVisualConversion( EFalse );
    iLabel->SetBrushStyle( CGraphicsContext::ENullBrush );
    CleanupStack::PopAndDestroy(); // labelBuffer
    _AKNTRACE_FUNC_EXIT;
    }

void CAknFastSwapWindowControl::UpdateLabelL()
    {
    _AKNTRACE_FUNC_ENTER;
    // layout
    TAknLayoutRect headingArea;
    TAknLayoutRect textArea;
    headingArea.LayoutRect( Rect(), AknLayoutScalable_Avkon::heading_pane_cp2().LayoutLine());
    
    AknLayoutUtils::LayoutLabel( 
        iLabel, 
        headingArea.Rect(), 
        AknLayoutScalable_Avkon::heading_pane_t1( 2 ).LayoutLine(), 
        iEikonEnv->NormalFont());
    
    // skin
    TRgb color;
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    TInt error = AknsUtils::GetCachedColor( skin, color, KAknsIIDQsnTextColors, 
        EAknsCIQsnTextColorsCG19 );
        
    if (!error)
        {
        // Ignore error
        TRAP_IGNORE( AknLayoutUtils::OverrideControlColorL( *iLabel, EColorLabelText, color ) );
        }
    _AKNTRACE_FUNC_EXIT;
    }   


// ---------------------------------------------------------
// CAknFastSwapWindowControl::CreateGridL
// Updates tooltip with right application name andthat shows application name of highlighted 
// application icon
// ---------------------------------------------------------
//
void CAknFastSwapWindowControl::UpdateTooltipL()
    {
    _AKNTRACE_FUNC_ENTER;
    iTooltip->HideInfoPopupNote();
    if ( !IsFocused() || IsDimmed() || iGrid->CurrentDataIndex() == KErrNotFound )
        {
        _AKNTRACE_FUNC_EXIT;
        return;
        }
            
    TRect currentItemRect = CurrentGridItemRect();
    if ( currentItemRect.iTl.iY < iGrid->View()->ViewRect().iTl.iY )
    	{
    	currentItemRect.iTl.iY = iGrid->View()->ViewRect().iTl.iY;
    	}
    TAknLayoutRect rect;
    TRect parent;
    AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EPopupParent, parent );
    currentItemRect.Move( FastSwapWindowRect().iTl );
    // The tooltip width must be set before calculating the floating point in 
    // SetPositionAndAlignment().
    iTooltip->SetTextL( CurrentAppName() );
    iTooltip->SetPositionByHighlight(currentItemRect); // This method also checks the current layout (European or Arabic)
    if( !iTooltipModeTouch )
        {
        iTooltip->SetTimeDelayBeforeShow(KTooltipTimeBefore);
        iTooltip->SetTimePopupInView(KTooltipTimeView);
        }
    _AKNTRACE_FUNC_EXIT;
    }

// ---------------------------------------------------------
// CAknFastSwapWindowControl::ShowTooltipTouchL
// Handles tooltip when touch input is used.
// ---------------------------------------------------------
//
void CAknFastSwapWindowControl::ShowTooltipTouchL(TBool aPointerOverItem)
    {
    _AKNTRACE_FUNC_ENTER;
    _AKNTRACE( "[%s] aPointerOverItem = %d", __FUNCTION__, aPointerOverItem );
    if( !iTooltipModeTouch && aPointerOverItem)
        {
        iTooltip->SetTimeDelayBeforeShow(KTooltipTimeBeforeTouch);
        iTooltip->SetTimePopupInView(KTooltipTimeViewTouch);
        iTooltipModeTouch = ETrue;
        }
    // Show tooltip only when fast swap control has keyboard focus.
    if (IsFocused())
        {
        UpdateTooltipL();
        iTooltip->ShowInfoPopupNote();
        }
    _AKNTRACE_FUNC_EXIT;
    }

// ---------------------------------------------------------
// CAknFastSwapWindowControl::CurrentGridItemRect
// The rect of current highlighted grid item
// ---------------------------------------------------------
//        
TRect CAknFastSwapWindowControl::CurrentGridItemRect()
    {
    _AKNTRACE_FUNC_ENTER;
    // must be item index, not data index as usual
    TInt index = iGrid->CurrentItemIndex();
    if( index != KErrNotFound )         
        {
        TRect currentItemRect = TRect( iGrid->View()->ItemPos( index ) /*item pos*/, 
            iGrid->View()->ItemSize( 0)  /*item size*/);

        _AKNTRACE_FUNC_EXIT;   
        return currentItemRect;
        }
    _AKNTRACE_FUNC_EXIT;
    return TRect( NULL, NULL, NULL, NULL );
    }
    
// ---------------------------------------------------------
// CAknFastSwapWindowControl::UpdateHeadingIconL
// Resets heading icon with the icon provided by the current skin
// ---------------------------------------------------------
//
void CAknFastSwapWindowControl::UpdateHeadingIconL()
    {
    _AKNTRACE_FUNC_ENTER;
    if ( iLowMemory )
    	{
    	_AKNTRACE_FUNC_EXIT;
        return;
    	}
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();    
    
    CGulIcon* headingIcon = AknsUtils::CreateGulIconL( 
        skin, KAknsIIDQgnIndiAppOpen, 
        AknIconUtils::AvkonIconFileName(),
        EMbmAvkonQgn_indi_app_open_add, 
        EMbmAvkonQgn_indi_app_open_add_mask);
        
    CleanupStack::PushL( headingIcon ); // to stack
    TAknLayoutRect headingArea;
    TAknLayoutRect headingBackground;
    TAknLayoutRect iconArea;
    headingArea.LayoutRect( Rect(), AknLayoutScalable_Avkon::heading_pane_cp2().LayoutLine() );
    
    headingBackground.LayoutRect( 
        headingArea.Rect(), 
        AknLayoutScalable_Avkon::bg_popup_heading_pane(  0 ).LayoutLine() );
        
    iconArea.LayoutRect( 
        headingBackground.Rect(), 
        AknLayoutScalable_Avkon::heading_pane_g2().LayoutLine() );
        
    User::LeaveIfError( AknIconUtils::SetSize( headingIcon->Bitmap(), iconArea.Rect().Size() ) ); 

    delete iHeadingIcon;                                         
    iHeadingIcon = headingIcon;
    CleanupStack::Pop(); // headingIcon    
    _AKNTRACE_FUNC_EXIT;
    }

// ---------------------------------------------------------
// CAknFastSwapWindowControl::CreateCbaL
// Softkey construction (component control of CAknFastswapWindowControl)
// ---------------------------------------------------------
//
void CAknFastSwapWindowControl::CreateCbaL()
    {
    _AKNTRACE_FUNC_ENTER;
    ASSERT(!iCba);
    TRect screenRect;
    AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EScreen, screenRect );    
    
    iCba = CEikButtonGroupContainer::NewL(
        CEikButtonGroupContainer::ECba,
        CEikButtonGroupContainer::EHorizontal,
        this, R_AVKON_SOFTKEYS_SELECT_CANCEL__SELECT);
        
    iCba->MakeVisible( EFalse );
    iCba->SetBoundingRect( screenRect );
    
    iCba->ButtonGroup()->AsControl()->DrawableWindow()->SetOrdinalPosition( -1 );   // -1 puts this window at the back
        
    iAppUi.RemoveFromStack( iCba->ButtonGroup()->AsControl() );
    AknGlobalPopupPriorityController::AddSubPopupL(*this, *iCba->ButtonGroup()->AsControl());
    _AKNTRACE_FUNC_EXIT; 
    }

// ---------------------------------------------------------
// CAknFastSwapWindowControl::UpdateItemArraysL
// Retrieves the application names and icons via the apparc
// server, and stores them in arrays.
// ---------------------------------------------------------
//
void CAknFastSwapWindowControl::UpdateItemArraysL()
    {
    _AKNTRACE_FUNC_ENTER;
    ClearItemArrays( EFalse );
    RWsSession& wsSession = iEikonEnv->WsSession();

    TBuf<2*KMaxFileName+1> name;

    // Set the icon size we wish retrieve
    TUid appUid;
    TInt wgId;

    for (TInt index=0; index<iNumberOfWGs; index++)
        {
        wgId=(*iShownWgIds)[index].iWgId;
        TApaAppInfo info;
        //
        // Always shown applications
        //
        if ( iAlwaysShownList->IsAlwaysShownApp( wgId ) )
            {
            appUid = iAlwaysShownList->IndexToAppUid( index );
            iAppArcSession.GetAppInfo( info, appUid );

            // retrieve the app name
            TPtrC caption = info.iShortCaption;
            name.Zero();
            
            // conversion from TInt to TReal, might be a problem in the future
            name.AppendNum( index ); 
            
            name.Append( KTab );
            name.Append( caption );
            }
        //
        // Running Applications
        //
        else 
            {
            CApaWindowGroupName* windowName = CApaWindowGroupName::NewLC( wsSession, wgId );
            appUid = windowName->AppUid();
            iAppArcSession.GetAppInfo( info, appUid );

            //Retrieve the app name
            TPtrC caption = info.iShortCaption;
            name.Zero();
            
            // conversion from TInt to TReal, might be a problem in the future
            name.AppendNum( index ); 
            
            name.Append( KTab );
            if ( !( caption.Length() ) ) // if not set - use thread name instead
                {
                if (windowName->Caption().Length() != 0)
                    {
                    name.Append( windowName->Caption() );
                    }
                else
                    {
                    TThreadId threadId;
                    TInt err = wsSession.GetWindowGroupClientThreadId( wgId, threadId );
                    if ( err == KErrNone )
                        {
                        RThread thread;
                        err = thread.Open( threadId);
                        if ( err==KErrNone )
                            {
                            name.Append( thread.Name() );
                            thread.Close();
                            }
                        }
                    }
                }
            else
                {
                name.Append( caption );
                }
            CleanupStack::PopAndDestroy();  //windowName
            }
        // we discontinue if no more items can be added to the icon array
        TBool iconAddSuccess = ETrue;
        TRAPD(error ,iconAddSuccess = AddIconToArrayL( appUid ));
        if (!iconAddSuccess)
            {
            break;      
            }
        if( error != KErrNone )
           {
           if( error == KErrNoMemory )
              {
              User::LeaveNoMemory();
              }
           if( error == KErrNotFound )
              {
              iIconArray->AppendL( iDefaultAppIcon);
              }
           else
              {
              User::Leave(error);
              }
            }            
        iItemTextArray->AppendL( name );
        }
       
    // update the grid according the changes made to icon arrays
    TInt newCount = iItemTextArray->MdcaCount();
    if (newCount >= iOldCount)
        iGrid->HandleItemAdditionL();
    else
        {
        iGrid->HandleItemRemovalL();
        if ( ( iGrid->Model()->NumberOfItems() % iGrid->GridView()->NumberOfColsInView() ) == 0 )
            { 
            TInt logicalRow;
            TInt logicalColumn;   
            TInt topItemIndex; 
            
            iGrid->GridView()->LogicalPosFromListBoxIndex(  
                iGrid->TopItemIndex(), 
                logicalRow, 
                logicalColumn );
                
            logicalRow = Max( 0, logicalRow - 1 ); 
            
            iGrid->GridView()->ListBoxIndexFromLogicalPos(  
                topItemIndex, 
                logicalRow, 
                logicalColumn );
                
            iGrid->SetTopItemIndex( topItemIndex );
            }
        }
    _AKNTRACE_FUNC_EXIT;
    }

// ---------------------------------------------------------
// CAknFastSwapWindowControl::AddIconToArrayL
// Application is added to the AknGrid icon array
// if it can be found and if there is enough memory
// If not, default application icon is used
// ---------------------------------------------------------
//
TBool CAknFastSwapWindowControl::AddIconToArrayL( TUid aAppUid )
    {
    _AKNTRACE_FUNC_ENTER;
    _AKNTRACE( "[%s] aAppUid = %d", __FUNCTION__, aAppUid.iUid );
    if ( iLowMemory )
        {
        // when memory is low, only one prereserved 
        // default app icon is used for every grid item
        TRAPD( err, iIconArray->AppendL( iDefaultAppIcon) );
        if ( err != KErrNone )
            {
            _AKNTRACE_FUNC_EXIT;
            // if memory runs out, FSW uses what it has 
            // and continues (should never happen)
            return EFalse;
            }
        iLowMemIcons = ETrue;
       
        // fsw can only quarantee KMinimumSupportedApps number of apps 
        // in low memory conditions, so after KMinimumSupportedApps items
        // no more items are added to the memory
        if ( iItemTextArray->Count() >= KMinimumSupportedApps )
            {
            _AKNTRACE_FUNC_EXIT;
            return EFalse;
            }
        }
    else
        {
        CGulIcon* icon;
        CFbsBitmap* bitmap;
        CFbsBitmap* mask;
        MAknsSkinInstance* skin = AknsUtils::SkinInstance();
        // Retrieve the app icon using the Uid
        AknsUtils::CreateAppIconLC( skin, aAppUid, EAknsAppIconTypeList,bitmap, mask );
        User::LeaveIfError( AknIconUtils::SetSize( bitmap, IconSize() ) );
        icon = CGulIcon::NewL( bitmap, mask );    //takes ownership
        CleanupStack::PushL( icon );
        CleanupStack::Pop( 2 ); // bitmap, mask
        iIconArray->AppendL( icon );       //takes ownership
        CleanupStack::Pop(); // icon
        }
    _AKNTRACE_FUNC_EXIT;
    return ETrue;
    }
   
// ---------------------------------------------------------
// CAknFastSwapWindowControl::SwitchToApplicationL
// Either launches an application using method LaunchAppL
// or brings existing task to foreground by calling method SwitchToTask
// ---------------------------------------------------------
//
void CAknFastSwapWindowControl::SwitchToApplicationL( TInt aIndex )
    {
    _AKNTRACE_FUNC_ENTER;
    _AKNTRACE( "[%s] aIndex = %d", __FUNCTION__, aIndex );
    // abort FSW transition when item chosen (case when choosing quickly)
    GfxTransEffect::Abort();
    TInt wgId = (*iShownWgIds)[ aIndex ].iWgId;

    // launches application and closes fastswap
    if ( wgId == KApplicationWithoutWG )
        {
        LaunchAppL( iAlwaysShownList->IndexToAppUid( aIndex ) );
        }
    // brings existing application to foreground and closes fastswap    
    else 
        {
        if ( iAlwaysShownList->IsAlwaysShownApp( wgId ) &&
             iAlwaysShownList->IndexToAppUid( aIndex ) == KMenuAppUid )
            {     
            TBuf<128> viewType;
            if ( wgId != iBackgroundWgId || 
                 ( RProperty::Get(KFSWMMenuPSCat, KFSWMMenuLastViewKey, viewType) == KErrNone &&
                 viewType.Compare(KFSWMMenuFolderView) != 0 ) )
                {
                TApaTask task( iEikonEnv->WsSession() );       
                task.SetWgId( wgId );       
                task.SendMessage(KUidApaMessageSwitchOpenFile, KNullDesC8);                       
                } 
            }
        SwitchToTask( wgId );
        } 
    _AKNTRACE_FUNC_EXIT;
    }

// ---------------------------------------------------------
// CAknFastSwapWindowControl::SwitchToTask
// Brings a task associated with the given window group to
// the foreground, and dismissed CAknFastswapWindowControl
// from the screen and removes it from the control stack
// ---------------------------------------------------------
//
void CAknFastSwapWindowControl::SwitchToTask( TInt aWgId )
    {
    _AKNTRACE_FUNC_ENTER;
    _AKNTRACE( "[%s] aWgId = %d", __FUNCTION__, aWgId );
    CloseFastSwap();
    if( iFirstAppWgId != aWgId && iBackgroundWgId != aWgId )
        {
        GfxTransEffect::BeginFullScreen(5000,
        TRect(0,0,0,0),
        AknTransEffect::EParameterType,
        
        AknTransEffect::GfxTransParam(
            iAppUi.Application()->AppDllUid(), 
            AknTransEffect::TParameter::EActivateExplicitContinue));
        }
        
    CAknSgcClient::MoveApp(aWgId, ESgcMoveAppToForeground);
    _AKNTRACE_FUNC_EXIT;
    }

// ---------------------------------------------------------
// CAknFastSwapWindowControl::SwitchToTask
// Launches an application to the phone memory based on the 
// given application uid and closes the fastswap
// ---------------------------------------------------------
//
void CAknFastSwapWindowControl::LaunchAppL( TUid aAppUid )
    {
    _AKNTRACE_FUNC_ENTER;
    _AKNTRACE( "[%s] aAppUid = %d", __FUNCTION__, aAppUid.iUid );
    RApaLsSession ls;                   
    User::LeaveIfError(ls.Connect());   
    CleanupClosePushL(ls);
    CApaCommandLine* cmdLine=CApaCommandLine::NewLC();
    cmdLine->SetCommandL(EApaCommandRun); 
    TApaAppInfo info; 
    iAppArcSession.GetAppInfo( info, aAppUid );
    cmdLine->SetExecutableNameL( info.iFullName );
    ls.StartApp( *cmdLine ); 
    CleanupStack::PopAndDestroy(2); // cmdLine, ls
    // informing the system about a transition 
    
    CloseFastSwap();    
    _AKNTRACE_FUNC_EXIT;
    }
    
        
// ---------------------------------------------------------
// CAknFastSwapWindowControl::CloseFastSwap
// Dismisses CAknFastswapWindowControl
// from the screen and removes it from the control stack
// ---------------------------------------------------------
//
void CAknFastSwapWindowControl::CloseFastSwap()
    {
    _AKNTRACE_FUNC_ENTER;
    if ( iIsDisplayed )
        {
        TInt effectValue( 0 );
        iThemesAppRepository->Get( KThemesTransitionEffects, effectValue );
        if ( effectValue == 0 ) /* TAT on */
            {
            MTouchFeedback* feedback = MTouchFeedback::Instance();
            if ( feedback )
                {
                feedback->InstantFeedback( ETouchFeedbackPopupClose );
                }
            }
        // calculate already here since PositionRelativeToScreen
        // causes a flush to WS, which can disturb transition
        TPoint dPoint( iGrid->PositionRelativeToScreen() );
        TRect dRect( iGrid->Rect() );
        dRect.Move( dPoint );
        TBool visible = IsVisible();
   
        TBool rsWasEnabled( EFalse );

        if( !iDisableFSWEffect )
            {
            if( !iTransparencyEnabled && Window().IsRedrawStoreEnabled() )
                {
                rsWasEnabled = ETrue;
                // disable rsStore during transition
                Window().EnableRedrawStore( EFalse );
                }
            // If we never got to the callback after the appear effect, we
            // remove the observer here, so that we don't get the callback
            // when the disappear effect finishes.
            CAknFastSwapData *data = 
                (CAknFastSwapData*)CAknTransitionUtils::GetData( (TInt)this );
            CAknTransitionUtils::RemoveObserver( data,
                CAknTransitionUtils::EEventControlTransitionFinished );

            if(visible)
                {   
                GfxTransEffect::Begin( this, KGfxControlDisappearAction );
                GfxTransEffect::NotifyExternalState(ECaptureComponentsBegin, (const TDesC8*)this);
                }
            }
        delete iConfirmCloseDialog;
        iConfirmCloseDialog = NULL;
        iTooltip->HideInfoPopupNote();

        if ( iTimeOut->IsActive() )
            {
            iTimeOut->Cancel();
            StopAnimation();
            iState = EWaiting;    
            iTooltipModeTouch = EFalse;
            }
        if ( iIsStylusPopupShow )
            {
            //for Hide popup menu,but CStylusPopupMenu does not export HideMenu method.  
            delete iPopupMenu;
            iPopupMenu = NULL;
            SetHiddenFlag();    
            }
        
         
        MakeVisible( EFalse );
        if( !iDisableFSWEffect )
            {
            if(visible)
                {              
                CAknTransitionUtils::MakeVisibleSubComponents( this,
                                        CAknTransitionUtils::EForceInvisible );
                GfxTransEffect::SetDemarcation( this, dRect );
                GfxTransEffect::NotifyExternalState(ECaptureComponentsEnd, (const TDesC8*)this);
                GfxTransEffect::End( this );
                }
            if( !iTransparencyEnabled && rsWasEnabled )
                {
                Window().EnableRedrawStore( ETrue );
                }
            }
        GfxTransEffect::Deregister( this );

        FadeBackground( EFalse );

        AknGlobalPopupPriorityController::ShowPopup(*this, EFalse);
        
        InvalidateWindows(this);
            
        iCba->MakeVisible( EFalse );
        SetFocus( EFalse );
        iAppUi.RemoveFromStack( iCba->ButtonGroup()->AsControl() );
        iAppUi.RemoveFromStack( this );
        
        SetPointerCapture( EFalse );
        //IgnoreEventsUntilNextPointerUp();

        // Item array data like app names and icons 
        // is not preserved when the FSW is not visible
        // (to save used heap)
        ClearItemArrays( ETrue );
        }
    iIsDisplayed = EFalse;
    _AKNTRACE_FUNC_EXIT;
    }

// ---------------------------------------------------------
// CAknFastSwapWindowControl::CleanupRunFastSwap
// ---------------------------------------------------------
//
void CAknFastSwapWindowControl::CleanupRunFastSwap(TAny* aThis)
    {
    ( (CAknFastSwapWindowControl*) aThis)->CloseFastSwap();
    }

// ---------------------------------------------------------
// CAknFastSwapWindowControl::HandleShortAppsKeyPressL
// ---------------------------------------------------------
//
void CAknFastSwapWindowControl::HandleShortAppsKeyPressL()
    {
    _AKNTRACE_FUNC_ENTER;
    if ( !iConfirmCloseDialog && IsFocused() )
        {
        TInt index = ( iGrid->CurrentDataIndex() + 1) % iShownWgIds->Count();
        iGrid->SetCurrentDataIndex( index );
        iGrid->DrawDeferred();
        UpdateTooltipL();
        iTooltip->ShowInfoPopupNote();
        }
    _AKNTRACE_FUNC_EXIT;
    }

// ---------------------------------------------------------
// CAknFastSwapWindowControl::HandleLongAppsKeyPressL
// ---------------------------------------------------------
//
void CAknFastSwapWindowControl::HandleLongAppsKeyPressL()
    {
    _AKNTRACE_FUNC_ENTER;
    if (!iConfirmCloseDialog)
        {
        HandleListBoxEventL( iGrid, EEventEnterKeyPressed );
        }
    _AKNTRACE_FUNC_EXIT;
    }

// ---------------------------------------------------------
// CAknFastSwapWindowControl::MopSupplyObject
// ---------------------------------------------------------
//
TTypeUid::Ptr CAknFastSwapWindowControl::MopSupplyObject(TTypeUid aId)
    {
    if ( aId.iUid == MAknsControlContext::ETypeId )
        {
        return ( MAknsControlContext::SupplyMopObject( aId, iFrameContext ) ) ;
        }

    return SupplyMopObject(aId, iCba);
    }

// ---------------------------------------------------------
// CAknFastSwapWindowControl::FastSwapWindowRect
// ---------------------------------------------------------
//
TRect CAknFastSwapWindowControl::FastSwapWindowRect()
    {
    _AKNTRACE_FUNC_ENTER;
    TRect parent;
    TAknLayoutRect rect;  
    TRect finalRect;  
    AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EPopupParent, parent );
    AknLayoutUtils::TAknCbaLocation cbaLocation( AknLayoutUtils::CbaLocation() );  
    
    TInt variety( 0 );
    if ( cbaLocation == AknLayoutUtils::EAknCbaLocationRight )
        {
        variety = 3;
        }
    else if ( cbaLocation == AknLayoutUtils::EAknCbaLocationLeft )
        {
        variety = 6;
        }
    else
        {
        variety = 0;
        }
        
    if( Layout_Meta_Data::IsLandscapeOrientation() && 
        Layout_Meta_Data::IsPenEnabled() &&
        cbaLocation == AknLayoutUtils::EAknCbaLocationBottom && 
        !AknStatuspaneUtils::FlatLayoutActive() )
        {
        variety = 3; 
        }
    rect.LayoutRect( parent, 
        AknLayoutScalable_Avkon::popup_fast_swap2_window( 
            variety + NumberOfVisibleRows() - 1 ).LayoutLine() );
    _AKNTRACE_FUNC_EXIT;
    return rect.Rect();        
    }
    
// ---------------------------------------------------------
// CAknFastSwapWindowControl::CountFadedComponents
// ---------------------------------------------------------
//
TInt CAknFastSwapWindowControl::CountFadedComponents()
    {
    return 4;
    }

// ---------------------------------------------------------
// CAknFastSwapWindowControl::FadedComponent
// ---------------------------------------------------------
//
CCoeControl* CAknFastSwapWindowControl::FadedComponent(TInt aIndex)
    {
    _AKNTRACE( "[%s] aIndex = %d", __FUNCTION__, aIndex );
    switch (aIndex)
        {
        case 0:
            return this;
        case 1:
            return iGrid;
        case 2:
            return iCba;
        case 3:
            return iLongTapAnimation;
        default:
            return NULL;
        }
    }

// ---------------------------------------------------------
// CAknFastSwapWindowControl::OfferCloseSelectedAppL
// ---------------------------------------------------------
//
TBool CAknFastSwapWindowControl::OfferCloseSelectedAppL(const TDesC& aName)
    {
    _AKNTRACE_FUNC_ENTER;
    HBufC* msg = StringLoader::LoadLC(R_CONFIRM_CLOSE_APP_MESSAGE, aName, iEikonEnv);
    delete iConfirmCloseDialog;
    iConfirmCloseDialog = NULL;
    iConfirmCloseDialog = CAknQueryDialog::NewL( CAknQueryDialog::EConfirmationTone );
    iConfirmCloseDialog->SetPromptL( *msg );
    CleanupStack::PopAndDestroy(msg);
    TBool ok = iConfirmCloseDialog->ExecuteLD(R_CONFIRM_CLOSE_APP_QUERY);
    iConfirmCloseDialog = NULL;
    _AKNTRACE_FUNC_EXIT;
    return ok;
    }

// ---------------------------------------------------------
// CAknFastSwapWindowControl::IsWgIdInShownList
// ---------------------------------------------------------
//
TBool CAknFastSwapWindowControl::IsWgIdInShownList(TInt aWgId)
    {
    _AKNTRACE_FUNC_ENTER;
    _AKNTRACE( "[%s] aWgId = %d", __FUNCTION__, aWgId );
    TInt count = iShownWgIds->Count();
    for (TInt ii=0; ii<count; ii++)
        {
        if ( iShownWgIds->At(ii).iWgId == aWgId )
            {
            _AKNTRACE_FUNC_EXIT;
            return ETrue;
            }
        }
    _AKNTRACE_FUNC_EXIT;
    return EFalse;
    }

// ---------------------------------------------------------
// CAknFastSwapWindowControl::FocusChanged
// ---------------------------------------------------------
//
void CAknFastSwapWindowControl::FocusChanged(TDrawNow /*aDrawNow*/)
    {
    _AKNTRACE_FUNC_ENTER;
    if( iGrid )
        {
        iGrid->SetFocus( IsFocused() );
        }

    if (!IsFocused() && iTooltip)
        {
        iTooltip->HideInfoPopupNote();
        }
    if ( !IsFocused() && iIsStylusPopupShow )
        {
        delete iPopupMenu;
        iPopupMenu = NULL;
        SetHiddenFlag();
        }
    _AKNTRACE_FUNC_EXIT;
    }

// ---------------------------------------------------------
// CAknFastSwapWindowControl::SizeChanged
// ---------------------------------------------------------
//
void CAknFastSwapWindowControl::SizeChanged()
    {
    _AKNTRACE_FUNC_ENTER;
    // FSW tries to update the UI
    TRAPD( err, UpdateViewL() );
   
    // if the creation of the grid wasn't successful,
    // FSW creates a grid without reserving new icons       
    if ( err != KErrNone )
        {
        if ( err == KErrNoMemory )
            {
            // FSW in low memory
            iLowMemory = ETrue;
            TRAP_IGNORE( UpdateViewL() );
            iLowMemory = EFalse;    
            // above should always work, because memory is always 
            // reserved for default application icon and the minimum of 20 apps
            }
        }    
    _AKNTRACE_FUNC_EXIT;
    }

// ---------------------------------------------------------
// CAknFastSwapWindowControl::HandleResourceChange
// ---------------------------------------------------------
//
void CAknFastSwapWindowControl::HandleResourceChange(TInt aType)
    {
    _AKNTRACE_FUNC_ENTER;
    _AKNTRACE( "[%s] aType = %d", __FUNCTION__, aType );
    CCoeControl::HandleResourceChange(aType);
    if ( aType == KAknsMessageSkinChange )
        {
        TRAP_IGNORE( UpdateDefaultAppIconL() );
        }
    if ( iCba )
        {
        iCba->HandleResourceChange(aType);
        }
    if(iGrid && iGrid->ScrollBarFrame() && iGrid->ScrollBarFrame()->VerticalScrollBar())
        {
        iGrid->ScrollBarFrame()->VerticalScrollBar()->HandleResourceChange(aType);
        }
    if ( aType == KEikDynamicLayoutVariantSwitch )
        {
        SetRect( FastSwapWindowRect() );
        }
    _AKNTRACE_FUNC_EXIT;
    }

// ---------------------------------------------------------
// CAknFastSwapWindowControl::CreateItemArraysL
// During the creation of the grid the used item arrays
// are also created and set in to the grid. Arrays reserve 
// memory so that fsw can be quaranteed to work also in 
// low memory conditions.
// ---------------------------------------------------------
//
void CAknFastSwapWindowControl::CreateItemArraysL()
    {
    _AKNTRACE_FUNC_ENTER;
    // fetch default application icon from the skin
    UpdateDefaultAppIconL();
    
    // FSW reserves memory for icon and item arrays
    iIconArray = new (ELeave) CArrayPtrFlat<CGulIcon>(KFSWArrayGranularity);
    iItemTextArray = new (ELeave) CDesCArrayFlat(KFSWArrayGranularity);
    iIconArray->SetReserveL( KMinimumSupportedApps );
    TBuf<2*KMaxFileName+1> name;
    for ( TInt count = 0; count < KMinimumSupportedApps; count ++)
        {
        iItemTextArray->AppendL( name );
        }
    iItemTextArray->Delete( NULL, iItemTextArray->Count() );  
    // without setting this null the automatically created itemtextarray
    // wont be freed
    iGrid->Model()->SetItemTextArray( NULL );
    // grid doesn't take ownership of the arrays
    iGrid->Model()->SetOwnershipType( ELbmDoesNotOwnItemArray );
    // arrays are set into grid
    iGrid->Model()->SetItemTextArray( iItemTextArray ); 
    iGrid->ItemDrawer()->FormattedCellData()->SetIconArrayL( iIconArray );
    _AKNTRACE_FUNC_EXIT;
    }

// ---------------------------------------------------------
// CAknFastSwapWindowControl::SetDefaultAppIconL
// Retrieves the default application icon from the skin,
// icon is to be used when there is no memory to reserve new icons
// ---------------------------------------------------------
//
void CAknFastSwapWindowControl::UpdateDefaultAppIconL()
    {
    _AKNTRACE_FUNC_ENTER;
    CGulIcon* defaultAppIcon = NULL;
    TRAPD( error,defaultAppIcon = AknsUtils::CreateGulIconL( 
        AknsUtils::SkinInstance(),
        KAknsIIDQgnMenuUnknownCxt,
        AknIconUtils::AvkonIconFileName(),
        EMbmAvkonQgn_menu_unknown_cxt,
        EMbmAvkonQgn_menu_unknown_cxt_mask ) );
    CleanupStack::PushL( defaultAppIcon );
    if ( error != KErrNone )
        {
        if ( error == KErrNoMemory )
            {
            _AKNTRACE_FUNC_EXIT;
            return;
            }
        else
            {
            User::LeaveIfError(error); 
            }
        }
    User::LeaveIfError( AknIconUtils::SetSize( 
        defaultAppIcon->Bitmap(),
        IconSize() ) );
    if ( iIconArray != NULL && iIconArray->Count() > 0)
        {
        for ( TInt i = 0; i < iIconArray->Count(); i++ )
             {
             if( iDefaultAppIcon == iIconArray->At(i) )
                {
                iIconArray->At(i) = defaultAppIcon;
                }
             }
        }
    delete iDefaultAppIcon;
    iDefaultAppIcon = defaultAppIcon;
    CleanupStack::Pop(); // defaultAppIcon 
    _AKNTRACE_FUNC_EXIT;
    }

// ---------------------------------------------------------
// CAknFastSwapWindowControl::ClearItemArrays
// The content is deleted from arrays and arrays can be compressed 
// to the reserved size KMinimumSupportedApps
//
// TBool aCompress states whether the arrays are are to be compressed or not
//
// ---------------------------------------------------------
//
void CAknFastSwapWindowControl::ClearItemArrays( TBool aCompress )
    {
    _AKNTRACE_FUNC_ENTER;
    _AKNTRACE( "[%s] aCompress = %d", __FUNCTION__, aCompress );
    // Old count is used comparison later when new items are added to array
    // if handling of the item addition / removal is needed for the fsw grid
    if ( !iIconArray ) 
        {
        _AKNTRACE_FUNC_EXIT;
        return;
        }
    TInt currentlyReserved = iIconArray->Count();
    if ( currentlyReserved > NULL ) 
        {
        // compression for arrays is done when the closefastswap is called
        // when the fsw is updated while visible compression is not very wise
        // since the item arrays are probably very close to the 
        if ( aCompress ) 
            {
            // if there have been two many applications running lets 
            // try to  compress the arrays to size of KMinimumSupportedApps
            if ( iItemTextArray->Count() > KMinimumSupportedApps ) 
                {
                iItemTextArray->Delete(
                    KMinimumSupportedApps, 
                    iItemTextArray->Count() - KMinimumSupportedApps);
                    
                iItemTextArray->Compress();
                }
            // arrays are deleted separately, since there exists situations
            // when memory allocation has failed and arrays have different 
            // number of cells
            if ( currentlyReserved > KMinimumSupportedApps )  
                {
                if ( iLowMemIcons ) 
                    {
                    // resizes to KMinimumSupportedApps, no dynamically loaded icons,
                    // every pointer in the icon array points to the same default app icon 
                    // (never deleted)
                    iIconArray->Delete( 
                        KMinimumSupportedApps, 
                        currentlyReserved - KMinimumSupportedApps );
                    }
                else
                    {
                    // deletes dynamically loaded icons
                    DeleteIcons( 
                        KMinimumSupportedApps, 
                        currentlyReserved - KMinimumSupportedApps );
                    }
                // compresses the array to max KMinimumSupportedApps
                iIconArray->Compress();
                TRAP_IGNORE( iGrid->HandleItemRemovalL() ); 
                }
            }
            
        // if arrays are emptified, fsw needs information 
        // how many apps were in the grid before the operation   
        iOldCount = iGrid->Model()->ItemTextArray()->MdcaCount();
        
        // the deletion doesn't free the memory reserved for the array,
        // but it emptifies the text array
        iItemTextArray->Delete( NULL, iItemTextArray->Count() );
    
        // if the memory was too low 
        // on the previously run, different icon array 
        // was used, and also needs to be freed differentely
        if ( iLowMemIcons ) 
            {
            // resizing doesn't free the memory
            // array or the used icon reserved
            //
            // below resize can leave when array is enlarged,
            // but in this case size always shrunk to NULL
            TRAP_IGNORE( iIconArray->Delete( NULL, iIconArray->Count() ) );
            iLowMemIcons = EFalse;
            }
        else 
            {
            // icons inside array are deleted from the memory, 
            // but the deletion doesn't free the memory 
            // reserved for the pointer array
            DeleteIcons( NULL, iIconArray->Count() );
            }
        }
    _AKNTRACE_FUNC_EXIT;
    }

// ---------------------------------------------------------
// CAknFastSwapWindowControl::IconSize
// Calculates and returns the icon size used in the fast swap list.
// ---------------------------------------------------------
//      
TSize CAknFastSwapWindowControl::IconSize()
    {
    _AKNTRACE_FUNC_ENTER;
    TRect appWindow;
    AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EApplicationWindow, appWindow );
    TAknLayoutRect rect;
    
    rect.LayoutRect( 
        FastSwapWindowRect(), 
        AknLayoutScalable_Avkon::aid_size_cell_fast2().LayoutLine());

    _AKNTRACE_FUNC_EXIT;
    return rect.Rect().Size();
    }

// ---------------------------------------------------------
// CAknFastSwapWindowControl::DeleteIcons
// Clears given array slots of dynamically loaded icons
// ---------------------------------------------------------
//
void CAknFastSwapWindowControl::DeleteIcons( TInt aIndex, TInt aCount )
    {
    _AKNTRACE_FUNC_ENTER;
    _AKNTRACE( "[%s] aIndex = %d aCount = %d", __FUNCTION__, aIndex, aCount );
    for ( TInt i = 0; i < aCount; i++ ) 
        {
        if(iDefaultAppIcon != iIconArray->At( aIndex + i ))
            {
                delete iIconArray->At( aIndex + i );
            }
        }
    iIconArray->Delete( aIndex, aCount ); 
    _AKNTRACE_FUNC_EXIT;
    }

// ---------------------------------------------------------
// CAknFastSwapWindowControl::NumberOfVisibleRows
// How many visible rows are shown in the fast swap grid
// ---------------------------------------------------------
//
TInt CAknFastSwapWindowControl::NumberOfVisibleRows()
    {
    _AKNTRACE_FUNC_ENTER;
    TAknLayoutScalableParameterLimits cellLimits = AknLayoutScalable_Avkon::cell_fast2_pane_ParamLimits();
    TInt numberOfGridColumns = cellLimits.LastColumn() + 1;
    TInt numberOfGridRows = cellLimits.LastRow() + 1;
    
    TInt numberOfRows = ( iNumberOfWGs - 1 ) / numberOfGridColumns + 1;
    if ( numberOfRows <= numberOfGridRows )
        {
        _AKNTRACE_FUNC_EXIT;
        return numberOfRows;
        }
    else 
        {
        _AKNTRACE_FUNC_EXIT;
        return numberOfGridRows;
        }
    }

// ---------------------------------------------------------
// CAknFastSwapWindowControl::CurrentAppName
// Gives the name of the application with current highlight
// ---------------------------------------------------------
//
TPtrC CAknFastSwapWindowControl::CurrentAppName()
    {
    _AKNTRACE_FUNC_ENTER;
    TPtrC name = iGrid->Model()->ItemText( iGrid->CurrentDataIndex() );
    name.Set( name.Mid( name.Find(KTab)+1) );
    _AKNTRACE_FUNC_EXIT;
    return name;
    }        

// ----------------------------------------------------------------------------
// CAknFastSwapperWindowControl::CreateStylusPopupMenu
// ----------------------------------------------------------------------------
// 
void CAknFastSwapWindowControl::CreateStylusPopupMenuL()
    {
    _AKNTRACE_FUNC_ENTER;
    if ( !iPopupMenu )
        {
        iPopupMenu = CAknStylusPopUpMenu::NewL( this, Rect().iTl );
        HBufC* openText = StringLoader::LoadLC( R_QTN_FSW_STYLUSPOPUPMENU_OPEN );
        HBufC* exitText = StringLoader::LoadLC( R_QTN_FSW_STYLUSPOPUPMENU_EXIT );
        iPopupMenu->AddMenuItemL( *openText, EAknCapServerCmdOpen );    
        iPopupMenu->AddMenuItemL( *exitText, EAknCapServerCmdClose );  
        CleanupStack::PopAndDestroy( exitText );
        CleanupStack::PopAndDestroy( openText );
        }
    _AKNTRACE_FUNC_EXIT;
    }

// ----------------------------------------------------------------------------
// CAknFastSwapperWindowControl::ShowPopupMenuL
// ----------------------------------------------------------------------------
//    
void CAknFastSwapWindowControl::ShowPopupMenuL() 
    {
    _AKNTRACE_FUNC_ENTER; 
    if ( !iPopupMenu )
        {
        CreateStylusPopupMenuL();    
        }
    
    if( iIsStylusPopupShow )
        {
        _AKNTRACE_FUNC_EXIT;
        return;
        }
    iIsStylusPopupShow = ETrue;

    iTooltipModeTouch = EFalse;
    SetPointerCapture( EFalse );
    RWindowGroup& rootWin = iCoeEnv->RootWin();
       
    TInt index = iGrid->CurrentDataIndex();
    index = index < 0 ? 0 : index;
   
    if ((*iShownWgIds)[index].iIsSystemApp)
        {            
        iPopupMenu->SetItemDimmed( EAknCapServerCmdClose, ETrue );
        }
    else
        {
        iPopupMenu->SetItemDimmed( EAknCapServerCmdClose, EFalse );   
        }
    iTooltip->HideInfoPopupNote();     
    TPoint pos = PositionRelativeToScreen();
    TInt itemIndex = iGrid->CurrentItemIndex();
    itemIndex = itemIndex < 0 ? 0 : itemIndex;
    TPoint posItem = iGrid->View()->ItemPos( itemIndex );
    if( posItem.iY < iGrid->View()->ViewRect().iTl.iY )
       {
       posItem.iY = iGrid->View()->ViewRect().iTl.iY;
       }
    pos.iY += posItem.iY;
    pos.iX += posItem.iX;

    if ( AknLayoutUtils::LayoutMirrored() )
        {
        TInt itemWidth = iGrid->View()->ItemSize( itemIndex ).iWidth;    
        pos.iX += itemWidth;
        }
    iPopupMenu->SetPosition( pos, CAknStylusPopUpMenu::EPositionTypeLeftBottom );
    
    MTouchFeedback* feedback = MTouchFeedback::Instance();
    if ( feedback )
        {
        // feedback on menu opening
        feedback->InstantFeedback( ETouchFeedbackPopUp );
        }
    iPopupMenu->ShowMenu();
    _AKNTRACE_FUNC_EXIT;
    }

// ----------------------------------------------------------------------------
// CAknFastSwapperWindowControl::TryCloseApplicationL
// ----------------------------------------------------------------------------
//    
void CAknFastSwapWindowControl::TryCloseApplicationL( TInt aIndex, TBool aIsShift )
    {
    _AKNTRACE_FUNC_ENTER;
    _AKNTRACE( "[%s] aIndex = %d aIsShift = %d", __FUNCTION__, aIndex, aIsShift );
    if ( aIndex == KErrNotFound || (*iShownWgIds)[aIndex].iIsSystemApp)
        {    
        _AKNTRACE_FUNC_EXIT;
        return;
        }

    iConfirmCloseWgId = (*iShownWgIds)[aIndex].iWgId;

    // if this leaves, okToClose will be left as ETrue
    iTooltip->HideInfoPopupNote();

    iIsClosing = ETrue;
    
    if ( aIsShift )
        {
        TApaTask task( iEikonEnv->WsSession() );
        task.SetWgId( iConfirmCloseWgId );
        task.SendSystemEvent( EApaSystemEventShutdown);
        }
    else
        {
        TWsEvent event;
        event.SetTimeNow();
        event.SetType(KAknShutOrHideApp); 
        iEikonEnv->WsSession().SendEventToWindowGroup(iConfirmCloseWgId, event);
        }

    _AKNTRACE_FUNC_EXIT;
    }
    
// ----------------------------------------------------------------------------
// CAknFastSwapperWindowControl::SetEmphasis
// ----------------------------------------------------------------------------
//    
void CAknFastSwapWindowControl::SetEmphasis(CCoeControl* /* aMenuControl */,TBool /* aEmphasis */)
    {
    
    }
    
// ----------------------------------------------------------------------------
// CAknFastSwapperWindowControl::SetHiddenFlag
// ----------------------------------------------------------------------------
//    
void CAknFastSwapWindowControl::SetHiddenFlag()
    {
    _AKNTRACE_FUNC_ENTER;
    if ( iIsStylusPopupShow )
        {
        SetPointerCapture( ETrue );
        iIsStylusPopupShow = EFalse;    
        }
    _AKNTRACE_FUNC_EXIT;
    }
    
// ----------------------------------------------------------------------------
// CAknFastSwapperWindowControl::PointerEventL
// ----------------------------------------------------------------------------
//      
void CAknFastSwapWindowControl::PointerEventL( const TPointerEvent& aEvent )
    {
    _AKNTRACE_FUNC_ENTER;
    _AKNTRACE( "[%s] event type = %d", __FUNCTION__, aEvent.iType );
    if ( ( iState == EShowingAnimation ||  iState == EWaitingForAnimation ) && 
           aEvent.iType == TPointerEvent::EDrag )
        {
        // Test whether the pointer event is filtered.
        TInt offset = AknLayoutScalable_Avkon::aid_value_unit2().LayoutLine().iW * 2 / 5;
        TRect dragMaxRect( iAnimationPosition.iX - offset, iAnimationPosition.iY - offset,
                           iAnimationPosition.iX + offset, iAnimationPosition.iY + offset );   
        if ( dragMaxRect.Contains( aEvent.iParentPosition ) )
            {
            _AKNTRACE_FUNC_EXIT;
            return;  
            }
        }

    // Whatever happens, cancel the timer and stop animation.
    iTimeOut->Cancel();
    StopAnimation();
    iState = EWaiting;
    iAnimationPosition = aEvent.iParentPosition;
    
    if ( iIsStylusPopupShow )
        {
        _AKNTRACE_FUNC_EXIT;
        // Do not start animation when the stylus popup menu is displayed.  
        return;    
        }
       
    if ( aEvent.iType == TPointerEvent::EButton1Down ) 
        {
        TInt touchedIndex = KErrNotFound;
        TBool isOverItem =
                            iGrid->GridView()->XYPosToItemIndex( aEvent.iPosition,
                            		                             touchedIndex);
        if( isOverItem && touchedIndex != iGrid->CurrentItemIndex())
           {
           iGrid->View()->ItemDrawer()->SetFlags( CListItemDrawer::EPressedDownState );
           touchedIndex = iGrid->GridView()->ActualDataIndex( touchedIndex );
           iGrid->SetCurrentDataIndex(touchedIndex);
           iGrid->DrawDeferred();       	
           }
        ShowTooltipTouchL( ETrue );
        iState = EWaitingForAnimation;
        iTimeOut->Start(
            KTimeDelayBeforeAnimation, 
            KTimeNeverHappenEvent,
            TCallBack( TimeOutCallBackL, this ) );
        }
    _AKNTRACE_FUNC_EXIT;
    }
    
// ----------------------------------------------------------------------------
// CAknFastSwapperWindowControl::ToolTipTimeOutCallBackL
// ----------------------------------------------------------------------------
//    
TInt CAknFastSwapWindowControl::ToolTipTimeOutCallBackL( TAny* aPtr )  
    {
    (STATIC_CAST(CAknFastSwapWindowControl*,aPtr))->HideTooltip();
    return KErrNone ;      
    }
    
// ----------------------------------------------------------------------------
// CAknFastSwapperWindowControl::HideTooltip
// ----------------------------------------------------------------------------
//     
void CAknFastSwapWindowControl::HideTooltip()
    {
    iToolTipTimer->Cancel();
    iTooltip->HideInfoPopupNote();     
    }
    
// ----------------------------------------------------------------------------
// CAknFastSwapperWindowControl::TimeOutCallBackL
// ----------------------------------------------------------------------------
//     
TInt CAknFastSwapWindowControl::TimeOutCallBackL( TAny* aPtr )
    {
    (STATIC_CAST(CAknFastSwapWindowControl*,aPtr))->ShowAnimationL(); 
    return KErrNone ;   
    }


// ---------------------------------------------------------------------------
// Handles the state changes in the long tap animation.
// ---------------------------------------------------------------------------
//      
void CAknFastSwapWindowControl::ShowAnimationL()
    {
    _AKNTRACE_FUNC_ENTER;
    if ( AknLayoutUtils::PenEnabled() )
        {
        switch ( iState )
            {
            case EWaitingForAnimation:
                {
                iState = EShowingAnimation;
                iTimeOut->Cancel();
                StartAnimationL();

                iTimeOut->Start( KLongTapDelay - KTimeDelayBeforeAnimation, 
                                 KTimeNeverHappenEvent,
                                 TCallBack( TimeOutCallBackL, this ) );
                break;
                }

            case EShowingAnimation:
            case EShowingPressedDownEffect:
                {
                iState = EShowingPressedDownEffect;
                iTimeOut->Cancel();
                StopAnimation();
                ShowPopupMenuL();
                iGrid->View()->ItemDrawer()->ClearFlags( CListItemDrawer::EPressedDownState ); 
                iState = EWaiting;
                break;
                }

            default:
                {
                break;
                }
            }
        }
    _AKNTRACE_FUNC_EXIT;
    }

// ----------------------------------------------------------------------------
// CAknFastSwapperWindowControl::StartAnimationL
// ----------------------------------------------------------------------------
//      
void CAknFastSwapWindowControl::StartAnimationL()
    { 
    iIsAnimationShowing = ETrue;
    iLongTapAnimation->ShowAnimationL( iAnimationPosition.iX,
                                       iAnimationPosition.iY );
    }

// ----------------------------------------------------------------------------
// CAknFastSwapperWindowControl::StopAnimationL
// ----------------------------------------------------------------------------
//     
void CAknFastSwapWindowControl::StopAnimation()
    {
    if ( iLongTapAnimation )
        {
        if ( iIsAnimationShowing )
            {
            iIsAnimationShowing = EFalse;    
            iLongTapAnimation->HideAnimation();
            }
        }        
    }
    
// ---------------------------------------------------------------------------
// CAknFastSwapperWindowControl::CancelAnimationAndPressDownEffect
// ---------------------------------------------------------------------------
//
void CAknFastSwapWindowControl::CancelAnimationAndPressDownEffect()
    {
    _AKNTRACE_FUNC_ENTER;
    iTimeOut->Cancel();
    StopAnimation();
    iState = EWaiting;

    iItemDraggingActioned = ETrue;

    CListItemDrawer* itemDrawer = iGrid->View()->ItemDrawer();

    if ( itemDrawer->Flags() & CListItemDrawer::EPressedDownState )
        {
        // Clear the pressed down state from the drawer and draw the
        // the normal highlight on the highlighter item.
        iGrid->View()->ItemDrawer()->ClearFlags( CListItemDrawer::EPressedDownState ); 
        iGrid->DrawItem( iGrid->CurrentItemIndex() );
        }
     _AKNTRACE_FUNC_EXIT;
    }

//  End of File
