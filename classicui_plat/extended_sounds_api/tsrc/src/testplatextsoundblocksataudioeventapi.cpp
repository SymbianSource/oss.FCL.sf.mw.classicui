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
* Description:  Test eikkeysound.h
*
*/

// [INCLUDE FILES]
#include "testplatextsound.h"

// FORWARD
class CTestObserver : public CBase, public MATEventCompleteObserver
    {
    public:
        /*Constructor*/
        CTestObserver(){}
        /*Deconstructor*/
        ~CTestObserver(){}
        /**
        * Callback function for client API to call.
        */
        void Complete( TInt /*aError*/, TAudioThemeEvent /*aEvent*/ ){}

    };

// ============================ MEMBER FUNCTIONS =========================


// --------------------------------------------------------------------------
// CTestPlatExtSound::TestCATAudioEventAPINewL
// --------------------------------------------------------------------------
//
TInt CTestPlatExtSound::TestCATAudioEventAPINewL( CStifItemParser& /*aItem*/ )
    {
    _LIT(Kctestplatextsound, "CTestPlatExtSound");
    _LIT(Ktestcataudioeventapinewl, "In TestCATAudioEventAPINewL");
    TestModuleIf().Printf(0, Kctestplatextsound, Ktestcataudioeventapinewl);
    iLog->Log(Ktestcataudioeventapinewl);

    CTestObserver* ob = new ( ELeave ) CTestObserver;
    CleanupStack::PushL( ob );
    CATAudioEventAPI* temp = CATAudioEventAPI::NewL( *ob );
    CleanupStack::PushL( temp );
    CleanupStack::PopAndDestroy( temp );
    CleanupStack::PopAndDestroy( ob );

    return KErrNone;
    }

// --------------------------------------------------------------------------
// CTestPlatExtSound::TestCATAudioEventAPINewLCL
// --------------------------------------------------------------------------
//
TInt CTestPlatExtSound::TestCATAudioEventAPINewLCL( CStifItemParser& /*aItem*/ )
    {
    _LIT(Kctestplatextsound, "CTestPlatExtSound");
    _LIT(Ktestcataudioeventapinewlcl, "In TestCATAudioEventAPINewLCL");
    TestModuleIf().Printf(0, Kctestplatextsound, Ktestcataudioeventapinewlcl);
    iLog->Log(Ktestcataudioeventapinewlcl);

    CTestObserver* ob = new ( ELeave ) CTestObserver;
    CleanupStack::PushL( ob );
    CATAudioEventAPI* temp = CATAudioEventAPI::NewLC( *ob );
    CleanupStack::PopAndDestroy( temp );
    CleanupStack::PopAndDestroy( ob );

    return KErrNone;
    }


