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
* Description:  Server applications framework: Open file service implementation
 *
 *
*/


#ifndef AKNOPENFILESERVICEIMPL_H
#define AKNOPENFILESERVICEIMPL_H

#include "AknOpenFileService.h"
#include <f32file.h>

class CAiwGenericParamList;
class CBufStore;
class CStreamDictionary;
class CEikDocument;

// dummy UID
const TUid KAknOpenFileServiceUid = { 0x101F8826 };

// ---------------------------------------------------------
//
// ---------------------------------------------------------
//
enum TAknOpenFileServiceCmds
    {
    EAknOpenFileServiceCmdOpenFilename = RApaAppServiceBase::KServiceCmdBase,
    EAknOpenFileServiceCmdOpenHandle,
    EAknOpenFileServiceCmdOpenFilenameWithParams,
    EAknOpenFileServiceCmdOpenHandleWithParams
    };


// ---------------------------------------------------------
//
// ---------------------------------------------------------
//
NONSHARABLE_CLASS(RAknOpenFileService) : public RAknAppServiceBase
    {
public:
    void OpenFileNameL(const TDesC& aFileName);
    void OpenFileNameL(const TDesC& aFileName, CAiwGenericParamList* aParam);
    void OpenHandleL(const RFile& aFile, CAiwGenericParamList* aParam);
private:
    TUid ServiceUid() const;
    };


// ---------------------------------------------------------
//
// ---------------------------------------------------------
//
NONSHARABLE_CLASS(CAknOpenFileServiceImpl) : public CAknOpenFileService
    {
public:
    ~CAknOpenFileServiceImpl();
    CAknOpenFileServiceImpl();

    void ConstructL(
        const TDesC& aFileName, MAknServerAppExitObserver* aObserver, CAiwGenericParamList* aParam);

    void ConstructL(
          const TUid& aAppUid, const RFile& aFileHandle, MAknServerAppExitObserver* aObserver, CAiwGenericParamList* aParam);
private:
    TUid FindAppForFileL(const TDesC& aFileName);

private:
    RAknOpenFileService         iService;
    CApaServerAppExitMonitor*   iMonitor;
    };


// ---------------------------------------------------------
//
// ---------------------------------------------------------
//
NONSHARABLE_CLASS(CAknOpenFileServiceSession) : public CAknAppServiceBase
    {
public:
    CAknOpenFileServiceSession();
    ~CAknOpenFileServiceSession();

protected: // from CSession2
    void CreateL();
    void ServiceL(const RMessage2& aMessage);
    void ServiceError(const RMessage2& aMessage,TInt aError);

private:
    void OpenFileNameL(const RMessage2& aMessage);
    void OpenFileNameWithParamsL(const RMessage2& aMessage);
    void OpenHandleWithParamsL(const RMessage2& aMessage);
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
