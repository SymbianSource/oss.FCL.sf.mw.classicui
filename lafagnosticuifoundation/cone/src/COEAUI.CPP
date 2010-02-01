// Copyright (c) 1997-2009 Nokia Corporation and/or its subsidiary(-ies).
// All rights reserved.
// This component and the accompanying materials are made available
// under the terms of "Eclipse Public License v1.0"
// which accompanies this distribution, and is available
// at the URL "http://www.eclipse.org/legal/epl-v10.html".
//
// Initial Contributors:
// Nokia Corporation - initial contribution.
//
// Contributors:
//
// Description:
//

#ifdef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <apaidpartner.h>
#include <vwsdefpartner.h>
#endif
#include <coeaui.h>
#include <coecntrl.h>
#include "coepanic.h"
#include <coemain.h>
#include <apgtask.h>
#include "COETLS.H"
#include "COEVWMAN.H"

#define STRICT_INNER_AND_OUTER_CHECKING

const TInt KAppUiControlStackGroupId=0;

//
// class CCoeControlStack
//

struct SStackedControl
	{
	CCoeControl* iControl;
	TInt iPriority;
	TInt iFlags;
	TInt iGroupId;
	};

class CCoeControlStack : public CArrayFixFlat<SStackedControl>
	{
public:
	inline CCoeControlStack() : CArrayFixFlat<SStackedControl>(2) { } // granularity of two
	TKeyResponse OfferKeyL(const TKeyEvent& aKeyEvent,TEventCode aType);
	inline void SetCurrentGroupId(TInt aGroupId) { iCurrentGroupId=aGroupId; };
	TBool IsGroupIdCurrent(TInt aGroupId) const;
public:
	TInt iKeyIndex;
	TInt iCurrentGroupId;
	};

TBool CCoeControlStack::IsGroupIdCurrent(TInt aGroupId) const
	{
	return (aGroupId==KAppUiControlStackGroupId || aGroupId==iCurrentGroupId);
	}

TKeyResponse CCoeControlStack::OfferKeyL(const TKeyEvent& aKeyEvent,TEventCode aType)
	{
	iKeyIndex=0;
	while (iKeyIndex<Count())
		{ // both iKeyIndex and Count() can be changed inside OfferKeyEventL call below
		SStackedControl& stacked=(*this)[iKeyIndex++];
		if (stacked.iFlags&ECoeStackFlagRefusesAllKeys)
			continue;
		if ( !IsGroupIdCurrent(stacked.iGroupId) )
			continue;
		const TInt oldKeyIndex=iKeyIndex;
		const TInt oldCount=Count();
		const TKeyResponse keyResponse=stacked.iControl->OfferKeyEventL(aKeyEvent,aType);
		if (Count()==oldCount)
			iKeyIndex=oldKeyIndex; // doing this means that CCoeControl::OfferKeyEventL implementations can be nested inside one another (which would happen if a control calls CCoeEnv::SimulateKeyEventL from it's OfferKeyEventL)
		if (keyResponse==EKeyWasConsumed)
			return(EKeyWasConsumed);
		}
	return(EKeyWasNotConsumed);
	}


//
// CCoeAppUi::CExtra class definition
//

class CCoeAppUi::CExtra : public CBase
	{
public:
	CCoeAppUi* iOuter; // this pointer does not own anything
	CCoeAppUi* iInner; // this pointer does not own anything
	};

//
// CCoeAppUi class definitions
//

/** C++ constructor. 

To complete construction, call ConstructL(). */
EXPORT_C CCoeAppUi::CCoeAppUi()
	{
	iCoeEnv=TheCoe();
	}

/** The destructor frees all resources owned by the object, 
including the control stack and the view server session. */
EXPORT_C CCoeAppUi::~CCoeAppUi()
	{
	if (iStack)
 		{
		TInt pos=0;
		const TInt count=iStack->Count();
		CCoeControlStack* stack=iStack;
		iStack=NULL;
		while (pos<count)
			{
			SStackedControl& stacked=(*stack)[pos++];
			if (stacked.iFlags&ECoeStackFlagOwnershipTransfered)
				{
				if (iExtra!=NULL)
					{
#if defined(STRICT_INNER_AND_OUTER_CHECKING)
					// we do not need to remove stacked.iControl from outer appUI-s as controls owned by an appUI (which, by this stage, we know is true of stacked.iControl) are *not* propagated to outer appUIs by AddToStackL
					__ASSERT_ALWAYS(iExtra->iInner==NULL, Panic(ECoePanicInnerAppUiNotNull1));
#else
					CCoeAppUi* appUi;
					for (appUi=iExtra->iOuter; appUi!=NULL; appUi=appUi->iExtra->iOuter)
						{
						appUi->DoRemoveFromStack(appUi->iStack,stacked.iControl,ERemoveOnlyIfSharable);
						}
					for (appUi=iExtra->iInner; appUi!=NULL; appUi=appUi->iExtra->iInner)
						{
						appUi->DoRemoveFromStack(appUi->iStack,stacked.iControl,ERemoveOnlyIfSharable);
						}
#endif
					}
				delete(stacked.iControl);
				}
			}
		delete(stack);
		}
	if (iExtra!=NULL)
		{
		CCoeAppUi* outer=iExtra->iOuter;
		CCoeAppUi* inner=iExtra->iInner;
		if (outer!=NULL)
			{
			outer->iExtra->iInner=inner;
			}
#if defined(STRICT_INNER_AND_OUTER_CHECKING)
		__ASSERT_ALWAYS(inner==NULL, Panic(ECoePanicInnerAppUiNotNull2));
#else
		if (inner!=NULL)
			{
			inner->iExtra->iOuter=outer;
			}
#endif
		}

	delete iViewManager;
	delete iExtra;
	}

/** Completes construction of the CCoeAppUi object.

It creates the application's control stack and starts a view server session.

@param aPrevious If non-NULL, ConstructL() transfers ownership of all of the 
controls owned by aPrevious to the new app UI being constructed, adding them 
to the new app UI's control stack. */
EXPORT_C void CCoeAppUi::ConstructL(CCoeAppUi* aPrevious)
	{
	iStack=new(ELeave) CCoeControlStack;
	iViewManager=CCoeViewManager::NewL(*iCoeEnv,*this,aPrevious);
	iExtra=new(ELeave) CExtra;
	iExtra->iOuter=aPrevious;
	if (!aPrevious)
		return;
	aPrevious->iExtra->iInner=this;
	CCoeControlStack* previousStack=aPrevious->iStack;
	TInt pos=0;
	const TInt count=previousStack->Count();
	while (pos<count)
		{
		SStackedControl stacked=(*previousStack)[pos++];
		if (!(stacked.iFlags&ECoeStackFlagSharable))
			continue;
		stacked.iFlags&=(~ECoeStackFlagOwnershipTransfered);
		iStack->AppendL(stacked);
		}
	}

