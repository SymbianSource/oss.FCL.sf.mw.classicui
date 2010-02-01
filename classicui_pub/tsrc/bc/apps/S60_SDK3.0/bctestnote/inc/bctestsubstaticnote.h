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
* Description:         Invoke static note's protected APIs.
*
*/









#ifndef C_CBCTESTSUBSTATICNOTE_H
#define C_CBCTESTSUBSTATICNOTE_H

#include <aknstaticnotedialog.h>

#include "bcteststaticnotecase.h"

/**
 * Invoke staticnote's protected APIs
 */
class CBCTestSubStaticNote: public CAknStaticNoteDialog
    {
public: // constructor and destructor

    friend class CBCTestStaticNoteCase;
    
    /**
     * Symbian 2nd static constructor
     */
    static CBCTestSubStaticNote* NewL();

    /**
     * Destructor
     */
    virtual ~CBCTestSubStaticNote ();
    
private: // constructor

    /**
     * C++ default constructor
     */
    CBCTestSubStaticNote();

    /**
     * Symbian 2nd constructor
     */
    void ConstructL();

private: // data
   
    };

#endif // C_CBCTESTSUBSTATICNOTE_H
