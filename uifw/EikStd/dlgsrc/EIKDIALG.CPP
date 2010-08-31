/*
* Copyright (c) 1997-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:
*
*/


#include <eikdialg.h>
#include <eikon.hrh>
#include <eikmover.h>
#include <eikcapc.h>
#include <eikcapca.h>
#include <eikcmbut.h>
#include <eikdialg.pan>
#include <eikform.pan>
#include <barsread.h>
#include <eikenv.h>
#include <AknDef.h>
#include <eikbtpan.h>
#include <eikbtgpc.h>
#include <eikcore.rsg>
#include <eikappui.h>
#include <eikdialg.h>
#include <eikdpsel.h>
#include "EIKDBCOB.H"
#include <eiklbbut.h>
#include <aknborders.h>
#include <avkon.rsg>
#include <avkon.hrh>
#include <eikdpage.h>
#include <eikmop.h>
#include <aknenv.h>
//<SKIN>
#include "eikdialogext.h"
#include <AknsListBoxBackgroundControlContext.h>
#include <AknsDrawUtils.h>
#include <AknUtils.h>
#include <AknsUtils.h>
#include <aknlayoutscalable_avkon.cdl.h>
#include <skinlayout.cdl.h>
#include <eikdpobs.h>

#include <aknedwindrawingmodifier.h>

#include <AknMediatorFacade.h>
#include <AknMediatorObserver.h>
    
#include <aknglobalpopupprioritycontroller.h>
#include <aknview.h>
#include <aknViewAppUi.h>

#include <gfxtranseffect/gfxtranseffect.h>
#include <akntransitionutils.h>

#include <AknTasHook.h> // for testability hooks
#ifdef RD_UI_TRANSITION_EFFECTS_POPUPS
#include <akntranseffect.h>
#endif
#include <AknQueryDialog.h>
#include <aknQueryControl.h>

#include "akncbacontentobserver.h"

TBool IsBlankScreenDisplayed();


// -----------------------------------------------------------------------------
// Returns ETrue if CBA is embedded to dialog.
// @return ETrue if cba is embedded.
// -----------------------------------------------------------------------------
//
TBool CbaEmbeddedInDialog( const TInt& aFlags )
    {
    return AknLayoutUtils::PenEnabled() && 
        !( aFlags & EEikDialogFlagFillAppClientRect ) &&
        !( aFlags & EEikDialogFlagFillScreen ) &&
        !( aFlags & EEikDialogFlagVirtualInput );
    }


// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
//
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

// -----------------------------------------------------------------------------
// Finds out if this control belongs to the window group that is in focus.
// This information can be used to skip effects when the window group is
// not visible.
//
// @param aThis The control in question.
//
// @return ETrue if the window group is in focus, otherwise EFalse
// -----------------------------------------------------------------------------
//
TBool IsFocusedWindowGroup( CEikDialog* aThis )
    {
    RWindowTreeNode* node = aThis->DrawableWindow();
    // this code finds out if this control belongs to window group
    // that is in focus, there are some rare cases when the latest opened
    // popup goes behind another one (e.g. system lock query -> power key menu)
    // we don't want transition in that case
    RWsSession& wsSession = CEikonEnv::Static()->WsSession();

    TInt nodeWindowGroupId = node->WindowGroupId();
    TInt focusedWindowGroupId = wsSession.GetFocusWindowGroup();
    
    if ( nodeWindowGroupId == focusedWindowGroupId )
        {
        return aThis->IsFocused();
        }

    TInt count = wsSession.NumWindowGroups( 0 );

    // because there is not leave here,so no need to use CleanupStack.
    CArrayFixFlat<TInt>* wgIds = new CArrayFixFlat<TInt>( count );
    if ( wgIds )
        {
        // Get list of window group ids from WServ
        wsSession.WindowGroupList( 0, wgIds );

        // Select the first in the list (which will always be the forground app)
        // and we assume that there always will be at least one window group with zero priority
        TInt wgId = (*wgIds)[0];

        delete wgIds;

        if ( focusedWindowGroupId == wgId )
            {
            return ETrue;
            }
        }
    return EFalse;
    }

GLDEF_C void Panic(TEikDialogPanic aPanic)
	{
	_LIT(KPanicCat,"EIKON-DIALOG");
	User::Panic(KPanicCat,aPanic);
	}

GLDEF_C void Panic(TEikFormPanic aPanic)
	{
	_LIT(KPanicCat,"EIKON-FORM");
	User::Panic(KPanicCat,aPanic);
	}

enum
    { // follow on from values in UIKON.HRH
    EEikDialogFlagSleeping	=0x20000,
	EEikDialogFlagBroughtForward=0x40000,
	// EEikDialogFlagNoBackgroundFade = 0x80000 in uikon.hrh,
	EEikDialogAttemptFadeWhenVisible=0x100000
    // 0x20000 is used by uikon.hrh
    };

// AknSecondaryDisplaySupportUtilities
#if ((defined(__COVER_DISPLAY) || defined(__VOICE_UI )))   

void IssueMediatorCommand(CEikDialog* aDialog)
    {
    CAknMediatorFacade* caps = AknMediatorFacade(aDialog);
    if (caps)
        {
        caps->IssueCommand();
        }
    }
	
void CancelMediatorCommand(CEikDialog* aDialog)
    {
    CAknMediatorFacade* caps = AknMediatorFacade(aDialog);
    if (caps)
        {
        caps->CancelCommand();
        }
    }

#else

void CancelMediatorCommand(CEikDialog*){}
void IssueMediatorCommand(CEikDialog*){}

#endif

EXPORT_C CEikDialog::CEikDialog()
    {
//	__DECLARE_NAME(_S("CEikDialog"));
//	No border in Avkon
	iBorder=TGulBorder(TGulBorder::ENone);
    SetMopParent(iEikonEnv->EikAppUi());
#if defined (__DEBUG__)
	RDebug::ProfileReset(PROFILE_POINT_EIKON_DIALOG_LOAD,1);
	RDebug::ProfileStart(PROFILE_POINT_EIKON_DIALOG_LOAD);
#endif
#ifdef RD_UI_TRANSITION_EFFECTS_POPUPS
    GfxTransEffect::Register(this,KGfxPopupDefaultControlUid);
#endif
    AKNTASHOOK_ADD( this, "CEikDialog" );
    }

EXPORT_C CEikDialog::~CEikDialog()
    {
    AKNTASHOOK_REMOVE();

    EnableContentObserver( EFalse );

    if ( GfxTransEffect::IsRegistered( this ) )
        {
        // ensure that this is not drawn since parts are destroyed
        MakeVisible( EFalse ); 
        CAknTransitionUtils::MakeVisibleSubComponents( this,
                                        CAknTransitionUtils::EForceInvisible );
        GfxTransEffect::Deregister(this); //Always deregister in destructor.
        }

    // remove from stack before deleting members, this way focus changed will behave correctly
	if (!(iDialogFlags&EEikDialogFlagModeless))
	    iEikonEnv->RemoveFromStack(this);

	FadeBehindPopup(EFalse);
	if (iDialogFlags&EEikDialogFlagBroughtForward)
		iEikonEnv->BringForwards(EFalse);
	AknGlobalPopupPriorityController::RemovePopupPriority(*this);
	delete iButtonCommandObserver;
	delete iTitleBar;
	delete iPageSelector;
	delete iButtonGroupContainer;
	delete iExtension ;
	iExtension = NULL;
	StopWaitingAsRequired();
    }

void CEikDialog::DynamicConstructL()
	{
    PreLayoutDynInitL();

    if ( iPageSelector && iPageSelector->IsForm() && Extension() )
        {
        Extension()->iPublicFlags.Set( CEikDialogExtension::EFullyConstructed );
        }

    EnableContentObserver( ETrue );

    Layout();
    PostLayoutDynInitL();
	}

/**
 * Prepares the dialog, constructing it from the resource with id aResourceId.
 *
 * The dialog is  added to the stack in here to avoid a possible reallocation
 * of the stack in RunLD,  the purpose is to be able to display note dialogs in OOM
 * situations.
 */
EXPORT_C void CEikDialog::PrepareLC(TInt aResourceId)
    {
    CleanupStack::PushL(this);
	BaseConstructL();
    StaticConstructL(aResourceId);
	
	if (!(iDialogFlags&EEikDialogFlagModeless))
		{
		AknGlobalPopupPriorityController::AddPopupToControlStackL(*this,ECoeStackPriorityDialog,ECoeStackFlagRefusesAllKeys);
		}
    }

/**
 * Reads the dialog resources into the dialog, constructing it from the specified resource.
 * The function is only to help loading dialog resources and 
 * extracting dialog data.
 *
 * Code is same as in PrepareLC() but iEikonEnv->EikAppUi()->AddToStackL() is omitted
 */
EXPORT_C void CEikDialog::ReadResourceLC(TInt aResourceId)
    {
    CleanupStack::PushL(this);
	BaseConstructL();
    StaticConstructL(aResourceId);
    }

/**
 * Prepares and runs the dialog and returns the id of the button used to dismiss
 * it. The dialog is constructed from the resource with id aResourceId and is destroyed
 * on exit.
 */
EXPORT_C TInt CEikDialog::ExecuteLD(TInt aResourceId)
    {
	PrepareLC(aResourceId);
	return(RunLD());
    }

void CEikDialog::BaseConstructL()
	{
    CreateWindowL();
	Window().SetBackgroundColor(iEikonEnv->ControlColor(EColorDialogBackground,*this));
	EnableDragEvents();
	Window().SetPointerGrab(ETrue);
    iContext=this;
    Window().SetBackgroundColor(iEikonEnv->ControlColor(EColorDialogBackground,*this));

	iButtonCommandObserver=CEikDialogButtonCommandObserver::NewL(*this);
    if (!iExtension)
        {
	    iExtension = CEikDialogExtension::NewL( *this ) ;        
        }
	}

void CEikDialog::StaticConstructL(TInt aResourceId)
    {
    TResourceReader reader;
    iCoeEnv->CreateResourceReaderLC(reader,aResourceId);
    ConstructFromResourceL(reader);
	CleanupStack::PopAndDestroy();
	
    if ( CAknEnv::Static()->TransparencyEnabled() )
        {
        if ( !(iDialogFlags & EEikDialogFlagFillAppClientRect ||
           iDialogFlags & EEikDialogFlagFillScreen ) )
            {
            Window().SetRequiredDisplayMode( EColor16MA );
            TInt err = Window().SetTransparencyAlphaChannel();

            if ( err == KErrNone )
                {
                Window().SetBackgroundColor(~0);
                }
            }
        }
    }

/**
 * Constructs a sleeping dialog from the resources identified by aResourceId.
 * A sleeping dialog is one which can be displayed at any time since its memorey
 * resources are pre-allocated.
 */
EXPORT_C void CEikDialog::ConstructSleepingDialogL(TInt aResourceId)
	{
	CommonConstructSleepingDialogL(aResourceId);
    AknGlobalPopupPriorityController::AddPopupToControlStackL(*this,ECoeStackPriorityDialog,ECoeStackFlagRefusesAllKeys|ECoeStackFlagRefusesFocus|ECoeStackFlagSharable);
	}

/**
 * Constructs a sleeping dialog from the resources identified by aResourceId
 * at a high priority on the control stack.
 */
EXPORT_C void CEikDialog::ConstructSleepingAlertDialogL(TInt aResourceId)
	{
 	CommonConstructSleepingDialogL(aResourceId);
    AknGlobalPopupPriorityController::AddPopupToControlStackL(*this,ECoeStackPriorityAlert,ECoeStackFlagRefusesAllKeys|ECoeStackFlagRefusesFocus|ECoeStackFlagSharable);
	}

void CEikDialog::CommonConstructSleepingDialogL(TInt aResourceId)
	//
	// code common to both ConstructSleepingDialogL & ConstructSleepingAlertDialogL
	//
	{
	iDialogFlags|=EEikDialogFlagSleeping;
	BaseConstructL();
	StaticConstructL(aResourceId);
	MakeVisible(EFalse);
	if (iButtonGroupContainer)
		{
		// non visible CBA's do not recieve keys
		iButtonGroupContainer->MakeVisible(EFalse);
		}
	}

TInt CEikDialog::WaitAsRequired()
    {
    TInt exitConfirmed=0;
#if defined (__DEBUG__)
	RDebug::ProfileEnd(PROFILE_POINT_EIKON_DIALOG_LOAD);
	TProfile profile;
	RDebug::ProfileResult(&profile,PROFILE_POINT_EIKON_DIALOG_LOAD,1);
	TBuf<60> tmp;
	_LIT(KMsg,"Time to load dialog: %d milliseconds");
	tmp.Format(KMsg,profile.iTime/1000);
	iEikonEnv->VerboseInfoMsg(tmp);
#endif

    if (iDialogFlags&EEikDialogFlagWait)
        {
		iExitConfirmed=(&exitConfirmed);
        iWait.Start();
        }

	return(exitConfirmed);
    }

void CEikDialog::StopWaitingAsRequired()
	{
	CAknEnv::StopSchedulerWaitWithBusyMessage(iWait);
	}

/**
 * Rouses a sleeping dialog by dynamically constructing it and then 
 * bringing it to the front.
 */
