/*
* Copyright (c) 2002-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Implementation for test cases.
*
*/

// INCLUDE FILES
#include <e32math.h>
#include <aknsoundsystem.h>
#include <aknappui.h>
#include <s32mem.h>
#include <eikkeysound.h>
#include <avkon.rsg>

#include "aknsoundserverstiftest.h"
#include "aknsoundserversession.h"
#include "eiksrvsoundserversession.h"

// Fail code used as a default, if no error code is available.
const TInt KDefaultFailCode = -999;

// Sound server session UIDs taken from test range (0xE0000000...0xEFFFFFFF).
const TInt KSession1Uid = 0xE2220001;
const TInt KSession2Uid = 0xE2220002;

// Fake resource ids taken from test range (0xE0000000...0xEFFFFFFF).
#define R_STIFTEST_SOUND_CONTEXT_1 0xE1110001
#define R_STIFTEST_SOUND_CONTEXT_2 0xE1110002

// TestModuleIf().Printf() seems to work better with a small delay.
const TInt KPrintDelay = 100000;

// Test case names.
_LIT(KTestCaseInit,            "'Init keysound server'");
_LIT(KTestCasePlayKey,         "'Play keysound'");
_LIT(KTestCasePlayKeyAsync,    "'Play keysound (async)'");
_LIT(KTestCasePlaySid,         "'Play sid'");
_LIT(KTestCaseStopCurrentTone, "'Stop current tone'");
_LIT(KTestCaseAddSids,         "'Add sids'"); 
_LIT(KTestCasePushContext,     "'Push context'");
_LIT(KTestCaseLockContext,     "'Lock context'");
_LIT(KTestCaseCloseServer,     "'Close server'");

// Generic test case texts.
_LIT(KTestPassed,              "Test case passed");
_LIT(KTestFailed,              "Test case failed");
_LIT(KBegin,                   "Begin");
_LIT(KEnd,                     "End");

// Error texts.
_LIT(KInitFailed,              "Init() failed");
_LIT(KConnectFailed,           "Connect() failed");
_LIT(KInvalidTRequestStatus,   "Invalid TRequestStatus");
_LIT(KFirstTopContextWrong,    "First TopContext() wrong");
_LIT(KSecondTopContextWrong,   "Second TopContext() wrong");
_LIT(KThirdTopContextWrong,    "Third TopContext() wrong");
_LIT(KFourthTopContextWrong,   "Fourth TopContext() wrong");
_LIT(KFifthTopContextWrong,    "Fifth TopContext() wrong");
_LIT(KSixthTopContextWrong,    "Sixth TopContext() wrong");
_LIT(KInvalidReturnValue,      "Return value not KErrPermissionDenied");

// Other texts
_LIT(KPlayingKeyClick,         "Playing key click");
_LIT(KPlayingErrorTone,        "Playing error tone");
_LIT(KBatteryLowStopped,       "Battery low stopped");
_LIT(KPlayingSid,              "Playing sid:");
_LIT(KSidId,                   "0x%x");
_LIT(KPlayingFinished,         "Playing finished"); 
_LIT(KPressingKey,             "Pressing key:");
_LIT(KKeyId,                   "%d" );
_LIT(KFinished,                "Finished");
 
// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CAknSoundServerStifTest::Case
// Returns a test case by number.
//
// This function contains an array of all available test cases 
// i.e pair of case name and test function. If case specified by parameter
// aCaseNumber is found from array, then that item is returned.
// 
// The reason for this rather complicated function is to specify all the
// test cases only in one place. It is not necessary to understand how
// function pointers to class member functions works when adding new test
// cases. See function body for instructions how to add new test case.
// -----------------------------------------------------------------------------
//
const TCaseInfo CAknSoundServerStifTest::Case ( 
    const TInt aCaseNumber ) const 
     {
    /**
    * To add new test cases, implement new test case function and add new 
    * line to KCases array specify the name of the case and the function 
    * doing the test case
    * In practice, do following
    * 1) Make copy of existing test case function and change its name
    *    and functionality. Note that the function must be added to 
    *    AknSoundServerStifTest.cpp file and to AknSoundServerStifTest.h 
    *    header file.
    *
    * 2) Add entry to following KCases array either by using:
    *
    * 2.1: FUNCENTRY or ENTRY macro
    * ENTRY macro takes two parameters: test case name and test case 
    * function name.
    *
    * FUNCENTRY macro takes only test case function name as a parameter and
    * uses that as a test case name and test case function name.
    *
    * Or
    *
    * 2.2: OOM_FUNCENTRY or OOM_ENTRY macro. Note that these macros are used
    * only with OOM (Out-Of-Memory) testing!
    *
    * OOM_ENTRY macro takes five parameters: test case name, test case 
    * function name, TBool which specifies is method supposed to be run using
    * OOM conditions, TInt value for first heap memory allocation failure and 
    * TInt value for last heap memory allocation failure.
    * 
    * OOM_FUNCENTRY macro takes test case function name as a parameter and uses
    * that as a test case name, TBool which specifies is method supposed to be
    * run using OOM conditions, TInt value for first heap memory allocation 
    * failure and TInt value for last heap memory allocation failure. 
    */ 

    static TCaseInfoInternal const KCases[] =
        {
        // To add new test cases, add new items to this array
        
        // NOTE: When compiled to GCCE, there must be Classname::
        // declaration in front of the method name, e.g. 
        // CAknSoundServerStifTest::PrintTest. Otherwise the compiler
        // gives errors.
        
        // enum TKeySoundServerCommands
        //     {
        //     EKeySoundServerInit,                 TestCaseInit()
        //     EKeySoundServerPlayKey,              TestCasePlayKey()
        //     EKeySoundServerPlaySID,              TestCasePlaySid()
        //     EKeySoundServerAddSIDS,              TestCaseAddSidsL()
        //     EKeySoundServerRemoveSIDS,           None. (Command is unused and should be removed!)
        //     EKeySoundServerPushContext,          TestCasePushContextL()
        //     EKeySoundServerPopContext,           TestCasePushContextL()
        //     EKeySoundServerBringToForeground,    TestCasePushContextL()
        //     EKeySoundServerStopCurrentTone,      TestCaseStopCurrentTone()
        //     EKeySoundServerLockContext,          TestCaseLockContextL()
        //     EKeySoundServerReleaseContext,       TestCaseLockContextL()
        //     EKeySoundServerCloseServer,          TestCaseCloseServerL()
        //     EKeySoundServerTopContext            TestCasePushContextL()
        //     };

        ENTRY("Init keysound server",   CAknSoundServerStifTest::TestCaseInit),
        ENTRY("Play keysound",          CAknSoundServerStifTest::TestCasePlayKey),
        ENTRY("Play keysound (async)",  CAknSoundServerStifTest::TestCasePlayKeyAsync),
        ENTRY("Play sid",               CAknSoundServerStifTest::TestCasePlaySid),
        ENTRY("Stop current tone",      CAknSoundServerStifTest::TestCaseStopCurrentTone),
        ENTRY("Add sids",               CAknSoundServerStifTest::TestCaseAddSidsL),
        ENTRY("Push context",           CAknSoundServerStifTest::TestCasePushContextL),
        ENTRY("Lock context",           CAknSoundServerStifTest::TestCaseLockContextL),
        ENTRY("Close server",           CAknSoundServerStifTest::TestCaseCloseServer)
        };

    // Verify that case number is valid
    if( (TUint) aCaseNumber >= sizeof( KCases ) / 
                               sizeof( TCaseInfoInternal ) )
        {
        // Invalid case, construct empty object
        TCaseInfo null( (const TText*) L"" );
        null.iMethod = NULL;
        null.iIsOOMTest = EFalse;
        null.iFirstMemoryAllocation = 0;
        null.iLastMemoryAllocation = 0;
        return null;
        } 

    // Construct TCaseInfo object and return it
    TCaseInfo tmp ( KCases[ aCaseNumber ].iCaseName );
    tmp.iMethod = KCases[ aCaseNumber ].iMethod;
    tmp.iIsOOMTest = KCases[ aCaseNumber ].iIsOOMTest;
    tmp.iFirstMemoryAllocation = KCases[ aCaseNumber ].iFirstMemoryAllocation;
    tmp.iLastMemoryAllocation = KCases[ aCaseNumber ].iLastMemoryAllocation;
    return tmp;
    }
    
