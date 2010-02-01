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
// Tests embedding feature of the application.
// 
//

/**
 @file
 @internalComponent - Internal Symbian test code
*/

#ifndef		__APPLANGSCSTARTER_H
#define		__APPLANGSCSTARTER_H


#include "appfwk_test_AppUi.h"
#include "messageactive.h"
#include "messageprovider.h"

_LIT(KTestApplicationLanguageSCStep, "TApplicationLanguageSC");

class CTestApplicationLanguageSCStep;


//! A CTestPackageStep test step class
/**
Class tests embedding feature of the application.
*/
class CTestApplicationLanguageSCStep : public MMessageProvider, public CTmsTestStep
	{
public:
	CTestApplicationLanguageSCStep();
	~CTestApplicationLanguageSCStep();
	virtual TVerdict doTestStepL();
	void ConstructAppL(CEikonEnv* aCoe);
	
public:	// from MMessageProvider
	virtual CMessageActive* Message() 
	{
		 return iMessage;
	}
	
	virtual RSemaphore& Semaphore() 
	{
		return semaphore;
	}
	
	RSemaphore semaphore;
	TInt StartThread();
	CMessageActive	*iMessage;
	};
	

#endif


