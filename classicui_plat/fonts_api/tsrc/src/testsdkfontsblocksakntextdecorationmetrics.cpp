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
// CTestSdkFonts::TestTDMTAknTextDecorationMetricsL
// -----------------------------------------------------------------------------
//

TInt CTestSdkFonts::TestTDMTAknTextDecorationMetricsL(CStifItemParser& /*aItem*/)
    {
    TAknTextDecorationMetrics* textDecorationMetrics = new ( ELeave ) TAknTextDecorationMetrics( 0 );
    CleanupStack::PushL( textDecorationMetrics );
    STIF_ASSERT_NOT_NULL( textDecorationMetrics );
    CleanupStack::PopAndDestroy( textDecorationMetrics );
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSdkFonts::TestTDMTAknTextDecorationMetricsFontL
// -----------------------------------------------------------------------------
//

TInt CTestSdkFonts::TestTDMTAknTextDecorationMetricsFontL(CStifItemParser& /*aItem*/)
    {
    const CFont* afont = CEikonEnv::Static()->NormalFont();
    TAknTextDecorationMetrics* textDecorationMetrics = new ( ELeave ) TAknTextDecorationMetrics( afont );
    CleanupStack::PushL( textDecorationMetrics );
    STIF_ASSERT_NOT_NULL( textDecorationMetrics );
    CleanupStack::PopAndDestroy( textDecorationMetrics );
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestSdkFonts::TestTDMTAknTextDecorationMetricsSpecL
// -----------------------------------------------------------------------------
//

TInt CTestSdkFonts::TestTDMTAknTextDecorationMetricsSpecL(CStifItemParser& /*aItem*/)
    {
    TAknFontSpecification fontSpec( ELatinPlain12 );
    TAknTextDecorationMetrics* textDecorationMetrics = new ( ELeave ) TAknTextDecorationMetrics( fontSpec );
    CleanupStack::PushL( textDecorationMetrics );
    STIF_ASSERT_NOT_NULL( textDecorationMetrics );
    CleanupStack::PopAndDestroy( textDecorationMetrics );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSdkFonts::TestTDMGetLeftAndRightMarginsL
// -----------------------------------------------------------------------------
//

TInt CTestSdkFonts::TestTDMGetLeftAndRightMarginsL(CStifItemParser& /*aItem*/)
    {
    TAknFontSpecification fontSpec( ELatinPlain12 );
    TAknTextDecorationMetrics* textDecorationMetrics = new ( ELeave ) TAknTextDecorationMetrics( fontSpec );
    CleanupStack::PushL( textDecorationMetrics );
    TInt left( 1 ); 
    TInt right( 2 );
    textDecorationMetrics->GetLeftAndRightMargins( left,right );
    CleanupStack::PopAndDestroy( textDecorationMetrics );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSdkFonts::TestTDMGetTopAndBottomMarginsL
// -----------------------------------------------------------------------------
//

TInt CTestSdkFonts::TestTDMGetTopAndBottomMarginsL(CStifItemParser& /*aItem*/)
    {
    TAknFontSpecification fontSpec( ELatinPlain12 );
    TAknTextDecorationMetrics* textDecorationMetrics = new ( ELeave ) TAknTextDecorationMetrics( fontSpec );
    CleanupStack::PushL( textDecorationMetrics );
    TInt top( 1 ); 
    TInt bottom( 2 );
    textDecorationMetrics->GetTopAndBottomMargins( top,bottom );
    CleanupStack::PopAndDestroy( textDecorationMetrics );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSdkFonts::TestTDMCursorWidthL
// -----------------------------------------------------------------------------
//

TInt CTestSdkFonts::TestTDMCursorWidthL(CStifItemParser& /*aItem*/)
    {
    TAknFontSpecification fontSpec( ELatinPlain12 );
    TAknTextDecorationMetrics* textDecorationMetrics = new ( ELeave ) TAknTextDecorationMetrics( fontSpec );
    CleanupStack::PushL( textDecorationMetrics );
    textDecorationMetrics->CursorWidth();
    CleanupStack::PopAndDestroy( textDecorationMetrics );

    return KErrNone;
    }


// -----------------------------------------------------------------------------
// CTestSdkFonts::TestTDMBaselineToUnderlineOffsetL
// -----------------------------------------------------------------------------
//

TInt CTestSdkFonts::TestTDMBaselineToUnderlineOffsetL(CStifItemParser& /*aItem*/)
    {
    TAknFontSpecification fontSpec( ELatinPlain12 );
    TAknTextDecorationMetrics* textDecorationMetrics = new ( ELeave ) TAknTextDecorationMetrics( fontSpec );
    CleanupStack::PushL( textDecorationMetrics );
    textDecorationMetrics->BaselineToUnderlineOffset();
    CleanupStack::PopAndDestroy( textDecorationMetrics );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSdkFonts::TestTDMUnderlineHeightL
// -----------------------------------------------------------------------------
//

TInt CTestSdkFonts::TestTDMUnderlineHeightL(CStifItemParser& /*aItem*/)
    {
    TAknFontSpecification fontSpec( ELatinPlain12 );
    TAknTextDecorationMetrics* textDecorationMetrics = new ( ELeave ) TAknTextDecorationMetrics( fontSpec );
    CleanupStack::PushL( textDecorationMetrics );
    textDecorationMetrics->UnderlineHeight();
    CleanupStack::PopAndDestroy( textDecorationMetrics );

    return KErrNone;
    }



//  [End of File]
