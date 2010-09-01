/*
* Copyright (c) 2004-2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Background task for activating sounds in skin package.
*
*/


#include "pslntaskactivatesounds.h"
#include "PslnSoundActivator.h"

// ======== MEMBER FUNCTIONS ========
// ---------------------------------------------------------------------------
// C++ constructor can NOT contain any code, that might leave.
// ---------------------------------------------------------------------------
//
CPslnTaskActivateSounds::CPslnTaskActivateSounds( 
    CPslnSoundActivator& aActivator ) : iDone( EFalse ), 
                                        iActivator( aActivator ),
                                        iActivationErr( KErrNone )
    {
    }

// ---------------------------------------------------------------------------
// Informs when task is finished.
// ---------------------------------------------------------------------------
//
TBool CPslnTaskActivateSounds::IsProcessDone() const
    {
    return iDone;
    }

// ---------------------------------------------------------------------------
// Task step.
// ---------------------------------------------------------------------------
//
void CPslnTaskActivateSounds::StepL()
    {
    if( IsProcessDone() ) 
        {
        return;
        }
    TRAP( iActivationErr, iActivator.ActivateToProfilesL() );
    iDone = ETrue;
    }

// End of file
