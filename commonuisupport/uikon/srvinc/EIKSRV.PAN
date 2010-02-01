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

#ifndef __EIKSRV_PAN__
#define __EIKSRV_PAN__

/**
@publishedPartner
@released
*/
#define __EIKON_SERVER _L("Eikon server")

/**
@publishedPartner
@released
*/
enum TEikServPanic
	{
	EEikServPanicNotifyBadDescriptor,
	EEikServPanicAlarmAlertServiceNotSupported,
	EEikServPanicNoTaskListDialog,
	EEikServPanicTaskNull,
	EEsPanicAlarmAlert,
	EEikServPanicAlarmAlertServerAlreadyConnected,
	EEikServEnvPanicNullAppUi,
	EEikServPanicNoSuchLabelInAlarm,
	EEikServPanicDriveIndexOutOfRange,
	EEikServPanicNotiferArrayNotNull,
	EEikServPanicChannelIndexOutOfRange,
	EEikServPanicNullObservedList,
	EEikServPanicQueueIndexOutOfRange,
	EEikServPanicNotifyAlertQueueEmpty,
	EEikSrvClientPanicInconsistentMessageParameters,
	};

/**
@publishedPartner
@released
*/
GLREF_C void Panic(TEikServPanic aPanic);

#endif	// __EIKSRV_PAN__
