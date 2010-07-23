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
* Description:  Test aknmfnesettingpage.h
*
*/

//INCLUDE 
#include "testaknmfnesettingpageprotected.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestMfneSettingPage::CTestMfneSettingPage
// -----------------------------------------------------------------------------
//
CTestMfneSettingPage::CTestMfneSettingPage( TInt aResourceId ):CAknMfneSettingPage( aResourceId )
    {
    
    }

// -----------------------------------------------------------------------------
// CTestMfneSettingPage::CTestMfneSettingPage
// -----------------------------------------------------------------------------
//
CTestMfneSettingPage::CTestMfneSettingPage( const TDesC* aSettingTitleText, 
    TInt aSettingNumber, 
    TInt aControlType,
    TInt aEditorResourceId, 
    TInt aSettingPageResourceId ):CAknMfneSettingPage( aSettingTitleText,
        aSettingNumber, 
        aControlType,
        aEditorResourceId,
        aSettingPageResourceId )
    {
    
    }

// -----------------------------------------------------------------------------
// CTestMfneSettingPage::~CTestMfneSettingPage
// -----------------------------------------------------------------------------
//
CTestMfneSettingPage::~CTestMfneSettingPage()
    {
    
    }

// -----------------------------------------------------------------------------
// CTestMfneSettingPage::DoBaseConstructL
// -----------------------------------------------------------------------------
//
void CTestMfneSettingPage::DoBaseConstructL()
    {
    BaseConstructL();
    }

// -----------------------------------------------------------------------------
// CTestMfneSettingPage::DoSizeChanged
// -----------------------------------------------------------------------------
//
void CTestMfneSettingPage::DoSizeChanged()
    {
    SizeChanged();
    }

// -----------------------------------------------------------------------------
// CTestMfneSettingPage::DoDraw
// -----------------------------------------------------------------------------
//
void CTestMfneSettingPage::DoDraw(const TRect& aRect) const
    {
    Draw( aRect );
    }

// -----------------------------------------------------------------------------
// CTestMfneSettingPage::DoMfne
// -----------------------------------------------------------------------------
//
CEikMfne* CTestMfneSettingPage::DoMfne() const
    {
    return Mfne();
    }

// -----------------------------------------------------------------------------
// CTestMfneSettingPage::DoCheckAndSetDataValidity
// -----------------------------------------------------------------------------
//
void CTestMfneSettingPage::DoCheckAndSetDataValidity()
    {
    CheckAndSetDataValidity();
    }

// -----------------------------------------------------------------------------
// CTestMfneSettingPage::DoHandleControlEventL
// -----------------------------------------------------------------------------
//
void CTestMfneSettingPage::DoHandleControlEventL(CCoeControl* aControl,
    TCoeEvent aEventType)
    {
    HandleControlEventL( aControl, aEventType );
    }

// -----------------------------------------------------------------------------
// CTestMfneSettingPage::DoConstructL
// -----------------------------------------------------------------------------
//
void CTestMfneSettingPage::DoConstructL()
    {
    ConstructL();
    }

// -----------------------------------------------------------------------------
// CTestMfneSettingPage::DoCountComponentControls
// -----------------------------------------------------------------------------
//
TInt CTestMfneSettingPage::DoCountComponentControls() const
    {
    return CountComponentControls();
    }

// -----------------------------------------------------------------------------
// CTestMfneSettingPage::DoComponentControl
// -----------------------------------------------------------------------------
//
CCoeControl* CTestMfneSettingPage::DoComponentControl(TInt anIndex) const
    {
    return ComponentControl( anIndex );
    }

// -----------------------------------------------------------------------------
// CTestMfneSettingPage::DoActivateGc
// -----------------------------------------------------------------------------
//
void CTestMfneSettingPage::DoActivateGc()
    {
    ActivateGc();
    }

// -----------------------------------------------------------------------------
// CTestMfneSettingPage::DoDeactivateGc
// -----------------------------------------------------------------------------
//
void CTestMfneSettingPage::DoDeactivateGc()
    {
    DeactivateGc();
    }

