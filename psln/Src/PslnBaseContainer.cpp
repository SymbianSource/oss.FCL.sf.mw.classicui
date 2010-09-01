/*
* Copyright (c) 2002-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Base class for Psln's view containers.
*
*/


// INCLUDE FILES
// General services.
#include    <barsread.h>
#include    <akntitle.h>
#include    <eiktxlbm.h>
#include    <AknUtils.h>

// Psln framework.
#include    <mpslnfwmsklabelobserver.h>

// Psln specific.
#include    "PslnModel.h"
#include    "PslnBaseContainer.h"
#include    "PslnUi.h"

//  MEMBER FUNCTIONS

// ---------------------------------------------------------------------------
// C++ default constructor
// ---------------------------------------------------------------------------
//
CPslnBaseContainer::CPslnBaseContainer()
    {
    iModel = static_cast<CPslnUi*>( ControlEnv()->AppUi() )->Model();
    }

// ---------------------------------------------------------------------------
// CPslnBaseContainer::BaseConstructL
// ---------------------------------------------------------------------------
//
void CPslnBaseContainer::BaseConstructL( const TRect& aRect, TInt aResLbxId )
    {
    CreateWindowL(); // Makes the control a window-owning control
    iListBox->SetContainerWindowL( *this );

    iListBox->ConstructL( this, EAknListBoxSelectionList );
    iItemArray = static_cast<CDesCArray*>
        ( iListBox->Model()->ItemTextArray() );

    ConstructListBoxL( aResLbxId );
    iListBox->CreateScrollBarFrameL( ETrue );
    iListBox->ScrollBarFrame()->SetScrollBarVisibilityL(
        CEikScrollBarFrame::EOff,
        CEikScrollBarFrame::EAuto );
    SetRect( aRect );
    ActivateL();
    }

