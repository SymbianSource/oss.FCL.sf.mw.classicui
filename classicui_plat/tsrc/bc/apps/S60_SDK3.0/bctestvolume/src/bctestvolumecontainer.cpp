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
* Description:         Avkon volume test application
*
*/









// INCLUDE FILES
#include <barsread.h>
#include <e32math.h>
#include <eikenv.h>
#include <eiklabel.h>
#include <avkon.hrh>
#include <aknappui.h>
#include <aknnavi.h>
#include <aknnavide.h>
#include <aknvolumesettingpage.h>
#include <apgcli.h>                     // For RApaLsSession
#include <aknutils.h>                   // For CompleteWithAppPath
#include <avkon.rsg>
#include <bctestvolume.rsg>
#include <eikdll.h>

#include "BCTestvolume.hrh"
#include "BCTestVolumeView.h"
#include "BCTestVolumeContainer.h"
#include "BCTestVolumePopupWindow.h"

// CONSTANTS
// for label
const TInt KBCTestVolumeAdjustX = 5;
const TInt KBCTestVolumeAdjustY = 5;

const TInt KBCTestVolumeHalf = 2;
// for count
const TInt KBCTestVolumeInitialCount = 0;
// for Text
const TInt KBCTestVolumeMessageBufLength = 256;
// for initializing variable
#define KBCTestVolumeInitialTime TInt64( 0 )
// for change state
#define BCTestVOLUME_SET_RETURN_VALUE_KEY   EKeyEnter
#define BCTestVOLUME_SET_RETURN_VALUE_KEY2  EKeyOK
// for clock masking
#define BCTestSPANE_ZERO_SIZE_AREA TRect(0,0,0,0)

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CBCTestVolumeContainer::CBCTestVolumeContainer( CBCTestVolumeView* )
// Overload constructor.
// ----------------------------------------------------------------------------
//
CBCTestVolumeContainer::CBCTestVolumeContainer( CBCTestVolumeView* aView )
    :   iLabel( NULL ),
        iNaviPane( NULL ),
        iView( aView ),
        iCurrentOutlineId( EBCTestVolumeCmdEmptyOutline )
    {
    }

// ----------------------------------------------------------------------------
// CBCTestVolumeContainer::ConstructL( const TRect& )
// Symbian 2nd phase constructor.
// ----------------------------------------------------------------------------
//
void CBCTestVolumeContainer::ConstructL( const TRect& aRect )
    {
    CreateWindowL(); // Creates window.
    SetRect( aRect ); // Sets rectangle of frame.

    // Capture volume keys
    RWindowGroup& windowGroup = ControlEnv()->RootWin();
    iKeyHandle1 = windowGroup.CaptureKey( EKeyDevice8, 0, 0 );
    iKeyHandle2 = windowGroup.CaptureKey( EKeyDevice9, 0, 0 );
    
    iKeyHandle3 = windowGroup.CaptureKey( EKeyLeftArrow, 0, 0 );
    iKeyHandle4 = windowGroup.CaptureKey( EKeyRightArrow, 0, 0 );

    ActivateL(); // Activates the window. (Ready to draw)
    }

// ----------------------------------------------------------------------------
// CBCTestVolumeContainer::~CBCTestVolumeContainer()
// Destructor.
// ----------------------------------------------------------------------------
//
CBCTestVolumeContainer::~CBCTestVolumeContainer()
    {
    RWindowGroup& windowGroup = ControlEnv()->Static()->RootWin();
    windowGroup.CancelCaptureKey( iKeyHandle1 );
    windowGroup.CancelCaptureKey( iKeyHandle2 );
    
    windowGroup.CancelCaptureKey( iKeyHandle3 );
    windowGroup.CancelCaptureKey( iKeyHandle4 );

    delete iPopUpControl;
    delete iLabel;
    ResetNaviPane();
    }

