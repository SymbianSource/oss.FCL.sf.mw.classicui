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
 @internalComponent - Internal Symbian test code.    
*/


#include <coecntss.h>
#include <coemain.h>
#include <coefontprovider.h>
#include <coefont.h>
#include <eikenv.h>

#include "tconecoecntssstep.h"

	
/**
   @SYMTestCaseID 	UIF-TConeTestApp-TestSetLogicalToPixelFontSizesL
  
   @SYMPREQ			DEF093550
  
   @SYMTestCaseDesc Tests the correct bevaciour of Set and Get LogicalToPixelFontSizes methods
  
   @SYMTestPriority High
  
   @SYMTestType : 	CIT 

   @SYMTestStatus 	Implemented
   
   @SYMTestActions: The tests starts by getting a copy of the default array of font pixel sizes by means of
   					a call to GetLogicalToPixelFontSizesL().
   					Different Font sizes are appended to the RArray and SetLogicalToPixelFontSizesL() function
   					is invoked, checking that the new values have been correctly added.
   					All original value are restored before finishing the test case.
  
   @SYMTestExpectedResults The Font's Size should be equal to the size that is appended.\n  
 */
void CTConeCoeCntSSAppUi::TestGetSetLogicalToPixelFontSizesL()
	{

	INFO_PRINTF1(_L("TestGetSetLogicalToPixelFontSizesL() test case started"));

	//Get a copy of the old sizes, for later restoration.
	INFO_PRINTF1(_L("Populates a TInt array provided as a parameter with the font pixel sizes..."));
	RArray<TInt> oldSizes;
	CleanupClosePushL(oldSizes);
	
	TRAPD(ret, CCoeControlStaticSettings::GetLogicalToPixelFontSizesL(oldSizes));
	TEST(ret == KErrNone);

	INFO_PRINTF1(_L("Values of original array:"));
	for (TInt ii=0; ii<oldSizes.Count(); ii++)
		{
		INFO_PRINTF3(_L("	Array[%d] = '%d'"), ii, oldSizes[ii]);
		}		
	
	//Append different sizes to the array.	
	INFO_PRINTF1(_L("Set new default array of font pixel sizes..."));
	RArray<TInt> newSizes;
	CleanupClosePushL(newSizes);

	newSizes.AppendL(24);		// Extra Small
	newSizes.AppendL(34);		// Small
	newSizes.AppendL(44);		// Medium
	newSizes.AppendL(54);		// Large
	newSizes.AppendL(64);		// Extra Large
   
	TRAP(ret, CCoeControlStaticSettings::SetLogicalToPixelFontSizesL(newSizes));
	TEST(ret == KErrNone);
	
    //Get the Zoomfactor and Font provider to obtain the fontsize and check it matches with new values.
	TZoomFactor accZoomFactor(iCoeEnv->ScreenDevice());
	const CCoeFontProvider& fontProvider = iCoeEnv->DefaultFontProvider();
	
	const CFont& font1 = fontProvider.Font(TCoeFont(TCoeFont::EExtraSmall, TCoeFont::EPlain), accZoomFactor);
	TInt actualSize1 = font1.FontMaxHeight();
	TEST(Rng(23, actualSize1, 24));

	const CFont& font2 = fontProvider.Font(TCoeFont(TCoeFont::ESmall, TCoeFont::EPlain), accZoomFactor);
	TInt actualSize2 = font2.FontMaxHeight();
	TEST(Rng(33, actualSize2, 34));

	const CFont& font3 = fontProvider.Font(TCoeFont(TCoeFont::EMedium, TCoeFont::EPlain), accZoomFactor);
	TInt actualSize3 = font3.FontMaxHeight();
	TEST(Rng(43, actualSize3, 44));

	const CFont& font4 = fontProvider.Font(TCoeFont(TCoeFont::ELarge, TCoeFont::EPlain), accZoomFactor);
	TInt actualSize4 = font4.FontMaxHeight();
	TEST(Rng(53, actualSize4, 54));

	const CFont& font5 = fontProvider.Font(TCoeFont(TCoeFont::EExtraLarge, TCoeFont::EPlain), accZoomFactor);
	TInt actualSize5 = font5.FontMaxHeight();
	TEST(Rng(63, actualSize5, 64));

	//Print new values of the array
	newSizes.Reset();
	TRAP(ret, CCoeControlStaticSettings::GetLogicalToPixelFontSizesL(newSizes));
	TEST(ret == KErrNone);

	INFO_PRINTF1(_L("Values of new array:"));
	for (TInt jj=0; jj<newSizes.Count(); jj++)
		{
		INFO_PRINTF3(_L("	Array[%d] = '%d'"), jj, newSizes[jj]);
		}		

	//Restoring original values
	INFO_PRINTF1(_L("Restoring original values..."));
	TRAP(ret, CCoeControlStaticSettings::SetLogicalToPixelFontSizesL(oldSizes));
	TEST(ret == KErrNone);
	
	//clean-up
	CleanupStack::PopAndDestroy(2, &oldSizes);
	}


void CTConeCoeCntSSAppUi::RunTestStepL(TInt aStepNum)
	{
	switch(aStepNum)
		{
		case 1:
			{
			SetTestStepID(_L("UIF-TConeTestApp-TestSetLogicalToPixelFontSizesL"));			
			TRAPD(ret, TestGetSetLogicalToPixelFontSizesL());
			TEST(ret == KErrNone);
			INFO_PRINTF2(_L("TestSetLogicalToPixelFontSizesL() finished with code '%d'"), ret);
			RecordTestResultL();	
			CloseTMSGraphicsStep();
			}
			break;

		default:
			AutoTestManager().FinishAllTestCases(CAutoTestManager::EPass);
			break;
		}
	}


void CTConeCoeCntSSAppUi::ConstructL()
	{
	CTestCoeAppUi::ConstructL();
	AutoTestManager().StartAutoTest();	
	}

CTConeCoeCntSSAppUi::CTConeCoeCntSSAppUi(CTmsTestStep* aStep) :
	CTestCoeAppUi(aStep)
	{
	}

CTConeCoeCntSSAppUi::~CTConeCoeCntSSAppUi()
	{
	}


//----------

void CTConeCoeCntSSStep::ConstructAppL(CCoeEnv* aCoe)
	{ // runs inside a TRAP harness
	aCoe->ConstructL();
	CTConeCoeCntSSAppUi* appUi= new (ELeave) CTConeCoeCntSSAppUi(this);
	aCoe->SetAppUi(appUi);
	appUi->ConstructL();
	}


CTConeCoeCntSSStep::CTConeCoeCntSSStep()
	{
	SetTestStepName(KTConeCoeCntSSStep);
	}

CTConeCoeCntSSStep::~CTConeCoeCntSSStep()
	{
	}

TVerdict CTConeCoeCntSSStep::doTestStepL()
	{
	INFO_PRINTF1(_L("Testing of CoeContolStaticSettings started..."));
	
	PreallocateHALBuffer();

	__UHEAP_MARK;
	CCoeEnv* coe=new(ELeave) CCoeEnv;
	TRAPD(err,ConstructAppL(coe));

	if (!err)
		coe->ExecuteD();
	else
		{
		SetTestStepResult(EFail);
		delete coe;
		}
	
	REComSession::FinalClose();	
	__UHEAP_MARKEND;

	INFO_PRINTF1(_L("...testing of CoeContolStaticSettings finished!"));
	return TestStepResult();
	}
