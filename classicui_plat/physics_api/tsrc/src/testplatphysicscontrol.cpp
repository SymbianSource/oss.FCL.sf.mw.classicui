/*
* Copyright (c) 2002 - 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description: Test aknphysics.h
*
*/

#include <coeaui.h>
#include "testplatphysicscontrol.h"

// -----------------------------------------------------------------------------
// CPhysicsControl::CPhysicsControl
// -----------------------------------------------------------------------------
//
CPhysicsControl::CPhysicsControl() : iControl(NULL)
{}

// -----------------------------------------------------------------------------
// CPhysicsControl::~CPhysicsControl
// -----------------------------------------------------------------------------
//
CPhysicsControl::~CPhysicsControl()
    {
    CCoeEnv::Static()->AppUi()->RemoveFromStack( this );
    }

// -----------------------------------------------------------------------------
// CPhysicsControl::NewL
// -----------------------------------------------------------------------------
//
CPhysicsControl* CPhysicsControl::NewL( TRect& aRect )
    {
    CPhysicsControl* self = new ( ELeave ) CPhysicsControl;
    CleanupStack::PushL( self );
    self->ConstructL( aRect );
    CCoeEnv::Static()->AppUi()->AddToStackL( self );
    CleanupStack::Pop( self );
    return self;
    }

// -----------------------------------------------------------------------------
// CPhysicsControl::ConsturnctL
// -----------------------------------------------------------------------------
//
void CPhysicsControl::ConstructL( TRect& aRect )
    {
    CreateWindowL();
    SetRect( aRect );
    ActivateL();
    }

// -----------------------------------------------------------------------------
// CPhysicsControl::SetComponentControlL
// -----------------------------------------------------------------------------
//
void CPhysicsControl::SetComponentControlL( CCoeControl* aControl )
    {
    iControl = aControl;
    iControl->SetExtent( Rect().iTl, iControl->MinimumSize() );
    iControl->ActivateL();
    }

// -----------------------------------------------------------------------------
// CPhysicsControl::ResetComponentControl
// -----------------------------------------------------------------------------
//
void CPhysicsControl::ResetComponentControl()
    {
    iControl = NULL;
    }
// -----------------------------------------------------------------------------
// CPhysicsControl::CountComponentControls
// -----------------------------------------------------------------------------
//
TInt CPhysicsControl::CountComponentControls() const
    {
    if ( iControl )
        {
        return 1;
        }
    else
        {
        return 0;
        }
    }

// -----------------------------------------------------------------------------
// CPhysicsControl::ComponentControl
// -----------------------------------------------------------------------------
//
CCoeControl* CPhysicsControl::ComponentControl( TInt /*aIndex*/ ) const
    {
    return iControl;
    }

// -----------------------------------------------------------------------------
// CPhysicsControl::ConsturnctL
// -----------------------------------------------------------------------------
//
void CPhysicsControl::ProcessCommandL( TInt /*aCommandId*/ )
    {
    // Nothing to do
    }
// End of file

