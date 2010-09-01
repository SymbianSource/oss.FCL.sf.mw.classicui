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
* Description:  Preview pop-up controller.
*
*/


// INCLUDE FILES
#include "AknPreviewPopUpController.h"
#include "AknPreviewPopUpContentProvider.h"
#include "AknPreviewPopUp.h"
#include <AknUtils.h>
#include <aknappui.h>
#include <AknSgcc.h>
#include <w32std.h>
#include <aknlayoutscalable_avkon.cdl.h>
#include <layoutmetadata.cdl.h>

// CONSTANTS
const TInt KDefaultPopUpShowDelay = 1000000;
const TInt KDefaultPopUpHideDelay = 10000000;
const TInt KObserverArrayGranularity = 1;

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CAknPreviewPopUpController::NewL
// -----------------------------------------------------------------------------
//
EXPORT_C CAknPreviewPopUpController* CAknPreviewPopUpController::NewL(
        CCoeControl& aContent, 
        MAknPreviewPopUpContentProvider& aContentProvider )
    {
    return CAknPreviewPopUpController::NewL( aContent, 
                                             aContentProvider, 
                                             ELayoutDefault );
    }


// -----------------------------------------------------------------------------
// CAknPreviewPopUpController::NewL
// -----------------------------------------------------------------------------
//
EXPORT_C CAknPreviewPopUpController* CAknPreviewPopUpController::NewL(
        CCoeControl& aContent )
    {
    return CAknPreviewPopUpController::NewL( aContent, ELayoutDefault);
    }


// -----------------------------------------------------------------------------
// CAknPreviewPopUpController::NewL
// -----------------------------------------------------------------------------
//
EXPORT_C CAknPreviewPopUpController* CAknPreviewPopUpController::NewL(
        CCoeControl& aContent, 
        MAknPreviewPopUpContentProvider& aContentProvider,
        const TInt aStyle )
    {
    CAknPreviewPopUpController* self = new ( ELeave ) CAknPreviewPopUpController(
        &aContentProvider );
    CleanupStack::PushL( self );
    self->ConstructL( aContent, aStyle );
    CleanupStack::Pop( self );
    return self;
    }


// -----------------------------------------------------------------------------
// CAknPreviewPopUpController::NewL
// -----------------------------------------------------------------------------
//
EXPORT_C CAknPreviewPopUpController* CAknPreviewPopUpController::NewL( 
        CCoeControl& aContent,
        const TInt aStyle )
    {
    CAknPreviewPopUpController* self = new ( ELeave ) CAknPreviewPopUpController(
        NULL );
    CleanupStack::PushL( self );
    self->ConstructL( aContent, aStyle );
    CleanupStack::Pop( self );        
    return self;        
    }


// -----------------------------------------------------------------------------
// CAknPreviewPopUpController::CAknPreviewPopUpController
// -----------------------------------------------------------------------------
//
CAknPreviewPopUpController::CAknPreviewPopUpController(
        MAknPreviewPopUpContentProvider* aContentProvider )
    : CTimer( CActive::EPriorityStandard ),
      iContentProvider( aContentProvider ),
      iPopUpShowDelay( KDefaultPopUpShowDelay ),
      iPopUpHideDelay( KDefaultPopUpHideDelay ),
      iObservers( KObserverArrayGranularity ),
      iResetting( EFalse )
    {
        
    }


// -----------------------------------------------------------------------------
// CAknPreviewPopUpController::ConstructL
// -----------------------------------------------------------------------------
//
void CAknPreviewPopUpController::ConstructL( CCoeControl& aContent, 
                                             const TInt aStyle )

    {
    iPopUp = CAknPreviewPopUp::NewL( aContent, *this, aStyle );
    CTimer::ConstructL();
    CActiveScheduler::Add( this );
    }


// -----------------------------------------------------------------------------
// CAknPreviewPopUpController::~CAknPreviewPopUpController
// -----------------------------------------------------------------------------
//
CAknPreviewPopUpController::~CAknPreviewPopUpController()
    {
    Cancel();
    delete iPopUp;
    iObservers.Reset();
    }


// -----------------------------------------------------------------------------
// CAknPreviewPopUpController::ContentSizeInLayout
// -----------------------------------------------------------------------------
//
EXPORT_C CAknPreviewPopUpController::TAknPreviewPopUpContentSize 
    CAknPreviewPopUpController::ContentSizeInLayout()
    {
    // feature removed
    return CAknPreviewPopUpController::ELarge;        
    }


