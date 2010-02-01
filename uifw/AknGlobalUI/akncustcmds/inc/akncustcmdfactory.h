/*
* Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description : Declaration of AknCustCmdFactory class.
*
*/
#ifndef AKNCUSTCMDFACTORY_H
#define AKNCUSTCMDFACTORY_H

#include <e32def.h>

class MSsmCustomCommand;

/**
* Creates custom command objects.
*/
class AknCustCmdFactory
    {
public:

	IMPORT_C static MSsmCustomCommand* CmdAknCapServerStartNewL();           // 1
    IMPORT_C static MSsmCustomCommand* CmdEnableAppsKeyAndGlobalNotesNewL(); // 2
    IMPORT_C static MSsmCustomCommand* CmdAknShutdownAppsNewL();             // 3
    };

#endif // AKNCUSTCMDFACTORY_H
