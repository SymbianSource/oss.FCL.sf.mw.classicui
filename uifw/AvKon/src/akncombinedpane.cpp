/*
* Copyright (c) 2010 Nokia Corporation and/or its subsidiary(-ies).
* All rights reserved.
* This component and the accompanying materials are made available
* under the terms of the License "Eclipse Public License v1.0"
* which accompanies this distribution, and is available
* at the URL "http://www.eclipse.org/legal/epl-v10.html".
*
* Initial Contributors:
* Nokia Corporation - initial contribution.
*
* Contributors:
*
* Description:  Status pane's combined subpane component.
*
*/

#include <AknsDrawUtils.h>
#include <AknIndicatorContainer.h>
#include <aknlayoutscalable_avkon.cdl.h>
#include <barsread.h>
#include <eikspane.h>
#include <avkon.hrh>
#include <AknPriv.hrh>
#include <AknSmallIndicator.h>
#include <aknappui.h>
#include <uikon/eikdefmacros.h>

#include "akncombinedpane.h"
#include "aknstatuspanedatasubscriber.h"

// This is used to calculate the amount of pixels that the subpanes are
// shifted to bottom and right when they are "pressed down". 
const TInt KPressedDownDeltaDivider( 35 ); // 0.3 units

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// Two-phased constructor.
// ----------------------------------------------------------------------------
//
CAknCombinedPane* CAknCombinedPane::NewL()
    {
    CAknCombinedPane* self = new ( ELeave ) CAknCombinedPane();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }


// ----------------------------------------------------------------------------
// Destructor
// ----------------------------------------------------------------------------
//
CAknCombinedPane::~CAknCombinedPane()
    {
    iSubPanes.Reset();

    if ( iAvkonAppUi )
        {
        iAvkonAppUi->RemoveFromStack( this );
        }
    }


// ----------------------------------------------------------------------------
// Returns number of controls inside this control.
// ----------------------------------------------------------------------------
//
TInt CAknCombinedPane::CountComponentControls() const
    {
    return iSubPanes.Count();
    }


// ----------------------------------------------------------------------------
// Returns a control determined by control index.
// ----------------------------------------------------------------------------
//
CCoeControl* CAknCombinedPane::ComponentControl( TInt aIndex ) const
    {
    CCoeControl* control = NULL;

    if ( iStatusPane && aIndex < iSubPanes.Count() )
        {
        TRAP_IGNORE( control = iStatusPane->ContainerControlL(
            TUid::Uid( iSubPanes[aIndex].iUid ) ) );
        }

    return control;
    }


// ----------------------------------------------------------------------------
// Handles a change to the control's resources.
// ----------------------------------------------------------------------------
//
void CAknCombinedPane::HandleResourceChange( TInt aType )
    {
    CAknButton::HandleResourceChange( aType );

    switch ( aType )
        {
        case KAknMessageFocusLost:      // fallthrough
        case KEikMessageFadeAllWindows:
            {
            SetSubPanesPressedDown( EFalse );
            DrawDeferred();
            break;
            }
        
        case KAknsMessageSkinChange:
            {
            DrawDeferred();
            break;
            }
            
        case KEikDynamicLayoutVariantSwitch:
            {
            SetSubPanesPressedDown( EFalse );
            // Recalculate the pressed down delta pixels on layout change.
            TAknWindowLineLayout unitValue(
                AknLayoutScalable_Avkon::aid_value_unit2().LayoutLine() );
            iPressedDownDelta = unitValue.iW / KPressedDownDeltaDivider;
            DrawDeferred();
            break;
            }
            
        default:
            {
            break;
            }
        }
    }


// ----------------------------------------------------------------------------
// Resource constructor.
// ----------------------------------------------------------------------------
//
void CAknCombinedPane::ConstructFromResourceL( TResourceReader& aReader )
    {
    aReader.ReadInt8(); // version

    TInt count = aReader.ReadInt16(); // amount of subpanes

    for ( TInt i = 0; i < count; ++i )
        {
        TSubPaneData subPane;

        aReader.ReadInt8(); // version
        subPane.iUid = aReader.ReadUint32(); // subpane UID
        subPane.iPressedDown = EFalse; // Isn't specified in the resource.
        aReader.ReadInt32(); // extension

        iSubPanes.AppendL( subPane );
        }

    aReader.ReadInt32(); // extension

    iStatusPane = CEikStatusPaneBase::Current();
    }


