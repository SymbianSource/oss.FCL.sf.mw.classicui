/*
* Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:         test case
*
*/








 
#include <w32std.h>
#include <coecntrl.h>
#include <aknlists.h>
#include <barsread.h>
#include <eikclbd.h>
#include <bctestmisc32.rsg>

#include "bctestlistdatacase.h"
#include "bctestmisc32container.h"
#include "bctestmisc32.hrh"
#include "bctestmisc32appui.h"

_LIT( KFormatListBoxCreate, "Create CAknDoubleStyle2ListBox ok" );
_LIT( KColumnListBoxCreate, "Create CAknDoubleStyle2ListBox ok" );
_LIT( KFormateDataTest1, "CFormattedCellListBoxData long text clipped");
_LIT( KFormateDataTest2, "CFormattedCellListBoxData short text not clipped");
_LIT( KColumnDataTest1, "CColumnListBoxData long text clipped");
_LIT( KColumnDataTest2, "CColumnListBoxData shot text not clipped");

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestListDataCase* CBCTestListDataCase::NewL( 
    CBCTestmisc32Container* aContainer )
    {
    CBCTestListDataCase* self = new( ELeave ) CBCTestListDataCase( 
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
CBCTestListDataCase::CBCTestListDataCase( 
    CBCTestmisc32Container* aContainer )
    : iContainer( aContainer )
    {    
    }
    
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestListDataCase::~CBCTestListDataCase()
    {  
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestListDataCase::ConstructL()
    {    
    BuildScriptL();    
    iEikEnv = CEikonEnv::Static();    
    }
    
// ---------------------------------------------------------------------------
// CBCTestListDataCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestListDataCase::BuildScriptL()
    { 
    // Add script as your need.   
    for ( TInt i=0; i <= EBCTestCmdOutline5 - EBCTestCmdOutline2; i++ )
        {
        AddTestL( LeftCBA, REP( Down, 1 ), KeyOK, TEND );
        AddTestL( REP( Down, i ), KeyOK, TEND );
        }      
    }
    
// ---------------------------------------------------------------------------
// CBCTestListDataCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestListDataCase::RunL( TInt aCmd )
    {
    if ( aCmd < EBCTestCmdOutline2 || aCmd > EBCTestCmdOutline5 )
        {
        return;
        }
    // Call release before prepare to let container has time to draw the 
    // control created in PrepareCaseL.
    ReleaseCaseL();
    PrepareCaseL( aCmd );
    switch ( aCmd )  
        {
        case EBCTestCmdOutline2:
            TestFmtLongTextWasClippedL();
            break;
        case EBCTestCmdOutline3:
            TestFmtShortTextWasClippedL();
            break;
        case EBCTestCmdOutline4:
            TestColLongTextWasClippedL();
            break;
        case EBCTestCmdOutline5:
            TestColShortTextWasClippedL();
            break;
        default:
            break;
        }
    }

// --------------------------------------------------------------------------
// CBCTestListDataCase::SetListBoxFromResourceL
// Sets listbox from resource using ConstructFromResourceL() of
// CEikColumnListBox class.
// --------------------------------------------------------------------------
//
void CBCTestListDataCase::SetListBoxFromResourceL(
    CEikColumnListBox* aListBox, const TInt aResourceId )
    {
    if ( aListBox && aResourceId )
        {
        aListBox->SetContainerWindowL( *iContainer );        

        TResourceReader reader;
        iEikEnv->CreateResourceReaderLC( reader, aResourceId );
        aListBox->ConstructFromResourceL( reader );
        CleanupStack::PopAndDestroy(); // resource stuffs.
        }
    }

// --------------------------------------------------------------------------
// CBCTestListDataCase::SetListBoxFromResourceL
// Sets listbox from resource using ConstructFromResourceL() of
// CEikFormattedCellListBox class.
// --------------------------------------------------------------------------
//
void CBCTestListDataCase::SetListBoxFromResourceL(
    CEikFormattedCellListBox* aListBox, const TInt aResourceId )
    {
    if ( aListBox && aResourceId )
        {
        aListBox->SetContainerWindowL( *iContainer );        
        
        TResourceReader reader;
        iEikEnv->CreateResourceReaderLC( reader, aResourceId );
        aListBox->ConstructFromResourceL( reader );
        CleanupStack::PopAndDestroy(); // resource stuffs.        
        }
    }

// ---------------------------------------------------------------------------
// CBCTestListDataCase::PrepareCaseL
// ---------------------------------------------------------------------------
//
void CBCTestListDataCase::PrepareCaseL( TInt aCmd )
    {        
    switch ( aCmd )
        {
        case EBCTestCmdOutline1:
            // Here is a simple demo. You should create your control 
            // instead of this.
            iControl = new( ELeave ) CCoeControl();            
            iControl->SetContainerWindowL( *iContainer );
            iControl->MakeVisible( ETrue );
		    // Pass the owner of iControl to iContainer.
		    iContainer->SetControl( iControl );
           break;
        case EBCTestCmdOutline2:
		    iFormattedListBox = new( ELeave ) CAknDoubleStyleListBox();
		    AssertNotNullL( iFormattedListBox, KFormatListBoxCreate );  
		    SetListBoxFromResourceL(
    		iFormattedListBox, R_BCTESTMISC32_SINGLE_LONGITEM );
	        iContainer->SetControl( iFormattedListBox );

            break;
        case EBCTestCmdOutline3:
		    iFormattedListBox = new( ELeave ) CAknDoubleStyleListBox();
		    AssertNotNullL( iFormattedListBox, KFormatListBoxCreate );    
		    SetListBoxFromResourceL(
    		iFormattedListBox, R_BCTESTMISC32_SINGLE_SHORTITEM );
	        iContainer->SetControl( iFormattedListBox );

            break;
        case EBCTestCmdOutline4:
		    iColumnListBox = new( ELeave ) CAknSingleStyleListBox();
		    AssertNotNullL( iColumnListBox, KColumnListBoxCreate );
		    SetListBoxFromResourceL(
    		iColumnListBox, R_BCTESTMISC32_SINGLE_LONGITEM );
   			iContainer->SetControl( iColumnListBox );

            break;
        case EBCTestCmdOutline5:
		    iColumnListBox = new( ELeave ) CAknSingleStyleListBox();
		    AssertNotNullL( iColumnListBox, KColumnListBoxCreate );
		    SetListBoxFromResourceL(
    		iColumnListBox, R_BCTESTMISC32_SINGLE_SHORTITEM );
   			iContainer->SetControl( iColumnListBox );

            break;
            
        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// CBCTestListDataCase::ReleaseCaseL
// ---------------------------------------------------------------------------
//   
void CBCTestListDataCase::ReleaseCaseL()
    {
    // let container delete the component control.
    iContainer->ResetControl();
    iFormattedListBox = NULL;
    iColumnListBox = NULL;    
    }

// ---------------------------------------------------------------------------
// CBCTestListDataCase::TestFmtLongTextWasClippedL
// ---------------------------------------------------------------------------
//    
void CBCTestListDataCase::TestFmtLongTextWasClippedL()
    {
    CFormattedCellListBoxData* data = 
        iFormattedListBox->ItemDrawer()->FormattedCellData();
    AssertTrueL( (data->CurrentItemTextWasClipped() != 0), 
        KFormateDataTest1 );
    
    }

// ---------------------------------------------------------------------------
// CBCTestListDataCase::TestFmtShortTextWasClippedL
// ---------------------------------------------------------------------------
//    
void CBCTestListDataCase::TestFmtShortTextWasClippedL()
    {
    CFormattedCellListBoxData* data = 
        iFormattedListBox->ItemDrawer()->FormattedCellData();  
    AssertTrueL( (data->CurrentItemTextWasClipped() == 0), 
        KFormateDataTest2 );    
    }

// ---------------------------------------------------------------------------
// CBCTestListDataCase::TestColLongTextWasClippedL
// ---------------------------------------------------------------------------
//    
void CBCTestListDataCase::TestColLongTextWasClippedL()
    {
    CColumnListBoxData* data = iColumnListBox->ItemDrawer()->ColumnData();
	AssertTrueL( (data->CurrentItemTextWasClipped() != 0), KColumnDataTest1 );      
	}

// ---------------------------------------------------------------------------
// CBCTestListDataCase::TestColShortTextWasClippedL
// ---------------------------------------------------------------------------
//    
void CBCTestListDataCase::TestColShortTextWasClippedL()
    {
    CColumnListBoxData* data = iColumnListBox->ItemDrawer()->ColumnData();
    AssertTrueL( (data->CurrentItemTextWasClipped() == 0), KColumnDataTest2 );  
    }        