// ----------------------------------------------------------------------------
// delete all components and set them to NULL
// ----------------------------------------------------------------------------
//
void CBCTestVolumeContainer::ResetComponentsL()
    {
    // Deletes each object.
    if ( iLabel )
        {
        delete iLabel;
        iLabel = NULL;
        }
    
    if (!iPopUpControl)
        {
        iPopUpControl = new(ELeave) CBCTestVolumePopUpWindow;
        iPopUpControl->ConstructL(BCTestSPANE_ZERO_SIZE_AREA);
        }
    
    ResetNaviPane();
    }

// ----------------------------------------------------------------------------
// delete the decorator inside the navigation pane.
// ----------------------------------------------------------------------------
//
void CBCTestVolumeContainer::ResetNaviPane()
    {
    if ( iNaviPane )
        {
        iNaviPane->Pop( NULL );
        if ( iDecorator )
            {
            CAknVolumeControl* volume = STATIC_CAST(
                CAknVolumeControl*, iDecorator->DecoratedControl() );
            iEikonEnv->EikAppUi()->RemoveFromStack( volume );
            delete iDecorator;
            iDecorator = NULL;
            }
        }
    }

// ----------------------------------------------------------------------------
// update the controls for redraw.
// ----------------------------------------------------------------------------
//
void CBCTestVolumeContainer::UpdateComponentsL()
    {
    SizeChanged();

    // if clock is visible, mask it off
    if (iEikonEnv->AppUiFactory()->StatusPane()->CurrentLayoutResId() ==
        R_AVKON_STATUS_PANE_LAYOUT_IDLE)
        {
        /* Is context or clock pane visible in the status pane */
        CEikStatusPane* sp = ((CAknAppUi*)iEikonEnv->EikAppUi())->StatusPane();
        TRect paneRect;
        if (sp->PaneCapabilities(
                TUid::Uid(EEikStatusPaneUidContext)).IsInCurrentLayout() )
            {
            paneRect = sp->PaneRectL(TUid::Uid(EEikStatusPaneUidContext));
            }
        else
            {
            paneRect = sp->PaneRectL(TUid::Uid(EEikStatusPaneUidClock));
            }

        iPopUpControl->SetRect(paneRect);
        }
    else // clear popup rectangle
        {
        iPopUpControl->SetRect(BCTestSPANE_ZERO_SIZE_AREA);
        }

    DrawNow();
    }

// ----------------------------------------------------------------------------
// void CBCTestVolumeContainer::DisplaytOutlineL( const TInt )
// Displays each outline screen.
// ----------------------------------------------------------------------------
//
void CBCTestVolumeContainer::DisplayOutlineL( const TInt aOutlineId )
    {
    iCurrentOutlineId = aOutlineId; // Sets current outline ID.

    ResetComponentsL();

    // Displays each outline screen.
    switch ( aOutlineId )
        {
        case EBCTestVolumeCmdEmptyOutline:
            CreateLabelL( R_BCTESTVOLUME_TEXT_LABEL_TITLE );
            break;

        default:
            break;
        }
        UpdateComponentsL();
    }

// ----------------------------------------------------------------------------
// void CBCTestVolumeContainer::CreateLabelL( const TInt )
// Creates the label object.
// ----------------------------------------------------------------------------
//
void CBCTestVolumeContainer::CreateLabelL( const TInt aResourceId )
    {
    TBuf<KBCTestVolumeMessageBufLength> labelText( 0 );

    iCoeEnv->ReadResourceL( labelText, aResourceId );

    // Creates the label object.
    if ( !iLabel )
        {
        iLabel = new( ELeave ) CEikLabel;
        iLabel->SetContainerWindowL( *this );
        iLabel->SetTextL( labelText );
        iLabel->SetFont( iEikonEnv->TitleFont() );
        iLabel->SetAlignment( EHCenterVCenter );
        }
    }

// ----------------------------------------------------------------------------
// TKeyResponse CBCTestVolumeContainer::OfferKeyEventL( const TKeyEvent&,
//  TEventCode )
// Handles the key events.
// ----------------------------------------------------------------------------
//
TKeyResponse CBCTestVolumeContainer::OfferKeyEventL( const TKeyEvent& aKeyEvent,
                                                    TEventCode aType )
    {
    if ( aType != EEventKey )
        {
        return EKeyWasNotConsumed;
        }

    switch ( aKeyEvent.iCode )
        {
        case EKeySpace: // Space key.
            // Required to display next outline screen.
            iView->DisplayNextOutlineL(); 
            break;
        case BCTestVOLUME_SET_RETURN_VALUE_KEY:
        case BCTestVOLUME_SET_RETURN_VALUE_KEY2:
            {
            if ( iCurrentOutlineId != EBCTestVolumeCmdOutline02 )
                {
                return EKeyWasNotConsumed;
                }
            break;
            }
        default:
            break;
        }
    return EKeyWasConsumed;
    }

