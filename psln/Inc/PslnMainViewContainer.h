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
* Description:  Main view container.
*
*/


#ifndef C_PSLNMAINVIEWCONTAINER_H
#define C_PSLNMAINVIEWCONTAINER_H

#include "PslnBaseContainer.h"

class CPslnFWPluginInterface;
class CPslnUi;
class CAknIconArray;
class TAknsItemID;

/**
*  Main view container.
*  Contains items to navigate to sub-views and application specfic theme views.
*
*  @since S60 3.1
*/
class CPslnMainViewContainer : public CPslnBaseContainer
    {
    public:

        /**
        * C++ constructor.
        * @param aPslnUi pointer to UI-class.
        */
        CPslnMainViewContainer( CPslnUi* aPslnUi );

        /**
        * By default Symbian 2nd phase constructor is private.
        * @param aRect client rect.
        */
        void ConstructL( const TRect& aRect );

        /**
        * Destructor.
        */
        virtual ~CPslnMainViewContainer();

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

        // Makes one specific folder name item.
        void MakeItemL( const TInt aIndex, const TInt aOffset = KErrNotFound );

        // Gets Help context.
        void GetHelpContext( TCoeHelpContext& aContext ) const;

        // Makes one plugin folder.
        TInt MakePluginItemL(
            CPslnFWPluginInterface& aPlugin,
            CAknIconArray& aIconList,
            TPtr& aBufPtr,
            TPtr& aItemPtr );

        // Adds icon to icon array.
        void AddIconL(
            CAknIconArray* aIcons,
            const TAknsItemID& aSkinId,
            const TDesC& aFileName,
            TInt aBitmapId,
            TInt aMaskId );

        // Parses icon file path to given parameter.
        void GetIconFilePath( TDes& aPath );

    private:    // Data

        // List of folder names.
        CDesCArrayFlat* iItems;

        // Array of loaded plugins.
        CArrayPtrFlat<CPslnFWPluginInterface>* iPluginArray;

        // Reference to Ui. Owned by Main view.
        CPslnUi* iPslnUi;
        
        // Has AS plugin been added.
        TBool iASAdded;

        // Has AI plugin been added.
        TBool iAIAdded;
    };

#endif      // C_PSLNMAINVIEWCONTAINER_H

// End of File
