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
// This is a support executable used by "Cone\tef\TConeTestServer" (TCone4Step in particular)
// This application covers the following tests for the static objects
// Test 1 : Existing CCoeStatic derived objects using the 2 parameter
// constructor must be destroyed before the app ui.
// Way to test this,
// Case 1: Get hold of a particular static using CCoeEnv::Static(TUid aUid) 
// in an application's override of CEikAppUi::PrepareToExit() and confirm the 
// returned pointer is not null. 
// Case 2: Then, the same thing is done in the app ui's destructor to check that 
// the pointer is now null.
// Test 2: A static constructed with a negative priority should be accessible from the 
// app ui's destructor, but then destroyed before another static that has a lower priority value.
// Way to test this,
// Case 1: Construct a static (A) using the 3 parameter constructor, specifying a negative priority.
// Then construct another static (B) specifying a priority (A's priority - 1). 
// Check that static A is still non-null when accessed from the app ui's destructor. 
// Case 2: Then check that static A is null when accessed from B's destructor.
// Test 3: Given two statics with different positive priorities,
// the higher priority one should be destroyed first.
// Way to test this,
// Case 1: If (for example) static A has priority EDefaultDestructionPriority,
// and static B has EDefaultDestructionPriority-1, A's destructor should be able to access B,
// Case 2: But B's destructor shouldn't be able to access A.
// Test 4: Statics with priorities immediately either side of the pre/post-destroy app ui should be destroyed before/after the app ui. Should also test that 
// the first negative priority static is destroyed and not "skipped over" when the code calculates
// which static should be destroyed next after the app ui has been destroyed.
// Way to test this,
// Case 1: We could create statics A, B and C with priority zero, -1 and -2 respectively. 
// Then check in the app ui destructor that A is null, and B and C are both non-null.
// Case 2: Then in B's destructor check that C is still non-null.
// Case 3: And in C's destructor check that B is now null.
// 
//

/**
 @file
 @internalComponent - Internal Symbian test code 
*/

#include <coeccntx.h>
#include <apgtask.h>
#include <eikenv.h>
#include <eikappui.h>
#include <eikapp.h>
#include <eikdoc.h>
#include <techview/eikmenup.h>
#include <f32file.h>
#include <techview/eikon.hrh>
#include <eikstart.h> //TKAS added for exe-app


#include <tconetestexe.rsg>

//! File which stores the test results.\n
_LIT(KConeTestResultsFileName, "c:\\system\\conetest\\ConeTestResultsFile2.txt");
//! Cone Test Directory.\n
_LIT(KConeTestDir, "c:\\system\\conetest\\");
//! Literal for Test Pass.\n
_LIT8(KTestPass ,"PASS\r\n");
//! Literal for Test Fail.\n
_LIT8(KTestFail,"FAIL\r\n");
//! Literal to indicate Test number one.\n
_LIT8(KConeTest1,"Test1:");
//! Literal to indicate Test number two.\n
_LIT8(KConeTest2,"Test2:");
//! Literal to indicate Test number three.\n
_LIT8(KConeTest3,"Test3:");
//! Literal to indicate Test number four.\n
_LIT8(KConeTest4,"Test4:");
//! Literal to indicate case number one.\n
_LIT8(KConeTestCase1,"Case1:");
//! Literal to indicate case number Two.\n
_LIT8(KConeTestCase2,"Case2:");
//! Literal to indicate Case number three.\n
_LIT8(KConeTestCase3,"Case3:");
//! Uid for Cone Test Application.\n
const TUid KUidConeTestApp = {0x10004C5A};

//! Uids for diffent classes for static 
//! Unique Uid for object of Singleton Class CTConeTestStatic.\n
const TUid KUidTestStatic		 = 	{0x13003ACE}; 
//! Unique Uid for object of Singleton Class CTConeTestNegativePrioStaticA.\n
const TUid KUidTestStaticNegativePrioA = {0x13004ACE}; 
//! Unique Uid for object of Singleton Class CTConeTestNegativePrioStaticB.\n
const TUid KUidTestStaticNegativePrioB = {0x13005ACE}; 
//! Unique Uid for object of Singleton Class CTConeTestPosPrioStaticA.\n
const TUid KUidTestStaticPosPriA =	{0x13006ACE};
//! Unique Uid for object of Singleton Class CTConeTestPosPrioStaticB.\n
const TUid KUidTestStaticPosPriB = 	{0x13007ACE};
//! Unique Uid for object of Singleton Class CTConeTestPrioZeroStaticA.\n
const TUid KUidTestStaticPriZeroA=	{0x13009ACE};
//! Unique Uid for object of Singleton Class CTConeTestPrioOneStaticB.\n
const TUid KUidTestStaticPriOneB =	{0x1300AACE};
//! Unique Uid for object of Singleton Class CTConeTestPrioTwoStaticC.\n
const TUid KUidTestStaticPriTwoC =	{0x1300BACE};

