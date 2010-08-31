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
* Description:  Test navigation_pane_api
*
*/


#ifndef C_TESTSDKNAVITABOBSERVER_H
#define C_TESTSDKNAVITABOBSERVER_H

// INCLUDES
#include <akntabobserver.h>

// CLASS DECLARATION
class MAknTabObserver;

/**
 * Observer class for CAknTabGroup
 */
class CTestSDKNaviTabObserver : public CBase, public MAknTabObserver
    {
public: //from MAknTabObserver

    /**
     * Method for handling tab change events in observed classes. 
     * 
     * @param aIndex Index of the active tab.
     *
     */
    virtual void TabChangedL(TInt aIndex);

    };

#endif // C_TESTSDKNAVITABOBSERVER_H
