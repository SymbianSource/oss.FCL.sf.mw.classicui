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
 @internalComponent - Internal Symbian test code 
*/


#include <e32keys.h>
#include <basched.h>
#include <coemain.h>
#include <coeaui.h>
#include <gulutil.h>

#include "TEgulAlignmentStep.h"



CTestAlignmentUi::CTestAlignmentUi(CTmsTestStep* aStep) :
	CTestCoeAppUi(aStep)
	{}

CTestAlignmentUi::~CTestAlignmentUi()
	{
	}

void CTestAlignmentUi::ConstructL()
	{
	CTestCoeAppUi::ConstructL();
	AutoTestManager().StartAutoTest();
	}


void CTestAlignmentUi::RunTestStepL(TInt aStep)
	{
	TGulAlignment align(EHLeftVTop);
	
	switch(aStep)
		{
	case 1:
		// Check that SetAbsoluteHAlignment() / HasAbsoluteHAlignment() works
		INFO_PRINTF1(_L("Test SetAbsoluteHAlignment() / HasAbsoluteHAlignment()"));
		TEST(!align.HasAbsoluteHAlignment());	// Make sure default value is false
	
		align.SetAbsoluteHAlignment(ETrue);		// Set to true
		TEST(align.HasAbsoluteHAlignment());	// Verify true
		
		align.SetAbsoluteHAlignment(EFalse);	// Set to false
		TEST(!align.HasAbsoluteHAlignment());	// Verify false
		
		// Check the operation of the implicitly called TGulAlignment(TGulAlignmentValue) constructor
		align.SetAbsoluteHAlignment(ETrue);		// Set to true
		align = EHRightVBottom;					// Change alignement to lower right...
		TEST(!align.HasAbsoluteHAlignment());	// ...and verify that absolution is reset to false
		break;
	case 2:
		// Check that HAlignment() swapps left and right for RightToLeft scripts, unless absolute alignment is set
		INFO_PRINTF1(_L("Test HAlignment(TBidiText::TDirectionality)"));
		
		align = EHLeftVCenter;
		TEST(align.HAlignment(TBidiText::ELeftToRight) == EHLeft);	// no swapping
		TEST(align.HAlignment(TBidiText::ERightToLeft) == EHRight);	// swap!
		align.SetAbsoluteHAlignment(ETrue);
		TEST(align.HAlignment(TBidiText::ELeftToRight) == EHLeft);	// no swapping
		TEST(align.HAlignment(TBidiText::ERightToLeft) == EHLeft);	// abs, no swapping
		
		align = EHCenterVCenter;
		TEST(align.HAlignment(TBidiText::ELeftToRight) == EHCenter);
		TEST(align.HAlignment(TBidiText::ERightToLeft) == EHCenter);
		align.SetAbsoluteHAlignment(ETrue);
		TEST(align.HAlignment(TBidiText::ELeftToRight) == EHCenter);
		TEST(align.HAlignment(TBidiText::ERightToLeft) == EHCenter);
		
		align = EHRightVCenter;
		TEST(align.HAlignment(TBidiText::ELeftToRight) == EHRight);	// no swapping
		TEST(align.HAlignment(TBidiText::ERightToLeft) == EHLeft);	// swap!
		align.SetAbsoluteHAlignment(ETrue);
		TEST(align.HAlignment(TBidiText::ELeftToRight) == EHRight);	// no swapping
		TEST(align.HAlignment(TBidiText::ERightToLeft) == EHRight);	// abs, no swapping
		break;
	case 3:
		// Check the operator() allows comparation between TGulAlignment value (left side) and TGulAlignment (right side)
		INFO_PRINTF1(_L("Test TAlignment::operator()"));
		align = EHCenterVCenter;
		TEST(!align.HasAbsoluteHAlignment());	// Verify false
		
		TEST(EHCenterVCenter == align);			// Test operator() with absolute alignment flag not set
		align.SetAbsoluteHAlignment(ETrue);		// Set absolute alignment flag
		TEST(EHCenterVCenter == align);			// Test operator() with absolute alignment flag set
		break;
	case 4:
		// Check that setting the horizontal alignment resets the absolute alignment flag
		align.SetAbsoluteHAlignment(ETrue);		// Set absolute horizontal alignment
		align.SetHAlignment(EHLeft);			// Set the alignment
		TEST(align.HAlignment() == EHLeft);		// Check set operation worked
		TEST(!align.HasAbsoluteHAlignment());	// Check set operation reset the absolute alignment flag as expected
		
		align.SetAbsoluteHAlignment(ETrue);		// Same as above
		align.SetHAlignment(EHCenter);
		TEST(align.HAlignment() == EHCenter);
		TEST(!align.HasAbsoluteHAlignment());
		
		align.SetAbsoluteHAlignment(ETrue);		// Same as above
		align.SetHAlignment(EHRight);
		TEST(align.HAlignment() == EHRight);
		TEST(!align.HasAbsoluteHAlignment());
		break;
	case 5:
		{
		// Check that InnerTopLeft() and InnerRect() does not swap alignment for the inner object
		// even though absolute horizontal alignment is ON
		const TRect outerRect(10,10,110,110);
		const TSize innerSize(20,20);
		TPoint innerTopLeft;
		TRect innerRect;
		
		align.SetHAlignment(EHLeft);
		innerTopLeft = align.InnerTopLeft(outerRect, innerSize);
		TEST( innerTopLeft == TPoint(10,10) );
		innerRect = align.InnerRect(outerRect, innerSize);
		TEST( innerRect == TRect(10,10,30,30) );
		
		align.SetHAlignment(EHCenter);
		innerTopLeft = align.InnerTopLeft(outerRect, innerSize);
		TEST( innerTopLeft == TPoint(50,10) );
		innerRect = align.InnerRect(outerRect, innerSize);
		TEST( innerRect  == TRect(50,10,70,30) );
		
		align.SetHAlignment(EHRight);
		innerTopLeft = align.InnerTopLeft(outerRect, innerSize);
		TEST( innerTopLeft == TPoint(90,10) );
		innerRect = align.InnerRect(outerRect, innerSize);
		TEST( innerRect == TRect(90,10,110,30) );
		
		
		align.SetVAlignment(EVCenter);
		
		
		align.SetHAlignment(EHLeft);
		innerTopLeft = align.InnerTopLeft(outerRect, innerSize);
		TEST( innerTopLeft == TPoint(10,50) );
		innerRect = align.InnerRect(outerRect, innerSize);
		TEST( innerRect == TRect(10,50,30,70) );
		
		align.SetHAlignment(EHCenter);
		innerTopLeft = align.InnerTopLeft(outerRect, innerSize);
		TEST( innerTopLeft == TPoint(50,50) );
		innerRect = align.InnerRect(outerRect, innerSize);
		TEST( innerRect  == TRect(50,50,70,70) );
		
		align.SetHAlignment(EHRight);
		innerTopLeft = align.InnerTopLeft(outerRect, innerSize);
		TEST( innerTopLeft == TPoint(90,50) );
		innerRect = align.InnerRect(outerRect, innerSize);
		TEST( innerRect == TRect(90,50,110,70) );
		
		
		align.SetVAlignment(EVBottom);
		
		
		align.SetHAlignment(EHLeft);
		innerTopLeft = align.InnerTopLeft(outerRect, innerSize);
		TEST( innerTopLeft == TPoint(10,90) );
		innerRect = align.InnerRect(outerRect, innerSize);
		TEST( innerRect == TRect(10,90,30,110) );
		
		align.SetHAlignment(EHCenter);
		innerTopLeft = align.InnerTopLeft(outerRect, innerSize);
		TEST( innerTopLeft == TPoint(50,90) );
		innerRect = align.InnerRect(outerRect, innerSize);
		TEST( innerRect  == TRect(50,90,70,110) );
		
		align.SetHAlignment(EHRight);
		innerTopLeft = align.InnerTopLeft(outerRect, innerSize);
		TEST( innerTopLeft == TPoint(90,90) );
		innerRect = align.InnerRect(outerRect, innerSize);
		TEST( innerRect == TRect(90,90,110,110) );
		}
		break;
		
	case 6:
		{
		// Check that InnerTopLeft(TBidiText::TDirectionality) and InnerRect(TBidiText::TDirectionality) 
		// does NOT swap alignment for the inner object when scrip directionality is RightToLeft (only)
		// when absolute alignment is ON
		const TRect outerRect(10,10,110,110);
		const TSize innerSize(20,20);
		TPoint innerTopLeft;
		TRect innerRect;
		
		align.SetHAlignment(EHLeft);
		align.SetAbsoluteHAlignment(ETrue);
		innerTopLeft = align.InnerTopLeft(outerRect, innerSize);
		TEST( innerTopLeft == TPoint(10,10) );
		innerRect = align.InnerRect(outerRect, innerSize);
		TEST( innerRect == TRect(10,10,30,30) );
		
		align.SetHAlignment(EHCenter);
		align.SetAbsoluteHAlignment(ETrue);
		innerTopLeft = align.InnerTopLeft(outerRect, innerSize);
		TEST( innerTopLeft == TPoint(50,10) );
		innerRect = align.InnerRect(outerRect, innerSize);
		TEST( innerRect  == TRect(50,10,70,30) );
		
		align.SetHAlignment(EHRight);
		align.SetAbsoluteHAlignment(ETrue);
		innerTopLeft = align.InnerTopLeft(outerRect, innerSize);
		TEST( innerTopLeft == TPoint(90,10) );
		innerRect = align.InnerRect(outerRect, innerSize);
		TEST( innerRect == TRect(90,10,110,30) );
		
		
		align.SetVAlignment(EVCenter);
		
		
		align.SetHAlignment(EHLeft);
		align.SetAbsoluteHAlignment(ETrue);
		innerTopLeft = align.InnerTopLeft(outerRect, innerSize);
		TEST( innerTopLeft == TPoint(10,50) );
		innerRect = align.InnerRect(outerRect, innerSize);
		TEST( innerRect == TRect(10,50,30,70) );
		
		align.SetHAlignment(EHCenter);
		align.SetAbsoluteHAlignment(ETrue);
		innerTopLeft = align.InnerTopLeft(outerRect, innerSize);
		TEST( innerTopLeft == TPoint(50,50) );
		innerRect = align.InnerRect(outerRect, innerSize);
		TEST( innerRect  == TRect(50,50,70,70) );
		
		align.SetHAlignment(EHRight);
		align.SetAbsoluteHAlignment(ETrue);
		innerTopLeft = align.InnerTopLeft(outerRect, innerSize);
		TEST( innerTopLeft == TPoint(90,50) );
		innerRect = align.InnerRect(outerRect, innerSize);
		TEST( innerRect == TRect(90,50,110,70) );
		
		
		align.SetVAlignment(EVBottom);
		
		
		align.SetHAlignment(EHLeft);
		align.SetAbsoluteHAlignment(ETrue);
		innerTopLeft = align.InnerTopLeft(outerRect, innerSize);
		TEST( innerTopLeft == TPoint(10,90) );
		innerRect = align.InnerRect(outerRect, innerSize);
		TEST( innerRect == TRect(10,90,30,110) );
		
		align.SetHAlignment(EHCenter);
		align.SetAbsoluteHAlignment(ETrue);
		innerTopLeft = align.InnerTopLeft(outerRect, innerSize);
		TEST( innerTopLeft == TPoint(50,90) );
		innerRect = align.InnerRect(outerRect, innerSize);
		TEST( innerRect  == TRect(50,90,70,110) );
		
		align.SetHAlignment(EHRight);
		align.SetAbsoluteHAlignment(ETrue);
		innerTopLeft = align.InnerTopLeft(outerRect, innerSize);
		TEST( innerTopLeft == TPoint(90,90) );
		innerRect = align.InnerRect(outerRect, innerSize);
		TEST( innerRect == TRect(90,90,110,110) );
		}
		break;
	
	case 7:
		{
		// Check that InnerTopLeft(TBidiText::TDirectionality) and InnerRect(TBidiText::TDirectionality) 
		// DOES swap alignment for the inner object when scrip directionality is RightToLeft (only)
		// when absolute alignment is OFF
		const TRect outerRect(10,10,110,110);
		const TSize innerSize(20,20);
		TPoint innerTopLeft;
		TRect innerRect;
		
		align.SetHAlignment(EHLeft);
		innerTopLeft = align.InnerTopLeft(outerRect, innerSize, TBidiText::ERightToLeft);
		TEST( innerTopLeft == TPoint(90,10) );
		innerRect = align.InnerRect(outerRect, innerSize, TBidiText::ERightToLeft);
		TEST( innerRect == TRect(90,10,110,30) );
		
		align.SetHAlignment(EHCenter);
		innerTopLeft = align.InnerTopLeft(outerRect, innerSize, TBidiText::ERightToLeft);
		TEST( innerTopLeft == TPoint(50,10) );
		innerRect = align.InnerRect(outerRect, innerSize, TBidiText::ERightToLeft);
		TEST( innerRect  == TRect(50,10,70,30) );
		
		align.SetHAlignment(EHRight);
		innerTopLeft = align.InnerTopLeft(outerRect, innerSize, TBidiText::ERightToLeft);
		TEST( innerTopLeft == TPoint(10,10) );
		innerRect = align.InnerRect(outerRect, innerSize, TBidiText::ERightToLeft);
		TEST( innerRect == TRect(10,10,30,30) );
		
		
		align.SetVAlignment(EVCenter);
		
		
		align.SetHAlignment(EHLeft);
		innerTopLeft = align.InnerTopLeft(outerRect, innerSize, TBidiText::ERightToLeft);
		TEST( innerTopLeft == TPoint(90,50) );
		innerRect = align.InnerRect(outerRect, innerSize, TBidiText::ERightToLeft);
		TEST( innerRect == TRect(90,50,110,70) );
		
		align.SetHAlignment(EHCenter);
		innerTopLeft = align.InnerTopLeft(outerRect, innerSize, TBidiText::ERightToLeft);
		TEST( innerTopLeft == TPoint(50,50) );
		innerRect = align.InnerRect(outerRect, innerSize, TBidiText::ERightToLeft);
		TEST( innerRect  == TRect(50,50,70,70) );
		
		align.SetHAlignment(EHRight);
		innerTopLeft = align.InnerTopLeft(outerRect, innerSize, TBidiText::ERightToLeft);
		TEST( innerTopLeft == TPoint(10,50) );
		innerRect = align.InnerRect(outerRect, innerSize, TBidiText::ERightToLeft);
		TEST( innerRect == TRect(10,50,30,70) );
		
		
		align.SetVAlignment(EVBottom);
		
		
		align.SetHAlignment(EHLeft);
		innerTopLeft = align.InnerTopLeft(outerRect, innerSize, TBidiText::ERightToLeft);
		TEST( innerTopLeft == TPoint(90,90) );
		innerRect = align.InnerRect(outerRect, innerSize, TBidiText::ERightToLeft);
		TEST( innerRect == TRect(90,90,110,110) );
		
		align.SetHAlignment(EHCenter);
		innerTopLeft = align.InnerTopLeft(outerRect, innerSize, TBidiText::ERightToLeft);
		TEST( innerTopLeft == TPoint(50,90) );
		innerRect = align.InnerRect(outerRect, innerSize, TBidiText::ERightToLeft);
		TEST( innerRect  == TRect(50,90,70,110) );
		
		align.SetHAlignment(EHRight);
		innerTopLeft = align.InnerTopLeft(outerRect, innerSize, TBidiText::ERightToLeft);
		TEST( innerTopLeft == TPoint(10,90) );
		innerRect = align.InnerRect(outerRect, innerSize, TBidiText::ERightToLeft);
		TEST( innerRect == TRect(10,90,30,110) );
		}
		break;
	
	case 8:
		// Check the operation of ParaAlign() and SetHAlignment(CParaFormat)
		align.SetHAlignment(CParaFormat::ELeftAlign);
		TEST(align.ParaAlign() == CParaFormat::ELeftAlign);
		TEST(align.HAlignment() == EHLeft);
		TEST(!align.HasAbsoluteHAlignment());
				
		align.SetHAlignment(CParaFormat::ERightAlign);
		TEST(align.ParaAlign() == CParaFormat::ERightAlign);
		TEST(align.HAlignment() == EHRight);
		TEST(!align.HasAbsoluteHAlignment());
		
		align.SetHAlignment(CParaFormat::EAbsoluteLeftAlign);
		TEST(align.ParaAlign() == CParaFormat::EAbsoluteLeftAlign);
		TEST(align.HAlignment() == EHLeft);
		TEST(align.HasAbsoluteHAlignment());
		
		align.SetHAlignment(CParaFormat::EAbsoluteRightAlign);
		TEST(align.ParaAlign() == CParaFormat::EAbsoluteRightAlign);
		TEST(align.HAlignment() == EHRight);
		TEST(align.HasAbsoluteHAlignment());
			
		break;

	default:
		AutoTestManager().FinishAllTestCases(CAutoTestManager::EPass);
		break;
		}

	}

//
// Main
//

void CTAlignmentStep::ConstructAppL(CCoeEnv* aCoeEnv)
    { // runs inside a TRAP harness
	aCoeEnv->ConstructL();
	CTestAlignmentUi* appUi=new(ELeave) CTestAlignmentUi(this);
	appUi->ConstructL();
	aCoeEnv->SetAppUi(appUi);
    }


CTAlignmentStep::~CTAlignmentStep()
/**
   Destructor
 */
	{
	}

CTAlignmentStep::CTAlignmentStep()
/**
   Constructor
 */
	{
	// Call base class method to set up the human readable name for logging
	SetTestStepName(KTAlignmentStep);
	}


TVerdict CTAlignmentStep::doTestStepL()
	{
	INFO_PRINTF1(_L("Test Started"));

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

 	INFO_PRINTF1(_L("Test Finished"));

	__UHEAP_MARKEND;
	return TestStepResult();
	}
