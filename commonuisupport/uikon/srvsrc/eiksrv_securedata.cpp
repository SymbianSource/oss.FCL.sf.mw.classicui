// Copyright (c) 1997-2009 Nokia Corporation and/or its subsidiary(-ies).
// All rights reserved.
// This component and the accompanying materials are made available
// under the terms of "Eclipse Public License v1.0"
// which accompanies this distribution, and is available
// at the URL "http://www.eclipse.org/legal/epl-v10.html".
//
// Initial Contributors:
// Nokia Corporation - initial contribution.
//
// Contributors:
//
// Description:
//

#include <eiksrv.h>
#include <eiksvdef.h>
#include <s32file.h>
#include <s32mem.h>
#include "CoeDataStorage.h"

//
// class CEikServSecureData
//
	
EXPORT_C void CEikServSecureData::GetInstalledFepNameL(TDes& aFepId)
/**
@deprecated
*/
	{
	CCoeDataStorage::GetL(*CCoeEnv::Static()).GetInstalledFepIdL(aFepId);
	}

EXPORT_C void CEikServSecureData::SetInstalledFepNameL(const TDesC& aFepId, TBool aRaiseFileError)
/**
@deprecated Use CCoeEnv::InstallFepL instead.
@capability WriteDeviceData
*/
	{
	// this function can't do anything other than leave with KErrPermissionDenied since it requires WriteDeviceData, but it's only to be called from the Eiksrvs process that doesn't have it!
	(void)aRaiseFileError;
	CCoeDataStorage::GetL(*CCoeEnv::Static()).SetInstalledFepIdL(aFepId);
	}

EXPORT_C void CEikServSecureData::OpenFepAttributesL()
/**
@deprecated
*/
	{
	// No longer needs to do anything
	}

EXPORT_C void CEikServSecureData::GetFepAttributeL(TUid aAttribUid, TDes8& aAttribData)
	{
	CCoeDataStorage::GetL(*CCoeEnv::Static()).GetFepAttributeL(aAttribUid, aAttribData);
	}

EXPORT_C void CEikServSecureData::SetFepAttributeL(TUid aAttribUid, const TDesC8& aAttribData)
/**
@deprecated
@capability WriteDeviceData
*/
	{
	// this function can't do anything other than leave with KErrPermissionDenied since it requires WriteDeviceData, but it's only to be called from the Eiksrvs process that doesn't have it!
	CCoeDataStorage::GetL(*CCoeEnv::Static()).SetFepAttributeL(aAttribUid, aAttribData);
	}

EXPORT_C void CEikServSecureData::CommitFepAttributesL()
/**
@deprecated
*/
	{
	// No longer needs to do anything
	}

EXPORT_C void CEikServSecureData::CloseFepAttributes()
	{
	// No longer needs to do anything
	}

EXPORT_C CBufBase* CEikServSecureData::GetBufferedSystemColorListL()
/**
@deprecated
*/
	{
	return CCoeDataStorage::GetL(*CCoeEnv::Static()).GetSystemColorListBufferL();
	}

EXPORT_C void CEikServSecureData::SetBufferedSystemColorListL(const TDesC8& aBuffer)
/**
@deprecated
@capability WriteDeviceData
*/
	{
	// this function can't do anything other than leave with KErrPermissionDenied since it requires WriteDeviceData, but it's only to be called from the Eiksrvs process that doesn't have it!
	CCoeDataStorage::GetL(*CCoeEnv::Static()).SetSystemColorListFromBufferL(aBuffer);
	}

