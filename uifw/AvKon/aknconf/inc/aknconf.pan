/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  This file contains panic codes.
 *
*/


#ifndef __AKNCONF_PAN__
#define __AKNCONF_PAN__

/** aknconf application panic codes */
enum TAknConfPanics
    {
    EAknConfUi = 1
    // add further panics here
    };

inline void Panic(TAknConfPanics aReason)
    {
    _LIT(applicationName, "aknconf");
    User::Panic(applicationName, aReason);
    }

#endif // __AKNCONF_PAN__
