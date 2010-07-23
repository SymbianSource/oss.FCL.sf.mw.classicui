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



// [INCLUDE FILES]


#include <eiktxlbx.h> 
#include <eikfrlb.h>
#include <aknpopup.h>
#include <aknpopuplayout.h>
#include <aknpopupheadingpane.h>
#include <eiklbx.h> 
#include <akndef.h>
#include <eikdef.h>

#include "testsdkpopups.h"
#include "testsdkpopupspl.h"

const TInt KLength = 20;
// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestPLNewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestPLNewL( CStifItemParser& /*aItem*/ )
    {
    CEikFormattedCellListBox* listBox = new (ELeave) CEikFormattedCellListBox;
    CleanupStack::PushL( listBox );
    STIF_ASSERT_NOT_NULL( listBox );
    
    CAknPopupList* popupList = CAknPopupList::NewL( listBox, R_AVKON_SOFTKEYS_SELECT_BACK, AknPopupLayouts::EPopupSNotePopupWindow );
    CleanupStack::PushL( popupList );
    STIF_ASSERT_NOT_NULL( popupList );
    
    CleanupStack::PopAndDestroy( popupList );
    CleanupStack::PopAndDestroy( listBox );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestPLExecuteLD
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestPLExecuteLD( CStifItemParser& /*aItem*/ )
    {
    CEikFormattedCellListBox* listBox = new (ELeave) CEikFormattedCellListBox;
    CleanupStack::PushL( listBox );
    STIF_ASSERT_NOT_NULL( listBox );
    
    CAknPopupList* popupList = CAknPopupList::NewL( listBox, R_AVKON_SOFTKEYS_SELECT_BACK, AknPopupLayouts::EPopupSNotePopupWindow );
    CleanupStack::PushL( popupList );
    STIF_ASSERT_NOT_NULL( popupList );
    
    listBox->ConstructL( popupList, EAknListBoxMenuList );
    TInt popupOk = popupList->ExecuteLD();
    
    CleanupStack::Pop( popupList );
    STIF_ASSERT_EQUALS( 0, popupOk );
    CleanupStack::PopAndDestroy( listBox );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestPLSetTitleL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestPLSetTitleL( CStifItemParser& /*aItem*/ )
    {
    CEikFormattedCellListBox* listBox = new (ELeave) CEikFormattedCellListBox;
    CleanupStack::PushL( listBox );
    STIF_ASSERT_NOT_NULL( listBox );
    
    CAknPopupList* popupList = CAknPopupList::NewL( listBox, R_AVKON_SOFTKEYS_SELECT_BACK, AknPopupLayouts::EPopupSNotePopupWindow );
    CleanupStack::PushL( popupList );
    STIF_ASSERT_NOT_NULL( popupList );
    
    listBox->ConstructL( popupList, EAknListBoxMenuList );
    
    _LIT( KTitle, "PopupList" );
    TBuf<KLength> title( KTitle );
    popupList->SetTitleL( title );
    
    TInt popupOk = popupList->ExecuteLD();
    
    CleanupStack::Pop( popupList );
    STIF_ASSERT_EQUALS( 0, popupOk );
    CleanupStack::PopAndDestroy( listBox );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestPLCancelPopupL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestPLCancelPopupL( CStifItemParser& /*aItem*/ )
    {
    CEikFormattedCellListBox* listBox = new (ELeave) CEikFormattedCellListBox;
    CleanupStack::PushL( listBox );
    STIF_ASSERT_NOT_NULL( listBox );
    
    CAknPopupList* popupList = CAknPopupList::NewL( listBox, R_AVKON_SOFTKEYS_SELECT_BACK, AknPopupLayouts::EPopupSNotePopupWindow );
    CleanupStack::PushL( popupList );
    STIF_ASSERT_NOT_NULL( popupList );
    
    listBox->ConstructL( popupList, EAknListBoxMenuList );
    
    popupList->CancelPopup();
    
    CleanupStack::Pop( popupList );
    CleanupStack::PopAndDestroy( listBox );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestPLButtonGroupContainerL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestPLButtonGroupContainerL( CStifItemParser& /*aItem*/ )
    {
    CEikFormattedCellListBox* listBox = new (ELeave) CEikFormattedCellListBox;
    CleanupStack::PushL( listBox );
    STIF_ASSERT_NOT_NULL( listBox );
    
    CAknPopupList* popupList = CAknPopupList::NewL( listBox, R_AVKON_SOFTKEYS_SELECT_BACK, AknPopupLayouts::EPopupSNotePopupWindow );
    CleanupStack::PushL( popupList );
    STIF_ASSERT_NOT_NULL( popupList );
    
    listBox->ConstructL( popupList, EAknListBoxMenuList );
    
    CEikButtonGroupContainer* container = popupList->ButtonGroupContainer();
    STIF_ASSERT_NOT_NULL( container );
    
    TInt popupOk = popupList->ExecuteLD();
    
    CleanupStack::Pop( popupList );
    STIF_ASSERT_EQUALS( 0, popupOk );
    CleanupStack::PopAndDestroy( listBox );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestPLHeadingL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestPLHeadingL( CStifItemParser& /*aItem*/ )
    {
    CEikFormattedCellListBox* listBox = new (ELeave) CEikFormattedCellListBox;
    CleanupStack::PushL( listBox );
    STIF_ASSERT_NOT_NULL( listBox );
    
    CAknPopupList* popupList = CAknPopupList::NewL( listBox, R_AVKON_SOFTKEYS_SELECT_BACK, AknPopupLayouts::EPopupSNotePopupWindow );
    CleanupStack::PushL( popupList );
    STIF_ASSERT_NOT_NULL( popupList );
    
    listBox->ConstructL( popupList, EAknListBoxMenuList );
    
    _LIT( KTitle, "PopupList" );
    TBuf<KLength> title( KTitle );
    popupList->SetTitleL( title );
    
    CAknPopupHeadingPane* pane = popupList->Heading();
    STIF_ASSERT_NOT_NULL( pane );
    
    TInt popupOk = popupList->ExecuteLD();
    
    CleanupStack::Pop( popupList );
    STIF_ASSERT_EQUALS( 0, popupOk );
    CleanupStack::PopAndDestroy( listBox );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestPLHeadingConstL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestPLHeadingConstL( CStifItemParser& /*aItem*/ )
    {
    CEikFormattedCellListBox* listBox = new (ELeave) CEikFormattedCellListBox;
    CleanupStack::PushL( listBox );
    STIF_ASSERT_NOT_NULL( listBox );
    
    CAknPopupList* popupList = CAknPopupList::NewL( listBox, R_AVKON_SOFTKEYS_SELECT_BACK, AknPopupLayouts::EPopupSNotePopupWindow );
    CleanupStack::PushL( popupList );
    STIF_ASSERT_NOT_NULL( popupList );
    
    listBox->ConstructL( popupList, EAknListBoxMenuList );
    
    _LIT( KTitle, "PopupList" );
    TBuf<KLength> title( KTitle );
    popupList->SetTitleL( title );
    
    const CAknPopupList* popupListConst = popupList;
    CAknPopupHeadingPane* pane = popupListConst->Heading();
    STIF_ASSERT_NOT_NULL( pane );
    
    TInt popupOk = popupList->ExecuteLD();
    
    CleanupStack::Pop( popupList );
    STIF_ASSERT_EQUALS( 0, popupOk );
    CleanupStack::PopAndDestroy( listBox );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestPLListBoxL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestPLListBoxL( CStifItemParser& /*aItem*/ )
    {
    CEikFormattedCellListBox* listBox = new (ELeave) CEikFormattedCellListBox;
    CleanupStack::PushL( listBox );
    STIF_ASSERT_NOT_NULL( listBox );
    
    CAknPopupList* popupList = CAknPopupList::NewL( listBox, R_AVKON_SOFTKEYS_SELECT_BACK, AknPopupLayouts::EPopupSNotePopupWindow );
    CleanupStack::PushL( popupList );
    STIF_ASSERT_NOT_NULL( popupList );
    
    listBox->ConstructL( popupList, EAknListBoxMenuList );
    
    CEikListBox* listBoxGet = popupList->ListBox();
    STIF_ASSERT_NOT_NULL( listBoxGet );
    STIF_ASSERT_TRUE( listBox == listBoxGet );
    
    TInt popupOk = popupList->ExecuteLD();
    
    CleanupStack::Pop( popupList );
    STIF_ASSERT_EQUALS( 0, popupOk );
    CleanupStack::PopAndDestroy( listBox );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestPLSetMaximumHeightL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestPLSetMaximumHeightL( CStifItemParser& /*aItem*/ )
    {
    CEikFormattedCellListBox* listBox = new (ELeave) CEikFormattedCellListBox;
    CleanupStack::PushL( listBox );
    STIF_ASSERT_NOT_NULL( listBox );
    
    CTestSDKPopupsPL* popupList = CTestSDKPopupsPL::NewL( listBox, R_AVKON_SOFTKEYS_SELECT_BACK, AknPopupLayouts::EPopupSNotePopupWindow );
    CleanupStack::PushL( popupList );
    STIF_ASSERT_NOT_NULL( popupList );
    
    listBox->ConstructL( popupList, EAknListBoxMenuList );
    
    const TInt Height = 50;
    popupList->SetMaximumHeight( Height );
    STIF_ASSERT_TRUE( popupList->Layout().iMaximumHeight == Height );
    
    TInt popupOk = popupList->ExecuteLD();
    
    CleanupStack::Pop( popupList );
    STIF_ASSERT_EQUALS( 0, popupOk );
    CleanupStack::PopAndDestroy( listBox );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestPLEnableFindL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestPLEnableFindL( CStifItemParser& /*aItem*/ )
    {
    CEikFormattedCellListBox* listBox = new (ELeave) CEikFormattedCellListBox;
    CleanupStack::PushL( listBox );
    STIF_ASSERT_NOT_NULL( listBox );
    
    CAknPopupList* popupList = CAknPopupList::NewL( listBox, R_AVKON_SOFTKEYS_SELECT_BACK, AknPopupLayouts::EPopupSNotePopupWindow );
    CleanupStack::PushL( popupList );
    STIF_ASSERT_NOT_NULL( popupList );
    
    listBox->ConstructL( popupList, EAknListBoxMenuList );
    
    TBool find = popupList->EnableFind( EFalse );
    STIF_ASSERT_TRUE( find );
    find = popupList->EnableFind( ETrue );
    STIF_ASSERT_TRUE( find );
    
    TInt popupOk = popupList->ExecuteLD();
    
    CleanupStack::Pop( popupList );
    STIF_ASSERT_EQUALS( 0, popupOk );
    CleanupStack::PopAndDestroy( listBox );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestPLEnableAdaptiveFindL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestPLEnableAdaptiveFindL( CStifItemParser& /*aItem*/ )
    {
    CEikFormattedCellListBox* listBox = new (ELeave) CEikFormattedCellListBox;
    CleanupStack::PushL( listBox );
    STIF_ASSERT_NOT_NULL( listBox );
    
    CAknPopupList* popupList = CAknPopupList::NewL( listBox, R_AVKON_SOFTKEYS_SELECT_BACK, AknPopupLayouts::EPopupSNotePopupWindow );
    CleanupStack::PushL( popupList );
    STIF_ASSERT_NOT_NULL( popupList );
    
    listBox->ConstructL( popupList, EAknListBoxMenuList );
    
    TBool find = popupList->EnableAdaptiveFind( EFalse );
    STIF_ASSERT_TRUE( find );
    find = popupList->EnableAdaptiveFind( ETrue );
    STIF_ASSERT_TRUE( find );
    
    TInt popupOk = popupList->ExecuteLD();
    
    CleanupStack::Pop( popupList );
    STIF_ASSERT_EQUALS( 0, popupOk );
    CleanupStack::PopAndDestroy( listBox );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestPLFindBoxL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestPLFindBoxL( CStifItemParser& /*aItem*/ )
    {
    CEikFormattedCellListBox* listBox = new (ELeave) CEikFormattedCellListBox;
    CleanupStack::PushL( listBox );
    STIF_ASSERT_NOT_NULL( listBox );
    
    CAknPopupList* popupList = CAknPopupList::NewL( listBox, R_AVKON_SOFTKEYS_SELECT_BACK, AknPopupLayouts::EPopupSNotePopupWindow );
    CleanupStack::PushL( popupList );
    STIF_ASSERT_NOT_NULL( popupList );
    
    listBox->ConstructL( popupList, EAknListBoxMenuList );
    
    TBool find = popupList->EnableFind( ETrue );
    STIF_ASSERT_TRUE( find );
    CAknSearchField* findBox = popupList->FindBox();
    STIF_ASSERT_NOT_NULL( findBox );
    
    TInt popupOk = popupList->ExecuteLD();
    
    CleanupStack::Pop( popupList );
    STIF_ASSERT_EQUALS( 0, popupOk );
    CleanupStack::PopAndDestroy( listBox );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestPLHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestPLHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    CEikFormattedCellListBox* listBox = new (ELeave) CEikFormattedCellListBox;
    CleanupStack::PushL( listBox );
    STIF_ASSERT_NOT_NULL( listBox );
    
    CAknPopupList* popupList = CAknPopupList::NewL( listBox, R_AVKON_SOFTKEYS_SELECT_BACK, AknPopupLayouts::EPopupSNotePopupWindow );
    CleanupStack::PushL( popupList );
    STIF_ASSERT_NOT_NULL( popupList );
    
    listBox->ConstructL( popupList, EAknListBoxMenuList );
    
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( 10, 30 );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    
    popupList->HandlePointerEventL( event );
    
    CleanupStack::PopAndDestroy( popupList );
    CleanupStack::PopAndDestroy( listBox );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestPLProcessCommandL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestPLProcessCommandL( CStifItemParser& /*aItem*/ )
    {
    CEikFormattedCellListBox* listBox = new (ELeave) CEikFormattedCellListBox;
    CleanupStack::PushL( listBox );
    STIF_ASSERT_NOT_NULL( listBox );
    
    CTestSDKPopupsPL* popupList = CTestSDKPopupsPL::NewL( listBox, R_AVKON_SOFTKEYS_SELECT_BACK, AknPopupLayouts::EPopupSNotePopupWindow );
    CleanupStack::PushL( popupList );
    STIF_ASSERT_NOT_NULL( popupList );
    
    listBox->ConstructL( popupList, EAknListBoxMenuList );
    
    popupList->ProcessCommandL( EAknSoftkeySelect );
    
    CleanupStack::Pop( popupList );
    
    popupList = CTestSDKPopupsPL::NewL( listBox, R_AVKON_SOFTKEYS_SELECT_BACK, AknPopupLayouts::EPopupSNotePopupWindow );
    CleanupStack::PushL( popupList );
    STIF_ASSERT_NOT_NULL( popupList );
    
    listBox->ConstructL( popupList, EAknListBoxMenuList );
    
    popupList->ProcessCommandL( EAknSoftkeyBack );
    
    CleanupStack::Pop( popupList );
    CleanupStack::PopAndDestroy( listBox );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestPLHandleListBoxEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestPLHandleListBoxEventL( CStifItemParser& /*aItem*/ )
    {
    CEikFormattedCellListBox* listBox = new (ELeave) CEikFormattedCellListBox;
    CleanupStack::PushL( listBox );
    STIF_ASSERT_NOT_NULL( listBox );
    
    CTestSDKPopupsPL* popupList = CTestSDKPopupsPL::NewL( listBox, R_AVKON_SOFTKEYS_SELECT_BACK, AknPopupLayouts::EPopupSNotePopupWindow );
    CleanupStack::PushL( popupList );
    STIF_ASSERT_NOT_NULL( popupList );
    
    listBox->ConstructL( popupList, EAknListBoxMenuList );
    
    popupList->HandleListBoxEventL( listBox, MEikListBoxObserver::EEventPenDownOnItem );
    
    CleanupStack::Pop( popupList );
    
    popupList = CTestSDKPopupsPL::NewL( listBox, R_AVKON_SOFTKEYS_SELECT_BACK, AknPopupLayouts::EPopupSNotePopupWindow );
    CleanupStack::PushL( popupList );
    STIF_ASSERT_NOT_NULL( popupList );
    
    listBox->ConstructL( popupList, EAknListBoxMenuList );
    
    popupList->HandleListBoxEventL( listBox, MEikListBoxObserver::EEventEnterKeyPressed );
    
    CleanupStack::Pop( popupList );
    CleanupStack::PopAndDestroy( listBox );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestPLHandleControlEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestPLHandleControlEventL( CStifItemParser& /*aItem*/ )
    {
    CEikFormattedCellListBox* listBox = new (ELeave) CEikFormattedCellListBox;
    CleanupStack::PushL( listBox );
    STIF_ASSERT_NOT_NULL( listBox );
    
    CTestSDKPopupsPL* popupList = CTestSDKPopupsPL::NewL( listBox, R_AVKON_SOFTKEYS_SELECT_BACK, AknPopupLayouts::EPopupSNotePopupWindow );
    CleanupStack::PushL( popupList );
    STIF_ASSERT_NOT_NULL( popupList );
    
    listBox->ConstructL( popupList, MCoeControlObserver::EEventStateChanged );
    
    popupList->HandleControlEventL( listBox, MCoeControlObserver::EEventStateChanged );
    
    CleanupStack::Pop( popupList );
    CleanupStack::PopAndDestroy( listBox );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestPLCAknPopupListL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestPLCAknPopupListL( CStifItemParser& /*aItem*/ )
    {
    CEikFormattedCellListBox* listBox = new (ELeave) CEikFormattedCellListBox;
    CleanupStack::PushL( listBox );
    STIF_ASSERT_NOT_NULL( listBox );
    
    CAknPopupList* popupList = CAknPopupList::NewL( listBox, R_AVKON_SOFTKEYS_SELECT_BACK, AknPopupLayouts::EPopupSNotePopupWindow );
    CleanupStack::PushL( popupList );
    STIF_ASSERT_NOT_NULL( popupList );
    
    CleanupStack::PopAndDestroy( popupList );
    CleanupStack::PopAndDestroy( listBox );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestPLDeconstrutorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestPLDeconstrutorL( CStifItemParser& /*aItem*/ )
    {
    CEikFormattedCellListBox* listBox = new (ELeave) CEikFormattedCellListBox;
    CleanupStack::PushL( listBox );
    STIF_ASSERT_NOT_NULL( listBox );
    
    CTestSDKPopupsPL* popupList = CTestSDKPopupsPL::NewL( listBox, R_AVKON_SOFTKEYS_SELECT_BACK, AknPopupLayouts::EPopupSNotePopupWindow );
    CleanupStack::PushL( popupList );
    STIF_ASSERT_NOT_NULL( popupList );
    
    CleanupStack::Pop( popupList );
    delete popupList;
    CleanupStack::PopAndDestroy( listBox );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestPLConstructL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestPLConstructL( CStifItemParser& /*aItem*/ )
    {
    CEikFormattedCellListBox* listBox = new (ELeave) CEikFormattedCellListBox;
    CleanupStack::PushL( listBox );
    STIF_ASSERT_NOT_NULL( listBox );
    
    CAknPopupList* popupList = CAknPopupList::NewL( listBox, R_AVKON_SOFTKEYS_SELECT_BACK, AknPopupLayouts::EPopupSNotePopupWindow );
    CleanupStack::PushL( popupList );
    STIF_ASSERT_NOT_NULL( popupList );
    
    CleanupStack::PopAndDestroy( popupList );
    CleanupStack::PopAndDestroy( listBox );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestPLAttemptExitL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestPLAttemptExitL( CStifItemParser& /*aItem*/ )
    {
    CEikFormattedCellListBox* listBox = new (ELeave) CEikFormattedCellListBox;
    CleanupStack::PushL( listBox );
    STIF_ASSERT_NOT_NULL( listBox );
    
    CTestSDKPopupsPL* popupList = CTestSDKPopupsPL::NewL( listBox, R_AVKON_SOFTKEYS_SELECT_BACK, AknPopupLayouts::EPopupSNotePopupWindow );
    CleanupStack::PushL( popupList );
    STIF_ASSERT_NOT_NULL( popupList );
    
    popupList->AttemptExitL( ETrue );
    
    CleanupStack::Pop( popupList );
    CleanupStack::PopAndDestroy( listBox );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestPLSetupWindowLayoutL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestPLSetupWindowLayoutL( CStifItemParser& /*aItem*/ )
    {
    CEikFormattedCellListBox* listBox = new (ELeave) CEikFormattedCellListBox;
    CleanupStack::PushL( listBox );
    STIF_ASSERT_NOT_NULL( listBox );
    
    CTestSDKPopupsPL* popupList = CTestSDKPopupsPL::NewL( listBox, R_AVKON_SOFTKEYS_SELECT_BACK, AknPopupLayouts::EPopupSNotePopupWindow );
    CleanupStack::PushL( popupList );
    STIF_ASSERT_NOT_NULL( popupList );
    
    listBox->ConstructL( popupList, MCoeControlObserver::EEventStateChanged );
    
    popupList->SetupWindowLayout( AknPopupLayouts::EMenuWindow );
    
    TInt popupOk = popupList->ExecuteLD();
    
    CleanupStack::Pop( popupList );
    STIF_ASSERT_EQUALS( 0, popupOk );
    CleanupStack::PopAndDestroy( listBox );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestPLListBoxConstL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestPLListBoxConstL( CStifItemParser& /*aItem*/ )
    {
    CEikFormattedCellListBox* listBox = new (ELeave) CEikFormattedCellListBox;
    CleanupStack::PushL( listBox );
    STIF_ASSERT_NOT_NULL( listBox );
    
    CTestSDKPopupsPL* popupList = CTestSDKPopupsPL::NewL( listBox, R_AVKON_SOFTKEYS_SELECT_BACK, AknPopupLayouts::EPopupSNotePopupWindow );
    CleanupStack::PushL( popupList );
    STIF_ASSERT_NOT_NULL( popupList );
    
    listBox->ConstructL( popupList, MCoeControlObserver::EEventStateChanged );
    
    const CTestSDKPopupsPL* popupListConst = popupList;
    CEikListBox* listBoxGet = popupListConst->ListBox();
    STIF_ASSERT_NOT_NULL( listBoxGet );
    
    TInt popupOk = popupList->ExecuteLD();
    
    CleanupStack::Pop( popupList );
    STIF_ASSERT_EQUALS( 0, popupOk );
    CleanupStack::PopAndDestroy( listBox );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestPLLayoutConstL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestPLLayoutConstL( CStifItemParser& /*aItem*/ )
    {
    CEikFormattedCellListBox* listBox = new (ELeave) CEikFormattedCellListBox;
    CleanupStack::PushL( listBox );
    STIF_ASSERT_NOT_NULL( listBox );
    
    CTestSDKPopupsPL* popupList = CTestSDKPopupsPL::NewL( listBox, R_AVKON_SOFTKEYS_SELECT_BACK, AknPopupLayouts::EPopupSNotePopupWindow );
    CleanupStack::PushL( popupList );
    STIF_ASSERT_NOT_NULL( popupList );
    
    listBox->ConstructL( popupList, EAknListBoxMenuList );
    
    const CTestSDKPopupsPL* popupListConst = popupList;
    const TInt Height = 50;
    popupList->SetMaximumHeight( Height );
    STIF_ASSERT_TRUE( popupListConst->Layout().iMaximumHeight == Height );
    
    TInt popupOk = popupList->ExecuteLD();
    
    CleanupStack::Pop( popupList );
    STIF_ASSERT_EQUALS( 0, popupOk );
    CleanupStack::PopAndDestroy( listBox );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestPLLayoutL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestPLLayoutL( CStifItemParser& aItem )
    {
    return TestPLSetMaximumHeightL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestPLMopSupplyObjectL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestPLMopSupplyObjectL( CStifItemParser& /*aItem*/ )
    {
    CEikFormattedCellListBox* listBox = new (ELeave) CEikFormattedCellListBox;
    CleanupStack::PushL( listBox );
    STIF_ASSERT_NOT_NULL( listBox );
    
    CTestSDKPopupsPL* popupList = CTestSDKPopupsPL::NewL( listBox, R_AVKON_SOFTKEYS_SELECT_BACK, AknPopupLayouts::EPopupSNotePopupWindow );
    CleanupStack::PushL( popupList );
    STIF_ASSERT_NOT_NULL( popupList );
    
    listBox->ConstructL( popupList, EAknListBoxMenuList );
    
    TTypeUid::Ptr ptr = TTypeUid::Null();
    ptr = popupList->MopSupplyObject( CAknPopupList::ETypeId );
    CTestSDKPopupsPL* point = static_cast<CTestSDKPopupsPL*> ( ptr.Pointer() );
    STIF_ASSERT_NOT_NULL( point );
    
    TInt popupOk = popupList->ExecuteLD();
    
    CleanupStack::Pop( popupList );
    STIF_ASSERT_EQUALS( 0, popupOk );
    CleanupStack::PopAndDestroy( listBox );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestPLHandleResourceChangeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestPLHandleResourceChangeL( CStifItemParser& /*aItem*/ )
    {
    CEikFormattedCellListBox* listBox = new (ELeave) CEikFormattedCellListBox;
    CleanupStack::PushL( listBox );
    STIF_ASSERT_NOT_NULL( listBox );
    
    CTestSDKPopupsPL* popupList = CTestSDKPopupsPL::NewL( listBox, R_AVKON_SOFTKEYS_SELECT_BACK, AknPopupLayouts::EPopupSNotePopupWindow );
    CleanupStack::PushL( popupList );
    STIF_ASSERT_NOT_NULL( popupList );
    
    listBox->ConstructL( popupList, EAknListBoxMenuList );
    
    popupList->HandleResourceChange( KEikDynamicLayoutVariantSwitch );
    popupList->HandleResourceChange( KEikMessageColorSchemeChange );
    
    TInt popupOk = popupList->ExecuteLD();
    
    CleanupStack::Pop( popupList );
    STIF_ASSERT_EQUALS( 0, popupOk );
    CleanupStack::PopAndDestroy( listBox );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestPLFadeBehindPopupL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestPLFadeBehindPopupL( CStifItemParser& /*aItem*/ )
    {
    CEikFormattedCellListBox* listBox = new (ELeave) CEikFormattedCellListBox;
    CleanupStack::PushL( listBox );
    STIF_ASSERT_NOT_NULL( listBox );
    
    CTestSDKPopupsPL* popupList = CTestSDKPopupsPL::NewL( listBox, R_AVKON_SOFTKEYS_SELECT_BACK, AknPopupLayouts::EPopupSNotePopupWindow );
    CleanupStack::PushL( popupList );
    STIF_ASSERT_NOT_NULL( popupList );
    
    listBox->ConstructL( popupList, EAknListBoxMenuList );
    
    popupList->FadeBehindPopup( EFalse );
    popupList->FadeBehindPopup( ETrue );
    
    TInt popupOk = popupList->ExecuteLD();
    
    CleanupStack::Pop( popupList );
    STIF_ASSERT_EQUALS( 0, popupOk );
    CleanupStack::PopAndDestroy( listBox );
    
    return KErrNone;
    
    }
