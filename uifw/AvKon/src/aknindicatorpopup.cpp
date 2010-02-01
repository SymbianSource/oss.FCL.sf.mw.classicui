/*
* Copyright (c) 2007-2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Interface for controlling the universal status
*                indicator popup.
*
*/


#include <AknPreviewPopUpController.h>
#include <aknlayoutscalable_avkon.cdl.h>
#include <layoutmetadata.cdl.h>
#include <AknUtils.h>
#include <AknStatuspaneUtils.h>

#include "aknindicatorpopup.h"
#include "aknindicatorpopupcontent.h"
#include "AknIndicatorPlugin.h"

const TInt KDefaultPopUpShowDelay = 0;
const TInt KDefaultPopUpHideDelay = 6000000; // 6 seconds

// ---------------------------------------------------------------------------
// CAknIndicatorPopup::NewL
// ---------------------------------------------------------------------------
//
CAknIndicatorPopup* CAknIndicatorPopup::NewL()
    {
    CAknIndicatorPopup* self = CAknIndicatorPopup::NewLC();
    CleanupStack::Pop( self );
    return self;
    }


// ---------------------------------------------------------------------------
// CAknIndicatorPopup::NewLC
// ---------------------------------------------------------------------------
//
CAknIndicatorPopup* CAknIndicatorPopup::NewLC()
    {
    CAknIndicatorPopup* self = new ( ELeave ) CAknIndicatorPopup();
    CleanupStack::PushL( self );
    self->ConstructL();
    return self;
    }


// ---------------------------------------------------------------------------
// Destructor.
// ---------------------------------------------------------------------------
//
CAknIndicatorPopup::~CAknIndicatorPopup()
    {
    delete iController;
    delete iContent;
    }


// ---------------------------------------------------------------------------
// CAknIndicatorPopup::ShowPopup
// ---------------------------------------------------------------------------
//
void CAknIndicatorPopup::ShowPopup()
    {
    if ( AknLayoutUtils::PenEnabled() )
        {
        iController->ShowPopUp();
        }
    }


// ---------------------------------------------------------------------------
// CAknIndicatorPopup::HidePopup
// ---------------------------------------------------------------------------
//
void CAknIndicatorPopup::HidePopup()
    {
    if ( AknLayoutUtils::PenEnabled() )
        {
        iController->HidePopUp();
        }
    }


// ---------------------------------------------------------------------------
// CAknIndicatorPopup::SetPosition
// ---------------------------------------------------------------------------
//
void CAknIndicatorPopup::SetPosition( const TPoint& aPoint )
    {
    // Position is the top right corner.
    iPosition = aPoint;
    iController->SetPosition( aPoint );
    }

// ---------------------------------------------------------------------------
// CAknIndicatorPopup::SetBottomPosition
// ---------------------------------------------------------------------------
//
void CAknIndicatorPopup::SetBottomPosition( const TPoint& aPoint )
    {
    // Position is the top right corner, so it must be calculated based
    // on the bottom right corner and the amount of items.
    TSize popupSize( iContent->MinimumSize() );
    TPoint position( aPoint );
    position.iY -= popupSize.iHeight;
    
    iPosition = position;
    iController->SetPosition( position );
    }

// ---------------------------------------------------------------------------
// CAknIndicatorPopup::SetSignalStateL
// ---------------------------------------------------------------------------
//
void CAknIndicatorPopup::SetSignalStateL( TInt aState )
    {
    iContent->SetSignalStateL( aState );
    }
// ---------------------------------------------------------------------------
// CAknIndicatorPopup::SetBatteryStateL
// ---------------------------------------------------------------------------
//

void CAknIndicatorPopup::SetBatteryStateL( TInt aState )
    {
    iContent->SetBatteryStateL( aState );
    }
