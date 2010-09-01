/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
* All rights reserved.
* This component and the accompanying materials are made available
* under the terms of "Eclipse Public License v1.0"
* which accompanies this distribution, and is available
* at the URL "http://www.eclipse.org/legal/epl-v10.html".
*
* Initial Contributors:
* Nokia Corporation - initial contribution.
*
* Contributors:
*
* Description:  AknSoundServerStifTest test module.
*
*/

#ifndef AKNSOUNDSERVERSTIFTEST_H
#define AKNSOUNDSERVERSTIFTEST_H

// INCLUDES
#include "stiftestmodule.h"
#include "aknsoundserversession.h"
#include <stiflogger.h>

// Officially allocated DLL UID for sound server session.
const TInt KDllUid = 0x101FB3E7; 

// For logging.
_LIT(KAknSoundServerStifTestLogPath, "\\logs\\testframework\\AknSoundServerStifTest\\"); 
_LIT(KAknSoundServerStifTestLogFile, "AknSoundServerStifTest.txt"); 
_LIT(KAknSoundServerStifTestLogFileWithTitle, "AknSoundServerStifTest_[%S].txt");

// CONSTANTS
#define GETPTR &
#define ENTRY(str,func) {_S(str), GETPTR func,0,0,0}
#define FUNCENTRY(func) {_S(#func), GETPTR func,0,0,0}
#define OOM_ENTRY(str,func,a,b,c) {_S(str), GETPTR func,a,b,c}
#define OOM_FUNCENTRY(func,a,b,c) {_S(#func), GETPTR func,a,b,c}

// FORWARD DECLARATIONS
class CAknSoundServerStifTest;
class CAknAppUi;
class CAknKeySoundSystem;

// DATA TYPES
typedef TInt (CAknSoundServerStifTest::* TestFunction)(TTestResult&);

// CLASS DECLARATION

/**
*  An internal structure containing a test case name and
*  the pointer to function doing the test
*
*  @lib ?library
*  @since ?Series60_version
*/
class TCaseInfoInternal
    {
public:
    const TText*    iCaseName;
    TestFunction    iMethod;
    TBool           iIsOOMTest;
    TInt            iFirstMemoryAllocation;
    TInt            iLastMemoryAllocation;
    };

// CLASS DECLARATION

/**
*  A structure containing a test case name and
*  the pointer to function doing the test
*
*  @lib ?library
*  @since ?Series60_version
*/
class TCaseInfo
    {
public:
    TPtrC        iCaseName;
    TestFunction iMethod;
    TBool        iIsOOMTest;
    TInt         iFirstMemoryAllocation;
    TInt         iLastMemoryAllocation;

TCaseInfo(const TText* a) : iCaseName((TText*) a) {};
    };

// CLASS DECLARATION

/**
*  This a AknSoundServerStifTest class.
*  ?other_description_lines
*
*  @lib ?library
*  @since ?Series60_version
*/
NONSHARABLE_CLASS(CAknSoundServerStifTest) : public CTestModuleBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CAknSoundServerStifTest* NewL();

    /**
    * Destructor.
    */
    virtual ~CAknSoundServerStifTest();

