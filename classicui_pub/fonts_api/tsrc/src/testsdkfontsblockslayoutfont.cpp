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
// CTestSdkFonts::TestLFUpdateL
// -----------------------------------------------------------------------------
//

TInt CTestSdkFonts::TestLFUpdateL(CStifItemParser& /*aItem*/)
    {
    TAknFontSpecification fontSpec( ELatinPlain12 );
    CAknLayoutFont* layoutFont = AknLayoutUtils::
        CreateLayoutFontFromSpecificationL( fontSpec ); 
    layoutFont->Update();
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSdkFonts::TestLFMaxAscentL
// -----------------------------------------------------------------------------
//

TInt CTestSdkFonts::TestLFMaxAscentL(CStifItemParser& /*aItem*/)
    {
    TAknFontSpecification fontSpec( ELatinPlain12 );
    CAknLayoutFont* layoutFont = AknLayoutUtils::
                                CreateLayoutFontFromSpecificationL( fontSpec ); 
    layoutFont->MaxAscent();
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSdkFonts::TestLFMaxDescentL
// -----------------------------------------------------------------------------
//

TInt CTestSdkFonts::TestLFMaxDescentL(CStifItemParser& /*aItem*/)
    {
    TAknFontSpecification fontSpec( ELatinPlain12 );
    CAknLayoutFont* layoutFont = AknLayoutUtils::
        CreateLayoutFontFromSpecificationL( fontSpec ); 
    layoutFont->MaxDescent();
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSdkFonts::TestLFTextPaneTopToBaselineL
// -----------------------------------------------------------------------------
//

TInt CTestSdkFonts::TestLFTextPaneTopToBaselineL(CStifItemParser& /*aItem*/)
    {
    TAknFontSpecification fontSpec( ELatinPlain12 );
    CAknLayoutFont* layoutFont = AknLayoutUtils::
        CreateLayoutFontFromSpecificationL( fontSpec ); 
    layoutFont->TextPaneTopToBaseline();
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSdkFonts::TestLFBaselineToTextPaneBottomL
// -----------------------------------------------------------------------------
//

TInt CTestSdkFonts::TestLFBaselineToTextPaneBottomL(CStifItemParser& /*aItem*/)
    {
    TAknFontSpecification fontSpec( ELatinPlain12 );
    CAknLayoutFont* layoutFont = AknLayoutUtils::
                                CreateLayoutFontFromSpecificationL( fontSpec ); 
    layoutFont->BaselineToTextPaneBottom();
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSdkFonts::TestLFTextPaneHeightL
// -----------------------------------------------------------------------------
//

TInt CTestSdkFonts::TestLFTextPaneHeightL(CStifItemParser& /*aItem*/)
    {
    TAknFontSpecification fontSpec( ELatinPlain12 );
    CAknLayoutFont* layoutFont = AknLayoutUtils::
                                CreateLayoutFontFromSpecificationL( fontSpec ); 
    layoutFont->TextPaneHeight();
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSdkFonts::TestLFAscentForCharacterL
// -----------------------------------------------------------------------------
//

TInt CTestSdkFonts::TestLFAscentForCharacterL(CStifItemParser& /*aItem*/)
    {
    TAknFontSpecification fontSpec( ELatinPlain12 );
    CAknLayoutFont* layoutFont = AknLayoutUtils::
                                CreateLayoutFontFromSpecificationL( fontSpec ); 
    layoutFont->TextPaneHeight();
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSdkFonts::TestLFAsCAknLayoutFontOrNullL
// -----------------------------------------------------------------------------
//

TInt CTestSdkFonts::TestLFAsCAknLayoutFontOrNullL(CStifItemParser& /*aItem*/)
    {
    const CFont* afont = CEikonEnv::Static()->NormalFont();
    TAknFontSpecification fontSpec( ELatinPlain12 );
    CAknLayoutFont* layoutFont = AknLayoutUtils::
                                CreateLayoutFontFromSpecificationL( fontSpec ); 
    layoutFont->AsCAknLayoutFontOrNull( afont );
    return KErrNone;
    
    }
// -----------------------------------------------------------------------------
// CTestSdkFonts::TestLFTextDecorationMetricsL
// -----------------------------------------------------------------------------
//

TInt CTestSdkFonts::TestLFTextDecorationMetricsL(CStifItemParser& /*aItem*/)
    {
    TAknFontSpecification fontSpec( ELatinPlain12 );
    CAknLayoutFont* layoutFont = AknLayoutUtils::
                                CreateLayoutFontFromSpecificationL( fontSpec ); 
    layoutFont->TextDecorationMetrics();
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSdkFonts::TestLFFontCategoryL
// -----------------------------------------------------------------------------
//

TInt CTestSdkFonts::TestLFFontCategoryL(CStifItemParser& /*aItem*/)
    {
    TAknFontSpecification fontSpec( ELatinPlain12 );
    CAknLayoutFont* layoutFont = AknLayoutUtils::
                                CreateLayoutFontFromSpecificationL( fontSpec ); 
    layoutFont->FontCategory();
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSdkFonts::TestLFFontCategoryL
// -----------------------------------------------------------------------------
//

TInt CTestSdkFonts::TestLFFontSpecificationL(CStifItemParser& /*aItem*/)
    {
    TAknFontSpecification fontSpec( ELatinPlain12 );
    CAknLayoutFont* layoutFont = AknLayoutUtils::
                                CreateLayoutFontFromSpecificationL( fontSpec ); 
    layoutFont->FontSpecification();
    return KErrNone;
    }



// End of File
