// Copyright (c) 2007-2010 Nokia Corporation and/or its subsidiary(-ies).
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
// The test step Tests the IsDisplayingDialog(),RemoveFromStack() APIs and 
// Change to CCoeControl::DoMakeVisible to call Makevisible on its child controls.\n
// 
//

/**
 @file
 @test
 @internalComponent - Internal Symbian test code
*/

#include <coeaui.h>
#include <coemain.h>
#include <coecntrl.h>
#include <coeccntx.h>
#include <coeutils.h>
#include <bassnd.h>
#include <coesndpy.h> 
#include <gulcolor.h>
#include <bautils.h>
#include <tcone2.rsg>
#include <ecom/ecom.h>

#include "TCone2Step.h"

//! Resource file path for Cone2 Test application.\n
_LIT(KTCone2ResourceFilePath, "z:\\system\\data\\tcone2.rsc");

//! This defines resource ID which signatures matches TCone2.rss, but ID does not exist in file.
#define R_TCONE2_TEST_RESOURCE_CORRECT_SIGNATURE_MISSING_ID     R_TCONE2_TEST_LAST_RESOURCE_BUFFER + 1
//! This defines resource ID that signature does not match with TCone2.rss signature
#define R_TCONE2_TEST_RESOURCE_INCORRECT_SIGNATURE_FOR_THIS_RC     R_TCONE2_TEST_LAST_RESOURCE_BUFFER + 0x12340000

/**
  Second phase constructor for component control "CTestCone2".\n
  Creates a control's window.\n
  The created window is the child of the application's window group.\n
  iDisplayed is set to ETrue to make the control visible.\n
*/
void CTestCone2Control::ConstructL()
	{
	CreateWindowL();
	iDisplayed = ETrue;
	}
/**
  Function to give access to the CCoeControl's protected CreateWindowL function.
  This is intended for use only with Low Memory tests.
*/
TInt CTestCone2Control::CreateWindow()
	{
	TRAPD(err,CreateWindowL());
	return err;
	}
/**
  Sets this control as visible or invisible.\n
  This causes the control to disappear or reappear.\n
  When a control is created, it is made visible by default.\n
*/
void CTestCone2Control::MakeVisible(TBool aVisible)
	{
	iDisplayed = aVisible;
	DrawNow();
	}
/**
  Destructor for the container control.\n
  Deletes the component control "CTestCone2Control".\n
*/
CTestContainerControl::~CTestContainerControl()
	{
	delete iDialogCtrl;
	}
/**
  Second phase construcor for the Container control namely CTestContainerControl.\n
  The method creates a component control "CTestCone2Control".\n
  Sets components to inherit visibility setting from their container control.\n
  If set, when MakeVisible() is called on the compound control, 
  the value for visibility is propagated to all its components.

*/
void CTestContainerControl::ConstructL()
	{
    CreateWindowL();
	iDialogCtrl  = new(ELeave)CTestCone2Control;
    iDialogCtrl->ConstructL();
	iDialogCtrl->SetMopParent(this);
	CTestCone2Control* objProv;
	MopGetObject(objProv);

	TBuf<KMaxFileName> name;
	ControlEnv()->ReadResourceL(name, R_TCONE2_TEST_BUFFER2);
	(name.Compare(_L("TCone2")));
	SetComponentsToInheritVisibility();
	DrawNow();
	}
/**
  CTestCone2Control is a component control for CTestContainerControl.\n
  The method returns the number of component controls for CTestContainer Control.\n
*/
TInt CTestContainerControl::CountComponentControls() const
	{
	return 1;
	}
/**
  CTestCone2Control is a component control for CTestContainerControl.\n
  The method returns the handle for the component control.\n
*/
CCoeControl* CTestContainerControl::ComponentControl(TInt /*aIndex*/) const
	{
	return(iDialogCtrl);
	}
/**
  CTestCone2Control is a component control for CTestContainerControl.\n
  The method returns the handle for the component control.\n
*/
CTestCone2Control* CTestContainerControl::GetComponentControl()
	{
	return(iDialogCtrl);
	}
/**
  CTestCone2Control is a component control for CTestContainerControl.\n
  The method checks if the  TestCone2 control is displayed.\n
*/
TBool CTestContainerControl::IsDialogControlVisible() const
	{
	return iDialogCtrl->iDisplayed;
	}

/**
  Single Argument constructor for CTestDriver class.\n
  Initializes the iAppUi and iStep member variables with the arguments.\n
*/
CTestDriver::CTestDriver(CCoeAppUi& aAppUi,CTestStep* aStep) : iAppUi(aAppUi), iStep(aStep)
	{
	}
