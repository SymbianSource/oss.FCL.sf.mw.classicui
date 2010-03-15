// Copyright (c) 1997-2010 Nokia Corporation and/or its subsidiary(-ies).
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

#include <coecntrl.h>
#include <coecntss.h>
#include <coeccntx.h>
#include <coemain.h>
#include <coeaui.h>
#include "COETLS.H"
#include "coepanic.h"
#include <coeinput.h>
#include <coedef.h>
#include <coefontprovider.h>
#include <coefont.h>
#include <coelayoutman.h>
#include <hal.h>
#include "CoeDynamicStorage.inl"
#include "coedefkeys.h"


//
// class CCoeControl
//

enum
	{
	ECoeCntrlUnused1					=0x00000001,
	EWindowIsSemiTransparent			=0x00000002,	// Indicated that the window has been set to make use of the alpha channel
	EOwnsWindow						 	=0x00000004,	// Signals that the control is window-owning
	EFocused							=0x00000008,	// Control has focus
	EActivated						  	=0x00000010,	// Control has been activated (thus ready to draw if visible)
	EInvisible						  	=0x00000020,	// Control is currently invisible
	EDimmed								=0x00000040,	// Control is currently dimmed (unavailable to the user)
	ESpareEnumReUseMe					=0x00000080,	// Was EGrabbed, now available for re-use
	EBackedUpWindow					 	=0x00000100,	// 
	ENonFocusing						=0x00000200,	// 
	EAllowStrayPointers					=0x00000400,	// Unless set, pointer up and drag events will be ignored unless 
														// there's been a pointer down event in the control previously
	ECanDrawOutsideRect					=0x00000800,	// 
	EBlank								=0x00001000,	// 
	ECapturesPointer					=0x00002000,	// 
	EIgnoresFirstExternalPointerUp		=0x00004000,	// For resolving problem with new windows being created on pointer down
	EIgnoresEventsUntilNextPointerUp	=0x00008000,	// For ignoring drag and up events after the user has pressed Esc
	EComponentsInheritVisibility		=0x00010000,	// 
	EGloballyCapturing					=0x00020000,	// 
	EIsBeingDestroyed					=0x00040000,	// 
	EMemoryAllocationFailed				=0x00080000,	// 
	ENotifyFocusObserversOnDestruction	=0x00100000, 	// This flag is needed as if CCoeControl::SetFocus needs to call 
														// CCoeControlExtension::SetFocusObserverNotificationIdentifier 
														// but can't because it can't create the CCoeControlExtension object
	EReportControlStateChange			=0x00200000		// This flag is used to control the ReportControlStateChange
	};

class CCoeControlStorage
	{
public:
	inline CCoeControlStorage();
	inline RCoeDynamicDataStorage& DynamicDataStorage();
	inline const RCoeDynamicDataStorage& DynamicDataStorage() const;
	inline TInt Open();
	inline void Close();
	inline void AttemptCompress();
	void SetPointerGrab(TUint aSet, TUint aClear);
	TUint8& PointerGrab();

private:
	RCoeDynamicDataStorage iDynamicDataStorage;
	TUint8 iPointerGrabFlags; // The grab-status of each of the supported pointers
	};

void CCoeControlStorage::SetPointerGrab(TUint aSet, TUint aClear)
	{
	ASSERT(aSet != aClear);
	
	iPointerGrabFlags &= ~aClear;
	iPointerGrabFlags |= aSet;
	}

TUint8& CCoeControlStorage::PointerGrab()
	{
	return iPointerGrabFlags;
	}

inline CCoeControlStorage::CCoeControlStorage()
: iDynamicDataStorage(), iPointerGrabFlags(0)  
	{}

inline RCoeDynamicDataStorage& CCoeControlStorage::DynamicDataStorage()
	{ return iDynamicDataStorage; }

inline const RCoeDynamicDataStorage& CCoeControlStorage::DynamicDataStorage() const
	{ return iDynamicDataStorage; }

inline TInt CCoeControlStorage::Open()
	{ return iDynamicDataStorage.Open(); }

inline void CCoeControlStorage::Close()
	{ iDynamicDataStorage.Close(); }

inline void CCoeControlStorage::AttemptCompress()
	{ iDynamicDataStorage.AttemptCompress(); }

EXPORT_C CCoeControl::CCoeControl()
/** Default C++ constructor. 

Initialises the CCoeControl base class.

Note: CCoeControl is normally used as a base class from which concrete 
control classes are derived. However, it can also be instantiated as a concrete 
class. */
	{
	Constructor(TheCoe());
	}

EXPORT_C CCoeControl::CCoeControl(CCoeEnv* aCoeEnv)
/** C++ constructor. 

Initialises the CCoeControl base class.

Note: CCoeControl is normally used as a base class from which concrete 
control classes are derived. However, it can also be instantiated as a concrete 
class. 

@param aCoeEnv The control environment.*/
	{
	Constructor(aCoeEnv);
	}

void CCoeControl::Constructor(CCoeEnv* aCoeEnv)
	{
	iCoeEnv = aCoeEnv;

	iData = new CCoeControlStorage;		// Non-leaving allocation
	if (!iData || iData->Open()!=KErrNone)
		iFlags |= EMemoryAllocationFailed;	// Handle OOM later

	SetFocusing(CCoeControlStaticSettings::FocusedByDefault(iCoeEnv));
	}

EXPORT_C CCoeControl::~CCoeControl()
/** Destructor. 

It destroys the window owned by the control, if it is a window-owning control.

In debug builds, this checks if the control still exists 
on the control stack and raises a CONE 44 panic if it is. An application 
must remove every control that it has added to the stack. */
	{
#if defined(_DEBUG)
	CCoeAppUi* appUi=static_cast<CCoeAppUi*>(iCoeEnv->AppUi());
	if (appUi && appUi->IsControlOnStack(this))
		Panic(ECoePanicControlNotRemovedFromStack);
#endif
	iFlags |= EIsBeingDestroyed;
	if ((iFlags&EFocused) || (iFlags&ENotifyFocusObserversOnDestruction)  && iCoeEnv->FocusObserverNotificationIsStillPending(DoGetFocusObserverNotificationIdentifier(iData->DynamicDataStorage())))
		iCoeEnv->NotifyFocusObserversOfDestructionOfFocusedItem();
	
	// The CCoeControlArray d'tor calls delete on components
	// which are not owned externally.
	delete DoGetComponentArray(iData->DynamicDataStorage());
		
	if (OwnsWindow())
		CloseWindow();
	
	MCoeLayoutManager* layoutMan = LayoutManager();
	if (layoutMan)
		layoutMan->Detach(*this);
	
	delete DoGetColorOverrides(iData->DynamicDataStorage());
	delete DoGetZoomWithType(iData->DynamicDataStorage());

	if(iData)
		iData->Close();
	delete iData;
	}
	
/**@return ETrue if the component array exists, EFalse otherwise
*/	
EXPORT_C TBool CCoeControl::ComponentArrayExists() const
    {
    CCoeControlArray* array = DoGetComponentArray(iData->DynamicDataStorage());
    return (array != NULL);
    }



EXPORT_C TBool CCoeControl::IsFocused() const
/** Tests if the control has focus. 

Focus is set and unset using SetFocus().

@return ETrue if the control has focus, EFalse if it doesn't. */
	{
	return (iFlags&EFocused);
	}

EXPORT_C TBool CCoeControl::IsVisible() const
/** Tests if the control is visible.

Unless MakeVisible() has been called with argument EFalse, the control is 
visible.

@return ETrue if the control is visible, EFalse if it is invisible. */
	{
	return (!(iFlags&EInvisible));
	}

EXPORT_C TBool CCoeControl::IsDimmed() const
/** Tests if the control is dimmed.

This function returns the value of a flag within the control which is set 
and unset using SetDimmed().

@return ETrue if the control is dimmed, EFalse if it is not dimmed. */
	{
	return (iFlags&EDimmed);
	}

EXPORT_C RDrawableWindow* CCoeControl::DrawableWindow() const
/** Gets the control's associated drawable window. 

The control must be a window-owning control. 

This function should be called if it is not known whether the window is of 
type RWindow or RBackedUpWindow. RDrawableWindow is an abstract base class 
from which RWindow and RBackedUpWindow are derived.

@return The control's associated window.
@see Window() */
	{
	return iWin;
	}

EXPORT_C TSize CCoeControl::Size() const
/** Gets the control's size.

@return The control's size, in pixels. */
	{
	return iSize;
	}
	
 
EXPORT_C TInt CCoeControl::MaximumWidth() const
/** Gets the control's maximum width

@return The controls maximum width. (0 if no value set). */
	{
	// Try to retrieve a maximum width value if one has been set, otherwise return zero.
	return DoGetMaximumWidth(iData->DynamicDataStorage());
	}


EXPORT_C TPoint CCoeControl::Position() const
/** Gets the control's position.

@return The position of the control, relative to its associated window. */
	{
	return iPosition;
	}

EXPORT_C TPoint CCoeControl::PositionRelativeToScreen() const
/** Gets the control's position relative to screen origin. 

The screen origin is its top-left corner.

@return The position of the control, measured in pixels, relative to the screen 
origin. */
	{
	TPoint ret=iWin->InquireOffset(iCoeEnv->RootWin());
	if (!OwnsWindow())
		ret+=iPosition;
	
	return ret;
	}

EXPORT_C void CCoeControl::SetObserver(MCoeControlObserver* aObserver)
/** Sets the control's observer.

@param aObserver The observer. */
	{
	if(DoSetObserver(iData->DynamicDataStorage(), aObserver) == KErrNoMemory)	
		iFlags |= EMemoryAllocationFailed;
	}

EXPORT_C MCoeControlObserver* CCoeControl::Observer() const
/** Gets the control's observer.

@return The control's observer. */
	{
	return DoGetObserver(iData->DynamicDataStorage());
	}

EXPORT_C TBool CCoeControl::IsReadyToDraw() const
/** Tests if the control is ready for drawing. 

This returns true if the control has been activated and is visible.

@return ETrue if the control is ready for drawing, EFalse if it is not ready 
for drawing. */
	{
	return ((iFlags&(EInvisible|EActivated))==(EActivated)) || (iFlags&EBackedUpWindow);
	}

EXPORT_C TBool CCoeControl::OwnsWindow() const
/** Tests if the control is window-owning.

@return ETrue if the control is window-owning. EFalse if the control is non-window-owning. */
	{
	return (iFlags&EOwnsWindow);
	}

EXPORT_C TBool CCoeControl::IsBackedUp() const
/** Tests if the window owned by the control is a backed-up window.

@return ETrue if the window owned by this control is a backed-up window. EFalse 
if it is not a backed-up window.
@deprecated
*/
	{
	return (iFlags&EBackedUpWindow);
	}

EXPORT_C TBool CCoeControl::IsActivated() const
/** Tests if the control has been activated. 

A control is not ready to draw until it is activated.

@return ETrue if the control is activated, EFalse if it is not activated. */
	{
	return (iFlags&EActivated);
	}

EXPORT_C TBool CCoeControl::IsBlank() const
/** Tests if the control is blank. 

This simply gets the value of the flag set by SetBlank().

@return ETrue if SetBlank() has been called on the control. EFalse if SetBank() 
has not been called on the control. */
	{
	return (iFlags&EBlank);
	}

EXPORT_C TBool CCoeControl::IsBeingDestroyed() const
/** Tests if the control is being destroyed.

@return ETrue if the control is being destroyed, otherwise EFalse. */
	{
	return (iFlags&EIsBeingDestroyed);
	}

/**
 @param aPointerNumber The pointer number. Defaulted to zero in the declaration.
*/
TBool CCoeControl::IsGrabbed(TInt aPointerNumber) const
	{
	ASSERT( ((aPointerNumber < KConeMaxSupportedPointers) && (aPointerNumber >= 0)) );
	
	return ( iData->PointerGrab() & (1 << aPointerNumber) );
	}

EXPORT_C TKeyResponse CCoeControl::OfferKeyEventL(const TKeyEvent& /*aKeyEvent*/,TEventCode /*aType*/)
/** Handles key events.

If a control wishes to process key events, it should implement this function. 
The implementation must ensure that the function returns EKeyWasNotConsumed 
if it does not do anything in response to a key event, otherwise, other 
controls or dialogs may be prevented from receiving the key event. If it is 
able to process the event it should return EKeyWasConsumed.

When a key event occurs, the control framework calls this function for each 
control on the control stack, until one of them can process the key event 
(and returns EKeyWasConsumed).

Each keyboard key press results in three separate events: EEventKeyDown, EEventKey, 
and EEventKeyUp, in that order. 

To receive key events, which can be processed by this function, the application 
should call CCoeAppUi::AddToStackL() to add the control to the stack. This 
only applies, however, to controls which are not components of a compound 
control. Compound controls should pass key events to their components as necessary: 
the components themselves do not go on the stack.

Classes that override CCoeControl::OfferKeyEventL() should also override the 
InputCapabilities() virtual function, returning a TCoeInputCapabilities object 
whose attributes correspond to the behaviour of the OfferKeyEventL() function. 
Note that it is not necessary to call InputCapabilities() on any component 
controls from inside a class' InputCapabilities() function. This is done 
automatically by the UI Control Framework.

If overriding OfferKeyEventL(), the implementation must include a base call to CCoeControl's
OfferKeyEventL().

@param aKeyEvent The key event.
@param aType The type of key event: EEventKey, EEventKeyUp or EEventKeyDown.
@return Indicates whether or not the key event was used by this control. */
	{
	return(EKeyWasNotConsumed);
	}

void CCoeControl::ProcessPointerBufferReadyL()
	{
	CCoeControl* destination=NULL;
	for (TInt i=0; i<CountComponentControls(); i++)
		{
		CCoeControl* ctrl=ComponentControl(i);
		if (ctrl->IsGrabbed() && !(ctrl->OwnsWindow()))
			destination=ctrl;
		}
	if (destination)
		destination->ProcessPointerBufferReadyL();
	else
		HandlePointerBufferReadyL();
	}

EXPORT_C void CCoeControl::HandlePointerBufferReadyL()
/** Handles pointer buffer ready events.

This function is called whenever the control receives an event of type EEventPointerBufferReady, 
unless one of its component controls has grabbed the pointer, in which case 
the function is called on that control. An event of type EEventPointerBufferReady 
will only be received if the pointer move buffer has been set up using window 
server functions. 

The pointer move buffer is typically used when the application requires a 
continuous stream of pointer drag events, such as in a drawing application.

@see RWindowBase::AllocPointerMoveBuffer() */
	{
	}

