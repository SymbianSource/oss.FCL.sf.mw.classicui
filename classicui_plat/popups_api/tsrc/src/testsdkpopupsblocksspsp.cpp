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



// [INCLUDE FILES]

#include <aknpopupsettingpage.h>
#include <barsread.h>
#include <coemain.h>
#include <eikenv.h>
#include <aknlists.h>
#include <aknform.h>
#include <badesca.h>
#include <aknqueryvaluetext.h>
#include <s32mem.h>
#include <testsdkpopups.rsg>

#include "testsdkpopups.hrh"
#include "testsdkpopups.h"
#include "testsdkpopupspf.h"
#include "testsdkpopupsspsp.h"
#include "testsdkpopupspsl.h"
#include "testsdkpopupscontrol.h"
const TInt KLength = 20;
// ============================ MEMBER FUNCTIONS ===============================
// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPSLCAknPopupSettingListL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPSLCAknPopupSettingListL( CStifItemParser& /*aItem*/ )
    {
    CAknPopupSettingList* popupSettingList = new (ELeave) CAknPopupSettingList;
    CleanupStack::PushL( popupSettingList );
    STIF_ASSERT_NOT_NULL( popupSettingList );
    
    CleanupStack::PopAndDestroy( popupSettingList );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPSLDeconstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPSLDeconstructorL( CStifItemParser& /*aItem*/ )
    {
    CAknPopupSettingList* popupSettingList = new (ELeave) CAknPopupSettingList;
    CleanupStack::PushL( popupSettingList );
    STIF_ASSERT_NOT_NULL( popupSettingList );

    CleanupStack::Pop( popupSettingList );
    delete popupSettingList;
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPSLConstructL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPSLConstructL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKPopupsControl* control = new (ELeave) CTestSDKPopupsControl;
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CDesCArrayFlat* item = CCoeEnv::Static()->ReadDesCArrayResourceL( R_TESTSDK_LIST_ITEM_ARRAY );
    CleanupStack::PushL( item );
    STIF_ASSERT_NOT_NULL( item );
    
    CAknQueryValueTextArray* textArray = CAknQueryValueTextArray::NewL();
    CleanupStack::PushL( textArray );
    STIF_ASSERT_NOT_NULL( textArray );
    textArray->SetArray( *item );
    
    CAknQueryValueText* queryValueText = CAknQueryValueText::NewL();
    CleanupStack::PushL( queryValueText );
    STIF_ASSERT_NOT_NULL( queryValueText );
    queryValueText->SetArrayL( textArray );
    
    CAknPopupSettingPage* popupSettingPage = new (ELeave) CAknPopupSettingPage( 
        R_TESTSDK_POPUP_SETTING_PAGE, *queryValueText );
    CleanupStack::PushL( popupSettingPage );
    STIF_ASSERT_NOT_NULL( popupSettingPage );
    
    popupSettingPage->ConstructL();
    popupSettingPage->SetContainerWindowL( *control );
    CAknPopupSettingList* popSettingList = popupSettingPage->PopupSettingListBox();
    
    popSettingList->ConstructL();
    
    CleanupStack::PopAndDestroy( popupSettingPage );
    CleanupStack::PopAndDestroy( queryValueText );
    CleanupStack::PopAndDestroy( textArray );
    CleanupStack::PopAndDestroy( item );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;

    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPSLSetAllowsUserDefinedEntryL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPSLSetAllowsUserDefinedEntryL( CStifItemParser& /*aItem*/ )
    {
    CDesCArrayFlat* item = CCoeEnv::Static()->ReadDesCArrayResourceL( R_TESTSDK_LIST_ITEM_ARRAY );
    CleanupStack::PushL( item );
    STIF_ASSERT_NOT_NULL( item );
    
    CAknQueryValueTextArray* textArray = CAknQueryValueTextArray::NewL();
    CleanupStack::PushL( textArray );
    STIF_ASSERT_NOT_NULL( textArray );
    textArray->SetArray( *item );
    
    CAknQueryValueText* queryValueText = CAknQueryValueText::NewL();
    CleanupStack::PushL( queryValueText );
    STIF_ASSERT_NOT_NULL( queryValueText );
    queryValueText->SetArrayL( textArray );
    
    CAknPopupSettingPage* popupSettingPage = new (ELeave) CAknPopupSettingPage( 
        R_TESTSDK_POPUP_SETTING_PAGE, *queryValueText );
    CleanupStack::PushL( popupSettingPage );
    STIF_ASSERT_NOT_NULL( popupSettingPage );
    
    popupSettingPage->ConstructL();
    CAknPopupSettingList* popSettingList = popupSettingPage->PopupSettingListBox();
    
    popSettingList->SetAllowsUserDefinedEntry( EFalse );
    popSettingList->SetAllowsUserDefinedEntry( ETrue );
    
    CleanupStack::PopAndDestroy( popupSettingPage );
    CleanupStack::PopAndDestroy( queryValueText );
    CleanupStack::PopAndDestroy( textArray );
    CleanupStack::PopAndDestroy( item );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPSLSetQueryValueL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPSLSetQueryValueL( CStifItemParser& /*aItem*/ )
    {
    CDesCArrayFlat* item = CCoeEnv::Static()->ReadDesCArrayResourceL( R_TESTSDK_LIST_ITEM_ARRAY );
    CleanupStack::PushL( item );
    STIF_ASSERT_NOT_NULL( item );
    
    CAknQueryValueTextArray* textArray = CAknQueryValueTextArray::NewL();
    CleanupStack::PushL( textArray );
    STIF_ASSERT_NOT_NULL( textArray );
    textArray->SetArray( *item );
    
    CAknQueryValueText* queryValueText = CAknQueryValueText::NewL();
    CleanupStack::PushL( queryValueText );
    STIF_ASSERT_NOT_NULL( queryValueText );
    queryValueText->SetArrayL( textArray );
    
    CAknPopupSettingPage* popupSettingPage = new (ELeave) CAknPopupSettingPage( 
        R_TESTSDK_POPUP_SETTING_PAGE, *queryValueText );
    CleanupStack::PushL( popupSettingPage );
    STIF_ASSERT_NOT_NULL( popupSettingPage );
    
    popupSettingPage->ConstructL();
    CAknPopupSettingList* popSettingList = popupSettingPage->PopupSettingListBox();
    
    popSettingList->SetQueryValueL( queryValueText );
    
    CleanupStack::PopAndDestroy( popupSettingPage );
    CleanupStack::PopAndDestroy( queryValueText );
    CleanupStack::PopAndDestroy( textArray );
    CleanupStack::PopAndDestroy( item );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPSLSetShowIndicatorsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPSLSetShowIndicatorsL( CStifItemParser& /*aItem*/ )
    {
    CDesCArrayFlat* item = CCoeEnv::Static()->ReadDesCArrayResourceL( R_TESTSDK_LIST_ITEM_ARRAY );
    CleanupStack::PushL( item );
    STIF_ASSERT_NOT_NULL( item );
    
    CAknQueryValueTextArray* textArray = CAknQueryValueTextArray::NewL();
    CleanupStack::PushL( textArray );
    STIF_ASSERT_NOT_NULL( textArray );
    textArray->SetArray( *item );
    
    CAknQueryValueText* queryValueText = CAknQueryValueText::NewL();
    CleanupStack::PushL( queryValueText );
    STIF_ASSERT_NOT_NULL( queryValueText );
    queryValueText->SetArrayL( textArray );
    
    CAknPopupSettingPage* popupSettingPage = new (ELeave) CAknPopupSettingPage( 
        R_TESTSDK_POPUP_SETTING_PAGE, *queryValueText );
    CleanupStack::PushL( popupSettingPage );
    STIF_ASSERT_NOT_NULL( popupSettingPage );
    
    popupSettingPage->ConstructL();
    CAknPopupSettingList* popSettingList = popupSettingPage->PopupSettingListBox();
    
    popSettingList->SetShowIndicators( EFalse );
    popSettingList->SetShowIndicators( ETrue );
    
    CleanupStack::PopAndDestroy( popupSettingPage );
    CleanupStack::PopAndDestroy( queryValueText );
    CleanupStack::PopAndDestroy( textArray );
    CleanupStack::PopAndDestroy( item );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPSLNumLinesL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPSLNumLinesL( CStifItemParser& /*aItem*/ )
    {
    CDesCArrayFlat* item = CCoeEnv::Static()->ReadDesCArrayResourceL( R_TESTSDK_LIST_ITEM_ARRAY );
    CleanupStack::PushL( item );
    STIF_ASSERT_NOT_NULL( item );
    
    CAknQueryValueTextArray* textArray = CAknQueryValueTextArray::NewL();
    CleanupStack::PushL( textArray );
    STIF_ASSERT_NOT_NULL( textArray );
    textArray->SetArray( *item );
    
    CAknQueryValueText* queryValueText = CAknQueryValueText::NewL();
    CleanupStack::PushL( queryValueText );
    STIF_ASSERT_NOT_NULL( queryValueText );
    queryValueText->SetArrayL( textArray );
    
    CAknPopupSettingPage* popupSettingPage = new (ELeave) CAknPopupSettingPage( 
        R_TESTSDK_POPUP_SETTING_PAGE, *queryValueText );
    CleanupStack::PushL( popupSettingPage );
    STIF_ASSERT_NOT_NULL( popupSettingPage );
    
    popupSettingPage->ConstructL();
    CAknPopupSettingList* popSettingList = popupSettingPage->PopupSettingListBox();
    
    TInt num = popSettingList->NumLines();
    
    CleanupStack::PopAndDestroy( popupSettingPage );
    CleanupStack::PopAndDestroy( queryValueText );
    CleanupStack::PopAndDestroy( textArray );
    CleanupStack::PopAndDestroy( item );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPSLSetPopupSettingListObserverL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPSLSetPopupSettingListObserverL( CStifItemParser& /*aItem*/ )
    {
    CDesCArrayFlat* item = CCoeEnv::Static()->ReadDesCArrayResourceL( R_TESTSDK_LIST_ITEM_ARRAY );
    CleanupStack::PushL( item );
    STIF_ASSERT_NOT_NULL( item );
    
    CAknQueryValueTextArray* textArray = CAknQueryValueTextArray::NewL();
    CleanupStack::PushL( textArray );
    STIF_ASSERT_NOT_NULL( textArray );
    textArray->SetArray( *item );
    
    CAknQueryValueText* queryValueText = CAknQueryValueText::NewL();
    CleanupStack::PushL( queryValueText );
    STIF_ASSERT_NOT_NULL( queryValueText );
    queryValueText->SetArrayL( textArray );
    
    CAknPopupSettingPage* popupSettingPage = new (ELeave) CAknPopupSettingPage( 
        R_TESTSDK_POPUP_SETTING_PAGE, *queryValueText );
    CleanupStack::PushL( popupSettingPage );
    STIF_ASSERT_NOT_NULL( popupSettingPage );
    
    popupSettingPage->ConstructL();
    CAknPopupSettingList* popSettingList = popupSettingPage->PopupSettingListBox();
    
    CTestSDKPopupsPF* observer = new (ELeave) CTestSDKPopupsPF;
    CleanupStack::PushL( observer );
    STIF_ASSERT_NOT_NULL( observer );
    
    popSettingList->SetPopupSettingListObserver( observer );
    
    CleanupStack::PopAndDestroy( observer );
    CleanupStack::PopAndDestroy( popupSettingPage );
    CleanupStack::PopAndDestroy( queryValueText );
    CleanupStack::PopAndDestroy( textArray );
    CleanupStack::PopAndDestroy( item );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPSLConstructFromResourceL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPSLConstructFromResourceL( CStifItemParser& /*aItem*/ )
    {
    CDesCArrayFlat* item = CCoeEnv::Static()->ReadDesCArrayResourceL( R_TESTSDK_LIST_ITEM_ARRAY );
    CleanupStack::PushL( item );
    STIF_ASSERT_NOT_NULL( item );
    
    CAknQueryValueTextArray* textArray = CAknQueryValueTextArray::NewL();
    CleanupStack::PushL( textArray );
    STIF_ASSERT_NOT_NULL( textArray );
    textArray->SetArray( *item );
    
    CAknQueryValueText* queryValueText = CAknQueryValueText::NewL();
    CleanupStack::PushL( queryValueText );
    STIF_ASSERT_NOT_NULL( queryValueText );
    queryValueText->SetArrayL( textArray );
    
    CAknPopupSettingPage* popupSettingPage = new (ELeave) CAknPopupSettingPage( 
        R_TESTSDK_POPUP_SETTING_PAGE, *queryValueText );
    CleanupStack::PushL( popupSettingPage );
    STIF_ASSERT_NOT_NULL( popupSettingPage );
    
    popupSettingPage->ConstructL();
    CTestSDKPopupSPSL* popSettingList = static_cast<CTestSDKPopupSPSL*> ( popupSettingPage->PopupSettingListBox() );
    
    popSettingList->CreateMenuListL();
    popSettingList->ActivateMenuListL();
    popSettingList->DestroyMenuList();
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_POPUP_SETTING_LIST );
    popSettingList->ConstructFromResourceL( reader );

    CleanupStack::PopAndDestroy();
    CleanupStack::PopAndDestroy( popupSettingPage );
    CleanupStack::PopAndDestroy( queryValueText );
    CleanupStack::PopAndDestroy( textArray );
    CleanupStack::PopAndDestroy( item );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPSLCreateMenuListL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPSLCreateMenuListL( CStifItemParser& /*aItem*/ )
    {
    CDesCArrayFlat* item = CCoeEnv::Static()->ReadDesCArrayResourceL( R_TESTSDK_LIST_ITEM_ARRAY );
    CleanupStack::PushL( item );
    STIF_ASSERT_NOT_NULL( item );
    
    CAknQueryValueTextArray* textArray = CAknQueryValueTextArray::NewL();
    CleanupStack::PushL( textArray );
    STIF_ASSERT_NOT_NULL( textArray );
    textArray->SetArray( *item );
    
    CAknQueryValueText* queryValueText = CAknQueryValueText::NewL();
    CleanupStack::PushL( queryValueText );
    STIF_ASSERT_NOT_NULL( queryValueText );
    queryValueText->SetArrayL( textArray );
    
    CAknPopupSettingPage* popupSettingPage = new (ELeave) CAknPopupSettingPage( 
        R_TESTSDK_POPUP_SETTING_PAGE, *queryValueText );
    CleanupStack::PushL( popupSettingPage );
    STIF_ASSERT_NOT_NULL( popupSettingPage );
    
    popupSettingPage->ConstructL();
    CTestSDKPopupSPSL* popSettingList = static_cast<CTestSDKPopupSPSL*> ( popupSettingPage->PopupSettingListBox() );
    
    popSettingList->CreateMenuListL();
    
    CleanupStack::PopAndDestroy( popupSettingPage );
    CleanupStack::PopAndDestroy( queryValueText );
    CleanupStack::PopAndDestroy( textArray );
    CleanupStack::PopAndDestroy( item );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPSLActivateMenuListL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPSLActivateMenuListL( CStifItemParser& /*aItem*/ )
    {
    CDesCArrayFlat* item = CCoeEnv::Static()->ReadDesCArrayResourceL( R_TESTSDK_LIST_ITEM_ARRAY );
    CleanupStack::PushL( item );
    STIF_ASSERT_NOT_NULL( item );
    
    CAknQueryValueTextArray* textArray = CAknQueryValueTextArray::NewL();
    CleanupStack::PushL( textArray );
    STIF_ASSERT_NOT_NULL( textArray );
    textArray->SetArray( *item );
    
    CAknQueryValueText* queryValueText = CAknQueryValueText::NewL();
    CleanupStack::PushL( queryValueText );
    STIF_ASSERT_NOT_NULL( queryValueText );
    queryValueText->SetArrayL( textArray );
    
    CAknPopupSettingPage* popupSettingPage = new (ELeave) CAknPopupSettingPage( 
        R_TESTSDK_POPUP_SETTING_PAGE, *queryValueText );
    CleanupStack::PushL( popupSettingPage );
    STIF_ASSERT_NOT_NULL( popupSettingPage );
    
    popupSettingPage->ConstructL();
    CTestSDKPopupSPSL* popSettingList = static_cast<CTestSDKPopupSPSL*> ( popupSettingPage->PopupSettingListBox() );
    
    popSettingList->CreateMenuListL();
    popSettingList->ActivateMenuListL();
    
    CleanupStack::PopAndDestroy( popupSettingPage );
    CleanupStack::PopAndDestroy( queryValueText );
    CleanupStack::PopAndDestroy( textArray );
    CleanupStack::PopAndDestroy( item );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPSLConfigureMenuListL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPSLConfigureMenuListL( CStifItemParser& /*aItem*/ )
    {
    CDesCArrayFlat* item = CCoeEnv::Static()->ReadDesCArrayResourceL( R_TESTSDK_LIST_ITEM_ARRAY );
    CleanupStack::PushL( item );
    STIF_ASSERT_NOT_NULL( item );
    
    CAknQueryValueTextArray* textArray = CAknQueryValueTextArray::NewL();
    CleanupStack::PushL( textArray );
    STIF_ASSERT_NOT_NULL( textArray );
    textArray->SetArray( *item );
    
    CAknQueryValueText* queryValueText = CAknQueryValueText::NewL();
    CleanupStack::PushL( queryValueText );
    STIF_ASSERT_NOT_NULL( queryValueText );
    queryValueText->SetArrayL( textArray );
    
    CAknPopupSettingPage* popupSettingPage = new (ELeave) CAknPopupSettingPage( 
        R_TESTSDK_POPUP_SETTING_PAGE, *queryValueText );
    CleanupStack::PushL( popupSettingPage );
    STIF_ASSERT_NOT_NULL( popupSettingPage );
    
    popupSettingPage->ConstructL();
    CTestSDKPopupSPSL* popSettingList = static_cast<CTestSDKPopupSPSL*> ( popupSettingPage->PopupSettingListBox() );
    
    popSettingList->CreateMenuListL();
    popSettingList->ConfigureMenuListL();
    
    CleanupStack::PopAndDestroy( popupSettingPage );
    CleanupStack::PopAndDestroy( queryValueText );
    CleanupStack::PopAndDestroy( textArray );
    CleanupStack::PopAndDestroy( item );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPSLDestroyMenuListL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPSLDestroyMenuListL( CStifItemParser& /*aItem*/ )
    {
    CDesCArrayFlat* item = CCoeEnv::Static()->ReadDesCArrayResourceL( R_TESTSDK_LIST_ITEM_ARRAY );
    CleanupStack::PushL( item );
    STIF_ASSERT_NOT_NULL( item );
    
    CAknQueryValueTextArray* textArray = CAknQueryValueTextArray::NewL();
    CleanupStack::PushL( textArray );
    STIF_ASSERT_NOT_NULL( textArray );
    textArray->SetArray( *item );
    
    CAknQueryValueText* queryValueText = CAknQueryValueText::NewL();
    CleanupStack::PushL( queryValueText );
    STIF_ASSERT_NOT_NULL( queryValueText );
    queryValueText->SetArrayL( textArray );
    
    CAknPopupSettingPage* popupSettingPage = new (ELeave) CAknPopupSettingPage( 
        R_TESTSDK_POPUP_SETTING_PAGE, *queryValueText );
    CleanupStack::PushL( popupSettingPage );
    STIF_ASSERT_NOT_NULL( popupSettingPage );
    
    popupSettingPage->ConstructL();
    CTestSDKPopupSPSL* popSettingList = static_cast<CTestSDKPopupSPSL*> ( popupSettingPage->PopupSettingListBox() );
    
    popSettingList->CreateMenuListL();
    popSettingList->ActivateMenuListL();
    popSettingList->DestroyMenuList();
    
    CleanupStack::PopAndDestroy( popupSettingPage );
    CleanupStack::PopAndDestroy( queryValueText );
    CleanupStack::PopAndDestroy( textArray );
    CleanupStack::PopAndDestroy( item );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPSLHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPSLHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    CDesCArrayFlat* item = CCoeEnv::Static()->ReadDesCArrayResourceL( R_TESTSDK_LIST_ITEM_ARRAY );
    CleanupStack::PushL( item );
    STIF_ASSERT_NOT_NULL( item );
    
    CAknQueryValueTextArray* textArray = CAknQueryValueTextArray::NewL();
    CleanupStack::PushL( textArray );
    STIF_ASSERT_NOT_NULL( textArray );
    textArray->SetArray( *item );
    
    CAknQueryValueText* queryValueText = CAknQueryValueText::NewL();
    CleanupStack::PushL( queryValueText );
    STIF_ASSERT_NOT_NULL( queryValueText );
    queryValueText->SetArrayL( textArray );
    
    CAknPopupSettingPage* popupSettingPage = new (ELeave) CAknPopupSettingPage( 
        R_TESTSDK_POPUP_SETTING_PAGE, *queryValueText );
    CleanupStack::PushL( popupSettingPage );
    STIF_ASSERT_NOT_NULL( popupSettingPage );
    
    popupSettingPage->ConstructL();
    CTestSDKPopupSPSL* popSettingList = static_cast<CTestSDKPopupSPSL*> ( popupSettingPage->PopupSettingListBox() );
    
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( 10, 30 );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    
    popSettingList->HandlePointerEventL( event );
    
    CleanupStack::PopAndDestroy( popupSettingPage );
    CleanupStack::PopAndDestroy( queryValueText );
    CleanupStack::PopAndDestroy( textArray );
    CleanupStack::PopAndDestroy( item );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPSLHandleResourceChangeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPSLHandleResourceChangeL( CStifItemParser& /*aItem*/ )
    {
    CDesCArrayFlat* item = CCoeEnv::Static()->ReadDesCArrayResourceL( R_TESTSDK_LIST_ITEM_ARRAY );
    CleanupStack::PushL( item );
    STIF_ASSERT_NOT_NULL( item );
    
    CAknQueryValueTextArray* textArray = CAknQueryValueTextArray::NewL();
    CleanupStack::PushL( textArray );
    STIF_ASSERT_NOT_NULL( textArray );
    textArray->SetArray( *item );
    
    CAknQueryValueText* queryValueText = CAknQueryValueText::NewL();
    CleanupStack::PushL( queryValueText );
    STIF_ASSERT_NOT_NULL( queryValueText );
    queryValueText->SetArrayL( textArray );
    
    CAknPopupSettingPage* popupSettingPage = new (ELeave) CAknPopupSettingPage( 
        R_TESTSDK_POPUP_SETTING_PAGE, *queryValueText );
    CleanupStack::PushL( popupSettingPage );
    STIF_ASSERT_NOT_NULL( popupSettingPage );
    
    popupSettingPage->ConstructL();
    CTestSDKPopupSPSL* popSettingList = static_cast<CTestSDKPopupSPSL*> ( popupSettingPage->PopupSettingListBox() );
    
    popSettingList->HandleResourceChange( KAknsMessageSkinChange );
    
    CleanupStack::PopAndDestroy( popupSettingPage );
    CleanupStack::PopAndDestroy( queryValueText );
    CleanupStack::PopAndDestroy( textArray );
    CleanupStack::PopAndDestroy( item );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPSLHandleListBoxEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPSLHandleListBoxEventL( CStifItemParser& /*aItem*/ )
    {
    CDesCArrayFlat* item = CCoeEnv::Static()->ReadDesCArrayResourceL( R_TESTSDK_LIST_ITEM_ARRAY );
    CleanupStack::PushL( item );
    STIF_ASSERT_NOT_NULL( item );
    
    CAknQueryValueTextArray* textArray = CAknQueryValueTextArray::NewL();
    CleanupStack::PushL( textArray );
    STIF_ASSERT_NOT_NULL( textArray );
    textArray->SetArray( *item );
    
    CAknQueryValueText* queryValueText = CAknQueryValueText::NewL();
    CleanupStack::PushL( queryValueText );
    STIF_ASSERT_NOT_NULL( queryValueText );
    queryValueText->SetArrayL( textArray );
    
    CAknPopupSettingPage* popupSettingPage = new (ELeave) CAknPopupSettingPage( 
        R_TESTSDK_POPUP_SETTING_PAGE, *queryValueText );
    CleanupStack::PushL( popupSettingPage );
    STIF_ASSERT_NOT_NULL( popupSettingPage );
    
    popupSettingPage->ConstructL();
    CTestSDKPopupSPSL* popSettingList = static_cast<CTestSDKPopupSPSL*> ( popupSettingPage->PopupSettingListBox() );
    
    CEikTextListBox* listBox = new( ELeave ) CAknSinglePopupMenuStyleListBox;
    CleanupStack::PushL( listBox );
    STIF_ASSERT_NOT_NULL( listBox );
    
    popSettingList->HandleListBoxEventL( listBox, MEikListBoxObserver::EEventEnterKeyPressed );
    
    CleanupStack::PopAndDestroy( listBox );
    CleanupStack::PopAndDestroy( popupSettingPage );
    CleanupStack::PopAndDestroy( queryValueText );
    CleanupStack::PopAndDestroy( textArray );
    CleanupStack::PopAndDestroy( item );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPSPCAknPopupSettingPageL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPSPCAknPopupSettingPageL( CStifItemParser& /*aItem*/ )
    {
    CDesCArrayFlat* item = CCoeEnv::Static()->ReadDesCArrayResourceL( R_TESTSDK_LIST_ITEM_ARRAY );
    CleanupStack::PushL( item );
    STIF_ASSERT_NOT_NULL( item );
    
    CAknQueryValueTextArray* textArray = CAknQueryValueTextArray::NewL();
    CleanupStack::PushL( textArray );
    STIF_ASSERT_NOT_NULL( textArray );
    textArray->SetArray( *item );
    
    CAknQueryValueText* queryValueText = CAknQueryValueText::NewL();
    CleanupStack::PushL( queryValueText );
    STIF_ASSERT_NOT_NULL( queryValueText );
    queryValueText->SetArrayL( textArray );
    
    CAknPopupSettingPage* popupSettingPage = new (ELeave) CAknPopupSettingPage( 
        R_TESTSDK_POPUP_SETTING_PAGE, *queryValueText );
    CleanupStack::PushL( popupSettingPage );
    STIF_ASSERT_NOT_NULL( popupSettingPage );
    
    CleanupStack::PopAndDestroy( popupSettingPage );
    CleanupStack::PopAndDestroy( queryValueText );
    CleanupStack::PopAndDestroy( textArray );
    CleanupStack::PopAndDestroy( item );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPSPCAknPopupSettingPageTextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPSPCAknPopupSettingPageTextL( CStifItemParser& /*aItem*/ )
    {
    CDesCArrayFlat* item = CCoeEnv::Static()->ReadDesCArrayResourceL( R_TESTSDK_LIST_ITEM_ARRAY );
    CleanupStack::PushL( item );
    STIF_ASSERT_NOT_NULL( item );
    
    CAknQueryValueTextArray* textArray = CAknQueryValueTextArray::NewL();
    CleanupStack::PushL( textArray );
    STIF_ASSERT_NOT_NULL( textArray );
    textArray->SetArray( *item );
    
    CAknQueryValueText* queryValueText = CAknQueryValueText::NewL();
    CleanupStack::PushL( queryValueText );
    STIF_ASSERT_NOT_NULL( queryValueText );
    queryValueText->SetArrayL( textArray );
    
    _LIT( KSettingListTitle, "title" );
    TBufC<KLength> title ( KSettingListTitle );
    
    CAknPopupSettingPage* popupSettingPage = new (ELeave) CAknPopupSettingPage( 
         &title, 0, 0, 0, R_TESTSDK_POPUP_SETTING_PAGE, *queryValueText );
    CleanupStack::PushL( popupSettingPage );
    STIF_ASSERT_NOT_NULL( popupSettingPage );
    
    CleanupStack::PopAndDestroy( popupSettingPage );
    CleanupStack::PopAndDestroy( queryValueText );
    CleanupStack::PopAndDestroy( textArray );
    CleanupStack::PopAndDestroy( item );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPSPConstructLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPSPConstructLL( CStifItemParser& /*aItem*/ )
    {
    CDesCArrayFlat* item = CCoeEnv::Static()->ReadDesCArrayResourceL( R_TESTSDK_LIST_ITEM_ARRAY );
    CleanupStack::PushL( item );
    STIF_ASSERT_NOT_NULL( item );
    
    CAknQueryValueTextArray* textArray = CAknQueryValueTextArray::NewL();
    CleanupStack::PushL( textArray );
    STIF_ASSERT_NOT_NULL( textArray );
    textArray->SetArray( *item );
    
    CAknQueryValueText* queryValueText = CAknQueryValueText::NewL();
    CleanupStack::PushL( queryValueText );
    STIF_ASSERT_NOT_NULL( queryValueText );
    queryValueText->SetArrayL( textArray );
    
    CAknPopupSettingPage* popupSettingPage = new (ELeave) CAknPopupSettingPage( 
        R_TESTSDK_POPUP_SETTING_PAGE, *queryValueText );
    CleanupStack::PushL( popupSettingPage );
    STIF_ASSERT_NOT_NULL( popupSettingPage );
    
    popupSettingPage->ConstructL();
    
    CleanupStack::PopAndDestroy( popupSettingPage );
    CleanupStack::PopAndDestroy( queryValueText );
    CleanupStack::PopAndDestroy( textArray );
    CleanupStack::PopAndDestroy( item );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPSPListBoxControlL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPSPListBoxControlL( CStifItemParser& /*aItem*/ )
    {
    CDesCArrayFlat* item = CCoeEnv::Static()->ReadDesCArrayResourceL( R_TESTSDK_LIST_ITEM_ARRAY );
    CleanupStack::PushL( item );
    STIF_ASSERT_NOT_NULL( item );
    
    CAknQueryValueTextArray* textArray = CAknQueryValueTextArray::NewL();
    CleanupStack::PushL( textArray );
    STIF_ASSERT_NOT_NULL( textArray );
    textArray->SetArray( *item );
    
    CAknQueryValueText* queryValueText = CAknQueryValueText::NewL();
    CleanupStack::PushL( queryValueText );
    STIF_ASSERT_NOT_NULL( queryValueText );
    queryValueText->SetArrayL( textArray );
    
    CAknPopupSettingPage* popupSettingPage = new (ELeave) CAknPopupSettingPage( 
        R_TESTSDK_POPUP_SETTING_PAGE, *queryValueText );
    CleanupStack::PushL( popupSettingPage );
    STIF_ASSERT_NOT_NULL( popupSettingPage );
    
    popupSettingPage->ConstructL();
    
    CAknSetStyleListBox* listBox = popupSettingPage->ListBoxControl();
    STIF_ASSERT_NOT_NULL( listBox );
    
    CleanupStack::PopAndDestroy( popupSettingPage );
    CleanupStack::PopAndDestroy( queryValueText );
    CleanupStack::PopAndDestroy( textArray );
    CleanupStack::PopAndDestroy( item );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPSPPopupSettingListBoxL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPSPPopupSettingListBoxL( CStifItemParser& /*aItem*/ )
    {
    CDesCArrayFlat* item = CCoeEnv::Static()->ReadDesCArrayResourceL( R_TESTSDK_LIST_ITEM_ARRAY );
    CleanupStack::PushL( item );
    STIF_ASSERT_NOT_NULL( item );
    
    CAknQueryValueTextArray* textArray = CAknQueryValueTextArray::NewL();
    CleanupStack::PushL( textArray );
    STIF_ASSERT_NOT_NULL( textArray );
    textArray->SetArray( *item );
    
    CAknQueryValueText* queryValueText = CAknQueryValueText::NewL();
    CleanupStack::PushL( queryValueText );
    STIF_ASSERT_NOT_NULL( queryValueText );
    queryValueText->SetArrayL( textArray );
    
    CAknPopupSettingPage* popupSettingPage = new (ELeave) CAknPopupSettingPage( 
        R_TESTSDK_POPUP_SETTING_PAGE, *queryValueText );
    CleanupStack::PushL( popupSettingPage );
    STIF_ASSERT_NOT_NULL( popupSettingPage );
    
    popupSettingPage->ConstructL();
    
    CAknPopupSettingList* popupSettingList = popupSettingPage->PopupSettingListBox();
    STIF_ASSERT_NOT_NULL( popupSettingList );
    
    CleanupStack::PopAndDestroy( popupSettingPage );
    CleanupStack::PopAndDestroy( queryValueText );
    CleanupStack::PopAndDestroy( textArray );
    CleanupStack::PopAndDestroy( item );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPSPHandlePopupSettingListEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPSPHandlePopupSettingListEventL( CStifItemParser& /*aItem*/ )
    {
    CDesCArrayFlat* item = CCoeEnv::Static()->ReadDesCArrayResourceL( R_TESTSDK_LIST_ITEM_ARRAY );
    CleanupStack::PushL( item );
    STIF_ASSERT_NOT_NULL( item );
    
    CAknQueryValueTextArray* textArray = CAknQueryValueTextArray::NewL();
    CleanupStack::PushL( textArray );
    STIF_ASSERT_NOT_NULL( textArray );
    textArray->SetArray( *item );
    
    CAknQueryValueText* queryValueText = CAknQueryValueText::NewL();
    CleanupStack::PushL( queryValueText );
    STIF_ASSERT_NOT_NULL( queryValueText );
    queryValueText->SetArrayL( textArray );
    
    CAknPopupSettingPage* popupSettingPage = new (ELeave) CAknPopupSettingPage( 
        R_TESTSDK_POPUP_SETTING_PAGE, *queryValueText );
    CleanupStack::PushL( popupSettingPage );
    STIF_ASSERT_NOT_NULL( popupSettingPage );
    
    popupSettingPage->ConstructL();
    
    CAknPopupSettingList* popupSettingList = popupSettingPage->PopupSettingListBox();
    STIF_ASSERT_NOT_NULL( popupSettingList );
    
    popupSettingPage->HandlePopupSettingListEventL( popupSettingList, 
        MAknPopupSettingListObserver::EAknPopupSettingSelectionAndRequestAccept, 0 );
    
    CleanupStack::PopAndDestroy( popupSettingPage );
    CleanupStack::PopAndDestroy( queryValueText );
    CleanupStack::PopAndDestroy( textArray );
    CleanupStack::PopAndDestroy( item );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPSPUpdateQueryValueL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPSPUpdateQueryValueL( CStifItemParser& /*aItem*/ )
    {
    CDesCArrayFlat* item = CCoeEnv::Static()->ReadDesCArrayResourceL( R_TESTSDK_LIST_ITEM_ARRAY );
    CleanupStack::PushL( item );
    STIF_ASSERT_NOT_NULL( item );
    
    CAknQueryValueTextArray* textArray = CAknQueryValueTextArray::NewL();
    CleanupStack::PushL( textArray );
    STIF_ASSERT_NOT_NULL( textArray );
    textArray->SetArray( *item );
    
    CAknQueryValueText* queryValueText = CAknQueryValueText::NewL();
    CleanupStack::PushL( queryValueText );
    STIF_ASSERT_NOT_NULL( queryValueText );
    queryValueText->SetArrayL( textArray );
    
    CAknPopupSettingPage* popupSettingPage = new (ELeave) CAknPopupSettingPage( 
        R_TESTSDK_POPUP_SETTING_PAGE, *queryValueText );
    CleanupStack::PushL( popupSettingPage );
    STIF_ASSERT_NOT_NULL( popupSettingPage );
    
    popupSettingPage->ConstructL();
    
    popupSettingPage->UpdateQueryValueL( queryValueText );
    
    CleanupStack::PopAndDestroy( popupSettingPage );
    CleanupStack::PopAndDestroy( queryValueText );
    CleanupStack::PopAndDestroy( textArray );
    CleanupStack::PopAndDestroy( item );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPSPHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPSPHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    CDesCArrayFlat* item = CCoeEnv::Static()->ReadDesCArrayResourceL( R_TESTSDK_LIST_ITEM_ARRAY );
    CleanupStack::PushL( item );
    STIF_ASSERT_NOT_NULL( item );
    
    CAknQueryValueTextArray* textArray = CAknQueryValueTextArray::NewL();
    CleanupStack::PushL( textArray );
    STIF_ASSERT_NOT_NULL( textArray );
    textArray->SetArray( *item );
    
    CAknQueryValueText* queryValueText = CAknQueryValueText::NewL();
    CleanupStack::PushL( queryValueText );
    STIF_ASSERT_NOT_NULL( queryValueText );
    queryValueText->SetArrayL( textArray );
    
    CAknPopupSettingPage* popupSettingPage = new (ELeave) CAknPopupSettingPage( 
        R_TESTSDK_POPUP_SETTING_PAGE, *queryValueText );
    CleanupStack::PushL( popupSettingPage );
    STIF_ASSERT_NOT_NULL( popupSettingPage );
    
    popupSettingPage->ConstructL();
    
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( 10, 30 );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;

    popupSettingPage->HandlePointerEventL( event );
    
    CleanupStack::PopAndDestroy( popupSettingPage );
    CleanupStack::PopAndDestroy( queryValueText );
    CleanupStack::PopAndDestroy( textArray );
    CleanupStack::PopAndDestroy( item );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPSPDeconstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPSPDeconstructorL( CStifItemParser& /*aItem*/ )
    {
    CDesCArrayFlat* item = CCoeEnv::Static()->ReadDesCArrayResourceL( R_TESTSDK_LIST_ITEM_ARRAY );
    CleanupStack::PushL( item );
    STIF_ASSERT_NOT_NULL( item );
    
    CAknQueryValueTextArray* textArray = CAknQueryValueTextArray::NewL();
    CleanupStack::PushL( textArray );
    STIF_ASSERT_NOT_NULL( textArray );
    textArray->SetArray( *item );
    
    CAknQueryValueText* queryValueText = CAknQueryValueText::NewL();
    CleanupStack::PushL( queryValueText );
    STIF_ASSERT_NOT_NULL( queryValueText );
    queryValueText->SetArrayL( textArray );
    
    CTestSDKPopupsSPSP* popupSettingPage = new (ELeave) CTestSDKPopupsSPSP( 
        R_TESTSDK_POPUP_SETTING_PAGE, *queryValueText );
    CleanupStack::PushL( popupSettingPage );
    STIF_ASSERT_NOT_NULL( popupSettingPage );
    
    CleanupStack::Pop( popupSettingPage );
    delete popupSettingPage;
    CleanupStack::PopAndDestroy( queryValueText );
    CleanupStack::PopAndDestroy( textArray );
    CleanupStack::PopAndDestroy( item );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPSPQueryValueL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPSPQueryValueL( CStifItemParser& /*aItem*/ )
    {
    CDesCArrayFlat* item = CCoeEnv::Static()->ReadDesCArrayResourceL( R_TESTSDK_LIST_ITEM_ARRAY );
    CleanupStack::PushL( item );
    STIF_ASSERT_NOT_NULL( item );
    
    CAknQueryValueTextArray* textArray = CAknQueryValueTextArray::NewL();
    CleanupStack::PushL( textArray );
    STIF_ASSERT_NOT_NULL( textArray );
    textArray->SetArray( *item );
    
    CAknQueryValueText* queryValueText = CAknQueryValueText::NewL();
    CleanupStack::PushL( queryValueText );
    STIF_ASSERT_NOT_NULL( queryValueText );
    queryValueText->SetArrayL( textArray );
    
    CTestSDKPopupsSPSP* popupSettingPage = new (ELeave) CTestSDKPopupsSPSP( 
        R_TESTSDK_POPUP_SETTING_PAGE, *queryValueText );
    CleanupStack::PushL( popupSettingPage );
    STIF_ASSERT_NOT_NULL( popupSettingPage );
    
    popupSettingPage->ConstructL();
    
    CAknQueryValueText* queryValueTextGet = static_cast<CAknQueryValueText*> ( popupSettingPage->QueryValue() );
    STIF_ASSERT_TRUE( queryValueTextGet == queryValueText );
    
    CleanupStack::PopAndDestroy( popupSettingPage );
    CleanupStack::PopAndDestroy( queryValueText );
    CleanupStack::PopAndDestroy( textArray );
    CleanupStack::PopAndDestroy( item );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPSPSelectCurrentItemL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPSPSelectCurrentItemL( CStifItemParser& /*aItem*/ )
    {
    CDesCArrayFlat* item = CCoeEnv::Static()->ReadDesCArrayResourceL( R_TESTSDK_LIST_ITEM_ARRAY );
    CleanupStack::PushL( item );
    STIF_ASSERT_NOT_NULL( item );
    
    CAknQueryValueTextArray* textArray = CAknQueryValueTextArray::NewL();
    CleanupStack::PushL( textArray );
    STIF_ASSERT_NOT_NULL( textArray );
    textArray->SetArray( *item );
    
    CAknQueryValueText* queryValueText = CAknQueryValueText::NewL();
    CleanupStack::PushL( queryValueText );
    STIF_ASSERT_NOT_NULL( queryValueText );
    queryValueText->SetArrayL( textArray );
    
    CTestSDKPopupsSPSP* popupSettingPage = new (ELeave) CTestSDKPopupsSPSP( 
        R_TESTSDK_POPUP_SETTING_PAGE, *queryValueText );
    CleanupStack::PushL( popupSettingPage );
    STIF_ASSERT_NOT_NULL( popupSettingPage );
    
    popupSettingPage->ConstructL();
    
    popupSettingPage->SelectCurrentItemL();
    
    CleanupStack::PopAndDestroy( popupSettingPage );
    CleanupStack::PopAndDestroy( queryValueText );
    CleanupStack::PopAndDestroy( textArray );
    CleanupStack::PopAndDestroy( item );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPSPWriteInternalStateL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPSPWriteInternalStateL( CStifItemParser& /*aItem*/ )
    {
    CDesCArrayFlat* item = CCoeEnv::Static()->ReadDesCArrayResourceL( R_TESTSDK_LIST_ITEM_ARRAY );
    CleanupStack::PushL( item );
    STIF_ASSERT_NOT_NULL( item );
    
    CAknQueryValueTextArray* textArray = CAknQueryValueTextArray::NewL();
    CleanupStack::PushL( textArray );
    STIF_ASSERT_NOT_NULL( textArray );
    textArray->SetArray( *item );
    
    CAknQueryValueText* queryValueText = CAknQueryValueText::NewL();
    CleanupStack::PushL( queryValueText );
    STIF_ASSERT_NOT_NULL( queryValueText );
    queryValueText->SetArrayL( textArray );
    
    CTestSDKPopupsSPSP* popupSettingPage = new (ELeave) CTestSDKPopupsSPSP( 
        R_TESTSDK_POPUP_SETTING_PAGE, *queryValueText );
    CleanupStack::PushL( popupSettingPage );
    STIF_ASSERT_NOT_NULL( popupSettingPage );
    
    popupSettingPage->ConstructL();
    
    const TInt LengthC = 200;
    CBufFlat* buf = CBufFlat::NewL( LengthC );
    CleanupStack::PushL( buf );
    STIF_ASSERT_NOT_NULL( buf );
    
    RBufWriteStream writeStream;
    CleanupClosePushL( writeStream );
    STIF_ASSERT_NOT_NULL( &writeStream );
    
    writeStream.Open( *buf );
    
    popupSettingPage->WriteInternalStateL( writeStream );
    
    CleanupStack::PopAndDestroy( &writeStream );
    CleanupStack::PopAndDestroy( buf );
    CleanupStack::PopAndDestroy( popupSettingPage );
    CleanupStack::PopAndDestroy( queryValueText );
    CleanupStack::PopAndDestroy( textArray );
    CleanupStack::PopAndDestroy( item );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPSPReservedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPSPReservedL( CStifItemParser& /*aItem*/ )
    {
    CDesCArrayFlat* item = CCoeEnv::Static()->ReadDesCArrayResourceL( R_TESTSDK_LIST_ITEM_ARRAY );
    CleanupStack::PushL( item );
    STIF_ASSERT_NOT_NULL( item );
    
    CAknQueryValueTextArray* textArray = CAknQueryValueTextArray::NewL();
    CleanupStack::PushL( textArray );
    STIF_ASSERT_NOT_NULL( textArray );
    textArray->SetArray( *item );
    
    CAknQueryValueText* queryValueText = CAknQueryValueText::NewL();
    CleanupStack::PushL( queryValueText );
    STIF_ASSERT_NOT_NULL( queryValueText );
    queryValueText->SetArrayL( textArray );
    
    _LIT( KSettingListTitle, "title" );
    TBufC<KLength> title ( KSettingListTitle );
    
    CTestSDKPopupsSPSP* popupSettingPage = new (ELeave) CTestSDKPopupsSPSP( 
         &title, 0, 0, 0, R_TESTSDK_POPUP_SETTING_PAGE, *queryValueText );
    CleanupStack::PushL( popupSettingPage );
    STIF_ASSERT_NOT_NULL( popupSettingPage );
    
    popupSettingPage->Reserved_2();
    
    CleanupStack::PopAndDestroy( popupSettingPage );
    CleanupStack::PopAndDestroy( queryValueText );
    CleanupStack::PopAndDestroy( textArray );
    CleanupStack::PopAndDestroy( item );
    
    return KErrNone;
    
    }
