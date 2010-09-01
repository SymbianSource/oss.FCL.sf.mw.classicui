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
* Description:  Test akntextsettingpage.h
*
*/

//INCLUDE
#include "testakntextsettingpageprotected.h"
#include "testsdksettingpagesstdinclude.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestEdwinSettingPage::CTestEdwinSettingPage
// -----------------------------------------------------------------------------
//
CTestEdwinSettingPage::CTestEdwinSettingPage( TInt aResourceId ):
    CAknEdwinSettingPage( aResourceId )
    {
    
    }

// -----------------------------------------------------------------------------
// CTestEdwinSettingPage::CTestEdwinSettingPage
// -----------------------------------------------------------------------------
//
CTestEdwinSettingPage::CTestEdwinSettingPage( const TDesC* aSettingTitleText, 
    TInt aSettingNumber, 
    TInt aControlType,
    TInt aEditorResourceId, 
    TInt aSettingPageResourceId ):CAknEdwinSettingPage( aSettingTitleText, aSettingNumber,
        aControlType, aEditorResourceId, aSettingPageResourceId )
    {
    
    }

// -----------------------------------------------------------------------------
// CTestEdwinSettingPage::~CTestEdwinSettingPage
// -----------------------------------------------------------------------------
//
CTestEdwinSettingPage::~CTestEdwinSettingPage()
    {
    
    }

// -----------------------------------------------------------------------------
// CTestEdwinSettingPage::SizeChanged
// -----------------------------------------------------------------------------
//
void CTestEdwinSettingPage::SizeChanged()
    {

    }

// -----------------------------------------------------------------------------
// CTestEdwinSettingPage::DoDraw
// -----------------------------------------------------------------------------
//
void CTestEdwinSettingPage::DoDraw(const TRect& aRect) const
    {
    Draw( aRect );
    }

// -----------------------------------------------------------------------------
// CTestEdwinSettingPage::DoActivateGc
// -----------------------------------------------------------------------------
//
void CTestEdwinSettingPage::DoActivateGc() const
    {
    ActivateGc();
    }

// -----------------------------------------------------------------------------
// CTestEdwinSettingPage::DoDeactivateGc
// -----------------------------------------------------------------------------
//
void CTestEdwinSettingPage::DoDeactivateGc() const
    {
    DeactivateGc();
    }

// -----------------------------------------------------------------------------
// CTestEdwinSettingPage::DoLayoutRect
// -----------------------------------------------------------------------------
//
void CTestEdwinSettingPage::DoLayoutRect()
    {
    TPoint topLeftPoint( KZero, KZero );
    TPoint bottomRightPoint( KTen, KTen );
    TRect rect( topLeftPoint, bottomRightPoint );
    iEdwinLayoutRect.LayoutRect( rect, KZero, KZero, KZero, KTen, KTen, KTen, KTen );
    iHorizontalShadow.LayoutRect( rect, KZero, KZero, KZero, KTen, KTen, KTen, KTen );
    iVerticalShadow.LayoutRect( rect, KZero, KZero, KZero, KTen, KTen, KTen, KTen );
    iOutlineFrame.LayoutRect( rect, KZero, KZero, KZero, KTen, KTen, KTen, KTen );
    }

// -----------------------------------------------------------------------------
// CTestTextSettingPage::CTestTextSettingPage
// -----------------------------------------------------------------------------
//
CTestTextSettingPage::CTestTextSettingPage( TInt aResourceID, 
    TDes& aText, TInt aTextSettingPageFlags ):CAknTextSettingPage( aResourceID, aText, 
    aTextSettingPageFlags )
    {
    
    }

// -----------------------------------------------------------------------------
// CTestTextSettingPage::CTestTextSettingPage
// -----------------------------------------------------------------------------
//
CTestTextSettingPage::CTestTextSettingPage( const TDesC* aSettingTitleText, 
        TInt aSettingNumber, 
        TInt aControlType,
        TInt aEditorResourceId, 
        TInt aSettingPageResourceId,
        TDes& aText, 
        TInt aTextSettingPageFlags ):CAknTextSettingPage( aSettingTitleText, aSettingNumber, 
            aControlType, aEditorResourceId, aSettingPageResourceId, aText, aTextSettingPageFlags )
    {
    
    }

// -----------------------------------------------------------------------------
// CTestTextSettingPage::~CTestTextSettingPage
// -----------------------------------------------------------------------------
//
CTestTextSettingPage::~CTestTextSettingPage()
    {
    
    }

// -----------------------------------------------------------------------------
// CTestTextSettingPage::DoDynamicInitL
// -----------------------------------------------------------------------------
//
void CTestTextSettingPage::DoDynamicInitL()
    {
    DynamicInitL();
    }

// -----------------------------------------------------------------------------
// CTestTextSettingPage::DoUpdateSettingL
// -----------------------------------------------------------------------------
//
void CTestTextSettingPage::DoUpdateSettingL()
    {
    UpdateSettingL();
    }

// -----------------------------------------------------------------------------
// CTestTextSettingPage::DoAcceptSettingL
// -----------------------------------------------------------------------------
//
void CTestTextSettingPage::DoAcceptSettingL()
    {
    AcceptSettingL();
    }

// -----------------------------------------------------------------------------
// CTestTextSettingPage::DoRestoreOriginalSettingL
// -----------------------------------------------------------------------------
//
void CTestTextSettingPage::DoRestoreOriginalSettingL()
    {
    RestoreOriginalSettingL();
    }

// -----------------------------------------------------------------------------
// CTestTextSettingPage::DoHandleControlEventL
// -----------------------------------------------------------------------------
//
void CTestTextSettingPage::DoHandleControlEventL(CCoeControl* aControl, TCoeEvent aEventType )
    {
    HandleControlEventL( aControl, aEventType );
    }