// -----------------------------------------------------------------------------
// CAknSoundServerStifTest::TestCaseInit()
// Creates and initializes a connection to Keysound Server.
// Test case for server command "EKeySoundServerInit".
// -----------------------------------------------------------------------------
//     
TInt CAknSoundServerStifTest::TestCaseInit(TTestResult& aResult)
    {
    // Default result is fail.
    aResult.SetResult(KDefaultFailCode, KTestFailed);

    // Start test.
    PrintWithDelay(0, KBegin, KTestCaseInit); 
    
    RAknSoundServerSession session;
    TInt err = session.Connect();
    
    if (!err)
        {
        // The application UID should be given as a parameter for Init().
        // However, we are already using that UID for iSoundServerSession 
        // and don't want to use it twice.
        TBool init = session.Init(KSession1Uid);

        if(init)
            {
            // Test case passed.
            aResult.SetResult(KErrNone, KTestPassed);
            }
        else
            {
            aResult.SetResult(KDefaultFailCode, KInitFailed);
            }
        }
    else
        {
        aResult.SetResult(err, KConnectFailed);
        }
        
    session.Close();  
    
    // End test.        
    PrintWithDelay(0, KEnd, KTestCaseInit);          

    // Case was executed
    return KErrNone; 
    }
    
// -----------------------------------------------------------------------------
// CAknSoundServerStifTest::TestCasePlayKey()
// Plays a keysound.
// Test case for server command "EKeySoundServerPlayKey".
// -----------------------------------------------------------------------------
//     
TInt CAknSoundServerStifTest::TestCasePlayKey(TTestResult& aResult)
    {
    // Default result is fail.
    aResult.SetResult(KDefaultFailCode, KTestFailed); 
    
    // Start test.
    PrintWithDelay(0, KBegin, KTestCasePlayKey);     
        
    RAknSoundServerSession session = CreateNewSessionL(KSession1Uid);
        
    // Execute step 1.
    session.KeyPressed(EStdKeyDownArrow, EFalse);
    
    PrintWithDelay(0, KNullDesC, KPlayingKeyClick);

    // Test case passed (unfortunately there is no means to really ensure it).
    aResult.SetResult(KErrNone, KTestPassed);    

    session.Close();
    
    // End test.        
    PrintWithDelay(0, KEnd, KTestCasePlayKey);    

    // Case was executed
    return KErrNone; 
    }
    
// -----------------------------------------------------------------------------
// CAknSoundServerStifTest::TestCasePlayKeyAsync()
// Plays a keysound asynchronously.
// Test case for server command "EKeySoundServerPlayKey".
// -----------------------------------------------------------------------------
//     
TInt CAknSoundServerStifTest::TestCasePlayKeyAsync(TTestResult& aResult)
    {
    // Default result is fail.
    aResult.SetResult(KDefaultFailCode, KTestFailed); 
    
    // Start test.
    PrintWithDelay(0, KBegin, KTestCasePlayKeyAsync);     
        
    // Note that REikSrvSoundServerSession is used instead of RAknSoundServerSession.        
    REikSrvSoundServerSession session;
    User::LeaveIfError(session.Connect());

    // Session must be initialised.
    session.Init(KSession1Uid);

    PrintWithDelay(0, KNullDesC, KPlayingKeyClick);
    
    TRequestStatus status;
    session.KeyPressed(EStdKeyDownArrow, status, EFalse);
    User::WaitForRequest(status);
    
    if(status.Int() == KErrNone)
        {
        // Test case passed.
        aResult.SetResult(KErrNone, KTestPassed);
        }
    else
        {
        aResult.SetResult(status.Int(), KInvalidTRequestStatus);
        }
        
    session.Close();     
    
    // End test.        
    PrintWithDelay(0, KEnd, KTestCasePlayKeyAsync);    
        
    // Case was executed
    return KErrNone; 
    }    

