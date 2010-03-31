/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Utility used for activation events
*
*
*/



#ifndef M_ITEMFINDEROBSERVER_H
#define M_ITEMFINDEROBSERVER_H

// INCLUDES
#include <ItemFinder.h> // for CItemFinder::CFindItemExt

/**
 * Item activation observer.
 *
 * Notifies observer when user activates highlightable items in 
 * CEikRichTextEditor. Observer class should implement this interface and
 * register itself to @c CItemFinder to receive item activation events.
 * 
 * The sent event includes information about the activated item,
 * method of activation and additional information about the activation.
 * 
 * Code example of listening to activation events:
 * @code
 * void CItemFinderObserver::HandleFindItemEventL( 
 *        CItemFinder::CFindItemExt& aItem,
 *        MAknItemFinderObserver::TEventFlag aEvent,
 *        TUint aFlags )
 *    {
 *    if ( aEvent == MAknItemFinderObserver::EPointerEvent 
 *            && aItem.iItemType == CItemFinder::EPhoneNumber )
 *        {
 *        HandleCallL( aItem.iItemDescriptor->Des() );
 *        }
 *    }
 * @endcode
 *
 * @lib commonui.lib
 * @since S60 v5.2
 */
class MAknItemFinderObserver
    {
    public:
        /**
         * Enum for activation event flags.
         */
        enum TEventFlag
            {
            /**
             * Item was activated by a pointer event.
             */
            EPointerEvent       = 0x00000001,
            /**
             * Item was activated by a key event.
             */
            EKeyEvent           = 0x00000002
            };
        /**
         * Handles the activation event.
         *
         * @param  aItem        Activated item.
         * @param  aEvent       Activation method.
         * @param  aFlags       Additional information about the event.
         */
        virtual void HandleFindItemEventL(
                const CItemFinder::CFindItemExt& aItem,
                MAknItemFinderObserver::TEventFlag aEvent,
                TUint aFlags = 0 ) = 0;
    };

#endif // M_ITEMFINDEROBSERVER_H
