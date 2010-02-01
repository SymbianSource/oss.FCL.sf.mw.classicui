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
* Description : Implementation of AknCustCmdFactory class.
*
*/

#include "akncustcmdfactory.h"
#include "akncapserverstart.h"
#include "aknenableappskeyandglobalnotes.h"
#include "aknshutdownapps.h"

// ======== MEMBER FUNCTIONS ========

EXPORT_C MSsmCustomCommand* AknCustCmdFactory::CmdAknCapServerStartNewL()
	{
	return CAknCapServerStart::NewL();
	}


EXPORT_C MSsmCustomCommand*
AknCustCmdFactory::CmdEnableAppsKeyAndGlobalNotesNewL()
	{
	return CAknEnableAppsKeyAndGlobalNotes::NewL();
	}


EXPORT_C MSsmCustomCommand* AknCustCmdFactory::CmdAknShutdownAppsNewL()
	{
	return CAknShutdownApps::NewL();
	}
