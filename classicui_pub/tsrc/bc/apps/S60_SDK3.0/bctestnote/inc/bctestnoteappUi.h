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
* Description:         Declares test bc for note control appui.
*
*/









#ifndef C_CBCTESTNOTEAPPUI_H
#define C_CBCTESTNOTEAPPUI_H

#include <aknviewappui.h>

class CBCTestNoteView;

/**
 * Application UI class
 */
class CBCTestNoteAppUi : public CAknViewAppUi
    {
public: // Constructors and destructor

    /**
     * ctor
     */
    CBCTestNoteAppUi();

    /**
     * symbian 2nd ctor
     */
    void ConstructL();

    /**
     * dtor
     */
    virtual ~CBCTestNoteAppUi();

private:

// From CEikAppUi
    /**
     * From CEikAppUi
     */
    void HandleCommandL( TInt aCommand );

private: // data

    /**
     * pointer to the view.
     * own
     */
    CBCTestNoteView*  iView;
    
    };

#endif // C_CBCTESTNOTEAPPUI_H