// CAknIndicatorPopup::AddItemL
// ---------------------------------------------------------------------------
//
void CAknIndicatorPopup::AddItemL( TInt aIndicatorUid,
                                   const TDesC& aText,
                                   TInt aTextType,
                                   const CGulIcon* aIcon,
                                   CAknIndicatorPlugin* aPlugin,
                                   TInt aPriority )
    {
    iContent->AddItemL( aIndicatorUid, aText, aTextType, aIcon, aPlugin, aPriority );
    iController->UpdateContentSize();
    }


// ---------------------------------------------------------------------------
// CAknIndicatorPopup::RemoveItem
// ---------------------------------------------------------------------------
//
void CAknIndicatorPopup::RemoveItem( TInt aIndicatorUid )
    {
    iContent->RemoveItem( aIndicatorUid );
    iController->UpdateContentSize();
    }


// ---------------------------------------------------------------------------
// CAknIndicatorPopup::SetContentVisible
// ---------------------------------------------------------------------------
//
void CAknIndicatorPopup::SetContentVisible( TBool aVisible )
    {
    iContent->SetContentVisible( aVisible );
    }


// ---------------------------------------------------------------------------
// CAknIndicatorPopup::SetObserverL
// ---------------------------------------------------------------------------
//
void CAknIndicatorPopup::SetObserverL(
    const MAknPreviewPopUpObserver& aObserver )
    {
    if ( iController )
        {
        iController->AddObserverL( aObserver );
        }
    }


// ---------------------------------------------------------------------------
// CAknIndicatorPopup::RemoveObserver
// ---------------------------------------------------------------------------
//
void CAknIndicatorPopup::RemoveObserver(
    const MAknPreviewPopUpObserver& aObserver )
    {
    if ( iController )
        {
        iController->RemoveObserver( aObserver );
        }
    }


// ---------------------------------------------------------------------------
// CAknIndicatorPopup::Controller
// ---------------------------------------------------------------------------
//
const CAknPreviewPopUpController* CAknIndicatorPopup::Controller() const
    {
    return iController;
    }


// -----------------------------------------------------------------------------
// CAknIndicatorPopup::UpdatePopupIndicatorL
// -----------------------------------------------------------------------------
//
void CAknIndicatorPopup::UpdatePopupIndicatorL( TInt aIndicatorUid )
    {
    iContent->HandlePluginUpdateL( aIndicatorUid );
    }


// -----------------------------------------------------------------------------
// CAknIndicatorPopup::UpdateAllPopupIndicatorsL
// -----------------------------------------------------------------------------
//
void CAknIndicatorPopup::UpdateAllPopupIndicatorsL()
    {
    iContent->UpdateAllIndicatorsL();
    }


// ---------------------------------------------------------------------------
// From base class MCoeControlObserver.
// Handles events received from the popup content.
// ---------------------------------------------------------------------------
//
void CAknIndicatorPopup::HandleControlEventL( CCoeControl* aControl,
                                              TCoeEvent aEventType )
    {
    if ( aControl == iContent )
        {
        switch ( aEventType )
            {
            case CAknIndicatorPopupContent::EAknIndicatorPopupTapEvent:
                {
                HidePopup();
                break;
                }
            default:
                {
                break;
                }
            }
        }
    }


// ---------------------------------------------------------------------------
// Default constructor.
// ---------------------------------------------------------------------------
//
CAknIndicatorPopup::CAknIndicatorPopup()
    {
    }


// ---------------------------------------------------------------------------
// CAknIndicatorPopup::ConstructL
// ---------------------------------------------------------------------------
//
void CAknIndicatorPopup::ConstructL()
    {
    iContent = CAknIndicatorPopupContent::NewL();
    iContent->SetObserver( this );

    iController = CAknPreviewPopUpController::NewL(
        *iContent,
        CAknPreviewPopUpController::ELayoutSubMenu | CAknPreviewPopUpController::EDontClose );

    iController->SetPopUpShowDelay( KDefaultPopUpShowDelay );
    iController->SetPopUpHideDelay( KDefaultPopUpHideDelay );

    SetPosition( TPoint( 0, 0 ) );
    }
