/*
* Copyright (c) 2002 Nokia Corporation and/or its subsidiary(-ies).
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

// AKNANIMDLL.H
//
// Copyright (c) 1997-2000 Symbian Ltd.  All rights reserved.
//

// Avkon Anim Dll Factory


#if !defined(__AKNANIMDLL_H__)
#define __AKNANIMDLL_H__

// INCLUDES

#include <e32std.h>
#include <e32base.h>
#include <w32std.h>
#include <w32adll.h>

// CLASS DECLARATION

/**
* AVKON animation plugin.
*/
class CAknAnimDll : public CAnimDll
    {
    public: // Functions from base classes

        /**
        * From CAnimDll, creates new instance.
        * @param aType type of instance to be created.
        * @return new instance.
        */
        virtual CAnim* CreateInstanceL( TInt aType );

    };

/**
* Creates window server animation plug-in.
* @return animation plug-in.
*/
IMPORT_C CAnimDll* CreateCAnimDllL();

#endif

// End of File
