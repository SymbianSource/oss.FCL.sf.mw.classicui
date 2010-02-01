/*
* Copyright (c) 2005 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  ECOM proxy table for PslnGSPlugin.
*
*/


// User includes
#include "PslnGSPlugin.h"

// System includes
#include <e32std.h>
#include <ecom/implementationproxy.h>


// Constants
const TImplementationProxy KPslnGSPluginImplementationTable[] =
    {
    IMPLEMENTATION_PROXY_ENTRY( 0x102818ED,  CPslnGSPlugin::NewL )
    };


// ---------------------------------------------------------------------------
// ImplementationGroupProxy
// Gate/factory function
//
// ---------------------------------------------------------------------------
//
EXPORT_C const TImplementationProxy* ImplementationGroupProxy(
    TInt& aTableCount )
    {
    aTableCount = sizeof( KPslnGSPluginImplementationTable )
        / sizeof( TImplementationProxy );
    return KPslnGSPluginImplementationTable;
    }


// ---------------------------------------------------------------------------
// E32Dll
// EKA1 entry point
//
// ---------------------------------------------------------------------------
//
#ifndef EKA2
GLDEF_C TInt E32Dll( TDllReason /*aReason*/ )
    {
    return( KErrNone );
    }
#endif // EKA2
// End of File
