// Copyright (c) 1997-2009 Nokia Corporation and/or its subsidiary(-ies).
// All rights reserved.
// This component and the accompanying materials are made available
// under the terms of "Eclipse Public License v1.0"
// which accompanies this distribution, and is available
// at the URL "http://www.eclipse.org/legal/epl-v10.html".
//
// Initial Contributors:
// Nokia Corporation - initial contribution.
//
// Contributors:
//
// Description:
//

#include <mda/client/utility.h>
#include <mdaaudiosampleplayer.h>
#include <mdaaudiotoneplayer.h>
#include <bassnd.h>
#include <coesndpy.h>
#include <coemain.h>
#include "coepanic.h"
#include <coeutils.h>

const TUid KLafSoundPlayerUid={0x10005F1A};

class CCoeSoundPlayer;

//
// class MCoeSoundPlayerObserver
//

class MCoeSoundPlayerObserver
	{
public:
	virtual void PlayEnded(const CCoeSoundPlayer& aPlayer)=0;
	};

//
// class CCoeSoundPlayer
//

class CCoeSoundPlayer : public CBase
	{
public:
	~CCoeSoundPlayer();
public:
	inline const TBaSystemSoundInfo& SoundInfo() const;
	inline TBool IsPlaying() const;
	virtual void StartPlay()=0;
protected:
	CCoeSoundPlayer(MCoeSoundPlayerObserver& aObserver,const TBaSystemSoundInfo& aInfo,
						TInt aPlayCount,TTimeIntervalMicroSeconds32 aGap);
	void BaseConstructL();
	static TInt PlayTimerCallBack(TAny* aSelf);
private:
	virtual void Play()=0;
protected:
	MCoeSoundPlayerObserver& iObserver;
	TBaSystemSoundInfo iSoundInfo;
	TInt iPlayCount;
	TTimeIntervalMicroSeconds32 iGap;
	CPeriodic* iTimer;
	TBool iPlaying;
	};

inline const TBaSystemSoundInfo& CCoeSoundPlayer::SoundInfo() const
	{return iSoundInfo;}
inline TBool CCoeSoundPlayer::IsPlaying() const
	{return iPlaying;}

CCoeSoundPlayer::~CCoeSoundPlayer()
	{
	delete iTimer;
	}

CCoeSoundPlayer::CCoeSoundPlayer(MCoeSoundPlayerObserver& aObserver,const TBaSystemSoundInfo& aInfo,
									TInt aPlayCount,TTimeIntervalMicroSeconds32 aGap)
	: iObserver(aObserver), iSoundInfo(aInfo), iPlayCount(aPlayCount), iGap(aGap), iPlaying(EFalse)
	{}

void CCoeSoundPlayer::BaseConstructL()
	{
	}

TInt CCoeSoundPlayer::PlayTimerCallBack(TAny* aSelf)
	{ // static
	CCoeSoundPlayer* player=REINTERPRET_CAST(CCoeSoundPlayer*,aSelf);
	player->iTimer->Cancel();
	player->Play();
	return 0;
	}

//
// class CCoeTonePlayer
//

class CCoeTonePlayer : public CCoeSoundPlayer, public MMdaAudioToneObserver
	{
public:
	static CCoeTonePlayer* NewLC(MCoeSoundPlayerObserver& aObserver,const TBaSystemSoundInfo& aInfo,
									CMdaServer& aMdaServer,TInt aPlayCount,TTimeIntervalMicroSeconds32 aGap);
	~CCoeTonePlayer();
private:
	CCoeTonePlayer(MCoeSoundPlayerObserver& aObserver,const TBaSystemSoundInfo& aInfo,
						TInt aPlayCount,TTimeIntervalMicroSeconds32 aGap);
	void ConstructL(CMdaServer& aMdaServer);
private: // from CCoeSoundPlayer
	void StartPlay();
	void Play();
private: // from MMdaAudioToneObserver
	void MatoPrepareComplete(TInt aError);
	void MatoPlayComplete(TInt aError);
private:
	CMdaAudioToneUtility* iPlayUtility;
	};