// ----------------------------------------------------------------------------
// void CBCTestVolumeContainer::SizeChanged()
// Called by framework when the view size is changed.
// ----------------------------------------------------------------------------
//
void CBCTestVolumeContainer::SizeChanged()
    {
    switch ( iCurrentOutlineId )
        {
        case EBCTestVolumeCmdOutline02:
            // Sets rectangle of top label.
            if ( iLabel )
                {
                TRect topRect( Rect() );
                topRect.SetHeight( topRect.Height() / KBCTestVolumeHalf );
                topRect.Shrink( KBCTestVolumeAdjustX, KBCTestVolumeAdjustY );
                iLabel->SetRect( topRect );
                }
            break;
        default:
            // Sets rectangle of label.
            if ( iLabel )
                {
                iLabel->SetRect( Rect() );
                }
            break;
        }
    }

// ----------------------------------------------------------------------------
// TInt CBCTestVolumeContainer::CountComponentControls() const
// Returns number of component.
// ----------------------------------------------------------------------------
//
TInt CBCTestVolumeContainer::CountComponentControls() const
    {
    TInt count( KBCTestVolumeInitialCount );

    if ( iLabel )
        {
        ++count;
        }
    return count; // Returns number of component.
    }

// ----------------------------------------------------------------------------
// CCoeControl* CBCTestVolumeContainer::ComponentControl( TInt ) const
// Returns pointer to particular component.
// ----------------------------------------------------------------------------
//
CCoeControl* CBCTestVolumeContainer::ComponentControl( TInt aIndex ) const
    {
    switch ( aIndex )
        {
        case EBCTestVolumeComponent1:
            return iLabel; // Returns the pointer to label object.
        default:
            return NULL; // Exception : Returns NULL value.
        }
    }

// ----------------------------------------------------------------------------
// void CBCTestVolumeContainer::Draw( const TRect& ) const
// Clears the window's rectangle.
// ----------------------------------------------------------------------------
//
void CBCTestVolumeContainer::Draw( const TRect& aRect ) const
    {
    // (Re)draw the rectangle of frame.
    CWindowGc& gc = SystemGc();
    gc.SetPenStyle( CGraphicsContext::ENullPen );
    gc.SetBrushColor( KRgbGray );
    gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
    gc.DrawRect( aRect );
    }

// ----------------------------------------------------------------------------
// void CBCTestVolumeContainer::HandleResourceChange(TInt)
// Makes dynamic resolution change smoother
// ----------------------------------------------------------------------------
//
void CBCTestVolumeContainer::HandleResourceChange(TInt aType)
    {
    if (aType == KEikDynamicLayoutVariantSwitch)
        {
        SetRect( iAvkonAppUi->ClientRect());
        }
    CCoeControl::HandleResourceChange( aType );
    }

// ----------------------------------------------------------------------------
// getter of the navigation pane.
// ----------------------------------------------------------------------------
//
CAknNavigationControlContainer* CBCTestVolumeContainer::NaviPane()
    {
    CEikStatusPane* statusPane = static_cast<CAknAppUi*>(iEikonEnv->EikAppUi() )->StatusPane();
    return static_cast<CAknNavigationControlContainer*>(statusPane->ControlL( TUid::Uid( EEikStatusPaneUidNavi ) ) );
    }

// ----------------------------------------------------------------------------
// setter for the decorator.
// ----------------------------------------------------------------------------
//
void CBCTestVolumeContainer::SetDecorator(CAknNavigationDecorator* aDecorator)
    {
    iNaviPane = NaviPane();
    iDecorator= aDecorator;
    }

// End of File
