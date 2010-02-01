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
* Description:  test AknPopupField.h 
*
*/


#ifndef C_TESTSDKPOPUPSCPF_H
#define C_TESTSDKPOPUPSCPF_H

#include <coecobs.h>
#include <aknpopupfield.h>

class CTestSDKPopupsCPF : public CAknPopupField
    {
public:// Constructors and destructor
    /**
    * C++ default constructor.
    */
    CTestSDKPopupsCPF();
    
    /**
    * Destructor.
    */
    ~CTestSDKPopupsCPF();
public:
    
    /**
    *  HandleControlEventL test function for testing the 
    * Test HandleControlEventL function
    */
    void HandleControlEventL( CCoeControl* aControl,TCoeEvent aEvent );
    
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
    *  CountComponentControls test function for testing the 
    * Test CountComponentControls function
    */
    TInt CountComponentControls() const;
    
    /**
    *  ComponentControl test function for testing the 
    * Test ComponentControl function
    */
    CCoeControl* ComponentControl(TInt aIndex) const;
    
    /**
    *  SizeChanged test function for testing the 
    * Test SizeChanged function
    */
    void SizeChanged();
    
    /**
    *  FocusChanged test function for testing the 
    * Test FocusChanged function
    */
    void FocusChanged( TDrawNow aDrawNow );
    
    /**
    *  Draw test function for testing the 
    * Test Draw function
    */
    void Draw(const TRect& aRect) const;
    
    /**
    *  MopSupplyObject test function for testing the 
    * Test MopSupplyObject function
    */
    TTypeUid::Ptr MopSupplyObject( TTypeUid aId );
    
    };
#endif /*C_TESTSDKPOPUPSCPF_H*/