/**
  Second phase constructor for CTestDriver class.\n
  Checks if the resource file "z:\\system\\data\\tcone2.rsc"exists.\n
  AAdds the specified resource file to the list maintained by CCoeEnv.\n
*/
void CTestDriver::ConstructL()
	{
	ConeUtils::FileExists(KTCone2ResourceFilePath);	

	TFileName* filename = new (ELeave) TFileName(KTCone2ResourceFilePath);
	CleanupStack::PushL(filename);
	CCoeEnv* coeEnv = CCoeEnv::Static();
	BaflUtils::NearestLanguageFile(coeEnv->FsSession(),*filename);
	iResourceFileFlag=coeEnv->AddResourceFileL(*filename);
	CleanupStack::PopAndDestroy(filename); 
	}

CTestDriver::~CTestDriver()
	{
	CCoeEnv::Static()->DeleteResourceFile(iResourceFileFlag); 
	}


/**
   @SYMTestCaseID UIF-TCone2Step-TestMakeVisibleOnChildControlsL
  
   @SYMPREQ
  
   @SYMTestCaseDesc Test CTestContainerControl::MakeVisible() and CTestContainerControl::SetFocusing() methods.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The method creates a CTestContainerControl and adds it to the CCoeAppUi. 
   Calls CTestContainerControl::MakeVisible(EFalse) to hide the control. 
   Calls CTestContainerControl::MakeVisible(ETrue) to show the control.
   Calls CTestContainerControl::SetFocusing(ETrue) to highlight the control.
   
   @SYMTestExpectedResults. The code tests if the control is displayed while its visiable and hidden when 
   its set as invisible.
   
 */

void CTestDriver::TestMakeVisibleOnChildControlsL()
	{
	CTestContainerControl* testControl = new(ELeave)CTestContainerControl;
	CleanupStack::PushL(testControl);
	testControl->ConstructL();
	//Add control to the appUi control stack
	iAppUi.AddToStackL(testControl, ECoeStackPriorityDialog);
	testControl->MakeVisible(EFalse);
	iStep->TEST(testControl->IsDialogControlVisible() == 0);
	testControl->MakeVisible(ETrue);
	testControl->SetFocusing(ETrue);
	iStep->TEST(testControl->IsDialogControlVisible() == 1);
	iAppUi.RemoveFromStack(testControl); 
	CleanupStack::PopAndDestroy(testControl); 
	}

/**
   @SYMTestCaseID UIF-TCone2Step-TestIsDisplayingDialogAndRemoveFromStackAPIsL
  
   @SYMPREQ
  
   @SYMTestCaseDesc Test CCoeAppUi::IsDisplayingDialog() and CCoeAppUi::RemoveFromStack() methods.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The method creates a CTestContainerControl and adds it to the CCoeAppUi 
   control stack. Then it creates a child CCoeAppUi and sets it as the applications user interface, it passes the
   current CCoeAppUi so tht the its control stack is copied. It then removes the control from the child child 
   CCoeAppUi's control stack.
   
   @SYMTestExpectedResults. The code tests if the control is displayed while it is on the parent CCoeAppUi stack,
   and that it is not displayed once it is removed from the child CCoeAppUi's control stack.
   
 */
void CTestDriver::TestIsDisplayingDialogAndRemoveFromStackAPIsL()
	{
	CTestContainerControl* testControl = new(ELeave)CTestContainerControl;
	CleanupStack::PushL(testControl);
	testControl->ConstructL();

	//Add control to the appUi control stack
	iAppUi.AddToStackL(testControl, ECoeStackPriorityDialog);

	CCoeAppUi* childAppUi=new(ELeave) CCoeAppUi();
	CCoeEnv::Static()->SetAppUi(childAppUi);
    childAppUi->ConstructL(&iAppUi);

	iStep->TEST(iAppUi.IsDisplayingDialog() == 1);

 	//Remove the control from the appUi control stack
	childAppUi->RemoveFromStack(testControl); 
	iStep->TEST(iAppUi.IsDisplayingDialog() == 0);
	iStep->TEST(iAppUi.IsDisplayingMenuOrDialog() == 0);

	CCoeEnv::Static()->SetAppUi(&iAppUi);
	delete childAppUi;
	CleanupStack::PopAndDestroy(testControl);
	}

/**
   @SYMTestCaseID UIF-TCone2Step-TestAppHelpContextAPIL
  
   @SYMPREQ
  
   @SYMTestCaseDesc Test the CCoeAppUi::AppHelpContextL() method.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The method creates a list of relevant contexts within an application help file 
   appropriate for the current state of the application.  
   
   @SYMTestExpectedResults. The code tests that the list created is empty.
 * 
 */

void CTestDriver::TestAppHelpContextAPIL()
	{
	CArrayFix<TCoeHelpContext>* contexts= iAppUi.AppHelpContextL();
	CleanupStack::PushL(contexts);
	iStep->TEST(contexts->Count() == KErrNone);
	CleanupStack::PopAndDestroy(contexts);
	}

