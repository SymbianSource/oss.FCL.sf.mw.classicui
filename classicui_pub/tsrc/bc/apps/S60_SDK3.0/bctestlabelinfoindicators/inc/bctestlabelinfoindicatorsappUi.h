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
* Description:         Declares test bc for labelinfoindicators appui.
*
*/









#ifndef C_CBCTESTLABELINFOINDICATORSAPPUI_H
#define C_CBCTESTLABELINFOINDICATORSAPPUI_H

#include <aknviewappui.h>

class CBCTestLabelInfoIndicatorsView;

/**
 * Application UI class
 */
class CBCTestLabelInfoIndicatorsAppUi : public CAknViewAppUi
    {
public: // Constructors and destructor

    /**
     * ctor
     */
    CBCTestLabelInfoIndicatorsAppUi();

    /**
     * symbian 2nd ctor
     */
    void ConstructL();

    /**
     * dtor
     */
    virtual ~CBCTestLabelInfoIndicatorsAppUi();

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
    CBCTestLabelInfoIndicatorsView*  iView;
    
    };

#endif // C_CBCTESTLABELINFOINDICATORSAPPUI_H
