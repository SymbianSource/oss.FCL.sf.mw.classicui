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
* Description:  Collection interface.
*
*/

#ifndef M_AKNCOLLECTION_H
#define M_AKNCOLLECTION_H

#include <e32std.h>
#include <coemop.h>

/**
 * Collection state provider.
 *
 * This interface is intended for those collections (e.g. lists)
 * that need to share information of its state and receive
 * collection notifications.
 *
 * @lib eikcoctl
 * @since S60 v5.2
 */
class MAknCollection
    {
public:

    DECLARE_TYPE_ID( 0x2002C343 )

    /**
     * Enum for collection state flags.
     */
    enum TStateFlag
        {
        /**
         * Collection is currently visible.
         */
        EStateCollectionVisible       = 0x00000001,
        /**
         * Collection has currently a visible highlight.
         */
        EStateHighlightVisible        = 0x00000002,
        /**
         * Collection can have multiple items selected.
         */
        EStateMultipleSelection       = 0x00000004,
        /**
         * Collection is view-only (no highlight ever).
         */
        EStateViewOnly                = 0x00000008
        };

    /**
     * Enum for collection extension types.
     */
    enum TExtensionType
        {
        /**
         * Collection supports multiple marking mode
         */
        EAknMarkingCollection = 1
        };

    /**
     * Returns the collection state. The state is combination of
     * flags defined in @c TStateFlag. 
     *
     * @return  Collection state.
     */
    virtual TUint CollectionState() const = 0;

    /**
     * Notifies that item action menu (@c CAknItemActionMenu)
     * was closed. 
     */
    virtual void ItemActionMenuClosed() = 0;

    /** 
     * Extension function.
     *
     * @param  aExtensionId  Extension id. 
     * @param  a0            First extension method parameter.
     * @param  a1            Second extension method parameter.
     */    
    virtual TInt CollectionExtension(
            TUint aExtensionId, TAny*& a0, TAny* a1 ) = 0;
    };


/**
 * Collection marking mode handler.
 *
 * This interface is intended for those collections that implement
 * multiple marking mode and wish to use mode directly from options menu.
 *
 * @lib eikcoctl
 * @since S60 v5.2
 */
class MAknMarkingCollection
    {
public:

    /**
     * Extension type.
     */
    enum { TYPE = MAknCollection::EAknMarkingCollection };

    /**
     * Enum for collection state flags.
     */
    enum TStateFlag
        {
        /**
         * Collection is in multiple marking mode.
         */
        EStateMarkingMode     = 0x00000001,
        /**
         * Collection has marked items.
         */
        EStateMarkedItems             = 0x00000002,
        /**
         * Collection is empty
         */
        EStateCollectionEmpty         = 0x00000004
        };

    /**
     * Sets multiple marking state.
     *
     * @param aActive ETrue if multiple marking should be active.
     */
    virtual void SetMultipleMarkingState( TBool aActive ) = 0;

    /**
     * Request to end marking mode
     * 
     * @return ETrue if marking mode can be ended 
     */
    virtual TBool ExitMarkingMode() = 0;
    
    /**
     * Returns the collection marking state. The state is combination of
     * flags defined in @c TStateFlag. 
     *
     * @return  Marking state.
     */
    virtual TUint MarkingState() const = 0;
    
    /**
     * Marks the currently selected item.
     */
    virtual void MarkCurrentItemL() = 0;
     
    /**
     * Marks all items in the collection.
     */
    virtual void MarkAllL() = 0; 

    /**
     * Unmarks all items in the collection.
     */
    virtual void UnmarkAll() = 0; 
    
    /*
     * Can current item be marked
     * 
     * @return ETrue if item is markable
     */
    virtual TBool CurrentItemMarkable() = 0;
    
    };

#endif // M_AKNCOLLECTION_H

