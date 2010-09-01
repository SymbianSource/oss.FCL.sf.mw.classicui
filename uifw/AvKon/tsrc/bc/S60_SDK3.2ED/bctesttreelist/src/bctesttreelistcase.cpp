/*
* Copyright (c) 2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  test case
*
*/


#include <w32std.h>
#include <coecntrl.h>
#include <aknlists.h>
#include <AknIconUtils.h>
#include <eikscrlb.h>
#include <aknsinglestyletreelist.h>
#include <aknsinglecolumnstyletreelist.h>
#include <avkon.mbg>

#include "BCTestTreeListcase.h"
#include "BCTestTreeListcontainer.h"
#include "BCTestTreeList.hrh"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestTreeListCase* CBCTestTreeListCase::NewL(
    CBCTestTreeListContainer* aContainer )
    {
    CBCTestTreeListCase* self = new( ELeave ) CBCTestTreeListCase(
        aContainer );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default constructor
// ---------------------------------------------------------------------------
//
CBCTestTreeListCase::CBCTestTreeListCase(
    CBCTestTreeListContainer* aContainer )
    : iContainer( aContainer )
    {
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestTreeListCase::~CBCTestTreeListCase()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestTreeListCase::ConstructL()
    {
    BuildScriptL();
    }

// ---------------------------------------------------------------------------
// CBCTestTreeListCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestTreeListCase::BuildScriptL()
    {
    const TInt scripts[] =
    	{
    	DELAY( 5 ), // delay between commands is 1*0.1 seconds = 0.1 seconds
    	LeftCBA,    	
    	LeftCBA    	
    	};
    AddTestScriptL( scripts, sizeof( scripts )/sizeof( TInt ) );
    }

// ---------------------------------------------------------------------------
// CBCTestTreeListCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestTreeListCase::RunL( TInt aCmd )
    {
    if ( aCmd < EBCTestCmdOutline1 || aCmd > EBCTestCmdOutline1 )
        {
        return;
        }    
    switch ( aCmd )
        {
        case EBCTestCmdOutline1:
            TestTreeList();
            TestSingleStyleTreeList();
            TestSingleColumnStyleTreeList();
            TestScrollBar();
            break;
        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// CBCTestTreeListCase::TestTreeList()
// ---------------------------------------------------------------------------
//
void CBCTestTreeListCase::TestTreeList()
    {
    CAknTreeList* list = CAknSingleStyleTreeList::NewLC();

    _LIT( KAddIconL, "Class CAknTreeList function AddIconL tested" );
    _LIT( KAssignIconL, "Class CAknTreeList function AssignIconL tested" );
    _LIT( KTabModeFunctionIndicators, "Class CAknTreeList function TabModeFunctionIndicators tested" );
    _LIT( KEnableTabModeFunctionIndicatorsL, "Class CAknTreeList function EnableTabModeFunctionIndicatorsL tested" );
    

    // Test missing CAknTreeList class exports here!


    // TInt AddIconL( CFbsBitmap*, CFbsBitmap*, TBool, TScaleMode )
    CFbsBitmap* bitmap = NULL;
    CFbsBitmap* mask = NULL;
    AknIconUtils::CreateIconLC( bitmap, mask,
        AknIconUtils::AvkonIconFileName(),
        EMbmAvkonQgn_indi_mce_priority_high,
        EMbmAvkonQgn_indi_mce_priority_high_mask );
    TInt icon = list->AddIconL( bitmap, mask, ETrue,
        EAspectRatioPreserved );
    CleanupStack::Pop( 2 );
    bitmap = NULL;
    mask = NULL;
    AssertTrueL( ETrue, KAddIconL ); 

    // void AssignIconL( TInt, CFbsBitmap*, CFbsBitmap*, TBool, TScaleMode )
    AknIconUtils::CreateIconLC( bitmap, mask,
        AknIconUtils::AvkonIconFileName(),
        EMbmAvkonQgn_indi_mce_priority_high,
        EMbmAvkonQgn_indi_mce_priority_high_mask );
    list->AssignIconL( icon, bitmap, mask, ETrue, EAspectRatioNotPreserved );
    CleanupStack::Pop( 2 );
    AssertTrueL( ETrue, KAssignIconL );

    // TBool TabModeFunctionIndicators() const
    list->TabModeFunctionIndicators();
    AssertTrueL( ETrue, KTabModeFunctionIndicators );

    // void EnableTabModeFunctionIndicatorsL( TBool )
    list->EnableTabModeFunctionIndicatorsL( ETrue );
    AssertTrueL( ETrue, KEnableTabModeFunctionIndicatorsL );

    CleanupStack::PopAndDestroy( list );
    }


// ---------------------------------------------------------------------------
// CBCTestTreeListCase::TestSingleStyleTreeList()
// ---------------------------------------------------------------------------
//
void CBCTestTreeListCase::TestSingleStyleTreeList()
    {
    _LIT( strNewL, "Class CAknSingleStyleTreeList function NewL tested" );
    _LIT( strNewL0, "Class CAknSingleStyleTreeList function NewL( const CCoeControl ) tested" );
    _LIT( strNewLC, "Class CAknSingleStyleTreeList fuction NewLC tested" );
    _LIT( strNewLC0, "Class CAknSingleStyleTreeList function NewLC( const CCoeControl ) tested" );
    _LIT( strAddNodeL, "Class CAknSingleStyleTreeList function AddNodeL tested" );
    _LIT( strAddLeafL, "Class CAknSingleStyleTreeList function AddLeafL tested" );
    _LIT( strSetTextL, "Class CAknSingleStyleTreeList function SetTextL tested" );
    _LIT( strText, "Class CAknSingleStyleTreeList function Text tested" );
    _LIT( strSetIcon, "Class CAknSingleStyleTreeList function SetIcon tested" );
    _LIT( strIcon, "Class CAknSingleStyleTreeList function Icon tested" );
    _LIT( strSortL, "Class CAknSingleStyleTreeList function SortL tested" );

    CAknSingleStyleTreeList* sList = CAknSingleStyleTreeList::NewL();
    CleanupStack::PushL( sList );
    AssertNotNullL( sList, strNewL );
    CleanupStack::PopAndDestroy( sList );

    CAknSingleStyleTreeList* iList = CAknSingleStyleTreeList::NewL( *iContainer );
    CleanupStack::PushL( iList );
    AssertNotNullL( iList, strNewL0 );
    CleanupStack::PopAndDestroy( iList );


    CAknSingleStyleTreeList* aList = CAknSingleStyleTreeList::NewLC();
    AssertNotNullL( aList, strNewLC );
    CleanupStack::PopAndDestroy( aList );

    CAknSingleStyleTreeList* tList = CAknSingleStyleTreeList::NewLC( *iContainer );
    AssertNotNullL( tList, strNewLC0 );

    _LIT( KNodeText, "Node" );
    TUint32 flags = CAknSingleStyleTreeList::EPersistent;
    TAknTreeItemID node = tList->AddNodeL( KAknTreeIIDRoot, KNodeText, flags, EFalse );
    AssertTrueL( ETrue, strAddNodeL );

    _LIT( KLeafText, "Leaf" );
    TAknTreeItemID leaf = tList->AddLeafL( node, KLeafText, flags, EFalse );
    AssertTrueL( ETrue, strAddLeafL );

    tList->SetTextL( node, KNodeText, ETrue );
    AssertTrueL( ETrue, strSetTextL );
    TDesC text = tList->Text( node );
    AssertTrueL( ETrue, strText );

    tList->SetIcon( leaf, CAknSingleStyleTreeList::ELeaf, EMbmAvkonQgn_prop_battery_icon, ETrue );
    AssertTrueL( ETrue, strSetIcon );
    TInt iIcon = tList->Icon( leaf, CAknSingleStyleTreeList::ELeaf );
    AssertTrueL( ETrue, strIcon );

    tList->SortL( CAknSingleStyleTreeList::EAscendingAlphabeticalOrdering, ETrue );
    AssertTrueL( ETrue, strSortL );
    CleanupStack::PopAndDestroy( tList );

    }


// ---------------------------------------------------------------------------
// CBCTestTreeListCase::TestSingleColumnStyleTreeList
// ---------------------------------------------------------------------------
//
void CBCTestTreeListCase::TestSingleColumnStyleTreeList()
    {
   _LIT( KNewL1, "Class CAknSingleColumnStyleTreeList function NewL() tested" );
   _LIT( KNewL2, "Class CAknSingleColumnStyleTreeList function NewL( const CCoeControl& ) tested" );
   _LIT( KNewLC1, "Class CAknSingleColumnStyleTreeList function NewLC() tested" );
   _LIT( KNewLC2, "Class CAknSingleColumnStyleTreeList function NewLC( const CCoeControl& ) tested" );
   _LIT( KAddSimpleDataRowL, "Class CAknSingleColumnStyleTreeList function AddSimpleDataRowL( TAknTreeItemID, const TDesC&, TUint32, TBool ) tested" );
   _LIT( KAddCoreDataRowL1, "Class CAknSingleColumnStyleTreeList function AddCoreDataRowL( TAknTreeItemID, const TDesC&, const TDesC&, TUint32, TBool ) tested" );
   _LIT( KAddCoreDataRowL2, "Class CAknSingleColumnStyleTreeList function AddCoreDataRowL( TAknTreeItemID, const TDesC&, const TDesC&, const TDesC&, TUint32, TBool ) tested" );
   _LIT( KAddSubtitleRowL, "Class CAknSingleColumnStyleTreeList function AddSubtitleRowL( TAknTreeItemID, const TDesC&, TUint32, TBool ) tested" );
   _LIT( KText1, "Class CAknSingleColumnStyleTreeList function Text( TAknTreeItemID ) const tested" );
   _LIT( KText2, "Class CAknSingleColumnStyleTreeList function Text( TAknTreeItemID, TInt ) const tested" );
   _LIT( KSetTextL1, "Class CAknSingleColumnStyleTreeList function SetTextL( TAknTreeItemID, const TDesC&, TBool ) tested" );
   _LIT( KSetTextL2, "Class CAknSingleColumnStyleTreeList function SetTextL( TAknTreeItemID, const TDesC&, TInt, TBool ) tested" );
   _LIT( KIsEmphasised, "Class CAknSingleColumnStyleTreeList function IsEmphasised( TAknTreeItemID ) const tested" );
   _LIT( KSetEmphasis, "Class CAknSingleColumnStyleTreeList function SetEmphasis( TAknTreeItemID, TBool, TBool ) tested" );
   _LIT( KIsThirdColumnEnabled, "Class CAknSingleColumnStyleTreeList function IsThirdColumnEnabled( TAknTreeItemID ) const tested" );
   _LIT( KEnableThirdColumn, "Class CAknSingleColumnStyleTreeList function EnableThirdColumn( TAknTreeItemID, TBool, TBool ) tested" );
   _LIT( KIcon, "Class CAknSingleColumnStyleTreeList function Icon( TAknTreeItemID, TIconType ) const tested" );
   _LIT( KSetIcon, "Class CAknSingleColumnStyleTreeList function SetIcon( const TAknTreeItemID, const TIconType, const TInt, const TBool ) tested" );
   _LIT( KItemType, "Class CAknSingleColumnStyleTreeList function TItemType CAknSingleColumnStyleTreeList::ItemType( TAknTreeItemID ) const tested" );

    // static CAknSingleColumnStyleTreeList* NewL()
    CAknSingleColumnStyleTreeList* list = CAknSingleColumnStyleTreeList::NewL();
    CleanupStack::PushL( list );
    AssertNotNullL( list, KNewL1 );
    CleanupStack::PopAndDestroy( list );
    list = NULL;

    // static CAknSingleColumnStyleTreeList* NewL( const CCoeControl& )
    list = CAknSingleColumnStyleTreeList::NewL( *iContainer );
    CleanupStack::PushL( list );
    AssertNotNullL( list, KNewL2 );
    CleanupStack::PopAndDestroy( list );
    list = NULL;

    // static CAknSingleColumnStyleTreeList* NewLC()
    list = CAknSingleColumnStyleTreeList::NewLC();
    AssertNotNullL( list, KNewLC1 );
    CleanupStack::PopAndDestroy( list );
    list = NULL;

    // static CAknSingleColumnStyleTreeList* NewLC( const CCoeControl& )
    list = CAknSingleColumnStyleTreeList::NewLC( *iContainer );
    AssertNotNullL( list, KNewLC2 );

    // TAknTreeItemID AddSimpleDataRowL( TAknTreeItemID, const TDesC&,
    //   TUint32, TBool )
    TAknTreeItemID simpleDataRow =
        list->AddSimpleDataRowL( KAknTreeIIDRoot, _L("text"), NULL, EFalse );
    AssertTrueL( simpleDataRow != KAknTreeIIDNone, KAddSimpleDataRowL );

    // TAknTreeItemID AddCoreDataRowL( TAknTreeItemID, const TDesC&,
    //   const TDesC&, TUint32, TBool )
    TAknTreeItemID coreDataRow1 =
        list->AddCoreDataRowL( KAknTreeIIDRoot, _L( "C1" ), _L("C2"),
            NULL, EFalse );
    AssertTrueL( coreDataRow1 != KAknTreeIIDNone, KAddCoreDataRowL1 );

    // TAknTreeItemID AddCoreDataRowL( TAknTreeItemID, const TDesC&,
    //   const TDesC&, const TDesC&, TUint32, TBool )
    TAknTreeItemID coreDataRow2 =
        list->AddCoreDataRowL( KAknTreeIIDRoot, _L( "C1" ), _L("C2"), _L("C3"),
            NULL, EFalse );
    AssertTrueL( coreDataRow2 != KAknTreeIIDNone, KAddCoreDataRowL2 );

    // TAknTreeItemID AddSubtitleRowL( TAknTreeItemID, const TDesC&,
    //   TUint32, TBool )
    TAknTreeItemID subtitleRow =
        list->AddSubtitleRowL( KAknTreeIIDRoot, _L("subtitle"), NULL, EFalse );
    AssertTrueL( subtitleRow != KAknTreeIIDNone, KAddSubtitleRowL );

    // const TDesC& Text( TAknTreeItemID ) const
    const TDesC& text = list->Text( simpleDataRow );
    AssertTrueL( text != KNullDesC, KText1 );

    // const TDesC& Text( TAknTreeItemID, TInt ) const
    const TDesC& column = list->Text( coreDataRow1, 1 );
    AssertTrueL( column != KNullDesC, KText2 );

    // void SetTextL( TAknTreeItemID, const TDesC&, TBool )
    list->SetTextL( subtitleRow, _L("another subtitle"), EFalse );
    AssertTrueL( ETrue, KSetTextL1 );

    // void SetTextL( TAknTreeItemID, const TDesC& aText, TInt, TBool )
    list->SetTextL( coreDataRow2, _L("column"), 2, EFalse );
    AssertTrueL( ETrue, KSetTextL2 );

    // TBool IsEmphasised( TAknTreeItemID ) const
    list->IsEmphasised( coreDataRow1 );
    AssertTrueL( ETrue, KIsEmphasised );

    // void SetEmphasis( TAknTreeItemID, TBool, TBool )
    list->SetEmphasis( coreDataRow1, ETrue, EFalse );
    AssertTrueL( ETrue, KSetEmphasis );

    // TBool IsThirdColumnEnabled( TAknTreeItemID ) const
    list->IsThirdColumnEnabled( coreDataRow1 );
    AssertTrueL( ETrue, KIsThirdColumnEnabled );

    // void EnableThirdColumn( TAknTreeItemID, TBool, TBool )
    list->EnableThirdColumn( coreDataRow1, ETrue, EFalse );
    AssertTrueL( ETrue, KEnableThirdColumn );

    // TInt Icon( TAknTreeItemID, TIconType ) const
    list->Icon( coreDataRow1, CAknSingleColumnStyleTreeList::ELeaf );
    AssertTrueL( ETrue, KIcon );

    // void SetIcon( const TAknTreeItemID, const TIconType, const TInt,
    //   const TBool )
    list->SetIcon( coreDataRow1, CAknSingleColumnStyleTreeList::ELeaf,
        4, EFalse );
    AssertTrueL( ETrue, KSetIcon );
    
    // CAknSingleColumnStyleTreeList::TItemType ItemType(
    //   TAknTreeItemID aItem ) const
    CAknSingleColumnStyleTreeList::TItemType type =
        list->ItemType( coreDataRow1 );
    AssertIntL( CAknSingleColumnStyleTreeList::ECoreDataRow, type,
        KItemType );

    CleanupStack::PopAndDestroy( list );
    }


// ---------------------------------------------------------------------------
// CBCTestTreeListCase::TestScrollBar
// ---------------------------------------------------------------------------
//
void CBCTestTreeListCase::TestScrollBar()
    {

    _LIT( strText, "Popup info Text" );
    _LIT( strPopupInfoTextL, "Class CAknDoubleSpanScrollBar function SetScrollPopupInfoTextL tested" );
    CAknDoubleSpanScrollBar *scrbar = new( ELeave ) CAknDoubleSpanScrollBar( iContainer );
    CleanupStack::PushL( scrbar );
    scrbar->SetScrollPopupInfoTextL( strText );
    AssertTrueL( ETrue, strPopupInfoTextL );
    CleanupStack::PopAndDestroy( scrbar );

    }