//! Priorities for static objects
enum {ENegativePriortyStaticA = -3};
enum {EPriorityTwoStaticC= -2,EPriorityOneStaticB = -1,EPriorityZeroStaticA= 0};


//! A CCoeStatic derived class.\n
/**
  Class used to test the deletion of a CCoeStatic members before deletion of appUi class.\n
*/
class CTConeTestStatic : public CCoeStatic
	{
public:
	inline CTConeTestStatic(RFile& aFile);
	inline static CTConeTestStatic* Self();
	~CTConeTestStatic();
	RFile iFile;
	};
/**
  Destructor for CTConeTestStatic Class.\n
*/
CTConeTestStatic::~CTConeTestStatic()
	{
	}

//! A CCoeStatic derived class.\n
/**
  A Static Class with Negative priority for Test Case 2.\n
*/
class CTConeTestNegativePrioStaticA : public CCoeStatic
	{
public:
	inline CTConeTestNegativePrioStaticA(RFile& aFile);
	inline static CTConeTestNegativePrioStaticA* Self();
	~CTConeTestNegativePrioStaticA();
	
	RFile& iFile;
	};

//! A CCoeStatic derived class.\n
/**
  Static class with negative priority for Test case 2. (priority less than CTConeTestNegativePrioStaticA).\n
*/
class CTConeTestNegativePrioStaticB : public CCoeStatic
	{
public:
	inline CTConeTestNegativePrioStaticB();
	inline static CTConeTestNegativePrioStaticB* Self();
	~CTConeTestNegativePrioStaticB();
	
	RFile iFile;
	RFs iFs;
	};
/**
  Destructor for CTConeTestNegativePrioStaticA Class.\n
*/
CTConeTestNegativePrioStaticA::~CTConeTestNegativePrioStaticA()
	{
	}
/**
   @SYMTestCaseID UIF-TConeTestApp-Test2Case2
  
   @SYMPREQ
  
   @SYMTestCaseDesc Check for the order of deletion of CCoeStatic objects with 
   negative priorities.\n
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions : CTConeTestNegativePrioStaticA and CTConeTestNegativePrioStaticB objects
   have negative priorities.\n
   CTConeTestNegativePrioStaticB has lower negative priority than CTConeTestNegativePrioStaticA object.\n
   CTConeTestNegativePrioStaticA object should be deleted before  CTConeTestNegativePrioStaticB object.\n
   Hence a pointer to CTConeTestNegativePrioStaticA is obtained in CTConeTestNegativePrioStaticB destructor.\n
   
   @SYMTestExpectedResults The CTConeTestNegativePrioStaticA object pointer should be NULL.\n
  
   @SYMTestType : CIT 
 */
CTConeTestNegativePrioStaticB::~CTConeTestNegativePrioStaticB()
	{
	// Test 2, Case 2
	CTConeTestNegativePrioStaticA* testCoeStaticA = CTConeTestNegativePrioStaticA::Self();
	iFile.Write(KConeTest2);
	iFile.Write(KConeTestCase2);
	
	if(testCoeStaticA == NULL)
		iFile.Write(KTestPass);
	else
		iFile.Write(KTestFail);
		
	// CTConeTestNegativePrioStaticB class object is the most negative prioritised
	// static objects .Hence the file and session handles are closed here as no
	// more logging is required hereafter. 	
	iFile.Close();
	iFs.Close();	
	}

// Static class with positive priority for Test case 3:
//! A CCoeStatic derived class.\n
/**
  Static class with positive priority for Test case 3:
*/
class CTConeTestPosPrioStaticA : public CCoeStatic
	{
public:
	inline CTConeTestPosPrioStaticA(RFile& aFile);
	inline static CTConeTestPosPrioStaticA* Self();
	~CTConeTestPosPrioStaticA();
	
	RFile& iFile;
	};

