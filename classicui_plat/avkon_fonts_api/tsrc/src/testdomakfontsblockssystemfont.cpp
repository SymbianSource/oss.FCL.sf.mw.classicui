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
* Description:  Test AknSystemFont.h
*
*/



/*
 * [INCLUDE FILES]
 */
#include <aknsystemfont.h>
#include <aknlayoutfont.h>
#include <gdi.h>
#include <eikenv.h>
#include <coemain.h>

#include "testdomakfonts.h"

const TUid KUidInterface = { 0xA000409E };

// -----------------------------------------------------------------------------
// Ctestdomakfonts::TestLOFONTNewL
// -----------------------------------------------------------------------------
//
TInt CTestDOMAKFONTS::TestSTFONTNewL( CStifItemParser& /*aItem*/ )
    {
    const CAknLayoutFont* layoutfont ;
    layoutfont = 
        CAknLayoutFont::AsCAknLayoutFontOrNull( CEikonEnv::Static( )->DenseFont() );
    CLafSystemFont* systemfont = NULL;
    systemfont = 
        CLafSystemFont::NewL( KUidInterface, (CAknLayoutFont*)layoutfont );
    STIF_ASSERT_NOT_NULL( systemfont );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDOMAKFONTS::TestSTFONTFontL
// -----------------------------------------------------------------------------
//
TInt CTestDOMAKFONTS::TestSTFONTFontL( CStifItemParser& /*aItem*/ )
    {
    const CAknLayoutFont* layoutfont ;
    layoutfont = 
        CAknLayoutFont::AsCAknLayoutFontOrNull( CEikonEnv::Static( )->DenseFont() );
    CLafSystemFont* systemfont = NULL;
    systemfont = 
        CLafSystemFont::NewL( KUidInterface, (CAknLayoutFont*)layoutfont );
    CFont* font(NULL);
    font = systemfont->Font();
    STIF_ASSERT_EQUALS( (CFont*)layoutfont, font );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDOMAKFONTS::TestSTFONTUidL
// -----------------------------------------------------------------------------
//
TInt CTestDOMAKFONTS::TestSTFONTUidL( CStifItemParser& /*aItem*/ )
    {
    const CAknLayoutFont* layoutfont ;
    layoutfont = 
        CAknLayoutFont::AsCAknLayoutFontOrNull( CEikonEnv::Static( )->DenseFont() );
    CLafSystemFont* systemfont = NULL;
    systemfont = 
        CLafSystemFont::NewL( KUidInterface, (CAknLayoutFont*)layoutfont );
    TUid uid;
    uid = systemfont->Uid();
    STIF_ASSERT_EQUALS( uid, KUidInterface );
    return KErrNone;
    }

/*
 * [End of File]
 */
