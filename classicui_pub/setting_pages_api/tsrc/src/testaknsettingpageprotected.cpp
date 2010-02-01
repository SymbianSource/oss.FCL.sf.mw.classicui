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
* Description:  Test aknsettingpage.h
*
*/

//INCLUDE
#include "testaknsettingpageprotected.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSettingPage::CTestSettingPage
// -----------------------------------------------------------------------------
//
CTestSettingPage::CTestSettingPage( TInt 
    aSettingPageResourceId ):CAknSettingPage( aSettingPageResourceId )
    {
    RFile file;
    }

// -----------------------------------------------------------------------------
// CTestSettingPage::CTestSettingPage
// -----------------------------------------------------------------------------
//
CTestSettingPage::CTestSettingPage( const TDesC* aSettingTitleText, 
    TInt aSettingNumber, 
    TInt aControlType,
    TInt aEditorResourceId, 
    TInt aSettingPageResourceId ):CAknSettingPage( aSettingTitleText, 
        aSettingNumber,
        aControlType,
        aEditorResourceId, 
        aSettingPageResourceId )
    {
    
    }

// -----------------------------------------------------------------------------
// CTestSettingPage::~CTestSettingPage
// -----------------------------------------------------------------------------
//
CTestSettingPage::~CTestSettingPage()
    {
    
    }

// -----------------------------------------------------------------------------
// CTestSettingPage::TestSizeChanged
// -----------------------------------------------------------------------------
//
void CTestSettingPage::TestSizeChanged()
    {
    SizeChanged();
    }

// -----------------------------------------------------------------------------
// CTestSettingPage::TestFocusChanged
// -----------------------------------------------------------------------------
//
void CTestSettingPage::TestFocusChanged(TDrawNow aDrawNow)
    {
    FocusChanged( aDrawNow );
    }

// -----------------------------------------------------------------------------
// CTestSettingPage::TestProcessCommandL
// -----------------------------------------------------------------------------
//
void CTestSettingPage::TestProcessCommandL(TInt aCommandId)
    {
    ProcessCommandL( aCommandId );
    }

// -----------------------------------------------------------------------------
// CTestSettingPage::TestHandleControlEventL
// -----------------------------------------------------------------------------
//
void CTestSettingPage::TestHandleControlEventL(CCoeControl* aControl,TCoeEvent aEventType)
    {
    HandleControlEventL( aControl, aEventType );
    }

// -----------------------------------------------------------------------------
// CTestSettingPage::TestOkToExitL
// -----------------------------------------------------------------------------
//
TBool CTestSettingPage::TestOkToExitL(TBool aAccept)
    {
    return OkToExitL( aAccept );
    }

// -----------------------------------------------------------------------------
// CTestSettingPage::TestDynamicInitL
// -----------------------------------------------------------------------------
//
void CTestSettingPage::TestDynamicInitL()
    {
    DynamicInitL();
    }

// -----------------------------------------------------------------------------
// CTestSettingPage::TestUpdateSettingL
// -----------------------------------------------------------------------------
//
void CTestSettingPage::TestUpdateSettingL()
    {
    UpdateSettingL();
    }

// -----------------------------------------------------------------------------
// CTestSettingPage::TestAcceptSettingL
// -----------------------------------------------------------------------------
//
void CTestSettingPage::TestAcceptSettingL()
    {
    AcceptSettingL();
    }

// -----------------------------------------------------------------------------
// CTestSettingPage::TestRestoreOriginalSettingL
// -----------------------------------------------------------------------------
//
void CTestSettingPage::TestRestoreOriginalSettingL()
    {
    RestoreOriginalSettingL();
    }

// -----------------------------------------------------------------------------
// CTestSettingPage::TestDisplayMenuL
// -----------------------------------------------------------------------------
//
void CTestSettingPage::TestDisplayMenuL()
    {
    DisplayMenuL();
    }

// -----------------------------------------------------------------------------
// CTestSettingPage::TestHideMenu
// -----------------------------------------------------------------------------
//
void CTestSettingPage::TestHideMenu()
    {
    HideMenu();
    }

// -----------------------------------------------------------------------------
// CTestSettingPage::TestSetFocusToEditor
// -----------------------------------------------------------------------------
//
void CTestSettingPage::TestSetFocusToEditor()
    {
    SetFocusToEditor();
    }

// -----------------------------------------------------------------------------
// CTestSettingPage::TestSelectCurrentItemL
// -----------------------------------------------------------------------------
//
void CTestSettingPage::TestSelectCurrentItemL()
    {
    SelectCurrentItemL();
    }

