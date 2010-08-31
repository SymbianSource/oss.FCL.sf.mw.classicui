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
#include "testbutton.h"
#include "testsdkgenericbuttoninclude.h"

// -----------------------------------------------------------------------------
// CTestParentControl::TestAknButtonShowHelpLL
// -----------------------------------------------------------------------------
//
CTestButton::CTestButton( const TInt aFlags ):CAknButton( aFlags )
        {
        
        }

// -----------------------------------------------------------------------------
// CTestParentControl::TestAknButtonShowHelpLL
// -----------------------------------------------------------------------------
//
CTestButton::~CTestButton()
    {
    
    }

CTestButton* CTestButton::NewL()
    {
    CTestButton* self = NewLC();
    CleanupStack::Pop( self );
    return self;
    }

CTestButton* CTestButton::NewLC()
    {
    CTestButton* self = new (ELeave) CTestButton( KFlagZero );
    CleanupStack::PushL( self );
    self->ConstructL();
    return self;
    }


// -----------------------------------------------------------------------------
// CTestParentControl::TestAknButtonShowHelpLL
// -----------------------------------------------------------------------------
//
TBool CTestButton::DetectiStatesIfNull()
    {
    TBool flag( EFalse );
    if( iStates->Count() == 0 )
        {
        flag = ETrue;
        }
    else
        {
        flag = EFalse;
        }
    return flag;
    }

// -----------------------------------------------------------------------------
// CTestParentControl::TestAknButtonShowHelpLL
// -----------------------------------------------------------------------------
//
TInt CTestButton::DetectiStatesCount()
    {
    return iStates->Count();
    }

// -----------------------------------------------------------------------------
// CTestParentControl::TestAknButtonShowHelpLL
// -----------------------------------------------------------------------------
//
void* CTestButton::DoExtensionInterface( TUid aInterface )
    {
    return ExtensionInterface( aInterface );
    }

// -----------------------------------------------------------------------------
// CTestParentControl::TestAknButtonShowHelpLL
// -----------------------------------------------------------------------------
//
const TDesC&  CTestButton::DoGetCurrentText() const
    {
    return GetCurrentText();
    }

// -----------------------------------------------------------------------------
// CTestParentControl::TestAknButtonShowHelpLL
// -----------------------------------------------------------------------------
//
TInt CTestButton::DoChangeState( TBool aDrawNow )
    {
    TInt returnvalue = ChangeState( aDrawNow );
    return returnvalue;
    }

// -----------------------------------------------------------------------------
// CTestParentControl::TestAknButtonShowHelpLL
// -----------------------------------------------------------------------------
//
void CTestButton::DoConstructL()
    {
    ConstructL();
    }

// -----------------------------------------------------------------------------
// CTestParentControl::TestAknButtonShowHelpLL
// -----------------------------------------------------------------------------
//
CGraphicsContext::TTextAlign CTestButton::GetiHorizontalAlignment()
    {
    return iHorizontalAlignment;
    }

// -----------------------------------------------------------------------------
// CTestParentControl::TestAknButtonShowHelpLL
// -----------------------------------------------------------------------------
//
void CTestButton::DoConstructLComplexL( CGulIcon* aIcon,
                            CGulIcon* aDimmedIcon,
                            CGulIcon* aPressedIcon,
                            CGulIcon* aHoverIcon,
                            const TDesC& aText,
                            const TDesC& aHelpText,
                            const TInt aStateFlags)
    {
    ConstructL( aIcon, aDimmedIcon, aPressedIcon, aHoverIcon,
        aText, aHelpText, aStateFlags );
    }

// -----------------------------------------------------------------------------
// CTestParentControl::TestAknButtonShowHelpLL
// -----------------------------------------------------------------------------
//
void CTestButton::DoConstructLMoreComplexL( const TDesC& aFilePath, 
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
                                const TInt aStateFlags,
                                const TAknsItemID& aId, 
                                const TAknsItemID& aDimmedId, 
                                const TAknsItemID& aPressedId,
                                const TAknsItemID& aHoverId )
    {
    ConstructL( aFilePath, aBmpId, aMaskId, aDimmedBmpId, aDimmedMaskId, aPressedBmpId, 
        aPressedMaskId, aHoverBmpId, aHoverMaskId, aText, aHelpText, aStateFlags, aId, 
        aDimmedId, aPressedId, aHoverId );
    }

// -----------------------------------------------------------------------------
// CTestParentControl::TestAknButtonShowHelpLL
// -----------------------------------------------------------------------------
//
void CTestButton::DoSizeChanged()
    {
    SizeChanged();
    }

// -----------------------------------------------------------------------------
// CTestParentControl::TestAknButtonShowHelpLL
// -----------------------------------------------------------------------------
//
TBool CTestButton::DetectIfShowHelp()
    {
    return iShowHelp;
    }

