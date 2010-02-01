/*
* Copyright (c) 2005-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Audio tone observer.
*
*/

// INCLUDE FILES
#include "AknEikAudioToneObserver.h"
#include "eikkeysoundserver.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CAknEikAudioToneObserver::CAknEikAudioToneObserver
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CAknEikAudioToneObserver::CAknEikAudioToneObserver(CEikSoundInfo& aSoundInfo)
    : iSoundInfo(aSoundInfo)
    {
    }

// -----------------------------------------------------------------------------
// CAknEikAudioToneObserver::ConstructL
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CAknEikAudioToneObserver::ConstructL()
    {
    }

// -----------------------------------------------------------------------------
// CAknEikAudioToneObserver::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CAknEikAudioToneObserver* CAknEikAudioToneObserver::NewL(CEikSoundInfo& aSoundInfo)
    {
    CAknEikAudioToneObserver* self = new(ELeave) CAknEikAudioToneObserver(aSoundInfo);
    
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop();

    return self;
    }
    
// -----------------------------------------------------------------------------
// CAknEikAudioToneObserver::~CAknEikAudioToneObserver
// Destructor
// -----------------------------------------------------------------------------
//    
CAknEikAudioToneObserver::~CAknEikAudioToneObserver()
    {
    }

// -----------------------------------------------------------------------------
// CAknEikAudioToneObserver::MatoPrepareComplete
// -----------------------------------------------------------------------------
//
void CAknEikAudioToneObserver::MatoPrepareComplete(TInt /*aError*/)
    {
    LOGTEXT(_L("CAknEikAudioToneObserver::MatoPrepareComplete()"));
    LOGTEXT2(_L("  aError:%d, iSoundInfo pointer:%d"), aError, (TInt)(&iSoundInfo));
        
    // Play sound.
    iSoundInfo.DoPlay();        
    }
    
// -----------------------------------------------------------------------------
// CAknEikAudioToneObserver::MatoPlayComplete
// -----------------------------------------------------------------------------
//
void CAknEikAudioToneObserver::MatoPlayComplete(TInt /*aError*/)
    {
    LOGTEXT(_L("CAknEikAudioToneObserver::MatoPlayComplete()"));
    LOGTEXT2(_L("  aError:%d, iSoundInfo pointer:%d"), aError, (TInt)(&iSoundInfo));
    
    // Tone playing is complete. 
    iSoundInfo.Stop();
    }    

//  End of File  
