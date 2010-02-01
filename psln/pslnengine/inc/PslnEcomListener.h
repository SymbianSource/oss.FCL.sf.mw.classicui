/*
* Copyright (c) 2006-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Listens to ECOM for screensaver plugin changes.
*
*/


#ifndef C_PSLNECOMLISTENER_H
#define C_PSLNECOMLISTENER_H

#include    <e32base.h>
#include    <ecom/ecom.h>

class CPslnModel;
class REComSession;
class MPslnScreenSaverECOMObserver;

/**
 *  Listens to ECOM for screensaver plugin changes.
 *
 *  Monitor changes in ECOM framework and requests model to update screensaver list, 
 *  if a change is notified.
 *
 *  @lib PslnEngine
 *  @since S60 v3.1
 */
NONSHARABLE_CLASS( CPslnEcomListener ): public CActive
    {
public:

    /**
    * Creates a new instance of CPslnEcomListener. Listener starts immediately
    * monitor ECOM and continues to do so, until class is destroyed.
    * @param aModel reference to PslnModel.
    * @return new instance of CPslnEcomListener.
    */
    IMPORT_C static CPslnEcomListener* NewL( 
        CPslnModel& aModel, 
        MPslnScreenSaverECOMObserver& aObserver );

    virtual ~CPslnEcomListener();

    /**
    * From CActive. 
    * Called when Active Object is ready.
    */
    void RunL();

    /**
    * From CActive. 
    * Called when Active Object has been cancelled.
    */
    void DoCancel();


private:

    /* Starts listening for ECOM changes */
    void StartECOMMonitoringL();

    CPslnEcomListener( 
        CPslnModel& aModel, 
        MPslnScreenSaverECOMObserver& aObserver );

    void ConstructL();

private: // data

    /**
     * Psln engine model reference.
     * Not own.
     */
    CPslnModel* iModel;

    /**
     * ECOM session.
     */
    REComSession iSession;

    /**
     * Observer interface,
     * Not own.
     */
    MPslnScreenSaverECOMObserver* iObserver;

    };


#endif // C_PSLNECOMLISTENER_H

// End of file
