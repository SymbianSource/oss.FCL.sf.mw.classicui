// Copyright (c) 2005-2009 Nokia Corporation and/or its subsidiary(-ies).
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

/**
 @file
 @internalComponent - Internal Symbian test code
*/

#ifndef __TREMOTECONTROL_H
#define __TREMOTECONTROL_H

#include <asaltdefs.h>

const TInt KRemoteQSize = 24;
const TInt KRemoteQMaxDataSize = 64;
_LIT(KRemoteQName, "RemoteControlQ");

enum TTestActions
	{
	ETestActionTaskKey = EASAltAlertServerResponsePauseSound + 1000,
	ETestActionHandleSwitch,
	ETestActionSetQuietPeriod,
	ETestActionDie,
	ETestActionHandleSwitchAndPause,
	};

/**
Utility class packing data into the message queue.
*/

class TRemoteMsg
	{
	public:
		TRemoteMsg(const TInt aValue) 
			{
			iPayload.iInt = aValue;
			}
		
		TRemoteMsg(const TUint8* aPtr, TInt aLength)
			{
			TPtr8 ptr(iPayload.iData, KRemoteQMaxDataSize);
			ptr.Copy(aPtr, aLength);
			}
		
		TRemoteMsg()
			{	
			}
			
		TInt Int() const
			{
			return iPayload.iInt;
			}
			
		TBool Bool() const
			{
			return TBool(iPayload.iInt);
			}
		
		const TUint8* Data() const
			{
			return iPayload.iData;
			}
	
	private:
		union TPayload 
			{
			TInt iInt;
			TUint8 iData[KRemoteQMaxDataSize];
			} iPayload;
	};

#endif // __TREMOTECONTROL_H
