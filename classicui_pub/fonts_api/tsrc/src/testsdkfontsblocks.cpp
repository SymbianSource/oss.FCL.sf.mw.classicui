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
* Description:  test fonts api
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>

#include "testsdkfonts.h"



// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// Ctestsdkfonts::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestSdkFonts::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 

        ENTRY( "TestFAGetFont", CTestSdkFonts::TestFAGetFont ),
        ENTRY( "TestFAGetFontDesc", CTestSdkFonts::TestFAGetFontDesc ),
        ENTRY( "TestFAGetClosestFont", CTestSdkFonts::TestFAGetClosestFont ),
        ENTRY( "TestFAGetClosestFontDesc", CTestSdkFonts::TestFAGetClosestFontDesc ),
        ENTRY( "TestFACreateLayoutFontFromSpecificationL",CTestSdkFonts::TestFACreateLayoutFontFromSpecificationL ),
        ENTRY( "TestFACreateLayoutFontFromSpecificationTTypefaceL",CTestSdkFonts::TestFACreateLayoutFontFromSpecificationTTypefaceL ),
        
        ENTRY( "TestLFUpdateL",CTestSdkFonts::TestLFUpdateL ),
        ENTRY( "TestLFMaxAscentL",CTestSdkFonts::TestLFMaxAscentL ),
        ENTRY( "TestLFMaxDescentL",CTestSdkFonts::TestLFMaxDescentL ),
        ENTRY( "TestLFTextPaneTopToBaselineL",CTestSdkFonts::TestLFTextPaneTopToBaselineL ),
        ENTRY( "TestLFBaselineToTextPaneBottomL",CTestSdkFonts::TestLFBaselineToTextPaneBottomL ),
        ENTRY( "TestLFTextPaneHeightL",CTestSdkFonts::TestLFTextPaneHeightL ),
        ENTRY( "TestLFAscentForCharacterL",CTestSdkFonts::TestLFAscentForCharacterL ),
        ENTRY( "TestLFAsCAknLayoutFontOrNullL",CTestSdkFonts::TestLFAsCAknLayoutFontOrNullL ),
        ENTRY( "TestLFTextDecorationMetricsL",CTestSdkFonts::TestLFTextDecorationMetricsL ),
        ENTRY( "TestLFFontCategoryL",CTestSdkFonts::TestLFFontCategoryL ),
        ENTRY( "TestLFFontSpecificationL",CTestSdkFonts::TestLFFontSpecificationL ),

        ENTRY( "TestTDMTAknTextDecorationMetricsL", CTestSdkFonts::TestTDMTAknTextDecorationMetricsL ),
        ENTRY( "TestTDMTAknTextDecorationMetricsFontL", CTestSdkFonts::TestTDMTAknTextDecorationMetricsFontL ),
        ENTRY( "TestTDMTAknTextDecorationMetricsSpecL", CTestSdkFonts::TestTDMTAknTextDecorationMetricsSpecL ),
        ENTRY( "TestTDMGetLeftAndRightMarginsL", CTestSdkFonts::TestTDMGetLeftAndRightMarginsL ),
        ENTRY( "TestTDMGetTopAndBottomMarginsL", CTestSdkFonts::TestTDMGetTopAndBottomMarginsL ),
        ENTRY( "TestTDMCursorWidthL", CTestSdkFonts::TestTDMCursorWidthL ),
        ENTRY( "TestTDMBaselineToUnderlineOffsetL", CTestSdkFonts::TestTDMBaselineToUnderlineOffsetL ),
        ENTRY( "TestTDMUnderlineHeightL", CTestSdkFonts::TestTDMUnderlineHeightL ),

        // [test cases entries]

        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }



//  [End of File]
