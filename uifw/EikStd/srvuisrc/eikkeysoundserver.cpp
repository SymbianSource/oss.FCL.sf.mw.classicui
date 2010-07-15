/*
* Copyright (c) 2002-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  EikSrv keysound server.
*
*/

#include <e32svr.h>
#include <coemain.h>
#include <barsread.h>
#include <eiksrvui.rsg>
#include <s32mem.h>
#include "eikkeysoundserver.h"
#include <aknanimdllstd.h>
#include "AknEikAudioToneObserver.h"
#include <avkon.hrh>
#include <centralrepository.h>
#include <ProfileEngineSDKCRKeys.h>     // KProEngActiveKeypadVolume
#include <ataudioeventapi.h>
#include <e32uid.h>

// Declare thread entry point
GLDEF_C TInt KeySoundServerThreadStartFunction(TAny* aPtr);

_LIT(KKeySoundServerThreadName,"KeySoundServerThread");
_LIT(KKeySoundServerSemaphoreName,"KeySoundServerSemaphore");
_LIT(KKeySoundServerDll,"AtSoundServerClient.dll");

const TInt KKeySoundServerStackSize     = 1024*8; // 8K
const TInt KAknSoundInfoMapGranularity  = 16;
const TInt KKeyClickPreference          = 0x00140001;
const TInt KKeySoundServerBufExpandSize = 1024*1; // 1K
const TInt KKeysoundServerDllUid        = 0x10281C86;

typedef CATAudioEventAPI* (*PFUNC)(MATEventCompleteObserver& aCient);

// =======================================
// CAknAnimKeySoundControl implementation.
// =======================================

CAknAnimKeySoundControl::CAknAnimKeySoundControl()
    {
    }

void CAknAnimKeySoundControl::ConstructL(RWindowGroup* aParent)
    {
    CreateWindowL(aParent);
    SetExtent(TPoint(0,0),TSize(0,0));
    Window().SetShadowDisabled(ETrue);
    Window().Activate();
    }

// ================================
// RAknAnimKeySound implementation.
// ================================

RAknAnimKeySound::RAknAnimKeySound(RAnimDll& aAnimDll)
:RAnim(aAnimDll)
    {
    }

void RAknAnimKeySound::ConstructL(RWindowGroup* aParent)
    {
    iKeySoundControl = new(ELeave)CAknAnimKeySoundControl();
    iKeySoundControl->ConstructL(aParent);
    RAnim::Construct(*(iKeySoundControl->DrawableWindow()), EAnimKeySound, TPtrC8());
    }

void RAknAnimKeySound::Close()
    {
    delete iKeySoundControl;
    iKeySoundControl = NULL;
    }

// ==================================
// CEikKeySoundServer implementation.
// ==================================

TInt CEikKeySoundServer::LaunchServer(TThreadId& aThreadId)
    {
    // First, check that ther server isn't already running.
    TFindServer findServer(__KEYSOUND_SERVER_NAME);
    TFullName name;
    if (findServer.Next(name) == KErrNone)
        {
        return KErrAlreadyExists;
        }

    // Create a semaphore.
    RSemaphore globStartSignal;
    TInt err = globStartSignal.CreateGlobal(KKeySoundServerSemaphoreName, EOwnerProcess);
    if (err != KErrNone)
        {
        err=globStartSignal.OpenGlobal(KKeySoundServerSemaphoreName, EOwnerProcess);
        if (err != KErrNone)
            {
            return err;
            }
        }
    RThread keySoundServerThread;

    err = keySoundServerThread.Create(
        KKeySoundServerThreadName,
        KeySoundServerThreadStartFunction,
        KKeySoundServerStackSize,
        NULL, // uses caller thread's heap
        NULL,
        EOwnerThread);

    aThreadId = keySoundServerThread.Id();
    keySoundServerThread.Resume();
    keySoundServerThread.Close();
    globStartSignal.Wait();
    return err;
    }

// Construct the server object
LOCAL_C void DoKeySoundServerThreadStartFunctionL()
    {
    CEikKeySoundServer::NewLC();

    RSemaphore globStartSignal;
    CleanupClosePushL(globStartSignal);
    User::LeaveIfError(globStartSignal.OpenGlobal(KKeySoundServerSemaphoreName));
    globStartSignal.Signal();
    CleanupStack::PopAndDestroy(); // globStartSignal.Close()

    CActiveScheduler::Start();
    CleanupStack::PopAndDestroy(); // keySoundServer
    }

// Entry point into the new thread
GLDEF_C TInt KeySoundServerThreadStartFunction(TAny* /*aPtr*/)
    {
    __UHEAP_MARK;
    RThread thread;

    TInt err = User::RenameThread(KKeySoundServerThreadName);
    if (err == KErrNone)
        {
        thread.SetPriority(EPriorityAbsoluteForeground);
        thread.Close();

        // Set up scheduler and cleanup stack for this thread
        CActiveScheduler* scheduler = new CActiveScheduler;
        if (!scheduler)
            {
            return KErrNoMemory;
            }
        CActiveScheduler::Install(scheduler);
        CTrapCleanup* trapCleanup = CTrapCleanup::New();
        if (!trapCleanup)
            {
            return KErrNoMemory;
            }

        // Set initial trap harness, and construct server object
        TRAP(err,DoKeySoundServerThreadStartFunctionL());

        delete CActiveScheduler::Current();
        delete trapCleanup;
        }
    __UHEAP_MARKEND;
    return err;
    }

