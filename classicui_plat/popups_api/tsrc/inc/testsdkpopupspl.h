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
* Description:  test aknPopup.h 
*
*/


#ifndef C_TESTSDKPOPUPSPL_H
#define C_TESTSDKPOPUPSPL_H

#include <aknpopup.h>
#include <coecobs.h>


class CTestSDKPopupsPL : public CAknPopupList
    {
private:// Constructors and destructor
    /**
    * C++ default constructor.
    */
    CTestSDKPopupsPL();
    
public:
    /**
    * Destructor.
    */
    ~CTestSDKPopupsPL();
    
    /**
    * Two-phased constructor.
    */
    static CTestSDKPopupsPL* NewL( CEikListBox* aListBox, TInt aCbaResource,
        AknPopupLayouts::TAknPopupLayouts aType = AknPopupLayouts::EMenuWindow );
public:
    /**
    *  Layout test function for testing the 
    * Test Layout function
    */
    TAknPopupWindowLayoutDef& Layout();
    
    /**
    *  ProcessCommandL test function for testing the 
    * Test ProcessCommandL function
    */
    void ProcessCommandL( TInt aCommandId );
    
    /**
    *  HandleListBoxEventL test function for testing the 
    * Test HandleListBoxEventL function
    */
    void HandleListBoxEventL( CEikListBox* aListBox, TListBoxEvent aEventType );
    
    /**
    *  HandleControlEventL test function for testing the 
    * Test HandleControlEventL function
    */
    void HandleControlEventL( CCoeControl* aControl, TCoeEvent aEventType );
    
    /**
    *  AttemptExitL test function for testing the 
    * Test AttemptExitL function
    */
    void AttemptExitL( TBool aAccept );
    
    /**
    *  SetupWindowLayout test function for testing the 
    * Test SetupWindowLayout function
    */
    void SetupWindowLayout( AknPopupLayouts::TAknPopupLayouts aType );
    
    /**
    *  ListBox test function for testing the 
    * Test ListBox function
    */
    CEikListBox* ListBox() const;
    
    /**
    *  Layout test function for testing the 
    * Test Layout function
    */
    const TAknPopupWindowLayoutDef& Layout() const;
    
    /**
    *  MopSupplyObject test function for testing the 
    * Test MopSupplyObject function
    */
    TTypeUid::Ptr MopSupplyObject( TTypeUid aId );
    
    /**
    *  HandleResourceChange test function for testing the 
    * Test HandleResourceChange function
    */
    void HandleResourceChange( TInt aType );
    
    /**
    *  FadeBehindPopup test function for testing the 
    * Test FadeBehindPopup function
    */
    void FadeBehindPopup( TBool aFade );
    
    /**
    *  ActivateGc test function for accessing the 
    *  protected function ActivateGc
    */
    void ActivateGc() const;

    /**
    *  DeactivateGc test function for accessing the 
    * protected function DeactivateGc
    */    
    void DeactivateGc() const;

    
    };

#endif /*C_TESTSDKPOPUPSPL_H*/
