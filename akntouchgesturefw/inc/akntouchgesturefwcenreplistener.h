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
* Description:  Touch gesture framework central repository listener.
*
*/

#ifndef C_AKNTOUCHGESTUREFWCENREPLISTENER_H
#define C_AKNTOUCHGESTUREFWCENREPLISTENER_H

#include <e32base.h>

class CRepository;

namespace AknTouchGestureFw {

/**
*  The central repository observer interface.
*
*  Interface for a central repository observer.
*
*  @lib akntouchgesturefw
*  @since S60 v5.2
*/
class MAknTouchGestureFwCenRepObserver
    {

public:

    /**
     * Informs the observer that the central repository
     * value has been changed.
     *
     * @param  aKey  CenRep value key.
     */
    virtual void CenRepValueChanged( const TInt& aKey ) = 0;
    };


/**
 * Touch gesture framework central repository listener.
 */
NONSHARABLE_CLASS( CAknTouchGestureFwCenRepListener ) : public CActive
    {

public:

    /**
     * Two-phased constructor.
     *
     * @param  aCenRep    Repository to listen.
     * @param  aObserver  Repository observer.
     */
    static CAknTouchGestureFwCenRepListener* NewL(
            CRepository* aCenRep,
            MAknTouchGestureFwCenRepObserver* aObserver );

    /**
     * Two-phased constructor.
     *
     * @param  aCenRep    Repository to listen.
     * @param  aObserver  Repository observer.
     */
    static CAknTouchGestureFwCenRepListener* NewLC(
            CRepository* aCenRep,
            MAknTouchGestureFwCenRepObserver* aObserver );

    /**
     * Destructor.
     */
    virtual ~CAknTouchGestureFwCenRepListener();

public: // From base class CActive.

    /**
     * Handles an active object's request completion event.
     */
    void RunL();

    /**
     * Implements cancellation of an outstanding request.
     */
    void DoCancel();

    /**
     * Handles errors during the request completion
     *
     * @param  aError  Error code of the leave.
     *
     * @return KErrNone
     */
    TInt RunError( TInt aError );

private:

    /**
     * C++ constructor.
     *
     * @param  aCenRep    Repository to listen.
     * @param  aObserver  Repository observer.
     */
    CAknTouchGestureFwCenRepListener(
            CRepository* aCenRep,
            MAknTouchGestureFwCenRepObserver* aObserver );

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
    MAknTouchGestureFwCenRepObserver* iObserver;
    };

} // AknTouchGestureFw

#endif // C_AKNTOUCHGESTUREFWCENREPLISTENER_H
