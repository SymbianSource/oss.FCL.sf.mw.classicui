/*
* Copyright (c) 2002-2005 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Provides Psln Application class methods.
*
*/


// INCLUDE FILES
#include <eikstart.h>

#include "PslnApplication.h"
#include "PslnDocument.h"
#include "PslnConst.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CPslnApplication::CreateDocumentL
// -----------------------------------------------------------------------------
//
CApaDocument* CPslnApplication::CreateDocumentL()
    {
    return CPslnDocument::NewL( *this );
    }

// -----------------------------------------------------------------------------
// CPslnApplication::AppDllUid
// -----------------------------------------------------------------------------
//
TUid CPslnApplication::AppDllUid() const
    {
    return KUidPsln;
    }

// ========================== OTHER EXPORTED FUNCTIONS =========================

LOCAL_C CApaApplication* NewApplication()
    {
    return new CPslnApplication;
    }

GLDEF_C TInt E32Main()
    {
    return EikStart::RunApplication( NewApplication );
    }
    
//lint -esym(714,uid) Inhibit message in Psln.uid.cpp

//  End of File
