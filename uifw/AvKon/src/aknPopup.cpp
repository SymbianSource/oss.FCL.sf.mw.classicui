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
* Description: 
*
*/

// AknPopup.cpp
//
// Copyright (c) 1997-2001 Symbian Ltd.  All rights reserved.
//

#include <aknPopupHeadingPane.h>
#include <AknPanic.h>
#include <aknsfld.h>
#include <AknsFrameBackgroundControlContext.h>
#include <eikfrlbd.h>
#include <eikmop.h>
#include <aknlayoutscalable_avkon.cdl.h>
#include <skinlayout.cdl.h>
#include <aknglobalpopupprioritycontroller.h>
#include <touchfeedback.h>

#ifdef RD_UI_TRANSITION_EFFECTS_POPUPS
#include <gfxtranseffect/gfxtranseffect.h>
#include <akntransitionutils.h>
#endif

#include <AknTasHook.h>

#include "aknPopup.h"
#include "akntrace.h"
#include "aknitemactionmenuregister.h"

const TInt KSpaceBelowTitle=7;
const TInt KSoftkeyHeightUndefined = -1;

enum TPopUpListFlags
    {    
    EPopupHandlingPointerEvent    = 0x01,
    EPopupAcceptAfterPointerEvent = 0x02,
    
    //EFTG-7HWDP6.
    //When portrait is initial model, and 'Full screen QWERTY keyboard' is default input method,
    //the behavior that double tap edit's area quickly may be treated by different control.
    //Findpane deals with first tapping, the Fep will be invoked,Then the model will changed from portrait to landscape.
    //Popuplist deals with second tapping. It invoke AttemptExitL( Efalse ) because pointer is outside of the popuplist.
    //The result is 'Full Screen QWERTY Keyboard' colsed. So we must prevent popuplist's exit in this case.
    //EPopupFepStartEvent will prevent popuplist's exit.        
    //EPopupLayoutSwitchEvent is a flag that decide EPopupFepStartEvent is valid or not.
    EPopupFepStartEvent           = 0x04,   
    EPopupLayoutSwitchEvent       = 0x08,
    
    // Multiselect popup list should not close when delay highlight happen 
    EPopupDelayHighlight          = 0x10,
    EPopupCancelAfterPointerEvent = 0x20,
    // Popup application is single click enabled.
    EPopupSingleClickEnabled      = 0x40
    };
 

/**
* Calculates and returns softkey rectangle.
*/
static TRect SoftkeyRect()
    {
    TRect screen;
    AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EScreen, screen );
           
    TAknLayoutRect softkeyRect;
    softkeyRect.LayoutRect( screen, 
        AknLayoutScalable_Avkon::popup_sk_window( 0 ).LayoutLine() );
    
    return softkeyRect.Rect();
    }

 
NONSHARABLE_CLASS(CAknPopupListExtension): public CBase
    {
    public:
        CAknPopupListExtension();
        ~CAknPopupListExtension();

        /**
         * Returns ETrue if popup pointer event is accepted otherwise EFalse.
         * 
         * @param aListBox Popup list listbox.
         * @return ETrue if event is accepted.
         */
        TBool AcceptPointerEvent( CEikListBox* aListBox ) const;

        /**
         * Returns ETrue if list box event is accepted otherwise EFalse.
         * 
         * @param aListBox Popup list listbox.
         * @param aEventType List event type.
         * @return ETrue if event is accepted.
         */
        TBool AcceptListBoxEvent(
                CEikListBox* aListBox,
                MEikListBoxObserver::TListBoxEvent aEventType ) const;

    public:
        CAknSearchField* iSearchControl;    // owned
        CAknsFrameBackgroundControlContext* iBgContext;        
 
        TInt  iFlags;    
        TBool iItemDraggingActioned;  
    };

CAknPopupListExtension::CAknPopupListExtension()
    {
    if ( AknLayoutUtils::PenEnabled() )
        {
        iFlags = 0;
        }
    }

CAknPopupListExtension::~CAknPopupListExtension()
    {
    delete iBgContext;
    }


TBool CAknPopupListExtension::AcceptPointerEvent(
        CEikListBox* aListBox ) const
    {
    TBool accept( EFalse );
    if ( aListBox )
        {
        // Do not accept if multiselection
        // or flag does not allow accepting
        // or highlight is disabled (list is view only)
        accept = !aListBox->IsMultiselection()
            && ( iFlags & EPopupAcceptAfterPointerEvent
            || iFlags & EPopupCancelAfterPointerEvent )
            && !( aListBox->View()->ItemDrawer()->Flags()
                    & CListItemDrawer::EDisableHighlight );
        }
    return accept;
    }

TBool CAknPopupListExtension::AcceptListBoxEvent(
        CEikListBox* aListBox,
        MEikListBoxObserver::TListBoxEvent aEventType ) const
    {
    TBool accept( EFalse );
    if ( aListBox )
        {
        switch ( aEventType )
            {
            case ( MEikListBoxObserver::EEventItemClicked ):
            case ( MEikListBoxObserver::EEventItemSingleClicked ):
                {
                if ( iItemDraggingActioned
                        || aListBox->IsMultiselection()
                        || ( !( iFlags & EPopupSingleClickEnabled )
                                && !AknLayoutUtils::PenEnabled() ) )
                    {
                    break;
                    }
                } // Fall through
            case ( MEikListBoxObserver::EEventEnterKeyPressed ):
                {
                accept = ETrue;
                break;
                }
            default:
                {
                break;
                }
            }
        }
    return accept;
    }


/**
* Constructor
*
*/
EXPORT_C CAknPopupList::CAknPopupList()
    {
    SetMopParent(iEikonEnv->EikAppUi());
#ifdef RD_UI_TRANSITION_EFFECTS_POPUPS
    GfxTransEffect::Register( this, KGfxContextMenuControlUid );
#endif
    }

