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
* Description:  AknPhysics observer interface
*
*/

#ifndef M_AKNPHYSICSOBSERVER_H
#define M_AKNPHYSICSOBSERVER_H

#include <e32base.h>

/**
 *  AknPhysics observer.
 *
 *  @lib aknphysics
 *  @since S60 v5.0
 */
class MAknPhysicsObserver
    {

public:

    /**
     * Physics emulation has moved the view.
     * 
     * When this method is called client should update its visual and logical
     * states to reflect the changes caused by view move. Note that if the
     * parameter @c aDrawNow is @c EFalse client is not allowed to redraw the
     * display but should only update its logical state.
     * Physics engine will ensure that the last frame is always drawn.
     *
     * @since S60 v5.0
     *
     * @param  aNewPosition  The new position of the view.
     * @param  aDrawNow      @c ETrue if client should redraw the screen,
     *                       otherwise @c EFalse.
     * @param  aFlags        Additional flags, not used currently.
     */
    virtual void ViewPositionChanged( const TPoint& aNewPosition,
                                      TBool aDrawNow,
                                      TUint aFlags ) = 0;
    
    /**
     * Physics emulation has stopped moving the view
     *
     * @since S60 v5.0
     */
    virtual void PhysicEmulationEnded() = 0;

    /**
     * Returns the observer's view position.
     *
     * @since S60 v5.0
     *
     * @return Physics observer's view position.
     */
    virtual TPoint ViewPosition() const = 0;
    };

#endif // M_AKNPHYSICSOBSERVER_H