// -----------------------------------------------------------------------------
// CTestSettingPage::TestBaseConstructL
// -----------------------------------------------------------------------------
//
void CTestSettingPage::TestBaseConstructL()
    {
    BaseConstructL();
    }

// -----------------------------------------------------------------------------
// CTestSettingPage::TestDismissL
// -----------------------------------------------------------------------------
//
void CTestSettingPage::TestDismissL( TBool aAccept )
    {
    DismissL( aAccept );
    }

// -----------------------------------------------------------------------------
// CTestSettingPage::TestMenuShowing
// -----------------------------------------------------------------------------
//
TBool CTestSettingPage::TestMenuShowing() const
    {
    return MenuShowing();
    }

// -----------------------------------------------------------------------------
// CTestSettingPage::TestConstructFromResourceL
// -----------------------------------------------------------------------------
//
void CTestSettingPage::TestConstructFromResourceL( TInt aResourceId)
    {
    ConstructFromResourceL( aResourceId );
    }

// -----------------------------------------------------------------------------
// CTestSettingPage::TestConstructFromResourceL
// -----------------------------------------------------------------------------
//
void CTestSettingPage::TestConstructFromResourceL(TResourceReader& aRes)
    {
    ConstructFromResourceL( aRes );
    }

// -----------------------------------------------------------------------------
// CTestSettingPage::TestAttemptExitL
// -----------------------------------------------------------------------------
//
void CTestSettingPage::TestAttemptExitL(TBool aAccept)
    {
    AttemptExitL( aAccept );
    }

// -----------------------------------------------------------------------------
// CTestSettingPage::TestWaiting
// -----------------------------------------------------------------------------
//
TBool CTestSettingPage::TestWaiting()
    {
    return Waiting();
    }

// -----------------------------------------------------------------------------
// CTestSettingPage::TestCba
// -----------------------------------------------------------------------------
//
CEikButtonGroupContainer* CTestSettingPage::TestCba() const 
    {
    return Cba();
    }

// -----------------------------------------------------------------------------
// CTestSettingPage::TestDefaultCbaResourceId
// -----------------------------------------------------------------------------
//
TInt CTestSettingPage::TestDefaultCbaResourceId() const
    {
    return DefaultCbaResourceId();
    }

// -----------------------------------------------------------------------------
// CTestSettingPage::TestOfferKeyEventL
// -----------------------------------------------------------------------------
//
TKeyResponse CTestSettingPage::TestOfferKeyEventL( const TKeyEvent& aKeyEvent, 
    TEventCode aType)
    {
    return OfferKeyEventL( aKeyEvent, aType );
    }

// -----------------------------------------------------------------------------
// CTestSettingPage::TestStandardSettingPageLayout
// -----------------------------------------------------------------------------
//
void CTestSettingPage::TestStandardSettingPageLayout()
    {
    StandardSettingPageLayout();
    }

// -----------------------------------------------------------------------------
// CTestSettingPage::TestIsBaseConstructed
// -----------------------------------------------------------------------------
//
TBool CTestSettingPage::TestIsBaseConstructed()
    {
    return IsBaseConstructed();
    }

// -----------------------------------------------------------------------------
// CTestSettingPage::TestSettingPageResourceId
// -----------------------------------------------------------------------------
//
TInt CTestSettingPage::TestSettingPageResourceId()
    {
    return SettingPageResourceId();
    }

// -----------------------------------------------------------------------------
// CTestSettingPage::TestBaseDraw
// -----------------------------------------------------------------------------
//
void CTestSettingPage::TestBaseDraw(const TRect& aRect) const
    {
    BaseDraw( aRect );
    }

// -----------------------------------------------------------------------------
// CTestSettingPage::TestResetFlags
// -----------------------------------------------------------------------------
//
void CTestSettingPage::TestResetFlags()
    {
    ResetFlags();
    }

// -----------------------------------------------------------------------------
// CTestSettingPage::TestPostDisplayCheckL
// -----------------------------------------------------------------------------
//
TBool CTestSettingPage::TestPostDisplayCheckL()
    {
    return PostDisplayCheckL();
    }

// -----------------------------------------------------------------------------
// CTestSettingPage::TestUpdateCbaL
// -----------------------------------------------------------------------------
//
void CTestSettingPage::TestUpdateCbaL()
    {
    UpdateCbaL();
    }

// -----------------------------------------------------------------------------
// CTestSettingPage::TestDataValidity
// -----------------------------------------------------------------------------
//
TBool CTestSettingPage::TestDataValidity() const
    {
    return DataValidity();
    }

// -----------------------------------------------------------------------------
// CTestSettingPage::TestSetDataValidity
// -----------------------------------------------------------------------------
//
void CTestSettingPage::TestSetDataValidity(TBool aValid)
    {
    SetDataValidity( aValid );
    }

