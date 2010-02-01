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
* Description:  item_finder_api
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <itemfinder.h>
#include <gulbordr.h>
#include <eikrted.h> 

#include "testdomitemfinder.h"

// CONSTANTS


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDOMItemFinder::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestDOMItemFinder::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "TestIFNewL", CTestDOMItemFinder::TestIFNewL ),
        ENTRY( "TestIFNextItemOrScrollL", CTestDOMItemFinder::TestIFNextItemOrScrollL ),
        ENTRY( "TestIFSetFindModeL", CTestDOMItemFinder::TestIFSetFindModeL ),
        ENTRY( "TestIFSetEditor", CTestDOMItemFinder::TestIFSetEditorL ),
        ENTRY( "TestIFParseThisTextL", CTestDOMItemFinder::TestIFParseThisTextL ),
        ENTRY( "TestIFCreateDoItTextL", CTestDOMItemFinder::TestIFCreateDoItTextL ),
        ENTRY( "TestIFActivateThisTextL", CTestDOMItemFinder::TestIFActivateThisTextL ),
        ENTRY( "TestIFReformatOnRecognise", CTestDOMItemFinder::TestIFReformatOnRecognise ),
        ENTRY( "TestIFReformatOnRollover", CTestDOMItemFinder::TestIFReformatOnRollover ),
        ENTRY( "TestIFGetRecogniseFormat", CTestDOMItemFinder::TestIFGetRecogniseFormat ),
        ENTRY( "TestIFGetRolloverFormat", CTestDOMItemFinder::TestIFGetRolloverFormat ),
        ENTRY( "TestIFConfirmCursorOverTagL", CTestDOMItemFinder::TestIFConfirmCursorOverTagL ),
        ENTRY( "TestIFRelease", CTestDOMItemFinder::TestIFRelease ),
        ENTRY( "TestIFMParser_Reserved_2", CTestDOMItemFinder::TestIFMParser_Reserved_2 ),
        ENTRY( "TestIFPositionOfNextItem", CTestDOMItemFinder::TestIFPositionOfNextItem ),
        ENTRY( "TestIFResetCurrentItem", CTestDOMItemFinder::TestIFResetCurrentItem ),
        ENTRY( "TestIFResolveAndSetItemTypeL", CTestDOMItemFinder::TestIFResolveAndSetItemTypeL ),
        ENTRY( "TestIFAddObserver", CTestDOMItemFinder::TestIFAddObserverL ),
        ENTRY( "TestIFItemWasTappedL", CTestDOMItemFinder::TestIFItemWasTappedL ),
        ENTRY( "TestIFSetExternalLinksL", CTestDOMItemFinder::TestIFSetExternalLinksL ),
        ENTRY( "TestIFCurrentItemExt", CTestDOMItemFinder::TestIFCurrentItemExt ),
        ENTRY( "TestIFCurrentSelection", CTestDOMItemFinder::TestIFCurrentSelection ),
        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }


// -----------------------------------------------------------------------------
// CTestDOMItemFinder::TestIFNewL
// -----------------------------------------------------------------------------
//
TInt CTestDOMItemFinder::TestIFNewL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomitemfinder, "testdomitemfinder" );
    _LIT( KTestIFNewL, "In TestIFNewL" );
    TestModuleIf().Printf( 0, Ktestdomitemfinder, KTestIFNewL );
    // Print to log file
    iLog->Log( KTestIFNewL );
    
    iItemFinder = CItemFinder::NewL();
    STIF_ASSERT_NOT_NULL( iItemFinder );
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestDOMItemFinder::TestIFNextItemOrScrollL
// -----------------------------------------------------------------------------
//
TInt CTestDOMItemFinder::TestIFNextItemOrScrollL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomitemfinder, "testdomitemfinder" );
    _LIT( KTestIFNextItemOrScrollL, "In TestIFNextItemOrScrollL" );
    TestModuleIf().Printf( 0, Ktestdomitemfinder, KTestIFNextItemOrScrollL );
    // Print to log file
    iLog->Log( KTestIFNextItemOrScrollL );
    TInt err = KErrNone;
    TRAP( err, iItemFinder->NextItemOrScrollL( CItemFinder::EInit ) );

    return err;
    }