CEikKeySoundServer* CEikKeySoundServer::NewLC()
    {
    CEikKeySoundServer* self = new(ELeave)CEikKeySoundServer();
    CleanupStack::PushL(self);
    self->ConstructL();
    self->StartL(__KEYSOUND_SERVER_NAME);
    return self;
    }

CEikKeySoundServer::CEikKeySoundServer()
:CServer2(EActivePriorityDefault),
iDisabledScanCode( -1 )
    {
    // construct all system SID objects
    }

void CEikKeySoundServer::ConstructL()
    {
    iInit = EFalse;
    iSidList = new(ELeave)CArrayFixFlat<TAknSoundID>(KAknSoundInfoMapGranularity);
    iSoundList = new(ELeave)CArrayPtrFlat<CEikSoundInfo>(KAknSoundInfoMapGranularity);

    // Default to loudest volume
    iKeypadVolume = CEikSoundInfo::EKeypadVolumeLoud;

    TRAPD(err, iProfilesRepository = CRepository::NewL(KCRUidProfileEngine));
    if (err == KErrNone)
        {
        iProfilesNotifyHandler = CCenRepNotifyHandler::NewL(*this,
                                                            *iProfilesRepository,
                                                            CCenRepNotifyHandler::EIntKey,
                                                            KProEngActiveKeypadVolume);

        iWarningToneEnableHandler = CCenRepNotifyHandler::NewL( *this,
                                                                *iProfilesRepository,
                                                                CCenRepNotifyHandler::EIntKey,
                                                                KProEngActiveWarningTones);

        iProfilesNotifyHandler->StartListeningL();
        iWarningToneEnableHandler->StartListeningL();

        iProfilesRepository->Get(KProEngActiveKeypadVolume, (TInt&)iKeypadVolume);
        iProfilesRepository->Get(KProEngActiveWarningTones, iWarningToneEnabled);
        }

    iATSoundServerAPI = NULL;

    RLibrary lib;
    TUidType uidType( KDynamicLibraryUid, KSharedLibraryUid, TUid::Uid( KKeysoundServerDllUid ) );

    if(lib.Load(KKeySoundServerDll, uidType) == KErrNone)
        {
        PFUNC func = (PFUNC)lib.Lookup(1); /* NewL */

        TRAPD(error, iATSoundServerAPI = (CATAudioEventAPI*) func(*this));
        if( error )
            {
            iATSoundServerAPI = NULL;
            }
        }

#ifdef _DEBUG
    RDebug::Print(_L("cenrep CEikKeySoundServer::ConstructL %d"), (TInt)iKeypadVolume);
#endif
    }

CEikKeySoundServer::~CEikKeySoundServer()
    {
    if (iProfilesNotifyHandler)
        {
        iProfilesNotifyHandler->StopListening();
        delete iProfilesNotifyHandler;
        }

    if (iWarningToneEnableHandler)
        {
        iWarningToneEnableHandler->StopListening();
        delete iWarningToneEnableHandler;
        }

    delete iProfilesRepository;
    delete iDefaultSoundMap;
    delete iSoundList;
    delete iSidList;
    delete iATSoundServerAPI;
    }

CSession2* CEikKeySoundServer::NewSessionL(const TVersion& aVersion,
    const RMessage2& /*aMessage*/) const
    {
    TVersion ver(KKeySoundServMajorVN, KKeySoundServMinorVN, KKeySoundServBuildVN);
    if (!User::QueryVersionSupported(ver, aVersion))
        {
        User::Leave(KErrNotSupported);
        }
    return CEikKeySoundSession::NewL(CONST_CAST(CEikKeySoundServer*,this));
    }

void CEikKeySoundServer::InitL(const RMessage2& aMessage)
    {
    TPckg<TInt> pckgBuf(iInit);
    aMessage.WriteL(0, pckgBuf);
    iInit = ETrue;
    }

void CEikKeySoundServer::Complete(TInt aError, TAudioThemeEvent aEvent)
	{
	if( aError != KErrNone && aError != ESilencedError 
	    && aError != EEventCurrentlyPlaying && aError != KErrUnderflow)
		{
		PlaySid(aEvent, ETrue);
		}
	}