EXPORT_C TInt CEikDialog::RouseSleepingDialog()
	{ // none of following ...L calls to Leave
	if (IsVisible())
		ExitSleepingDialog(); // eg for rousing an already roused Alert dialog


    #ifdef RD_UI_TRANSITION_EFFECTS_POPUPS
    //make sure that "this" is registered
    if( !GfxTransEffect::IsRegistered( this ) )
        {
        if ( iExtension->iRegisteredContext != KNullUid )
            {
            GfxTransEffect::Register( this, iExtension->iRegisteredContext );
            }
        else
            {
            GfxTransEffect::Register( this, KGfxPopupDefaultControlUid );
            }
        }
    #endif
    //if registered then do not animate bitmaps until after transition is complete
    if( GfxTransEffect::IsRegistered( this ) ) 
        {
        CAknTransitionUtils::SetData(EDontAnimateBitmaps, (TAny*)this);
        }
	ResetLineMinimumSizes();

	iEikonEnv->BringForwards(ETrue); // before the call to EnableBackup()
  	DrawableWindow()->SetOrdinalPosition(0);
	if (iButtonGroupContainer && iButtonGroupContainer->Location() == CEikButtonGroupContainer::EExternal)
	  	iButtonGroupContainer->ButtonGroup()->AsControl()->DrawableWindow()->SetOrdinalPosition(0);	
	AknGlobalPopupPriorityController::ShowPopup(*this, ETrue);
	iDialogFlags|=EEikDialogFlagBroughtForward;

	TRAPD(err, DynamicConstructL());
	if (err)
        {
        if( GfxTransEffect::IsRegistered( this ) ) 
            {
            CAknTransitionUtils::RemoveData( EDontAnimateBitmaps );
            }
        iEikonEnv->HandleError(err); // non mem allocating note shown
        return KErrNone; // Error handled, no need to show another note, 
        } //we will not delete dialog as there might be enough memory to show it in next try  

	if (~iDialogFlags&EEikDialogFlagNoBackup)
		DrawableWindow()->EnableBackup();

	FadeBehindPopup(ETrue);

	AknGlobalPopupPriorityController::RouseSleepingPopup(*this,ETrue);
	if (iCoeEnv->LastEvent().Type()==EEventPointer)
		ClaimPointerGrab(ETrue); // send pointer up to any dragged component
    SetInitialCurrentLine();

	TInt slidingMode = ESlidingDisabled;                 

	if ( (iExtension->LayoutCategory() == CEikDialogExtension::EPopupLayout) &&
	     (slidingMode != ESlidingDisabled) &&
	     IsVisible() )
	    {
        SlideDialog();	    
	    }

	TRAP(err, ActivateL());
	if (err)
		Panic(EEikDialogLeaveInSleepingDialog);

    IssueMediatorCommand(this);

    if( GfxTransEffect::IsRegistered(this) && !IsVisible() &&
        IsFocusedWindowGroup( this ) && !IsBlankScreenDisplayed() )
		{
        MakeVisible( EFalse );
        GfxTransEffect::NotifyExternalState( ENotifyGlobalAbort );
        CAknTransitionUtils::MakeVisibleSubComponents( this,
                                        CAknTransitionUtils::EForceInvisible );

		CAknTransitionUtils::SetAllParents(this);
        InvalidateWindows( this );
		GfxTransEffect::Begin(this, KGfxControlAppearAction);
		GfxTransEffect::NotifyExternalState(ECaptureComponentsBegin, (const TDesC8*)this);
		
		TRect demarcation;
		CAknTransitionUtils::GetDemarcation(CAknTransitionUtils::EPopup, 
		                                    demarcation);
		GfxTransEffect::SetDemarcation(this, demarcation);

        MakeVisible(ETrue);
        CAknTransitionUtils::MakeVisibleSubComponents( this,
                                        CAknTransitionUtils::EForceVisible );

		GfxTransEffect::NotifyExternalState(ECaptureComponentsEnd, (const TDesC8*)this);
		GfxTransEffect::End(this);
		}
	else
		{
		MakeVisible(ETrue);
		}
		
	if( GfxTransEffect::IsRegistered(this) )
		{
		CAknTransitionUtils::RemoveData(EDontAnimateBitmaps); 
		} 
		
	if (iButtonGroupContainer)
		{
		if (iButtonGroupContainer->Location() == CEikButtonGroupContainer::EExternal)
			{
			// Bring CBA to foreground and make visible
			// CBA used to be set to high control stack priority here,
			// but that resulted in bugs whereby a sleeping dialog which was behind another dialog
			// always had a higher CBA - just make sure they have the highest cba priority
			CCoeControl* cba = iButtonGroupContainer->ButtonGroup()->AsControl();
			AknGlobalPopupPriorityController::AddPopupToControlStackL(*cba,ECoeStackPriorityCba,ECoeStackFlagRefusesFocus);
			static_cast<CEikCba*>(cba)->SetSkinBackgroundId( KAknsIIDQsnBgAreaControlPopup );
			cba->MakeVisible(ETrue);
			cba->DrawNow();
			}
		}

    return(WaitAsRequired());
	}

/**
 * Exits a sleeping dialog without deleteing it.
 */
EXPORT_C void CEikDialog::ExitSleepingDialog()
	{
	FadeBehindPopup(EFalse);

    EnableContentObserver( EFalse );

	if(GfxTransEffect::IsRegistered(this) && IsVisible() 

#ifdef RD_UI_TRANSITION_EFFECTS_POPUPS	
	&& !iExtension->iSleepDialogExitBeginCalled
#endif
        && IsFocusedWindowGroup( this )
        && !IsBlankScreenDisplayed()
	)
		{
		CAknTransitionUtils::SetAllParents(this);
		GfxTransEffect::Begin(this, KGfxControlDisappearAction);
#ifdef RD_UI_TRANSITION_EFFECTS_POPUPS
		iExtension->iSleepDialogExitBeginCalled = ETrue;
#endif
		GfxTransEffect::NotifyExternalState(ECaptureComponentsBegin, (const TDesC8*)this);
		
#ifdef RD_UI_TRANSITION_EFFECTS_POPUPS
        TUid t;
        GfxTransEffect::NotifyExternalState(EGetRegistrationType, (const TDesC8*)&t);
        iExtension->iRegisteredContext = t;
#endif

		TRect demarcation;
		CAknTransitionUtils::GetDemarcation(CAknTransitionUtils::EPopup, 
		                                    demarcation);
		GfxTransEffect::SetDemarcation(this, demarcation);
		
		MakeVisible(EFalse);
        CAknTransitionUtils::MakeVisibleSubComponents( this,
                                        CAknTransitionUtils::EForceInvisible );

		GfxTransEffect::NotifyExternalState(ECaptureComponentsEnd, (const TDesC8*)this);
		GfxTransEffect::End(this);
		}
	else
		{
		MakeVisible(EFalse);
		}
#ifdef RD_UI_TRANSITION_EFFECTS_POPUPS
	GfxTransEffect::Deregister( this );
#endif

	if (iButtonGroupContainer)
		{
		iButtonGroupContainer->MakeVisible(EFalse);
		}
	AknGlobalPopupPriorityController::RouseSleepingPopup(*this,EFalse);
	if (iDialogFlags&EEikDialogFlagBroughtForward)
		{
		iEikonEnv->BringForwards(EFalse);
		AknGlobalPopupPriorityController::ShowPopup(*this, EFalse);
		iDialogFlags&=(~EEikDialogFlagBroughtForward);
		}
    StopWaitingAsRequired();
#ifdef RD_UI_TRANSITION_EFFECTS_POPUPS   
    if( iExtension )
        {   
	    iExtension->iSleepDialogExitBeginCalled = EFalse;
	    }
#endif
    CancelMediatorCommand(this);	
	}

/**
 * Returns the id of the control in the line with focus.
 */
EXPORT_C TInt CEikDialog::IdOfFocusControl() const
	{
	return iPageSelector->FocusedLineId();
	}

/**
 * Recalculates the minimum sizes of the lines on the active page.
 */
EXPORT_C void CEikDialog::ResetLineMinimumSizes()
	{
	iPageSelector->ResetLineMinimumSizes(); // !! what about MP dialogs?
	}

/**
 * Constructs the dialog from resources using the resource reader aReader.
 */
EXPORT_C void CEikDialog::ConstructFromResourceL(TResourceReader& aReader)
    {
    iDialogFlags |=aReader.ReadInt32();
            
#ifdef RD_SCALABLE_UI_V2            
    if ( AknLayoutUtils::PenEnabled() )
    {
    	if ( iDialogFlags & EEikDialogFlagVirtualInput )
	    	{
	    	Extension()->iPublicFlags.Set( CEikDialogExtension::EUseVirtualInput );
	    	}
    }
#endif

	CreateTitleBarL();
	iTitleBar->ConstructFromResourceL(aReader);
	TInt PageSelectorResourceId=aReader.ReadInt32();
	TInt ButtonGroupContainerResourceId=aReader.ReadInt32();
	CreateButtonGroupContainerL(ButtonGroupContainerResourceId);
	CreatePageSelectorL(PageSelectorResourceId);
	if (!iPageSelector)
		{
		CreatePageSelectorL();
		iPageSelector->AddPageL(0,KNullDesC,aReader);
		if (iDialogFlags&EEikDialogFlagDensePacking)
			iPageSelector->SetAllPagesDensePacked(ETrue);
		}
	else
		ASSERT(aReader.ReadInt16()==0);
	
	SetBorderStyle();  // Moved to the end of construction to allow access to individual lines.
	}

void CEikDialog::SetBorderStyle()
	{
	if (!((iDialogFlags&EEikDialogFlagFillAppClientRect) || 
		  (iDialogFlags&EEikDialogFlagFillScreen) ))
		{
		// One additional check...   (if NoBorder requested then no action to default to no border (see constructor))
		if ( !( iDialogFlags & EEikDialogFlagNoBorder ) )
			iBorder=TGulBorder(BorderStyle()); // AKNLAF TGulBorder::EThickDeepRaisedWithOutline
		// SERIES60 specific request:  If no border and no shadow then position the controls without spacing.
		if ( (iDialogFlags & EEikDialogFlagNoBorder) && (iDialogFlags & EEikDialogFlagNoShadow) )
			{
			}
		}
	}

void CEikDialog::CreatePageSelectorL()
	{
	iPageSelector=CEikDialogPageSelector::NewL(*this,this);
	iPageSelector->SetObserver(this);
	RegisterDialgWithPageSelector(); // Added JIn
	}

void CEikDialog::CreatePageSelectorL(TInt aResourceId)
	{
	if (aResourceId)
		{
		TResourceReader reader;
		iCoeEnv->CreateResourceReaderLC(reader,aResourceId);
		iPageSelector=CEikDialogPageSelector::NewL(*this,reader,this);
		iPageSelector->SetObserver(this);
		CleanupStack::PopAndDestroy();
		if (iDialogFlags&EEikDialogFlagDensePacking)
			iPageSelector->SetAllPagesDensePacked(ETrue);
		RegisterDialgWithPageSelector(); // Added JIn
		}
	}

void CEikDialog::CreateButtonGroupContainerL(TInt aResourceId)
	{
	// Avkon simplification: Always use CBA; always set buttons 
    // Flags:      
    // buttons are keen on drawing even if not actually visible yet,
	// don't activate them in case of sleeping dialog 
    // yet so extra drawings are suppressed until dialog is really
	// roused to screen
    
    TUint flags = ( iDialogFlags & EEikDialogFlagSleeping ) ?
                    ( CEikButtonGroupContainer::EAddToStack |
                    CEikButtonGroupContainer::EDelayActivation ) :
                    CEikButtonGroupContainer::EAddToStack;
    
    // Softkeys are embedded if dialog doesn't fill application client
    // rect/whole screen and dialog is not Query Input.
    // Shortly: softkeys are embedded only to "normal" dialogs
    TBool isEmbedded = CbaEmbeddedInDialog( iDialogFlags );
    if ( isEmbedded )
        {
        flags |= CEikButtonGroupContainer::EIsEmbedded;
        flags |= CEikButtonGroupContainer::EDelayActivation;
        }
        
    iButtonGroupContainer = CEikButtonGroupContainer::NewL(
            CEikButtonGroupContainer::ECba,
            CEikButtonGroupContainer::EHorizontal,
            iButtonCommandObserver, aResourceId, *this, flags );

    EnableContentObserver( ETrue );
	
	AknGlobalPopupPriorityController::AddSubPopupL(*this, *iButtonGroupContainer->ButtonGroup()->AsControl());
	AknGlobalPopupPriorityController::AddPopupToControlStackL(*iButtonGroupContainer->ButtonGroup()->AsControl(), ECoeStackPriorityCba, ECoeStackFlagRefusesFocus);
	}

void CEikDialog::CreateTitleBarL()
	{
	iTitleBar=new(ELeave) CEikMover;
	iTitleBar->SetContainerWindowL(*this);
    }

/**
 * Initializes the dialog's controls before the dialog is sized and layed out. Empty by default.
 */
EXPORT_C void CEikDialog::PreLayoutDynInitL()
    {
    }

/**
 * Initializes the dialog's controls after the dialog has been sized but before it has been activated.
 * Empty by default.
 */
EXPORT_C void CEikDialog::PostLayoutDynInitL()
    {
    }

/**
 * Sets the size and position of the dialog given the size hint aSize.
 *
 * The parameter is ignored if the FlagFillAppClientRect is set.
 * Otherwise it it centred and given the size asked for
 */
