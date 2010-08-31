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
* Description:         Implements test bc for popup setting page testcase.
*
*/









#include <w32std.h>
#include <coecntrl.h>
#include <aknlists.h>
#include <bctestpopups.mbg>
#include <bctestpopups.rsg> 
#include <barsread.h> // TResourceRead
#include <aknquerydialog.h>
#include <eikenv.h>
#include <aknpopuplayout.h>
#include <s32mem.h>

#include "bctestpopupsettingpagecase.h"
#include "bctestsubaknpopupsettinglist.h"
#include "bctestsubaknpopuplist.h"
#include "bctestsubaknsettingpage.h"
#include "bctestpopupscontainer.h"
#include "bctestpopups.hrh"
#include "autotestcommands.h"

// constant
_LIT( KSettingListTitle, "Settings" );
_LIT( KSettingPageConstructor,
   "CAknPopupSettingPage's CBCTestPopupSettingPage(...)" );
_LIT( KSettingPageConstructorB,
    "CAknPopupSettingPage's CBCTestPopupSettingPage()" );
_LIT( KAknPopupSettingPageConstructL,
    "Invoke CAknPopupSettingPage's ConstructL()" );
_LIT( KListBoxControl,
    "Invoke CAknPopupSettingPage's ListBoxControl()" );
_LIT( KHandlePopupSettingListEventL,
    "Invoke CAknPopupSettingPage's HandlePopupSettingListEventL()" );
_LIT( KHandlePointerEventL,
    "Invoke CAknPopupSettingPage's HandlePointerEventL()" );
_LIT( KQueryValue, "Invoke CAknPopupSettingPage's QueryValue()" );
_LIT( KSelectCurrentItemL,
    "Invoke CAknPopupSettingPage's SelectCurrentItemL()" );
_LIT( KReserved_2, "Invoke CAknPopupSettingPage's Reserved_2()" );
_LIT( KUpdateQueryValueL, 
    "Invoke CAknPopupSettingPage's UpdateQueryValueL()" );
_LIT( KWriteInternalStateL, 
    "Invoke CAknPopupSettingPage's WriteInternalStateL()" );
_LIT( KPopupSettingListBox,
    "Invoke CAknPopupSettingPage's PopupSettingListBox()" );
_LIT( KPSLSetQueryValueL,
    "Invoke CAknPopupSettingList's SetQueryValueL()" );
_LIT( KPSLNumLines,
    "Invoke CAknPopupSettingList's NumLines()" );
_LIT( KPSLSetPopupSettingListObserver,
    "Invoke CAknPopupSettingList's SetPopupSettingListObserver()" );
_LIT( KPopupSettingListSetAllowsUserDefinedEntry,
    "Invoke CAknPopupSettingList's SetAllowsUserDefinedEntry()" );
_LIT( KPopupSettingListSetShowIndicators,
    "Invoke CAknPopupSettingList's SetShowIndicators()" );
_LIT( KPopupSettingListHandlePointerEventL,
    "Invoke CAknPopupSettingList's HandlePointerEventL()" );
_LIT( KPopupSettingListHandleResourceChange,
    "Invoke CAknPopupSettingList's HandleResourceChange()" );
_LIT( KPopupSettingListCreateMenuListL,
    "Invoke CAknPopupSettingList's CreateMenuListL()" );
_LIT( KPopupSettingListActivateMenuListL,
    "Invoke CAknPopupSettingList's ActivateMenuListL()" );
_LIT( KPopupSettingListDestroyMenuList,
    "Invoke CAknPopupSettingList's DestroyMenuList()" );
_LIT( KPopupSettingListConfigureMenuListL,
    "Invoke CAknPopupSettingList's ConfigureMenuListL()" );
_LIT( KPopupSettingListHandleListBoxEventL, 
    "Invoke CAknPopupSettingList's HandleListBoxEventL()" );
_LIT( KCAknPopupSettingList,
    "Invoke CAknPopupSettingList's CAknPopupSettingList()" );
_LIT( KLayoutHandleSizeChanged,
    "AknPopupLayouts's HandleSizeChanged()" );
