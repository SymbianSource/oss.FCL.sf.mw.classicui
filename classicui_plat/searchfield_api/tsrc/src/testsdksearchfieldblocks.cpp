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
* Description:  Description
*
*/



// [INCLUDE FILES]
#include <stifparser.h>
#include <stiftestinterface.h>
#include <aknsfld.h>
#include <coemain.h>
#include <eikedwin.h> 

#include "testsdksearchfield.h"
#include "testsdksearchfieldcontainer.h"
#include "testsdksfastobserver.h"
#include "testsdksfview.h"

const TInt KSearchFieldMaxLength = 256;
const TInt KExpected = 0;
const TInt KOne = 1;
const TInt KThree = 3;

_LIT( KText, "TestSearchField" );
_LIT( KGridText, "TestGrid" );
_LIT( KInfoText, "This is my searchfield.");
const TInt KBufSize = 32;

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// Ctestsdksearchfield::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void CTestSDKSearchField::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// Ctestsdksearchfield::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestSDKSearchField::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "TestSFNewL", CTestSDKSearchField::TestSFNewL ),
        ENTRY( "TestSFDelete", CTestSDKSearchField::TestSFDelete ),
        ENTRY( "TestSFTextLength", CTestSDKSearchField::TestSFTextLength ),
        ENTRY( "TestSFGetSearchText", CTestSDKSearchField::TestSFGetSearchText ),
        ENTRY( "TestSFSetSearchTextL", CTestSDKSearchField::TestSFSetSearchTextL ),
        ENTRY( "TestSFSelectSearchTextL", CTestSDKSearchField::TestSFSelectSearchTextL ),
        ENTRY( "TestSFResetL", CTestSDKSearchField::TestSFResetL ),
        ENTRY( "TestSFSetInfoTextL", CTestSDKSearchField::TestSFSetInfoTextL ),
        ENTRY( "TestSFClipboardL", CTestSDKSearchField::TestSFClipboardL ),
        ENTRY( "TestSFSearchFieldStyle", CTestSDKSearchField::TestSFSearchFieldStyle ),
        ENTRY( "TestSFSetSkinEnabledL", CTestSDKSearchField::TestSFSetSkinEnabledL ),
        ENTRY( "TestSFOfferKeyEventL", CTestSDKSearchField::TestSFOfferKeyEventL ),
        ENTRY( "TestSFMinimumSize", CTestSDKSearchField::TestSFMinimumSize ),
        ENTRY( "TestSFMakeVisible", CTestSDKSearchField::TestSFMakeVisible ),
        ENTRY( "TestSFSetLinePos", CTestSDKSearchField::TestSFSetLinePos ),
        ENTRY( "TestSFEditor", CTestSDKSearchField::TestSFEditor ),
        ENTRY( "TestSFSetAdaptiveGridChars", CTestSDKSearchField::TestSFSetAdaptiveGridChars ),
        ENTRY( "TestSFShowAdaptiveSearchGrid", CTestSDKSearchField::TestSFShowAdaptiveSearchGrid ),
        ENTRY( "TestSFSetListColumnFilterFlags", CTestSDKSearchField::TestSFSetListColumnFilterFlagsL ),
        ENTRY( "TestSFListColumnFilterFlags", CTestSDKSearchField::TestSFListColumnFilterFlags ),
        ENTRY( "TestSFAddAdaptiveSearchTextObserverL", CTestSDKSearchField::TestSFAddAdaptiveSearchTextObserverL ),
        ENTRY( "TestSFRemoveAdaptiveSearchTextObserver", CTestSDKSearchField::TestSFRemoveAdaptiveSearchTextObserver ),
        ENTRY( "TestSFAdaptiveSearchEnabled", CTestSDKSearchField::TestSFAdaptiveSearchEnabled ),
        ENTRY( "TestSFLanguageChanged", CTestSDKSearchField::TestSFLanguageChanged ),
        
        // [test cases entries]

        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// Ctestsdksearchfield::TestSFNewL
