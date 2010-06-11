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


#include <e32std.h>
#include <e32math.h>
#include <centralrepository.h>
#include "CoeDataStorage.h"
#include <eiksrvc.h>
#include <eiksvdef.h>
#include <s32mem.h>
#include <eikdebug.h>
#include "eiksrvsconsts.h"
#include "../coresrc/eikdebugprefs.h"

const TUint KDefaultBufSize = 0x8;
const TUid KServerUid3={0x10003A4A};
#ifdef __WINS__
_LIT(KEikSrvName,"eiksrvs.exe");
#else // ! __WINS__
_LIT(KEikSrvName,"z:\\system\\programs\\eiksrvs.exe");
#endif

GLDEF_C void PanicServer(TEikAppUiServPanic aPanic)
	{
	_LIT(KPanicCat,"EIKON-SERVER");
	User::Panic(KPanicCat,aPanic);
	}

// REikAppUiSession::CExtension

class REikAppUiSession::CExtension : public CBase
	{
	friend class REikAppUiSession;
private: // but public to REikAppUiSession
	CCoeDataStorage* iDataStorage;
	};

// REikAppUiSession

/**
Default Constructor
@publishedPartner
*/
EXPORT_C REikAppUiSession::REikAppUiSession()
: iExtension(NULL)
	{
	}

/**
Connect to the server attempting to start it if required
@return System error code.
*/
EXPORT_C TInt REikAppUiSession::Connect()
	{
	Close();
	TInt err=KErrNone;
	TInt retry=KNumConnectRetries;
	FOREVER
		{
		err=CreateSession(EIKAPPUI_SERVER_NAME,Version());
		if ((--retry>0) && ((err==KErrNotFound) || (err==KErrServerTerminated)))
			{
			TRAP(err,StartServerL());
			if ((err!=KErrNone) && (err!=KErrAlreadyExists))
				{
				break;
				}
			}
		else
			{
			break;
			}
		}
	if (err==KErrNone)
		{
		
		TRAP(err,
				iExtension=new(ELeave) CExtension;
				iExtension->iDataStorage=CCoeDataStorage::NewL());
		}
	if (err!=KErrNone)
		{
		Close();
		}
	return err;
	}


/**
Closes connection with server.
@publishedPartner
*/
EXPORT_C void REikAppUiSession::Close()
	{
	RSessionBase::Close();
	if (iExtension!=NULL)
		{
		delete iExtension->iDataStorage;
		delete iExtension;
		iExtension=NULL;
		}
	}

/**
Creates and starts server.  Waits for success or failure.
Doesn't leave with the 'exit reason' if the server panicked as this
is the panic 'reason' and may be '0' which cannot be distinguished
from KErrNone.
@internalComponent
*/
void REikAppUiSession::StartServerL()
	{
	const TUidType serverUid(KNullUid,KNullUid,KServerUid3);

	RProcess server;
	User::LeaveIfError(server.Create(KEikSrvName,KNullDesC,serverUid));
	TRequestStatus stat;
	server.Rendezvous(stat);
	if (stat!=KRequestPending)
		server.Kill(0);         // abort startup
	else
		server.Resume();        // logon OK - start the server
	User::WaitForRequest(stat);             // wait for start or death
	// we can't use the 'exit reason' if the server panicked as this
	// is the panic 'reason' and may be '0' which cannot be distinguished
	// from KErrNone
	TInt r=(server.ExitType()==EExitPanic) ? KErrGeneral : stat.Int();
	server.Close();
	User::LeaveIfError(r);
	}

/**
@return version number.
@publishedPartner
*/
EXPORT_C TVersion REikAppUiSession::Version(void) const
	{
	return(TVersion(1,0,0));
	}

/**
Asks server to launch the Task List
@publishedPartner
*/
EXPORT_C void REikAppUiSession::LaunchTaskList() const
	{
#if defined(_DEBUG)
	const TInt error=
#endif
	SendReceive(EEikAppUiLaunchTaskList,TIpcArgs());
	__ASSERT_DEBUG(error==KErrNone,User::Invariant());
	}

/**
Asks the server to cycle through the tasks (in the list) by one in the specified direction
@param aDirection EForwards or EBackwards
@publishedPartner
*/
EXPORT_C void REikAppUiSession::CycleTasks(TTaskCycleDirection aDirection) const
	{
#if defined(_DEBUG)
	const TInt error=
#endif
	SendReceive(EEikAppUiCycleTasks,TIpcArgs(aDirection));
	__ASSERT_DEBUG(error==KErrNone,User::Invariant());
	}

