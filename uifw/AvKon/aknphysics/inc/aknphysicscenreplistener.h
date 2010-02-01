/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  AknPhysics cenrep listener
*
*/


#ifndef C_AKNPHYSICSCENREPLISTENER_H
#define C_AKNPHYSICSCENREPLISTENER_H


#include <e32base.h>

class CRepository;

/**
*  The cenrep observer interface.
*
*  Interface for cenrep observer.
*
*  @lib aknphysics
*  @since S60 v5.0
*/
class MAknPhysicsCenRepObserver
    {

public:

    /**
     * Informs the observer that the cenrep
     * value has been changed.
     *
     * @param aKey CenRep value key.
     */
    virtual void CenRepValueChanged( const TInt& aKey ) = 0;

    };


/**
 *  AknPhysics cenrep listener.
 *
 */
NONSHARABLE_CLASS( CAknPhysicsCenRepListener ) : public CActive
    {

public:

    /**
     * Two-phased constructor.
     * @param aCenRep Repository to listen.
     * @param aObserver Repository observer.
     */
    static CAknPhysicsCenRepListener* NewL( 
        CRepository* aCenRep, MAknPhysicsCenRepObserver* aObserver );
                                            
    /**
     * Two-phased constructor.
     * @param aCenRep Repository to listen.
     * @param aObserver Repository observer.
     */
    static CAknPhysicsCenRepListener* NewLC( 
        CRepository* aCenRep, MAknPhysicsCenRepObserver* aObserver );

    /**
     * Destructor.
     */
    virtual ~CAknPhysicsCenRepListener();

// from base class CActive
    
    /**
     * Handles an active object's request completion event.
     */
    void RunL();

    /**
     * Implements cancellation of an outstanding request.
     */
    void DoCancel();
    
private:

    /**
     * C++ constructor.
     * @param aCenRep Repository to listen.
     * @param aObserver Repository observer.
     */
    CAknPhysicsCenRepListener( CRepository* aCenRep,
                               MAknPhysicsCenRepObserver* aObserver );

    /**
     * Symbian second-phase constructor.
     */
    void ConstructL();
    
    /**
     * Renews the request.
     */
    void RenewRequestL();
    
private: // data

    /**
     * Central repository.
     * Not own.
     */
    CRepository* iCenRep;
    
    /**
     * CenRep observer.
     * Not own.
     */
    MAknPhysicsCenRepObserver* iObserver;

    };


#endif // C_AKNPHYSICSCENREPLISTENER_H
