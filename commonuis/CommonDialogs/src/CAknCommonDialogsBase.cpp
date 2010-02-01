/*
* Copyright (c) 2002-2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  ?Description
*
*/


// INCLUDES
#include "CAknCommonDialogsBase.h"

#include <coemain.h>

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CAknCommonDialogsBase::CAknCommonDialogsBase
//
//
// -----------------------------------------------------------------------------
//
CAknCommonDialogsBase::CAknCommonDialogsBase()
    :   iCoeEnv( CCoeEnv::Static() ), // Cache pointer to CCoeEnv
        iResourceLoader( *iCoeEnv ) // Construct iResourceLoader
    {
    }

// -----------------------------------------------------------------------------
// CAknCommonDialogsBase::BaseConstructL
//
// -----------------------------------------------------------------------------
//
void CAknCommonDialogsBase::BaseConstructL()
    {
    // Resource file of Common File Dialogs
    _LIT( KCFDResourceFileName, "z:\\resource\\commondialogs.rsc" );

    TFileName resourceFileName( KCFDResourceFileName );
    iResourceLoader.OpenL( resourceFileName );
    }

// Destructor
CAknCommonDialogsBase::~CAknCommonDialogsBase()
    {
    iResourceLoader.Close();
    }

//  End of File