EXPORT_C void CCoeControl::ClaimPointerGrab(TBool aSendUpEvent)
/** Claims the pointer-grab from another control. 

This ensures that all subsequent pointer events are delivered to it and not 
to the control that originally owned the grab.

The function allows a control to claim the pointer grab only if the pointer 
is already grabbed by another control.

This method is to be used in systems implementing single-pointer events. Or in systems 
implementing multiple-pointer events but where this control's window has single-pointer 
emulation enabled.

@param aSendUpEvent Passed as the argument to RWindowBase::ClaimPointerGrab().
@see RWindowBase::ClaimPointerGrab() */
	{
	iFlags |= EAllowStrayPointers|EIgnoresFirstExternalPointerUp;	// EIgnoresFirstExternalPointerUp reset in ProcessPointerEventL()
	iWin->SetPointerGrab(ETrue);
	iWin->ClaimPointerGrab(aSendUpEvent);

	ControlClaimPointerGrab(TAdvancedPointerEvent::EDefaultPointerNumber);	
	}

EXPORT_C TInt CCoeControl::ClaimPointerGrab( TInt aPointerNumber, TBool aSendUpEvent )
/** Claims pointer grab from another control.

This ensures that all subsequent pointer events of the specified pointer are delivered 
to it and not to the control that originally owned the grab.

The function allows a control to claim the pointer grab only if the pointer 
is already grabbed by another control.

This method is intended to be called on a control who's window implements multi-pointer events.
If called on a window without multiple pointers enabled, wserv will ignore the pointer 
number and grab the emulated pointer. 

@param aSendUpEvent Passed as the argument to RWindowBase::ClaimPointerGrab().
@param aPointerNumber The number of the pointer for which to claim the grab.
@return KErrNone if successful, KErrNotFound if pointer number out of range (Panics in debug build), or KErrNotSupported if incorrect pointer grab claimed for window in emulation mode.
@see RWindowBase::ClaimPointerGrab() 
@see RWindowBase::EnableMMultiplePointers() */
	{ 
	__ASSERT_DEBUG( ((aPointerNumber < ControlEnv()->SupportedPointers()) && (aPointerNumber >= 0)), Panic(ECoePanicNoSuchNumberedPointer) );
	
	iFlags |= EAllowStrayPointers|EIgnoresFirstExternalPointerUp;	// EIgnoresFirstExternalPointerUp reset in ProcessPointerEventL()
	iWin->SetPointerGrab(ETrue);
	TInt errNo = iWin->ClaimPointerGrab(aPointerNumber, aSendUpEvent);
	if(KErrNone == errNo)
		{
		ControlClaimPointerGrab(aPointerNumber);
		}
	return errNo;
	}

void CCoeControl::ControlClaimPointerGrab(TInt aPointerNumber)
	{
	// Without this code, claiming pointer grab only work between 
	// window owning controls, not between controls in the same window 
	const CCoeControl* parent = WindowOwningParent(); 
	
	if(parent)
		{
		CCoeControl* ctrl = parent->GrabbingComponent( aPointerNumber );
		
		if(ctrl)
			{
			ctrl->SetGrabbed(EFalse, aPointerNumber);
			}
		}
		
	SetGrabbed(ETrue, aPointerNumber);		
	}

EXPORT_C void CCoeControl::IgnoreEventsUntilNextPointerUp()
/** Sets the control to ignore pointer events until the next pointer up.

This means that all events until and including the next pointer up event are 
discarded and are not processed. 

This can be used for example if the user presses the Esc key while selecting
text by dragging the pointer device to ensure that further dragging does not
result in continued selection.
*/
	{
	iFlags|=EIgnoresEventsUntilNextPointerUp;
	}

void CCoeControl::ProcessPointerEventL(const TPointerEvent& aPointerEvent)
	{
	TBool requiresFocus = EFalse;
	TInt pointerNumber = TAdvancedPointerEvent::EDefaultPointerNumber;
	
	if (aPointerEvent.IsAdvancedPointerEvent())
		{
		User::LeaveIfError(ValidateAdvancedPointerNumber(aPointerEvent));
		pointerNumber = aPointerEvent.AdvancedPointerEvent()->PointerNumber(); 
		}

	if (aPointerEvent.iType==TPointerEvent::EButton1Down)
		{
		// If this is a window owning control with a hit-test object attached....
		if(OwnsWindow())
			{
			// ...then if the hit-test fails, try passing the event up to the next level...
			const MCoeControlHitTest* hitTest = HitTest();
			if(hitTest && !hitTest->HitRegionContains(aPointerEvent.iPosition, *this))
				{
				// ...i.e. up to the next window owning parent, thus allowing even window owning controls 
				// to be transparent to pointer events.
				CCoeControl* windowOwningParent = Parent()->WindowOwningParent();	// safe even if not parent exists
				if(windowOwningParent)
					{
					windowOwningParent->ProcessPointerEventL(aPointerEvent);
					return;	// Don't continue in this part of the control tree
					}
				}
			}	
	
		SetGrabbed(EFalse, pointerNumber);	// Reset the grabbing
		if (!IsVisible())	
			return;
		
		if (IsDimmed())
			{
			ReportEventL(MCoeControlObserver::EEventInteractionRefused);
			return;
			}
			
		// If the control does not aleady have focus (but can take focus)
		// then generate a prepare-focus-transition event now, and a 
		// request-focus event once the pointer event has been handled 
		// (see end of this function)
		if (!IsFocused() && !IsNonFocusing())
			{
			ReportEventL(MCoeControlObserver::EEventPrepareFocusTransition);
			requiresFocus = ETrue;
			}
			
		SetGrabbed(ETrue, pointerNumber);	// Set the control grabbing any further pointer events.
											// This ensures that the control that got the pointer down also gets the
											// pointer up event (and any drag events).
		}
	else	// Mainly EButton1Up or EDrag. Other events will be ignored unless stray events are allowed (see below)
		{
		if ( IsGrabbed(pointerNumber) )	// If there's been a EButton1Down event...
			{				
			if (aPointerEvent.iType==TPointerEvent::EButton1Up)	// ...and this is the matching EButton1Up event...
				SetGrabbed(EFalse, pointerNumber);				// ...then terminate the grabbing state.
			}
		else	// If no EButton1Down event has been recorded; then either this is it, or it's a stray event.
			{
			if ( !(iFlags&EAllowStrayPointers) && !(aPointerEvent.iModifiers & EModifierAdvancedPointerEvent) )  
				return;			// Ignore stray events unless explicitly allowed
			
//mm something's fishy here...			
			// The code that follows intends to resolve the problem that occurs when a pointer tap 
			// (down-up event) on a menu item results in a sub-menu being opened and that sub-menu 
			// appears "under" the pointer. In these cases the up-event must not invoke the menu item 
			// in the sub-menu that happens to be located at the coordinate of the event.
			
			// If the pointer grab has been claimed (by calling ClaimPointerGrab())
			if (iFlags&EIgnoresFirstExternalPointerUp)	
				{
				// If the pointer event occured inside this control (and not in the "sub-menu")...
				if (Rect().Contains(aPointerEvent.iPosition))
					iFlags &= ~EIgnoresFirstExternalPointerUp;	// ...then no need to ignore the pointer up event.
				else
					{
					if (aPointerEvent.iType==TPointerEvent::EButton1Up)	// If the event was the pointer-up...
						iFlags &= ~EIgnoresFirstExternalPointerUp;		// ...then reset the flag...
			
					return;												// ...and ignore the event.
					}
				}
			}
		}
	
	// If flag is set, ignore all pointer events until the next pointer up.
	// See doxygen comments for IgnoreEventsUntilNextPointerUp().
	if (iFlags&EIgnoresEventsUntilNextPointerUp)
		{
		if (aPointerEvent.iType==TPointerEvent::EButton1Up)	// Reset the flag on the first pointer up
			iFlags&=(~EIgnoresEventsUntilNextPointerUp);
	
		return;	// Ignore the event
		}
	
	HandlePointerEventL(aPointerEvent);
	
	// If there was a pointer down event on a non-focused control, then generate a request-focus event.
	if (requiresFocus)
		ReportEventL(MCoeControlObserver::EEventRequestFocus);
	}


/** Handles pointer events.

This function gets called whenever a pointer event occurs in the control, 
i.e. when the pointer is within the control's extent, or when the control has 
grabbed the pointer. The control should implement this function to handle 
pointer events.

Note: events of type EButton1Down are processed before HandlePointerEventL() is 
called, in order to transfer keyboard focus to the control in which the EButton1Down 
event occurred.

If overriding HandlePointerEventL(), the implementation must include a base call to CCoeControl's
HandlePointerEventL().

The TPointerEvent& parameter aPointerEvent can be safely transformed into a TAdvancedPointerEvent
at all times by deploying the following code:-

const TAdvancedPointerEvent* advancedPointerEvent = aPointerEvent.AdvancedPointerEvent();
@see TPointerEvent
@see TAdvancedPointerEvent

The TAdvancedPointerEvent methods supply safe and meaningful values even in systems not 
implementing advanced pointers.

@param aPointerEvent The pointer event. */
EXPORT_C void CCoeControl::HandlePointerEventL(const TPointerEvent& aPointerEvent)
	{
	// The code below will traverse down the control hierarchy, effectively offer the pointer
	// event to all controls intersecting the pointer event coordinate, from the window-owning 
	// parent down to the furthest child node.

	// Offers the pointer down (and move) events to component controls in the order from the window-owning 
	// parent and down throught the control tree. Other events always go the the control that got the down event.
	CCoeControl* pointerRecipient = NULL;
	if (aPointerEvent.iType==TPointerEvent::EButton1Down 
						  || aPointerEvent.iType==TPointerEvent::EMove
						  || aPointerEvent.iType==TPointerEvent::EEnterCloseProximity
						  || aPointerEvent.iType==TPointerEvent::EExitCloseProximity
						  || aPointerEvent.iType==TPointerEvent::EOutOfRange) 
		{		
		// For all children...
		const TInt count = CountComponentControls();
		for (TInt ii=count-1; ii>=0; ii--)
			{
			CCoeControl* ctrl = ComponentControl(ii);
			// ...ignoring any window-owning children (as they would have got the event directly from the WServ 
			// if they intersect the pointer coordinate) and any invisible children...
			if (ctrl->OwnsWindow() || !(ctrl->IsVisible()))
				continue;
			
			// ...if the child intersects the pointer coordinate...
			if(ctrl->Rect().Contains(aPointerEvent.iPosition))
				{
				// ...check if the child has a hit-test object attached, and if it has then only progress down 
				// its branch if the test succeeded (this way controls that are partly transparent won't react
				// to pointer events outside their visible area)...
				const MCoeControlHitTest* childHitTest = ctrl->HitTest();
				if(childHitTest && !childHitTest->HitRegionContains(aPointerEvent.iPosition, *ctrl)) // If the test failed...
					continue;	// ...then offer the event to next sibling (two partly transparent siblings may overlap!)
				
				pointerRecipient = ctrl;
				break;
				}	
			}
		}
	else 
		{
		// Always offer all events except down- and move-events to the grabbing control (that got the original down event)
		TInt pointerNum = aPointerEvent.IsAdvancedPointerEvent() ? aPointerEvent.AdvancedPointerEvent()->PointerNumber() : TAdvancedPointerEvent::EDefaultPointerNumber;
		pointerRecipient = GrabbingComponent(pointerNum);
		}
	
	// Pass the pointer event on to the child found to intersect the pointer event coordintate
	// (or that got the original pointer down event)
	if (pointerRecipient)
		pointerRecipient->ProcessPointerEventL(aPointerEvent);
	}

EXPORT_C void CCoeControl::ReportEventL(MCoeControlObserver::TCoeEvent aEvent)
/** Sends an event to the control's observer (if the control has one).

@param aEvent The event type. */
	{
	MCoeControlObserver* observer = DoGetObserver(iData->DynamicDataStorage());
	if (observer)
		observer->HandleControlEventL(this,aEvent);
	}

EXPORT_C void CCoeControl::PrepareForFocusLossL()
/** Prepares the control for loss of focus. 

A control which is displayed within a dialog should implement this function 
if it wishes to validate data entered into the control.

This function is called by the dialog framework immediately before it removes 
keyboard focus from a control within a dialog. It is intended to be used for 
validating the state of the control: for example, if the control allows the 
user to enter a date, PrepareForFocusLossL() would normally check to make 
sure the user did not enter an invalid date such as February 31st. If an invalid 
state is detected, PrepareForFocusLossL() should leave and issue a message 
to the user if appropriate. If it does leave, the framework does not perform 
the action that would have resulted in the control losing focus, and focus 
remains with the control to allow valid data to be entered.

In standard GUI dialogs, various actions can result in a control losing focus, 
for instance if the user presses the OK button or the Enter key to close the dialog 
and enter the information, or if the user navigates away from 
the focussed control. These actions result in PrepareForFocusLossL() being 
called on the control that currently has keyboard focus.

The default implementation of this function is empty, and it is not called 
from within the UI control framework. The function exists only to provide 
an interface to the control, for the GUI and any other UI library. */
	{
	}

EXPORT_C void CCoeControl::PrepareForFocusGainL()
/** Prepares the control for gaining focus.

Implementations may by taking any action required, such as updating control 
information. The default implementation is empty. */
	{
	}

EXPORT_C void CCoeControl::SetAdjacent(TInt /*aAdjacent*/)
/** Sets the control's appearance when it is next to other controls. 

Its intended use is to remove the double border that may occur if two controls, 
both with borders, are adjacent within a container control.

This function has an empty default implementation, and is not used within 
the UI control framework. However, it may be implemented and used by derived 
control classes. 

@param aAdjacent Typically a value defined in TGulAdjacent. */
	{
	}

EXPORT_C void CCoeControl::SetNeighbor(CCoeControl* /*aNeighbor*/)
/** Sets an associated control. 

This can be used to establish co-ordinated groups of controls for instance in dialogs 
without specific application co-operation.

This function has an empty default implementation, and is not used within 
the UI control framework. However, it may be implemented and used by derived 
control classes.

@param aNeighbor A control to be used by this function. */
	{
	}

EXPORT_C TBool CCoeControl::HasBorder() const
/** Tests if the control has a border.

When component controls are arranged in a container, the container control 
may need to know whether or not the components have borders, as this may affect 
the way the components are laid out within the container.

The default implementation of this function returns EFalse, but can 
be overridden to provide the required functionality.

@return ETrue if the control has a border, EFalse if the control does not 
have a border. The default implementation of this function returns 
EFalse. */
	{
	return EFalse;
	}