/**
   @SYMTestCaseID UIF-TCone2Step-TestSetAndGetSystemDefaultViewAPIsL
  
   @SYMPREQ
  
   @SYMTestCaseDesc Test's CCoeAppUi::CreateActivateViewEventL, CCoeAppUi::SetSystemDefaultViewL and
   SetSystemDefaultViewL::GetDefaultViewId() methods.
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions Creates a TVwsViewId and assigns it iAppUid iViewUid properties default values, 
   it then calls CCoeAppUi::CreateActivateViewEventL to create a default view with the id. 
   It then assigns the tests CCoeAppUi object's default view. Then it uses SetSystemDefaultViewL::GetDefaultViewId()
   to retriveve the defalt view.
   defalt view to be the   
   
   @SYMTestExpectedResults. The code tests that default view is the one previously set.
   
 */

void CTestDriver::TestSetAndGetSystemDefaultViewAPIsL()
	{
	TVwsViewId viewId;
	viewId.iAppUid = KNullUid;
	viewId.iViewUid = KNullUid;
	iAppUi.CreateActivateViewEventL(viewId, KNullUid, _L8(""));
	iAppUi.SetSystemDefaultViewL(viewId, 0);
	iAppUi.SetSystemDefaultViewL(viewId);
	TVwsViewId defaultViewId;
	iAppUi.GetDefaultViewId(defaultViewId);
	iStep->TEST(viewId == defaultViewId);
	}

/**
   @SYMTestCaseID UIF-TCone2Step-TestCoeControlAPIsL
  
   @SYMPREQ
  
   @SYMTestCaseDesc Test's Tests CTestContainerControl::Index, CTestContainerControl::GetComponentControl(),
   CCoeControl::PrepareForFocusGainL,CCoeControl::PrepareForFocusLossL methods.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions Tests that the control has itself as a component at index 0.
   
   @SYMTestExpectedResults. The code tests that the result of the above operation is KErrNone .
   
 */

void CTestDriver::TestCoeControlAPIsL()
	{
	CTestContainerControl* testControl = new(ELeave)CTestContainerControl;
	CleanupStack::PushL(testControl);
	testControl->ConstructL();
	iStep->TEST(testControl->Index(testControl->GetComponentControl()) == KErrNone);
	CleanupStack::PopAndDestroy(testControl);

	RWsSession ws;
	User::LeaveIfError(ws.Connect());
	RWindowGroup group(ws);
	User::LeaveIfError(group.Construct(888));
	RWindow win1(ws);
	User::LeaveIfError(win1.Construct(group,111));
	RBackedUpWindow backedUp(ws);
	User::LeaveIfError(backedUp.Construct(group,EGray4,222));

	CCoeControl* ctrl = new (ELeave) CCoeControl();
	CleanupStack::PushL(ctrl);
	ctrl->SetContainerWindowL(win1);
	ctrl->SetContainerWindowL(backedUp);
	ctrl->PrepareForFocusGainL();
	ctrl->PrepareForFocusLossL();
	iAppUi.HandleSwitchOnEventL(ctrl);
	TCoeInputCapabilities capabilities = ctrl->InputCapabilities();
	capabilities = ctrl->RecursivelyMergedInputCapabilities();
	TCoeHelpContext helpContext;
	ctrl->GetHelpContext(helpContext);
	helpContext.IsNull();
	ctrl->ControlContext();
	
	CleanupStack::PopAndDestroy(ctrl); 
	win1.Close();
	backedUp.Close();
	group.Close();
	ws.Close();
	}

/**
   @SYMTestCaseID UIF-TCone2Step-TestColorUseAPIsL
  
   @SYMPREQ
  
   @SYMTestCaseDesc Test's CCoeBrushAndPenContext::SetPenColor(), CCoeBrushAndPenContext::SetBrushStyle(), CCoeBrushAndPenContext::SetBrushColor()
   CCoeBrushAndPenContext::SetBrushBitmap(), CCoeBrushAndPenContext::PenColor(), CCoeBrushAndPenContext::BrushStyle()
   and CCoeBrushAndPenContext::BrushColor() methods.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions Code uses TCoeColorUse and  CCoeBrushAndPenContext getters and setter.
   
   @SYMTestExpectedResults. The code tests that TCoeColorUse and CCoeBrushAndPenContext objects have the correct properties.  
   
 */

