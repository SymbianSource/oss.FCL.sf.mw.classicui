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
* Description:  Test aknslidersettingpage.h
*
*/

//INCLUDE
#include "testaknslidersettingpageprotected.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSliderSettingPage::CTestSliderSettingPage
// -----------------------------------------------------------------------------
// 
CTestSliderSettingPage::CTestSliderSettingPage( TInt aResourceID, 
    TInt& aSliderValue ):CAknSliderSettingPage( aResourceID, aSliderValue )
    {
    
    }

// -----------------------------------------------------------------------------
// CTestSliderSettingPage::CTestSliderSettingPage
// -----------------------------------------------------------------------------
// 
CTestSliderSettingPage::CTestSliderSettingPage( const TDesC* aSettingTitleText, 
    TInt aSettingNumber, 
    TInt aControlType,
    TInt aEditorResourceId, 
    TInt aSettingPageResourceId,
    TInt& aSliderValue ):CAknSliderSettingPage( aSettingTitleText, 
        aSettingNumber, 
        aControlType,
        aEditorResourceId, 
        aSettingPageResourceId,
        aSliderValue )
    {
    
    }

// -----------------------------------------------------------------------------
// CTestSliderSettingPage::~CTestSliderSettingPage
// -----------------------------------------------------------------------------
// 
CTestSliderSettingPage::~CTestSliderSettingPage()
    {
    
    }

// -----------------------------------------------------------------------------
// CTestSliderSettingPage::DoSizeChanged
// -----------------------------------------------------------------------------
// 
void CTestSliderSettingPage::DoSizeChanged()
    {
    SizeChanged();
    }

// -----------------------------------------------------------------------------
// CTestSliderSettingPage::DoDraw
// -----------------------------------------------------------------------------
// 
void CTestSliderSettingPage::DoDraw(const TRect &aRect) const
    {
    Draw( aRect );
    }

// -----------------------------------------------------------------------------
// CTestSliderSettingPage::DoWriteInternalStateL
// -----------------------------------------------------------------------------
// 
void CTestSliderSettingPage::DoWriteInternalStateL(RWriteStream& aWriteStream) const
    {
    WriteInternalStateL( aWriteStream );
    }

// -----------------------------------------------------------------------------
// CTestSliderSettingPage::DoUpdateSettingL
// -----------------------------------------------------------------------------
// 
void CTestSliderSettingPage::DoUpdateSettingL()
    {
    UpdateSettingL();
    }

// -----------------------------------------------------------------------------
// CTestSliderSettingPage::DoAcceptSettingL
// -----------------------------------------------------------------------------
// 
void CTestSliderSettingPage::DoAcceptSettingL()
    {
    AcceptSettingL();
    }

// -----------------------------------------------------------------------------
// CTestSliderSettingPage::DoRestoreOriginalSettingL
// -----------------------------------------------------------------------------
// 
void CTestSliderSettingPage::DoRestoreOriginalSettingL()
    {
    RestoreOriginalSettingL();
    }

// -----------------------------------------------------------------------------
// CTestSliderSettingPage::DoActivateGc
// -----------------------------------------------------------------------------
//
void CTestSliderSettingPage::DoActivateGc() const
    {
    ActivateGc();
    }

// -----------------------------------------------------------------------------
// CTestSliderSettingPage::DoDeactivateGc
// -----------------------------------------------------------------------------
//
void CTestSliderSettingPage::DoDeactivateGc() const
    {
    DeactivateGc();
    }

//End file


