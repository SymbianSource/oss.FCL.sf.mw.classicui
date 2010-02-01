/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Definitions for AknCompaSrv process
*
*/


#ifndef __AKNCOMPASRV_H__
#define __AKNCOMPASRV_H__

#include <e32base.h>

_LIT(KAknCompaSrvName,"AknCompaSrv");

const TUint KAknCompaSrvMajorVersionNumber=0;
const TUint KAknCompaSrvMinorVersionNumber=1;
const TUint KAknCompaSrvBuildVersionNumber=1;

const TUid KAknCompaSrvUid3={0x2000F864};

const TInt KAknCompaSrvMessageSlots = 2;
const TInt KServerRetryCount = 2;

// Function codes (opcodes) used in message passing between client and server
enum TAknCompaSrvRqst
    {
    ECompaSrvSimulateKeyEvent = 1,
    ECompaSrvDisaTransEffects = 2,
    ECompaSrvRestoreTransEffects = 3
    };

#endif // __AKNCOMPASRV_H__