// -----------------------------------------------------------------------------
// CTestTextSettingPage::DoCheckAndSetDataValidity
// -----------------------------------------------------------------------------
//
void CTestTextSettingPage::DoCheckAndSetDataValidity()
    {
    CheckAndSetDataValidity();
    }

// -----------------------------------------------------------------------------
// CTestTextSettingPage::DoUpdateTextL
// -----------------------------------------------------------------------------
//
void CTestTextSettingPage::DoUpdateTextL()
    {
    UpdateTextL();
    }

// -----------------------------------------------------------------------------
// CTestTextSettingPage::DoUpdateCbaL
// -----------------------------------------------------------------------------
//
void CTestTextSettingPage::DoUpdateCbaL()
    {
    UpdateCbaL();
    }

// -----------------------------------------------------------------------------
// CTestTextSettingPage::DoOkToExitL
// -----------------------------------------------------------------------------
//
void CTestTextSettingPage::DoOkToExitL(TBool aAccept)
    {
    OkToExitL( aAccept );
    }

// -----------------------------------------------------------------------------
// CTestTextSettingPage::DoOfferKeyEventL
// -----------------------------------------------------------------------------
//
void CTestTextSettingPage::DoOfferKeyEventL( const TKeyEvent& aKeyEvent, TEventCode aType)
    {
    OfferKeyEventL( aKeyEvent, aType );
    }

// -----------------------------------------------------------------------------
// CTestTextSettingPage::DoSizeChanged
// -----------------------------------------------------------------------------
//
void CTestTextSettingPage::DoSizeChanged()
    {
    SizeChanged();
    }

// -----------------------------------------------------------------------------
// CTestTextSettingPage::DoWriteInternalStateL
// -----------------------------------------------------------------------------
//
void CTestTextSettingPage::DoWriteInternalStateL(RWriteStream& aWriteStream) const
    {
    WriteInternalStateL( aWriteStream );
    }

// -----------------------------------------------------------------------------
// CTestIntegerSettingPage::CTestIntegerSettingPage
// -----------------------------------------------------------------------------
//
CTestIntegerSettingPage::CTestIntegerSettingPage( TInt aResourceID, 
    TInt& aValue, TInt aTextSettingPageFlags ):CAknIntegerSettingPage( aResourceID,
    aValue, aTextSettingPageFlags )
    {
    
    }

// -----------------------------------------------------------------------------
// CTestIntegerSettingPage::CTestIntegerSettingPage
// -----------------------------------------------------------------------------
//
CTestIntegerSettingPage::CTestIntegerSettingPage( const TDesC* aSettingTitleText, 
    TInt aSettingNumber, 
    TInt aControlType,
    TInt aEditorResourceId, 
    TInt aSettingPageResourceId,
    TInt& aValue, 
    TInt aIntegerSettingPageFlags ):CAknIntegerSettingPage( aSettingTitleText,
    aSettingNumber, aControlType, aEditorResourceId, aSettingPageResourceId,
    aValue, aIntegerSettingPageFlags )
    {
    
    }

// -----------------------------------------------------------------------------
// CTestIntegerSettingPage::~CTestIntegerSettingPage
// -----------------------------------------------------------------------------
//
CTestIntegerSettingPage::~CTestIntegerSettingPage()
    {
    
    }

// -----------------------------------------------------------------------------
// CTestIntegerSettingPage::DoDynamicInitL
// -----------------------------------------------------------------------------
//
void CTestIntegerSettingPage::DoDynamicInitL()
    {
    DynamicInitL();
    }

// -----------------------------------------------------------------------------
// CTestIntegerSettingPage::DoUpdateSettingL
// -----------------------------------------------------------------------------
//
void CTestIntegerSettingPage::DoUpdateSettingL()
    {
    UpdateSettingL();
    }

// -----------------------------------------------------------------------------
// CTestIntegerSettingPage::DoRestoreOriginalSettingL
// -----------------------------------------------------------------------------
//
void CTestIntegerSettingPage::DoRestoreOriginalSettingL()
    {
    RestoreOriginalSettingL();
    }

// -----------------------------------------------------------------------------
// CTestIntegerSettingPage::DoCheckAndSetDataValidity
// -----------------------------------------------------------------------------
//
void CTestIntegerSettingPage::DoCheckAndSetDataValidity()
    {
    CheckAndSetDataValidity();
    }

// -----------------------------------------------------------------------------
// CTestIntegerSettingPage::DoUpdateCbaL
// -----------------------------------------------------------------------------
//
void CTestIntegerSettingPage::DoUpdateCbaL()
    {
    UpdateCbaL();
    }

// -----------------------------------------------------------------------------
// CTestIntegerSettingPage::DoHandleControlEventL
// -----------------------------------------------------------------------------
//
void CTestIntegerSettingPage::DoHandleControlEventL(CCoeControl* aControl, TCoeEvent aEventType )
    {
    HandleControlEventL( aControl, aEventType );
    }

// -----------------------------------------------------------------------------
// CTestIntegerSettingPage::DoSizeChanged
// -----------------------------------------------------------------------------
//
void CTestIntegerSettingPage::DoSizeChanged()
    {
    SizeChanged();
    }

// -----------------------------------------------------------------------------
// CTestIntegerSettingPage::DoWriteInternalStateL
// -----------------------------------------------------------------------------
//
void CTestIntegerSettingPage::DoWriteInternalStateL(RWriteStream& aWriteStream) const
    {
    WriteInternalStateL( aWriteStream );
    }

//Endfile