// -----------------------------------------------------------------------------
// CTestSettingPage::TestCheckAndSetDataValidity
// -----------------------------------------------------------------------------
//
void CTestSettingPage::TestCheckAndSetDataValidity()
    {
    CheckAndSetDataValidity();
    }

// -----------------------------------------------------------------------------
// CTestSettingPage::TestSetEmphasis
// -----------------------------------------------------------------------------
//
void CTestSettingPage::TestSetEmphasis(CCoeControl* aMenuControl,TBool aEmphasis)
    {
    SetEmphasis( aMenuControl, aEmphasis );
    }

// -----------------------------------------------------------------------------
// CTestSettingPage::TestDynInitMenuPaneL
// -----------------------------------------------------------------------------
//
void CTestSettingPage::TestDynInitMenuPaneL( TInt aResourceId, CEikMenuPane* aMenuPane )
    {
    DynInitMenuPaneL( aResourceId, aMenuPane );
    }

// -----------------------------------------------------------------------------
// CTestSettingPage::TestHandleResourceChange
// -----------------------------------------------------------------------------
//
void CTestSettingPage::TestHandleResourceChange(TInt aType)
    {
    HandleResourceChange( aType );
    }

// -----------------------------------------------------------------------------
// CTestSettingPage::TestCountComponentControls
// -----------------------------------------------------------------------------
//
TInt CTestSettingPage::TestCountComponentControls() const
    {
    return CountComponentControls();
    }

// -----------------------------------------------------------------------------
// CTestSettingPage::TestComponentControl
// -----------------------------------------------------------------------------
//
CCoeControl* CTestSettingPage::TestComponentControl(TInt anIndex) const
    {
    return ComponentControl( anIndex );
    }

// -----------------------------------------------------------------------------
// CTestSettingPage::TestHandlePointerEventL
// -----------------------------------------------------------------------------
//
void CTestSettingPage::TestHandlePointerEventL(const TPointerEvent& aPointerEvent)
    {
    HandlePointerEventL( aPointerEvent );
    }

// -----------------------------------------------------------------------------
// CTestSettingPage::TestInputCapabilities
// -----------------------------------------------------------------------------
//
TCoeInputCapabilities CTestSettingPage::TestInputCapabilities() const
    {
    return InputCapabilities();
    }

// -----------------------------------------------------------------------------
// CTestSettingPage::TestInvalidDataCbaResourceId
// -----------------------------------------------------------------------------
//
TInt CTestSettingPage::TestInvalidDataCbaResourceId() const
    {
    return InvalidDataCbaResourceId();
    }

// -----------------------------------------------------------------------------
// CTestSettingPage::TestMopSupplyObject
// -----------------------------------------------------------------------------
//
TTypeUid::Ptr CTestSettingPage::TestMopSupplyObject(TTypeUid aId)
    {
    return MopSupplyObject( aId );
    }

// -----------------------------------------------------------------------------
// CTestSettingPage::TestWriteInternalStateL
// -----------------------------------------------------------------------------
//
void CTestSettingPage::TestWriteInternalStateL(RWriteStream& aWriteStream) const
    {
    WriteInternalStateL( aWriteStream );
    }

// -----------------------------------------------------------------------------
// CTestSettingPage::DoActivateGc
// -----------------------------------------------------------------------------
//
void CTestSettingPage::DoActivateGc() const
    {
    ActivateGc();
    }

// -----------------------------------------------------------------------------
// CTestSettingPage::DoDeactivateGc
// -----------------------------------------------------------------------------
//
void CTestSettingPage::DoDeactivateGc() const
    {
    DeactivateGc();
    }

// -----------------------------------------------------------------------------
// CTestSettingPage::GetWindow
// -----------------------------------------------------------------------------
//
RWindow& CTestSettingPage::GetWindow() const
    {
    return Window();
    }

// -----------------------------------------------------------------------------
// CTestSettingPage::TestTextLabel
// -----------------------------------------------------------------------------
//
CEikLabel* CTestSettingPage::TestTextLabel() const
    {
    return TextLabel();
    }

// -----------------------------------------------------------------------------
// CTestSettingPage::TestShadowText
// -----------------------------------------------------------------------------
//  
CEikLabel* CTestSettingPage::TestShadowText() const
    {
    return ShadowText();
    }

// -----------------------------------------------------------------------------
// CTestSettingPage::SetiUpdateMode
// -----------------------------------------------------------------------------
// 
void CTestSettingPage::SetiUpdateMode( TInt aUpdateMode )
    {
    iUpdateMode = aUpdateMode;
    }
//End file


