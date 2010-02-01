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
* Description:         Invoke eik progress info's protected APIs.
*
*/









#ifndef C_CBCTESTSUBEIKPROGRESSINFO_H
#define C_CBCTESTSUBEIKPROGRESSINFO_H

#include <eikprogi.h>

#include "bctesteikprogressinfocase.h"

/**
 * Invoke staticnote's protected APIs
 */
class CBCTestSubEikProgressInfo: public CEikProgressInfo
    {
public: // constructor and destructor

    friend class CBCTestEikProgressInfoCase;
    
    /**
     * Symbian 2nd static constructor
     */
    static CBCTestSubEikProgressInfo* NewL();

    /**
     * Destructor
     */
    virtual ~CBCTestSubEikProgressInfo();
    
private: // constructor

    /**
     * C++ default constructor
     */
    CBCTestSubEikProgressInfo();

    /**
     * Symbian 2nd constructor
     */
    void ConstructL();

private: // data
   
    };

#endif // C_CBCTESTSUBEIKPROGRESSINFO_H
