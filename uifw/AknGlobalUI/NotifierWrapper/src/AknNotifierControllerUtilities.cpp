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
* Description:  
*
*/

#include <eikenv.h>
#include <AknDlgShut.h>
#include <aknglobalpopupprioritycontroller.h>

#include "AknNotifierControllerUtilities.h"

EXPORT_C void CAknNotifierControllerUtility::DoAllowNotifications()
    {
    AknGlobalPopupPriorityController::SetRootWinOrdinalPosition(iMyOrdinalPosition);
    AknGlobalPopupPriorityController::AllowGlobalPopups(ETrue);
    }

EXPORT_C void CAknNotifierControllerUtility::DoStopNotifications()
    {
    AknGlobalPopupPriorityController::AllowGlobalPopups(EFalse);
    }

EXPORT_C void CAknNotifierControllerUtility::DoCancelAllNotificatonsL() 
    {
    AknDialogShutter::ShutDialogsL(*CEikonEnv::Static());
    }

void CAknNotifierControllerUtility::DoNotifierContollerCommandL(TNotifierControllerCommand aCommand)
    {
    switch (aCommand)
        {
        case EDoAllow:
            DoAllowNotifications();
            break;
        case EDoStop:
            DoStopNotifications();
            break;
        case DoCancelAll:
            DoCancelAllNotificatonsL();
            break;
        default:
            User::Leave(KErrNotSupported);
        }
    }

// End of file
