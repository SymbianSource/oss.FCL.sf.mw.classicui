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

#include "testsdklistslistboxdata.h"

const TInt KFontHeightInTwips = 20;
// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKListsListBoxData::SetSkinBackgroundControlContextL()
// -----------------------------------------------------------------------------
//
void CTestSDKListsListBoxData::TestSetSkinBackgroundControlContextL(MAknsControlContext* aContext)
    {
    CListBoxData::SetSkinBackgroundControlContextL( aContext );
    }

// -----------------------------------------------------------------------------
// CTestSDKListsListBoxData::TestSetSkinEnabledL()
// -----------------------------------------------------------------------------
//
void CTestSDKListsListBoxData::TestSetSkinEnabledL(TBool aEnabled)
    {
    CListBoxData::SetSkinEnabledL( aEnabled );
    }

// -----------------------------------------------------------------------------
// CTestSDKListsListBoxData::ConstructFontL()
// -----------------------------------------------------------------------------
//
void CTestSDKListsListBoxData::TestConstructFontL(const CFont* aBaseFont)
    {
    TFontStyle style( EPostureItalic, EStrokeWeightBold, 
        EPrintPosSuperscript );
    ConstructFontL( aBaseFont, style, iItalicFont );
    }

// -----------------------------------------------------------------------------
// CTestSDKListsListBoxData::UpdateFontBoundValues()
// -----------------------------------------------------------------------------
//
void CTestSDKListsListBoxData::TestUpdateFontBoundValues(const CFont* aFont)
    {
    UpdateFontBoundValues( *aFont );
    }

// -----------------------------------------------------------------------------
// CTestSDKListsListBoxData::RegenerateFonts()
// -----------------------------------------------------------------------------
//
TInt CTestSDKListsListBoxData::TestRegenerateFonts()
    {
    TInt ret = RegenerateFonts( iNormalFont, KFontHeightInTwips );    
    return ret;
    }

// -----------------------------------------------------------------------------
// CTestSDKListsListBoxData::TestReleaseFonts()
// -----------------------------------------------------------------------------
//
void CTestSDKListsListBoxData::TestReleaseFonts()
    {
    iNormalFont.ReleaseFonts();
    }

// -----------------------------------------------------------------------------
// CTestSDKListsListBoxData::TestFontStyle()
// -----------------------------------------------------------------------------
//
void CTestSDKListsListBoxData::TestFontStyle()
    {
    TFontStyle fontStyle = iNormalFont.FontStyle();
    }

// -----------------------------------------------------------------------------
// CTestSDKListsListBoxData::TestSetFontStyle()
// -----------------------------------------------------------------------------
//
TBool CTestSDKListsListBoxData::TestSetFontStyle()
    {
    TFontStyle style( EPostureItalic, EStrokeWeightBold, 
        EPrintPosSuperscript );    
    iNormalFont.SetFontStyle( style );
    TFontStyle fontStyle = iNormalFont.FontStyle();
    return ( fontStyle == style );
    }
