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
* Description:         Declares main application class.
*
*/









#ifndef C_CBCTESTLAUNCHERAPP_H
#define C_CBCTESTLAUNCHERAPP_H

#include <aknapp.h>

// UID of the application
const TUid KUidBCTestLauncher = { 0x20004743 };

/**
 * CBCTestLauncherApp application class.
 * Provides factory to create concrete document object.
 * 
 */
class CBCTestLauncherApp : public CAknApplication
    {
private:  // From CApaApplication

    /**
    * From CApaApplication,
    * creates CBCTestLauncherDocument document object.
    * @return A pointer to the created document object.
    */
    CApaDocument* CreateDocumentL();

    /**
    * From CApaApplication,
    * returns application's UID ( KUidBCTestLauncher ).
    * @return The value of KUidBCTestLauncher.
    */
    TUid AppDllUid() const;
    };

#endif //C_CBCTESTLAUNCHERAPP_H


