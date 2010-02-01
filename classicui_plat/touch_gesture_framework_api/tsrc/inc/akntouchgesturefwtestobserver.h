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
* Description:  Test observer
*
*/

#ifndef C_AKNTOUCHGESTUREFWTESTOBSERVER_H
#define C_AKNTOUCHGESTUREFWTESTOBSERVER_H

#include <e32base.h>
#include <akntouchgesturefwobserver.h>

using namespace AknTouchGestureFw;

class CCoeControl;
class CAknTouchGestureFwTest;
class CAknTouchGestureFwTestSubscriberControl;

/**
 *  Test observer.
 */
NONSHARABLE_CLASS( CAknTouchGestureFwTestObserver )
    :
    public CBase,
    public MAknTouchGestureFwObserver
    {

public:

    /**
     * Two-phased constructor.
     */
    static CAknTouchGestureFwTestObserver* NewL(
            CAknTouchGestureFwTest* aTester );

    /**
     * Two-phased constructor.
     */
    static CAknTouchGestureFwTestObserver* NewLC(
            CAknTouchGestureFwTest* aTester );

    /**
     * Destructor.
     */
    virtual ~CAknTouchGestureFwTestObserver();

    /**
     * Provides test control.
     *
     * @return Test control.
     */
    CCoeControl* TestControl() const;

public: // From base class MAknTouchGestureFwObserver.

    /**
     * Handle the gesture event
     *
     * @param  aEvent  Event describing the gesture.
     */
    void HandleTouchGestureL( MAknTouchGestureFwEvent& aEvent );

private:

    /**
     * C++ constructor.
     */
    CAknTouchGestureFwTestObserver( CAknTouchGestureFwTest* aTester );

    /**
     * Symbian second-phase constructor.
     */
    void ConstructL();

private: // data

    /**
     * Test control.
     * Own.
     */
    CAknTouchGestureFwTestSubscriberControl* iControl;

    /**
     * Test component instance
     * Not own.
     */
    CAknTouchGestureFwTest* iTester;    
    
    };

#endif // C_AKNTOUCHGESTUREFWTESTOBSERVER_H
