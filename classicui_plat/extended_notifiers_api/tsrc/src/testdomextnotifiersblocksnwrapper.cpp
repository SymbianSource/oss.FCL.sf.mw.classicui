/*
* Copyright (c) 2002 - 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  test functions for testing AknNotifierWrapper.h
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <aknnotifierwrapper.h>
#include <aknnotifierwrapperdefs.h>
#include <aknnotifystd.h>
#include <btmanclient.h>
#include <aknnotewrappers.h>
#include <bttypes.h>

#include "testdomextnotifiers.h"

// CONSTANTS
const TUid KTestUid = { 0x90000001 };
const TInt KGeneralBufferLength = 32;

// FORWARD DECLARATION
// CTestMAknNotifierWrapper for testing MAknNotifierWrapper
class CTestMAknNotifierWrapper : public CBase, public MAknNotifierWrapper
    {
public:
    // Constructor
    CTestMAknNotifierWrapper() : CBase() {}
    
    // from MAknNotifierWrapper
    TPtrC8 UpdateNotifierL( TUid /*aNotifierUid*/, const TDesC8& /*aBuffer*/)
        { return NULL; }
    
    // from MAknNotifierWrapper
    void CancelNotifier( TUid /*aNotifierUid*/ ) {}
    
    // from MAknNotifierWrapper
    void StartNotifierL(  TUid /*aNotifierUid*/, const TDesC8& /*aBuffer*/,
                    TInt /*aReplySlot*/, const RMessagePtr2& /*aMessage*/ ) {}
    
    // from MAknNotifierWrapper
    TPtrC8 StartNotifierL( TUid /*aNotifierUid*/, const TDesC8& /*aBuffer*/)
        { return NULL; }
    
    // from MAknNotifierWrapper
    const TUid& AppServerUid() const { return KTestUid; }
    
    // from MAknNotifierWrapper
    TPtr8 SynchronousReplyBuf() { TPtr8 ptr( 0, 0 ); return ptr; }
    
    // from MAknNotifierWrapper
    void AsyncMessageCompleted( CAknNotifierMessageObserver* /*aEntry*/ ) {}
    
    // from MAknNotifierWrapper
    void UpdateNotifierL(  TUid aNotifierUid, const TDesC8& aBuffer,
                        TInt aReplySlot, const RMessagePtr2& aMessage )
        {
        MAknNotifierWrapper::UpdateNotifierL( aNotifierUid, aBuffer, aReplySlot, aMessage );
        }
    };

