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


// This include should be the first #include in this file.
#include "aknkeys.h"
#include <coedef.h>

TBool AknKeys::IsNumberKey(const TKeyEvent& aKeyEvent, TEventCode aType)
    {
    if (aType!=EEventKey)
        {
        return EFalse;
        }
    
    switch (aKeyEvent.iCode) 
        {
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '0':
            {
            return ETrue;
            }
        default:
            {
            return EFalse;
            }
        }
    }

// End of File
