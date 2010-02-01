/*
* Copyright (c) 1997-1999 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:
*
*/



#if !defined(__EIKTXLBM_H__)
#define __EIKTXLBM_H__  

#if !defined(__EIKLBM_H__)
#include <eiklbm.h>
#endif

/**
* Text list box model.
*/
class CTextListBoxModel : public CBase, public MTextListBoxModel
    {
    public:
        /**
        * Default constructor.
        */
        IMPORT_C CTextListBoxModel();

        /**
        * destructor
        */
        IMPORT_C virtual ~CTextListBoxModel();

        /**
        * Gets the number of text items in this list box model.
        * @return The number of text items.
        */
        IMPORT_C virtual TInt NumberOfItems() const;

        /**
        * Gets an array of strings for incremental matching of
        * typed characters. For the text list box model, these
        * strings are those that are displayed (see ItemText()).
        *
        * @return A text array for matching.
        */
        IMPORT_C virtual const MDesCArray* MatchableTextArray() const;

        /**
        * Gets the text to be displayed in the list box control
        * for the specified item.
        *
        * @param aItemIndex Index of an item. 
        * @return Text string to be displayed. 
        */
        IMPORT_C virtual TPtrC ItemText( TInt aItemIndex ) const;

        /**
        * Second-phase constructor.
        *
        * This function completes construction of a
        * default-constructed CTextListBoxModel, initialising any
        * members which are stored on the heap. Whether ownership of
        * the array is taken depends on the value of the
        * TListBoxModelItemArrayOwnership enum.
        *
        * @param aItemTextArray The item array. 
        * @param aOwnershipType Whether or not to take ownership of the array. 
        */
        IMPORT_C virtual void ConstructL( MDesCArray* aItemTextArray = NULL,
                                          TListBoxModelItemArrayOwnership aOwnershipType = ELbmOwnsItemArray );

        /**
        * Sets a new text item array. Panics if aItemTextArray is NULL.
        *
        * @param aItemTextArray New item text array. 
        */
        IMPORT_C void SetItemTextArray( MDesCArray* aItemTextArray );

        /**
        * Sets the item array ownership type.
        *
        * @param aOwnershipType Item array ownership. 
        */
        IMPORT_C void SetOwnershipType( TListBoxModelItemArrayOwnership aOwnershipType );

        /**
        * The array of text items modelled by this text list box model.
        *
        * @return A pointer to the array.
        */
        IMPORT_C MDesCArray* ItemTextArray() const;

    protected:
        /**
        * Gets the item array ownership type.
        *
        * @return Item array ownership. 
        */
        IMPORT_C TListBoxModelItemArrayOwnership ItemArrayOwnershipType() const;
        
    private: // from MListBoxModel
        IMPORT_C virtual TAny* MListBoxModel_Reserved();
        
    protected:
        /**
        * The array of text items modelled by this text list box model.
        */
        MDesCArray* iItemTextArray;
        
    private:
        TListBoxModelItemArrayOwnership iItemArrayOwnershipType;
    }; 


#endif