// ---------------------------------------------------------------------------
// CPslnBaseContainer::BaseConstructL
// ---------------------------------------------------------------------------
//
void CPslnBaseContainer::BaseConstructL(
    const TRect& aRect, TInt aResTitleId, TInt aResLbxId )
    {
    // Set title
    if ( aResTitleId )
        {
        CEikStatusPane* sp =
            iAvkonAppUi->StatusPane();
        if ( sp )
            {
            CAknTitlePane* title = static_cast<CAknTitlePane*>(
                sp->ControlL( TUid::Uid( EEikStatusPaneUidTitle ) ) );
            if ( title )
                {
                TResourceReader rReader;
                iCoeEnv->CreateResourceReaderLC( rReader, aResTitleId );
                title->SetFromResourceL( rReader );
                CleanupStack::PopAndDestroy(); //rReader
                }
            }
        }
    BaseConstructL( aRect, aResLbxId );
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CPslnBaseContainer::~CPslnBaseContainer()
    {
    delete iListBox;
    }

// ---------------------------------------------------------------------------
// CPslnBaseContainer::SetListBoxObserver
// ---------------------------------------------------------------------------
//
void CPslnBaseContainer::SetListBoxObserver( MEikListBoxObserver* aObserver )
    {
    iListBox->SetListBoxObserver( aObserver );
    }

// ---------------------------------------------------------------------------
// CPslnBaseContainer::CurrentItemIndex
// ---------------------------------------------------------------------------
//
TInt CPslnBaseContainer::CurrentItemIndex() const
    {
    return iListBox->CurrentItemIndex();
    }

// ---------------------------------------------------------------------------
// CPslnBaseContainer::SetCurrentItemIndexAndDraw
// ---------------------------------------------------------------------------
//
void CPslnBaseContainer::SetCurrentItemIndexAndDraw( TInt aNewIndex )
    {
    if( ( aNewIndex >= 0 ) &&
        ( aNewIndex < iListBox->Model()->NumberOfItems() ) )
        {
        iListBox->SetCurrentItemIndexAndDraw( aNewIndex );
        }
    }

// ---------------------------------------------------------------------------
// CPslnBaseContainer::SetCurrentItemIndex
// ---------------------------------------------------------------------------
//
void CPslnBaseContainer::SetCurrentItemIndex( TInt aNewIndex )
    {
    if( ( aNewIndex >= 0 ) &&
        ( aNewIndex < iListBox->Model()->NumberOfItems() ) )
        {
        iListBox->SetCurrentItemIndex( aNewIndex );
        }
    }

// ---------------------------------------------------------------------------
// CPslnBaseContainer::GetMiddleSoftkeyObserver
// ---------------------------------------------------------------------------
//
MPslnFWMSKObserver* CPslnBaseContainer::GetMiddleSoftkeyObserver()
    {
    return iMSKObserver;
    }

// ---------------------------------------------------------------------------
// Sets observer for MSK label updations.
// ---------------------------------------------------------------------------
//
void CPslnBaseContainer::SetMiddleSoftkeyObserver( MPslnFWMSKObserver* aObserver )
    {
    if ( !iMSKObserver && aObserver )
        {
        iMSKObserver = aObserver;
        }
    }

// ---------------------------------------------------------------------------
// CPslnBaseContainer::UpdateListBoxL
// ---------------------------------------------------------------------------
//
void CPslnBaseContainer::UpdateListBoxL()
    {
    // Update items.
    CreateListBoxItemsL();
    }

// ---------------------------------------------------------------------------
// Called when a key is pressed.
// ---------------------------------------------------------------------------

TKeyResponse CPslnBaseContainer::OfferKeyEventL(
    const TKeyEvent& aKeyEvent, TEventCode aType )
    {
    switch ( aKeyEvent.iCode )
        {
        case EKeyUpArrow:
        case EKeyDownArrow:
            {
            TKeyResponse listboxResp =
                iListBox->OfferKeyEventL( aKeyEvent, aType );
            if ( iMSKObserver )
                {
                iMSKObserver->CheckMiddleSoftkeyLabelL();
                }
            return listboxResp;
            }
        case EKeyLeftArrow:
        case EKeyRightArrow:
            // Listbox takes all events even if it doesn't use them
            return EKeyWasNotConsumed;
        default:
            break;
        }

    return iListBox->OfferKeyEventL( aKeyEvent, aType );
    }

// ---------------------------------------------------------------------------
// Called by framwork when the view size is changed.
// ---------------------------------------------------------------------------
//
void CPslnBaseContainer::SizeChanged()
    {
    if ( iListBox )
        {
        iListBox->SetRect( Rect() );
        }
    }

// ---------------------------------------------------------------------------
// CPslnBaseContainer::CountComponentControls
// ---------------------------------------------------------------------------
//
TInt CPslnBaseContainer::CountComponentControls() const
    {
    return 1; //magic
    }

// ---------------------------------------------------------------------------
// CPslnBaseContainer::ComponentControl
// ---------------------------------------------------------------------------
//
CCoeControl* CPslnBaseContainer::ComponentControl( TInt /*aIndex*/ ) const
    {
    return iListBox;
    } //lint !e1763 Member intentionally exposed through const method

// ---------------------------------------------------------------------------
// CPslnBaseContainer::HandleResourceChange
// ---------------------------------------------------------------------------
//
void CPslnBaseContainer::HandleResourceChange( TInt aType )
    {
    CCoeControl::HandleResourceChange( aType );
    if ( aType == KEikDynamicLayoutVariantSwitch )
        {
        TRect mainPaneRect;
        AknLayoutUtils::LayoutMetricsRect(
            AknLayoutUtils::EMainPane,
            mainPaneRect );
        SetRect( mainPaneRect );
        }
    }

// ---------------------------------------------------------------------------
// CPslnBaseContainer::FocusChanged
// ---------------------------------------------------------------------------
//
void CPslnBaseContainer::FocusChanged( TDrawNow aDrawNow )
    {
    // Pass focus changed event to listbox.
    if ( iListBox )
        {
        iListBox->SetFocus( IsFocused(), aDrawNow );
        }
    }

//  End of File
