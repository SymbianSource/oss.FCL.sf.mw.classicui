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
* Description:  test aknpopupfader.h aknpopupfield.h aknpopupsettingpage.h
*
*/


#ifndef C_TESTSDKPOPUPSPF_H
#define C_TESTSDKPOPUPSPF_H

#include <coecobs.h>
#include <aknpopupfader.h>
#include <aknpopupfield.h>
#include <aknpopupsettingpage.h> 


class CTestSDKPopupsPF : public CBase,
                         public MAknFadedComponent,
                         public MAknPopupFieldObserver,
                         public MAknPopupSettingListObserver
    {
public:// Constructors and destructor
    /**
    * C++ default constructor.
    */
    CTestSDKPopupsPF();
    
    /**
    * Destructor.
    */
    ~CTestSDKPopupsPF();
    
public://from MAknFadedComponent
    /**
    *  CountFadedComponents test function for testing the 
    * Test CountFadedComponents function
    */
    TInt CountFadedComponents();

    /**
    *  FadedComponent test function for testing the 
    * Test FadedComponent function
    */
    CCoeControl* FadedComponent( TInt aIndex );
    
public://from MAknPopupFieldObserver
    void HandlePopupFieldEventL ( CAknPopupField* aPopupField, 
             TAknPopupFieldEvent aEventType, TInt aHint );
    
public://from MAknPopupSettingListObserver
    void HandlePopupSettingListEventL( CAknPopupSettingList* aPopupSettingList, 
             TAknPopupSettingListEvent aEventType, TInt aHint);
    };

#endif /*C_TESTSDKPOPUPSPF_H*/
