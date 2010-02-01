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

#include <eikstart.h>
#include <fbs.h>

#include "tbitmap.h"


//
//
// CBitmapAppUi
//
//

CBitmapAppUi::CBitmapAppUi() : CTestAppUi(NULL, KNullDesC)
  {
  }

void CBitmapAppUi::ConstructL()
    {
   	CTestAppUi::ConstructL();
	AutoTestManager().StartAutoTest();
	}

CBitmapAppUi::~CBitmapAppUi()
	{
	}

void CBitmapAppUi::HandleCommandL(TInt /*aCommand*/)
	{
	}


void CBitmapAppUi::TestCreateBitmapL()
	{
	_LIT(KApplicationDefaultBitmapPath,"z:\\resource\\apps\\tbitmap.mbm");
	_LIT(KFileNameWildCharacterDoubleQuote,"*");
			
	CEikonEnv* eikonEnv = CEikonEnv::Static();
	
	CFbsBitmap* appDefaultBitmap = eikonEnv->CreateBitmapL(KApplicationDefaultBitmapPath,0);
	CleanupStack::PushL(appDefaultBitmap);
	CFbsBitmap* WildCharacterBitmapDoubleQuote = eikonEnv->CreateBitmapL(KFileNameWildCharacterDoubleQuote, 0);
	CleanupStack::PushL(WildCharacterBitmapDoubleQuote);

	CompareBitmapsL(*appDefaultBitmap, *WildCharacterBitmapDoubleQuote, EColor16M);
	
	CleanupStack::PopAndDestroy(2, appDefaultBitmap);
	}


void CBitmapAppUi::CompareBitmapsL(CFbsBitmap& aBmp1,CFbsBitmap& aBmp2,TDisplayMode aDispMode) const
	{
	const TSize bmpSize = aBmp1.SizeInPixels();
	if (!(bmpSize == aBmp2.SizeInPixels()))
		{
		RProcess().Terminate(KErrBitMapDoesNotMatch);
		}

	RBuf8 buf1; 
	CleanupClosePushL(buf1);
	buf1.CreateL(bmpSize.iWidth * 4);
	RBuf8 buf2;
	CleanupClosePushL(buf2);
	buf2.CreateL(bmpSize.iWidth * 4);
	
	for (TInt row = 0; row < bmpSize.iHeight; row++)
		{
		aBmp1.GetScanLine(buf1, TPoint(0,row), bmpSize.iWidth, aDispMode);
		aBmp2.GetScanLine(buf2, TPoint(0,row), bmpSize.iWidth, aDispMode);
		const TInt ret = buf1.Compare(buf2);
		if (ret != 0)
			{
			CleanupStack::PopAndDestroy(2, &buf1);
			RProcess().Terminate(KErrBitMapDoesNotMatch);
			}
		}
	CleanupStack::PopAndDestroy(2, &buf1);
	}
	
void CBitmapAppUi::RunTestStepL(TInt aNumStep)
	{
	switch(aNumStep)
		{
		case 1:	
			{
			TRAPD(err, TestCreateBitmapL());
			if (err != KErrNone)
				{
				RProcess().Terminate(err);
				}
			AutoTestManager().FinishAllTestCases(CAutoTestManager::EPass);
			break;
			}
		default:
			break;
		}
	
	}

//
//
// CBitmapDocument
//
//
CBitmapDocument::CBitmapDocument(CEikApplication& aApp)
		: CEikDocument(aApp)
	{
	}

CEikAppUi* CBitmapDocument::CreateAppUiL()
	{
	return new (ELeave) CBitmapAppUi();
    }


//
//
// CBitmapApplication
//
//
TUid CBitmapApplication::AppDllUid() const
	{
	return KUidBitmap;
	}

CApaDocument* CBitmapApplication::CreateDocumentL()
	{
	return new (ELeave) CBitmapDocument(*this);
	}

LOCAL_C CApaApplication* NewApplication()
	{
	return new CBitmapApplication;
	}

GLDEF_C TInt E32Main()
	{
	return EikStart::RunApplication(NewApplication);
	}

