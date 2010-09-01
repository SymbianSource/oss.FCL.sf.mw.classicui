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
* Description:  Test EIKESECED.H
*
*/

#ifndef C_TESTSDKEDITORSSECRETTEXT_H
#define C_TESTSDKEDITORSSECRETTEXT_H

//  INCLUDES
#include <eikseced.h>

    /**
    *  CTestSDKEditorsRichText test class for CEikRichTextEditor protected API.
    */
class CTestSDKEditorsSecretText : public CEikSecretEditor
    {
public:
    
    /**
    *  WriteInternalStateL test function for testing the 
    * Test WriteInternalStateL function
    */
    void AppendCharacterL( TInt aKeyCode );
    
    /**
    *  EditObserver test function for testing the 
    * Test EditObserver function
    */
    void Update();
    
    /**
    *  SizeChanged test function for testing the 
    * Test SizeChanged function
    */
    void SizeChanged();
    };


#endif /*C_TESTSDKEDITORSSECRETTEXT_H*/
