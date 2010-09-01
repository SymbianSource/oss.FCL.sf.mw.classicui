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

#ifndef C_TESTSDKEDITORSEIKMFNE_H
#define C_TESTSDKEDITORSEIKMFNE_H

//  INCLUDES
#include <eikmfne.h>

    /**
    *  CTestSDKEditorsNumed test class for CAknNumericEdwin protected API.
    */
class CTestSDKEditorsEIKMFNE : public CEikMfne
    {
public:
    
    /**
    *  FocusChanged test function for testing the 
    * Test FocusChanged function
    */
    void FocusChanged(TDrawNow aDrawNow);
    
    /**
    *  WriteInternalStateL test function for testing the 
    * Test WriteInternalStateL function
    */
    void WriteInternalStateL(RWriteStream& aWriteStream) const;
    
    /**
    *  HandleInteraction test function for testing the 
    * Test HandleInteraction function
    */
    void HandleInteraction( TBool aHandleDeHighlight, 
                            TInt aNewCurrentField, 
                            TInt aOldWidthInPixelsOfOldCurrentField,
                            CEikMfneField::THighlightType aOldHighlightTypeOfOldCurrentField, 
                            TBool& aDataAltered, 
                            TBool& aError );

    /**
    *  FieldIsAboutToBeDeHighlighted test function for testing the 
    * Test FieldIsAboutToBeDeHighlighted function
    */
    void FieldIsAboutToBeDeHighlighted( CEikMfneField* aField, 
                                       TBool& aDrawAllFields );
    
    /**
    *  MfneSize test function for testing the 
    * Test MfneSize function
    */
    TSize MfneSize() const;
    
    /**
    *  MfneSize test function for testing the 
    * Test MfneSize function
    */
    TSize MfneSize(TBool aShrinkToMinimumSize);
    
    /**
    *  SizeChanged test function for testing the 
    * Test SizeChanged function
    */
    void SizeChanged();
    };



#endif /*C_TESTSDKEDITORSEIKMFNE_H*/