// NewL test method function.
// -----------------------------------------------------------------------------
//
TInt CTestSDKSearchField::TestSFNewL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdksearchfield, "testsdksearchfield" );
    _LIT( KTestSFNewL, "In Example" );
    TestModuleIf().Printf( 0, Ktestsdksearchfield, KTestSFNewL );
    // Print to log file
    iLog->Log( KTestSFNewL );

    iObserver = new( ELeave ) CTestSDKSFASTObserver();
    
    iTestSDKSFView = CTestSDKSFView::NewL();
    CCoeAppUi* appUi = CCoeEnv::Static()->AppUi();
    iTestSDKSearchFieldContainer = new ( ELeave ) CTestSDKSearchFieldContainer();

    iTestSDKSearchFieldContainer->SetMopParent( iTestSDKSFView );
    iTestSDKSearchFieldContainer->ConstructL( iTestSDKSFView->ClientRect() );
    CCoeEnv::Static()->AppUi()->AddToStackL( iTestSDKSearchFieldContainer );
    iTestSDKSearchFieldContainer->MakeVisible( ETrue );

    iSearchField = CAknSearchField::NewL( *iTestSDKSearchFieldContainer, CAknSearchField::ESearch, NULL, KSearchFieldMaxLength );
    STIF_ASSERT_NOT_NULL( iSearchField );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdksearchfield::TestSFDelete
// destructor test method function.
// -----------------------------------------------------------------------------
//
TInt CTestSDKSearchField::TestSFDelete( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdksearchfield, "testsdksearchfield" );
    _LIT( KTestSFDelete, "In Example" );
    TestModuleIf().Printf( 0, Ktestsdksearchfield, KTestSFDelete );
    // Print to log file
    iLog->Log( KTestSFDelete );

    CCoeEnv::Static()->AppUi()->RemoveFromStack( iTestSDKSearchFieldContainer );
    delete iSearchField;
    iSearchField = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdksearchfield::TestSFTextLength
// TextLength test method function.
// -----------------------------------------------------------------------------
//
TInt CTestSDKSearchField::TestSFTextLength( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdksearchfield, "testsdksearchfield" );
    _LIT( KTestSFTextLength, "In Example" );
    TestModuleIf().Printf( 0, Ktestsdksearchfield, KTestSFTextLength );
    // Print to log file
    iLog->Log( KTestSFTextLength );

    TInt length;
    length = iSearchField->TextLength();
    STIF_ASSERT_EQUALS( KExpected, length );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdksearchfield::TestSFGetSearchText
// GetSearchText test method function.
// -----------------------------------------------------------------------------
//
TInt CTestSDKSearchField::TestSFGetSearchText( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdksearchfield, "testsdksearchfield" );
    _LIT( KTestSFGetSearchText, "In Example" );
    TestModuleIf().Printf( 0, Ktestsdksearchfield, KTestSFGetSearchText );
    // Print to log file
    iLog->Log( KTestSFGetSearchText );

    TBuf<KBufSize> expectedTxt( KText );
    TBuf<KBufSize> rSearchTxt;
    iSearchField->GetSearchText( rSearchTxt );
    TBool flag = expectedTxt == rSearchTxt;
    STIF_ASSERT_TRUE( flag );

    return KErrNone;
    }


// -----------------------------------------------------------------------------
// Ctestsdksearchfield::TestSFSetSearchTextL
// SetSearchTextL test method function.
// -----------------------------------------------------------------------------
//
TInt CTestSDKSearchField::TestSFSetSearchTextL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( Ktestsdksearchfield, "testsdksearchfield" );
    _LIT( KTestSFSetSearchTextL, "In Example" );
    TestModuleIf().Printf( 0, Ktestsdksearchfield, KTestSFSetSearchTextL );
    // Print to log file
    iLog->Log( KTestSFSetSearchTextL );

    iSearchField->SetSearchTextL( KText );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdksearchfield::TestSFSelectSearchTextL
