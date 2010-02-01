/*
* Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Plugin declaration of global list message query.
*
*/

#ifndef __AKNSYSTEMLISTMSGPOPUP_H__
#define __AKNSYSTEMLISTMSGPOPUP_H__

#include <e32std.h>
#include <e32base.h>
#include <eiknotapi.h>
#include <eikcmobs.h>
#include <AknNotifyStd.h>
#include "AknListMsgQueryNotificationDialog.h"

NONSHARABLE_CLASS(CAknGlobalListMsgQuerySubject): 
    public CBase, 
    public MEikSrvNotifierBase2, 
    public MAknListQueryNotificationCallback
    {
public:
    static CAknGlobalListMsgQuerySubject* NewL();
    virtual ~CAknGlobalListMsgQuerySubject();
    
    // From MEikSrvNotifierBase.
    void Release();
    TNotifierInfo RegisterL();
    TNotifierInfo Info() const;
    TPtrC8 StartL(const TDesC8& aBuffer);
    void StartL(const TDesC8& aBuffer, TInt aReplySlot, const RMessagePtr2& aMessage);
    TPtrC8 UpdateL(const TDesC8& aBuffer);
    void Cancel();
    
    // From MAknListQueryNotificationCallback.
    void QueryDismissedL(TInt aResult);

private:
    CAknGlobalListMsgQuerySubject();
    void ConstructL();

private:
    CAknListMsgQueryNotificationDialog* iDlg;
    RMessagePtr2 iMessage;
    const TAny* iReturnVal;
    TBool iPending;
    TNotifierInfo iInfo;

    CDesCArrayFlat* iArray;
    HBufC* iHeading;
    HBufC* iMsgText;

    TInt iSelectFirst; // Which item in the array will be selected first.
    TPtrC iArrayText;  // Array text
    TInt iListIndex;
    TBool iAppsKeySuppressed;
    
    CEikonEnv* iStoredEikonEnv;
    };

#endif // __AKNSYSTEMLISTMSGPOPUP_H__

// End of File
