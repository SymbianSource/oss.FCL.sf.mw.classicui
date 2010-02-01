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
* Description:  AknPhysics drag event observer
*
*/


#ifndef C_AKNPHYSICSDRAGOBSERVER_H
#define C_AKNPHYSICSDRAGOBSERVER_H


#include <e32base.h>

class TPointerEvent;
class CAknPhysicsParameterProvider;
class CAknPhysicsFlickTracker;

/**
 *  AknPhysics drag event observer
 *
 */
NONSHARABLE_CLASS( CAknPhysicsDragObserver ) : public CBase
    {

public:

    /**
     * Two-phased constructor.
     */
    static CAknPhysicsDragObserver* NewL( 
        CAknPhysicsParameterProvider* aProvider );

    /**
     * Two-phased constructor.
     */
    static CAknPhysicsDragObserver* NewLC(
        CAknPhysicsParameterProvider* aProvider );

    /**
     * Destructor.
     */
    virtual ~CAknPhysicsDragObserver();

    /**
     * Registers pointer event position.
     *
     * @param aEvent pointer event
     */
    void RegisterEventPosition( const TPointerEvent* aEvent );

    /**
     * Returns changed drag distance point.
     *
     * @return Changed drag distance.
     */
    TPoint ChangedDragDistance() const;

    /**
     * Returns changed vertical drag move time.
     *
     * @return Changed drag move time.
     */
    TInt ChangedVerticalDragMoveTime() const;

    /**
     * Returns changed horizontal drag move time.
     *
     * @return Changed drag move time.
     */
    TInt ChangedHorizontalDragMoveTime() const;

    /**
     * Returns ETrue if drag parameters has been changed during drag event.
     *
     * @return ETrue if drag parameters has been changed.
     */
    TBool DragChanged() const;

private:

    /**
     * C++ constructor.
     */
    CAknPhysicsDragObserver();

    /**
     * Symbian second-phase constructor.
     */
    void ConstructL( CAknPhysicsParameterProvider* aProvider );

    /**
     * Handles pointer down event.
     *
     * @param aPosition Down event position.
     */
    void HandlePointerDownEvent( const TPoint& aPosition );

    /**
     * Handles pointer drag event.
     *
     * @param aPosition Drag event position.
     */
    void HandlePointerDragEvent( const TPoint& aPosition );

    /**
     * Handles pointer up event.
     *
     * @param aPosition Up event position.
     */
    void HandlePointerUpEvent( const TPoint& aPosition );

    /**
     * Resets state.
     */
    void Reset();

private: // data
 
    /**
     * Dragging event down position.
     */
    TPoint iDownPosition;

    /**
     * Dragging event up position.
     */
    TPoint iUpPosition;

    /**
     * Vertical flick tracker.
     * Own.
     */
    CAknPhysicsFlickTracker* iVerticalTracker;

    /**
     * Horizontal flick tracker.
     * Own.
     */
    CAknPhysicsFlickTracker* iHorizontalTracker;

    /**
     * Boolean flag to indicate whether pointer is considered to be down.
     */
    TBool iPointerDown;
    };


#endif // C_AKNPHYSICSDRAGOBSERVER_H

