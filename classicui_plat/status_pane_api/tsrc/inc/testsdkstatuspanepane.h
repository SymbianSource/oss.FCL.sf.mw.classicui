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
* Description:  test eikspane.h
 *
*/


#ifndef C_TESTSDKSTATUSPANEPANE_H
#define C_TESTSDKSTATUSPANEPANE_H

#include <eikspane.h>

class CTestSDKStatusPanePane : public CEikStatusPane
    {
public:
    
    /**
    * C++ default constructor.
    */
    static CTestSDKStatusPanePane* NewL( CEikonEnv& aEikEnv, RWindowGroup* aParent, TInt aCoreStatusPaneModelResId );
    
    /**
    *  Rect test function for testing the 
    * Test Rect function
    */
    TRect Rect() const;
    
    /**
    *  DisableClearer test function for testing the 
    * Test DisableClearer function
    */
    void DisableClearer( TBool aDisabled );
    
    /**
    *  CommonPrepareForAppExit test function for testing the 
    * Test CommonPrepareForAppExit function
    */
    void CommonPrepareForAppExit();

    };


#endif /*C_TESTSDKSTATUSPANEPANE_H*/

