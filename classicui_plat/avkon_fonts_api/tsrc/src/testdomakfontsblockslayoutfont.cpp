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
* Description:  Test AknFontIdLayoutFont.h
*
*/



/*
 * [INCLUDE FILES]
 */
#include <aknfontidlayoutfont.h>
#include <w32std.h>
#include <eikenv.h>

#include "testdomakfonts.h"

const TInt KTen = 10;

// -----------------------------------------------------------------------------
// Ctestdomakfonts::TestLOFONTNewL
// -----------------------------------------------------------------------------
//
TInt CTestDOMAKFONTS::TestLOFONTNewL( CStifItemParser& /*aItem*/ )
    {
    CWsScreenDevice* screendevice = CEikonEnv::Static()->ScreenDevice();
    TInt fontid(0);
    CAknFontIdLayoutFont* layoutfont = NULL;
    layoutfont = CAknFontIdLayoutFont::NewL( *screendevice,
        fontid );
    STIF_ASSERT_NOT_NULL( layoutfont );
    delete layoutfont;
    delete screendevice;
    
    return KErrNone;
    }
    
// -----------------------------------------------------------------------------
// CTestDOMAKFONTS::TestLOFONTFontIdL
// -----------------------------------------------------------------------------
//
TInt CTestDOMAKFONTS::TestLOFONTFontIdL( CStifItemParser& /*aItem*/ )
    {
    CWsScreenDevice* screendevice = CEikonEnv::Static()->ScreenDevice();
    
    TInt fontid(0);
    CAknFontIdLayoutFont* layoutfont ;
    layoutfont = CAknFontIdLayoutFont::NewL( *screendevice, 
        fontid );
    
    TInt returnfontid(1);
    returnfontid = layoutfont->FontId();
    
    STIF_ASSERT_NOT_EQUALS( 1, returnfontid );
    STIF_ASSERT_EQUALS( fontid, returnfontid );
    
    delete layoutfont;
    delete screendevice;
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDOMAKFONTS::TestLOFONTUpdateId
// -----------------------------------------------------------------------------
//
TInt CTestDOMAKFONTS::TestLOFONTUpdateIdL( CStifItemParser& /*aItem*/ )
    {
    CWsScreenDevice* screendevice = CEikonEnv::Static()->ScreenDevice();
    
    TInt fontid(0);
    CAknFontIdLayoutFont* layoutfont = NULL;
    layoutfont = CAknFontIdLayoutFont::NewL( *screendevice, 
        fontid );
    
    TInt updatefontid( KTen );
    layoutfont->UpdateId( updatefontid );
    
    updatefontid = 0;
    updatefontid = layoutfont->FontId();
    STIF_ASSERT_EQUALS( KTen, updatefontid );
    delete layoutfont;
    delete screendevice;
    return KErrNone;
    }


/*
 * [End of File]
 */
