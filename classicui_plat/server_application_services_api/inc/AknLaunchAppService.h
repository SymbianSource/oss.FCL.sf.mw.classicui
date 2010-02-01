/*
* Copyright (c) 2004 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Server applications framework: LaunchApp service client API
 *
 *
*/


#ifndef AKNLAUNCHAPPSERVICE_H
#define AKNLAUNCHAPPSERVICE_H

#include <AknServerApp.h>

class CAiwGenericParamList;

// ---------------------------------------------------------
//
// ---------------------------------------------------------
//
class CAknLaunchAppService : public CBase
    {
public:
    IMPORT_C static CAknLaunchAppService* NewL(
        const TUid& aAppUid, MAknServerAppExitObserver* aObserver, CAiwGenericParamList* aParam);

    static CAknLaunchAppService* NewLC(
        const TUid& aAppUid, MAknServerAppExitObserver* aObserver, CAiwGenericParamList* aParam);
    };

#endif

// End of file.