/**
Asks the server to set status pane flags as specified
@param aFlags Status pane dependant flags.
@publishedPartner
*/
EXPORT_C TInt REikAppUiSession::SetStatusPaneFlags(TInt aFlags) const
	{
	return SendReceive(EEikAppUiSetStatusPaneFlags,TIpcArgs(aFlags));
	}

/**
Sends status pane resource layout ID to server
@param aLayoutResId  Resource ID of status pane layout resource
@publishedPartner
*/
EXPORT_C TInt REikAppUiSession::SetStatusPaneLayout(TInt aLayoutResId) const
	{
	return SendReceive(EEikAppUiSetStatusPaneLayout,TIpcArgs(aLayoutResId));
	}

/**
Sends blank screen message to server
@publishedPartner
*/
EXPORT_C TInt REikAppUiSession::BlankScreen() const
	{
	return SendReceive(EEikAppUiBlankScreen,TIpcArgs());
	}

/**
Sends unblank screen message to server
@publishedPartner
*/
EXPORT_C TInt REikAppUiSession::UnblankScreen() const
	{
	return SendReceive(EEikAppUiUnblankScreen,TIpcArgs());
	}

/**
Retrieves error text for error code (if code is valid)
@param aText Output parameter - error message
@param aError Standard error code
@param aAppUid Application UID
@return EErrorNumValid or EErrorNumInvalid
@see CEikonEnv::TErrorValidity
@publishedPartner
*/
EXPORT_C CEikonEnv::TErrorValidity REikAppUiSession::ResolveError(TDes& aText,TInt aError,TUid aAppUid) const
	{
	return STATIC_CAST(CEikonEnv::TErrorValidity, SendReceive(EEikAppUiResolveError,TIpcArgs(&aText,aError,aAppUid.iUid)));
	}

/**
Retrieves error text, title text, error resource ID and resource flags for the given error code (if code is valid)
@param aErrorText Output parameter - Error Text.
@param aError Standard Error Code
@param aFlags Output parameter - Error Resource Flag.
@param aTextId Output parameter - Error Text Resource Id.
@param aTitleText Output parameter - Error Title Text.

@return EErrorNumValid or EErrorNumInvalid
@see CEikonEnv::TErrorValidity
@released
*/
EXPORT_C CEikonEnv::TErrorValidity REikAppUiSession::ResolveErrorWithTitleL(TDes& aErrorText, TInt aError, TInt& aTextId, TUint& aFlags, TDes& aTitleText, TBool aIsMemoryAllocatedByErrResolver) const
	{
	TErrorFlagAndId errInfo;
	TPckg<TErrorFlagAndId> package(errInfo);
	errInfo.iIsMemoryAllocatedByErrResolver = aIsMemoryAllocatedByErrResolver;
	errInfo.iTextId = 0;
	errInfo.iFlags = 0;
	
	TInt errValidity = User::LeaveIfError(SendReceive(EEikAppUiResolveErrorWithTitleText, TIpcArgs(&aErrorText, aError, &package, &aTitleText)));
	
	aTextId = errInfo.iTextId;
	aFlags = errInfo.iFlags;
	return STATIC_CAST(CEikonEnv::TErrorValidity, errValidity);
	}

/**
Retrieves pointer descriptor of specified extension.
@param aExtensionUid 
@publishedPartner
@see MEikServAppUiSessionHandler::Extension(TUid aExtensionUid,const TDesC8& aBuffer,RMessagePtr2 aMessage)
*/
EXPORT_C void REikAppUiSession::Extension(TUid aExtensionUid,const TDesC8& aBuffer,TRequestStatus& aRequestStatus) const
	{
	SendReceive(EEikAppUiExtension, TIpcArgs(aExtensionUid.iUid,&aBuffer), aRequestStatus);
	}

/** Gets the identifier of the currently installed FEP. 

@param aFepId On return, contains the identifier of the FEP currently installed.

@return KErrNone if successful, otherwise another of the system-wide error codes.
@deprecated
*/
EXPORT_C TInt REikAppUiSession::GetInstalledFepName(TDes& aFepId) const
	{
	TRAPD(error, iExtension->iDataStorage->GetInstalledFepIdL(aFepId));
	return error;
	}

/** Sets the identifier of the installed FEP.

@param aFepId The identifier of the installed FEP.
@param aRaiseFileError No longer used.

@capability WriteDeviceData
@return KErrNone if successful, otherwise another of the system-wide error codes.
@deprecated Use CCoeEnv::InstallFepL instead.
*/
EXPORT_C TInt REikAppUiSession::SetInstalledFepName(const TDesC& aFepId, TBool aRaiseFileError) const
	{
	(void)aRaiseFileError;
	TRAPD(error, iExtension->iDataStorage->SetInstalledFepIdL(aFepId));
	return error;
	}
	
