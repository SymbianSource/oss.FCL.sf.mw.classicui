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
* Description:  Test EIKLABEL.H, eikfnlab.h
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>

#include "testsdklabels.h"


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKLabels::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void CTestSDKLabels::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// CTestSDKLabels::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestSDKLabels::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {
        //eikfnlab.h
        ENTRY( "TestLCEikFileNameLabelL", CTestSDKLabels::TestLCEikFileNameLabelL ),
        ENTRY( "TestLDeconstructorL", CTestSDKLabels::TestLDeconstructorL ),
        ENTRY( "TestLConstructL", CTestSDKLabels::TestLConstructL ),
        ENTRY( "TestLUpdateL", CTestSDKLabels::TestLUpdateL ),
        ENTRY( "TestLGetColorUseListL", CTestSDKLabels::TestLGetColorUseListL ),
        ENTRY( "TestLHandleResourceChangeL", CTestSDKLabels::TestLHandleResourceChangeL ),
        ENTRY( "TestLMinimumSizeL", CTestSDKLabels::TestLMinimumSizeL ),
        ENTRY( "TestLHandlePointerEventL", CTestSDKLabels::TestLHandlePointerEventL ),
        ENTRY( "TestLDrawL", CTestSDKLabels::TestLDrawL ),
        
        //EIKLABEL.H
        ENTRY( "TestLabelDeconstructorL", CTestSDKLabels::TestLabelDeconstructorL ),
        ENTRY( "TestLabelCEikLabelL", CTestSDKLabels::TestLabelCEikLabelL ),
        ENTRY( "TestLabelSetLabelAlignmentL", CTestSDKLabels::TestLabelSetLabelAlignmentL ),
        ENTRY( "TestLabelSetBrushStyleL", CTestSDKLabels::TestLabelSetBrushStyleL ),
        ENTRY( "TestLabelSetBrushStyleFromContextL", CTestSDKLabels::TestLabelSetBrushStyleFromContextL ),
        ENTRY( "TestLabelMinimumSizeL", CTestSDKLabels::TestLabelMinimumSizeL ),
        ENTRY( "TestLabelConstructFromResourceL", CTestSDKLabels::TestLabelConstructFromResourceL ),
        ENTRY( "TestLabelGetColorUseListL", CTestSDKLabels::TestLabelGetColorUseListL ),
        ENTRY( "TestLabelHandleResourceChangeL", CTestSDKLabels::TestLabelHandleResourceChangeL ),
        ENTRY( "TestLabelDrawL", CTestSDKLabels::TestLabelDrawL ),
        ENTRY( "TestLabelSetTextL", CTestSDKLabels::TestLabelSetTextL ),
        ENTRY( "TestLabelTextL", CTestSDKLabels::TestLabelTextL ),
        ENTRY( "TestLabelCropTextL", CTestSDKLabels::TestLabelCropTextL ),
        ENTRY( "TestLabelSetBufferReserveLengthL", CTestSDKLabels::TestLabelSetBufferReserveLengthL ),
        ENTRY( "TestLabelSetFontL", CTestSDKLabels::TestLabelSetFontL ),
        ENTRY( "TestLabelFontL", CTestSDKLabels::TestLabelFontL ),
        ENTRY( "TestLabelSetEmphasisL", CTestSDKLabels::TestLabelSetEmphasisL ),
        ENTRY( "TestLabelSetPixelGapBetweenLinesL", CTestSDKLabels::TestLabelSetPixelGapBetweenLinesL ),
        ENTRY( "TestLabelPixelGapBetweenLinesL", CTestSDKLabels::TestLabelPixelGapBetweenLinesL ),
        ENTRY( "TestLabelIsUnderlinedL", CTestSDKLabels::TestLabelIsUnderlinedL ),
        ENTRY( "TestLabelSetUnderliningL", CTestSDKLabels::TestLabelSetUnderliningL ),
        ENTRY( "TestLabelIsStrikethroughL", CTestSDKLabels::TestLabelIsStrikethroughL ),
        ENTRY( "TestLabelSetStrikethroughL", CTestSDKLabels::TestLabelSetStrikethroughL ),
        ENTRY( "TestLabelCalcMinimumSizeL", CTestSDKLabels::TestLabelCalcMinimumSizeL ),
        ENTRY( "TestLabelNumberOfLinesL", CTestSDKLabels::TestLabelNumberOfLinesL ),
        ENTRY( "TestLabelBufferReserveLengthL", CTestSDKLabels::TestLabelBufferReserveLengthL ),
        ENTRY( "TestLabelUseLogicalToVisualConversionL", CTestSDKLabels::TestLabelUseLogicalToVisualConversionL ),
        ENTRY( "TestLabelLogicalToVisualConversionUsedL", CTestSDKLabels::TestLabelLogicalToVisualConversionUsedL ),
        ENTRY( "TestLabelEnablePictographsL", CTestSDKLabels::TestLabelEnablePictographsL ),
        ENTRY( "TestLabelDisablePictographsL", CTestSDKLabels::TestLabelDisablePictographsL ),
        ENTRY( "TestLabelHandlePointerEventL", CTestSDKLabels::TestLabelHandlePointerEventL ),
        ENTRY( "TestLabelWriteInternalStateL", CTestSDKLabels::TestLabelWriteInternalStateL ),

        // [test cases entries]

        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

//  [End of File]