/** Handles events sent to the application by the window server. 

This function is called whenever the window server sends key or pointer events 
or some other special events to the application. It calls one of a number of 
functions, according to the type of event.

For key events, it calls CCoeControl::OfferKeyEventL() for each control 
on the control stack, beginning with the control at the top (position 0) until 
a control consumes it. If no control on the stack consumes the key event, the app UI's  
HandleKeyEventL() is called. Note that CCoeControl::OfferKeyEventL() is not 
called for controls whose ECoeStackFlagRefusesAllKeys flag is set.

For pointer events, CCoeControl::ProcessPointerEventL() is called 
on the control specified in aDestination.

For pointer buffer ready events, ProcessPointerBufferReadyL() is called 
on the control specified in aDestination.

For other events, for instance focus change events, this function 
calls one of the following CCoeAppUi private virtual functions: 

- HandleForegroundEventL()
- HandleSwitchOnEventL()
- HandleSystemEventL()
- HandleScreenDeviceChangedL()
- HandleApplicationSpecificEventL(). 

All these functions have empty implementations in this class, and are implemented by 
derived classes, if required.

@param aEvent A window server event.
@param aDestination The control associated with the event. This is only relevant 
for pointer events.
@see CCoeAppUi::HandleWsEventL() */
EXPORT_C void CCoeAppUi::HandleWsEventL(const TWsEvent& aEvent,CCoeControl* aDestination)
	{
	TInt type=aEvent.Type();
	switch (type)
		{
	case EEventKey:
	case EEventKeyUp:
	case EEventKeyDown:
		if (iStack->OfferKeyL(*aEvent.Key(),(TEventCode)type)==EKeyWasNotConsumed)
			HandleKeyEventL(*aEvent.Key(),(TEventCode)type);
		break;
	case EEventPointer:
		aDestination->ProcessPointerEventL(*aEvent.Pointer());
		break;
	case EEventPointerBufferReady:
		aDestination->ProcessPointerBufferReadyL();
		break;
	case EEventFocusLost:
	case EEventFocusGained:
		{
		TBool foreground=(type==EEventFocusGained);
		if (foreground)
			{
			iCoeEnv->NotifyForegroundObserversOfGainingForeground();
			}
		else
			{
			iCoeEnv->NotifyForegroundObserversOfLosingForeground();
			}
		CCoeControl* topFocusable=TopFocusableControl();
		HandleForegroundEventL(foreground);
		if (!topFocusable)
			SetAndDrawFocus(foreground);
		else if(IsControlOnStack(topFocusable))
			{
			TBool isFocused=topFocusable->IsFocused();
			if ((foreground && !isFocused) || (!foreground && isFocused))
				topFocusable->SetFocus(foreground,EDrawNow);
			}
		break;
		}
	case EEventSwitchOn:
		HandleSwitchOnEventL(aDestination);
		break;
	case EEventUser:
		{
		TApaSystemEvent data(*(TApaSystemEvent*)(aEvent.EventData()));
		// EApaSystemEventSecureShutdown must be sent with event-type EEventPowerMgmt to be valid
		if(data<KApaSystemEventsWithPowerMgmtCapabilityStart || data>KApaSystemEventsWithPowerMgmtCapabilityEnd)
			HandleSystemEventL(aEvent);
		break;
		}
	case EEventPowerMgmt:
		HandleSystemEventL(aEvent);
		break;
	case EEventMessageReady:
		{
		TUid messageUid;
		TPtr8 messageParameters(NULL, 0, 0);
		iCoeEnv->GetMessageNotifyingObserversLC(aEvent.Handle(), messageUid, messageParameters, aEvent);
		CleanupStack::PopAndDestroy(); // stuff left on cleanup-stack by GetMessageNotifyingObserversLC
		}
		break;
	case EEventScreenDeviceChanged:
		HandleScreenDeviceChangedL();
		break;
		
	default:
		if (type>EEventUser)
			{
			HandleApplicationSpecificEventL(type,aEvent);
			iCoeEnv->NotifyResourceObserversOfChangeInResource();
			}
		break;
		}
	}

/**Monitor function for passing all windows events to registered monitor observers for optional inspection
@param aEvent The windows server event that has occured
*/
void CCoeAppUi::MonitorWsEvent(const TWsEvent& aEvent)
	{
	iCoeEnv->NotifyMessageMonitorObserversOfEvent(aEvent);
	}
		
/** Handles key events. 

This function is called by HandleWsEventL() if a key event occurred but 
none of the controls in the app UI's control stack consumed it.

Key events are sent to the application by the window server. A key press generates 
three separate key events in the order EEventKeyDown, EEventKey, and EEventKeyUp. 
Controls and app UIs are usually only interested in EEventKey events. 

This default implementation simply returns EKeyWasNotConsumed. It may need to be 
overridden if the derived app UI needs to handle certain key events itself. For 
example, in some applications, arrow keys may be used to navigate between views. 
In this case, the app UI should override this function to consume the arrow keys.

@param aKeyEvent The key event details, including the key code and any modifiers.
@param aType The type of key event, for instance standard, key up or key down.
@return This indicates whether or not the key event was consumed by the app UI. 

@publishedAll 
@released */
EXPORT_C TKeyResponse CCoeAppUi::HandleKeyEventL(const TKeyEvent& /*aKeyEvent*/,TEventCode /*aType*/)
	{
	return EKeyWasNotConsumed;
	}


/** Handles changes in keyboard focus when the application is brought to the 
foreground, or put into the background.

This function is called from HandleWsEventL() when an EEventFocusLost or 
EEventFocusGained event occurs.

This default implementation is empty.

@param aForeground ETrue if the application is being brought to the 
foreground, EFalse if it is being put into the background. */
EXPORT_C void CCoeAppUi::HandleForegroundEventL(TBool /*aForeground*/)
	{
	}


