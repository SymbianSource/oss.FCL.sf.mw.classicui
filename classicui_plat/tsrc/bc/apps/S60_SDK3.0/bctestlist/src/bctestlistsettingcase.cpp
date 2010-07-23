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
* Description:         test case for setting list box classes
*
*/









#include <aknlists.h>

#include "bctestlistsettingcase.h"
#include "bctestlistcontainer.h"
#include "bctestlist.hrh"
#include <bctestlist.rsg>
#include <bctestlist.mbg>

_LIT( KSettingCreate1, "Create CAknSettingStyleListBox" );
_LIT( KSettingCreate2, "Create CAknSettingNumberStyleListBox" );

_LIT( KSettingTest1, "CAknSettingStyleListBox::SizeChanged" );
_LIT( KSettingTest2, "CAknSettingStyleListBox::MinimumSize" );
_LIT( KSettingTest3, "CAknSettingStyleListBox::HandlePointerEventL" );
_LIT( KSettingItemDrawer, "CSettingsListBoxItemDrawer::DrawText" );

_LIT( KSettingNumberTest1, "CAknSettingNumberStyleListBox::SizeChanged" );
_LIT( KSettingNumberTest2, "CAknSettingNumberStyleListBox::MinimumSize" );
_LIT( KSettingNumberTest3, "CAknSettingNumberStyleListBox::HandlePointerEventL" );

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestListSettingCase* CBCTestListSettingCase::NewL( 
    CBCTestListContainer* aContainer, CEikonEnv* aEikEnv )
    {
    CBCTestListSettingCase* self = new( ELeave ) CBCTestListSettingCase( 
        aContainer, aEikEnv );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }
    