EXPORT_C void CEikDialog::SetSizeAndPosition(const TSize& aSize)
    {
	if (iDialogFlags&EEikDialogFlagFillAppClientRect)
	    {
        // if this is a view app then ask client rect from the currently active view
        TVwsViewId uid;    
        if ( iAvkonAppUi->GetActiveViewId( uid ) == KErrNone )
            {
            if ( uid.iAppUid != uid.iViewUid )
                {
                CAknView* view = iAvkonViewAppUi->View(uid.iViewUid);
                if (view)
                    {
                    SetRect(view->ClientRect());
                    }
                else
                    {
                    SetRect(iEikonEnv->EikAppUi()->ClientRect());
                    }
                }
            else
                {
                SetRect(iEikonEnv->EikAppUi()->ClientRect());
                }
            }
         else
            {
            SetRect( iEikonEnv->EikAppUi()->ClientRect() );
            }
	    }
	else
        {
        SetRect( TRect( AknPopupUtils::Position( aSize, this ), aSize ) );
        }
    }

/**
 * Returns the border style for this dialog.
 */
EXPORT_C TInt CEikDialog::BorderStyle()
	{
#ifndef RD_NO_DIALOG_BORDERS
	return AknBorderId::EAknBorderNotePopup;
#else
    return TGulBorder::ENone;
#endif
	}

/**
 * Returns the minimum size of the area that the contents of the dialog should occupy.
 */
EXPORT_C TSize CEikDialog::MinimumSize()
    {
	if (iDialogFlags&EEikDialogFlagFillScreen)
        {
        TAknWindowLineLayout windowLineLayoutScreen = AknLayoutScalable_Avkon::Screen().LayoutLine();
        TRect rectZero = TRect(0,0,0,0);
        TAknLayoutRect layoutRect;
        layoutRect.LayoutRect( rectZero, windowLineLayoutScreen );
        TRect rectScreen( layoutRect.Rect() );

		return rectScreen.Size();
        }
	else if (iDialogFlags&EEikDialogFlagFillAppClientRect)
        {
        // if this is a view app then ask client rect from the currently active view
        TVwsViewId uid;    
        if ( iAvkonAppUi->GetActiveViewId( uid ) == KErrNone )
            {
            if ( uid.iAppUid != uid.iViewUid )
                {
                CAknView* view = iAvkonViewAppUi->View(uid.iViewUid);
                if (view)
                    {
                    SetRect(view->ClientRect());
                    }
                else
                    {
                    SetRect(iEikonEnv->EikAppUi()->ClientRect());
                    }
                }
            else
                {
                SetRect(iEikonEnv->EikAppUi()->ClientRect());
                }
            }
        else
            {
            SetRect( iEikonEnv->EikAppUi()->ClientRect() );
            }
        }

	TSize pageSelectorSize(iPageSelector->MinimumSize());

	return pageSelectorSize;
    }

/**
 * Returns the preferred size of the dialog given that it must fit in a maximum size of aMaxSize.
 * 
 * @since ER5U
 */
EXPORT_C TSize CEikDialog::PreferredSize(const TSize& aMaxSize) const
	{
	if (iDialogFlags&EEikDialogFlagFillScreen)
		return iEikonEnv->ScreenDevice()->SizeInPixels();
	else if (iDialogFlags&EEikDialogFlagFillAppClientRect)
	
	    {
        // if this is a view app then ask client rect from the currently active view
        TVwsViewId uid;    
        if ( iAvkonAppUi->GetActiveViewId( uid ) == KErrNone )
            {
            if ( uid.iAppUid != uid.iViewUid )
                {
                CAknView* view = iAvkonViewAppUi->View(uid.iViewUid);
                if (view)
                    {
                    return view->ClientRect().Size();
                    }
                else
                    {
                    return iEikonEnv->EikAppUi()->ClientRect().Size();
                    }
                }
            else
                {
                return iEikonEnv->EikAppUi()->ClientRect().Size();
                }
            }
        else
            {
            return iEikonEnv->EikAppUi()->ClientRect().Size();
            }
	    }
		

	// Calculate max size available to page selector, taking into account the border.
	TSize maxSize(aMaxSize);

	// Take off border
	maxSize-=iBorder.SizeDelta();

	const TSize pageSelectorSize(iPageSelector->PreferredSize(maxSize));

	TSize preferredSize(0,0);
	// Don't allow pageSelector to expand width
	preferredSize.iWidth=Min(pageSelectorSize.iWidth,maxSize.iWidth);
	// Take its height
	preferredSize.iHeight=pageSelectorSize.iHeight;

	// Add border back on
	preferredSize+=iBorder.SizeDelta();
	
    if ( CbaEmbeddedInDialog( iDialogFlags) )
        {
        // If dialog doesn't fill application client rect/whole screen,
        // dialog is not Query Input and soft keys have some text,
        // preferred dialog size is extended so that softkey buttons
        // can be added on bottom of the dialog rect
        
        // Preferred size is passed to all dialogs in call to function
        // SetSizeAndPosition( const TSize& aSize ).
        // It should be used in all derived dialogs. 
        
        CEikCba* cba = static_cast<CEikCba*>(
                iButtonGroupContainer->ButtonGroup() );
        
        if ( cba->IsVisible() && !cba->IsEmpty() )
            {
            TRect screen;
                AknLayoutUtils::LayoutMetricsRect( 
                    AknLayoutUtils::EScreen, screen );
        
            TAknLayoutRect cbaRect;
                cbaRect.LayoutRect( screen, 
                AknLayoutScalable_Avkon::popup_sk_window( 0 ).LayoutLine() );
            
            preferredSize += TSize( 0, cbaRect.Rect().Height() );
            }
        }
        
	return preferredSize;
	}

/**
 * Lays out the dialog's components when the size of the dialog is changed.
 * Position of DpSel is always at (0,0) relative to dialog.
 * For Avkon, the DPSEL always stays the same size as the CEikDialog minus an optional title 
 * bar. 
 */
EXPORT_C void CEikDialog::SizeChanged()
    {
	__ASSERT_DEBUG( iButtonGroupContainer->Location() == CEikButtonGroupContainer::EExternal, 
		Panic( EEikDialogPanicIllegalOption ) );

	TInt excludeCbaHeight = -1;

	if (iButtonGroupContainer)
        {
        TAknWindowLineLayout windowLineLayoutScreen = AknLayoutScalable_Avkon::Screen().LayoutLine();
        TRect rectZero = TRect(0,0,0,0);
        TAknLayoutRect layoutRect;
        layoutRect.LayoutRect( rectZero, windowLineLayoutScreen );
        TRect rectScreen( layoutRect.Rect() );

        iButtonGroupContainer->SetBoundingRect(rectScreen);

		if ( iExtension && iExtension->LayoutCategory() == CEikDialogExtension::EPopupLayout )
			{
			CCoeControl* cba = iButtonGroupContainer->ButtonGroup()->AsControl();
			static_cast<CEikCba*>(cba)->SetSkinBackgroundId( KAknsIIDQsnBgAreaControlPopup );
			}

        if ( CbaEmbeddedInDialog( iDialogFlags ) )
            {
            CEikCba* cba = static_cast<CEikCba*>(
                    iButtonGroupContainer->ButtonGroup() );
            
            // If dialog doesn't fill application client rect/whole screen,
            // dialog is not Query Input and soft keys have some text,
            // softkeys are located on bottom of the dialog rect
      
            if ( cba->IsVisible() && !cba->IsEmpty() )
                {
                TRect screen;
                    AknLayoutUtils::LayoutMetricsRect( 
                        AknLayoutUtils::EScreen, screen );
        
                TAknLayoutRect cbaRect;
                    cbaRect.LayoutRect( screen, 
                    AknLayoutScalable_Avkon::popup_sk_window( 
                        0 ).LayoutLine() );
                
                TRect rect( Rect() );
                cba->SetRect( TRect(
                    rect.iTl.iX ,
                    rect.iBr.iY  - cbaRect.Rect().Height(),
                    rect.iBr.iX ,
                    rect.iBr.iY ) );

                excludeCbaHeight = cbaRect.Rect().Height();
                }
            else
                {
                // Otherway softkeys are located out of dialog rect
                cba->SetRect( TRect(0, 0, 0, 0 ) );
                }
            }
		}
	if (iTitleBar)
		{
		TRect nullRect(0,0,0,0);
		iTitleBar->SetRect( nullRect );
		}

    // This calculation left in even though border should be ENone
	TRect rect ( iBorder.InnerRect( Rect() ) );

	if ( excludeCbaHeight != -1 )
	    {
	    rect.iBr.iY = Min( rect.iBr.iY, Rect().iBr.iY - excludeCbaHeight );
	    }

	TInt activePageNum = ActivePageId();
	CEikDialogPage* currentPage = NULL ;
	if ( activePageNum >= 0 ) 
		{ // prevent unnecessary resizing of form components
		currentPage = iPageSelector->PageContainer()->Page( activePageNum ) ;
		currentPage->SetFormFlag( CEikDialogPage::EFormResizeOptimisationFlag, ETrue ) ;
		}
	iPageSelector->SetRect(rect);

	if ( activePageNum >= 0 ) // disable optimisation flag
		currentPage->SetFormFlag( CEikDialogPage::EFormResizeOptimisationFlag,  EFalse ) ;

	// <SKIN>
	iExtension->iBgContext->SetParentPos( PositionRelativeToScreen() ) ;
	iExtension->iBgContext->SetRect( Rect() ) ;
	}

/**
 * Sets the title text for the dialog to aText.
 */
EXPORT_C void CEikDialog::SetTitleL(const TDesC& aText )
    {
	iTitleBar->SetTextL(aText);
    }

/**
 * Sets the title text for the dialog by reading it from the resource with id aResourceId.
 */
EXPORT_C void CEikDialog::SetTitleL(TInt aResourceId )
    {
	HBufC* tmpBuf=iCoeEnv->AllocReadResourceLC(aResourceId);
	SetTitleL(tmpBuf->Des());
	CleanupStack::PopAndDestroy(); // tmpBuf
    }

/**
 * Dims and inactivates the dialog line containing the control identified by aControlId if
 * aDimmed is ETrue. Does not cause a redraw.
 */
EXPORT_C void CEikDialog::SetLineDimmedNow(TInt aControlId,TBool aDimmed)
    {
    CEikCaptionedControl* line=Line(aControlId);
	CCoeControl* control=line->iControl;
	if (control->IsDimmed()==aDimmed)
		return;
	control->SetDimmed(aDimmed);
    line->CheckDimmedDisplayState();
    control->DrawNow();
    }

/**
 * Sets the dialog line containing the control identified by aControlId to a non-focusing state
 * so that it will never be given keyboard focus.
 */
EXPORT_C void CEikDialog::SetLineNonFocusing(TInt aControlId)
	{
    CEikCaptionedControl* line=Line(aControlId);
	line->SetNonFocusing();
	line->iControl->SetNonFocusing();
	}

/**
 * Makes the dialog line containing the control identified by aControlId visible, i.e. sets it
 * to draw itself, if aVisible is ETrue.
 */
EXPORT_C void CEikDialog::MakeLineVisible(TInt aControlId,TBool aVisible)
    {
    CEikCaptionedControl* line=Line(aControlId);
	CCoeControl* control=line->iControl;
	if (control->IsVisible()==aVisible)
		return;
    control->MakeVisible(aVisible);
    line->CheckDimmedDisplayState();
    }

/**
 * Makes the whole dialog line containing the control identified by aControlId visible, i.e. sets it
 * to draw itself, if aVisible is ETrue.
 */
EXPORT_C void CEikDialog::MakeWholeLineVisible(TInt aControlId,TBool aVisible)
    {
    CEikCaptionedControl* line=Line(aControlId);
	if (line->IsVisible()==aVisible)
		return;
	CCoeControl* control=line->iControl;
    if (line->iCaption)
		line->iCaption->MakeVisible(aVisible);
	if (line->iTrailer)
		line->iTrailer->MakeVisible(aVisible);
    control->MakeVisible(aVisible);
	line->MakeVisible(aVisible);
    }

/**
 * Lays out the dialog, setting it to take its preferred size and position
 * for the screen.
 *
 * TODO (RSD) I have noticed this routine and I suspect that it is responsible for one of
 * the sizechanged cascades in Form.  This should use best current information to layout
 * the dialog, but I have not investigated too much
 * 
 * @since ER5U
 */
EXPORT_C void CEikDialog::Layout()
	{
    TAknWindowLineLayout windowLineLayoutScreen = AknLayoutScalable_Avkon::Screen().LayoutLine();
    TRect rectZero = TRect(0,0,0,0);
    TAknLayoutRect layoutRect;
    layoutRect.LayoutRect( rectZero, windowLineLayoutScreen );
    TRect rectScreen( layoutRect.Rect() );

	TSize maxSize = rectScreen.Size();

	SetSizeAndPosition(PreferredSize( maxSize ));
	}

/**
 * Deletes the dialog line with the control identified by aControlId.
 */
EXPORT_C void CEikDialog::DeleteLine(TInt aControlId, TBool aRedraw)
	{
	iPageSelector->DeleteLine(aControlId, aRedraw);
	}

/**
 * Inserts a line in the dialog on the page identified by aPageId at the line index aIndex
 * and constructed from the resource specified by aResourceId.
 */
EXPORT_C void CEikDialog::InsertLineL(TInt aIndex,TInt aResourceId,TInt aPageId)
	{
	iPageSelector->InsertLineL(aIndex,aPageId,aResourceId);
	}

/**
 * Sets the page identified by aPageId to be densely packed if aDensePacking is ETrue.
 * The spacing between the dialog's lines is then reduced.
 * TODO (RSD) This seems to be rather un-avkonlike.  Perhaps should be stubbed out.
 */
