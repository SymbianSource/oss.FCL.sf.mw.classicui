// Copyright (c) 2007-2009 Nokia Corporation and/or its subsidiary(-ies).
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

#include <e32keys.h>
#include <basched.h>
#include <gdi.h>
#include <gulutil.h>
#include <gulbordr.h>
#include <gulcolor.h>
#include <coecntrl.h>
#include <coeutils.h>
#include <eikenv.h>
#include <eikappui.h>
#include <eikdef.h>
#include <eikdoc.h>
#include <eikapp.h>
#include "eiksrvc.h"

#include "TSysColor.h"
#include "TSysColor.hrh"

//
//  global  //
//

LOCAL_D void SetColors(const TRgb& aColor,CColorList*& aColorlist)
	{
	aColorlist->SetColor(EColorWindowText,aColor);
	aColorlist->SetColor(EColorDialogText,aColor);
	aColorlist->SetColor(EColorMenuPaneText,aColor);
	aColorlist->SetColor(EColorToolbarText,aColor);
	aColorlist->SetColor(EColorStatusPaneText,aColor);
	aColorlist->SetColor(EColorLabelText,aColor);
	}
	
//Some coloUrs (!)
const TRgb gBlack(0,0,0);
const TRgb gWhite(0xff,0xff,0xff);
const TRgb gRed(0xff, 0, 0);

//
// CTSysColorControl //
//

/**
   This method creates the user interface control on which tests are carried out.
 */
void CTSysColorControl::ConstructL(const TRect& aRect)
    {
	CreateWindowL();
	SetRect(aRect);
	SetBlank();
	ActivateL();
	}

//
// CTSysColorAppUi//
//

/**
   This method prepares the test step's user interface and prepares it to start the tests. 
   As part of user interface it creates a control on which the tests are carried out.
 */
void CTSysColorAppUi::ConstructL()
    {
	CTestAppUi::ConstructL();
    
	iTSysColorControl=new(ELeave) CTSysColorControl;
    iTSysColorControl->ConstructL(ClientRect());
    AddToStackL(iTSysColorControl);
 
	AutoTestManager().StartAutoTest();
   }

CTSysColorAppUi::CTSysColorAppUi(CTmsTestStep* aStep)
	: CTestAppUi(aStep, KNullDesC)
	{
	}

CTSysColorAppUi::~CTSysColorAppUi()
	{
	RemoveFromStack(iTSysColorControl);
    delete iTSysColorControl;
	}

/**
   The method is an override from CTestAppUi.   
 */
void CTSysColorAppUi::RunTestStepL(TInt aNextStep)
	{
	switch(aNextStep)
		{
		case 1:
			{
			SetTestStepID(_L("UIF-SysColorSet-ExecuteL"));
			INFO_PRINTF1(_L("testing test case \'Set\'..."));
			TRAPD(ret, TestCaseSetL());
			TEST(ret==KErrNone);
			INFO_PRINTF2(_L("done with return = '%d'\n"), ret);
			RecordTestResultL();
			break;
			}
		case 2:
			{
			SetTestStepID(_L("UIF-SysColorGet-ExecuteL"));
			INFO_PRINTF1(_L("testing test case \'Get\'..."));
			TRAPD(ret, TestCaseGetL());
			TEST(ret==KErrNone);
			INFO_PRINTF2(_L("done with return = '%d'\n"), ret);
			RecordTestResultL();
			break;
			}
		case 3:
			{
			SetTestStepID(_L("UIF--UIKON-0007"));
			INFO_PRINTF1(_L("testing creating system color..."));
			TRAPD(ret, TestCaseCreateL());
			TEST(ret==KErrNone);
			INFO_PRINTF2(_L("done with return = '%d'\n"), ret);
			RecordTestResultL();
			CloseTMSGraphicsStep();
			break;
			}
		case 4:
			{
			AutoTestManager().FinishAllTestCases(CAutoTestManager::EPass);
			return;
			}
		default:
			break;
		}
	}

