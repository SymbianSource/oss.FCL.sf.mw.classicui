/*
* Copyright (c) 2002 - 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Test navigation_pane_api
*
*/


#ifndef C_TESTSDKNAVIPANENAVIEXT_H
#define C_TESTSDKNAVIPANENAVIEXT_H

// INCLUDES
#include <aknnavi.h>

// CLASS DECLARATION

/**
 * the class derived from the CAknNavigationControlContainer class
 */
class CAknNavigationControlContainerExt:
    public CAknNavigationControlContainer
    {
public: //ConstructL
    void ConstructL();

public:
    // from CCoeControl
    /**
     * From @c CCoeControl.
     *
     * Handles the size change events.
     */
    virtual void SizeChanged();

    /**
     * From @c CCoeControl.
     *
     * Handles a change to the control's resources of type @c aType
     * which are shared across the environment, e.g. color scheme change.
     *
     * @param aType Event type.
     */
    virtual void HandleResourceChange(TInt aType);

    /**
     * From @c CCoeControl.
     *
     * Returns number of controls inside the context pane control.
     *
     * @return Number of component controls.
     */
    virtual TInt CountComponentControls() const;

    /**
     * From @c CCoeControl.
     *
     * Returns a control determined by control id.
     *
     * @param aIndex Index of a control to be returned.
     * @return Pointer to control.
     */
    virtual CCoeControl* ComponentControl(TInt aIndex) const;

public: // from MCoeControlObserver

    /**
     * From @c  MCoeControlObserver.
     *
     * Handles Control event.
     *
     * @param aControl Control that caused the event.
     * @param aEventType Type of the event.
     */
    void HandleControlEventL(CCoeControl* aControl,
        TCoeEvent aEventType);

    /**
     * From @c CCoeControl.
     *
     * Retrieves an object of the same type as that encapsulated in aId.
     *
     * This function is used to allow controls to ask their owners for
     * access to other objects that they own.
     *
     * Other than in the case where NULL is returned, the object returned
     * must be of the same object type - that is, the @c ETypeId member of
     * the object pointed to by the pointer returned by this function must
     * be equal to the @c iUid member of @c aId.
     *
     * @param aId An encapsulated object type ID.
     * @return Encapsulated pointer to the provided object.
     *         Note that the encapsulated pointer may be NULL.
     */
    TTypeUid::Ptr MopSupplyObject( TTypeUid aId );
    };

#endif // C_TESTSDKNAVIPANENAVIEXT_H
