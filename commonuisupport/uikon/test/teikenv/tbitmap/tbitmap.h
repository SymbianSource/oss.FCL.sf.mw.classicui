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

/**
 @file
 @test
 @internalComponent - Internal Symbian test code
*/

#ifndef		__TBITMAP_H
#define		__TBITMAP_H

#include <eikappui.h>
#include <eikapp.h>
#include <eikdoc.h>
#include <eikenv.h>
#include <apgcli.h>
#include <eikon.mbg>

#include <test/testexecutestepbase.h>
#include "appfwk_test_AppUi.h"


_LIT16(KTestBitmapStep, "TBitMap");

const TUid KUidBitmap = {0xA000110E}; 
const TInt KErrBitMapDoesNotMatch = -1234;


//
//
// CBitmapAppUi
//
//
class CBitmapAppUi : public CTestAppUi
    {
public:
	CBitmapAppUi();
    void ConstructL();
	~CBitmapAppUi();

private: 
	void RunTestStepL(TInt aNumStep);
	// from CEikAppUi
	void HandleCommandL(TInt aCommand);	

private:
	void TestCreateBitmapL();
	void CompareBitmapsL(CFbsBitmap& aBmp1, CFbsBitmap& aBmp2, TDisplayMode aDispMode) const;
	};


//
//
// CBitmapDocument
//
//
class CBitmapDocument : public CEikDocument
	{
public:
	static CBitmapDocument* NewL(CEikApplication& aApp);
	CBitmapDocument(CEikApplication& aApp);
	void ConstructL();

private: 
	// Inherited from CEikDocument
	CEikAppUi* CreateAppUiL();
	};
	

//
//
// CBitmapApplication
//
//
class CBitmapApplication : public CEikApplication
	{
private: 
	// Inherited from class CApaApplication
	CApaDocument* CreateDocumentL();
	TUid AppDllUid() const;

private:
	CApaDocument* CreateDocumentL(CApaProcess* a) { return CEikApplication::CreateDocumentL(a); }
	};

#endif


