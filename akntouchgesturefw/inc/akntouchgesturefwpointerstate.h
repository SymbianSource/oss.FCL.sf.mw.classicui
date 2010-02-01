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
* Description:  Touch gesture framework pointer state.
*
*/

#ifndef C_AKNTOUCHGESTUREFWPOINTERSTATE_H
#define C_AKNTOUCHGESTUREFWPOINTERSTATE_H

#include "akntouchgesturefwutils.h"

namespace AknTouchGestureFw {

/**
 * Maximum amount of simultaneous pointers supported by the
 * touch gesture framework.
 */
const TInt KMaxPointerCount( 2 );

/**
 * Represents a single pointer data
 */
struct TPointerData
    {
    TPoint iPosition;
    TPoint iStartPosition;
    TBool iIsPressedDown;
    TBool iTargetedToControl;
    };

/**
 * Touch gesture framework pointer state.
 *
 * @lib akntouchgesturefw
 * @since S60 v5.2
 */
NONSHARABLE_CLASS( CAknTouchGestureFwPointerState ) : public CBase
    {

public:

    /**
     * Two-phased constructor.
     */
    static CAknTouchGestureFwPointerState* NewL();

    /**
     * Two-phased constructor.
     */
    static CAknTouchGestureFwPointerState* NewLC();

    /**
     * Destructor.
     */
    virtual ~CAknTouchGestureFwPointerState();

    /**
     * Resets pointer state.
     */
    void Reset();

    /**
     * Updates pointer-related data.
     *
     * @param  aPointerData  Pointer event related data.
     */
    TBool Update( const TPointerEventData& aPointerData );

    /**
     * Provides the position of first pointer.
     *
     * @return First pointer position.
     */
    TPoint* FirstPointerPosition();

    /**
     * Provides the position of second pointer.
     *
     * @return Second pointer position.
     */
    TPoint* SecondPointerPosition();

    /**
     * Returns @c ETrue if two pointers are down.
     *
     * @return @c ETrue if two pointer are down.
     */
    TBool IsDoubleTouch() const;

    /**
     * Returns @c ETrue if single pointer is down.
     *
     * @return @c ETrue if single pointer is down.
     */
    TBool IsSingleTouch() const;

    /**
     * Returns @c ETrue if no pointers are down.
     *
     * @return @c ETrue if no pointers are down.
     */
    TBool IsNoTouch() const;

    /**
     * Returns @c ETrue if event was invalid because of two successive
     * down events.
     *
     * @return @c ETrue if two successive down events were received.
     */
    TBool SuccessiveDownEventsReceived();

private:

    /**
     * C++ constructor.
     */
    CAknTouchGestureFwPointerState();

    /**
     * Updates order of pointers. In practice updates variables
     * @c iFirstPointerNumber an @c iSecondPointerNumber.
     *
     * @c iFirstPointerNumber contains always the number (=id) of pointer
     * that was pressed down first and/or released last.
     *
     * @c iSecondPointerNumber contains always the number (=id) of pointer
     * that was pressed down when first pointer was already down and/or
     * released first when another pointer was still down.
     *
     * @param  aPointerType    Pointer state
     * @param  aPointerNumber  Number (=id) of the pointer
     */
    void UpdatePointerOrder( TPointerEvent::TType aPointerType,
                             TInt aPointerNumber );

    /**
     * Returns @c ETrue if pointer event is valid (for example up received
     * after down).
     *
     * @param  aPointerType    New pointer state.
     * @param  aPointerNumber  Pointer number.
     *
     * @return @c ETrue if valid & can be accepted, @c EFalse otherwise.
     */
    TBool IsValidEvent( TPointerEvent::TType aPointerType,
                        TInt aPointerNumber );

    /**
     * Returns @c ETrue if pointers are down outside control area.
     * 
     * @return @c ETrue if pointers are down outside control area.
     */
    TBool PointersDownOutsideControlArea() const;

private: // data

    /**
     * Pointer number (=id) of pointer that was pressed down first.
     */
    TInt iFirstPointerNumber;

    /**
     * Pointer number (=id) of pointer that was pressed down next.
     */
    TInt iSecondPointerNumber;

    /**
     * Data for each pointer.
     */
    TPointerData iPointerData[ KMaxPointerCount ];

    /**
     * Tells number of pointers pressed down.
     */
    TInt iPointerCount;

    /**
     * @c ETrue if event was invalid because of two successive down events.
     * Used only for testing.
     */
    TBool iSuccessiveDownEvents;
    };

} // namespace AknTouchGestureFw

#endif // C_AKNTOUCHGESTUREFWPOINTERSTATE_H