/** Handles the special switch on event.

This function is called by HandleWsEventL() if the device is switched on. 
This default implementation is empty.

@param aDestination The control associated with the event. */
EXPORT_C void CCoeAppUi::HandleSwitchOnEventL(CCoeControl* /*aDestination*/)
	{
	}


/** Handles system events generated by the window server.

This method should be overridden by the UI layer like @c CEikAppUi but not by individual applications. 
Application events (has a positive value greater than EEventUser) will be sent to 
@c HandleApplicationSpecificEventL.

Unrecognized events should be forwarded to the base class.

@param aEvent The window server event that occurred. */
EXPORT_C void CCoeAppUi::HandleSystemEventL(const TWsEvent& /*aEvent*/)
	{
	}

/** Handles an application-specific event.

This function is called from HandleWsEventL() when the app UI receives a window 
server event that is not in the standard range (in other words, it has a positive value 
greater than EEventUser). 

This default implementation is empty.

@param aType The application-specific event value, greater than EEventUser.
@param aEvent The window server event that occurred. */
EXPORT_C void CCoeAppUi::HandleApplicationSpecificEventL(TInt /*aType*/,const TWsEvent& /*aEvent*/)
	{
	}

/** Handles a change to the application's run-time resources for all controls on 
the app UI's control stack.

These are resources which are shared across the environment, such as colours, fonts or ZoomFactor.

@param aType Specifies a resource type. */
EXPORT_C void CCoeAppUi::HandleStackedControlsResourceChange(TInt aType)
	{
	TInt count=iStack->Count();
	for(TInt i=0;i<count;i++)
		{
		CCoeControl* control = (*iStack)[i].iControl;
		if (control && control->DrawableWindow())
			{
			if(aType == KUidValueCoeZoomChangeEvent)
				{
				TRAP_IGNORE(control->SetZoomFactorL(iCoeEnv->ZoomFactor().ZoomFactor()));//this method calls CCoeControl::HandleResourceChange()
				}
			else
				{
				control->HandleResourceChange(aType);	
				}
			}
		
		// There is a possibility that HandleResourceChange modifies the 
		// number of controls on the stack (by adding or removing controls)
		TInt newCount = iStack->Count();
		if (newCount != count)
			{
			// We must make sure that we update i to ensure that we don't skip
			// any control on the stack
			// 1) If controls have been added then we assume that they already use the correct resources
			//    so there isn't any need to update i no matter at which position they have been inserted
			//    (there is a risk we update them unnecessarily but this shouldn't be a problem)
			// 2) If controls have been removed we need to update i because they could have been removed 
			//    at a position <= i in which case we would skip a few controls if we didn't update i
			//    (as before there is a risk we update some controls twice if the removed controls were
			//    at a position > i).
			i = Max(-1, i + Min(0, newCount - count));   
			count = newCount;
			}
		}
	}

//
// Returns ETrue if aControl is present on this appUi's control stack
//
TBool CCoeAppUi::IsControlOnStack(CCoeControl* aControl) const
	{
	const TInt pos=(iStack? FindPos(iStack,aControl) : KErrNotFound);
	return (pos!=KErrNotFound);
	}
	
//
// Sets the current control stack group id to aGroupId. Only if a stacked control is part of the 
// current group does it play a part in the normal operation of the control stack.
//
// @since App-Framework_6.1
//
void CCoeAppUi::SetCurrentControlStackGroupId(TInt aGroupId)
	{
	iStack->SetCurrentGroupId(aGroupId);
	}


void CCoeAppUi::NotifyFontChange(const CCoeFontProvider& aFontProvider) 
    { 
    const CCoeFontProvider* fontProvider = &aFontProvider; 
    
    if(fontProvider == &iCoeEnv->DefaultFontProvider()) 
            fontProvider = NULL; 
            
    const TInt count = iStack->Count(); 
    for(TInt i = 0; i < count; i++) 
        { 
        CCoeControl* control = (*iStack)[i].iControl; 
        if (control && control->DrawableWindow()) 
            { 
            control->HandleResourceChange(KUidValueCoeFontChangeEvent); 
            control->NotifyFontChange(fontProvider); 
            } 
        } 
    } 
    
/** Notify all CCoeFontProvider's that the global logical-to-pixel mapping has changed in 
	CCoeControlStaticSettings
	
	@internalTechnology
*/
void CCoeAppUi::RefetchPixelMappingL()
	{
	const TInt count = iStack->Count(); 
    for(TInt i = 0; i < count; i++) 
        { 
        CCoeControl* control = (*iStack)[i].iControl; 
        if (control && control->DrawableWindow()) 
            { 
            control->RefetchPixelMappingL(); 
            control->HandleResourceChange(KUidValueCoeFontChangeEvent);
    		control->RequestRelayout(NULL);
            } 
        } 	
	}

/** Returns a list of help contexts appropriate to the current state of the application.

The array is generated from the help contexts for all visible controls on the app UI's 
control stack, and from the app UI itself (via CCoeAppUi::HelpContextL()).

@return A list of pointers to relevant help contexts. */
EXPORT_C CArrayFix<TCoeHelpContext>* CCoeAppUi::AppHelpContextL() const
	{
	CArrayFix<TCoeHelpContext>* contexts=new(ELeave) CArrayFixFlat<TCoeHelpContext>(1);
	CleanupStack::PushL(contexts);
	// walk the control stack for active contexts
	TInt count=iStack->Count();
	for (TInt ii=0;ii<count;ii++)
		{
		SStackedControl stacked=(*iStack)[ii];
		if ( !(iStack->IsGroupIdCurrent(stacked.iGroupId)) )
			continue;
		CCoeControl* ctrl=stacked.iControl;
		if (ctrl->IsVisible())
			{
			TCoeHelpContext help;
			ctrl->GetHelpContext(help);
			if (!help.IsNull())
				contexts->AppendL(help);
			}
		}
	// ...then get any from the appui
	CArrayFix<TCoeHelpContext>* appContexts=HelpContextL();
	if (appContexts)
		{
		CleanupStack::PushL(appContexts);
		count=appContexts->Count();
		for (TInt ii=0;ii<count;ii++)
			contexts->AppendL((*appContexts)[ii]);
		CleanupStack::PopAndDestroy(); // appContexts
		}
	CleanupStack::Pop(); // contexts
	return contexts;
	}


