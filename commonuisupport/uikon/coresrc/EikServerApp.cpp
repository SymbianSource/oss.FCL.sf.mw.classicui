// Copyright (c) 2004-2009 Nokia Corporation and/or its subsidiary(-ies).
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

#include "EikServerApp.h"
#include <apgcli.h>
#include <apacmdln.h>
#include <e32math.h>
#include <w32std.h>
#include <eikenv.h>
#include <eikappui.h>
//
// EikServerAppUtils
//

NONSHARABLE_CLASS(EikServerAppUtils)
	{
public: // internal
	static TUint GenerateServerDifferentiatorAndName(TName& aServerName, TUid aServerUid);
	static void ServerName(TName& aServerName, TUid aServerUid, TUint aServerDifferentiator);
	};


void EikServerAppUtils::ServerName(TName& aServerName, TUid aAppServerUid, TUint aServerDifferentiator)
	{
	_LIT(KServerNameFormat, "%08x_%08x_AppServer");
	aServerName.Format(KServerNameFormat, aServerDifferentiator, aAppServerUid);
	}
	
TUint EikServerAppUtils::GenerateServerDifferentiatorAndName(TName& aServerName, TUid aAppServerUid)
	{
	TUint r;
	FOREVER
		{
		r = Math::Random();
		if (r==0)
			continue;
		ServerName(aServerName, aAppServerUid, r);
		TFindServer find(aServerName);
		TFullName fullName;
		if (find.Next(fullName) == KErrNone)
			continue;
		break;
		}		
	return r;
	}



/** Launch a new instance of a server app and connect to
its server.
@param aAppUid The UID of the server application to connect to. */
EXPORT_C void REikAppServiceBase::ConnectNewAppL(TUid aAppUid)
	{
	TUint differentiator = StartServerL(aAppUid, NULL);
	TName serverName;
	EikServerAppUtils::ServerName(serverName, aAppUid, differentiator);
	ConnectExistingByNameL(serverName);
	}

/** Launch a new instance of a server app and connect to
its server.
@param aAppUid The UID of the server application to connect to. 
@param aSecurityPolicy The TSecurityPolicy which should be matched with the TSecurityPolicy of the app to be connected.

@see TSecurityPolicy*/
EXPORT_C void REikAppServiceBase::ConnectNewAppL(TUid aAppUid, const TSecurityPolicy& aSecurityPolicy)
	{
	TUint differentiator = StartServerL(aAppUid, NULL);
	TName serverName;
	EikServerAppUtils::ServerName(serverName, aAppUid, differentiator);
	ConnectExistingByNameL(serverName, aSecurityPolicy);
	}

/** Connect a new child app.  Use for window chaining.
@param aAppUid The UID of the server application to connect to.
@param aParentWindowGroup The parent window group */
EXPORT_C void REikAppServiceBase::ConnectNewChildAppL(TUid aAppUid, RWindowGroup& aParentWindowGroup)
	{
	TUint differentiator = StartServerL(aAppUid, &aParentWindowGroup);
	TName serverName;
	EikServerAppUtils::ServerName(serverName, aAppUid, differentiator);
	ConnectExistingByNameL(serverName);
	}

/** Connect a new child app.  Use for window chaining.
@param aAppUid The UID of the server application to connect to.
@param aWindowGroupID The window group ID 
@param aSecurityPolicy The TSecurityPolicy which should be matched with the TSecurityPolicy of the app to be connected.

@see TSecurityPolicy*/
EXPORT_C void REikAppServiceBase::ConnectNewChildAppL(TUid aAppUid, RWindowGroup& aParentWindowGroup, const TSecurityPolicy& aSecurityPolicy)
	{
	TUint differentiator = StartServerL(aAppUid, &aParentWindowGroup);
	TName serverName;
	EikServerAppUtils::ServerName(serverName, aAppUid, differentiator);
	ConnectExistingByNameL(serverName, aSecurityPolicy);
	}
	
/** Session close function. */
EXPORT_C void REikAppServiceBase::Close()
	{
	RApaAppServiceBase::Close();
	}


/**
@param aAppUid UID of server application.
@param aParentWindowGroup May be null.
@return A differentiator - an auto-generated number used to identify the server.
@internalComponent
*/
TUint REikAppServiceBase::StartServerL(TUid aAppUid, RWindowGroup* aParentWindowGroup)
	{
	TName notUsed;
	const TUint differentiator = EikServerAppUtils::GenerateServerDifferentiatorAndName(notUsed, aAppUid);
	TRequestStatus requestStatusForRendezvous;
	TApaCommand launchCommand;
	LaunchAppL(aAppUid, differentiator, aParentWindowGroup, requestStatusForRendezvous, launchCommand);

	if (launchCommand != EApaCommandBackground && launchCommand != EApaCommandBackgroundAndWithoutViews)
		{
		// deactivate current app's view so that the deactivation does not block
	    // server app startup.
	 	CEikonEnv* eikEnv = CEikonEnv::Static();
	 	
	 	if (eikEnv)
	  		{
	  		CEikAppUi* appUi = eikEnv->EikAppUi();
	  		if (appUi)
	   			{
	   			appUi->DeactivateActiveViewL();
	   			}
	  		}
		}

	User::WaitForRequest(requestStatusForRendezvous);
	User::LeaveIfError(requestStatusForRendezvous.Int());
	return differentiator;
	}


