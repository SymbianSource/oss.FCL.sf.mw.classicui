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
* Description:  General theme container.
*
*/



#ifndef PSLNGENERALTHEMECONTAINER_H
#define PSLNGENERALTHEMECONTAINER_H

#include "PslnBaseContainer.h"

/**
*  General theme container.
*  Contains available skins.
*
*  @since S60 v3.1
*/
class CPslnGeneralThemeContainer : public CPslnBaseContainer
    {
    public:  // Constructors and destructor   
    
        /**
        * C++ default constructor.
        */
        CPslnGeneralThemeContainer();

        /**
        * By default Symbian 2nd phase constructor is private.
        * @param aRect client rect.
        */
        void ConstructL( const TRect& aRect );        
        
        /**
        * Destructor.
        */
        virtual ~CPslnGeneralThemeContainer();
        
    public: // New methods
    
        /**
        * Is embedded link visible. 
        * @return ETrue if link should be shown.
        */
        TBool IsEmbeddedLinkVisible() const;
        
        /**
        * Updates skin list.
        */
        void UpdateSkinListItemsL( const TInt& aNewIndex );

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
        * Updates D column icons when skin preview activates.
        *
        * @since 5.0
        */
        void UpdateSkinListItemsDColumnOnlyL();
        

    private:            
        
        // Gets Help context.        
        void GetHelpContext( TCoeHelpContext& aContext ) const;

    private: // data

        /*
        * To be used index in highlight when container is updated.
        * This is used when skin is activated and user has already
        * highlighted some other theme.
        */
        TInt iToBeUsedIndex;

        /*
        * Current preview theme index in listbox.
        */
        TInt iActiveSkinItemIndex;

        /*
        * Old Skin Num.
        */
        TInt iOldSkinNum;
    };

#endif      // PSLNGENERALTHEMECONTAINER_H  
            
// End of File
