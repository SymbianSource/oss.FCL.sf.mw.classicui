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



#if !defined(__EIKLBM_H__)
#define __EIKLBM_H__  


#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

#if !defined(__BAMDESCA_H__)
#include <bamdesca.h>
#endif


// for some reason, doxygen seems to refuse documenting this...

/** @enum TListBoxModelItemArrayOwnership
* List box item array ownership flags. These values are used to
* describe whether or not a list box model owns an item array.
*/
enum TListBoxModelItemArrayOwnership
    {
    /** The list box model owns the item array, and will delete it in
    * its destructor.*/
    ELbmOwnsItemArray,
    /** The model does not own the item array. You must maintain a
    * pointer to it and free it explicitly before your program exits. */
    ELbmDoesNotOwnItemArray
    };

/**
* Description
* List box data model interface.
* 
* This mixin protocol is implemented by all list box models. List box
* models provide information needed to display the required data in a
* list box.
*
* Writing derived classes:
* 
* This class should be implemented by anything providing data for
* display in a CEikListBox-derived class. The very basic interface
* offered by MListBoxModel is usually expanded upon to provide more
* information for the specialised subclasses of CEikListBox. It is
* usual when deriving specialised list boxes to subclass the list box
* class, its view classes and its model together. See also:
*
*/
class MListBoxModel 
    {
    public:
        /**
        * Destructor.
        */
        IMPORT_C virtual ~MListBoxModel();

        /**
        * Gets the number of items in the list box
        * @return Number of items.
        */
        virtual TInt NumberOfItems() const = 0;

        /**
        * Gets an array of strings used by the list box for matching
        * user keypresses incrementally.
        *
        * @return A pointer to the array.
        */
        virtual const MDesCArray* MatchableTextArray() const = 0;

    private:
        IMPORT_C virtual TAny* MListBoxModel_Reserved();
    };

/**
* Text list box model interface.
*
* Text list box models provide the text of the items which are drawn
* by an associated CTextListItemDrawer. This interface is implemented
* by CTextListBoxModel.
*/

class MTextListBoxModel : public MListBoxModel
    {
    public:
        /**
        * Destructor
        */
        IMPORT_C ~MTextListBoxModel();

        /**
        * Gets the item text for an item by its index. This text,
        * rather than the matcher string, is drawn by
        * CTextListItemDrawers.
        * 
        * @param aItemIndex Index specifying an item.
        * @return The text for that item.
        */
        virtual TPtrC ItemText(TInt aItemIndex) const = 0;

    private: // from MListBoxModel
        IMPORT_C virtual TAny* MListBoxModel_Reserved();
    };

#endif
