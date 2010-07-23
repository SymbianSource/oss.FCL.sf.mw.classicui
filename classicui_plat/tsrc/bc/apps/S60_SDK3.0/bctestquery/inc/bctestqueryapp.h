/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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









#ifndef C_BCTESTQUERYAPP_H
#define C_BCTESTQUERYAPP_H

#include <aknapp.h>

const TUid KUidBCTestQuery = { 0x200045C9 }; // UID of the application         

/**
* CBCTestQueryApp application class.
* Provides factory to create concrete document object.
*/

class CBCTestQueryApp : public CAknApplication
    {
	
private: // From CApaAppcication
	
	/**
	 * From CApaApplication, CreateDocumentL.
	 * Creates CBCTestQueryDocument document object.
	 * @return A pointer to the created document object.
	 */
	CApaDocument* CreateDocumentL();
	
	/**
	 * From CApaApplication, AppDllUid.
	 * Returns application's UID (KUidBCTestQuery).
	 * @return The value of KUidBCTestQuery.
	 */
	TUid AppDllUid() const;

    };

#endif // C_BCTESTQUERYAPP_H

