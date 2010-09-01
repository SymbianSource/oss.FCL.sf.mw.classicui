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
* Description:  test AknPopupSettingPage.h
*
*/


#ifndef C_TESTSDKPOPUPSEX_H
#define C_TESTSDKPOPUPSEX_H

#include <aknpopup.h>
#include <aknpopuplayout.h>
#include <coecobs.h>
#include <aknpopupfader.h>
#include <aknpopupfield.h>
#include <aknpopupsettingpage.h> 

class CTestSDKPopupSPSL : public CAknPopupSettingList
    {
public:// Constructors and destructor
    /**
    * C++ default constructor.
    */
    CTestSDKPopupSPSL();
    
    /**
    * Destructor.
    */
    ~CTestSDKPopupSPSL();
    
    /**
    *  CreateMenuListL test function for testing the 
    * Test CreateMenuListL function
    */
    void CreateMenuListL();
    
    /**
    *  ActivateMenuListL test function for testing the 
    * Test ActivateMenuListL function
    */
    void ActivateMenuListL();
    
    /**
    *  ConfigureMenuListL test function for testing the 
    * Test ConfigureMenuListL function
    */
    void ConfigureMenuListL();
    
    /**
    *  DestroyMenuList test function for testing the 
    * Test DestroyMenuList function
    */
    void DestroyMenuList();
    
    /**
    *  HandleListBoxEventL test function for testing the 
    * Test HandleListBoxEventL function
    */
    void HandleListBoxEventL( CEikListBox* aListBox, TListBoxEvent aEventType );
    };

#endif /*C_TESTSDKPOPUPSEX_H*/
