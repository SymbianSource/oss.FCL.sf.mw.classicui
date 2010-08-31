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

#ifndef __EIKKEYSOUNDSERVER_H__
#define __EIKKEYSOUNDSERVER_H__

#include <e32base.h>
#include <mdaaudiosampleplayer.h>
#include <mdaaudiotoneplayer.h>
#include <mdaaudiosampleeditor.h>
#include "eikkeysoundmap.h"
#include "eikkeysound.h"
#include <coecntrl.h>
#include <cenrepnotifyhandler.h>
#include "EikSrvUiConfig.hrh"

#include <ataudioeventapi.h>
#include <mateventcompleteobserver.h>

class CATAudioEventAPI;
class CEikSoundInfo;
class CAknToneSoundInfo;
class CAknFileSoundInfo;
class CAknSequenceSoundInfo;
class TAknSoundID;
class CAknEikAudioToneObserver;

// For debugging purposes. Traces for EikKeySoundServer are enabled or disabled.
#if defined(_DEBUG) && defined(EIKKSS_ENABLE_TRACES)
        #define LOGTEXT(AAA)                     RDebug::Print(AAA)
        #define LOGTEXT1(AAA,BBB)                RDebug::Print(AAA,BBB)
        #define LOGTEXT2(AAA,BBB,CCC)            RDebug::Print(AAA,BBB,CCC)
        #define LOGTEXT3(AAA,BBB,CCC,DDD)        RDebug::Print(AAA,BBB,CCC,DDD)
#else
        #define LOGTEXT(AAA)
        #define LOGTEXT1(AAA,BBB)
        #define LOGTEXT2(AAA,BBB,CCC)
        #define LOGTEXT3(AAA,BBB,CCC,DDD)
#endif

// Anim Dll capture control.
class CAknAnimKeySoundControl : public CCoeControl
    {
public:
    CAknAnimKeySoundControl();
    void ConstructL(RWindowGroup* aParent);
    };


// Anim Dll Interface.
NONSHARABLE_CLASS(RAknAnimKeySound) : public RAnim
    {
public:
    RAknAnimKeySound(RAnimDll &aAnimDll);
    void ConstructL(RWindowGroup* aParent);
    void Close();
private:
    CAknAnimKeySoundControl* iKeySoundControl;
    };


// Storage for a single sound. Base class.
NONSHARABLE_CLASS(CEikSoundInfo) : public CBase
    {
public:
    enum TVolumeSetting
        {
        EKeypadVolumeOff = 0,
        EKeypadVolumeQuiet,
        EKeypadVolumeMedium,
        EKeypadVolumeLoud,
        ESoundVolume0 = EKeypadVolumeOff,
        ESoundVolume1 = EKeypadVolumeOff + 1,
        ESoundVolume2 = EKeypadVolumeOff + 2,
        ESoundVolume3 = EKeypadVolumeOff + 3,
        ESoundVolume4 = EKeypadVolumeOff + 4,
        ESoundVolume5 = EKeypadVolumeOff + 5,
        ESoundVolume6 = EKeypadVolumeOff + 6,
        ESoundVolume7 = EKeypadVolumeOff + 7,
        ESoundVolume8 = EKeypadVolumeOff + 8,
        ESoundVolume9 = EKeypadVolumeOff + 9
        };
public:
    CEikSoundInfo(TInt aPriority, TInt aPreference);
    virtual ~CEikSoundInfo();
    virtual void PlayL() = 0;
    virtual void Stop() = 0;
    virtual void SetVolume(TVolumeSetting aVolume) = 0;
    TInt Preference();
    TVolumeSetting Volume();
    virtual void DoPlay() = 0;
protected:
    TInt iPriority;
    TInt iPreference;
    TVolumeSetting iVolume;
    };


// Key sound server
NONSHARABLE_CLASS(CEikKeySoundServer) :
    public CServer2,
    public MCenRepNotifyHandlerCallback,
    public MATEventCompleteObserver
    {
public:
    static TInt LaunchServer(TThreadId& aThreadId);
    static CEikKeySoundServer* NewLC();
    ~CEikKeySoundServer();

    // Methods called from session
    void InitL(const RMessage2& aMessage);
    void PlaySid(TInt aSid, TBool aPlaySelf);
    void StopSid(TInt aSid);
    void SetVolumeForPreferenceType(TInt aPreference, CEikSoundInfo::TVolumeSetting aVolume);

    void SetDisabledScanCode( TInt aScanCode );
    TInt DisabledScanCode();

    // From MCenRepNotifyHandlerCallback
    void HandleNotifyInt(TUint32 aId, TInt aNewValue);

    inline TBool ContextLocked()
        {
        return iContextLocked;
        }
    inline void SetContextLocked(TBool aLock)
        {
        iContextLocked = aLock;
        }

    //Method for AT Audio Server callback
    void Complete( TInt aError, TAudioThemeEvent aEvent);
private:
    CEikKeySoundServer();
    void ConstructL();
    // from CServer2
    virtual CSession2* NewSessionL(const TVersion& aVersion, const RMessage2& aMessage) const;

public:
    TBool iInit;
    CArrayPtrFlat<CEikSoundInfo>* iSoundList;
    CArrayFixFlat<TAknSoundID>* iSidList;
    CEikKeySoundMap* iDefaultSoundMap;
    CEikKeySoundStack* iCurrentSoundStack;
    CEikSoundInfo::TVolumeSetting iKeypadVolume;
    CCenRepNotifyHandler*   iProfilesNotifyHandler;
    CRepository*            iProfilesRepository;
    TBool iContextLocked;

    TInt iDisabledScanCode;

    CCenRepNotifyHandler   *iWarningToneEnableHandler;
    TInt                    iWarningToneEnabled;

    CATAudioEventAPI* 		iATSoundServerAPI;
    };