// static class with positive priority less than CTConeTestPosPrioStaticA for Test case 3.
//! A CCoeStatic derived class.\n
/**
  Static class with positive priority less than CTConeTestPosPrioStaticA for Test case 3.\n
*/
class CTConeTestPosPrioStaticB : public CCoeStatic
	{
public:
	inline CTConeTestPosPrioStaticB(RFile& aFile);
	inline static CTConeTestPosPrioStaticB* Self();
	~CTConeTestPosPrioStaticB();
	
	RFile& iFile;
	};
/**
   @SYMTestCaseID UIF-TConeTestApp-Test3Case1
  
   @SYMPREQ
  
   @SYMTestCaseDesc Check for the availabity of CCoeStatic object with 
   lower positive priority in destructor of higher positive priority object.\n
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions : CTConeTestPosPrioStaticA and CTConeTestPosPrioStaticB objects
   have positive priorities.\n
   CTConeTestPosPrioStaticB has lower priority than CTConeTestPosPrioStaticA object.\n
   CTConeTestNegativePrioStaticB object should be available in  CTConeTestPosPrioStaticA object's destructor.\n
   Hence a pointer to CTConeTestPosPrioStaticB is obtained in CTConeTestPosPrioStaticA's destructor.\n
   
   @SYMTestExpectedResults The CTConeTestPosPrioStaticB object pointer should not be NULL.\n
  
   @SYMTestType : CIT 
 */
CTConeTestPosPrioStaticA::~CTConeTestPosPrioStaticA()
	{
	// Test 3 , Case 1
	CTConeTestPosPrioStaticB* testPosPrioStaticB = CTConeTestPosPrioStaticB::Self();
	iFile.Write(KConeTest3);
	iFile.Write(KConeTestCase1);
	
	if(testPosPrioStaticB != NULL)
		iFile.Write(KTestPass);
	else
		iFile.Write(KTestFail);
	}
/**
   @SYMTestCaseID UIF-TConeTestApp-Test3Case2
  
   @SYMPREQ
  
   @SYMTestCaseDesc Check for the order of deletion of CCoeStatics object with 
   different positive priorities.\n
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions : CTConeTestPosPrioStaticA and CTConeTestPosPrioStaticB objects
   have positive priorities.\n
   CTConeTestPosPrioStaticB has lower priority than CTConeTestPosPrioStaticA object.\n
   CTConeTestNegativePrioStaticA object should be deleted before CTConeTestPosPrioStaticB object's destructor is called.\n
   Hence a pointer to CTConeTestPosPrioStaticA is obtained in CTConeTestPosPrioStaticB's destructor.\n
   
   @SYMTestExpectedResults The CTConeTestPosPrioStaticA object pointer should be NULL.\n
  
   @SYMTestType : CIT 
 */
CTConeTestPosPrioStaticB::~CTConeTestPosPrioStaticB()
	{
	// Test 3 , Case 2
	CTConeTestPosPrioStaticA* testPosPrioStaticA = CTConeTestPosPrioStaticA::Self();
	iFile.Write(KConeTest3);
	iFile.Write(KConeTestCase2);
	
	if(testPosPrioStaticA == NULL)
		iFile.Write(KTestPass);
	else
		iFile.Write(KTestFail);
	}

//! A CCoeStatic derived class.\n
/**
  A static class with  priority 0 for test case 4
*/
class CTConeTestPrioZeroStaticA : public CCoeStatic
	{
public:
	inline CTConeTestPrioZeroStaticA(RFile& aFile);
	inline static CTConeTestPrioZeroStaticA* Self();
	~CTConeTestPrioZeroStaticA();
	
	RFile& iFile;
	};

//! A CCoeStatic derived class.\n
/**
  A static class with priority -1 for test case 4
*/
class CTConeTestPrioOneStaticB : public CCoeStatic
	{
public:
	inline CTConeTestPrioOneStaticB(RFile& aFile);
	inline static CTConeTestPrioOneStaticB* Self();
	~CTConeTestPrioOneStaticB();
	
	RFile& iFile;
	};

