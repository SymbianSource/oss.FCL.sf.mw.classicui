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
* Description:  AknPhysics key consuming control
*
*/


#ifndef C_AKNPHYSICSKEYCONSUMER_H
#define C_AKNPHYSICSKEYCONSUMER_H


#include <coecntrl.h>

class CAknPhysicsConeObserver;

/**
 *  AknPhysics key consuming control
 *
 */
NONSHARABLE_CLASS( CAknPhysicsKeyConsumer ) : public CCoeControl
    {

public:

    /**
     * Two-phased constructor.
     */
    static CAknPhysicsKeyConsumer* NewL( 
        CAknPhysicsConeObserver* aConeObserver );

    /**
     * Two-phased constructor.
     */
    static CAknPhysicsKeyConsumer* NewLC( 
        CAknPhysicsConeObserver* aConeObserver );

    /**
     * Destructor.
     */
    virtual ~CAknPhysicsKeyConsumer();
    
private:

    /**
     * C++ constructor.
     */
    CAknPhysicsKeyConsumer( CAknPhysicsConeObserver* aConeObserver );

    /**
     * Symbian second-phase constructor.
     */
    void ConstructL();
    
// from base class CCoeControl

    /**
     * Handles key events.
     *
     * @param aKeyEvent The key event.
     * @param aType The type of key event: 
     * EEventKey, EEventKeyUp or EEventKeyDown.
     */
    TKeyResponse OfferKeyEventL( const TKeyEvent &aKeyEvent, 
                                       TEventCode aType );

private: // data

    /**
     * Physics control environment observer.
     * Not own.
     */
    CAknPhysicsConeObserver* iConeObserver;

    };


#endif // C_AKNPHYSICSKEYCONSUMER_H
