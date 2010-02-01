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
* Description:  Server applications framework: Open file service client API
 *
 *
*/


#ifndef AKNOPENFILESERVICE_H
#define AKNOPENFILESERVICE_H

#include <AknServerApp.h>

class CAiwGenericParamList;

// ---------------------------------------------------------
//
// ---------------------------------------------------------
//
class CAknOpenFileService : public CBase
    {
public:
    IMPORT_C static CAknOpenFileService* NewL(
        const TDesC& aFileName, MAknServerAppExitObserver* aObserver, CAiwGenericParamList* aParam);

    static CAknOpenFileService* NewLC(
        const TDesC& aFileName, MAknServerAppExitObserver* aObserver, CAiwGenericParamList* aParam);

    IMPORT_C static CAknOpenFileService* NewL(
        const TUid& aAppUid, const RFile& aFileHandle, MAknServerAppExitObserver* aObserver, CAiwGenericParamList* aParam);
        
    static CAknOpenFileService* NewLC(
        const TUid& aAppUid, const RFile& aFileHandle, MAknServerAppExitObserver* aObserver, CAiwGenericParamList* aParam);
    };

#endif

// End of file.
