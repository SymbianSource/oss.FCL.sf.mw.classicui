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
* Description:  Wrapper dll for wallpaperutils.dll.
*
*/

#include <AknsWallpaperUtils.h>

#include "pslnwallpaperutilsloader.h"
#include "PslnConst.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// C++ default constructor can NOT contain any code, that might leave.
// ---------------------------------------------------------------------------
//
CPslnWallpaperUtilsLoader::CPslnWallpaperUtilsLoader()
    {
    }

// ---------------------------------------------------------------------------
// Two-phased constructor.
// ---------------------------------------------------------------------------
//
CPslnWallpaperUtilsLoader* CPslnWallpaperUtilsLoader::NewL()
    {
    CPslnWallpaperUtilsLoader* self = 
        new( ELeave ) CPslnWallpaperUtilsLoader();

    return self;
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CPslnWallpaperUtilsLoader::~CPslnWallpaperUtilsLoader()
    {
    }

// ---------------------------------------------------------------------------
// Set idle wallpaper.
// ---------------------------------------------------------------------------
//
TInt CPslnWallpaperUtilsLoader::SetIdleWallpaper( 
    const TDesC& aFilename, 
    CCoeEnv* aCoeEnv, 
    TInt aWaitNoteTextResourceID, 
    TInt aWaitNoteResourceID )
    {
    return AknsWallpaperUtils::SetIdleWallpaper(
            aFilename, 
            aCoeEnv, 
            aWaitNoteTextResourceID, 
            aWaitNoteResourceID );
    }

//----------------------------------------------------------------------------   
// Launcher gate function
//----------------------------------------------------------------------------
EXPORT_C TAny* GateFunction()
    {
    CPslnWallpaperUtilsLoader* launcher = NULL;
    TRAPD( err, launcher = CPslnWallpaperUtilsLoader::NewL() );
    if( err != KErrNone )
        {
        return NULL;
        }

    return launcher;
    }

//  End of File  
