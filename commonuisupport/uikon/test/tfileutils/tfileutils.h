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
// Tests EikFileUtils APIs.
// 
//

/**
 @file
 @internalComponent - Internal Symbian test code
*/

#if (!defined __TFILEUTILS_H__)
#define __TFILEUTILS_H__


#include <test/testexecutestepbase.h>
#include "appfwk_test_AppUi.h"


//!  A CFileUtilsStep test class. 
/**
 Tests EikFileUtils APIs.
*/
class CFileUtilsStep : public CTmsTestStep
	{
public:
	CFileUtilsStep();
	~CFileUtilsStep();
	virtual TVerdict doTestStepL();
	void ConstructAppL(CEikonEnv* aEikEnv);
private:
	};


//!  CTFileUtilsAppUi 
/**
 UI class for test class CFileUtilsStep.
*/
class CTFileUtilsAppUi : public CTestAppUi
    {
public:
	CTFileUtilsAppUi(CTmsTestStep* aStep);
    void ConstructL();
    ~CTFileUtilsAppUi();
protected: //from CTestAppUi
 	virtual void RunTestStepL(TInt aNumStep);
private: // framework
private://test functions
	void TestFileOperations();
	void TestFileOperations2();
	void TestFileOperations3();
	void TestFileOperations4();
	void TestUidTypeMatches();
	void TestAbbreviateFileName();
	TFileName FolderNameFromFullName(const TDesC& aFullName);
	void TestValidFolderName();
	void TestDiskListL();
	void TestSortByTableL();
    };

_LIT(KFileUtilsStep,"TFileUtils");

#endif


