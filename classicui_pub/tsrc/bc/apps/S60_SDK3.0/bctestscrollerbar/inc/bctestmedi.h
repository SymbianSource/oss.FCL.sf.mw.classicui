/*
* Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:         test case
*
*/









#ifndef BCTEST_MEDI_H
#define BCTEST_MEDI_H

#include <eikscrlb.h>


/**
* test case for various list classes
*/

class CBCTestMedi: public CEikScrollBar 
    {
public: // constructor and destructor
    friend class CBCTestScrollerCase;  

    /**
     * C++ default constructor
     */
     CBCTestMedi();

     
    /**
     * Symbian 2nd constructor
     */
     void ConstructL();

    /**
    * Destructor
    */
    virtual ~CBCTestMedi();
private:
    void SizeChanged();
    
    };

#endif // BCTEST_MISCELLCASE_H