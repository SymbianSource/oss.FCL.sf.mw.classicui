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
* Description:  functions implement in container.h
*
*/


#include <coeaui.h>
#include "testsdkbuttonscontainer.h"

// -----------------------------------------------------------------------------
// CButtonControl::CButtonControl
// -----------------------------------------------------------------------------
//
CButtonControl::CButtonControl() : iControl(NULL)
{}

// -----------------------------------------------------------------------------
// CButtonControl::~CButtonControl
// -----------------------------------------------------------------------------
//
CButtonControl::~CButtonControl()
    {
    CCoeEnv::Static()->AppUi()->RemoveFromStack( this );
    }

// -----------------------------------------------------------------------------
// CButtonControl::NewL
// -----------------------------------------------------------------------------
//
CButtonControl* CButtonControl::NewL( TRect& aRect )
    {
    CButtonControl* self = new ( ELeave ) CButtonControl;
    CleanupStack::PushL( self );
    self->ConstructL( aRect );
    CCoeEnv::Static()->AppUi()->AddToStackL( self );
    CleanupStack::Pop( self );
    return self;
    }

// -----------------------------------------------------------------------------
// CButtonControl::ConsturnctL
// -----------------------------------------------------------------------------
//
void CButtonControl::ConstructL( TRect& aRect )
    {
    CreateWindowL();
    SetRect( aRect );
    ActivateL();
    }

// -----------------------------------------------------------------------------
// CButtonControl::SetComponentControlL
// -----------------------------------------------------------------------------
//
void CButtonControl::SetComponentControlL( CCoeControl* aControl )
    {
    iControl = aControl;
    iControl->SetExtent( Rect().iTl, iControl->MinimumSize() );
    iControl->ActivateL();
    }

// -----------------------------------------------------------------------------
// CButtonControl::ResetComponentControl
// -----------------------------------------------------------------------------
//
void CButtonControl::ResetComponentControl()
    {
    iControl = NULL;
    }
// -----------------------------------------------------------------------------
// CButtonControl::CountComponentControls
// -----------------------------------------------------------------------------
//
TInt CButtonControl::CountComponentControls() const
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
// CButtonControl::ComponentControl
// -----------------------------------------------------------------------------
//
CCoeControl* CButtonControl::ComponentControl( TInt /*aIndex*/ ) const
    {
    return iControl;
    }

// -----------------------------------------------------------------------------
// CButtonControl::ConsturnctL
// -----------------------------------------------------------------------------
//
void CButtonControl::ProcessCommandL( TInt /*aCommandId*/ )
    {
    // Nothing to do
    }

// -----------------------------------------------------------------------------
// CButtonControl::ActivateGc
// -----------------------------------------------------------------------------
//
void CButtonControl::ActivateGc()
    {
    CCoeControl::ActivateGc();
    }

// -----------------------------------------------------------------------------
// CButtonControl::DeactivateGc
// -----------------------------------------------------------------------------
//
void CButtonControl::DeactivateGc()
    {
    CCoeControl::DeactivateGc();
    }

// End of file

