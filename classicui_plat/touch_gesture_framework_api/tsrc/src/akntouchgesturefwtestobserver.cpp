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
* Description:  Test observer.
*
*/

#include "akntouchgesturefwtest.h"
#include "akntouchgesturefwtestobserver.h"
#include "akntouchgesturefwtestsubscribercontrol.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CAknTouchGestureFwTestObserver::NewL
// ---------------------------------------------------------------------------
//
CAknTouchGestureFwTestObserver* CAknTouchGestureFwTestObserver::NewL(
    CAknTouchGestureFwTest* aTester )
    {
    CAknTouchGestureFwTestObserver* self =
        CAknTouchGestureFwTestObserver::NewLC( aTester );
    CleanupStack::Pop( self );
    return self;
    }


// ---------------------------------------------------------------------------
// CAknTouchGestureFwTestObserver::NewLC
// ---------------------------------------------------------------------------
//
CAknTouchGestureFwTestObserver* CAknTouchGestureFwTestObserver::NewLC(
    CAknTouchGestureFwTest* aTester )
    {
    CAknTouchGestureFwTestObserver* self
        = new ( ELeave ) CAknTouchGestureFwTestObserver( aTester );
    CleanupStack::PushL( self );
    self->ConstructL();
    return self;
    }


// ---------------------------------------------------------------------------
// CAknTouchGestureFwTestObserver::~CAknTouchGestureFwTestObserver
// ---------------------------------------------------------------------------
//
CAknTouchGestureFwTestObserver::~CAknTouchGestureFwTestObserver()
    {
    delete iControl;
    }


// ---------------------------------------------------------------------------
// CAknTouchGestureFwTestObserver::HandleTouchGestureL
// ---------------------------------------------------------------------------
//
CCoeControl* CAknTouchGestureFwTestObserver::TestControl() const
    {
    return iControl;
    }


// ---------------------------------------------------------------------------
// CAknTouchGestureFwTestObserver::HandleTouchGestureL
// ---------------------------------------------------------------------------
//
void CAknTouchGestureFwTestObserver::HandleTouchGestureL(
    MAknTouchGestureFwEvent& aEvent )
    {
    iTester->DoGestureTest( aEvent );
    }


// ---------------------------------------------------------------------------
// CAknTouchGestureFwTestObserver::CAknTouchGestureFwTestObserver
// ---------------------------------------------------------------------------
//
CAknTouchGestureFwTestObserver::CAknTouchGestureFwTestObserver(
    CAknTouchGestureFwTest* aTester ) : iTester( aTester ) 
    {
    }


// ---------------------------------------------------------------------------
// CAknTouchGestureFwTestObserver::ConstructL
// ---------------------------------------------------------------------------
//
void CAknTouchGestureFwTestObserver::ConstructL()
    {
    iControl = CAknTouchGestureFwTestSubscriberControl::NewL();
    }

//  End of File