// -----------------------------------------------------------------------------
// CAknSoundServerStifTest::TestCasePlaySid()
// Plays a sid.
// Test case for server command "EKeySoundServerPlaySID".
// -----------------------------------------------------------------------------
//     
TInt CAknSoundServerStifTest::TestCasePlaySid(TTestResult& aResult)
    {
    // Default result is fail.
    aResult.SetResult(KDefaultFailCode, KTestFailed); 
        
    // Start test.
    PrintWithDelay(0, KBegin, KTestCasePlaySid);         
    
    RAknSoundServerSession session = CreateNewSessionL(KSession1Uid);
        
    session.PlaySound(EAvkonSIDErrorTone);
    
    PrintWithDelay(0, KNullDesC, KPlayingErrorTone);     

    // Test case passed (unfortunately there is no means to really ensure it).
    aResult.SetResult(KErrNone, KTestPassed);    

    session.Close();

    // End test.        
    PrintWithDelay(0, KEnd, KTestCasePlaySid);    
    
    // Case was executed
    return KErrNone; 
    }
    
// -----------------------------------------------------------------------------
// CAknSoundServerStifTest::TestCaseStopCurrentTone()
// Stops a playing sid.
// Test case for server command "EKeySoundServerStopCurrentTone".
// -----------------------------------------------------------------------------
//     
TInt CAknSoundServerStifTest::TestCaseStopCurrentTone(TTestResult& aResult)
    {
    // Default result is fail.
    aResult.SetResult(KDefaultFailCode, KTestFailed); 
        
    // Start test.
    PrintWithDelay(0, KBegin, KTestCaseStopCurrentTone);         
    
    RAknSoundServerSession session = CreateNewSessionL(KSession1Uid);

    session.PlaySound(EAvkonSIDBatteryLowTone);

    // Small delay for checking that the tone starts playing.
    User::After(300000);

    session.StopSound(EAvkonSIDBatteryLowTone);
    
    PrintWithDelay(0, KNullDesC, KBatteryLowStopped);    

    // Test case passed (unfortunately there is no means to really ensure it).
    aResult.SetResult(KErrNone, KTestPassed); 

    session.Close();
    
    // End test.        
    PrintWithDelay(0, KEnd, KTestCaseStopCurrentTone);    

    // Case was executed
    return KErrNone; 
    }
    
