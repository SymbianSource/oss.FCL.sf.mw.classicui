/*
* Copyright (c) 2002-2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Plugin declaration of global list query.
*
*/

#ifndef __AKNSYSTEMLISTPOPUP_H__
#define __AKNSYSTEMLISTPOPUP_H__

#include <e32std.h>
#include <e32base.h>
#include <eiknotapi.h>
#include <eikcmobs.h>
#include <AknNotifyStd.h>
#include "AknListQueryNotificationDialog.h"
#include "AknNotifierControllerPlugin.h"

NONSHARABLE_CLASS(CAknGlobalListQuerySubject): 
    public CBase, 
    public MEikSrvNotifierBase2, 
    public MAknListQueryNotificationCallback
    {
public:
    static CAknGlobalListQuerySubject* NewL(MAknKeyLockController* aKeyLockController);
    virtual ~CAknGlobalListQuerySubject();
    
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
    
    TBool IsKeyLockEnable()
        {
        return iKeyLockController->IsKeyLockEnabled();
        }

private:
    CAknGlobalListQuerySubject(MAknKeyLockController* aKeyLockController);
    void ConstructL();

private:
    CAknListQueryNotificationDialog* iDlg;
    RMessagePtr2 iMessage;
    const TAny* iReturnVal;
    TBool iPending;
    TNotifierInfo iInfo;

    CDesCArrayFlat* iArray;
    HBufC* iHeading;

    TInt iSelectFirst; // Which item in the array will be selected first.
    TPtrC iArrayText;  // Array text
    TInt iListIndex;
    TBool iAppsKeySuppressed;
    
    CEikonEnv* iStoredEikonEnv;
    
    MAknKeyLockController* iKeyLockController;
    
    };

#endif // __AKNSYSTEMLISTPOPUP_H__

// End of file
