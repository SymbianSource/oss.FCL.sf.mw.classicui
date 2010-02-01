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
* Description:  Application class of bctestsingleclick.
*
*/

#ifndef C_BCTESTSINGLECLICKAPP_H
#define C_BCTESTSINGLECLICKAPP_H

#include <aknapp.h>

const TUid KUidBCTESTSingleClick = { 0x200089c8 }; // UID of the application.

/**
* CBCTESTSingleClickApp class.
* Provides factory to create concrete document object.
*/
class CBCTESTSingleClickApp : public CAknApplication
    {
    private: // From CApaApplication

        /**
        * From CApaApplication, CreateDocumentL.
        * Creates CBCTESTSingleClickDocument document object.
        * @return A pointer to the created document object.
        */
        CApaDocument* CreateDocumentL();

        /**
        * From CApaApplication, AppDllUid.
        * Returns application's UID ( KUidBCTESTSingleClick ).
        * @return The value of KUidBCTESTSingleClick.
        */
        TUid AppDllUid() const;

    };

#endif // C_BCTESTSINGLECLICKAPP_H

// End of File