EXPORT_C void CEikDialog::SetPageDensePacking(TInt aPageId,TBool aDensePacking)
	{
	iPageSelector->SetPageDensePacked(aPageId,aDensePacking);
	}

/**
 * Dynamically constructs a dialog with flags aFlags, buttons constructed from
 * the resource aButtonsId, and with a single activated empty page with id 0. The
 * dialog is therefore ready to dynamically add lines to.
 */
EXPORT_C void CEikDialog::ConstructAutoDialogLC(TInt aFlags,TInt aButtonsId)
	{
    CleanupStack::PushL(this);
	BaseConstructL();
	iDialogFlags=aFlags;
	CreateTitleBarL();
	CreateButtonGroupContainerL(aButtonsId);
	CreatePageSelectorL();
	iPageSelector->AddPageL(0,KNullDesC);
	SetBorderStyle();  // Moved to the end of construction to allow access to individual lines.
	}

/**
 * @deprecated
 */
EXPORT_C void CEikDialog::DeclareItemAuto(TInt aControlId,TInt aControlType,TAny* aReturnValue)
	{
	CEikCaptionedControl* line=Line(aControlId);
	if (line->iControlType!=aControlType)
		Panic(EEikDialogPanicWrongAutoType);
	line->iReturnValue=aReturnValue;
	}

/**
 * Creates a control line in the dialog.on the active page with caption text aCaption.
 * The line can thereafter be accessed through the identifier aControlId.
 * A control of type aControlType is created by the Eikon control factory
 * and the return value of the line set to aReturnValue.
 * If the value of aControlType is not known to the Eikon control factory then
 * the construction of the control must be handled by CreateCustomControlL.
 */
EXPORT_C CCoeControl* CEikDialog::CreateLineByTypeL(const TDesC& aCaption,TInt aControlId,TInt aControlType,TAny* aReturnValue)
	{
	return iPageSelector->CreateLineByTypeL(aCaption,aControlId,aControlType,aReturnValue);
	}

/**
 * Overloaded member which creates a control line in the dialog on the page specified by aPageId.
 *
 * @since ER5U
 */
EXPORT_C CCoeControl* CEikDialog::CreateLineByTypeL(const TDesC& aCaption,TInt aPageId,TInt aControlId,TInt aControlType,TAny* aReturnValue)
	{
	return iPageSelector->CreateLineByTypeL(aCaption,aPageId,aControlId,aControlType,aReturnValue);
	}

/**
 * Creates a custom control of type aControlType. Returns the control information for the custom control
 * which is created. Called when creating a line on the dialog page if the Eikon control factory does not
 * recognise the type aControlType.
 *
 * This method panics by default. It must be reimplemented if it is to be called.
 *
 * The parent of a custom control should be the line which contains it - not the dialog itself -
 * but the line is not accessible at this stage. If necessary, the line should be set as the parent in
 * PreLayoutDynInitL
 */
EXPORT_C SEikControlInfo CEikDialog::CreateCustomControlL(TInt /*aControlType*/)
	{
	Panic(EEikDialogPanicNoSuchControl);
	return SEikControlInfo();
	}

EXPORT_C MEikDialogPageObserver::TFormControlTypes CEikDialog::ConvertCustomControlTypeToBaseControlType(TInt /*aControlType*/) const
	{
/** 
 * For Forms only:
 * This should be overrridden with mappings between the base control types that 
 * form knows how to layout (described in eikdpobs.h)
 */
	return MEikDialogPageObserver::EUnknownType;
	}
/**
 * Sets the caption of the control identified by aControlId to the descriptor aText.
 */
EXPORT_C void CEikDialog::SetControlCaptionL(TInt aControlId,const TDesC& aText)
	{
	CEikCaptionedControl* line=Line(aControlId);
	if (line)
		{
		line->SetCaptionL(aText);
		line->DrawNow();
		}
	}

/**
 * Sets the caption of the control identified by aControlId by reading the caption
 * text from the resource specified by aResourceId.
 */
EXPORT_C void CEikDialog::SetControlCaptionL(TInt aControlId,TInt aResourceId)
	{
	HBufC* captionBuf=iCoeEnv->AllocReadResourceLC(aResourceId);
	SetControlCaptionL(aControlId,captionBuf->Des());
	CleanupStack::PopAndDestroy();
	}

/**
 * Returns a pointer to the caption of the control identified by aControlId.
 * Does not imply transfer of ownership.
 */
EXPORT_C CEikLabel* CEikDialog::ControlCaption(TInt aControlId) const
	{
	return iPageSelector->Line(aControlId)->iCaption;
	}

/**
 * Returns a pointer to the first control found to be identified by aControlId.
 * Panics if the control id is invalid. Does not imply transfer of ownership.
 */
EXPORT_C CCoeControl* CEikDialog::Control(TInt aControlId) const
	{
	CEikCaptionedControl* line=iPageSelector->Line(aControlId);
	CCoeControl* control=line->iControl;
	ASSERT(control);
	return control;
	}

/**
 * Returns a pointer to the control identified by aControlId or NULL
 * if the control id is invalid. Does not imply transfer of ownership.
 */
EXPORT_C CCoeControl* CEikDialog::ControlOrNull(TInt aControlId) const
	{
	if (!iPageSelector)
		return NULL;
	CEikCaptionedControl* line=iPageSelector->LineOrNull(aControlId);
	if (line)
		return line->iControl;

	return NULL;
	}

/**
 * Returns a reference to the button group container supplying the command
 * buttons for the dialog.
 *
 * @since ER5U
 */
EXPORT_C CEikButtonGroupContainer& CEikDialog::ButtonGroupContainer() const
	{
	ASSERT(iButtonGroupContainer);
	return *iButtonGroupContainer;
	}

/**
 * Swaps the the button group container with a new container aContainer. The dialog takes ownership
 * of the new container. Returns a pointer to the old button group container and transfers ownership.
 *
 * @since ER5U
 */
EXPORT_C CEikButtonGroupContainer* CEikDialog::SwapButtonGroupContainer(CEikButtonGroupContainer* aContainer)
	{
	ASSERT(iButtonGroupContainer);
	ASSERT(aContainer);

	CEikButtonGroupContainer* oldContainer=iButtonGroupContainer;
	iButtonGroupContainer=aContainer;
	return oldContainer;
	}

/**
 * Returns a reference to the dialog title bar. 
 *
 * @since ER5U
 */
EXPORT_C CEikMover& CEikDialog::Title() const
	{
	return *iTitleBar;
	}

/**
 * Returns the id of the dialog's active page.
 *
 * @since ER5U
 */
EXPORT_C TInt CEikDialog::ActivePageId() const
	{
	return iPageSelector->ActivePageId();
	}

/**
 * Activates the first page on the dialog. At least one page must be activated
 * before the dialog can be used.
 *
 * @since ER5U
 */
EXPORT_C void CEikDialog::ActivateFirstPageL() const
	{
	iPageSelector->ActivateFirstPageL();
	}


/**
 * Sets the Editable state.  This exists to support forms
 *
 * @since ER5U
 */
EXPORT_C void CEikDialog::SetEditableL( TBool aEditable ) 
    {
    if ( !iExtension->iFlags[CEikDialogExtension::EEditableStateInitialised] ||
         iIsEditable != aEditable )
        {
        iExtension->iFlags.Set(CEikDialogExtension::EEditableStateInitialised);
        iIsEditable = aEditable ;
        // tell each of the pages on the dialog about the editable state...
        iPageSelector->SetEditableL( aEditable );
        DrawNow();
        }
    }

/**
 * Returns the Editable state.  This exists to support forms
 *
 * @since ER5U
 */	
EXPORT_C TBool CEikDialog::IsEditable() const 
	{
	return ( iIsEditable ) ;
	}

/**
 * Returns the line index of the control aControl or KErrNotFound if the control
 * is not on the active page.
 */
EXPORT_C TInt CEikDialog::FindLineIndex(const CCoeControl& aControl) const
	{
	return iPageSelector->FindLineIndex(aControl);
	}

/**
 * Returns a pointer to the line containing the control identified by aControlId.
 * Does not imply transfer of ownership.
 */
EXPORT_C CEikCaptionedControl* CEikDialog::Line(TInt aControlId) const
	{
	return iPageSelector->Line(aControlId);
	}

/**
 * Returns a pointer to the current line.
 * Does not imply transfer of ownership.
 */
EXPORT_C CEikCaptionedControl* CEikDialog::CurrentLine() const
	{
	return iPageSelector->CurrentLine();
	}

/**
 * Rotates the focus by aDelta steps. Each line is a step, as are dialog tabs..
 */
EXPORT_C TBool CEikDialog::RotateFocusByL(TInt aDelta)
	{
	return iPageSelector->RotateFocusByL(aDelta);
	}

/**
 * Returns the index of the dialog's active page. Pages are indexed from 0 in the
 * order that they are added.
 *
 * @since ER5U
 */
EXPORT_C TInt CEikDialog::ActivePageIndex() const
	{
	return iPageSelector->ActivePageIndex();
	}

/**
 * Runs the dialog and returns the id of the button used to dismiss it.
 * The dialog is destroyed on exit.
 */
EXPORT_C TInt CEikDialog::RunLD()
	{
    // Moved BringForwards in the beginning to enable 1-frame animations.
	iEikonEnv->BringForwards(ETrue); // before call to EnableBackup()
	AknGlobalPopupPriorityController::ShowPopup(*this, ETrue);
	iDialogFlags|=EEikDialogFlagBroughtForward;

    // This makes sure that forms, ie. dialogs that fill up the whole
    // application rect, and therefore look like views,
    // not have popup transition effects.
    if ( iDialogFlags & EEikDialogFlagFillAppClientRect ||
         iDialogFlags & EEikDialogFlagFillScreen ||
         (AknLayoutUtils::PenEnabled() && ( iDialogFlags & EEikDialogFlagVirtualInput ) )
         )
        {
        GfxTransEffect::Deregister( this );
        }

	// Need to fade here or background will not be faded during transition
	if(GfxTransEffect::IsRegistered(this) && IsVisible())
	    {
	    CAknTransitionUtils::SetData(EDontAnimateBitmaps, (TAny*)this);
		}

	DynamicConstructL();
	if (!(iDialogFlags&EEikDialogFlagModeless))
		{
        if ( !(iDialogFlags&EEikDialogFlagFillAppClientRect) )
            {
            // Modal partial screen dialogs (like queries) capture pointer events.
            SetGloballyCapturing( ETrue );
            SetPointerCapture(ETrue);		    
            }
		SetFocus(EFalse);
		AknGlobalPopupPriorityController::AddPopupToControlStackL(*this, ECoeStackPriorityDialog);
		}

	if (~iDialogFlags&EEikDialogFlagNoBackup)
	    {
		DrawableWindow()->EnableBackup();
	    }

    TBool wgFocused = IsFocusedWindowGroup( this );
    if ( !GfxTransEffect::IsRegistered( this ) || !IsVisible() || !wgFocused )
		{
		// Call this when there won't be any effect in order to work exactly
		// like it would if there were no transition effects
	FadeBehindPopup(ETrue);
		}
	
    // Get the foreground information _before_ calling ActivateL because something
    // unwanted could be flushed to the screen (IsForeground causes a window server
    // flush)
    CAknAppUi* aknAppUi = static_cast<CAknAppUi*>( CEikonEnv::Static()->EikAppUi() );
    TBool threadIsFg = aknAppUi->IsForeground();
        		
    iExtension->iInitialMade = ETrue;
    iPageSelector->ActivateFirstPageL();           
    ActivateL();

    if ( iButtonGroupContainer && CbaEmbeddedInDialog( iDialogFlags ) )
        {
        iButtonGroupContainer->ActivateL();
        }

    SetInitialCurrentLine();
    iExtension->iInitialMade = EFalse;

    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
	    
	TInt slidingMode = AknsDrawUtils::SlidingMode(skin);

	if ( (iExtension && iExtension->LayoutCategory() == CEikDialogExtension::EPopupLayout) &&
	     (slidingMode != ESlidingDisabled) &&
	     IsVisible() )
	    {
        SlideDialog();
	    }
	    	
	IssueMediatorCommand(this);
	
    CleanupStack::Pop();

    if ( GfxTransEffect::IsRegistered( this ) && IsVisible() && wgFocused &&
	    Size().iWidth > 0 && Size().iHeight > 0 && threadIsFg && !IsBlankScreenDisplayed())
		{
		MakeVisible(EFalse); //make sure it is invisible when calling begin
        CAknTransitionUtils::MakeVisibleSubComponents( this,
                                    CAknTransitionUtils::EAppearInvisible );

        InvalidateWindows( this );
		
		CAknTransitionUtils::SetAllParents(this);
#ifdef RD_UI_TRANSITION_EFFECTS_POPUPS
		GfxTransEffect::NotifyExternalState(EInternalHandleSequence, (const TDesC8*)this);
#endif
		GfxTransEffect::Begin(this, KGfxControlAppearAction);
		GfxTransEffect::NotifyExternalState(ECaptureComponentsBegin, (const TDesC8*)this);
		
		TRect demarcation;
		CAknTransitionUtils::GetDemarcation(CAknTransitionUtils::EPopup, demarcation);
		GfxTransEffect::SetDemarcation(this, demarcation);

		MakeVisible(ETrue);
        CAknTransitionUtils::MakeVisibleSubComponents( this,
                                        CAknTransitionUtils::EAppearVisible );

		GfxTransEffect::NotifyExternalState(ECaptureComponentsEnd, (const TDesC8*)this);
		GfxTransEffect::End(this);
		}
	else
		{
		FadeBehindPopup(ETrue);
		}
		
    if( GfxTransEffect::IsRegistered( this ) && IsVisible() ) 
        { 
        CAknTransitionUtils::RemoveData(EDontAnimateBitmaps);   
        }
        
	// Claim pointer grab and send the pointer up event to the
	// control that otherwise would be receiving the drag events.
	Window().ClaimPointerGrab(ETrue);
	
    return(WaitAsRequired());
	}