//! A CCoeStatic derived class.\n
/**
  A static class with priority -2 for test case 4	
*/
class CTConeTestPrioTwoStaticC : public CCoeStatic
	{
public:
	inline CTConeTestPrioTwoStaticC(RFile& aFile);
	inline static CTConeTestPrioTwoStaticC* Self();
	~CTConeTestPrioTwoStaticC();
	
	RFile& iFile;
	};
/**
  Destructor for CTConeTestPrioZeroStaticA Class.\n
*/ 
CTConeTestPrioZeroStaticA::~CTConeTestPrioZeroStaticA()
	{
	}
/**
   @SYMTestCaseID UIF-TConeTestApp-Test4Case2
  
   @SYMPREQ
  
   @SYMTestCaseDesc Check for the availability of CTConeTestPrioTwoStaticC object in 
   CTConeTestPrioOneStaticB's destructor.\n
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions : CTConeTestPrioOneStaticB and CTConeTestPrioTwoStaticC objects
   have negative priorities of -1 and -2 respectively.\n
   CTConeTestPrioTwoStaticC object should be available in CTConeTestPrioOneStaticB object's destructor is called.\n
   Hence a pointer to CTConeTestPrioTwoStaticC is obtained in CTConeTestPrioOneStaticB's destructor.\n
   
   @SYMTestExpectedResults The CTConeTestPosPrioStaticA object pointer should not be NULL.\n
  
   @SYMTestType : CIT 
 */	
CTConeTestPrioOneStaticB::~CTConeTestPrioOneStaticB()
	{
	// Test 4 , Case 2
	CTConeTestPrioTwoStaticC* testPrioTwoCoeStaticC = CTConeTestPrioTwoStaticC::Self();
	iFile.Write(KConeTest4);
	iFile.Write(KConeTestCase2);

	if(testPrioTwoCoeStaticC != NULL)
		iFile.Write(KTestPass);
	else
		iFile.Write(KTestFail);
	}
	
/**
   @SYMTestCaseID UIF-TConeTestApp-Test4Case3
  
   @SYMPREQ
  
   @SYMTestCaseDesc Check for the deletion of CTConeTestPrioOneStaticB object before  
   CTConeTestPrioTwoStaticC's destructor is called.\n
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions : CTConeTestPrioOneStaticB and CTConeTestPrioTwoStaticC objects
   have negative priorities of -1 and -2 respectively.\n
   CTConeTestPrioOneStaticB object should be deleted before CTConeTestPrioTwoStaticC object's destructor is called.\n
   Hence a pointer to CTConeTestPrioOneStaticB is obtained in CTConeTestPrioTwoStaticC's destructor.\n
   
   @SYMTestExpectedResults The CTConeTestPosPrioStaticA object pointer should be NULL.\n
  
   @SYMTestType : CIT 
 */	
CTConeTestPrioTwoStaticC::~CTConeTestPrioTwoStaticC()
	{
	// Test 4 , Case 3
	CTConeTestPrioOneStaticB* testPrioOneCoeStaticB = CTConeTestPrioOneStaticB::Self();
	iFile.Write(KConeTest4);
	iFile.Write(KConeTestCase3);

	if(testPrioOneCoeStaticB == NULL)
		iFile.Write(KTestPass);
	else
		iFile.Write(KTestFail);
	}

//
//
// CTConeTestAppView
//
//
//! A CCoeControl derived class.\n
/**
  View Class for TConeTestApp Application.\n
*/
class CTConeTestAppView : public CCoeControl
    {
public:
	static CTConeTestAppView* NewL(const TRect& aRect);
	CTConeTestAppView();
	~CTConeTestAppView();
    void ConstructL(const TRect& aRect);
private:
    // Inherited from CCoeControl
	void Draw(const TRect& /*aRect*/) const;
private:
	HBufC*  iConeTestText;
    };
/**
  Constructor for the View Class.\n
*/
CTConeTestAppView::CTConeTestAppView()
	{
	}
/**
  Static function used to instantiate the View Class.\n
  
  @return CTConeTestAppView*, Pointer to the newly created View.\n
*/
CTConeTestAppView* CTConeTestAppView::NewL(const TRect& aRect)
	{
	CTConeTestAppView* self = new(ELeave) CTConeTestAppView();
	CleanupStack::PushL(self);
	self->ConstructL(aRect);
	CleanupStack::Pop();
	return self;
	}
