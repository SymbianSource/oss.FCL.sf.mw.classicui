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
* Description:  for test eikslb.h
*
*/

// [INCLUDE FILES]
#include <e32base.h>
#include <aknlists.h>
#include <testsdklists.rsg>
#include <coemain.h>
#include <coeaui.h>
#include <eikslb.h>
#include <barsread.h>
#include <eikslbd.h>

#include "testsdklists.h"
#include "testsdkcontainer.h"
#include "testsdklistssettingslistbox.h"

const TInt KThirty = 30;
const TInt KFifty = 50;
// ============================ MEMBER FUNCTIONS ===============================

// =====================class CSettingsListBoxItemDrawer========================
// -----------------------------------------------------------------------------
// CTestSDKLists::TestSLBIDConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSLBIDConstructorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKSLBTestModule" );
    _LIT( KTestEIKSLB, "In TestLBConstructorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKSLB );
    // Print to log file
    iLog->Log( KTestEIKSLB );

    CEikSettingsListBox* listBox = new( ELeave ) CEikSettingsListBox();
    CleanupStack::PushL( listBox );
    STIF_ASSERT_NOT_NULL( listBox );

    CTextListBoxModel* model = listBox->Model();
    CSettingsListBoxData* data = CSettingsListBoxData::NewL();
    CleanupStack::PushL( data );
    const CFont* font = iEikonEnvPointer->NormalFont();

    CSettingsListBoxItemDrawer* drawer =
        new( ELeave ) CSettingsListBoxItemDrawer( model, font, data );
    CleanupStack::PushL( drawer );
    STIF_ASSERT_NOT_NULL( drawer );
    CleanupStack::PopAndDestroy( drawer );
    CleanupStack::Pop( data );
    CleanupStack::PopAndDestroy( listBox );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSLBIDDetructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSLBIDDetructorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKSLBTestModule" );
    _LIT( KTestEIKSLB, "In TestSLBIDDetructorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKSLB );
    // Print to log file
    iLog->Log( KTestEIKSLB );

    CEikSettingsListBox* listBox = new( ELeave ) CEikSettingsListBox();
    CleanupStack::PushL( listBox );
    STIF_ASSERT_NOT_NULL( listBox );

    CTextListBoxModel* model = listBox->Model();
    CSettingsListBoxData* data = CSettingsListBoxData::NewL();
    CleanupStack::PushL( data );
    const CFont* font = iEikonEnvPointer->NormalFont();

    CSettingsListBoxItemDrawer* drawer =
        new( ELeave ) CSettingsListBoxItemDrawer( model, font, data );
    CleanupStack::PushL( drawer );
    STIF_ASSERT_NOT_NULL( drawer );
    CleanupStack::Pop( 2 );
    CleanupStack::PopAndDestroy( listBox );
    delete drawer;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSLBIDSettingsDataL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSLBIDSettingsDataL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKSLBTestModule" );
    _LIT( KTestEIKSLB, "In TestSLBIDSettingsDataL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKSLB );
    // Print to log file
    iLog->Log( KTestEIKSLB );

    CEikSettingsListBox* listBox = new( ELeave ) CEikSettingsListBox();
    CleanupStack::PushL( listBox );
    STIF_ASSERT_NOT_NULL( listBox );

    CTextListBoxModel* model = listBox->Model();
    CSettingsListBoxData* data = CSettingsListBoxData::NewL();
    CleanupStack::PushL( data );
    const CFont* font = iEikonEnvPointer->NormalFont();

    CSettingsListBoxItemDrawer* drawer =
        new( ELeave ) CSettingsListBoxItemDrawer( model, font, data );
    CleanupStack::PushL( drawer );
    STIF_ASSERT_NOT_NULL( drawer );

    CSettingsListBoxData* getData = drawer->SettingsData();
    STIF_ASSERT_NOT_NULL( getData );
    STIF_ASSERT_TRUE( data == getData );
    CleanupStack::PopAndDestroy( drawer );
    CleanupStack::Pop( data );
    CleanupStack::PopAndDestroy( listBox );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSLBIDDrawItemTextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSLBIDDrawItemTextL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKSLBTestModule" );
    _LIT( KTestEIKSLB, "In TestSLBIDDrawItemTextL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKSLB );
    // Print to log file
    iLog->Log( KTestEIKSLB );

    CEikSettingsListBox* listBox = new( ELeave ) CEikSettingsListBox();
    CleanupStack::PushL( listBox );
    STIF_ASSERT_NOT_NULL( listBox );

    listBox->SetContainerWindowL( *iContainer );        
    
    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_SETTING );
    listBox->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy(); // resource stuffs.        

    CSettingsListBoxItemDrawer* drawer = listBox->ItemDrawer();

    TRect rect( TPoint( 0, 0 ), TSize( KFifty, KThirty ) );
    drawer->DrawItemText(0, rect, ETrue, EFalse, EFalse );

    CleanupStack::PopAndDestroy( listBox );

    return KErrNone;
    }

// =========================class CEikSettingsListBox===========================
// -----------------------------------------------------------------------------
// CTestSDKLists::TestSettingsLBConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSettingsLBConstructorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKSLBTestModule" );
    _LIT( KTestEIKSLB, "In TestSettingsLBConstructorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKSLB );
    // Print to log file
    iLog->Log( KTestEIKSLB );

    CEikSettingsListBox* listBox = new( ELeave ) CEikSettingsListBox();
    CleanupStack::PushL( listBox );
    STIF_ASSERT_NOT_NULL( listBox );

    listBox->SetContainerWindowL( *iContainer );        
    
    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_SETTING );
    listBox->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy(); // resource stuffs.        

    CleanupStack::PopAndDestroy( listBox );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSettingsLBItemDrawerL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSettingsLBItemDrawerL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKSLBTestModule" );
    _LIT( KTestEIKSLB, "In TestSettingsLBItemDrawerL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKSLB );
    // Print to log file
    iLog->Log( KTestEIKSLB );

    CEikSettingsListBox* listBox = new( ELeave ) CEikSettingsListBox();
    CleanupStack::PushL( listBox );
    STIF_ASSERT_NOT_NULL( listBox );

    listBox->SetContainerWindowL( *iContainer );        
    
    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_SETTING );
    listBox->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy(); // resource stuffs.        

    CSettingsListBoxItemDrawer* drawer = listBox->ItemDrawer();
    STIF_ASSERT_NOT_NULL( drawer );

    CleanupStack::PopAndDestroy( listBox );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSettingsLBMakeViewClassInstanceL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSettingsLBMakeViewClassInstanceL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKSLBTestModule" );
    _LIT( KTestEIKSLB, "In TestSettingsLBMakeViewClassInstanceL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKSLB );
    // Print to log file
    iLog->Log( KTestEIKSLB );

    CEikSettingsListBox* listBox = new( ELeave ) CEikSettingsListBox();
    CleanupStack::PushL( listBox );
    STIF_ASSERT_NOT_NULL( listBox );

    listBox->SetContainerWindowL( *iContainer );        
    
    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_SETTING );
    listBox->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy(); // resource stuffs.        

    CListBoxView* view = listBox->MakeViewClassInstanceL();
    CleanupStack::PushL( view );
    STIF_ASSERT_NOT_NULL( view );
    CleanupStack::PopAndDestroy( view );

    CleanupStack::PopAndDestroy( listBox );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSettingsLBHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSettingsLBHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKSLBTestModule" );
    _LIT( KTestEIKSLB, "In TestSettingsLBHandlePointerEventL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKSLB );
    // Print to log file
    iLog->Log( KTestEIKSLB );

    CEikSettingsListBox* listBox = new( ELeave ) CEikSettingsListBox();
    CleanupStack::PushL( listBox );
    STIF_ASSERT_NOT_NULL( listBox );

    listBox->SetContainerWindowL( *iContainer );        
    
    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_SETTING );
    listBox->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy(); // resource stuffs.        

    TInt err = KErrNone;
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( 0, KThirty );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    TRAP( err, listBox->HandlePointerEventL( event ) );

    CleanupStack::PopAndDestroy( listBox );

    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSettingsLBCreateItemDrawerL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSettingsLBCreateItemDrawerL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKSLBTestModule" );
    _LIT( KTestEIKSLB, "In TestSettingsLBCreateItemDrawerL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKSLB );
    // Print to log file
    iLog->Log( KTestEIKSLB );

    CTestSDKListsSettingsListBox* listBox =
        new( ELeave ) CTestSDKListsSettingsListBox();
    CleanupStack::PushL( listBox );
    STIF_ASSERT_NOT_NULL( listBox );

    TInt err = KErrNone;
    TRAP( err, listBox->CreateItemDrawerL() );

    CleanupStack::PopAndDestroy( listBox );

    return err;
    }

// =========================class CSettingsListBoxView==========================
// -----------------------------------------------------------------------------
// CTestSDKLists::TestSettingsLBVDrawL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSettingsLBVDrawL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKSLBTestModule" );
    _LIT( KTestEIKSLB, "In TestSettingsLBVDrawL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKSLB );
    // Print to log file
    iLog->Log( KTestEIKSLB );

    CTestSDKListsSettingsListBox* listBox = new( ELeave ) CTestSDKListsSettingsListBox();
    CleanupStack::PushL( listBox );
    STIF_ASSERT_NOT_NULL( listBox );

    listBox->SetContainerWindowL( *iContainer );        
    
    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_SETTING );
    listBox->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy(); // resource stuffs.        

    CSettingsListBoxView* view = listBox->View();
    TRect rect = iContainer->Rect();
    view->Draw( &rect );

    CleanupStack::PopAndDestroy( listBox );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSettingsLBVDrawItemL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSettingsLBVDrawItemL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKSLBTestModule" );
    _LIT( KTestEIKSLB, "In TestSettingsLBVDrawItemL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKSLB );
    // Print to log file
    iLog->Log( KTestEIKSLB );

    CTestSDKListsSettingsListBox* listBox = new( ELeave ) CTestSDKListsSettingsListBox();
    CleanupStack::PushL( listBox );
    STIF_ASSERT_NOT_NULL( listBox );

    listBox->SetContainerWindowL( *iContainer );        
    
    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_SETTING );
    listBox->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy(); // resource stuffs.        

    CSettingsListBoxView* view = listBox->View();
    view->DrawItem( 0 );

    CleanupStack::PopAndDestroy( listBox );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSettingsLBVItemDrawerL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSettingsLBVItemDrawerL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKSLBTestModule" );
    _LIT( KTestEIKSLB, "In TestSettingsLBVItemDrawerL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKSLB );
    // Print to log file
    iLog->Log( KTestEIKSLB );

    CTestSDKListsSettingsListBox* listBox = new( ELeave ) CTestSDKListsSettingsListBox();
    CleanupStack::PushL( listBox );
    STIF_ASSERT_NOT_NULL( listBox );

    listBox->SetContainerWindowL( *iContainer );        
    
    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_SETTING );
    listBox->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy(); // resource stuffs.        

    CSettingsListBoxItemDrawer* drawer = listBox->ItemDrawer();
    STIF_ASSERT_NOT_NULL( drawer );

    CleanupStack::PopAndDestroy( listBox );

    return KErrNone;
    }
