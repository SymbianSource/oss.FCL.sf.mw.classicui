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
* Description: Class for tracing the direction in which pointer
*              is being dragged.
*
*/

#ifndef C_AKNTOUCHGESTUREFWDRAGTRACER_H
#define C_AKNTOUCHGESTUREFWDRAGTRACER_H

#include <e32base.h>

namespace AknTouchGestureFw
{

/**
 * Traces the direction in which pointer is being dragged.
 */
NONSHARABLE_CLASS( CAknTouchGestureFwDragTracer ) : public CBase
    {
public:

    /**
     * Values used to represent horizontal and vertical direction.
     */
    enum TDirection
        {
        EDirectionNone,     ///< No change in position.
        EDirectionForward,  ///< Movement towards right or down.
        EDirectionBackward  ///< Movement towards left or up.
        };

    /**
     * Two-phased constructor.
     */
    static CAknTouchGestureFwDragTracer* NewL();

    /**
     * Two-phased constructor.
     */
    static CAknTouchGestureFwDragTracer* NewLC();

    /**
     * Destructor.
     */
    virtual ~CAknTouchGestureFwDragTracer();

    /**
     * Initializes tracer.
     *
     * @param  aStartPosition  Start coordinate.
     */
    void Initialize( const TPoint& aStartPosition );

    /**
     * Checks if dragging direction has changed with new position.
     *
     * @param  aPosition     New position.
     * @param  aSensitivity  Tells how many points can be dragged to reversed
     *                       direction before direction is changed.
     *
     * @return @c ETrue if direction has changed
     */
    TBool IsDirectionChanged( const TPoint& aPosition, TInt aSensitivity );

private:

    /**
     * C++ constructor.
     */
    CAknTouchGestureFwDragTracer();

    /**
     * Checks if dragging direction has changed horizontally or vertically
     * with new position. Only horizontal or vertical direction can be checked
     * with single call.
     *
     * @param  aCurrentCoordinate  Current X- or Y-coordinate
     * @param  aPrevCoordinate     Previous X- or Y-coordinate
     * @param  aDirection          Current direction, will be updated within
     *                             this call.
     * @param  aCounter            Counter of coordinates that are dragged
     *                             to reversed direction, will be updated
     *                             within this call.
     * @param  aSensitivity        Tells how many points can be dragged to
     *                             reversed direction before direction is
     *                             changed.
     *
     * @return @c ETrue if direction has changed
     */
    TBool IsDirectionChanged( TInt aCurrentCoordinate,
                              TInt aPrevCoordinate,
                              TDirection& aDirection,
                              TInt& aCounter,
                              TInt aSensitivity );

private: // data

    /**
     * Current horizontal direction
     */
    TDirection iHorizDirection;

    /**
     * Current vertical direction
     */
    TDirection iVertDirection;

    /**
     * Counter for points which are to reversed horizontal direction
     * compared to current direction.
     */
    TInt iHorizCounter;

    /**
     * Counter for points which are to reversed vertical direction
     * compared to current direction.
     */
    TInt iVertCounter;

    /**
     * Current position.
     */
    TPoint iPosition;
    };

} // namespace AknTouchGestureFw

#endif // C_AKNTOUCHGESTUREFWDRAGTRACER_H
