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
* Description:  test AknPopupField.h 
*
*/


//  INCLUDES
#include <coecobs.h>
#include <aknpopupheadingpane.h>
#include <barsread.h>
#include <coemain.h>
#include <testsdkpopups.rsg>

#include "testsdkpopupscpf.h"
// ============================ MEMBER FUNCTIONS ===============================
// -----------------------------------------------------------------------------
// CTestSDKPopupsCPF::HandleControlEventL
// -----------------------------------------------------------------------------
void CTestSDKPopupsCPF::HandleControlEventL( CCoeControl* aControl,TCoeEvent aEvent )
    {
    CAknPopupField::HandleControlEventL( aControl, aEvent );
    }

// -----------------------------------------------------------------------------
// CTestSDKPopupsCPF::CTestSDKPopupsCPF
// -----------------------------------------------------------------------------
CTestSDKPopupsCPF::CTestSDKPopupsCPF():CAknPopupField()
    {
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopupsCPF::~CTestSDKPopupsCPF
// -----------------------------------------------------------------------------
CTestSDKPopupsCPF::~CTestSDKPopupsCPF()
    {
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopupsCPF::ProcessCommandL
// -----------------------------------------------------------------------------
void CTestSDKPopupsCPF::ProcessCommandL( TInt aCommandId )
    {
    CAknPopupField::ProcessCommandL( aCommandId );
    }

// -----------------------------------------------------------------------------
// CTestSDKPopupsCPF::HandleListBoxEventL
// -----------------------------------------------------------------------------
void CTestSDKPopupsCPF::HandleListBoxEventL( CEikListBox* aListBox, TListBoxEvent aEventType )
    {
    CAknPopupField::HandleListBoxEventL( aListBox, aEventType );
    }

// -----------------------------------------------------------------------------
// CTestSDKPopupsCPF::CountComponentControls
// -----------------------------------------------------------------------------
TInt CTestSDKPopupsCPF::CountComponentControls() const
    {
    return CAknPopupField::CountComponentControls();
    }

// -----------------------------------------------------------------------------
// CTestSDKPopupsCPF::ComponentControl
// -----------------------------------------------------------------------------
CCoeControl* CTestSDKPopupsCPF::ComponentControl(TInt aIndex) const
    {
    return CAknPopupField::ComponentControl( aIndex );
    }

// -----------------------------------------------------------------------------
// CTestSDKPopupsCPF::SizeChanged
// -----------------------------------------------------------------------------
void CTestSDKPopupsCPF::SizeChanged()
    {
    CAknPopupField::SizeChanged();
    }

// -----------------------------------------------------------------------------
// CTestSDKPopupsCPF::FocusChanged
// -----------------------------------------------------------------------------
void CTestSDKPopupsCPF::FocusChanged( TDrawNow aDrawNow )
    {
    CAknPopupField::FocusChanged( aDrawNow );
    }

// -----------------------------------------------------------------------------
// CTestSDKPopupsCPF::Draw
// -----------------------------------------------------------------------------
void CTestSDKPopupsCPF::Draw(const TRect& aRect) const
    {
    CAknPopupField::Draw( aRect );
    }

// -----------------------------------------------------------------------------
// CTestSDKPopupsCPF::MopSupplyObject
// -----------------------------------------------------------------------------
TTypeUid::Ptr CTestSDKPopupsCPF::MopSupplyObject( TTypeUid aId )
    {
    return CAknPopupField::MopSupplyObject( aId );
    }
