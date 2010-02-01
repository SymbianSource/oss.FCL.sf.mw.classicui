/*
* Copyright (c) 2002-2005 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Interface for handling control's state change.
*
*/



#if !defined(__AKNEDSTSOBS_H__)
#define __AKNEDSTSOBS_H__

// FORWARD DECLERATIONS
class CAknEdwinState;


// CLASS DECLERATION
/**
* Interface for handling control's state change.
* 
* @since Series 60 0.9
*/
class MAknEdStateObserver
	{
public:
	/** 
    * Observer event types.
    */
	enum EAknEdwinStateEvent
        {
        /** The state has been updated */ 
        EAknEdwinStateEventStateUpdate, 
        /** The input mode has been updated */     
        EAknEdwinStateInputModeUpdate,
        /** The case mode has been updated */   
        EAknEdwinStateCaseModeUpdate,
        /** The local language has been updated */    
        EAknEdwinStateLocalLanguageUpdate, 
        /** The flags have been updated */  
        EAknEdwinStateFlagsUpdate,
        /** The edwin state needs to be sync'ed */
        EAknSyncEdwinState,
        /** Cursor position has changed in editor */
        EAknCursorPositionChanged,
        /** VKB/HW activation request */
        EAknActivatePenInputRequest,
        /** Prompt Text has changed */
        EAknEdwinStatePromptUpdate,
        /** editor is destroyed */
        EAknEdwinDestroy,
        /** VKB/HW close request */
        EAknClosePenInputRequest
        };
public:
	/**
    * Handles an state event from a observed control.
    * Pure virtual function that is called when a control, for which this
    * control is the observer, calls @c ReportAknedstateEventL().
    * It should be implemented by the observer control and should handle all
    * state events sent by controls it observed. 
    * @param aAknEdwinState The control that sent the event.
    * @param aEventType The event type defined in @c EAknEdwinStateEvent.
    */
	virtual void HandleAknEdwinStateEventL(CAknEdwinState* aAknEdwinState,
		EAknEdwinStateEvent aEventType) = 0;
	};

#endif
