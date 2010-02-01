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
* Description:         test case for popup list box classes
*
*/









#include <eikenv.h>
#include <eikapp.h>

#include "bctestlistpopupcase.h"
#include "bctestlistcontainer.h"
#include "bctestlist.hrh"
#include <bctestlist.rsg>
#include <bctestlist.mbg>

_LIT( KPopupCreate1, "Create CAknSinglePopupMenuStyleListBox" );
_LIT( KPopupCreate2, "Create CAknSingleGraphicPopupMenuStyleListBox" );
_LIT( KPopupCreate3, "Create CAknSingleGraphicBtPopupMenuStyleListBox" );
_LIT( KPopupCreate4, "Create CAknSingleHeadingPopupMenuStyleListBox" );
_LIT( KPopupCreate5, "Create CAknSingleGraphicHeadingPopupMenuStyleListBox" );
_LIT( KPopupCreate6, "Create CAknDoublePopupMenuStyleListBox" );
_LIT( KPopupCreate7, "Create CAknSinglePopupSubmenuStyleListBox" );
_LIT( KPopupCreate8, "Create CAknDoubleLargeGraphicPopupMenuStyleListBox" );
_LIT( KPopupCreate9, "Create CAknDouble2PopupMenuStyleListBox" );
_LIT( KPopupCreate10, "Create CAknSingle2GraphicPopupMenuStyleListBox" );
_LIT( KPopupCreate11, "Create CAknDoubleGraphicPopupMenuStyleListBox" );
_LIT( KPopupCreate12, "Create CAknSetStyleListBox" );
_LIT( KSetConstructWithWindow, "CAknSetStyleListBox::ConstructWithWindowL" );
_LIT( KPopupCreate13, "Create CAknFormGraphicStyleListBox" );
_LIT( KFormGraphicConstructWithWindow, "CAknFormGraphicStyleListBox::ConstructWithWindowL" );
_LIT( KPopupCreate14, "Create CAknFormGraphicWideStyleListBox" );

_LIT( KSinglePopupMenuTest1, "CAknSinglePopupMenuStyleListBox::SizeChanged" );
_LIT( KSinglePopupMenuTest2, "CAknSinglePopupMenuStyleListBox::MinimumSize" );
_LIT( KSinglePopupMenuTest3, "CAknSinglePopupMenuStyleListBox::HandlePointerEventL" );

_LIT( KSingleGraphicPopupMenuTest1, "CAknSingleGraphicPopupMenuStyleListBox::SizeChanged" );
_LIT( KSingleGraphicPopupMenuTest2, "CAknSingleGraphicPopupMenuStyleListBox::MinimumSize" );
_LIT( KSingleGraphicPopupMenuTest3, "CAknSingleGraphicPopupMenuStyleListBox::HandlePointerEventL" );

_LIT( KSingleGraphicBtPopupMenuTest1, "CAknSingleGraphicBtPopupMenuStyleListBox::SizeChanged" );
_LIT( KSingleGraphicBtPopupMenuTest2, "CAknSingleGraphicBtPopupMenuStyleListBox::HandlePointerEventL" );

_LIT( KSingleHeadingPopupMenuTest1, "CAknSingleHeadingPopupMenuStyleListBox::SizeChanged" );
_LIT( KSingleHeadingPopupMenuTest2, "CAknSingleHeadingPopupMenuStyleListBox::MinimumSize" );
_LIT( KSingleHeadingPopupMenuTest3, "CAknSingleHeadingPopupMenuStyleListBox::HandlePointerEventL" );

_LIT( KSingleGraphicHeadingPopupMenuTest1, "CAknSingleGraphicHeadingPopupMenuStyleListBox::SizeChanged" );
_LIT( KSingleGraphicHeadingPopupMenuTest2, "CAknSingleGraphicHeadingPopupMenuStyleListBox::MinimumSize" );
_LIT( KSingleGraphicHeadingPopupMenuTest3, "CAknSingleGraphicHeadingPopupMenuStyleListBox::HandlePointerEventL" );

_LIT( KDoublePopupMenuTest1, "CAknDoublePopupMenuStyleListBox::SizeChanged" );
_LIT( KDoublePopupMenuTest2, "CAknDoublePopupMenuStyleListBox::MinimumSize" );
_LIT( KDoublePopupMenuTest3, "CAknDoublePopupMenuStyleListBox::HandlePointerEventL" );

