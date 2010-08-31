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
* Description:  test aknPopupHeadingPane.h 
*
*/


#ifndef C_TESTSDKPOPUPSCONTROL_H
#define C_TESTSDKPOPUPSCONTROL_H

#include <coecobs.h>

class CTestSDKPopupsControl : public CCoeControl
    {
public:// Constructors and destructor
    /**
    * C++ default constructor.
    */
    CTestSDKPopupsControl();
    
    /**
    * Destructor.
    */
    ~CTestSDKPopupsControl();
    
    /**
     * ConstructL
     */
    void ConstructL();
    };

#endif /*C_TESTSDKPOPUPSCONTROL_H*/
