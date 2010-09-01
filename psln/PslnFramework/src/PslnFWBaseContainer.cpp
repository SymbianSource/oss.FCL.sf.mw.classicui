/*
* Copyright (c) 2005-2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Base container for Psln some views.
*
*/


// INCLUDE FILES
#include "pslnfwbasecontainer.h"

// Title and status pane.
#include <akntitle.h>
#include <eikspane.h>

// AVKON App Ui.
#include <aknappui.h>
#include <AknUtils.h>

// Resource reader.
#include <barsread.h>

// ================= MEMBER FUNCTIONS =======================

// ---------------------------------------------------------------------------
// Base constructor.
// ---------------------------------------------------------------------------
//
EXPORT_C void CPslnFWBaseContainer::BaseConstructL( const TRect& aRect, 
                                                TInt aResTitleId, 
                                                TInt aResLbxId )
    {
    // Create title if needed.
    if ( aResTitleId != 0 )
        {
        CEikStatusPane* sp = iAvkonAppUi->StatusPane();

        CAknTitlePane* title = 
            static_cast<CAknTitlePane*> ( 
            sp->ControlL( TUid::Uid( EEikStatusPaneUidTitle ) ) );

        TResourceReader rReader;
        iCoeEnv->CreateResourceReaderLC( rReader, aResTitleId );
        title->SetFromResourceL( rReader );
        CleanupStack::PopAndDestroy(); // rReader
        }
    
    CreateWindowL(); // Makes the control a window-owning control
 
    // Set iListBox to be contained in this container:
    iListBox->SetContainerWindowL( *this ); 

    ConstructListBoxL( aResLbxId );
    
    iListBox->CreateScrollBarFrameL( ETrue );
    iListBox->ScrollBarFrame()->SetScrollBarVisibilityL( 
        CEikScrollBarFrame::EOff, 
        CEikScrollBarFrame::EAuto );

    SetRect( aRect );
    ActivateL();
    }

// ---------------------------------------------------------------------------
// C++ default constructor.
// ---------------------------------------------------------------------------
//
EXPORT_C CPslnFWBaseContainer::CPslnFWBaseContainer()
    {
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
EXPORT_C CPslnFWBaseContainer::~CPslnFWBaseContainer()
    {
    delete iListBox;
    }

// ---------------------------------------------------------------------------
// Sets observer for MSK label updations.
// ---------------------------------------------------------------------------
//
EXPORT_C void CPslnFWBaseContainer::SetMiddleSoftkeyObserver( 
    MPslnFWMSKObserver* aObserver )
    {
    if ( !iMSKObserver && aObserver )
        {        
        iMSKObserver = aObserver;
        }
    }

// ---------------------------------------------------------------------------
//  Construct's ListBox from Resource ID
// ---------------------------------------------------------------------------
//
void CPslnFWBaseContainer::ConstructListBoxL( TInt aResLbxId )
    {
    TResourceReader rReader;
    iCoeEnv->CreateResourceReaderLC( rReader, aResLbxId );
    iListBox->ConstructFromResourceL( rReader );
    CleanupStack::PopAndDestroy(); // rReader
    }

// ---------------------------------------------------------------------------
// Handles system changes (skin change and layout changes).
// ---------------------------------------------------------------------------
EXPORT_C void CPslnFWBaseContainer::HandleResourceChange( TInt aType )
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
// Called by framework when the view size is changed.
// ---------------------------------------------------------------------------
//
EXPORT_C void CPslnFWBaseContainer::SizeChanged()
    {
    if ( iListBox )
        {
        iListBox->SetRect( Rect() );
        }
    }

// ---------------------------------------------------------------------------
// Count component controls.
// ---------------------------------------------------------------------------
//
EXPORT_C TInt CPslnFWBaseContainer::CountComponentControls() const
    {
    return 1;
    }

// ---------------------------------------------------------------------------
//  Returns mathcing component.
// ---------------------------------------------------------------------------
//
EXPORT_C CCoeControl* CPslnFWBaseContainer::ComponentControl( TInt /*aIndex*/ ) 
    const
    {
    return iListBox;
    }

// ---------------------------------------------------------------------------
// Called when a key is pressed.
// ---------------------------------------------------------------------------
EXPORT_C TKeyResponse CPslnFWBaseContainer::OfferKeyEventL(
    const TKeyEvent& aKeyEvent, 
    TEventCode aType )
    {
    switch ( aKeyEvent.iCode )
        {
        case EKeyNext:
        case EKeyPrevious:
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
// Handles focus change events.
// ---------------------------------------------------------------------------
//
EXPORT_C void CPslnFWBaseContainer::FocusChanged( TDrawNow aDrawNow )
    {
    // Pass focus changed event to listbox.
    if ( iListBox )
        {
        iListBox->SetFocus( IsFocused(), aDrawNow );
        }
    }
    
//  End of File