//LOCAL_C void 

/**
   @SYMTestCaseID		UIF-SysColorSet-ExecuteL
  
   @SYMDEF 				DEF068462
  
   @SYMTestCaseDesc 	Testing functionality of SetSystemColorsL 
  
   @SYMTestPriority		Low
  
   @SYMTestStatus 		Implemented
   
   @SYMTestActions
   Get the system colour pallette and change some of the text items to red.
   Set the system pallette to the altered one. The test to verify that the
   colours have been changed is performed in the next step so the test here
   is just that Get & SetSystemColorsL don't panic.
   API Calls:\n		
   REikAppUiSession::Connect();
   REikAppUiSession::GetSystemColorsL();
   REikAppUiSession::SetSystemColorsL();
   ColorList::SetColor();
      
   @SYMTestExpectedResults
   Test should complete without any panic.
 */
void CTSysColorAppUi::TestCaseSetL()
	{
	REikAppUiSession uiSession;

	User::LeaveIfError(uiSession.Connect());
	CleanupClosePushL(uiSession);

	CColorList* colorlist;
	TRAPD(err,colorlist = uiSession.GetSystemColorsL());
	if(err!=KErrNone)
		{
		ERR_PRINTF1(_L("GetSystemColorsL failed"));
		User::Leave(err);
		}
	CleanupStack::PushL(colorlist);
	
	SetColors(gRed, colorlist);
	
	TRAP(err,uiSession.SetSystemColorsL(*colorlist));
	if(err!=KErrNone)
		{
		ERR_PRINTF1(_L("SetSystemColorsL failed"));
		User::Leave(err);
		}

	CleanupStack::PopAndDestroy(2);
	}
	
	
/**
   @SYMTestCaseID		UIF-SysColorGet-ExecuteL
  
   @SYMDEF 				DEF068462
  
   @SYMTestCaseDesc 	Testing functionality of GetSystemColorsL 
  
   @SYMTestPriority		Low
  
   @SYMTestStatus 		Implemented
   
   @SYMTestActions
   Get the system colour pallette and test whether a selection of items are set
   to expected colours, including those that were changed in the previous step.
   API Calls:\n		
   REikAppUiSession::Connect();
   REikAppUiSession::GetSystemColorsL();
   ColorList::Color();
      
   @SYMTestExpectedResults
   Test should complete without any panic.
 */
void CTSysColorAppUi::TestCaseGetL()
	{
	REikAppUiSession uiSession;

	User::LeaveIfError(uiSession.Connect());
	CleanupClosePushL(uiSession);

	CColorList* colorlist;
	TRAPD(err,colorlist = uiSession.GetSystemColorsL());
	if(err!=KErrNone)
		{
		ERR_PRINTF1(_L("GetSystemColorsL failed"));
		User::Leave(err);
		}
	CleanupStack::PushL(colorlist);

	TEST(colorlist->Color(EColorWindowText)==gRed);
	TEST(colorlist->Color(EColorControlBackground)==gWhite);
	TEST(colorlist->Color(EColorControlText)==gBlack);
	TEST(colorlist->Color(EColorControlSurroundText)==gBlack);
	TEST(colorlist->Color(EColorControlHighlightText)==gWhite);
	TEST(colorlist->Color(EColorDialogText)==gRed);
	TEST(colorlist->Color(EColorDialogTitleText)==gWhite);
	TEST(colorlist->Color(EColorMenubarText)==gBlack);
	TEST(colorlist->Color(EColorMenuPaneText)==gRed);
	TEST(colorlist->Color(EColorMenuPaneTextHighlight)==gWhite);
	TEST(colorlist->Color(EColorButtonText)==gBlack);
	TEST(colorlist->Color(EColorScrollBarNoShaftOrThumb)==gWhite);
	TEST(colorlist->Color(EColorScrollButtonIcon)==gBlack);
	TEST(colorlist->Color(EColorScrollThumbEdge)==gBlack);
	TEST(colorlist->Color(EColorToolbarText)==gRed);
	TEST(colorlist->Color(EColorStatusPaneText)==gRed);
	TEST(colorlist->Color(EColorLabelText)==gRed);
	TEST(colorlist->Color(EColorLabelTextEmphasis)==gWhite);

	//Set the text colours back to black, otherwise they stay red forever
	SetColors(gBlack, colorlist);
	TRAP(err,uiSession.SetSystemColorsL(*colorlist));
	if(err!=KErrNone)
		{
		ERR_PRINTF1(_L("SetSystemColorsL failed"));
		User::Leave(err);
		}

	CleanupStack::PopAndDestroy(2);
	}


