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
* Description:  Button state for CAknButton use in CEikCba.
*
*/


#include "akncommandbuttonstate.h"

// ============================ MEMBER FUNCTIONS =============================

// ---------------------------------------------------------------------------
// CAknCommandButtonState::~CAknCommandButtonState
// Destructor
// ---------------------------------------------------------------------------
//
CAknCommandButtonState::~CAknCommandButtonState()
    {
    }


// ---------------------------------------------------------------------------
// CAknCommandButtonState::CAknCommandButtonState
// Constructor
// ---------------------------------------------------------------------------
//
CAknCommandButtonState::CAknCommandButtonState( const TInt aFlags,
                                                const TInt aCommandId )
    : CAknButtonState( aFlags ), iCommandId( aCommandId )
    {
    }


// ---------------------------------------------------------------------------
// CAknCommandButtonState::SetCommand
// Sets the command attached with this state.
// ---------------------------------------------------------------------------
//
void CAknCommandButtonState::SetCommand( const TInt aCommandId )
    {
    iCommandId = aCommandId;
    }

// ---------------------------------------------------------------------------
// CAknCommandButtonState::CommandId
// Gets the command attached with this state.
// ---------------------------------------------------------------------------
//
TInt CAknCommandButtonState::CommandId() const
    {
    return iCommandId;
    }


