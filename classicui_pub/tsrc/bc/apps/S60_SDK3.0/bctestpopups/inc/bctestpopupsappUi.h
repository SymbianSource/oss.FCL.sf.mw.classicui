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
* Description:         Declares test bc for popups control appui.
*
*/









#ifndef C_CBCTESTPOPUPSAPPUI_H
#define C_CBCTESTPOPUPSAPPUI_H

#include <aknviewappui.h>

class CBCTestPopupsView;

/**
 * Application UI class
 */
class CBCTestPopupsAppUi : public CAknViewAppUi
    {
public: // Constructors and destructor

    /**
     * ctor
     */
    CBCTestPopupsAppUi();

    /**
     * symbian 2nd ctor
     */
    void ConstructL();

    /**
     * dtor
     */
    virtual ~CBCTestPopupsAppUi();

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
    CBCTestPopupsView*  iView;
    
    };

#endif // C_CBCTESTPOPUPSAPPUI_H
