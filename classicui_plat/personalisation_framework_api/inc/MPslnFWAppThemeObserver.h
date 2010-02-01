/*
* Copyright (c) 2005-2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Observer interface for application specific theme events.
*
*/


#ifndef MPSLNFWAPPTHEMEOBSERVER_H
#define MPSLNFWAPPTHEMEOBSERVER_H

#include <e32base.h>
#include <XnThemeManagement.h>

class CXnODT;

/**
 *  Observer interface for application specific theme events.
 *
 *  PslnFramework passes events from XUIKON through this observer.
 *
 *  @lib PslnFramework.lib
 *  @since S60 3.1
 */
class MPslnFWAppThemeObserver
    {

public:

    /**
     * New indication of application's theme list. Implementation of this
     * MUST NOT leave.
     *
     * @param aMessage indication message. Can be one of the following:
     * 
     *   EXnGetListHeadersEmpty    - no themes currently available, please destroy 
     *                               existing list of themes (if given previously)
     *   EXnGetListHeadersFailed   - theme retrieval failed, updates are not working.
     *   EXnServiceRequestCanceled - theme retrieval has been cancelled.
     *   EXnServiceRequestError    - an error occured while retrieving latest theme, 
     *                               theme updation is still ongoing.
     */
    virtual void HandleMessage( TXnServiceCompletedMessage aMessage ) = 0;

    /**
     * New indication of application's theme list. Implementation of this
     * MUST NOT leave. 
     *
     * @param aMessage indication message. Can be one of the following:
     * 
     *   EXnGetListHeadersUpdate  - either a new skin has appeared, or framework
     *                              has received all applicable skins from server.
     *   EXnGetListHeadersRestart - old application theme list is not 
     *                              valid anymore, please use the new one.
     * @param aAppThemeList list of themes
     */
    virtual void HandleMessage( 
        const TXnServiceCompletedMessage aMessage,
        CArrayPtrFlat<CXnODT>& aAppThemeList ) = 0;
    };


#endif // MPSLNFWAPPTHEMEOBSERVER_H
