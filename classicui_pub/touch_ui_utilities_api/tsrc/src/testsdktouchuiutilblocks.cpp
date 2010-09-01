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
* Description:  test function implement of CTestSDKTouchUiUtil
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>

#include "testsdktouchuiutil.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKTouchUiUtil::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestSDKTouchUiUtil::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "TestCAknLongTapDetectorNewL", CTestSDKTouchUiUtil::TestCAknLongTapDetectorNewL ),
        ENTRY( "TestCAknLongTapDetectorNewLC", CTestSDKTouchUiUtil::TestCAknLongTapDetectorNewLC ),
        ENTRY( "TestCAknLongTapDetectorPointerEventL", CTestSDKTouchUiUtil::TestCAknLongTapDetectorPointerEventL ),
        ENTRY( "TestCAknLongTapDetectorSetTimeDelayBeforeAnimationL", CTestSDKTouchUiUtil::TestCAknLongTapDetectorSetTimeDelayBeforeAnimationL ),
        ENTRY( "TestCAknLongTapDetectorSetLongTapDelayL", CTestSDKTouchUiUtil::TestCAknLongTapDetectorSetLongTapDelayL ),
        ENTRY( "TestCAknLongTapDetectorEnableLongTapAnimationL", CTestSDKTouchUiUtil::TestCAknLongTapDetectorEnableLongTapAnimationL ),
        ENTRY( "TestCAknLongTapDetectorIsAnimationRunningL", CTestSDKTouchUiUtil::TestCAknLongTapDetectorIsAnimationRunningL ),
        ENTRY( "TestCAknLongTapDetectorCancelAnimationL", CTestSDKTouchUiUtil::TestCAknLongTapDetectorCancelAnimationL ),
        ENTRY( "TestCAknPointerSuppressorNewL", CTestSDKTouchUiUtil::TestCAknPointerSuppressorNewL ),
        ENTRY( "TestCAknPointerSuppressorSuppressPointerEventL", CTestSDKTouchUiUtil::TestCAknPointerSuppressorSuppressPointerEventL ),
        ENTRY( "TestCAknPointerSuppressorSetMaxTapDurationL", CTestSDKTouchUiUtil::TestCAknPointerSuppressorSetMaxTapDurationL ),
        ENTRY( "TestCAknPointerSuppressorSetMaxTapMoveL", CTestSDKTouchUiUtil::TestCAknPointerSuppressorSetMaxTapMoveL ),
        ENTRY( "TestCAknPointerSuppressorSetMinInterDragIntervalL", CTestSDKTouchUiUtil::TestCAknPointerSuppressorSetMinInterDragIntervalL ),
        
        // [test cases entries]
        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }


//  [End of File]
