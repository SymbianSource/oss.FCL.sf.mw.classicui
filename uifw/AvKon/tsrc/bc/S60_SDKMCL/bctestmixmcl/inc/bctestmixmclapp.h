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


#ifndef C_BCTESTMIXMCLAPP_H
#define C_BCTESTMIXMCLAPP_H

#include <aknapp.h>

/**   UID of the application */
const TUid KUidBCTestMixMCL = { 0xA00040AD }; 

/**
 * CBCTestMixMCLApp class.
 * Provides factory to create concrete document object.
 *
 *  @lib avkon.lib eikcore.lib eiksrv.lib 
 *  @since S60 v5.0
 */
class CBCTestMixMCLApp : public CAknApplication
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

#endif // C_BCTESTMIXMCLAPP_H