/**
  Destructor for the View Class.\n
*/
CTConeTestAppView::~CTConeTestAppView()
	{
	delete iConeTestText;
	}
/**
  Second phase constructor for CTConeTestAppView Class.\n
*/
void CTConeTestAppView::ConstructL(const TRect& aRect)
    {
	iConeTestText = iEikonEnv->AllocReadResourceL(R_TCONETEST_TEXT_TITLE);
	CreateWindowL();
	SetRect(aRect);
	ActivateL();
	}
/**
  Draws the TConeTestApp Application's View.\n
*/
void CTConeTestAppView::Draw(const TRect& /*aRect*/) const
	{
	CWindowGc& gc = SystemGc();
	TRect      drawRect = Rect();
	const CFont*  fontUsed = iEikonEnv->TitleFont();
	
	gc.Clear();
	gc.UseFont(fontUsed);
	TInt   baselineOffset=(drawRect.Height() - fontUsed->HeightInPixels())/2; 
	gc.DrawText(*iConeTestText,drawRect,baselineOffset,CGraphicsContext::ECenter, 0);
	gc.DiscardFont();
	}

//
//
// CTConeTestAppUi
//
//
//! A CEikAppUi derived class.\n
/**
  The class is the AppUi class for the TCone4Step test case.\n
*/
class CTConeTestAppUi : public CEikAppUi
    {
public:
    void ConstructL();
	~CTConeTestAppUi();
private:
    // Inherirted from class CEikAppUi
	void PrepareToExit();
	void HandleCommandL(TInt aCommand);
	void TestSetLogicalToPixelFontSizesL();

private:
	CCoeControl*	iAppView;
	};
	
/**
  Second phase constructor for  CTConeTestAppUi Class.\n
  Creates the following singleton objects.\n
  1. CTConeTestStatic.\n
  2. CTConeTestNegativePrioStaticA.\n
  3. CTConeTestPrioTwoStaticC.\n
  4. CTConeTestPosPrioStaticA.\n
  5. CTConeTestPosPrioStaticB.\n
  6. CTConeTestPrioZeroStaticA.\n
  7. CTConeTestPrioOneStaticB.\n
*/	
void CTConeTestAppUi::ConstructL()
    {
    BaseConstructL();
	iAppView = CTConeTestAppView::NewL(ClientRect());
	
	// Constructs the static object for tests
	CTConeTestNegativePrioStaticB* testCoeStaticB = new(ELeave)CTConeTestNegativePrioStaticB();
	
	CTConeTestStatic* testCoeStatic = new (ELeave)CTConeTestStatic(testCoeStaticB->iFile);
	CTConeTestNegativePrioStaticA* testCoeStaticA  = new(ELeave)CTConeTestNegativePrioStaticA(testCoeStaticB->iFile);
	CTConeTestPrioTwoStaticC* testPrioTwoStaticC = new(ELeave) CTConeTestPrioTwoStaticC(testCoeStaticB->iFile);
    CTConeTestPosPrioStaticA* testPosPriStaticA = new(ELeave) CTConeTestPosPrioStaticA(testCoeStaticB->iFile);
	CTConeTestPosPrioStaticB* testPosPriStaticB = new(ELeave) CTConeTestPosPrioStaticB(testCoeStaticB->iFile);
	CTConeTestPrioZeroStaticA* testPrioZeroStaticA = new(ELeave) CTConeTestPrioZeroStaticA(testCoeStaticB->iFile);
	CTConeTestPrioOneStaticB* testPrioOneStaticB = new(ELeave) CTConeTestPrioOneStaticB(testCoeStaticB->iFile);
	
	// to get rid of compiler warnings
	if(testCoeStatic==NULL  || testCoeStaticA == NULL ||  testCoeStaticB == NULL|| testPosPriStaticA ==NULL ||
		testPosPriStaticB == NULL || testPrioZeroStaticA == NULL || testPrioOneStaticB == NULL|| testPrioTwoStaticC == NULL)
		 return;	
	}
