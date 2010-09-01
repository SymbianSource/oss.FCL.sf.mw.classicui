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

#include "testdomjapanesereading.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDomJapaneseReading::TestRCNewL
// -----------------------------------------------------------------------------
//
TInt CTestDomJapaneseReading::TestRCNewL( CStifItemParser& /*aItem*/ ) 
    {
    CReadingConverter* rdconver = CReadingConverter::NewL();
    CleanupStack::PushL( rdconver );
    STIF_ASSERT_NOT_NULL( rdconver );
    CleanupStack::PopAndDestroy( rdconver );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomJapaneseReading::TestRCNewCEikEdwinL
// -----------------------------------------------------------------------------
//
TInt CTestDomJapaneseReading::TestRCNewCEikEdwinL( CStifItemParser& /*aItem*/ ) 
    {
    CEikEdwin* maineditor = NULL;
    CReadingConverter*rdconver = CReadingConverter::NewL( *maineditor, *maineditor );
    CleanupStack::PushL( rdconver );
    STIF_ASSERT_NOT_NULL( rdconver );
    CleanupStack::PopAndDestroy( rdconver );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomJapaneseReading::TestRCHandleCompletionOfTransactionL
// -----------------------------------------------------------------------------
//
TInt CTestDomJapaneseReading::TestRCHandleCompletionOfTransactionL( CStifItemParser& /*aItem*/ ) 
    {
    CEikEdwin* maineditor = NULL;
    CReadingConverter*rdconver = CReadingConverter::NewL( *maineditor, *maineditor );
    CleanupStack::PushL( rdconver );
    STIF_ASSERT_NOT_NULL( rdconver );
    rdconver->HandleCompletionOfTransactionL();
    CleanupStack::PopAndDestroy( rdconver );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomJapaneseReading::TestRCSetMainEditorL
// -----------------------------------------------------------------------------
//
TInt CTestDomJapaneseReading::TestRCSetMainEditorL( CStifItemParser& /*aItem*/ ) 
    {
    CEikEdwin* maineditor = NULL;
    CReadingConverter*rdconver = CReadingConverter::NewL( *maineditor, *maineditor );
    CleanupStack::PushL( rdconver );
    STIF_ASSERT_NOT_NULL( rdconver );
    rdconver->SetMainEditor( *maineditor );
    CleanupStack::PopAndDestroy( rdconver );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomJapaneseReading::TestRCMainEditorL
// -----------------------------------------------------------------------------
//
TInt CTestDomJapaneseReading::TestRCMainEditorL( CStifItemParser& /*aItem*/ ) 
    {
    CEikEdwin* maineditor = NULL;
    CReadingConverter*rdconver = CReadingConverter::NewL( *maineditor, *maineditor );
    CleanupStack::PushL( rdconver );
    STIF_ASSERT_NOT_NULL( rdconver );
    rdconver->MainEditor();
    CleanupStack::PopAndDestroy( rdconver );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomJapaneseReading::TestRCSetReadingEditorL
// -----------------------------------------------------------------------------
//
TInt CTestDomJapaneseReading::TestRCSetReadingEditorL( CStifItemParser& /*aItem*/ ) 
    {
    CEikEdwin* maineditor = NULL;
    CReadingConverter*rdconver = CReadingConverter::NewL( *maineditor, *maineditor );
    CleanupStack::PushL( rdconver );
    STIF_ASSERT_NOT_NULL( rdconver );
    rdconver->SetReadingEditor( *maineditor );
    CleanupStack::PopAndDestroy( rdconver );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomJapaneseReading::TestRCReadingEditorL
// -----------------------------------------------------------------------------
//
TInt CTestDomJapaneseReading::TestRCReadingEditorL( CStifItemParser& /*aItem*/ ) 
    {
    CEikEdwin* maineditor = NULL;
    CReadingConverter*rdconver = CReadingConverter::NewL( *maineditor, *maineditor );
    CleanupStack::PushL( rdconver );
    STIF_ASSERT_NOT_NULL( rdconver );
    rdconver->ReadingEditor();
    CleanupStack::PopAndDestroy( rdconver );
    return KErrNone;
    }

// End of File