// -----------------------------------------------------------------------------
// CTestDateSettingPage::CTestDateSettingPage
// -----------------------------------------------------------------------------
//
CTestDateSettingPage::CTestDateSettingPage( TInt aResourceID, 
        TTime& aDateValue ):CAknDateSettingPage( aResourceID, 
            aDateValue )
    {
    
    }

// -----------------------------------------------------------------------------
// CTestDateSettingPage::CTestDateSettingPage
// -----------------------------------------------------------------------------
//
CTestDateSettingPage::CTestDateSettingPage( const TDesC* aSettingTitleText, 
    TInt aSettingNumber, 
    TInt aControlType,
    TInt aEditorResourceId, 
    TInt aSettingPageResourceId,    
    TTime& aDateValue ):CAknDateSettingPage( aSettingTitleText,
        aSettingNumber, 
        aControlType,
        aEditorResourceId, 
        aSettingPageResourceId,
        aDateValue )
    {
    
    }

// -----------------------------------------------------------------------------
// CTestDateSettingPage::~CTestDateSettingPage
// -----------------------------------------------------------------------------
//
CTestDateSettingPage::~CTestDateSettingPage()
    {
    
    }

// -----------------------------------------------------------------------------
// CTestDateSettingPage::DoUpdateSettingL
// -----------------------------------------------------------------------------
//
void CTestDateSettingPage::DoUpdateSettingL()
    {
    UpdateSettingL();
    }

// -----------------------------------------------------------------------------
// CTestDateSettingPage::DoAcceptSettingL
// -----------------------------------------------------------------------------
//
void CTestDateSettingPage::DoAcceptSettingL()
    {
    AcceptSettingL();
    }
// -----------------------------------------------------------------------------
// CTestDateSettingPage::DoRestoreOriginalSettingL
// -----------------------------------------------------------------------------
//
void CTestDateSettingPage::DoRestoreOriginalSettingL()
    {
    RestoreOriginalSettingL();
    }

// -----------------------------------------------------------------------------
// CTestDateSettingPage::DoWriteInternalStateL
// -----------------------------------------------------------------------------
//
void CTestDateSettingPage::DoWriteInternalStateL(RWriteStream& aWriteStream) const
    {
    WriteInternalStateL( aWriteStream );
    }

// -----------------------------------------------------------------------------
// CTestTimeSettingPage::CTestTimeSettingPage
// -----------------------------------------------------------------------------
//
CTestTimeSettingPage::CTestTimeSettingPage( TInt aResourceID, 
    TTime& aTimeValue ):CAknTimeSettingPage( aResourceID, aTimeValue )
    {
    
    }

// -----------------------------------------------------------------------------
// CTestTimeSettingPage::CTestTimeSettingPage
// -----------------------------------------------------------------------------
//
CTestTimeSettingPage::CTestTimeSettingPage( const TDesC* aSettingTitleText, 
    TInt aSettingNumber, 
    TInt aControlType,
    TInt aEditorResourceId, 
    TInt aSettingPageResourceId,    
    TTime& aTimeValue ):CAknTimeSettingPage( aSettingTitleText,
        aSettingNumber, 
        aControlType,
        aEditorResourceId, 
        aSettingPageResourceId,
        aTimeValue )
    {
    
    }

// -----------------------------------------------------------------------------
// CTestTimeSettingPage::~CTestTimeSettingPage
// -----------------------------------------------------------------------------
//
CTestTimeSettingPage::~CTestTimeSettingPage()
    {
    
    }

// -----------------------------------------------------------------------------
// CTestTimeSettingPage::DoUpdateSettingL
// -----------------------------------------------------------------------------
//
void CTestTimeSettingPage::DoUpdateSettingL()
    {
    UpdateSettingL();
    }

// -----------------------------------------------------------------------------
// CTestTimeSettingPage::DoAcceptSettingL
// -----------------------------------------------------------------------------
//
void CTestTimeSettingPage::DoAcceptSettingL()
    {
    AcceptSettingL();
    }