/** Sets the keyboard focus of a control and draws it.

This is called by HandleWsEventL() when it receives a focus change event 
and can also be called when a new control is moved to the top of the control 
stack.

This default implementation is empty. It is intended that an implementation 
should set the value of a focus flag within the control to the value given by 
aFocus. This flag indicates whether or not the control has keyboard focus. 
The function should then draw or change the appearance of the control to indicate 
whether or not it has focus.

@param aFocus ETrue sets the control as having keyboard focus. EFalse sets 
the control as not having keyboard focus. */
EXPORT_C void CCoeAppUi::SetAndDrawFocus(TBool /*aFocus*/)
	{
	}


/** Gets a list of help contexts for the app UI.

This default implementation returns NULL.

@return The array of help contexts. 

@publishedAll
@released  */
EXPORT_C CArrayFix<TCoeHelpContext>* CCoeAppUi::HelpContextL() const
	{
	return NULL;
	}

/** Inserts a control into the app UI's control stack.

Use the other AddToStackL() overload if the app UI uses multiple views.

@param aControl The control to add to the stack.
@param aPriority An optional control stack priority. The default value is 
ECoeStackPriorityDefault. Higher priority controls are offered key events before lower 
priority controls.
@param aStackingFlags The control's event handling behaviour. 
The possible values are defined in coeaui.h, beginning with ECoeStackFlagStandard. */
EXPORT_C void CCoeAppUi::AddToStackL(CCoeControl* aControl,TInt aPriority,TInt aStackingFlags)
	{
	DoAddToStackL(iStack,aControl,aPriority,aStackingFlags);
	if (aStackingFlags&ECoeStackFlagSharable)
		{
		const TBool ownershipTransfered=(aStackingFlags&ECoeStackFlagOwnershipTransfered);
		aStackingFlags&=(~ECoeStackFlagOwnershipTransfered);
#if defined(STRICT_INNER_AND_OUTER_CHECKING)
		if (!ownershipTransfered)
#endif
			{
			for (CCoeAppUi* appUi=iExtra->iOuter; appUi!=NULL; appUi=appUi->iExtra->iOuter)
				{
				appUi->DoAddToStackL(appUi->iStack,aControl,aPriority,aStackingFlags);
				}
			}
#if defined(STRICT_INNER_AND_OUTER_CHECKING)
		__ASSERT_ALWAYS(iExtra->iInner==NULL, Panic(ECoePanicInnerAppUiNotNull3));
#else
		for (CCoeAppUi* appUi=iExtra->iInner; appUi!=NULL; appUi=appUi->iExtra->iInner)
			{
			appUi->DoAddToStackL(appUi->iStack,aControl,aPriority,aStackingFlags);
			}
#endif
		}
	}

/** Removes a control from the app UI's control stack.

This function also handles any focus changes that may occur.

@param aControl The control to remove from the stack. */
EXPORT_C void CCoeAppUi::RemoveFromStack(CCoeControl* aControl)
	{
	DoRemoveFromStack(iStack,aControl);
	CCoeAppUi* appUi;
	if (iExtra)
		{
		for (appUi=iExtra->iOuter; appUi!=NULL; appUi=appUi->iExtra->iOuter)
			{
			appUi->DoRemoveFromStack(appUi->iStack,aControl,ERemoveUnconditionally);
			}
#if !defined(STRICT_INNER_AND_OUTER_CHECKING)
		for (appUi=iExtra->iInner; appUi!=NULL; appUi=appUi->iExtra->iInner)
			{
			appUi->DoRemoveFromStack(appUi->iStack,aControl,ERemoveUnconditionally);
			}
#endif
		}
	}

/** Handles changes to the control stack.

This function ensures that the focusable control with the highest priority 
on the control stack has keyboard focus.

It may need to be called when a control's flag values are modified, by calling 
UpdateStackedControlFlags(). It is called automatically when a control is added 
to or removed from the stack. */
EXPORT_C void CCoeAppUi::HandleStackChanged()
	{
	CCoeControl* toFocus=TopFocusableControl();
	CCoeControl* focused=TopFocusedControl();
	if (toFocus!=focused)
		{
		SetFocusToControl(focused,EFalse);
		SetFocusToControl(toFocus,ETrue);
		}
	else if (!toFocus)
		SetAndDrawFocus(ETrue);
	}

/** Tests whether the application is displaying a control between the given control 
stack priorities. 

@param aLowerPriority Lower bound.
@param aHigherPriority Upper bound.
@return ETrue if the application is currently displaying a control 
which has a control stack priority between (but not including) 
aLowerPriority and aHigherPriority. EFalse if not. */
EXPORT_C TBool CCoeAppUi::IsDisplayingControlBetweenPriorities(TInt aLowerPriority, TInt aHigherPriority) const
	{
	TBool ret=EFalse;
	const TInt count=iStack->Count();
	for (TInt ii=0; ii<count; ii++)
		{
		SStackedControl sC=(*iStack)[ii];
		if ( !(iStack->IsGroupIdCurrent(sC.iGroupId)) )
			continue;
		if (sC.iPriority>aLowerPriority && sC.iPriority<aHigherPriority)
			{
			if (sC.iControl->IsVisible())
				{
				ret=ETrue;
				break;
				}
			}
		}
	return ret;
	}

/** Tests whether the application is displaying a menu bar or dialog.

@return ETrue if the application is currently displaying a menu bar or a dialog. 
EFalse if not. */
EXPORT_C TBool CCoeAppUi::IsDisplayingMenuOrDialog() const
	{
	return IsDisplayingControlBetweenPriorities(ECoeStackPriorityMenu-1, ECoeStackPriorityCba) ||
		   IsDisplayingControlBetweenPriorities(ECoeStackPriorityCba, ECoeStackPriorityAlert+1);
	}

/** Tests whether the application is displaying a dialog.

@return ETrue if the application is currently displaying a dialog. 
EFalse if not. */
EXPORT_C TBool CCoeAppUi::IsDisplayingDialog() const
	{
	return IsDisplayingControlBetweenPriorities(ECoeStackPriorityDialog-1, ECoeStackPriorityCba) ||
		   IsDisplayingControlBetweenPriorities(ECoeStackPriorityCba, ECoeStackPriorityAlert+1);
	}

