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
* Description:  Avkon Anim Dll Factory
 *
*/


// AKNANIMDLL.CPP
//
// Copyright (c) 1997-2000 Symbian Ltd.  All rights reserved.
//

#include "AknAnimDll.h"
#include "aknanimdllstd.h"
#include "AknAnimKeySound.h"

// CAknAnimDll

//----------------------------------------------------------------------------
// CAknAnimDll::CreateInstanceL
//----------------------------------------------------------------------------
//
CAnim* CAknAnimDll::CreateInstanceL( TInt aType )
    {
    switch ( aType )
        {
        case EAnimKeySound:
            return new ( ELeave ) CAknAnimKeySound();

        default:
            return NULL;
        }
    }

//----------------------------------------------------------------------------
// CreateCAnimDllL
//----------------------------------------------------------------------------
//
EXPORT_C CAnimDll* CreateCAnimDllL()
    {
    return new ( ELeave ) CAknAnimDll();
    }

// End of File
