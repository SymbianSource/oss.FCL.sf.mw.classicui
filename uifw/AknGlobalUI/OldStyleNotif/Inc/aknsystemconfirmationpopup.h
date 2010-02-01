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
* Description:  Plugin implementation of global confirmation query.
*
*/

#ifndef __AKNSYSTEMCONFIRMATIONPOPUP_H__
#define __AKNSYSTEMCONFIRMATIONPOPUP_H__

#include <e32std.h>
#include <e32base.h>
#include <eiknotapi.h>
#include <eikcmobs.h>
#include <AknQueryDialog.h>
#include "aknsystemmsgpopup.h" // for MAknQueryNotificationCallback

NONSHARABLE_CLASS(CAknQueryNotificationDialog) : public CAknQueryDialog
    {
public:
    CAknQueryNotificationDialog(
        MAknQueryNotificationCallback* aCallBack,
        CAknQueryNotificationDialog** aSelfPtr,
        TInt aSoftkeys = 0,
        TInt aAnimation = 0,
        CEikImage* aImage = NULL,
        const TTone aTone = ENoTone,
        TBool aEveryKeyDismisses = EFalse,
        TInt aImageId = 0,
        TInt aMaskId = 0);

    ~CAknQueryNotificationDialog();
    
    TKeyResponse OfferKeyEventL( 
        const TKeyEvent& aKeyEvent,
        TEventCode aType);

protected:
    TBool OkToExitL(TInt aButtonId);
    void PostLayoutDynInitL();

private:
    virtual void CEikDialog_Reserved_1();
    virtual void CEikDialog_Reserved_2();   
    virtual void CAknDialog_Reserved();
    virtual void CAknQueryDialog_Reserved();

private:
    TInt iSoftkeys;
    TInt iAnimation;
    CEikImage* iImage;
    MAknQueryNotificationCallback* iCallBack;
    CAknQueryNotificationDialog** iSelfPtr;
    TBool iEveryKeyDismisses;
    TInt iImageId, iMaskId;
    };


NONSHARABLE_CLASS(CAknGlobalConfirmationQuerySubject) : 
    public CBase, 
    public MEikSrvNotifierBase2, 
    public MAknQueryNotificationCallback
    {
public:
    static CAknGlobalConfirmationQuerySubject* NewL();
    virtual ~CAknGlobalConfirmationQuerySubject();
    
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
    CAknGlobalConfirmationQuerySubject();
    void ConstructL();

private:
    RMessagePtr2 iMessage;
    const TAny* iReturnVal;
    TBool iPending;
    TNotifierInfo iInfo;
    CAknQueryNotificationDialog* iDlg;
    TBool iAppsKeySuppressed;

    CEikonEnv* iStoredEikonEnv;
    };

#endif // __AKNSYSTEMCONFIRMATIONPOPUP_H__

// End of file
