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
* Description:  DomInputMethods test app
*
*/


// system includes
#include <ecom/implementationproxy.h>

// user includes
#include "bctestdomrecognizer.h"
#include "bctestdompticore.h"

// Map the interface UIDs
const TImplementationProxy ImplementationTable[] = 
    {
    IMPLEMENTATION_PROXY_ENTRY( 0xa00040a9, CBCTestDomHwrRecognizer::NewL ),
    IMPLEMENTATION_PROXY_ENTRY( 0xa00040ad, CBCTestDomPtiCore::NewL )
    };
 
// Exported proxy for instantiation method resolution
EXPORT_C const TImplementationProxy* ImplementationGroupProxy(TInt& aTableCount)
    {
    aTableCount = sizeof( ImplementationTable ) / sizeof( TImplementationProxy );
    return ImplementationTable;
    }
