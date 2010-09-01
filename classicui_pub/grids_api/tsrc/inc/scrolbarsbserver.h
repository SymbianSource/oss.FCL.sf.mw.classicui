/*
* Copyright (c) 2002 - 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Test grids_api
*
*/


#ifndef C_SCROLLBAROBSERVER_H
#define C_SCROLLBAROBSERVER_H

/*
 * Include files
 */
#include<eiksbobs.h> 
#include<e32base.h>

/*
 * This class inherit from MEidSsrollBarObserver class for construction special paramer
 */
class CStifScrollBarObserver:public CBase,public MEikScrollBarObserver
    {
public:
    /*
     * Constructor
     */
    CStifScrollBarObserver();
    /*
     * Destructor
     */
    ~CStifScrollBarObserver();
    /*
     * This function inherit from MEikScrollBarObserver class
     */
    void HandleScrollEventL(CEikScrollBar* aScrollBar, TEikScrollEvent aEventType);
    };

#endif

/*
 * End file
 */
