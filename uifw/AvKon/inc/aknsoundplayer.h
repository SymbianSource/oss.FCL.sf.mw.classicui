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

// AKNSOUNDPLAYER.H
//
// Copyright (c) 1997-2001 Symbian Ltd.  All rights reserved.
//

// Avkon KeySound Player


#if !defined(__AKNSOUNDPLAYER_H__)
#define __AKNSOUNDPLAYER_H__


#include <e32base.h>
#include <barsread.h>


#include <aknSoundinfo.h>

class RAknSoundServerSession : public RSessionBase
    {
public:
    TInt Connect();
    TBool Init(TInt aUid);
    void AddSoundInfoResourceL(TInt aUid, TResourceReader aReader);
    void PlaySound(TInt aSid);
    void StopSound(TInt aSid);
    void PushContextL(TInt aUid, TResourceReader& aReader, TInt aResourceId);
    void PopContext();
    void BringToForeground();
    void KeyPressed(TInt aKey, TBool aRepeat);
    void LockContext();
    void ReleaseContext();
    TInt ServerRequest(TInt aFunction,const TIpcArgs& aArgs);
    TInt TopContext();
    
    void DisableNextKeySound( TInt aScanCode );
    
private:
    TBool iKeySoundServerExists;
    };


NONSHARABLE_CLASS(CAknSoundPlayer) : public CBase
    {
public:
    static CAknSoundPlayer* NewL(TInt aUid);
    ~CAknSoundPlayer();
    void ConstructL();
    void Play(TInt aSid);
    void Stop(TInt aSid);
    void AddAppSoundInfoListL(TInt aResourceId);
    void PushContextL(TInt aResource);
    void PopContext();
    void BringToForeground();
    void PlaySound(TInt aScanCode, TInt aRepeat);
    void LockContext();
    void ReleaseContext();
    TInt RequestSoundInfoL(TInt aAvkonSid, CAknSoundInfo& aInfo);
    TInt TopContext();
    
    void DisableNextKeySound( TInt aScanCode );

private:
    CAknSoundPlayer(TInt aUid);
    TInt Connect();
    void DoAddSoundInfoResourceL(TInt aUid, TInt aResourceId);
    void DoPushContextL(TInt aUid, TInt aResource);
private:
    RAknSoundServerSession iSession;
    TInt iAppUid;
    TInt iSpare;
    };



#endif
