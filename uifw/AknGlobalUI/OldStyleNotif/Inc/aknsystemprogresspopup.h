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
* Description:  Plugin declaration of global progress dialog.
*
*/

#ifndef __AKNSYSTEMPROGRESSPOPUP_H__
#define __AKNSYSTEMPROGRESSPOPUP_H__

#include <e32std.h>
#include <e32base.h>
#include <eiknotapi.h>
#include <eikcmobs.h>
#include <AknProgressDialog.h>

class CAknProgressDialog;

NONSHARABLE_CLASS(CAknGlobalProgressDialogSubject) : 
    public CBase, 
    public MEikSrvNotifierBase2, 
    public MProgressDialogCallback
	{
public:
	static CAknGlobalProgressDialogSubject* NewL();
	virtual ~CAknGlobalProgressDialogSubject();
	
	// From MEikSrvNotifierBase.
	void Release();
	TNotifierInfo RegisterL();
	TNotifierInfo Info() const;
	TPtrC8 StartL(const TDesC8& aBuffer);
	void StartL(const TDesC8& aBuffer, TInt aReplySlot, const RMessagePtr2& aMessage);
	TPtrC8 UpdateL(const TDesC8& aBuffer);
	void Cancel();
	
    // From MProgressDialogCallback.
    void DialogDismissedL(TInt aButtonId);

private:
	CAknGlobalProgressDialogSubject();
	void ConstructL();

private:
	RMessagePtr2 iMessage;
	const TAny* iReturnVal;
	TBool iPending;
	TNotifierInfo iInfo;
    HBufC* iPrompt;
    CEikProgressInfo* iProgressInfo;
    CAknProgressDialog* iDlg;
	TBool iAppsKeySuppressed;
	CEikonEnv* iStoredEikonEnv;
    };

#endif // __AKNSYSTEMPROGRESSPOPUP_H__

// End of file
