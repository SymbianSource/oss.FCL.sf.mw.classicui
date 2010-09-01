/*
* Copyright (c) 2005-2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Wallpaper view's container.
*
*/



#ifndef PSLNWALLPAPERCONTAINER_H
#define PSLNWALLPAPERCONTAINER_H

//  INCLUDES
#include "PslnBaseContainer.h"

// CLASS DECLARATION

/**
*  Wallpaper container.
*  Contains wallpaper setting items.
*
*  @since S60 v3.1
*/
class CPslnWallpaperContainer : public CPslnBaseContainer
    {
    public:

        /**
        * C++ default constructor.
        */
        CPslnWallpaperContainer();

        /**
        * By default Symbian 2nd phase constructor is private.
        * @param aRect client rect.
        */
        void ConstructL( const TRect& aRect );

        /**
        * Destructor.
        */
        virtual ~CPslnWallpaperContainer();

        /**
        * From CPslnBaseContainer.
        * Updates the whole container.
        */
        void UpdateListBoxL();

    private:

        /**
        * From CPslnBaseContainer.
        * Constructs list box and items.
        * @param aResLbxId used resource ID.
        */
        void ConstructListBoxL( TInt aResLbxId );

        /**
        * From CPslnBaseContainer.
        * Creates listbox items.
        */
        void CreateListBoxItemsL();

        /**
        * From CCoeControl. Gets help context.
        */
        void GetHelpContext( TCoeHelpContext& aContext ) const;

    private:    // Data

        /**
        * List of setting items. 
        * Own.
        */
        CDesCArrayFlat* iItems;
    };

#endif      // PSLNWALLPAPERCONTAINER_H  
            
// End of File