// SelectSearchTextL test method function.
// -----------------------------------------------------------------------------
//
TInt CTestSDKSearchField::TestSFSelectSearchTextL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( Ktestsdksearchfield, "testsdksearchfield" );
    _LIT( KTestSFSelectSearchTextL, "In Example" );
    TestModuleIf().Printf( 0, Ktestsdksearchfield, KTestSFSelectSearchTextL );
    // Print to log file
    iLog->Log( KTestSFSelectSearchTextL );

    iSearchField->SelectSearchTextL();

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdksearchfield::TestSFResetL
// ResetL test method function.
// -----------------------------------------------------------------------------
//
TInt CTestSDKSearchField::TestSFResetL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( Ktestsdksearchfield, "testsdksearchfield" );
    _LIT( KTestSFResetL, "In Example" );
    TestModuleIf().Printf( 0, Ktestsdksearchfield, KTestSFResetL );
    // Print to log file
    iLog->Log( KTestSFResetL );

    iSearchField->ResetL();
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdksearchfield::TestSFSetInfoTextL
// SetInfoTextL test method function.
// -----------------------------------------------------------------------------
//
TInt CTestSDKSearchField::TestSFSetInfoTextL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( Ktestsdksearchfield, "testsdksearchfield" );
    _LIT( KTestSFSetInfoTextL, "In Example" );
    TestModuleIf().Printf( 0, Ktestsdksearchfield, KTestSFSetInfoTextL );
    // Print to log file
    iLog->Log( KTestSFSetInfoTextL );

    iSearchField->SetInfoTextL( KInfoText );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdksearchfield::TestSFClipboardL
// ClipboardL test method function.
// -----------------------------------------------------------------------------
//
TInt CTestSDKSearchField::TestSFClipboardL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( Ktestsdksearchfield, "testsdksearchfield" );
    _LIT( KTestSFClipboardL, "In Example" );
    TestModuleIf().Printf( 0, Ktestsdksearchfield, KTestSFClipboardL );
    // Print to log file
    iLog->Log( KTestSFClipboardL );

    iSearchField->ClipboardL( CEikEdwin::ECopy );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdksearchfield::TestSFSearchFieldStyle
// SearchFieldStyle test method function.
// -----------------------------------------------------------------------------
//
TInt CTestSDKSearchField::TestSFSearchFieldStyle( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdksearchfield, "testsdksearchfield" );
    _LIT( KTestSFSearchFieldStyle, "In Example" );
    TestModuleIf().Printf( 0, Ktestsdksearchfield, KTestSFSearchFieldStyle );
    // Print to log file
    iLog->Log( KTestSFSearchFieldStyle );

    CAknSearchField::TSearchFieldStyle axpected = CAknSearchField::ESearch;
    CAknSearchField::TSearchFieldStyle style = iSearchField->SearchFieldStyle();
    STIF_ASSERT_EQUALS( axpected, style );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdksearchfield::TestSFSetSkinEnabledL
// SetSkinEnabledL test method function.
// -----------------------------------------------------------------------------
//
TInt CTestSDKSearchField::TestSFSetSkinEnabledL( CStifItemParser& aItem )
    {

    // Print to UI
    _LIT( Ktestsdksearchfield, "testsdksearchfield" );
    _LIT( KTestSFSetSkinEnabledL, "In Example" );
    TestModuleIf().Printf( 0, Ktestsdksearchfield, KTestSFSetSkinEnabledL );
    // Print to log file
    iLog->Log( KTestSFSetSkinEnabledL );

    TInt choose;
    aItem.GetNextInt( choose );
    if ( choose == 1 )
        {
        iSearchField->SetSkinEnabledL( ETrue );
        }
    else
        {
        iSearchField->SetSkinEnabledL( EFalse );
        }

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdksearchfield::TestSFOfferKeyEventL
// OfferKeyEventL test method function.
// -----------------------------------------------------------------------------
//
TInt CTestSDKSearchField::TestSFOfferKeyEventL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdksearchfield, "testsdksearchfield" );
    _LIT( KTestSFOfferKeyEventL, "In Example" );
    TestModuleIf().Printf( 0, Ktestsdksearchfield, KTestSFOfferKeyEventL );
    // Print to log file
    iLog->Log( KTestSFOfferKeyEventL );

    TKeyEvent keyevent;
    keyevent.iCode = EKeyOK;
    iSearchField->OfferKeyEventL( keyevent, EEventKey ); 
        
    keyevent.iCode = EKeyRightArrow;
    iSearchField->OfferKeyEventL( keyevent, EEventKey ); 

    keyevent.iCode = EKeyLeftArrow;
    iSearchField->OfferKeyEventL( keyevent, EEventKey );
        
    keyevent.iCode = EKeyUpArrow;
    iSearchField->OfferKeyEventL( keyevent, EEventKey );    

    keyevent.iCode = EKeyDownArrow;
    iSearchField->OfferKeyEventL( keyevent, EEventKey );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdksearchfield::TestSFMinimumSize
