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
* Description:  
*
*/

#ifndef __AKNMEMORYCARDDIALOGIMPL_H__
#define __AKNMEMORYCARDDIALOGIMPL_H__

#include <e32std.h>
#include <e32base.h>
#include <eikenv.h>
#include <eiknotapi.h>
#include <AknNotifyStd.h>
#include <AknPanic.h>

#include "AknMemoryCardUi.h"

struct TMessageWithClientId
    {
    TMessageWithClientId(const RMessagePtr2& aMsg,TInt aID):iMessage(aMsg),iClientId(aID){}
    RMessagePtr2 iMessage;
    TInt         iClientId;
    };

class CAknCodeQuery;

class CAknMMCPasswordRequester : public CBase
    {
public:
    static CAknMMCPasswordRequester* NewL();
    CAknMMCPasswordRequester();
    ~CAknMMCPasswordRequester();

    void StartL(TInt aDrive, TBool aStore, const RMessagePtr2& aMessage, TInt aClientID = 0);
    void Cancel(TInt aClientID);
    void UnlockCard(TBool aAccept);
    void ClientExit(TInt aClientID, TBool aCompleteWithCancel = EFalse);
    void AppendQueueItemL(const RMessagePtr2& aMessage, TInt aClientID);
    void CompleteAllMessages(TInt aReason);

private:
    void ConstructL();

private:
    void  SetPromptL();
    TBool  PopupL();

private:
    TResourceFileLoader            iResFileLdr;
    HBufC*                         iPrompt;
    TBuf<KMaxMediaPassword/2>      iPassWd;
    TInt                           iNumberOfAttempts;
    TBool                          iStore;
    CAknCodeQuery*                 iQuery;
    TInt                           iDriveNumber;
    RArray<TMessageWithClientId>   iMessages;
    };

#endif // __AKNMEMORYCARDDIALOGIMPL_H__
