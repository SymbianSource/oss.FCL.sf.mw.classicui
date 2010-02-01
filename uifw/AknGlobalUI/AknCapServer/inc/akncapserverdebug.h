/*
* Copyright (c) 2002-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Debug macros for AknCapServer.
*
*/

#ifndef AKNCAPSERVERDEBUG_H
#define AKNCAPSERVERDEBUG_H

#include "akncapserverconfig.hrh"

#if defined(_DEBUG) && defined(AKNCAPSERVER_TRACES)
    #define LOGTEXT0(AAA)       RDebug::Print(_L(AAA))
    #define LOGTEXT1(AAA,BBB)   RDebug::Print(_L(AAA),BBB)
#else
    #define LOGTEXT0(AAA)                     
    #define LOGTEXT1(AAA,BBB)                
#endif 

#endif // AKNCAPSERVERDEBUG_H

// End of File
