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
* Description:  Test EIKEGTED.H
*
*/

#ifndef C_TESTSDKEDITORSGLOBALTEXT_H
#define C_TESTSDKEDITORSGLOBALTEXT_H

//  INCLUDES
#include <eikgted.h>

    /**
    *  CTestSDKEditorsGloablText test class for CEikGlobalTextEditor protected API.
    */
class CTestSDKEditorsGloablText : public CEikGlobalTextEditor
    {
public:
    
    /**
    *  WriteInternalStateL test function for testing the 
    * Test WriteInternalStateL function
    */
    void WriteInternalStateL(RWriteStream& aWriteStream) const;
    
    /**
    *  BaseConstructL test function for testing the 
    * Test BaseConstructL function
    */
    void BaseConstructL();
    };
#endif /*C_TESTSDKEDITORSGLOBALTEXT_H*/
