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
* Description:         Invoke eik mover's protected APIs.
*
*/









#ifndef C_CBCTESTSUBEIKMOVER_H
#define C_CBCTESTSUBEIKMOVER_H

#include <eikmover.h>

/**
 * Invoke eik mover's protected APIs
 */
class CBCTestSubEikMover: public CEikMover
    {    

    friend class CBCTestEikControlGroupCase;

public: // constructor and destructor

    /**
     * Destructor
     */
    virtual ~CBCTestSubEikMover();

    /**
     * C++ default constructor
     */
    CBCTestSubEikMover();

    };

#endif // C_CBCTESTSUBEIKMOVER_H
