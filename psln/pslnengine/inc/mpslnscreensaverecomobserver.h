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
* Description:  ECOM change observer interface.
*
*/


#ifndef MPSLNSCREENSAVERECOMOBSERVER_H
#define MPSLNSCREENSAVERECOMOBSERVER_H

#include <e32base.h>

/**
 *  Defines interface that listens for changes in ECOM.
 *
 *  It is used to observe when new plugins become available for 
 *  the Psln Framework.
 *
 *  @lib PslnEngine
 *  @since S60 v3.1
 */
class MPslnScreenSaverECOMObserver
    {

public:

    /**
     * Interface that is called in observer, when change in ECOM occurs.
     */
    virtual void HandlePluginListChangeL() = 0;

    };


#endif // MPSLNSCREENSAVERECOMOBSERVER_H

// End of file