public: // Functions from base classes

    /**
    * From CTestModuleBase InitL is used to initialize the 
    *       AknSoundServerStifTest. It is called once for every instance of 
    *       TestModuleAknSoundServerStifTest after its creation.
    * @since ?Series60_version
    * @param aIniFile Initialization file for the test module (optional)
    * @param aFirstTime Flag is true when InitL is executed for first 
    *               created instance of AknSoundServerStifTest.
    * @return Symbian OS error code
    */
    TInt InitL(TFileName& aIniFile, TBool aFirstTime);

    /**
    * From CTestModuleBase GetTestCasesL is used to inquiry test cases 
    *   from AknSoundServerStifTest. 
    * @since ?Series60_version
    * @param aTestCaseFile Test case file (optional)
    * @param aTestCases  Array of TestCases returned to test framework
    * @return Symbian OS error code
    */
    TInt GetTestCasesL( 
        const TFileName& aTestCaseFile, 
        RPointerArray<TTestCaseInfo>& aTestCases);

    /**
    * From CTestModuleBase RunTestCaseL is used to run an individual 
    *   test case. 
    * @since ?Series60_version
    * @param aCaseNumber Test case number
    * @param aTestCaseFile Test case file (optional)
    * @param aResult Test case result returned to test framework (PASS/FAIL)
    * @return Symbian OS error code (test case execution error, which is 
    *           not reported in aResult parameter as test case failure).
    */   
    TInt RunTestCaseL( 
        const TInt aCaseNumber, 
        const TFileName& aTestCaseFile,
        TTestResult& aResult);

    /**
    * From CTestModuleBase; OOMTestQueryL is used to specify is particular
    * test case going to be executed using OOM conditions
    * @param aTestCaseFile Test case file (optional)
    * @param aCaseNumber Test case number (optional)
    * @param aFailureType OOM failure type (optional)
    * @param aFirstMemFailure The first heap memory allocation failure value (optional)
    * @param aLastMemFailure The last heap memory allocation failure value (optional)
    * @return TBool
    */
    virtual TBool OOMTestQueryL( 
        const TFileName& /* aTestCaseFile */, 
        const TInt /* aCaseNumber */, 
        TOOMFailureType& aFailureType, 
        TInt& /* aFirstMemFailure */, 
        TInt& /* aLastMemFailure */);

    /**
    * From CTestModuleBase; OOMTestInitializeL may be used to initialize OOM
    * test environment
    * @param aTestCaseFile Test case file (optional)
    * @param aCaseNumber Test case number (optional)
    * @return None
    */
    virtual void OOMTestInitializeL( 
        const TFileName& /* aTestCaseFile */, 
        const TInt /* aCaseNumber */ ); 

    /**
    * From CTestModuleBase; OOMHandleWarningL
    * @param aTestCaseFile Test case file (optional)
    * @param aCaseNumber Test case number (optional)
    * @param aFailNextValue FailNextValue for OOM test execution (optional)
    * @return None
    *
    * User may add implementation for OOM test warning handling. Usually no
    * implementation is required.           
    */
    virtual void OOMHandleWarningL( 
        const TFileName& /* aTestCaseFile */,
        const TInt /* aCaseNumber */, 
        TInt& /* aFailNextValue */); 

    /**
    * From CTestModuleBase; OOMTestFinalizeL may be used to finalize OOM
    * test environment
    * @param aTestCaseFile Test case file (optional)
    * @param aCaseNumber Test case number (optional)
    * @return None
    */
    virtual void OOMTestFinalizeL( 
        const TFileName& /* aTestCaseFile */, 
        const TInt /* aCaseNumber */ );

private:
    /**
    * C++ default constructor.
    */
    CAknSoundServerStifTest();

    /**
    * By default Symbian 2nd phase constructor is private.
    */
    void ConstructL();

    /**
    * Function returning test case name and pointer to test case function.
    * @since ?Series60_version
    * @param aCaseNumber test case number
    * @return TCaseInfo 
    */
    const TCaseInfo Case (const TInt aCaseNumber) const;

    // --------------
    // Helper methods
    // --------------
    RAknSoundServerSession CreateNewSessionL(TInt aSessionUid);
    void PushContextL(RAknSoundServerSession& aSession, TInt aResId, TInt aSessionUid);
    void PrintWithDelay(const TInt aPriority, const TDesC& aDesC1, const TDesC& aDesC2);
    
    // -----------
    // Test cases.
    // -----------
    TInt TestCaseInit(TTestResult& aResult);
    TInt TestCasePlayKey(TTestResult& aResult);
    TInt TestCasePlayKeyAsync(TTestResult& aResult);
    TInt TestCasePlaySid(TTestResult& aResult);
    TInt TestCaseStopCurrentTone(TTestResult& aResult);
    TInt TestCaseAddSidsL(TTestResult& aResult);
    TInt TestCasePushContextL(TTestResult& aResult);
    TInt TestCaseLockContextL(TTestResult& aResult);
    TInt TestCaseCloseServer(TTestResult& aResult);    
    
private: // Data
    // Pointer to test (function) to be executed
    TestFunction iMethod;

    // Pointer to logger
    CStifLogger * iLog; 

    // Normal logger
    CStifLogger* iStdLog;

    // Test case logger
    CStifLogger* iTCLog;

    // Flag saying if test case title should be added to log file name
    TBool iAddTestCaseTitleToLogName;
    
    // Session to keysound server. Not to be used in test cases. This session is
    // for STIF application keysounds. Without this the application's keysounds 
    // would stop working when tests are executed. BringToForeground() must
    // be called for this session in the end of a test case if BringToForeground()
    // is called for some other session.    
    RAknSoundServerSession iSoundServerSession;
    };

#endif // AKNSOUNDSERVERSTIFTEST_H

// End of File