// -----------------------------------------------------------------------------
// CAknPreviewPopUpController::SetPopUpShowDelay
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknPreviewPopUpController::SetPopUpShowDelay(
        const TTimeIntervalMicroSeconds32& aDelay )
    {
    iPopUpShowDelay = aDelay;
    }

    
 // -----------------------------------------------------------------------------
// CAknPreviewPopUpController::SetPopUpHideDelay
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknPreviewPopUpController::SetPopUpHideDelay(
        const TTimeIntervalMicroSeconds32& aDelay )
    {
    iPopUpHideDelay = aDelay;
    }

   
// -----------------------------------------------------------------------------
// CAknPreviewPopUpController::ShowPopUp
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknPreviewPopUpController::ShowPopUp()
    {
    Cancel();
    UpdateContentSize();
    iState = EShowing;
    After( iPopUpShowDelay );
    }


// -----------------------------------------------------------------------------
// CAknPreviewPopUpController::HidePopUp
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknPreviewPopUpController::HidePopUp()
    {
    Cancel();
    iPopUp->Hide();
    }


// -----------------------------------------------------------------------------
// CAknPreviewPopUpController::ContentReady
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknPreviewPopUpController::ContentReady()
    {
    TRequestStatus* status = &iStatus;
    User::RequestComplete( status, KErrNone );
    }


// -----------------------------------------------------------------------------
// CAknPreviewPopUpController::SetPosition
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknPreviewPopUpController::SetPosition( const TPoint& aPoint )
    {
    if ( !( iPopUp->Flags() & EFixedMode ) )
        {
        TPoint askedPoint( aPoint );
        TSize popupSize( iPopUp->MinimumSize() );
        
        // if popup's position is to be mirrored then open it right from the asked
        // location
        if ( ( iPopUp->Flags() & EAutoMirror ) && AknLayoutUtils::LayoutMirrored() )
            {
            askedPoint.iX += popupSize.iWidth;
            }
        
        TBool resize = EFalse;

        if ( popupSize != iPopUp->Size() )
            {
            resize = ETrue;
            }

        // Adjust the position if the popup would go outside of the screen
        // rect with the given position.
        TRect screenRect;
        AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EScreen, screenRect );
        TInt screenWidth( screenRect.Width() );
        TInt screenHeight( screenRect.Height() );

        TPoint finalPosition;

        // Resize if the popup is too wide.
        if ( popupSize.iWidth > screenWidth )
            {
            resize = ETrue;
            popupSize.iWidth = screenWidth;
            }

        // Resize if the popup is too tall.
        if ( popupSize.iHeight > screenHeight )
            {
            resize = ETrue;
            popupSize.iHeight = screenHeight;
            }

        // Default horizontal position is left from the given point.
        if ( askedPoint.iX - popupSize.iWidth >= screenRect.iTl.iX )
            {
            finalPosition.iX = askedPoint.iX - popupSize.iWidth;
            }
        else
            {
            // outside left border, move to left border
            finalPosition.iX = screenRect.iTl.iX;
            }

        // Check the right border.
        if ( finalPosition.iX + popupSize.iWidth > screenRect.iBr.iX )
            {
            finalPosition.iX = screenRect.iBr.iX - popupSize.iWidth;
            }

        // Default vertical position is up from the given point.
        // Coordinates grow from top to bottom.
        if ( askedPoint.iY > screenRect.iTl.iY )
            {
            finalPosition.iY = askedPoint.iY;
            }
        else
            {
            // Outside top border, move to top border.
            finalPosition.iY = screenRect.iTl.iY;
            }

        // Outside bottom border, move to bottom border.
        if ( ( askedPoint.iY + popupSize.iHeight ) > screenRect.iBr.iY )
            {
            finalPosition.iY = screenRect.iBr.iY - popupSize.iHeight;
            }

        if ( resize )
            {
            iPopUp->SetSize( popupSize );
            }

        iPopUp->SetPosition( finalPosition );
        }
    }


// -----------------------------------------------------------------------------
// CAknPreviewPopUpController::SetPositionByHighlight
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknPreviewPopUpController::SetPositionByHighlight( 
    const TRect& aHighlightRect )
    {
    if ( !( iPopUp->Flags() & EFixedMode ) )
        {
        TRect rect( AknLayoutUtils::HighlightBasedRect( aHighlightRect, iPopUp ) );

        // Call SetRect only when truly necessary in order to avoid unnecessary 
        // SizeChanged calls in the pop-up side.
        if ( rect.Size() != iPopUp->Size() )
            {
            iPopUp->SetRect( rect );
            }
        else
            {
            iPopUp->SetPosition( rect.iTl );
            }
        }
    }

    