void CEikKeySoundServer::PlaySid(TInt aSid, TBool aPlaySelf)
    {
    if (aSid == EAvkonSIDWarningTone && iWarningToneEnabled == 0)
        {
        // Don't play warning tone, when the warning tone is disabled in setting.
        return;
        }

    TInt error(KErrNone);

// special cases when the sound is always played in the key sound server
    if (aSid <= 1000 || aSid == EAvkonSIDStandardKeyClick ||
        aSid == EAvkonSIDReadialCompleteTone || aSid == EAvkonSIDPowerOffTone ||
        aSid == EAvkonSIDPowerOnTone || aSid == EAvkonSIDVoiceRecordingTone ||
        aSid == EAvkonSIDVoiceRecordingStartTone ||
        aSid == EAvkonSIDVoiceRecordingStopTone || aSid == EAvkonSIDNetBusy ||
        aSid == EAvkonSIDNetCallWaiting || aSid == EAvkonSIDNetReorder ||
        aSid == EAvkonSIDNetCongestion || aSid == EAvkonSIDNetSpecialInformation ||
        aSid == EAvkonSIDNetRadioNotAvailable || aSid == EAvkonSIDIHFActive ||
        aSid == EAvkonSIDRadioPathAcknowledge || aSid == EAvkonSIDDial ||
        aSid == EAvkonSIDRingGoing || aSid == EAvkonSIDLocationRequest ||
        aSid == EAvkonSIDInformationTone || aSid == EAvkonSIDConfirmationTone ) 
        {
        aPlaySelf = ETrue;
        }

	if(!iATSoundServerAPI)
        {
    	aPlaySelf = ETrue;
    	}

    if(!aPlaySelf && iATSoundServerAPI)
        {
        TAudioThemeEvent event = static_cast<TAudioThemeEvent>(aSid);
        TRAP(error, iATSoundServerAPI->SendAudioEventL(event, EFalse));
        }

    if (aPlaySelf || error)
        {
        TKeyArrayFix sidKey(_FOFF(TAknSoundID, iSid), ECmpTUint);
        TAknSoundID soundId;
        soundId.iSid = aSid;
        TInt index;
        if (iSidList->FindIsq(soundId, sidKey, index) == 0)
            {
            CEikSoundInfo* info = ((*iSidList)[index]).iSoundInfo;
            if (info && info->Volume() != CEikSoundInfo::EKeypadVolumeOff )
                {
                TRAP_IGNORE(info->PlayL());
#if defined(EIKKSS_DEBUGSOUNDID)
                RDebug::Print(_L("Playing SoundID:%d"), aSid & 0xffff);
#endif
                LOGTEXT2(_L(" PlaySid(): Index:%d, pointer:%d"), index, (TInt)info);
                }
            }
        }
    }

void CEikKeySoundServer::StopSid(TInt aSid)
    {
    TKeyArrayFix sidKey(_FOFF(TAknSoundID, iSid), ECmpTUint);
    TAknSoundID soundId;
    soundId.iSid = aSid;
    TInt index;
    if (iSidList->FindIsq(soundId, sidKey, index) == 0)
        {
        CEikSoundInfo* info = ((*iSidList)[index]).iSoundInfo;
        if (info)
            {
            info->Stop();
#if defined(EIKKSS_DEBUGSOUNDID)
            RDebug::Print(_L("Force Stopping SoundID:%d"), aSid & 0xffff);
#endif
            }
        }
    }

void CEikKeySoundServer::SetVolumeForPreferenceType(TInt aPreference,
    CEikSoundInfo::TVolumeSetting aVolume)
    {
    TInt count = iSoundList->Count();
    for (TInt ii = 0; ii < count; ii++)
        {
        CEikSoundInfo* info = (*iSoundList)[ii];
        if (info)
            {
            if (info->Preference() == aPreference)
                {
                info->SetVolume(aVolume);
                }
            }
        }
    }

void CEikKeySoundServer::SetDisabledScanCode( TInt aScanCode )
	{
	iDisabledScanCode = aScanCode;
	}

TInt CEikKeySoundServer::DisabledScanCode()
	{
	return iDisabledScanCode;
	}


void CEikKeySoundServer::HandleNotifyInt(TUint32 aId, TInt aNewValue)
    {
    if (aId == KProEngActiveKeypadVolume)
        {
        iKeypadVolume = (CEikSoundInfo::TVolumeSetting)aNewValue;
        SetVolumeForPreferenceType( KKeyClickPreference, iKeypadVolume );
        }
    else if (aId == KProEngActiveWarningTones)
        {
        iWarningToneEnabled = aNewValue;
        }
    }

// ===================================
// CEikKeySoundSession implementation.
// ===================================

CEikKeySoundSession* CEikKeySoundSession::NewL(CEikKeySoundServer* aServer)
    {
    CEikKeySoundSession* self = new(ELeave)CEikKeySoundSession(aServer);
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop();
    return self;
    }


CEikKeySoundSession::CEikKeySoundSession(CEikKeySoundServer* aServer)
:CSession2(), iServer(aServer)
    {
    }

CEikKeySoundSession::~CEikKeySoundSession()
    {
    RemoveSids(iClientUid);
    if (iHasLockedContext)
        {
        if( iServer )
            {
            iServer->SetContextLocked(EFalse);
            }
        }
    if (iOwnsDefaultSounds)
        {
        RemoveSids(0);
        iServer->iInit = EFalse;
        }
    if (iSoundStack)
        {
        if (iSoundStack->Count() > 0)
            {
            // Bottom entry is owned by server, so remove before deleting other sound maps
            iSoundStack->Delete(0);
            iSoundStack->ResetAndDestroy();
            }
        // Make sure server isn't using this soundstack
        if (iServer->iCurrentSoundStack == iSoundStack)
            {
            iServer->iCurrentSoundStack = NULL;
            }
        delete iSoundStack;
        }
    }


void CEikKeySoundSession::ConstructL()
    {
    iSoundStack = CEikKeySoundStack::NewL();
    if (iServer->iDefaultSoundMap)
        {
        iSoundStack->AppendL(iServer->iDefaultSoundMap);
        }
    }