/**
   @SYMTestCaseID UIF-TConeTestApp-Test1Case2-Test2Case1-Test4Case1
  
   @SYMPREQ
  
   @SYMTestCaseDesc Following testcases are tested.\n
   1. Deletion of Static objects with positive priority before AppUi's destructor.\n
   2. Availability of Static objects with negative priority in AppUi's destructor.\n
   
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions : 
  
   @SYMTestExpectedResults 1. Static objects with positive priority should be deleted before AppUi is deleted.\n
   2.Negative priority static objects should be available in AppUi's destructor.\n
    
   @SYMTestType : CIT 
 */
CTConeTestAppUi::~CTConeTestAppUi()
	{
	CTConeTestNegativePrioStaticB* testNegStaticB = CTConeTestNegativePrioStaticB::Self();
	// Test 1, Case 2
	CTConeTestStatic* testCoeStatic = CTConeTestStatic::Self();
	testNegStaticB->iFile.Write(KConeTest1);
	testNegStaticB->iFile.Write(KConeTestCase2);
	
	if(testCoeStatic == NULL)
		testNegStaticB->iFile.Write(KTestPass);
	else
		testNegStaticB->iFile.Write(KTestFail);
		
	// Test 2, Case 1	 
	CTConeTestNegativePrioStaticA* testCoeStaticA = CTConeTestNegativePrioStaticA::Self();
	testNegStaticB->iFile.Write(KConeTest2);
	testNegStaticB->iFile.Write(KConeTestCase1);

	if(testCoeStaticA != NULL)
		testNegStaticB->iFile.Write(KTestPass);
	else
		testNegStaticB->iFile.Write(KTestFail);

	// Test 4, Case 1
	CTConeTestPrioZeroStaticA* testPrioZeroCoeStaticA = CTConeTestPrioZeroStaticA::Self();
	CTConeTestPrioOneStaticB* testPrioOneCoeStaticB = CTConeTestPrioOneStaticB::Self();
	CTConeTestPrioTwoStaticC* testPrioTwoCoeStaticC = CTConeTestPrioTwoStaticC::Self();
	testNegStaticB->iFile.Write(KConeTest4);
	testNegStaticB->iFile.Write(KConeTestCase1);

	if(testPrioZeroCoeStaticA == NULL && testPrioOneCoeStaticB != NULL && testPrioTwoCoeStaticC != NULL)
		testNegStaticB->iFile.Write(KTestPass);
	else
		testNegStaticB->iFile.Write(KTestFail);

	delete iAppView;
	}
/**
  Handles the user commands.\n
  Exits the application when EEikCmdExit command is generated.\n
*/
void CTConeTestAppUi::HandleCommandL(TInt aCommand)
	{
	switch (aCommand)
		{
 	case EEikCmdExit: 
		Exit();
		break;
		}
	}
/**
   @SYMTestCaseID UIF-TConeTestApp-Test1Case1
  
   @SYMPREQ
  
   @SYMTestCaseDesc Availability of Positive priority static objects before AppUi is deleted.\n
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions : The PrepareToExit function performs pre-exit processing
   to ensure the application will exit cleanly.\n
   Static objects with positive priority should be available in this function.\n
   Pointer to CTConeTestStatic object is obtained.\n
   The validity of the pointer is checked.\n
  
   @SYMTestExpectedResults The pointer should be valid.\n
  
   @SYMTestType : CIT 
 */
void CTConeTestAppUi::PrepareToExit()
	{
	CEikAppUi::PrepareToExit();
	// Test 1, Case 1
	CTConeTestStatic* testCoeStatic = CTConeTestStatic::Self();
	
	testCoeStatic->iFile.Write(KConeTest1);
	testCoeStatic->iFile.Write(KConeTestCase1);

	if(testCoeStatic != NULL)
		testCoeStatic->iFile.Write(KTestPass);
	else
		testCoeStatic->iFile.Write(KTestFail);
	}
	

//
//
// CTConeTestDocument
//
//
//! A CEikDocument derived class.\n
/**
  The base for all Uikon applications’ documents.\n
  A class derived from CEikDocument is used in each Uikon application.\n
  In file-based applications, the document provides an intermediate layer between the user interface, the model and the file the model will be stored in.\n
  Non-file-based applications will only use a document to create the application UI.
*/
class CTConeTestDocument : public CEikDocument
	{
public:
	static CTConeTestDocument* NewL(CEikApplication& aApp);
	CTConeTestDocument(CEikApplication& aApp);
	void ConstructL();
private: 
	// Inherited from CEikDocument
	CEikAppUi* CreateAppUiL();
	};
