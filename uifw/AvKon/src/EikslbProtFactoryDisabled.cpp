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
*  Implementation of CSettingsProtListBoxItemDrawer factory that is used when
*  'settings protection' feature is disabled.
*  Returns NULL.
*
*/


// INCLUDES
#include "EikslbProtFactory.h"

// -----------------------------------------------------------------------------
// SettingsProtListBoxItemDrawerFactory::CreateSettingsProtListBoxItemDrawerL()
// -----------------------------------------------------------------------------

CSettingsProtListBoxItemDrawer* SettingsProtListBoxItemDrawerFactory::
    CreateSettingsProtListBoxItemDrawerL(
        MTextListBoxModel* /*aTextListBoxModel*/,
	    const CFont* /*aFont*/,
	    CSettingsListBoxData* /*aSettingsData*/,
	    CEikListBox* /*aListBox*/ )
    {
    return NULL;
    }

// End of File
