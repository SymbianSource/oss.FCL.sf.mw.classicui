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
* Description:  
*
*/

#include "AknMemoryCardDialogImpl.h"
#include <eikenv.h>
#include <eikspane.h>
#include <avkon.hrh>
#include <eikspane.h>
#include <aknappui.h>
#include <bautils.h>
#include <aknnotpi.rsg>

/**
 * TResourceFileLoader
 *
 * Load and destroy resource file for this DLL
 */
void TResourceFileLoader::DeleteResourceFile()
    {
    if (iResourceFileOffset > 0)
        {
        CCoeEnv::Static()->DeleteResourceFile(iResourceFileOffset);
        iResourceFileOffset = 0;
        }
    }

void TResourceFileLoader::AddResourceFileL()
    {
    if (iResourceFileOffset == 0)
        {
        CCoeEnv* environment = CCoeEnv::Static();
        TFileName resourceFile = _L("z:\\private\\10207218\\aknmemorycardui.rsc");
        BaflUtils::NearestLanguageFile(environment->FsSession(), resourceFile);
        iResourceFileOffset = environment->AddResourceFileL(resourceFile);
        }
    }

// End of file