// -----------------------------------------------------------------------------
// CTestDOMItemFinder::TestIFSetFindModeL
// -----------------------------------------------------------------------------
//
TInt CTestDOMItemFinder::TestIFSetFindModeL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomitemfinder, "testdomitemfinder" );
    _LIT( KTestIFSetFindModeL, "In TestIFSetFindModeL" );
    TestModuleIf().Printf( 0, Ktestdomitemfinder, KTestIFSetFindModeL );
    // Print to log file
    iLog->Log( KTestIFSetFindModeL );
    TInt err = KErrNone;
    TRAP( err, iItemFinder->SetFindModeL( CItemFinder::EUrlAddress ) );

    return err;
    }
// -----------------------------------------------------------------------------
// CTestDOMItemFinder::TestIFSetEditor
// -----------------------------------------------------------------------------
//
TInt CTestDOMItemFinder::TestIFSetEditorL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomitemfinder, "testdomitemfinder" );
    _LIT( KTestIFSetEditor, "In TestIFSetEditor" );
    TestModuleIf().Printf( 0, Ktestdomitemfinder, KTestIFSetEditor );
    // Print to log file
    iLog->Log( KTestIFSetEditor );
    TGulBorder gulBorder;
    CEikRichTextEditor* editor = new ( ELeave ) CEikRichTextEditor ( gulBorder );
    CleanupStack::PushL( editor );
    CCoeControl* control = new ( ELeave ) CCoeControl();
    CleanupStack::PushL( control );
    editor->ConstructL( control, 0, 0, 0 );
    iItemFinder->SetEditor( &editor );
    CleanupStack::PopAndDestroy( control );
    CleanupStack::PopAndDestroy( editor );
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestDOMItemFinder::TestIFParseThisText
// -----------------------------------------------------------------------------
//
TInt CTestDOMItemFinder::TestIFParseThisTextL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomitemfinder, "testdomitemfinder" );
    _LIT( KTestIFParseThisText, "In TestIFParseThisText" );
    TestModuleIf().Printf( 0, Ktestdomitemfinder, KTestIFParseThisText );
    // Print to log file
    iLog->Log( KTestIFParseThisText );
    TInt tag(0), len(0);
    TGulBorder gulBorder;
    CEikRichTextEditor* editor = new ( ELeave ) CEikRichTextEditor ( gulBorder );
    CleanupStack::PushL( editor );
    CCoeControl* control = new ( ELeave ) CCoeControl();
    CleanupStack::PushL( control );
    editor->ConstructL( control, 0, 0, 0 );
    CRichText* richText = editor->RichText();  
    iItemFinder->ParseThisText( *richText, ETrue, 1, 1, tag, len );
    CleanupStack::PopAndDestroy( control );
    CleanupStack::PopAndDestroy( editor );
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestDOMItemFinder::TestIFCreateDoItTextL
// -----------------------------------------------------------------------------
//
TInt CTestDOMItemFinder::TestIFCreateDoItTextL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomitemfinder, "testdomitemfinder" );
    _LIT( KTestIFCreateDoItTextL, "In TestIFCreateDoItTextL" );
    TestModuleIf().Printf( 0, Ktestdomitemfinder, KTestIFCreateDoItTextL );
    // Print to log file
    iLog->Log( KTestIFCreateDoItTextL );

    TGulBorder gulBorder;
    CEikRichTextEditor* editor = new ( ELeave ) CEikRichTextEditor ( gulBorder );
    CleanupStack::PushL( editor );
    CCoeControl* control = new ( ELeave ) CCoeControl();
    CleanupStack::PushL( control );
    editor->ConstructL( control, 0, 0, 0 );
    CRichText* richText = editor->RichText();  
    iItemFinder->CreateDoItText( *richText, 1, 1 );
    CleanupStack::PopAndDestroy( control );
    CleanupStack::PopAndDestroy( editor );
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestDOMItemFinder::TestIFActivateThisTextL
// -----------------------------------------------------------------------------
//
TInt CTestDOMItemFinder::TestIFActivateThisTextL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomitemfinder, "testdomitemfinder" );
    _LIT( KTestIFActivateThisTextL, "In TestIFActivateThisTextL" );
    TestModuleIf().Printf( 0, Ktestdomitemfinder, KTestIFActivateThisTextL );
    // Print to log file
    iLog->Log( KTestIFActivateThisTextL );

    TInt err = KErrNone;
    TGulBorder gulBorder;
    CEikRichTextEditor* editor = new ( ELeave ) CEikRichTextEditor ( gulBorder );
    CleanupStack::PushL( editor );
    CCoeControl* control = new ( ELeave ) CCoeControl();
    CleanupStack::PushL( control );
    editor->ConstructL( control, 0, 0, 0 );
    CRichText* richText = editor->RichText();  
    TRAP( err, iItemFinder->ActivateThisTextL( *richText, 1, 1 ) );
    CleanupStack::PopAndDestroy( control );
    CleanupStack::PopAndDestroy( editor );
    return err;
    }