CCoeTonePlayer* CCoeTonePlayer::NewLC(MCoeSoundPlayerObserver& aObserver,const TBaSystemSoundInfo& aInfo,
								CMdaServer& aMdaServer,TInt aPlayCount,TTimeIntervalMicroSeconds32 aGap)
	{ // static
	CCoeTonePlayer* self=new(ELeave) CCoeTonePlayer(aObserver,aInfo,aPlayCount,aGap);
	CleanupStack::PushL(self);
	self->ConstructL(aMdaServer);
	return self;
	}

CCoeTonePlayer::~CCoeTonePlayer()
	{
	delete iPlayUtility;
	}

CCoeTonePlayer::CCoeTonePlayer(MCoeSoundPlayerObserver& aObserver,const TBaSystemSoundInfo& aInfo,
					TInt aPlayCount,TTimeIntervalMicroSeconds32 aGap)
	: CCoeSoundPlayer(aObserver,aInfo,aPlayCount,aGap)
	{}

void CCoeTonePlayer::ConstructL(CMdaServer& aMdaServer)
	{
	iPlayUtility=CMdaAudioToneUtility::NewL(*this,&aMdaServer);
	BaseConstructL();
	}

void CCoeTonePlayer::StartPlay()
	{
	TBaSystemSoundInfo::TSoundCategory soundCat=iSoundInfo.SoundCategory();
	if (soundCat==TBaSystemSoundInfo::ESequence)
		iPlayUtility->PrepareToPlayFixedSequence(iSoundInfo.FixedSequenceNumber());
	else if (soundCat==TBaSystemSoundInfo::ETone)
		{
		TBaSystemSoundInfo::TTone tone=iSoundInfo.Tone();
		TInt64 time(tone.iDuration.Int());
		TTimeIntervalMicroSeconds duration(time);
		iPlayUtility->PrepareToPlayTone(tone.iFrequency,duration);
		}
	else
		iObserver.PlayEnded(*this);
	}

void CCoeTonePlayer::Play()
	{
    iPlayUtility->SetVolume(iSoundInfo.iVolume);
	iPlayUtility->Play();
	}

void CCoeTonePlayer::MatoPrepareComplete(TInt aError)
	{
	if (aError == KErrNone)
		{
		iPlayUtility->SetVolume(iSoundInfo.iVolume);
		iPlayUtility->SetPriority(iSoundInfo.iPriority,EMdaPriorityPreferenceNone);
		iPlaying=ETrue;
		if (--iPlayCount>0)
			{
			TInt64 val(iGap.Int());
			TTimeIntervalMicroSeconds gap(val);
			iPlayUtility->SetRepeats(iPlayCount,gap);
			}
		iPlayUtility->Play();
		}
	else
		iObserver.PlayEnded(*this);
	}

void CCoeTonePlayer::MatoPlayComplete(TInt /*aError*/)
	{
	iObserver.PlayEnded(*this);
	}

//
// class CCoeFilePlayer
//

class CCoeFilePlayer : public CCoeSoundPlayer, public MMdaAudioPlayerCallback
	{
public:
	static CCoeFilePlayer* NewLC(MCoeSoundPlayerObserver& aObserver,const TBaSystemSoundInfo& aInfo,
									TInt aPlayCount,TTimeIntervalMicroSeconds32 aGap);
	~CCoeFilePlayer();
private:
	CCoeFilePlayer(MCoeSoundPlayerObserver& aObserver,const TBaSystemSoundInfo& aInfo,
						TInt aPlayCount,TTimeIntervalMicroSeconds32 aGap);
	void ConstructL();
private: // from CCoeSoundPlayer
	void StartPlay();
	void Play();
private: // from MMdaAudioPlayerCallback
	void MapcInitComplete(TInt aStatus, const TTimeIntervalMicroSeconds& aDuration);
	void MapcPlayComplete(TInt aErr);
private:
	CMdaAudioPlayerUtility* iPlayUtility;
	TBool iReadyToPlay;
	};

