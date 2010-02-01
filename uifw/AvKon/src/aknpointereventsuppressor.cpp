/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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
#include <aknpointereventsuppressor.h>
#include <aknlayoutscalable_avkon.cdl.h>

const TInt KAknPointerEventSuppressorDefaultMaxTapDuration = 400000;	// 0.4 seconds
const TInt KAknPointerEventSuppressorDefaultMinInterDragInterval = 0;

EXPORT_C CAknPointerEventSuppressor* CAknPointerEventSuppressor::NewL()
	{
	return new(ELeave) CAknPointerEventSuppressor;
	}

EXPORT_C CAknPointerEventSuppressor::~CAknPointerEventSuppressor()
	{
	}

CAknPointerEventSuppressor::CAknPointerEventSuppressor()
: iMaxTapDuration(KAknPointerEventSuppressorDefaultMaxTapDuration),
  iMinInterDragInterval(KAknPointerEventSuppressorDefaultMinInterDragInterval),
  iTap(EFalse)
  	{
  	// default move limit is 6 units, which seems to be a forgiving value for finger touch
    TInt maxMove = AknLayoutScalable_Avkon::aid_value_unit2().LayoutLine().iW * 6 / 10;
	iMaxTapMove.iWidth = maxMove;
	iMaxTapMove.iHeight = maxMove;
  	}

EXPORT_C TBool CAknPointerEventSuppressor::SuppressPointerEvent(const TPointerEvent& aPointerEvent)
	{
	switch (aPointerEvent.iType)
		{
		case TPointerEvent::EButton1Down:
			iDownTime.HomeTime();
			iTap = ETrue;
			iDownPos = aPointerEvent.iPosition;
			iLastEventTime = iDownTime;
			break;
			
		case TPointerEvent::EDrag:
			{
			TTime now;
			now.HomeTime();
			if (iTap)
				{
				TPoint delta = aPointerEvent.iPosition - iDownPos;
				if (Abs(delta.iX) > iMaxTapMove.iWidth ||
					Abs(delta.iY) > iMaxTapMove.iHeight ||
					now.MicroSecondsFrom(iDownTime) >= iMaxTapDuration)
					{
					// This touch action has gone outside the parameters of a tap
					// the drag event should be handled
					iTap = EFalse;
					iLastEventTime = now;
					return EFalse;
					}
				else
					{
					// still a tap, so suppress the drag event
					return ETrue;
					}
				}
			else if (now.MicroSecondsFrom(iLastEventTime) < iMinInterDragInterval)
				{
				// too soon since the last drag, suppress it
				return ETrue;
				}

			// this drag event should be handled
			iLastEventTime = now;
			break;
			}

		case TPointerEvent::EButton1Up:
			iTap = EFalse;
			break;

		default:
			break;
		}
	
	// all non-drag events should be handled
	return EFalse;
	}

EXPORT_C void CAknPointerEventSuppressor::SetMaxTapDuration(TTimeIntervalMicroSeconds aDuration)
	{
	iMaxTapDuration = aDuration;
	}

EXPORT_C void CAknPointerEventSuppressor::SetMaxTapMove(TSize aMoveLimits)
	{
	iMaxTapMove = aMoveLimits;
	}
	
EXPORT_C void CAknPointerEventSuppressor::SetMinInterDragInterval(TTimeIntervalMicroSeconds aInterval)
	{
	iMinInterDragInterval = aInterval;
	}