// Key sound session
NONSHARABLE_CLASS(CEikKeySoundSession) : public CSession2
    {
public:
    static CEikKeySoundSession* NewL(CEikKeySoundServer* aServer);
    ~CEikKeySoundSession();
    void DispatchMessageL(const RMessage2& aMessage);
    // from CShareableSession
    virtual void ServiceL(const RMessage2& aMessage);
private:
    CEikKeySoundSession(CEikKeySoundServer* aServer);
    void ConstructL();
    void AddSoundIdBufferL(const RMessage2& aMessage);
    void RemoveSids(TInt aUid);
    void AddToneSidL(const TAknSoundID& aSoundID, CAknToneSoundInfo* aSoundInfo);
    void AddFileSidL(const TAknSoundID& aSoundID, CAknFileSoundInfo* aSoundInfo,
        const TDesC& aFileName);
    void AddSequenceSidL(const TAknSoundID& aSoundID, CAknSequenceSoundInfo* aSoundInfo);
    void PushContextL(const RMessage2& aMessage);
    void PopContext();
private:
    CEikKeySoundServer* iServer;
    CEikKeySoundStack* iSoundStack;
    TInt iClientUid;
    TBool iOwnsDefaultSounds;
    TBool iHasLockedContext;
    };


// Specialized base class for synthetized sounds (tones and sequences).
NONSHARABLE_CLASS(CAknSynthSoundInfo) : public CEikSoundInfo
    {
public:
    CAknSynthSoundInfo(TInt aPriority, TInt aPreference);
    virtual ~CAknSynthSoundInfo();
    void InitL();
    virtual void PlayL();
    virtual void Stop();
    virtual void SetVolume(TVolumeSetting aVolume);
    virtual void DoPlay();
private:
    virtual void Prepare();
    void DoSetVolume(CMdaAudioToneUtility* aTonePlayer);
protected:
    CAknEikAudioToneObserver* iToneObserver;
    CMdaAudioToneUtility* iTonePlayer;
    TBool iPlayedStatically;
    };


// Tone sound info.
NONSHARABLE_CLASS(CAknToneSoundInfo) : public CAknSynthSoundInfo
    {
public:
    CAknToneSoundInfo(TInt aPriority, TInt aPreference);
    virtual ~CAknToneSoundInfo();
private:
    virtual void Prepare();
public:
    TInt iFrequency;
    TTimeIntervalMicroSeconds iMs;
    };


// Sequence sound info.
NONSHARABLE_CLASS(CAknSequenceSoundInfo) : public CAknSynthSoundInfo
    {
public:
    CAknSequenceSoundInfo(TInt aPriority, TInt aPreference);
    virtual ~CAknSequenceSoundInfo();
    void ReadSequenceL(RReadStream& aStream);
private:
    virtual void Prepare();
public:
    HBufC8* iSequence;
    };


// File sound info.
NONSHARABLE_CLASS(CAknFileSoundInfo) :
    public CEikSoundInfo,
    public MMdaAudioPlayerCallback,
    public MMdaObjectStateChangeObserver
    {
public:
    CAknFileSoundInfo(TInt aPriority, TInt aPreference);
    virtual ~CAknFileSoundInfo();
    void InitL(const TDesC& aFileName, CMdaServer* aMdaServer);
    virtual void PlayL();
    virtual void Stop();
    virtual void SetVolume(TVolumeSetting aVolume);
    // From MMdaAudioPlayerCallback
    virtual void MapcInitComplete(TInt aError, const TTimeIntervalMicroSeconds& aDuration);
    virtual void MapcPlayComplete(TInt aError);
    virtual void DoPlay();
private:
    void LoadAudioDataL(RFs& aFs, const TDesC& aFileName, TDes8& aDes);
    void DoSetVolume(CMdaAudioPlayerUtility* aAudioPlayer);

    // From MMdaObjectStateChangeObserver
    virtual void MoscoStateChangeEvent(CBase* aObject, TInt aPreviousState, TInt aCurrentState,
        TInt aErrorCode);
public:
    CMdaAudioPlayerUtility* iAudioPlayer;
    HBufC8* iAudioData;
private:
    TBool iPlaying;
    TBool iPrepared;
    CMdaServer* iMdaServer;
    };


class TAknSoundID
    {
public:
    TInt iAppUid;
    TUint iSid;
    CEikSoundInfo* iSoundInfo;  // reference only
    };


class TAknSoundMessageInfo
    {
public:
    TInt iSid;
    TUint8 iFile;
    TInt iFrequency;
    TInt iMs;
    };

#endif
