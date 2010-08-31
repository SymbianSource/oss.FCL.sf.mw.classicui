/*
* Copyright (c) 2002-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:         Avkon misc test app
*
*/









// INCLUDE FILES
#include "bctestmisc32app.h"
#include "bctestmisc32document.h"
#include <eikstart.h>

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// TUid CBCTestmisc32App::AppDllUid()
// Returns application UID.
// ----------------------------------------------------------------------------
//
TUid CBCTestmisc32App::AppDllUid() const
    {
    return KUidBCTestmisc32;
    }

// ----------------------------------------------------------------------------
// CApaDocument* CBCTestmisc32App::CreateDocumentL()
// Creates CBCTestmisc32Document object.
// ----------------------------------------------------------------------------
//
CApaDocument* CBCTestmisc32App::CreateDocumentL()
    {
    return CBCTestmisc32Document::NewL( *this );
    }

// ================= OTHER EXPORTED FUNCTIONS =================================
//
// ----------------------------------------------------------------------------
// CApaApplication* NewApplication()
// Constructs CBCTestmisc32App.
// Returns: CApaDocument*: created application object
// ----------------------------------------------------------------------------
//
LOCAL_C CApaApplication* NewApplication()
    {
    return new CBCTestmisc32App;
    }

GLDEF_C TInt E32Main()
    {
    return EikStart::RunApplication(NewApplication);
    }

// End of File