EXPORT_C TSize CCoeControl::MinimumSize()
/** Sets the control's minimum required size.

This function should be overridden by the concrete control class if the control 
is to be displayed inside a dialog. Standard GUI dialogs set the size and 
position of their components automatically, and use this function to enquire 
the minimum size that a control requires.

Other container controls that automatically calculate the layout of their 
components may also use this function.

@return The minimum size required by the control. */
	{ 
	// designed to be overridden
	MCoeLayoutManager* layoutManager = LayoutManager();
	if (layoutManager)
		{
		return layoutManager->CalcMinimumSize(*this);
		}
		
	return(iSize);
	}
	

EXPORT_C void CCoeControl::HandleComponentControlsResourceChange(TInt aType)
/** Handles a change to the resources in the components of a compound control.

@param aType A message UID value.
@see HandleResourceChange() */
	{
	const TInt count=CountComponentControls();
	for(TInt ii=0;ii<count;ii++)
		{
		CCoeControl* control = ComponentControl(ii);
		if (control && control->iWin)
			{
			control->HandleResourceChange(aType);
			}
		}
	}

/** Sets a pointer to a MCoeControlBackground object that is responsible for
drawing the control's background

@param aBackground Pointer to an object that implements MCoeControlBackground
@see CCoeControl::EnableWindowTransparency()
@publishedAll
@released
*/
EXPORT_C void CCoeControl::SetBackground(const MCoeControlBackground* aBackground)
	{
	if(DoSetBackground(iData->DynamicDataStorage(), aBackground) == KErrNoMemory)
		iFlags |= EMemoryAllocationFailed;
	}

/**
By default, all windows are opaque. This means that semi-transparent drawing 
performed into the window will blend with other content of that window, but not
with the content of the window(s) behind. This acts as an important performance 
optimization, limiting the amount of drawing needed to update the screen.

Call this method to allow semi-transparent drawing into the window to be blended
with the content of the windows behind. (Because of the performance implications, 
be careful not to enable window transparency unless really required.)

This will set the window to use the alpha channel information of the drawing 
performed into it, and set the initialize window background to fully transparent
(before any drawing is made into it).

Note that although the same effect can be achieved by calling the RWindow methods
directly, calling this method instead will allow correct drawing of semi-transparent
control backgrounds (see MCoeControlBackground).

This method must only be called on (non-BackedUp) window owning controls.

@see MCoeControlBackground
@publishedAll
*/

EXPORT_C void CCoeControl::EnableWindowTransparency()
	{
    __ASSERT_DEBUG(OwnsWindow(), Panic(ECoePanicControlNotWindowOwning));
    __ASSERT_DEBUG(!(iFlags&EBackedUpWindow), Panic(ECoePanicControlWindowIsBackedUp));

    RWindow& win = Window();
    win.SetTransparencyAlphaChannel();
    win.SetBackgroundColor(~0);
    iFlags |= EWindowIsSemiTransparent;
    }


/** Set the zoom factor for this control.

@param aZoomFactor Amount of zoom (multiplied by 1000)
@param aZoomType Absolute or relative (EAbsoluteZoom or ERelativeZoom)
@publishedAll
@released
*/
EXPORT_C void CCoeControl::SetZoomFactorL(TInt aZoomFactor, TZoomType aZoomType)
    {
    TCoeZoomWithType* zoom = GetZoomWithType();
    if(!zoom)
        {
        zoom = new (ELeave) TCoeZoomWithType;
        CleanupStack::PushL(zoom);
        User::LeaveIfError(SetZoomWithType(zoom));
        CleanupStack::Pop();
        }

    zoom->iZoomFactor = aZoomFactor;
    zoom->iZoomType = aZoomType;

    HandleResourceChange(KUidValueCoeZoomChangeEvent);
    RequestRelayout(this);
    }

/** Set the font provider. This is an external object that takes the responsibililty
for finding an appropriate font away from the control.

@param aFontProvider The provider to use.
@publishedAll
@released
*/
EXPORT_C void CCoeControl::SetFontProviderL(const CCoeFontProvider& aFontProvider)
    {
    User::LeaveIfError(SetFontProvider(&aFontProvider));

    HandleResourceChange(KUidValueCoeFontChangeEvent);
    RequestRelayout(this);
    }

/** Return the zoom factor for this control. Takes account of zoom factors in parent controls 
to calculate accumulated zoom factor.


@return Accumulated zoom factor.  
@publishedAll
@released
*/
EXPORT_C TZoomFactor CCoeControl::AccumulatedZoom() const
    {
    TZoomFactor accZoomFactor(iCoeEnv->ScreenDevice());

    const TCoeZoomWithType* zoomWithType = NULL;
    const CCoeControl* parent = this;

#ifdef _DEBUG
    TInt safetyCount = 100;
#endif
    while(parent)        // Look for all zoom factors, all the way up. Don't stop at the first parent with one set.
        {
        zoomWithType = parent->GetZoomWithType();

        if(zoomWithType)
            {
            if(zoomWithType->iZoomType == ERelativeZoom)
            	{
            	accZoomFactor.SetZoomFactor(accZoomFactor.ZoomFactor() * zoomWithType->iZoomFactor / 1000);
            	}
            else
                {
                accZoomFactor.SetZoomFactor(zoomWithType->iZoomFactor * accZoomFactor.ZoomFactor() /1000);
                break;
                }
            }

        parent = parent->Parent();
#ifdef _DEBUG
        safetyCount--;
        __ASSERT_DEBUG(safetyCount, Panic(ECoePanicCyclicParentChildRelationship));
#endif
        }

    if(zoomWithType && (zoomWithType->iZoomType == ERelativeZoom))
    	{
		accZoomFactor.SetZoomFactor(accZoomFactor.ZoomFactor() * iCoeEnv->ZoomFactor().ZoomFactor() / 1000);
    	}

    return accZoomFactor;
    }
    
/** Return the zoom factor but without taking into account the
zoom factor of the parent. Use of AccumulatedZoom() is recommended as it takes
into account the zoom factor of the parent.

@publishedAll
@released
*/
EXPORT_C const TCoeZoomWithType* CCoeControl::ZoomWithType() const
   	{
	return DoGetZoomWithType(iData->DynamicDataStorage());
	}

/** Return the font provider used by this control
 
@return The font provider used by this control
*/
EXPORT_C const CCoeFontProvider& CCoeControl::FindFontProvider() const
    {
    const CCoeFontProvider* fontProvider = GetFontProvider();
    const CCoeControl* parent = Parent();

#ifdef _DEBUG
    TInt safetyCount = 100;
    while(!fontProvider && parent)
        {
        fontProvider = parent->GetFontProvider();
        parent = parent->Parent();
        safetyCount--;
        __ASSERT_DEBUG(safetyCount, Panic(ECoePanicCyclicParentChildRelationship));
        }
#else
    while(!fontProvider && parent)
        {
        fontProvider = DoGetFontProvider(parent->iData->DynamicDataStorage());
        parent = parent->Parent();
        }
#endif

    return (!fontProvider ? CCoeEnv::Static()->DefaultFontProvider() : *fontProvider);
    }

/** Returns the closest matching font from the control's current font provider to the 
requested logical font, taking into account the control's zoom factor.

This function should be used in preference to legacy functions like 
CEikonEnv::LegendFont(), CCoeEnv::NormalFont() or CCoeEnv::CreateScreenFontL().

Example 1: 
Instead of the control using a CFont class member, or calling NormalFont(), 
LegendFont() etc, it is recommended the control (e.g. in its Draw() method) call the 
new ScreenFont() method to temporarily access a CFont object owned by the font provider. 
This is a lot more efficient than repeatedly e.g. calling GetNearestFontInPixels(), 
and allows the CFont object used for text drawing to vary depending on the current 
zoom factor. Thus the CFont reference must not be kept as class member data, as it 
may be changed by the font provider at any time.

@code
CSomeControl::Draw(const TRect& aRect)
	{
	XCoeTextDrawer textDrawer(TextDrawer());
	textDrawer.SetAlignment(EHCenterVCenter);
	textDrawer.DrawText(gc, iText, aRect, ScreenFont(TCoeFont::LegendFont());
	}
@endcode

Example 2:
Although efficiently implemented, try not to call ScreenFont() or CCoeFontProvider::Font() 
repeatedly unnecessarily. Instead, create and use a local const CFont& on the stack, 
as shown below.

Note that the ScreenFont() call above is provided as short-hand for the code on 
the first two lines below. Also note that font providers and zoom factors apply
hieratically to the control tree (i.e. setting the zoom factor or font provider on
a container control affects the child controls too).

@code
CSomeControl::Draw(const TRect& aRect)
	{
	const CCoeFontProvider& fontProvider = FindFontProvider();
	const CFont& font = fontProvider.Font(TCoeFont::LegendFont(), AccumulatedZoom());
	XCoeTextDrawer textDrawer(TextDrawer());
	textDrawer.SetAlignment(EHCenterVCenter);
	textDrawer.DrawText(gc, iText, aRect, font);
    textDrawer.DrawText(gc, iText2, aRect, font);
    }
@endcode

@param aFont Logical font to use.
@see CCoeFontProvider
@see TCoeFont
*/
EXPORT_C const CFont& CCoeControl::ScreenFont(const TCoeFont& aFont) const
    {
    TZoomFactor zoomFactor = AccumulatedZoom();
    return FindFontProvider().Font(aFont, zoomFactor);
    }

/** Notify controls that the font has changed
*/
void CCoeControl::NotifyFontChange(const CCoeFontProvider* aFontProvider)
    {
    if(!IsActivated() || Rect().IsEmpty())
    	return;

    if(!aFontProvider)        // Notify on highest possible level
        {
        HandleResourceChange(KUidValueCoeFontChangeEvent);
        RequestRelayout(NULL);
        }
    else if(aFontProvider == GetFontProvider())        // Look for use of the font provider that changed
        {
        HandleResourceChange(KUidValueCoeFontChangeEvent);
        RequestRelayout(NULL);
        }
    else        // As long as we didn't find the right font provider, keep looking down the control tree
        {
        const TInt numControls = CountComponentControls();
        for(TInt i = 0; i < numControls; i++)
            {
            CCoeControl* control = ComponentControl(i);
            control->NotifyFontChange(aFontProvider);
            }
        }
    }
    
 
/** Force all CCoeFontProviders to update their logical-to-pixel mapping from CCoeControlStaticSettings

@internalTechnology
*/  
void CCoeControl::RefetchPixelMappingL()
	{
	CCoeFontProvider* fontProvider = const_cast<CCoeFontProvider*>(GetFontProvider()); 
	if(fontProvider) 
		{
		fontProvider->RefetchPixelMappingL();
		}
	
	// and search for CCoeFontProvider's down the control tree
	const TInt numControls = CountComponentControls();
    for(TInt i = 0; i < numControls; i++)
    	{
        CCoeControl* control = ComponentControl(i);
        control->RefetchPixelMappingL();
        }
	}


EXPORT_C void CCoeControl::HandleResourceChange(TInt aType)
/** Handles a change to the control's resources. 

The types of resources handled are those which are shared across the environment, 
e.g. colours or fonts. For colour scheme changes, DrawDeferred() is called in 
order to redraw the control.

If overriding HandleResourceChange(), the implementation must include a base call to CCoeControl's
HandleResourceChange().

@param aType A message UID value.
@see HandleComponentControlsResourceChange() */
	{
	HandleComponentControlsResourceChange(aType);	
	if ((aType == KUidValueCoeColorSchemeChangeEvent) || (aType == KUidValueCoeZoomChangeEvent))
		{
		DrawDeferred();
		}
	}

EXPORT_C void CCoeControl::GetColorUseListL(CArrayFix<TCoeColorUse>& /*aColorUseList*/) const
/** Gets the list of logical colours used to draw the control. 

The list includes an explanation of how each colour is used. 
The default implementation is empty.

If overriding GetColorUseListL(), the implementation must include a base call to CCoeControl's
GetColorUseListL().

@param aColorUseList The colour list. */
	{
	}

EXPORT_C void CCoeControl::GetHelpContext(TCoeHelpContext& /*aContext*/) const
/** Gets the control's help context.

The default implementation is empty. The function must be implemented in 
derived classes to associate the control with a particular Help file and 
topic in a context sensitive application. The implementation should set 
the public data members of TCoeHelpContext to the required Help file UID 
and context descriptor, as created using the Context-Sensitive Help Compiler.

@param aContext The control's help context */
	{
	}

EXPORT_C void CCoeControl::ConstructFromResourceL(TResourceReader& /*aSource*/)
/** Constructs the control from a resource file. 

This function has an empty default implementation. It should be implemented 
if the control is to be displayed within a dialog. It should initialise the 
control, reading in resource values from the resource file.

Note: if a control is not displayed in a dialog, it is necessary to set the control's 
associated window using SetContainerWindowL(). Since this may leave, the control 
should be constructed using ConstructL().

@param aSource The resource reader with which to access the control's resource 
values. */
	{
	}

EXPORT_C RWindow& CCoeControl::Window() const
/** Gets the control's associated window. 

The control must be window owning, and the window must be of type RWindow. 
If you don't know whether the window is of type RWindow or RBackedUpWindow, 
you should use DrawableWindow().

@return The control's associated window, cast to an RWindow. */
	{
	return(STATIC_CAST(RWindow&,*iWin));
	}

EXPORT_C RBackedUpWindow& CCoeControl::BackedUpWindow() const
/** Gets the backed-up window owned by the control. 

The window must be of type RBackedUpWindow. If you don't know whether the 
window is of type RWindow or RBackedUpWindow, you should use DrawableWindow().

@return The control's associated window, cast to an RBackedUpWindow.
@deprecated
*/
	{
	return(STATIC_CAST(RBackedUpWindow&,*iWin));
	}

EXPORT_C void CCoeControl::CloseWindow()
/** Closes the window owned by this control. 

It is called from CCoeControl's destructor for window-owning controls. */
	{
	__ASSERT_DEBUG(OwnsWindow(),Panic(ECoePanicNoWindow));
	if (iWin)
		{
		iWin->Close();
		delete(iWin);
		iWin=NULL;
		}
	iFlags&=(~(EOwnsWindow|EBackedUpWindow|EActivated));
	}

EXPORT_C void CCoeControl::CreateBackedUpWindowL(RWindowTreeNode& aParent)
/** Creates a control's window as a backed-up window.

The new window is the child of aParent and the display mode of the control 
becomes the same as that of aParent.

@param aParent The window to be the parent of this control's window. Does 
not have to be a backed-up window.
@deprecated
*/
	{
	if(iFlags&EMemoryAllocationFailed)
		User::LeaveNoMemory();
	
	TInt colors=0;
	TInt grays=0;
	TDisplayMode defaultMode=iCoeEnv->WsSession().GetDefModeMaxNumColors(colors,grays);
	CreateBackedUpWindowL(aParent,defaultMode);
	}

