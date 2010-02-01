// Copyright (c) 2005-2009 Nokia Corporation and/or its subsidiary(-ies).
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

/**
 @file
 @internalComponent - Internal Symbian test code 
*/

#if !defined(__TNOTIFY2V2_H__)
#define __TNOTIFY2V2_H__

#include <e32std.h>
#include <e32base.h>
#include <eiknotapi.h>
#include <techview/eikdialg.h>
#include <eikmsg.h>			

// Used by ecom based Version2 notifiers
const TUid KMyNewSmsNotifierUid={0x10021238};
const TUid KMyNewEmailNotifierUid={0x10021237};

// Used by non ecom based Version2 notifiers
const TUid KMySmsNotifierUid={0x10021231};
const TUid KMyEmailNotifierUid={0x10021230};


IMPORT_C CArrayPtr<MEikSrvNotifierBase2>* NotifierArray();

class CMySmsNotifierSubject:  public CEikDialog, public MEikSrvNotifierBase2
	{
public:
	static CMySmsNotifierSubject* NewLC();
	~CMySmsNotifierSubject();

private:
	CMySmsNotifierSubject();
	void ConstructL();
	TInt DisplayNotifier();
//from CEikDialog
	void PreLayoutDynInitL();
	TBool OkToExitL(TInt aButtonId);
//from MEikSrvNotifierBase
	void Release();
	TNotifierInfo RegisterL();
	TNotifierInfo Info() const;
	TPtrC8 StartL(const TDesC8& aBuffer);
	void StartL(const TDesC8& aBuffer, TInt aReplySlot, const RMessagePtr2& aMessage);
	void Cancel();
	TPtrC8 UpdateL(const TDesC8& aBuffer);
	void UpdateL(const TDesC8& aBuffer, TInt aReplySlot, const RMessagePtr2& aMessage);

private:

	TNotifierInfo iInfo;

	};


class CMyLEDSmsNotifierSubject: public CEikDialog, public MEikSrvNotifierBase2
	{
public:
	static CMyLEDSmsNotifierSubject* NewLC();
	~CMyLEDSmsNotifierSubject();

private:
	CMyLEDSmsNotifierSubject();
	void ConstructL();
	TInt DisplayNotifier();

//from MEikSrvNotifierBase2
	void Release();
	TNotifierInfo RegisterL();
	TNotifierInfo Info() const;
	TPtrC8 StartL(const TDesC8& aBuffer);
	void StartL(const TDesC8& aBuffer, TInt aReplySlot, const RMessagePtr2& aMessage);
	void Cancel();
	TPtrC8 UpdateL(const TDesC8& aBuffer);
	void UpdateL(const TDesC8& aBuffer, TInt aReplySlot, const RMessagePtr2& aMessage);

private:

	TNotifierInfo iInfo;
	CEikBusyMsgWin* iBusyMsgWin;
	};



class CMyEmailNotifierSubject: public CEikDialog, public MEikSrvNotifierBase2
	{
public:
	static CMyEmailNotifierSubject* NewLC();
	~CMyEmailNotifierSubject();


private:
	CMyEmailNotifierSubject();
	void ConstructL();
	TInt DisplayNotifier();
//from CEikDialog
	void PreLayoutDynInitL();
	TBool OkToExitL(TInt aButtonId);

//from MEikSrvNotifierBase2
	void Release();
	TNotifierInfo RegisterL();
	TNotifierInfo Info() const;
	TPtrC8 StartL(const TDesC8& aBuffer);
	void StartL(const TDesC8& aBuffer, TInt aReplySlot, const RMessagePtr2& aMessage);
	void Cancel();
	TPtrC8 UpdateL(const TDesC8& aBuffer);
	void UpdateL(const TDesC8& aBuffer, TInt aReplySlot, const RMessagePtr2& aMessage);
private:
	TNotifierInfo iInfo;
	};


class CMyLEDEmailNotifierSubject: public CEikDialog, public MEikSrvNotifierBase2
	{
public:
	static CMyLEDEmailNotifierSubject* NewLC();
	~CMyLEDEmailNotifierSubject();

private:
	CMyLEDEmailNotifierSubject();
	void ConstructL();
	TInt DisplayNotifier();

//from MEikSrvNotifierBase2
	void Release();
	TNotifierInfo RegisterL();
	TNotifierInfo Info() const;
	TPtrC8 StartL(const TDesC8& aBuffer);
	void StartL(const TDesC8& aBuffer, TInt aReplySlot, const RMessagePtr2& aMessage);
	void Cancel();
	TPtrC8 UpdateL(const TDesC8& aBuffer);
	void UpdateL(const TDesC8& aBuffer, TInt aReplySlot, const RMessagePtr2& aMessage);
private:
	TNotifierInfo iInfo;
	CEikBusyMsgWin* iBusyMsgWin;
	};


#endif
