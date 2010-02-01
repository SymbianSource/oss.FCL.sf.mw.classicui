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
* Description:         Invoke popup list's protected APIs.
*
*/









#ifndef C_CBCTESTSUBPOPUP_H
#define C_CBCTESTSUBPOPUP_H

#include <aknpopup.h>

/**
 * Invoke popup list's protected APIs
 */
class CBCTestSubPopup: public CAknPopupList
    {
public: // constructor and destructor

    friend class CBCTestPopupCase;

    /**
     * Symbian 2nd static constructor
     */
    static CBCTestSubPopup* NewL(
        CEikListBox *aListBox, TInt aCbaResource,
        AknPopupLayouts::TAknPopupLayouts
        aType = AknPopupLayouts::EMenuWindow );

    /**
     * Destructor
     */
    virtual ~CBCTestSubPopup ();

private: // constructor

    /**
     * C++ default constructor
     */
    CBCTestSubPopup();

    /**
     * Symbian 2nd constructor
     */
    void ConstructL(
        CEikListBox *aListBox, TInt aCbaResource,
        AknPopupLayouts::TAknPopupLayouts
        aType = AknPopupLayouts::EMenuWindow );

private: //data

    };

#endif // C_CBCTESTSUBPOPUP_H
