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
* Description:  test AknPopupSettingPage.h
*
*/


//  INCLUDES
#include <coecobs.h>
#include <aknpopupheadingpane.h>
#include <barsread.h>
#include <coemain.h>
#include <testsdkpopups.rsg>

#include "testsdkpopupsspsp.h"

// ============================ MEMBER FUNCTIONS ===============================
// -----------------------------------------------------------------------------
// CTestSDKPopupsSPSP::CTestSDKPopupsSPSP
// -----------------------------------------------------------------------------
CTestSDKPopupsSPSP::CTestSDKPopupsSPSP( TInt aResourceID, 
        MAknQueryValue& aQueryValue ):CAknPopupSettingPage( aResourceID, aQueryValue )
    {
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopupsSPSP::CTestSDKPopupsSPSP
// -----------------------------------------------------------------------------
CTestSDKPopupsSPSP::CTestSDKPopupsSPSP( const TDesC* aSettingTitleText, 
     TInt aSettingNumber, 
     TInt aControlType,
     TInt aEditorResourceId, 
     TInt aSettingPageResourceId,
     MAknQueryValue& aQueryValue ):CAknPopupSettingPage( aSettingTitleText, aSettingNumber,
         aControlType, aEditorResourceId, aSettingPageResourceId, aQueryValue )
    {
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopupsSPSP::~CTestSDKPopupsSPSP
// -----------------------------------------------------------------------------
CTestSDKPopupsSPSP::~CTestSDKPopupsSPSP()
    {
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopupsSPSP::QueryValue
// -----------------------------------------------------------------------------
MAknQueryValue* CTestSDKPopupsSPSP::QueryValue() const
    {
    return CAknPopupSettingPage::QueryValue();
    }

// -----------------------------------------------------------------------------
// CTestSDKPopupsSPSP::SelectCurrentItemL
// -----------------------------------------------------------------------------
void CTestSDKPopupsSPSP::SelectCurrentItemL()
    {
    CAknPopupSettingPage::SelectCurrentItemL();
    }

// -----------------------------------------------------------------------------
// CTestSDKPopupsSPSP::WriteInternalStateL
// -----------------------------------------------------------------------------
void CTestSDKPopupsSPSP::WriteInternalStateL( RWriteStream& aWriteStream ) const
    {
    CAknPopupSettingPage::WriteInternalStateL( aWriteStream );
    }

// -----------------------------------------------------------------------------
// CTestSDKPopupsSPSP::Reserved_2
// -----------------------------------------------------------------------------
void CTestSDKPopupsSPSP::Reserved_2()
    {
    CAknPopupSettingPage::Reserved_2();
    }
