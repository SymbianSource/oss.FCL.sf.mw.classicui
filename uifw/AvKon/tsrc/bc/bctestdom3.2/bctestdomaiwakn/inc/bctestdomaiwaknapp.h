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
* Description: 
*
*/

#ifndef C_CBCTESTDOMAIWAKNAPP_H
#define C_CBCTESTDOMAIWAKNAPP_H

#include <aknapp.h>

const TUid KUidBCTestAiwAkn = { 0xA000409E }; // UID of the application.

/**
 *  CBCTestDomAiwAknApp class.
 *  Provides factory to create concrete document object.
 *
 *  @code
 *    
 *  @endcode
 *
 *  @lib avkon.lib eikcore.lib eiksrv.lib 
 *  @since S60 v5.0
 */
class CBCTestDomAiwAknApp : public CAknApplication
    {

private:  
// from base class CApaApplication

    /**
     * From CApaApplication.
     * Creates CBCTestDomAiwAknDocument document object.
     *
     * @since S60 v5.0
     * @return A pointer to the created document object.
     */        
    CApaDocument* CreateDocumentL();


    /**
     * From CApaApplication.
     * Returns application's UID ( KUidBCTestAiwAkn ).
     *
     * @since S60 v5.0
     * @return The value of KUidBCTestAiwAkn.
     */ 
    TUid AppDllUid() const;

    };

#endif // C_CBCTESTDOMAIWAKNAPP_H

// End of File
