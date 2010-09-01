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
* Description:  Touch gesture framework simulation class - for testing
*               purposes only.
*
*/

#ifndef C_AKNTOUCHGESTUREFWSIMULATION_H
#define C_AKNTOUCHGESTUREFWSIMULATION_H

#include <coemain.h>

/**
 *  Ugly hack class to enable pointer number setting.
 *  Needed only for pointer event simulation.
 */
class TAdvancedPointerEventHelper
    {
public:

    /**
     * Sets pointer number to an advanced pointer event.
     *
     * @param[in,out]  aEvent          Advanced pointer event in which the
     *                                 pointer number is attached to.
     * @param          aPointerNumber  Pointer number.
     */
    static void SetPointerNumberToEvent( TAdvancedPointerEvent* aEvent,
                                         TInt aPointerNumber );
    };

namespace AknTouchGestureFw
{

class CAknTouchGestureFw;
class CAknTouchGestureFwImpl;

const TUid KAknTouchGestureFwSimulation = { 0x20026770 };

/**
 * Touch gesture framework simulation interface.
 *
 */
class MAknTouchGestureFwSimulator
    {

public:

    /**
     * Simulation function.
     *
     * @param  aGestureFw      Gesture FW to which to send the event.
     * @param  aEvent          Simulated pointer event.
     * @param  aPointerNumber  Simulated pointer event pointer number.
     * @param  aTimeStamp      Simulated pointer event time stamp.
     */
    virtual void SimulateL( CAknTouchGestureFw* aGestureFw,
	                        TPointerEvent& aEvent,
                            TInt aPointerNumber,
                            TTime aTimeStamp ) = 0;
    };


/**
 *  Simulation data class.
 *
 */
NONSHARABLE_CLASS ( TAknTouchGestureFwSimulationData )
    {

public:

    /**
     * Pointer to gesture framework instance.
     * Not own.
     */
    CAknTouchGestureFw* iGestureFw;

    /**
     * Pointer to gesture framework engine.
     * Not own.
     */
    CAknTouchGestureFwImpl* iGestureEngine;
    };


/**
 * Touch gesture framework simulation class.
 *
 */
NONSHARABLE_CLASS( CAknTouchGestureFwSimulation )
    : public CCoeStatic,
      public MAknTouchGestureFwSimulator
    {

public:

    /**
     * Initializes simulation for a Gesture FW instance.
     *
     * @param  aGestureFw      Pointer to Gesture FW.
     * @param  aGestureEngine  Pointer to Gesture FW implementation.
     */
    static void InitSimulationL( CAknTouchGestureFw* aGestureFw,
                                 CAknTouchGestureFwImpl* aGestureEngine );

    /**
     * Ends simulation for a Gesture FW instance.
     *
     * @param  aGestureFw  Pointer to Gesture FW.
     */
    static void EndSimulation( CAknTouchGestureFw* aGestureFw );

    /**
     * Destructor.
     */
    virtual ~CAknTouchGestureFwSimulation();

public: // From base class MAknTouchGestureFwSimulator.

    /**
     * Simulation function.
     *
     * @param  aGestureFw      Gesture FW to which to send the event.
     * @param  aEvent          Simulated pointer event.
     * @param  aPointerNumber  Simulated pointer event pointer number.
     * @param  aTimeStamp      Simulated pointer event time stamp.
     */
    void SimulateL( CAknTouchGestureFw* aGestureFw,
                    TPointerEvent& aEvent,
                    TInt aPointerNumber,
                    TTime aTimeStamp );

private:

    /**
     * C++ constructor.
     */
    CAknTouchGestureFwSimulation();

private: // data

    /**
     * Array of simulation data.
     */
    RArray <TAknTouchGestureFwSimulationData> iDataArray;
    };

} // namespace AknTouchGestureFw

#endif // C_AKNTOUCHGESTUREFWSIMULATION_H
