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
* Description:  Server applications framework: Null service implementation
 *
 *
*/


#ifndef AKNNULLSERVICEIMPL_H
#define AKNNULLSERVICEIMPL_H

#include "AknNullService.h"
#include <f32file.h>

const TUid KAknNullServiceUid = { 0x101F8827 };

// ---------------------------------------------------------
//
// ---------------------------------------------------------
//
NONSHARABLE_CLASS(RAknNullService) : public RAknAppServiceBase
    {
public:

private:
    TUid ServiceUid() const;
    };


// ---------------------------------------------------------
//
// ---------------------------------------------------------
//
NONSHARABLE_CLASS(CAknNullServiceImpl) : public CAknNullService
    {
public:
    ~CAknNullServiceImpl();
    CAknNullServiceImpl();

    void ConstructL(const TUid& aAppUid, MAknServerAppExitObserver* aObserver);

private:
    RAknNullService             iService;
    CApaServerAppExitMonitor*   iMonitor;
    };


#endif

// End of file.