_LIT( KSinglePopupSubMenuTest1, "CAknSinglePopupSubmenuStyleListBox::SizeChanged" );
_LIT( KSinglePopupSubMenuTest2, "CAknSinglePopupSubmenuStyleListBox::MinimumSize" );
_LIT( KSinglePopupSubMenuTest3, "CAknSinglePopupSubmenuStyleListBox::HandlePointerEventL" );

_LIT( KDoubleLargeGraphicPopupMenuTest1, "CAknDoubleLargeGraphicPopupMenuStyleListBox::SizeChanged" );
_LIT( KDoubleLargeGraphicPopupMenuTest2, "CAknDoubleLargeGraphicPopupMenuStyleListBox::MinimumSize" );
_LIT( KDoubleLargeGraphicPopupMenuTest3, "CAknDoubleLargeGraphicPopupMenuStyleListBox::HandlePointerEventL" );

_LIT( KDouble2PopupMenuTest1, "CAknDouble2PopupMenuStyleListBox::SizeChanged" );
_LIT( KDouble2PopupMenuTest2, "CAknDouble2PopupMenuStyleListBox::MinimumSize" );
_LIT( KDouble2PopupMenuTest3, "CAknDouble2PopupMenuStyleListBox::HandlePointerEventL" );

_LIT( KSingle2GraphicPopupMenuTest1, "CAknSingle2GraphicPopupMenuStyleListBox::SizeChanged" );
_LIT( KSingle2GraphicPopupMenuTest2, "CAknSingle2GraphicPopupMenuStyleListBox::MinimumSize" );
_LIT( KSingle2GraphicPopupMenuTest3, "CAknSingle2GraphicPopupMenuStyleListBox::HandlePointerEventL" );

_LIT( KDoubleGraphicPopupMenuTest1, "CAknDoubleGraphicPopupMenuStyleListBox::SizeChanged" );
_LIT( KDoubleGraphicPopupMenuTest2, "CAknDoubleGraphicPopupMenuStyleListBox::MinimumSize" );
_LIT( KDoubleGraphicPopupMenuTest3, "CAknDoubleGraphicPopupMenuStyleListBox::HandlePointerEventL" );

_LIT( KSetTest1, "CAknSetStyleListBox::SizeChanged" );
_LIT( KSetTest2, "CAknSetStyleListBox::MinimumSize" );
_LIT( KSetTest3, "CAknSetStyleListBox::HandlePointerEventL" );
_LIT( KSetTest4, "CAknSetStyleListBox::MopSupplyObject" );
_LIT( KSetTest5, "CAknSetStyleListBox::Draw with empty list" );
_LIT( KSetTest6, "CAknSetStyleListBox::Draw with item" );

_LIT( KFormGraphicTest1, "CAknFormGraphicStyleListBox::SizeChanged" );
_LIT( KFormGraphicTest2, "CAknFormGraphicStyleListBox::MinimumSize" );
_LIT( KFormGraphicTest3, "CAknFormGraphicStyleListBox::AdjustRectHeightToWholeNumberOfItems" );
_LIT( KFormGraphicTest4, "CAknFormGraphicStyleListBox::HandlePointerEventL" );

