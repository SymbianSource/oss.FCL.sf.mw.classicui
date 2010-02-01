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
* Description:  Declares main application class.
 *
*/


#ifndef __AKNCONFAPPLICATION_H__
#define __AKNCONFAPPLICATION_H__

// INCLUDES
#include <aknapp.h>
#include "aknconf.hrh"

// UID for the application;
// this should correspond to the uid defined in the mmp file
const TUid KUidaknconfApp =
    {_UID3};

// CLASS DECLARATION

/**
 * CAknConfApplication application class.
 * Provides factory to create concrete document object.
 * An instance of CAknConfApplication is the application part of the
 * AVKON application framework for the aknconf example application.
 */
class CAknConfApplication : public CAknApplication
    {
public:
    // Functions from base classes

    /**
     * From CApaApplication, AppDllUid.
     * @return Application's UID (KUidaknconfApp).
     */
    TUid AppDllUid() const;

protected:
    // Functions from base classes

    /**
     * From CApaApplication, CreateDocumentL.
     * Creates CAknConfDocument document object. The returned
     * pointer in not owned by the CAknConfApplication object.
     * @return A pointer to the created document object.
     */
    CApaDocument* CreateDocumentL();
    };

#endif // __AKNCONFAPPLICATION_H__
// End of File