EXPORT_C void CCoeControl::CreateBackedUpWindowL(RWindowTreeNode& aParent,TDisplayMode aDisplayMode)
/** Creates a control's window as a backed-up window.

The new window is the child of aParent. Furthermore, the window's extent is set to that of the control.

The window will have the same display mode as the system display mode (the provided aDisplayMode is ignored).

@param aParent The window of the control to be the parent of this control. 
Does not have to be a backed-up window.
@param aDisplayMode Ignored. The window will always be created with the system display mode.
@deprecated
*/
	{
	if(iFlags&EMemoryAllocationFailed)
		User::LeaveNoMemory();
	
	__ASSERT_DEBUG(!OwnsWindow(), Panic(ECoePanicWindowAlreadyCreated));
	iWin=new(ELeave) RBackedUpWindow(iCoeEnv->WsSession());
	iFlags|=EOwnsWindow|EBackedUpWindow;
	User::LeaveIfError(((RBackedUpWindow*)iWin)->Construct(aParent,aDisplayMode,(TUint32)this));
	const TInt err = (static_cast<RBackedUpWindow*>(iWin))->SetExtentErr(iPosition,iSize);
	if (err!=KErrNone)
   				iFlags|=EMemoryAllocationFailed;
	}

EXPORT_C void CCoeControl::CreateWindowL(RWindowTreeNode& aParent)
/** Creates a control's window, specifying its parent window and its extent.

This function makes the specified control a window-owning control, and would 
typically be called in the control's ConstructL() function. It also sets the window's extent to that of the control.

Note:

The use of window owning controls is discouraged, as these tax run-time resources. 
Ideally only the top level control in an appUi would be window owning. There 
are some exceptions to this rule, e.g. floating controls like menus, dialogs 
and scroll bars.

In general, the overload with no parameters should be used.

@param aParent The window of the control to be the parent of this control. */
	{
	if(iFlags&EMemoryAllocationFailed)
		User::LeaveNoMemory();
	
	__ASSERT_DEBUG(!OwnsWindow(), Panic(ECoePanicWindowAlreadyCreated));
	iWin=new(ELeave) RWindow(iCoeEnv->WsSession());
	iFlags|=EOwnsWindow;
	User::LeaveIfError(((RWindow*)iWin)->Construct(aParent,(TUint32)this));
	(static_cast<RWindow*>(iWin))->SetExtent(iPosition,iSize);
	}

//
// Overloaded member function which creates a containing window for the control to own. The window
// containing the control aParent is used as the window's parent if the control pointer is not NULL.
// Otherwise the root window will be used as parent.
//
EXPORT_C void CCoeControl::CreateWindowL(const CCoeControl* aParent)
/** Creates a control's window, specifying the parent control. 

The control's window is created as a child of the parent control's window.

This function makes the specified control a window-owning control, and would 
typically be called in the control's ConstructL() function.

Note:

The use of window owning controls is discouraged, as these tax run-time resources. 
Ideally only the top level control in an appUi would be window owning. There 
are some exceptions to this rule, e.g. floating controls like menus, dialogs 
and scroll bars.

In general, the overload with no parameters should be used.

@param aParent The control to be the parent of this control. */
	{	
	SetMopParent(const_cast<CCoeControl*>(aParent));
	User::LeaveIfError(SetParent(const_cast<CCoeControl*>(aParent)));

	CreateWindowL(aParent? (RWindowTreeNode&)(*aParent->iWin): (RWindowTreeNode&)iCoeEnv->RootWin());
	}

//
// Overloaded member function which creates a containing window for the control to own. The window
// group aParent is used as the window's parent if it is not NULL. Otherwise the root window will be
// used as the parent.
//
EXPORT_C void CCoeControl::CreateWindowL(RWindowGroup* aParent)
/** Creates a control's window, specifying its parent window group.

This function makes the specified control a window-owning control, and would 
typically be called in the control's ConstructL() function.

Note:

The use of window owning controls is discouraged, as these tax run-time resources. 
Ideally only the top level control in an appUi would be window owning. There 
are some exceptions to this rule, e.g. floating controls like menus, dialogs 
and scroll bars.

In general, the overload with no parameters should be used.

@param aParent The window group of the control to be the parent of this control */
	{
	CreateWindowL(aParent? (RWindowTreeNode&)(*aParent): (RWindowTreeNode&)iCoeEnv->RootWin());
	}

//
// Overloaded member function which creates a containing window for the control to own. The root window is
// used as a parent.
//
EXPORT_C void CCoeControl::CreateWindowL()
/** Creates a control's window. 

The created window is the child of the application's window group.

This function makes the specified control a window-owning control, and would 
typically be called in the control's ConstructL() function.

Note:

The use of window owning controls is discouraged, as these tax run-time resources. 
Ideally only the top level control in an appUi would be window owning. There 
are some exceptions to this rule, e.g. floating controls like menus, dialogs 
and scroll bars. */
	{
	CreateWindowL(iCoeEnv->RootWin());
	}

EXPORT_C void CCoeControl::HandleRedrawEvent(const TRect& aRect) const
/** Handles redraw events.

In normal circumstances this function should not be used or overridden by 
the derived control class.

@param aRect The rectangle to be redrawn. */
	{
	Window().BeginRedraw(aRect);
	
	if (IsReadyToDraw())
		{
		ActivateGc();
		// Draw the background if found, but not if this is a semi-transparent window-owning control
		// without its own background attached (or we risk drawing a semi-transparent skin multiple times)
		if ((OwnsWindow() || Background()) && !(iFlags&EWindowIsSemiTransparent && !Background()))
        	{	
			const MCoeControlBackground* background = FindBackground();
			if (background)
				background->Draw(SystemGc(), *this, aRect);
			}

		Draw(aRect);
		DrawComponents(aRect);
		DeactivateGc();
		}
	Window().EndRedraw();
	}

void CCoeControl::DrawComponents(const TRect& aRect) const
	{
	CWindowGc* containerGc = CustomGc();
	CWindowGc* gc = (containerGc ? containerGc : &SystemGc());	

	const TInt count=CountComponentControls();
	for (TInt ii=0; ii<count; ii++)
		{
		const CCoeControl* ctrl=ComponentControl(ii);
		
		if (!(ctrl->OwnsWindow()) && ctrl->IsVisible())
			{
			TRect rect;
			const TRect* pRect=(&aRect);
			if (!((ctrl->iFlags)&ECanDrawOutsideRect))
				{
				rect=ctrl->Rect();
				rect.Intersection(aRect);
				if (rect.IsEmpty())
					continue;
				pRect=(&rect);
				}
				
			const MCoeControlBackground* background = ctrl->Background();
			if(background) // ctrl is always non-window owning. Draw if it itself has background attached
				background->Draw(*gc, *ctrl, *pRect);

			if (iContext)
				iContext->ResetContext(*gc);
			else	
				gc->Reset();
					
			ctrl->Draw(*pRect);
			ctrl->DrawComponents(*pRect);
			}
		}
	}



EXPORT_C void CCoeControl::Draw(const TRect& aRect) const
/** Draws the control. 

All controls, except blank controls, should implement this function. The default 
implementation draws a blank control.

This function is called by window server. It is used for window server-initiated 
redrawing of controls, and for some application-initiated drawing. It should be 
implemented by each control, but is only called from within CCoeControl's member 
functions, and not from the derived class. For this reason it is a private member 
function of CCoeControl.

The rectangle aRect indicates the region of the control that needs to be redrawn. 
The implementation of Draw() must always draw to every pixel within this rectangle.

Notes:

For non-window-owning controls, care must be taken not to draw outside the 
control, as drawing will not be clipped to the control. Drawing is clipped 
to window-owning-controls, but not to non-window-owning controls.

Drawing outside aRect may cause flicker.

Drawing should be done using a graphics context (CWindowGc), which can be 
obtained using SystemGc().

@param aRect The region of the control to be redrawn. Co-ordinates are relative 
to the control's origin (top left corner). */
	{
	if (iFlags&EBlank)
		{ // else do nothing
		// If there is a background then it will be used
		// to draw the background so don't blank the window
		if(!FindBackground())
			{
			CGraphicsContext& gc=SystemGc();
			gc.SetPenStyle(CGraphicsContext::ENullPen);
			gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
    		gc.DrawRect(aRect);
			}
		}
	}

EXPORT_C void CCoeControl::DrawNow() const
/** Draws the entire control

This function is called by an application or other code. 
The application should call this function when the control is first created 
and is ready for drawing, or if a change in application data or the control's 
internal state means that entire control's appearance is no longer up-to-date.

Partial redrawing of a control is sometimes more appropriate than drawing 
the entire control, and in this case, use DrawNow(const TRect &aRect) instead.

DrawNow() is implemented by CCoeControl and MAY NOT be overridden. It calls 
Draw() on the control itself, and also on all its component controls, if it 
is a compound control. (To do this it uses CountComponentControls() and ComponentControl(), 
which should be implemented by the derived control class.) If the control 
is a window-owning control, it also calls Draw() for its child windows (if 
any). */
	{
	DrawNow(Rect());
	}

/** Draws the control, its components and child windows, within the bounds defined by the given rectangle.
@param aRect The rectangular region of the control to be drawn. */
EXPORT_C void CCoeControl::DrawNow(const TRect &aRect) const
	{
	if (!IsReadyToDraw())
		return;

	TBool backedUp=IsBackedUp();
	if (!backedUp)
		{
		Window().Invalidate(aRect);
		Window().BeginRedraw(aRect);
		}
		
	const CCoeControl* parent = WindowOwningParent();
	if (parent && parent->IsReadyToDraw())	// Parents should always be ready to draw, but there are flaky code out there...
		{
		__ASSERT_DEBUG(parent->OwnsWindow(), User::Invariant());
		parent->ActivateGc();
		const MCoeControlBackground* background = parent->FindBackground();
		// Draw the background if found, but not if this is a semi-transparent window-owning control
		// without its own background attached (or we risk drawing a semi-transparent skin multiple times)
		if (background && !(iFlags&EWindowIsSemiTransparent && !Background()))
			background->Draw(parent->SystemGc(), *parent, aRect);			
			
		parent->Draw(aRect);
		parent->DrawComponents(aRect);
		parent->DeactivateGc();
		if (!backedUp)
			Window().EndRedraw();
		parent->DrawWindowOwningComponentsNow(aRect);
		}
	else
		{
		ActivateGc();
		Draw(aRect);
		DrawComponents(aRect);
		DeactivateGc();
		if (!backedUp)
			Window().EndRedraw();

		DrawWindowOwningComponentsNow(aRect);
		}
	}

void CCoeControl::DrawWindowOwningComponentsNow(const TRect &aRect) const
	{
	const TInt count=CountComponentControls();
	for (TInt ii=0; ii<count; ii++)
		{
		CCoeControl* ctrl=ComponentControl(ii);
				
		if (!ctrl->OwnsWindow())
			{
			ctrl->DrawWindowOwningComponentsNow(aRect);
			}
		else
			{
			TRect adjustedRect(aRect);
            const RWindow& parentWindow = Window();
            const RDrawableWindow& childWindow = *(ctrl->DrawableWindow());
            if (parentWindow.WsHandle() != childWindow.WsHandle())
				{
                const TPoint childRelativePos = childWindow.InquireOffset(parentWindow);
                // Adjust the parent referenced rectangle to the child window co-ordinates
                adjustedRect.Move(-childRelativePos);
                }
            else
                {
                // As the child owns the window, the parent is a lodger of the child, so allow for the parent position
                adjustedRect.Move(-iPosition);
                }
            adjustedRect.Intersection(ctrl->Rect());
            if (!adjustedRect.IsEmpty())
				{
                ctrl->DrawNow(adjustedRect);
                }

			}
		}
	}

		

EXPORT_C void CCoeControl::DrawDeferred() const
/** Draws the control, with low priority.

This function is called by an application or other code.

It causes the control area to be marked as invalid, which will 
eventually cause a redraw initiated by the window server. The control framework 
handles redraw events at a lower priority than user input events, which means 
that any pending user input events will be processed before the redraw event. 
DrawDeferred() therefore allows a control to do drawing at a lower priority 
than drawing performed by DrawNow().

An advantage of using DrawDeferred() is that if you make multiple calls to 
DrawDeferred() on the same area of a control, the window server will not generate 
a redraw event to do drawing that has already been superceded. If you make 
multiple calls to DrawNow(), however, all of them get processed, even if they 
have already been superceded by the time they are processed. */
	{
	if (!IsReadyToDraw())
		return;
	if (IsBackedUp())
		DrawNow();
	else
		Window().Invalidate(Rect());
	const TInt count=CountComponentControls();
	for (TInt ii=0; ii<count; ii++)
		{
		const CCoeControl* ctrl=ComponentControl(ii);
		if (ctrl->OwnsWindow())
			ctrl->DrawDeferred();
		}
	}

/** Find a control in the parent chain (including this) that owns a window
*/
CCoeControl* CCoeControl::WindowOwningParent()
	{
	CCoeControl* parent = this;	// start with this, in case it is window owning

#ifdef _DEBUG
	TInt safetyCount = 100;
#endif
	while(parent && !parent->OwnsWindow())
		{
		parent = parent->Parent();
#ifdef _DEBUG
		--safetyCount;
		ASSERT(safetyCount);
#endif
		}
	return parent;
	}

/** Returns the background drawer object associated with this object, if any. 
Null is returned if there is no such object. Compare with FindBackground(), which looks up the parent chain
to find a background drawer. 

@return The background drawer object associated with this object. */
EXPORT_C const MCoeControlBackground* CCoeControl::Background() const
	{
	return DoGetBackground(iData->DynamicDataStorage());
	}
	
/** Return an MCoeControlBackground object, if there is one - looking up
the parent chain as necessary. Compare to Background(), which does not
go up the parent chain.
*/
EXPORT_C const MCoeControlBackground* CCoeControl::FindBackground() const
	{
	const MCoeControlBackground* background = Background();
	const CCoeControl* parent = Parent();

#ifdef _DEBUG
	TInt safetyCount = 100;
#endif
	while(!background && parent)
		{
		background = parent->Background();
		parent = parent->Parent();
#ifdef _DEBUG
		safetyCount--;
		ASSERT(safetyCount);
#endif
		}
	return background;
	}

