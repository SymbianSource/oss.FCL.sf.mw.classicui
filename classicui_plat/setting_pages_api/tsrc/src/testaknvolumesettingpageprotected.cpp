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
* Description:  Test aknvolumesettingpage.h
*
*/

//INCLUDE
#include "testaknvolumesettingpageprotected.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestVolumeSettingPage::CTestVolumeSettingPage
// -----------------------------------------------------------------------------
//
CTestVolumeSettingPage::CTestVolumeSettingPage( TInt aResourceID, 
    TInt& aVolume ):CAknVolumeSettingPage( aResourceID, aVolume )
    {
    
    }

// -----------------------------------------------------------------------------
// CTestVolumeSettingPage::CTestVolumeSettingPage
// -----------------------------------------------------------------------------
//
CTestVolumeSettingPage::CTestVolumeSettingPage( const TDesC* aSettingTitleText, 
    TInt aSettingNumber, 
    TInt aControlType,
    TInt aEditorResourceId, 
    TInt aSettingPageResourceId,
    TInt& aVolume ):CAknVolumeSettingPage( aSettingTitleText,
        aSettingNumber, 
        aControlType,
        aEditorResourceId,
        aSettingPageResourceId,
        aVolume )
    {
    
    }

// -----------------------------------------------------------------------------
// CTestVolumeSettingPage::~CTestVolumeSettingPage
// -----------------------------------------------------------------------------
//
CTestVolumeSettingPage::~CTestVolumeSettingPage()
    {
    
    }

// -----------------------------------------------------------------------------
// CTestVolumeSettingPage::DoConstructL
// -----------------------------------------------------------------------------
//
void CTestVolumeSettingPage::DoConstructL()
    {
    ConstructL();
    }

// -----------------------------------------------------------------------------
// CTestVolumeSettingPage::DoVolumeControl
// -----------------------------------------------------------------------------
//
CAknVolumeControl* CTestVolumeSettingPage::DoVolumeControl()
    {
    return VolumeControl();
    }

// -----------------------------------------------------------------------------
// CTestVolumeSettingPage::DoSizeChanged
// -----------------------------------------------------------------------------
//
void CTestVolumeSettingPage::DoSizeChanged()
    {
    SizeChanged();
    }

// -----------------------------------------------------------------------------
// CTestVolumeSettingPage::DoDraw
// -----------------------------------------------------------------------------
//
void CTestVolumeSettingPage::DoDraw(const TRect &aRect) const
    {
    Draw( aRect );
    }

// -----------------------------------------------------------------------------
// CTestVolumeSettingPage::DoWriteInternalStateL
// -----------------------------------------------------------------------------
//
void CTestVolumeSettingPage::DoWriteInternalStateL(RWriteStream& aWriteStream) const
    {
    WriteInternalStateL( aWriteStream );
    }

// -----------------------------------------------------------------------------
// CTestVolumeSettingPage::DoUpdateSettingL
// -----------------------------------------------------------------------------
//
void CTestVolumeSettingPage::DoUpdateSettingL()
    {
    UpdateSettingL();
    }

// -----------------------------------------------------------------------------
// CTestVolumeSettingPage::DoAcceptSettingL
// -----------------------------------------------------------------------------
//
void CTestVolumeSettingPage::DoAcceptSettingL()
    {
    AcceptSettingL();
    }

// -----------------------------------------------------------------------------
// CTestVolumeSettingPage::DoRestoreOriginalSettingL
// -----------------------------------------------------------------------------
//
void CTestVolumeSettingPage::DoRestoreOriginalSettingL()
    {
    RestoreOriginalSettingL();
    }

// -----------------------------------------------------------------------------
// CTestVolumeSettingPage::DoActivateGc
// -----------------------------------------------------------------------------
//
void CTestVolumeSettingPage::DoActivateGc() const
    {
    ActivateGc();
    }

// -----------------------------------------------------------------------------
// CTestVolumeSettingPage::DoDeactivateGc
// -----------------------------------------------------------------------------
//
void CTestVolumeSettingPage::DoDeactivateGc() const
    {
    DeactivateGc();
    }

//End file


