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

        // allowed rect
        TRect clientRect;
        AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EMainPane, clientRect );
        
        // Control is allowed to be on top of the status pane but it cannot
        // overlay either stacon pane or control pane.
        
        //switch ( iAvkonAppUi->StatusPane()->CurrentLayoutResId() )
        CEikStatusPaneBase* statusPane = CEikStatusPaneBase::Current();
        TInt currentStatusPaneLayoutResId = 0;
        if (statusPane)
            {
            currentStatusPaneLayoutResId = statusPane->CurrentLayoutResId();
            }
        else
            {
            // If this app does not have statuspane, then we ask the layout from AknCapServer.
            currentStatusPaneLayoutResId = CAknSgcClient::CurrentStatuspaneResource();        
            }
            
        switch ( currentStatusPaneLayoutResId )
            {
            case R_AVKON_STACON_PANE_LAYOUT_USUAL_SOFTKEYS_RIGHT:
            case R_AVKON_STACON_PANE_LAYOUT_USUAL_SOFTKEYS_LEFT:
            case R_AVKON_STACON_PANE_LAYOUT_IDLE_SOFTKEYS_RIGHT:
            case R_AVKON_STACON_PANE_LAYOUT_IDLE_SOFTKEYS_LEFT:
            case R_AVKON_STACON_PANE_LAYOUT_EMPTY_SOFTKEYS_RIGHT:
            case R_AVKON_STACON_PANE_LAYOUT_EMPTY_SOFTKEYS_LEFT:
                break;
                
            default:
                TRect statusPaneRect;
                AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EStatusPane, 
                                                   statusPaneRect );

                clientRect.BoundingRect( statusPaneRect );
            }

        TPoint finalPosition;

        // resize if the popup is too wide
        if ( popupSize.iWidth > clientRect.Width() )
            {
            resize = ETrue;
            popupSize.iWidth = clientRect.Width();
            }

        // resize if the popup is too tall
        if ( popupSize.iHeight > clientRect.Height() )
        	{
            resize = ETrue;
            popupSize.iHeight = clientRect.Height();
        	}

        // :winterTTr:
        // Auto mirror left <==> right if there is space on the other side.
        // Let the popup not drop out under the finger, if possible
        if ( ( askedPoint.iX <= clientRect.iBr.iX ) 
        	 && ( askedPoint.iX - popupSize.iWidth >=  clientRect.iTl.iX ) )
        	{
        	finalPosition.iX = askedPoint.iX - popupSize.iWidth ;
        	}
        else if ( askedPoint.iX > clientRect.iBr.iX )
        	{
        	if ( askedPoint.iX - popupSize.iWidth * 2 >= clientRect.iTl.iX )
        		{
        		finalPosition.iX = askedPoint.iX - popupSize.iWidth * 2 ;
        		}
        	else
        		{
        		finalPosition.iX = clientRect.iBr.iX - popupSize.iWidth ;
        		}
        	}
        else // askedPoint.iX - popupSize.iWidth <  clientRect.iTl.iX
        	{
        	if ( askedPoint.iX + popupSize.iWidth <= clientRect.iBr.iX )
        		{
        		finalPosition.iX = askedPoint.iX;
        		}
        	else
        		{
        		finalPosition.iX = clientRect.iTl.iX;
        		}
        	
        	}
        
        // :winterTTr:
        // Auto mirror top <==> buttom if there is space on the other side.
        // Let the popup not drop out under the finger, if possible
        if ( askedPoint.iY >= clientRect.iTl.iY 
        		&& askedPoint.iY + popupSize.iHeight <= clientRect.iBr.iY )
        	{
        	finalPosition.iY = askedPoint.iY;
        	}
        else if ( askedPoint.iY < clientRect.iTl.iY )
        	{
        	if ( askedPoint.iY + popupSize.iHeight *2 <= clientRect.iBr.iY )
        		{
        		finalPosition.iY = askedPoint.iY + popupSize.iHeight;
        		}
        	else
        		{
        		finalPosition.iY = clientRect.iTl.iY;
        		}
        	}
        else // askedPoint.iY + popupSize.iHeight > clientRect.iBr.iY
        	{
        	if ( askedPoint.iY - popupSize.iHeight >= clientRect.iTl.iY )
        		{
        		finalPosition.iY = askedPoint.iY - popupSize.iHeight;
        		}
        	else
        		{
        		finalPosition.iY = clientRect.iBr.iY - popupSize.iHeight;
        		}
        	
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
