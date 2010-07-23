/*
* Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:         test case
*
*/









#ifndef BCTEST_SETTINGITEMLIST_H
#define BCTEST_SETTINGITEMLIST_H

#include <aknsettingitemlist.h>

class CBCTestSettingPageCase;

class CBCTestSettingItem : public CAknSettingItem
    {

friend class CBCTestSettingPageCase;

public:
    /**
    * Constructor
    *
    * @param the unique identifier fo the setting item (not its number)
    */
    IMPORT_C CBCTestSettingItem( TInt identifier );

    /**
    * Destructor
    */
    IMPORT_C virtual ~CBCTestSettingItem();

    };

/**
* Support for abstact text setting type.  Corresponds to CAknTextSettingPage
*
*/
class CBCTestTextSettingItem : public CAknTextSettingItem
{

friend class CBCTestSettingPageCase;

public:
    /*
    * Constructor
    *
    * @param        resource identifier for this setting item
    * @param        Setting text
    *
    */
    IMPORT_C CBCTestTextSettingItem( TInt aIdentifier, TDes& aText );

    /**
    * Destructor
    */
    IMPORT_C virtual ~CBCTestTextSettingItem();
};


/**
*
* Abstract setting item for integer editing.
*
* This class is not disposed toward any particular type of setting page
*
*/
class CBCTestIntegerSettingItem : public CAknIntegerSettingItem
    {

    friend class CBCTestSettingPageCase;

    public:
    /*
    * Constructor
    *
    * @param        resource identifier for this setting item
    * @param        integer value to edit.
    *
    */
    IMPORT_C CBCTestIntegerSettingItem( TInt aIdentifier, TInt& aValue );
    IMPORT_C virtual ~CBCTestIntegerSettingItem();

    /**
    *
    * Pure virtual editItemL
    *
    * @param        aCalledFromMenu - ignored in this class
    *
    */
    void EditItemL( TBool aCalledFromMenu );

    };

/**
*
* Class for holding a password setting item
*
*/
class CBCTestPasswordSettingItem : public CAknPasswordSettingItem
{

friend class CBCTestSettingPageCase;

public:
    /*
    * Constructor
    *
    * @param        resource identifier for this setting item
    * @param        password mode; text or numeric
    * @param        password to change
    */
    IMPORT_C CBCTestPasswordSettingItem( TInt aIdentifier, enum TAknPasswordSettingItemMode aMode, TDes& aPassword );

};


/**
* An abstrct integer setting that uses the volume control as its editor
*
*/
class CBCTestVolumeSettingItem : public CAknVolumeSettingItem
    {

    friend class CBCTestSettingPageCase;
public:
    /*
    * Constructor
    *
    * @param        resource identifier for this setting item
    * @param        volume value. Must be in range 0 to 10, inclusive
    *
    */
    IMPORT_C CBCTestVolumeSettingItem( TInt aIdentifier, TInt& aExternalVolume );

    };

/**
* Slider control setting item
*
*
*/

class CBCTestSliderSettingItem : public CAknSliderSettingItem
    {

    friend class CBCTestSettingPageCase;
public:
    /*
    * Constructor
    *
    * @param        resource identifier for this setting item
    * @param        Slider value; must be within the minimum and maximum values in resource
    *
    */
    IMPORT_C CBCTestSliderSettingItem( TInt aIdentifier, TInt& aExternalSliderValue );

    };


/**
* CAknEnumeratedTextSettingItem
*
* Abstract Base class for deriving listbox setting page related setting items
*
* The class provides standard array support for these setting items and their
* listboxes.  Then approach is centred upon the CAknEnumeratedText type.
*
* The texts are exposed to the user, and appear in two versions, if desired - the text shown
* in the setting list when not being edited, and the "popped-up" version of the texts.
*
*/
class CBCTestEnumeratedTextSettingItem : public CAknEnumeratedTextSettingItem
    {

    friend class CBCTestSettingPageCase;
public:
    /**
    * Constructor.  Resource Id for the setting item
    *
    */
    IMPORT_C CBCTestEnumeratedTextSettingItem( TInt aResourceId );

    /**
    * Destructor
    */
    IMPORT_C virtual ~CBCTestEnumeratedTextSettingItem();

    };



/**
* Setting item type for CAknEnumeratedItems.
*
* The main use case for this is for list of texts that are being manipulated in the
* client source code as a set of enumerations, while the texts, read from resource,
* are not strongly exposed to the client.
*
* They are exposed to the user, and appear in two versions, if desired - the text shown
* in the setting list when not being edited, and the "popped-up" version of the texts.
*
*/
class CBCTestEnumeratedTextPopupSettingItem : public CAknEnumeratedTextPopupSettingItem
    {

    friend class CBCTestSettingPageCase;
public:
    /**
    * Construct a list, storing in it a resource (to be read at 2nd stage construction)
    * and a reference to na externally owned integer - the value to be manipulated
    *
    */
    IMPORT_C CBCTestEnumeratedTextPopupSettingItem( TInt aResourceId, TInt& aValue );

    /**
    * Destructor
    */
    IMPORT_C virtual ~CBCTestEnumeratedTextPopupSettingItem();

    };


class CBCTestBinaryPopupSettingItem : public CAknBinaryPopupSettingItem
    {

    friend class CBCTestSettingPageCase;

public:
    /**
    * Constructs a binary setting value, given a resource id and a reference to
    * an externally owned external boolen setting item.
    * Resource supplied is just as for CAknEnumeratedTextPopupSettingItem
    *
    * @param aIdentifier    Resource id for the associated values and texts;
    *
    */
    IMPORT_C CBCTestBinaryPopupSettingItem( TInt aIdentifier, TBool& aBinaryValue );

    };


/**
 * This class can be used as a base class for "Big Settings". The additional
 * functionality is small - merely to ensure that there is an empty string
 * in the list box text.
 *
 * To derive from this class, the client code is usually expected to add a new constructor,
 * re-implement StoreL, LoadL() and EditItemL().
 *
 */
class CBCTestBigSettingItemBase : public CAknBigSettingItemBase
    {

    friend class CBCTestSettingPageCase;
public:
    /**
    * Contruct the "Big" setting item. The passed resource identifier all that is needed
    * There is no external value to reference.
    */
    IMPORT_C CBCTestBigSettingItemBase( TInt aIdentifier );

    };


/**
 * This class holds the setting items themselves and also manages the bitmap array
 */
class CBCTestSettingItemArray : public CAknSettingItemArray
    {

    friend class CBCTestSettingPageCase;
public:
    /**
    * CAknSettingItemArray is constructed as a numbered or unnumbered array.
    * @param aGranularity   - number of items to extend when the aarray needs extention
    * @param aIsNumbered    - flags the array as numbered or not
    * @param aInitialOrdinal - value to start the numbering at
    */
    IMPORT_C CBCTestSettingItemArray( TInt aGranularity, TBool aIsNumbered, TInt aInitialOrdinal );
    /**
    * Destructor
    */
    IMPORT_C virtual ~CBCTestSettingItemArray();

    };


class CBCTestSettingItemList : public CAknSettingItemList
    {
    friend class CBCTestSettingPageCase;
public:
    /**
    * Constructs the setting item list
    */
    IMPORT_C CBCTestSettingItemList();
    /**
    * Destructor
    */
    IMPORT_C virtual ~CBCTestSettingItemList();

    };

#endif
