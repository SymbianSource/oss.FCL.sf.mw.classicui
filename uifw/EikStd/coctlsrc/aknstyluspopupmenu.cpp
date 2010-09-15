/*
* Copyright (c) 2005-2010 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Interface for controlling stylus popup menu.
*
*/


#include <AknPreviewPopUpController.h>
#include <eikmobs.h>
#include <AknUtils.h>
#include <barsread.h>
#include <aknlayoutscalable_avkon.cdl.h>
#include <eikapp.h>
#include <aknappui.h>
#include <AknDef.h>
#include <touchfeedback.h>
#include <akntranseffect.h>
#include <akntransitionutils.h>
#include "aknstyluspopupmenu.h"
#include "aknstyluspopupmenucontent.h"

const TInt KDefaultPopUpShowDelay = 0;
const TInt KDefaultPopUpHideDelay = 6000000; // 6 seconds

enum TStylusPopUpFlags
    {
    EIdleDisabled // usage of iControllerIdle is disabled 
    };

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Default constructor
// ---------------------------------------------------------------------------
//
CAknStylusPopUpMenu::CAknStylusPopUpMenu( MEikMenuObserver* aObserver, 
    const TPoint& aPoint,
    CAknPreviewPopUpController* aPopup,
    const TInt aFlags )
    : iPosition ( aPoint ),
     iMenuObserver( aObserver ),
     iPreviewPopup( aPopup ),
     iPositionType( EPositionTypeLeftTop ),
     iModeFlags ( aFlags )
    {
    }


// ---------------------------------------------------------------------------
// CAknStylusPopUpMenu::ConstructL
// ---------------------------------------------------------------------------
//

void CAknStylusPopUpMenu::ConstructL()
    {
    iContent = CAknStylusPopUpMenuContent::NewL( *this );
    
    iContent->SetObserver(this); 
    }


