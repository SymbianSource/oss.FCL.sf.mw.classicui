/*
* Copyright (c) 2002 Nokia Corporation and/or its subsidiary(-ies).
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
*     Interface class for indicator observer. This observer is used
*     by applications to observe when an indicator of that particular
*     application is tapped.
*
*
*
*/


#ifndef AKNINDICATOROBSERVER_H
#define AKNINDICATOROBSERVER_H

#include <e32base.h>

class MAknIndicatorObserver
    {
    public:
    enum TIndicatorEvents
        {
        EIndicatorItemTapped = 1
        };
        
	public:
    	/**
        * HandleIndicatorEventL function for handling indicator events
        * in observed classes 
        * 
        * @param aIndicatorUid the uid of indicator which causes this event
        * @param aEventID TIndicatorEvents event to be handled 
        */
		virtual void HandleIndicatorEventL(TUid aIndicatorUid, TInt aEventID ) = 0;
    };


#endif //AKNINDICATOROBSERVER_H