void CTestDriver::TestColorUseAPIsL()
	{
	TInt commonAttributes = TCoeColorUse::EContents|TCoeColorUse::ENeutral;
	TInt use = TCoeColorUse::EFore|TCoeColorUse::EActive|TCoeColorUse::ENormal|commonAttributes;
	TCoeColorUse colorUse;
	colorUse.SetLogicalColor(EColorButtonText);
	colorUse.SetUse(use);

	iStep->TEST(colorUse.LogicalColor() == EColorButtonText);
	iStep->TEST(colorUse.Use() == use);
	iStep->TEST(colorUse.IsForeground() == TCoeColorUse::EFore);
	iStep->TEST(colorUse.IsBackground() == EFalse);
	iStep->TEST(colorUse.IsContents() == TCoeColorUse::EContents);
	iStep->TEST(colorUse.IsHighlights() == EFalse);
	iStep->TEST(colorUse.IsSurrounds() == EFalse);
	iStep->TEST(colorUse.IsBorders() == EFalse);
	iStep->TEST(colorUse.IsActive() == TCoeColorUse::EActive);
	iStep->TEST(colorUse.IsPressed() == EFalse);
	iStep->TEST(colorUse.IsDimmed() == EFalse);
	iStep->TEST(colorUse.IsNormal()== TCoeColorUse::ENormal);
	iStep->TEST(colorUse.IsSet() == EFalse);

	CCoeBrushAndPenContext* brushAndPen = CCoeBrushAndPenContext::NewL();
 	CFbsBitmap* bmp1=NULL;
	brushAndPen->SetPenColor(KRgbBlue);
	brushAndPen->SetBrushStyle(CWindowGc::ENullBrush);
	brushAndPen->SetBrushColor(KRgbWhite);
	brushAndPen->SetBrushBitmap(*bmp1);
	iStep->TEST(brushAndPen->PenColor() == KRgbBlue);
	iStep->TEST(brushAndPen->BrushStyle() == CWindowGc::ENullBrush);
	iStep->TEST(brushAndPen->BrushColor() == KRgbWhite);
	brushAndPen->BrushBitmap();
	delete brushAndPen;
	}

/**
   @SYMTestCaseID UIF-TCone2Step-TestConeAppUiSimpleAndMiscAPIsL
  
   @SYMPREQ
  
   @SYMTestCaseDesc Test's CCoeEnv::Static()->Version(), CCoeEnv::Static()->DisableExitChecks(EFalse),
   and CCoeEnv::Static()->FepUid() API's.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions Code uses CCoeEnv::Static
   
   @SYMTestExpectedResults. The code tests that the static CCoeEnv methods do not panic.  
 */

void CTestDriver::TestConeMiscAPIsL()
	{
	ConeUtils::EnsurePathExistsL(_L("c:\\system\\conetest\\conte2step\\"));	// no capabilities required for this folder

	// The following functions are called just to check they don't panic. 
	CCoeEnv::Static()->Version();
	CCoeEnv::Static()->DisableExitChecks(EFalse);
	CCoeEnv::Static()->FepUid();
	}

/**
   @SYMTestCaseID UIF-TCone2Step-TestConeInputCapabilitiesAPIs
  
   @SYMPREQ
  
   @SYMTestCaseDesc Test's TCoeInputCapabilities API's.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions Code uses getters and setters, merge functionality, assignment operator and copy constructors to test the
   TCoeInputCapabilities object.
   
   @SYMTestExpectedResults. The code tests that the object has the correct properties after using  getter's and setters, merge
   functionality, assignment operators and copy constructors. It also tests for correct default initialisation.
 
 */