// CTestMAknNotifierCustomSecurityCheck for testing CAknCommonNotifierWrapper
class CTestMAknNotifierCustomSecurityCheck : public CBase , public MAknNotifierCustomSecurityCheck
    {
public:
    // Constructor
    CTestMAknNotifierCustomSecurityCheck() : CBase() {}
    
    // from MAknNotifierCustomSecurityCheck
    void Release() {};
    
    // from MAknNotifierCustomSecurityCheck
    void CustomSecurityCheckL(const RMessagePtr2& /*aMessage*/) {};
    };


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDomExtNotifiers::TestMANWUpdateNotifierL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtNotifiers::TestMANWUpdateNotifierL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtNotifiers, "TestDomExtNotifiers" );
    _LIT( KTestCAknADNNewL, "TestCAknADNNewL" );
    TestModuleIf().Printf( 0, KTestDomExtNotifiers, KTestCAknADNNewL );
    // Print to log file
    iLog->Log( KTestCAknADNNewL );
    
    CTestMAknNotifierWrapper* testWrapper = new ( ELeave ) CTestMAknNotifierWrapper();
    CleanupStack::PushL( testWrapper );
    
    RMessagePtr2 msgPtr2;
    TBuf8<32> buf;
    TRAPD( err, testWrapper->UpdateNotifierL( TUid::Null(), buf, 1, msgPtr2 ) );
    STIF_ASSERT_EQUALS( err, KErrNotSupported ); 
    
    CleanupStack::PopAndDestroy( testWrapper );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtNotifiers::TestCANMONewServerRequestL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtNotifiers::TestCANMONewServerRequestL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtNotifiers, "TestDomExtNotifiers" );
    _LIT( KTestCANMONewServerRequestL, "TestCANMONewServerRequestL" );
    TestModuleIf().Printf( 0, KTestDomExtNotifiers, KTestCANMONewServerRequestL );
    // Print to log file
    iLog->Log( KTestCANMONewServerRequestL );
    
    CTestMAknNotifierWrapper* wrapper = new ( ELeave ) CTestMAknNotifierWrapper();
    CleanupStack::PushL( wrapper );
    RMessagePtr2 msgPtr2;
    
    CAknNotifierMessageObserver* observer =
            CAknNotifierMessageObserver::NewServerRequestL( KAknNotifierServiceUid, wrapper, msgPtr2, 1 );
    CleanupStack::PushL( observer );
    
    STIF_ASSERT_NOT_NULL( observer );
    
    CleanupStack::PopAndDestroy( observer );
    CleanupStack::PopAndDestroy( wrapper );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtNotifiers::TestCANWLCAknNotifierWrapperLightL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtNotifiers::TestCANWLCAknNotifierWrapperLightL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtNotifiers, "TestDomExtNotifiers" );
    _LIT( KTestCANWLCAknNotifierWrapperLightL, "TestCANWLCAknNotifierWrapperLightL" );
    TestModuleIf().Printf( 0, KTestDomExtNotifiers, KTestCANWLCAknNotifierWrapperLightL );
    // Print to log file
    iLog->Log( KTestCANWLCAknNotifierWrapperLightL );
    
    CAknNotifierWrapper* wrapper =
                CAknNotifierWrapper::NewL( KAknNotifierServiceUid,
                        KAknNotifierServiceUid, 0, KCommonNotifierAppSrvUid, 0 );
    CleanupStack::PushL( wrapper );
    
    CAknNotifierWrapperLight* light =
                new ( ELeave ) CAknNotifierWrapperLight( *wrapper,
                        KAknNotifierServiceUid, KAknNotifierServiceUid, 1 );
    CleanupStack::PushL( light );
    
    STIF_ASSERT_NOT_NULL( light );
    
    CleanupStack::PopAndDestroy( light );
    CleanupStack::Pop( wrapper );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtNotifiers::TestCANWLMostFunction1L
