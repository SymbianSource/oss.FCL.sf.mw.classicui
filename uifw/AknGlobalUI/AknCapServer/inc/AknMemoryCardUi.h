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

#ifndef __AKNMEMORYCARDUI_H__
#define __AKNMEMORYCARDUI_H__

#include <e32std.h>
#include <e32base.h>
#include <eiknotapi.h>
#include <AknPanic.h>
#include <bautils.h>

class TResourceFileLoader
    {
    public:
        TResourceFileLoader() : iResourceFileOffset(0) {}
    public:
        void AddResourceFileL();
        void DeleteResourceFile();
    private:
        TInt iResourceFileOffset;
    };

#endif // __AKNMEMORYCARDUI_H__