void CTestDriver::TestConeInputCapabilitiesAPIs()
	{
	TCoeInputCapabilities inputCapabilities1(TCoeInputCapabilities::EWesternAlphabetic);
	TCoeInputCapabilities inputCapabilities2(inputCapabilities1.Capabilities());
	iStep->TEST(inputCapabilities1 == inputCapabilities2);
	inputCapabilities1 = iAppUi.InputCapabilities();
	inputCapabilities1 = TCoeInputCapabilities::ESecretText;
	iStep->TEST(inputCapabilities1 != inputCapabilities2);
	inputCapabilities1.MergeWith(inputCapabilities2);
	inputCapabilities1.SetCapabilities(TCoeInputCapabilities::EAllText);
	iStep->TEST(inputCapabilities1.IsNone() == KErrNone);
	iStep->TEST(inputCapabilities1.SupportsAllText() == TCoeInputCapabilities::EAllText);
	iStep->TEST(inputCapabilities1.SupportsWesternNumericIntegerPositive() == 0);
	iStep->TEST(inputCapabilities1.SupportsWesternNumericIntegerNegative() == 0);
	iStep->TEST(inputCapabilities1.SupportsWesternNumericReal() == 0);
	iStep->TEST(inputCapabilities1.SupportsWesternAlphabetic() == 0);
	iStep->TEST(inputCapabilities1.SupportsJapaneseHiragana() == 0);
	iStep->TEST(inputCapabilities1.SupportsJapaneseKatakanaHalfWidth() == 0);
	iStep->TEST(inputCapabilities1.SupportsJapaneseKatakanaFullWidth() == 0);
	iStep->TEST(inputCapabilities1.SupportsDialableCharacters() == 0);
	iStep->TEST(inputCapabilities1.SupportsSecretText() == 0);
	iStep->TEST(inputCapabilities1.SupportsAutoSentenceCase() == 0);
	iStep->TEST(inputCapabilities1.SupportsNonPredictive() == 0);	
	iStep->TEST(inputCapabilities1.SupportsNavigation() == 0);
	inputCapabilities1.SetCapabilities(TCoeInputCapabilities::EAutoSentenceCase);
	iStep->TEST(inputCapabilities1.SupportsAutoSentenceCase() == TCoeInputCapabilities::EAutoSentenceCase);
	MCoeCaptionRetrieverForFep*  captionRetrieverForFep=inputCapabilities1.CaptionRetrieverForFep();
	iStep->TEST(captionRetrieverForFep == NULL);
	TCoeInputCapabilities::MCoeFepSpecificExtensions* fepSpecificInputCapabilityExtensions=inputCapabilities1.FepSpecificExtensions(KNullUid);
	iStep->TEST(fepSpecificInputCapabilityExtensions ==NULL);
	MCoeFepAwareTextEditor* fepAwareTextEditor=inputCapabilities1.FepAwareTextEditor();
	TCoeInputCapabilities inputCapabilities3(TCoeInputCapabilities::EWesternAlphabetic, fepAwareTextEditor, captionRetrieverForFep );
	TCoeInputCapabilities inputCapabilities4(TCoeInputCapabilities::EWesternAlphabetic, fepAwareTextEditor, captionRetrieverForFep, KNullUid , fepSpecificInputCapabilityExtensions);
	iStep->TEST(inputCapabilities3 == inputCapabilities4);

	// MObjectProvider api
	// null initialisation
	iStep->TEST(inputCapabilities1.ObjectProvider() == NULL);
	iStep->TEST(inputCapabilities2.ObjectProvider() == NULL);
	iStep->TEST(inputCapabilities3.ObjectProvider() == NULL);
	iStep->TEST(inputCapabilities4.ObjectProvider() == NULL);
	// get and set
	MObjectProvider* mop = (MObjectProvider*)0x12345678;
	inputCapabilities1.SetObjectProvider(mop);
	iStep->TEST(inputCapabilities1.ObjectProvider() == mop);
	// merge
	inputCapabilities1.MergeWith(inputCapabilities2);
	iStep->TEST(inputCapabilities1.ObjectProvider() == mop);
	iStep->TEST(inputCapabilities2.ObjectProvider() == NULL);
	inputCapabilities3.MergeWith(inputCapabilities1);
	iStep->TEST(inputCapabilities1.ObjectProvider() == mop);
	iStep->TEST(inputCapabilities3.ObjectProvider() == mop);
	MObjectProvider* mop2 = (MObjectProvider*)0x87654320;
	inputCapabilities4.SetObjectProvider(mop2);
	inputCapabilities3.MergeWith(inputCapabilities4);
	iStep->TEST(inputCapabilities3.ObjectProvider() == mop);
	inputCapabilities2.MergeWith(inputCapabilities4);
	iStep->TEST(inputCapabilities2.ObjectProvider() == mop2);
	// assignment operator
	inputCapabilities2 = inputCapabilities1;
	iStep->TEST(inputCapabilities1.ObjectProvider() == inputCapabilities2.ObjectProvider());
	// copy construction
	TCoeInputCapabilities inputCapabilities5(inputCapabilities1);
	iStep->TEST(inputCapabilities5.ObjectProvider() == mop);
	// comparison operators
	inputCapabilities1.SetObjectProvider(NULL);
	iStep->TEST(inputCapabilities1 != inputCapabilities2);
	inputCapabilities1.SetObjectProvider(mop);
	iStep->TEST(inputCapabilities1 == inputCapabilities2);
	}

/**
   @SYMTestCaseID UIF-TCone2Step-TestReadResourceAPIsL
  
   @SYMPREQ
  
   @SYMTestCaseDesc Test's the CCoeEnv::ReadResourceL(),AllocReadResourceL,AllocReadResourceLC,ReadDesCArrayResourceL,
   AllocReadResourceAsDes8LC, ReadResourceAsDes8L, AllocReadResourceAsDes16LC, and Format256 methods.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The method creates a list of relevant contexts within an application help file 
   appropriate for the current state of the application.  
   
   @SYMTestExpectedResults. The code tests that the list created is empty.
   
 */

