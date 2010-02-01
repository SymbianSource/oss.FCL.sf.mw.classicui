/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Test case class of bctestsingleclick.
*
*/

#include <w32std.h>
#include <coecntrl.h>
#include <aknitemactionmenu.h>
#ifdef RD_TOUCH2
#include <aknViewAppUi.h>
#include <aknview.h>
#else
#include <aknappui.h>
#endif // RD_TOUCH2
#include <eikmenup.h>
#include <eikmenub.h>
#include <avkon.hrh>
#include <eikfrlb.h>
#include <bctestsingleclick.rsg>
#ifdef RD_TOUCH2
#include <aknitemactionmenuregister.h>
#endif // RD_TOUCH2

#include "bctestsingleclickcase.h"
#include "bctestsingleclickcontainer.h"
#include "bctestsingleclick.hrh"


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTESTSingleClickCase* CBCTESTSingleClickCase::NewL( 
    CBCTESTSingleClickContainer* aContainer )
    {
    CBCTESTSingleClickCase* self = 
        new( ELeave ) CBCTESTSingleClickCase( aContainer );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }
    
// ---------------------------------------------------------------------------
// C++ default constructor
// ---------------------------------------------------------------------------
//
CBCTESTSingleClickCase::CBCTESTSingleClickCase( CBCTESTSingleClickContainer* 
    aContainer )
    : iContainer( aContainer )
    {    
    }
    
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTESTSingleClickCase::~CBCTESTSingleClickCase()
    {      
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTESTSingleClickCase::ConstructL()
    {    
    BuildScriptL();    
    }
    
// ---------------------------------------------------------------------------
// CBCTESTSingleClickCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTESTSingleClickCase::BuildScriptL()
    { 
    // Add script as your need.   
    // Use 30 to wait all discreet popups showing
    AddTestL( DELAY(1), LeftCBA, KeyOK, DELAY(1), TEND );
    }
    
// ---------------------------------------------------------------------------
// CBCTESTSingleClickCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTESTSingleClickCase::RunL( TInt aCmd )
    {
    // Call release before prepare to let container has time to draw the 
    // control created in PrepareCaseL.
    ReleaseCaseL();
    PrepareCaseL( aCmd );
    switch ( aCmd )  
        {
        case EBCTestCmdOutline1:
            TestSingleClickL();
            TestListBoxL();
            break;
        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// CBCTESTSingleClickCase::PrepareCaseL
// ---------------------------------------------------------------------------
//
void CBCTESTSingleClickCase::PrepareCaseL( TInt aCmd )
    {        
    switch ( aCmd )
        {
        case EBCTestCmdOutline1:
            // Here is a simple demo. You should create your control 
            // instead of this.
            iControl = new( ELeave ) CCoeControl();            
            iControl->SetContainerWindowL( *iContainer );
            iControl->MakeVisible( ETrue );
            break;
        default:
            break;
        }
    // Pass the owner of iControl to iContainer.
    iContainer->SetControlL( iControl );
    }

// ---------------------------------------------------------------------------
// CBCTESTSingleClickCase::ReleaseCaseL
// ---------------------------------------------------------------------------
//   
void CBCTESTSingleClickCase::ReleaseCaseL()
    {
    // let container delete the component control.
    iContainer->ResetControl();
    iControl = NULL;
    }

TUint CBCTESTSingleClickCase::CollectionState() const
    {
    return 1;
    }

void CBCTESTSingleClickCase::ItemActionMenuClosed()
    {
    
    }

TInt CBCTESTSingleClickCase::CollectionExtension(
    TUint /*aExtensionId*/, TAny*& /*a0*/, TAny* /*a1*/ )
    {
    return 1;
    }

// ---------------------------------------------------------------------------
// CBCTESTSingleClickCase::TestSingleClickL
// ---------------------------------------------------------------------------
//    
void CBCTESTSingleClickCase::TestSingleClickL()
    {
    _LIT( KSetConstructingMenuBarOwnerL, 
        "AknItemActionMenuRegister::SetConstructingMenuBarOwnerL" );
    _LIT( KIsSingleClickCompatible, 
        "CAknAppUiBase::IsSingleClickCompatible()" );    
    _LIT( KRegisterCollectionL, "CAknItemActionMenu::RegisterCollectionL" ); 
    _LIT( KInitMenuL, "CAknItemActionMenu::InitMenuL" ); 
    _LIT( KShowMenuL, "CAknItemActionMenu::ShowMenuL" ); 
    _LIT( KRemoveCollection, "CAknItemActionMenu::RemoveCollection" ); 
    _LIT( KItemSpecificCommandsEnabled, 
         "CEikMenuBar::ItemSpecificCommandsEnabled()" );
    _LIT( KSetItemSpecific, "CEikMenuPane::SetItemSpecific()" );    
#ifdef RD_TOUCH2    
    _LIT( KSetOverridingMenuBarOwnerL, 
        "AknItemActionMenuRegister::SetOverridingMenuBarOwnerL" );
    _LIT( KCollectionChanged, "CAknItemActionMenu::CollectionChanged" );
#endif // RD_TOUCH2

    //AknItemActionMenuRegister::SetConstructingMenuBarOwnerL is invoked in 
    //CAknView::BaseConstructL().
    AssertTrueL( ETrue, KSetConstructingMenuBarOwnerL );

#ifdef RD_TOUCH2
    CCoeControl* dummy = new ( ELeave ) CCoeControl;
    CleanupStack::PushL( dummy );
    AknItemActionMenuRegister::SetOverridingMenuBarOwnerL( dummy );
    AknItemActionMenuRegister::SetOverridingMenuBarOwnerL( NULL );
    AssertTrueL( ETrue, KSetOverridingMenuBarOwnerL );
    CleanupStack::PopAndDestroy();
#endif // RD_TOUCH2
    
    TBool isSingleClick = iAvkonAppUiBase->IsSingleClickCompatible();
    AssertTrueL( isSingleClick, KIsSingleClickCompatible );
    
    CAknItemActionMenu* aknItemActionMenu = 
        CAknItemActionMenu::RegisterCollectionL( *this );
    AssertTrueL( ETrue, KRegisterCollectionL );
    if ( aknItemActionMenu )
        {        
        aknItemActionMenu->InitMenuL();
        AssertTrueL( ETrue, KInitMenuL );
        
        TPoint p( 10, 10 );
        aknItemActionMenu->ShowMenuL( p );
        AssertTrueL( ETrue, KShowMenuL );
        
#ifdef RD_TOUCH2
        aknItemActionMenu->CollectionChanged( *this );
        AssertTrueL( ETrue, KCollectionChanged );
#endif // RD_TOUCH2

        aknItemActionMenu->RemoveCollection( *this );
        AssertTrueL( ETrue, KRemoveCollection );
        }
    
#ifdef RD_TOUCH2
    TVwsViewId uid;
    
    iAvkonViewAppUi->GetActiveViewId( uid );
    CEikMenuBar* menuBar = iAvkonViewAppUi->View( uid.iViewUid )->MenuBar();
#else
    CEikMenuBar* menuBar = CEikonEnv::Static()->AppUiFactory()->MenuBar();
#endif // RD_TOUCH2
    CEikMenuPane* menuPane = NULL;
    if ( menuBar )
        {
        menuBar->ItemSpecificCommandsEnabled();
        AssertTrueL( ETrue, KItemSpecificCommandsEnabled );
        menuPane = menuBar->MenuPane();
        } 
       
    if ( menuPane )
        {
        menuPane->AddMenuItemsL( R_BCTESTSINGLECLICK_ADD_MENU );
        menuPane->SetItemSpecific( EBCTestCmdOutline2, ETrue );    
        AssertTrueL( ETrue, KSetItemSpecific );
        }
    }

// ---------------------------------------------------------------------------
// CBCTESTSingleClickCase::TestSingleClickL
// ---------------------------------------------------------------------------
//    
void CBCTESTSingleClickCase::TestListBoxL()
    {
    _LIT( KDisableSingleClick, "CEikListBox::DisableSingleClick() invoked" );
     
    CEikFormattedCellListBox* listbox = new CEikFormattedCellListBox();
    CleanupStack::PushL( listbox );
    
    listbox->ConstructL( iContainer, EAknListBoxSelectionList );
    CDesCArrayFlat* text = new (ELeave) CDesCArrayFlat(1);
    CleanupStack::PushL( text );
    
    text->AppendL( _L( "\tTextItem1\t" ) );
    text->AppendL( _L( "\tTextItem2\t" ) );
    text->AppendL( _L( "\tTextItem3\t" ) );
    
    listbox->Model()->SetItemTextArray( text );
    listbox->Model()->SetOwnershipType( ELbmDoesNotOwnItemArray );
    
    listbox->DisableSingleClick( ETrue );
    AssertTrueL( ETrue, KDisableSingleClick );
   
    CleanupStack::PopAndDestroy( text );
    CleanupStack::PopAndDestroy( listbox );
    }

