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
* Description:         Application
*
*/








#ifndef C_CBCTESTLISTAPP_H
#define C_CBCTESTLISTAPP_H

// INCLUDES
#include <aknapp.h>

// CONSTANTS
const TUid KUidBCTestList = { 0x20004748 }; // UID of the application         

// CLASS DECLARATION

/**
* CBCTestListApp application class.
* Provides factory to create concrete document object.
*/

class CBCTestListApp : public CAknApplication
    {
	
    private: // From CApaAppcication
	
	/**
	* From CApaApplication, CreateDocumentL.
	* Creates CBCTestListDocument document object.
	* @return A pointer to the created document object.
	*/
	CApaDocument* CreateDocumentL();
	
	/**
	* From CApaApplication, AppDllUid.
	* Returns application's UID (KUidBCTestList).
	* @return The value of KUidBCTestList.
	*/
	TUid AppDllUid() const;

    };

#endif // C_CBCTESTLISTAPP_H
