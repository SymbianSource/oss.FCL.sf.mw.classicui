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

#ifndef __COECOBS_H__
#define __COECOBS_H__

#include <e32base.h>
#include <coemop.h>

class CCoeControl;

class MCoeControlObserver
/** Interface for a control to send events to its observer control. 

@publishedAll 
@released */
	{
public:
	/** Observer event types. */
	enum TCoeEvent
		{
		/** Request exit. 
		This event is used to indicate exit from a mode when 
		the user has completed an operation 'successfully'. For example, this 
		event might be sent when the user has a choice list open and presses 
		enter to select an item. The UI Control Framework does not use this 
		event itself. */
		EEventRequestExit,
		/** Request cancel.
		This event is used to indicate exit from a mode when the user has cancelled 
		the operation that caused entry into the mode originally. For example, this 
		event might be sent when the user presses escape to close the list and leave 
		the choice as it was. The UI Control Framework does not use this event itself. */
		EEventRequestCancel,
		/** Request focus.
		This event is notified by the UI Control Framework during pointer down event 
		processing after EEventPrepareFocusTransition is handled. */
		EEventRequestFocus,
		/** Prepare focus transition.
		This event is notified by the UI Control Framework during pointer down event 
		processing if the control does not yet have, but could get, focus. */
		EEventPrepareFocusTransition,
		/** State changed.
		This event can be used by a control to report that some piece of internal 
		data has changed, and hence that any observer should be notified accordingly. 
		The UI Control Framework does not use this value itself. */
		EEventStateChanged,
		/** Interaction refused.
		This event is notified by the UI Control Framework during pointer down event 
		processing if the control is dimmed (disabled). */
		EEventInteractionRefused
		};
public:
	/** Handles an event from an observed control.
	
	This function is called when a control for which this control is the observer 
	calls CCoeControl::ReportEventL(). It should be implemented by the observer 
	control, and should handle all events sent by controls it observes.
	
	@param aControl The control that sent the event.
	@param aEventType The event type. */
	virtual void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEventType)=0;
protected:
    IMPORT_C MCoeControlObserver();
    
private:
    IMPORT_C virtual void MCoeControlObserver_Reserved1();
    IMPORT_C virtual void MCoeControlObserver_Reserved2();
    
private:
    TInt iMCoeControlObserver_Reserved1;
	};

class MCoeControlStateObserver
/** This class defines an interface which will given notification of when a CCoeControl
changes its visibility or dimmed state.

@publishedAll
@released */
	{
	friend class CCoeControl;
public:
	/** The MObjectProvider framework should use this UID to know when to return a concrete instance of this interface. */
	DECLARE_TYPE_ID(0x10285A45)
	enum TCoeState
		{
		/** This enum is used to say that the control has changed its Dimmed state */
		EStateDimmed,
		/** This enum is used to say that the control has changed its Visibility state */
		EStateVisibility
		};
private:
	/**
	If an object implementing this interface has been attached to the MObjectProvider
	hierarchy in which a CCoeControl is a member, any call to the CCoeControl's
	SetDimmed() or MakeVisible() (that results in an actual state change) will trigger
	a call to this interface.

	@param aControl	A pointer to the control that has changed.
	@param aState	An enum from TCoeState to say how the control has changed.
	@return 		A system wide error code, currently ignored but may not be in future.*/
	virtual TInt HandleControlStateChange(CCoeControl* aControl,TCoeState aState)=0;
	};

#endif	// __COECOBS_H__
