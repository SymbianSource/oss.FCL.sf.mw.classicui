/*
* Copyright (c) 2005-2009 Nokia Corporation and/or its subsidiary(-ies).
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
    CAknPreviewPopUpController* aPopup ) 
    : iPosition ( aPoint ),
     iMenuObserver( aObserver ),
     iPreviewPopup( aPopup ),
     iPositionType( EPositionTypeLeftTop )
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
    TRAPD( err, 
           iController = CAknPreviewPopUpController::NewL( *iContent,
                   CAknPreviewPopUpController::ELayoutSubMenu | 
                   CAknPreviewPopUpController::EAutoMirror |
                   CAknPreviewPopUpController::EDontClose ) );
    if ( err )
        {
        return;
        }
            
    iController->SetPopUpShowDelay( KDefaultPopUpShowDelay );
    iController->SetPopUpHideDelay( KDefaultPopUpHideDelay );
    iContent->Parent()->DrawableWindow()->SetNonFading(ETrue);
    
    TSize size(iController->Size());
    iController->ShowPopUp();

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
EXPORT_C void CAknStylusPopUpMenu::SetPosition( const TPoint& aPoint, TPositionType aPosType )
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
	// calculate to right-top corner by aPosType and popup menu size
    switch ( aPosType )	
        {
        case EPositionTypeRightTop: 
            break;
        case EPositionTypeLeftTop:
            if( AknLayoutUtils::LayoutMirrored() ) 
                {
                adjustedPoint.iX -= menuSize.iWidth;
                }
            else
                {
                adjustedPoint.iX += menuSize.iWidth;
                }
            break;   
        case EPositionTypeRightBottom:
            adjustedPoint.iY -= menuSize.iHeight;
            break;
        case EPositionTypeLeftBottom: 
            if( AknLayoutUtils::LayoutMirrored() ) 
                {
                adjustedPoint.iX -= menuSize.iWidth;
                }
            else
                {
                adjustedPoint.iX += menuSize.iWidth;
                }
            adjustedPoint.iY -= menuSize.iHeight;
            break;    
        default:
            break;  
    
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
        if ( iPreviewPopup )
            {
            iPreviewPopup->HidePopUp();
            }
        if ( iController )
            {
            iController->HidePopUp();
            }

        if ( iMenuObserver )
            {
            iFlags.Set( EIdleDisabled );
            TBool isDeleted = EFalse;
            iIsDeleted = &isDeleted;

            iMenuObserver->ProcessCommandL( iContent->CurrentCommandId() );

            if ( isDeleted )
                {
                return;
                }

            iIsDeleted = NULL;
            iFlags.Clear( EIdleDisabled );
            }

        StartControllerIdleL();
        }
    else if ( aControl && aEventType == EEventRequestExit )
        {
        if ( iPreviewPopup )
            {
            iPreviewPopup->HidePopUp();
            }
        if ( iController )
            {
            iController->HidePopUp();
            }      

        StartControllerIdleL();
        }
    else if ( aControl && aEventType == EEventRequestCancel )
        {
        if ( iMenuObserver )
            {
            iFlags.Set( EIdleDisabled );
            iMenuObserver->ProcessCommandL( KErrCancel );
            iFlags.Clear( EIdleDisabled );
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
