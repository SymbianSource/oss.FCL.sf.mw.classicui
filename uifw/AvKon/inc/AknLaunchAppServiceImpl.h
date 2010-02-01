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
* Description:  Server applications framework: LaunchApp service implementation
 *
 *
*/


#ifndef AKNLAUNCHAPPSERVICEIMPL_H
#define AKNLAUNCHAPPSERVICEIMPL_H

#include "AknLaunchAppService.h"
#include <f32file.h>

class CAiwGenericParamList;
class CBufStore;
class CStreamDictionary;
class CEikDocument;

const TUid KAknLaunchAppServiceUid = { 0x101F887A };

// ---------------------------------------------------------
//
// ---------------------------------------------------------
//
enum TAknLaunchAppServiceCmds
{
    EAknLaunchAppServiceCmdLaunchAppWithParams = RApaAppServiceBase::KServiceCmdBase
};

// ---------------------------------------------------------
//
// ---------------------------------------------------------
//
NONSHARABLE_CLASS(RAknLaunchAppService) : public RAknAppServiceBase
    {
public:
    void LaunchAppL(CAiwGenericParamList* aParam);

private:
    TUid ServiceUid() const;
    };


// ---------------------------------------------------------
//
// ---------------------------------------------------------
//
NONSHARABLE_CLASS(CAknLaunchAppServiceImpl) : public CAknLaunchAppService
    {
public:
    ~CAknLaunchAppServiceImpl();
    CAknLaunchAppServiceImpl();

    void ConstructL(
        const TUid& aAppUid, MAknServerAppExitObserver* aObserver, CAiwGenericParamList* aParam);

private:
    RAknLaunchAppService        iService;
    CApaServerAppExitMonitor*   iMonitor;
    };

// ---------------------------------------------------------
//
// ---------------------------------------------------------
//
NONSHARABLE_CLASS(CAknLaunchAppServiceSession) : public CAknAppServiceBase
{
public:
    CAknLaunchAppServiceSession();
    ~CAknLaunchAppServiceSession();

protected: // from CSession2
    void CreateL();
    void ServiceL(const RMessage2& aMessage);
    void ServiceError(const RMessage2& aMessage,TInt aError);

private:
    void LaunchAppWithParamsL(const RMessage2& aMessage);
    void ExternalizeParamsL(CAiwGenericParamList* aParamList);

private:

    /**
     * In memory store for parameter passing
     */
    CBufStore* iStore;

    /**
     * Store dictionary for parameter passing
     */
    CStreamDictionary* iDictionary;

    /**
     * Stream id for parameter passing
     */
    TStreamId iStreamId;

    CEikDocument* iDoc;

};

#endif

// End of file.
