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

#if !defined(__TPLUGINV2_H__)
#define __TPLUGINV2_H__

#include <e32std.h>
#include <e32base.h>
#include <eiknotapi.h>
#include <techview/eikdialg.h>
#include <eikmsg.h>			

// Used by ecom based Version2 notifiers
const TUid KMyNewPhoneNotifierUid={0x10021241};
const TUid KMyNewLowBatteryNotifierUid={0x10021242};
const TUid KMyNewAgendaAlarmUid={0x10021243};

// Used by non ecom based Version2 notifiers
const TUid KMyPhoneNotifierUid={0x10021234};
const TUid KMyLowBatteryNotifierUid={0x10021235};
const TUid KMyAgendaAlarmUid={0x10021236};


IMPORT_C CArrayPtr<MEikSrvNotifierBase2>* NotifierArray();

class CMyPhoneNotifierSubject:  public CEikDialog, public MEikSrvNotifierBase2
	{
public:
	static CMyPhoneNotifierSubject* NewLC();
	~CMyPhoneNotifierSubject();

private:
	CMyPhoneNotifierSubject();
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


class CMyLEDPhoneNotifierSubject: public CEikDialog, public MEikSrvNotifierBase2
	{
public:
	static CMyLEDPhoneNotifierSubject* NewLC();
	~CMyLEDPhoneNotifierSubject();

private:
	CMyLEDPhoneNotifierSubject();
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

class CMyLowBatteryNotifierSubject: public CEikDialog, public MEikSrvNotifierBase2
	{
public:
	static CMyLowBatteryNotifierSubject* NewLC();
	~CMyLowBatteryNotifierSubject();

private:
	CMyLowBatteryNotifierSubject();
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
	//Added for flip support GPO 18.05.2001
	void HandleSystemEventL(TUid aEvent);
	//Added for flip support GPO 18.05.2001
	virtual TInt NotifierCapabilites();

private:

	TNotifierInfo iInfo;

	};

class CMyLEDLowBatteryNotifierSubject: public CEikDialog, public MEikSrvNotifierBase2
	{
	public:
	static CMyLEDLowBatteryNotifierSubject* NewLC();
	~CMyLEDLowBatteryNotifierSubject();


private:
	CMyLEDLowBatteryNotifierSubject();
	void ConstructL();
	TInt DisplayNotifier();

//from MEikSrvNotifierBase
	void Release();
	TNotifierInfo RegisterL();
	TNotifierInfo Info() const;
	TPtrC8 StartL(const TDesC8& aBuffer);
	void StartL(const TDesC8& aBuffer, TInt aReplySlot, const RMessagePtr2& aMessage);
	void Cancel();
	TPtrC8 UpdateL(const TDesC8& aBuffer);
	void UpdateL(const TDesC8& aBuffer, TInt aReplySlot, const RMessagePtr2& aMessage);
	//Added for flip support GPO 18.05.2001
	void HandleSystemEventL(TUid aEvent);
	//Added for flip support GPO 18.05.2001
	virtual TInt NotifierCapabilites();
private:

	TNotifierInfo iInfo;
	CEikBusyMsgWin* iBusyMsgWin;

	};


class CMyAgendaNotifierSubject: public CEikDialog, public MEikSrvNotifierBase2
	{
public:
	static CMyAgendaNotifierSubject* NewLC();
	~CMyAgendaNotifierSubject();


private:
	CMyAgendaNotifierSubject();
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


class CMyLEDAgendaNotifierSubject: public CEikDialog, public MEikSrvNotifierBase2
	{
public:
	static CMyLEDAgendaNotifierSubject* NewLC();
	~CMyLEDAgendaNotifierSubject();

private:
	CMyLEDAgendaNotifierSubject();
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
