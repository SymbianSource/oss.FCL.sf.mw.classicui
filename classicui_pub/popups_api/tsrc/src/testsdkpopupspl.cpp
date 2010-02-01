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
* Description:  test aknPopup.h 
*
*/


//  INCLUDES

#include <coecobs.h>
#include <aknpopupheadingpane.h>
#include <barsread.h>
#include <coemain.h>
#include <testsdkpopups.rsg>

#include "testsdkpopupspl.h"

// ============================ MEMBER FUNCTIONS ===============================
// -----------------------------------------------------------------------------
// CTestSDKPopupsPL::CTestSDKPopupsPL
// -----------------------------------------------------------------------------
CTestSDKPopupsPL::CTestSDKPopupsPL():CAknPopupList()
    {
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopupsPL::~CTestSDKPopupsPL
// -----------------------------------------------------------------------------
CTestSDKPopupsPL::~CTestSDKPopupsPL()
    {
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopupsPL::Layout
// -----------------------------------------------------------------------------
TAknPopupWindowLayoutDef& CTestSDKPopupsPL::Layout()
    {
    return CAknPopupList::Layout();
    }

// -----------------------------------------------------------------------------
// CTestSDKPopupsPL::NewL
// -----------------------------------------------------------------------------
CTestSDKPopupsPL* CTestSDKPopupsPL::NewL( CEikListBox* aListBox, TInt aCbaResource,
        AknPopupLayouts::TAknPopupLayouts aType )
    {
    return static_cast<CTestSDKPopupsPL*> ( CAknPopupList::NewL( aListBox, aCbaResource, aType ) );
    }

// -----------------------------------------------------------------------------
// CTestSDKPopupsPL::ProcessCommandL
// -----------------------------------------------------------------------------
void CTestSDKPopupsPL::ProcessCommandL( TInt aCommandId )
    {
    CAknPopupList::ProcessCommandL( aCommandId );
    }

// -----------------------------------------------------------------------------
// CTestSDKPopupsPL::HandleListBoxEventL
// -----------------------------------------------------------------------------
void CTestSDKPopupsPL::HandleListBoxEventL( CEikListBox* aListBox, TListBoxEvent aEventType )
    {
    CAknPopupList::HandleListBoxEventL( aListBox, aEventType );
    }

// -----------------------------------------------------------------------------
// CTestSDKPopupsPL::HandleControlEventL
// -----------------------------------------------------------------------------
void CTestSDKPopupsPL::HandleControlEventL( CCoeControl* aControl, TCoeEvent aEventType )
    {
    CAknPopupList::HandleControlEventL( aControl, aEventType );
    }

// -----------------------------------------------------------------------------
// CTestSDKPopupsPL::AttemptExitL
// -----------------------------------------------------------------------------
void CTestSDKPopupsPL::AttemptExitL(TBool aAccept)
    {
    CAknPopupList::AttemptExitL( aAccept );
    }

// -----------------------------------------------------------------------------
// CTestSDKPopupsPL::SetupWindowLayout
// -----------------------------------------------------------------------------
void CTestSDKPopupsPL::SetupWindowLayout( AknPopupLayouts::TAknPopupLayouts aType )
    {
    CAknPopupList::SetupWindowLayout( aType );
    }

// -----------------------------------------------------------------------------
// CTestSDKPopupsPL::SetupWindowLayout
// -----------------------------------------------------------------------------
CEikListBox* CTestSDKPopupsPL::ListBox() const
    {
    return CAknPopupList::ListBox();
    }

// -----------------------------------------------------------------------------
// CTestSDKPopupsPL::SetupWindowLayout
// -----------------------------------------------------------------------------
const TAknPopupWindowLayoutDef& CTestSDKPopupsPL::Layout() const
    {
    return CAknPopupList::Layout();
    }

// -----------------------------------------------------------------------------
// CTestSDKPopupsPL::MopSupplyObject
// -----------------------------------------------------------------------------
TTypeUid::Ptr CTestSDKPopupsPL::MopSupplyObject( TTypeUid aId )
    {
    return CAknPopupList::MopSupplyObject( aId );
    }

// -----------------------------------------------------------------------------
// CTestSDKPopupsPL::HandleResourceChange
// -----------------------------------------------------------------------------
void CTestSDKPopupsPL::HandleResourceChange( TInt aType )
    {
    CAknPopupList::HandleResourceChange( aType );
    }

// -----------------------------------------------------------------------------
// CTestSDKPopupsPL::FadeBehindPopup
// -----------------------------------------------------------------------------
void CTestSDKPopupsPL::FadeBehindPopup( TBool aFade )
    {
    CAknPopupList::FadeBehindPopup( aFade );
    }

// -----------------------------------------------------------------------------
// CTestSDKPopupsPL::ActivateGc
// -----------------------------------------------------------------------------
void CTestSDKPopupsPL::ActivateGc() const
    {
    CAknPopupList::ActivateGc();
    }

// -----------------------------------------------------------------------------
// CTestSDKPopupsPL::DeactivateGc
// -----------------------------------------------------------------------------
void CTestSDKPopupsPL::DeactivateGc() const
    {
    CAknPopupList::DeactivateGc();
    }
