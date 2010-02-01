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
* Description:  test japanese_reading_api
*
*/


// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <ptiengine.h>

#include "testdomjapanesereading.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDomJapaneseReading::TestJRCreateL
// -----------------------------------------------------------------------------
//
TInt CTestDomJapaneseReading::TestJRCreateL( CStifItemParser& /*aItem*/ ) 
{
    CPtiEngine* ptiEngine = CPtiEngine::NewL();
    CleanupStack::PushL( ptiEngine );
    STIF_ASSERT_NOT_NULL( ptiEngine );
    CAknJapaneseReading::CreateL( ptiEngine );
    CleanupStack::PopAndDestroy( ptiEngine );
    return KErrNone;
}

// -----------------------------------------------------------------------------
// CTestDomJapaneseReading::TestJRReadingTextL
// -----------------------------------------------------------------------------
//
TInt CTestDomJapaneseReading::TestJRReadingTextL( CStifItemParser& /*aItem*/ ) 
{
    CAknJapaneseReading::ReadingTextL();
    return KErrNone;
}

//END OF FILE