void CTestDriver::TestReadResourceAPIsL()
	{
	__UHEAP_MARK;

	CCoeEnv* coeEnv = CCoeEnv::Static();

	TBuf<KMaxFileName> testBuffer;
	coeEnv->ReadResourceL(testBuffer, R_TCONE2_TEST_BUFFER1);

	HBufC* resourceBuf1=coeEnv->AllocReadResourceL(R_TCONE2_TEST_BUFFER1);
	delete resourceBuf1;
	resourceBuf1 = NULL;

	resourceBuf1=coeEnv->AllocReadResourceLC(R_TCONE2_TEST_BUFFER1);
	CleanupStack::PopAndDestroy(resourceBuf1);

	INFO_PRINTF1(_L("coeEnv->IsResourceAvailable"));
	TBool isResourceAvailable = coeEnv->IsResourceAvailableL( R_TCONE2_TEST_RESOURCE_CORRECT_SIGNATURE_MISSING_ID );
	iStep->TEST( !isResourceAvailable );
	isResourceAvailable = coeEnv->IsResourceAvailableL( R_TCONE2_TEST_RESOURCE_INCORRECT_SIGNATURE_FOR_THIS_RC );
	iStep->TEST( !isResourceAvailable );
	isResourceAvailable = coeEnv->IsResourceAvailableL( R_TCONE2_TEST_BUFFER1 );
	iStep->TEST( isResourceAvailable );

	INFO_PRINTF1(_L("coeEnv->ReadDesCArrayResourceL"));
	CDesCArray* array=coeEnv->ReadDesCArrayResourceL(R_TCONE2_STRING_ARRAY);
	CleanupStack::PushL(array);
	iStep->TEST(array->MdcaCount() == 3);
	CleanupStack::PopAndDestroy(array);  

	INFO_PRINTF1(_L("coeEnv->AllocReadResourceAsDes8LC"));
	HBufC8*  buf8 = coeEnv->AllocReadResourceAsDes8LC(R_TCONE2_TEST_BUFFER1);
	HBufC8* tempbuf8 = HBufC8::NewLC(buf8->Size());
	TPtr8 tempbuf8ptr = tempbuf8->Des(); 
	coeEnv->ReadResourceAsDes8L(tempbuf8ptr, R_TCONE2_TEST_BUFFER1);
	iStep->TEST(buf8->Des().Compare(*tempbuf8) == KErrNone);
	CleanupStack::PopAndDestroy(2, buf8);
	
	INFO_PRINTF1(_L("coeEnv->AllocReadResourceAsDes16LC"));
	HBufC16*  buf16 = coeEnv->AllocReadResourceAsDes16LC(R_TCONE2_TEST_BUFFER1);
	iStep->TEST(*buf16 == _L16("Cone"));
	TPtr16 tempbuf16 = buf16->Des();

	INFO_PRINTF1(_L("coeEnv->ReadResourceAsDes16L"));
	coeEnv->ReadResourceAsDes16L(tempbuf16, R_TCONE2_TEST_BUFFER1);
	iStep->TEST(tempbuf16 == _L16("Cone"));

	CleanupStack::PopAndDestroy(buf16);

	TBuf<KMaxFileName> formatBuf;	
	INFO_PRINTF1(_L("coeEnv->Format256"));
	coeEnv->Format256(formatBuf,R_TCONE2_TEST_FORMAT_BUFFER,KTCone2ResourceFilePath().Length());

	REComSession::FinalClose();	
	__UHEAP_MARKEND;
	}


/**
   @SYMTestCaseID UIF-TCone2Step-TestSetandGetCCoeControlAPIsL
  
   @SYMPREQ
  
   @SYMTestCaseDesc Test's the CCoeControl::MaximumWidth() and CCoeControl::SetMaximumWidth methods. Also tests the
   defalut initialisation of CCoeControl's Maximum Width property.
  	
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The test creates a CCoeControl object and checks that it maximum width property is 0. 
   It then sets this value and retrives it using getteers and setters.
   
   @SYMTestExpectedResults. The code tests the MaximumWidth property is initially 0, and that it can be set 
   and retrieved correctly.
   
 */
void CTestDriver::TestSetandGetCCoeControlAPIsL()
	{
	// Create a new CCoeControl object
	CCoeControl* testCtrl = new (ELeave) CCoeControl();
	CleanupStack::PushL(testCtrl);

	// Part 1: Check that a default value of 0 is returned when no
	// max width value has been set yet.
	iStep->TEST(testCtrl->MaximumWidth() == 0);

	// Part 2: Set the maximum width to a new value.
	TInt newMaxWidth = 5;
	iStep->TEST(testCtrl->SetMaximumWidth(newMaxWidth) == KErrNone);

	// Part 3: Access maximum width. Test that it equals the
	// value previously set.
	iStep->TEST(testCtrl->MaximumWidth() == newMaxWidth);

	CleanupStack::PopAndDestroy(testCtrl);
	}

/**
   @SYMTestCaseID UIF-TCone2Step-TestSetandGetCCoeControlAPIsL

   @SYMDEF ou1cimx1#261261

   @SYMTestCaseDesc Tests creating a CCoeControl in low memory conditions.
   In particular it tries to trip up the RCoeDynamicDataStorage mechanism.

   @SYMTestPriority High

   @SYMTestStatus Implemented

   @SYMTestActions The test creates a CCoeControl object in an OOM loop with different burst values.
   And sets and reads back a property that is stored in the DynamicDataStoreage.
   Note: This test didn't actually suceed in producing the crash reported in the defect.
   I couldn't see anyway to get to the crashing line with things in a bad state.

   @SYMTestExpectedResults. The code doesn't crash.
 */