EXPORT_C void CEikDialog::Draw(const TRect& /*aRect*/) const
    {
    TRect rect=Rect();
    CWindowGc& gc=SystemGc(); //No reason to demote the gc, CWindowGc is more usable.

    if ( iExtension->LayoutCategory() == CEikDialogExtension::EPopupLayout )
        {
        MAknsSkinInstance* skin = AknsUtils::SkinInstance();

        TRect windowRect = Rect();
    
        TAknLayoutRect topLeft;
        topLeft.LayoutRect(windowRect, SkinLayout::Popup_windows_skin_placing__frame_general__Line_2());

        TAknLayoutRect bottomRight;
    	bottomRight.LayoutRect(windowRect, SkinLayout::Popup_windows_skin_placing__frame_general__Line_5());

        TRect outerRect = TRect(topLeft.Rect().iTl, bottomRight.Rect().iBr);
        TRect innerRect = TRect(topLeft.Rect().iBr, bottomRight.Rect().iTl);

        CFbsBitmap* cbaExtension = 0;
        cbaExtension = AknsUtils::GetCachedBitmap( skin, KAknsIIDQsnBgSlicePopup );


        if ( cbaExtension ) 
            {
            TAknWindowLineLayout lineLayoutPopupBgSlice = SkinLayout::Popup_windows_skin_placing__background_slice__Line_2();
            TAknLayoutRect layoutRect;
            layoutRect.LayoutRect( windowRect, lineLayoutPopupBgSlice );
            TRect rectPopupBgSlice( layoutRect.Rect() );

            AknIconUtils::SetSize( cbaExtension, TSize( rectPopupBgSlice.Width(), rectPopupBgSlice.Height() ) ); 

            gc.BitBlt(TPoint(rect.iTl.iX, rect.iBr.iY - cbaExtension->SizeInPixels().iHeight), cbaExtension);
            }

        if ( CAknEnv::Static()->TransparencyEnabled() )
            {
            TRect rect( outerRect ); 
            TRegionFix<16> drawFrameClipReg;
            TBool drawFrame = EFalse;
            
            // Add CBA area to drawing region
            if ( iButtonGroupContainer && CbaEmbeddedInDialog( iDialogFlags ) )
                {
                CEikCba* cba = static_cast<CEikCba*>( 
                    iButtonGroupContainer->ButtonGroup() );
                
                if ( cba )
                    {
                    drawFrame = ETrue;
            
                    drawFrameClipReg.AddRect( 
                        TRect( cba->Position(), cba->Rect().Size() ) );
                        
                    rect.iBr.iY = Min( rect.iBr.iY, 
                        Rect().iBr.iY - cba->Rect().Height() );
                    }
                }

            // Add area outside page selector area to drawing region. 
            if ( iPageSelector && rect != iPageSelector->Rect() )
                {
                drawFrame = ETrue;
                drawFrameClipReg.AddRect( rect );

                if ( iExtension->iPublicFlags[ CEikDialogExtension::EClipChildControlRect ] )
                    {                    
                    drawFrameClipReg.SubRect( iPageSelector->Rect() );
                    }
                }
            
            // Draw background
            if ( drawFrame )
                {
                gc.SetClippingRegion( drawFrameClipReg );
                
                AknsDrawUtils::DrawFrame( skin, gc, outerRect, innerRect,
                    KAknsIIDQsnFrPopup,KAknsIIDQsnFrPopupCenter);
                        
                gc.CancelClippingRegion();
                }
            }
        else
            {
            AknsDrawUtils::DrawFrame( skin, gc, outerRect, innerRect,
                KAknsIIDQsnFrPopup,KAknsIIDQsnFrPopupCenter);
            }    
        }
    }
    
EXPORT_C void CEikDialog::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CEikBorderedControl::HandlePointerEventL(aPointerEvent); 
    }    

EXPORT_C void* CEikDialog::ExtensionInterface( TUid /*aInterface*/ )
    {
    return NULL;
    }   

TKeyResponse CEikDialog::TryAnimateButtonAndExitL(TInt aKeycode)
	{
	TInt buttonId=EEikBidCancel;
	switch (aKeycode)
		{
	case EKeyEnter:
	case EKeyOK:
		buttonId=EEikBidOk;
		break;
	case EKeySpace:
		buttonId=EEikBidSpace;
		break;
	case EKeyTab:
		buttonId=EEikBidTab;
		break;
	case EKeyBackspace:
		buttonId=EEikBidDelete;
		break;
		}

	CEikButtonGroupContainer& buttonGroupContainer = ButtonGroupContainer();
	CCoeControl* button = buttonGroupContainer.ControlOrNull(buttonId);

	if (button)
		{
		if (button->IsDimmed() || !button->IsVisible())
			return EKeyWasNotConsumed;
		buttonGroupContainer.AnimateCommand(buttonId);
		}

	if (button || buttonId==EEikBidCancel || buttonId==EEikBidOk)
		{
		TryExitL(buttonId);
		return EKeyWasConsumed;
		}

	return EKeyWasNotConsumed;
	}

/**
 * Prepares for a transistion in focus in the dialog. By default, calls the currently
 * focused control to prepare fo loss of focus.
 */
EXPORT_C void CEikDialog::PrepareForFocusTransitionL()
    {
	CEikCaptionedControl* currentLine=CurrentLine();
	if (currentLine)
		currentLine->iControl->PrepareForFocusLossL();
    }

/**
 * Handles the key event aKeyEvent with code aType. Returns EKeyWasConsumed if the control
 * takes action on the key event or EKeyWasNotConsumed otherwise.
 */
EXPORT_C TKeyResponse CEikDialog::OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)
    {


	// Hide the tool tip (if there is one!)
	if ( ( iPageSelector->NumPages() == 1 ) && ( CurrentLine() ) && ( CurrentLine()->ToolTipText( ) ) )
		{
		switch ( aKeyEvent.iScanCode )
			{
			case EStdKeyEscape :
			default :
				break ;
			}
		}
    if (!(iDialogFlags&EEikDialogFlagDontEatUpDownEvents) && aKeyEvent.iScanCode != EStdKeyYes)
	{
	if (aType!=EEventKey)
	    return(EKeyWasConsumed);
	}

	TInt code=aKeyEvent.iCode;
	const TUint modifiers = aKeyEvent.iModifiers;
	TKeyResponse response;

	// Pass the key event to the button group container first (if required)

	if (iDialogFlags&EEikDialogFlagAllKeysToButtons || ((modifiers & EAllStdModifiers) == EModifierCtrl) )
		{
		response = iButtonGroupContainer->OfferKeyEventL(aKeyEvent,aType);
		if(response==EKeyWasConsumed)
			return EKeyWasConsumed;
		}

	//

    switch (code)
        {
    case EKeyEnter:
    case EKeyOK:
	// the next one tries to disable selection_key when
	// left softkey has no command in it.
	if (iButtonGroupContainer && iButtonGroupContainer->ButtonGroup())
	    if (iButtonGroupContainer->ButtonGroup()->CommandId(0) == 0)
		goto KeyToFocus;

		if(iPageSelector->TakesEnterKey()  || (modifiers&EModifierCtrl && !(modifiers&EModifierPureKeycode)) )
			goto KeyToFocus; // else fall through
        break;
    case EKeyEscape:
		if (modifiers&EModifierShift)
			iPageSelector->OfferKeyEventL(aKeyEvent, aType);
// Add to remove repeated keypress return event of OK key
		if (aKeyEvent.iRepeats&&EKeyOK==code)
			return EKeyWasConsumed;
		if ((!(modifiers&EModifierCtrl) || modifiers&EModifierPureKeycode) &&
			!(iDialogFlags&EEikDialogFlagModeless))
			TryAnimateButtonAndExitL(code);
        break;
	case EKeyTab:
		if (aKeyEvent.iModifiers&EModifierCtrl)
			{
			response = iPageSelector->OfferKeyEventL(aKeyEvent, aType);
			if (response==EKeyWasConsumed)
				break;
			}
		// drop through
	case EKeySpace:
	case EKeyBackspace:
		if (TryAnimateButtonAndExitL(code)==EKeyWasConsumed)
			break;
    default:
		iPageSelector->OfferKeyEventL(aKeyEvent, aType);
		break;
	KeyToFocus:
		if(iPageSelector->OfferHotKeysKeyEventL(aKeyEvent,aType)==EKeyWasConsumed)
			return EKeyWasConsumed;

		}

	return (aKeyEvent.iScanCode == EStdKeyYes ? EKeyWasNotConsumed:EKeyWasConsumed);
    }

/**
* Hands focus to current dialog line.
*/
EXPORT_C void CEikDialog::FocusChanged(TDrawNow aDrawNow)
    {
    CEikBorderedControl::FocusChanged( aDrawNow );

    TInt controlID = IdOfFocusControl();
    if (controlID)
        {
        Line(controlID)->SetFocus(IsFocused(), aDrawNow);
        }
    }

/**
 * Tries to initiate user exit of the dialog when the button identified
 * by aButtonId is pressed, if this button should exit the dialog. See OkToExitL to
 * determine which buttons can exit the dialog.
 *
 * This will fail if user exit is prevented by the EEikDialogFlagNoUserExit flag.
 * If the EEikDialogFlagNotifyEsc flag is not set and the dialog has been cancelled it
 * immediately deletes itself. 
 */
EXPORT_C void CEikDialog::TryExitL(TInt aButtonId)
    {
    if ( iDialogFlags & EEikDialogFlagNoUserExit )
        {
		return;
        }
        
    // use delayed exit if pointer event handling is in progress
    if ( Extension()->iPublicFlags.IsSet( CEikDialogExtension::EDelayedExit ) )
        {
        Extension()->iButtonId = aButtonId;
        Extension()->StartDelayedExit();
        return;
        }
        
    TBool effectTriggered = EFalse;
    TBool effectButton = aButtonId == EEikBidCancel
                      || aButtonId == EAknSoftkeyExit
                      || aButtonId == EAknSoftkeyBack
                      || aButtonId == EAknSoftkeyNo;
#ifdef RD_UI_TRANSITION_EFFECTS_POPUPS
    effectButton =    effectButton
					  || aButtonId == EAknSoftkeyClose
                      || aButtonId == EAknSoftkeyDone;
#endif
    CAknAppUi* aknAppUi = static_cast<CAknAppUi*>( iEikonEnv->EikAppUi() );
    if ( GfxTransEffect::IsRegistered( this ) && IsVisible() && effectButton
#ifdef RD_UI_TRANSITION_EFFECTS_POPUPS        
        && !(iDialogFlags&EEikDialogFlagSleeping)
#endif
        && ( !aknAppUi->IsFullScreenApp() || aknAppUi->IsForeground() )
        && !IsBlankScreenDisplayed()
         )
        {
        CAknTransitionUtils::SetAllParents(this);
        GfxTransEffect::Begin(this, KGfxControlDisappearAction);
        GfxTransEffect::NotifyExternalState(ECaptureComponentsBegin, (const TDesC8*)this);

        TRect demarcation;
        CAknTransitionUtils::GetDemarcation(CAknTransitionUtils::EPopup,
                                            demarcation);
        GfxTransEffect::SetDemarcation(this, demarcation);
        effectTriggered = ETrue;
        }

    if (aButtonId!=EEikBidCancel)
        PrepareForFocusTransitionL();
    else if (!(iDialogFlags&EEikDialogFlagNotifyEsc))
		goto finished;
	if (!OkToExitL(aButtonId))
            {
        if ( effectTriggered )
            {
            GfxTransEffect::NotifyExternalState( ECaptureComponentsAbort,
                                                 ( const TDesC8* ) this );
            GfxTransEffect::Abort( this );
            }
   			return;
            }

	if (aButtonId!=EEikBidCancel)
		GetAutoValues();
finished:
    if (iExitConfirmed)
		*iExitConfirmed=((MappedCommandId( aButtonId ) ==EEikBidCancel)? 0: aButtonId);

    // Remove content observer in order to prevent unnecessary layout 
    // calculations in dialog shutdown.
    EnableContentObserver( EFalse );

	if (iDialogFlags&EEikDialogFlagSleeping)
		ExitSleepingDialog();
	else
		{
        // Remove content observer in order to prevent unnecessary layout 
        // calculations in dialog shutdown.
        EnableContentObserver( EFalse );

        if ( effectTriggered )
						{
        		MakeVisible(EFalse);
                CAknTransitionUtils::MakeVisibleSubComponents( this,
                                        CAknTransitionUtils::EForceInvisible );

        		GfxTransEffect::NotifyExternalState(ECaptureComponentsEnd, (const TDesC8*)this);
        		GfxTransEffect::End(this);
        		}
        	else
			    {
        		MakeVisible(EFalse);
                CAknTransitionUtils::MakeVisibleSubComponents( this,
                                        CAknTransitionUtils::EForceInvisible );
        		GfxTransEffect::NotifyExternalState( ECaptureComponentsAbort,
                                                 ( const TDesC8* ) this );
		    	GfxTransEffect::Abort(this);
			}
	    delete(this);
		}
    }