/** Returns the input capabilities of the control with focus.

Classes that override CCoeAppUi::HandleKeyEventL() should also override this 
virtual function. The TCoeInputCapabilities object returned should have 
attributes that match the behaviour of the HandleKeyEventL() function. 

Overriding app UIs should do a base-call and "merge" 
the returned input capabilities with its own input capabilities. If the overriding 
InputCapabilities() function needs to get the input capabilities of any top-level 
control, it should do so by calling CCoeControl::RecursivelyMergedInputCapabilities() 
on that control.

@return The types of input which can be consumed by the focussed control. */
EXPORT_C TCoeInputCapabilities CCoeAppUi::InputCapabilities() const
	{
	// this only traverses the top focused control and its component-controls - should it go down the control-stack?
	TCoeInputCapabilities inputCapabilities(TCoeInputCapabilities::ENone);
	CCoeControl* topFocusedControl=TopFocusedControl();
	if (topFocusedControl!=NULL)
		{
		topFocusedControl->RecursivelyMergeInputCapabilities(inputCapabilities);
		}
	return inputCapabilities;
	}

void CCoeAppUi::SetFocusToControl(CCoeControl* aControl,TBool aFocus)
	{
	if (aControl)
		aControl->SetFocus(aFocus,EDrawNow);
	else
		SetAndDrawFocus(aFocus);
	}

/** Returns the top control of this appui which currently has the focus.

@return Returns the top control of this AppUi which currently has the focus. If none of the 
controls has focus it returns NULL.

@internalTechnology */
EXPORT_C CCoeControl* CCoeAppUi::TopFocusedControl() const
	{
	if (iStack)
		{
		TInt pos=0;
		const TInt count=iStack->Count();
		while (pos<count)
			{
			SStackedControl stacked=(*iStack)[pos++];
			if ( !(iStack->IsGroupIdCurrent(stacked.iGroupId)) )
				continue;
			CCoeControl* const control=stacked.iControl;
			if (control->IsFocused())
				return(control);
			}
		}

	return(NULL);
	}

CCoeControl* CCoeAppUi::TopFocusableControl() const
	{
	TInt pos=0;
	const TInt count=iStack->Count();
	while (pos<count)
		{
		SStackedControl& stacked=(*iStack)[pos++];
		if ( !(iStack->IsGroupIdCurrent(stacked.iGroupId)) )
			continue;
		if (!(stacked.iFlags&ECoeStackFlagRefusesFocus))
			return(stacked.iControl);
		}

	return(NULL);
	}

TInt CCoeAppUi::FindPos(CCoeControlStack* aStack,CCoeControl* aControl) const
	{
	TInt pos=0;
	const TInt count=aStack->Count();
	FOREVER
		{
		if (pos==count)
			return(KErrNotFound);
		if ((*aStack)[pos].iControl==aControl)
			break;
		pos++;
		}
	return(pos);
	}

/** Updates the flag values for a control on the control stack.

The mask defines which flags are modified, while aFlags defines the values they 
are set to.

@param aControl The control to update.
@param aFlags Contains the required value for each of the flag bits whose bit 
is set in aMask.
@param aMask Contains a set bit for each flag bit to modify.
@panic CONE 4 The specified control is not on the stack. */
EXPORT_C void CCoeAppUi::UpdateStackedControlFlags(CCoeControl* aControl,TInt aFlags,TInt aMask)
	{
	DoUpdateStackedControlFlags(iStack,aControl,aFlags,aMask);
	}

void CCoeAppUi::DoAddToStackL(CCoeControlStack* aStack,CCoeControl* aControl,TInt aPriority,TInt aStackingFlags)
	{
	if (IsControlOnStack(aControl))
		return;
	
	DoAddToStackL(aStack,aControl,aPriority,aStackingFlags,KAppUiControlStackGroupId);
	}

void CCoeAppUi::DoAddToStackL(CCoeControlStack* aStack,CCoeControl* aControl,TInt aPriority,TInt aStackingFlags,TInt aGroupId)
	{
	SStackedControl newStacked;
	newStacked.iControl=aControl;
	newStacked.iPriority=aPriority;
	newStacked.iFlags=aStackingFlags;
	newStacked.iGroupId=aGroupId;
	TInt pos=0;
	const TInt count=aStack->Count();
	while (pos<count)
		{
		if (aPriority>=(*aStack)[pos].iPriority)
			break;
		pos++;
		}
	aStack->InsertL(pos,newStacked);
	if (pos<aStack->iKeyIndex)
		aStack->iKeyIndex++;
	HandleStackChanged();
	}

void CCoeAppUi::DoRemoveFromStack(CCoeControlStack* aStack,CCoeControl* aControl,TRemoveCondition aRemoveCondition)
	{
	if (!aStack)
		return; // whole stack in process of destruction
	TInt pos=FindPos(aStack,aControl);
	if (pos>=0)
		{
		SStackedControl stacked=(*aStack)[pos];
		if ((aRemoveCondition!=ERemoveOnlyIfSharable) || (stacked.iFlags&ECoeStackFlagSharable))
			{
			aStack->Delete(pos);
			if (stacked.iFlags&ECoeStackFlagOwnershipTransfered)
				delete stacked.iControl;
			if (pos<aStack->iKeyIndex)
				aStack->iKeyIndex--;
			HandleStackChanged();
			}
		}
	}

void CCoeAppUi::DoUpdateStackedControlFlags(CCoeControlStack* aStack,CCoeControl* aControl,TInt aFlags,TInt aMask)
	{
	TInt pos=FindPos(aStack,aControl);
	if (pos<0)
		Panic(ECoePanicNoSuchControlInStack);
	SStackedControl& stacked=(*aStack)[pos];
	stacked.iFlags&=(~aMask);
	stacked.iFlags|=(aFlags&aMask);
	if ((stacked.iFlags&(ECoeStackFlagRefusesAllKeys|ECoeStackFlagRefusesFocus))==(ECoeStackFlagRefusesAllKeys|ECoeStackFlagRefusesFocus))
		return; // else promote control to start of section of equi-priority controls
	TInt startPos=pos;
	while (startPos--)
		{
		if ((*aStack)[startPos].iPriority!=stacked.iPriority)
			break;
		}
	if (++startPos==pos)
		return;
	SStackedControl copy=stacked;
	aStack->Delete(pos);
	TRAP_IGNORE(aStack->InsertL(startPos,copy)); // bound to succeed
	}

/** Activates an application view. 

A leave occurs if view activation fails.

@param aViewId Identifier of the view to activate. */
EXPORT_C void CCoeAppUi::ActivateViewL(const TVwsViewId& aViewId)
	{
	iViewManager->ActivateViewL(aViewId);
	}

