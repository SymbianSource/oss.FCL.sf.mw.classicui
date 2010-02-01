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

#ifndef __EIKSRVS_H__
#define __EIKSRVS_H__

#include <eikappui.h>
#include <eikenv.h>
#include <eiksrv.pan>
#include <apgtask.h>
#include <eiksrv.h>

class CDictionaryFileStore;

/**
@publishedPartner
@released
*/
_LIT(EIKAPPUI_SERVER_NAME,"!EikAppUiServer");

/**
@publishedPartner
@released
*/
_LIT(EIKAPPUI_SERVER_THREAD_NAME,"EikAppUiServerThread");

/**
@publishedPartner
@released
*/
_LIT(EIKAPPUI_SERVER_SEMAPHORE,"EikAppUiServerStartSemaphore");

/**
WARNING: For internal use ONLY. Compatibility is not guaranteed in future releases.
*/
enum TEikAppUiRanges
	{
	EFirstUnrestrictedOpcodeInEikAppUi
	};
/**
WARNING: For internal use ONLY. Compatibility is not guaranteed in future releases.
*/
enum TEikUiOpCode
	{
	// No Capability requirement
	EEikAppUiFirst=EFirstUnrestrictedOpcodeInEikAppUi,
	EEikAppUiLaunchTaskList,
	EEikAppUiCycleTasks,
	EEikAppUiSetStatusPaneFlags,
	EEikAppUiSetStatusPaneLayout,
	EEikAppUiBlankScreen,
	EEikAppUiUnblankScreen,
	EEikAppUiResolveError,
	EEikAppUiExtension,
	EEikAppUiEnableTaskList,
	EEikAppUiGetDebugPreferences,	
	EEikAppUiResolveErrorWithTitleText,
	// End Marker no Capability
	EEikAppUiFirstUnusedOpcode,
	};


#endif	// __EIKSRVS_H__
