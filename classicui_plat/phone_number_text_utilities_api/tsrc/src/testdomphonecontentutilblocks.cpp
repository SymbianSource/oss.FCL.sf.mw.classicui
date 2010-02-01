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
* Description:  Implement of function
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <e32base.h>
#include <stifparser.h>
#include <stiftestinterface.h>

#include "testdomphonecontentutil.h"

// CONSTANTS
_LIT( KPhoneNum, "1234567890" );
const TInt KBufSize = 64;
const TInt KArraySize = 10;

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDomPhoneContentUtil::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestDomPhoneContentUtil::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "TestAknPhoneNumberTextUtilsWrapToArrayL", CTestDomPhoneContentUtil::TestAknPhoneNumberTextUtilsWrapToArrayL ),
        ENTRY( "TestAknPhoneNumberTextUtilsClipLineOnLeft", CTestDomPhoneContentUtil::TestAknPhoneNumberTextUtilsClipLineOnLeft ),
        ENTRY( "TestAknPhoneNumberTextUtilsCharsThatFitOnRight", CTestDomPhoneContentUtil::TestAknPhoneNumberTextUtilsCharsThatFitOnRight ),
        
        // [test cases entries]

        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// CTestDomPhoneContentUtil::TestAknPhoneNumberTextUtilsWrapToArrayL
// -----------------------------------------------------------------------------
//
TInt CTestDomPhoneContentUtil::TestAknPhoneNumberTextUtilsWrapToArrayL( CStifItemParser& /*aItem*/ )
    {
    TBufC<KBufSize> buf( KPhoneNum );
    const CFont *font = CEikonEnv::Static()->NormalFont();
    CArrayFix<TPtrC>* array = new ( ELeave ) CArrayFixFlat<TPtrC>( KArraySize );
    CleanupStack::PushL( array );
    const TInt max = 10;
    AknPhoneNumberTextUtils::WrapPhoneNumberToArrayL(
                                                     buf,
                                                     1,
                                                     max,
                                                     *font,
                                                     *array
                                                     );
    CleanupStack::PopAndDestroy( array );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDomPhoneContentUtil::TestAknPhoneNumberTextUtilsClipLineOnLeft
// -----------------------------------------------------------------------------
//
TInt CTestDomPhoneContentUtil::TestAknPhoneNumberTextUtilsClipLineOnLeft( CStifItemParser& /*aItem*/ )
    {
    TBuf<KBufSize> buf( KPhoneNum );
    
    TPtrC ptrc = buf.Left( 2 );
    const CFont *font = CEikonEnv::Static()->NormalFont();
    AknPhoneNumberTextUtils::ClipLineOnLeft(
                                            ptrc,
                                            buf,
                                            1,
                                            *font
                                            );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDomPhoneContentUtil::TestAknPhoneNumberTextUtilsCharsThatFitOnRight
// -----------------------------------------------------------------------------
//
TInt CTestDomPhoneContentUtil::TestAknPhoneNumberTextUtilsCharsThatFitOnRight( CStifItemParser& /*aItem*/ )
    {
    TBuf<KBufSize> buf( KPhoneNum );
    const CFont *font = CEikonEnv::Static()->NormalFont();
    AknPhoneNumberTextUtils::CharsThatFitOnRight(
                                                 buf,
                                                 1,
                                                 *font
                                                 );

    return KErrNone;

    }

//  [End of File]