/** Sets aParent as the parent of this control.
If setting aParent as parent of this control will create a cyclic relationship, 
this method does nothing.

@param aParent The control to set as this control's parent.
@return KErrNone if successful, otherwise another of the system error codes.
*/
EXPORT_C TInt CCoeControl::SetParent(CCoeControl* aParent)
	{
	if(aParent)	// Check for cyclic relationships only if parent is not being set to NULL
		{
		const CCoeControl* parent = aParent->SearchParent(this);
		// If "parent" is non-NULL, it means that "this" is already a parent of aParent.
		// Such circularity should not occur...
		if(parent)				// ...but because there are bad controls out there (like CEikButtonGroupContainer)...
			return KErrNone;	// ...do nothing, to avoid creating a cyclic parent-child relationship.
		}
		
	const TInt err = DoSetParent(iData->DynamicDataStorage(), aParent);
	if(err)
		 iFlags |= EMemoryAllocationFailed;	// Doom the control
	return err; 
	}

/** Safety check to avoid loops in the parent chain.
*/
const CCoeControl* CCoeControl::SearchParent(const CCoeControl* aParentToFind) const
	{
	const CCoeControl* parent = this;
#ifdef _DEBUG
	TInt safetyCount = 100;
#endif
	while (parent && parent != aParentToFind)
		{
		parent = parent->Parent();
#ifdef _DEBUG
		--safetyCount;
		ASSERT(safetyCount);
#endif
		}
	
	return parent;
	}

/**
Sets the control's custom graphics context. This value overrides the system context for 
this control and any children.

If aGraphicsContext is null, the control's graphics context is reset to the one it inherited 
from its parent, or to the default system graphics context (iCoeEnv->SystemGc()) if none of 
its parents have set their own graphics context.

This value is retrieved by CCoeControl::SystemGc().
@param aGraphContext The new graphics context for this class and its children.
The caller keeps ownership.
*/
EXPORT_C TInt CCoeControl::SetCustomGc(CWindowGc* aGraphicsContext)
	{
	return DoSetCustomGc(iData->DynamicDataStorage(), aGraphicsContext);
	}


/**
Returns the custom graphics context set for this control (if any). Note that unlike 
CCoeControl::SystemGc(), this function ignores the parent window's state and 
returns the context set explicitly for this control instance, or NULL if none has been set.

@return The current graphics context.
*/
EXPORT_C CWindowGc* CCoeControl::CustomGc() const
	{
	return DoGetCustomGc(iData->DynamicDataStorage());
	}

/** Draws the control's background using its graphics context. 
Unlike DrawNow() and DrawDeferred(), this function does not propagate 
the draw to component controls. 

@param aRect The area to be redrawn. This can be the control's entire rectangle, or a 
sub-rectangle within it.
*/
EXPORT_C void CCoeControl::DrawBackground(const TRect& aRect) const
	{
	CWindowGc& gc=SystemGc();
	const MCoeControlBackground* theBackground = Background();
	if(theBackground)
		{
		theBackground->Draw(gc, *this, aRect);
		}
	}
	
/** Draws the control's foreground using the control's graphics context. 
Unlike DrawNow() and DrawDeferred(), this function does not propagate the draw to component controls. 

@param aRect The area to be redrawn. This can be the control's entire rectangle, or a 
sub-rectangle within it.
*/
EXPORT_C void CCoeControl::DrawForeground(const TRect& aRect) const
	{
	Draw(aRect);
	}

/** Installs a hit tester for this control. The tester defines the hit region, 
which is the area within the control that accepts pointer events. If no hit region is set, 
pointer events are accepted in the control's entire rectangle.

@param aHitTestControl Object which defines the hit region.
@return KErrNone if successful, or another system error code.
*/
EXPORT_C TInt CCoeControl::SetHitTest(const MCoeControlHitTest* aHitTestControl)
	{
	return DoSetHitTest(iData->DynamicDataStorage(), aHitTestControl);
	}

/** Gets the object that defines the hit region inside the control's rectangle.
The object is set by calling SetHitTest().

@return The hit region tester.
*/
EXPORT_C const MCoeControlHitTest* CCoeControl::HitTest() const
	{
	return DoGetHitTest(iData->DynamicDataStorage());
	}

TCoeZoomWithType* CCoeControl::GetZoomWithType() const
	{
	return DoGetZoomWithType(iData->DynamicDataStorage());
	}

TInt CCoeControl::SetZoomWithType(TCoeZoomWithType* aZoomWithType)
	{
	return DoSetZoomWithType(iData->DynamicDataStorage(), aZoomWithType);
	}

const CCoeFontProvider* CCoeControl::GetFontProvider() const
	{
	return DoGetFontProvider(iData->DynamicDataStorage());
	}

TInt CCoeControl::SetFontProvider(const CCoeFontProvider* aFontProvider)
	{
	return DoSetFontProvider(iData->DynamicDataStorage(), aFontProvider);
	}

EXPORT_C CWindowGc& CCoeControl::SystemGc() const
/** Gets the graphics context that is used when drawing the control. 
 
This function walks the CCoeControl hierarchy upwards from child to parent until a context 
is found. If no control in the hierarchy has defined its own graphics context, the default system 
graphics context (iCoeEnv->SystemGc()) is returned.

All drawing is carried out through a graphics context. A graphics context 
must be activated before it can be drawn to, and deactivated 
when it is no longer needed. When drawing is done using Draw(), DrawNow() 
or DrawDeferred(), the application does not have to do this, as it is done 
within the control framework. However, for application-initiated drawing which 
is not done using DrawNow() or DrawDeferred(), the application should activate 
and deactivate the graphics context using ActivateGc() and DeactivateGc() 
(or CWindowGc::Activate() and CWindowGc::Deactivate()).

@return The system graphics context. */
	{
	const CCoeControl* theControl = this;
	do
		{
		CWindowGc* customGc = DoGetCustomGc(theControl->iData->DynamicDataStorage());
		if(customGc)
			return *customGc;
		}
	while((theControl=theControl->Parent()) != NULL);
	
	return(iCoeEnv->SystemGc());
	}

EXPORT_C void CCoeControl::ActivateGc() const
/** Activates the standard graphics context. 

This is the graphics context owned by the control environment (CCoeEnv).

Applications do not normally need to call this function, as it is called 
by the control framework whenever it is about to call Draw(). */
	{
	CWindowGc& gc=SystemGc();
	if (iContext)
		iContext->ActivateContext(gc,*iWin);
	else
		gc.Activate(*iWin);
	ActivateGcRecursive();
	}

void CCoeControl::ActivateGcRecursive() const
	{
	const TInt numComponentControls = CountComponentControls();

	for(TInt i = numComponentControls - 1; i >= 0; i--)
		{
		const CCoeControl* control = ComponentControl(i);

		if(control)
			{
			CWindowGc* redirectedgc = control->CustomGc();
			CWindowGc* containerGc = CustomGc();
			const TBool swapGc = (redirectedgc && (redirectedgc != containerGc));

			if(swapGc)
				{          
				if(iContext)
					{
					iContext->ActivateContext(*redirectedgc,*DrawableWindow());
					}
				else
					{
					redirectedgc->Activate(*DrawableWindow());
					}
				}

			control->ActivateGcRecursive();
			}
		}
	}

EXPORT_C void CCoeControl::ResetGc() const
/** Resets the standard graphics context. 

The function resets the graphics context owned by the control environment 
to its default settings. */
	{
	CWindowGc& gc=SystemGc();
	if (iContext)
		iContext->ResetContext(gc);
	else
		gc.Reset();
	}

EXPORT_C void CCoeControl::DeactivateGc() const
/** Deactivates the standard graphics context owned by the UI control framework.

Applications do not normally need to call this function, as it is called 
by the control framework whenever it has called Draw() and drawing is completed. */
	{ // no harm done if Gc other than system one used
	SystemGc().Deactivate();
	
	DeactivateGcRecursive();
	}

void CCoeControl::DeactivateGcRecursive() const
	{
	TInt numComponentControls = CountComponentControls();

	for(TInt i = numComponentControls - 1; i >= 0; i--)
		{
		const CCoeControl* control = ComponentControl(i);

		if(control)
			{
			CWindowGc* redirectedgc = control->CustomGc();
			CWindowGc* containerGc = CustomGc();
			const TBool swapGc = (redirectedgc && (redirectedgc != containerGc));

			if(swapGc)
				{
				redirectedgc->Deactivate();                    
				}
       
			control->DeactivateGcRecursive();
			}
		}
	}
	
EXPORT_C void CCoeControl::SetFocus(TBool aFocus,TDrawNow aDrawNow)
/** Sets this control to have the keyboard focus.

It sets the value of a focus flag within the control to the value 
given by aFocus. This flag indicates whether or not the control has keyboard 
focus, and its value can be enquired using IsFocused(). It then calls FocusChanged(), 
passing it the value given by aDrawNow, unless the control is invisible or 
not activated, in which case it passes ENoDrawNow.

Note that setting focus does not initiate a redraw. The control's implementation 
of FocusChanged() should do this if required. The control's Draw() function, 
or that of its container, should normally change the appearance of the control 
to indicate whether or not it currently has focus.

@param aFocus ETrue sets the control as having keyboard focus, EFalse sets 
it as not having keyboard focus.
@param aDrawNow Flag to pass to FocusChanged(). */
	{
	iCoeEnv->QueueNotificationToFocusObserversOfChangeInFocus();
	if (aFocus)
		{
		iFlags|=EFocused;
		iFlags&=(~ENotifyFocusObserversOnDestruction);
		}
	else
		{
		if (iFlags&EFocused)
			{
			iFlags&=(~EFocused);

			if(DoSetFocusObserverNotificationIdentifier(iData->DynamicDataStorage(), iCoeEnv->FocusObserverNotificationIdentifier()) == KErrNoMemory)	
				iFlags|=ENotifyFocusObserversOnDestruction;
			else
				iFlags&=(~ENotifyFocusObserversOnDestruction);
			}
		}

	if (aDrawNow && !IsReadyToDraw())
		aDrawNow=ENoDrawNow;
	
	FocusChanged(aDrawNow);
	}

EXPORT_C void CCoeControl::FocusChanged(TDrawNow /*aDrawNow*/)
/** Responds to a change in focus.

This is called whenever the control gains or loses focus, as a result 
of a call to SetFocus(). A typical use of FocusChanged() is to change the 
appearance of the control, for example by drawing a focus rectangle around it.

The default implementation is empty, and should be overridden by the CCoeControl-derived 
class.

@param aDrawNow Contains the value that was passed to it by SetFocus(). */
	{
	}

void CCoeControl::ReportControlStateChange(MCoeControlStateObserver::TCoeState aType)
/** Reports a change in the controls visibility or dimmed state to the Mop Framework

Looks for an object through the Mop framework both starting at this control and from the 
control enviroment.  Calls them both if they provide different objects.*/
	{
	if(iFlags&EReportControlStateChange && iCoeEnv->ControlStateChange())	//Do control state change only if it is enabled
		{
		MCoeControlStateObserver* stateObserver1=NULL;
		MCoeControlStateObserver* stateObserver2=NULL;
		iCoeEnv->MopGetObjectNoChaining(stateObserver1);
		MopGetObject(stateObserver2);
		if (stateObserver1)
			stateObserver1->HandleControlStateChange(this,aType);	//Ignore returned error code
		if (stateObserver2 && stateObserver1!=stateObserver2)
			stateObserver2->HandleControlStateChange(this,aType);	//Ignore returned error code
		}
	}

TInt CCoeControl::ValidateAdvancedPointerNumber( const TPointerEvent& aPointerEvent ) const
/** Determines that the pointer-number in an advanced-pointer-event is within the supported range.
 
 @param aPointerEvent the TPointerEvent reference to be validated.
 @return KErrArgument if the pointer-number is out of range of the supported number of pointers. 
*/
	{
	TInt err = KErrNone;

	// Called only for advancedpointerevent so AdvancedPointerEvent()->PointerNumber() is safe  
	if( aPointerEvent.AdvancedPointerEvent()->PointerNumber() >= ControlEnv()->SupportedPointers() )
		{
		err = KErrArgument;
		}	
	
	return err;
	}

EXPORT_C void CCoeControl::SetDimmed(TBool aDimmed)
/** Sets the control to be dimmed.

This function sets a flag within the control which indicates whether or not 
the control is dimmed (greyed out). This is typically used to show that the 
control is temporarily unavailable.

SetDimmed() does not initiate a redraw of the control. The application should 
call DrawNow() or DrawDeferred() if a redraw is required after calling SetDimmed(). 
The control's Draw() function should draw the control appropriately according 
to whether it is dimmed or not. (This can be enquired using IsDimmed().)

If overriding SetDimmed(), the implementation must include a base call to CCoeControl's
SetDimmed().

@param aDimmed ETrue to dim the control, EFalse to set the control as not 
dimmed. */
	{
	if (!(iFlags&EDimmed)==!aDimmed)
		return;
	if (aDimmed)
		iFlags|=EDimmed;
	else
		iFlags&=(~EDimmed);
	ReportControlStateChange(MCoeControlStateObserver::EStateDimmed);
	}

void CCoeControl::SetGrabbed(TBool aGrabbed, TInt aPointerNumber)
/** Sets the control to grab pointer events
	
*/
	{
	if (aGrabbed)
		{
		// sets pointer grab flag for given pointer number  
		iData->SetPointerGrab( (1 << aPointerNumber), 0 );
		}
	else
		{
		iData->SetPointerGrab( 0, (1 << aPointerNumber) );
		}
	}

EXPORT_C void CCoeControl::MakeVisible(TBool aVisible)
/** Sets this control as visible or invisible. 

This causes the control to disappear or reappear. When a control is created, 
it is made visible by default.

MakeVisible() can be called before or after the control is activated.

Notes:

This function may be overridden.

The visibility of the control can be queried using IsVisible().

If MakeVisible() is used to make a component visible, and the control captures 
the pointer (see CapturesPointer()), MakeVisible() throws away any pending 
pointer events for that control.

Typical uses are for scrollbars, or for dialogs where some user responses 
are not required in certain circumstances.

@param aVisible ETrue to make the control visible, EFalse to make it invisible. */
	{
	DoMakeVisible(aVisible);
	if (iFlags&ECapturesPointer)
		CheckPointerEventPurge();
	}

void CCoeControl::DoMakeVisible(TBool aVisible)
	{
	TBool isVisible=IsVisible();
	if ((isVisible && aVisible) || (!isVisible && !aVisible))
		return;		// No change
	if (aVisible)
		iFlags&=(~EInvisible);
	else
		iFlags|=EInvisible;
	if (OwnsWindow())
		iWin->SetVisible(aVisible);
	else if (IsActivated())
		{
		if (IsBackedUp())
			DrawNow();
		else
			Window().Invalidate(Rect());
		}
	if (iFlags&EComponentsInheritVisibility)
		{
		const TInt count=CountComponentControls();
		for (TInt ii=0; ii<count; ii++)
			ComponentControl(ii)->MakeVisible(aVisible);
		}
	ReportControlStateChange(MCoeControlStateObserver::EStateVisibility);
	}

