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
* Description:  
 *
*/


// INCLUDE FILES
#include "aknconf.hrh"
#include "aknconfdocument.h"
#include "aknconfapplication.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CAknConfApplication::CreateDocumentL()
// Creates CApaDocument object
// -----------------------------------------------------------------------------
//
CApaDocument* CAknConfApplication::CreateDocumentL()
    {
    // Create an aknconf document, and return a pointer to it
    return CAknConfDocument::NewL(*this);
    }

// -----------------------------------------------------------------------------
// CAknConfApplication::AppDllUid()
// Returns application UID
// -----------------------------------------------------------------------------
//
TUid CAknConfApplication::AppDllUid() const
    {
    // Return the UID for the aknconf application
    return KUidaknconfApp;
    }

// End of File
