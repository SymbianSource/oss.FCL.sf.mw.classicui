/*
* Copyright (c) 1997-1999 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:
*
*/


#if !defined(__AKNEIKSRVC_H__)
#define __AKNEIKSRVC_H__

#include <eiksrvc.h>
#include <eiksrv.h>

class RAknEikAppUiSession : public REikAppUiSession
/**
@publishedPartner 
@released
*/
	{   
public:
	IMPORT_C RAknEikAppUiSession();
	// These functions are deprecated
	IMPORT_C TInt SetSgcParams(TInt aWgId, TBitFlags aAppFlags, TInt aSpLayout, TInt aSpFlags);
	IMPORT_C TInt BlockServerStatusPaneRedraws();
	IMPORT_C TInt RedrawServerStatusPane();
	IMPORT_C TInt PrepareForAppExit(TInt aWgId);
	IMPORT_C TInt SetSystemFaded(TBool aFade);
	IMPORT_C TInt IsSystemFaded(TBool& aFade) const;
    IMPORT_C TInt ShutdownApps(
    	const TUid aRequesterUID, 
    	const TInt aTimeoutInMicroseconds) const;
	// --------------------------------

	
public: // internal to avkon	
	TInt DoNotifierControllerCommand(TInt aCommand);

public: // internal for avkon server (SID protected)
	IMPORT_C TInt AllowNotifierAppServersToLoad();
	IMPORT_C TInt DoSynchWaitForAknCapServer();
	};

//**********************************
//global functions
//**********************************

/**
function to panic the server
@internalComponent
*/
GLREF_C void PanicServer(TEikAppUiServPanic aPanic);


#endif