EXPORT_C void CCoeControl::SetComponentsToInheritVisibility(TBool aInherit)
/** Sets the control's components to inherit the visibility setting of their 
container control.

If set, when MakeVisible() is called on the compound control, the visibility 
setting is propagated to all its components.

@param aInherit If ETrue, the control's components inherit its visibility 
setting; if EFalse they do not. */
	{
	if (aInherit)
		iFlags|=EComponentsInheritVisibility;
	else
		iFlags&=(~EComponentsInheritVisibility);
	}

EXPORT_C TCoeInputCapabilities CCoeControl::InputCapabilities() const
/** Gets the control's input capabilities.

Classes that override CCoeControl::OfferKeyEventL() should also override this 
function, returning a TCoeInputCapabilities object whose attributes correspond 
to the behaviour of the OfferKeyEventL() function. The default implementation 
returns TCoeInputCapabilities::ENone.

It is not necessary to call InputCapabilities() on any component controls 
from inside a class's InputCapabilities() function. This is done automatically 
by the UI Control Framework.

@return The control's input capabilities. */
	{
	return TCoeInputCapabilities(TCoeInputCapabilities::ENone);
	}

EXPORT_C void CCoeControl::SetGloballyCapturing(TBool aGlobal)
/** Sets the global pointer capture flag. 

This flag indicates whether or not pointer capture should be global. 

The flag is used by SetPointerCapture() to determine what value to pass to 
RWindowBase::SetPointerCapture(). The default for the global capture flag, 
when a control is created, is EFalse.

@param aGlobal Value for global capture flag. */
	{
	if (aGlobal)
		iFlags|=EGloballyCapturing;
	else
		iFlags&=(~EGloballyCapturing);
	}

EXPORT_C void CCoeControl::SetNonFocusing()
/** Deprecated. Use SetFocusing().

Sets the control as unable to receive keyboard focus. The function would typically 
be called during construction of the control. */
	{
	iFlags|=ENonFocusing;
	}

EXPORT_C void CCoeControl::SetFocusing(TBool aFocusing)
/** Sets the control as able to receive keyboard focus. 

@param aFocusing ETrue if the control can have focus, EFalse if it can't. */
	{
	if (aFocusing)
		iFlags&=(~ENonFocusing);
	else
		iFlags|=ENonFocusing;
	}

EXPORT_C TBool CCoeControl::IsNonFocusing() const
/** Tests if the control can receive focus.

@return ETrue if the control cannot receive focus, EFalse if it can.
@see SetNonFocusing() */
	{
	return(iFlags&ENonFocusing);
	}

EXPORT_C void CCoeControl::SetAllowStrayPointers()
/** Sets whether or not to allow stray pointer events.

This function sets a flag that affects the way the control framework handles 
pointer events. By default, the flag is not set, and the control will ignore 
any pointer drag events and up events where the matching pointer down event 
occurred in a different control. This would happen if a user pressed the pointer 
down in a control, but then dragged the pointer into a different control before 
releasing it.

SetAllowStrayPointers() is typically used for menus, where stray pointer events 
are required because it is the pointer up event that is used to activate a 
menu option even when the pointer down event occured in a different menu pane. 
This is not the case in some other components such as command buttons, 
where a pointer down event and up event in succession are required to activate 
the button. */
	{
	iFlags|=EAllowStrayPointers;
	}

EXPORT_C void CCoeControl::SetCanDrawOutsideRect()
/** Allows the control to draw outside its own extent.

When a compound control is drawn, all its component controls are also drawn. 
However, unless this flag is set, they are not drawn if the rectangle they 
inhabit on the screen doesn't intersect with the rectangle to be drawn.

Setting this flag has the effect of allowing a component control to draw outside 
its own extent. It should be used with caution! By default, this flag is not 
set. */
	{
	iFlags|=ECanDrawOutsideRect;
	}

EXPORT_C void CCoeControl::SetBlank()
/** Sets a flag to indicate that the control is blank. 

Once set, this flag cannot be unset for the lifetime of the control.

@see IsBlank() */
	{
	iFlags|=EBlank;
	}

EXPORT_C void CCoeControl::SetRect(const TRect& aRect)
/** Sets the control's extent, specifying a rectangle.

Note: calling this function results in a call to SizeChanged().

@param aRect The rectangle that defines the control's extent. The rectangle's 
origin is relative to the origin of its associated window. */
	{
	SetExtent(aRect.iTl,aRect.Size());
	}

EXPORT_C void CCoeControl::SetExtentToWholeScreen()
/** Sets the control's extent to the whole screen.

Note: calling this function results in a call to SizeChanged(). */
	{
	SetExtent(TPoint(0,0),iCoeEnv->ScreenDevice()->SizeInPixels());
	}

EXPORT_C void CCoeControl::SetExtent(const TPoint& aPosition,const TSize& aSize)
/** Sets the control's extent, specifying a size and a position.

Note: calling this function results in a call to SizeChanged().

@param aPosition The position of the control, relative to its associated window.
@param aSize The size of the control, in pixels. */
	{
	if (OwnsWindow())
		{
		if (IsBackedUp())
			{
			const TInt err=iWin->SetExtentErr(aPosition,aSize);
			if (err!=KErrNone)
				iFlags|=EMemoryAllocationFailed;	// Doom the control
			}
		else
			Window().SetExtent(aPosition,aSize);
		}
	iPosition=aPosition;
	iSize=aSize;
	SizeChanged();
	}

EXPORT_C void CCoeControl::SizeChanged()
/** Responds to changes to the size and position of the contents of this control.

For a simple control this might include text or graphics. For a compound control 
it sets the size and position of the components.

The function is called whenever SetExtent(), SetSize(), SetRect(), SetCornerAndSize(), 
or SetExtentToWholeScreen() are called on the control. Note that the window 
server does not generate size-changed events: SizeChanged() gets called only 
as a result of calling the functions listed above. Therefore, if a resize 
of one control affects the size of other controls, it is up to the application 
to ensure that it handles the re-sizing of all affected controls. */
	{
	MCoeLayoutManager* layout = LayoutManager();
	if (layout)
		{
		layout->PerformLayout();
		}
	}

EXPORT_C void CCoeControl::PositionChanged()
/** Responds to changes in the position of a control. 

It has an empty default implementation which may be overridden by the CCoeControl-derived 
class.

This function is called whenever the application calls SetPosition() on 
the control. */
	{
	}

EXPORT_C void CCoeControl::SetSize(const TSize& aSize)
/** Sets the control's size.

If the size, but not the position, of a control is set, then its position 
will default to TPoint(0,0).

Note: calling this function results in a call to SizeChanged().

@param aSize The control's size, in pixels. */
	{
	SetSizeWithoutNotification(aSize);
	SizeChanged();
	}
 
EXPORT_C TInt CCoeControl::SetMaximumWidth(TInt aMaxWidth)
/** Sets the controls maximum width.

@param aMaxWidth The control's maximum width.
@return  Error Code. (KErrNone if max width was set successfully) */
	{
	//  Set the maximum width value	
	return DoSetMaximumWidth(iData->DynamicDataStorage(), aMaxWidth);
	}

EXPORT_C void CCoeControl::SetPosition(const TPoint& aPosition)
/** Sets the control's position.

If the control owns its containing window, it achieves this by setting the position of the window.
Otherwise, the position of the control is set relative to its containing window. The 
positions of the control's components are adjusted accordingly and PositionChanged()
is called.

@param aPosition The position of the the top-left of the control, relative to its 
associated window. */
	{
	if (OwnsWindow())
		{
		iPosition=aPosition;
		iWin->SetPosition(aPosition);
		}
	else
		{
		const TPoint delta=aPosition-iPosition;
		iPosition=aPosition;
		const TInt count=CountComponentControls();
		for (TInt ii=0;ii<count;ii++)
			{
			CCoeControl* ctrl=ComponentControl(ii);
			const TPoint pos=ctrl->Position();
			ctrl->SetPosition(pos+delta);
			}
		}
	PositionChanged();
	}

/** Sets a control's size without calling SizeChanged().

If the size, but not the position, of a control is set, then its position 
will default to TPoint(0,0).

@param aSize The control's size, in pixels.
@see SetSize() */
EXPORT_C void CCoeControl::SetSizeWithoutNotification(const TSize& aSize)
	{
	if (OwnsWindow())
		{
		if (IsBackedUp())
			{
			const TInt err=iWin->SetSizeErr(aSize);
			if (err!=KErrNone)
				iFlags|=EMemoryAllocationFailed;	// Doom the control
			}
		else
			Window().SetSize(aSize);
		}
	iSize=aSize;
	}

/** Creates a component array to store child controls.

This function is useful when the control is a compound control. It creates an array where the 
child controls can be stored. The CCoeControl::Components return the created array. The CCoeControlArray class
provides functions to easily add and remove controls.
*/
EXPORT_C void CCoeControl::InitComponentArrayL()
	{
 	CCoeControlArray* array = DoGetComponentArray(iData->DynamicDataStorage());
	if(!array)
		{
		array = CCoeControlArray::NewL(*this);
		if(DoSetComponentArray(iData->DynamicDataStorage(), array) != KErrNone)
			{
			delete array;
			User::LeaveNoMemory();
			}
		}
	}

/** Returns a component array to store child controls.

This function is useful when the control is a compound control. The CCoeControlArray class
provides functions to easily add and remove controls. The array must have been created before 
this function can be called. The InitComponentArrayL does this.

@return The control array
@see CCoeControl::InitComponentArrayL()
*/
EXPORT_C CCoeControlArray& CCoeControl::Components()
	{
	return *DoGetComponentArray(iData->DynamicDataStorage());
	}
	
/** Returns a component array to store child controls.

This function is useful when the control is a compound control. The CCoeControlArray class
provides functions to easily add and remove controls. The array must have been created before 
this function can be called. The InitComponentArrayL does this.

@return The control array
@see CCoeControl::InitComponentArrayL()
*/	
EXPORT_C const CCoeControlArray& CCoeControl::Components() const
	{
	return *DoGetComponentArray(iData->DynamicDataStorage());
	}

/** Handles events generated by the CCoeControlArray.

This function is useful when the control is a compound control and the CCoeControlArray functionality is used.
The CCoeControlArray functions that add and remove controls will use this event handler to notify the
control that child controls have been added or removed.

The default implementation of this function forwards the events to the layout manager (if there is one). If the
event is EControlAdded it also sets the container window of the new child control unless the child control is a window
owning control. If the event is EControlRemoved it also sets the parent of the removed child control to null.

@param aEvent The type of the event
@param aArray The array that generated the event
@param aControl The control affected by the event
@param aControlId The id of the control affected by the event
*/
EXPORT_C void CCoeControl::HandleControlArrayEventL(CCoeControlArray::TEvent aEvent, const CCoeControlArray* aArray, 
													CCoeControl* aControl, TInt /*aControlId*/)
	{
	if (aArray != &Components())
		return; 	// some other array
	
	switch(aEvent)
		{
		case CCoeControlArray::EControlAdded:
			{
 			__ASSERT_DEBUG(aControl->Parent() == NULL || aControl->Parent() == this, Panic(ECoePanicIncorrectControlParent));
			__ASSERT_DEBUG(DrawableWindow(), Panic(ECoePanicNoWindow));	// Make sure the container window is set

			if(!aControl->OwnsWindow())
				aControl->SetContainerWindowL(*this);
 	
			MCoeLayoutManager* layoutManager = LayoutManager();
			if(layoutManager)
				layoutManager->HandleAddedControlL(*this, *aControl);
			}
			break;
		case CCoeControlArray::EControlRemoved:
			{
 			MCoeLayoutManager* layoutManager = LayoutManager();
			if(layoutManager)
				layoutManager->HandleRemovedControl(*this, *aControl);
	
			aControl->SetParent(NULL);
			}
			break;
		default:
			ASSERT(0);
		}
	}

/** Gets an indexed component of a compound control. 

There are 2 ways to implement a compound control. One way is to override this function. The other way
is to use the CCoeControlArray functionality (see the InitComponentArrayL method).

Note: within a compound control, each component control is identified by an index, 
where the index depends on the order the controls were added: the first is 
given an index of 0, the next an index of 1, and so on.

@param aIndex The index of the control.
@return The component control with an index of aIndex.
*/
EXPORT_C CCoeControl* CCoeControl::ComponentControl(TInt aIndex) const
	{
	CCoeControlArray* components = DoGetComponentArray(iData->DynamicDataStorage());
	return ( components ? components->At(aIndex).iControl : NULL );
	}


EXPORT_C void CCoeControl::ActivateL()
/** Sets the control as ready to be drawn. 

The application should call this function on all controls that are not components 
in a compound control.

The purpose of this function is that controls are not always ready to be drawn 
as soon as they have been constructed. For example, it may not be possible 
to set the control's extent during construction, but its extent should always 
be set before it is drawn. Similarly, if a control is to be made invisible, 
this should be done before it is activated.

The default implementation sets a flag in the control to indicate it is ready 
to be drawn. If the control is a compound control, the default implementation 
also calls ActivateL() for all the control's components. To get the control's 
components it uses CountComponentControls() and ComponentControl(), which 
should be implemented by the compound control.

ActivateL() is typically called from the control's ConstructL() function .

Notes:

This function can be overridden. This is useful for doing late initialisation 
of the control, using information that was not available at the time the control 
was created. For example, a text editor might override ActivateL() and use it 
to enquire whether it is focused: if it is, it makes the cursor and any highlighting 
visible. At the time when the editor is created, it doesn't know whether or 
not it has keyboard focus. 

If overriding ActivateL(), the implementation must include a base call to CCoeControl's
ActivateL().*/
	{
	if (iFlags&EMemoryAllocationFailed)
		User::LeaveNoMemory();
	
	if (!(iFlags&EActivated))
		{
		iFlags|=EActivated;
		if (OwnsWindow())
			{
			iWin->Activate();
			if (iFlags&ECapturesPointer)
				CheckPointerEventPurge();
			if (IsBackedUp())
				DrawNow();
			}
			
		iData->AttemptCompress();	// Purge any unused member data memory
		}
		
	const TInt count=CountComponentControls();
	for (TInt ii=0; ii<count; ii++)
		{
		CCoeControl* child = ComponentControl(ii);
		if(!child->Parent())
			child->SetParent(this);		// Set the parent if not already set
		child->ActivateL();
		}
	}

