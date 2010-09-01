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
*     Interface class for tab group observer.
*
*
*
*/


#ifndef AKNTABOBSERVER_H
#define AKNTABOBSERVER_H

#include <e32base.h>

class MAknTabObserver
{
public:

   	/**
     * Method for handling tab change events in observed classes. 
     * 
     * @param aIndex Index of the active tab.
     *
     */
	virtual void TabChangedL(TInt aIndex) = 0;
};


#endif