/**
 * Returns the input capabilites of the dialog. By default, the dialog is
 * capable of handling all text input.
 *
 * @since ER5U
 */
EXPORT_C TCoeInputCapabilities CEikDialog::InputCapabilities() const
	{
	return TCoeInputCapabilities(TCoeInputCapabilities::ENavigation);
	}

void CEikDialog::GetAutoValues()
	{
	iPageSelector->GetAutoValues();
	}

/**
 * Tries to change focus to the line identified by aLineId. Fails if the line id is not
 * valid. Calls PrepareForFocusTransitionL before focus is given to the line.
 */
EXPORT_C void CEikDialog::TryChangeFocusToL(TInt aLineId)
	{
	iPageSelector->FocusLineL(aLineId);
    }

/** * Returns the number of control components. 
 * In Avkon returns 2 as the button group container is not internal
 */
EXPORT_C TInt CEikDialog::CountComponentControls() const
    {
    if ( CbaEmbeddedInDialog( iDialogFlags ) && iButtonGroupContainer
            && iButtonGroupContainer->ButtonGroup() )
        {
        // Count Buttongroup 
        return 3;
        }

	return 2;	// Title bar and page selector.
    }

/**
 * Returns a pointer to the component control at index aIndex in the component control list.
 * Returns the title bar at index 0, then the page selector 
 * Does not imply transfer of ownership.
 */
EXPORT_C CCoeControl* CEikDialog::ComponentControl(TInt aIndex) const
    {
    if ( CbaEmbeddedInDialog( iDialogFlags ) )
        {
        switch (aIndex)
            {
            case 0:
                return iTitleBar;
            case 1:
                return iPageSelector;
            case 2:
                return ( iButtonGroupContainer &&
                    iButtonGroupContainer->ButtonGroup() ) ?
                    iButtonGroupContainer->ButtonGroup()->AsControl() :
                    NULL; 
            default:
                return NULL;
            }
        }

	switch (aIndex)
		{
		case 0:
			return iTitleBar;
		case 1:
		default:
			return iPageSelector;
		}
	}

/**
 * Handles an event of type aEventType reported by the control aControl. By default, handles
 * EEventStateChanged by calling HandleControlStateChangeL and EEventInteractionRefused by
 * calling HandleInteractionRefused.
 */  
EXPORT_C void CEikDialog::HandleControlEventL(CCoeControl* aControl,TCoeEvent aEventType)
    {
    switch (aEventType)
        {
    case EEventStateChanged:
		{
	    if ( iPageSelector && iPageSelector->IsForm() && Extension() )
	        {
	        if ( Extension()->iPublicFlags.IsSet( CEikDialogExtension::EFullyConstructed ) )
	            {
                TInt lineId = iPageSelector->LineId( *aControl );
                
                if ( lineId != KErrNotFound )
                    {
                    HandleControlStateChangeL( lineId );
                    }
	            }
	        }
		}
        break;
    case EEventInteractionRefused:
		{
		if (aControl==iButtonGroupContainer)
			HandleInteractionRefused(0);
		else
			{
			TInt lineId=iPageSelector->LineId(*aControl);
			if (lineId!=KErrNotFound)
				HandleInteractionRefused(lineId);
			}
		}
        break;
    default:
        break;
        }
    }

/**
 * Set the line which initally receives focus.
 * This is the first focusable line on the first page in the
 * dialog by default. Reimplementations of this method must
 * activate a page before doing anything else.
 */
EXPORT_C void CEikDialog::SetInitialCurrentLine()
    {
	if ( !iExtension->iInitialMade )
	    {
	    TRAP_IGNORE(iPageSelector->ActivateFirstPageL());
	    }
	if( !iIsEditable )
	    {
	    iPageSelector->SetInitialFocus();
	    }
    }

/**
 * Handles a dialog button press for the button with id aButtonId.
 * The cancel button press is not passed to the handler unless EEikDialogFlagNotifyEsc
 * is set. Returns ETrue if the dialog is ready to exit. Returns ETrue by default.
 */
EXPORT_C TBool CEikDialog::OkToExitL(TInt /*aButtonId*/)
    {
    return ETrue;
    }

/**
 * Handles a state change in the control with id aControlId. Empty by default.
 */
EXPORT_C void CEikDialog::HandleControlStateChangeL(TInt /*aControlId*/)
    {
    }

/**
 * Handles an attempt by the user to activate a dimmed button with
 * id aControlId. Prints an info message by default.
 */
EXPORT_C void CEikDialog::HandleInteractionRefused(TInt /*aControlId*/)
    {
	// Does nothing in Avkon
    }

/**
 * Adjusts all the ids of controls on the page identified by aPageId by incrementing their
 * id values by aControlIdDelta.
 */
EXPORT_C void CEikDialog::AdjustAllIdsOnPage(TInt aPageId,TInt aControlIdDelta)
	{
	iPageSelector->AdjustAllIds(aPageId,aControlIdDelta);
	}

/**
 * Makes the panel button identified by aButtonId visible if aVisible is ETrue.
 */
EXPORT_C void CEikDialog::MakePanelButtonVisible(TInt aButtonId,TBool aVisible)
	{
	// *** ToDo: Check whether this is only applicable for internal button group containers?
	ButtonGroupContainer().MakeCommandVisible(aButtonId,aVisible);
	}

/**
 * Takes any action required when the active dialog page is changed to aPageId.
 * Empty by default.
 */
EXPORT_C void CEikDialog::PageChangedL(TInt /*aPageId*/)
	{
	}

/**
 * Takes any action required when the current line is changed to aControlId.
 * Empty by default.
 *
 * @since ER5U
 */
EXPORT_C void CEikDialog::LineChangedL(TInt /*aControlId*/)
	{
	}

/**
 * Switches the latent line from aNoLongerLatent to aBecomesLatent. If dialog lines are
 * latent they are not visible and are not taken into account when laying out the dialog.
 * Latent lines can then be swapped around on the dialog later.
 */
EXPORT_C void CEikDialog::SwitchLineLatency(TInt aBecomesLatent,TInt aNoLongerLatent)
	{
	CEikCaptionedControl* becomesLatent=Line(aBecomesLatent);
	CEikCaptionedControl* noLongerLatent=Line(aNoLongerLatent);
#if defined(_DEBUG)
	if (becomesLatent->IsLatent() || !noLongerLatent->IsLatent())
		Panic(EEikDialogPanicWrongLatencySwitch);
#endif
	becomesLatent->SetLatent(ETrue);
	noLongerLatent->SetLatent(EFalse);
	noLongerLatent->CheckDimmedDisplayState();
	}

/**
 * Sets the page identified by aPageId to be dimmed if aDimmmed is ETrue.
 */
EXPORT_C void CEikDialog::SetPageDimmedNow(TInt aPageId,TBool aDimmed)
	{
	iPageSelector->SetPageDimmed(aPageId,aDimmed,EDrawNow);
	}

/**
 * Prepares the graphics context aGc for drawing the control in its normal state.
 */
EXPORT_C void CEikDialog::PrepareContext(CWindowGc& aGc) const
	{
	aGc.SetBrushStyle(CGraphicsContext::ESolidBrush);
	aGc.SetBrushColor(iEikonEnv->ControlColor(EColorDialogBackground,*this));
	aGc.SetPenColor(iEikonEnv->ControlColor(EColorDialogText,*this));
	}

/**
 * Gets the list of logical colors employed in the drawing of the control,
 * paired with an explanation of how they are used. Appends the list to aColorUseList.
 *
 * @since ER5U
 */
EXPORT_C void CEikDialog::GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const
	{
	TInt commonAttributes = TCoeColorUse::ESurrounds|TCoeColorUse::EActive|TCoeColorUse::ENormal|TCoeColorUse::ENeutral;
	TCoeColorUse colorUse;

	colorUse.SetLogicalColor(EColorDialogText);
	colorUse.SetUse(TCoeColorUse::EFore|commonAttributes);
	aColorUseList.AppendL(colorUse);

	colorUse.SetLogicalColor(EColorDialogBackground);
	colorUse.SetUse(TCoeColorUse::EBack|commonAttributes);
	aColorUseList.AppendL(colorUse);
	}

/**
 * Handles a change to the control's resources of type aType
 * which are shared across the environment, e.g. colors or fonts.
 *
 * @since ER5U
 */
EXPORT_C void CEikDialog::HandleResourceChange(TInt aType)
    {
        
    if(aType==KEikDynamicLayoutVariantSwitch)
        {
        if (IsVisible())
			DoResourceChangeLayout();
        else if (iExtension)
        	iExtension->iFlags.Set(CEikDialogExtension::ELayoutChangeWhileInvisible);

        CCoeControl::HandleResourceChange(aType);
        return;
        }
    else
    	{
    	CCoeControl::HandleResourceChange(aType);
        }
    
    if( !CAknEnv::Static()->TransparencyEnabled() && aType==KEikColorResourceChange)
        {
        Window().SetBackgroundColor(iEikonEnv->ControlColor(EColorDialogBackground,*this));
        }
    }

void CEikDialog::DoResourceChangeLayout()
	{
    // Layout must be forced through - bypass optimisations
    // Must work through all pages
    
    Layout();
    SizeChanged();
    
    TInt lastPage =  ( iPageSelector->PageContainer()->NumPages() - 1 );
    TInt pageIndex = 0;
    CEikDialogPage* page;

    while ( pageIndex++ <= lastPage )
        {
        page = iPageSelector->PageContainer()->Page( pageIndex );
        page->HandleResourceChange( KEikDynamicLayoutVariantSwitch );
        }

   	if (iExtension)
   		iExtension->iFlags.Clear(CEikDialogExtension::ELayoutChangeWhileInvisible);
	}

/**
 * Returns a pointer to the dialog's internal button command observer. This is required when creating a
 * new button group container for the dialog.
 *
 * A dialog uses a proxy to observe button commands. This means dialog subclasses can directly observe
 * commands issued by controls added to the dialog pages or by menus launched by the dialog.
 *
 * @since ER5U
 */
EXPORT_C MEikCommandObserver* CEikDialog::ButtonCommandObserver() const
	{
	return (MEikCommandObserver*)iButtonCommandObserver;
	}

/**
 * Writes the internal state of the control and its components to aStream.
 * Does nothing in release mode.
 * Designed to be overidden and base called by subclasses.
 *
 * @internal
 * @since App-Framework_6.1
 */
#ifndef _DEBUG
EXPORT_C void CEikDialog::WriteInternalStateL(RWriteStream&) const
	{}
#else
EXPORT_C void CEikDialog::WriteInternalStateL(RWriteStream& aWriteStream) const
	{
	CEikBorderedControl::WriteInternalStateL(aWriteStream);
	}
#endif

EXPORT_C void CEikDialog::Reserved_2()
	{}
EXPORT_C void CEikDialog::CEikDialog_Reserved_1()
	{}
EXPORT_C void CEikDialog::CEikDialog_Reserved_2()
	{}

EXPORT_C void CEikDialog::MakeVisible(TBool aVisible)
	{
   	if (iExtension && iExtension->iFlags[CEikDialogExtension::ELayoutChangeWhileInvisible])
   		DoResourceChangeLayout();

	// only for popup dialogs
	if ( aVisible )
	    {
    	if (!(iDialogFlags&EEikDialogFlagFillAppClientRect) && !(iDialogFlags&EEikDialogFlagFillScreen) &&
            !(iDialogFlags&EEikDialogFlagNoBackgroundFade) 
            // FIX for PTPA-7FYFDE: Query Input is also faded
            // && !( AknLayoutUtils::PenEnabled() && ( iDialogFlags & EEikDialogFlagVirtualInput ) ) 
            )
    	    {
            AknGlobalPopupPriorityController::FadeBehindPopup(*this, iPopupFader, *this, aVisible);
    	    }
        }
    
	CEikBorderedControl::MakeVisible(aVisible);

	}

void CEikDialog::FadeBehindPopup(TBool aFade)
	{
	// record the requested fade state
	if (aFade)
		iDialogFlags |= EEikDialogAttemptFadeWhenVisible;
	else
		iDialogFlags &= ~EEikDialogAttemptFadeWhenVisible;

	// Attempt to set the fade state to the requested fade state
	DoFadeBehindPopup(aFade);
	}

void CEikDialog::DoFadeBehindPopup(TBool aFade)
	{
	// Fix for ELWG-7DSEKG: Fullscreen dialogs are now added to the fade stack to allow them
	// to be opened on top of popups. PopupFader makes sure that actual fading does not happen.
	//if ((iDialogFlags&EEikDialogFlagFillAppClientRect) || (iDialogFlags&EEikDialogFlagFillScreen) ||
    //    ( iDialogFlags & EEikDialogFlagNoBackgroundFade ) ||
    
    
    // FIX for PTPA-7FYFDE: Query Input is added also to the fade stack 
    //if ( AknLayoutUtils::PenEnabled() && ( iDialogFlags & EEikDialogFlagVirtualInput ) ) 
	//	{
	//	return;
	//	}
      
	// Real fade state is only set on when the dialog is visible
	if (!IsVisible())
		aFade = EFalse;
	
	AknGlobalPopupPriorityController::FadeBehindPopup(*this, iPopupFader, *this, aFade);
	}

//
//
//

/**
 * @deprecated
 */