/**
@param aAppUid UID of application application to be launched
@param aSeverDifferentiator Identifier for server instantiation
@param aParentWindowGroup May be null
@param aRequestStatusForRendezvous Asynchronous request status - passed through
@param aLaunchCommand Output parameter  @see TApaCommand
@internalComponent
*/
void REikAppServiceBase::LaunchAppL(TUid aAppUid, TUint aServerDifferentiator, RWindowGroup* aParentWindowGroup, TRequestStatus& aRequestStatusForRendezvous, TApaCommand& aLaunchCommand)
	{
	RApaLsSession apa;
	User::LeaveIfError(apa.Connect());
	CleanupClosePushL(apa);
	
	TApaAppInfo info;
	User::LeaveIfError(apa.GetAppInfo(info, aAppUid));

	CApaCommandLine* cmdLine = CApaCommandLine::NewLC();
	cmdLine->SetExecutableNameL(info.iFullName);
	cmdLine->SetServerRequiredL(aServerDifferentiator);

	TApaAppCapabilityBuf caps;
	User::LeaveIfError(apa.GetAppCapability(caps, aAppUid));
	TBool launchInBackground = caps().iLaunchInBackground;
	aLaunchCommand = launchInBackground ? EApaCommandBackground : EApaCommandRun;
	cmdLine->SetCommandL(aLaunchCommand);

	// server app's background launching takes precedence over
	// client's wish for a chained window group. Using the two
	// together would throw the client into the background too.
	if (aParentWindowGroup && !launchInBackground)
		{
		const TInt parentWindowGroupID = aParentWindowGroup->Identifier();
		if (parentWindowGroupID)
			{
			cmdLine->SetParentWindowGroupID(parentWindowGroupID);
			aParentWindowGroup->AllowProcessToCreateChildWindowGroups(aAppUid);
			}
		}

	TThreadId notUsed;
	User::LeaveIfError(apa.StartApp(*cmdLine, notUsed, &aRequestStatusForRendezvous));

	CleanupStack::PopAndDestroy(2, &apa);	// cmdLine and apa
	}

/** Extension mechanism - for internal BC proofing. */
EXPORT_C void REikAppServiceBase::ExtensionInterface(TUid /*aInterfaceId*/, TAny*& /*aImplementaion*/)
	{
	}


/**
Constructs a uniquely named instantiation of a server
@param aServerDifferentiator Auto generated identifier
@param aAppUid UID of server application.
@internalTechnology
*/
void CEikAppServer::ConstructUniqueL(TUint aServerDifferentiator, TUid aAppUid)
	{
	TName serverName;
	EikServerAppUtils::ServerName(serverName, aAppUid, aServerDifferentiator);
	ConstructL(serverName);
	}

/** CEikAppServer's override of CApaAppServer::ConstructL().
Classes which further derive from this one must base-call.
@param aFixedServerName - the name that this server will use. */
EXPORT_C void CEikAppServer::ConstructL(const TDesC& aFixedServerName)
	{
	CApaAppServer::ConstructL(aFixedServerName);
	}

/** CEikAppServer's override of CApaAppServer::CreateServiceL().
This allows uikon to create standard services.
Classes which further derive from this one must base-call.
@param aServiceType The UID of the service that the client wants to connect to.
@return an object derived from CApaAppServiceBase that can handle the
service type requested by the client. */
EXPORT_C CApaAppServiceBase* CEikAppServer::CreateServiceL(TUid aServiceType) const 
	{
	return CApaAppServer::CreateServiceL(aServiceType);
	}

/** Function to allow security checks on the client before they
connect to a service.
Server apps should override this method if they want to restict
connections to some services to clients with particular capabilities.
@param aServiceType The UID of the service that the client wants to connect to.
@param	aMsg The message to check.
@param	aAction A reference to the action to take if the security check
		fails. This is either a value from TFailureAction or a negative
		value which has meaning to the CustomFailureActionL() method of
		a derived class.
		The policy server framework gives this value a default of
		EFailClient.  If a derived implementation wishes a
		different value, then it should change this.
@param 	aMissing A reference to the list of security attributes missing
		from the checked process.  The policy server initialises this
		object to zero (that is a sid of 0, a vid of 0, and no capabilities).
		If derived implementations wish to take advantage of a list of
		missing attributes in their implementation of CustomFailureActionL(),
		then they should set those missing attributes here in
		CustomSecurityCheckL().
@return A value from CPolicyServer::TCustomResult.
@see CPolicyServer */
EXPORT_C CPolicyServer::TCustomResult CEikAppServer::CreateServiceSecurityCheckL(TUid aServiceType, const RMessage2& aMsg, TInt& aAction, TSecurityInfo& aMissing)
	{
	return CApaAppServer::CreateServiceSecurityCheckL(aServiceType, aMsg, aAction, aMissing);
	}

/** Extension mechanism - for internal BC proofing. */
EXPORT_C void CEikAppServer::ExtensionInterface(TUid /*aInterfaceId*/, TAny*& /*aImplementaion*/)
	{
	}