EXPORT_C TRect CCoeControl::Rect() const
/** Gets the control's extent.

The position of the top-left of the rectangle is (0,0) if the control owns its 
window. Otherwise, its position is relative to its window.

@return The control's extent. */
	{
	return(TRect(OwnsWindow()? TPoint(0,0): iPosition,iSize));
	}

EXPORT_C void CCoeControl::SetContainerWindowL(const CCoeControl& aContainer)
/** Sets the control's containing window by copying it from aContainer.

It also copies the control context from aContainer if one has not previously been set.

This function can only be called on non-window-owning (or 'lodger') controls. 

If overriding SetContainerWindowL(), the implementation must include a base call to CCoeControl's
SetContainerWindowL().

@param aContainer The compound control that is the container for this control. */
	{
	if(iFlags&EMemoryAllocationFailed)
		User::LeaveNoMemory();
	
	if(OwnsWindow())
        CloseWindow();

	iWin = aContainer.iWin;
	if (!iContext)
		iContext = aContainer.iContext;
	
	if (aContainer.IsBackedUp())
		iFlags |= EBackedUpWindow;
	
	SetMopParent(const_cast<CCoeControl*>(&aContainer));
	User::LeaveIfError(SetParent(const_cast<CCoeControl*>(&aContainer)));
	}


EXPORT_C void CCoeControl::SetContainerWindowL(RWindow& aWindow)
/** Sets the control's containing window, without transferring ownership 
of the window to this control.

This function can only be called on non-window-owning ('lodger') controls.

Note: the container's window can be accessed using Window(), DrawableWindow(), or 
BackedUpWindow().

@param aWindow The window owned by the container control. */
	{
	if(iFlags&EMemoryAllocationFailed)
		User::LeaveNoMemory();
	
	if(OwnsWindow())
        CloseWindow();
	
	iWin=&aWindow;
	}

EXPORT_C void CCoeControl::SetContainerWindowL(RBackedUpWindow& aWindow)
/** Sets the control's containing window without transferring ownership 
of the window to this control.

The function can only be called on non-window-owning ('lodger') controls. 

Note: the container's window can be accessed using Window(), DrawableWindow(), or 
BackedUpWindow().

@param aWindow The backed up window owned by the container control.
@deprecated
*/
	{
	if(iFlags&EMemoryAllocationFailed)
		User::LeaveNoMemory();
	
	if(OwnsWindow())
        CloseWindow();

	iWin=&aWindow;
	iFlags|=EBackedUpWindow;
	}

EXPORT_C void CCoeControl::SetCornerAndSize(TGulAlignment aCorner,const TSize& aSize)
/** Sets the control's alignment and size. 

The control's position is calculated, relative to the screen, according to 
the requested alignment.

Note: calling this function results in a call to SizeChanged().

@param aCorner The alignment of the control.
@param aSize The control's size. */
	{ // the following assumes the window is being positioned wrt the screen
	TPoint pos=aCorner.InnerTopLeft(iCoeEnv->ScreenDevice()->SizeInPixels(),aSize);
	SetExtent(pos,aSize);
	}

/** Gets the number of controls contained in a compound control. 

There are 2 ways to implement a compound control. One way is to override this function. The other way
is to use the CCoeControlArray functionality (see the InitComponentArrayL method).

@return The number of component controls contained by this control. */
EXPORT_C TInt CCoeControl::CountComponentControls() const
	{
	CCoeControlArray* components = DoGetComponentArray(iData->DynamicDataStorage());
	return ( components ? components->Count() : 0 );
	}
 
EXPORT_C void CCoeControl::EnableDragEvents()
/** Requests pointer drag events.

This function should be called if a control is required to receive pointer 
drag and move events. The default behaviour for all controls is that pointer 
drag and move events are not delivered. 

The control framework does not provide a function to disable drag events at 
a later time, but this can be done via the Window Server API, by calling Window()->PointerFilter().

Note:

By default, pointer move events are not delivered, even after calling EnableDragEvents(), 
because they are not normally required in a pen-based system. The window server 
can be configured to deliver pointer move events if required, e.g. for a mouse-based 
system.

@see RWindowBase::PointerFilter() */
	{
	const TInt KPointerFilterBitsAllClear = 0;
	iWin->PointerFilter(EPointerFilterDrag, KPointerFilterBitsAllClear);
	}

EXPORT_C void CCoeControl::SetPointerCapture(TBool aCapture)
/** Sets pointer capture. 

Once set, pointer capture lasts until SetPointerCapture() is called on the 
control with aCapture=EFalse.

This function is typically used by dialogs, to discard any pointer events 
that occur outside of the dialog.

@param aCapture If ETrue, passes the following value as the argument to 
RWindowBase::SetPointerCapture(): RWindowBase::TCaptureFlagAllGroups|RWindowBase::TCaptureFlagEnabled, 
if the control's global capture flag is set to ETrue (see SetGloballyCapturing()) 
or RWindowBase::TCaptureFlagEnabled if the control's global capture flag is 
set to EFalse. If EFalse, passes EFalse as the argument to RWindowBase::SetPointerCapture().
@see RWindowBase::SetPointerCapture() */
	{
	TInt captureFlags=0;
	iFlags&=(~ECapturesPointer);
	if (aCapture)
		captureFlags=(iFlags&EGloballyCapturing? RWindowBase::TCaptureFlagAllGroups|RWindowBase::TCaptureFlagEnabled: RWindowBase::TCaptureFlagEnabled);
	iWin->SetPointerCapture(captureFlags);
	if (aCapture)
		{
		iFlags|=ECapturesPointer;
		CheckPointerEventPurge();
		}
	}

EXPORT_C TBool CCoeControl::CapturesPointer() const
/** Tests whether pointer capture is set for the control. 

This returns true if SetPointerCapture() has been called with aCapture=ETrue.

@return ETrue if pointer capture is set. EFalse if it isn't. */
	{
	return iFlags&ECapturesPointer;
	}

void CCoeControl::CheckPointerEventPurge() const
	{
	if (IsReadyToDraw())
		iCoeEnv->WsSession().PurgePointerEvents();
	}

EXPORT_C TInt CCoeControl::Index(const CCoeControl* aControl) const
/** Gets the index of a control that is a component of this control.

@param aControl The component control.
@return The index of the component control within the compound control, or 
KErrNotFound if aControl is not a component of this control. */
	{
	TInt count=CountComponentControls();
	for (TInt ii=0; ii<count; ii++)
		{
		if (aControl==ComponentControl(ii))
			return(ii);
		}
	return(KErrNotFound);
	}

EXPORT_C void CCoeControl::SetControlContext(MCoeControlContext* aContext)
/** Set the control context for this control.

@param aContext The context for this control. */
	{
	iContext=aContext;
	}

EXPORT_C void CCoeControl::CopyControlContextFrom(const CCoeControl* aControl)
/** Sets the control's context from another control.

@param aControl The control whose context is copied. */
	{
	iContext=aControl->iContext;
	}

EXPORT_C MCoeControlContext* CCoeControl::ControlContext() const
/** Gets the control context being used by this control. 

The function does not transfer ownership to the caller.

@return The control context. */
	{
	return iContext;
	}

EXPORT_C CCoeControl* CCoeControl::GrabbingComponent() const
/** Returns the component of this control which is grabbing the pointer 
    in systems implementing a single pointer. Or in a multi-pointer system where 
    single-pointer emulation is enabled on this control's window.

@return The component control that is currently grabbing the pointer. If no 
component of this control is grabbing the pointer, or if this 
is not a compound control, the function returns NULL. */
	{
	return GrabbingComponent(TAdvancedPointerEvent::EDefaultPointerNumber);
	}

EXPORT_C CCoeControl* CCoeControl::GrabbingComponent(TInt aPointer) const
/** Returns the component of this control which is grabbing the specified pointer.
    This method is to be used on controls who's window has multiple-pointer events enabled.

@return The component control that is currently grabbing the pointer. If no 
component of this control is grabbing the pointer, or if this 
is not a compound control, the function returns NULL. */
	{
	const TInt count=CountComponentControls();
	
	for (TInt ii=0; ii<count; ii++)
		{
		CCoeControl* ctrl=ComponentControl(ii);
		if ( ctrl && ctrl->IsGrabbed(aPointer) )
			{
			return(ctrl);
			}
		}
	
	return(NULL);
	}

TInt CCoeControl::FindColor(TInt aLogicalColor) const
	{
	CArrayFix<SColorOverride>* colorOverrides = DoGetColorOverrides(iData->DynamicDataStorage());
	if(colorOverrides)
		{
		TInt pos;
		TKeyArrayFix key(4,ECmpTInt);
		SColorOverride override;
		override.iLogicalColor=aLogicalColor;
		override.iColor=TRgb(); // ignore the actual color
		if (colorOverrides->Find(override,key,pos)==KErrNone)
			return pos;
		}
	return KErrNotFound;
	}


EXPORT_C void CCoeControl::OverrideColorL(TInt aLogicalColor,TRgb aColor)
/** Overrides the control's colour setting, as specified in the application's colour 
scheme. 

This function does not change the application's colour scheme. It changes 
the colour mapping used in this control only.

@param aLogicalColor The logical colour. Indicates which part of a control 
the physical colour maps to. The set of logical colours for a standard application 
are defined in TLogicalColor.
@param aColor The new physical colour to which the logical colour should be 
mapped.
@see GetColor() */
	{
	CArrayFix<SColorOverride>* colorOverrides = DoGetColorOverrides(iData->DynamicDataStorage());
	if (!colorOverrides)
		{
		colorOverrides=new(ELeave) CArrayFixFlat<SColorOverride>(2);
		if(DoSetColorOverrides(iData->DynamicDataStorage(), colorOverrides) == KErrNoMemory)
			{
			delete colorOverrides;
			User::LeaveNoMemory();
			}
		}
	
	SColorOverride override;
	override.iLogicalColor=aLogicalColor;
	override.iColor=aColor;
	const TInt index=FindColor(aLogicalColor);
	if (index==KErrNotFound)
		colorOverrides->AppendL(override);
	else
		(*colorOverrides)[index]=override;

	const TInt count=CountComponentControls();
	for (TInt ii=0; ii<count; ii++)
		ComponentControl(ii)->OverrideColorL(aLogicalColor,aColor);
	}

EXPORT_C TBool CCoeControl::GetColor(TInt aLogicalColor,TRgb& aColor) const
/** Gets the overridden physical colour. 

This is the colour which has been mapped to the logical colour specified by 
a call to OverrideColorL(). If the logical colour specified has not been overridden, 
the aColor value is not changed.

@param aLogicalColor The logical colour for which the corresponding physical 
colour will be retrieved. The set of logical colours for a standard GUI application 
are defined in TLogicalColor.
@param aColor On return, contains the physical colour which has been mapped 
to aLogicalColour by a call to OverrideColorL().
@return ETrue if aLogicalColour has been overridden, EFalse otherwise. */
	{
	CArrayFix<SColorOverride>* colorOverrides = DoGetColorOverrides(iData->DynamicDataStorage());
	if(!colorOverrides)
		return EFalse;
	
	const TInt index=FindColor(aLogicalColor);
	if(index==KErrNotFound)
		return EFalse;
	
	aColor=(*colorOverrides)[index].iColor;
	return ETrue;
	}


/**
Gets the input capabilities of the control and all its components.

@since     6.0
@return   "TCoeInputCapabilities"
            The input capabilities of the control.
*/
void CCoeControl::RecursivelyMergeInputCapabilities(TCoeInputCapabilities& aInputCapabilities) const
	{
	if (!IsBeingDestroyed())
		{
		if (IsFocused())
			{
			aInputCapabilities.MergeWith(InputCapabilities());
			}
		for (TInt i=CountComponentControls()-1; i>=0; --i)
			{
			ComponentControl(i)->RecursivelyMergeInputCapabilities(aInputCapabilities);
			}
		}
	}

/** Gets the input capabilities of the control and all its components.

@return The input capabilities of the control. */
EXPORT_C TCoeInputCapabilities CCoeControl::RecursivelyMergedInputCapabilities() const
	{
	TCoeInputCapabilities inputCapabilities(TCoeInputCapabilities::ENone);
	RecursivelyMergeInputCapabilities(inputCapabilities);
	return inputCapabilities;
	}


#ifndef _DEBUG
void CCoeControl::WriteInternalStateNowL(RWriteStream&) const
	{}
#else
void CCoeControl::WriteInternalStateNowL(RWriteStream& aWriteStream) const
	{
	WriteInternalStateL(aWriteStream);
	}
#endif


#ifdef _DEBUG


/** Writes the internal state of the control and its components to aWriteStream.
Does nothing in release builds.
This function is designed to be overidden and base called by subclasses 
wishing to output state information. 

If overriding WriteInternalStateL(), the implementation must include a base call to CCoeControl's
WriteInternalStateL().*/
EXPORT_C void CCoeControl::WriteInternalStateL(RWriteStream& aWriteStream) const
	{
	_LIT8(KCoeLitControlSt,"<CCoeControl>\r\n");
	_LIT8(KCoeLitControlEnd,"</CCoeControl>\r\n");
	TBuf8<100> element;

	aWriteStream.WriteL(KCoeLitControlSt);

	_LIT8(KCoeLitPosition, "<iPosition iX=\"%d\" iY=\"%d\"/>\r\n");
	element.Format(KCoeLitPosition,iPosition.iX,iPosition.iY);
	aWriteStream.WriteL(element);

	_LIT8(KCoeLitSize, "<iSize iWidth=\"%d\" iHeight=\"%d\"/>\r\n");
	element.Format(KCoeLitSize,iSize.iWidth,iSize.iHeight);
	aWriteStream.WriteL(element);

	// extension stuff
	_LIT8(KCoeLitFlags, "<Flags value=\"0x%08x\"/>\r\n");
	element.Format(KCoeLitFlags,iFlags);
	aWriteStream.WriteL(element);

	_LIT8(KCoeLitColors, "<ColorOverrides>\r\n");
	_LIT8(KCoeLitColorsEnd, "</ColorOverrides>\r\n");
	aWriteStream.WriteL(KCoeLitColors);
	
	CArrayFix<SColorOverride>* colorOverrides = DoGetColorOverrides(iData->DynamicDataStorage());
	if (colorOverrides)
		{
		TBuf8<8> integer;
		const TInt count=colorOverrides->Count();
		for(TInt i=0; i<count; i++)
			{
			const SColorOverride& colOvrride=(*colorOverrides)[i];
			integer.Num(MAKE_TINT64(0,colOvrride.iColor.Color16M()));
			aWriteStream.WriteL(integer);
			integer.Num(MAKE_TINT64(0,colOvrride.iLogicalColor));
			aWriteStream.WriteL(integer);
			}
		}
	aWriteStream.WriteL(KCoeLitColorsEnd);

	const TInt components=CountComponentControls();
	_LIT8(KCoeLitComponent,"<Component>\r\n");
	_LIT8(KCoeLitComponentEnd,"</Component>\r\n");
	//
	for(TInt i=0;i<components;i++)
		{
		aWriteStream.WriteL(KCoeLitComponent);
		//
		ComponentControl(i)->WriteInternalStateL(aWriteStream);
		//
		aWriteStream.WriteL(KCoeLitComponentEnd);
		}
	aWriteStream.WriteL(KCoeLitControlEnd);
	}
