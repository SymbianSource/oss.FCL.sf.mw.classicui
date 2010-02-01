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
* Description:         Invoke popup field's protected APIs.
*
*/









#ifndef C_CBCTESTSUBPOPUPFIELDTEXT_H
#define C_CBCTESTSUBPOPUPFIELDTEXT_H

#include <aknpopupfield.h>

class CAknForm;

/**
 * Invoke popup field's protected APIs
 */
class CBCTestSubPopupFieldText: public CAknPopupField
    {
public: // constructor and destructor

    friend class CBCTestPopupFieldTextCase;
    
    /**
     * Symbian 2nd static constructor
     */
    static CBCTestSubPopupFieldText* NewL();

    /**
     * Destructor
     */
    virtual ~CBCTestSubPopupFieldText ();
    
private: // constructor

    /**
     * C++ default constructor
     */
    CBCTestSubPopupFieldText();

    /**
     * Symbian 2nd constructor
     */
    void ConstructL();

private: //data

    CAknForm* iBaseDialog;    
   
    };

#endif // C_CBCTESTSUBPOPUPFIELDTEXT_H
