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
* Description:         ui class
*
*/









#ifndef BCTESTFORMAPPUI_H
#define BCTESTFORMAPPUI_H

// INCLUDES
#include <aknviewappui.h>

// FORWARD DECLARATIONS
//class CAknAtScreenCaptureContainer;
class CBCTestUtil;
// CONSTANTS

// CLASS DECLARATION

/**
* Application UI class.
* Provides support for the following features:
* - UIKON control architecture
* - view architecture
* - status pane
*/
class CBCTestFormAppUi : public CAknViewAppUi
    {
    public: // Constructors and destructor

	/**
	* Default constructor.
	*/
	CBCTestFormAppUi();

	/**
	* Symbian 2nd phase constructor.
	*/
	void ConstructL();

	/**
	* Destructor.
	*/
	virtual ~CBCTestFormAppUi();

    private: // From CEikAppUi
        CBCTestUtil*  iTestUtil;
	/**
	* From CEikAppUi, HandleCommandL.
	* Handles the commands.
	* @param aCommand Command to be handled
	*/
	void HandleCommandL( TInt aCommand );
//CAknAtScreenCaptureContainer* iScreenCaptureContainer;
    };

#endif

// End of File
