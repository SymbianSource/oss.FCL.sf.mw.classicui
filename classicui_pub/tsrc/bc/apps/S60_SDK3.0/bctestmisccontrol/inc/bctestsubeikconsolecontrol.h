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
* Description:         Invoke eik console control's protected APIs.
*
*/









#ifndef C_CBCTESTSUBEIKCONSOLECONTROL_H
#define C_CBCTESTSUBEIKCONSOLECONTROL_H

#include <eikconso.h>

/**
 * Invoke eik captioned control's protected APIs
 */
class CBCTestSubEikConsoleControl: public CEikConsoleControl  
    {    

    friend class CBCTestEikConsoleControlCase;
    
public: // constructor and destructor

    /**
     * Destructor
     */
    virtual ~CBCTestSubEikConsoleControl();

    /**
     * C++ default constructor
     */
    CBCTestSubEikConsoleControl();

    };

#endif // C_CBCTESTSUBEIKCONSOLECONTROL_H
