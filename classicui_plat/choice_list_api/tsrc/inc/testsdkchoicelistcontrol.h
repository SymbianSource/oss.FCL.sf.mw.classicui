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
* Description:  test aknchoicelist.h
*
*/


#ifndef C_TESTSDKCHOICELISTCONTROL_H
#define C_TESTSDKCHOICELISTCONTROL_H

#include <aknchoicelist.h>

class CTestSDKChoiceListControl : public CCoeControl
    {
public:// Constructors and destructor
    
    /**
    * Two-phased constructor.
    */
    static CTestSDKChoiceListControl* NewLC();
    
    /**
    * Destructor.
    */
    ~CTestSDKChoiceListControl();
private:
    
    /**
    * C++ default constructor.
    */
    CTestSDKChoiceListControl();
    
    /**
    * By default Symbian 2nd phase constructor is private.
    */
    void ConstructL();
    
private://from CCoeControl
    
    /**
    * CTestSDKChoiceListControl::OfferKeyEventL()
    */
    TKeyResponse OfferKeyEventL( const TKeyEvent& aKeyEvent,TEventCode aType );
    
    /**
    * CTestSDKChoiceListControl::HandlePointerEventL()
    */
    void HandlePointerEventL( const TPointerEvent& aPointerEvent );
    
    /**
    * CTestSDKChoiceListControl::Draw()
    */
    void Draw( const TRect& aRect ) const;
    
    /**
    * CTestSDKChoiceListControl::CountComponentControls()
    */
    TInt CountComponentControls() const;
    
    /**
    * CTestSDKChoiceListControl::ComponentControl()
    */
    CCoeControl* ComponentControl( TInt aIndex ) const;
    
    /**
    * CTestSDKChoiceListControl::SizeChanged()
    */
    void SizeChanged();
    };

#endif /*C_TESTSDKCHOICELISTCONTROL_H*/