// -----------------------------------------------------------------------------
// CAknSoundServerStifTest::TestCaseAddSidsL()
// Adds sids.
// Test case for server command "EKeySoundServerAddSIDS".
// -----------------------------------------------------------------------------
//
TInt CAknSoundServerStifTest::TestCaseAddSidsL(TTestResult& aResult)
    {
    // Default result is fail.
    aResult.SetResult(KDefaultFailCode, KTestFailed); 
        
    // Start test.
    PrintWithDelay(0, KBegin, KTestCaseAddSids);         
    
    RAknSoundServerSession session = CreateNewSessionL(KSession1Uid);

    // Simulate resource reading for the following resource:
    //
    //  RESOURCE AVKON_SOUND_INFO_LIST r_keysoundapp_sound_list
    //      {
    //      list =
    //          {
    //          AVKON_SOUND_INFO {sid=1; frequency=300;  ms=600000;},
    //          AVKON_SOUND_INFO {sid=2; frequency=600;  ms=700000;},
    //          AVKON_SOUND_INFO {sid=3; frequency=900;  ms=800000;},
    //          AVKON_SOUND_INFO {sid=4; frequency=1200; ms=900000;}
    //          };
    //      }
    //
    const TInt KAknResourceBufferSize = 512;
            
    // Package information to a buffer.
    CBufFlat* buffer = CBufFlat::NewL(KAknResourceBufferSize);
    CleanupStack::PushL(buffer);

    RBufWriteStream bufStream;
    bufStream.Open(*buffer);

    CleanupClosePushL(bufStream);

    // Take lowest 16 bits from KSession1Uid...
    TInt soundId = (KSession1Uid << 16);

    // Count
    bufStream.WriteUint16L(4);                           // count
            
    // AVKON_SOUND_INFO 1
    bufStream.WriteUint32L(soundId + 1);                 // soundId
    bufStream.WriteUint16L(EAvkonLowLevelNotesPriority); // priority
    bufStream.WriteUint32L(EAknAudioPrefDefaultTone);    // preference
    bufStream.WriteUint8L(1);                            // type 1, tone
    bufStream.WriteUint16L(300);                         // frequency
    bufStream.WriteUint32L(600000);                      // ms
    bufStream.WriteUint8L(9);                            // volume
        
    // AVKON_SOUND_INFO 2
    bufStream.WriteUint32L(soundId + 2);                 // soundId
    bufStream.WriteUint16L(EAvkonLowLevelNotesPriority); // priority
    bufStream.WriteUint32L(EAknAudioPrefDefaultTone);    // preference
    bufStream.WriteUint8L(1);                            // type 1, tone
    bufStream.WriteUint16L(600);                         // frequency
    bufStream.WriteUint32L(700000);                      // ms
    bufStream.WriteUint8L(9);                            // volume            
    
    // AVKON_SOUND_INFO 3
    bufStream.WriteUint32L(soundId + 3);                 // soundId
    bufStream.WriteUint16L(EAvkonLowLevelNotesPriority); // priority
    bufStream.WriteUint32L(EAknAudioPrefDefaultTone);    // preference
    bufStream.WriteUint8L(1);                            // type 1, tone
    bufStream.WriteUint16L(900);                         // frequency
    bufStream.WriteUint32L(800000);                      // ms
    bufStream.WriteUint8L(9);                            // volume                
    
    // AVKON_SOUND_INFO 4
    bufStream.WriteUint32L(soundId + 4);                 // soundId
    bufStream.WriteUint16L(EAvkonLowLevelNotesPriority); // priority
    bufStream.WriteUint32L(EAknAudioPrefDefaultTone);    // preference
    bufStream.WriteUint8L(1);                            // type 1, tone
    bufStream.WriteUint16L(1200);                        // frequency
    bufStream.WriteUint32L(900000);                      // ms
    bufStream.WriteUint8L(9);                            // volume              

    CleanupStack::PopAndDestroy(); // bufstream close

    TPtr8 bufPtr = buffer->Ptr(0);
    TIpcArgs args (KSession1Uid, bufPtr.Length(), &bufPtr);
    User::LeaveIfError(session.ServerRequest(EKeySoundServerAddSIDS, args)); 

    CleanupStack::PopAndDestroy();  // buffer

    // Wait for keyclick playing before starting actual test playings.
    User::After(500000);

    for (TInt i = 1; i < 5; i++)
        {
        session.PlaySound(soundId + i);
        TestModuleIf().Printf(0, KPlayingSid, KSidId, soundId + i);
        User::After(1000000);
        }

    PrintWithDelay(0, KPlayingFinished, KNullDesC);

    // Test case passed (unfortunately there is no means to really ensure it).
    aResult.SetResult(KErrNone, KTestPassed);
    
    session.Close();
        
    // End test.        
    PrintWithDelay(0, KEnd, KTestCaseAddSids);        
        
    // Case was executed
    return KErrNone; 
    }
    