void CEikKeySoundSession::ServiceL(const RMessage2& aMessage)
    {
    if (aMessage.Function() == EKeySoundServerPlayKey)
        {
        TInt scancode = aMessage.Int0() & 0xff;
        TBool repeat = aMessage.Int1();
        aMessage.Complete(KErrNone);
        TInt sid;
        if (iServer->iCurrentSoundStack)
            {
            if (iServer->iCurrentSoundStack->Find(scancode, repeat, sid))
                {
                if ( scancode != iServer->DisabledScanCode() )
                	{
                    iServer->PlaySid(sid, EFalse);
                	}
                else
                	{
                	iServer->SetDisabledScanCode( -1 );
                	}
                }
            }
        }
    else
        {
        TRAPD(err, DispatchMessageL(aMessage));
        aMessage.Complete(err);
        }
    }


void CEikKeySoundSession::DispatchMessageL(const RMessage2& aMessage)
    {
    switch (aMessage.Function())
        {
        case EKeySoundServerInit:
            iClientUid = aMessage.Int1();
            iServer->InitL(aMessage);
            break;
        case EKeySoundServerPlaySID:
            iServer->PlaySid(aMessage.Int0(), EFalse);
            break;
        case EKeySoundServerAddSIDS:
            AddSoundIdBufferL(aMessage);
            break;
        case EKeySoundServerPushContext:
            PushContextL(aMessage);
            break;
        case EKeySoundServerPopContext:
            PopContext();
            break;
        case EKeySoundServerTopContext:
            {
            TInt id = 0;
            if (iServer->iCurrentSoundStack && iServer->iCurrentSoundStack->Count())
                {
                CEikKeySoundMap* map = iServer->iCurrentSoundStack->At(
                    iServer->iCurrentSoundStack->Count() - 1);

                id = map->ContextResourceId();
                }
            TPckg<TInt> pckg(id);
            aMessage.WriteL(0, pckg);
            break;
            }
        case EKeySoundServerBringToForeground:
            if ( !iServer->ContextLocked() )
                {
                iServer->iCurrentSoundStack = iSoundStack;
                }
            break;
        case EKeySoundServerStopCurrentTone:
            iServer->StopSid(aMessage.Int0());
            break;
        case EKeySoundServerLockContext:
            // We do not want lock twice and we do not want lock other's context.
            if ( !iServer->ContextLocked() && iServer->iCurrentSoundStack == iSoundStack )
                {
                iServer->SetContextLocked( ETrue );
                iHasLockedContext = ETrue;
                }
            break;
        case EKeySoundServerReleaseContext:
            iServer->SetContextLocked( EFalse );
            iHasLockedContext = EFalse;
            break;
        case EKeySoundServerCloseServer:
            {
            RProcess myProcess;
            TUid myUid = myProcess.SecureId();

            // This server command is not allowed to be called outside eiksrvs process.
            if (aMessage.SecureId() != myProcess.SecureId())
                {
                User::Leave(KErrPermissionDenied);
                }

            CActiveScheduler::Stop();
            break;
            }

        case EKeySoundServerDisableNextKeySound:
            iServer->SetDisabledScanCode( aMessage.Int0() );
            break;

        default:
            User::Leave(KErrNotSupported);
            break;
        }
    }

void CEikKeySoundSession::AddSoundIdBufferL(const RMessage2& aMessage)
    {
    TInt uid = aMessage.Int0();
    TInt size = aMessage.Int1();

    // CBufFlat requires that size must be positive and not larger than KMaxTInt / 2.
    // Without this check the KeySoundServer could panic.
    if (size <= 0 || size >= ((KMaxTInt / 2) - KKeySoundServerBufExpandSize))
        {
        User::Leave(KErrArgument);
        }

    if (uid == 0)
        {
        // Remember if this session is loading the default sounds,
        // so they can be restored if this session goes down.
        iOwnsDefaultSounds = ETrue;
        }

    CBufFlat* buffer = CBufFlat::NewL(KKeySoundServerBufExpandSize);
    CleanupStack::PushL(buffer);

    buffer->ExpandL(0,size);
    TPtr8 buf(buffer->Ptr(0));
    aMessage.ReadL(2,buf);

    // Internalize the data from the stream
    RBufReadStream readStream;
    readStream.Open(*buffer);

    CleanupClosePushL(readStream);

    TInt count = readStream.ReadUint16L();

    for (TInt ii = 0; ii < count; ii++)
        {
        TAknSoundID soundId;
        soundId.iSid = readStream.ReadUint32L();
        soundId.iAppUid = uid;

        TInt priority = readStream.ReadUint16L();
        TInt preference = readStream.ReadUint32L();

        TInt type = readStream.ReadInt8L();
        switch (type)
            {
            case 0: // File
                {
                CAknFileSoundInfo* soundInfo = new(ELeave)CAknFileSoundInfo(priority, preference);
                CleanupStack::PushL(soundInfo);
                soundId.iSoundInfo = soundInfo;
                TFileName file;
                readStream >> file;

                TInt volume = readStream.ReadInt8L();

                if ( volume >= CEikSoundInfo::ESoundVolume0
                    && volume <= CEikSoundInfo::ESoundVolume9 )
                    {
                    soundInfo->SetVolume((CEikSoundInfo::TVolumeSetting)volume);
                    }
                // No need to use else, because sound infos default to the loudest.

                AddFileSidL(soundId, soundInfo, file);
                CleanupStack::Pop();    // soundInfo
                break;
                }
            case 1: // tone
                {
                CAknToneSoundInfo* soundInfo = new(ELeave)CAknToneSoundInfo(priority, preference);
                CleanupStack::PushL(soundInfo);
                soundId.iSoundInfo = soundInfo;
                soundInfo->iFrequency = readStream.ReadUint16L();
                TInt64 ms(STATIC_CAST(TUint,readStream.ReadUint32L()));
                soundInfo->iMs = TTimeIntervalMicroSeconds(ms);

                TInt volume = readStream.ReadInt8L();

                if ( volume >= CEikSoundInfo::ESoundVolume0
                    && volume <= CEikSoundInfo::ESoundVolume9 )
                    {
                    soundInfo->SetVolume((CEikSoundInfo::TVolumeSetting)volume);
                    }
                // No need to use else, because sound infos default to the loudest.

                AddToneSidL(soundId, soundInfo);
                CleanupStack::Pop();    // soundInfo
                break;
                }
            case 2: // sequence
                {
                CAknSequenceSoundInfo* soundInfo = new(ELeave)CAknSequenceSoundInfo(priority,
                    preference);

                CleanupStack::PushL(soundInfo);
                soundInfo->ReadSequenceL(readStream);
                soundId.iSoundInfo = soundInfo;

                TInt volume = readStream.ReadInt8L();

                if ( volume >= CEikSoundInfo::ESoundVolume0
                    && volume <= CEikSoundInfo::ESoundVolume9 )
                    {
                    soundInfo->SetVolume((CEikSoundInfo::TVolumeSetting)volume);
                    }
                // No need to use else, because sound infos default to the loudest.

                AddSequenceSidL(soundId, soundInfo);
                CleanupStack::Pop();    // soundinfo
                break;
                }
            } // end of switch
        }

    CleanupStack::PopAndDestroy(2); // readstream close, buffer
    // Set default volumes.
    iServer->SetVolumeForPreferenceType(KKeyClickPreference, iServer->iKeypadVolume);
    }

