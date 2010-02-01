/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Declares main application class.
*
*/


#ifndef C_CBCTESTDOMHWRRECOGNIZER_H
#define C_CBCTESTDOMHWRRECOGNIZER_H


#include <ptihwrrecognizer.h>

class CBCTestDomHwrRecognizer : public CHwrRecognizer
    {
public:
    static CBCTestDomHwrRecognizer* NewL();       
    
    ~CBCTestDomHwrRecognizer(); 
protected:

    /**
     * C++ default constructor
     */
    CBCTestDomHwrRecognizer();

    /**
    * Second phase constructor
    *
    * @return None
    */
    void ConstructL();
    };

#endif