// -----------------------------------------------------------------------------
// CAknSoundServerStifTest::TestCasePushContextL()
// 
// Test case for following server commands:
//    "EKeySoundServerPushContext"
//    "EKeySoundServerBringToForeground"
//    "EKeySoundServerTopContext"
//    "EKeySoundServerPopContext"
// -----------------------------------------------------------------------------
//
TInt CAknSoundServerStifTest::TestCasePushContextL(TTestResult& aResult)
    {
    // Default result is fail.
    aResult.SetResult(KDefaultFailCode, KTestFailed); 
        
    // Start test.
    PrintWithDelay(0, KBegin, KTestCasePushContext);        

    RAknSoundServerSession session = CreateNewSessionL(KSession1Uid);

    // Step 1
    if (session.TopContext() != R_AVKON_DEFAULT_SKEY_LIST)
        {
        // Test case failed.
        aResult.SetResult(KDefaultFailCode, KFirstTopContextWrong);

        session.Close();
        return KErrNone;
        }
        
    // Step 2            
    PushContextL(session, R_STIFTEST_SOUND_CONTEXT_1, KSession1Uid);
        
    // Step 3            
    session.BringToForeground();
    
    // Step 4
    if (session.TopContext() != R_STIFTEST_SOUND_CONTEXT_1)
        {
        // Test case failed.
        aResult.SetResult(KDefaultFailCode, KSecondTopContextWrong);
        
        session.Close();
        return KErrNone;            
        }
    
    // Wait for keyclick playing before starting actual test playings.
    User::After(500000);

    // Step 5 (simulate key presses to play sounds)
    for (TInt i = 1; i < 4; i++)
        {
        // Ascii characters '1' = 49, '2' = 50 and '3' = 51.
        session.KeyPressed(48 + i, EFalse);
        TestModuleIf().Printf(0, KPressingKey, KKeyId, i);
        User::After(1500000);
        }    
        
    PrintWithDelay(0, KFinished, KNullDesC);
    
    // Step 6
    session.PopContext();
    
    // Step 7
    if (session.TopContext() != R_AVKON_DEFAULT_SKEY_LIST)
        {
        // Test case failed.
        aResult.SetResult(KDefaultFailCode, KThirdTopContextWrong);                
        
        session.Close();
        return KErrNone;        
        }

    // Test case passed.
    aResult.SetResult(KErrNone, KTestPassed);
    
    session.Close();
    
    // Without this the keysounds of STIF application itself would get broken.
    iSoundServerSession.BringToForeground();    
        
    // End test.        
    PrintWithDelay(0, KEnd, KTestCasePushContext);        
        
    // Case was executed
    return KErrNone; 
    }
    
// -----------------------------------------------------------------------------
// CAknSoundServerStifTest::TestCaseLockContextL()
// 
// Test case for following server commands:
//    "EKeySoundServerLockContext"
//    "EKeySoundServerReleaseContext"
// -----------------------------------------------------------------------------
//
TInt CAknSoundServerStifTest::TestCaseLockContextL(TTestResult& aResult)
    {
    // Default result is fail.
    aResult.SetResult(KDefaultFailCode, KTestFailed); 
        
    // Start test.
    PrintWithDelay(0, KBegin, KTestCaseLockContext);

    // -------------------------------------------------------
    // In this test case we need two keysound server sessions.
    // -------------------------------------------------------
    RAknSoundServerSession session1 = CreateNewSessionL(KSession1Uid);
    RAknSoundServerSession session2 = CreateNewSessionL(KSession2Uid);

    // Step 1
    PushContextL(session1, R_STIFTEST_SOUND_CONTEXT_1, KSession1Uid);

    // Step 2
    session1.BringToForeground();
    
    // Step 3
    session1.LockContext();
    
    // Step 4
    if (session1.TopContext() != R_STIFTEST_SOUND_CONTEXT_1)
        {
        // Test case failed.
        aResult.SetResult(KDefaultFailCode, KFirstTopContextWrong);

        session1.Close();
        session2.Close();
        return KErrNone;
        }
        
    // Step 5 (change to session2)
    if (session2.TopContext() != R_STIFTEST_SOUND_CONTEXT_1)
        {
        // Test case failed.
        aResult.SetResult(KDefaultFailCode, KSecondTopContextWrong);

        session1.Close();
        session2.Close();
        return KErrNone;
        }        

    // Step 6
    PushContextL(session2, R_STIFTEST_SOUND_CONTEXT_2, KSession2Uid);
            
    // Step 7
    session2.BringToForeground();

    // Step 8            
    if (session2.TopContext() != R_STIFTEST_SOUND_CONTEXT_1)
        {
        // Test case failed.
        aResult.SetResult(KDefaultFailCode, KThirdTopContextWrong);

        session1.Close();
        session2.Close();
        return KErrNone;
        }
    
    // Step 9
    session2.PopContext();
    
    // Step 10
    if (session2.TopContext() != R_STIFTEST_SOUND_CONTEXT_1)
        {
        // Test case failed.
        aResult.SetResult(KDefaultFailCode, KFourthTopContextWrong);

        session1.Close();
        session2.Close();
        return KErrNone;
        }    

    // Step 11 (change back to session1)
    if (session1.TopContext() != R_STIFTEST_SOUND_CONTEXT_1)
        {
        // Test case failed.
        aResult.SetResult(KDefaultFailCode, KFifthTopContextWrong);

        session1.Close();
        session2.Close();
        return KErrNone;
        } 

    // Step 12
    session1.ReleaseContext();
    
    // Step 13
    session1.PopContext();           
    
    // Step 14
    if (session1.TopContext() != R_AVKON_DEFAULT_SKEY_LIST)
        {
        // Test case failed.
        aResult.SetResult(KDefaultFailCode, KSixthTopContextWrong);

        session1.Close();
        session2.Close();
        return KErrNone;
        }    
        
    // Test case passed.
    aResult.SetResult(KErrNone, KTestPassed);        
    
    session1.Close();
    session2.Close();
    
    // Without this the keysounds of STIF application itself would get broken.
    iSoundServerSession.BringToForeground();
        
    // End test.        
    PrintWithDelay(0, KEnd, KTestCaseLockContext);
        
    // Case was executed
    return KErrNone; 
    }    

