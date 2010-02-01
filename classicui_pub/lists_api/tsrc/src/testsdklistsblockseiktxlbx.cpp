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
* Description:  for test eiktxlbx.h
*
*/

// [INCLUDE FILES]
#include <e32base.h>
#include <aknlists.h>
#include <testsdklists.rsg>
#include <coemain.h>
#include <coeaui.h>
#include <eiktxlbx.h>
#include <barsread.h>
#include <s32file.h>

#include "testsdklists.h"
#include "testsdkcontainer.h"
#include "testsdkliststextlistbox.h"

const TInt KFour = 4;
const TInt KNine = 9;
// ============================ MEMBER FUNCTIONS ===============================

// ========================= class CEikTextListBox==============================
// -----------------------------------------------------------------------------
// CTestSDKLists::TestTXLBConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestTXLBConstructorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKTXLBXTestModule" );
    _LIT( KTestEIKTXLBX, "In TestTXLBConstructorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKTXLBX );
    // Print to log file
    iLog->Log( KTestEIKTXLBX );

    CEikTextListBox* list = new( ELeave ) CEikTextListBox();
    CleanupStack::PushL( list );
    STIF_ASSERT_NOT_NULL( list );
    CleanupStack::PopAndDestroy( list );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestTXLBDestructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestTXLBDestructorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKTXLBXTestModule" );
    _LIT( KTestEIKTXLBX, "In TestTXLBDestructorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKTXLBX );
    // Print to log file
    iLog->Log( KTestEIKTXLBX );

    CEikTextListBox* list = new( ELeave ) CEikTextListBox();
    CleanupStack::PushL( list );
    STIF_ASSERT_NOT_NULL( list );
    CleanupStack::Pop( list );
    delete list;
    list = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestTXLBConstructFromResourceL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestTXLBConstructFromResourceL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKTXLBXTestModule" );
    _LIT( KTestEIKTXLBX, "In TestTXLBConstructFromResourceL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKTXLBX );
    // Print to log file
    iLog->Log( KTestEIKTXLBX );

    CEikTextListBox* textList = new( ELeave ) CEikTextListBox();
    CleanupStack::PushL( textList );
    textList->SetContainerWindowL( *iContainer );
    TResourceReader textReader;
    iEikonEnvPointer->CreateResourceReaderLC( textReader, 
            R_TESTLIST_SINGLE_1 );
    textList->ConstructFromResourceL( textReader );
    CleanupStack::PopAndDestroy();
    CleanupStack::PopAndDestroy( textList );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestTXLBConstructL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestTXLBConstructL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKTXLBXTestModule" );
    _LIT( KTestEIKTXLBX, "In TestTXLBConstructL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKTXLBX );
    // Print to log file
    iLog->Log( KTestEIKTXLBX );

    TInt flags = CEikListBox::EIncrementalMatching | 
                EAknListBoxSelectionList | EAknListBoxViewerFlags;

    CEikTextListBox* list = new( ELeave ) CEikTextListBox();
    CleanupStack::PushL( list );
    list->ConstructL( iContainer, flags );
    CleanupStack::PopAndDestroy( list );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestTXLBModelL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestTXLBModelL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKTXLBXTestModule" );
    _LIT( KTestEIKTXLBX, "In TestTXLBModelL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKTXLBX );
    // Print to log file
    iLog->Log( KTestEIKTXLBX );

    TInt flags = CEikListBox::EIncrementalMatching | 
                EAknListBoxSelectionList | EAknListBoxViewerFlags;
    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_SETTING );
    CleanupStack::PushL( textArray );

    CEikTextListBox* list = new( ELeave ) CEikTextListBox();
    CleanupStack::PushL( list );
    list->ConstructL( iContainer, flags );
    list->Model()->SetItemTextArray( textArray );
    list->Model()->SetOwnershipType( ELbmOwnsItemArray );
    iContainer->SetControlL( list );

    CTextListBoxModel* model = list->Model();
    STIF_ASSERT_NOT_NULL( model );
    iContainer->ResetControl();
    CleanupStack::Pop( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestTXLBGetColorUseListL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestTXLBGetColorUseListL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKTXLBXTestModule" );
    _LIT( KTestEIKTXLBX, "In TestTXLBGetColorUseListL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKTXLBX );
    // Print to log file
    iLog->Log( KTestEIKTXLBX );

    TInt flags = CEikListBox::EIncrementalMatching | 
                EAknListBoxSelectionList | EAknListBoxViewerFlags;
    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_SETTING );
    CleanupStack::PushL( textArray );

    CEikTextListBox* list = new( ELeave ) CEikTextListBox();
    CleanupStack::PushL( list );
    list->ConstructL( iContainer, flags );
    list->Model()->SetItemTextArray( textArray );
    list->Model()->SetOwnershipType( ELbmOwnsItemArray );
    iContainer->SetControlL( list );

    CArrayFixFlat<TCoeColorUse>* colorUseList = new( ELeave ) 
        CArrayFixFlat<TCoeColorUse>( KFour );
    CleanupStack::PushL( colorUseList );
    list->GetColorUseListL( *colorUseList );
    colorUseList->Reset();    
    CleanupStack::PopAndDestroy( colorUseList );

    iContainer->ResetControl();
    CleanupStack::Pop( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestTXLBHandleResourceChangeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestTXLBHandleResourceChangeL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKTXLBXTestModule" );
    _LIT( KTestEIKTXLBX, "In TestTXLBHandleResourceChangeL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKTXLBX );
    // Print to log file
    iLog->Log( KTestEIKTXLBX );

    TInt flags = CEikListBox::EIncrementalMatching | 
                EAknListBoxSelectionList | EAknListBoxViewerFlags;
    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_SETTING );
    CleanupStack::PushL( textArray );

    CEikTextListBox* list = new( ELeave ) CEikTextListBox();
    CleanupStack::PushL( list );
    list->ConstructL( iContainer, flags );
    list->Model()->SetItemTextArray( textArray );
    list->Model()->SetOwnershipType( ELbmOwnsItemArray );
    iContainer->SetControlL( list );

    list->HandleResourceChange( KAknsMessageSkinChange );

    iContainer->ResetControl();
    CleanupStack::Pop( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestTXLBHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestTXLBHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKTXLBXTestModule" );
    _LIT( KTestEIKTXLBX, "In TestTXLBHandlePointerEventL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKTXLBX );
    // Print to log file
    iLog->Log( KTestEIKTXLBX );

    TInt flags = CEikListBox::EIncrementalMatching | 
                EAknListBoxSelectionList | EAknListBoxViewerFlags;
    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_SETTING );
    CleanupStack::PushL( textArray );

    CEikTextListBox* list = new( ELeave ) CEikTextListBox();
    CleanupStack::PushL( list );
    list->ConstructL( iContainer, flags );
    list->Model()->SetItemTextArray( textArray );
    list->Model()->SetOwnershipType( ELbmOwnsItemArray );
    iContainer->SetControlL( list );

    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( 0, KNine );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    list->HandlePointerEventL( event );

    iContainer->ResetControl();
    CleanupStack::Pop( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestTXLBWriteInternalStateL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestTXLBWriteInternalStateL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKTXLBXTestModule" );
    _LIT( KTestEIKTXLBX, "In TestTXLBWriteInternalStateL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKTXLBX );
    // Print to log file
    iLog->Log( KTestEIKTXLBX );

    TInt flags = CEikListBox::EIncrementalMatching | 
                EAknListBoxSelectionList | EAknListBoxViewerFlags;
    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_SETTING );
    CleanupStack::PushL( textArray );

    CTestSDKListsTextListBox* list = new( ELeave ) CTestSDKListsTextListBox();
    CleanupStack::PushL( list );
    list->ConstructL( iContainer, flags );
    list->Model()->SetItemTextArray( textArray );
    list->Model()->SetOwnershipType( ELbmOwnsItemArray );
    iContainer->SetControlL( list );

    RFs& tempServer = iEikonEnvPointer->FsSession();    
    tempServer.Delete( KStreamName );    
    RFileWriteStream fWrite;
    User::LeaveIfError( fWrite.Create( tempServer, 
        KStreamName, EFileWrite ) );
    CleanupClosePushL( fWrite );
    list->WriteInternalStateL( fWrite );

    CleanupStack::PopAndDestroy();
    iContainer->ResetControl();
    CleanupStack::Pop( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestTXLBCreateItemDrawerL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestTXLBCreateItemDrawerL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKTXLBXTestModule" );
    _LIT( KTestEIKTXLBX, "In TestTXLBCreateItemDrawerL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKTXLBX );
    // Print to log file
    iLog->Log( KTestEIKTXLBX );

    CTestSDKListsTextListBox* list = new( ELeave ) CTestSDKListsTextListBox();
    CleanupStack::PushL( list );

    TInt err = KErrNone;
    TRAP( err, list->CreateItemDrawerL() );

    CleanupStack::PopAndDestroy( list );

    return err;
    }

// ======================= class CEikSnakingTextListBox=========================
// -----------------------------------------------------------------------------
// CTestSDKLists::TestSTXLBConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSTXLBConstructorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKTXLBXTestModule" );
    _LIT( KTestEIKTXLBX, "In TestSTXLBConstructorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKTXLBX );
    // Print to log file
    iLog->Log( KTestEIKTXLBX );

    CEikSnakingTextListBox* list = new( ELeave ) CEikSnakingTextListBox();
    CleanupStack::PushL( list );
    STIF_ASSERT_NOT_NULL( list );
    CleanupStack::PopAndDestroy( list );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSTXLBDestructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSTXLBDestructorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKTXLBXTestModule" );
    _LIT( KTestEIKTXLBX, "In TestSTXLBDestructorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKTXLBX );
    // Print to log file
    iLog->Log( KTestEIKTXLBX );

    CEikSnakingTextListBox* list = new( ELeave ) CEikSnakingTextListBox();
    CleanupStack::PushL( list );
    STIF_ASSERT_NOT_NULL( list );
    CleanupStack::Pop( list );
    delete list;
    list = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSTXLBConstructL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSTXLBConstructL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKTXLBXTestModule" );
    _LIT( KTestEIKTXLBX, "In TestSTXLBConstructL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKTXLBX );
    // Print to log file
    iLog->Log( KTestEIKTXLBX );

    TInt flags = CEikListBox::EIncrementalMatching |  EAknListBoxSelectionList | 
        EAknListBoxViewerFlags | CEikListBox::ELeftDownInViewRect;
    CEikSnakingTextListBox* list = new( ELeave ) CEikSnakingTextListBox();
    CleanupStack::PushL( list );
    list->ConstructL( iContainer, flags );
    CleanupStack::PopAndDestroy( list );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSTXLBModelL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSTXLBModelL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKTXLBXTestModule" );
    _LIT( KTestEIKTXLBX, "In TestSTXLBModelL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKTXLBX );
    // Print to log file
    iLog->Log( KTestEIKTXLBX );

    TInt flags = CEikListBox::EIncrementalMatching |  EAknListBoxSelectionList | 
        EAknListBoxViewerFlags | CEikListBox::ELeftDownInViewRect;
    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_SETTING );
    CleanupStack::PushL( textArray );

    CEikSnakingTextListBox* list = new( ELeave ) CEikSnakingTextListBox();
    CleanupStack::PushL( list );
    list->ConstructL( iContainer, flags );
    list->Model()->SetItemTextArray( textArray );
    list->Model()->SetOwnershipType( ELbmOwnsItemArray );
    iContainer->SetControlL( list );

    CTextListBoxModel* model = list->Model();
    STIF_ASSERT_NOT_NULL( model );

    iContainer->ResetControl();
    CleanupStack::Pop( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSTXLBGetColorUseListL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSTXLBGetColorUseListL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKTXLBXTestModule" );
    _LIT( KTestEIKTXLBX, "In TestSTXLBGetColorUseListL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKTXLBX );
    // Print to log file
    iLog->Log( KTestEIKTXLBX );

    TInt flags = CEikListBox::EIncrementalMatching |  EAknListBoxSelectionList | 
        EAknListBoxViewerFlags | CEikListBox::ELeftDownInViewRect;
    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_SETTING );
    CleanupStack::PushL( textArray );

    CEikSnakingTextListBox* list = new( ELeave ) CEikSnakingTextListBox();
    CleanupStack::PushL( list );
    list->ConstructL( iContainer, flags );
    list->Model()->SetItemTextArray( textArray );
    list->Model()->SetOwnershipType( ELbmOwnsItemArray );
    iContainer->SetControlL( list );

    CArrayFixFlat<TCoeColorUse>* colorUseList = new( ELeave ) 
        CArrayFixFlat<TCoeColorUse>( KFour );
    CleanupStack::PushL( colorUseList );
    list->GetColorUseListL( *colorUseList );
    colorUseList->Reset();    
    CleanupStack::PopAndDestroy( colorUseList );

    iContainer->ResetControl();
    CleanupStack::Pop( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSTXLBHandleResourceChangeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSTXLBHandleResourceChangeL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKTXLBXTestModule" );
    _LIT( KTestEIKTXLBX, "In TestSTXLBHandleResourceChangeL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKTXLBX );
    // Print to log file
    iLog->Log( KTestEIKTXLBX );

    TInt flags = CEikListBox::EIncrementalMatching |  EAknListBoxSelectionList | 
        EAknListBoxViewerFlags | CEikListBox::ELeftDownInViewRect;
    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_SETTING );
    CleanupStack::PushL( textArray );

    CEikSnakingTextListBox* list = new( ELeave ) CEikSnakingTextListBox();
    CleanupStack::PushL( list );
    list->ConstructL( iContainer, flags );
    list->Model()->SetItemTextArray( textArray );
    list->Model()->SetOwnershipType( ELbmOwnsItemArray );
    iContainer->SetControlL( list );

    list->HandleResourceChange( KAknsMessageSkinChange );

    iContainer->ResetControl();
    CleanupStack::Pop( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSTXLBHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSTXLBHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKTXLBXTestModule" );
    _LIT( KTestEIKTXLBX, "In TestSTXLBHandlePointerEventL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKTXLBX );
    // Print to log file
    iLog->Log( KTestEIKTXLBX );

    TInt flags = CEikListBox::EIncrementalMatching |  EAknListBoxSelectionList | 
        EAknListBoxViewerFlags | CEikListBox::ELeftDownInViewRect;
    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_SETTING );
    CleanupStack::PushL( textArray );

    CEikSnakingTextListBox* list = new( ELeave ) CEikSnakingTextListBox();
    CleanupStack::PushL( list );
    list->ConstructL( iContainer, flags );
    list->Model()->SetItemTextArray( textArray );
    list->Model()->SetOwnershipType( ELbmOwnsItemArray );
    iContainer->SetControlL( list );

    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( 0, KNine );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    list->HandlePointerEventL( event );

    iContainer->ResetControl();
    CleanupStack::Pop( 2 );

    return KErrNone;
    }