// MinimumSize test method function.
// -----------------------------------------------------------------------------
//
TInt CTestSDKSearchField::TestSFMinimumSize( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdksearchfield, "testsdksearchfield" );
    _LIT( KTestSFMinimumSize, "In Example" );
    TestModuleIf().Printf( 0, Ktestsdksearchfield, KTestSFMinimumSize );
    // Print to log file
    iLog->Log( KTestSFMinimumSize );

    TSize size = iSearchField->MinimumSize();

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdksearchfield::TestSFMakeVisible
// MakeVisible test method function.
// -----------------------------------------------------------------------------
//
TInt CTestSDKSearchField::TestSFMakeVisible( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdksearchfield, "testsdksearchfield" );
    _LIT( KTestSFMakeVisible, "In Example" );
    TestModuleIf().Printf( 0, Ktestsdksearchfield, KTestSFMakeVisible );
    // Print to log file
    iLog->Log( KTestSFMakeVisible );

    iSearchField->MakeVisible( ETrue );
    iSearchField->MakeVisible( EFalse );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdksearchfield::TestSFSetLinePos
// SetLinePos test method function.
// -----------------------------------------------------------------------------
//
TInt CTestSDKSearchField::TestSFSetLinePos( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdksearchfield, "testsdksearchfield" );
    _LIT( KTestSFMakeVisible, "In Example" );
    TestModuleIf().Printf( 0, Ktestsdksearchfield, KTestSFMakeVisible );
    // Print to log file
    iLog->Log( KTestSFMakeVisible );

    // two path for 1 and 3
    iSearchField->SetLinePos( KOne );
    iSearchField->SetLinePos( KThree );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdksearchfield::TestSFEditor
// Editor test method function.
// -----------------------------------------------------------------------------
//
TInt CTestSDKSearchField::TestSFEditor( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdksearchfield, "testsdksearchfield" );
    _LIT( KTestSFMakeVisible, "In Example" );
    TestModuleIf().Printf( 0, Ktestsdksearchfield, KTestSFMakeVisible );
    // Print to log file
    iLog->Log( KTestSFMakeVisible );

    CEikEdwin& edwin = iSearchField->Editor();

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdksearchfield::TestSFSetAdaptiveGridChars
// SetAdaptiveGridChars test method function.
// -----------------------------------------------------------------------------
//
TInt CTestSDKSearchField::TestSFSetAdaptiveGridChars( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdksearchfield, "testsdksearchfield" );
    _LIT( KTestSFMakeVisible, "In Example" );
    TestModuleIf().Printf( 0, Ktestsdksearchfield, KTestSFMakeVisible );
    // Print to log file
    iLog->Log( KTestSFMakeVisible );

    iSearchField->SetAdaptiveGridChars( KGridText );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdksearchfield::TestSFShowAdaptiveSearchGrid
