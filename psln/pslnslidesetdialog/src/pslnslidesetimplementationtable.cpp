/*
* Copyright (c) 2006-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  ECOM proxy table for PslnApplicationShellPlugin.
*
*/


#include <e32std.h>
#include <ecom/implementationproxy.h>

#include "pslnslidesetscreensaverdialog.h"
#include "pslnslidesetwallpaperdialog.h"

// CONSTANTS
// Define two entries - one for each type of dialog.
const TImplementationProxy KPslnApplicationShellPluginImplementationTable[] = 
    {
    IMPLEMENTATION_PROXY_ENTRY( 0x102823AE, CPslnWallpaperSlidesetDialog::NewL ),
    IMPLEMENTATION_PROXY_ENTRY( 0x102823AF, CPslnSlidesetScreensaverDialog::NewL )
    };

// ---------------------------------------------------------------------------
// ImplementationGroupProxy
// 
// Gate/factory function
// ---------------------------------------------------------------------------
//
EXPORT_C const TImplementationProxy* ImplementationGroupProxy( TInt& aTableCount )
    {
    aTableCount = sizeof( KPslnApplicationShellPluginImplementationTable ) 
        / sizeof( TImplementationProxy );
    return KPslnApplicationShellPluginImplementationTable;
    }


// ---------------------------------------------------------------------------
// E32Dll
// EKA1 entry point
//
// ---------------------------------------------------------------------------
//
#ifndef EKA2
GLDEF_C TInt E32Dll(TDllReason /*aReason*/)
    {
    return( KErrNone );
    }
#endif

