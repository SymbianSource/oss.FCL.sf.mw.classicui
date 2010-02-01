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
* Description:         Implements test bc for popup testcase.
*
*/









#include <w32std.h>
#include <coecntrl.h>
#include <bctestpopups.rsg> 
#include <aknpopup.h>
#include <aknpopupfader.h>
#include <barsread.h>
#include <aknform.h>
#include <aknlists.h>
#include <eikbtgpc.h>
#include <aknscontrolcontext.h> //MAknsControlContext
#include <aknform.h>

#include "bctestsubpopup.h"
#include "bctestpopupcase.h"
#include "bctestpopupscontainer.h"
#include "bctestpopups.hrh"
#include "autotestcommands.h" 

// constant
const TInt KMaximumHeight = 5;

_LIT( KAknPopupList, "PopupList created" ); 
_LIT( KTitle, "Popup control" );
_LIT( KSetTitleL, "Invoke CAknPopupList's SetTitleL()" );
_LIT( KHeading, "Invoke CAknPopupList's Heading()" );
_LIT( KButtonGroupContainer, 
    "Invoke CAknPopupList's ButtonGroupContainer()" );
_LIT( KEnableFind, "Invoke CAknPopupList's EnableFind()" );
_LIT( KListBox, "Invoke CAknPopupList's ListBox()" );
_LIT( KFindBox, "Invoke CAknPopupList's FindBox()" );
_LIT( KHandlePointerEventL, 
    "Invoke CAknPopupList's HandlePointerEventL()" );
_LIT( KSetMaximumHeight, "Invoke CAknPopupList's SetMaximumHeight()" );
_LIT( KExecuteLD, "Invoke CAknPopupList's ExecuteLD()" );
_LIT( KSubPopup, "subpopup created" );
_LIT( KLayout, "Invoke CAknPopupList's Layout()" );
_LIT( KMopSupplyObject, "Invoke CAknPopupList's MopSupplyObject()" );
_LIT( KHandleResourceChange, 
    "Invoke CAknPopupList's HandleResourceChange()" );
_LIT( KHandleControlEventL, 
    "Invoke CAknPopupList's HandleControlEventL()" );
_LIT( KHandleListBoxEventL, 
    "Invoke CAknPopupList's HandleListBoxEventL()" );
_LIT( KListBoxOverLoad, "Invoke CAknPopupList's ListBox() againg" );
_LIT( KConstListBox, "Invoke CAknPopupList's ListBox()(const)" );
_LIT( KConstLayout, "Invoke CAknPopupList's Layout()(const)" );
_LIT( KMinimumSize, "Invoke CAknPopupList's MinimumSize()" );
_LIT( KOfferKeyEventL, "Invoke CAknPopupList's OfferKeyEventL()" );
_LIT( KBaseDialog, "BaseDialog created" );
_LIT( KFadeBehindPopup, "Invoke TAknPopupFader's FadeBehindPopup()" );