/**
  Single argument constructor for CTConeTestDocument.\n
  Call base class's (CEikDocument) constructor.\n
*/
CTConeTestDocument::CTConeTestDocument(CEikApplication& aApp)
		: CEikDocument(aApp)
	{
	}
/**
  Creates the AppUi for the application.\n
  Instantiates CTConeTestAppUi object.\n
  @return CTConeTestAppUi*, Pointer to AppUi object.\n
*/
CEikAppUi* CTConeTestDocument::CreateAppUiL()
	{
    return new(ELeave) CTConeTestAppUi;
	}

//
//
// CTConeTestApplication
//
//
//! A CEikApplication derived class.\n
/**
  The root of all Uikon applications.\n
  CEikApplication builds on CApaApplication, providing a basis for applications 
  working within the framework provided by Uikon.\n
  It also contains an interface to the resource file and the document.
*/
class CTConeTestApplication : public CEikApplication
	{
private: 
	// Inherited from class CApaApplication
	CApaDocument* CreateDocumentL();
	TUid AppDllUid() const;
private:
	CApaDocument* CreateDocumentL(CApaProcess* a) { return CEikApplication::CreateDocumentL(a); }
	};
/**
  Gets the application specific UID.\n
  The UID is used to differentiate between UI applications.\n
  An implementation of this function must be supplied by the UI application.\n
 
  @return TUid,Application specific Uid.\n
*/
TUid CTConeTestApplication::AppDllUid() const
	{
	return KUidConeTestApp;
	}
/**
  Creates a document object.\n
  The function is called by the application process when a new document is required.\n
  The application process adds the new document to its list of documents.\n
  An implementation of this function is supplied by the UI framework.\n
 
  @return CApaDocument* , A pointer to the newly created document.\n
  
*/
CApaDocument* CTConeTestApplication::CreateDocumentL()
	{
	return new (ELeave) CTConeTestDocument(*this);
	}
/**
  The only exported function.\n
  This function will be called by Application framework to create the application.\n
 
  @return CApaApplication*, A pointer to the newly created application.\n
  
*/
LOCAL_C CApaApplication* NewApplication()
	{
	return new CTConeTestApplication;
	}
/**
   Entry Function.\n
*/
GLDEF_C TInt E32Main()
	{
	return EikStart::RunApplication( NewApplication );
	}



//
// inline functions 
//

// inline function for CTConeTestStatic
/**
  Constructor for CTConeTestStatic Class.\n
*/
inline CTConeTestStatic::CTConeTestStatic(RFile& aFile)
	: CCoeStatic(KUidTestStatic),iFile(aFile)
	{
	}
/**
  Returns pointer to CTConeTestStatic Object.\n
*/
inline CTConeTestStatic* CTConeTestStatic::Self()
	{
	return STATIC_CAST(CTConeTestStatic*,CCoeEnv::Static(KUidTestStatic));
	}
	
// inline functions for CTConeTestNegativePrioStaticA
/**
  Constructor for CTConeTestNegativePrioStaticA Class.\n
*/
inline CTConeTestNegativePrioStaticA::CTConeTestNegativePrioStaticA(RFile& aFile)
	: CCoeStatic(KUidTestStaticNegativePrioA,ENegativePriortyStaticA),iFile(aFile)
	{
	}
/**
  Returns pointer to CTConeTestNegativePrioStaticA Object.\n
*/
inline CTConeTestNegativePrioStaticA* CTConeTestNegativePrioStaticA::Self()
	{
	return STATIC_CAST(CTConeTestNegativePrioStaticA*,CCoeEnv::Static(KUidTestStaticNegativePrioA));
	}
	
// inline functions for CTConeTestNegativePrioStaticB
/**
  Constructor for CTConeTestNegativePrioStaticB Class.\n
*/	
inline CTConeTestNegativePrioStaticB::CTConeTestNegativePrioStaticB()
	: CCoeStatic(KUidTestStaticNegativePrioB,ENegativePriortyStaticA - 1)
	{
	User::LeaveIfError(iFs.Connect());
	TInt err = iFs.MkDirAll(KConeTestDir);
	
	err = iFile.Create(iFs,KConeTestResultsFileName,EFileWrite | EFileShareAny);
	if(err == KErrAlreadyExists)
		iFile.Open(iFs,KConeTestResultsFileName,EFileWrite | EFileShareAny);
	}
