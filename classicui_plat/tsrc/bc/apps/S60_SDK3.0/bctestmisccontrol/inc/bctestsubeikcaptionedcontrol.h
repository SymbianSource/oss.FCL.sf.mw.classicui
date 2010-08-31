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
* Description:         Invoke eik captioned control's protected APIs.
*
*/









#ifndef C_CBCTESTSUBEIKCAPTIONEDCONTROL_H
#define C_CBCTESTSUBEIKCAPTIONEDCONTROL_H

#include <eikcapc.h>

/**
 * Invoke eik captioned control's protected APIs
 */
class CBCTestSubEikCaptionedControl: public CEikCaptionedControl  
    {    

    friend class CBCTestEikCaptionedControlCase;
    
public: // constructor and destructor

    /**
     * Destructor
     */
    virtual ~CBCTestSubEikCaptionedControl();

    /**
     * C++ default constructor
     */
    CBCTestSubEikCaptionedControl();

    };

#endif // C_CBCTESTSUBEIKCAPTIONEDCONTROL_H
