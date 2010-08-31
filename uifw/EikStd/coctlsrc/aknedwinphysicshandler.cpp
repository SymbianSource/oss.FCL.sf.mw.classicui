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
 * Description:  EikEdwin physics handler
 *
 */

#include <aknphysics.h>
#include <aknphysicsobserveriface.h>
#include <babitflags.h>

#include "eikedwin.h"
#include "aknedwinphysicshandler.h"


const TInt KMaxWorldSize( 100000000 );  // Maximum world size

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CAknEdwinPhysicsHandler::NewL
// ---------------------------------------------------------------------------
//
CAknEdwinPhysicsHandler* CAknEdwinPhysicsHandler::NewL( CEikEdwin& aEdwin )
    {
    CAknEdwinPhysicsHandler* self = CAknEdwinPhysicsHandler::NewLC( aEdwin );
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// CAknEdwinPhysicsHandler::NewLC
// ---------------------------------------------------------------------------
//
CAknEdwinPhysicsHandler* CAknEdwinPhysicsHandler::NewLC( CEikEdwin& aEdwin )
    {
    CAknEdwinPhysicsHandler* self = new ( ELeave ) CAknEdwinPhysicsHandler(
            aEdwin );
    CleanupStack::PushL( self );
    self->ConstructL();
    return self;
    }

// ---------------------------------------------------------------------------
// CAknEdwinPhysicsHandler::~CAknEdwinPhysicsHandler
// ---------------------------------------------------------------------------
//
CAknEdwinPhysicsHandler::~CAknEdwinPhysicsHandler()
    {
    delete iPhysics;
    }

// ---------------------------------------------------------------------------
// CAknEdwinPhysicsHandler::HandlePointerEvent
// ---------------------------------------------------------------------------
//
void CAknEdwinPhysicsHandler::HandlePointerEvent(
    const TPointerEvent& aPointerEvent )
    {   
    if ( aPointerEvent.iType == TPointerEvent::EButton1Down &&
        iViewRect.Contains( aPointerEvent.iPosition ) &&
        iEventUnblockingAllowed )
        {
        BlockEvents( EFalse );
        iPreviousYCoordinate = - KMaxWorldSize;
        }
    if ( iEventsBlocked )
        {
	    return;
        }

    // Dragging/flicking logic    
    
    if ( aPointerEvent.iType == TPointerEvent::EButton1Down &&
        iViewRect.Contains( aPointerEvent.iPosition ) )
        {
        // Pointer down inside view rect, set flag to allow dragging 
        // and initialize values
        iFlags.Set( EFlagDraggingAllowed );
        iPrevPosition = aPointerEvent.iPosition;
        iStartPosition = aPointerEvent.iPosition;
        StopPhysics();

        iStartTime.HomeTime();
        iDragThresholdExceeded = EFalse;
        iFlags.Clear( EFlagBouncingUp );
        iFlags.Clear( EFlagBouncingDown );
        return;
        }
    if ( iFlags.IsClear( EFlagDraggingAllowed ) )
        {
        return;
        }

    if ( aPointerEvent.iType == TPointerEvent::EDrag )
        {
        if ( !iDragThresholdExceeded )
            {
            TInt drag( iStartPosition.iY - aPointerEvent.iPosition.iY );
            if ( Abs( drag ) > DragThreshold() )
                {
                iDragThresholdExceeded = ETrue;
                }
            }

        if ( iDragThresholdExceeded )
            {
            TInt deltaY( iPrevPosition.iY - aPointerEvent.iPosition.iY );
            iPrevPosition = aPointerEvent.iPosition;

            TPoint deltaPoint( 0, deltaY );
            iPhysics->RegisterPanningPosition( deltaPoint );
            }
        }
    else if ( aPointerEvent.iType == TPointerEvent::EButton1Up )
        {
        iFlags.Clear( EFlagDraggingAllowed );
        TPoint drag( 0, iStartPosition.iY - aPointerEvent.iPosition.iY );
        iPhysics->StartPhysics( drag, iStartTime );
        }
    }

// ---------------------------------------------------------------------------
// CAknEdwinPhysicsHandler::SetViewRect
// ---------------------------------------------------------------------------
//
void CAknEdwinPhysicsHandler::SetViewRect( const TRect& aRect )
    {
    iViewRect = aRect;
    }

// ---------------------------------------------------------------------------
// CAknEdwinPhysicsHandler::InitPhysicsL
// ---------------------------------------------------------------------------
//   
void CAknEdwinPhysicsHandler::InitPhysicsL()
    {
    TSize totalSize( iViewRect.Width(), iViewRect.Height() + KMaxWorldSize );
    TSize viewSize( iViewRect.Width(), iViewRect.Height() );

    iPhysics->InitPhysicsL( totalSize, viewSize, EFalse );
    }

// ---------------------------------------------------------------------------
// CAknEdwinPhysicsHandler::MoveScrollIndex
// ---------------------------------------------------------------------------
//     
void CAknEdwinPhysicsHandler::MoveScrollIndex( TInt aPixelsToMove )
    {
    // This is called when user moves content using scrollbar
    
    // Do nothing if handler itself is updating the view
    if ( iFlags.IsSet( EFlagUpdatingView ) )
        {
        return;
        }

    iWorldIndex += aPixelsToMove;
    ScrollView( EFalse );
    }

// ---------------------------------------------------------------------------
// CAknEdwinPhysicsHandler::EmulationOngoing
// ---------------------------------------------------------------------------
//     
TBool CAknEdwinPhysicsHandler::EmulationOngoing()
    {
    return IsFlicking() || IsBouncing();
    }

// ---------------------------------------------------------------------------
// CAknEdwinPhysicsHandler::DragThreshold
// ---------------------------------------------------------------------------
//     
TInt CAknEdwinPhysicsHandler::DragThreshold() const
    {
    return iPhysics->DragThreshold();
    }

// ---------------------------------------------------------------------------
// CAknEdwinPhysicsHandler::ViewPositionChanged
// ---------------------------------------------------------------------------
//
void CAknEdwinPhysicsHandler::ViewPositionChanged( const TPoint& aNewPosition,
        TBool /*aDrawNow*/, TUint /*aFlags*/)
    {        
    // Skip equal sequential values.
    if ( aNewPosition.iY == iPreviousYCoordinate )
        {
        return;
        }
    iPreviousYCoordinate = aNewPosition.iY;
    
    TInt y( 0 );
    if ( iFlags.IsSet( EFlagBouncingDown ) )
        {
        // We are at the beginning of world
        y = aNewPosition.iY + iBounceDownIndex;
        }
    else if ( iFlags.IsSet( EFlagBouncingUp ) )
        {
        // We are at the end of world
        y = aNewPosition.iY + iBounceUpIndex - KMaxWorldSize;
        }
    else
        {
        // We are at the middle of world
        y = aNewPosition.iY - KMaxWorldSize / 2;
        }

    iWorldIndex = y - iViewRect.Height() / 2;

    // If bounce is ongoing, block all pointer events.
    if ( IsBouncing() )
        {
        BlockEvents( ETrue );
        }
    // Scroll view based on values from aknphysics
    ScrollView( ETrue );
    }

// ---------------------------------------------------------------------------
// CAknEdwinPhysicsHandler::PhysicEmulationEnded
// ---------------------------------------------------------------------------
//    
void CAknEdwinPhysicsHandler::PhysicEmulationEnded()
    {
    TInt offset = iEdwin.PixelsOutOfBorder();
    if ( offset != 0 )
        {
        // If physics emulation ends and view position is not moved
        // back to original position (to position where bounce started)
        // we adjust it here. This is because aknphysics won't return
        // always to original position.
     
        TPoint newPosition( 0, iPreviousYCoordinate + offset );
        ViewPositionChanged( newPosition, ETrue, 0 );
        }
    
    // Enable pointer events when next pointer down received
    iEventUnblockingAllowed = ETrue;
    
    // Show cursor again if needed   
    iEdwin.RestoreCursorState();
    }

// ---------------------------------------------------------------------------
// CAknEdwinPhysicsHandler::ViewPosition
// ---------------------------------------------------------------------------
//    
TPoint CAknEdwinPhysicsHandler::ViewPosition() const
    {
    // Aknphysics calls this function to get current view position.
    // We adjust the position based on information if we
    // are are bouncing up or down (in other words we
    // have exceeded end- or beginning of real editor content).
    // In these situations we adjust returned value so that
    // from aknphysic's point of view we seem to be at the beginning
    // or end of almost infinite large world. If we have not exceeded
    // borders of editor content, we are at the middle of this world.
    // So, when we are at the middle of this almost infinite large world,
    // we can in practice add and remove content to editor
    // and we must not tell correct position to aknphysics (we also can't because
    // it seems to be impossible to calculate excatly correct position and size
    // of world if we haven't formatted yet the whole editor content).  

    TInt y( 0 );

    if ( iFlags.IsClear( EFlagBouncingDown )
            && iFlags.IsClear( EFlagBouncingUp ) )
        {
        // We are at the middle of world
        y = iWorldIndex + KMaxWorldSize / 2;
        }
    else if ( iFlags.IsSet( EFlagBouncingDown ) )
        {
        // We are at the beginning of world
        y = iWorldIndex - iBounceDownIndex;
        }
    else if ( iFlags.IsSet( EFlagBouncingUp ) )
        {
        // We are at the end of world
        y = iWorldIndex - iBounceUpIndex +  KMaxWorldSize;
        }

    return TPoint( iViewRect.Width() / 2, y + iViewRect.Height() / 2 );
    }

// ---------------------------------------------------------------------------
// CAknEdwinPhysicsHandler::CAknEdwinPhysicsHandler
// ---------------------------------------------------------------------------
//
CAknEdwinPhysicsHandler::CAknEdwinPhysicsHandler( CEikEdwin& aEdwin ) :
    iWorldIndex( 0 ),
    iPreviousWorldIndex( 0 ),
    iPhysics( NULL ),
    iEdwin( aEdwin )
    {
    }

// ---------------------------------------------------------------------------
// CAknEdwinPhysicsHandler::ConstructL
// ---------------------------------------------------------------------------
//
void CAknEdwinPhysicsHandler::ConstructL()
    {
    iPhysics = CAknPhysics::NewL( *this, &iEdwin );    
    }

// ---------------------------------------------------------------------------
// CAknEdwinPhysicsHandler::ScrollView
// ---------------------------------------------------------------------------
//     
void CAknEdwinPhysicsHandler::ScrollView( TBool aAllowBounce )
    {
    iFlags.Set( EFlagUpdatingView );
    if ( iPreviousWorldIndex != iWorldIndex )
        {
        // Calculate amount of pixels to scroll based on previous position
        TInt pixelsToScroll( iPreviousWorldIndex - iWorldIndex );
        if ( pixelsToScroll != 0 )
            {
            if ( iFlags.IsSet( EFlagBouncingDown ) ||
                    iFlags.IsSet( EFlagBouncingUp ) )
                {
                // Bounce ongoing, use function that supports scrolling
                // over the content borders (there can be empty space above or
                // below the editor content)
                TInt restOfPixels( 0 );
                ScrollStepWithBounce( pixelsToScroll, restOfPixels );
                
                // If restOfPixels is not zero, we were bouncing back
                // and exceeded the border again. In this situation
                // we must scroll rest of pixels using function
                // that stops if we again exceed the border. This is needed
                // because we need to know if we exceed the border again
                // (for example if length of content is short) to adjust
                // position on aknphysics world correctly.

                if ( restOfPixels != 0)
                    {
                    ScrollStep( pixelsToScroll, ETrue );
                    }
                }
            else
                {
                // Bounce not ongoing, use function that stops if we exceed the border
                ScrollStep( pixelsToScroll, aAllowBounce );
                }
            }
        }
    iFlags.Clear( EFlagUpdatingView );
    }

// ---------------------------------------------------------------------------
// CAknEdwinPhysicsHandler::ScrollStep
// ---------------------------------------------------------------------------
//   
void CAknEdwinPhysicsHandler::ScrollStep( TInt aPixelsToScroll,
    TBool aAllowBounce )
    {
    TInt restOfPixels( 0 );
    TBool borderExceeded( EFalse );

    TInt scrolledPixels = iEdwin.ScrollView( aPixelsToScroll, borderExceeded,
        restOfPixels );
           
    if ( borderExceeded && aAllowBounce )
        {
        if ( aPixelsToScroll != 0 )
            {
            MoveWorldIndex( scrolledPixels );
            
            if ( IsFlicking() )
                {
                // Flicking is ongoing and end of content is arrived.
                // In this situation we stop physics, adjust the view position in the
                // aknphysics (in function ViewPosition) and restart physics with
                // current force and velocity.
                
                iPhysics->SuspendPhysics();
                InitBounce( aPixelsToScroll > 0 );
                iPhysics->ResumePhysics();
                }
            else
                {
                InitBounce( aPixelsToScroll > 0 );
                ScrollRestOfPixels( restOfPixels );
                }
            }
        return;
        }

    MoveWorldIndex( scrolledPixels );
    }

// ---------------------------------------------------------------------------
// CAknEdwinPhysicsHandler::ScrollStepWithBounce
// ---------------------------------------------------------------------------
// 
void CAknEdwinPhysicsHandler::ScrollStepWithBounce( TInt aPixelsToScroll,
    TInt& aRestOfPixels )
    {
    TBool endOfBounce( EFalse );
    TInt scrolledPixels = iEdwin.ScrollViewWithBounce(
        aPixelsToScroll, endOfBounce, aRestOfPixels );

    MoveWorldIndex( scrolledPixels );

    if ( endOfBounce )
        {
        iFlags.Clear( EFlagBouncingDown );  
        iFlags.Clear( EFlagBouncingUp );
        }
    }

// ---------------------------------------------------------------------------
// CAknEdwinPhysicsHandler::MoveWorldIndex
// ---------------------------------------------------------------------------
//
void CAknEdwinPhysicsHandler::MoveWorldIndex( TInt aDelta )
    {
    iWorldIndex = iPreviousWorldIndex - aDelta;
    iPreviousWorldIndex = iWorldIndex;
    }

// ---------------------------------------------------------------------------
// CAknEdwinPhysicsHandler::ScrollRestOfPixels
// ---------------------------------------------------------------------------
//
void CAknEdwinPhysicsHandler::ScrollRestOfPixels( TInt aRestOfPixels )
    {
    // Scroll rest of pixels
    TBool endOfBounce;
    TInt restOfPixels( 0 );
    
    TInt scrolledPixels = iEdwin.ScrollViewWithBounce( aRestOfPixels,
            endOfBounce, restOfPixels );
    
    MoveWorldIndex( scrolledPixels );
    }

// ---------------------------------------------------------------------------
// CAknEdwinPhysicsHandler::StopPhysics
// ---------------------------------------------------------------------------
//
void CAknEdwinPhysicsHandler::StopPhysics()
    {
    iPhysics->StopPhysics();
    iPhysics->ResetFriction();
    }

// ---------------------------------------------------------------------------
// CAknEdwinPhysicsHandler::BlockEvents
// ---------------------------------------------------------------------------
//
void CAknEdwinPhysicsHandler::BlockEvents( TBool aBlocked )
    {
    iEventsBlocked = aBlocked;
    iEventUnblockingAllowed = EFalse;
    }

// ---------------------------------------------------------------------------
// CAknEdwinPhysicsHandler::IsFlicking
// ---------------------------------------------------------------------------
//
TBool CAknEdwinPhysicsHandler::IsFlicking() const
    {
    return iPhysics->OngoingPhysicsAction()
            == CAknPhysics::EAknPhysicsActionFlicking;
    }

// ---------------------------------------------------------------------------
// CAknEdwinPhysicsHandler::IsBouncing
// ---------------------------------------------------------------------------
//
TBool CAknEdwinPhysicsHandler::IsBouncing() const
    {
    return iPhysics->OngoingPhysicsAction()
            == CAknPhysics::EAknPhysicsActionBouncing;
    }

// ---------------------------------------------------------------------------
// CAknEdwinPhysicsHandler::InitBounce
// ---------------------------------------------------------------------------
//
void CAknEdwinPhysicsHandler::InitBounce( TBool aBouncingDown )
    {
    if ( aBouncingDown )
        {
        iFlags.Clear( EFlagBouncingUp );
        iFlags.Set( EFlagBouncingDown );
        iBounceDownIndex = iWorldIndex;
        }
    else
        {
        iFlags.Set( EFlagBouncingUp );
        iFlags.Clear( EFlagBouncingDown );
        iBounceUpIndex = iWorldIndex;
        }   
    }

// ---------------------------------------------------------------------------
// CAknEdwinPhysicsHandler::InitKineticScrolling
// ---------------------------------------------------------------------------
//
void CAknEdwinPhysicsHandler::InitKineticScrolling(
    const TPoint& aStartPosition )
    {
    iSelectionStarted = EFalse;
    iDraggingStarted = EFalse;
    iStartPosition = aStartPosition;
    }

// ---------------------------------------------------------------------------
// CAknEdwinPhysicsHandler::HandleKineticScrolling
// ---------------------------------------------------------------------------
//
void CAknEdwinPhysicsHandler::HandleKineticScrolling(
    const TPointerEvent& aPointerEvent, TBool& aShouldReturn )
    {
    aShouldReturn = EFalse;
    
    // If editor content is empty, it is not possible to drag,
    // flick or select text and we return here. Other events
    // are passed because they are handled later.
    if ( aPointerEvent.iType == TPointerEvent::EDrag
        && iEdwin.TextLength() == 0 )
        {
        aShouldReturn = ETrue;
        return;
        }
    
    // If dragging or selection not started,
    // check if it should be started
    if ( aPointerEvent.iType == TPointerEvent::EDrag && !iSelectionStarted
        && !iDraggingStarted )
        {
        // Get delta values for pointer movement
        TInt deltaX( aPointerEvent.iPosition.iX - iStartPosition.iX );
        TInt deltaY( aPointerEvent.iPosition.iY - iStartPosition.iY );
            
        // If drag threshold not exceeded, return.
        if ( Abs( deltaX ) < DragThreshold()
            && Abs( deltaY ) < DragThreshold() )
            {
            HandlePointerEvent( aPointerEvent );
            aShouldReturn = ETrue;
            return;
            }
                  
        // If dragged horizontally more than vertically,
        // text selection started. Otherwise dragging started.
        if ( Abs( deltaX ) > Abs( deltaY ) )
            {
            iSelectionStarted = ETrue;
            }
        else
            {
            iDraggingStarted = ETrue;
                
            // If cursor is visible, disable it and store
            // cursor visibility info when dragging starts.
            iEdwin.StoreCursorState();
            }
        }

    // Forward all events to physics handler, except:
    // If text selection started, don't forward drag and up events
    // because kinetic scrolling can't be used when selecting text.
    // However, fast scrolling can be used when we are selecting text.

    if ( !( iSelectionStarted &&
            ( aPointerEvent.iType == TPointerEvent::EDrag ||
                aPointerEvent.iType == TPointerEvent::EButton1Up ) ) )
        {
        HandlePointerEvent( aPointerEvent );
        }
    
    if ( aPointerEvent.iType == TPointerEvent::EButton1Up )
        {
        // If flick or bounce effect was started, check if there
        // is need to hide cursor.
        // If flick or bounce was not started, show cursor again if needed.
        if ( EmulationOngoing() )
            {
            iEdwin.StoreCursorState();
            }
        else
            {
            iEdwin.RestoreCursorState();
            }
        }

    // If selection not started, don't handle drag events but return
    // All other events must be handled anyway.
    if ( !iSelectionStarted && aPointerEvent.iType
            == TPointerEvent::EDrag )
        {
        aShouldReturn = ETrue;                     
        return;
        }
    }

// ---------------------------------------------------------------------------
// CAknEdwinPhysicsHandler::SelectionStarted
// ---------------------------------------------------------------------------
//
TBool CAknEdwinPhysicsHandler::SelectionStarted() const
    {
    return iSelectionStarted;
    }

// ---------------------------------------------------------------------------
// CAknEdwinPhysicsHandler::DraggingStarted
// ---------------------------------------------------------------------------
//
TBool CAknEdwinPhysicsHandler::DraggingStarted() const
    {
    return iDraggingStarted;
    }

// ---------------------------------------------------------------------------
// CAknEdwinPhysicsHandler::DragThresholdExceeded
// ---------------------------------------------------------------------------
//
TBool CAknEdwinPhysicsHandler::DragThresholdExceeded(
    const TPoint& aCurrentPosition ) const
    {
    // Get delta values for pointer movement
    TInt deltaX( aCurrentPosition.iX - iStartPosition.iX );
    TInt deltaY( aCurrentPosition.iY - iStartPosition.iY );

    if ( Abs( deltaX ) >= DragThreshold() || Abs( deltaY ) >= DragThreshold() )
        {
        return ETrue;
        }
    return EFalse;
    }
