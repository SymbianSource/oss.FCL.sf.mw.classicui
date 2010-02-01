/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  ?Description
*
*/


#include <w32std.h>
#include <coemain.h>
#include <coecntrl.h>
#include <finditemdialog.h>
#include <finditemmenu.h>
#include <eikmenup.h> 
#include <eikrted.h> 
#include <findutil.h>
#include <gulbordr.h>
#include <coeaui.h>
#include <txtfrmat.h>

#include <bctestdomavkonpsln.rsg>
#include "bctestdomfindcase.h"
#include "bctestdomavkonpslncontainer.h"
#include "bctestdomavkonpslnext.h"
#include "bctestdomavkonpsln.hrh"

//CONSTANT

const TInt KDesLength = 32;
_LIT( KUrlDes, "http://www.symbian.com" );
_LIT( KNumberDes, "callback73644444");

// =========================== MEMBER FUNCTIONS =============================

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestDomFindCase* CBCTestDomFindCase::NewL( CBCTestDomAvkonPslnContainer* 
    aContainer )
    {
    CBCTestDomFindCase* self = new( ELeave ) CBCTestDomFindCase( 
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
CBCTestDomFindCase::CBCTestDomFindCase( CBCTestDomAvkonPslnContainer* 
    aContainer )
    : iContainer( aContainer )
    {    
    }
    
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestDomFindCase::~CBCTestDomFindCase()
    {  
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestDomFindCase::ConstructL()
    {    
    BuildScriptL();    
    }
    
// ---------------------------------------------------------------------------
// CBCTestDomFindCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestDomFindCase::BuildScriptL()
    { 
    const TInt scripts[] =
        {
        LeftCBA,
        REP( Down, 2 ),
        LeftCBA,
        
        WAIT(3),
        RightCBA,
        KeyOK,
        WAIT(3),
        KeyOK
        };
    AddTestScriptL( scripts, sizeof(scripts)/sizeof(TInt) );   
    }
    
// ---------------------------------------------------------------------------
// CBCTestDomFindCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestDomFindCase::RunL( TInt aCmd )
    {
    if ( aCmd != EBCTestCmdOutline3 )
        {
        return;
        }
    switch ( aCmd )  
        {
        case EBCTestCmdOutline3:
            TestFindItemDialogL();
            TestFindItemMenuL();
            TestFindUtilL();
            TestItemFinderL();
            break;
        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// CBCTestDomEikCase::TestFindItemDialogL()
// ---------------------------------------------------------------------------
//    
void CBCTestDomFindCase::TestFindItemDialogL()
{
    _LIT( KNewL, "CFindItemDialog::NewL invoked" );
    _LIT( KOfferKeyEventL, "CFindItemDialog::OfferKeyEventL invoked" );
    _LIT( KProcessCommandL, "CFindItemDialog::ProcessCommandL invoked" );
    _LIT( KExecuteLD, "CFindItemDialog::ExecuteLD invoked" );
              
    CFindItemDialog* dlg = CFindItemDialog::NewL( KUrlDes, 
                           CFindItemEngine::EFindItemSearchURLBin );
    CleanupStack::PushL( dlg );
    AssertNotNullL( dlg, KNewL );
    
    TKeyEvent keyEvent = { EKeyPause, EStdKeySpace, 0, 0  };
    dlg->OfferKeyEventL( keyEvent, EEventKey );
    AssertTrueL( ETrue, KOfferKeyEventL );
  

    CCoeEnv::Static()->AppUi()->AddToStackL( dlg );
    dlg->ProcessCommandL( EAknSoftkeyHide );
    AssertTrueL( ETrue, KProcessCommandL );
    CCoeEnv::Static()->AppUi()->RemoveFromStack( dlg );
    
    CleanupStack::Pop( dlg );
    dlg->ExecuteLD();
    AssertTrueL( ETrue, KExecuteLD );
}

// ---------------------------------------------------------------------------
// CBCTestDomEikCase::TestFindItemMenuL()
// ---------------------------------------------------------------------------
//    
void CBCTestDomFindCase::TestFindItemMenuL()
{
    _LIT( KNewL, "CFindItemMenu::NewL invoked" );
    _LIT( KNewLC, "CFindItemMenu::NewLC invoked" );
    _LIT( KDes, "CFindItemMenu::~CFindItemMenu invoked" );
    
    CFindItemMenu* menu = CFindItemMenu::NewL( 0 );
    CleanupStack::PushL( menu );
    
    AssertNotNullL( menu, KNewL );
    CleanupStack::PopAndDestroy( menu );
    AssertTrueL( ETrue, KDes );
    
    menu = CFindItemMenu::NewLC( R_BCTESTDOMAVKONPSLN_CASE_MENU );
    AssertNotNullL( menu, KNewLC );
    
    CAknForm* frm = new (ELeave) CAknForm;  
    CleanupStack::PushL( frm );
    frm->ConstructL();
    
    CEikMenuPane* pane = new ( ELeave ) CEikMenuPane( frm );
    CleanupStack::PushL( pane );
    pane->ConstructL( pane,0 );
    
    _LIT( KDisplayFindItemMenuItemL, 
        "CFindItemMenu::DisplayFindItemMenuItemL invoked" );
    menu->DisplayFindItemMenuItemL( *pane, 0 );
    AssertTrueL( ETrue, KDisplayFindItemMenuItemL );
    
    _LIT( KDisplayFindItemCascadeMenuL, 
        "CFindItemMenu::DisplayFindItemCascadeMenuL invoked" );
    menu->DisplayFindItemCascadeMenuL( *pane );
    AssertTrueL( ETrue, KDisplayFindItemCascadeMenuL );
    
    _LIT( KCommandIsValidL, "CFindItemMenu::CommandIsValidL invoked" );
    menu->CommandIsValidL( 0 );
    AssertTrueL( ETrue, KCommandIsValidL );
    
    _LIT( KSearchCase, "CFindItemMenu::SearchCase invoked" );
    menu->SearchCase( R_BCTESTDOMAVKONPSLN_CASE_MENU+1 );
    AssertTrueL( ETrue, KSearchCase );
    
    _LIT( KUpdateItemFinderMenuL, "CFindItemMenu::UpdateItemFinderMenuL invoked" );
    menu->UpdateItemFinderMenuL( R_BCTESTDOMAVKONPSLN_CASE_MENU, pane );
    AssertTrueL( ETrue, KUpdateItemFinderMenuL );
    
    _LIT( KHandleItemFinderCommandL, 
        "CFindItemMenu::HandleItemFinderCommandL invoked" );
    menu->HandleItemFinderCommandL( 0 );
    AssertTrueL( ETrue, KHandleItemFinderCommandL );
    
    _LIT( KAttachItemFinderMenuL, 
        "CFindItemMenu::HandleItemFinderCommandL invoked" );
    menu->AttachItemFinderMenuL( R_BCTESTDOMAVKONPSLN_CASE_MENU );
    AssertTrueL( ETrue, KAttachItemFinderMenuL );
    
    _LIT( KSetCallbackNumber, 
        "CFindItemMenu::SetCallbackNumber invoked" );
    
    menu->SetCallbackNumber( KNumberDes );
    AssertTrueL( ETrue, KSetCallbackNumber );
    
    _LIT( KHandleCallL, 
        "CFindItemMenu::HandleCallL invoked" );
    menu->HandleCallL( KUrlDes );
    AssertTrueL( ETrue, KHandleCallL );
    
    _LIT( KHandleVoIPCallL, 
        "CFindItemMenu::HandleCallL invoked" );
    menu->HandleVoIPCallL( KUrlDes );
    AssertTrueL( ETrue, KHandleVoIPCallL );
    
    _LIT( KSetSenderHighlightStatus, 
        "CFindItemMenu::SetSenderHighlightStatus invoked" );
    menu->SetSenderHighlightStatus( ETrue );
    AssertTrueL( ETrue, KSetSenderHighlightStatus );
    
    _LIT( KSetSenderDisplayText, 
        "CFindItemMenu::SetSenderDisplayText invoked" );
    menu->SetSenderDisplayText( KNumberDes );
    AssertTrueL( ETrue, KSetSenderDisplayText );
    
    _LIT( KAddItemFindMenuL, 
        "CFindItemMenu::AddItemFindMenuL() invoked" );

    CItemFinder* finder = CItemFinder::NewL();
    CleanupStack::PushL( finder );
    menu->AddItemFindMenuL( finder, pane, 0, KNumberDes );
    AssertTrueL( ETrue, KAddItemFindMenuL );
    
    _LIT( KSetSenderDescriptorType, 
        "CFindItemMenu::SetSenderDescriptorType() invoked" );
          
    menu->SetSenderDescriptorType( CItemFinder::EUrlAddress );
    AssertTrueL( ETrue, KSetSenderDescriptorType );
    
    CleanupStack::PopAndDestroy( finder );
    CleanupStack::PopAndDestroy( pane );
    CleanupStack::PopAndDestroy( frm );
    CleanupStack::PopAndDestroy( menu );
}

// ---------------------------------------------------------------------------
// CBCTestDomEikCase::TestFindUtilL()
// ---------------------------------------------------------------------------
//    
void CBCTestDomFindCase::TestFindUtilL()
    {
    _LIT( KNewL, "CFindUtil::NewL() invoked" );
    _LIT( KDes, "CFindUtil::~CFindUtil() invoked" );
    CFindUtil* util = CFindUtil::NewL();
    CleanupStack::PushL( util );
    AssertNotNullL( util, KNewL );
    
    CleanupStack::Pop( util );
    delete util;
    AssertTrueL( ETrue, KDes );
    }

// ---------------------------------------------------------------------------
// CBCTestDomEikCase::TestItemFinderL()
// ---------------------------------------------------------------------------
//    
void CBCTestDomFindCase::TestItemFinderL()
    {
    
    _LIT( KNewL, "CItemFinder::NewL() invoked" );
    _LIT( KNextItemOrScrollL, "CItemFinder::NextItemOrScrollL() invoked" );
    _LIT( KSetFindModeL, "CItemFinder::SetFindModeL() invoked" );    
    _LIT( KSetEditor, "CItemFinder::SetEditor() invoked" );
    _LIT( KParseThisText, "CItemFinder::ParseThisText() invoked" );
    _LIT( KCreateDoItText, "CItemFinder::CreateDoItText() invoked" );
    _LIT( KActivateThisTextL, "CItemFinder::ActivateThisTextL() invoked" );
    _LIT( KReformatOnRecognise, "CItemFinder::ReformatOnRecognise() invoked" );
    _LIT( KReformatOnRollover, "CItemFinder::ReformatOnRollover() invoked" );
    _LIT( KGetRecogniseFormat, "CItemFinder::GetRecogniseFormat() invoked" );
    _LIT( KGetRolloverFormat, "CItemFinder::GetRolloverFormat() invoked" );
    _LIT( KConfirmCursorOverTag, "CItemFinder::ConfirmCursorOverTag() invoked" );
    _LIT( KMParser_Reserved_2, "CItemFinder::MParser_Reserved_2() invoked" );
    _LIT( KPositionOfNextItem, "CItemFinder::PositionOfNextItem() invoked" );
    _LIT( KResetCurrentItem, "CItemFinder::ResetCurrentItem() invoked" );
    _LIT( KResolveAndSetItemTypeL, "CItemFinder::ResolveAndSetItemTypeL() invoked" );
    _LIT( KAddObserver, "CItemFinder::AddObserver() invoked" );
    _LIT( KItemWasTappedL, "CItemFinder::ItemWasTappedL() invoked" );
    _LIT( KSetExternalLinks, "CItemFinder::SetExternalLinks() invoked" );
    _LIT( KDes, "CItemFinder::~CItemFinder() invoked" );
    _LIT( KRelease, "CItemFinder::Release() invoked" );
    _LIT( KCurrentSelection, "CItemFinder::CurrentSelection() invoked" );
    _LIT( KCurrentItemExt, "CItemFinder::CurrentItemExt() invoked" );
    
    
    CItemFinder* finder = CItemFinder::NewL();
    CleanupStack::PushL( finder );
    AssertNotNullL( finder, KNewL );
    
    finder->NextItemOrScrollL( CItemFinder::EInit );
    AssertTrueL( ETrue, KNextItemOrScrollL );
    
    finder->SetFindModeL( 0 );
    AssertTrueL( ETrue, KSetFindModeL );
    
    TGulBorder gulBorder;
    CEikRichTextEditor* editor = new ( ELeave ) CEikRichTextEditor ( gulBorder );
    CleanupStack::PushL( editor );
    editor->ConstructL( iContainer, 0, 0, 0 );
    
    finder->SetEditor( &editor );
    AssertTrueL( ETrue, KSetEditor );
    
    TInt tag(0), len(0);
    CRichText* richText = editor->RichText();  
    finder->ParseThisText( *richText, ETrue, 1, 1, tag, len ) ;
    AssertTrueL( ETrue, KParseThisText );
    
    finder->CreateDoItText( *richText, 1, 1 );
    AssertTrueL( ETrue, KCreateDoItText );
    
    finder->ActivateThisTextL( *richText, 1, 1 );
    AssertTrueL( ETrue, KActivateThisTextL );
    
    finder->ReformatOnRecognise();
    AssertTrueL( ETrue, KReformatOnRecognise );
    
    finder->ReformatOnRollover();
    AssertTrueL( ETrue, KReformatOnRollover );
    
    TCharFormat format;
    finder->GetRecogniseFormat( format );
    AssertTrueL( ETrue, KGetRecogniseFormat );
    
    finder->GetRolloverFormat( format );
    AssertTrueL( ETrue, KGetRolloverFormat );
    
    finder->ConfirmCursorOverTag( *richText, 1, 1, 1 );
    AssertTrueL( ETrue, KConfirmCursorOverTag );
    
    finder->MParser_Reserved_2();
    AssertTrueL( ETrue, KMParser_Reserved_2 );
    
    finder->PositionOfNextItem( CItemFinder::EInit );
    AssertTrueL( ETrue, KPositionOfNextItem );
    
    finder->ResetCurrentItem();
    AssertTrueL( ETrue, KResetCurrentItem );
    
    finder->ResolveAndSetItemTypeL();
    AssertTrueL( ETrue, KResolveAndSetItemTypeL );
    
    CItemFinderObserverExt* observer = new ( ELeave ) CItemFinderObserverExt;
    CleanupStack::PushL( observer );
    
    finder->AddObserver( *observer );
    AssertTrueL( ETrue, KAddObserver );
    
    TPoint point( 0, 0 );
    finder->ItemWasTappedL( point );
    AssertTrueL( ETrue, KItemWasTappedL );
    
    TBuf<KDesLength> des( KUrlDes );
    CItemFinder::CFindItemExt* findex = new ( ELeave ) CItemFinder::CFindItemExt;
    CleanupStack::PushL( findex );
    
    findex->iItemType = CItemFinder::EUrlAddress;
    findex->iItemDescriptor = des.AllocL();
    CArrayPtrFlat<CItemFinder::CFindItemExt>* links = 
        new ( ELeave ) CArrayPtrFlat<CItemFinder::CFindItemExt>( 1 );
    CleanupStack::PushL( links );
    links->AppendL( findex );
    
    finder->SetExternalLinks( links );
    AssertTrueL( ETrue, KSetExternalLinks );
    
    finder->CurrentItemExt();
    AssertTrueL( ETrue, KCurrentItemExt );
    
    finder->CurrentSelection();
    AssertTrueL( ETrue, KCurrentSelection );
    
    finder->Release();
    AssertTrueL( ETrue, KRelease );
    
    CleanupStack::PopAndDestroy( links );
    CleanupStack::PopAndDestroy( findex );
    CleanupStack::PopAndDestroy( observer );
    CleanupStack::PopAndDestroy( editor );
    CleanupStack::PopAndDestroy( finder );

    AssertTrueL( ETrue, KDes );
    }
    //end of file
