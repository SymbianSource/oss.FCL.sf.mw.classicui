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
* Description:  test AknCustomCursorSupport.h
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <akncustomcursorsupport.h>
#include <gdi.h>
#include <aknfontcategory.hrh>

#include "testdomcustomcursors.h"

const TInt KSize = 10;

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDOMCustomCursors::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestDOMCustomCursors::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        ENTRY( "TestCCSCustomBidiTextCursorId", CTestDOMCustomCursors::TestCCSCustomBidiTextCursorId ),
        ENTRY( "TestCCSGetBidiTextCursorFromFontSpec", CTestDOMCustomCursors::TestCCSGetBidiTextCursorFromFontSpec ),
        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// =========================== CLASS AknCustomCursorSupport=====================
// -----------------------------------------------------------------------------
// CTestDOMCustomCursors::TestCCSCustomBidiTextCursorId
// -----------------------------------------------------------------------------
TInt CTestDOMCustomCursors::TestCCSCustomBidiTextCursorId( CStifItemParser& /*aItem*/ )
    {
    TRect bitmapRect( TSize( KSize, KSize ) );
    TInt id = AknCustomCursorSupport::CustomBidiTextCursorId( EAknFontCategoryPrimary, bitmapRect, ETrue );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestDOMCustomCursors::TestCCSGetBidiTextCursorFromFontSpec
// -----------------------------------------------------------------------------
TInt CTestDOMCustomCursors::TestCCSGetBidiTextCursorFromFontSpec( CStifItemParser& /*aItem*/ )
    {
    TFontSpec spec;
    TTextCursor cursor;
    TInt flag = AknCustomCursorSupport::GetBidiTextCursorFromFontSpec( spec, ETrue, cursor );
    STIF_ASSERT_TRUE( KErrNone == flag );
    
    return KErrNone;
    
    }
//  [End of File]
