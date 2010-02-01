/*
* Copyright (c) 1997-1999 Nokia Corporation and/or its subsidiary(-ies).
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


#include <uiklaf/private/lafshut.h>

// ---------------------------------------------------------
// Stub versions of LafShutdown exports.
// Implemented versions are in OODMonitor.
// ---------------------------------------------------------
//
EXPORT_C CLafShutdownManagerBase* LafShutdown::CreateShutdownManager(MShutdownEventObserver& /*aObserver*/)
    { // static
    return NULL;
    }

EXPORT_C MSaveObserver::TSaveType LafShutdown::SaveFromViewSwitch()
    { // static
    return MSaveObserver::ESaveNone;
    }
    
EXPORT_C MSaveObserver::TSaveType LafShutdown::SaveFromAppSwitch()
    { // static
    return MSaveObserver::ESaveNone;
    }

// End of file.
