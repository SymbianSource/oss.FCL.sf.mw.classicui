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
* Description:  RNotifier handler for dynamic soft notifications.
*
*/

#ifndef AKNDYNAMICNOTIFIER_H
#define AKNDYNAMICNOTIFIER_H

// INCLUDES
#include <e32base.h>

// FORWARD DECLARATIONS

// CLASS DECLARATION
class RDynNotifier : public RNotifier
    {
public:
    TInt Connect();
    };

/**
*  Base class for handling RNotifier.
*
*  @since S60 3.2
*/
NONSHARABLE_CLASS( CAknDynamicNotifier ) : public CBase
    {
public:
    /**
     * Destructor.
     */
    ~CAknDynamicNotifier();

    /**
     * C++ constructor.
     * @param aUid The UID identifying the plug-in notifier.
     */
    CAknDynamicNotifier( TUid aUid );

public: // New methods
    
    /**
     * Starts or updates the notifier. Synchronous request.
     * @param aBuffer Data that can be passed to notifier.
     * @param aResponse Data that can be returned by notifier.
     * @return Generic symbian errorcode.
     */
    TInt StartOrUpdate(
        const TDesC8& aBuffer, 
        TDes8& aResponse );

    /**
     * Starts the notifier. Asynchronous request.
     * @param aStatus The request status.
     * @param aBuffer Data that can be passed to the notifier.
     * @param aResponse Data that can be returned by the notifier.
     * @return Generic symbian errorcode.
     */
    TInt StartOrUpdate(
        TRequestStatus& aStatus,
        const TDesC8& aBuffer,
        TDes8& aResponse);

private: // Data
    /// Uid of the accessed notifier.
    TUid iUid;
    /// Flag whether the notifier is already started.
    TBool iStarted;
    /// Own. Handle to notifier server. 
    RDynNotifier iNotify;
    };

#endif // AKNDYNAMICNOTIFIER_H
