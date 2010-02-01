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
* Description:  test function implement of CTestDomExtAnimation
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>

#include "testdomextanimation.h"


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDomExtAnimation::RunMethodL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAnimation::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function.

        // For TAnimStep in aknAnimData.h
        ENTRY( "TestTAnimStepTAnimStepL",
                CTestDomExtAnimation::TestTAnimStepTAnimStepL ),
        ENTRY( "TestTAnimStepLineDrawStep",
                CTestDomExtAnimation::TestTAnimStepLineDrawStep ),
        ENTRY( "TestTAnimStepBlitStep",
                CTestDomExtAnimation::TestTAnimStepBlitStep ),
        ENTRY( "TestTAnimStepSetColorStep",
                CTestDomExtAnimation::TestTAnimStepSetColorStep ),
        ENTRY( "TestTAnimStepSlideStep",
                CTestDomExtAnimation::TestTAnimStepSlideStep ),
        ENTRY( "TestTAnimStepWaitStep",
                CTestDomExtAnimation::TestTAnimStepWaitStep ),
        ENTRY( "TestTAnimStepSetType",
                CTestDomExtAnimation::TestTAnimStepSetType ),
        ENTRY( "TestTAnimStepType",
                CTestDomExtAnimation::TestTAnimStepType ),

        // For TAnimMultiStep in aknAnimData.h
        ENTRY( "TestTAnimMultiStepTAnimMultiStepL",
                CTestDomExtAnimation::TestTAnimMultiStepTAnimMultiStepL ),

        // For CAknAnimationData in aknAnimData.h
        ENTRY( "TestCAknAnimDataCAknAnimationDataL",
                CTestDomExtAnimation::TestCAknAnimDataCAknAnimationDataL ),
        ENTRY( "TestCAknAnimDataConstructFromResourceL",
                CTestDomExtAnimation::TestCAknAnimDataConstructFromResourceL ),
        ENTRY( "TestCAknAnimDataSetScreenSizeL",
                CTestDomExtAnimation::TestCAknAnimDataSetScreenSizeL ),
        ENTRY( "TestCAknAnimDataSetViewBitmapL",
                CTestDomExtAnimation::TestCAknAnimDataSetViewBitmapL ),
        ENTRY( "TestCAknAnimDataSetOldBitmapL",
                CTestDomExtAnimation::TestCAknAnimDataSetOldBitmapL ),
        ENTRY( "TestCAknAnimDataSetClearOldViewL",
                CTestDomExtAnimation::TestCAknAnimDataSetClearOldViewL ),
        ENTRY( "TestCAknAnimDataClearOldViewL",
                CTestDomExtAnimation::TestCAknAnimDataClearOldViewL ),
        ENTRY( "TestCAknAnimDataWaitBetweenSectionsL",
                CTestDomExtAnimation::TestCAknAnimDataWaitBetweenSectionsL ),
        ENTRY( "TestCAknAnimDataSetWaitForeverAtEndL",
                CTestDomExtAnimation::TestCAknAnimDataSetWaitForeverAtEndL ),
        ENTRY( "TestCAknAnimDataWaitForeverAtEndL",
                CTestDomExtAnimation::TestCAknAnimDataWaitForeverAtEndL ),
        ENTRY( "TestCAknAnimDataDrawNextAnimationStepL",
                CTestDomExtAnimation::TestCAknAnimDataDrawNextAnimationStepL ),
        ENTRY( "TestCAknAnimDataIntervalL",
                CTestDomExtAnimation::TestCAknAnimDataIntervalL ),
        ENTRY( "TestCAknAnimDataConstructL",
                CTestDomExtAnimation::TestCAknAnimDataConstructL ),

        // For CAknAnimatedView in aknAnimView.h
        ENTRY( "TestCAknAnimViewCAknAnimatedViewL",
                CTestDomExtAnimation::TestCAknAnimViewCAknAnimatedViewL ),
        ENTRY( "TestCAknAnimViewSetAnimationDataL",
                CTestDomExtAnimation::TestCAknAnimViewSetAnimationDataL ),
        ENTRY( "TestCAknAnimViewAknViewActivatedL",
                CTestDomExtAnimation::TestCAknAnimViewAknViewActivatedL ),
        ENTRY( "TestCAknAnimViewPreAnimateSetupL",
                CTestDomExtAnimation::TestCAknAnimViewPreAnimateSetupL ),
        ENTRY( "TestCAknAnimViewPostAnimateSetupL",
                CTestDomExtAnimation::TestCAknAnimViewPostAnimateSetupL ),
        ENTRY( "TestCAknAnimViewSwapListBoxGcL",
                CTestDomExtAnimation::TestCAknAnimViewSwapListBoxGcL ),

        // [test cases entries]

        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }


//  [End of File]