// -----------------------------------------------------------------------------
// CTestTimeSettingPage::DoRestoreOriginalSettingL
// -----------------------------------------------------------------------------
//
void CTestTimeSettingPage::DoRestoreOriginalSettingL()
    {
    RestoreOriginalSettingL();
    }

// -----------------------------------------------------------------------------
// CTestTimeSettingPage::DoWriteInternalStateL
// -----------------------------------------------------------------------------
//
void CTestTimeSettingPage::DoWriteInternalStateL(RWriteStream& aWriteStream) const
    {
    WriteInternalStateL( aWriteStream );
    }

// -----------------------------------------------------------------------------
// CTestDurationSettingPage::CTestDurationSettingPage
// -----------------------------------------------------------------------------
//
CTestDurationSettingPage::CTestDurationSettingPage( TInt aResourceID, 
        TTimeIntervalSeconds& aDurationValue ):CAknDurationSettingPage( aResourceID,
        aDurationValue )
    {
    
    }

// -----------------------------------------------------------------------------
// CTestDurationSettingPage::CTestDurationSettingPage
// -----------------------------------------------------------------------------
//
CTestDurationSettingPage::CTestDurationSettingPage( const TDesC* aSettingTitleText, 
    TInt aSettingNumber, 
    TInt aControlType,
    TInt aEditorResourceId, 
    TInt aSettingPageResourceId,    
    TTimeIntervalSeconds& aDurationValue ):CAknDurationSettingPage( aSettingTitleText, 
        aSettingNumber, 
        aControlType,
        aEditorResourceId,
        aSettingPageResourceId,
        aDurationValue )
    {
    
    }

// -----------------------------------------------------------------------------
// CTestDurationSettingPage::~CTestDurationSettingPage
// -----------------------------------------------------------------------------
//
CTestDurationSettingPage::~CTestDurationSettingPage()
    {
    
    }

// -----------------------------------------------------------------------------
// CTestDurationSettingPage::DoUpdateSettingL
// -----------------------------------------------------------------------------
//
void CTestDurationSettingPage::DoUpdateSettingL()
    {
    UpdateSettingL();
    }

// -----------------------------------------------------------------------------
// CTestDurationSettingPage::DoAcceptSettingL
// -----------------------------------------------------------------------------
//
void CTestDurationSettingPage::DoAcceptSettingL()
    {
    AcceptSettingL();
    }

// -----------------------------------------------------------------------------
// CTestDurationSettingPage::DoRestoreOriginalSettingL
// -----------------------------------------------------------------------------
//
void CTestDurationSettingPage::DoRestoreOriginalSettingL()
    {
    RestoreOriginalSettingL();
    }

// -----------------------------------------------------------------------------
// CTestDurationSettingPage::DoWriteInternalStateL
// -----------------------------------------------------------------------------
//
void CTestDurationSettingPage::DoWriteInternalStateL(RWriteStream& aWriteStream) const
    {
    WriteInternalStateL( aWriteStream );
    }

// -----------------------------------------------------------------------------
// CTestTimeOffsetSettingPage::CTestTimeOffsetSettingPage
// -----------------------------------------------------------------------------
//
CTestTimeOffsetSettingPage::CTestTimeOffsetSettingPage( TInt aResourceID, 
        TTimeIntervalSeconds& aTimeOffsetValue ):CAknTimeOffsetSettingPage( aResourceID, 
            aTimeOffsetValue )
    {
    
    }

// -----------------------------------------------------------------------------
// CTestTimeOffsetSettingPage::CTestTimeOffsetSettingPage
// -----------------------------------------------------------------------------
//
CTestTimeOffsetSettingPage::CTestTimeOffsetSettingPage( const TDesC* aSettingTitleText, 
    TInt aSettingNumber, 
    TInt aControlType,
    TInt aEditorResourceId, 
    TInt aSettingPageResourceId,    
    TTimeIntervalSeconds&   aTimeOffsetValue ):CAknTimeOffsetSettingPage( aSettingTitleText,
        aSettingNumber, 
        aControlType,
        aEditorResourceId,
        aSettingPageResourceId,
        aTimeOffsetValue )
    {
    
    }

