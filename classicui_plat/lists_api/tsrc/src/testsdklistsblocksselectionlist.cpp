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
* Description:  Test CAknListBoxLayoutDecorator.H
*
*/


// [INCLUDE FILES]
#include <e32base.h>
#include <aknselectionlist.h>
#include <testsdklists.rsg>
#include <coemain.h>
#include <coeaui.h>

#include "testsdklists.h"
#include "testsdkcontainer.h"
#include "testsdklistsselectionlistdialog.h"
#include "testsdklistsmarkablelistdialog.h"

const TInt KUnexpected = 0;
const TInt KNum = 10;
// ============================ MEMBER FUNCTIONS ===============================

//========================== CAknSelectionListDialog ===========================
// -----------------------------------------------------------------------------
// CTestSDKLists::TestSLDNewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSLDNewL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AknSelectionListTestModule" );
    _LIT( KTestSLDNewL, "In TestSLDNewL" );
    TestModuleIf().Printf( 0, KTestModule, KTestSLDNewL );
    // Print to log file
    iLog->Log( KTestSLDNewL );

    TInt value = -1;

    CDesCArray* textArray = NULL;   
    textArray = CCoeEnv::Static()->ReadDesCArrayResourceL( R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );

    CAknSelectionListDialog* selLDlg = 
        CAknSelectionListDialog::NewL( value, textArray, R_AVKON_DIALOG_EMPTY_MENUBAR, NULL );
    CleanupStack::PushL( selLDlg );
    STIF_ASSERT_NOT_NULL( selLDlg );

    CleanupStack::PopAndDestroy( 2 );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSLDNewLC
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSLDNewLC( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AknSelectionListTestModule" );
    _LIT( KTestSLDNewLC, "In TestSLDNewLC" );
    TestModuleIf().Printf( 0, KTestModule, KTestSLDNewLC );
    // Print to log file
    iLog->Log( KTestSLDNewLC );

    TInt value = -1;

    CDesCArray* textArray = NULL;   
    textArray = CCoeEnv::Static()->ReadDesCArrayResourceL( R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );

    CAknSelectionListDialog* selLDlg = 
        CAknSelectionListDialog::NewLC( value, textArray, R_AVKON_DIALOG_EMPTY_MENUBAR, NULL );
    
    STIF_ASSERT_NOT_NULL( selLDlg );

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSLDConstructL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSLDConstructL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AknSelectionListTestModule" );
    _LIT( KTestSLDConstructL, "In TestSLDConstructL" );
    TestModuleIf().Printf( 0, KTestModule, KTestSLDConstructL );
    // Print to log file
    iLog->Log( KTestSLDConstructL );

    TInt value = -1;

    CDesCArray* textArray = NULL;   
    textArray = CCoeEnv::Static()->ReadDesCArrayResourceL( R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );

    CAknSelectionListDialog* selLDlg = 
        CAknSelectionListDialog::NewL( value, textArray, R_AVKON_DIALOG_EMPTY_MENUBAR, NULL );
    CleanupStack::PushL( selLDlg );

    TInt err = KErrNone;
    TRAP( err, selLDlg->ConstructL( R_AVKON_DIALOG_EMPTY_MENUBAR ) );

    CleanupStack::PopAndDestroy( 2 );

    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSLDSetupFindL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSLDSetupFindL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AknSelectionListTestModule" );
    _LIT( KTestSLDSetupFindL, "In TestSLDSetupFindL" );
    TestModuleIf().Printf( 0, KTestModule, KTestSLDSetupFindL );
    // Print to log file
    iLog->Log( KTestSLDSetupFindL );

    TInt value = -1;

    CDesCArray* textArray = NULL;   
    textArray = CCoeEnv::Static()->ReadDesCArrayResourceL( R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );

    CAknSelectionListDialog* selLDlg = 
        CAknSelectionListDialog::NewL( value, textArray, R_AVKON_DIALOG_EMPTY_MENUBAR, NULL );
    CleanupStack::PushL( selLDlg );

    selLDlg->SetupFind( CAknSelectionListDialog::EFixedFind );

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSLDIconArrayL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSLDIconArrayL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AknSelectionListTestModule" );
    _LIT( KTestSLDIconArrayL, "In TestSLDIconArrayL" );
    TestModuleIf().Printf( 0, KTestModule, KTestSLDIconArrayL );
    // Print to log file
    iLog->Log( KTestSLDIconArrayL );

    TInt value = -1;

    CDesCArray* textArray = NULL;   
    textArray = CCoeEnv::Static()->ReadDesCArrayResourceL( R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );

    CAknSelectionListDialog* selLDlg = 
        CAknSelectionListDialog::NewL( value, textArray, R_AVKON_DIALOG_EMPTY_MENUBAR, NULL );
    CleanupStack::PushL( selLDlg );
    selLDlg->SetContainerWindowL( *iContainer );
    selLDlg->PrepareLC( R_TESTLIST_SELECTION_LIST_DIALOG );

    CArrayPtr<CGulIcon>* icons = new( ELeave ) CArrayPtrFlat<CGulIcon>( KNum );
    CleanupStack::PushL( icons );
    selLDlg->SetIconArrayL( icons );
    CArrayPtr<CGulIcon>* getIcons = selLDlg->IconArray();
    STIF_ASSERT_TRUE( icons == getIcons );

    CleanupStack::Pop( 2 );
    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSLDSetIconArrayL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSLDSetIconArrayL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AknSelectionListTestModule" );
    _LIT( KTestSLDSetIconArrayL, "In TestSLDSetIconArrayL" );
    TestModuleIf().Printf( 0, KTestModule, KTestSLDSetIconArrayL );
    // Print to log file
    iLog->Log( KTestSLDSetIconArrayL );

    TInt value = -1;

    CDesCArray* textArray = NULL;   
    textArray = CCoeEnv::Static()->ReadDesCArrayResourceL( R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );

    CAknSelectionListDialog* selLDlg = 
        CAknSelectionListDialog::NewL( value, textArray, R_AVKON_DIALOG_EMPTY_MENUBAR, NULL );
    CleanupStack::PushL( selLDlg );
    selLDlg->SetContainerWindowL( *iContainer );
    selLDlg->PrepareLC( R_TESTLIST_SELECTION_LIST_DIALOG );

    TInt err = KErrNone;
    CArrayPtr<CGulIcon>* icons = new( ELeave ) CArrayPtrFlat<CGulIcon>( KNum );
    CleanupStack::PushL( icons );
    TRAP( err, selLDlg->SetIconArrayL( icons ) );

    CleanupStack::Pop( 2 );
    CleanupStack::PopAndDestroy( 2 );

    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSLDHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSLDHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AknSelectionListTestModule" );
    _LIT( KTestSLDHandlePointerEventL, "In TestSLDHandlePointerEventL" );
    TestModuleIf().Printf( 0, KTestModule, KTestSLDHandlePointerEventL );
    // Print to log file
    iLog->Log( KTestSLDHandlePointerEventL );

    TInt value = -1;

    CDesCArray* textArray = NULL;   
    textArray = CCoeEnv::Static()->ReadDesCArrayResourceL( R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );

    CAknSelectionListDialog* selLDlg = 
        CAknSelectionListDialog::NewL( value, textArray, R_AVKON_DIALOG_EMPTY_MENUBAR, NULL );
    selLDlg->SetContainerWindowL( *iContainer );
    selLDlg->PrepareLC( R_TESTLIST_SELECTION_LIST_DIALOG );

    TInt err = KErrNone;
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( 10, 30 );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;

    selLDlg->HandlePointerEventL( event );

    CleanupStack::PopAndDestroy( 2 );
    
    return err;
    }

