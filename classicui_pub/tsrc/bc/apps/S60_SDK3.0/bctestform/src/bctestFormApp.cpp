/*
* Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:         For bctestform application
*
*/








// INCLUDE FILES
#include "BCTestFormApp.h"
#include "BCTestFormDocument.h"
#include <eikstart.h>

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// TUid CBCTestFormApplication::AppDllUid()
// Returns application UID.
// ----------------------------------------------------------------------------
//
TUid CBCTestFormApplication::AppDllUid() const
    {
    return KUidBCTestForm;
    }

// ----------------------------------------------------------------------------
// CApaDocument* CBCTestFormApplication::CreateDocumentL()
// Creates CBCTestFormDocument object.
// ----------------------------------------------------------------------------
//
CApaDocument* CBCTestFormApplication::CreateDocumentL()
    {
    return CBCTestFormDocument::NewL( *this );
    }

// ================= OTHER EXPORTED FUNCTIONS =================================

// ----------------------------------------------------------------------------
// CApaApplication* NewApplication()
// Constructs CBCTestFormApplication.
// Returns: CApaDocument*: created application object
// ----------------------------------------------------------------------------
//
LOCAL_C CApaApplication* NewApplication()
    {
    return new CBCTestFormApplication;
    }

GLDEF_C TInt E32Main()
    {
    return EikStart::RunApplication(NewApplication);
    }

// End of File