CCoeFilePlayer* CCoeFilePlayer::NewLC(MCoeSoundPlayerObserver& aObserver,const TBaSystemSoundInfo& aInfo,
								TInt aPlayCount,TTimeIntervalMicroSeconds32 aGap)
	{ // static
	CCoeFilePlayer* self=new(ELeave) CCoeFilePlayer(aObserver,aInfo,aPlayCount,aGap);
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CCoeFilePlayer::~CCoeFilePlayer()
	{
	delete iPlayUtility;
	}

CCoeFilePlayer::CCoeFilePlayer(MCoeSoundPlayerObserver& aObserver,const TBaSystemSoundInfo& aInfo,
					TInt aPlayCount,TTimeIntervalMicroSeconds32 aGap)
	: CCoeSoundPlayer(aObserver,aInfo,aPlayCount,aGap)
	{}

void CCoeFilePlayer::ConstructL()
	{
	BaseConstructL();
	TFileName name=iSoundInfo.FileName();
	iPlayUtility=CMdaAudioPlayerUtility::NewFilePlayerL(name,*this,iSoundInfo.iPriority);
	}

void CCoeFilePlayer::StartPlay()
	{
	if (iReadyToPlay)
		Play();
	else
		iReadyToPlay=ETrue;
	}

void CCoeFilePlayer::Play()
	{
	if(iSoundInfo.iVolume > iPlayUtility->MaxVolume() )
		{
		iSoundInfo.iVolume = iPlayUtility->MaxVolume();
		}
	iPlayUtility->SetVolume(iSoundInfo.iVolume); 
	iPlaying=ETrue;
	iPlayUtility->Play();
	}

void CCoeFilePlayer::MapcInitComplete(TInt aStatus,const TTimeIntervalMicroSeconds& /*aDuration*/)
	{
	if (aStatus!=KErrNone)
		iObserver.PlayEnded(*this);
	else
		{
		iPlayUtility->SetVolume(iSoundInfo.iVolume);
		if (--iPlayCount>0)
			{
			TInt64 val(iGap.Int());
			TTimeIntervalMicroSeconds gap(val);
			iPlayUtility->SetRepeats(iPlayCount,gap);
			}
 		if (iReadyToPlay)
			{
			Play();
			}
 		else
			{
			iReadyToPlay=ETrue;
			}
   		}

	}

void CCoeFilePlayer::MapcPlayComplete(TInt /*aErr*/)
	{
	iObserver.PlayEnded(*this);
	}

//
// class CCoeSoundPlayerManager
//

class CCoeSoundPlayerManager : public CCoeStatic, public MCoeSoundPlayerObserver
	{
public:
	static CCoeSoundPlayerManager* NewL();
	void PlaySoundL(const TBaSystemSoundType& aType,TInt aPlayCount,const TTimeIntervalMicroSeconds32& aGap,TBool aInterrupt);
	void CancelSound(const TBaSystemSoundType& aType);
private: // from MCoeSoundPlayerObserver
	void PlayEnded(const CCoeSoundPlayer& aPlayer);
private:
	CCoeSoundPlayerManager();
	~CCoeSoundPlayerManager();
	void ConstructL();
private:
	CArrayPtrFlat<CCoeSoundPlayer> iPlayers;
	CMdaServer* iMdaServer;
	};

CCoeSoundPlayerManager* CCoeSoundPlayerManager::NewL()
	{ // static
	CCoeSoundPlayerManager* self=new(ELeave) CCoeSoundPlayerManager();
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop(); // self
	return self;
	}

/*
 * Initialize the sound matching aType.  Interrupt any lower priority sound but, if a higher or 
 * equal priority sound is already playing, then wait for it to finish
 *
 */
void CCoeSoundPlayerManager::PlaySoundL(const TBaSystemSoundType& aType,TInt aPlayCount,
												const TTimeIntervalMicroSeconds32& aGap,TBool aInterrupt)
	{
	TBaSystemSoundInfo info;
	User::LeaveIfError( BaSystemSound::GetSound(CCoeEnv::Static()->FsSession(),aType,info) );
	if (info.SoundCategory()==TBaSystemSoundInfo::EFile)
		{
		TBaSystemSoundName fileName=info.FileName();
		if (aType.iMinor!=KNullUid && !ConeUtils::FileExists(fileName))
			{
			TBaSystemSoundType defaultType(aType.iMajor,KNullUid);
		 	User::LeaveIfError( BaSystemSound::GetSound(CCoeEnv::Static()->FsSession(),defaultType,info) );
			}
		}
	if (info.iVolume == 0) //do not play the sound, if the volume is set to silent.
		return;
	info.iType=aType; // clients will try to cancel this sound using aType rather than whatever sound was actually found
	TInt count=iPlayers.Count();
	if (count)
		{
		CCoeSoundPlayer* player=iPlayers[0];
		if (aInterrupt || player->SoundInfo().iPriority<info.iPriority)
			{
			delete player;
			iPlayers.Delete(0);
			--count;
			}
		}
	CCoeSoundPlayer* player=NULL;
	if (info.SoundCategory()==TBaSystemSoundInfo::EFile)
		player=CCoeFilePlayer::NewLC(*this,info,aPlayCount,aGap);
	else
		player=CCoeTonePlayer::NewLC(*this,info,*iMdaServer,aPlayCount,aGap);
	TInt ii=0;
	for (;ii<count;ii++)
		{
		if (iPlayers[ii]->SoundInfo().iPriority<info.iPriority)
			{
			iPlayers.InsertL(ii,player);
			break;
			}
		}
	if (iPlayers.Count()==count) // we haven't managed to insert it anywhere
		iPlayers.AppendL(player);
	CleanupStack::Pop(); // player
	if (ii==0)
		iPlayers[0]->StartPlay();
	}

void CCoeSoundPlayerManager::CancelSound(const TBaSystemSoundType& aType)
	{
	TInt loop=0;
	while (loop<iPlayers.Count())
		{
		CCoeSoundPlayer* player=iPlayers[loop];
		if (player->SoundInfo().iType==aType)
			{
			delete player;
			iPlayers.Delete(loop);
			}
		else
			++loop;
		}
	if (iPlayers.Count()==0)
		delete this;
	}

void CCoeSoundPlayerManager::PlayEnded(const CCoeSoundPlayer& aPlayer)
// don't need to check the actaul player that's finished as it's always
// index 0.  Leave the code alone for now in case we change once apps
// start using it
	{
	TInt ii=-1;
	FOREVER
		{
		CCoeSoundPlayer* player=iPlayers[++ii];
		if (&aPlayer==player)
			{
			delete player;
			iPlayers.Delete(ii);
			break;
			}
		}
	if (iPlayers.Count())
		iPlayers[0]->StartPlay();
	else
		delete this; // no more sounds to play so allow media server to close
	}

CCoeSoundPlayerManager::CCoeSoundPlayerManager()
	: CCoeStatic(KLafSoundPlayerUid), iPlayers(1)
	{}

CCoeSoundPlayerManager::~CCoeSoundPlayerManager()
	{
	iPlayers.ResetAndDestroy();
	delete iMdaServer;
	}

void CCoeSoundPlayerManager::ConstructL()
	{
	iMdaServer=CMdaServer::NewL();
	}

//
// class CoeSoundPlayer
//

EXPORT_C void CoeSoundPlayer::PlaySound(const TBaSystemSoundType& aType,TInt aPlayCount,
											TTimeIntervalMicroSeconds32 aGap,TBool aInterrupt)
	{ // static
	TRAP_IGNORE(ManagerL()->PlaySoundL(aType,aPlayCount,aGap,aInterrupt));
	}

EXPORT_C void CoeSoundPlayer::CancelSound(const TBaSystemSoundType& aType)
/** Stops playing the specified sound.

@param aType The sound to stop playing. */
	{ // static
	TRAP_IGNORE(ManagerL()->CancelSound(aType));
	}

CCoeSoundPlayerManager* CoeSoundPlayer::ManagerL()
	{ // static
	CCoeEnv* env=CCoeEnv::Static();
	__ASSERT_ALWAYS(env,Panic(ECoePanicNullEnvironment));
	CCoeSoundPlayerManager* manager=
		STATIC_CAST(CCoeSoundPlayerManager*,env->FindStatic(KLafSoundPlayerUid));
	if (!manager)
		manager=CCoeSoundPlayerManager::NewL();
	return manager;
	}