/** Activates an application view and passes a message to it.

A leave occurs if view activation fails.

Notes:

Activation works synchronously so that in general, this method returns when 
the view is activated.

An application defines and publishes the message UIDs that it recognises. 
For example, a contacts application might activate an email editor view, passing 
an email address as a custom message. To do this, the contacts application 
must use a message UID, and descriptor encoding that the email application 
has published as being recognisable.

@param aViewId Identifies the view to activate.
@param aCustomMessageId Specifies the message type.
@param aCustomMessage The message to pass to the activated view. */
EXPORT_C void CCoeAppUi::ActivateViewL(const TVwsViewId& aViewId,TUid aCustomMessageId,const TDesC8& aCustomMessage)
	{
	iViewManager->ActivateViewL(aViewId,aCustomMessageId,aCustomMessage);
	}


/** Activates the top view for this app UI. 

This is the most recently active view, if any. Otherwise, it activates the default view.
If there is no default view, it activates the first registered view.

@publishedPartner
@released */
EXPORT_C void CCoeAppUi::ActivateTopViewL()
	{
	iViewManager->ActivateTopViewL();
	}

/** Checks whether the view-server client that initiated the current view-switch matches the security-policy given in the parameter.

This function leaves with KErrUnknown if called outside of an implementation of MCoeView's ViewConstructL or of MCoeView's ViewActivatedL.

@see TSecurityPolicy

@param aSecurityPolicy The TSecurityPolicy object which the client that initiated the current view switch must match.
@param aDiagnostic A string that will be emitted along with any diagnostic message
							that may be issued if the policy check fails.
							This string should be enclosed in the __PLATSEC_DIAGNOSTIC_STRING macro
							which enables it to be easily removed from the system.
@return EFalse (zero) if the security-policy does not match the client that initiated the current view switch, other-wise returns "true", i.e. a non-zero value. */
EXPORT_C TBool CCoeAppUi::CheckSourceOfViewSwitchL(const TSecurityPolicy& aSecurityPolicy,const char* aDiagnostic/*=NULL*/) const
	{
	return iViewManager->CheckSourceOfViewSwitchL(aSecurityPolicy,aDiagnostic);
	}

/** Deactivates the active view. 

Deactivating the active view is necessary before exiting if the app UI has an active view.
In most cases, DeactivateActiveViewIfOwnerMatch should be used instead of this function.

@publishedAll
@released 
@see DeactivateActiveViewIfOwnerMatch */

EXPORT_C void CCoeAppUi::DeactivateActiveViewL()
	{
	iViewManager->DeactivateActiveViewL();
	}
/** Deactivates the active view if the current view is owned by this application.
 
 Deactivating the active view is necessary before exiting if the app UI has an active view.
 This function is called by the UI framework during application closure.
 
 @publishedAll
 @released */
EXPORT_C void CCoeAppUi::DeactivateActiveViewIfOwnerMatchL()
	{
	iViewManager->DeactivateActiveViewIfOwnerMatchL();
	}
 

/** Gets the ID of the app UI's currently active view. 

@param aViewId On return, contains the ID of the currently active view. This is 
unchanged if there is no active view.
@return KErrNone if this app UI has an active view, KErrNotFound if it does not. */
EXPORT_C TInt CCoeAppUi::GetActiveViewId(TVwsViewId& aViewId) const
	{
	return iViewManager->GetActiveViewId(aViewId);
	}


/** 
@publishedPartner
@deprecated
*/
EXPORT_C void CCoeAppUi::RegisterViewAndAddStackL(MCoeView& aView)
	{
	iViewManager->RegisterViewL(aView);
	}

/** Registers a view with the view server.

All views should be registered in the app UI's ConstructL().

@param aView The view to be registered. */
EXPORT_C void CCoeAppUi::RegisterViewL(MCoeView& aView)
	{
	iViewManager->RegisterViewL(aView);
	}


/** Registers a pseudo-view for the application identified by aAppUid.

The view server is notified that a view exists for the application, which 
allows it to participate in the view switching mechanism, even though it does 
not implement any views.

Activating the application view means bringing the application into the foreground.

@param aAppUid The ID of the application for which a view should be registered.
@publishedAll
@released */
EXPORT_C void CCoeAppUi::RegisterApplicationViewL(TUid aAppUid)
	{
	iViewManager->RegisterApplicationViewL(aAppUid);
	}

/** Deregisters the application view from the view architecture.

@publishedAll
@released */
EXPORT_C void CCoeAppUi::DeregisterApplicationView()
	{
	if (iViewManager)
		{
		iViewManager->DeregisterApplicationView();
		}
	}

/** Sets one of the app UI's views as the default. 

The default view should be constructed, drawn, registered and set as the 
default as early as possible in the app UI's ConstructL() function. 

The meaning of the default view varies depending on the UI. It is normally 
the view that is displayed when the application is launched. It may also 
be the view that is displayed when the application is brought to the 
foreground.

@param aView The view to set as the default. */
EXPORT_C void CCoeAppUi::SetDefaultViewL(const MCoeView& aView)
	{
	iViewManager->SetDefaultViewL(aView);
	}


/** Sets the application view to be the default view. 

In debug builds, this panics if no application view has been added for this app UI.

@internalTechnology */
EXPORT_C void CCoeAppUi::SetApplicationViewAsDefaultL()
	{
	iViewManager->SetApplicationViewAsDefaultL();
	}

/** Ensures that at least one view is registered for the app UI. 

It adds an application view as the default if no views have been added,
so that the application can participate in the view switching mechanism. 
It also sets a default view if none has been set. 

This is called by the UI framework during application construction.

@param aAppUid The application's 3rd UID.
@publishedPartner
@released */
EXPORT_C void CCoeAppUi::CheckInitializeViewsL(TUid aAppUid)
	{
	iViewManager->CheckInitializeViewsL(aAppUid);
	}

/** Gets this app UI's default view ID.

@param aViewId On return, contains the ID of the app UI's default view.
This is unchanged if there is no default view.
@return KErrNone if this app UI has a default view, KErrNotFound if 
it doesn't.*/
EXPORT_C TInt CCoeAppUi::GetDefaultViewId(TVwsViewId& aViewId) const
	{
	return iViewManager->GetDefaultViewId(aViewId);
	}