void CEikKeySoundSession::RemoveSids(TInt aUid)
    {
    TUint uid = aUid << 16;
    if (!iServer->iSidList)
        {
        return;
        }
    TInt count = iServer->iSidList->Count();
    for (TInt ii=0; ii<count; ii++)
        {
        TAknSoundID& id = iServer->iSidList->At(ii);
        if ( (id.iSid & 0xffff0000) == uid)
            {
            // Check first for possible duplicate sid. It is possible to have duplicates
            // in some cases when 2 instances of same application (uid) are running
            // simultaneusly, e.g. the real application and an embedded instance of
            // the application.
            TBool duplicateFound = EFalse;
            for (TInt jj = ii + 1; jj < count; jj++)
                {
                TAknSoundID& possibleDuplicateId = iServer->iSidList->At(jj);
                if (possibleDuplicateId.iSid == id.iSid)
                    {
                    duplicateFound = ETrue;
                    break;
                    }
                }
            // If no duplicate found, sid is deleted. Else duplicate will be
            // deleted when the for-loop reaches it (unless there is even more duplicates).
            if (!duplicateFound)
                {
                // Remove sound at this position
                delete id.iSoundInfo;
                if (iServer->iSoundList)
                    {
                    iServer->iSoundList->Delete(ii);
                    }
                iServer->iSidList->Delete(ii);
                ii--;
                count--;
                }
            }
        }
    }

void CEikKeySoundSession::PushContextL(const RMessage2& aMessage)
    {
    TInt items = aMessage.Int0();
    TInt uid = aMessage.Int2();
    TInt resSize = (items * 5);
    TInt contextResId = aMessage.Int3();

    // CBufFlat requires that resSize must be positive and not larger than KMaxTInt / 2.
    // Without this check the KeySoundServer could panic.
    if (resSize <= 0 || resSize >= ((KMaxTInt / 2) - KKeySoundServerBufExpandSize))
        {
        User::Leave(KErrArgument);
        }

    CBufFlat* buffer = CBufFlat::NewL(KKeySoundServerBufExpandSize);
    CleanupStack::PushL(buffer);

    buffer->ExpandL(0,resSize);
    TPtr8 buf(buffer->Ptr(0));
    aMessage.ReadL(1,buf);

    // Internalize the data from the stream
    RBufReadStream readStream;
    readStream.Open(*buffer);

    CleanupClosePushL(readStream);

    CEikKeySoundMap* soundMap = CEikKeySoundMap::NewL();
    CleanupStack::PushL(soundMap);
    soundMap->SetContextResourceId(contextResId);
    soundMap->InternalizeL(readStream, items, uid);
    iSoundStack->AppendL(soundMap);
    CleanupStack::Pop();    //   soundMap

    if (iServer->iDefaultSoundMap == NULL)
        {
        iServer->iDefaultSoundMap = soundMap;
        }

    CleanupStack::PopAndDestroy(2); // readstream close, buffer
    }

void CEikKeySoundSession::PopContext()
    {
    if (iSoundStack)
        {
        TInt count = iSoundStack->Count();
        if (count > 1)
            {
            delete iSoundStack->At(count-1);
            iSoundStack->Delete(count-1);
            }
        }
    }