// -----------------------------------------------------------------------------
// CAknPreviewPopUpController::AddObserverL
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknPreviewPopUpController::AddObserverL(
        const MAknPreviewPopUpObserver& aObserver )
    {
    iObservers.InsertInAddressOrderL( &aObserver );
    }

        
// -----------------------------------------------------------------------------
// CAknPreviewPopUpController::RemoveObserver
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknPreviewPopUpController::RemoveObserver(
        const MAknPreviewPopUpObserver& aObserver )
    {
    TInt index = iObservers.FindInAddressOrder( &aObserver );
    
    if ( index != KErrNotFound )
        {
        iObservers.Remove( index );
        }
    }

        
// -----------------------------------------------------------------------------
// CAknPreviewPopUpController::UpdateContentSize
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknPreviewPopUpController::UpdateContentSize()
    {
    TSize popupSize( iPopUp->MinimumSize() );

    if ( popupSize != iPopUp->Size() )
        {
        iPopUp->SetSize( popupSize );
        }
    }


// -----------------------------------------------------------------------------
// CAknPreviewPopUpController::Size
// -----------------------------------------------------------------------------
//
EXPORT_C TSize CAknPreviewPopUpController::Size() const
    {
    return iPopUp->Size();
    }


// -----------------------------------------------------------------------------
// CAknPreviewPopUpController::SetHeadingTextL
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknPreviewPopUpController::SetHeadingTextL( const TDesC& aText )
    {
    iPopUp->SetHeadingTextL( aText );
    }


// -----------------------------------------------------------------------------
// CAknPreviewPopUpController::NotifyObservers
// -----------------------------------------------------------------------------
//
void CAknPreviewPopUpController::NotifyObservers(
        MAknPreviewPopUpObserver::TPreviewPopUpEvent aEvent )
    {
    for ( TInt i = 0; i < iObservers.Count(); ++i )
        {
        TRAP_IGNORE( iObservers[i]->HandlePreviewPopUpEventL( this, aEvent ) );
        }
    }


// -----------------------------------------------------------------------------
// CAknPreviewPopUpController::RunL
// -----------------------------------------------------------------------------
//
void CAknPreviewPopUpController::RunL()
    {
    switch ( iState )
        {
        case EShowing:
            if ( iContentProvider )
                {
                iState = EBuildingContent;
                iStatus = KRequestPending;
                SetActive();
                iContentProvider->StartContentBuildingL();
                }
            else
                {
                iPopUp->Show();
                
                if ( iPopUpHideDelay.Int() > 0 && 
                     !( iPopUp->Flags() & EPermanentMode ) )
                    {
                    iState = EHiding;
                    After( iPopUpHideDelay );
                    }
                }
            break;
            
        case EHiding:
            iPopUp->Hide();
            break;
            
        case EBuildingContent:
            iPopUp->Show();

            if ( iPopUpHideDelay.Int() > 0 && 
                 !( iPopUp->Flags() & EPermanentMode ) )
                {
                iState = EHiding;
                After( iPopUpHideDelay );
                }
            break;
            
        default:
            User::Panic( _L( "Preview pop-up" ), KErrUnknown );
        }
    }


// -----------------------------------------------------------------------------
// CAknPreviewPopUpController::DoCancel
// -----------------------------------------------------------------------------
//
void CAknPreviewPopUpController::DoCancel()
    {
    if ( iState == EBuildingContent )
        {
        iContentProvider->CancelContentBuilding();
        if ( iStatus.Int() == KRequestPending )
            {
            TRequestStatus* status = &iStatus;
            User::RequestComplete( status, KErrCancel );    
            }
        }
    else
        {
        CTimer::DoCancel();

        if(iResetting)
        	{       	
        	iResetting = EFalse;
        	}
        else
        	{
        	iPopUp->Hide();	
        	}
        }
    }


// -----------------------------------------------------------------------------
// CAknPreviewPopUpController::ResetTimer
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknPreviewPopUpController::ResetTimer()
    {
	iResetting = ETrue;
	Cancel();
	After( iPopUpHideDelay );
    }


// -----------------------------------------------------------------------------
// CAknPreviewPopUpController::RunError
// -----------------------------------------------------------------------------
//
TInt CAknPreviewPopUpController::RunError( TInt /*aError*/ )
    {
    return KErrNone;
    }
    
//  End of File  
