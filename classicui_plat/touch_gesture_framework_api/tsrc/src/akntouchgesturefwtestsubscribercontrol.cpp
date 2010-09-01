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

#include <coecntrl.h>

#include "akntouchgesturefwtestsubscribercontrol.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Two-phased constructor.
// ---------------------------------------------------------------------------
//
CAknTouchGestureFwTestSubscriberControl* CAknTouchGestureFwTestSubscriberControl::NewL()
    {
    CAknTouchGestureFwTestSubscriberControl* self =
        CAknTouchGestureFwTestSubscriberControl::NewLC();
    CleanupStack::Pop( self );
    return self;
    }


// ---------------------------------------------------------------------------
// Two-phased constructor.
// ---------------------------------------------------------------------------
//
CAknTouchGestureFwTestSubscriberControl* CAknTouchGestureFwTestSubscriberControl::NewLC()
    {
    CAknTouchGestureFwTestSubscriberControl* self
        = new ( ELeave ) CAknTouchGestureFwTestSubscriberControl();
    CleanupStack::PushL( self );
    self->ConstructL();
    return self;
    }


// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CAknTouchGestureFwTestSubscriberControl::~CAknTouchGestureFwTestSubscriberControl()
    {
    }


// ---------------------------------------------------------------------------
// Default C++ constructor
// ---------------------------------------------------------------------------
//
CAknTouchGestureFwTestSubscriberControl::CAknTouchGestureFwTestSubscriberControl()
    {
    }


// ---------------------------------------------------------------------------
// Second-phase constructor.
// ---------------------------------------------------------------------------
//
void CAknTouchGestureFwTestSubscriberControl::ConstructL()
    {
    CreateWindowL();
    SetExtentToWholeScreen();
    }

//  End of File
