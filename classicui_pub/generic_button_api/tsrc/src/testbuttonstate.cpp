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
* Description:  Test AknButton.h
*
*/



/*
 * Inclue files
 */
#include "testbuttonstate.h"

// -----------------------------------------------------------------------------
// CTestParentControl::TestAknButtonShowHelpLL
// -----------------------------------------------------------------------------
//
CTestButtonState::CTestButtonState( const TInt aFlags ):CAknButtonState( aFlags )
    {

    }

// -----------------------------------------------------------------------------
// CTestParentControl::TestAknButtonShowHelpLL
// -----------------------------------------------------------------------------
//
CTestButtonState::~CTestButtonState()
    {
    }

// -----------------------------------------------------------------------------
// CTestParentControl::TestAknButtonShowHelpLL
// -----------------------------------------------------------------------------
//
TBool CTestButtonState::StifHasText() const
    {
    TBool flag = HasText();
    return flag;
    }

// -----------------------------------------------------------------------------
// CTestParentControl::TestAknButtonShowHelpLL
// -----------------------------------------------------------------------------
//
void CTestButtonState::DoConstructL( CGulIcon* aIcon,
    CGulIcon* aDimmedIcon, 
    CGulIcon* aPressedIcon,
    CGulIcon* aHoverIcon,
    const TDesC& aText, 
    const TDesC& aHelpText )
    {
    ConstructL( aIcon, aDimmedIcon, aPressedIcon, aHoverIcon, aText, aHelpText );
    }

// -----------------------------------------------------------------------------
// CTestParentControl::TestAknButtonShowHelpLL
// -----------------------------------------------------------------------------
//
void CTestButtonState::DoConstructDeepL( const TDesC& aFilePath, 
        const TInt aBmpId, 
        const TInt aMaskId,
        const TInt aDimmedBmpId, 
        const TInt aDimmedMaskId,
        const TInt aPressedBmpId, 
        const TInt aPressedMaskId,
        const TInt aHoverBmpId,
        const TInt aHoverMaskId,
        const TDesC& aText, 
        const TDesC& aHelpText,
        const TAknsItemID& aId, 
        const TAknsItemID& aDimmedId, 
        const TAknsItemID& aPressedId,
        const TAknsItemID& aHoverId )
    {
    ConstructL( aFilePath, aBmpId, aMaskId,aDimmedBmpId, aDimmedMaskId,
                    aPressedBmpId, aPressedMaskId,aHoverBmpId,aHoverMaskId,aText, 
                        aHelpText,aId,aDimmedId, aPressedId,aHoverId );
    }

// -----------------------------------------------------------------------------
// CTestParentControl::TestAknButtonShowHelpLL
// -----------------------------------------------------------------------------
//
void CTestButtonState::DoConstructFromResourceL( TResourceReader& aReader )
    {
    ConstructFromResourceL( aReader );
    }

// -----------------------------------------------------------------------------
// CTestParentControl::TestAknButtonShowHelpLL
// -----------------------------------------------------------------------------
//
TBool CTestButtonState::DoHasText()
    {
    TBool returnvalue = HasText();
    return returnvalue;
    }

// -----------------------------------------------------------------------------
// CTestParentControl::TestAknButtonShowHelpLL
// -----------------------------------------------------------------------------
//
TBool CTestButtonState::DoHasHelp()
    {
    TBool returnvalue = HasHelp();
    return returnvalue;
    }

// -----------------------------------------------------------------------------
// CTestParentControl::TestAknButtonShowHelpLL
// -----------------------------------------------------------------------------
//
void CTestButtonState::DoSizeChanged( const TRect& aRect, TScaleMode aScaleMode )
    {
    SizeChanged( aRect, aScaleMode );
    }
   
//End file


