/*
* Copyright (c) 2004-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Notifier server app wrapper constant definitions.
*
*/

#ifndef __AKNNOTIFIERSERVERAPPWRAPPERDEF_H__
#define __AKNNOTIFIERSERVERAPPWRAPPERDEF_H__

#include <e32std.h>

const TUid KAknNotifierServiceUid = {0x101F8829};
const TUid KCommonNotifierAppSrvUid = {0x10281EF2};

enum TAdditionalCommandsForAknNfySrv
    {
    EAknNfySrvLoadLibrary = 42
    };
      
#endif // __AKNNOTIFIERSERVERAPPWRAPPERDEF_H__

// End of file
