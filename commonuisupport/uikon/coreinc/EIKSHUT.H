// Copyright (c) 1997-2009 Nokia Corporation and/or its subsidiary(-ies).
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

#ifndef __EIKSHUT_H__
#define __EIKSHUT_H__

#include <e32base.h>
#include <coemain.h>	// class CCoeStatic

class CEikonEnv;
class CEikAppUi;

//header doesn't need to be exported to epoc32/include
/**
@internalComponent 
*/
NONSHARABLE_CLASS(CEikShutter) : private CActive, private CCoeStatic
	{
public:
	static void DeferredExecuteL(CEikonEnv& aEikEnv);
	static void DeferredExecuteL(CEikonEnv& aEikEnv, TUid aMessageUid, const TDesC8& aMessageParameters);
private: // virtual from CActive
	void DoCancel();
	void RunL();
	TInt RunError(TInt aError);
private:
	CEikShutter(CEikonEnv& aEikEnv, TUid aMessageUid, HBufC8* aMessageParameters);
	~CEikShutter();
	void Queue();
	static TInt StartLevel();
	void Terminate();
private:
	enum TFlags
		{
		ETriedDismissMenu=0x01,
		ETryingToTerminateApp=0x02,
		EDestroySelfPending=0x04,
		};
private:
	CEikonEnv& iEikEnv;
	TUid iMessageUid;
	HBufC8* iMessageParameters;
	TInt iFlags;
	TInt iCount;
	TInt iStartLevel;
	};

#endif	// __EIKSHUT_H__