void CTestDriver::TestLowMemoryCoeControl()
	{
	CCoeControl* const parentVal=NULL;
	CTestCone2Control* cnt;
	CCoeControl* parent;
	TInt burst;
	TInt failRate;
	TInt sucesses;
	TBool sucess=EFalse;
	TInt setErr;
	TInt creErr;
	for (burst=1;burst<15;++burst)
		{
		failRate=burst>1 ? 1:0;
		sucesses=0;
		do	{
			cnt=NULL;
			parent=reinterpret_cast<CCoeControl*>(KMaxTUint);
			setErr=99;
			creErr=99;
			__UHEAP_BURSTFAILNEXT(failRate,burst);
			__UHEAP_MARK;
			cnt=new CTestCone2Control();
			if (cnt)
				{
				setErr=cnt->SetParent(parentVal);
				parent=cnt->Parent();
				creErr=cnt->CreateWindow();
				if (parent==parentVal && setErr==KErrNone && creErr==KErrNone)
					sucess=ETrue;
				delete cnt;
				}
			__UHEAP_MARKEND;
			__UHEAP_RESET;
			if (sucess)
				{
				++sucesses;
				sucess=EFalse;
				}
			else
				sucesses=0;
			//Useful logging to see more details of what this code does
			//INFO_PRINTF7(_L("FR=% 2d S=% 2d C=0x%x SE=%d WCE=%d PAR=0x%x"),failRate,sucesses,cnt,setErr,creErr,parent);
			++failRate;
			} while (sucesses<10);
		}
	}

/**
  Single Argument Constructor for CCone2TestAppUi class.\n
*/
CCone2TestAppUi::CCone2TestAppUi(CTmsTestStep* aStep) :
	CTestCoeAppUi(aStep)
	{}
/**
  Destructor for CCone2TestAppUi class.\n
*/
CCone2TestAppUi::~CCone2TestAppUi()
    {
	delete iDriver;
	}
 /**
  Second phase Constructor for CCone2TestAppUi class.\n
  Invokes the base class CTestCoeAppUi second phase constructor.\n
  Instantiates a Test Driver used to drive the tests.\n
  Executes the testcases asynchronously using Autotest Manager.\n
*/   
void CCone2TestAppUi::ConstructL(CTmsTestStep* aStep)
    {
    CTestCoeAppUi::ConstructL();

	iDriver=new (ELeave) CTestDriver(*this, aStep); 
	iDriver->ConstructL();
	
	AutoTestManager().StartAutoTest();

   }

/**
   Auxiliary Function for all Test Cases
  
   The method is an override from CTestCoeAppUi. 
   This function is called asynchronously by RunL function of the
   AutotestManager after previous test case is executed.\n
   Calls the following functions one by one.\n
   1. TestIsDisplayingDialogAndRemoveFromStackAPIsL
   2. TestMakeVisibleOnChildControlsL
   3. TestAppHelpContextAPIL
   4. TestReadResourceAPIsL
   5. TestCoeControlAPIsL
   6. TestColorUseAPIsL
   7. TestConeAppUiSimpleAndMiscAPIsL
   8. TestConeInputCapabilitiesAPIs
   9. TestSetAndGetSystemDefaultViewAPIsL
   10. TestSetandGetCCoeControlAPIsL
   11. TestLowMemoryCoeControl
 */