EXPORT_C void CEikDialog::GetCustomAutoValue(TAny* /*aReturnValue*/,TInt /*aControlType*/,const CCoeControl* /*aControl*/)
	{
	ASSERT(EFalse);
	}

/**
 *  Routine to map the button id ( Avkon softkey command id) to CEikBidCancel if it is a 
 *  "cancel" type command type and to CEikBidOk if it is an "accept" type command
 *  Other cases left unchanged
 *
 * @since Avkon
 */
EXPORT_C TInt CEikDialog::MappedCommandId( TInt aButtonId )
	{	
	switch ( aButtonId )
		{
// Do not test for case EEikBidCancel; it is defined to be the same as EAknSoftkeyCancel
		case EAknSoftkeyCancel:
		case EAknSoftkeyBack:
		case EAknSoftkeyNo:
		return EEikBidCancel;

		default:
		break;
		}

// Also process user range:
	if ( aButtonId >= EAknSoftkeyLowestUserRejectId 
		&& aButtonId < EAknSoftkeyLowestUserAcceptId )
		return EEikBidCancel;

	return aButtonId;
	}

EXPORT_C TInt CEikDialog::FormFlagsFromActivePage()
	{
	TInt activePageNum = ActivePageId();
	if (activePageNum >=0) // not sure of valid range,,,,
		return iPageSelector->PageContainer()->Page(activePageNum)->GetFormFlags();
	return 0;
	}

/* deprecated method
Instead use 
	TInt GetNumberOfLinesOnPage(TInt aPageIndex) const
	TInt GetNumberOfPages() const
	CEikCaptionedControl* GetLineByLineAndPageIndex(TInt aLineIndex, TInt aPageIndex) const
*/

EXPORT_C CEikCaptionedControl* CEikDialog::GetFirstLineOnFirstPageOrNull()
	{
	if (!iPageSelector)
		return 0;
	if (iPageSelector->PageContainer()->NumPages()>0)
		{
		CEikDialogPage* dPagePtr = iPageSelector->PageContainer()->Page(0);
		CEikCaptionedControl* linePtr = dPagePtr->LineOnPageOrNull(0);
		return linePtr;
		}
	else return 0;
	
	};

/* deprecated method
Instead use 
	TInt GetNumberOfLinesOnPage(TInt aPageIndex) const
	TInt GetNumberOfPages() const
	CEikCaptionedControl* GetLineByLineAndPageIndex(TInt aLineIndex, TInt aPageIndex) const
*/
EXPORT_C void CEikDialog::ControlsOnPage(RArray<CEikCaptionedControl*>& aControls, TInt aPageId) const
	{
	if (!iPageSelector || iPageSelector->PageContainer()->NumPages() < aPageId)
		return;
	
	CEikDialogPage* dlgPage = iPageSelector->PageContainer()->Page(aPageId);
	if (!dlgPage)
		return;

	TInt i = 0;
	CEikCaptionedControl* control = NULL;
	do
		{
		control = dlgPage->LineOnPageOrNull(i++);
		if (control)
			aControls.Append(control);
		}
		while (control != NULL);
	}

EXPORT_C TInt CEikDialog::DialogFlags()
	{ 
	return iDialogFlags;
	};

void CEikDialog::RegisterDialgWithPageSelector()
	{
	if (iPageSelector)
		iPageSelector->SetDialg(this);
	};

EXPORT_C TTypeUid::Ptr CEikDialog::MopSupplyObject(TTypeUid aId)
	{
	if ( aId.iUid == MAknsControlContext::ETypeId 
		&& Extension() 
		&& ( Extension()->LayoutCategory() == CEikDialogExtension::EFormLayout ) )
		return ( MAknsControlContext::SupplyMopObject( aId, iExtension->iBgContext ) ) ;

    if ( aId.iUid == CAknEdwinDrawingModifier::ETypeId )
        if ( Extension() && Extension()->iDrawingModifier )
            return aId.MakePtr( Extension()->iDrawingModifier );
    
    if ( aId.iUid == KAknMediatorFacade && iExtension )
        { // we actually don't care if this is set or not
        return aId.MakePtr(iExtension->iAknDSSD);
        }
    if( aId.iUid == CEikScrollBarFrame::ETypeId )
    	{
    	TInt activePageNum = ActivePageId();
		CEikDialogPage* currentPage = NULL ;
		if ( activePageNum >= 0 ) 
			{
			currentPage = iPageSelector->PageContainer()->Page( activePageNum ) ;
    		currentPage->SetScbState(ETrue);
			}
    	return aId.MakePtr(iPageSelector->PageContainer()->ScrollBar());
    	}
    	
    if ( aId.iUid == CEikDialog::ETypeId )
        {
        return aId.MakePtr( this );
        }

	return SupplyMopObject(aId, iButtonGroupContainer);
	}


EXPORT_C TInt CEikDialog::CountFadedComponents()
	{
	// Don't count the CBA if it contains no commands, since
	// we don't want it to be unfaded.
	CCoeControl* cba = iButtonGroupContainer->ButtonGroup()->AsControl();
    TBool fadeCba = static_cast<CEikCba*>( cba )->IsEmpty();
	return fadeCba ? 1 : 2;
	}

EXPORT_C CCoeControl* CEikDialog::FadedComponent(TInt aIndex)
	{
	switch (aIndex)
		{
		case 0:
			return this;
		case 1:
			return iButtonGroupContainer;
		default:
			return NULL;
		}
	}

EXPORT_C void CEikDialog::UpdatePageL(TBool aRedraw)
	{
	if (Rect().Height())
		{
		if (iPageSelector)
			if (iPageSelector->IsForm())
				if (iPageSelector->PageContainer())
					{
					iPageSelector->PageContainer()->SetEditableL(iIsEditable);
					if (CurrentLine())
						TryChangeFocusToL(CurrentLine()->iId);
					if (aRedraw)
						DrawDeferred();
					}
		}
	}


EXPORT_C TInt CEikDialog::GetNumberOfLinesOnPage(TInt aPageIndex) const
	{
	if (iPageSelector)
		{
		CEikDialogPageContainer* pageContainer = iPageSelector->PageContainer();
		if (pageContainer)
			{
			CEikDialogPage* page = pageContainer->Page(aPageIndex);
			if (page)
				return page->NumberOfLines();
			}
		}
	return 0;
	}

EXPORT_C TInt CEikDialog::GetNumberOfPages() const
	{
	if (iPageSelector)
		{
		CEikDialogPageContainer* pageContainer = iPageSelector->PageContainer();
		if (pageContainer)
			return pageContainer->NumPages();
		}
	return 0;
    }
    
//--------------------------------------------------------------------------------
// CEikDialog::HandleDialogPageEventL(TInt aEventID) 
// Handles dialog page events by closing dialog when event is EDialogPageTapped
// and dialog has flag EEikDialogFlagCloseDialogWhenTapped
//--------------------------------------------------------------------------------
//
EXPORT_C void CEikDialog::HandleDialogPageEventL(TInt aEventID )       
	{
	// If event is EDialogPageTapped and flag EEikDialogFlagCloseDialogWhenTapped is on
	if ( (aEventID == MEikDialogPageObserver::EDialogPageTapped) && 
	     (iDialogFlags & EEikDialogFlagCloseDialogWhenTapped) )
	    {	    
	    // Exit from dialog with cancel.
	    TryExitL(EEikBidCancel);
	    }
	}

EXPORT_C CEikCaptionedControl* CEikDialog::GetLineByLineAndPageIndex(TInt aLineIndex, TInt aPageIndex) const
	{
	if (iPageSelector)
		{
		CEikDialogPageContainer* pageContainer = iPageSelector->PageContainer();
		if (pageContainer)
			{
			CEikDialogPage* page = pageContainer->Page(aPageIndex);
			if (page)
				return page->LineByIndex(aLineIndex);
			}
		}
	return 0;
	}

EXPORT_C CEikDialogExtension* CEikDialog::Extension() const
	{
	return iExtension ;
	}

CEikDialogExtension* CEikDialogExtension::NewL( const CEikDialog& aParent ) // static 
	{
	CEikDialogExtension* self = new (ELeave) CEikDialogExtension( aParent ) ;
	CleanupStack::PushL( self ) ;
    self->ConstructL();
	CleanupStack::Pop( self ) ;
	return self ;
	}

CEikDialogExtension::CEikDialogExtension( const CEikDialog& aParent ) : 
    CActive( EPriorityLow ),
    iParent( aParent )
#ifdef RD_UI_TRANSITION_EFFECTS_POPUPS
    , iRegisteredContext( KNullUid )
#endif
	{
	}

CEikDialogExtension::~CEikDialogExtension() 
	{
	if ( IsActive() )
	    {
	    Cancel();
	    }
    delete iAknDSSD; // will cancel commands if active
	delete iBgContext ;
    delete iDrawingModifier ;
	}

void CEikDialogExtension::ConstructL()
    {
	// <SKIN> create iBgContext
    iBgContext = CAknsListBoxBackgroundControlContext::NewL( 
        KAknsIIDQsnBgAreaMainListGene, iParent.Rect(), ETrue,
        KAknsIIDQsnBgColumnAB, iParent.Rect() )  ; // Last two parameters are effectively place-holders	
    iDrawingModifier = new (ELeave )CAknEdwinDrawingModifier();
    iDrawingModifier->SetInhibitNotifyNewFormatDrawing( ETrue );
    CActiveScheduler::Add( this );
    }

EXPORT_C CEikDialogExtension::TLayoutCategory CEikDialogExtension::LayoutCategory() const
	{
	TLayoutCategory type = EUnknownLayout;
	if ( !iParent.iPageSelector )
		type = ENotConstructed;
	else if ( iParent.iPageSelector->IsForm() )
		type = EFormLayout;
	else if ( (iParent.iDialogFlags)&EEikDialogFlagFillAppClientRect ) // full screen but not Form
		type = EFullScreenLayout;
	else 
		type = EPopupLayout; // ends up being the default. 

	return type;
	}

#if (defined(__COVER_DISPLAY) || defined(__VOICE_UI ) )   

EXPORT_C void CEikDialog::PublishDialogL(TInt aDialogIndex, TUid aCatUid)
    {
    // create utility for these someday perhaps..
    if (!iExtension)
        {
        iExtension = CEikDialogExtension::NewL( *this );
        }
    if (!iExtension->iAknDSSD)
        {
        iExtension->iAknDSSD = CAknMediatorFacade::NewL(this);
        }
    else // just in case, if someone changes the indeces while previous commands active
        {
        CancelMediatorCommand(this); // handles flagging  
        }
    
    iExtension->iAknDSSD->CatUid() = aCatUid;
    iExtension->iAknDSSD->DialogIndex() = aDialogIndex;
    iExtension->iAknDSSD->ResetBuffer();
    }	
	
EXPORT_C void CEikDialog::SetMediatorObserver(MAknDialogMediatorObserver* aObserver)
    {
    if (!iExtension)
        {
        iExtension = CEikDialogExtension::NewL( *this );
        }
    if (!iExtension->iAknDSSD)
        {
        iExtension->iAknDSSD = CAknMediatorFacade::NewL(this);
        }

    iExtension->iAknDSSD->SetObserver(aObserver);    
    }
#else
EXPORT_C void CEikDialog::PublishDialogL(TInt, TUid) {}
EXPORT_C void CEikDialog::SetMediatorObserver(MAknDialogMediatorObserver*){}
#endif

void CEikDialogExtension::DoCancel()
    {    
    }

void CEikDialogExtension::RunL()
    {
    const_cast<CEikDialog&>( iParent ).TryExitL( iButtonId );
    }

void CEikDialogExtension::StartDelayedExit()
    {
    if (!IsActive())
        {
        TRequestStatus* status = &iStatus;
        User::RequestComplete( status, KErrNone );
        SetActive();    	
        }
    }
    
