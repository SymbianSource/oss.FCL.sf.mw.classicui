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
* Description:  
*
*/

#include <aknsitemid.h>

#include "testsdklistsclbdata.h"

// ============================ MEMBER FUNCTIONS ===============================
// -----------------------------------------------------------------------------
// CTestSDKColumnListBoxData::CTestSDKColumnListBoxData()
// -----------------------------------------------------------------------------
//
CTestSDKColumnListBoxData::CTestSDKColumnListBoxData()
    {
    }

// -----------------------------------------------------------------------------
// CTestSDKColumnListBoxData::~CTestSDKColumnListBoxData()
// -----------------------------------------------------------------------------
//
CTestSDKColumnListBoxData::~CTestSDKColumnListBoxData()
    {
    }

// -----------------------------------------------------------------------------
// CTestSDKColumnListBoxData::ConstructLD()
// -----------------------------------------------------------------------------
//
void CTestSDKColumnListBoxData::ConstructLD()
    {
    CColumnListBoxData::ConstructLD();
    }

// -----------------------------------------------------------------------------
// CTestSDKColumnListBoxData::ConstructLD()
// -----------------------------------------------------------------------------
//
void CTestSDKColumnListBoxData::ConstructLD( const TAknsItemID& aAnimationIID )
    {
    CColumnListBoxData::ConstructLD( aAnimationIID );
    }

// -----------------------------------------------------------------------------
// CTestSDKColumnListBoxData::DrawText()
// -----------------------------------------------------------------------------
//
void CTestSDKColumnListBoxData::DrawText( CWindowGc& aGc, const TRect& aTextRect, 
                                                    const TDesC& aText, const TDesC& aClippedText, 
                                                    const TInt aBaselineOffset, 
                                                    const CGraphicsContext::TTextAlign aAlign, 
                                                    const CFont& aFont, const TBool aHighlight, 
                                                    const TBool aIsTextClipped )
    {
    CColumnListBoxData::DrawText( aGc, aTextRect, aText, aClippedText, aBaselineOffset,
                                  aAlign, aFont, aHighlight, aIsTextClipped );
    }

// ======== MEMBER FUNCTIONS ========
// TTestListBoxAnimBgDrawer

// ---------------------------------------------------------------------------
// TTestListBoxAnimBgDrawer::DrawHighlightAnimBackground
// ---------------------------------------------------------------------------
//
TBool TTestListBoxAnimBgDrawer::
    DrawHighlightAnimBackground( CFbsBitGc& ) const
    {
    return ETrue;
    }