// -----------------------------------------------------------------------------
// CTestDOMItemFinder::TestIFReformatOnRecognise
// -----------------------------------------------------------------------------
//
TInt CTestDOMItemFinder::TestIFReformatOnRecognise( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomitemfinder, "testdomitemfinder" );
    _LIT( KTestIFReformatOnRecognise, "In TestIFReformatOnRecognise" );
    TestModuleIf().Printf( 0, Ktestdomitemfinder, KTestIFReformatOnRecognise );
    // Print to log file
    iLog->Log( KTestIFReformatOnRecognise );

    iItemFinder->ReformatOnRecognise();

    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestDOMItemFinder::TestIFReformatOnRollover
// -----------------------------------------------------------------------------
//
TInt CTestDOMItemFinder::TestIFReformatOnRollover( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomitemfinder, "testdomitemfinder" );
    _LIT( KTestIFReformatOnRollover, "In TestIFReformatOnRollover" );
    TestModuleIf().Printf( 0, Ktestdomitemfinder, KTestIFReformatOnRollover );
    // Print to log file
    iLog->Log( KTestIFReformatOnRollover );

    iItemFinder->ReformatOnRollover();

    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestDOMItemFinder::TestIFGetRecogniseFormat
// -----------------------------------------------------------------------------
//
TInt CTestDOMItemFinder::TestIFGetRecogniseFormat( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomitemfinder, "testdomitemfinder" );
    _LIT( KTestIFGetRecogniseFormat, "In TestIFGetRecogniseFormat" );
    TestModuleIf().Printf( 0, Ktestdomitemfinder, KTestIFGetRecogniseFormat );
    // Print to log file
    iLog->Log( KTestIFGetRecogniseFormat );
    TCharFormat format;
    iItemFinder->GetRecogniseFormat( format );

    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestDOMItemFinder::TestIFGetRolloverFormat
// -----------------------------------------------------------------------------
//
TInt CTestDOMItemFinder::TestIFGetRolloverFormat( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomitemfinder, "testdomitemfinder" );
    _LIT( KTestIFGetRolloverFormat, "In TestIFGetRolloverFormat" );
    TestModuleIf().Printf( 0, Ktestdomitemfinder, KTestIFGetRolloverFormat );
    // Print to log file
    iLog->Log( KTestIFGetRolloverFormat );
    TCharFormat format;
    iItemFinder->GetRolloverFormat( format );

    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestDOMItemFinder::TestIFConfirmCursorOverTagL
