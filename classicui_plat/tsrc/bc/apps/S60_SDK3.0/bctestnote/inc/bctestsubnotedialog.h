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
* Description:         Invoke note dialog's protected APIs.
*
*/









#ifndef C_CBCTESTSUBNOTEDIALOG_H
#define C_CBCTESTSUBNOTEDIALOG_H

#include <aknnotedialog.h>

#include "bctestnotedialogcase.h"

/**
 * Invoke notedialog's protected APIs
 */
class CBCTestSubNoteDialog: public CAknNoteDialog
    {
public: // constructor and destructor

    friend class CBCTestNoteDialogCase;
    
    /**
     * Symbian 2nd static constructor
     */
    static CBCTestSubNoteDialog* NewL();

    /**
     * Destructor
     */
    virtual ~CBCTestSubNoteDialog ();
    
private: // constructor

    /**
     * C++ default constructor
     */
    CBCTestSubNoteDialog();

    /**
     * Symbian 2nd constructor
     */
    void ConstructL();

private: // data
   
    };

#endif // C_CBCTESTSUBNOTEDIALOG_H