_LIT( KFormGraphicWideTest1, "CAknFormGraphicWideStyleListBox::SizeChanged" );
_LIT( KFormGraphicWideTest2, "CAknFormGraphicWideStyleListBox::MinimumSize" );
_LIT( KFormGraphicWideTest3, "CAknFormGraphicWideStyleListBox::HandlePointerEventL" );

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestListPopupCase* CBCTestListPopupCase::NewL( 
    CBCTestListContainer* aContainer, CEikonEnv* aEikEnv )
    {
    CBCTestListPopupCase* self = new( ELeave ) CBCTestListPopupCase( 
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
CBCTestListPopupCase::CBCTestListPopupCase( CBCTestListContainer* aContainer,
    CEikonEnv* aEikEnv )
    : CBCTestListBaseCase( aContainer, aEikEnv )
    {    
    }
    
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestListPopupCase::~CBCTestListPopupCase()
    {    
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestListPopupCase::ConstructL()
    {    
    BuildScriptL();    
    }
    
// ---------------------------------------------------------------------------
// CBCTestListPopupCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestListPopupCase::BuildScriptL()
    {    
    for ( TInt i=0; i <= EBCTestCmdOutline39 - EBCTestCmdOutline26; i++ )
        {
        AddTestL( LeftCBA, REP( Down, 3 ), KeyOK, TEND );
        AddTestL( REP( Down, i ), KeyOK, TEND );
        }      
    }
    
// ---------------------------------------------------------------------------
// CBCTestListPopupCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestListPopupCase::RunL( TInt aCmd )
    {    
    if ( aCmd < EBCTestCmdOutline26 ||
         aCmd > EBCTestCmdOutline39 )
        {
        return;
        }
    iOutlineId = aCmd;
    ReleaseCase();
    PrepareCaseL( aCmd );
    TestPopupListL( aCmd );    
    }
    
// ---------------------------------------------------------------------------
// CBCTestListPopupCase::PrepareCaseL
// ---------------------------------------------------------------------------
//
void CBCTestListPopupCase::PrepareCaseL( TInt aCmd )
    {    
    TInt flags = EAknListBoxSelectionList | EAknListBoxViewerFlags;
    TBool useGraphics( EFalse );                       

    switch ( aCmd )
        {        
        case EBCTestCmdOutline26:
            {
            iListBox = new( ELeave ) CBCTestSinglePopupMenuStyleListBox();
            AssertNotNullL( iListBox, KPopupCreate1 );            
            }                   
            break;
        case EBCTestCmdOutline27:
            {
            iListBox = new( ELeave ) CBCTestSingleGraphicPopupMenuStyleListBox();
            AssertNotNullL( iListBox, KPopupCreate2 );
            }
            break;
        case EBCTestCmdOutline28:
            {
            iListBox = new( ELeave ) CAknSingleGraphicBtPopupMenuStyleListBox();
            AssertNotNullL( iListBox, KPopupCreate3 );
            }            
            break;
        case EBCTestCmdOutline29:
            {
            iListBox = new( ELeave ) CAknSingleHeadingPopupMenuStyleListBox();
            AssertNotNullL( iListBox, KPopupCreate4 );
            }            
            break;
        case EBCTestCmdOutline30:
            {
            iListBox = new( ELeave ) CAknSingleGraphicHeadingPopupMenuStyleListBox();
            AssertNotNullL( iListBox, KPopupCreate5 );
            }            
            break;
        case EBCTestCmdOutline31:
            {
            iListBox = new( ELeave ) CAknDoublePopupMenuStyleListBox();
            AssertNotNullL( iListBox, KPopupCreate6 );
            }            
            break;
        case EBCTestCmdOutline32:
            {
            iListBox = new( ELeave ) CAknSinglePopupSubmenuStyleListBox();
            AssertNotNullL( iListBox, KPopupCreate7 );
            }
            break;
        case EBCTestCmdOutline33:
            {
            iListBox = new( ELeave ) CAknDoubleLargeGraphicPopupMenuStyleListBox();
            AssertNotNullL( iListBox, KPopupCreate8 );
            }            
            break;
        case EBCTestCmdOutline34:
            {
            iListBox = new( ELeave ) CAknDouble2PopupMenuStyleListBox();
            AssertNotNullL( iListBox, KPopupCreate9 );
            }            
            break;
        case EBCTestCmdOutline35:
            {
            iListBox = new( ELeave ) CBCTestSingle2GraphicPopupMenuStyleListBox();
            AssertNotNullL( iListBox, KPopupCreate10 );
            }            
            break;
        case EBCTestCmdOutline36:
            {
            iListBox = new( ELeave ) CBCTestDoubleGraphicPopupMenuStyleListBox();
            AssertNotNullL( iListBox, KPopupCreate11 );
            }            
            break;
        case EBCTestCmdOutline37:
            {
            useGraphics = ETrue;
            iListBox = new( ELeave ) CAknSetStyleListBox();
            AssertNotNullL( iListBox, KPopupCreate12 );
            CAknSetStyleListBox* listbox = 
                static_cast<CAknSetStyleListBox*>( iListBox );
            listbox->ConstructWithWindowL( iContainer, flags );            
            AssertTrueL( ETrue, KSetConstructWithWindow );            
            }                       
            break;
        case EBCTestCmdOutline38:
            {
            useGraphics = ETrue;
            iListBox = new( ELeave ) CAknFormGraphicStyleListBox();
            AssertNotNullL( iListBox, KPopupCreate13 );
            CAknFormGraphicStyleListBox* listbox = 
                static_cast<CAknFormGraphicStyleListBox*>( iListBox );
            listbox->ConstructWithWindowL( iContainer, flags );
            AssertTrueL( ETrue, KFormGraphicConstructWithWindow );            
            }            
            break;
        case EBCTestCmdOutline39:
            {
            useGraphics = ETrue;
            iListBox = new( ELeave ) CAknFormGraphicWideStyleListBox();
            AssertNotNullL( iListBox, KPopupCreate14 );
            CAknFormGraphicWideStyleListBox* listbox = 
                static_cast<CAknFormGraphicWideStyleListBox*>( iListBox );
            listbox->ConstructWithWindowL( iContainer, flags );            
            }            
            break;
            
        default:
            break;
        }

    if ( iListBox )
        {
        
        if ( aCmd < EBCTestCmdOutline37 )            
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
// CBCTestListPopupCase::ReleaseCase
// ---------------------------------------------------------------------------
//
void CBCTestListPopupCase::ReleaseCase()
    {
    iContainer->ResetControl();    
    iListBox = NULL;
    }
    
// ---------------------------------------------------------------------------
// CBCTestListPopupCase::TestPopupListL
// ---------------------------------------------------------------------------
//
void CBCTestListPopupCase::TestPopupListL( TInt aCmd )
    {
    if ( !iListBox )
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
        case EBCTestCmdOutline26:
            {
            CBCTestSinglePopupMenuStyleListBox* listbox = 
                static_cast<CBCTestSinglePopupMenuStyleListBox*>( iListBox );           
            listbox->SizeChanged();
            AssertTrueL( ETrue, KSinglePopupMenuTest1 );            
            size = listbox->MinimumSize();
            AssertTrueL( ETrue, KSinglePopupMenuTest2 );            
            listbox->TestHandlePointerEventL( event );
            AssertTrueL( ETrue, KSinglePopupMenuTest3 );            
            }
            break;
        case EBCTestCmdOutline27:
            {
            CBCTestSingleGraphicPopupMenuStyleListBox* listbox = 
                static_cast<CBCTestSingleGraphicPopupMenuStyleListBox*>( iListBox );           
            listbox->SizeChanged();
            AssertTrueL( ETrue, KSingleGraphicPopupMenuTest1 );            
            size = listbox->MinimumSize();
            AssertTrueL( ETrue, KSingleGraphicPopupMenuTest2 );            
            listbox->TestHandlePointerEventL( event );
            AssertTrueL( ETrue, KSingleGraphicPopupMenuTest3 );            
            }            
            break;
        case EBCTestCmdOutline28:
            {   
            CAknSingleGraphicBtPopupMenuStyleListBox* listbox = 
                static_cast<CAknSingleGraphicBtPopupMenuStyleListBox*>( iListBox );           
            listbox->SizeChanged();
            AssertTrueL( ETrue, KSingleGraphicBtPopupMenuTest1 );
            listbox->HandlePointerEventL( event );
            AssertTrueL( ETrue, KSingleGraphicBtPopupMenuTest2 );            
            }          
            break;
        case EBCTestCmdOutline29:
            {
            CAknSingleHeadingPopupMenuStyleListBox* listbox = 
                static_cast<CAknSingleHeadingPopupMenuStyleListBox*>( iListBox );           
            listbox->SizeChanged();
            AssertTrueL( ETrue, KSingleHeadingPopupMenuTest1 );            
            size = listbox->MinimumSize();
            AssertTrueL( ETrue, KSingleHeadingPopupMenuTest2 );            
            listbox->HandlePointerEventL( event );
            AssertTrueL( ETrue, KSingleHeadingPopupMenuTest3 );            
            }            
            break;
        case EBCTestCmdOutline30:            
            {
            CAknSingleGraphicHeadingPopupMenuStyleListBox* listbox = 
                static_cast<CAknSingleGraphicHeadingPopupMenuStyleListBox*>( iListBox );           
            listbox->SizeChanged();
            AssertTrueL( ETrue, KSingleGraphicHeadingPopupMenuTest1 );            
            size = listbox->MinimumSize();
            AssertTrueL( ETrue, KSingleGraphicHeadingPopupMenuTest2 );            
            listbox->HandlePointerEventL( event );
            AssertTrueL( ETrue, KSingleGraphicHeadingPopupMenuTest3 );            
            }            
            break;
        case EBCTestCmdOutline31:            
            {
            CAknDoublePopupMenuStyleListBox* listbox = 
                static_cast<CAknDoublePopupMenuStyleListBox*>( iListBox );           
            listbox->SizeChanged();
            AssertTrueL( ETrue, KDoublePopupMenuTest1 );            
            size = listbox->MinimumSize();
            AssertTrueL( ETrue, KDoublePopupMenuTest2 );            
            listbox->HandlePointerEventL( event );
            AssertTrueL( ETrue, KDoublePopupMenuTest3 );            
            }            
            break;
        case EBCTestCmdOutline32:            
            {
            CAknSinglePopupSubmenuStyleListBox* listbox = 
                static_cast<CAknSinglePopupSubmenuStyleListBox*>( iListBox );           
            listbox->SizeChanged();
            AssertTrueL( ETrue, KSinglePopupSubMenuTest1 );            
            size = listbox->MinimumSize();
            AssertTrueL( ETrue, KSinglePopupSubMenuTest2 );            
            listbox->HandlePointerEventL( event );
            AssertTrueL( ETrue, KSinglePopupSubMenuTest3 );            
            }            
            break;
        case EBCTestCmdOutline33:
            {
            CAknDoubleLargeGraphicPopupMenuStyleListBox* listbox = 
                static_cast<CAknDoubleLargeGraphicPopupMenuStyleListBox*>( iListBox );           
            listbox->SizeChanged();
            AssertTrueL( ETrue, KDoubleLargeGraphicPopupMenuTest1 );            
            size = listbox->MinimumSize();
            AssertTrueL( ETrue, KDoubleLargeGraphicPopupMenuTest2 );            
            listbox->HandlePointerEventL( event );
            AssertTrueL( ETrue, KDoubleLargeGraphicPopupMenuTest3 );            
            }            
            break;
        case EBCTestCmdOutline34:
            {           
            CAknDouble2PopupMenuStyleListBox* listbox = 
                static_cast<CAknDouble2PopupMenuStyleListBox*>( iListBox );           
            listbox->SizeChanged();
            AssertTrueL( ETrue, KDouble2PopupMenuTest1 );             
            size = listbox->MinimumSize();
            AssertTrueL( ETrue, KDouble2PopupMenuTest2 );             
            listbox->HandlePointerEventL( event );
            AssertTrueL( ETrue, KDouble2PopupMenuTest3 );            
            }            
            break;
        case EBCTestCmdOutline35:
            {
            CBCTestSingle2GraphicPopupMenuStyleListBox* listbox = 
                static_cast<CBCTestSingle2GraphicPopupMenuStyleListBox*>( iListBox );           
            listbox->SizeChanged();
            AssertTrueL( ETrue, KSingle2GraphicPopupMenuTest1 );            
            size = listbox->MinimumSize();
            AssertTrueL( ETrue, KSingle2GraphicPopupMenuTest2 );            
            listbox->TestHandlePointerEventL( event );
            AssertTrueL( ETrue, KSingle2GraphicPopupMenuTest3 );            
            }            
            break;
        case EBCTestCmdOutline36:
            { 
            CBCTestDoubleGraphicPopupMenuStyleListBox* listbox = 
                static_cast<CBCTestDoubleGraphicPopupMenuStyleListBox*>( iListBox );            
            AssertTrueL( ETrue, KDoubleGraphicPopupMenuTest1 );            
            size = listbox->MinimumSize();
            AssertTrueL( ETrue, KDoubleGraphicPopupMenuTest2 );            
            listbox->TestHandlePointerEventL( event );
            AssertTrueL( ETrue, KDoubleGraphicPopupMenuTest3 );            
            }            
            break;
        case EBCTestCmdOutline37:
            {
            CAknSetStyleListBox* listbox = 
                static_cast<CAknSetStyleListBox*>( iListBox );
            listbox->SizeChanged();
            AssertTrueL( ETrue, KSetTest1 );            
            size = listbox->MinimumSize();
            AssertTrueL( ETrue, KSetTest2 );            
            listbox->HandlePointerEventL( event );
            AssertTrueL( ETrue, KSetTest3 );            
            
            TTypeUid typeId( iEikEnv->EikAppUi()->Application()->AppDllUid().iUid );
            TTypeUid::Ptr uidPtr = listbox->MopSupplyObject( typeId );
            AssertTrueL( ETrue, KSetTest4 );
            listbox->Draw( iContainer->Rect() );
            AssertTrueL( ETrue, KSetTest5 );            
            CDesCArray* textArray = iEikEnv->ReadDesCArrayResourceL(
                R_BCTESTLIST_ITEM_SINGLE_NUMBER );
            if ( textArray )
                {                
                listbox->Model()->SetItemTextArray( textArray );
                listbox->Model()->SetOwnershipType( ELbmOwnsItemArray );
                }
            listbox->Draw( iContainer->Rect() );
            AssertTrueL( ETrue, KSetTest6 );            
            }
            break;
        case EBCTestCmdOutline38:        
            {
            CAknFormGraphicStyleListBox* listbox = 
                static_cast<CAknFormGraphicStyleListBox*>( iListBox );
            listbox->SizeChanged();
            AssertTrueL( ETrue, KFormGraphicTest1 );            
            size = listbox->MinimumSize();
            AssertTrueL( ETrue, KFormGraphicTest2 );            
            TRect rect = iContainer->Rect();
            TInt height = listbox->AdjustRectHeightToWholeNumberOfItems( rect );
            AssertTrueL( ETrue, KFormGraphicTest3 );
            listbox->HandlePointerEventL( event );
            AssertTrueL( ETrue, KFormGraphicTest4 );            
            }
            break;
        case EBCTestCmdOutline39:
            {
            CAknFormGraphicWideStyleListBox* listbox = 
                static_cast<CAknFormGraphicWideStyleListBox*>( iListBox );
            listbox->SizeChanged();
            AssertTrueL( ETrue, KFormGraphicWideTest1 );            
            size = listbox->MinimumSize();
            AssertTrueL( ETrue, KFormGraphicWideTest2 );            
            listbox->HandlePointerEventL( event );
            AssertTrueL( ETrue, KFormGraphicWideTest3 );            
            }
            break;
                            
        default:
            break;
        }        
    }
    
// ---------------------------------------------------------------------------
// CBCTestListPopupCase::GraphicIconL
// ---------------------------------------------------------------------------
//
void CBCTestListPopupCase::GraphicIconL( CArrayPtr<CGulIcon>* aIcons )
    {
    if ( aIcons )
        {
        // Appends icon according to iOutlineId.
        switch ( iOutlineId )
            {            
            case EBCTestCmdOutline37:
            case EBCTestCmdOutline38:
            case EBCTestCmdOutline39:
                for ( TInt i = 0; i< 10; i++ )
                    {
                    CreateIconAndAddToArrayL(
                    aIcons, KBCTestListMbmFileName,
                    EMbmBctestlistGolgo2,
                    EMbmBctestlistGolgo2_mask );    
                    }
                                    
                break;
           
            default:
                break;
            }
        }
    }

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CBCTestSinglePopupMenuStyleListBox::TestCreateItemDrawerL
// ---------------------------------------------------------------------------
//
void CBCTestSinglePopupMenuStyleListBox::
    TestHandlePointerEventL(const TPointerEvent& aPointerEvent)
    {
    HandlePointerEventL( aPointerEvent );
    }

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CBCTestSingleGraphicPopupMenuStyleListBox::TestCreateItemDrawerL
// ---------------------------------------------------------------------------
//    
void CBCTestSingleGraphicPopupMenuStyleListBox::
    TestHandlePointerEventL(const TPointerEvent& aPointerEvent)
    {
    HandlePointerEventL( aPointerEvent );    
    }
    
// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CBCTestSingle2GraphicPopupMenuStyleListBox::TestHandlePointerEventL
// ---------------------------------------------------------------------------
//    
void CBCTestSingle2GraphicPopupMenuStyleListBox::
    TestHandlePointerEventL( const TPointerEvent& aPointerEvent )
    {
    HandlePointerEventL( aPointerEvent );
    }
    
// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CBCTestDoubleGraphicPopupMenuStyleListBox::TestHandlePointerEventL
// ---------------------------------------------------------------------------
//    
void CBCTestDoubleGraphicPopupMenuStyleListBox::
    TestHandlePointerEventL( const TPointerEvent& aPointerEvent )
    {
    HandlePointerEventL( aPointerEvent );
    }
    
