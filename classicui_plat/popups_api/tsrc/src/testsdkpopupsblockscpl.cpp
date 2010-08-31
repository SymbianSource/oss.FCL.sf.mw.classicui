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
* Description:  test AknPopupLayout.h 
*
*/



// [INCLUDE FILES]
#include <aknpopupfield.h> 
#include <barsread.h>
#include <coemain.h>
#include <aknqueryvaluetext.h> 
#include <eikenv.h>
#include <aknlists.h>
#include <aknform.h>
#include <aknpopupheadingpane.h>
#include <aknsfld.h>
#include <coecntrl.h>
#include <testsdkpopups.rsg>

#include "testsdkpopups.hrh"
#include "testsdkpopups.h"
#include "testsdkpopupspl.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPLHandleSizeChangedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPLHandleSizeChangedL( CStifItemParser& /*aItem*/ )
    {
    CEikTextListBox* list = new( ELeave ) CAknSinglePopupMenuStyleListBox;
    CleanupStack::PushL( list );
    CTestSDKPopupsPL* popupList = CTestSDKPopupsPL::NewL( list, R_AVKON_SOFTKEYS_SELECT_CANCEL, AknPopupLayouts::EMenuWindow );
    CleanupStack::PushL( popupList );
    
    const TInt Maximumheight = 2;
    popupList->SetMaximumHeight( Maximumheight );
    
    list->ConstructL( popupList, CEikListBox::ELeftDownInViewRect );
    list->CreateScrollBarFrameL( ETrue );
    list->ScrollBarFrame()->SetScrollBarVisibilityL( CEikScrollBarFrame::EOff, CEikScrollBarFrame::EAuto );
    
    CDesCArray* items = CCoeEnv::Static()->ReadDesCArrayResourceL( R_TESTSDK_TEXT_ARRAY );
    CTextListBoxModel* model = list->Model();
    model->SetItemTextArray( items );
    model->SetOwnershipType( ELbmOwnsItemArray );
    
    TAknPopupLayoutsNode listNode = { 0, EListNode, popupList->ListBox() };
    TAknPopupLayoutsNode heading = { &listNode, EHeadingNode, static_cast<CCoeControl*> ( popupList->Heading() ) };
    TAknPopupLayoutsNode windowOwning = { &heading, EWindowOwningNode, popupList };
    TAknPopupLayoutsNode findPane = { &windowOwning, EFindBoxNode, static_cast<CCoeControl*> ( popupList->FindBox() ) };
    TAknPopupLayoutsNode *listBegin = &findPane;
    
    AknPopupLayouts::HandleSizeChanged( popupList->Layout(), AknPopupLayouts::EMenuWindow, listBegin );

    CleanupStack::PopAndDestroy( popupList );
    CleanupStack::PopAndDestroy( list );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPLHandleSizeChangedListBoxL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPLHandleSizeChangedListBoxL( CStifItemParser& /*aItem*/ )
    {
    CEikTextListBox* list = new( ELeave ) CAknSinglePopupMenuStyleListBox;
    CleanupStack::PushL( list );
    CTestSDKPopupsPL* popupList = CTestSDKPopupsPL::NewL( list, R_AVKON_SOFTKEYS_SELECT_CANCEL, AknPopupLayouts::EMenuWindow );
    CleanupStack::PushL( popupList );
    
    const TInt Maximumheight = 2;
    popupList->SetMaximumHeight( Maximumheight );
    
    list->ConstructL( popupList, CEikListBox::ELeftDownInViewRect );
    list->CreateScrollBarFrameL( ETrue );
    list->ScrollBarFrame()->SetScrollBarVisibilityL( CEikScrollBarFrame::EOff, CEikScrollBarFrame::EAuto );
    
    CDesCArray* items = CCoeEnv::Static()->ReadDesCArrayResourceL( R_TESTSDK_TEXT_ARRAY );
    CTextListBoxModel* model = list->Model();
    model->SetItemTextArray( items );
    model->SetOwnershipType( ELbmOwnsItemArray );
    
    TAknPopupLayoutsNode listNode = { 0, EListNode, popupList->ListBox() };
    TAknPopupLayoutsNode heading = { &listNode, EHeadingNode, static_cast<CCoeControl*> ( popupList->Heading() ) };
    TAknPopupLayoutsNode windowOwning = { &heading, EWindowOwningNode, popupList };
    TAknPopupLayoutsNode findPane = { &windowOwning, EFindBoxNode, static_cast<CCoeControl*> ( popupList->FindBox() ) };
    
    AknPopupLayouts::HandleSizeChanged( popupList->Layout(), AknPopupLayouts::EMenuWindow, popupList->Heading(), popupList->ListBox(), popupList );

    CleanupStack::PopAndDestroy( popupList );
    CleanupStack::PopAndDestroy( list );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPLHandleDrawL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPLHandleDrawL( CStifItemParser& /*aItem*/ )
    {
    CEikTextListBox* list = new( ELeave ) CAknSinglePopupMenuStyleListBox;
    CleanupStack::PushL( list );
    CTestSDKPopupsPL* popupList = CTestSDKPopupsPL::NewL( list, R_AVKON_SOFTKEYS_SELECT_CANCEL, AknPopupLayouts::EMenuWindow );
    CleanupStack::PushL( popupList );
    
    const TInt Maximumheight = 2;
    popupList->SetMaximumHeight( Maximumheight );
    
    list->ConstructL( popupList, CEikListBox::ELeftDownInViewRect );
    list->CreateScrollBarFrameL( ETrue );
    list->ScrollBarFrame()->SetScrollBarVisibilityL( CEikScrollBarFrame::EOff, CEikScrollBarFrame::EAuto );
    
    CDesCArray* items = CCoeEnv::Static()->ReadDesCArrayResourceL( R_TESTSDK_TEXT_ARRAY );
    CTextListBoxModel* model = list->Model();
    model->SetItemTextArray( items );
    model->SetOwnershipType( ELbmOwnsItemArray );
    
    TAknPopupLayoutsNode listNode = { 0, EListNode, popupList->ListBox() };
    TAknPopupLayoutsNode heading = { &listNode, EHeadingNode, static_cast<CCoeControl*> ( popupList->Heading() ) };
    TAknPopupLayoutsNode windowOwning = { &heading, EWindowOwningNode, popupList };
    TAknPopupLayoutsNode findPane = { &windowOwning, EFindBoxNode, static_cast<CCoeControl*> ( popupList->FindBox() ) };
    TAknPopupLayoutsNode *listBegin = &findPane;
    
    AknPopupLayouts::HandleSizeChanged( popupList->Layout(), AknPopupLayouts::EMenuWindow, listBegin );
    CWindowGc& gc = CCoeEnv::Static()->SystemGc();
    popupList->ActivateGc();
    AknPopupLayouts::HandleDraw( CEikonEnv::Static() , gc, popupList->Layout(), popupList->ListBox(), popupList->Heading() );
    popupList->DeactivateGc();
    
    CleanupStack::PopAndDestroy( popupList );
    CleanupStack::PopAndDestroy( list );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPLModifyWindowGraphicForHeadingL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPLModifyWindowGraphicForHeadingL( CStifItemParser& /*aItem*/ )
    {
    CEikTextListBox* list = new( ELeave ) CAknSinglePopupMenuStyleListBox;
    CleanupStack::PushL( list );
    CTestSDKPopupsPL* popupList = CTestSDKPopupsPL::NewL( list, R_AVKON_SOFTKEYS_SELECT_CANCEL, AknPopupLayouts::EMenuWindow );
    CleanupStack::PushL( popupList );
    
    const TInt Maximumheight = 2;
    popupList->SetMaximumHeight( Maximumheight );
    
    list->ConstructL( popupList, CEikListBox::ELeftDownInViewRect );
    list->CreateScrollBarFrameL( ETrue );
    list->ScrollBarFrame()->SetScrollBarVisibilityL( CEikScrollBarFrame::EOff, CEikScrollBarFrame::EAuto );
    
    CDesCArray* items = CCoeEnv::Static()->ReadDesCArrayResourceL( R_TESTSDK_TEXT_ARRAY );
    CTextListBoxModel* model = list->Model();
    model->SetItemTextArray( items );
    model->SetOwnershipType( ELbmOwnsItemArray );
    
    TAknPopupLayoutsNode listNode = { 0, EListNode, popupList->ListBox() };
    TAknPopupLayoutsNode heading = { &listNode, EHeadingNode, static_cast<CCoeControl*> ( popupList->Heading() ) };
    TAknPopupLayoutsNode windowOwning = { &heading, EWindowOwningNode, popupList };
    TAknPopupLayoutsNode findPane = { &windowOwning, EFindBoxNode, static_cast<CCoeControl*> ( popupList->FindBox() ) };
    
    AknPopupLayouts::ModifyWindowGraphicForHeading( popupList->Layout() );

    CleanupStack::PopAndDestroy( popupList );
    CleanupStack::PopAndDestroy( list );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPLModifyWindowGraphicForMessageBoxL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPLModifyWindowGraphicForMessageBoxL( CStifItemParser& /*aItem*/ )
    {
    CEikTextListBox* list = new( ELeave ) CAknSinglePopupMenuStyleListBox;
    CleanupStack::PushL( list );
    CTestSDKPopupsPL* popupList = CTestSDKPopupsPL::NewL( list, R_AVKON_SOFTKEYS_SELECT_CANCEL, AknPopupLayouts::EMenuWindow );
    CleanupStack::PushL( popupList );
    
    const TInt Maximumheight = 2;
    popupList->SetMaximumHeight( Maximumheight );
    
    list->ConstructL( popupList, CEikListBox::ELeftDownInViewRect );
    list->CreateScrollBarFrameL( ETrue );
    list->ScrollBarFrame()->SetScrollBarVisibilityL( CEikScrollBarFrame::EOff, CEikScrollBarFrame::EAuto );
    
    CDesCArray* items = CCoeEnv::Static()->ReadDesCArrayResourceL( R_TESTSDK_TEXT_ARRAY );
    CTextListBoxModel* model = list->Model();
    model->SetItemTextArray( items );
    model->SetOwnershipType( ELbmOwnsItemArray );
    
    TAknPopupLayoutsNode listNode = { 0, EListNode, popupList->ListBox() };
    TAknPopupLayoutsNode heading = { &listNode, EHeadingNode, static_cast<CCoeControl*> ( popupList->Heading() ) };
    TAknPopupLayoutsNode windowOwning = { &heading, EWindowOwningNode, popupList };
    TAknPopupLayoutsNode findPane = { &windowOwning, EFindBoxNode, static_cast<CCoeControl*> ( popupList->FindBox() ) };
    
    const TInt num = 2;
    AknPopupLayouts::ModifyWindowGraphicForMessageBox( popupList->Layout(), num );

    CleanupStack::PopAndDestroy( popupList );
    CleanupStack::PopAndDestroy( list );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPLCalcPopupMenuWindowL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPLCalcPopupMenuWindowL( CStifItemParser& /*aItem*/ )
    {
    CEikTextListBox* list = new( ELeave ) CAknSinglePopupMenuStyleListBox;
    CleanupStack::PushL( list );
    CTestSDKPopupsPL* popupList = CTestSDKPopupsPL::NewL( list, R_AVKON_SOFTKEYS_SELECT_CANCEL, AknPopupLayouts::EMenuWindow );
    CleanupStack::PushL( popupList );
    
    const TInt Maximumheight = 2;
    popupList->SetMaximumHeight( Maximumheight );
    
    list->ConstructL( popupList, CEikListBox::ELeftDownInViewRect );
    list->CreateScrollBarFrameL( ETrue );
    list->ScrollBarFrame()->SetScrollBarVisibilityL( CEikScrollBarFrame::EOff, CEikScrollBarFrame::EAuto );
    
    CDesCArray* items = CCoeEnv::Static()->ReadDesCArrayResourceL( R_TESTSDK_TEXT_ARRAY );
    CTextListBoxModel* model = list->Model();
    model->SetItemTextArray( items );
    model->SetOwnershipType( ELbmOwnsItemArray );
    
    TAknPopupLayoutsNode listNode = { 0, EListNode, popupList->ListBox() };
    TAknPopupLayoutsNode heading = { &listNode, EHeadingNode, static_cast<CCoeControl*> ( popupList->Heading() ) };
    TAknPopupLayoutsNode windowOwning = { &heading, EWindowOwningNode, popupList };
    TAknPopupLayoutsNode findPane = { &windowOwning, EFindBoxNode, static_cast<CCoeControl*> ( popupList->FindBox() ) };
    
    const TInt num = 2;
    TRect rect;
    AknPopupLayouts::CalcPopupMenuWindow( popupList->Layout(), rect, num );

    CleanupStack::PopAndDestroy( popupList );
    CleanupStack::PopAndDestroy( list );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPLCalcPopupMenuGraphicWindowL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPLCalcPopupMenuGraphicWindowL( CStifItemParser& /*aItem*/ )
    {
    CEikTextListBox* list = new( ELeave ) CAknSinglePopupMenuStyleListBox;
    CleanupStack::PushL( list );
    CTestSDKPopupsPL* popupList = CTestSDKPopupsPL::NewL( list, R_AVKON_SOFTKEYS_SELECT_CANCEL, AknPopupLayouts::EMenuWindow );
    CleanupStack::PushL( popupList );
    
    const TInt Maximumheight = 2;
    popupList->SetMaximumHeight( Maximumheight );
    
    list->ConstructL( popupList, CEikListBox::ELeftDownInViewRect );
    list->CreateScrollBarFrameL( ETrue );
    list->ScrollBarFrame()->SetScrollBarVisibilityL( CEikScrollBarFrame::EOff, CEikScrollBarFrame::EAuto );
    
    CDesCArray* items = CCoeEnv::Static()->ReadDesCArrayResourceL( R_TESTSDK_TEXT_ARRAY );
    CTextListBoxModel* model = list->Model();
    model->SetItemTextArray( items );
    model->SetOwnershipType( ELbmOwnsItemArray );
    
    TAknPopupLayoutsNode listNode = { 0, EListNode, popupList->ListBox() };
    TAknPopupLayoutsNode heading = { &listNode, EHeadingNode, static_cast<CCoeControl*> ( popupList->Heading() ) };
    TAknPopupLayoutsNode windowOwning = { &heading, EWindowOwningNode, popupList };
    TAknPopupLayoutsNode findPane = { &windowOwning, EFindBoxNode, static_cast<CCoeControl*> ( popupList->FindBox() ) };
    
    const TInt num = 2;
    TRect rect;
    AknPopupLayouts::CalcPopupMenuGraphicWindow( popupList->Layout(), rect, num );

    CleanupStack::PopAndDestroy( popupList );
    CleanupStack::PopAndDestroy( list );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPLCalcPopupMenuGraphicHeadingWindowL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPLCalcPopupMenuGraphicHeadingWindowL( CStifItemParser& /*aItem*/ )
    {
    CEikTextListBox* list = new( ELeave ) CAknSinglePopupMenuStyleListBox;
    CleanupStack::PushL( list );
    CTestSDKPopupsPL* popupList = CTestSDKPopupsPL::NewL( list, R_AVKON_SOFTKEYS_SELECT_CANCEL, AknPopupLayouts::EMenuWindow );
    CleanupStack::PushL( popupList );
    
    const TInt Maximumheight = 2;
    popupList->SetMaximumHeight( Maximumheight );
    
    list->ConstructL( popupList, CEikListBox::ELeftDownInViewRect );
    list->CreateScrollBarFrameL( ETrue );
    list->ScrollBarFrame()->SetScrollBarVisibilityL( CEikScrollBarFrame::EOff, CEikScrollBarFrame::EAuto );
    
    CDesCArray* items = CCoeEnv::Static()->ReadDesCArrayResourceL( R_TESTSDK_TEXT_ARRAY );
    CTextListBoxModel* model = list->Model();
    model->SetItemTextArray( items );
    model->SetOwnershipType( ELbmOwnsItemArray );
    
    TAknPopupLayoutsNode listNode = { 0, EListNode, popupList->ListBox() };
    TAknPopupLayoutsNode heading = { &listNode, EHeadingNode, static_cast<CCoeControl*> ( popupList->Heading() ) };
    TAknPopupLayoutsNode windowOwning = { &heading, EWindowOwningNode, popupList };
    TAknPopupLayoutsNode findPane = { &windowOwning, EFindBoxNode, static_cast<CCoeControl*> ( popupList->FindBox() ) };
    
    const TInt num = 2;
    TRect rect;
    AknPopupLayouts::CalcPopupMenuGraphicHeadingWindow( popupList->Layout(), rect, num );

    CleanupStack::PopAndDestroy( popupList );
    CleanupStack::PopAndDestroy( list );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPLCalcPopupMenuDoubleWindowL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPLCalcPopupMenuDoubleWindowL( CStifItemParser& /*aItem*/ )
    {
    CEikTextListBox* list = new( ELeave ) CAknSinglePopupMenuStyleListBox;
    CleanupStack::PushL( list );
    CTestSDKPopupsPL* popupList = CTestSDKPopupsPL::NewL( list, R_AVKON_SOFTKEYS_SELECT_CANCEL, AknPopupLayouts::EMenuWindow );
    CleanupStack::PushL( popupList );
    
    const TInt Maximumheight = 2;
    popupList->SetMaximumHeight( Maximumheight );
    
    list->ConstructL( popupList, CEikListBox::ELeftDownInViewRect );
    list->CreateScrollBarFrameL( ETrue );
    list->ScrollBarFrame()->SetScrollBarVisibilityL( CEikScrollBarFrame::EOff, CEikScrollBarFrame::EAuto );
    
    CDesCArray* items = CCoeEnv::Static()->ReadDesCArrayResourceL( R_TESTSDK_TEXT_ARRAY );
    CTextListBoxModel* model = list->Model();
    model->SetItemTextArray( items );
    model->SetOwnershipType( ELbmOwnsItemArray );
    
    TAknPopupLayoutsNode listNode = { 0, EListNode, popupList->ListBox() };
    TAknPopupLayoutsNode heading = { &listNode, EHeadingNode, static_cast<CCoeControl*> ( popupList->Heading() ) };
    TAknPopupLayoutsNode windowOwning = { &heading, EWindowOwningNode, popupList };
    TAknPopupLayoutsNode findPane = { &windowOwning, EFindBoxNode, static_cast<CCoeControl*> ( popupList->FindBox() ) };
    
    const TInt num = 2;
    TRect rect;
    AknPopupLayouts::CalcPopupMenuDoubleWindow( popupList->Layout(), rect, num );

    CleanupStack::PopAndDestroy( popupList );
    CleanupStack::PopAndDestroy( list );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPLCalcPopupMenuDoubleLargeGraphicWindowL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPLCalcPopupMenuDoubleLargeGraphicWindowL( CStifItemParser& /*aItem*/ )
    {
    CEikTextListBox* list = new( ELeave ) CAknSinglePopupMenuStyleListBox;
    CleanupStack::PushL( list );
    CTestSDKPopupsPL* popupList = CTestSDKPopupsPL::NewL( list, R_AVKON_SOFTKEYS_SELECT_CANCEL, AknPopupLayouts::EMenuWindow );
    CleanupStack::PushL( popupList );
    
    const TInt Maximumheight = 2;
    popupList->SetMaximumHeight( Maximumheight );
    
    list->ConstructL( popupList, CEikListBox::ELeftDownInViewRect );
    list->CreateScrollBarFrameL( ETrue );
    list->ScrollBarFrame()->SetScrollBarVisibilityL( CEikScrollBarFrame::EOff, CEikScrollBarFrame::EAuto );
    
    CDesCArray* items = CCoeEnv::Static()->ReadDesCArrayResourceL( R_TESTSDK_TEXT_ARRAY );
    CTextListBoxModel* model = list->Model();
    model->SetItemTextArray( items );
    model->SetOwnershipType( ELbmOwnsItemArray );
    
    TAknPopupLayoutsNode listNode = { 0, EListNode, popupList->ListBox() };
    TAknPopupLayoutsNode heading = { &listNode, EHeadingNode, static_cast<CCoeControl*> ( popupList->Heading() ) };
    TAknPopupLayoutsNode windowOwning = { &heading, EWindowOwningNode, popupList };
    TAknPopupLayoutsNode findPane = { &windowOwning, EFindBoxNode, static_cast<CCoeControl*> ( popupList->FindBox() ) };
    
    const TInt num = 2;
    TRect rect;
    AknPopupLayouts::CalcPopupMenuDoubleLargeGraphicWindow( popupList->Layout(), rect, num );

    CleanupStack::PopAndDestroy( popupList );
    CleanupStack::PopAndDestroy( list );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPLCalcPopupSNoteGroupWindowL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPLCalcPopupSNoteGroupWindowL( CStifItemParser& /*aItem*/ )
    {
    CEikTextListBox* list = new( ELeave ) CAknSinglePopupMenuStyleListBox;
    CleanupStack::PushL( list );
    CTestSDKPopupsPL* popupList = CTestSDKPopupsPL::NewL( list, R_AVKON_SOFTKEYS_SELECT_CANCEL, AknPopupLayouts::EMenuWindow );
    CleanupStack::PushL( popupList );
    
    const TInt Maximumheight = 2;
    popupList->SetMaximumHeight( Maximumheight );
    
    list->ConstructL( popupList, CEikListBox::ELeftDownInViewRect );
    list->CreateScrollBarFrameL( ETrue );
    list->ScrollBarFrame()->SetScrollBarVisibilityL( CEikScrollBarFrame::EOff, CEikScrollBarFrame::EAuto );
    
    CDesCArray* items = CCoeEnv::Static()->ReadDesCArrayResourceL( R_TESTSDK_TEXT_ARRAY );
    CTextListBoxModel* model = list->Model();
    model->SetItemTextArray( items );
    model->SetOwnershipType( ELbmOwnsItemArray );
    
    TAknPopupLayoutsNode listNode = { 0, EListNode, popupList->ListBox() };
    TAknPopupLayoutsNode heading = { &listNode, EHeadingNode, static_cast<CCoeControl*> ( popupList->Heading() ) };
    TAknPopupLayoutsNode windowOwning = { &heading, EWindowOwningNode, popupList };
    TAknPopupLayoutsNode findPane = { &windowOwning, EFindBoxNode, static_cast<CCoeControl*> ( popupList->FindBox() ) };
    
    const TInt num = 2;
    TRect rect;
    AknPopupLayouts::CalcPopupSNoteGroupWindow( popupList->Layout(), rect, num );

    CleanupStack::PopAndDestroy( popupList );
    CleanupStack::PopAndDestroy( list );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPLSetupMenuPopupWindowL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPLSetupMenuPopupWindowL( CStifItemParser& /*aItem*/ )
    {
    CEikTextListBox* list = new( ELeave ) CAknSinglePopupMenuStyleListBox;
    CleanupStack::PushL( list );
    CTestSDKPopupsPL* popupList = CTestSDKPopupsPL::NewL( list, R_AVKON_SOFTKEYS_SELECT_CANCEL, AknPopupLayouts::EMenuWindow );
    CleanupStack::PushL( popupList );
    
    const TInt Maximumheight = 2;
    popupList->SetMaximumHeight( Maximumheight );
    
    list->ConstructL( popupList, CEikListBox::ELeftDownInViewRect );
    list->CreateScrollBarFrameL( ETrue );
    list->ScrollBarFrame()->SetScrollBarVisibilityL( CEikScrollBarFrame::EOff, CEikScrollBarFrame::EAuto );
    
    CDesCArray* items = CCoeEnv::Static()->ReadDesCArrayResourceL( R_TESTSDK_TEXT_ARRAY );
    CTextListBoxModel* model = list->Model();
    model->SetItemTextArray( items );
    model->SetOwnershipType( ELbmOwnsItemArray );
    
    TAknPopupLayoutsNode listNode = { 0, EListNode, popupList->ListBox() };
    TAknPopupLayoutsNode heading = { &listNode, EHeadingNode, static_cast<CCoeControl*> ( popupList->Heading() ) };
    TAknPopupLayoutsNode windowOwning = { &heading, EWindowOwningNode, popupList };
    TAknPopupLayoutsNode findPane = { &windowOwning, EFindBoxNode, static_cast<CCoeControl*> ( popupList->FindBox() ) };
    
    const TInt num = 2;
    AknPopupLayouts::SetupMenuPopupWindow( popupList->Layout(), num, ETrue );

    CleanupStack::PopAndDestroy( popupList );
    CleanupStack::PopAndDestroy( list );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPLSetupPopupMenuGraphicWindowL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPLSetupPopupMenuGraphicWindowL( CStifItemParser& /*aItem*/ )
    {
    CEikTextListBox* list = new( ELeave ) CAknSinglePopupMenuStyleListBox;
    CleanupStack::PushL( list );
    CTestSDKPopupsPL* popupList = CTestSDKPopupsPL::NewL( list, R_AVKON_SOFTKEYS_SELECT_CANCEL, AknPopupLayouts::EMenuWindow );
    CleanupStack::PushL( popupList );
    
    const TInt Maximumheight = 2;
    popupList->SetMaximumHeight( Maximumheight );
    
    list->ConstructL( popupList, CEikListBox::ELeftDownInViewRect );
    list->CreateScrollBarFrameL( ETrue );
    list->ScrollBarFrame()->SetScrollBarVisibilityL( CEikScrollBarFrame::EOff, CEikScrollBarFrame::EAuto );
    
    CDesCArray* items = CCoeEnv::Static()->ReadDesCArrayResourceL( R_TESTSDK_TEXT_ARRAY );
    CTextListBoxModel* model = list->Model();
    model->SetItemTextArray( items );
    model->SetOwnershipType( ELbmOwnsItemArray );
    
    TAknPopupLayoutsNode listNode = { 0, EListNode, popupList->ListBox() };
    TAknPopupLayoutsNode heading = { &listNode, EHeadingNode, static_cast<CCoeControl*> ( popupList->Heading() ) };
    TAknPopupLayoutsNode windowOwning = { &heading, EWindowOwningNode, popupList };
    TAknPopupLayoutsNode findPane = { &windowOwning, EFindBoxNode, static_cast<CCoeControl*> ( popupList->FindBox() ) };
    
    const TInt num = 2;
    AknPopupLayouts::SetupPopupMenuGraphicWindow( popupList->Layout(), num, ETrue );

    CleanupStack::PopAndDestroy( popupList );
    CleanupStack::PopAndDestroy( list );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPLSetupPopupMenuGraphicHeadingWindowL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPLSetupPopupMenuGraphicHeadingWindowL( CStifItemParser& /*aItem*/ )
    {
    CEikTextListBox* list = new( ELeave ) CAknSinglePopupMenuStyleListBox;
    CleanupStack::PushL( list );
    CTestSDKPopupsPL* popupList = CTestSDKPopupsPL::NewL( list, R_AVKON_SOFTKEYS_SELECT_CANCEL, AknPopupLayouts::EMenuWindow );
    CleanupStack::PushL( popupList );
    
    const TInt Maximumheight = 2;
    popupList->SetMaximumHeight( Maximumheight );
    
    list->ConstructL( popupList, CEikListBox::ELeftDownInViewRect );
    list->CreateScrollBarFrameL( ETrue );
    list->ScrollBarFrame()->SetScrollBarVisibilityL( CEikScrollBarFrame::EOff, CEikScrollBarFrame::EAuto );
    
    CDesCArray* items = CCoeEnv::Static()->ReadDesCArrayResourceL( R_TESTSDK_TEXT_ARRAY );
    CTextListBoxModel* model = list->Model();
    model->SetItemTextArray( items );
    model->SetOwnershipType( ELbmOwnsItemArray );
    
    TAknPopupLayoutsNode listNode = { 0, EListNode, popupList->ListBox() };
    TAknPopupLayoutsNode heading = { &listNode, EHeadingNode, static_cast<CCoeControl*> ( popupList->Heading() ) };
    TAknPopupLayoutsNode windowOwning = { &heading, EWindowOwningNode, popupList };
    TAknPopupLayoutsNode findPane = { &windowOwning, EFindBoxNode, static_cast<CCoeControl*> ( popupList->FindBox() ) };
    
    const TInt num = 2;
    AknPopupLayouts::SetupPopupMenuGraphicHeadingWindow( popupList->Layout(), num, ETrue );

    CleanupStack::PopAndDestroy( popupList );
    CleanupStack::PopAndDestroy( list );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPLSetupPopupMenuDoubleWindowL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPLSetupPopupMenuDoubleWindowL( CStifItemParser& /*aItem*/ )
    {
    CEikTextListBox* list = new( ELeave ) CAknSinglePopupMenuStyleListBox;
    CleanupStack::PushL( list );
    CTestSDKPopupsPL* popupList = CTestSDKPopupsPL::NewL( list, R_AVKON_SOFTKEYS_SELECT_CANCEL, AknPopupLayouts::EMenuWindow );
    CleanupStack::PushL( popupList );
    
    const TInt Maximumheight = 2;
    popupList->SetMaximumHeight( Maximumheight );
    
    list->ConstructL( popupList, CEikListBox::ELeftDownInViewRect );
    list->CreateScrollBarFrameL( ETrue );
    list->ScrollBarFrame()->SetScrollBarVisibilityL( CEikScrollBarFrame::EOff, CEikScrollBarFrame::EAuto );
    
    CDesCArray* items = CCoeEnv::Static()->ReadDesCArrayResourceL( R_TESTSDK_TEXT_ARRAY );
    CTextListBoxModel* model = list->Model();
    model->SetItemTextArray( items );
    model->SetOwnershipType( ELbmOwnsItemArray );
    
    TAknPopupLayoutsNode listNode = { 0, EListNode, popupList->ListBox() };
    TAknPopupLayoutsNode heading = { &listNode, EHeadingNode, static_cast<CCoeControl*> ( popupList->Heading() ) };
    TAknPopupLayoutsNode windowOwning = { &heading, EWindowOwningNode, popupList };
    TAknPopupLayoutsNode findPane = { &windowOwning, EFindBoxNode, static_cast<CCoeControl*> ( popupList->FindBox() ) };
    
    const TInt num = 2;
    AknPopupLayouts::SetupPopupMenuDoubleWindow( popupList->Layout(), num, ETrue );

    CleanupStack::PopAndDestroy( popupList );
    CleanupStack::PopAndDestroy( list );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPLSetupImageSelectionMenuPopupWindowL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPLSetupImageSelectionMenuPopupWindowL( CStifItemParser& /*aItem*/ )
    {
    CEikTextListBox* list = new( ELeave ) CAknSinglePopupMenuStyleListBox;
    CleanupStack::PushL( list );
    CTestSDKPopupsPL* popupList = CTestSDKPopupsPL::NewL( list, R_AVKON_SOFTKEYS_SELECT_CANCEL, AknPopupLayouts::EMenuWindow );
    CleanupStack::PushL( popupList );
    
    const TInt Maximumheight = 2;
    popupList->SetMaximumHeight( Maximumheight );
    
    list->ConstructL( popupList, CEikListBox::ELeftDownInViewRect );
    list->CreateScrollBarFrameL( ETrue );
    list->ScrollBarFrame()->SetScrollBarVisibilityL( CEikScrollBarFrame::EOff, CEikScrollBarFrame::EAuto );
    
    CDesCArray* items = CCoeEnv::Static()->ReadDesCArrayResourceL( R_TESTSDK_TEXT_ARRAY );
    CTextListBoxModel* model = list->Model();
    model->SetItemTextArray( items );
    model->SetOwnershipType( ELbmOwnsItemArray );
    
    TAknPopupLayoutsNode listNode = { 0, EListNode, popupList->ListBox() };
    TAknPopupLayoutsNode heading = { &listNode, EHeadingNode, static_cast<CCoeControl*> ( popupList->Heading() ) };
    TAknPopupLayoutsNode windowOwning = { &heading, EWindowOwningNode, popupList };
    TAknPopupLayoutsNode findPane = { &windowOwning, EFindBoxNode, static_cast<CCoeControl*> ( popupList->FindBox() ) };
    
    const TInt num = 2;
    AknPopupLayouts::SetupImageSelectionMenuPopupWindow( popupList->Layout(), num, ETrue );

    CleanupStack::PopAndDestroy( popupList );
    CleanupStack::PopAndDestroy( list );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPLSetupPopupSNoteGroupWindowL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPLSetupPopupSNoteGroupWindowL( CStifItemParser& /*aItem*/ )
    {
    CEikTextListBox* list = new( ELeave ) CAknSinglePopupMenuStyleListBox;
    CleanupStack::PushL( list );
    CTestSDKPopupsPL* popupList = CTestSDKPopupsPL::NewL( list, R_AVKON_SOFTKEYS_SELECT_CANCEL, AknPopupLayouts::EMenuWindow );
    CleanupStack::PushL( popupList );
    
    const TInt Maximumheight = 2;
    popupList->SetMaximumHeight( Maximumheight );
    
    list->ConstructL( popupList, CEikListBox::ELeftDownInViewRect );
    list->CreateScrollBarFrameL( ETrue );
    list->ScrollBarFrame()->SetScrollBarVisibilityL( CEikScrollBarFrame::EOff, CEikScrollBarFrame::EAuto );
    
    CDesCArray* items = CCoeEnv::Static()->ReadDesCArrayResourceL( R_TESTSDK_TEXT_ARRAY );
    CTextListBoxModel* model = list->Model();
    model->SetItemTextArray( items );
    model->SetOwnershipType( ELbmOwnsItemArray );
    
    TAknPopupLayoutsNode listNode = { 0, EListNode, popupList->ListBox() };
    TAknPopupLayoutsNode heading = { &listNode, EHeadingNode, static_cast<CCoeControl*> ( popupList->Heading() ) };
    TAknPopupLayoutsNode windowOwning = { &heading, EWindowOwningNode, popupList };
    TAknPopupLayoutsNode findPane = { &windowOwning, EFindBoxNode, static_cast<CCoeControl*> ( popupList->FindBox() ) };
    
    const TInt num = 2;
    AknPopupLayouts::SetupPopupSNoteGroupWindow( popupList->Layout(), num, ETrue );

    CleanupStack::PopAndDestroy( popupList );
    CleanupStack::PopAndDestroy( list );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPLHandleSizeAndPositionOfComponentsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPLHandleSizeAndPositionOfComponentsL( CStifItemParser& /*aItem*/ )
    {
    CEikTextListBox* list = new( ELeave ) CAknSinglePopupMenuStyleListBox;
    CleanupStack::PushL( list );
    CTestSDKPopupsPL* popupList = CTestSDKPopupsPL::NewL( list, R_AVKON_SOFTKEYS_SELECT_CANCEL, AknPopupLayouts::EMenuWindow );
    CleanupStack::PushL( popupList );
    
    const TInt Maximumheight = 2;
    popupList->SetMaximumHeight( Maximumheight );
    
    list->ConstructL( popupList, CEikListBox::ELeftDownInViewRect );
    list->CreateScrollBarFrameL( ETrue );
    list->ScrollBarFrame()->SetScrollBarVisibilityL( CEikScrollBarFrame::EOff, CEikScrollBarFrame::EAuto );
    
    CDesCArray* items = CCoeEnv::Static()->ReadDesCArrayResourceL( R_TESTSDK_TEXT_ARRAY );
    CTextListBoxModel* model = list->Model();
    model->SetItemTextArray( items );
    model->SetOwnershipType( ELbmOwnsItemArray );
    
    TAknPopupLayoutsNode listNode = { 0, EListNode, popupList->ListBox() };
    TAknPopupLayoutsNode heading = { &listNode, EHeadingNode, static_cast<CCoeControl*> ( popupList->Heading() ) };
    TAknPopupLayoutsNode windowOwning = { &heading, EWindowOwningNode, popupList };
    TAknPopupLayoutsNode findPane = { &windowOwning, EFindBoxNode, static_cast<CCoeControl*> ( popupList->FindBox() ) };
    TAknPopupLayoutsNode *listBegin = &findPane;
    
    AknPopupLayouts::HandleSizeChanged( popupList->Layout(), AknPopupLayouts::EMenuWindow, listBegin );
    AknPopupLayouts::HandleSizeAndPositionOfComponents( popupList->Layout(), popupList->ListBox(), popupList->Heading() );

    CleanupStack::PopAndDestroy( popupList );
    CleanupStack::PopAndDestroy( list );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPLSetupDefaultsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPLSetupDefaultsL( CStifItemParser& /*aItem*/ )
    {
    CEikTextListBox* list = new( ELeave ) CAknSinglePopupMenuStyleListBox;
    CleanupStack::PushL( list );
    CTestSDKPopupsPL* popupList = CTestSDKPopupsPL::NewL( list, R_AVKON_SOFTKEYS_SELECT_CANCEL, AknPopupLayouts::EMenuWindow );
    CleanupStack::PushL( popupList );
    
    const TInt Maximumheight = 2;
    popupList->SetMaximumHeight( Maximumheight );
    
    list->ConstructL( popupList, CEikListBox::ELeftDownInViewRect );
    list->CreateScrollBarFrameL( ETrue );
    list->ScrollBarFrame()->SetScrollBarVisibilityL( CEikScrollBarFrame::EOff, CEikScrollBarFrame::EAuto );
    
    CDesCArray* items = CCoeEnv::Static()->ReadDesCArrayResourceL( R_TESTSDK_TEXT_ARRAY );
    CTextListBoxModel* model = list->Model();
    model->SetItemTextArray( items );
    model->SetOwnershipType( ELbmOwnsItemArray );
    
    TAknPopupLayoutsNode listNode = { 0, EListNode, popupList->ListBox() };
    TAknPopupLayoutsNode heading = { &listNode, EHeadingNode, static_cast<CCoeControl*> ( popupList->Heading() ) };
    TAknPopupLayoutsNode windowOwning = { &heading, EWindowOwningNode, popupList };
    TAknPopupLayoutsNode findPane = { &windowOwning, EFindBoxNode, static_cast<CCoeControl*> ( popupList->FindBox() ) };
    
    AknPopupLayouts::SetupDefaults( popupList->Layout() );

    CleanupStack::PopAndDestroy( popupList );
    CleanupStack::PopAndDestroy( list );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPLWindowRectL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPLWindowRectL( CStifItemParser& /*aItem*/ )
    {
    CEikTextListBox* list = new( ELeave ) CAknSinglePopupMenuStyleListBox;
    CleanupStack::PushL( list );
    CTestSDKPopupsPL* popupList = CTestSDKPopupsPL::NewL( list, R_AVKON_SOFTKEYS_SELECT_CANCEL, AknPopupLayouts::EMenuWindow );
    CleanupStack::PushL( popupList );
    
    const TInt Maximumheight = 2;
    popupList->SetMaximumHeight( Maximumheight );
    
    list->ConstructL( popupList, CEikListBox::ELeftDownInViewRect );
    list->CreateScrollBarFrameL( ETrue );
    list->ScrollBarFrame()->SetScrollBarVisibilityL( CEikScrollBarFrame::EOff, CEikScrollBarFrame::EAuto );
    
    CDesCArray* items = CCoeEnv::Static()->ReadDesCArrayResourceL( R_TESTSDK_TEXT_ARRAY );
    CTextListBoxModel* model = list->Model();
    model->SetItemTextArray( items );
    model->SetOwnershipType( ELbmOwnsItemArray );
    
    TAknPopupLayoutsNode listNode = { 0, EListNode, popupList->ListBox() };
    TAknPopupLayoutsNode heading = { &listNode, EHeadingNode, static_cast<CCoeControl*> ( popupList->Heading() ) };
    TAknPopupLayoutsNode windowOwning = { &heading, EWindowOwningNode, popupList };
    TAknPopupLayoutsNode findPane = { &windowOwning, EFindBoxNode, static_cast<CCoeControl*> ( popupList->FindBox() ) };
    
    TRect rect = AknPopupLayouts::WindowRect( popupList->Layout() );
    STIF_ASSERT_NOT_NULL( &rect );
    TSize size = rect.Size();
    TPoint point = size.AsPoint();
    STIF_ASSERT_EQUALS( point.iX, 0 );
    STIF_ASSERT_EQUALS( point.iY, 0 );
    
    CleanupStack::PopAndDestroy( popupList );
    CleanupStack::PopAndDestroy( list );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPLMenuRectL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPLMenuRectL( CStifItemParser& /*aItem*/ )
    {
    CEikTextListBox* list = new( ELeave ) CAknSinglePopupMenuStyleListBox;
    CleanupStack::PushL( list );
    CTestSDKPopupsPL* popupList = CTestSDKPopupsPL::NewL( list, R_AVKON_SOFTKEYS_SELECT_CANCEL, AknPopupLayouts::EMenuWindow );
    CleanupStack::PushL( popupList );
    
    const TInt Maximumheight = 2;
    popupList->SetMaximumHeight( Maximumheight );
    
    list->ConstructL( popupList, CEikListBox::ELeftDownInViewRect );
    list->CreateScrollBarFrameL( ETrue );
    list->ScrollBarFrame()->SetScrollBarVisibilityL( CEikScrollBarFrame::EOff, CEikScrollBarFrame::EAuto );
    
    CDesCArray* items = CCoeEnv::Static()->ReadDesCArrayResourceL( R_TESTSDK_TEXT_ARRAY );
    CTextListBoxModel* model = list->Model();
    model->SetItemTextArray( items );
    model->SetOwnershipType( ELbmOwnsItemArray );
    
    TAknPopupLayoutsNode listNode = { 0, EListNode, popupList->ListBox() };
    TAknPopupLayoutsNode heading = { &listNode, EHeadingNode, static_cast<CCoeControl*> ( popupList->Heading() ) };
    TAknPopupLayoutsNode windowOwning = { &heading, EWindowOwningNode, popupList };
    TAknPopupLayoutsNode findPane = { &windowOwning, EFindBoxNode, static_cast<CCoeControl*> ( popupList->FindBox() ) };
    
    TRect rect = AknPopupLayouts::MenuRect( popupList->Layout() );
    STIF_ASSERT_NOT_NULL( &rect );
    TSize size = rect.Size();
    TPoint point = size.AsPoint();
    STIF_ASSERT_EQUALS( point.iX, 0 );
    STIF_ASSERT_EQUALS( point.iY, 0 );
    
    CleanupStack::PopAndDestroy( popupList );
    CleanupStack::PopAndDestroy( list );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPLCheckRangeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPLCheckRangeL( CStifItemParser& /*aItem*/ )
    {
    CEikTextListBox* list = new( ELeave ) CAknSinglePopupMenuStyleListBox;
    CleanupStack::PushL( list );
    CTestSDKPopupsPL* popupList = CTestSDKPopupsPL::NewL( list, R_AVKON_SOFTKEYS_SELECT_CANCEL, AknPopupLayouts::EMenuWindow );
    CleanupStack::PushL( popupList );
    
    const TInt Maximumheight = 2;
    popupList->SetMaximumHeight( Maximumheight );
    
    list->ConstructL( popupList, CEikListBox::ELeftDownInViewRect );
    list->CreateScrollBarFrameL( ETrue );
    list->ScrollBarFrame()->SetScrollBarVisibilityL( CEikScrollBarFrame::EOff, CEikScrollBarFrame::EAuto );
    
    CDesCArray* items = CCoeEnv::Static()->ReadDesCArrayResourceL( R_TESTSDK_TEXT_ARRAY );
    CTextListBoxModel* model = list->Model();
    model->SetItemTextArray( items );
    model->SetOwnershipType( ELbmOwnsItemArray );
    
    TAknPopupLayoutsNode listNode = { 0, EListNode, popupList->ListBox() };
    TAknPopupLayoutsNode heading = { &listNode, EHeadingNode, static_cast<CCoeControl*> ( popupList->Heading() ) };
    TAknPopupLayoutsNode windowOwning = { &heading, EWindowOwningNode, popupList };
    TAknPopupLayoutsNode findPane = { &windowOwning, EFindBoxNode, static_cast<CCoeControl*> ( popupList->FindBox() ) };
    
    TInt value = 1;
    const TInt min = 2;
    const TInt max = 3;
    AknPopupLayouts::CheckRange( value, min, max );
    
    CleanupStack::PopAndDestroy( popupList );
    CleanupStack::PopAndDestroy( list );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKPopups::TestCPLMenuPopupWindowGraphicsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKPopups::TestCPLMenuPopupWindowGraphicsL( CStifItemParser& /*aItem*/ )
    {
    CEikTextListBox* list = new( ELeave ) CAknSinglePopupMenuStyleListBox;
    CleanupStack::PushL( list );
    CTestSDKPopupsPL* popupList = CTestSDKPopupsPL::NewL( list, R_AVKON_SOFTKEYS_SELECT_CANCEL, AknPopupLayouts::EMenuWindow );
    CleanupStack::PushL( popupList );
    
    const TInt Maximumheight = 2;
    popupList->SetMaximumHeight( Maximumheight );
    
    list->ConstructL( popupList, CEikListBox::ELeftDownInViewRect );
    list->CreateScrollBarFrameL( ETrue );
    list->ScrollBarFrame()->SetScrollBarVisibilityL( CEikScrollBarFrame::EOff, CEikScrollBarFrame::EAuto );
    
    CDesCArray* items = CCoeEnv::Static()->ReadDesCArrayResourceL( R_TESTSDK_TEXT_ARRAY );
    CTextListBoxModel* model = list->Model();
    model->SetItemTextArray( items );
    model->SetOwnershipType( ELbmOwnsItemArray );
    
    TAknPopupLayoutsNode listNode = { 0, EListNode, popupList->ListBox() };
    TAknPopupLayoutsNode heading = { &listNode, EHeadingNode, static_cast<CCoeControl*> ( popupList->Heading() ) };
    TAknPopupLayoutsNode windowOwning = { &heading, EWindowOwningNode, popupList };
    TAknPopupLayoutsNode findPane = { &windowOwning, EFindBoxNode, static_cast<CCoeControl*> ( popupList->FindBox() ) };
    
    AknPopupLayouts::MenuPopupWindowGraphics( popupList->Layout() );
    
    CleanupStack::PopAndDestroy( popupList );
    CleanupStack::PopAndDestroy( list );
    
    return KErrNone;
    
    }
