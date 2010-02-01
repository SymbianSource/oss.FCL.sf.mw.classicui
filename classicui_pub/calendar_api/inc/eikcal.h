/*
* Copyright (c) 2002-2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Interface class for EIKON calendar observer.
*
*/


#ifndef __EIKCAL_H__
#define __EIKCAL_H__

#include <eikbctrl.h>
#include <eikscbut.h>
#include <eikcmbut.h>

/**
 * Calendar observer interface.
 *
 * <b> Not used in S60. </b>
 *
 * @lib eikctl.lib
 * @since S60 0.9
 */
class MEikCalendarObserver
	{
public:

    /**
     * <b> Not used in S60. </b>
     */
	virtual void GetMinimumAndMaximumAndInitialDatesForCalendarL(
	                                            TTime& aMinimumDate,
	                                            TTime& aMaximumDate,
	                                            TTime& aInitialDate) const=0;
	
	/**
	 * <b> Not used in S60. </b>
     */
	virtual void SetDateFromCalendarAndDrawNow(const TTime& aDate)=0;
	};

#endif // __EIKCAL_H__