// -----------------------------------------------------------------------------
// CTestTimeOffsetSettingPage::~CTestTimeOffsetSettingPage
// -----------------------------------------------------------------------------
//
CTestTimeOffsetSettingPage::~CTestTimeOffsetSettingPage()
    {
    
    }

// -----------------------------------------------------------------------------
// CTestTimeOffsetSettingPage::DoUpdateSettingL
// -----------------------------------------------------------------------------
//
void CTestTimeOffsetSettingPage::DoUpdateSettingL()
    {
    UpdateSettingL();
    }

// -----------------------------------------------------------------------------
// CTestTimeOffsetSettingPage::DoAcceptSettingL
// -----------------------------------------------------------------------------
//
void CTestTimeOffsetSettingPage::DoAcceptSettingL()
    {
    AcceptSettingL();
    }

// -----------------------------------------------------------------------------
// CTestTimeOffsetSettingPage::DoRestoreOriginalSettingL
// -----------------------------------------------------------------------------
//
void CTestTimeOffsetSettingPage::DoRestoreOriginalSettingL()
    {
    RestoreOriginalSettingL();
    }

// -----------------------------------------------------------------------------
// CTestTimeOffsetSettingPage::DoWriteInternalStateL
// -----------------------------------------------------------------------------
//
void CTestTimeOffsetSettingPage::DoWriteInternalStateL(RWriteStream& aWriteStream) const
    {
    WriteInternalStateL( aWriteStream );
    }

// -----------------------------------------------------------------------------
// CTestIpFieldSettingPage::CTestIpFieldSettingPage
// -----------------------------------------------------------------------------
//
CTestIpFieldSettingPage::CTestIpFieldSettingPage( TInt aResourceID, 
        TInetAddr& aIpAddress ):CAknIpFieldSettingPage( aResourceID,
            aIpAddress )
    {
    
    }

// -----------------------------------------------------------------------------
// CTestIpFieldSettingPage::CTestIpFieldSettingPage
// -----------------------------------------------------------------------------
//
CTestIpFieldSettingPage::CTestIpFieldSettingPage( const TDesC* aSettingTitleText, 
    TInt aSettingNumber, 
    TInt aControlType,
    TInt aEditorResourceId, 
    TInt aSettingPageResourceId,
    TInetAddr&  aIpAddress ):CAknIpFieldSettingPage( aSettingTitleText,
        aSettingNumber, 
        aControlType,
        aEditorResourceId,
        aSettingPageResourceId,
        aIpAddress )
    {
    
    }

// -----------------------------------------------------------------------------
// CTestIpFieldSettingPage::~CTestIpFieldSettingPage
// -----------------------------------------------------------------------------
//
CTestIpFieldSettingPage::~CTestIpFieldSettingPage()
    {
    
    }

// -----------------------------------------------------------------------------
// CTestIpFieldSettingPage::DoUpdateSettingL
// -----------------------------------------------------------------------------
//
void CTestIpFieldSettingPage::DoUpdateSettingL()
    {
    UpdateSettingL();
    }

// -----------------------------------------------------------------------------
// CTestIpFieldSettingPage::DoAcceptSettingL
// -----------------------------------------------------------------------------
//
void CTestIpFieldSettingPage::DoAcceptSettingL()
    {
    AcceptSettingL();
    }

// -----------------------------------------------------------------------------
// CTestIpFieldSettingPage::DoRestoreOriginalSettingL
// -----------------------------------------------------------------------------
//
void CTestIpFieldSettingPage::DoRestoreOriginalSettingL()
    {
    RestoreOriginalSettingL();
    }

// -----------------------------------------------------------------------------
// CTestIpFieldSettingPage::DoWriteInternalStateL
// -----------------------------------------------------------------------------
//
void CTestIpFieldSettingPage::DoWriteInternalStateL(RWriteStream& aWriteStream) const
    {
    WriteInternalStateL( aWriteStream );
    }
    
//End file


