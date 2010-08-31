/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:   AknStylusPopUpMenu physics handler
*
*/


#include <stdlib.h>
#include <aknphysics.h>
#include <aknphysicsobserveriface.h>
#include <AknUtils.h>

#include <touchfeedback.h>
#include "aknstyluspopupmenuphysicshandler.h"
#include "aknstyluspopupmenucontent.h"

const TInt KNoItemSelected( -1 ); 



// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CAknStylusPopUpMenuPhysicsHandler::NewL
// ---------------------------------------------------------------------------
//
 CAknStylusPopUpMenuPhysicsHandler* CAknStylusPopUpMenuPhysicsHandler::NewL(
    CAknStylusPopUpMenuContent* aPopUpMenuContent )
    {
    CAknStylusPopUpMenuPhysicsHandler* self = 
        CAknStylusPopUpMenuPhysicsHandler::NewLC( aPopUpMenuContent );
    CleanupStack::Pop( self );
    return self;
    }


// ---------------------------------------------------------------------------
// CAknStylusPopUpMenuPhysicsHandler::NewLC
// ---------------------------------------------------------------------------
//
CAknStylusPopUpMenuPhysicsHandler* CAknStylusPopUpMenuPhysicsHandler::NewLC( 
    CAknStylusPopUpMenuContent* aPopUpMenuContent )
    {
    CAknStylusPopUpMenuPhysicsHandler* self 
        = new ( ELeave ) CAknStylusPopUpMenuPhysicsHandler( aPopUpMenuContent );
    CleanupStack::PushL( self );
    self->ConstructL();
    return self;
    }


// ---------------------------------------------------------------------------
// CAknStylusPopUpMenuPhysicsHandler::~CAknStylusPopUpMenuPhysicsHandler
// ---------------------------------------------------------------------------
//
CAknStylusPopUpMenuPhysicsHandler::~CAknStylusPopUpMenuPhysicsHandler()
    {
    delete iPhysics;
    }


// ---------------------------------------------------------------------------
// CAknStylusPopUpMenuPhysicsHandler::HandlePointerEventL
// ---------------------------------------------------------------------------
//
void CAknStylusPopUpMenuPhysicsHandler::HandlePointerEventL( const TPointerEvent& aPointerEvent )
    {

    // EButton1Down
    if ( aPointerEvent.iType == TPointerEvent::EButton1Down )
        {
        
        TBool wasScrolling = ( iPhysics->OngoingPhysicsAction() != 
            CAknPhysics::EAknPhysicsActionNone );
        
        iPosition = aPointerEvent.iPosition;
        iStartPosition = aPointerEvent.iPosition;

        StopPhysics();
        iStartTime.HomeTime();
        iPanningActivated = EFalse;
        iPressedDown = ETrue;
                
        
        // if pointer event (EButton1Down) inside items rect, launch higlight timer
        // if content was not flicking, set also item to be selected
        
        TPoint adjustedPosition( aPointerEvent.iPosition + TPoint(0, Offset() ) );
        TInt item = iPopUpMenuContent->ContainingItem( adjustedPosition );
        if ( item != KNoItemSelected )
            {
            if ( !wasScrolling )
                {
                SetHighlight( item );
                CCoeEnv::Static()->WsSession().Finish();
                }

            MTouchFeedback* feedback = MTouchFeedback::Instance();
            if ( feedback )
                {
                feedback->InstantFeedback( NULL,
                                           ETouchFeedbackBasicItem,
                                           aPointerEvent );
                }
            }
        }
    
    // EDrag    
   
    if ( aPointerEvent.iType == TPointerEvent::EDrag )
        {
        TInt distanceFromStart( iStartPosition.iY - aPointerEvent.iPosition.iY );
        
        if ( !iPanningActivated && Abs( distanceFromStart ) > DragThreshold() )
            {
            iPanningActivated = ETrue;
            iPosition = aPointerEvent.iPosition;

            // clear highlight
            iPopUpMenuContent->SetHighlight( KNoItemSelected );
            }
			
        if ( iPanningActivated )
            {
            TInt deltaY( iPosition.iY - aPointerEvent.iPosition.iY );
            iPosition = aPointerEvent.iPosition;
            iPhysics->RegisterPanningPosition( TPoint( 0, deltaY ) );
            }
        }

    // EButton1Up   
   
    if ( aPointerEvent.iType == TPointerEvent::EButton1Up )
        {
        iPressedDown = EFalse;              
        TPoint adjustedPosition( aPointerEvent.iPosition + TPoint(0, Offset() ) );
        TInt item = iPopUpMenuContent->ContainingItem( adjustedPosition );
        if ( item != KNoItemSelected )
            {
        MTouchFeedback* feedback = MTouchFeedback::Instance();
        if ( feedback )
            {
                feedback->InstantFeedback( NULL,
                                           ETouchFeedbackBasicItem,
                                           ETouchFeedbackVibra,
                                           aPointerEvent );
                }
            }
 
        TPoint distance( 0, iStartPosition.iY - aPointerEvent.iPosition.iY );
        if ( iPhysics->StartPhysics( distance, iStartTime ) )
            {
            return;
            }
            
        // select item 
        if ( !iPanningActivated && 
                iPopUpMenuContent->CurrentItem() != KNoItemSelected )
            {
            if ( iViewRect.Contains( aPointerEvent.iPosition ) )
                {
                iPopUpMenuContent->SelectItem( 
                        iPopUpMenuContent->CurrentItem() );
                }
            else 
                {
                // Clear highlight
                SetHighlight( KNoItemSelected );
                }
            }
        }
   }