// -----------------------------------------------------------------------------
//
TInt CTestDomExtNotifiers::TestCANWLMostFunction1L( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtNotifiers, "TestDomExtNotifiers" );
    _LIT( KTestCANWLMostFunction1L, "TestCANWLMostFunction1L" );
    TestModuleIf().Printf( 0, KTestDomExtNotifiers, KTestCANWLMostFunction1L );
    // Print to log file
    iLog->Log( KTestCANWLMostFunction1L );
    
    TBTAuthorisationParamsPckg pckg;
    pckg().iBDAddr = TInt64(0x12345678);
    pckg().iUid.iUid = 0xabcd1234;
    TPckgBuf<TBool> resultPckg;
 
    RNotifier not1;
    User::LeaveIfError(not1.Connect());
    TRequestStatus stat;
    not1.StartNotifierAndGetResponse(stat, KBTManAuthNotifierUid, pckg, resultPckg);
    User::WaitForRequest(stat);
    
    // Now send device name.
    TBuf<16> name16 = _L("Nigel's Dongle");
    TBTNotifierUpdateParamsPckg updpckg;
    updpckg().iName = name16;
    updpckg().iResult = KErrNone;
 
    TBuf8<1> answer;
    TInt err = not1.UpdateNotifier(KBTManAuthNotifierUid, updpckg, answer);
    if (err)
        {
        TBuf<20> error(_L("Error:"));
        error.AppendNum(err);
        CAknInformationNote* note = new(ELeave)CAknInformationNote( ETrue );
        note->ExecuteLD(error);
        }
    User::WaitForRequest(stat);
    not1.CancelNotifier(KBTManAuthNotifierUid);
    not1.Close();
 
    TBuf<60> resultbuf(_L("Authorisation Complete:"));
    resultbuf.Zero();
    if (resultPckg())
        {
        resultbuf.Append(_L("Accepted"));
        }
    else
        {
        resultbuf.Append(_L("Denied"));
        }
 
    CAknInformationNote* note = new(ELeave)CAknInformationNote( ETrue );
    note->ExecuteLD(resultbuf);

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtNotifiers::TestCANWLMostFunction2L
// -----------------------------------------------------------------------------
//
TInt CTestDomExtNotifiers::TestCANWLMostFunction2L( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtNotifiers, "TestDomExtNotifiers" );
    _LIT( KTestCANWLMostFunction2L, "TestCANWLMostFunction2L" );
    TestModuleIf().Printf( 0, KTestDomExtNotifiers, KTestCANWLMostFunction2L );
    // Print to log file
    iLog->Log( KTestCANWLMostFunction2L );
    
    TBTAuthorisationParamsPckg pckg;
    pckg().iBDAddr = TInt64(0x12345678);
    pckg().iUid.iUid = 0xabcd1234;
    TPckgBuf<TBool> resultPckg;
 
    RNotifier not1;
    User::LeaveIfError(not1.Connect());
    TRequestStatus stat;
    not1.StartNotifierAndGetResponse(stat, KBTManAuthNotifierUid, pckg, resultPckg);
    User::WaitForRequest(stat);
    
    // Now send device name.
    TBuf<16> name16 = _L("Nigel's Dongle");
    TBTNotifierUpdateParamsPckg updpckg;
    updpckg().iName = name16;
    updpckg().iResult = KErrNone;
 
    TBuf8<1> answer;
    TInt err = not1.UpdateNotifier(KBTManAuthNotifierUid, updpckg, answer);
    if (err)
        {
        TBuf<20> error(_L("Error:"));
        error.AppendNum(err);
        CAknInformationNote* note = new(ELeave)CAknInformationNote( ETrue );
        note->ExecuteLD(error);
        }
    User::WaitForRequest(stat);
    not1.CancelNotifier(KBTManAuthNotifierUid);
    not1.Close();
 
    TBuf<60> resultbuf(_L("Authorisation Complete:"));
    resultbuf.Zero();
    if (resultPckg())
        {
        resultbuf.Append(_L("Accepted"));
        }
    else
        {
        resultbuf.Append(_L("Denied"));
        }
 
    CAknInformationNote* note = new(ELeave)CAknInformationNote( ETrue );
    note->ExecuteLD(resultbuf);
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtNotifiers::TestCANWLMostFunction3L
// -----------------------------------------------------------------------------
//
TInt CTestDomExtNotifiers::TestCANWLMostFunction3L( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtNotifiers, "TestDomExtNotifiers" );
    _LIT( KTestCANWLMostFunction3L, "TestCANWLMostFunction3L" );
    TestModuleIf().Printf( 0, KTestDomExtNotifiers, KTestCANWLMostFunction3L );
    // Print to log file
    iLog->Log( KTestCANWLMostFunction3L );
    
    TBTAuthorisationParamsPckg pckg;
    pckg().iBDAddr = TInt64(0x12345678);
    pckg().iUid.iUid = 0xabcd1234;
    TPckgBuf<TBool> resultPckg;
 
    RNotifier not1;
    User::LeaveIfError(not1.Connect());
    TRequestStatus stat;
    not1.StartNotifierAndGetResponse(stat, KBTManAuthNotifierUid, pckg, resultPckg);
    User::WaitForRequest(stat);
    
    // Now send device name.
    TBuf<16> name16 = _L("Nigel's Dongle");
    TBTNotifierUpdateParamsPckg updpckg;
    updpckg().iName = name16;
    updpckg().iResult = KErrNone;
 
    TBuf8<1> answer;
    TInt err = not1.UpdateNotifier(KBTManAuthNotifierUid, updpckg, answer);
    if (err)
        {
        TBuf<20> error(_L("Error:"));
        error.AppendNum(err);
        CAknInformationNote* note = new(ELeave)CAknInformationNote( ETrue );
        note->ExecuteLD(error);
        }
    User::WaitForRequest(stat);
    not1.CancelNotifier(KBTManAuthNotifierUid);
    not1.Close();
 
    TBuf<60> resultbuf(_L("Authorisation Complete:"));
    resultbuf.Zero();
    if (resultPckg())
        {
        resultbuf.Append(_L("Accepted"));
        }
    else
        {
        resultbuf.Append(_L("Denied"));
        }
 
    CAknInformationNote* note = new(ELeave)CAknInformationNote( ETrue );
    note->ExecuteLD(resultbuf);
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtNotifiers::TestCANWLStartWithRetL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtNotifiers::TestCANWLStartWithRetL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtNotifiers, "TestDomExtNotifiers" );
    _LIT( KTestCANWLStartWithRetL, "TestCANWLStartWithRetL" );
    TestModuleIf().Printf( 0, KTestDomExtNotifiers, KTestCANWLStartWithRetL );
    // Print to log file
    iLog->Log( KTestCANWLStartWithRetL );
    
    TBuf8<KGeneralBufferLength> buffer;
    TBuf8<KGeneralBufferLength> responseBuffer;
    
    RNotifier notify;
    User::LeaveIfError( notify.Connect() );
    
    //Call StartL() function.
    notify.StartNotifier( KAknGlobalNoteUid,
        buffer, responseBuffer);
    
    notify.UpdateNotifier( KAknGlobalNoteUid,
        buffer, responseBuffer );
    
    notify.CancelNotifier( KAknGlobalNoteUid );
    notify.Close();
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtNotifiers::TestCANWLInfoL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtNotifiers::TestCANWLInfoL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtNotifiers, "TestDomExtNotifiers" );
    _LIT( KTestCANWLInfoL, "TestCANWLInfoL" );
    TestModuleIf().Printf( 0, KTestDomExtNotifiers, KTestCANWLInfoL );
    // Print to log file
    iLog->Log( KTestCANWLInfoL );
    
    TBuf8<KGeneralBufferLength> buffer;
    TBuf8<KGeneralBufferLength> responseBuffer;
    
    RNotifier notify;
    User::LeaveIfError( notify.Connect() );
    
    //Call Info() function.
    notify.StartNotifier( KAknGlobalNoteUid,
        buffer, responseBuffer);
    
    notify.UpdateNotifier( KAknGlobalNoteUid,
        buffer, responseBuffer );
    
    notify.CancelNotifier( KAknGlobalNoteUid );
    notify.Close();
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtNotifiers::TestCANWStartNotifierWithRetL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtNotifiers::TestCANWStartNotifierWithRetL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtNotifiers, "TestDomExtNotifiers" );
    _LIT( KTestCANWStartNotifierWithRetL, "TestCANWStartNotifierWithRetL" );
    TestModuleIf().Printf( 0, KTestDomExtNotifiers, KTestCANWStartNotifierWithRetL );
    // Print to log file
    iLog->Log( KTestCANWStartNotifierWithRetL );
    
    TBuf8<KGeneralBufferLength> buffer;
    TBuf8<KGeneralBufferLength> responseBuffer;
    
    RNotifier notify;
    User::LeaveIfError( notify.Connect() );
    
    //Call StartL() function.
    notify.StartNotifier( KAknGlobalNoteUid,
        buffer, responseBuffer);
    
    notify.UpdateNotifier( KAknGlobalNoteUid,
        buffer, responseBuffer );
    
    notify.CancelNotifier( KAknGlobalNoteUid );
    notify.Close();
    
    return KErrNone;
    }


//  [End of File]









