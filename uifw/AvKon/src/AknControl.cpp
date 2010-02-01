/*
* Copyright (c) 2005 Nokia Corporation and/or its subsidiary(-ies).
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


// INCLUDE FILES

#include <AknControl.h>
#include <AknTasHook.h> // for testability hooks

// CONSTANTS

// ================= MEMBER FUNCTIONS ==========================================

EXPORT_C CAknControl::CAknControl()
    {
    AKNTASHOOK_ADD( this, "CAknControl" );
    }

EXPORT_C CAknControl::~CAknControl()
    {
    AKNTASHOOK_REMOVE();
    }

EXPORT_C void* CAknControl::ExtensionInterface( TUid /*aInterface*/ )
    {
    return NULL;
    }

//  End of File  