/**
* Destructor
*
*/
EXPORT_C CAknPopupList::~CAknPopupList()
    {
    _AKNTRACE_FUNC_ENTER;
    AKNTASHOOK_REMOVE();
    if ( iPopoutCba )
        {
        iPopoutCba->MakeVisible( EFalse );
        }
#ifdef RD_UI_TRANSITION_EFFECTS_POPUPS
    // prevent drawing when Deregistering
    MakeVisible( EFalse ); 
    GfxTransEffect::Deregister( this );
#endif
    if (iCoeEnv && iEikonEnv)
        {
        iEikonEnv->RemoveFromStack(this);
        if (iAppBroughtForwards)
            iEikonEnv->BringForwards(EFalse);
        }
    if (iReturn)
        {
        FadeBehindPopup(EFalse);
        }
    AknGlobalPopupPriorityController::RemovePopupPriority(*this);
    delete iTitle;
    delete iPopoutCba;
    delete iIdle;
    if (FindBox())
        {
        delete FindBox();
        }
    delete iPopupListExtension;
    // Only stop the scheduler if a return value has been set -
    // otherwise the construction failed before the scheduler started.
    // The iReturn value is a convienient value to use since it is the
    // last member ste before the actiave scheduler is started.

    // Reset action menu register
    AknItemActionMenuRegister::SetConstructingMenuBarOwnerL( NULL );
    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C void CAknPopupList::CloseState()
    {
    _AKNTRACE_FUNC_ENTER;
    CancelPopup();
    _AKNTRACE_FUNC_EXIT;
    }


EXPORT_C void CAknPopupList::SetMaximumHeight(TInt aItems)
    {
    _AKNTRACE("CAknPopupList::SetMaximumHeight aItems=%d", aItems);
    iLayout.iMaximumHeight = aItems;
    }

/**
* Creates the pop-up list
*
* @param        aListBox        Pre-existing listbox-derived class
* @param        aCbaResource        Softkey pane to display while pop-up is active
*/
EXPORT_C CAknPopupList* CAknPopupList::NewL(CEikListBox* aListBox, TInt aCbaResource, AknPopupLayouts::TAknPopupLayouts aType)
    {
    _AKNTRACE_FUNC_ENTER;
    CAknPopupList* self = new(ELeave)CAknPopupList();        
    CleanupStack::PushL(self);
    self->ConstructL(aListBox, aCbaResource, aType);
    CleanupStack::Pop();        // self
    AKNTASHOOK_ADDL( self, "CAknPopupList" );
    _AKNTRACE_FUNC_EXIT;
    return self;
    }

/**
* 2nd phase construction
*
*/
EXPORT_C void CAknPopupList::ConstructL(CEikListBox* aListBox, TInt aCbaResource, AknPopupLayouts::TAknPopupLayouts aType)
    {
    _AKNTRACE_FUNC_ENTER;
    CreateWindowL();
    Window().SetPointerGrab(ETrue);
    if( CAknEnv::Static()->TransparencyEnabled() )
        {
        Window().SetRequiredDisplayMode( EColor16MA );
        TInt err = Window().SetTransparencyAlphaChannel();

        if ( err == KErrNone )
            {
            Window().SetBackgroundColor(~0);
            }
        }

    iListBox = aListBox;
    iWindowType = aType;
    // Set a popout-type border

    iBorder.SetType(TGulBorder::ENone);
    iListBox->SetBorder(TGulBorder::ENone);

    // Create extension class
    if (!iPopupListExtension)
        iPopupListExtension = new (ELeave) CAknPopupListExtension(); 

    CAknAppUi* appUi = static_cast<CAknAppUi*>( iEikonEnv->EikAppUi() );
    if ( appUi && appUi->IsSingleClickCompatible() )
        {
        iPopupListExtension->iFlags |= EPopupSingleClickEnabled;
        }

    // If the system 'markable' CBA's are used, flag the listbox
    // as markable. (This allows it to update the CBA when the selected item
    // is changed).
    if (aCbaResource == R_AVKON_SOFTKEYS_MARK_BACK ||
        aCbaResource == R_AVKON_SOFTKEYS_UNMARK_BACK)
        iMarkable = ETrue;

    iCurrentResource = aCbaResource;

    // Create a CBA for use with the popup

    TUint flags = CEikButtonGroupContainer::EAddToStack;

    // Embedded CBA only in touch layout
    if ( AknLayoutUtils::PenEnabled() )
        {
        flags |= CEikButtonGroupContainer::EIsEmbedded;
        flags |= CEikButtonGroupContainer::EDelayActivation;
        }
    
    // Notify action menu register though popup list has no menubar.
    // This way item action menu and list is linked correctly and item
    // specific softkey state is changed according to list highlight.
    AknItemActionMenuRegister::SetConstructingMenuBarOwnerL( this );
    iPopoutCba = CEikButtonGroupContainer::NewL(
                CEikButtonGroupContainer::ECba,
                CEikButtonGroupContainer::EHorizontal,
                this, iCurrentResource, *this, flags );
    
    // non visible CBA's do not recieve keys
    iPopoutCba->MakeVisible(EFalse);

	AknGlobalPopupPriorityController::AddSubPopupL(*this, *iPopoutCba->ButtonGroup()->AsControl());

    iPopupListExtension->iBgContext = NULL;
 
    SetGloballyCapturing( ETrue );
    SetPointerCapture( ETrue );

    _AKNTRACE_FUNC_EXIT;
    }

/**
* Set the title for the selection list
*
* @param        aTitle        Title to be displayed
*/
EXPORT_C void CAknPopupList::SetTitleL(const TDesC& aTitle)
    {
    _AKNTRACE("CAknPopupList::SetTitleL: aTitle=%S",&aTitle);
    if (!iTitle)
        {
        iTitle = new(ELeave)CAknPopupHeadingPane;
        iTitle->SetContainerWindowL(*this);
        iTitle->ConstructL(aTitle);
        } 
    else 
        {
        iTitle->SetTextL(aTitle);
        }
    }

/**
* Executes the pop-up selection list. Only returns when the user can accepted
* or cancelled the pop-up.
*
* @return        ETrue if the popup was accepted. EFalse if the popup was cancelled
*/
EXPORT_C TBool CAknPopupList::ExecuteLD()
    {
    _AKNTRACE_FUNC_ENTER;
    __ASSERT_DEBUG(iListBox,Panic(EAknPanicListboxUndefined));
    iPopoutCba->SetBoundingRect(TRect(iAvkonAppUi->ApplicationRect().Size()));
    
    // Disable item specific menu just before the popup is about to be shown.
    // It can't be done earlier since CAknPopupList doesn't know whether the
    // embedded listbox is fully constructed when passed to its constructor or
    // not.
    iListBox->DisableItemSpecificMenu();

    // Technically it's wrong to disable findbox here, but doing so improves
    // compatibility with the old CAknEnv::ExecuteEmptyPopupListL implementation.
    // This code block can be removed to make the findbox permanently visible
    // (as is the case with main pane lists that use a fixed findbox).
    if ( FindBox() && iListBox->Model()->NumberOfItems() == 0 )
        {
        STATIC_CAST(CAknFilteredTextListBoxModel*,
                    ListBox()->Model())->Filter()->SetSearchField( NULL );
        FindBox()->Editor().SetFocus( EFalse );                    
        delete iPopupListExtension->iSearchControl;
        iPopupListExtension->iSearchControl = NULL;
        }

    if (FindBox())
        {
        SetupWindowLayout(AknPopupLayouts::TAknPopupLayouts(EAknPopupLayoutsFind + iWindowType));
        }        
    else
        {
        SetupWindowLayout(iWindowType);
        }

    iListBox->SetListBoxObserver(this);        
    iPopoutCba->MakeVisible(ETrue);

    AknGlobalPopupPriorityController::AddPopupToControlStackL(*this,ECoeStackPriorityDialog);
    AknGlobalPopupPriorityController::AddPopupToControlStackL(*iPopoutCba->ButtonGroup()->AsControl(),
        ECoeStackPriorityCba, ECoeStackFlagRefusesFocus );
    SetFocus(ETrue);

    if (iMarkable)
        {
        // If markable, set the popup to observe event change events.
        // Call HandleControlEvent to set the CBA appropriate to the 1st item
        iListBox->SetObserver(this);
        HandleControlEventL(iListBox, EEventStateChanged);
        }

    FadeBehindPopup( ETrue );
    
    
    #ifdef RD_UI_TRANSITION_EFFECTS_PHASE2	
    // this code finds out if this control belongs to focused window group
    // this is done to find out if popuplist is shown behind another dialog
    // (this happens in wlan setup queries) If popuplist is not on foreground
    // the transition effect is skipped
    RWsSession& wsSession = CEikonEnv::Static()->WsSession();
	
	TInt focusGroup = wsSession.GetFocusWindowGroup();
		
    TInt count = wsSession.NumWindowGroups(0);
    TBool thisIsFocused( EFalse );
    
    CArrayFixFlat<TInt>* wgIds=new(ELeave) CArrayFixFlat<TInt>(count);
    CleanupStack::PushL(wgIds);
    // Get list of window group ids from WServ
    wsSession.WindowGroupList(0,wgIds);
    // Select the first in the list (which will always be the forground app)
    TInt wgId = (*wgIds)[0];
    
    if( focusGroup == wgId )
        thisIsFocused = ETrue;
        
    CleanupStack::PopAndDestroy();  // wgIds;
    
    
	#endif //RD_UI_TRANSITION_EFFECTS_PHASE2
	
	

#ifdef RD_UI_TRANSITION_EFFECTS_POPUPS
	if( GfxTransEffect::IsRegistered(this) && thisIsFocused )
		{
    MakeVisible( EFalse );
    CAknTransitionUtils::MakeVisibleSubComponents( this,
                                        CAknTransitionUtils::EForceInvisible );
		}
#endif

    ActivateL();
    iPopoutCba->ActivateL();

    // this is required here to make code like
    // iList->SetCurrentItemIndex( last item of the list );
    // iPopupList->ExecuteLD();
    // to work as it used to. Without this current item of the
    // list would be topmost item, and there would be unused empty
    // space below that.
    iListBox->UpdateScrollBarsL();
    
#ifdef RD_UI_TRANSITION_EFFECTS_POPUPS
    if(GfxTransEffect::IsRegistered(this) && thisIsFocused )
        {
        CAknTransitionUtils::SetAllParents(this);
#ifdef RD_UI_TRANSITION_EFFECTS_POPUPS
        // sequence support
        GfxTransEffect::NotifyExternalState(EInternalHandleSequence, (const TDesC8*)this);
#endif
        GfxTransEffect::Begin(this, KGfxControlAppearAction);
        GfxTransEffect::NotifyExternalState(ECaptureComponentsBegin, (const TDesC8*)this);
        
        TRect demarcation;
        CAknTransitionUtils::GetDemarcation(CAknTransitionUtils::EPopup, demarcation);
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
#endif        
    
    if (!iAppBroughtForwards)
        {
        iEikonEnv->BringForwards(ETrue);
        iAppBroughtForwards = ETrue;
        AknGlobalPopupPriorityController::ShowPopup(*this, ETrue);
        }

    TBool returnValue;
    iReturn = &returnValue;
    iWait.Start();
    delete this;
    _AKNTRACE_FUNC_EXIT;
    return returnValue;
    }

EXPORT_C void CAknPopupList::FadeBehindPopup(TBool aFade)
    {
    // Real fade state is only set on when the dialog is visible
    if (!IsVisible())
        aFade = EFalse;

	AknGlobalPopupPriorityController::FadeBehindPopup(*this, iPopupFader, *this, aFade);
    }


EXPORT_C TSize CAknPopupList::MinimumSize()
    {
    iListBox->View()->CalcDataWidth();
    TInt minWidth = iListBox->CalcWidthBasedOnRequiredItemWidth(iListBox->View()->DataWidth());
    if (Heading())
        {
        minWidth = Max(minWidth, Heading()->MinimumSize().iWidth);
        }
    TInt minHeight = iListBox->MinimumSize().iHeight;
    if (Heading())
        {
        minHeight += KSpaceBelowTitle + Heading()->MinimumSize().iHeight;
        }
    return TSize(minWidth,minHeight);
    }


EXPORT_C void CAknPopupList::Draw(const TRect& /*aRect*/) const
    {
    _AKNTRACE_FUNC_ENTER;
    CWindowGc& gc = SystemGc();
    gc.Clear();

    AknPopupLayouts::HandleDraw(iEikonEnv, gc, Layout(), iListBox, Heading());
    _AKNTRACE_FUNC_EXIT;
    }

// Get component controls into a table
const TInt KMaxPopupListControls = 6;

static TInt ComponentControls( CEikListBox* aListBox,
    CAknPopupHeadingPane* aHeading, CAknSearchField* aFindBox,
    CCoeControl* aCba,
    CCoeControl* aControls[KMaxPopupListControls] )
    {
    TInt i = 0;
    aControls[i++] = aListBox;
    if (aHeading)
        {
        aControls[i++] = aHeading;
        }
    if (aFindBox)
        {
        aControls[i++] = aFindBox;
        }

    if ( aCba )
        {
        aControls[i++] = aCba;
        }
    
    // In order to support non-window owning scroll bar, it is returned as a
    // component of CAknPopupList. It is also component of CEikListBox. This
    // does not cause any harm. Otherwise drawing would not work as scroll
    // bars are outside of list box rectangle.
    CEikScrollBarFrame* scrollBarFrame = aListBox->ScrollBarFrame();
    if (scrollBarFrame)
        {
        CEikScrollBar* scrollBar = scrollBarFrame->GetScrollBarHandle(
            CEikScrollBar::EVertical);
        if (scrollBar && !scrollBar->OwnsWindow())
            {
            aControls[i++] = scrollBar;
            }
        scrollBar = scrollBarFrame->GetScrollBarHandle(
            CEikScrollBar::EHorizontal);
        if (scrollBar && !scrollBar->OwnsWindow())
            {
            aControls[i++] = scrollBar;
            }
        }
    return i;
    }

EXPORT_C TInt CAknPopupList::CountComponentControls() const
    {
     CCoeControl* controls[KMaxPopupListControls];

     return ComponentControls( iListBox, 
                               Heading(), 
                               FindBox(), 
                               iPopoutCba->ButtonGroup()->AsControl(), 
                               controls );
    }

EXPORT_C CCoeControl* CAknPopupList::ComponentControl(TInt aIndex) const
    {
     CCoeControl* controls[KMaxPopupListControls];

     TInt cnt = ComponentControls( iListBox, 
                                   Heading(), 
                                   FindBox(), 
                                   iPopoutCba->ButtonGroup()->AsControl(),
                                   controls );

     if (aIndex < cnt)
        {
        return controls[aIndex];
        }
    else
        {
        return NULL;
        }
    }

/**
* Processes events from the softkeys. Responds to EAknSoftkeyOk and EAknSoftkeyBack
* to accept or cancel the pop-up.
*
* @param        aCommandId        Event Id from the soft-key
*/
EXPORT_C void CAknPopupList::ProcessCommandL(TInt aCommandId)
    {
    _AKNTRACE_FUNC_ENTER;
    _AKNTRACE("ProcessCommandL: aCommandId=%d", aCommandId);
    // Respond to softkey events
    switch (aCommandId)
        {
        case EAknSoftkeySelect:
        case EAknSoftkeyYes:
        case EAknSoftkeyOk:
        case EAknSoftkeyDone:
            iPopupListExtension->iFlags &= ~EPopupFepStartEvent;
            AttemptExitL(ETrue);
            break;
        case EAknSoftkeyExit:
        case EAknSoftkeyClose:
        case EAknSoftkeyNo:
        case EAknSoftkeyCancel:
        case EAknSoftkeyBack:
            iPopupListExtension->iFlags &= ~EPopupFepStartEvent;
            AttemptExitL(EFalse);
            break;
            // Deal with markable lists
        case EAknSoftkeyMark:
            {
            TInt index = iListBox->CurrentItemIndex();
            iListBox->View()->SelectItemL(index);
            if (iMarkable && iPopoutCba)
                {
                iPopoutCba->SetCommandSetL(R_AVKON_SOFTKEYS_UNMARK_BACK);
                iPopoutCba->DrawNow();
                iCurrentResource = R_AVKON_SOFTKEYS_UNMARK_BACK;
                }
            }
            break;
        case EAknSoftkeyUnmark:
            {
            TInt index = iListBox->CurrentItemIndex();
            iListBox->View()->DeselectItem(index);
            if (iMarkable && iPopoutCba)
                {
                iPopoutCba->SetCommandSetL(R_AVKON_SOFTKEYS_MARK_BACK);
                iPopoutCba->DrawNow();
                iCurrentResource = R_AVKON_SOFTKEYS_MARK_BACK;
                }
            }
            break;
        default:
            break;
        }
    _AKNTRACE_FUNC_EXIT;
    }

/**
* Processes key events from the listbox. Respnds to EEventEnterKeyPressed to accept
* the pop-up.
*
* @param        aListBox        Listbox being observed
* @param        aEventType        Event observed
*/
EXPORT_C void CAknPopupList::HandleListBoxEventL(CEikListBox* aListBox, TListBoxEvent aEventType)
    {
    _AKNTRACE_FUNC_ENTER;
    // Respond to events from listbox
    if (aListBox == iListBox)
        {
        // if left softkey is empty, we do not handle enter key either.
        if (iPopoutCba && iPopoutCba->ButtonGroup())
            if (iPopoutCba->ButtonGroup()->CommandId(0) != 0) // CommandId(0) is left softkey.
                {
                switch ( aEventType )
                    {
                    case MEikListBoxObserver::EEventPenDownOnItem:
                        iPopupListExtension->iItemDraggingActioned = EFalse;
                        break;
                        
                    case MEikListBoxObserver::EEventItemDraggingActioned:
                    case MEikListBoxObserver::EEventPanningStarted:
                    case MEikListBoxObserver::EEventFlickStarted:
                        iPopupListExtension->iItemDraggingActioned = ETrue;
                        break;
                    
                    default:
                        break;
                    }
                
                if ( iPopupListExtension->AcceptListBoxEvent( iListBox, aEventType ) )
                    {
                    // Ok / Enter key pressed, so remove popup
                    AttemptExitL(ETrue);                    
                    }
                }
        }
    _AKNTRACE_FUNC_EXIT;
    }
/**
* Processes state changed events from the listbox.
*
* @param        aControl        Control being observed
* @param        aEventType        Event observed
*/
EXPORT_C void CAknPopupList::HandleControlEventL(CCoeControl* aControl,TCoeEvent aEventType)
    {
    _AKNTRACE_FUNC_ENTER;    
    if (aControl == iListBox)
        {
        if (aEventType == EEventStateChanged)
            {
            TInt index = iListBox->CurrentItemIndex();
            TKeyArrayFix key(0, ECmpTInt);        
            TInt pos;
            TBool unmarked = iListBox->View()->SelectionIndexes()->Find(index, key, pos);
            if (unmarked)
                {
                if (iCurrentResource != R_AVKON_SOFTKEYS_MARK_BACK)
                    {
                    if (iPopoutCba)
                        {
                        iPopoutCba->SetCommandSetL(R_AVKON_SOFTKEYS_MARK_BACK);
                        iPopoutCba->DrawNow();
                        }
                    iCurrentResource = R_AVKON_SOFTKEYS_MARK_BACK;
                    }
                }
            else
                {
                if (iCurrentResource != R_AVKON_SOFTKEYS_UNMARK_BACK)
                    {
                    if (iPopoutCba)
                        {
                        iPopoutCba->SetCommandSetL(R_AVKON_SOFTKEYS_UNMARK_BACK);
                        iPopoutCba->DrawNow();
                        }
                    iCurrentResource = R_AVKON_SOFTKEYS_UNMARK_BACK;
                    }
                }
            }
        }
    _AKNTRACE_FUNC_EXIT;
    }

/**
* Called when the user accepts or cancels the listbox. Default implementation
* sets the return value and exists. If there is no return value it means that
* the construction has failed so we don't care about setting the return value
* anyway.
*
* @param        aAccept        ETrue if the user accepted. EFalse if the user cancelled.
*/
EXPORT_C void CAknPopupList::AttemptExitL(TBool aAccept)
    {
    _AKNTRACE_FUNC_ENTER;
    //EFTG-7HWDP6.
    if( FindBox()
        && !( FindBox()->Editor().AknEdwinFlags() & EAknEditorFlagTouchInputModeOpened )
        && ( iPopupListExtension->iFlags & EPopupLayoutSwitchEvent ) )
        {
        iPopupListExtension->iFlags &= ~EPopupFepStartEvent;
        }

    // if exiting is tried to do when pointer event handling is on, then 
    // do it after pointer event handling is over. 
    if ( (iPopupListExtension->iFlags & EPopupHandlingPointerEvent) && AknLayoutUtils::PenEnabled() )
        {
        // Set flag to correspond correct action. 
        if ( aAccept )
            {            
            iPopupListExtension->iFlags |= EPopupAcceptAfterPointerEvent;
            }
        else 
            {
            iPopupListExtension->iFlags |= EPopupCancelAfterPointerEvent;
            }
        }
    else if( !(iPopupListExtension->iFlags & EPopupFepStartEvent) )
        {  
#ifdef RD_UI_TRANSITION_EFFECTS_POPUPS
        // no transition if accepted
        if( IsVisible() && GfxTransEffect::IsRegistered(this) && !aAccept )
            {
            //If still visible, do a transition to invisible state.
            CAknTransitionUtils::SetAllParents(this);
            GfxTransEffect::Begin(this, KGfxControlDisappearAction);
            GfxTransEffect::NotifyExternalState(ECaptureComponentsBegin, (const TDesC8*)this);

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
        GfxTransEffect::Deregister(this); //Always deregister in destructor.
#endif

        ListBox()->MakeVisible(EFalse);
        CEikScrollBarFrame* sbframe = ListBox()->ScrollBarFrame();
        if ( sbframe && sbframe->VerticalScrollBar() )
            {
            sbframe->VerticalScrollBar()->MakeVisible(EFalse);
            }
        RemoveFindFiltering();
        if (iReturn) //Always not null unless ExecuteLD leaves
            *iReturn = aAccept;
        
        CAknEnv::StopSchedulerWaitWithBusyMessage(iWait);
        }
    _AKNTRACE_FUNC_EXIT;
    }

/** 
* Returns the listbox being used
*
* @return        Listbox contained in the pop-up
*/
EXPORT_C CEikListBox* CAknPopupList::ListBox() const
    {
    return iListBox;
    }


/**
* Cancels the current popup. The popup ExecuteLD will return with EFalse.
*
*/
EXPORT_C void CAknPopupList::CancelPopup()
    {
    _AKNTRACE_FUNC_ENTER;
    // Attempt to cancel. Ignore any error.
    TRAP_IGNORE(AttemptExitL(EFalse));
    _AKNTRACE_FUNC_EXIT;
    }


EXPORT_C void CAknPopupList::SetupWindowLayout(AknPopupLayouts::TAknPopupLayouts aType)
    {
    _AKNTRACE_FUNC_ENTER;
    // A linked list for HandleSizeChanged().
    TAknPopupLayoutsNode list = { 0, EListNode, ListBox() };
    TAknPopupLayoutsNode heading = { &list, EHeadingNode, Heading() };
    TAknPopupLayoutsNode windowOwning = { &heading, EWindowOwningNode, this };
    TAknPopupLayoutsNode findPane = { &windowOwning, EFindBoxNode, FindBox() };
    TAknPopupLayoutsNode *listBegin = &findPane;

    AknPopupLayouts::HandleSizeChanged( Layout(), aType, listBegin);

    // create skin context for popuplist (list itemdrawer uses normal list skinning)
    TRect windowRect(Rect());

    TAknLayoutRect topLeft;
    topLeft.LayoutRect(windowRect, SkinLayout::Popup_windows_skin_placing__frame_general__Line_2());

    TAknLayoutRect bottomRight;
    bottomRight.LayoutRect(windowRect, SkinLayout::Popup_windows_skin_placing__frame_general__Line_5());

    TRect outerRect(topLeft.Rect().iTl, bottomRight.Rect().iBr);
    TRect innerRect(topLeft.Rect().iBr, bottomRight.Rect().iTl);
    
    TInt softkeyHeight( KSoftkeyHeightUndefined );

    if (!iPopupListExtension->iBgContext)
        {
        TRAP_IGNORE( iPopupListExtension->iBgContext = CAknsFrameBackgroundControlContext::NewL(
            KAknsIIDQsnFrPopup, outerRect, innerRect, ETrue ) );
        iPopupListExtension->iBgContext->SetParentPos( PositionRelativeToScreen() );
        iPopupListExtension->iBgContext->SetBitmap(KAknsIIDQsnFrPopupCenter);
        }
    else
        {
        iPopupListExtension->iBgContext->SetFrameRects( outerRect, innerRect );
        iPopupListExtension->iBgContext->SetParentPos( PositionRelativeToScreen() );
        }

    if ( FindBox() )
        {
        TInt headingVariety( 1 );
        
        if ( Heading() )
            {
            headingVariety = 0;
            }
            
        // When softkeys are embedded inside popup we need to move the FindBox
        // upwards by the height of softkeys. There is no layout data available 
        // for embedded version, so we must do it with calculation.
        if ( AknLayoutUtils::PenEnabled() )
            {
            softkeyHeight = SoftkeyRect().Height(); 
            windowRect.Move( 0, -softkeyHeight );            
            }
   
        AknLayoutUtils::LayoutControl( FindBox(), windowRect,
            AknLayoutScalable_Avkon::find_popup_pane_cp2( headingVariety ) );
        }

    if ( AknLayoutUtils::PenEnabled() )
        {
        CEikCba* cba = static_cast<CEikCba*>( iPopoutCba->ButtonGroup() );
            
        if ( !cba->IsEmpty() )
            {
            TRect rect( Rect() );
            
            if ( softkeyHeight == KSoftkeyHeightUndefined )
                {
                softkeyHeight = SoftkeyRect().Height();
                }
                    
            // softkeys are located on bottom of the rect
            cba->SetRect( TRect( rect.iTl.iX,
                rect.iBr.iY - softkeyHeight,
                rect.iBr.iX,
                rect.iBr.iY) );
            }
        }


    // we can safely use FormattedCellData only if normal popup layouts are in use
    switch(iWindowType)
        {
        case AknPopupLayouts::EMenuUnknownColumnWindow:
        case AknPopupLayouts::EMenuUnknownFormattedCellWindow:
            break;
        default:  
            {
            CFormattedCellListBoxData *boxData =
                ((CEikFormattedCellListBox*)ListBox())->ItemDrawer()->FormattedCellData();

            boxData->SetSkinPopupFrame(&KAknsIIDQsnFrPopup,&KAknsIIDQsnFrPopupCenter);
            boxData->SetSkinPopupFramePosition(outerRect,innerRect);
            }
            break;
        }
    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C TAknPopupWindowLayoutDef &CAknPopupList::Layout()
    {
    return iLayout;
    }

EXPORT_C const TAknPopupWindowLayoutDef &CAknPopupList::Layout() const
    {
    return iLayout;
    }

EXPORT_C CEikButtonGroupContainer *CAknPopupList::ButtonGroupContainer()
    {
    return iPopoutCba;
    }

EXPORT_C CAknPopupHeadingPane *CAknPopupList::Heading() const
    {
    return CONST_CAST(CAknPopupList*,this)->Heading();
    }
EXPORT_C CAknPopupHeadingPane *CAknPopupList::Heading()
    {
    // This if statement will remove the heading if
    // the string from resource is "".
    if (iTitle && iTitle->Prompt())
        return iTitle;
    return 0;
    }

EXPORT_C CEikListBox *CAknPopupList::ListBox()
    {
    return iListBox;
    }


EXPORT_C TKeyResponse CAknPopupList::OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)
    {
    _AKNTRACE_FUNC_ENTER;
    /* this must be first check, since window will be faded when fast
    * swap window is visible */
    if (aType==EEventKey && aKeyEvent.iCode == EKeyEscape)
        {
        AttemptExitL(EFalse);
        return EKeyWasConsumed;
        }

    if ( Window().IsFaded() )
        {
        /* this happens, when popuplist has a findbox, and user
        * presses shift to launch fep menu. Fep menu has priority menu
        * in control stack, but we have dialog priority. As result,
        * keyevents will get here first. If we return
        * EKeyWasNotConsumed, fep menu will catch those events
        * next. */
        return EKeyWasNotConsumed;
        }

    TBool needRefresh = EFalse;
    TKeyResponse res = AknFind::HandleFindOfferKeyEventL(aKeyEvent, aType, this, ListBox(), FindBox(), EFalse, needRefresh);

    if (needRefresh && FindBox())
        {
        DrawNow();
        }

    if ( res == EKeyWasConsumed )
        {
        return res;
        }
    
    TKeyResponse response = iListBox->OfferKeyEventL(aKeyEvent, aType);
    _AKNTRACE_FUNC_EXIT;
    return response;
    }

EXPORT_C void CAknPopupList::FocusChanged(TDrawNow aDrawNow)
    {
    if (iListBox)
        iListBox->SetFocus(IsFocused(), aDrawNow);
    if ( FindBox() )
        FindBox()->SetFocus(IsFocused(), aDrawNow);
    }

EXPORT_C TTypeUid::Ptr CAknPopupList::MopSupplyObject(TTypeUid aId)
    {
    if (aId.iUid == CAknPopupList::ETypeId)
        {
        return aId.MakePtr(this);
        }
    if (aId.iUid == MAknsControlContext::ETypeId)
        {
        if (iPopupListExtension && iPopupListExtension->iBgContext)
            {
            return MAknsControlContext::SupplyMopObject(aId, iPopupListExtension->iBgContext);
            }
        else if ( iListBox && 
                  iListBox->View() &&
                  iListBox->View()->ItemDrawer() )
            {
            return aId.MakePtr(iListBox->View()->ItemDrawer()->SkinBackgroundControlContext());
            }
        else
            {
            return TTypeUid::Null();
            }
        }
    if (!iPopoutCba) return CEikBorderedControl::MopSupplyObject(aId);
    return SupplyMopObject(aId, iPopoutCba);
    }

EXPORT_C TInt CAknPopupList::CountFadedComponents()
    {
    return 2;
    }

EXPORT_C CCoeControl* CAknPopupList::FadedComponent(TInt aIndex)
    {
    switch (aIndex)
        {
        case 0:
            return this;

        case 1:
            return iPopoutCba;

        default:
            return NULL;
        }
    }

//----------------------------------------------------------------------------
// CAknPopupList::HandlePointerEventL()
// Handles pointer events Button1Up and Button1Down that happens outside 
// of list rect by closing and canceling selection. 
// Other pointerevents are handled in CEikListbox
//----------------------------------------------------------------------------
//
EXPORT_C void CAknPopupList::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    {
    _AKNTRACE_FUNC_ENTER;
    _AKNTRACE("HandlePointerEventL: aPointerEvent.iPosition=(%d,%d)", 
            aPointerEvent.iPosition.iX, aPointerEvent.iPosition.iY);
    
    if ( AknLayoutUtils::PenEnabled() )
        {
        iPopupListExtension->iFlags |= EPopupHandlingPointerEvent;

        TInt index;
        TBool pointerOnItem = iListBox->View()->XYPosToItemIndex( aPointerEvent.iPosition, index );
        if ( aPointerEvent.iType == TPointerEvent::EButton1Down
                && pointerOnItem )
            {
            iListBox->View()->ItemDrawer()->SetFlags(
                    CListItemDrawer::EPressedDownState );
            }

        CCoeControl::HandlePointerEventL( aPointerEvent );
        
        iPopupListExtension->iFlags &= ~EPopupHandlingPointerEvent;
        
        switch ( aPointerEvent.iType )
            {
            case TPointerEvent::EButton1Up:
                {
                _AKNTRACE("CAknPopupList::HandlePointerEventL: TPointerEvent::EButton1Up");
                TBool accepted(
                        iPopupListExtension->AcceptPointerEvent( iListBox ) );
                
                if ( accepted )
                    {
                    if ( Rect().Contains( aPointerEvent.iPosition )
                            && ( iPopupListExtension->iFlags
                                    & EPopupAcceptAfterPointerEvent ) )
                        {
                        AttemptExitL( ETrue );
                        }
                    else
                        {
                        AttemptExitL( EFalse );
                        }
                    }

                //EFTG-7HWDP6. 
                //If model didn't change from portrait to landscape, 
                //EPopupFepStartEvent should be deleted.
                else if( !(iPopupListExtension->iFlags & EPopupLayoutSwitchEvent) )
                    {
                    iPopupListExtension->iFlags &= ~EPopupFepStartEvent;
                    }
                }
                break;
            case TPointerEvent::EButton1Down:
                _AKNTRACE("CAknPopupList::HandlePointerEventL: TPointerEvent::EButton1Down");
                // as in comments close popup if pointer goes outside of the popup list
                if ( !Rect().Contains( aPointerEvent.iPosition ) )
                    {
                    MTouchFeedback* feedback = MTouchFeedback::Instance();
                    if ( feedback )
                        {
                        feedback->InstantFeedback( ETouchFeedbackPopUp );
                        }
                    AttemptExitL( EFalse );                	
                    }
                else 
                    {
                    if( FindBox() 
                        && ( FindBox()->Editor().Rect().Contains( aPointerEvent.iPosition ) ) 
                        && !( iPopupListExtension->iFlags & EPopupLayoutSwitchEvent ) )
                        {
                        iPopupListExtension->iFlags |= EPopupFepStartEvent;
                        }
                    }
                break;
            case TPointerEvent::EDrag:
                _AKNTRACE("CAknPopupList::HandlePointerEventL: TPointerEvent::EDrag");
                if ( !iListBox->Rect().Contains( aPointerEvent.iPosition ))
                    {
                    iPopupListExtension->iItemDraggingActioned = ETrue;
                    }
            default:
                // do nothing with the rest of the events
                break;
            }
        }
    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C void* CAknPopupList::ExtensionInterface( TUid /*aInterface*/ ) 
    { 
    return NULL;
    }
    
EXPORT_C TBool CAknPopupList::EnableFind(TBool /*aEnable*/)
    {
    if (!iPopupListExtension)
        return EFalse; // no extension class, failed
    if (!iPopupListExtension->iSearchControl)
        {
        CAknSearchField::TSearchFieldStyle flags = CAknSearchField::EPopupWindow;
        TRAPD(err,
              iPopupListExtension->iSearchControl = CAknSearchField::NewL( *this, flags, 0, 40 );
              STATIC_CAST(CAknFilteredTextListBoxModel*,ListBox()->Model())->CreateFilterL(ListBox(),FindBox());
            ); // end TRAP
        if (err != KErrNone) // error in creating findbox, do nothing
            return EFalse;
        
        // Do layout only if visible, otherwise it would be done both here
        // and in ExecuteLD.
        if ( iReturn )
            {
            AknPopupLayouts::TAknPopupLayouts layout =
                AknPopupLayouts::TAknPopupLayouts(EAknPopupLayoutsFind + iWindowType);
            SetupWindowLayout(layout);
            }

        // set layout for fixed find box in popup window - this makes highlights working
        STATIC_CAST(CAknFilteredTextListBoxModel*,ListBox()->Model())->Filter()->SetParentControl(this);
        
        // popup_find_window overlaps listbox, but this doesn't matter because findbox
        // doesn't draw background
        }

    return ETrue;
    }
    
EXPORT_C TBool CAknPopupList::EnableAdaptiveFind(TBool /*aEnable*/)
    {
    if (!iPopupListExtension)
        return EFalse; // no extension class, failed
    if (!iPopupListExtension->iSearchControl)
        {
        CAknSearchField::TSearchFieldStyle flags = CAknSearchField::EPopupAdaptiveSearchWindow;
        TRAPD(err,
              iPopupListExtension->iSearchControl = CAknSearchField::NewL( *this, flags, 0, 40 );
              STATIC_CAST(CAknFilteredTextListBoxModel*,ListBox()->Model())->CreateFilterL(ListBox(),FindBox());
            ); // end TRAP
        if (err != KErrNone) // error in creating findbox, do nothing
            return EFalse;
        
        // Do layout only if visible, otherwise it would be done both here
        // and in ExecuteLD.
        if ( iReturn )
            {
            AknPopupLayouts::TAknPopupLayouts layout =
                AknPopupLayouts::TAknPopupLayouts(EAknPopupLayoutsFind + iWindowType);
            SetupWindowLayout(layout);
            }

        // set layout for fixed find box in popup window - this makes highlights working
        STATIC_CAST(CAknFilteredTextListBoxModel*,ListBox()->Model())->Filter()->SetParentControl(this);
        
        // popup_find_window overlaps listbox, but this doesn't matter because findbox
        // doesn't draw background
        }

    return ETrue;
    }    
    

EXPORT_C CAknSearchField* CAknPopupList::FindBox() const
    {
    if (iPopupListExtension)
        return iPopupListExtension->iSearchControl;
    return NULL;
    }

void CAknPopupList::RemoveFindFiltering()
    {
    if (FindBox())
        { // this removes filtering from popup list so that listboxes state is valid for application to read.
        TInt currentItemIndex = ListBox()->CurrentItemIndex();
        TInt realCurrentItemIndex = currentItemIndex >= 0 ? STATIC_CAST(CAknFilteredTextListBoxModel*,ListBox()->Model())->Filter()->FilteredItemIndex(currentItemIndex) : -1;
        TRAP_IGNORE( FindBox()->SetSearchTextL(_L("")) );
        TRAP_IGNORE( STATIC_CAST(CAknFilteredTextListBoxModel*,ListBox()->Model())->Filter()->HandleOfferkeyEventL() );
        if (realCurrentItemIndex >= 0)
            ListBox()->SetCurrentItemIndex(realCurrentItemIndex);
        }
    }

EXPORT_C void CAknPopupList::HandleResourceChange(TInt aType)
    {
    _AKNTRACE_FUNC_ENTER;
    if( aType == KEikDynamicLayoutVariantSwitch )
        {
        
        //EFTG-7HWDP6. 
        //Tapping Edit'area can arouse the CAknPopupList::HandleResourceChange()
        //when portrait is initial model, and 'Full screen QWERTY keyboard' is default input method.
        //Just then, EPopupLayoutSwitchEvent will be setted once.
        if( ( iPopupListExtension->iFlags & EPopupFepStartEvent ) && 
            !( iPopupListExtension->iFlags & EPopupLayoutSwitchEvent ) )
            {
            iPopupListExtension->iFlags |= EPopupLayoutSwitchEvent;
            }
        else
            {
            iPopupListExtension->iFlags &= ~EPopupFepStartEvent;
            iPopupListExtension->iFlags &= ~EPopupLayoutSwitchEvent;    
            }
        
        iPopoutCba->SetBoundingRect(TRect(iAvkonAppUi->ApplicationRect().Size()));
        CCoeControl::HandleResourceChange(aType);

        if ( FindBox() )
            {
            SetupWindowLayout( AknPopupLayouts::TAknPopupLayouts(EAknPopupLayoutsFind + iWindowType) );
            }
        else
            {
            //ELWG-7KH94H 
            //When layout is changed, CEikListView::ScrollToMakeItemVisible
            //may be called before list box background's area update  
            //occasionally and it will incur flicker. 
            iListBox->View()->SetDisableRedraw( ETrue );
            SetupWindowLayout( iWindowType );
            iListBox->View()->SetDisableRedraw( EFalse );
            }
        }
    else
        {
        CCoeControl::HandleResourceChange(aType);
        }
    // EFLU-7HH5DA. CEikListBox::HandleResourceChange will re-set layout of scrollbar 
    // when skin is changed. So we need to set it back to correct.
    if( aType == KEikMessageColorSchemeChange || aType == KAknsMessageSkinChange )
        {
        if ( FindBox() )
            {
            SetupWindowLayout( AknPopupLayouts::TAknPopupLayouts(EAknPopupLayoutsFind + iWindowType) );
            }
        else
            {
            SetupWindowLayout( iWindowType );
            }
        }
    _AKNTRACE_FUNC_EXIT;
    }
// End of File
