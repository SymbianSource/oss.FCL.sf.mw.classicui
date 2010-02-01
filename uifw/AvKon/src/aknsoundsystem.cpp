/*
* Copyright (c) 2002 Nokia Corporation and/or its subsidiary(-ies).
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
* Description: 
*
*/

// AKNSOUNDSYSTEM.CPP
//
// Copyright (c) 1997-2001 Symbian Ltd.  All rights reserved.
//

// CAknKeySoundSystem - interface for controlling keysounds


#include "aknsoundsystem.h"
#include "aknsoundplayer.h"
#include <eikenv.h>
#include <eikappui.h>
#include <eikapp.h>
#include <avkon.rsg>

// CAknKeySoundSystem

EXPORT_C CAknKeySoundSystem* CAknKeySoundSystem::NewL(TInt aUid)
    {
    CAknKeySoundSystem* self = new(ELeave)CAknKeySoundSystem();
    CleanupStack::PushL(self);
    self->ConstructL(aUid);
    CleanupStack::Pop();    // self
    return self;
    }

CAknKeySoundSystem::CAknKeySoundSystem()
    {
    }

EXPORT_C CAknKeySoundSystem::~CAknKeySoundSystem()
    {
    delete iSoundPlayer;
    }


void CAknKeySoundSystem::ConstructL(TInt aUid)
    {
    iSoundPlayer = CAknSoundPlayer::NewL(aUid);
    iSoundPlayer->ConstructL();
    }


EXPORT_C void CAknKeySoundSystem::PushContextL(TInt aResourceId)
    {
    iSoundPlayer->PushContextL(aResourceId);
    }

EXPORT_C void CAknKeySoundSystem::PopContext()
    {
    iSoundPlayer->PopContext();
    }

EXPORT_C void CAknKeySoundSystem::PlaySound(const TKeyEvent& aKeyEvent)
    {
    iSoundPlayer->PlaySound(aKeyEvent.iScanCode, aKeyEvent.iRepeats);
    }

EXPORT_C void  CAknKeySoundSystem::PlaySound(TInt aSid)
    {
    iSoundPlayer->Play(aSid);
    }


EXPORT_C void CAknKeySoundSystem::AddAppSoundInfoListL(TInt aResourceId)
    {
    iSoundPlayer->AddAppSoundInfoListL(aResourceId);
    }


EXPORT_C void CAknKeySoundSystem::BringToForeground()
    {
    iSoundPlayer->BringToForeground();
    }

EXPORT_C void CAknKeySoundSystem::StopSound(TInt aSid)
    {
    iSoundPlayer->Stop(aSid);
    }

EXPORT_C void CAknKeySoundSystem::LockContext()
    {
    iSoundPlayer->LockContext();
    }

EXPORT_C void CAknKeySoundSystem::ReleaseContext()
    {
    iSoundPlayer->ReleaseContext();
    }

EXPORT_C TInt CAknKeySoundSystem::RequestSoundInfoL(TInt aAvkonSid, CAknSoundInfo& aInfo)
    {
    return iSoundPlayer->RequestSoundInfoL(aAvkonSid, aInfo);
    }

EXPORT_C TInt CAknKeySoundSystem::TopContext()
    {
    return iSoundPlayer->TopContext();      
    }
    
    
    
void CAknKeySoundSystem::DisableNextKeySound( TInt aScanCode )
	{
	iSoundPlayer->DisableNextKeySound( aScanCode );
	}



EXPORT_C CAknSoundInfo* CAknSoundInfo::NewL()
    {
    return new ( ELeave ) CAknSoundInfo();
    }

CAknSoundInfo::CAknSoundInfo()
    {
    }

EXPORT_C CAknSoundInfo::~CAknSoundInfo()
    {   
    delete iFile;
    delete iSequence;
    }

EXPORT_C void CAknSoundInfo::InternalizeL( RReadStream& /*aStream*/ )
    {
    }   

EXPORT_C void CAknSoundInfo::ExternalizeL( RWriteStream& /*aStream*/ ) const
    {   
    }


// End of File