// ShowAdaptiveSearchGrid test method function.
// -----------------------------------------------------------------------------
//
TInt CTestSDKSearchField::TestSFShowAdaptiveSearchGrid( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdksearchfield, "testsdksearchfield" );
    _LIT( KTestSFMakeVisible, "In Example" );
    TestModuleIf().Printf( 0, Ktestsdksearchfield, KTestSFMakeVisible );
    // Print to log file
    iLog->Log( KTestSFMakeVisible );

    iSearchField->ShowAdaptiveSearchGrid();

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdksearchfield::TestSFSetListColumnFilterFlags
// SetListColumnFilterFlags test method function.
// -----------------------------------------------------------------------------
//
TInt CTestSDKSearchField::TestSFSetListColumnFilterFlagsL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdksearchfield, "testsdksearchfield" );
    _LIT( KTestSFMakeVisible, "In Example" );
    TestModuleIf().Printf( 0, Ktestsdksearchfield, KTestSFMakeVisible );
    // Print to log file
    iLog->Log( KTestSFMakeVisible );

    TBitFlags32* bitFlag = new( ELeave ) TBitFlags32();
    CleanupStack::PushL( bitFlag );
    iSearchField->SetListColumnFilterFlags( *bitFlag );
    CleanupStack::Pop( bitFlag );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdksearchfield::TestSFListColumnFilterFlags
// ListColumnFilterFlags test method function.
// -----------------------------------------------------------------------------
//
TInt CTestSDKSearchField::TestSFListColumnFilterFlags( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdksearchfield, "testsdksearchfield" );
    _LIT( KTestSFMakeVisible, "In Example" );
    TestModuleIf().Printf( 0, Ktestsdksearchfield, KTestSFMakeVisible );
    // Print to log file
    iLog->Log( KTestSFMakeVisible );

    iSearchField->ListColumnFilterFlags();

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdksearchfield::TestSFAddAdaptiveSearchTextObserverL
// AddAdaptiveSearchTextObserverL test method function.
// -----------------------------------------------------------------------------
//
TInt CTestSDKSearchField::TestSFAddAdaptiveSearchTextObserverL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdksearchfield, "testsdksearchfield" );
    _LIT( KTestSFMakeVisible, "In Example" );
    TestModuleIf().Printf( 0, Ktestsdksearchfield, KTestSFMakeVisible );
    // Print to log file
    iLog->Log( KTestSFMakeVisible );

    iSearchField->AddAdaptiveSearchTextObserverL( iObserver );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdksearchfield::TestSFRemoveAdaptiveSearchTextObserver
// RemoveAdaptiveSearchTextObserver test method function.
// -----------------------------------------------------------------------------
//
TInt CTestSDKSearchField::TestSFRemoveAdaptiveSearchTextObserver( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdksearchfield, "testsdksearchfield" );
    _LIT( KTestSFMakeVisible, "In Example" );
    TestModuleIf().Printf( 0, Ktestsdksearchfield, KTestSFMakeVisible );
    // Print to log file
    iLog->Log( KTestSFMakeVisible );

    TBool flag = iSearchField->RemoveAdaptiveSearchTextObserver( iObserver );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdksearchfield::TestSFAdaptiveSearchEnabled
// AdaptiveSearchEnabled test method function.
// -----------------------------------------------------------------------------
//
TInt CTestSDKSearchField::TestSFAdaptiveSearchEnabled( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdksearchfield, "testsdksearchfield" );
    _LIT( KTestSFMakeVisible, "In Example" );
    TestModuleIf().Printf( 0, Ktestsdksearchfield, KTestSFMakeVisible );
    // Print to log file
    iLog->Log( KTestSFMakeVisible );

    TBool flag = iSearchField->AdaptiveSearchEnabled();

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdksearchfield::TestSFLanguageChanged
// LanguageChanged test method function.
// -----------------------------------------------------------------------------
//
TInt CTestSDKSearchField::TestSFLanguageChanged( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdksearchfield, "testsdksearchfield" );
    _LIT( KTestSFMakeVisible, "In Example" );
    TestModuleIf().Printf( 0, Ktestsdksearchfield, KTestSFMakeVisible );
    // Print to log file
    iLog->Log( KTestSFMakeVisible );

    TBool flag = iSearchField->LanguageChanged();

    return KErrNone;
    }

//  [End of File]