void CEikKeySoundSession::AddToneSidL(const TAknSoundID& aSoundID, CAknToneSoundInfo* aSoundInfo)
    {
    aSoundInfo->InitL();

    TKeyArrayFix sidKey(_FOFF(TAknSoundID, iSid), ECmpTUint);
    if (iServer->iSidList && iServer->iSoundList)
        {
        TInt position = iServer->iSidList->InsertIsqAllowDuplicatesL(aSoundID, sidKey);
        TRAPD(err,
        iServer->iSoundList->AppendL(aSoundInfo));
        if (err != KErrNone)
            {
            iServer->iSidList->Delete(position);
            }
        }
    }

void CEikKeySoundSession::AddSequenceSidL(const TAknSoundID& aSoundID,
    CAknSequenceSoundInfo* aSoundInfo)
    {
    aSoundInfo->InitL();

    TKeyArrayFix sidKey(_FOFF(TAknSoundID, iSid), ECmpTUint);

    if (iServer->iSidList && iServer->iSoundList)
        {
        TInt position = iServer->iSidList->InsertIsqAllowDuplicatesL(aSoundID, sidKey);
        TRAPD(err,
        iServer->iSoundList->AppendL(aSoundInfo));
        if (err != KErrNone)
            {
            iServer->iSidList->Delete(position);
            }
        }
    }

void CEikKeySoundSession::AddFileSidL(const TAknSoundID& aSoundID, CAknFileSoundInfo* aSoundInfo,
    const TDesC& aFileName)
    {
    aSoundInfo->InitL(aFileName, NULL);

    TKeyArrayFix sidKey(_FOFF(TAknSoundID, iSid), ECmpTUint);
    if (iServer->iSidList && iServer->iSoundList)
        {
        TInt position = iServer->iSidList->InsertIsqAllowDuplicatesL(aSoundID, sidKey);
        TRAPD(err,
        iServer->iSoundList->AppendL(aSoundInfo));
        if (err != KErrNone)
            {
            iServer->iSidList->Delete(position);
            }
        }
    }

// =============================
// CEikSoundInfo implementation.
// =============================

CEikSoundInfo::CEikSoundInfo(TInt aPriority, TInt aPreference)
    {
    iPriority = aPriority;
    iPreference = aPreference;
    iVolume = ESoundVolume9; // default to loudest
    }

CEikSoundInfo::~CEikSoundInfo()
    {
    LOGTEXT(_L("CEikSoundInfo::~CEikSoundInfo(). Destructor."));
    // Empty implementation.
    }

TInt CEikSoundInfo::Preference()
    {
    return iPreference;
    }

CEikSoundInfo::TVolumeSetting CEikSoundInfo::Volume()
    {
    return iVolume;
    }

// ==================================
// CAknSynthSoundInfo implementation.
// ==================================

CAknSynthSoundInfo::CAknSynthSoundInfo(TInt aPriority, TInt aPreference)
: CEikSoundInfo(aPriority, aPreference), iPlayedStatically(EFalse)
    {
    }

CAknSynthSoundInfo::~CAknSynthSoundInfo()
    {
    LOGTEXT(_L("CAknSynthSoundInfo::~CAknSynthSoundInfo(). Destructor."));

    // Stops playing and deletes instances if they exist.
    Stop();

    delete iToneObserver;
    delete iTonePlayer;
    }

void CAknSynthSoundInfo::Prepare()
    {
    LOGTEXT(_L("CAknSynthSoundInfo::Prepare()."));
    // This base class method should never be called.
    }

void CAknSynthSoundInfo::InitL()
    {
    // Keyclicks are played with a statically reserved CMdaAudioToneUtility.
    // Same concerns also error tones (this is a hack to avoid an endless error dialog
    // loop because of audio server crash).
    if ((iPriority == EAvkonKeyClickPriority && iPreference == KKeyClickPreference) ||
        (iPriority == EAvkonErrorNotePriority && iPreference == EAvkonErrorNotePreference))
        {
        LOGTEXT(_L("CAknSynthSoundInfo::InitL(). Static init."));

        iPlayedStatically = ETrue;
        iToneObserver = CAknEikAudioToneObserver::NewL(*this);
        iTonePlayer = CMdaAudioToneUtility::NewL(*iToneObserver, NULL); // Synchronous
        }
    }

void CAknSynthSoundInfo::PlayL()
    {
    LOGTEXT(_L("CAknSynthSoundInfo::PlayL()."));
    LOGTEXT3(_L(" This:%d, iPriority:%d, iPreference:%d"), (TInt)this, iPriority, iPreference);

    // Stops playing and deletes instances if they exist.
    Stop();

    if (!iPlayedStatically)
        {
        // Create new tone player and observer.
        iToneObserver = CAknEikAudioToneObserver::NewL(*this);
        iTonePlayer = CMdaAudioToneUtility::NewL(*iToneObserver, NULL); // Synchronous
        }

    // Prepare to play either a tone or a sequence depending on subclass.
    Prepare();
    }