// test protected of CAknSelectionListDialog
// -----------------------------------------------------------------------------
// CTestSDKLists::TestSLDConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSLDConstructorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AknSelectionListTestModule" );
    _LIT( KTestSLDConstructor, "In TestSLDConstructorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestSLDConstructor );
    // Print to log file
    iLog->Log( KTestSLDConstructor );

    TInt value = -1;

    iTextArray = CCoeEnv::Static()->ReadDesCArrayResourceL( R_TESTLIST_ITEM_ARRAY );

    iSelDlg = new( ELeave ) CTestSDKListsSelectionListDialog( value, iTextArray, NULL );
    iSelDlg->SetContainerWindowL( *iContainer );
    iSelDlg->PrepareLC( R_TESTLIST_SELECTION_LIST_DIALOG );

    CleanupStack::Pop( iSelDlg );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSLDDestructor
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSLDDestructor( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AknSelectionListTestModule" );
    _LIT( KTestSLDDestructor, "In TestSLDDestructor" );
    TestModuleIf().Printf( 0, KTestModule, KTestSLDDestructor );
    // Print to log file
    iLog->Log( KTestSLDDestructor );

    delete iSelDlg;
    iSelDlg = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSLDSelectionListProcessCommandL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSLDSelectionListProcessCommandL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AknSelectionListTestModule" );
    _LIT( KTestSLDSelectionListProcessCommandL, "In TestSLDSelectionListProcessCommandL" );
    TestModuleIf().Printf( 0, KTestModule, KTestSLDSelectionListProcessCommandL );
    // Print to log file
    iLog->Log( KTestSLDSelectionListProcessCommandL );

    TInt err = KErrNone;
    TRAP( err , iSelDlg->SelectionListProcessCommandL( EAknMarkAll ) );

    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSLDIsAcceptableListBoxType
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSLDIsAcceptableListBoxType( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AknSelectionListTestModule" );
    _LIT( KTestSLDIsAcceptableListBoxType, "In TestSLDIsAcceptableListBoxType" );
    TestModuleIf().Printf( 0, KTestModule, KTestSLDIsAcceptableListBoxType );
    // Print to log file
    iLog->Log( KTestSLDIsAcceptableListBoxType );

    TBool flag = ETrue;
    iSelDlg->IsAcceptableListBoxType( 0 , flag );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSLDProcessCommandL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSLDProcessCommandL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AknSelectionListTestModule" );
    _LIT( KTestSLDProcessCommandL, "In TestSLDProcessCommandL" );
    TestModuleIf().Printf( 0, KTestModule, KTestSLDProcessCommandL );
    // Print to log file
    iLog->Log( KTestSLDProcessCommandL );

    TInt err = KErrNone;
    TRAP( err , iSelDlg->ProcessCommandL( EAknUnmarkAll ) );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSLDPreLayoutDynInitL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSLDPreLayoutDynInitL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AknSelectionListTestModule" );
    _LIT( KTestSLDPreLayoutDynInitL, "In TestSLDPreLayoutDynInitL" );
    TestModuleIf().Printf( 0, KTestModule, KTestSLDPreLayoutDynInitL );
    // Print to log file
    iLog->Log( KTestSLDPreLayoutDynInitL );

    TInt err = KErrNone;
    TRAP( err , iSelDlg->PreLayoutDynInitL() );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSLDPostLayoutDynInitL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSLDPostLayoutDynInitL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AknSelectionListTestModule" );
    _LIT( KTestSLDPostLayoutDynInitL, "In TestSLDPostLayoutDynInitL" );
    TestModuleIf().Printf( 0, KTestModule, KTestSLDPostLayoutDynInitL );
    // Print to log file
    iLog->Log( KTestSLDPostLayoutDynInitL );

    TInt err = KErrNone;
    TRAP( err , iSelDlg->PostLayoutDynInitL() );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSLDSetSizeAndPosition
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSLDSetSizeAndPosition( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AknSelectionListTestModule" );
    _LIT( KTestSLDSetSizeAndPosition, "In TestSLDSetSizeAndPosition" );
    TestModuleIf().Printf( 0, KTestModule, KTestSLDSetSizeAndPosition );
    // Print to log file
    iLog->Log( KTestSLDSetSizeAndPosition );

    iSelDlg->SetSizeAndPosition( iContainer->Rect().Size() );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSLDOkToExitL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSLDOkToExitL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AknSelectionListTestModule" );
    _LIT( KTestSLDOkToExitL, "In TestSLDOkToExitL" );
    TestModuleIf().Printf( 0, KTestModule, KTestSLDOkToExitL );
    // Print to log file
    iLog->Log( KTestSLDOkToExitL );

    TInt err = KErrNone;
    TRAP( err, iSelDlg->OkToExitL( 0 ) );

    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSLDHandleListBoxEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSLDHandleListBoxEventL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AknSelectionListTestModule" );
    _LIT( KTestSLDHandleListBoxEventL, "In TestSLDHandleListBoxEventL" );
    TestModuleIf().Printf( 0, KTestModule, KTestSLDHandleListBoxEventL );
    // Print to log file
    iLog->Log( KTestSLDHandleListBoxEventL );

    TInt err = KErrNone;
    TRAP( err , 
            iSelDlg->HandleListBoxEventL( iSelDlg->ListBox(), MEikListBoxObserver::EEventEnterKeyPressed ) );

    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSLDCountComponentControls
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSLDCountComponentControls( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AknSelectionListTestModule" );
    _LIT( KTestSLDCountComponentControls, "In TestSLDCountComponentControls" );
    TestModuleIf().Printf( 0, KTestModule, KTestSLDCountComponentControls );
    // Print to log file
    iLog->Log( KTestSLDCountComponentControls );

    TInt count = iSelDlg->CountComponentControls();
    STIF_ASSERT_NOT_EQUALS( KUnexpected, count );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSLDComponentControl
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSLDComponentControl( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AknSelectionListTestModule" );
    _LIT( KTestSLDComponentControl, "In TestSLDComponentControl" );
    TestModuleIf().Printf( 0, KTestModule, KTestSLDComponentControl );
    // Print to log file
    iLog->Log( KTestSLDComponentControl );

    for ( int i = 0; i < iSelDlg->CountComponentControls(); i++ )
        {
        CCoeControl* control = iSelDlg->ComponentControl( i );
        }

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSLDOfferKeyEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSLDOfferKeyEventL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AknSelectionListTestModule" );
    _LIT( KTestSLDOfferKeyEventL, "In TestSLDOfferKeyEventL" );
    TestModuleIf().Printf( 0, KTestModule, KTestSLDOfferKeyEventL );
    // Print to log file
    iLog->Log( KTestSLDOfferKeyEventL );

    TInt err = KErrNone;
    TKeyEvent keyEvent = { EKeyPause, EStdKeySpace, 0, 0  };
    TRAP( err, iSelDlg->OfferKeyEventL( keyEvent, EEventKey ) );

    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSLDCreateCustomControlL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSLDCreateCustomControlL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AknSelectionListTestModule" );
    _LIT( KTestSLDCreateCustomControlL, "In TestSLDCreateCustomControlL" );
    TestModuleIf().Printf( 0, KTestModule, KTestSLDCreateCustomControlL );
    // Print to log file
    iLog->Log( KTestSLDCreateCustomControlL );

    SEikControlInfo info = iSelDlg->CreateCustomControlL( EAknCtSingleNumberListBox );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSLDListBox
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSLDListBox( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AknSelectionListTestModule" );
    _LIT( KTestSLDListBox, "In TestSLDListBox" );
    TestModuleIf().Printf( 0, KTestModule, KTestSLDListBox );
    // Print to log file
    iLog->Log( KTestSLDListBox );

    CEikListBox* listBox = iSelDlg->ListBox();

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSLDFindBox
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSLDFindBox( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AknSelectionListTestModule" );
    _LIT( KTestSLDFindBox, "In TestSLDFindBox" );
    TestModuleIf().Printf( 0, KTestModule, KTestSLDFindBox );
    // Print to log file
    iLog->Log( KTestSLDFindBox );

    CAknSearchField* searchField = iSelDlg->FindBox();

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSLDIsFormattedCellListBox
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSLDIsFormattedCellListBox( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AknSelectionListTestModule" );
    _LIT( KTestSLDIsFormattedCellListBox, "In TestSLDIsFormattedCellListBox" );
    TestModuleIf().Printf( 0, KTestModule, KTestSLDIsFormattedCellListBox );
    // Print to log file
    iLog->Log( KTestSLDIsFormattedCellListBox );

    TBool flag = iSelDlg->IsFormattedCellListBox();
    STIF_ASSERT_FALSE( flag );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSLDDraw
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSLDDraw( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AknSelectionListTestModule" );
    _LIT( KTestSLDDraw, "In TestSLDDraw" );
    TestModuleIf().Printf( 0, KTestModule, KTestSLDDraw );
    // Print to log file
    iLog->Log( KTestSLDDraw );

    TRect rect = iContainer->Rect();
    iSelDlg->Draw( rect );

    return KErrNone;
    }

// ============================ MEMBER FUNCTIONS ===============================

//========================== CAknMarkableListDialog ============================
// -----------------------------------------------------------------------------
// CTestSDKLists::TestMLDNewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestMLDNewL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AknSelectionListTestModule" );
    _LIT( KTestMLDNewL, "In TestMLDNewL" );
    TestModuleIf().Printf( 0, KTestModule, KTestMLDNewL );
    // Print to log file
    iLog->Log( KTestMLDNewL );

    TInt value( -1 );

    iMarkedItems = new( ELeave ) CArrayFixFlat<TInt>( 2 );

    iTextArray = CCoeEnv::Static()->ReadDesCArrayResourceL( R_TESTLIST_ITEM_ARRAY );

    iMLDlg = CAknMarkableListDialog::NewL( value, iMarkedItems, iTextArray, 
            R_AVKON_DIALOG_EMPTY_MENUBAR, R_AVKON_DIALOG_EMPTY_MENUBAR, NULL );
    STIF_ASSERT_NOT_NULL( iMLDlg );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestMLDNewLCL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestMLDNewLCL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AknSelectionListTestModule" );
    _LIT( KTestMLDNewLCL, "In TestMLDNewLCL" );
    TestModuleIf().Printf( 0, KTestModule, KTestMLDNewLCL );
    // Print to log file
    iLog->Log( KTestMLDNewLCL );

    TInt value( -1 );

    CArrayFix<TInt>* markedItems = new( ELeave ) CArrayFixFlat<TInt>( 2 );
    CleanupStack::PushL( markedItems );

    CDesCArray* textArray = NULL;
    textArray = CCoeEnv::Static()->ReadDesCArrayResourceL( R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );

    CAknMarkableListDialog* markLDlg = CAknMarkableListDialog::NewLC( value, markedItems, textArray, 
            R_AVKON_DIALOG_EMPTY_MENUBAR, R_AVKON_DIALOG_EMPTY_MENUBAR, NULL );
    STIF_ASSERT_NOT_NULL( markLDlg );

    CleanupStack::PopAndDestroy( 3 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestMLDDeprecatedNewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestMLDDeprecatedNewL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AknSelectionListTestModule" );
    _LIT( KTestMLDDeprecatedNewL, "In TestMLDDeprecatedNewL" );
    TestModuleIf().Printf( 0, KTestModule, KTestMLDDeprecatedNewL );
    // Print to log file
    iLog->Log( KTestMLDDeprecatedNewL );

    TInt value( -1 );

    iMarkedItems = new( ELeave ) CArrayFixFlat<TInt>( 2 );

    iTextArray = CCoeEnv::Static()->ReadDesCArrayResourceL( R_TESTLIST_ITEM_ARRAY );

    iMLDlg = CAknMarkableListDialog::NewL( value, iMarkedItems, iTextArray, 
            R_AVKON_DIALOG_EMPTY_MENUBAR );
    STIF_ASSERT_NOT_NULL( iMLDlg );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestMLDDeprecatedNewLCL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestMLDDeprecatedNewLCL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AknSelectionListTestModule" );
    _LIT( KTestMLDDeprecatedNewLCL, "In TestMLDDeprecatedNewLCL" );
    TestModuleIf().Printf( 0, KTestModule, KTestMLDDeprecatedNewLCL );
    // Print to log file
    iLog->Log( KTestMLDDeprecatedNewLCL );

    TInt value( -1 );

    CArrayFix<TInt>* markedItems = new( ELeave ) CArrayFixFlat<TInt>( 2 );
    CleanupStack::PushL( markedItems );

    CDesCArray* textArray = NULL;
    textArray = CCoeEnv::Static()->ReadDesCArrayResourceL( R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );

    CAknMarkableListDialog* markLDlg = CAknMarkableListDialog::NewLC( value, markedItems, textArray, 
            R_AVKON_DIALOG_EMPTY_MENUBAR );
    STIF_ASSERT_NOT_NULL( markLDlg );

    CleanupStack::PopAndDestroy( 3 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestMLDConstructL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestMLDConstructL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AknSelectionListTestModule" );
    _LIT( KTestMLDConstructL, "In TestMLDConstructL" );
    TestModuleIf().Printf( 0, KTestModule, KTestMLDConstructL );
    // Print to log file
    iLog->Log( KTestMLDConstructL );

    TInt err = KErrNone;
    TRAP( err, iMLDlg->ConstructL( R_AVKON_DIALOG_EMPTY_MENUBAR ) );

    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestMLDDestructor
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestMLDDestructor( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AknSelectionListTestModule" );
    _LIT( KTestMLDDestructor, "In TestMLDDestructor" );
    TestModuleIf().Printf( 0, KTestModule, KTestMLDDestructor );
    // Print to log file
    iLog->Log( KTestMLDDestructor );

    delete iMLDlg;
    iMLDlg = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestMLDHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestMLDHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AknSelectionListTestModule" );
    _LIT( KTestMLDHandlePointerEventL, "In TestMLDHandlePointerEventL" );
    TestModuleIf().Printf( 0, KTestModule, KTestMLDHandlePointerEventL );
    // Print to log file
    iLog->Log( KTestMLDHandlePointerEventL );

    iMLDlg->PrepareLC( R_TESTLIST_MARKABLE_DIALOG );

    TInt err = KErrNone;
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( 10, 30 );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    TRAP( err, iMLDlg->HandlePointerEventL( event ) );

    CleanupStack::Pop();

    return err;
    }

// test protected of CAknMarkableListDialog
// -----------------------------------------------------------------------------
// CTestSDKLists::TestMLDConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestMLDConstructorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AknSelectionListTestModule" );
    _LIT( KTestMLDConstructorL, "In TestMLDConstructorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestMLDConstructorL );
    // Print to log file
    iLog->Log( KTestMLDConstructorL );

    TInt value( -1 );

    CArrayFix<TInt>* markedItems = new( ELeave ) CArrayFixFlat<TInt>( 2 );
    CleanupStack::PushL( markedItems );

    CDesCArray* textArray = NULL;
    textArray = CCoeEnv::Static()->ReadDesCArrayResourceL( R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );

    CTestSDKListsMarkableListDialog* markListDlg =
        new( ELeave ) CTestSDKListsMarkableListDialog( value, markedItems, textArray, 
                R_AVKON_DIALOG_EMPTY_MENUBAR, R_AVKON_DIALOG_EMPTY_MENUBAR, NULL );
    CleanupStack::PushL( markListDlg );
    STIF_ASSERT_NOT_NULL( markListDlg );

    CleanupStack::PopAndDestroy( 3 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestMLDDeprecatedConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestMLDDeprecatedConstructorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AknSelectionListTestModule" );
    _LIT( KTestMLDDeprecatedConstructorL, "In TestMLDDeprecatedConstructorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestMLDDeprecatedConstructorL );
    // Print to log file
    iLog->Log( KTestMLDDeprecatedConstructorL );

    TInt value( -1 );

    CArrayFix<TInt>* markedItems = new( ELeave ) CArrayFixFlat<TInt>( 2 );
    CleanupStack::PushL( markedItems );

    CDesCArray* textArray = NULL;
    textArray = CCoeEnv::Static()->ReadDesCArrayResourceL( R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );

    CTestSDKListsMarkableListDialog* markListDlg =
        new( ELeave ) CTestSDKListsMarkableListDialog( value, markedItems, textArray, NULL );
    CleanupStack::PushL( markListDlg );
    STIF_ASSERT_NOT_NULL( markListDlg );

    CleanupStack::PopAndDestroy( 3 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestMLDPreLayoutDynInitL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestMLDPreLayoutDynInitL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AknSelectionListTestModule" );
    _LIT( KTestMLDPreLayoutDynInitL, "In TestMLDPreLayoutDynInitL" );
    TestModuleIf().Printf( 0, KTestModule, KTestMLDPreLayoutDynInitL );
    // Print to log file
    iLog->Log( KTestMLDPreLayoutDynInitL );

    TInt value( -1 );

    CArrayFix<TInt>* markedItems = new( ELeave ) CArrayFixFlat<TInt>( 2 );
    CleanupStack::PushL( markedItems );

    CDesCArray* textArray = NULL;
    textArray = CCoeEnv::Static()->ReadDesCArrayResourceL( R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );

    CTestSDKListsMarkableListDialog* markListDlg =
        new( ELeave ) CTestSDKListsMarkableListDialog( value, markedItems, textArray, 
                R_AVKON_DIALOG_EMPTY_MENUBAR, R_AVKON_DIALOG_EMPTY_MENUBAR, NULL );
    CleanupStack::PushL( markListDlg );
    markListDlg->SetContainerWindowL( *iContainer );
    markListDlg->PrepareLC( R_TESTLIST_MARKABLE_DIALOG );

    TInt err = KErrNone;
    TRAP( err, markListDlg->PreLayoutDynInitL() );
    CleanupStack::Pop();
    CleanupStack::PopAndDestroy( 3 );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestMLDPostLayoutDynInitL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestMLDPostLayoutDynInitL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AknSelectionListTestModule" );
    _LIT( KTestMLDPostLayoutDynInitL, "In TestMLDPostLayoutDynInitL" );
    TestModuleIf().Printf( 0, KTestModule, KTestMLDPostLayoutDynInitL );
    // Print to log file
    iLog->Log( KTestMLDPostLayoutDynInitL );

    TInt value( -1 );

    CArrayFix<TInt>* markedItems = new( ELeave ) CArrayFixFlat<TInt>( 2 );
    CleanupStack::PushL( markedItems );

    CDesCArray* textArray = NULL;
    textArray = CCoeEnv::Static()->ReadDesCArrayResourceL( R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );

    CTestSDKListsMarkableListDialog* markListDlg =
        new( ELeave ) CTestSDKListsMarkableListDialog( value, markedItems, textArray, 
                R_AVKON_DIALOG_EMPTY_MENUBAR, R_AVKON_DIALOG_EMPTY_MENUBAR, NULL );
    CleanupStack::PushL( markListDlg );
    markListDlg->SetContainerWindowL( *iContainer );
    markListDlg->PrepareLC( R_TESTLIST_MARKABLE_DIALOG );

    TInt err = KErrNone;
    TRAP ( err, markListDlg->PostLayoutDynInitL() );
    CleanupStack::Pop();
    CleanupStack::PopAndDestroy( 3 );

    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestMLDSelectionListProcessCommandL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestMLDSelectionListProcessCommandL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AknSelectionListTestModule" );
    _LIT( KTestMLDSelectionListProcessCommandL, "In TestMLDSelectionListProcessCommandL" );
    TestModuleIf().Printf( 0, KTestModule, KTestMLDSelectionListProcessCommandL );
    // Print to log file
    iLog->Log( KTestMLDSelectionListProcessCommandL );

    TInt value( -1 );

    CArrayFix<TInt>* markedItems = new( ELeave ) CArrayFixFlat<TInt>( 2 );
    CleanupStack::PushL( markedItems );

    CDesCArray* textArray = NULL;
    textArray = CCoeEnv::Static()->ReadDesCArrayResourceL( R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );

    CTestSDKListsMarkableListDialog* markListDlg =
        new( ELeave ) CTestSDKListsMarkableListDialog( value, markedItems, textArray, 
                R_AVKON_DIALOG_EMPTY_MENUBAR, R_AVKON_DIALOG_EMPTY_MENUBAR, NULL );
    CleanupStack::PushL( markListDlg );
    markListDlg->SetContainerWindowL( *iContainer );
    markListDlg->PrepareLC( R_TESTLIST_MARKABLE_DIALOG );

    TInt err = KErrNone;
    TRAP ( err, markListDlg->SelectionListProcessCommandL( EAknMarkAll ) );
    CleanupStack::Pop();
    CleanupStack::PopAndDestroy( 3 );

    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestMLDProcessCommandL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestMLDProcessCommandL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AknSelectionListTestModule" );
    _LIT( KTestMLDProcessCommandL, "In TestMLDProcessCommandL" );
    TestModuleIf().Printf( 0, KTestModule, KTestMLDProcessCommandL );
    // Print to log file
    iLog->Log( KTestMLDProcessCommandL );

    TInt value( -1 );

    CArrayFix<TInt>* markedItems = new( ELeave ) CArrayFixFlat<TInt>( 2 );
    CleanupStack::PushL( markedItems );

    CDesCArray* textArray = NULL;
    textArray = CCoeEnv::Static()->ReadDesCArrayResourceL( R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );

    CTestSDKListsMarkableListDialog* markListDlg =
        new( ELeave ) CTestSDKListsMarkableListDialog( value, markedItems, textArray, 
                R_AVKON_DIALOG_EMPTY_MENUBAR, R_AVKON_DIALOG_EMPTY_MENUBAR, NULL );
    CleanupStack::PushL( markListDlg );
    markListDlg->SetContainerWindowL( *iContainer );
    markListDlg->PrepareLC( R_TESTLIST_MARKABLE_DIALOG );

    TInt err = KErrNone;
    TRAP( err, markListDlg->ProcessCommandL( EAknUnmarkAll ) );
    CleanupStack::Pop();
    CleanupStack::PopAndDestroy( 3 );

    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestMLDDynInitMenuPaneL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestMLDDynInitMenuPaneL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AknSelectionListTestModule" );
    _LIT( KTestMLDDynInitMenuPaneL, "In TestMLDDynInitMenuPaneL" );
    TestModuleIf().Printf( 0, KTestModule, KTestMLDDynInitMenuPaneL );
    // Print to log file
    iLog->Log( KTestMLDDynInitMenuPaneL );

    TInt value( -1 );

    CArrayFix<TInt>* markedItems = new( ELeave ) CArrayFixFlat<TInt>( 2 );
    CleanupStack::PushL( markedItems );

    CDesCArray* textArray = NULL;
    textArray = CCoeEnv::Static()->ReadDesCArrayResourceL( R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );

    CTestSDKListsMarkableListDialog* markListDlg =
        new( ELeave ) CTestSDKListsMarkableListDialog( value, markedItems, textArray, 
                R_AVKON_DIALOG_EMPTY_MENUBAR, R_AVKON_DIALOG_EMPTY_MENUBAR, NULL );
    CleanupStack::PushL( markListDlg );
    markListDlg->SetContainerWindowL( *iContainer );
    markListDlg->PrepareLC( R_TESTLIST_MARKABLE_DIALOG );

    TInt err = KErrNone;
    CEikMenuPane* menuPane = new( ELeave ) CEikMenuPane( markListDlg );
    CleanupStack::PushL( menuPane );    
    TRAP( err, markListDlg->DynInitMenuPaneL( R_TESTLIST_COLUMN_MENU, menuPane ) );

    CleanupStack::PopAndDestroy( menuPane );
    CleanupStack::Pop();
    CleanupStack::PopAndDestroy( 3 );

    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestMLDHandleListBoxEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestMLDHandleListBoxEventL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AknSelectionListTestModule" );
    _LIT( KTestMLDHandleListBoxEventL, "In TestMLDHandleListBoxEventL" );
    TestModuleIf().Printf( 0, KTestModule, KTestMLDHandleListBoxEventL );
    // Print to log file
    iLog->Log( KTestMLDHandleListBoxEventL );

    TInt value( -1 );

    CArrayFix<TInt>* markedItems = new( ELeave ) CArrayFixFlat<TInt>( 2 );
    CleanupStack::PushL( markedItems );

    CDesCArray* textArray = NULL;
    textArray = CCoeEnv::Static()->ReadDesCArrayResourceL( R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );

    CTestSDKListsMarkableListDialog* markListDlg =
        new( ELeave ) CTestSDKListsMarkableListDialog( value, markedItems, textArray, 
                R_AVKON_DIALOG_EMPTY_MENUBAR, R_AVKON_DIALOG_EMPTY_MENUBAR, NULL );
    CleanupStack::PushL( markListDlg );
    markListDlg->SetContainerWindowL( *iContainer );
    markListDlg->PrepareLC( R_TESTLIST_MARKABLE_DIALOG );

    TInt err = KErrNone;
    TRAP( err, markListDlg->HandleListBoxEventL( markListDlg->ListBox(), 
        MEikListBoxObserver::EEventItemClicked ) );  

    CleanupStack::Pop();
    CleanupStack::PopAndDestroy( 3 );

    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestMLDOfferKeyEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestMLDOfferKeyEventL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AknSelectionListTestModule" );
    _LIT( KTestMLDOfferKeyEventL, "In TestMLDOfferKeyEventL" );
    TestModuleIf().Printf( 0, KTestModule, KTestMLDOfferKeyEventL );
    // Print to log file
    iLog->Log( KTestMLDOfferKeyEventL );

    TInt value( -1 );

    CArrayFix<TInt>* markedItems = new( ELeave ) CArrayFixFlat<TInt>( 2 );
    CleanupStack::PushL( markedItems );

    CDesCArray* textArray = NULL;
    textArray = CCoeEnv::Static()->ReadDesCArrayResourceL( R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );

    CTestSDKListsMarkableListDialog* markListDlg =
        new( ELeave ) CTestSDKListsMarkableListDialog( value, markedItems, textArray, 
                R_AVKON_DIALOG_EMPTY_MENUBAR, R_AVKON_DIALOG_EMPTY_MENUBAR, NULL );
    CleanupStack::PushL( markListDlg );
    markListDlg->SetContainerWindowL( *iContainer );
    markListDlg->PrepareLC( R_TESTLIST_MARKABLE_DIALOG );

    TInt err = KErrNone;
    TKeyEvent keyEvent;
    keyEvent.iCode = EKeyLeftArrow;    
    TRAP( err, markListDlg->OfferKeyEventL( keyEvent, EEventKey ) );
    keyEvent.iCode = 'M';
    TRAP( err, markListDlg->OfferKeyEventL( keyEvent, EEventKey ) );

    CleanupStack::Pop();
    CleanupStack::PopAndDestroy( 3 );

    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestMLDOkToExitL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestMLDOkToExitL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AknSelectionListTestModule" );
    _LIT( KTestMLDOkToExitL, "In KTestMLDOkToExitL" );
    TestModuleIf().Printf( 0, KTestModule, KTestMLDOkToExitL );
    // Print to log file
    iLog->Log( KTestMLDOkToExitL );

    TInt value( -1 );

    CArrayFix<TInt>* markedItems = new( ELeave ) CArrayFixFlat<TInt>( 2 );
    CleanupStack::PushL( markedItems );

    CDesCArray* textArray = NULL;
    textArray = CCoeEnv::Static()->ReadDesCArrayResourceL( R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );

    CTestSDKListsMarkableListDialog* markListDlg =
        new( ELeave ) CTestSDKListsMarkableListDialog( value, markedItems, textArray, 
                R_AVKON_DIALOG_EMPTY_MENUBAR, R_AVKON_DIALOG_EMPTY_MENUBAR, NULL );
    CleanupStack::PushL( markListDlg );
    markListDlg->SetContainerWindowL( *iContainer );
    markListDlg->PrepareLC( R_TESTLIST_MARKABLE_DIALOG );

    TInt err = KErrNone; 
    TRAP( err, markListDlg->OkToExitL( EAknSoftkeyOk ) );

    CleanupStack::Pop();
    CleanupStack::PopAndDestroy( 3 );

    return err;
    }
