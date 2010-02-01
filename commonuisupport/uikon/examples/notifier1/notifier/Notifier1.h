// Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
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

#ifndef __NOTIFIER1_H__
#define __NOTIFIER1_H__

#include <eikdialg.h>	// For CEikDialog
#include <eiknotapi.h> 	// For MEikSrvNotifierBase2

class CNotifier1 : public CEikDialog, public MEikSrvNotifierBase2
	{
public:
	static CNotifier1* NewLC();
	~CNotifier1();
	
private:
	CNotifier1();
	void ConstructL();
	
public:	// from MEikSrvNotifierBase2
	void Release();
	TNotifierInfo RegisterL();
	TNotifierInfo Info() const;
	void StartL(const TDesC8& aBuffer, TInt aReplySlot, const RMessagePtr2& aMessage);
	TPtrC8 StartL(const TDesC8& aBuffer);
	void Cancel();
	TPtrC8 UpdateL(const TDesC8& aBuffer);
	void UpdateL(const TDesC8& aBuffer, TInt aReplySlot, const RMessagePtr2& aMessage);
	
private:
	TNotifierInfo iInfo;
	};

#endif
