/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  declaration of app.
*
*/


#ifndef C_BCTESTDOMAPOPUPAPP_H
#define C_BCTESTDOMAPOPUPAPP_H

#include <aknapp.h>

const TUid KUidBCTestDomPopup = { 0xA00040A6 }; // UID of the application.

/**
* CBCDomainTestPopupApp class.
* Provides factory to create concrete document object.
*/
class CBCDomainTestPopupApp : public CAknApplication
    {
private: 
// From CApaApplication

    /**
    * From CApaApplication, CreateDocumentL.
    * Creates CBCDomainTestPopupDocument document object.
    * @return A pointer to the created document object.
    */
    CApaDocument* CreateDocumentL();

    /**
    * From CApaApplication, AppDllUid.
    * Returns application's UID ( KUidBCDomainTestPopup ).
    * @return The value of KUidBCDomainTestPopup.
    */
    TUid AppDllUid() const;

    };

#endif // C_BCTESTDOMAPOPUPAPP_H

// End of File
