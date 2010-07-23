/*
* Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).
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

#ifndef AKNPOINTEREVENTSUPPRESSOR_H
#define AKNPOINTEREVENTSUPPRESSOR_H

//  INCLUDES
#include <coecntrl.h>

// CLASS DECLARATION

/**
*  Utility class for removing unwanted pointer events, for instance
*  when distinguishing tap events from intended drags.
*
*  Usage pattern, where iSuppressor is a CAknPointerEventSuppressor*:
*
*  void CMyControl::HandlePointerEventL(const TPointerEvent& aPointerEvent)
*  	{
*  	if (iSuppressor->SuppressPointerEvent(aPointerEvent))
*  		return;
*  	
*  	switch (aPointerEvent.iType)
*  		{
*  		case TPointerEvent::EButton1Down:
*  			iTap = ETrue;
*  			break;
*  		case TPointerEvent::EButton1Up:
*  			if (iTap)
*  				HandleTapL(aPointerEvent);
*  			break;
*  		case TPointerEvent::EDrag:
*  			iTap = EFalse;
*  			HandleDragL(aPointerEvent);
*  			break;
*  		default:
*  			break;
*  		}
*  	}
*
*  @since S60 5.0
*/
NONSHARABLE_CLASS(CAknPointerEventSuppressor) : public CBase
	{
public:
	/**
	* Factory function
	*
	* This creates a pointer event suppressor that will suppress
	* drag events while the pointer interaction may be a tap.
	*/
	IMPORT_C static CAknPointerEventSuppressor* NewL();
    /**
    * Destructor.
    */    
	IMPORT_C ~CAknPointerEventSuppressor();
	
	/**
	* Tests whether a pointer event should be suppressed.
	*
	* A control that wants pointer event suppression should feed
	* all pointer events to this function. It will return ETrue if
	* the pointer event should be ignored by the control.
	* Only controls that have unrelated behaviour on tap and drag
	* actions need to use pointer event suppression.
	*
	* If this class is used to suppress drag events during a possible
	* tap, and this function does not suppress a drag event, the
	* client can be sure that a drag action is happening.
	*
	* @param aPointerEvent the pointer event which may need to be suppressed.
	* @return ETrue if the pointer event should be suppressed, or EFalse if it should be handled.
	*/
	IMPORT_C TBool SuppressPointerEvent(const TPointerEvent& aPointerEvent);
	/**
	* Set the maximum time period that drag events should be
	* ignored during a pointer interaction.
	*
	* @param aDuration the maximum duration of a tap action.
	*/
	IMPORT_C void SetMaxTapDuration(TTimeIntervalMicroSeconds aDuration);
	/**
	* Set the maximum pointer movement for which drag events
	* should be ignored during a pointer interaction.
	*
	* @param aMoveLimits the pixel movement limits within which a touch action is considered a tap
	*/
	IMPORT_C void SetMaxTapMove(TSize aMoveLimits);
	/**
	* Set the minimum time between drag events.
	* This can be used to reduce the frequency of drag event reception when
	* events are not desired at maximum speed.
	*
	* @param aInterval the minimum interval between which drag events are wanted
	*/
	IMPORT_C void SetMinInterDragInterval(TTimeIntervalMicroSeconds aInterval);

private:
	CAknPointerEventSuppressor();

private:
	TTimeIntervalMicroSeconds iMaxTapDuration;
	TSize iMaxTapMove;
	TTimeIntervalMicroSeconds iMinInterDragInterval;
	TTime iDownTime;
	TPoint iDownPos;
	TBool iTap;
	TTime iLastEventTime;
	};


#endif