/**
@publishedPartner
@deprecated
*/
EXPORT_C void CCoeAppUi::DeregisterViewAndRemoveStack(const MCoeView& aView)
	{
	if (iViewManager)
		{
		iViewManager->DeregisterView(aView);
		}
	}

/** Deregisters a view. 

All views must be deregistered before the application exits. This is
usually done in the app UI's destructor.

It has no effect if the specified view does not exist.

@param aView The view to be deregistered. */
EXPORT_C void CCoeAppUi::DeregisterView(const MCoeView& aView)
	{
	if (iViewManager)
		{
		iViewManager->DeregisterView(aView);
		}
	}

/** Inserts a control into the app UI's control stack.

@param aView The view that contains the control.
@param aControl The control to add to the stack. This may itself be a view.
@param aPriority An optional control stack priority. The default value is 
ECoeStackPriorityDefault. Higher priority controls are offered key events before lower 
priority controls. 
@param aStackingFlags The control's event handling behaviour. 
The possible values are defined in coeaui.h, beginning with ECoeStackFlagStandard. */
EXPORT_C void CCoeAppUi::AddToStackL(const MCoeView& aView,CCoeControl* aControl,TInt aPriority,TInt aStackingFlags)
	{
	DoAddToStackL(iStack,aControl,aPriority,aStackingFlags,aView.ViewId().iViewUid.iUid);
	}


/**
@publishedAll 
@deprecated
*/
EXPORT_C void CCoeAppUi::AddToViewStackL(const MCoeView& aView,CCoeControl* aControl,TInt aPriority,TInt aStackingFlags)
	{
	DoAddToStackL(iStack,aControl,aPriority,aStackingFlags,aView.ViewId().iViewUid.iUid);
	}


/**
@publishedAll 
@deprecated
*/
EXPORT_C void CCoeAppUi::RemoveFromViewStack(const MCoeView& /*aView*/,CCoeControl* aControl)
	{
	DoRemoveFromStack(iStack,aControl);
	}


/**
@internalTechnology
@deprecated
*/
EXPORT_C void CCoeAppUi::UpdateViewStackedControlFlags(const MCoeView& /*aView*/,CCoeControl* aControl,TInt aFlags,TInt aMask)
	{
	DoUpdateStackedControlFlags(iStack,aControl,aFlags,aMask);
	}

/** Adds an observer to the list of observers to be notified of view deactivations.

All view deactivation observers that have been added to the app UI are notified 
via their HandleViewDeactivation() function when any of this app UI's views are 
deactivated.

@param aViewDeactivationObserver The observer to add.
@publishedAll 
@released */
EXPORT_C void CCoeAppUi::AddViewDeactivationObserverL(MCoeViewDeactivationObserver* aViewDeactivationObserver)
	{
	iViewManager->AddViewDeactivationObserverL(aViewDeactivationObserver);
	}


/** Removes an observer from the list to be notified of view deactivations.

This has no effect if the observer is not found in the list.

@param aViewDeactivationObserver The observer to remove.
@publishedAll 
@released */
EXPORT_C void CCoeAppUi::RemoveViewDeactivationObserver(MCoeViewDeactivationObserver* aViewDeactivationObserver)
	{
	if (iViewManager)
		{
		iViewManager->RemoveViewDeactivationObserver(aViewDeactivationObserver);
		}
	}


/** Requests that the next deactivation of the view identified by aViewId be notified to 
the specified view deactivation observer. 

The request is cleared after the notification: the observer can only be notified once,
and this app UI can have no more than one such request pending.

@param aViewId The view to be observed. This can any view registered with the view server.
@param aViewDeactivationObserver The observer to be notified.
@panic CONE 39 In debug builds, there was already a request pending when this 
function was called.
@publishedAll 
@released */
EXPORT_C void CCoeAppUi::NotifyNextDeactivation(const TVwsViewId& aViewId, MCoeViewDeactivationObserver& aViewDeactivationObserver)
	{
	iViewManager->NotifyNextDeactivation(aViewId,aViewDeactivationObserver);
	}


/** Requests that the next deactivation of any view registered with the view server 
be notified to the specified view deactivation observer.

The request is cleared after the notification: the observer can only be notified once,
and this app UI can have no more than one such request pending. 

@param aViewDeactivationObserver The observer to be notified.
@panic CONE 39 In debug builds, there was already a request pending when this 
function was called.
@publishedAll 
@released */
EXPORT_C void CCoeAppUi::NotifyNextDeactivation(MCoeViewDeactivationObserver& aViewDeactivationObserver)
	{
	iViewManager->NotifyNextDeactivation(aViewDeactivationObserver);
	}


/** Adds an observer to the list of observers to be notified of view activations.

All view activation observers that have been added to the app UI are notified 
via their HandleViewActivation() function when any of this app UI's views are 
activated.

@param aViewActivationObserver The observer to add.
@publishedPartner
@released */
EXPORT_C void CCoeAppUi::AddViewActivationObserverL(MCoeViewActivationObserver* aViewActivationObserver)
	{
	iViewManager->AddViewActivationObserverL(aViewActivationObserver);
	}


/** Removes the specified observer from the list to be notified of view 
activations.

@param aViewActivationObserver The observer to remove.
@panic CONE 38 The observer was not found.
@publishedPartner
@released */
EXPORT_C void CCoeAppUi::RemoveViewActivationObserver(MCoeViewActivationObserver* aViewActivationObserver)
	{
	iViewManager->RemoveViewActivationObserver(aViewActivationObserver);
	}


/** Requests that the next activation of the view identified by aViewId be notified to the 
specified view activation observer. 

The request is cleared after the notification: the observer can only be notified once,
and there can be no more than one such request pending. 

@param aViewId The view to be notified about. This can any view registered with the view server.
@param aViewActivationObserver The observer to be notified.
@panic CONE 39 In debug builds, there was already a request pending when this 
function was called.
@publishedPartner
@released */
EXPORT_C void CCoeAppUi::NotifyNextActivation(const TVwsViewId& aViewId, MCoeViewActivationObserver& aViewActivationObserver)
	{
	iViewManager->NotifyNextActivation(aViewId,aViewActivationObserver);
	}


