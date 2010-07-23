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
* Description:  Test aknradiobuttonsettingpage.h
*
*/


//Include files
#include "testaknradiobuttonsettingpageprotected.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestRadioButtonSettingPage::CTestRadioButtonSettingPage
// -----------------------------------------------------------------------------
//
CTestRadioButtonSettingPage::CTestRadioButtonSettingPage( TInt aResourceID, 
    TInt& aCurrentSelectionIndex, 
    const MDesCArray* aItemArray ):CAknRadioButtonSettingPage( aResourceID,
    aCurrentSelectionIndex,
    aItemArray )
    {
    
    }

// -----------------------------------------------------------------------------
// CTestRadioButtonSettingPage::CTestRadioButtonSettingPage
// -----------------------------------------------------------------------------
//
CTestRadioButtonSettingPage::CTestRadioButtonSettingPage( const TDesC* aSettingTitleText, 
    TInt aSettingNumber, 
    TInt aControlType,
    TInt aEditorResourceId, 
    TInt aSettingPageResourceId,
    TInt& aCurrentSelectionIndex, 
    const MDesCArray* aItemArray ):CAknRadioButtonSettingPage( aSettingTitleText, 
    aSettingNumber, 
    aControlType,
    aEditorResourceId,
    aSettingPageResourceId,
    aCurrentSelectionIndex,
    aItemArray )
    {
    
    }

// -----------------------------------------------------------------------------
// CTestRadioButtonSettingPage::~CTestRadioButtonSettingPage
// -----------------------------------------------------------------------------
//
CTestRadioButtonSettingPage::~CTestRadioButtonSettingPage()
    {
    
    }

// -----------------------------------------------------------------------------
// CTestRadioButtonSettingPage::DoUpdateSettingL
// -----------------------------------------------------------------------------
//
void CTestRadioButtonSettingPage::DoUpdateSettingL()
    {
    UpdateSettingL();
    }

// -----------------------------------------------------------------------------
// CTestRadioButtonSettingPage::DoDynamicInitL
// -----------------------------------------------------------------------------
//
void CTestRadioButtonSettingPage::DoDynamicInitL()
    {
    DynamicInitL();
    }

// -----------------------------------------------------------------------------
// CTestRadioButtonSettingPage::DoSelectCurrentItemL
// -----------------------------------------------------------------------------
//
void CTestRadioButtonSettingPage::DoSelectCurrentItemL()
    {
    SelectCurrentItemL();
    }

// -----------------------------------------------------------------------------
// CTestRadioButtonSettingPage::DoWriteInternalStateL
// -----------------------------------------------------------------------------
//
void CTestRadioButtonSettingPage::DoWriteInternalStateL(RWriteStream& aWriteStream) const
    {
    WriteInternalStateL( aWriteStream );
    }

//End file