_LIT( KLayoutModifyWindowGraphicForHeading,
    "AknPopupLayouts's ModifyWindowGraphicForHeading()" );
_LIT( KLayoutModifyWindowGraphicForMessageBox,
    "AknPopupLayouts's ModifyWindowGraphicForMessageBox()" );
_LIT( KLayoutCalcPopupMenuWindow,
    "AknPopupLayouts's CalcPopupMenuWindow()" );
_LIT( KLayoutCalcPopupMenuGraphicWindow,
    "AknPopupLayouts's CalcPopupMenuGraphicWindow()" );
_LIT( KLayoutCalcPopupMenuGraphicHeadingWindow,
    "AknPopupLayouts's CalcPopupMenuGraphicHeadingWindow()" );
_LIT( KLayoutCalcPopupMenuDoubleWindow,
    "AknPopupLayouts's CalcPopupMenuDoubleWindow()" );
_LIT( KLayoutCalcPopupMenuDoubleLargeGraphicWindow,
    "AknPopupLayouts's CalcPopupMenuDoubleLargeGraphicWindow()" );
_LIT( KLayoutCalcPopupSNoteGroupWindow,
    "AknPopupLayouts's CalcPopupSNoteGroupWindow()" );
_LIT( KLayoutSetupMenuPopupWindow,
    "AknPopupLayouts's SetupMenuPopupWindow()" );
_LIT( KLayoutSetupPopupMenuGraphicWindow,
    "AknPopupLayouts's SetupPopupMenuGraphicWindow()" );
_LIT( KLayoutSetupPopupMenuGraphicHeadingWindow,
    "AknPopupLayouts's SetupPopupMenuGraphicHeadingWindow()" );
_LIT( KLayoutSetupPopupMenuDoubleWindow,
    "AknPopupLayouts's SetupPopupMenuDoubleWindow()" );
_LIT( KLayoutSetupImageSelectionMenuPopupWindow,
    "AknPopupLayouts's SetupImageSelectionMenuPopupWindow()" );
_LIT( KLayoutSetupPopupSNoteGroupWindow,
    "AknPopupLayouts's SetupPopupSNoteGroupWindow()" );
_LIT( KLayoutHandleSizeAndPositionOfComponents,
    "AknPopupLayouts's HandleSizeAndPositionOfComponents()" );
_LIT( KLayoutSetupDefaults, "AknPopupLayouts's SetupDefaults()" );
_LIT( KLayoutWindowRectA, "AknPopupLayouts's WindowRect()" );
_LIT( KLayoutMenuRect, "AknPopupLayouts's MenuRect()" );
_LIT( KLayoutCheckRange, "AknPopupLayouts's CheckRange()" );
_LIT( KLayoutMenuPopupWindowGraphics,
    "AknPopupLayouts's MenuPopupWindowGraphics()" );

const TInt KOne = 1;
const TInt KTwo = 2;
const TInt KThree = 3;
const TInt KFour = 4;
const TInt KSixteen = 16;
const TInt KTwoHundred = 200;

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestPopupSettingPageCase* CBCTestPopupSettingPageCase::NewL(
    CBCTestPopupsContainer* aContainer )
    {
    CBCTestPopupSettingPageCase* self = new( ELeave ) 
        CBCTestPopupSettingPageCase( aContainer );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    } 