/** Requests that the next activation of any view registered with the view server 
be notified to the specified observer.

The request is cleared after the notification: the observer can only be notified once,
and there can be no more than one such pending request. 

@param aViewActivationObserver The observer to be notified.
@panic CONE 39 In debug builds, there was already a request pending when this 
function was called.
@publishedPartner 
@released */
EXPORT_C void CCoeAppUi::NotifyNextActivation(MCoeViewActivationObserver& aViewActivationObserver)
	{
	iViewManager->NotifyNextActivation(aViewActivationObserver);
	}


/** Sends a request to the view server to activate the specified view, 
and returns without waiting for the request to complete.

Note that this method may return without error but the activation may subsequently fail. 

@param aViewId Identifies the view to activate.
@param aCustomMessageId The message type.
@param aCustomMessage The message to pass to the activated view.
@publishedPartner 
@released */
EXPORT_C void CCoeAppUi::CreateActivateViewEventL(const TVwsViewId& aViewId,TUid aCustomMessageId,const TDesC8& aCustomMessage)
	{
	iViewManager->CreateActivateViewEventL(aViewId,aCustomMessageId,aCustomMessage);
	}


/** Adds the specified observer to the list of view observers.

All view observers added using this function are notified via their 
HandleViewEventL() function when the app UI receives any view activation 
or deactivation event. 

@param aViewObserver The observer to be added to the list.
@publishedPartner
@released */
EXPORT_C void CCoeAppUi::AddViewObserverL(MCoeViewObserver* aViewObserver)
	{
	iViewManager->AddViewObserverL(aViewObserver);
	}

/** Removes the specified observer from the list of view observers.

This has no effect if the specified observer is not found in the list.

@param aViewObserver The view observer to be removed from the list.
@publishedPartner 
@released */
EXPORT_C void CCoeAppUi::RemoveViewObserver(MCoeViewObserver* aViewObserver)
	{
	iViewManager->RemoveViewObserver(aViewObserver);
	}

/** Enables/disables external view switches for this instance of this application

By default external view switches are enabled.
@param aEnable Whether external view switches should be enabled or not.
@publishedPartner
@released
@return KErrNone if successful, otherwise one of the system-wide error codes. */
EXPORT_C TInt CCoeAppUi::EnableExternalViewSwitches(TBool aEnable)
	{
	return iViewManager->EnableExternalViewSwitches(aEnable);
	}

EXPORT_C void CCoeAppUi::HandleScreenDeviceChangedL()
	{
	}

/** Indicates the default behaviour for synchronizing to the startup (usually SystemStarter).

@publishedPartner 
@released
@return ETrue. Meaning the framework will synchronize the application to the starter.
        Derived classes may override this and return EFalse if they wish to perform 
        the synchronization themselves. ie RProcess::Rendezvous( KErrNone )*/
EXPORT_C TBool  CCoeAppUi::FrameworkCallsRendezvous() const
	{
	return ETrue;
   	}

/** @internalComponent */   	
EXPORT_C void CCoeAppUi::CCoeAppUi_Reserved_2()
	{
	}

/** Performs pre-exit processing on the control environment.

This function is called after the control environment's active scheduler 
exits, but before the control environment (i.e. the CCoeEnv object) is destroyed. 
The default implementation is empty, and this function is not implemented 
by CCoeAppUi, but it may be implemented by derived 
classes to perform pre-exit processing on the control environment. */
EXPORT_C void CCoeAppUi::PrepareToExit()
	{
	}

/**
@publishedPartner
@released
*/
EXPORT_C void CCoeAppUi::SetSystemDefaultViewL(const TVwsViewId& aViewId,TInt aMode)
	{
	iViewManager->SetSystemDefaultViewL(aViewId, aMode);
	}

/**
@publishedPartner
@released
*/
EXPORT_C void CCoeAppUi::SetSystemDefaultViewL(const TVwsViewId& aViewId)
	{
	iViewManager->SetSystemDefaultViewL(aViewId);
	}

/**
@internalTechnology
*/
EXPORT_C void CCoeAppUi::GetSystemDefaultViewL(TVwsViewId& aViewId)
	{
	iViewManager->GetSystemDefaultViewL(aViewId);
	}

#ifdef _DEBUG
/** Writes the internal state of all CCoeControls on the control stack into aWriteStream.
Works in debug builds only.

@internalTechnology */
EXPORT_C void CCoeAppUi::WriteInternalStateOfStackedControlsL(RWriteStream& aWriteStream) const
	{
	const TInt count=iStack->Count();
	for(TInt ii=0;ii<count;ii++)
		{
		(*iStack)[ii].iControl->WriteInternalStateNowL(aWriteStream);
		}
	}
#else
EXPORT_C void CCoeAppUi::WriteInternalStateOfStackedControlsL(RWriteStream&) const
	{}
#endif

/** Checks if the view has been constructed or not.
@param aViewId The id of the view
@return ETrue if the view has been constructed, EFalse otherwise.
*/
EXPORT_C TBool CCoeAppUi::IsViewConstructed(const TVwsViewId& aViewId) const
	{
	return iViewManager->IsViewConstructed(aViewId);
	}

/** Allows customised control of Window Group ordinal position during view activations
@param aCustomControl Non-zero if Customised Control is switched on.
@publishedPartner
*/
EXPORT_C void CCoeAppUi::SetCustomControl(TInt aCustomControl)
	{
	iViewManager->SetCustomControl(aCustomControl);
	}

/** Finds and returns the current top view, not necessarily the currently active view
@param aViewId On return, contains the ID of the current top view. This is 
unchanged if there is no top view.
@return KErrNone if the top view could be found, KErrNotFound if it could not.
@publishedPartner
*/
EXPORT_C TInt CCoeAppUi::GetTopViewId(TVwsViewId& aViewId) const
	{
	return iViewManager->GetTopViewId(aViewId);
	}

/** Changes the default window group ordinal position used when bringing views to the foreground. Only used
if CCoeAppUi::SetCustomControl has been called with a positive value.
@param aWindowGroupOrdinal The customised window group ordinal position.
@publishedPartner
*/
EXPORT_C void CCoeAppUi::SetWindowGroupOrdinal(TInt aWindowGroupOrdinal)
	{
	iViewManager->SetWindowGroupOrdinal(aWindowGroupOrdinal);
	}

/** Changes the default background color for the View Server screen blanking window
@param aBgColor The new background color to be used.
@publishedPartner
*/
EXPORT_C void CCoeAppUi::UpdateViewServerBackgroundColor(const TRgb& aBgColor)
	{
	iViewManager->UpdateViewServerBackgroundColor(aBgColor);
	}
