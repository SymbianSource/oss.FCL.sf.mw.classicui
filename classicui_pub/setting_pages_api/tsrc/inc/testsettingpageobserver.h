/*
* Copyright (c) 2002 - 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Test setting_pages_api
*
*/

#ifndef C_TESTSETTINGPAGEOBSERVER_H
#define C_TESTSETTINGPAGEOBSERVER_H

//Include files
#include <aknsettingitemlist.h>
#include <akncheckboxsettingpage.h> 
/*
 * This class inherit from the CAknSettingItem class for 
 * providing parmer for special function which wold be tested
 */ 
class CSettingItemObserver : public CAknSettingItem
    {
public:
    /*
     * Constructor
     */
    CSettingItemObserver( TInt aIdentifier );
    /*
     * Destructor
     */
    ~CSettingItemObserver();
protected:
    /*
     * This function is a implement of the parent class
     */
    void EditItemL( TBool aCalledFromMenu );
private:
    //data
    CSelectionItemList* iSelectionList;
    };

#endif/*C_TESTSETTINGPAGEOBSERVER_H*/

//End file


