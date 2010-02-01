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
// Support for communication between processes during uikon tests.
// 
//

/**
 @file
 @internalComponent - Internal Symbian test code
*/

#ifndef	__MESSAGEACTIVE_H
#define	__MESSAGEACTIVE_H

#include <e32base.h>
#include <test/testexecutestepbase.h>

//! CMessageActive
/**
Class is used to log message from client.
*/
class CMessageActive : public CActive
{
public:
	IMPORT_C static CMessageActive* NewL(); 
	IMPORT_C ~CMessageActive();
	void RequestForTheMessageOutput(TInt aCode = KErrNone);
	
private:
	CMessageActive();
 
	void RunL();
	void DoCancel();
	void Init();
	
private:
	TThreadId iID;
	
public:
	CTestStep* iStep;
	TInt iLineNumber;
	TInt iError;
	TBuf<512> iMsg;
	TBuf8<256> iFileName;
};

#endif