// ---------------------------------------------------------------------------
// CAknStylusPopUpMenuPhysicsHandler::SetViewRect
// ---------------------------------------------------------------------------
//
void CAknStylusPopUpMenuPhysicsHandler::SetViewRect( const TRect& aRect )
    {
    iViewRect = aRect;
    }

// ---------------------------------------------------------------------------
// CAknStylusPopUpMenuPhysicsHandler::SetItemHeight
// ---------------------------------------------------------------------------
//
void CAknStylusPopUpMenuPhysicsHandler::SetItemHeight( TInt aItemHeight )
    {
    iItemHeight = aItemHeight;
    }
    
// ---------------------------------------------------------------------------
// CAknStylusPopUpMenuPhysicsHandler::SetWorldHeight
// ---------------------------------------------------------------------------
//
void CAknStylusPopUpMenuPhysicsHandler::SetWorldHeight( TInt aWorldHeight )
    {
    iWorldHeight = aWorldHeight;
    }

// ---------------------------------------------------------------------------
// CAknStylusPopUpMenuPhysicsHandler::Offset
// ---------------------------------------------------------------------------
//
TInt CAknStylusPopUpMenuPhysicsHandler::Offset() const 
    {
    if ( iItemHeight == 0 )
        {
        return 0;
        }
        
    if ( iScrollIndex < 0 )
        {
        return iScrollIndex;
        }
    
    if ( iScrollIndex >= iWorldHeight - iViewRect.Height() )
        {
        return iScrollIndex - ( iWorldHeight - iViewRect.Height() );
        }   
    
    return iScrollIndex % iItemHeight;
    }


// ---------------------------------------------------------------------------
// CAknStylusPopUpMenuPhysicsHandler::InitPhysicsL
// ---------------------------------------------------------------------------
//   
void CAknStylusPopUpMenuPhysicsHandler::InitPhysicsL()
    {
    TSize worldSize( iViewRect.Width(), iWorldHeight );
    TSize viewSize( iViewRect.Width(), iViewRect.Height() );
    
    iPhysics->InitPhysicsL( worldSize, viewSize, EFalse );
    iPhysics->UpdateViewWindowControl( iPopUpMenuContent );
    }
    


// ---------------------------------------------------------------------------
// CAknStylusPopUpMenuPhysicsHandler::HandleScrollEvent
// ---------------------------------------------------------------------------
//     
void CAknStylusPopUpMenuPhysicsHandler::HandleScrollEvent( TInt aNewScrollIndex )
    {
    iScrollIndex = aNewScrollIndex;
    ScrollView();                        
    }


// ---------------------------------------------------------------------------
// CAknStylusPopUpMenuPhysicsHandler::Reset
// ---------------------------------------------------------------------------
//
void CAknStylusPopUpMenuPhysicsHandler::Reset()
    {
    iPrevOffset = -1;
    iPrevTopmostItem = -1;
    iScrollIndex = 0;
    }


// ---------------------------------------------------------------------------
// CAknStylusPopUpMenuPhysicsHandler::ViewPositionChanged
// ---------------------------------------------------------------------------
//
void CAknStylusPopUpMenuPhysicsHandler::ViewPositionChanged(
    const TPoint& aNewPosition,
    TBool aDrawNow,
    TUint /*aFlags*/ )
    {
    iScrollIndex = aNewPosition.iY - iViewRect.Height() / 2;
    
    ScrollView( aDrawNow );
    }
    
    
// ---------------------------------------------------------------------------
// CAknStylusPopUpMenuPhysicsHandler::PhysicEmulationEnded
// ---------------------------------------------------------------------------
//    
void CAknStylusPopUpMenuPhysicsHandler::PhysicEmulationEnded()
    {
    }