// ----------------------------------------------------------------------------
// Handles pointer events inside the control.
// ----------------------------------------------------------------------------
//
void CAknCombinedPane::HandlePointerEventL(
    const TPointerEvent& aPointerEvent )
    {
    CAknButton::HandlePointerEventL( aPointerEvent );

    switch ( aPointerEvent.iType )
        {
        case TPointerEvent::EButton1Down:
            {
            SetSubPanesPressedDown( ETrue );
            iPointerDownInCombinedArea = ETrue;
            break;
            }
            
        case TPointerEvent::EButton1Up:
            {
            SetSubPanesPressedDown( EFalse );
            
            if ( iPointerDownInCombinedArea &&
                 Rect().Contains( aPointerEvent.iPosition ) )
                {
                // Display the universal indicator popup.
                CAknSmallIndicator* indicatorNotifier =
                    CAknSmallIndicator::NewLC( TUid::Uid( 0 ) );
                indicatorNotifier->HandleIndicatorTapL();
                CleanupStack::PopAndDestroy( indicatorNotifier );
                }
            
            iPointerDownInCombinedArea = EFalse;
            break;
            }
            
        case TPointerEvent::EDrag:
            {
            TRect combinedRect( Rect() );
            if ( !combinedRect.Contains( aPointerEvent.iPosition ) )
                {
                SetSubPanesPressedDown( EFalse );
                }
            else if ( iPointerDownInCombinedArea &&
                      combinedRect.Contains( aPointerEvent.iPosition ) )
                {
                SetSubPanesPressedDown( ETrue );
                }
            break;
            }
            
        default:
            {
            break;
            }
        }

    DrawDeferred();
    }


// ----------------------------------------------------------------------------
// Default C++ constructor.
// ----------------------------------------------------------------------------
//
CAknCombinedPane::CAknCombinedPane() : CAknButton( 0 ),
                                       iStatusPane( NULL )
    {
    // Calculate the pressed down delta pixels from layout data,
    // aid_value_unit2 is a 10ux10u rectangle.
    TAknWindowLineLayout unitValue(
        AknLayoutScalable_Avkon::aid_value_unit2().LayoutLine() );
    // Move the control 0.3 units to right and down for the
    // "pressed down" effect.
    iPressedDownDelta = unitValue.iW / KPressedDownDeltaDivider;
    }


// ----------------------------------------------------------------------------
// Second-phase constructor.
// ----------------------------------------------------------------------------
//
void CAknCombinedPane::ConstructL()
    {
    CAknButton::ConstructL( NULL, NULL, NULL, NULL, KNullDesC, KNullDesC, 0 );

    // Use the softkey frame graphics so that the bottom area appears
    // consistent.
    SetFrameAndCenterIds( KAknsIIDQgnFrSctrlSkButton,
                          KAknsIIDQgnFrSctrlSkButtonCenter,
                          KAknsIIDNone,
                          KAknsIIDNone,
                          KAknsIIDNone,
                          KAknsIIDNone,
                          KAknsIIDQgnFrSctrlSkButtonPressed,
                          KAknsIIDQgnFrSctrlSkButtonCenterPressed,
                          KAknsIIDNone,
                          KAknsIIDNone );
    
    // Add to the control stack in order to receive the focus lost events. 
    iAvkonAppUi->AddToStackL( this, 
                              ECoeStackPriorityCba,
                              ECoeStackFlagRefusesAllKeys |
                              ECoeStackFlagRefusesFocus );
    }


// ----------------------------------------------------------------------------
// Sets the pressed down state of the subpanes.
// ----------------------------------------------------------------------------
//
void CAknCombinedPane::SetSubPanesPressedDown( TBool aPressedDown )
    {
    TInt delta = aPressedDown ? iPressedDownDelta : -iPressedDownDelta;

    for ( TInt i = 0; i < iSubPanes.Count(); ++i )
        {
        if ( !COMPARE_BOOLS( iSubPanes[i].iPressedDown, aPressedDown ) )
            {
            CCoeControl* control = ComponentControl( i );
            TRect controlRect( control->Rect() );
            controlRect.Move( delta, delta );
            control->SetRect( controlRect );
            iSubPanes[i].iPressedDown = aPressedDown;
            }
        }
    }

// End of File