// ---------------------------------------------------------------------------
// C++ default constructor
// ---------------------------------------------------------------------------
//
CBCTestPopupSettingPageCase::CBCTestPopupSettingPageCase(
    CBCTestPopupsContainer* aContainer ) : iContainer( aContainer )
    {
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestPopupSettingPageCase::~CBCTestPopupSettingPageCase()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestPopupSettingPageCase::ConstructL()
    {
    iEikEnv = static_cast<CEikonEnv*> ( iContainer->GetCoeEnv() );
    BuildScriptL();
    }

// ---------------------------------------------------------------------------
// CBCTestPopupSettingPageCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestPopupSettingPageCase::BuildScriptL()
    {
    const TInt scripts[] =
        {
        //outline10
        DELAY( KOne ),  // delay between commands is 1*0.1 seconds = 0.1 seconds
        LeftCBA,
        REP( Down, KThree ),
        KeyOK,
        KeyOK,

        //outline11
        LeftCBA,
        REP( Down, KThree ),
        KeyOK,
        REP( Down, KOne ),
        KeyOK,

        //outline12
        LeftCBA,
        REP( Down, KFour ),
        KeyOK,
        REP( Down, KTwo ),
        KeyOK
        };
    AddTestScriptL( scripts, sizeof( scripts ) / sizeof( TInt ) );
    }

// ---------------------------------------------------------------------------
// CBCTestPopupSettingPageCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestPopupSettingPageCase::RunL( TInt aCmd )
    {
    if ( ( aCmd < EBCTestPopupsCmdOutline10 )
        || ( aCmd > EBCTestPopupsCmdOutline12 ) )
        {
        return;
        }
    switch ( aCmd )
        {
        case EBCTestPopupsCmdOutline10:
            TestFunctionsForSettingPageL();
            break;
        case EBCTestPopupsCmdOutline11:
            break;
        case EBCTestPopupsCmdOutline12:
            TestFunctionForPopLayoutsL();
            break;
        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// CBCTestPopupSettingPageCase::TestFunctionsForSettingPageL
// ---------------------------------------------------------------------------
//
void CBCTestPopupSettingPageCase::TestFunctionsForSettingPageL()
    {
    // Construct
    CDesCArrayFlat* item;
    CAknQueryValueTextArray* textArray;
    CAknQueryValueText*      queryValueText;

    item = iEikEnv->ReadDesCArrayResourceL( R_BCTESTPOPUPS_LIST_ITEM_ARRAY );
    CleanupStack::PushL( item );
    
    textArray = CAknQueryValueTextArray::NewL();
    textArray->SetArray( *item );
    CleanupStack::PushL( textArray );
    
    queryValueText = CAknQueryValueText::NewL();
    CleanupStack::PushL( queryValueText );
    queryValueText->SetArrayL( textArray );

    TBufC<KSixteen> title ( KSettingListTitle );

    iSettingPage =
        new( ELeave ) CBCTestPopupSettingPage( &title,
                                            0,
                                            0,
                                            0,
                                            R_BCTESTPOPUPS_POPUP_SETTING_PAGE,
                                            *queryValueText );
    iSettingPage->ConstructL();// construct it correctly
    AssertTrueL(  ETrue, KSettingPageConstructor );
    delete iSettingPage;
    iSettingPage = NULL;

    // Invoke CAknPopupSettingPage's CBCTestPopupSettingPage()
    iSettingPage = new( ELeave ) CBCTestPopupSettingPage(
        R_BCTESTPOPUPS_POPUP_SETTING_PAGE, *queryValueText );
    AssertTrueL( ETrue, KSettingPageConstructorB );

    // Invoke CAknPopupSettingPage's ConstructL()
    iSettingPage->ConstructL();
    AssertTrueL( ETrue, KAknPopupSettingPageConstructL );

    // Invoke CAknPopupSettingPage's ListBoxControl()
    CAknSetStyleListBox* listBox = iSettingPage->ListBoxControl();
    AssertTrueL( ETrue, KListBoxControl );    

    // Invoke CAknPopupSettingPage's HandlePopupSettingListEventL()
    iSettingPage->HandlePopupSettingListEventL( 
        NULL,
        MAknPopupSettingListObserver
        ::EAknPopupSettingSelectionAndRequestAccept,
        0 );
    AssertTrueL( ETrue, KHandlePopupSettingListEventL );

    // Invoke CAknPopupSettingPage's HandlePointerEventL()
    TPointerEvent pointEvent;
    pointEvent.iType = TPointerEvent::EButton1Down;
    iSettingPage->HandlePointerEventL( pointEvent );
    AssertTrueL( ETrue, KHandlePointerEventL );

    // Invoke CAknPopupSettingPage's QueryValue()
    iSettingPage->QueryValue();
    AssertTrueL( ETrue, KQueryValue );

    // Invoke CAknPopupSettingPage's SelectCurrentItemL()
    iSettingPage->SelectCurrentItemL();
    AssertTrueL( ETrue, KSelectCurrentItemL );
    
    // Invoke CAknPopupSettingPage's Reserved_2()
    iSettingPage->Reserved_2();
    AssertTrueL( ETrue, KReserved_2 );
    
    // Invoke CAknPopupSettingPage's UpdateQueryValueL()
    iSettingPage->UpdateQueryValueL( queryValueText );
    AssertTrueL( ETrue, KUpdateQueryValueL );

    // Invoke CAknPopupSettingPage's WriteInternalStateL()
    CBufFlat* buf = CBufFlat::NewL( KTwoHundred );
    CleanupStack::PushL( buf );
    RBufWriteStream stream;
    stream.Open( *buf );
    iSettingPage->WriteInternalStateL( stream );
    AssertTrueL( ETrue, KWriteInternalStateL ); 
    stream.Close();
    CleanupStack::PopAndDestroy( buf );

    // Invoke CAknPopupSettingPage's PopupSettingListBox()
    CAknPopupSettingList* popSettingList = 
        iSettingPage->PopupSettingListBox();
    AssertTrueL( ETrue, KPopupSettingListBox );
    TestFunctionsForSettingListL( popSettingList, queryValueText );

    delete iSettingPage;
    iSettingPage = NULL;
    CleanupStack::PopAndDestroy( queryValueText );
    CleanupStack::PopAndDestroy( textArray );
    CleanupStack::PopAndDestroy( item );
    }
    
// ---------------------------------------------------------------------------
// CBCTestPopupSettingPageCase::TestFunctionsForSettingListL
// ---------------------------------------------------------------------------
//
void CBCTestPopupSettingPageCase::TestFunctionsForSettingListL( 
    CAknPopupSettingList* aPopSettingList, MAknQueryValue* aQueryValueText )
    {
    // Invoke CAknPopupSettingList's SetQueryValueL()    
    aPopSettingList->SetQueryValueL( aQueryValueText );
    AssertTrueL( ETrue, KPSLSetQueryValueL );
    
    // Invoke CAknPopupSettingList's NumLines()  
    aPopSettingList->NumLines();
    AssertTrueL( ETrue, KPSLNumLines );
    
    // Invoke CAknPopupSettingList's SetPopupSettingListObserver()    
    aPopSettingList->SetPopupSettingListObserver( iSettingPage );
    AssertTrueL( ETrue, KPSLSetPopupSettingListObserver );    
    
    // Invoke CAknPopupSettingList's SetAllowsUserDefinedEntry()    
    aPopSettingList->SetAllowsUserDefinedEntry( EFalse );
    aPopSettingList->SetAllowsUserDefinedEntry( ETrue );
    AssertTrueL( ETrue, KPopupSettingListSetAllowsUserDefinedEntry );

    // Invoke CAknPopupSettingList's SetShowIndicators()    
    aPopSettingList->SetShowIndicators( ETrue );
    AssertTrueL( ETrue, KPopupSettingListSetShowIndicators );

    // Invoke CAknPopupSettingList's HandlePointerEventL()    
    TPointerEvent pointEvent;
    pointEvent.iType = TPointerEvent::ESwitchOn;
    aPopSettingList->HandlePointerEventL( pointEvent );
    AssertTrueL( ETrue, KPopupSettingListHandlePointerEventL );

    // Invoke CAknPopupSettingList's HandleResourceChange()    
    aPopSettingList->HandleResourceChange( 0 );
    AssertTrueL( ETrue, KPopupSettingListHandleResourceChange );
        
    CBCTestSubAknPopupSettingList* subPopSettingList = 
         static_cast<CBCTestSubAknPopupSettingList*> ( aPopSettingList );

    // Invoke CAknPopupSettingList's CreateMenuListL()    
    subPopSettingList->CreateMenuListL();
    AssertTrueL( ETrue, KPopupSettingListCreateMenuListL );
    
    // Invoke CAknPopupSettingList's ActivateMenuListL()    
    subPopSettingList->ActivateMenuListL();
    AssertTrueL( ETrue, KPopupSettingListActivateMenuListL );
    
    // Invoke CAknPopupSettingList's DestroyMenuList()    
    subPopSettingList->DestroyMenuList();
    AssertTrueL( ETrue, KPopupSettingListDestroyMenuList );
    
    // Invoke CAknPopupSettingList's ConfigureMenuListL()    
    subPopSettingList->ConfigureMenuListL();
    AssertTrueL( ETrue, KPopupSettingListConfigureMenuListL );   
    
    // Invoke CAknPopupSettingList's HandleListBoxEventL()
    CEikTextListBox* listBox = new( ELeave ) CAknSinglePopupMenuStyleListBox;
    CleanupStack::PushL( listBox );    
    subPopSettingList->HandleListBoxEventL( listBox, 
        MEikListBoxObserver::EEventItemClicked );
    AssertTrueL( ETrue, KPopupSettingListHandleListBoxEventL );
    CleanupStack::PopAndDestroy( listBox );     
 
     // Invoke CAknPopupSettingList's CAknPopupSettingList()   
    CAknPopupSettingList* popupSettingList = 
        new( ELeave ) CAknPopupSettingList();          
    AssertNotNullL( popupSettingList, KCAknPopupSettingList );  
    CleanupStack::PushL( popupSettingList );
    CleanupStack::PopAndDestroy( popupSettingList );
    
    }

// ---------------------------------------------------------------------------
// CBCTestPopupSettingPageCase::TestFunctionForPopLayoutsL
// ---------------------------------------------------------------------------
//
void CBCTestPopupSettingPageCase::TestFunctionForPopLayoutsL()
    {
    CEikTextListBox* list = new( ELeave ) CAknSinglePopupMenuStyleListBox;
    CleanupStack::PushL( list );

    CBCTestSubAknPopupList* popupList = ( CBCTestSubAknPopupList* ) 
        CBCTestSubAknPopupList::NewL( list, R_AVKON_SOFTKEYS_SELECT_CANCEL,
        AknPopupLayouts::EMenuWindow );
    CleanupStack::PushL( popupList );

    popupList->SetMaximumHeight( KTwo );

    list->ConstructL( popupList, CEikListBox::ELeftDownInViewRect );
    list->CreateScrollBarFrameL( ETrue );
    list->ScrollBarFrame()->SetScrollBarVisibilityL(
        CEikScrollBarFrame::EOff, CEikScrollBarFrame::EAuto );

    CDesCArray* items =
        iEikEnv->ReadDesCArrayResourceL( R_BCTESTPOPUPS_EIGHT_TEXT_ARRAY );

    CTextListBoxModel* model = list->Model();
    model->SetItemTextArray( items );
    model->SetOwnershipType( ELbmOwnsItemArray );

    TAknPopupLayoutsNode lst = { 0, EListNode, popupList->ListBox() };
    TAknPopupLayoutsNode heading = { &lst, 
        EHeadingNode, popupList->Heading() };
    TAknPopupLayoutsNode windowOwning = { &heading, 
        EWindowOwningNode, popupList };
    TAknPopupLayoutsNode findPane =
        { &windowOwning, EFindBoxNode, ( CCoeControl* ) popupList->FindBox() };
    TAknPopupLayoutsNode *listBegin = &findPane;

    AknPopupLayouts::HandleSizeChanged( popupList->Layout(),
        AknPopupLayouts::EMenuWindow,
        listBegin );
    AssertTrueL( ETrue, KLayoutHandleSizeChanged );

    AknPopupLayouts::HandleSizeChanged(
        popupList->Layout(),
        AknPopupLayouts::EMenuWindow,
        popupList->Heading(),
        popupList->ListBox(),
        popupList
        );
    AssertTrueL( ETrue, KLayoutHandleSizeChanged );

    AknPopupLayouts::ModifyWindowGraphicForHeading( popupList->Layout() );
    AssertTrueL( ETrue, KLayoutModifyWindowGraphicForHeading );

    AknPopupLayouts::ModifyWindowGraphicForMessageBox( 
        popupList->Layout(), KTwo );
    AknPopupLayouts::ModifyWindowGraphicForMessageBox( 
        popupList->Layout(), KThree );        
    AssertTrueL( ETrue, KLayoutModifyWindowGraphicForMessageBox );

    TRect rect;

    AknPopupLayouts::CalcPopupMenuWindow( popupList->Layout(), rect, KTwo );
    AssertTrueL( ETrue, KLayoutCalcPopupMenuWindow );

    AknPopupLayouts::CalcPopupMenuGraphicWindow( popupList->Layout(), 
                                                 rect, KTwo );
    AssertTrueL( ETrue, KLayoutCalcPopupMenuGraphicWindow );

    AknPopupLayouts::CalcPopupMenuGraphicHeadingWindow( popupList->Layout(),
                                                        rect, KTwo );
    AssertTrueL( ETrue, KLayoutCalcPopupMenuGraphicHeadingWindow );

    AknPopupLayouts::CalcPopupMenuDoubleWindow( popupList->Layout(), 
                                                rect, KTwo );
    AknPopupLayouts::CalcPopupMenuDoubleWindow( popupList->Layout(), 
                                                rect, KOne );                                                
    AssertTrueL( ETrue, KLayoutCalcPopupMenuDoubleWindow );

    AknPopupLayouts::CalcPopupMenuDoubleLargeGraphicWindow(
        popupList->Layout(),
        rect,
        KTwo );
    AknPopupLayouts::CalcPopupMenuDoubleLargeGraphicWindow(
        popupList->Layout(),
        rect,
        KOne ); 
               
    AssertTrueL( ETrue, KLayoutCalcPopupMenuDoubleLargeGraphicWindow );

    AknPopupLayouts::CalcPopupSNoteGroupWindow( popupList->Layout(), 
                                                rect, KOne );
    AssertTrueL( ETrue, KLayoutCalcPopupSNoteGroupWindow );

    AknPopupLayouts::SetupMenuPopupWindow( popupList->Layout(), KOne, ETrue );
    AssertTrueL( ETrue, KLayoutSetupMenuPopupWindow );

    AknPopupLayouts::SetupPopupMenuGraphicWindow( popupList->Layout(), 
                                                  KOne, ETrue );
    AssertTrueL( ETrue, KLayoutSetupPopupMenuGraphicWindow );

    AknPopupLayouts::SetupPopupMenuGraphicHeadingWindow( popupList->Layout(),
                                                         KOne, ETrue );
    AssertTrueL( ETrue, KLayoutSetupPopupMenuGraphicHeadingWindow );

    AknPopupLayouts::SetupPopupMenuDoubleWindow( popupList->Layout(), 
                                                 KOne, ETrue );
    AssertTrueL( ETrue, KLayoutSetupPopupMenuDoubleWindow );

    AknPopupLayouts::SetupImageSelectionMenuPopupWindow( popupList->Layout(),
                                                         KOne, ETrue );
    AssertTrueL( ETrue, KLayoutSetupImageSelectionMenuPopupWindow );

    AknPopupLayouts::SetupPopupSNoteGroupWindow( popupList->Layout(), 
                                                 KOne, ETrue );
    AssertTrueL( ETrue, KLayoutSetupPopupSNoteGroupWindow );

    AknPopupLayouts::HandleSizeAndPositionOfComponents(
        popupList->Layout(),
        popupList->ListBox(),
        popupList->Heading() );
    AssertTrueL( ETrue, KLayoutHandleSizeAndPositionOfComponents );

    AknPopupLayouts::SetupDefaults( popupList->Layout() );
    AssertTrueL( ETrue, KLayoutSetupDefaults );

    rect = AknPopupLayouts::WindowRect( popupList->Layout() );
    AssertTrueL( ETrue, KLayoutWindowRectA );

    rect = AknPopupLayouts::MenuRect( popupList->Layout() );
    AssertTrueL( ETrue, KLayoutMenuRect );

    TInt value = 1;
    AknPopupLayouts::CheckRange( value, KTwo, KThree );
    value = 5;    
    AknPopupLayouts::CheckRange( value, KOne, KThree );
    AssertTrueL( ETrue, KLayoutCheckRange );

    AknPopupLayouts::MenuPopupWindowGraphics( popupList->Layout() );
    AssertTrueL( ETrue, KLayoutMenuPopupWindowGraphics );

    CleanupStack::PopAndDestroy( popupList ); // listBox and popupList
    CleanupStack::PopAndDestroy( list );
    }