// -----------------------------------------------------------------------------
// CAknToolbar::SlideToolbar
// Draws the toolbar with sliding effect.
// -----------------------------------------------------------------------------
//    
EXPORT_C void CEikDialog::SlideDialog()
    {
#ifdef RD_SLIDING_ANIMATION_EFFECTS
	TBool useScreenBitmap = EFalse;
	TBool useFrameBitmap = EFalse;

    CFbsBitmap* screenCapture;
    CFbsBitmap* frameBitmap;
	
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
	    
	TInt slidingMode = AknsDrawUtils::SlidingMode(skin);

    TPoint startPos = Position();
    TRect origRect(Position(),Rect().Size());
        
    const TSize screenSize = iEikonEnv->EikAppUi()->ApplicationRect().Size();

    // Try to copy screen to backup bitmap
    iCoeEnv->WsSession().Flush(); // first update screen (not necessary?)
    CWsScreenDevice* scrDevice = static_cast<CWsScreenDevice*>( SystemGc().Device() );
    TDisplayMode displayMode( scrDevice->DisplayMode() );

    RWsSession& wsSession = CCoeEnv::Static()->WsSession();

	TRAPD( SCerr, screenCapture = new (ELeave) CWsBitmap( wsSession ) );
    
    TInt errCode( KErrNone );
    if (SCerr == KErrNone)
        {
        errCode = screenCapture->Create( screenSize, displayMode );
        }
        
    if (errCode == KErrNone)
        {
        errCode = scrDevice->CopyScreenToBitmap( screenCapture );
        }
    
    if (errCode == KErrNone)
        {
        useScreenBitmap = ETrue;
        }


    // Try to draw skin frame to offscreen bitmap
    CFbsBitGc* fbsBitGc( NULL );
    CFbsBitmapDevice* bmpDevice( NULL );
    TRAPD(FBerr, 
            { 
            frameBitmap = new (ELeave) CFbsBitmap( );
            CleanupStack::PushL(frameBitmap);
            User::LeaveIfError( frameBitmap->Create( Rect().Size(), displayMode ) );
            bmpDevice = CFbsBitmapDevice::NewL( frameBitmap );
            CleanupStack::PushL( bmpDevice );
                
            fbsBitGc = CFbsBitGc::NewL();
            CleanupStack::PushL( fbsBitGc );
            
            fbsBitGc->Activate( bmpDevice );
            CleanupStack::Pop(3);
            }  
        );
    
    if ( iExtension->LayoutCategory() == CEikDialogExtension::EPopupLayout && FBerr == KErrNone)
        {
        MAknsSkinInstance* skin = AknsUtils::SkinInstance();

        TAknLayoutRect topLeft;
        topLeft.LayoutRect(Rect(), SkinLayout::Popup_windows_skin_placing__frame_general__Line_2());

        TAknLayoutRect bottomRight;
    	bottomRight.LayoutRect(Rect(), SkinLayout::Popup_windows_skin_placing__frame_general__Line_5());

        TRect outerRect = TRect(topLeft.Rect().iTl, bottomRight.Rect().iBr);
        TRect innerRect = TRect(topLeft.Rect().iBr, bottomRight.Rect().iTl);
    
        useFrameBitmap = ETrue;
        if (!AknsDrawUtils::DrawFrame( skin, *fbsBitGc, outerRect, innerRect,
						KAknsIIDQsnFrPopup,KAknsIIDQsnFrPopupCenter) )
            {
            useFrameBitmap = EFalse;
            }
        else
            {
            useFrameBitmap = ETrue;
            }
        }


    CEikDialogSlider* slider = NULL;
    TRAPD( sliderErr, slider = slider->NewL(SystemGc(),frameBitmap,screenCapture ));

    // sliding from the softkey direction
    if (slidingMode == ESlidingFromCBA)
        {
	    AknLayoutUtils::TAknCbaLocation location = AknLayoutUtils::CbaLocation();
        switch(location)
            {
            case AknLayoutUtils::EAknCbaLocationRight:
                slidingMode = ESlidingFromRight;
                break;
            case AknLayoutUtils::EAknCbaLocationLeft:
                slidingMode = ESlidingFromLeft;
                break;
            case AknLayoutUtils::EAknCbaLocationBottom:
                slidingMode = ESlidingFromBottom;
                break;
            default:
                slidingMode = ESlidingFromBottom;
                break;
            }
        }


    // don't use math-library (one less dependency)
    if (slidingMode == ESlidingFromRandom)
        {
        TTime homeTime;
        homeTime.HomeTime();
        TInt64 seed = homeTime.Int64();
        TInt value = seed & 0xff;
        value = value >> 5; // take bits 5-7
        slidingMode = ESlidingFromLeft + value;
        }
        
    switch(slidingMode)
    	{
    	case ESlidingFromLeft:
            startPos.iX = 0 - origRect.Size().iWidth; // just out of screen
            break;

    	case ESlidingFromTopLeft:
            startPos.iX = 0 - origRect.Size().iWidth;
            startPos.iY = 0 - origRect.Size().iHeight;
            break;

    	case ESlidingFromTop:
            startPos.iY = 0 - origRect.Size().iHeight;
            break;

    	case ESlidingFromTopRight:
            startPos.iX = screenSize.iWidth;
            startPos.iY = 0 - origRect.Size().iHeight;
            break;

        case ESlidingFromRight:
            startPos.iX = screenSize.iWidth;
            break;

       	case ESlidingFromBottomRight:
            startPos.iX = screenSize.iWidth;
            startPos.iY = screenSize.iHeight;
            break;

       	case ESlidingFromBottom:
            startPos.iY = screenSize.iHeight;
            break;

       	case ESlidingFromBottomLeft:
            startPos.iX = 0 - origRect.Size().iWidth;
            startPos.iY = screenSize.iHeight;
            break;
    
        default:
            break;
    	}

    TPoint start = startPos;
    
    TInt stepCount = 12;
        
    //iCoeEnv->WsSession().Flush();
    
    // only do sliding if we have screen capture, dialog background in bitmap and slider
    // otherwise we have OOM and do no sliding
    if (useScreenBitmap && useFrameBitmap && sliderErr == KErrNone)
        {
        TRAP_IGNORE(slider->SlideDialogL(start, origRect.iTl, stepCount));
        }
    
    //TRAP_IGNORE(ActivateL()); // do we need to do this before slider is deleted?
    
    if (slider)
        {
        delete slider;
        slider = NULL;
        }
    
	if (SCerr == KErrNone)
	    {
    	delete screenCapture;	    
	    }
	    
	if (FBerr == KErrNone)
	    {
	    delete bmpDevice;
	    delete fbsBitGc;
	    delete frameBitmap;
	    }
#endif //RD_SLIDING_ANIMATION_EFFECTS
    }
    
#ifdef RD_SLIDING_ANIMATION_EFFECTS
CEikDialogSlider::CEikDialogSlider(CWindowGc& aWindowGc, CFbsBitmap*& aDialogBack, CFbsBitmap*& aScreen)
:iWindowGc(aWindowGc), iDialogBack(aDialogBack), iScreen(aScreen)
	{
	}
	

CEikDialogSlider* CEikDialogSlider::NewL(CWindowGc& aWindowGc, CFbsBitmap*& aDialogBack, CFbsBitmap*& aScreen)
	{
	CEikDialogSlider* self = new(ELeave)CEikDialogSlider(aWindowGc, aDialogBack, aScreen);
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop();
	return self;
	}


void CEikDialogSlider::ConstructL()
	{
    const TSize screenSize = iEikonEnv->EikAppUi()->ApplicationRect().Size();
	
	CreateWindowL();
    SetExtent( TPoint(0,0), screenSize);
	}
	
CEikDialogSlider::~CEikDialogSlider()
	{
	}

void CEikDialogSlider::Draw(const TRect& /* aRect */) const
    {
    // only SlideDialog does drawing
    }
    
    
void CEikDialogSlider::SlideDialogL(TPoint& aStart, TPoint& aEnd, TInt aStepCount)
	{
	ActivateL();
	
    TInt stepX = ( aEnd.iX - aStart.iX ) / aStepCount;
    TInt stepY = ( aEnd.iY - aStart.iY ) / aStepCount;
    TSize dialogSize = iDialogBack->SizeInPixels();	
    TSize ScreenSize = iScreen->SizeInPixels();
    TPoint oldPos;
    TRect vertiRect; // these are used to restore background under slided dialog
    TRect horizRect;
	
	// Because of rounding error, endpoint from sliding is not same as aEnd.
	// To correct this, adjust startpoint.
	aStart.iX = aEnd.iX - aStepCount * stepX;
	aStart.iY = aEnd.iY - aStepCount * stepY;
	
	// slide all but last frame
    for (TInt i=0 ; i < aStepCount ; i++)
        {
        oldPos = aStart;
        aStart.iX += stepX;
        aStart.iY += stepY;
        ActivateGc();
        Window().Invalidate( );
        Window().BeginRedraw( ); // this flushes window server
        
        TRect dlgRect(aStart,dialogSize);
        
        iWindowGc.BitBlt(dlgRect.iTl, iDialogBack);

        if (stepX < dlgRect.Width() && stepY < dlgRect.Height()) // old and new rects are intersecting
            {
            if (stepY > 0) // dialog moving down, restore area from top of dialog
                {
                vertiRect = TRect(dlgRect.iTl.iX - stepX,
                                  dlgRect.iTl.iY - stepY,
                                  dlgRect.iBr.iX - stepX,
                                  dlgRect.iTl.iY);
                horizRect.iTl.iY = dlgRect.iTl.iY;
                horizRect.iBr.iY = dlgRect.iBr.iY - stepY;
                }
            else if (stepY < 0) // moving up
                {
                vertiRect = TRect(dlgRect.iTl.iX - stepX,
                                 dlgRect.iBr.iY,
                                 dlgRect.iBr.iX - stepX,
                                 dlgRect.iBr.iY - stepY);
                horizRect.iTl.iY = dlgRect.iTl.iY - stepY;
                horizRect.iBr.iY = dlgRect.iBr.iY;
                }

            if (stepX > 0) // dialog moving right, restore area from left of dialog
                {
                horizRect.iTl.iX = dlgRect.iTl.iX - stepX;
                horizRect.iBr.iX = dlgRect.iTl.iX;
                }
            else if (stepX < 0) // moving left
                {
                horizRect.iTl.iX = dlgRect.iBr.iX;
                horizRect.iBr.iX = dlgRect.iBr.iX - stepX;
                }
                
            if (stepX != 0 && stepY == 0) // set y-coordinates if only moving horizontally
            	{
            	horizRect.iTl.iY = dlgRect.iTl.iY;
            	horizRect.iBr.iY = dlgRect.iBr.iY;
            	}

            iWindowGc.BitBlt(vertiRect.iTl,iScreen,vertiRect);
            iWindowGc.BitBlt(horizRect.iTl,iScreen,horizRect);
            }
        else // old and new rects are not intersecting -> clear under old rect
            {
            TRect oldRect(oldPos,dialogSize);
            iWindowGc.BitBlt(oldPos,iScreen,oldRect);
            }
            
        Window().EndRedraw();            
        DeactivateGc();

        iCoeEnv->WsSession().Flush();
        User::After(2000); // give little time to active objects
        }
	}
#endif //RD_SLIDING_ANIMATION_EFFECTS

EXPORT_C void CEikDialog::SetMultilineQuery(TBool aIsMultilineQuery)
	{
	if (iPageSelector)
		{
		CEikDialogPageContainer* pageContainer = iPageSelector->PageContainer();
		if (pageContainer)
			{
			CEikDialogPage* page = pageContainer->Page(0);
			if (page)
				page->SetDoubleQuery(aIsMultilineQuery);
			}
		}

	}
    

void CEikDialog::HandleEmbeddedSofkeyStateChange()
    {
    // Check that dialog is constructed and actually with embedded
    // softkeys
    if ( iExtension && CbaEmbeddedInDialog( iDialogFlags ) )
        {
        TSize dialogSize( Rect().Size() );
        CEikCba* cba = static_cast<CEikCba*>(
                iButtonGroupContainer->ButtonGroup() );
        TBool cbaVisible( cba->IsVisible() && !cba->IsEmpty() );

        TRect screenRect;
        AknLayoutUtils::LayoutMetricsRect(
            AknLayoutUtils::EScreen, screenRect );
        TAknLayoutRect cbaRect;
        cbaRect.LayoutRect(
            screenRect, 
            AknLayoutScalable_Avkon::popup_sk_window( 0 ).LayoutLine() );
        
        if ( cbaVisible )
            {
            if ( dialogSize.iHeight == MinimumSize().iHeight )
                {
                dialogSize.iHeight += cbaRect.Rect().Height();
                }
            }
        else
            {
            dialogSize.iHeight -= cbaRect.Rect().Height();
            }

        SetRect( TRect(
            AknPopupUtils::Position( dialogSize, this ), dialogSize ) );
        }
    }


TInt CEikDialog::HandleEmbeddedSoftkeyStateChangeCallBack( TAny* aAny )
    {
    CEikDialog* self = static_cast<CEikDialog*>( aAny );
    self->HandleEmbeddedSofkeyStateChange();
    return KErrNone;
    }


void CEikDialog::EnableContentObserver( TBool aEnabled )
    {
    // Content observer is only used with embedded softkeys.
    if ( !CbaEmbeddedInDialog( iDialogFlags ) )
        {
        return;
        }
 
    // Set observer call back.
    TCallBack callBack;
    callBack.iPtr = NULL;
    
    if ( aEnabled )
        {
        callBack = TCallBack(
            HandleEmbeddedSoftkeyStateChangeCallBack, this );
        }
    
    if ( iButtonGroupContainer && iButtonGroupContainer->ButtonGroup() )
        {
        CCoeControl* control = iButtonGroupContainer->ButtonGroup()->AsControl();
        CEikCba* cba = static_cast<CEikCba*>( control );
        if ( cba )
            {
            AknCbaContentObserver::SetContentObserver( cba, callBack );
            }
        }
    }


// Checking if the blank screen is being displayed.
// If so, the blank screen will cover everything.
const TInt KWgPriorityOfBlankScreen = 10000; // copied from akncapserverentry.cpp
TBool IsBlankScreenDisplayed()
    {
    TBool isBlankScreenDisplayed(EFalse);
    RWsSession& wsSession = CEikonEnv::Static()->WsSession();
    
    CArrayFixFlat<TInt> *wgIds = new CArrayFixFlat<TInt>(2);
    if (wgIds != NULL)
        {
        if (KErrNone == wsSession.WindowGroupList(wgIds) && wgIds->Count() > 0)
            {
            TInt priority = wsSession.GetWindowGroupOrdinalPriority(wgIds->At(0));
            RDebug::Printf("IsBlankScreenDisplayed():priority:%d",priority);
            if (priority == KWgPriorityOfBlankScreen)
                {
                isBlankScreenDisplayed = ETrue;
                }
            }
        }
    delete wgIds;
    RDebug::Printf("IsBlankScreenDisplayed():isBlankScreenDisplayed:%d",isBlankScreenDisplayed);
    return isBlankScreenDisplayed;
    }
    