// -----------------------------------------------------------------------------
// CTestParentControl::TestAknButtonShowHelpLL
// -----------------------------------------------------------------------------
//
TBool CTestButton::DetectIfiDimmedHelpText()
    {
    if( iDimmedHelpText == NULL )
        {
        return EFalse;
        }
    else
        {
        return ETrue;
        }
    }

// -----------------------------------------------------------------------------
// CTestParentControl::TestAknButtonShowHelpLL
// -----------------------------------------------------------------------------
//
void CTestButton::DoShowHelpL()
    {
    ShowHelpL();
    }

// -----------------------------------------------------------------------------
// CTestParentControl::TestAknButtonShowHelpLL
// -----------------------------------------------------------------------------
//
void CTestButton::DoHideHelp()
    {
    HideHelp();
    }

// -----------------------------------------------------------------------------
// CTestParentControl::TestAknButtonShowHelpLL
// -----------------------------------------------------------------------------
//
const CFont* CTestButton::GetiFont()
    {
    return iFont;
    }

// -----------------------------------------------------------------------------
// CTestParentControl::TestAknButtonShowHelpLL
// -----------------------------------------------------------------------------
//
TAknsItemID& CTestButton::GetiTextColorTableId()
    {
    return iTextColorTableId;
    }

// -----------------------------------------------------------------------------
// CTestParentControl::TestAknButtonShowHelpLL
// -----------------------------------------------------------------------------
//
TInt CTestButton::GetiTextColorIndex()
    {
    return iTextColorIndex;
    }

// -----------------------------------------------------------------------------
// CTestParentControl::TestAknButtonShowHelpLL
// -----------------------------------------------------------------------------
//
CAknButton::TAlignment CTestButton::GetiVerticalAlignment()
    {
    return iVerticalAlignment;
    }

// -----------------------------------------------------------------------------
// CTestParentControl::TestAknButtonShowHelpLL
// -----------------------------------------------------------------------------
//
TInt CTestButton::GetiHelpNoteWaitInterval()
    {
    return iHelpNoteWaitInterval;
    }

// -----------------------------------------------------------------------------
// CTestParentControl::TestAknButtonShowHelpLL
// -----------------------------------------------------------------------------
//
TInt CTestButton::GetiHelpNoteInViewInterval()
    {
    return iHelpNoteInViewInterval;
    }

// -----------------------------------------------------------------------------
// CTestParentControl::TestAknButtonShowHelpLL
// -----------------------------------------------------------------------------
//
TInt CTestButton::GetiKeyRepeatDelay()
    {
    return iKeyRepeatDelay;
    }

// -----------------------------------------------------------------------------
// CTestParentControl::TestAknButtonShowHelpLL
// -----------------------------------------------------------------------------
//
TInt CTestButton::GetiKeyRepeatInterval()
    {
    return iKeyRepeatInterval;
    }

// -----------------------------------------------------------------------------
// CTestParentControl::TestAknButtonShowHelpLL
// -----------------------------------------------------------------------------
//
TBool CTestButton::GetiButtonPressed()
    {
    return iButtonPressed;
    }

// -----------------------------------------------------------------------------
// CTestParentControl::TestAknButtonShowHelpLL
// -----------------------------------------------------------------------------
//
void CTestButton::SetiButtonPressed( TBool aButtonPressed )
    {
    iButtonPressed = aButtonPressed;
    }

// -----------------------------------------------------------------------------
// CTestParentControl::TestAknButtonShowHelpLL
// -----------------------------------------------------------------------------
//
TBool CTestButton::GetiShowHelp()
    {
    return iShowHelp;
    }

// -----------------------------------------------------------------------------
// CTestParentControl::TestAknButtonShowHelpLL
// -----------------------------------------------------------------------------
//
void CTestButton::SetiShowHelp( TBool aShowHelp )
    {
    iShowHelp = aShowHelp;
    }

// -----------------------------------------------------------------------------
// CTestParentControl::TestAknButtonShowHelpLL
// -----------------------------------------------------------------------------
//
void CTestButton::DoFocusChanged( TDrawNow aDrawNow )
    {
    FocusChanged( aDrawNow );
    }

// -----------------------------------------------------------------------------
// CTestParentControl::TestAknButtonShowHelpLL
// -----------------------------------------------------------------------------
//
const CGulIcon* CTestButton::DoGetCurrentIcon() const
    {
    const CGulIcon* returnicon = GetCurrentIcon();
    return returnicon;
    }

// -----------------------------------------------------------------------------
// CTestParentControl::TestAknButtonShowHelpLL
// -----------------------------------------------------------------------------
//
void CTestButton::SetiKeyDownReported( TBool keydownreported )
    {
    iKeyDownReported = keydownreported;
    }

// -----------------------------------------------------------------------------
// CTestParentControl::TestAknButtonShowHelpLL
// -----------------------------------------------------------------------------
//
TBool CTestButton::GetiKeyDownReported()
    {
    return iKeyDownReported;
    }

//End file