// ---------------------------------------------------------------------------
// CAknStylusPopUpMenuPhysicsHandler::ViewPosition
// ---------------------------------------------------------------------------
//    
TPoint CAknStylusPopUpMenuPhysicsHandler::ViewPosition() const
    {
    return TPoint( iViewRect.Width() / 2, iScrollIndex + iViewRect.Height() / 2 ); 
    }

// ---------------------------------------------------------------------------
// CAknStylusPopUpMenuPhysicsHandler::CAknStylusPopUpMenuPhysicsHandler
// ---------------------------------------------------------------------------
//
CAknStylusPopUpMenuPhysicsHandler::CAknStylusPopUpMenuPhysicsHandler( 
    CAknStylusPopUpMenuContent* aPopUpMenuContent )
    :
    iPopUpMenuContent( aPopUpMenuContent ),
    iPhysics( NULL ),
    iPrevOffset( -1 ),
    iPrevTopmostItem( -1 ),
    iOffsetItemCount( 0 )
    {
    }


// ---------------------------------------------------------------------------
// CAknStylusPopUpMenuPhysicsHandler::ConstructL
// ---------------------------------------------------------------------------
//
void CAknStylusPopUpMenuPhysicsHandler::ConstructL()
    {
    iPhysics = CAknPhysics::NewL( *this, iPopUpMenuContent );
    }


// ---------------------------------------------------------------------------
// CAknStylusPopUpMenuPhysicsHandler::DragThreshold
// ---------------------------------------------------------------------------
//     
TInt CAknStylusPopUpMenuPhysicsHandler::DragThreshold()
    {
    return iPhysics->DragThreshold();
    }




// ---------------------------------------------------------------------------
// CAknStylusPopUpMenuPhysicsHandler::SetHighlight
// ---------------------------------------------------------------------------
//     
void CAknStylusPopUpMenuPhysicsHandler::SetHighlight( TInt aItem )
    {
    iPopUpMenuContent->SetHighlight( aItem );
    }

// ---------------------------------------------------------------------------
// CAknStylusPopUpMenuPhysicsHandler::ScrollView
// ---------------------------------------------------------------------------
//     
void CAknStylusPopUpMenuPhysicsHandler::ScrollView( TBool aDrawNow )
    {
    if ( iItemHeight != 0 )
        {
        TInt scrollIndex( Min( iScrollIndex, iWorldHeight - iViewRect.Height() ) );
        TInt topmostItem( scrollIndex / iItemHeight );
        
        // Update view based on topmostItem and offset.
        // Offset is retrieved from Physics handler by PopupMenuContent
        // inside this function call.
        
        // Update only if topmost item or offset changed 
        if ( aDrawNow &&
             ( topmostItem != iPrevTopmostItem || Offset() != iPrevOffset ) )
            {
            iPopUpMenuContent->UpdateView( topmostItem );
            }

        iPrevOffset = Offset();
        iPrevTopmostItem = topmostItem;    
        
        //when appear or dispear a tiem,a feedback was given.
        if ( abs( iPrevOffset ) <= iViewRect.Height()
              && ( iPrevOffset/iItemHeight ) != iOffsetItemCount )
            {
            if ( iPhysics )
                {
                TTouchFeedbackType feedbackType = ETouchFeedbackVibra;
                switch( iPhysics->OngoingPhysicsAction() )
                    {
                    case CAknPhysics::EAknPhysicsActionDragging:
                        {
                        feedbackType = static_cast<TTouchFeedbackType>
                                  ( ETouchFeedbackVibra | ETouchFeedbackAudio );
                        }
                    case CAknPhysics::EAknPhysicsActionFlicking:
                    case CAknPhysics::EAknPhysicsActionBouncing:
                        {
                        MTouchFeedback* feedback = MTouchFeedback::Instance();
                        if ( feedback )
                            {
                            feedback->InstantFeedback( iPopUpMenuContent,
                                                    ETouchFeedbackSensitiveItem,
                                                    feedbackType,
                                                    TPointerEvent() );
                            }
                        break;
                        }
                    default:
                        break;
                    }
                }
            }
        iOffsetItemCount = iPrevOffset/iItemHeight;
        }
    }

// ---------------------------------------------------------------------------
// CAknStylusPopUpMenuPhysicsHandler::StopPhysics
// ---------------------------------------------------------------------------
//
void CAknStylusPopUpMenuPhysicsHandler::StopPhysics()
    {
    iPhysics->StopPhysics();
    iPhysics->ResetFriction();
    }
