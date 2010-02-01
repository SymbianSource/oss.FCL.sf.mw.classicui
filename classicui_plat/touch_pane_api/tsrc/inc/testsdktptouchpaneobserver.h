/*
* Copyright (c) 2006 Nokia Corporation and/or its subsidiary(-ies).
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

#ifndef C_TESTSDKTPTOUCHPANEOBSERVER_H
#define C_TESTSDKTPTOUCHPANEOBSERVER_H

#include <akntouchpane.h>
#include <akntouchpaneobserver.h> 

/**
 *  CTestTouchPaneObserver class
 */
class CTestSDKTPTouchPaneObserver: public CBase, public MAknTouchPaneObserver
    { 
    /**
    * Handles a change in the size or position of touch pane.
    * This function is called when touch pane changes its size or position.
    */
    void HandleTouchPaneSizeChange();
    };

#endif /*C_TESTSDKTPTOUCHPANEOBSERVER_H*/
