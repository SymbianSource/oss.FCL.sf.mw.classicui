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
* Description:  Test EIKLABEL.H, eikfnlab.h
*
*/


#ifndef C_TESTSDKLABELSLABEL_H
#define C_TESTSDKLABELSLABEL_H

#include <eiklabel.h>

class CTestSDKLabelsLabel : public CEikLabel
    {
public:
    /**
    * Two-phased constructor.
    */
    static CTestSDKLabelsLabel* NewLC();
    
    /**
    * destructor
    */
    ~CTestSDKLabelsLabel();
    
    /**
    *  WriteInternalStateL test function for testing the 
    * Test WriteInternalStateL function
    */
    void WriteInternalStateL( RWriteStream& aWriteStream ) const;
    
private:
    /**
    * By default Symbian 2nd phase constructor is private.
    */
    void ConstructL();
    
    /**
    * Constructors
    */
    CTestSDKLabelsLabel();
    };

#endif /*C_TESTSDKLABELSLABEL_H*/