// -----------------------------------------------------------------------------
// CAknSoundServerStifTest::TestCaseCloseServer()
// Tries to close the keysound server. Call should fail with KErrPermissionDenied.
// Test case for server command "EKeySoundServerCloseServer".
// -----------------------------------------------------------------------------
//
TInt CAknSoundServerStifTest::TestCaseCloseServer(TTestResult& aResult)
    {
    // Default result is fail.
    aResult.SetResult(KDefaultFailCode, KTestFailed); 
        
    // Start test.
    PrintWithDelay(0, KBegin, KTestCaseCloseServer);        

    RAknSoundServerSession session = CreateNewSessionL(KSession1Uid);
    
    // Make a direct server request. There is no method for calling close server.
    TInt err = session.ServerRequest(EKeySoundServerCloseServer, TIpcArgs());
    
    // Only calls from eiksrvs process should be accepted, so KErrPermissionDenied
    // is the expected result.
    if (err == KErrPermissionDenied)
        {
        // Test case passed.
        aResult.SetResult(KErrNone, KTestPassed);
        }
    else
        {
        aResult.SetResult(KDefaultFailCode, KInvalidReturnValue);
        }
    
    session.Close();
  
    // End test.        
    PrintWithDelay(0, KEnd, KTestCaseCloseServer);
        
    // Case was executed
    return KErrNone; 
    }

// -----------------------------------------------------------------------------
// CAknSoundServerStifTest::CreateNewSessionL()
// Convenience method for creating a new keysound server session.
// -----------------------------------------------------------------------------
//     
RAknSoundServerSession CAknSoundServerStifTest::CreateNewSessionL(TInt aSessionUid)
    {
    RAknSoundServerSession session;     
    User::LeaveIfError(session.Connect());
    
    // Connection succeeded, call Init().
    TInt init = session.Init(aSessionUid);
    if (!init)
        {
        // Initialisation failed. Close session and leave.
        session.Close();
        User::Leave(KErrUnknown);
        }
    return session;        
    }
    
