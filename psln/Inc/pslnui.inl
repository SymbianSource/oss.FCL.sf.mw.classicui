/*
* Copyright (c) 2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Inline methods from PslnUi.
*
*/


// -----------------------------------------------------------------------------
// Returns current status of given state.
// -----------------------------------------------------------------------------
//
inline TBool CPslnUi::GetStatus( TInt aInternalState ) const
    {
    return ( iPslnUiStatus & aInternalState );
    }

// -----------------------------------------------------------------------------
// Checks if state is off and then sets it on.
// -----------------------------------------------------------------------------
//
inline void CPslnUi::SetStateOn( TInt aInternalState )
    {
    if ( !( iPslnUiStatus & aInternalState ) )
        {
        iPslnUiStatus += aInternalState;
        }
    }

// -----------------------------------------------------------------------------
// Checks if state is on and then sets it off.
// -----------------------------------------------------------------------------
//
inline void CPslnUi::SetStateOff( TInt aInternalState )
    {
    if ( iPslnUiStatus & aInternalState )
        {
        iPslnUiStatus &= ~aInternalState;
        }
    }