void CAknSynthSoundInfo::DoPlay()
    {
    LOGTEXT(_L("CAknSynthSoundInfo::DoPlay()."));
    LOGTEXT3(_L(" This:%d, iPriority:%d, iPreference:%d"), (TInt)this, iPriority, iPreference);

    if (iTonePlayer->State() == EMdaAudioToneUtilityPrepared)
        {
        LOGTEXT(_L(" CAknSynthSoundInfo::DoPlay(). Prepare successful, play."));

        iTonePlayer->SetPriority(iPriority,(TMdaPriorityPreference)iPreference);
        DoSetVolume(iTonePlayer);

        LOGTEXT1(_L(" iVolume just before calling play: %d"), iVolume);
        LOGTEXT1(_L(" Volume from iTonePlayer: %d"), iTonePlayer->Volume());

        iTonePlayer->Play();
        }
    else
        {
        LOGTEXT(_L(" CAknSynthSoundInfo::DoPlay(). Prepare failed, delete!"));

        if (!iPlayedStatically)
            {
            LOGTEXT(_L(" CAknSynthSoundInfo::DoPlay(). Deleting iTonePlayer and iToneObserver."));

            delete iTonePlayer;
            iTonePlayer = NULL;
            delete iToneObserver;
            iToneObserver = NULL;
            }
        }
    }

void CAknSynthSoundInfo::Stop()
    {
    LOGTEXT(_L("CAknSynthSoundInfo::Stop()."));
    LOGTEXT3(_L(" This:%d, iPriority:%d, iPreference:%d"), (TInt)this, iPriority, iPreference);

    // Stop playing and delete tone player if it exists.
    if (iTonePlayer)
        {
        LOGTEXT(_L(" CAknSynthSoundInfo::Stop(). iTonePlayer exists."));

        if (iTonePlayer->State() == EMdaAudioToneUtilityPlaying)
            {
            LOGTEXT(_L(" CAknSynthSoundInfo::Stop(). Playing, call CancelPlay()."));

            iTonePlayer->CancelPlay();
            }

        if (!iPlayedStatically)
            {
            LOGTEXT(_L(" CAknSynthSoundInfo::Stop(). Dynamic playing. Deleting iTonePlayer."));

            delete iTonePlayer;
            iTonePlayer = NULL;
            }
        }

    // Delete also tone observer if it exists.
    if (iToneObserver)
        {
        LOGTEXT(_L(" CAknSynthSoundInfo::Stop(). iToneObserver exists."));

        if (!iPlayedStatically)
            {
            LOGTEXT(_L(" CAknSynthSoundInfo::Stop(). Dynamic playing. Deleting iToneObserver."));

            delete iToneObserver;
            iToneObserver = NULL;
            }
        }
    }

void CAknSynthSoundInfo::SetVolume(TVolumeSetting aVolume)
    {
    iVolume = aVolume;
    }

void CAknSynthSoundInfo::DoSetVolume(CMdaAudioToneUtility* aTonePlayer)
    {
    TInt max = aTonePlayer->MaxVolume();

    if ( max == 0x0000ffff ) // 16bit -1 i.e. not set
        {
        max = (TInt)ESoundVolume9; // Set it to our max
        }

    TInt volume = 0;

    if ( Preference() != KKeyClickPreference ) // Other sounds than key click
        {
        aTonePlayer->SetVolume( ((TInt)iVolume * max )/(TInt)ESoundVolume9);
        return;
        }

    switch (iVolume)
        {
        case EKeypadVolumeOff:
            break;
        case EKeypadVolumeQuiet:
            volume = max / 3;
            break;
        case EKeypadVolumeMedium:
            volume = (max * 2) / 3;
            break;
        default: //case EKeypadVolumeLoud:
            volume = max;
            break;
        }
    aTonePlayer->SetVolume(volume);
    }


// =================================
// CAknToneSoundInfo implementation.
// =================================

CAknToneSoundInfo::CAknToneSoundInfo(TInt aPriority, TInt aPreference)
: CAknSynthSoundInfo(aPriority, aPreference)
    {
    }

CAknToneSoundInfo::~CAknToneSoundInfo()
    {
    LOGTEXT(_L("CAknToneSoundInfo::~CAknToneSoundInfo(). Destructor."));
    // Empty implementation.
    }

void CAknToneSoundInfo::Prepare()
    {
    LOGTEXT(_L("CAknToneSoundInfo::Prepare()."));

    // Prepare
    iTonePlayer->PrepareToPlayTone(iFrequency, iMs);
    }


// =====================================
// CAknSequenceSoundInfo implementation.
// =====================================

CAknSequenceSoundInfo::CAknSequenceSoundInfo(TInt aPriority, TInt aPreference)
: CAknSynthSoundInfo(aPriority, aPreference)
    {
    }

CAknSequenceSoundInfo::~CAknSequenceSoundInfo()
    {
    LOGTEXT(_L("CAknSequenceSoundInfo::~CAknSequenceSoundInfo(). Destructor."));

    delete iSequence;
    }

void CAknSequenceSoundInfo::Prepare()
    {
    LOGTEXT(_L("CAknSequenceSoundInfo::Prepare()."));

    // Prepare
    iTonePlayer->PrepareToPlayDesSequence(*iSequence);
    }

void CAknSequenceSoundInfo::ReadSequenceL(RReadStream& aStream)
    {
    delete iSequence;
    iSequence = NULL;

    TInt length = aStream.ReadInt16L();
    iSequence = HBufC8::NewMaxL(length);
    TPtr8 ptr = iSequence->Des();
    for (TInt ii = 0; ii < length; ii++)
        {
        ptr[ii] = aStream.ReadUint8L();
        }
    }

