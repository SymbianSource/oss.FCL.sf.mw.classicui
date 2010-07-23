/*
* Copyright (c) 2006-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:         Declares UI class for application.
*
*/









#ifndef C_CBCTESTLAUNCHERAPPUI_H
#define C_CBCTESTLAUNCHERAPPUI_H

#include <eikapp.h>
#include <eikdoc.h>
#include <e32std.h>
#include <coeccntx.h>
#include <aknviewappui.h>
#include <akntabgrp.h>
#include <aknnavide.h>

class CBCTestLauncherContainer;
class CBCTestLauncherView;
class CBCTestRunner;

/**
 * Application UI class.
 */
class CBCTestLauncherAppUi : public CAknViewAppUi
    {
public:  // Constructors and destructor
    
    /**
     * C++ default constructor.
     */
    CBCTestLauncherAppUi();

    /**
     * Symbian 2nd phase constructor.
     */      
    void ConstructL();

    /**
     * Destructor.
     */      
    virtual ~CBCTestLauncherAppUi();
    
    void DoCommand();

private:  // From CEikAppUi

    /**
     * From CEikAppUi, takes care of command handling.
     * @param aCommand command to be handled
     */
    void HandleCommandL( TInt aCommand );

    /**
     * From CEikAppUi, handles key events.
     * @param aKeyEvent Event to handled.
     * @param aType Type of the key event. 
     * @return Reponse code ( EKeyWasConsumed, EKeyWasNotConsumed ). 
     */
    virtual TKeyResponse HandleKeyEventL(
        const TKeyEvent& aKeyEvent, TEventCode aType );

private: //Data

    CAknNavigationControlContainer*  iNaviPane;
    CBCTestLauncherContainer* iAppContainer; // Ptr to Container class 
	CBCTestLauncherView* iAppView;
    CBCTestRunner*       iRunner;   // own
    
    };
    
#endif // C_CBCTESTLAUNCHERAPPUI_H