/**
  Returns pointer to CTConeTestNegativePrioStaticB object.\n
*/
inline CTConeTestNegativePrioStaticB* CTConeTestNegativePrioStaticB::Self()
	{
	return STATIC_CAST(CTConeTestNegativePrioStaticB*,CCoeEnv::Static(KUidTestStaticNegativePrioB));
	}

// inline functions for CTConeTestPosPrioStaticA
/**
  Constructor for CTConeTestPosPrioStaticA Class.\n
*/	
inline CTConeTestPosPrioStaticA::CTConeTestPosPrioStaticA(RFile& aFile)
	: CCoeStatic(KUidTestStaticPosPriA,EDefaultDestructionPriority),iFile(aFile)
	{
	}
/**
  Returns pointer to CTConeTestPosPrioStaticA object.\n
*/
inline CTConeTestPosPrioStaticA* CTConeTestPosPrioStaticA::Self()
	{
	return STATIC_CAST(CTConeTestPosPrioStaticA*,CCoeEnv::Static(KUidTestStaticPosPriA));
	}

// inline functions for CTConeTestPosPrioStaticB		
/**
  Constructor for CTConeTestPosPrioStaticB Class.\n
*/
inline CTConeTestPosPrioStaticB::CTConeTestPosPrioStaticB(RFile& aFile)
	: CCoeStatic(KUidTestStaticPosPriB,EDefaultDestructionPriority-1),iFile(aFile)
	{
	}
/**
  Returns pointer to CTConeTestPosPrioStaticB object.\n
*/
inline CTConeTestPosPrioStaticB* CTConeTestPosPrioStaticB::Self()
	{
	return STATIC_CAST(CTConeTestPosPrioStaticB*,CCoeEnv::Static(KUidTestStaticPosPriB));
	}
	
// inline functions for CTConeTestPrioZeroStaticA			
/**
  Constructor for CTConeTestPrioZeroStaticA Class.\n
*/
inline CTConeTestPrioZeroStaticA::CTConeTestPrioZeroStaticA(RFile& aFile)
	: CCoeStatic(KUidTestStaticPriZeroA,EPriorityZeroStaticA),iFile(aFile)
	{
	}
/**
  Returns pointer to CTConeTestPrioZeroStaticA object.\n
*/
inline CTConeTestPrioZeroStaticA* CTConeTestPrioZeroStaticA::Self()
	{
	return STATIC_CAST(CTConeTestPrioZeroStaticA*,CCoeEnv::Static(KUidTestStaticPriZeroA));
	}
	
// inline functions for CTConeTestPrioOneStaticB					
/**
  Constructor for CTConeTestPrioOneStaticB Class.\n
*/
inline CTConeTestPrioOneStaticB::CTConeTestPrioOneStaticB(RFile& aFile)
	: CCoeStatic(KUidTestStaticPriOneB,EPriorityOneStaticB),iFile(aFile)
	{	
	}
/**
  Returns pointer to CTConeTestPrioOneStaticB object.\n
*/
inline CTConeTestPrioOneStaticB* CTConeTestPrioOneStaticB::Self()
	{
	return STATIC_CAST(CTConeTestPrioOneStaticB*,CCoeEnv::Static(KUidTestStaticPriOneB));
	}

// inline functions for CTConeTestPrioTwoStaticC						
/**
  Constructor for CTConeTestPrioTwoStaticC Class.\n
*/
inline CTConeTestPrioTwoStaticC::CTConeTestPrioTwoStaticC(RFile& aFile)
	: CCoeStatic(KUidTestStaticPriTwoC,EPriorityTwoStaticC),iFile(aFile)
	{
	}
/**
  Returns pointer to CTConeTestPrioTwoStaticC object.\n
*/
inline CTConeTestPrioTwoStaticC* CTConeTestPrioTwoStaticC::Self()
{
	return STATIC_CAST(CTConeTestPrioTwoStaticC*,CCoeEnv::Static(KUidTestStaticPriTwoC));
}



