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
* Description:  for test eiktxlbm.h
*
*/

// [INCLUDE FILES]
#include <e32base.h>
#include <aknlists.h>
#include <testsdklists.rsg>
#include <coemain.h>
#include <coeaui.h>
#include <eiktxlbm.h>
#include <barsread.h>
#include <bamdesca.h>

#include "testsdklists.h"
#include "testsdkcontainer.h"
#include "testsdkliststextlistboxmodel.h"

const TInt KFive = 5;
const TInt KNine = 9;
// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKLists::TestTXLBMConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestTXLBMConstructorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKTXLBMTestModule" );
    _LIT( KTestEIKTXLBM, "In TestTXLBMConstructorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKTXLBM );
    // Print to log file
    iLog->Log( KTestEIKTXLBM );

    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();
    CleanupStack::PushL( model );
    STIF_ASSERT_NOT_NULL( model );
    CleanupStack::PopAndDestroy( model );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestTXLBMDestructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestTXLBMDestructorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKTXLBMTestModule" );
    _LIT( KTestEIKTXLBM, "In TestTXLBMDestructorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKTXLBM );
    // Print to log file
    iLog->Log( KTestEIKTXLBM );

    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();
    CleanupStack::PushL( model );
    STIF_ASSERT_NOT_NULL( model );
    CleanupStack::Pop( model );
    delete model;
    model = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestTXLBMNumberOfItemsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestTXLBMNumberOfItemsL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKTXLBMTestModule" );
    _LIT( KTestEIKTXLBM, "In TestTXLBMNumberOfItemsL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKTXLBM );
    // Print to log file
    iLog->Log( KTestEIKTXLBM );

    TInt flags = CEikListBox::EIncrementalMatching | 
                EAknListBoxSelectionList | EAknListBoxViewerFlags;
    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );

    CEikTextListBox* list = new( ELeave ) CEikTextListBox();
    CleanupStack::PushL( list );
    list->ConstructL( iContainer, flags );
    list->Model()->SetItemTextArray( textArray );
    list->Model()->SetOwnershipType( ELbmOwnsItemArray );
    iContainer->SetControlL( list );

    CTextListBoxModel* model = list->Model();

    TInt num = model->NumberOfItems();
    STIF_ASSERT_EQUALS( KNine, num );

    iContainer->ResetControl();
    CleanupStack::Pop( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestTXLBMMatchableTextArrayL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestTXLBMMatchableTextArrayL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKTXLBMTestModule" );
    _LIT( KTestEIKTXLBM, "In TestTXLBMMatchableTextArrayL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKTXLBM );
    // Print to log file
    iLog->Log( KTestEIKTXLBM );

    TInt flags = CEikListBox::EIncrementalMatching | 
                EAknListBoxSelectionList | EAknListBoxViewerFlags;
    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );

    CEikTextListBox* list = new( ELeave ) CEikTextListBox();
    CleanupStack::PushL( list );
    list->ConstructL( iContainer, flags );
    list->Model()->SetItemTextArray( textArray );
    list->Model()->SetOwnershipType( ELbmOwnsItemArray );
    iContainer->SetControlL( list );

    CTextListBoxModel* model = list->Model();

    STIF_ASSERT_NOT_NULL( model->MatchableTextArray() );

    iContainer->ResetControl();
    CleanupStack::Pop( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestTXLBMItemTextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestTXLBMItemTextL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKTXLBMTestModule" );
    _LIT( KTestEIKTXLBM, "In TestTXLBMItemTextL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKTXLBM );
    // Print to log file
    iLog->Log( KTestEIKTXLBM );

    TInt flags = CEikListBox::EIncrementalMatching | 
                EAknListBoxSelectionList | EAknListBoxViewerFlags;
    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );

    CEikTextListBox* list = new( ELeave ) CEikTextListBox();
    CleanupStack::PushL( list );
    list->ConstructL( iContainer, flags );
    list->Model()->SetItemTextArray( textArray );
    list->Model()->SetOwnershipType( ELbmOwnsItemArray );
    iContainer->SetControlL( list );

    CTextListBoxModel* model = list->Model();
    model->ItemText( 0 );

    iContainer->ResetControl();
    CleanupStack::Pop( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestTXLBMConstructL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestTXLBMConstructL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKTXLBMTestModule" );
    _LIT( KTestEIKTXLBM, "In TestTXLBMConstructL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKTXLBM );
    // Print to log file
    iLog->Log( KTestEIKTXLBM );

    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();
    CleanupStack::PushL( model );
    STIF_ASSERT_NOT_NULL( model );
    model->ConstructL();
    CleanupStack::PopAndDestroy( model );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestTXLBMSetItemTextArrayL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestTXLBMSetItemTextArrayL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKTXLBMTestModule" );
    _LIT( KTestEIKTXLBM, "In TestTXLBMSetItemTextArrayL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKTXLBM );
    // Print to log file
    iLog->Log( KTestEIKTXLBM );

    TInt flags = CEikListBox::EIncrementalMatching | 
                EAknListBoxSelectionList | EAknListBoxViewerFlags;
    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );

    CEikTextListBox* list = new( ELeave ) CEikTextListBox();
    CleanupStack::PushL( list );
    list->ConstructL( iContainer, flags );
    list->Model()->SetItemTextArray( textArray );
    list->Model()->SetOwnershipType( ELbmOwnsItemArray );
    iContainer->SetControlL( list );

    MDesCArray* array = new( ELeave ) CDesCArrayFlat( KFive );
    CTextListBoxModel* model = list->Model();
    model->SetItemTextArray( array );

    iContainer->ResetControl();
    CleanupStack::Pop( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestTXLBMSetOwnershipTypeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestTXLBMSetOwnershipTypeL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKTXLBMTestModule" );
    _LIT( KTestEIKTXLBM, "In TestTXLBMSetOwnershipTypeL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKTXLBM );
    // Print to log file
    iLog->Log( KTestEIKTXLBM );

    TInt flags = CEikListBox::EIncrementalMatching | 
                EAknListBoxSelectionList | EAknListBoxViewerFlags;
    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );

    CEikTextListBox* list = new( ELeave ) CEikTextListBox();
    CleanupStack::PushL( list );
    list->ConstructL( iContainer, flags );
    list->Model()->SetItemTextArray( textArray );
    list->Model()->SetOwnershipType( ELbmOwnsItemArray );
    iContainer->SetControlL( list );

    CTextListBoxModel* model = list->Model();
    model->SetOwnershipType( ELbmOwnsItemArray );

    iContainer->ResetControl();
    CleanupStack::Pop( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestTXLBMItemTextArrayL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestTXLBMItemTextArrayL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKTXLBMTestModule" );
    _LIT( KTestEIKTXLBM, "In TestTXLBMItemTextArrayL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKTXLBM );
    // Print to log file
    iLog->Log( KTestEIKTXLBM );

    TInt flags = CEikListBox::EIncrementalMatching | 
                EAknListBoxSelectionList | EAknListBoxViewerFlags;
    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );

    CEikTextListBox* list = new( ELeave ) CEikTextListBox();
    CleanupStack::PushL( list );
    list->ConstructL( iContainer, flags );
    list->Model()->SetItemTextArray( textArray );
    list->Model()->SetOwnershipType( ELbmOwnsItemArray );
    iContainer->SetControlL( list );

    CTextListBoxModel* model = list->Model();
    MDesCArray* array = model->ItemTextArray();
    STIF_ASSERT_NOT_NULL( array );

    iContainer->ResetControl();
    CleanupStack::Pop( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestTXLBMItemArrayOwnershipTypeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestTXLBMItemArrayOwnershipTypeL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKTXLBMTestModule" );
    _LIT( KTestEIKTXLBM, "In TestTXLBMItemArrayOwnershipTypeL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKTXLBM );
    // Print to log file
    iLog->Log( KTestEIKTXLBM );

    TInt flags = CEikListBox::EIncrementalMatching | 
                EAknListBoxSelectionList | EAknListBoxViewerFlags;
    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY );
    CleanupStack::PushL( textArray );

    CEikTextListBox* list = new( ELeave ) CEikTextListBox();
    CleanupStack::PushL( list );
    list->ConstructL( iContainer, flags );
    list->Model()->SetItemTextArray( textArray );
    list->Model()->SetOwnershipType( ELbmOwnsItemArray );
    iContainer->SetControlL( list );

    CTestSDKListsTextListBoxModel* model =
        static_cast< CTestSDKListsTextListBoxModel* > ( list->Model() );
    model->ItemArrayOwnershipType();

    iContainer->ResetControl();
    CleanupStack::Pop( 2 );

    return KErrNone;
    }
