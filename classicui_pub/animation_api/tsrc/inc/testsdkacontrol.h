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
* Description:  Test AknBitmapAnimation.h
*
*/

#ifndef C_TESTSDKACONTROL_H
#define C_TESTSDKACONTROL_H
//  INCLUDES
#include <coecntrl.h>
#include <e32std.h>
#include <testclassassert.h>
#include <stifitemparser.h>
#include <aknbitmapanimation.h>

class CTestControl : public CCoeControl
    {
public:
    /**
    * Two-phased constructor.
    */
    static CTestControl* NewL();
    
    /**
    * destructor
    */
    ~CTestControl();
    
    /**
    *  TestRunL test function for testing the 
    * Test TestRunL function
    */
    void TestRunL();
    
    /**
    *  SetFrameIndexL test function for testing the 
    * Test SetFrameIndexL function
    */
    void SetFrameIndexL( TInt aIndex );
    
    /**
    *  SetFrameIntervalL test function for testing the 
    * Test SetFrameIntervalL function
    */
    void SetFrameIntervalL( TInt aFrameIntervalInMilliSeconds );
    
    /**
    *  TestCancelL test function for testing the 
    * Test TestCancelL function
    */
    void TestCancelL();
private:
    
    /**
    * Constructors
    */
    CTestControl();
    
    /**
    * By default Symbian 2nd phase constructor is private.
    */
    void ConstructL();
    
    /**
    * OfferKeyEventL
    */
    TKeyResponse OfferKeyEventL( const TKeyEvent& aKeyEvent,TEventCode aType );
    
    /**
    * Draw
    */
    void Draw( const TRect& aRect ) const;
    
    /**
    * CountComponentControls
    */
    TInt CountComponentControls() const;
    
    /**
    * ComponentControl
    */
    CCoeControl* ComponentControl( TInt aIndex ) const;
    
    /**
    * SizeChanged
    */
    void SizeChanged();
    
private:
    //data
    CAknBitmapAnimation* iBitmapAnimation;
    };

#endif /*C_TESTSDKACONTROL_H*/
