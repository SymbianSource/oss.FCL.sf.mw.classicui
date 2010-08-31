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

#endif // M_AKNCOLLECTION_H