const TInt KOne = 1;
const TInt KTwo = 2;

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestPopupCase* CBCTestPopupCase::NewL(
    CBCTestPopupsContainer* aContainer )
    {
    CBCTestPopupCase* self = new( ELeave ) CBCTestPopupCase(
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
CBCTestPopupCase::CBCTestPopupCase(
    CBCTestPopupsContainer* aContainer ) : iContainer( aContainer )
    {
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestPopupCase::~CBCTestPopupCase()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestPopupCase::ConstructL()
    {
    BuildScriptL();
    }

// ---------------------------------------------------------------------------
// CBCTestPopupCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestPopupCase::BuildScriptL()
    {
    const TInt scripts[] =
        {
        //outline4
        DELAY( KOne ),  // delay between commands is 1*0.1 seconds = 0.1 seconds
        LeftCBA,
        Down,
        KeyOK,
        KeyOK,
        RightCBA,

        //outline5
        LeftCBA,
        Down,
        KeyOK,
        REP( Down, KOne ),
        KeyOK,
        
        //outline6
        LeftCBA,
        Down,
        KeyOK,
        REP( Down, KTwo ),
        KeyOK 
        };
    AddTestScriptL( scripts, sizeof( scripts ) / sizeof( TInt ) );    
    }

// ---------------------------------------------------------------------------
// CBCTestPopupCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestPopupCase::RunL( TInt aCmd )
    {
    if ( ( aCmd < EBCTestPopupsCmdOutline04 ) 
        || ( aCmd > EBCTestPopupsCmdOutline06 ) )
        {
        return;
        }
    switch ( aCmd )
        {
        case EBCTestPopupsCmdOutline04:
            TestPopupL();
            break;
        case EBCTestPopupsCmdOutline05:
            TestProtectedFunctionsL();
            break;
        case EBCTestPopupsCmdOutline06:
            TestTAknPopupFaderFunctionsL();           
            break;
        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// CBCTestPopupCase::TestPopupL
// ---------------------------------------------------------------------------
//
void CBCTestPopupCase::TestPopupL()
    {
    CEikFormattedCellListBox* listBox = 
        new( ELeave ) CAknSinglePopupMenuStyleListBox;
    CleanupStack::PushL( listBox );
    
    CAknPopupList* popupList = CAknPopupList::NewL( listBox, 
        R_AVKON_SOFTKEYS_SELECT_BACK, 
        AknPopupLayouts::EPopupSNotePopupWindow );
    CleanupStack::PushL( popupList );    
    AssertNotNullL( popupList, KAknPopupList );
    
    listBox->ConstructL( popupList, EAknListBoxMenuList );
    
    // Invoke CAknPopupList's SetTitleL()
    popupList->SetTitleL( KTitle );
    AssertTrueL( ETrue, KSetTitleL );
 
     // Invoke CAknPopupList's Heading()
    popupList->Heading();
    AssertTrueL( ETrue, KHeading ); 

     // Invoke CAknPopupList's ButtonGroupContainer()    
    popupList->ButtonGroupContainer();
    AssertTrueL( ETrue, KButtonGroupContainer ); 

     // Invoke CAknPopupList's EnableFind()
    popupList->EnableFind( EFalse );
    popupList->EnableFind( ETrue );
    AssertTrueL( ETrue, KEnableFind ); 

    // Invoke CAknPopupList's ListBox()
    popupList->ListBox();
    AssertTrueL( ETrue, KListBox ); 
    
    // Invoke CAknPopupList's FindBox()
    popupList->FindBox();
    AssertTrueL( ETrue, KFindBox ); 

    // Invoke CAknPopupList's HandlePointerEventL()
    TPointerEvent pointEvent;
    pointEvent.iType = TPointerEvent::EButton1Down;
    popupList->HandlePointerEventL( pointEvent );
    AssertTrueL( ETrue, KHandlePointerEventL ); 
    
    // Invoke CAknPopupList's SetMaximumHeight()
    popupList->SetMaximumHeight( KMaximumHeight );
    AssertTrueL( ETrue, KSetMaximumHeight );   
   
    CleanupStack::Pop( popupList );
    
    // Invoke CAknPopupList's ExecuteLD()
    popupList->ExecuteLD();
    AssertTrueL( ETrue, KExecuteLD );          
   
    // Invoke CAknPopupList's MinimumSize() 
    CCoeControl* pList = CAknPopupList::NewL( listBox, 
        R_AVKON_SOFTKEYS_SELECT_BACK, 
        AknPopupLayouts::EPopupSNotePopupWindow );
    CleanupStack::PushL( pList );
    pList->MinimumSize();
    AssertTrueL( ETrue, KMinimumSize );
    
    // Invoke CAknPopupList's OfferKeyEventL() 
    TKeyEvent keyEvent;
    keyEvent.iCode = EKeyCBA1;
    pList->OfferKeyEventL( keyEvent, EEventKey );
    AssertTrueL( ETrue, KOfferKeyEventL );
    
    CleanupStack::PopAndDestroy( pList );
    
    CleanupStack::PopAndDestroy( listBox );
    }
    
// ---------------------------------------------------------------------------
// CBCTestPopupCase::TestProtectedFunctionsL
// ---------------------------------------------------------------------------
//
void CBCTestPopupCase::TestProtectedFunctionsL()
    {
    CEikFormattedCellListBox* formatListBox = 
        new( ELeave ) CAknSinglePopupMenuStyleListBox;
    CleanupStack::PushL( formatListBox );
    
    CBCTestSubPopup* subPopup = CBCTestSubPopup::NewL( formatListBox, 
        R_AVKON_SOFTKEYS_SELECT_BACK, 
        AknPopupLayouts::EPopupSNotePopupWindow );
    CleanupStack::PushL( subPopup );
    AssertNotNullL( subPopup, KSubPopup );
        
    // Invoke CAknPopupList's Layout()
    subPopup->Layout(); 
    AssertTrueL( ETrue, KLayout );
    
    // Invoke CAknPopupList's MopSupplyObject()
    TTypeUid typeUid( MAknsControlContext::ETypeId );
    subPopup->MopSupplyObject( typeUid ); 
    AssertTrueL( ETrue, KMopSupplyObject );
    
    // Invoke CAknPopupList's HandleResourceChange()
    subPopup->HandleResourceChange( KEikDynamicLayoutVariantSwitch_APAC ); 
    AssertTrueL( ETrue, KHandleResourceChange );

    // Invoke CAknPopupList's HandleControlEventL()
    subPopup->HandleControlEventL( formatListBox, 
        MCoeControlObserver::EEventRequestExit );
    AssertTrueL( ETrue, KHandleControlEventL );
    
    // Invoke CAknPopupList's HandleListBoxEventL()  
    // the value EEventItemClicked maybe caused invoke CAknPopupList::AttemptExitL(),this function will disconstruct popuplist pointer,
    // so change the value to EEventItemDoubleClicked
    subPopup->HandleListBoxEventL( NULL, 
        MEikListBoxObserver::EEventItemDoubleClicked );//EEventItemClicked );
    AssertTrueL( ETrue, KHandleListBoxEventL );
    
    // Invoke CAknPopupList's ListBox()
    subPopup->ListBox();
    AssertTrueL( ETrue, KListBoxOverLoad );    

    // create const pointer of CAknPopupList
    const CBCTestSubPopup* constSubPopup = 
        const_cast<const CBCTestSubPopup*> ( subPopup );

    // Invoke CAknPopupList's Listbox()(const)    
    constSubPopup->ListBox();
    AssertTrueL( ETrue, KConstListBox );
    
    // Invoke CAknPopupList's Layout()(const)    
    constSubPopup->Layout();
    AssertTrueL( ETrue, KConstLayout );
    CleanupStack::PopAndDestroy( subPopup );     

    CleanupStack::PopAndDestroy( formatListBox );   
    } 
    
// ---------------------------------------------------------------------------
// CBCTestPopupCase::TestTAknPopupFaderFunctionsL
// ---------------------------------------------------------------------------
//
void CBCTestPopupCase::TestTAknPopupFaderFunctionsL()
    {
    // Invoke TAknPopupFader's CreateStaticL()
    CAknForm* baseDialog = new( ELeave ) CAknForm();
    CleanupStack::PushL( baseDialog );
    AssertNotNullL( baseDialog, KBaseDialog );       
    baseDialog->PrepareLC( R_BCTESTPOPUPS_FIELD_TEXT_DIALOG );
    CleanupStack::Pop();
    
    TAknPopupFader aknPopup;
    aknPopup.FadeBehindPopup( baseDialog, NULL, EFalse );
    AssertTrueL( ETrue, KFadeBehindPopup );

    
    CleanupStack::PopAndDestroy( baseDialog );
    }


    





    
   

    
