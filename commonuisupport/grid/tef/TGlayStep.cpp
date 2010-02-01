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
// Tests the grid layout functionalities that controls appearance of columns, rows and their selections.\n
// One of the test case tests the functionalitie for Setting , Inserting , Deleting rows and coloums and \n
// the other tests whether the grid labels/lines are to be printed/Drawn.
// 
//

/**
 @file
 @internalComponent - Internal Symbian test code
*/
 
#include <s32mem.h>
#include "grdstd.h"
#include "TGlayStep.h"

/**
  Auxiliary Function for Test Case ID TGlayStep-Test1L & TGlayStep-Test2L.\n
  Call the ConstructL function of CGridLay.\n
  ConstructL is the second-phase constructor for constructing the object with definite row boundaries.\n
 */
void CTGlayStep::ConstructGridLayLC(CGridLay*& aGridLay)
	{
	aGridLay = new(ELeave) CGridLay(NULL);
	CleanupStack::PushL(aGridLay);
	aGridLay->ConstructL(NULL,NULL,100,100);
	}
/**
  @SYMTestCaseID UIF-TGlayStep-Test1L

  @SYMPREQ
 
  @SYMTestCaseDesc Tests the functionalitie for Setting , Inserting , Deleting rows and coloums and \n.
  The CGridLay APIs are being tested.\n
 
  @SYMTestPriority High 
 
  @SYMTestStatus Implemented
  
  @SYMTestActions Using the CGridLay APIs,
  1)Construct the Grid layout.\n
  2)Set the Coloum width.\n
  3)Insert a coloum.\n 
  4)Set row height.\n
  5)Delete the coloum.\n
  6)Retrieve the parameter set.\n
  7)Compare the retrieved value with the orginal parameters.\n
 
 
  @SYMTestExpectedResults The test passes when the set parameter values match with the retrieved parameter values.\n
   
 */
void CTGlayStep::Test1L()
	{
	__UHEAP_MARK;
	CGridLay* gridLay;
	ConstructGridLayLC(gridLay);

	gridLay->SetDefaultColumnWidthInTwips(123);
	gridLay->SetColumnWidthInTwipsL(5,55);
	gridLay->SetColumnWidthInTwipsL(12,18,77);
	gridLay->InsertDeleteColumns(12,2);
	gridLay->SetRowHeightInTwipsL(6,7,99);
	gridLay->InsertDeleteRows(2,-2);

	TEST(gridLay->ColumnWidthInTwips(5)==55);
	TEST(gridLay->ColumnWidthInTwips(12)==123);	// default
	TEST(gridLay->ColumnWidthInTwips(20)==77);
	TEST(gridLay->RowHeightInTwips(4)==99);
	gridLay->SetRowHeightsToDefault();
	TEST(gridLay->RowHeightInTwips(4)==gridLay->DefaultRowHeightInTwips());

	CleanupStack::PopAndDestroy();
	__UHEAP_MARKEND;
	}
/**
   @SYMTestCaseID UIF-TGlayStep-Test2L
  
   @SYMPREQ
  
   @SYMTestCaseDesc Tests whether the grid labels are to be printed/Drawn.\n
   The CGridLay APIs are being tested.\n
  
   @SYMTestPriority High 
  
   @SYMTestStatus Implemented
   
   @SYMTestActions Using the CGridLay APIs,
   1)Construct the Grid layout.\n
   2)Set that side labels are not to be printed.\n
   3)Set that side  vertical grid lines are not to be drawn.\n 
   4)Sets the default height of rows.\n
  
   Create a write stream interface and externalize the CGridLay object.\n
   Close the stream.\n
   Re-Initialize the CGridLay object.\n
   Tests whether side grid labels are printed (returning default settings).\n
   Tests whether vertical grid lines are to be drawn (returning default settings).\n
  
   Create a read stream interface and Internalize CGridLay object
   Test whether side grid labels are not to be printed (Setting matches with the externalised CGridLay object).\n
   Tests whether vertical grid lines are not to be drawn(Setting matches with the externalised CGridLay object).\n
   Test that the default height of rows being set matches with the settings of externalised CGridLay object.\n
  
   @SYMTestExpectedResults Test passes if there is no difference in the CGridLay object settings due to externalising and internalising.\n
    
 */
void CTGlayStep::Test2L()
	{
	__UHEAP_MARK;
	CBufFlat* bufFlat = CBufFlat::NewL(100);
	CleanupStack::PushL(bufFlat);

	CGridLay* gridLay;
	ConstructGridLayLC(gridLay);

	gridLay->SetSideLabels(EFalse);
	gridLay->SetVerticalGridLines(EFalse);
	gridLay->SetDefaultRowHeightInTwips(333);

	RBufWriteStream writeStream;
	writeStream.Open(*bufFlat,0);
	writeStream << *gridLay;
	writeStream.Close();

	CleanupStack::PopAndDestroy();	// gridLay
	ConstructGridLayLC(gridLay);
// 2 and 8 are the default settings for SideLabels and VerticalGridlInes
	TEST(gridLay->IsSideLabels()==2);
	TEST(gridLay->IsVerticalGridLines()==8);

	RBufReadStream readStream;
	readStream.Open(*bufFlat,0);
	readStream >> *gridLay;
	readStream.Close();

	TEST(!gridLay->IsSideLabels());
	TEST(!gridLay->IsVerticalGridLines());
	TEST(gridLay->DefaultRowHeightInTwips()==333);

	CleanupStack::PopAndDestroy(2);// gridLay + bufFlat
	}


//
CTGlayStep::~CTGlayStep()
/**
   Destructor
 */
	{
	}

CTGlayStep::CTGlayStep()
/**
   Constructor
 */
	{
	// Call base class method to set up the human readable name for logging
	SetTestStepName(KTGlayStep);
	}
/**
   
   Entry function for the test steps.\n
   Call the test steps.\n
  
   @return TVerdict indicating whether the test step has executed without error.\n
  
 */
TVerdict CTGlayStep::doTestStepL()

	{
	INFO_PRINTF1(_L("Test Started"));
	__UHEAP_MARK;

	INFO_PRINTF1(_L("Setting/Inserting/Deleting Rows and Columns"));

	SetTestStepID(_L("UIF-TGlayStep-Test1L"));
	TRAPD(err,CTGlayStep::Test1L());
	TEST(err==KErrNone);
	RecordTestResultL();
	INFO_PRINTF1(_L("Externalizing/Internalizing"));
	SetTestStepID(_L("UIF-TGlayStep-Test2L"));
	TRAP(err,CTGlayStep::Test2L());
	TEST(err==KErrNone);
	RecordTestResultL();
	CloseTMSGraphicsStep();

	INFO_PRINTF1(_L("test finished"));

	__UHEAP_MARKEND;
	return TestStepResult();
	}