/** Gets the system colour list, which is a palette of standard colours used by the system.

The function returns NULL if no such data exists.

@return Pointer to the system colour list. 
*/
EXPORT_C CColorList* REikAppUiSession::GetSystemColorsL() const
	{
	return iExtension->iDataStorage->GetSystemColorListL();	
	}

/** Sets the system colour list with the list specified.

If no system colour list exists, one is created.

@param aColorList The new colour list.
*/
EXPORT_C void REikAppUiSession::SetSystemColorsL(const CColorList& aColorList) const
	{
	iExtension->iDataStorage->SetSystemColorListL(aColorList);
	}

/** No longer needs to do anything.

@return KErrNone.
*/
EXPORT_C TInt REikAppUiSession::OpenFepAttributes() const
	{
	return KErrNone;
	}

/** Gets the FEP's attributes for the given UID.

@param aAttribUid The attribute UID for which the attribute data has to be queried for.
@param aAttribData On return contains the attribute data.

@return KErrNone if successful, otherwise another of the system-wide error codes.
*/
EXPORT_C TInt REikAppUiSession::GetFepAttribute(TUid aAttribUid, TDes8& aAttribData) const
	{
	TRAPD(error, iExtension->iDataStorage->GetFepAttributeL(aAttribUid, aAttribData));
	return error;
	}

/** Sets the attribute data for the specified UID.

If no attribute is associated with the specified UID, then a new attribute is created.
If an attribute is currently associated with the specified UID, then this existing
attribute is replaced with the new attribute.
  
@param aAttribUid The attribute UID of the new attribute data.
@param aAttribData Attribute data to add.

@return KErrNone if successful, otherwise another of the system-wide error codes.
*/
EXPORT_C TInt REikAppUiSession::SetFepAttribute(TUid aAttribUid, const TDesC8& aAttribData) const
	{
	TRAPD(error, iExtension->iDataStorage->SetFepAttributeL(aAttribUid, aAttribData));
	return error;
	}

/** No longer needs to do anything.
@return KErrNone.
*/
EXPORT_C TInt REikAppUiSession::CommitFepAttributes() const
	{
	return KErrNone;
	}

/** No longer needs to do anything.
*/
EXPORT_C void REikAppUiSession::CloseFepAttributes() const
	{
	}

/** Enables activation of the task list if successful.

@return KErrNone if successful, otherwise another of the system-wide error codes.
*/
EXPORT_C TInt REikAppUiSession::EnableTaskList() const
	{
	return SendReceive(EEikAppUiEnableTaskList);
	}

/** Reserved for future use */
EXPORT_C void REikAppUiSession::REikAppUiSession_Reserved1()
	{
	}

/** Reserved for future use */
EXPORT_C void REikAppUiSession::REikAppUiSession_Reserved2()
	{
	}

/** Gets the debug preferences object 

@internalComponent
@return pointer to the debug preferences object and transfers ownership to the caller.
*/
EXPORT_C CEikDebugPreferences* REikAppUiSession::GetDebugPreferencesL() const
	{
	CBufFlat* buffer = CBufFlat::NewL(KDefaultBufSize); // allocate buffer with a default size that should be large enough in most cases
	CleanupStack::PushL(buffer);
	buffer->ExpandL(0,KDefaultBufSize);
	TPtr8 bufPtr = buffer->Ptr(0);
	const TInt sizeRequired = User::LeaveIfError(SendReceive(EEikAppUiGetDebugPreferences,TIpcArgs(buffer->Size(),&bufPtr)));
	if (sizeRequired > 0)
		{
		CleanupStack::PopAndDestroy(buffer);
		buffer = CBufFlat::NewL(sizeRequired);
		CleanupStack::PushL(buffer);
		buffer->ExpandL(0,sizeRequired);
		bufPtr.Set(buffer->Ptr(0));
#if defined(_DEBUG)
		const TInt check = 
#endif
		User::LeaveIfError(SendReceive(EEikAppUiGetDebugPreferences,TIpcArgs(0,&bufPtr)));
		__ASSERT_DEBUG(check == 0, User::Invariant());
		}
	CEikDebugPreferences* debugPreferences = CEikDebugPreferences::NewLC();
	RBufReadStream readStream(*buffer);
	CleanupClosePushL(readStream);
	readStream >> *debugPreferences;
	CleanupStack::PopAndDestroy(); //readStream
	CleanupStack::Pop(); //debugPreferences
	CleanupStack::PopAndDestroy(); //buffer
	return debugPreferences;
	}
	
	