/**
   @SYMTestCaseID		UIF--UIKON-0007
  
   @SYMDEF 				DEF100056
  
   @SYMTestCaseDesc 	Testing functionality of CreateSystemColorListL()
  
   @SYMTestPriority		Low
  
   @SYMTestStatus 		Implemented
   
   @SYMTestActions
   Create the system colour list and merge it with another colour list. First with and
   empty one (and check the merge does not panic, but is not done), and second with a valid
   colour list (and check that the merge is now done as expected)
   API Calls:\n		
   CColorList* CEikonEnv::CreateSystemColorListL();
   CColorList* CEikonEnv::CreateSystemColorListL(const CColorList &aColorList);
      
   @SYMTestExpectedResults	Test should complete without any panic.
 */
void CTSysColorAppUi::TestCaseCreateL()
	{
	INFO_PRINTF1(_L("Create a default System Color List"));
	CColorList* originalList = iEikonEnv->CreateSystemColorListL();
	TEST(originalList != NULL);
	CleanupStack::PushL(originalList);
	
	// Random application uid to use for colour list tests
	const TUid KRandomTestAppUid = {0x01233210};
	
	// Create a new system colour list passing as a parameter an empty color list (not a good practise...)
	//
	// In a pre-DEF100056 world, this would panic with KERN-EXEC 3....not anymore!
	INFO_PRINTF1(_L("Create a new system colour list passing as a parameter an empty color list"));
	CColorList* emptyColorList = CColorList::NewLC();
	CColorList* newColorList = iEikonEnv->CreateSystemColorListL(*emptyColorList);
	TEST(newColorList != NULL);
	//
	// No merge takes place, i.e.,  'newColorList' == 'originalList'
	TEST(newColorList->Count() == originalList->Count());
	for (TInt index = 0; index < originalList->Count(); index++)
		{
		TEST(newColorList->Color(TLogicalColor(index)) == originalList->Color(TLogicalColor(index)));
		}
	TEST(newColorList->ContainsColorArray(TUid::Uid(KEikCustomColorsArrayValue)));
	TEST(!newColorList->ContainsColorArray(KRandomTestAppUid));
	delete newColorList;
	newColorList = NULL;
	CleanupStack::PopAndDestroy(emptyColorList);
	
	// Create a new system colour list passing as a parameter a proper color list
	//
	// First create a proper list
	INFO_PRINTF1(_L("Creating a proper list..."));
	CArrayFix<TRgb>* rgbs=new(ELeave) CArrayFixFlat<TRgb>(3);
	CleanupStack::PushL(rgbs);
	rgbs->AppendL(KRgbWhite);
	rgbs->AppendL(KRgbGray);
	rgbs->AppendL(KRgbCyan);
	CColorList* list=CColorList::NewL(rgbs);
	CleanupStack::Pop(rgbs);
	CleanupStack::PushL(list);
	//
	// Check the list values are as expected
	TEST(list->Count()==3);
	TEST(list->Color(TLogicalColor(0))==KRgbWhite);		
	TEST(list->Color(TLogicalColor(1))==KRgbGray);
	TEST(list->Color(TLogicalColor(2))==KRgbCyan);
	//
	// Set the list values to something else. With this we want to check that CreateSystemColorListL
	//	only merges the applications color lists (i.e, those added with CColorList::AddColorArrayL())
	list->SetColor(TLogicalColor(0),KRgbBlack);	
	list->SetColor(TLogicalColor(1),KRgbBlack);
	list->SetColor(TLogicalColor(2),KRgbBlack);
	CColorArray* array=CColorArray::NewLC();
	array->AddL(200,KRgbDarkMagenta);
	array->AddL(201,KRgbDarkCyan);
	array->AddL(202,KRgbDarkMagenta);
	list->AddColorArrayL(KRandomTestAppUid,array);
	CleanupStack::Pop(array); 
	//
	// Now create the new system color list. 
	INFO_PRINTF1(_L("Use the proper list to create a new system colour list"));
	newColorList = iEikonEnv->CreateSystemColorListL(*list);
	TEST(newColorList != NULL);
	//
	// Both colorlists have been successfully merged in terms of the application arrays...
	// 	(1) iEikColors are not merged
	//	(2) iAppColors are merged ('newColorList' now must contain the color array from the application)
	TEST(newColorList->Count() == originalList->Count());
	for (TInt index = 0; index < originalList->Count(); index++)
		{
		// iEikColors are not merged (they remain as the 'originalList', although 'list' set them to KRgbBlack)
		TEST(newColorList->Color(TLogicalColor(index)) == originalList->Color(TLogicalColor(index)));
		}
	TEST(newColorList->ContainsColorArray(TUid::Uid(KEikCustomColorsArrayValue)));
	TEST(newColorList->ContainsColorArray(KRandomTestAppUid));
	TEST(newColorList->Color(KRandomTestAppUid, TLogicalColor(200)) == KRgbDarkMagenta);
	TEST(newColorList->Color(KRandomTestAppUid, TLogicalColor(201)) == KRgbDarkCyan);
	TEST(newColorList->Color(KRandomTestAppUid, TLogicalColor(202)) == KRgbDarkMagenta);

	// Clean-up everything
	delete newColorList;
	CleanupStack::PopAndDestroy(2, originalList);
	}



