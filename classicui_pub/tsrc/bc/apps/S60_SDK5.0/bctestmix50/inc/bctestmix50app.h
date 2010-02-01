/*
* Copyright (c) 2007-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:         declaration of app.
*
*/









#ifndef C_BCTESTMIX50APP_H
#define C_BCTESTMIX50APP_H

#include <aknapp.h>

const TUid KUidBCTestMix50 = { 0xA00040AB }; // UID of the application.

/**
 * CBCTestMix50App class.
 * Provides factory to create concrete document object.
 */
class CBCTestMix50App : public CAknApplication
    {

private:

// From CApaApplication

    /**
     * From CApaApplication, CreateDocumentL.
     * Creates CBCTestMix50Document document object.
     * @return A pointer to the created document object.
     */
    CApaDocument* CreateDocumentL();

    /**
     * From CApaApplication, AppDllUid.
     * Returns application's UID ( KUidBCTestMix50 ).
     * @return The value of KUidBCTestMix50.
     */
    TUid AppDllUid() const;

    };

#endif // C_BCTESTMIX50APP_H