// -----------------------------------------------------------------------------
//
TInt CTestDOMItemFinder::TestIFConfirmCursorOverTagL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomitemfinder, "testdomitemfinder" );
    _LIT( KTestIFConfirmCursorOverTagL, "In TestIFConfirmCursorOverTagL" );
    TestModuleIf().Printf( 0, Ktestdomitemfinder, KTestIFConfirmCursorOverTagL );
    // Print to log file
    iLog->Log( KTestIFConfirmCursorOverTagL );
    TGulBorder gulBorder;
    CEikRichTextEditor* editor = new ( ELeave ) CEikRichTextEditor ( gulBorder );
    CleanupStack::PushL( editor );
    CCoeControl* control = new ( ELeave ) CCoeControl();
    CleanupStack::PushL( control );
    editor->ConstructL( control, 0, 0, 0 );
    CRichText* richText = editor->RichText();  
    iItemFinder->ConfirmCursorOverTag( *richText, 1, 1, 1 );
    CleanupStack::PopAndDestroy( control );
    CleanupStack::PopAndDestroy( editor );
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestDOMItemFinder::TestIFRelease
// -----------------------------------------------------------------------------
//
TInt CTestDOMItemFinder::TestIFRelease( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomitemfinder, "testdomitemfinder" );
    _LIT( KTestIFRelease, "In TestIFRelease" );
    TestModuleIf().Printf( 0, Ktestdomitemfinder, KTestIFRelease );
    // Print to log file
    iLog->Log( KTestIFRelease );

    iItemFinder->Release();
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestDOMItemFinder::TestIFMParser_Reserved_2
// -----------------------------------------------------------------------------
//
TInt CTestDOMItemFinder::TestIFMParser_Reserved_2( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomitemfinder, "testdomitemfinder" );
    _LIT( KTestIFMParser_Reserved_2, "In TestIFMParser_Reserved_2" );
    TestModuleIf().Printf( 0, Ktestdomitemfinder, KTestIFMParser_Reserved_2 );
    // Print to log file
    iLog->Log( KTestIFMParser_Reserved_2 );

    iItemFinder->MParser_Reserved_2();
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestDOMItemFinder::TestIFPositionOfNextItem
// -----------------------------------------------------------------------------
//
TInt CTestDOMItemFinder::TestIFPositionOfNextItem( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomitemfinder, "testdomitemfinder" );
    _LIT( KTestIFPositionOfNextItem, "In TestIFPositionOfNextItem" );
    TestModuleIf().Printf( 0, Ktestdomitemfinder, KTestIFPositionOfNextItem );
    // Print to log file
    iLog->Log( KTestIFPositionOfNextItem );

    iItemFinder->PositionOfNextItem( CItemFinder::ENextDown );
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestDOMItemFinder::TestIFResetCurrentItem
// -----------------------------------------------------------------------------
//
TInt CTestDOMItemFinder::TestIFResetCurrentItem( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomitemfinder, "testdomitemfinder" );
    _LIT( KTestIFResetCurrentItem, "In TestIFResetCurrentItem" );
    TestModuleIf().Printf( 0, Ktestdomitemfinder, KTestIFResetCurrentItem );
    // Print to log file
    iLog->Log( KTestIFResetCurrentItem );

    iItemFinder->ResetCurrentItem();
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestDOMItemFinder::TestIFResolveAndSetItemTypeL
// -----------------------------------------------------------------------------
//
TInt CTestDOMItemFinder::TestIFResolveAndSetItemTypeL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomitemfinder, "testdomitemfinder" );
    _LIT( KTestIFResolveAndSetItemTypeL, "In TestIFResolveAndSetItemTypeL" );
    TestModuleIf().Printf( 0, Ktestdomitemfinder, KTestIFResolveAndSetItemTypeL );
    // Print to log file
    iLog->Log( KTestIFResolveAndSetItemTypeL );

    iItemFinder->ResolveAndSetItemTypeL();
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestDOMItemFinder::TestIFAddObserver
// -----------------------------------------------------------------------------
//
TInt CTestDOMItemFinder::TestIFAddObserverL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomitemfinder, "testdomitemfinder" );
    _LIT( KTestIFAddObserver, "In TestIFAddObserver" );
    TestModuleIf().Printf( 0, Ktestdomitemfinder, KTestIFAddObserver );
    // Print to log file
    iLog->Log( KTestIFAddObserver );
    CItemFinderObserverExt* observer = new ( ELeave ) CItemFinderObserverExt;
    CleanupStack::PushL( observer );
    iItemFinder->AddObserver( *observer );
    CleanupStack::PopAndDestroy( observer );
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestDOMItemFinder::TestIFItemWasTappedL
// -----------------------------------------------------------------------------
//
TInt CTestDOMItemFinder::TestIFItemWasTappedL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomitemfinder, "testdomitemfinder" );
    _LIT( KTestIFItemWasTappedL, "In TestIFItemWasTappedL" );
    TestModuleIf().Printf( 0, Ktestdomitemfinder, KTestIFItemWasTappedL );
    // Print to log file
    iLog->Log( KTestIFItemWasTappedL );
    TInt err = KErrNone;
    TPoint point( 0, 0 );
    TRAP( err, iItemFinder->ItemWasTappedL( point ) );

    return err;
    }