// ---------------------------------------------------------------------------
// CAknStylusPopUpMenu::NewL
// ---------------------------------------------------------------------------
//
EXPORT_C CAknStylusPopUpMenu* CAknStylusPopUpMenu::NewL( 
                            MEikMenuObserver* aObserver, const TPoint& aPoint,
                            CAknPreviewPopUpController* aPopup )
    {
    CAknStylusPopUpMenu* self = CAknStylusPopUpMenu::NewLC( aObserver, 
                                                            aPoint,
                                                            aPopup );
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// CAknStylusPopUpMenu::NewL
// ---------------------------------------------------------------------------
//
CAknStylusPopUpMenu* CAknStylusPopUpMenu::NewL( MEikMenuObserver* aObserver,
        const TPoint& aPoint,
        CAknPreviewPopUpController* aPopup,
        const TInt aFlags )
    {
    CAknStylusPopUpMenu* self = new ( ELeave ) CAknStylusPopUpMenu( aObserver,
                                                                    aPoint,
                                                                    aPopup,
                                                                    aFlags );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// CAknStylusPopUpMenu::NewL
// ---------------------------------------------------------------------------
//
EXPORT_C CAknStylusPopUpMenu* CAknStylusPopUpMenu::NewL( 
                            MEikMenuObserver* aObserver, const TPoint& aPoint )
    {
    CAknStylusPopUpMenu* self = CAknStylusPopUpMenu::NewLC( aObserver, 
                                                            aPoint, NULL );
    CleanupStack::Pop( self );
    return self;
    }


// ---------------------------------------------------------------------------
// CAknStylusPopUpMenu::NewLC
// ---------------------------------------------------------------------------
//
EXPORT_C CAknStylusPopUpMenu* CAknStylusPopUpMenu::NewLC(
                            MEikMenuObserver* aObserver, const TPoint& aPoint,
                            CAknPreviewPopUpController* aPopup )
    {
    CAknStylusPopUpMenu* self = new ( ELeave ) CAknStylusPopUpMenu( aObserver,
                                                                    aPoint,
                                                                    aPopup );
    CleanupStack::PushL( self );
    self->ConstructL();
    return self;
    }


// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CAknStylusPopUpMenu::~CAknStylusPopUpMenu()
    {
    if ( iContent )
        {
        iContent->SetObserver(NULL);
        }
    if ( iIsDeleted )
        {
        *iIsDeleted = ETrue;
        iIsDeleted = NULL;
        }

    if ( iControllerIdle )
         {
         iControllerIdle->Cancel();
         }
    delete iControllerIdle;
    delete iController;
    delete iContent;
    }


// ---------------------------------------------------------------------------
// CAknStylusPopUpMenu::AddMenuItemL
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknStylusPopUpMenu::AddMenuItemL( const TDesC& aItem, 
                                                        const TInt aCommandId )
    {
    iContent->AddMenuItemL( aItem, aCommandId );
    }


// ---------------------------------------------------------------------------
// CAknStylusPopUpMenu::RemoveMenuItem
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknStylusPopUpMenu::RemoveMenuItem( const TInt aCommandId )
    {
    iContent->RemoveMenuItem( aCommandId );
    }


// ---------------------------------------------------------------------------
// CAknStylusPopUpMenu::SetItemDimmed
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknStylusPopUpMenu::SetItemDimmed( const TInt aCommandId, const TBool aDimmed )
    {
    iContent->SetItemDimmed( aCommandId, aDimmed );
    }


// ---------------------------------------------------------------------------
// CAknStylusPopUpMenu::ShowMenu
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknStylusPopUpMenu::ShowMenu()
    {
    // if contoller exists, re-use it .
    if ( !iController )
        {
        TInt err ( KErrNone );

        if ( iModeFlags & EConsumeKeyEvents )
            {
            TRAP( err, iController = CAknPreviewPopUpController::NewL(
                    *iContent,
                    CAknPreviewPopUpController::ELayoutSubMenu |
                    CAknPreviewPopUpController::EAutoMirror |
                    CAknPreviewPopUpController::EDontClose |
                    CAknPreviewPopUpController::EConsumeKeys ) );
            }
        else
            {
            TRAP( err, iController = CAknPreviewPopUpController::NewL(
                    *iContent,
                    CAknPreviewPopUpController::ELayoutSubMenu |
                    CAknPreviewPopUpController::EAutoMirror |
                    CAknPreviewPopUpController::EDontClose ) );
            }
        if ( err )
            {
            return;
            }
            
        iController->SetPopUpShowDelay( KDefaultPopUpShowDelay );
        iController->SetPopUpHideDelay( KDefaultPopUpHideDelay );
        }
    
    TSize size(iController->Size());
    iController->ShowPopUp();
    if ( AknLayoutUtils::PenEnabled() )
        {
        MTouchFeedback* feedback = MTouchFeedback::Instance();
        if ( feedback )
            {
            TTouchLogicalFeedback feedbackType = ETouchFeedbackPopUp;
            if ( CAknTransitionUtils::TransitionsEnabled( AknTransEffect::EComponentTransitionsOff ) )
                {
                feedbackType = ETouchFeedbackOptionsMenuOpened;
                }
            feedback->InstantFeedback(
                    iContent,
                    feedbackType,
                    ETouchFeedbackVibra,
                    TPointerEvent() );
            }
        }
    if ( size.iWidth == 0 && size.iHeight == 0 )
        {
        if ( iPositionType != KErrNotFound )
            {
            SetPosition( iPosition, TPositionType( iPositionType ) );
            }
        else
            {
            SetPosition( iPosition );
            }        
        }
    else
        {
        //position already adjusted.
        iController->SetPosition( iPosition );
        }
    
    }


// ---------------------------------------------------------------------------
// CAknStylusPopUpMenu::SetPosition
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknStylusPopUpMenu::SetPosition( const TPoint& aPoint )
    {
    SetPosition( aPoint, EPositionTypeLeftTop );
    }


// ---------------------------------------------------------------------------
// CAknStylusPopUpMenu::SetPosition 
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknStylusPopUpMenu::SetPosition( const TPoint& aPoint,
                                                TPositionType aPosType )
    {
    TPoint adjustedPoint( aPoint );
    if ( !iController )
        {
        iPosition = aPoint;
        iPositionType = aPosType;
        return;
        }

    iController->UpdateContentSize(); 
    TSize menuSize = iController->Size();

	// Calculate the position to right-top corner by aPosType and
    // popup menu size. Add also a margin between the screen borders and the
    // popup if the popup is too close to screen border.
    TBool layoutMirrored( AknLayoutUtils::LayoutMirrored() );
    TRect screenRect;
    AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EScreen,
                                       screenRect );
    
    // Margin is read from the popup window's layout data
    // (left parameter used).
    TAknWindowLineLayout popupWindowLayout(
        AknLayoutScalable_Avkon::popup_touch_menu_window( 0 ).LayoutLine() );
    TInt windowMargin = layoutMirrored ? popupWindowLayout.ir :
                                         popupWindowLayout.il;

    switch ( aPosType )	
        {
        case EPositionTypeRightTop:
            {
            break;
            }

        case EPositionTypeLeftTop:
            {
            if ( !layoutMirrored ) 
                {
                adjustedPoint.iX += menuSize.iWidth;
                }

            break;
            }

        case EPositionTypeRightBottom:
            {
            adjustedPoint.iY -= menuSize.iHeight;

            break;
            }

        case EPositionTypeLeftBottom:
            {
            if ( !layoutMirrored ) 
                {
                adjustedPoint.iX += menuSize.iWidth;
                }

            adjustedPoint.iY -= menuSize.iHeight;

            break;
            }

        default:
            {
            break;
            }
        }

    // Check if margins need to be added.
    TInt xLeftPos( layoutMirrored ? adjustedPoint.iX :
                                    adjustedPoint.iX - menuSize.iWidth );
    TInt xRightPos( layoutMirrored ? adjustedPoint.iX + menuSize.iWidth :
                                     adjustedPoint.iX );
    TInt xPosRightMargin( screenRect.iBr.iX - windowMargin );
    TInt xPosBottomMargin( screenRect.iBr.iY - windowMargin );

    if ( xLeftPos < windowMargin )
        {
        // Too close to the left side of the screen.
        adjustedPoint.iX = windowMargin + menuSize.iWidth;
        }
    else if ( xRightPos > xPosRightMargin )
        {
        // Too close to the right side of the screen.
        if ( layoutMirrored )
            {
            // In mirrored layout a left-top position must be provided
            // for the preview popup controller.
            adjustedPoint.iX = xPosRightMargin - menuSize.iWidth;
            }
        else
            {
            adjustedPoint.iX = xPosRightMargin;
            }
        }

    if ( adjustedPoint.iY < windowMargin )
        {
        // Too close to the top border of the screen.
        adjustedPoint.iY = windowMargin;
        }
    else if ( adjustedPoint.iY + menuSize.iHeight > xPosBottomMargin )
        {
        // Too close to the bottom border of the screen.
        adjustedPoint.iY = xPosBottomMargin - menuSize.iHeight;
        }
    
    iPosition = adjustedPoint;           
    iController->SetPosition( adjustedPoint ); 
    }


// ---------------------------------------------------------------------------
// CAknStylusPopUpMenu::ConstructFromResourceL
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknStylusPopUpMenu::ConstructFromResourceL( TResourceReader&
                                                           aReader )
    {
    TInt count = aReader.ReadInt16();
    TInt commandId;
    for ( TInt i = 0; i < count; i++ )
        {
        TPtrC text = aReader.ReadTPtrC();
        commandId = aReader.ReadInt32();
        iContent->AddMenuItemL( text, commandId );
        aReader.ReadInt32(); // extension link
        }
    }


// ---------------------------------------------------------------------------
// From class MCoeControlObserver.
// Handles stylus tap events by forwarding the event to the observer.
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknStylusPopUpMenu::HandleControlEventL( CCoeControl* aControl,
                                                        TCoeEvent aEventType )
    {
    if ( aControl && aEventType == EEventStateChanged )
        {
        HidePreviewPopup();

        if ( iMenuObserver )
            {
            TBool isAlreadySet = iFlags.IsSet( EIdleDisabled );

            iFlags.Set( EIdleDisabled );
            TBool isDeleted = EFalse;
            iIsDeleted = &isDeleted;

            CleanupStack::PushL( TCleanupItem( CleanLocalRef, this ) );
            iMenuObserver->ProcessCommandL( iContent->CurrentCommandId() );
            CleanupStack::Pop();
            
            if ( isDeleted )
                {
                return;
                }

            iIsDeleted = NULL;
            if( !isAlreadySet )
                {
                iFlags.Clear( EIdleDisabled );
                }
            }

        StartControllerIdleL();
        }
    else if ( aControl && aEventType == EEventRequestExit )
        {
        HidePreviewPopup();

        StartControllerIdleL();
        }
    else if ( aControl && aEventType == EEventRequestCancel )
        {
        HidePreviewPopup();

        if ( iMenuObserver )
            {
            TBool isAlreadySet = iFlags.IsSet( EIdleDisabled );

            iFlags.Set( EIdleDisabled );
            iMenuObserver->ProcessCommandL( KErrCancel );

            if( !isAlreadySet )
                {
                iFlags.Clear( EIdleDisabled );
                }

            }

        StartControllerIdleL();
        }
    }


// ---------------------------------------------------------------------------
// CAknStylusPopUpMenu::UpdatePosition
// ---------------------------------------------------------------------------
//
void CAknStylusPopUpMenu::UpdatePosition()
    {
	SetPosition( iPosition );
    }


// ---------------------------------------------------------------------------
// CAknStylusPopUpMenu::Clear
// ---------------------------------------------------------------------------
//
void CAknStylusPopUpMenu::Clear()
    {
    iContent->Clear();
    if ( iController )
        {
        iController->UpdateContentSize();
        }
    }


// ---------------------------------------------------------------------------
// CAknStylusPopUpMenu::HideMenu
// ---------------------------------------------------------------------------
//
void CAknStylusPopUpMenu::HideMenu()
    {
    if ( iController )
        {
        iController->HidePopUp();
        }
    }


// -----------------------------------------------------------------------------
// CAknStylusPopUpMenu::StartControllerIdleL
// -----------------------------------------------------------------------------
//
void CAknStylusPopUpMenu::StartControllerIdleL()
    {
    if ( !iFlags.IsSet( EIdleDisabled ) )
        {
        if ( !iControllerIdle )
            {
            iControllerIdle = CIdle::NewL( CActive::EPriorityIdle );
            }
    
        if ( !iControllerIdle->IsActive() && iController )
             {
             iControllerIdle->Start( TCallBack( ControllerCallBack, this ) );
             }
        }
    }

// -----------------------------------------------------------------------------
// CAknStylusPopUpMenu::ControllerCallBack
// -----------------------------------------------------------------------------
//
TInt CAknStylusPopUpMenu::ControllerCallBack( TAny* aThis )
    {
    CAknStylusPopUpMenu* self = static_cast<CAknStylusPopUpMenu*>( aThis );
    self->RemoveController();
    self->iFlags.Clear( EIdleDisabled );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CAknStylusPopUpMenu::RemoveController
// -----------------------------------------------------------------------------
//
void CAknStylusPopUpMenu::RemoveController()
    {
    if ( iController )
        {
        delete iController;
        iController = NULL;
        }
    }

// -----------------------------------------------------------------------------
// CAknStylusPopUpMenu::CleanLocalRef
// -----------------------------------------------------------------------------
//
void CAknStylusPopUpMenu::CleanLocalRef( TAny* aParam )
    {
    static_cast<CAknStylusPopUpMenu*>( aParam )->iIsDeleted = NULL;
    }

// -----------------------------------------------------------------------------
// Hide Preview Popups
// -----------------------------------------------------------------------------
//
void CAknStylusPopUpMenu::HidePreviewPopup()
    {
    if ( iPreviewPopup )
        {
        iPreviewPopup->HidePopUp();
        }

    if ( iController )
        {
        iController->HidePopUp();
        }
    }