// -----------------------------------------------------------------------------
// CAknSoundServerStifTest::PushContextL()
// Simulates resource reading and calls pushcontext for the given resource.
// Only R_STIFTEST_SOUND_CONTEXT_1 and R_STIFTEST_SOUND_CONTEXT_1 are supported.
// -----------------------------------------------------------------------------
//     
void CAknSoundServerStifTest::PushContextL(RAknSoundServerSession& aSession, 
    TInt aResId, TInt aSessionUid)
    {
    switch (aResId)
        {
        case R_STIFTEST_SOUND_CONTEXT_1:
            {
            // Simulates resource reading and calls pushcontext for the following context:
            // 
            //     RESOURCE AVKON_SKEY_LIST r_stiftest_sound_context_1
            //         {
            //         list=
            //             {
            //             AVKON_SKEY_INFO {key='1'; sid=EAvkonSIDReadialCompleteTone;},
            //             AVKON_SKEY_INFO {key='2'; sid=EAvkonSIDBatteryLowTone;},
            //             AVKON_SKEY_INFO {key='3'; sid=EAvkonSIDRechargeBatteryTone;}
            //             };
            //         }            
            //
            const TInt items = 3;
            const TInt resSize = (items * 5);

            CBufFlat* buffer = CBufFlat::NewL(resSize);
            CleanupStack::PushL(buffer);

            RBufWriteStream bufStream;
            bufStream.Open(*buffer);

            CleanupClosePushL(bufStream);
            
            bufStream.WriteInt16L(EAvkonSIDReadialCompleteTone); // sid
            bufStream.WriteUint16L('1');                         // key
            bufStream.WriteUint8L(ESKeyTypeShort);               // type
            
            bufStream.WriteInt16L(EAvkonSIDBatteryLowTone);      // sid 
            bufStream.WriteUint16L('2');                         // key
            bufStream.WriteUint8L(ESKeyTypeShort);               // type     
            
            bufStream.WriteInt16L(EAvkonSIDRechargeBatteryTone); // sid
            bufStream.WriteUint16L('3');                         // key
            bufStream.WriteUint8L(ESKeyTypeShort);               // type            

            CleanupStack::PopAndDestroy(); // bufstream close            
            
            TPtr8 bufPtr = buffer->Ptr(0);
            TIpcArgs args (items, &bufPtr, aSessionUid, aResId);
            User::LeaveIfError(aSession.ServerRequest(EKeySoundServerPushContext, args));
            CleanupStack::PopAndDestroy(); // buffer                
            
            break;
            }
        case R_STIFTEST_SOUND_CONTEXT_2:
            {
            // Simulates resource reading and calls pushcontext for the following context:
            // 
            //     RESOURCE AVKON_SKEY_LIST r_stiftest_sound_context_2
            //         {
            //         list=
            //             {
            //             AVKON_SKEY_INFO {key='1'; sid=EAvkonSIDVoiceRecordingTone;},
            //             AVKON_SKEY_INFO {key='2'; sid=EAvkonSIDVoiceRecordingStartTone;},
            //             AVKON_SKEY_INFO {key='3'; sid=EAvkonSIDVoiceRecordingStopTone;}
            //             };
            //         }          
            //            
            const TInt items = 3;
            const TInt resSize = (items * 5);

            CBufFlat* buffer = CBufFlat::NewL(resSize);
            CleanupStack::PushL(buffer);

            RBufWriteStream bufStream;
            bufStream.Open(*buffer);

            CleanupClosePushL(bufStream);
            
            bufStream.WriteInt16L(EAvkonSIDVoiceRecordingTone);      // sid
            bufStream.WriteUint16L('1');                             // key
            bufStream.WriteUint8L(ESKeyTypeShort);                   // type
            
            bufStream.WriteInt16L(EAvkonSIDVoiceRecordingStartTone); // sid 
            bufStream.WriteUint16L('2');                             // key
            bufStream.WriteUint8L(ESKeyTypeShort);                   // type     
            
            bufStream.WriteInt16L(EAvkonSIDVoiceRecordingStopTone);  // sid
            bufStream.WriteUint16L('3');                             // key
            bufStream.WriteUint8L(ESKeyTypeShort);                   // type            

            CleanupStack::PopAndDestroy(); // bufstream close            
            
            TPtr8 bufPtr = buffer->Ptr(0);
            TIpcArgs args (items, &bufPtr, aSessionUid, R_STIFTEST_SOUND_CONTEXT_2);
            User::LeaveIfError(aSession.ServerRequest(EKeySoundServerPushContext, args));
            CleanupStack::PopAndDestroy(); // buffer
            
            break;
            }
        default:
            {
            break;
            }
        }
    }
    
// -----------------------------------------------------------------------------
// CAknSoundServerStifTest::PrintWithDelay()
// Convenience method for printing with delay. (Printing seems to work better
// if a delay is used.)
// -----------------------------------------------------------------------------
//   
void CAknSoundServerStifTest::PrintWithDelay(const TInt aPriority, const TDesC& aDesC1, 
    const TDesC& aDesC2)  
    {
    TestModuleIf().Printf(aPriority, aDesC1, aDesC2);
    User::After(KPrintDelay);    
    }
     
//  End of File