// ---------------------------------------------------------------------------
// C++ default constructor
// ---------------------------------------------------------------------------
//
CBCTestListSettingCase::CBCTestListSettingCase( 
    CBCTestListContainer* aContainer, CEikonEnv* aEikEnv )
    : CBCTestListBaseCase( aContainer, aEikEnv )
    {    
    }
    
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestListSettingCase::~CBCTestListSettingCase()
    {    
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestListSettingCase::ConstructL()
    {    
    BuildScriptL();
    }
    
// ---------------------------------------------------------------------------
// CBCTestListSettingCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestListSettingCase::BuildScriptL()
    {    
    for ( TInt i=0; i <= EBCTestCmdOutline25 - EBCTestCmdOutline23; i++ )
        {
        AddTestL( LeftCBA, REP( Down, 2 ), KeyOK, TEND );
        AddTestL( REP( Down, i ), KeyOK, TEND );
        }      
    }
    
// ---------------------------------------------------------------------------
// CBCTestListSettingCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestListSettingCase::RunL( TInt aCmd )
    {    
    if ( aCmd < EBCTestCmdOutline23 ||
         aCmd > EBCTestCmdOutline25 )
        {
        return;
        }
    iOutlineId = aCmd;
    ReleaseCase();
    PrepareCaseL( aCmd );
    TestSettingListL( aCmd );    
    }
    
// ---------------------------------------------------------------------------
// CBCTestListSettingCase::PrepareCaseL
// ---------------------------------------------------------------------------
//
void CBCTestListSettingCase::PrepareCaseL( TInt aCmd )
    {    
    TInt resourceId( KBCTestListInitListResourceId );    
    TBool useGraphics( EFalse );

    switch ( aCmd )
        {        
        case EBCTestCmdOutline23:  
            resourceId = R_BCTESTLIST_SETTING_ADD_RM;
            useGraphics = ETrue;          
            iListBox = new( ELeave ) CAknSettingStyleListBox();
            AssertNotNullL( iListBox, KSettingCreate1 );
            break;
        case EBCTestCmdOutline24:
            resourceId = R_BCTESTLIST_SETTING_NUMBER;            
            useGraphics = ETrue;
            iListBox = new( ELeave ) CAknSettingNumberStyleListBox();
            AssertNotNullL( iListBox, KSettingCreate2 );
            break;
            
        default:
            break;
        }

    if ( iListBox )
        {        
        if ( resourceId != 0 )
            {
            SetListBoxFromResourceL( iListBox, resourceId );            
            }
        else
            {            
            SetListBoxFromInnerDescriptionL( iListBox );            
            }
               
        if ( useGraphics )
            {
            SetGraphicIconL( iListBox );
            }            
        
        iContainer->SetControl( iListBox );        
        }    
    }
    
// ---------------------------------------------------------------------------
// CBCTestListSettingCase::ReleaseCase
// ---------------------------------------------------------------------------
//
void CBCTestListSettingCase::ReleaseCase()
    {
    iContainer->ResetControl();    
    iListBox = NULL;
    }
    
// ---------------------------------------------------------------------------
// CBCTestListSettingCase::TestSettingListL
// ---------------------------------------------------------------------------
//
void CBCTestListSettingCase::TestSettingListL( TInt aCmd )
    {
    if ( !iListBox && aCmd != EBCTestCmdOutline25 )
        {
        return;
        }
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos(0, 30);
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    
    TSize size;
    switch ( aCmd )
        {
        case EBCTestCmdOutline23:
            {
            CAknSettingStyleListBox* listbox = 
                static_cast<CAknSettingStyleListBox*>( iListBox );           
            listbox->SizeChanged();
            AssertTrueL( ETrue, KSettingTest1 );            
            size = listbox->MinimumSize();
            AssertTrueL( ETrue, KSettingTest2 );            
            listbox->HandlePointerEventL( event );
            AssertTrueL( ETrue, KSettingTest3 );            
            
            CSettingsListBoxItemDrawer* itemDrawer = listbox->ItemDrawer();            
            TRect rect( TPoint( 0, 0 ), TSize( 50, 30 ) );
            itemDrawer->CSettingsListBoxItemDrawer::DrawItemText( 
                0, rect, ETrue, EFalse, EFalse );
            AssertTrueL( ETrue, KSettingItemDrawer );         
            }
            break;
        case EBCTestCmdOutline24:
            {
            CAknSettingNumberStyleListBox* listbox = 
                static_cast<CAknSettingNumberStyleListBox*>( iListBox );           
            listbox->SizeChanged();
            AssertTrueL( ETrue, KSettingNumberTest1 );            
            size = listbox->MinimumSize();
            AssertTrueL( ETrue, KSettingNumberTest2 );            
            listbox->HandlePointerEventL( event );
            AssertTrueL( ETrue, KSettingNumberTest3 );            
            }
            break;
        case EBCTestCmdOutline25:
            {
            _LIT( KItemText, "Item1" );
            TBuf<20> temp( KItemText );            
            
            CSelectableItem* item = new( ELeave ) CSelectableItem( temp, EFalse );
            CleanupStack::PushL( item );            
            item->ConstructL();
            
            CSelectionItemList* itemList = new( ELeave ) CSelectionItemList( 1 );
            CleanupStack::PushL( itemList );            
            itemList->AppendL( item );
            
            CBCTestCheckSettingPage* settingPage = new( ELeave )
                CBCTestCheckSettingPage( R_BCTESTLIST_CHECKBOX_SETTING_PAGE,
                     itemList );
            CleanupStack::PushL( settingPage );
            
            settingPage->ConstructL();            
            
            settingPage->CAknListBoxSettingPage::CheckAndSetDataValidity();
            _LIT( KSettingPage1, "CAknListBoxSettingPage::CheckAndSetDataValidity" );
            AssertTrueL( ETrue, KSettingPage1 );
            
            settingPage->CAknListBoxSettingPage::SizeChanged();
            _LIT( KSettingPage2, "CAknListBoxSettingPage::SizeChanged" );
            AssertTrueL( ETrue, KSettingPage2 );
            
            settingPage->CAknListBoxSettingPage::UpdateCbaL();
            _LIT( KSettingPage3, "CAknListBoxSettingPage::UpdateCbaL" );
            AssertTrueL( ETrue, KSettingPage3 );
            
            settingPage->CAknListBoxSettingPage::HandleListBoxEventL(
                settingPage->ListBoxControl(), 
                MEikListBoxObserver::EEventItemClicked );
            _LIT( KSettingPage4, "CAknListBoxSettingPage::HandleListBoxEventL" );
            AssertTrueL( ETrue, KSettingPage4 );
            
            iContainer->ActivateGc();
            settingPage->CAknListBoxSettingPage::Draw( iContainer->Rect() );
            _LIT( KSettingPage5, "CAknListBoxSettingPage::Draw" );
            AssertTrueL( ETrue, KSettingPage5 );
            iContainer->DeactivateGc();
            
            CleanupStack::PopAndDestroy( settingPage );
            CleanupStack::PopAndDestroy( itemList );
            CleanupStack::PopAndDestroy( item );
            }
            break;                            
        default:
            break;
        }        
        
    }
    
// ---------------------------------------------------------------------------
// CBCTestListSettingCase::GraphicIconL
// ---------------------------------------------------------------------------
//
void CBCTestListSettingCase::GraphicIconL( CArrayPtr<CGulIcon>* aIcons )
    {
    if ( aIcons )
        {
        // Appends icon according to iOutlineId.
        switch ( iOutlineId )
            {            
            case EBCTestCmdOutline23:
            case EBCTestCmdOutline24:
                CreateIconAndAddToArrayL(
                    aIcons, KBCTestListMifFileName,
                    EMbmBctestlistQgn_indi_marked_add,
                    EMbmBctestlistQgn_indi_marked_add_mask );
                CreateIconAndAddToArrayL(
                    aIcons, KBCTestListMbmFileName,
                    EMbmBctestlistGolgo2,
                    EMbmBctestlistGolgo2_mask );                    
                break;
           
            default:
                break;
            }
        }
    }

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// C++ constructor
// ---------------------------------------------------------------------------
//
CBCTestCheckSettingPage::CBCTestCheckSettingPage( TInt aResourceId, 
    CSelectionItemList* aItemArray ) : 
    CAknCheckBoxSettingPage( aResourceId, aItemArray )
    {    
    }
