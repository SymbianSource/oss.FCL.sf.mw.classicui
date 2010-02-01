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
* Description:  Server applications framework: Null service client API
 *
 *
*/


#ifndef AKNNULLSERVICE_H
#define AKNNULLSERVICE_H

#include <AknServerApp.h>

// ---------------------------------------------------------
//
// ---------------------------------------------------------
//
class CAknNullService : public CBase
    {
public:
    IMPORT_C static CAknNullService* NewL(const TUid& aAppUid, MAknServerAppExitObserver* aObserver);

    static CAknNullService* NewLC(const TUid& aAppUid, MAknServerAppExitObserver* aObserver);
    };

#endif

// End of file.