#else
EXPORT_C void CCoeControl::WriteInternalStateL(RWriteStream&) const
	{}
#endif

EXPORT_C void CCoeControl::Reserved_2()
	{
	}

/** Sets the context - that is, the enclosing parent control - for this control. 
If setting aParent as MopParent of this control creates a cyclic relationship, 
this method will do nothing.

@param aParent The parent object which is the context for the control. */
EXPORT_C void CCoeControl::SetMopParent(MObjectProvider* aParent)
	{
	if (aParent)
		{
		const MObjectProvider* mopParent = aParent->FindParent(static_cast<MObjectProvider*>(this)); 	
		if (mopParent)	
			return;
		}
	iMopParent = aParent;
	}

/** Retrieves an object of the same type as that encapsulated in aId.

This function is used to allow controls to ask their owners for access to 
other objects that they own.

Other than in the case where NULL is returned, the object returned must be 
of the same object type - that is, the ETypeId member of the object pointed 
to by the pointer returned by this function must be equal to the iUid member 
of aId.

@param aId An encapsulated object type ID.
@return Encapsulates the pointer to the object provided. Note that the encapsulated 
pointer may be NULL. */
EXPORT_C TTypeUid::Ptr CCoeControl::MopSupplyObject(TTypeUid /*aId*/)
	{
	return TTypeUid::Null();
	}


/** Retrieves the control's parent.

This function may be overridden to continue the 
chain of object providers which are to be asked to supply an object.

When overriding this function for any given class of control, it is important 
to ensure that the function does not return, either directly or indirectly, 
a pointer to the instance of that class on which the function was called. 
For example, suppose that bar is an object of class foo. The override for 
the class foo could legitimately return a pointer to the object provider in 
which bar is contained, but must never return a pointer either to bar or to 
an object provider which may return bar. Failure to observe this restriction 
may result in an infinite loop.

@return A pointer to an object provider, or NULL if none is defined. 
@publishedAll 
@released */
EXPORT_C MObjectProvider* CCoeControl::MopNext()
	{
	return iMopParent;
	}

// TEXT DRAWER


/**
Gets the text drawer to be used for the control.
This method returns a reference simply because the return value must never be NULL.
The ownership transfer rules of the returned CCoeTextDrawerBase object obey specific rules.
If the CCoeTextDrawerBase::IsReusable() flag is set then the caller must call Reset when the object
is not needed anymore else it should simply delete the object. The XCoeTextDrawer class is a wrapper
around the CCoeTextDrawerBase that will implement this logic automatically.
The method will start with the default text drawer. 
It then allows  the childs background control to change the text drawer if the child itself is window owning.
Otherwise only the  parent control can change the text drawer.


@param aKey This parameter can be used by clients that need some custom behaviour. The framework
doesn't use this parameter.
@return reference to a CCoeTextDrawerBase object
*/
EXPORT_C CCoeTextDrawerBase& CCoeControl::TextDrawer(TInt aKey) const
	{
 	// Get the default text drawer
	CCoeTextDrawerBase* textDrawer = &iCoeEnv->DefaultTextDrawer();
 
 	// Retrieve a background object
	const MCoeControlBackground* background = FindBackground();
 
 	// Let the text drawer be updated according to the background object
	if(background)
		background->GetTextDrawer(textDrawer, this);
	
	// Let the text drawer be updated according to the text drawers of the
	// parent hierarchy.
	RecursivelyMergeTextDrawers(textDrawer, this, aKey);
	
	return *textDrawer;
	}


/**
This method recursively merges the control's parents' text drawers if it is non-window owning. If a parent control creates 
a new text drawer, this method makes sure that the old one is deleted or reset.



@param aTextDrawer reference to the CCoeTextDrawerBase object to be updated
@param aKey TInt
@return void
*/
void CCoeControl::RecursivelyMergeTextDrawers(CCoeTextDrawerBase*& aTextDrawer, 
	const CCoeControl* aDrawingControl, TInt aKey) const
	{
	const CCoeControl* parent = Parent();
	if(parent && !OwnsWindow())
		parent->RecursivelyMergeTextDrawers(aTextDrawer, aDrawingControl, aKey);
			
	CCoeTextDrawerBase* oldTextDrawer = aTextDrawer;
	GetTextDrawer(aTextDrawer, aDrawingControl, aKey);

	if(!aTextDrawer)	// in case allocation of new text drawer failed
		aTextDrawer = oldTextDrawer;
	
	if(aTextDrawer != oldTextDrawer)	// delete or reset the old text drawer
										// if a new one was created
		{
		if(!oldTextDrawer->IsReusable())
			delete oldTextDrawer;
		else
			oldTextDrawer->Reset();
		}
	}


/**
Controls that want to change or replace the text drawer that it or its children 
controls use shall override this method. The aTextDrawer argument is guaranteed 
never to be NULL, and the control can choose to modify it or create a new
text drawer in its place.
*/ 
EXPORT_C void CCoeControl::GetTextDrawer(CCoeTextDrawerBase*& /*aTextDrawer*/, const CCoeControl* /*aDrawingControl*/, TInt /*aKey*/) const
	{}

 
EXPORT_C CCoeControl* CCoeControl::Parent()
	{
	return DoGetParent(iData->DynamicDataStorage());
	}

EXPORT_C const CCoeControl* CCoeControl::Parent() const
	{
	return DoGetParent(iData->DynamicDataStorage());
	}

/**
Gets the offset to the first text baseline relative to the top of the control.

The default implementation calls CalcTextBaselineOffset of the layout manager if
one is installed. It returns 0 if no layout manager is installed.

Derived classes that don't want to use the layout manager and still want to
return a baseline offset should re-implement this function.

@param aRect The offset of the baseline may depend on the size of the control. This argument specifies the size to use when computing the baseline offset.
@return The offset of the baseline from the top of the control.
*/
EXPORT_C TInt CCoeControl::TextBaselineOffset(const TSize& aSize) const
	{
	TInt retval = 0;
	if(LayoutManager())
		retval = LayoutManager()->CalcTextBaselineOffset(*this, aSize);
	return retval;
	}

/**
Sets the spacing between text baselines.

The default implementation calls SetTextBaselineSpacing of the layout manager if one is installed. It does nothing if there is no layout manager.

Derived classes that don't want to use the layout manager and still want to do something when the this function is called should re-implement it.

@param aBaselineSpacing The baseline spacing i.e. the space in pixels between the text baselines.
*/
EXPORT_C void CCoeControl::SetTextBaselineSpacing(TInt aBaselineSpacing)
	{
	if(LayoutManager())
		LayoutManager()->SetTextBaselineSpacing(aBaselineSpacing);
	}

/**
 * Returns a Unique Handle (identifier) previously allocated to the control.
 *
 * @see SetUniqueHandle
 * @return Previously allocated value.
 */
EXPORT_C TInt CCoeControl::UniqueHandle() const 
	{
	return DoGetUniqueHandle(iData->DynamicDataStorage());
	}
	
/**
 * Sets a Unique Handle (identifier).  That the number is unique is the perogative
 * of the caller!
 *
 * @see UniqueHandle()
 * @param a number.  This number is used to identify this control
 * @return Standard error code
 */
EXPORT_C TInt CCoeControl::SetUniqueHandle( TInt aUniqueHandle )
	{
	return DoSetUniqueHandle(iData->DynamicDataStorage(), aUniqueHandle);
	}
	
/** Sets the layout manager

If the control already has a layout manager, its <code>MCoeLayoutManager::Detatch()</code> is called.
<code>MCoeLayoutManager::Attach()</code> is called on <code>aLayout</code>

The control doesn't take ownership of the Layout manager.

@see MCoeLayoutManager::Attach
@param aLayout The new layout manager, <code>NULL</code> if you just want to remove the current
layout manager.
*/
EXPORT_C void CCoeControl::SetLayoutManagerL(MCoeLayoutManager* aLayout)
	{
	MCoeLayoutManager* layout = LayoutManager();
	if (layout)
		layout->Detach(*this);

	User::LeaveIfError(DoSetLayoutManager(iData->DynamicDataStorage(), NULL));
	
	if (aLayout)
		aLayout->AttachL(*this);
	
	User::LeaveIfError(DoSetLayoutManager(iData->DynamicDataStorage(), aLayout));
	}

/** Gets the layout manager
@return The current layout manager, or <code>NULL</code> if the control has no layout manager
*/
EXPORT_C MCoeLayoutManager* CCoeControl::LayoutManager() const
	{
	// Try to retrieve the layout manager if one has been set, otherwise return NULL.
	return DoGetLayoutManager(iData->DynamicDataStorage());
	}

/** Requests a relayout

The default implementation is to call the parents <code>RequestRelayout()</code>.

Should normally be overridden by top-level controls, such as scrollable containers. Classes that
override this function must ensure that they don't cause infinite loops, since a relayout might
cause calls to <code>RequestRelayout()</code> itself, This might be solved like this:
@code
TBool CAnyControl::RequestRelayout(const CCoeControl* aChildControl)
	{
	if(iRelayoutInProgress) return EFalse;
	iRelayoutInProgress = ETrue;
	//perform the relayout
	iRelayoutInProgress = EFalse;
	return ETrue;
	}
@endcode

When the request is addressed the requesting control knows that its <code>SizeChanged()</code>
will be called.

@param aChildControl The child control that requests the relayout, might be <code>NULL</code>
@return <code>ETrue</code> if the request is addressed, otherwise <code>EFalse</code>
*/
EXPORT_C TBool CCoeControl::RequestRelayout(const CCoeControl* aChildControl)
	{
	TBool reqComplete = EFalse;
	if(aChildControl && !aChildControl->IsActivated())
		{
		reqComplete = EFalse;
		}
	else if(Parent())
		{
		reqComplete = Parent()->RequestRelayout(this);
		}
	return reqComplete;
	}
		

void CCoeControl::RemoveFromParent()	
	{
	CCoeControl* parent = Parent();
	if (parent)
		{
		parent->Components().Remove(this);
		}
	}

/**
Set the status of the report control state change.
@param aState Set the state as Enable or Disable to control the report control state change. 
@see SetDimmed(), MakeVisible()
*/
EXPORT_C void CCoeControl::EnableReportControlStateChange(TBool aState)
	{	
	if(aState)
		{
		iFlags |= EReportControlStateChange;
		}
	else
		{
		iFlags &= ~EReportControlStateChange;
		}
	}

/** @internalComponent */
EXPORT_C void CCoeControl::Reserved_CCoeControl_8()
	{	
	}
	
/** @internalComponent */
EXPORT_C void CCoeControl::Reserved_CCoeControl_9()
	{	
	}

/** @internalComponent */
EXPORT_C void CCoeControl::Reserved_CCoeControl_10()
	{	
	}
	
/** @internalComponent */
EXPORT_C void CCoeControl::Reserved_CCoeControl_11()
	{	
	}
	
/** @internalComponent */
EXPORT_C void CCoeControl::Reserved_CCoeControl_12()
	{	
	}
	
/** @internalComponent */
EXPORT_C void CCoeControl::Reserved_CCoeControl_13()
	{	
	}	

/**
Default empty method.
@param aTextDrawer Not used.
@param aDrawingControl Not used.
*/
EXPORT_C void MCoeControlBackground::GetTextDrawer(CCoeTextDrawerBase*& /*aTextDrawer*/, const CCoeControl* /*aDrawingControl*/) const
{}
 
// For future use
EXPORT_C  void MCoeControlBackground::MCoeControlBackground_Reserved1() {} 
EXPORT_C  void MCoeControlBackground::MCoeControlBackground_Reserved2() {} 
EXPORT_C  void MCoeControlBackground::MCoeControlBackground_Reserved3() {} 
EXPORT_C  void MCoeControlBackground::MCoeControlBackground_Reserved4() {} 
EXPORT_C  void MCoeControlBackground::MCoeControlBackground_Reserved5() {} 

	
//
// From coecntrl.h (MCoeLayoutManager)
//
	
EXPORT_C MCoeLayoutManager::MCoeLayoutManager() : iMCoeLayoutManager_Reserved1(0) {}
EXPORT_C void MCoeLayoutManager::Reserved_MCoeLayoutManager_1() {}
EXPORT_C void MCoeLayoutManager::Reserved_MCoeLayoutManager_2() {}
EXPORT_C void MCoeLayoutManager::Reserved_MCoeLayoutManager_3() {}
EXPORT_C void MCoeLayoutManager::Reserved_MCoeLayoutManager_4() {}
EXPORT_C void MCoeLayoutManager::Reserved_MCoeLayoutManager_5() {}
EXPORT_C void MCoeLayoutManager::Reserved_MCoeLayoutManager_6() {}
EXPORT_C void MCoeLayoutManager::Reserved_MCoeLayoutManager_7() {}
EXPORT_C void MCoeLayoutManager::Reserved_MCoeLayoutManager_8() {}
EXPORT_C void MCoeLayoutManager::Reserved_MCoeLayoutManager_9() {}
EXPORT_C void MCoeLayoutManager::Reserved_MCoeLayoutManager_10() {}
EXPORT_C void MCoeLayoutManager::Reserved_MCoeLayoutManager_11() {}

//
// From coecntrl.h (MCoeControlBackground)
//
	
EXPORT_C MCoeControlBackground::MCoeControlBackground()	{}
	
//
// From coecntrl.h (MCoeControlHitTest)
//
	
EXPORT_C MCoeControlHitTest::MCoeControlHitTest() : iMCoeControlHitTest_Reserved1(0) {}
EXPORT_C void MCoeControlHitTest::MCoeControlHitTest_Reserved1() {}
EXPORT_C void MCoeControlHitTest::MCoeControlHitTest_Reserved2() {}


//
// From coecobs.h (MCoeControlObserver)
//

EXPORT_C MCoeControlObserver::MCoeControlObserver() : iMCoeControlObserver_Reserved1(0) {}
EXPORT_C void MCoeControlObserver::MCoeControlObserver_Reserved1() {}
EXPORT_C void MCoeControlObserver::MCoeControlObserver_Reserved2() {}
