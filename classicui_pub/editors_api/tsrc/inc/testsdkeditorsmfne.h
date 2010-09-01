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
* Description:  Test EikMFNE.H
*
*/

#ifndef C_TESTSDKEDITORSMFNE_H
#define C_TESTSDKEDITORSMFNE_H

//  INCLUDES
#include <eikmfne.h>

    /**
    *  CTestSDKEditorsNumed test class for CAknNumericEdwin protected API.
    */
class CTestSDKEditorsMFNE : public CEikMfneField
    {
public:
    
    /**
    * C++ default constructor.
    */
    CTestSDKEditorsMFNE();
    
    /**
     * Destructor.
     */
    ~CTestSDKEditorsMFNE();
    
    /**
    *  MaximumWidthInPixels test function for testing the 
    * Test MaximumWidthInPixels function
    */
    TInt MaximumWidthInPixels( const CFont& aFont, TBool aShrinkToMinimumSize );

    /**
    *  InputCapabilities test function for testing the 
    * Test InputCapabilities function
    */
    TCoeInputCapabilities InputCapabilities() const;
    
    /**
    *  HandleLeftOrRightArrow test function for testing the 
    * Test HandleLeftOrRightArrow function
    */
    void HandleLeftOrRightArrow( TChar aKey, TBool& aDataAltered, TInt& aHighlightIncrement );
    
private:
    /**
    *  Text test function for testing the 
    * Test Text function
    */
    const TDesC& Text() const;

    };


#endif /*C_TESTSDKEDITORSMFNE_H*/
