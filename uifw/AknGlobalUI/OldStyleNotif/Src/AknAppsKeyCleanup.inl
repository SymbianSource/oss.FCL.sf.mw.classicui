/*
* Copyright (c) 2002-2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Cleanup function for releasing the apps key.
*
*/

#include <e32std.h>
#include <aknappui.h>
#include <AknNotiferAppServerApplication.h>

LOCAL_C void ReleaseAppsKey(TAny*)
    {
    ((CAknNotifierAppServerAppUi*)(iAvkonAppUi))->SuppressAppSwitching(EFalse);
    }

// End of file
