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
* Description:  AknConf setting item component
 *
*/


#ifndef C_AKNCONFSETTINGITEM_H
#define C_AKNCONFSETTINGITEM_H
#include <aknsettingitemlist.h>

class CAknConfSettingList;

/**
 *  AknConf integer setting item component
 */
class CAknConfSettingItem : public CAknIntegerEdwinSettingItem
    {

public:

    /**
     * Constructor.
     */
    CAknConfSettingItem( CAknConfSettingList* aList,
                         TInt& aValue,
                         const TInt& aId,
                         const TInt& aCenRepKey);

    
    /**
     * Destructor.
     */
    ~CAknConfSettingItem();
    
// from base class CAknIntegerEdwinSettingItem

    /**
     * Handles an event of type aEventType reported by the 
     * Setting Page to this observer.
     *
     * @param aSettingPage Setting page
     * @param aEventType Event type
     */
    void HandleSettingPageEventL( CAknSettingPage *aSettingPage, 
                                  TAknSettingPageEvent aEventType );
private:

    /**
     * Parent list.
     * Not own.
     */
    CAknConfSettingList* iList;
    
    /**
     * Pointer to this setting value.
     */
    TInt* iValue;

    /**
     * Setting cenrep key.
     */
    TInt iCenRepKey;
    
    };


/**
 *  AknConf binary setting item component
 */
class CAknConfBinarySettingItem : public CAknBinaryPopupSettingItem
    {

public:

    /**
     * Constructor.
     */
    CAknConfBinarySettingItem( CAknConfSettingList* aList,
                               TBool& aValue,
                               const TInt& aId,
                               const TInt& aCenRepKey);

    
    /**
     * Destructor.
     */
    ~CAknConfBinarySettingItem();
    
// from base class CAknBinaryPopupSettingItem

    /**
     * This launches the setting page (or just toggles) the binary setting.
     *
     * @param aCalledFromMenu This flag determines if the setting page actually
     * launches or not. It does not if this flag is EFalse 
     * - the value is just toggled.
     */
    void EditItemL( TBool aCalledFromMenu );

    /**
     * Handles an event of type aEventType reported by the 
     * Setting Page to this observer.
     *
     * @param aSettingPage Setting page
     * @param aEventType Event type
     */
    void HandleSettingPageEventL( CAknSettingPage *aSettingPage, 
                                  TAknSettingPageEvent aEventType );
private:

    /**
     * Parent list.
     * Not own.
     */
    CAknConfSettingList* iList;
    
    /**
     * Pointer to this setting value.
     */
    TBool* iValue;

    /**
     * Setting cenrep key.
     */
    TInt iCenRepKey;
    
    };

/**
 *  AknConf slider setting item component
 */
class CAknConfSliderSettingItem : public CAknSliderSettingItem
    {

public:

    /**
     * Constructor.
     */
    CAknConfSliderSettingItem( CAknConfSettingList* aList,
                               TInt& aValue,
                               const TInt& aId,
                               const TInt& aCenRepKey);

    
    /**
     * Destructor.
     */
    ~CAknConfSliderSettingItem();
    
// from base class CAknSliderSettingItem

    /**
     * Handles an event of type aEventType reported by the 
     * Setting Page to this observer.
     *
     * @param aSettingPage Setting page
     * @param aEventType Event type
     */
    void HandleSettingPageEventL( CAknSettingPage *aSettingPage, 
                                  TAknSettingPageEvent aEventType );
private:

    /**
     * Parent list.
     * Not own.
     */
    CAknConfSettingList* iList;
    
    /**
     * Pointer to this setting value.
     */
    TInt* iValue;

    /**
     * Setting cenrep key.
     */
    TInt iCenRepKey;
    
    };

#endif // C_AKNCONFSETTINGITEM_H

