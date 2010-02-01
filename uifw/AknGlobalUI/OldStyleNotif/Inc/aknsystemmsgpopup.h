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
* Description:  Plugin declaration of global message query.
*
*/

#ifndef __AKNSYSTEMMSGPOPUP_H__
#define __AKNSYSTEMMSGPOPUP_H__

#include <e32std.h>
#include <e32base.h>
#include <eiknotapi.h>
#include <eikcmobs.h>
#include <aknmessagequerydialog.h>

class CApaMaskedBitmap;

class MAknQueryNotificationCallback
    {
public:
    virtual void QueryDismissedL(TInt aResult) = 0;
    };

NONSHARABLE_CLASS(CAknMsgQueryNotificationDialog) : public CAknMessageQueryDialog
    {
public:
    CAknMsgQueryNotificationDialog(
        MAknQueryNotificationCallback* aCallBack,
        CAknMsgQueryNotificationDialog** aSelfPtr,
        HBufC* aMessage,
        TInt aSoftkeys,
        HBufC* aHeader,
        CEikImage* aHeaderImage = NULL,
        const TTone aTone = ENoTone);

    ~CAknMsgQueryNotificationDialog();
    
    TKeyResponse OfferKeyEventL( 
        const TKeyEvent& aKeyEvent,
        TEventCode aType);

protected:
    TBool OkToExitL(TInt aButtonId);
    void PreLayoutDynInitL();
    void PostLayoutDynInitL();

private:
    virtual void CEikDialog_Reserved_1();
    virtual void CEikDialog_Reserved_2();   
    virtual void CAknDialog_Reserved();
    virtual void CAknQueryDialog_Reserved();

private:
    TInt iSoftkeys;
    MAknQueryNotificationCallback* iCallBack;
    CAknMsgQueryNotificationDialog** iSelfPtr;
    CPeriodic* iTimer;
    TInt iDelay;
    
    // These are needed because of awkward APIs and member handling in base class.
    HBufC* iMessage;
    HBufC* iHeader;
    CEikImage* iHeaderImage;

    static TInt DeleteMe(TAny* aThis);

public: 
    void SetExitDelay(TInt aDelay) {iDelay = aDelay;};
    };

NONSHARABLE_CLASS(CAknGlobalMsgQuerySubject): 
    public CBase, 
    public MEikSrvNotifierBase2, 
    public MAknQueryNotificationCallback
    {
public:
    static CAknGlobalMsgQuerySubject* NewL();
    virtual ~CAknGlobalMsgQuerySubject();
    
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
    CAknGlobalMsgQuerySubject();
    void ConstructL();

private:
    RMessagePtr2 iMessage;
    const TAny* iReturnVal;
    TBool iPending;
    TNotifierInfo iInfo;
    CAknMsgQueryNotificationDialog* iDlg;
    TBool iAppsKeySuppressed;
    CApaMaskedBitmap* iBitmap;
    
    CEikonEnv* iStoredEikonEnv;    
    };

#endif // __AKNSYSTEMMSGPOPUP_H__

// End of file