void CCone2TestAppUi::RunTestStepL(TInt aStepNum)
	{
	_LIT(KTest11Name,"UIF-TCone2Step-LowMemoryCoeControlConstruction");
	_LIT(KTest11Desc,"Test creating CCoeControl in low memory");
	_LIT(KReturn,"...completed with return value '%d'\n");
	_LIT(KFinished,"Test Finished\n");
	TInt ret;

	switch(aStepNum)
		{
	case 1:
		SetTestStepID(_L("UIF-TCone2Step-TestIsDisplayingDialogAndRemoveFromStackAPIsL"));
		INFO_PRINTF1(_L("Test IsDisplayingDialog() and RemoveFromStack() APIs"));
		TRAP(ret,iDriver->TestIsDisplayingDialogAndRemoveFromStackAPIsL());
		INFO_PRINTF2(KReturn,ret);
		TEST(ret==KErrNone);
		RecordTestResultL();
		break;
	case 2:
		SetTestStepID(_L("UIF-TCone2Step-TestMakeVisibleOnChildControlsL"));
		INFO_PRINTF1(_L("Test makevisible on its child controls"));
		TRAP(ret,iDriver->TestMakeVisibleOnChildControlsL());
		INFO_PRINTF2(KReturn,ret);
		TEST(ret==KErrNone);
		RecordTestResultL();
		break;
	case 3:
		SetTestStepID(_L("UIF-TCone2Step-TestAppHelpContextAPIL"));
		INFO_PRINTF1(_L("Test AppHelpContext API"));
		TRAP(ret,iDriver->TestAppHelpContextAPIL());
		INFO_PRINTF2(KReturn,ret);
		TEST(ret==KErrNone);
		RecordTestResultL();
		break;
	case 4:
		SetTestStepID(_L("UIF-TCone2Step-TestReadResourceAPIsL"));
		INFO_PRINTF1(_L("Test ReadResource APIs"));
		TRAP(ret,iDriver->TestReadResourceAPIsL());
		INFO_PRINTF2(KReturn,ret);
		TEST(ret==KErrNone);
		RecordTestResultL();
		break;
	case 5:
		SetTestStepID(_L("UIF-TCone2Step-TestCoeControlAPIsL"));
		INFO_PRINTF1(_L("Test SetContainerWindow APIs"));
		TRAP(ret,iDriver->TestCoeControlAPIsL());
		INFO_PRINTF2(KReturn,ret);
		TEST(ret==KErrNone);
		RecordTestResultL();
		break;
	case 6:
		SetTestStepID(_L("UIF-TCone2Step-TestColorUseAPIsL"));
		INFO_PRINTF1(_L("Test ColorUse APIs"));
		TRAP(ret,iDriver->TestColorUseAPIsL());
		INFO_PRINTF2(KReturn,ret);
		TEST(ret==KErrNone);
		RecordTestResultL();
		break;
	case 7:
		SetTestStepID(_L("UIF-TCone2Step-TestConeAppUiSimpleAndMiscAPIsL"));
		INFO_PRINTF1(_L("Test Cone Misc APIs"));
		TRAP(ret,iDriver->TestConeMiscAPIsL());
		INFO_PRINTF2(KReturn,ret);
		TEST(ret==KErrNone);
		RecordTestResultL();
		break;
	case 8:
		SetTestStepID(_L("UIF-TCone2Step-TestConeInputCapabilitiesAPIs"));
		INFO_PRINTF1(_L("Test InputCapabilities APIs"));
		TRAP(ret,iDriver->TestConeInputCapabilitiesAPIs());
		INFO_PRINTF2(KReturn,ret);
		TEST(ret==KErrNone);
		RecordTestResultL();
		break;
	case 9:
		SetTestStepID(_L("UIF-TCone2Step-TestSetAndGetSystemDefaultViewAPIsL"));
		INFO_PRINTF1(_L("Test Set and Get system default view APIs"));
		TRAP(ret,iDriver->TestSetAndGetSystemDefaultViewAPIsL());
		INFO_PRINTF2(KReturn,ret);
		TEST(ret==KErrNone);
		RecordTestResultL();
		break;
	case 10:
		SetTestStepID(_L("UIF-TCone2Step-TestSetandGetCCoeControlAPIsL"));
		INFO_PRINTF1(_L("Test Set and Get APIs for CCoeControl"));
		TRAP(ret,iDriver->TestSetandGetCCoeControlAPIsL());
		INFO_PRINTF2(KReturn,ret);
		TEST(ret==KErrNone);
		RecordTestResultL();
		break;
	case 11:
		SetTestStepID(KTest11Name);
		INFO_PRINTF1(KTest11Desc);
		iDriver->TestLowMemoryCoeControl();
		INFO_PRINTF1(KFinished);
		RecordTestResultL();
		CloseTMSGraphicsStep();
		break;
	case 12:
		AutoTestManager().FinishAllTestCases(CAutoTestManager::EPass);
		break;
	default:
		break;
		}
	}

/**
  Completes the construction of the Control Environment(CCoeEnv object).\n
  Instantiates the CCone2TestAppUi class which serves as a AppUi class.\n
  Sets the CCone2TestAppUi object as the application's user interface object.\n
  Invokes the second phase constructor of the application's UI.\n
*/
void CTCone2Step::ConstructCone2AppL(CCoeEnv* aCoe)
	{ // runs inside a TRAP harness
	aCoe->ConstructL();
	CCone2TestAppUi* appUi=new(ELeave) CCone2TestAppUi(this);
	aCoe->SetAppUi(appUi);
	appUi->ConstructL(this);
	}

CTCone2Step::CTCone2Step()
	{
	SetTestStepName(KTCone2Step);
	}

CTCone2Step::~CTCone2Step()
	{
	}

TVerdict CTCone2Step::doTestStepL()
	{

	INFO_PRINTF1(_L("Test Started"));

	PreallocateHALBuffer();
	
	__UHEAP_MARK;

	CCoeEnv* coe=new(ELeave) CCoeEnv;
	TRAPD(err,ConstructCone2AppL(coe));
	if (!err)
		coe->ExecuteD();
	else
		{
		SetTestStepResult(EFail);
		delete coe;
		}

	REComSession::FinalClose();	
	__UHEAP_MARKEND;

	INFO_PRINTF1(_L("Test Finished"));
	return TestStepResult();
	}