//
// CTSysColorStep//
//

CTSysColorStep::CTSysColorStep()
	{
	SetTestStepName(KTSysColorStep);
	}
	
CTSysColorStep::~CTSysColorStep()
	{
	}

TVerdict CTSysColorStep::doTestStepPreambleL()
	{
	SetTestStepResult(EPass);
	return TestStepResult();
	}
	
/**
   The method creates & sets the application's user interface object.
 */
void CTSysColorStep::ConstructAppL(CEikonEnv* aEikEnv)
    {
	aEikEnv->ConstructL();
 	CTSysColorAppUi* appUi=new(ELeave) CTSysColorAppUi(this);

	CleanupStack::PushL(appUi);
 	aEikEnv->SetAppUi(appUi);
	appUi->ConstructL();
	CleanupStack::Pop(appUi);
    }

/**
   The method creates & sets the test step's user interface object and launches the test step.
 */
TVerdict CTSysColorStep::doTestStepL()
	{
	INFO_PRINTF1(_L("Test SysColor started....\n"));

	PreallocateHALBuffer();
	
	__UHEAP_MARK;

 	CEikonEnv* eikEnv=new CEikonEnv;
 	TEST(eikEnv!=NULL);
 	if (eikEnv==NULL)
		{
		INFO_PRINTF1(_L("Failed to create Eikon Environment due to lack of Memory"));
 		return TestStepResult();
		}
		
 	TRAPD(err,ConstructAppL(eikEnv));
 	TEST(err==KErrNone);
 	if (err!=KErrNone)
		{
		INFO_PRINTF2(_L("Failed to construct Eikon Environment, error %d"), err);
		delete eikEnv;
		}
 	else
 		{
		// Run tests
 		eikEnv->ExecuteD();
	 	}

	REComSession::FinalClose();	

	__UHEAP_MARKEND;

	INFO_PRINTF1(_L("....test completed!"));
	return TestStepResult();
	}





