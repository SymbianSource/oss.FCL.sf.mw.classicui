/*
* Copyright (c) 2005-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Container for screen saver view.
*
*/



#ifndef C_PSLNSCREENSAVERCONTAINER_H
#define C_PSLNSCREENSAVERCONTAINER_H

#include "PslnBaseContainer.h"

/**
*  Container for screen saver view.
*  Creates setting items for different types of screen savers.
*
*  @since S60 v3.1
*/
class CPslnScreenSaverContainer : public CPslnBaseContainer
    {
    public:

        /**
        * C++ default constructor.
        */
        CPslnScreenSaverContainer();

        /**
        * By default Symbian 2nd phase constructor is private.
        * @param aRect Client rect.
        */
        void ConstructL( const TRect& aRect );

        /**
        * Destructor.
        */
        virtual ~CPslnScreenSaverContainer();

        /**
        * Updates the whole container.
        */
        void UpdateListBoxL();

    private:

        /**
        * From CPslnBaseContainer.
        * Creates listbox.
        */
        void ConstructListBoxL( TInt aResLbxId );

        /**
        * From CPslnBaseContainer.
        * Creates listbox items.
        */
        void CreateListBoxItemsL();

        /* Gets Help context. */
        void GetHelpContext( TCoeHelpContext& aContext ) const;

    };

#endif      // C_PSLNSCREENSAVERCONTAINER_H

// End of File