// -----------------------------------------------------------------------------
// CTestDOMItemFinder::TestIFSetExternalLinks
// -----------------------------------------------------------------------------
//
TInt CTestDOMItemFinder::TestIFSetExternalLinksL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomitemfinder, "testdomitemfinder" );
    _LIT( KTestIFSetExternalLinks, "In TestIFSetExternalLinks" );
    TestModuleIf().Printf( 0, Ktestdomitemfinder, KTestIFSetExternalLinks );
    // Print to log file
    iLog->Log( KTestIFSetExternalLinks );
    _LIT( KUrlDes, "http://www.symbian.com" );
    TBuf<32> des( KUrlDes );
    CItemFinder::CFindItemExt* findex = new ( ELeave ) CItemFinder::CFindItemExt;
    CleanupStack::PushL( findex );
   
    findex->iItemType = CItemFinder::EUrlAddress;
    findex->iItemDescriptor = des.AllocL();
    CArrayPtrFlat<CItemFinder::CFindItemExt>* links = 
        new ( ELeave ) CArrayPtrFlat<CItemFinder::CFindItemExt>( 1 );
    CleanupStack::PushL( links );
    TGulBorder gulBorder;
    CEikRichTextEditor* editor = new ( ELeave ) CEikRichTextEditor ( gulBorder );
    CleanupStack::PushL( editor );
    CCoeControl* control = new ( ELeave ) CCoeControl();
    CleanupStack::PushL( control );
    editor->ConstructL( control, 0, 0, 0 );
    iItemFinder->SetEditor( &editor );
    links->AppendL( findex );
    iItemFinder->SetExternalLinks( links );
    CleanupStack::PopAndDestroy( control );
    CleanupStack::PopAndDestroy( editor );
    CleanupStack::PopAndDestroy( links );
    CleanupStack::PopAndDestroy( findex );
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestDOMItemFinder::TestIFCurrentItemExt
// -----------------------------------------------------------------------------
//
TInt CTestDOMItemFinder::TestIFCurrentItemExt( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomitemfinder, "testdomitemfinder" );
    _LIT( KTestIFCurrentItemExt, "In TestIFCurrentItemExt" );
    TestModuleIf().Printf( 0, Ktestdomitemfinder, KTestIFCurrentItemExt );
    // Print to log file
    iLog->Log( KTestIFCurrentItemExt );
    iItemFinder->CurrentItemExt();
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestDOMItemFinder::TestIFCurrentSelection
// -----------------------------------------------------------------------------
//
TInt CTestDOMItemFinder::TestIFCurrentSelection( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomitemfinder, "testdomitemfinder" );
    _LIT( KTestIFCurrentSelection, "In TestIFCurrentSelection" );
    TestModuleIf().Printf( 0, Ktestdomitemfinder, KTestIFCurrentSelection );
    // Print to log file
    iLog->Log( KTestIFCurrentSelection );
    iItemFinder->CurrentSelection();
    return KErrNone;
    }
//  [End of File]