// =================================
// CAknFileSoundInfo implementation.
// =================================

CAknFileSoundInfo::CAknFileSoundInfo(TInt aPriority, TInt aPreference)
: CEikSoundInfo(aPriority, aPreference)
    {
    }

CAknFileSoundInfo::~CAknFileSoundInfo()
    {
    delete iAudioPlayer;
    }

void CAknFileSoundInfo::InitL(const TDesC& aFileName, CMdaServer* aMdaServer)
    {
    LOGTEXT(_L("CAknFileSoundInfo::InitL() - Filename:"));
    LOGTEXT(aFileName);
    iFileName = aFileName;
    LOGTEXT(_L(" CAknFileSoundInfo::InitL() - Exit"));
    }

void CAknFileSoundInfo::PlayL()
    {
    LOGTEXT(_L("CAknFileSoundInfo::PlayL()."));
    LOGTEXT3(_L(" This:%d, iPriority:%d, iPreference:%d"), (TInt)this, iPriority, iPreference);

    // Stops playing and deletes audio player instance if it exist.
    Stop();

    // Create audio player. DoPlay() will be called in all circumstances.
    iAudioPlayer = CMdaAudioPlayerUtility::NewFilePlayerL(iFileName, *this, iPriority,(TMdaPriorityPreference)iPreference );
    LOGTEXT(_L(" CAknFileSoundInfo::PlayL() - Exit"));
    }


void CAknFileSoundInfo::DoPlay()
    {
    LOGTEXT(_L("CAknFileSoundInfo::DoPlay()."));

    if (iPrepared)
        {
        LOGTEXT(_L(" CAknFileSoundInfo::DoPlay(). Prepared succesfull, play."));

        // No need to set priority. It is already set in NewDesPlayerReadOnlyL().

        // Set volume.
        DoSetVolume(iAudioPlayer);

        LOGTEXT1(_L(" iVolume just before calling play: %d"), iVolume);

        iAudioPlayer->Play();
        iPlaying = ETrue;
        }
    else
        {
        LOGTEXT(_L(" CAknFileSoundInfo::DoPlay(). Prepare failed, delete!"));
        LOGTEXT(_L(" CAknFileSoundInfo::DoPlay(). Deleting iAudioPlayer."));

        delete iAudioPlayer;
        iAudioPlayer = NULL;
        }
    }


void CAknFileSoundInfo::Stop()
    {
    LOGTEXT(_L("CAknFileSoundInfo::Stop()."));

    // Stop playing and delete audio player if it exists.
    if (iAudioPlayer)
        {
        LOGTEXT(_L(" CAknFileSoundInfo::Stop(). iAudioPlayer exists."));

        if (iPlaying)
            {
            LOGTEXT(_L(" CAknFileSoundInfo::Stop(). Playing, call CancelPlay()."));

            iAudioPlayer->Stop();
            iPlaying = EFalse;
            }

        LOGTEXT(_L(" CAknFileSoundInfo::Stop(). Deleting iAudioPlayer."));

        delete iAudioPlayer;
        iAudioPlayer = NULL;
        iPrepared = EFalse;
        }
    }

void CAknFileSoundInfo::MoscoStateChangeEvent(CBase* /*aObject*/, TInt /*aPreviousState*/,
    TInt /*aCurrentState*/, TInt /*aErrorCode*/)
    {
    }

void CAknFileSoundInfo::SetVolume(TVolumeSetting aVolume)
    {
    iVolume = aVolume;
    }

void CAknFileSoundInfo::DoSetVolume(CMdaAudioPlayerUtility* aAudioPlayer)
    {
    TInt max = aAudioPlayer->MaxVolume();

    if ( max == 0x0000ffff ) // 16bit -1 i.e. not set
        {
        max = (TInt)ESoundVolume9; // Set it to our max
        }

    TInt volume = 0;

    if ( Preference() != KKeyClickPreference ) // Other sounds than key click
        {
		//change (TInt)ESoundVolume9 to ((TInt)ESoundVolume9 + 1)) to keep consistent with audiotheme
        aAudioPlayer->SetVolume( ((TInt)iVolume * max )/((TInt)ESoundVolume9 + 1));
        return;
        }

    switch (iVolume)
        {
        case EKeypadVolumeOff:
            break;
        case EKeypadVolumeQuiet:
            volume = max / 3;
            break;
        case EKeypadVolumeMedium:
            volume = (max * 2) / 3;
            break;
        default: //case EKeypadVolumeLoud:
            volume = max;
            break;
        }
    aAudioPlayer->SetVolume(volume);
    }

void CAknFileSoundInfo::MapcInitComplete(TInt aError,
    const TTimeIntervalMicroSeconds& /*aDuration*/)
    {
    LOGTEXT(_L("CAknFileSoundInfo::MapcInitComplete()."));
    LOGTEXT1(_L(" aError:%d"), aError);

    if (aError == KErrNone)
        {
        iPrepared = ETrue;
        SetVolume(iVolume);
        }

    DoPlay();
    }

void CAknFileSoundInfo::MapcPlayComplete(TInt /*aError*/)
    {
    LOGTEXT(_L("CAknFileSoundInfo::MapcPlayComplete()"));

    iPlaying = EFalse;

    delete iAudioPlayer;
    iAudioPlayer = NULL;
    iPrepared = EFalse;
    }

// End of file
