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

#include <aknfontaccess.h> 
#include <stringloader.h> 
#include <gdi.h>

#include "testsdkfonts.h"

// CONSTANTS
_LIT( Kstring, "test item");

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSdkFonts::TestFAGetFont
// -----------------------------------------------------------------------------
//

TInt CTestSdkFonts::TestFAGetFont(CStifItemParser& /*aItem*/)
    {
    CWsScreenDevice* screenDev = CCoeEnv::Static()->ScreenDevice();
    TFontStyle fontStyle;
    TInt foundIndex( KErrNotFound );
    iFontAccess->GetFont( *screenDev,fontStyle,foundIndex,AknFontAccess::EAknFontFamilySansSerif );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSdkFonts::TestFAGetFontDesc
// -----------------------------------------------------------------------------
//

TInt CTestSdkFonts::TestFAGetFontDesc(CStifItemParser& /*aItem*/)
    {
    CWsScreenDevice* screenDev = CCoeEnv::Static()->ScreenDevice();
    TFontStyle fontStyle;
    TInt foundIndex( KErrNotFound );
    TDesC16 tmp = Kstring;
    iFontAccess->GetFont( *screenDev,fontStyle,foundIndex,tmp );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSdkFonts::TestFAGetClosestFont
// -----------------------------------------------------------------------------
//

TInt CTestSdkFonts::TestFAGetClosestFont(CStifItemParser& /*aItem*/)
    {
    CWsScreenDevice* screenDev = CCoeEnv::Static()->ScreenDevice();
    TFontStyle fontStyle;
    TInt foundIndex( KErrNotFound );
    iFontAccess->GetClosestFont( *screenDev,fontStyle,foundIndex,AknFontAccess::EAknFontFamilySansSerif );
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSdkFonts::TestFAGetClosestFontDesc
// -----------------------------------------------------------------------------
//

TInt CTestSdkFonts::TestFAGetClosestFontDesc(CStifItemParser& /*aItem*/)
    {
    CWsScreenDevice* screenDev = CCoeEnv::Static()->ScreenDevice();
    TFontStyle fontStyle;
    TInt foundIndex( KErrNotFound );
    TDesC16 tmp = Kstring;
    iFontAccess->GetClosestFont( *screenDev,fontStyle,foundIndex,tmp );
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSdkFonts::TestFACreateLayoutFontFromSpecificationL
// -----------------------------------------------------------------------------
//

TInt CTestSdkFonts::TestFACreateLayoutFontFromSpecificationL(CStifItemParser& /*aItem*/)
    {
    CWsScreenDevice* screenDev = CCoeEnv::Static()->ScreenDevice();
    TAknFontSpecification fontSpecification( 1 );
    iFontAccess->CreateLayoutFontFromSpecificationL( *screenDev, fontSpecification );
    return KErrNone;
    
    }
// -----------------------------------------------------------------------------
// CTestSdkFonts::TestFACreateLayoutFontFromSpecificationTTypefaceL
// -----------------------------------------------------------------------------
//

TInt CTestSdkFonts::TestFACreateLayoutFontFromSpecificationTTypefaceL(CStifItemParser& /*aItem*/)
    {
    TTypeface* typeface=new ( ELeave )TTypeface();
    CleanupStack::PushL( typeface );
    CWsScreenDevice* screenDev = CCoeEnv::Static()->ScreenDevice();
    TAknFontSpecification fontSpecification( 1 );
    iFontAccess->CreateLayoutFontFromSpecificationL( *screenDev, *typeface, fontSpecification );
    CleanupStack::PopAndDestroy( typeface );
    return KErrNone;
    }

// End of File
