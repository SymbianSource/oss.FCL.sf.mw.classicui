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


#include <e32uid.h>
#include <e32hal.h>
#include <c32comm.h>
#include <s32file.h>
#include <basched.h>
#include <bautils.h>
#include <barsread.h>
#include <babackup.h>
#include <centralrepository.h>
#include <apasvst.h>
#include <apgcli.h>
#include <apgwgnam.h>
#include <viewcli.h>
#include <vwsappst.h>
#include <fepbase.h>
#include <eikenv.h>
#include <eikdll.h>
#include <eikrutil.h>
#include <uiklaf/private/lafenv.h>
#include <uiklafgt/eikpriv.rsg>
#include <uiklaf/private/lafsrv.h>
#include <eiksrv.h>
#include <eiksrvs.h>
#include <eiksvdef.h>
#include <eikdebug.h>
#include <s32mem.h>
#include "EIKSVFTY.H"
#include "EIKNFYSV.H"
#include "EIKALSRV.H"
#include "EIKSRV.PAN"
#include "eiksrvsconsts.h"
#include "../coresrc/eikdebugprefs.h"
#include <graphics/cone/coedefkeys.h>
#include "eikdefconst.h"


/** Default snooze increment in minutes.
@publishedPartner */
EXPORT_C extern const TInt KEikAlarmDefaultSnoozeInMinutes = 9;  // must not be initialized in the same CPP file as used, or the compiler will optimize it out

const TInt KBufferExpansionGranularity = 0x8;
const TUid KUidPasswordMode = {0x1000012B};

_LIT(KPanicClient,"EikSrv-client");
GLDEF_C void Panic(TEikServPanic aPanic)
	{
	_LIT(KPanicCat,"EIKON-SERVER");
	User::Panic(KPanicCat,aPanic);
	}

const TUint KRangeCount = 2;
const TInt KOpCodeRanges[KRangeCount] =
	{
	EFirstUnrestrictedOpcodeInEikAppUi,
	EEikAppUiFirstUnusedOpcode,
	};

const TUint8 KElementsIndex[KRangeCount] =
	{
	CPolicyServer::EAlwaysPass, 	//Always passing no capability required  0-99
	CPolicyServer::ENotSupported, 	//Not Supported		EEikAppUiFirstUnusedOpcode-End
	};

const CPolicyServer::TPolicy KEikServAppUiPolicy =
	{
	CPolicyServer::EAlwaysPass,
	KRangeCount,
	KOpCodeRanges,
	KElementsIndex,
	NULL
	};

//
// class CEikServAppUiServer
//

EXPORT_C CEikServAppUiServer* CEikServAppUiServer::NewL()
	{
	CEikServAppUiServer *pS=new CEikServAppUiServer();
    __ASSERT_ALWAYS(pS!=NULL,PanicServer(EEikSrvSvrCreateServer));
	CleanupStack::PushL(pS);
	pS->ConstructL();
	pS->StartL(EIKAPPUI_SERVER_NAME);
	CleanupStack::Pop();
	static_cast<CEikServEnv*>(CEikonEnv::Static())->SetEikServer(pS);
	return pS;
	}

const TInt KEiksrvUiDllValue = 0x100053D0;

/** Creates an interface object to Eikon server.

@publishedPartner
@released
*/
typedef CEikAppUi* (*CreateCEikServAppUiBase)();

void CEikServAppUiServer::ConstructL()
	{
	CEikonEnv& eikonEnv=*CEikonEnv::Static();
	if (eikonEnv.WsSession().FindWindowGroupIdentifier(0,__EIKON_SERVER_NAME,0)==KErrNotFound)
		{
		// read the default FEP configuration from resource-file
		TResourceReader resourceReader;
		eikonEnv.CreateResourceReaderLC(resourceReader, R_EIK_FEP_DEFAULT_DATA);
		const TPtrC defaultFep(resourceReader.ReadTPtrC());
		const TUint onKeyCharacterCodeForFoldedMatch = resourceReader.ReadUint32();
		const TUint onKeyModifierMask = resourceReader.ReadUint32();
		const TUint onKeyModifierValues = resourceReader.ReadUint32();
		const TUint offKeyCharacterCodeForFoldedMatch = resourceReader.ReadUint32();
		const TUint offKeyModifierMask = resourceReader.ReadUint32();
		const TUint offKeyModifierValues = resourceReader.ReadUint32();
		const TBool onState = resourceReader.ReadUint8();
		
		// write the "ERepositoryKeyMask_DefaultSetting" settings to the KUidFepFrameworkRepository repository
		CRepository* const repository = CRepository::NewLC(TUid::Uid(KUidFepFrameworkRepository));
		User::LeaveIfError(repository->StartTransaction(CRepository::EConcurrentReadWriteTransaction));
		repository->CleanupCancelTransactionPushL();
		CFepGenericGlobalSettings::WriteOnStateAndBroadcastL(*repository, onState, ERepositoryKeyMask_DefaultSetting);
		User::LeaveIfError(repository->Set(ERepositoryKey_DefaultFepId, defaultFep));
		CFepGenericGlobalSettings::WriteOnOrOffKeyDataAndBroadcastL(*repository, TFepOnOrOffKeyData(onKeyCharacterCodeForFoldedMatch, onKeyModifierMask, onKeyModifierValues), ERepositoryKey_DefaultOnKeyData);
		CFepGenericGlobalSettings::WriteOnOrOffKeyDataAndBroadcastL(*repository, TFepOnOrOffKeyData(offKeyCharacterCodeForFoldedMatch, offKeyModifierMask, offKeyModifierValues), ERepositoryKey_DefaultOffKeyData);
		CleanupStack::Pop(); // repository->CleanupCancelTransactionPushL
		TUint32 notUsed = 0;
		User::LeaveIfError(repository->CommitTransaction(notUsed)); // should never leave with KErrLocked as the "ERepositoryKeyMask_DefaultSetting" settings are only ever written to here
		CleanupStack::PopAndDestroy(repository);
		CleanupStack::PopAndDestroy(); // resourceReader
		
		// Try to load Fepswitch.exe
		RProcess fepswitchProcess;
		_LIT(KLitFepswitchExe, "z:\\sys\\bin\\Fepswitch.exe");
		const TInt fepSwitchLoadErr = fepswitchProcess.Create(KLitFepswitchExe, KNullDesC, TUidType(TUid::Uid(0x1000007a), TUid::Null(), TUid::Uid(0x10272617)));
		if(fepSwitchLoadErr != KErrNotFound)	// Fail silently if optional component fepswitch.exe does not exist
			{
			User::LeaveIfError(fepSwitchLoadErr);			
			CleanupClosePushL(fepswitchProcess);
			TRequestStatus requestStatus;
			fepswitchProcess.Rendezvous(requestStatus);
			fepswitchProcess.Resume();
			User::WaitForRequest(requestStatus);
			User::LeaveIfError(requestStatus.Int());
			CleanupStack::PopAndDestroy(&fepswitchProcess);
			}

		// load the UI-specific DLL into the Eiksrvs process
		TParse parse;
		_LIT(KEiksrvUiDllName,"\\sys\\bin\\EiksrvUi.dll");
		TFileName myDrive;
		Dll::FileName(myDrive); // we want the drive-component, in order to load EiksrvUi.dll from the same drive as we're on
		User::LeaveIfError(parse.SetNoWild(KEiksrvUiDllName,&myDrive,NULL));
		TUidType uidType(KDynamicLibraryUid,KSharedLibraryUid,TUid::Uid(KEiksrvUiDllValue));
		RLibrary lib;
		User::LeaveIfError(lib.Load(KEiksrvUiDllName,parse.FullName(),uidType));
		CleanupClosePushL(lib);
		CreateCEikServAppUiBase appUi = (CreateCEikServAppUiBase)lib.Lookup(1);
		CEikAppUi* self = (*appUi)();
		User::LeaveIfNull(self);
		static_cast<CEikServEnv&>(eikonEnv).SetUiDll(lib);
		CleanupStack::Pop(); // lib
		self->ConstructL(); // no leaving function may between the creation of "self" and this ConstructL call, as ownership of "this" is transferred to the CCoeEnv at the *start* of CEikServAppUiBase::ConstructL (hence also why "CleanupStack::PushL(self)" is not and should not be done)
		
		//create CEikDebugPreferences object
		iDebugPreferences = CEikDebugPreferences::NewL();
		TRAP_IGNORE(iDebugPreferences->RestoreL(eikonEnv.FsSession()));
#if defined (_DEBUG) // debug keys are always on, in debug target
		iDebugPreferences->SetFlags(iDebugPreferences->Flags()|CEikDebugPreferences::EFlagDebugKeysOn);
#endif
		}
	}
	
CEikServAppUiServer::~CEikServAppUiServer()
	{
	delete iDebugPreferences;
	}

CSession2* CEikServAppUiServer::NewSessionL(const TVersion &aVersion,const RMessage2&) const
	{
	const TVersion version(1,0,0);
	if (!User::QueryVersionSupported(version,aVersion))
		User::Leave(KErrNotSupported);

	const CEikServEnv* env = static_cast<CEikServEnv*>(CEikonEnv::Static());	
	MEikServAppUiSessionFactory* factory = env->EikServAppUiSessionFactory();
	return (factory ? factory->CreateSessionL() : NULL);
	}

CEikServAppUiServer::CEikServAppUiServer (TInt aPriority)
 	:CPolicyServer(aPriority, KEikServAppUiPolicy)
	{}
	
CEikAppUi& CEikServAppUiServer::AppUi()
	{
	return *iAppUi;
	}

//
// class CEikServAppUiSession
//

EXPORT_C CEikServAppUiSession::CEikServAppUiSession(MEikServAppUiSessionHandler* aHandler)
	{
	iSessionHandler=aHandler;
	}

EXPORT_C CEikServAppUiSession::~CEikServAppUiSession()
	{
	if(iScreenBlanked && iAppUiServer && iAppUiServer->iAppUi && iSessionHandler)
		iSessionHandler->UnblankScreen();
	}
	
EXPORT_C void CEikServAppUiSession::ConstructL()
	{
	}

void CEikServAppUiSession::PanicClient(const RMessage2& aMessage, TEikAppUiServPanic aCode)
	{
	aMessage.Panic(KPanicClient, aCode);
	}


EXPORT_C MEikServAppUiSessionHandler* CEikServAppUiSession::SessionHandler() const
	{
	return iSessionHandler;
	}		

EXPORT_C void CEikServAppUiSession::ServiceL(const RMessage2 &aMessage)
	{
	ASSERT(iSessionHandler);
	TBool completeMessage = ETrue;
	TInt err = KErrNone;
	switch (aMessage.Function())
		{
	case EEikAppUiCycleTasks:
		iSessionHandler->CycleTasksL(TTaskCycleDirection(aMessage.Int0()));
		break;
	case EEikAppUiSetStatusPaneFlags:
		iSessionHandler->SetStatusPaneFlags(aMessage.Int0());
		break;
	case EEikAppUiSetStatusPaneLayout:
		TRAP(err, iSessionHandler->SetStatusPaneLayoutL(aMessage.Int0()));
		// Complete with error locally before the break
		completeMessage=EFalse;
		aMessage.Complete(err);
		break;
	case EEikAppUiBlankScreen:
        {
        TRAP(err, iSessionHandler->BlankScreenL());
		if (err == KErrNone)
			iScreenBlanked = ETrue;
        completeMessage = EFalse;
		aMessage.Complete(err);
        }
		break;
	case EEikAppUiUnblankScreen:
		iSessionHandler->UnblankScreen();
		iScreenBlanked=EFalse;
		break;
	case EEikAppUiEnableTaskList:
		iSessionHandler->EnableTaskListL();
		break;
	case EEikAppUiLaunchTaskList:
		iSessionHandler->LaunchTaskListL();
		break;
	case EEikAppUiResolveError:
		{
		const TInt errCode=aMessage.Int1();
		const TUid appUid=TUid::Uid(aMessage.Int2());
		TBuf<KEikErrorResolverMaxTextLength> errText;
		const CEikonEnv::TErrorValidity errValidity=CEikonEnv::Static()->GetErrorText(errText,errCode,appUid);
		if (errValidity==CEikonEnv::EErrorNumValid) 
			aMessage.WriteL(0,errText);

		aMessage.Complete(errValidity); 
		break;
		}
	case EEikAppUiExtension: 
		{
		volatile TBool weAreResponsibleForCompletingMessage=ETrue;
		TRAPD(error,
			const TInt lengthOfRemoteBuffer=User::LeaveIfError(aMessage.GetDesLength(1));
			TPtr8 buffer(NULL,0);
			if (lengthOfRemoteBuffer>0)
				{
				buffer.Set(HBufC8::NewLC(lengthOfRemoteBuffer)->Des());
				aMessage.ReadL(1, buffer);
				}

			weAreResponsibleForCompletingMessage=EFalse; // the CEikServAppUiBase-derived class here takes responsibility for completing (or panicking) the message, either in its Extension function or later (asynchronously)	
			iSessionHandler->Extension(TUid::Uid(aMessage.Int0()),buffer,aMessage);
			if (lengthOfRemoteBuffer>0)
				CleanupStack::PopAndDestroy(); // the HBufC8
			);

		if(!weAreResponsibleForCompletingMessage)
			completeMessage = EFalse;
		else
			{
			if (error==KErrBadDescriptor)
				aMessage.Panic(__EIKON_SERVER,EEikServPanicNotifyBadDescriptor);
			else
				aMessage.Complete(error);
			}
		}
		break;
	case EEikAppUiGetDebugPreferences:
		{
		CEikDebugPreferences* debugPreferences = Server().iDebugPreferences;
		CBufFlat* const buffer = CBufFlat::NewL(KBufferExpansionGranularity);
		CleanupStack::PushL(buffer);
		RBufWriteStream writeStream(*buffer);
		CleanupClosePushL(writeStream);
		writeStream << *debugPreferences;
		writeStream.CommitL();
		
		const TInt initialBufSize = aMessage.Int0();
		if (initialBufSize && (buffer->Size() > initialBufSize))
			{
			// default buffer provided by client is too small, ask client to provide buffer of correct size
			User::Leave(buffer->Ptr(0).Size());
			}		
		aMessage.WriteL(1, buffer->Ptr(0));
		CleanupStack::PopAndDestroy(2); //writeStream & buffer
		}
		break;	
	case EEikAppUiResolveErrorWithTitleText:
		{
		const TInt errCode=aMessage.Int1();

		TErrorFlagAndId errInfo;
		TPckg<TErrorFlagAndId> errInfoPackage(errInfo);
		aMessage.ReadL(2, errInfoPackage);

		const TInt lengthOfErrorTextBuffer = aMessage.GetDesMaxLengthL(0);
		const TInt lengthOfTitleBuffer = aMessage.GetDesMaxLengthL(3);
		
		RBuf errText;
		errText.CreateL(lengthOfErrorTextBuffer);
		CleanupClosePushL(errText);

		RBuf errorTitleText;
		errorTitleText.CreateL(lengthOfTitleBuffer);
		CleanupClosePushL(errorTitleText);

		const CEikonEnv::TErrorValidity errValidity = CEikonEnv::Static()->DoGetErrorTextAndTitle(errText, errCode, errInfo.iTextId, errInfo.iFlags, errorTitleText, errInfo.iIsMemoryAllocatedByErrResolver);
		if (errValidity == CEikonEnv::EErrorNumValid) 
			{
			aMessage.WriteL(0, errText);
			aMessage.WriteL(3, errorTitleText);
			}

		CleanupStack::PopAndDestroy(2, &errText);
		aMessage.WriteL(2, TPckg<TErrorFlagAndId>(errInfo));
		aMessage.Complete(errValidity); 
		break;
		}

	default:
		aMessage.Complete(KErrNotSupported);
		break;
		}
		
	if (completeMessage && !aMessage.IsNull())
		aMessage.Complete(KErrNone);
	}


EXPORT_C void CEikServAppUiSession::ServiceError(const RMessage2& aMessage,TInt aError)
	{
	if (!aMessage.IsNull())
		{
		switch(aError)
			{
		case KErrBadDescriptor:
			PanicClient(aMessage, EEikSrvBadDescriptor);
			break;
		default:
			aMessage.Complete(aError);
			break;
			}
		}
	}
		
	
// Panic the server
GLDEF_C void PanicServer(TEikAppUiServPanic aPanic)
	{
	_LIT(KPanicCat,"EikAppUiServer");
	User::Panic(KPanicCat,aPanic);
	}

//
// CEikPasswordModeCategory
//

/**  Constructs a new password mode category object. 

The system's ini file (c:\\system\\system.ini) is opened, or created if it does not 
already exist. 

@param aFs A file server session.
@return The new password mode category object, or NULL if the disk is full. */
EXPORT_C CEikPasswordModeCategory* CEikPasswordModeCategory::NewLC(RFs& aFs)
	{ // static
	CEikPasswordModeCategory* self=new(ELeave) CEikPasswordModeCategory();
	CleanupStack::PushL(self);
	TRAPD(err, self->ConstructL(aFs));
	if( err == KErrDiskFull )
		{
		CleanupStack::PopAndDestroy( self );
		return NULL;
		}
	else if( err != KErrNone )
		User::Leave( err );
	
	return self;
	}

/**  Destructor. Deletes the file store used to read and write the password mode. */
EXPORT_C CEikPasswordModeCategory::~CEikPasswordModeCategory()
	{
	delete iStore;
	}

/** Reads the password mode entry from the system.ini file, if it contains such an entry, 
and returns it in aMode.

@param aMode On return, the system's password mode.*/
EXPORT_C void CEikPasswordModeCategory::GetPasswordModeL(TPasswordMode& aMode) const
	{
	if(iStore && iStore->IsPresentL(KUidPasswordMode))
		{
		RDictionaryReadStream stream;
		stream.OpenLC(*iStore,KUidPasswordMode);
		aMode = static_cast<TPasswordMode>(stream.ReadInt32L());
		CleanupStack::PopAndDestroy(); // stream
		}
	}

/**  Sets the system's password mode by writing the value specified in aMode 
to the system.ini file. 

@param aMode The new value for the system's password mode. */
EXPORT_C void CEikPasswordModeCategory::SetPasswordModeL(TPasswordMode aMode)
	{
	if(iStore)
		{
		RDictionaryWriteStream stream;
		stream.AssignLC(*iStore,KUidPasswordMode);
		stream.WriteInt32L(aMode);
		stream.CommitL();
		CleanupStack::PopAndDestroy(); // stream
		iStore->CommitL();
		}
	}

CEikPasswordModeCategory::CEikPasswordModeCategory()
	{}

void CEikPasswordModeCategory::ConstructL(RFs& aFs)
	{
	iStore=CDictionaryFileStore::SystemL(aFs);
	}

//
// class CEikServEnv
//

EXPORT_C CEikServEnv::CEikServEnv()
	{
	iIsTaskListEnabled = !(LafEnv::IsTaskListDisabledAtInitialization());
	}

EXPORT_C CEikServEnv::~CEikServEnv()
	{
	iUiDll.Close();
	}

EXPORT_C void CEikServEnv::DestroyEnvironment()
	{
	delete iServer;
	iServer = NULL;
	CEikonEnv::DestroyEnvironment();
	}

void CEikServEnv::SetEikServer(CEikServAppUiServer* aServer)
	{
	iServer = aServer;
	}

EXPORT_C void CEikServEnv::SetUiDll(RLibrary& aDll)
	{
	iUiDll = aDll;
	}

/**  Sets the Eikon Server Session Factory. This must be called by the System GUI during startup.

@param aSessionFactory a pointer to an object of an MEikServSessionFactory derived class. */
EXPORT_C void CEikServEnv::SetEikServAppUiSessionFactory(MEikServAppUiSessionFactory* aSessionFactory)
	{
	ASSERT(iSessionFactory == NULL);
	iSessionFactory = aSessionFactory;
	}
	
/**  Returns the EikServ Session Factory.

@return the EikServ Session Factory. */
EXPORT_C MEikServAppUiSessionFactory* CEikServEnv::EikServAppUiSessionFactory() const
	{
	return iSessionFactory;
	}

/**  Returns the status of the task list.

@return ETrue if the task list is enabled, EFalse if it is not. */
EXPORT_C TBool CEikServEnv::IsTaskListEnabled() const
	{
	return iIsTaskListEnabled;
	}

/**  Enables the task list.
*/
EXPORT_C void CEikServEnv::EnableTaskList()
	{
	iIsTaskListEnabled = ETrue;
	}


//
// MEikNotifyAlertCompletionObserver
// 

/** Constructor for MEikNotifyAlertCompletionObserver */
EXPORT_C MEikNotifyAlertCompletionObserver::MEikNotifyAlertCompletionObserver()
	{
	}

/** Reserved for future use */
EXPORT_C void MEikNotifyAlertCompletionObserver::MEikNotifyAlertCompletionObserver_Reserved1()
	{
	}
	
/** Reserved for future use */
EXPORT_C void MEikNotifyAlertCompletionObserver::MEikNotifyAlertCompletionObserver_Reserved2()
	{
	}

/** Reserved for future use */
EXPORT_C void CEikServEnv::CEikServEnv_Reserved1()
	{
	}
	
/** Reserved for future use */
EXPORT_C void CEikServEnv::CEikServEnv_Reserved2()
	{
	}
		
/** Reserved for future use */
EXPORT_C void CEikServEnv::CEikServEnv_Reserved3()
	{
	}
/** Reserved for future use */
EXPORT_C void CEikServEnv::CEikServEnv_Reserved4()
	{
	}
	
/** Reserved for future use */
EXPORT_C void CEikServEnv::CEikServEnv_Reserved5()
	{
	}
	
/** Reserved for future use */
EXPORT_C void CEikServEnv::CEikServEnv_Reserved6()
	{
	}

// from CCoeEnv
/** Reserved for future use */
EXPORT_C void CEikServEnv::Reserved_1()
	{
	}
	
/** Reserved for future use */
EXPORT_C void CEikServEnv::Reserved_2()
	{
	}

		
//
// MEikServAppUiSessionHandler
//

EXPORT_C MEikServAppUiSessionHandler::MEikServAppUiSessionHandler()
	{
	}
	
/** Reserved for future use */
EXPORT_C void MEikServAppUiSessionHandler::MEikServAppUiSessionHandler_Reserved1()
	{
	}
/** Reserved for future use */
EXPORT_C void MEikServAppUiSessionHandler::MEikServAppUiSessionHandler_Reserved2()
	{
	}


//
// MEikServAppUiSessionFactory
//

EXPORT_C MEikServAppUiSessionFactory::MEikServAppUiSessionFactory()
	{
	}

/** Reserved for future use */
EXPORT_C void MEikServAppUiSessionFactory::MEikServAppUiSessionFactory_Reserved1()
	{
	}

/** Reserved for future use */
EXPORT_C void MEikServAppUiSessionFactory::MEikServAppUiSessionFactory_Reserved2()
	{
	}


//
// MEikServNotifyAlert
// 

/** Constructor for MEikServNotifyAlert */
EXPORT_C MEikServNotifyAlert::MEikServNotifyAlert()
	{
	}

/** Reserved for future use */
EXPORT_C void MEikServNotifyAlert::MEikServNotifyAlert_Reserved1()
	{
	}
	
/** Reserved for future use */
EXPORT_C void MEikServNotifyAlert::MEikServNotifyAlert_Reserved2()
	{
	}

//
// MEikServAlarm
// 

/** Constructor for MEikServAlarm */
EXPORT_C MEikServAlarm::MEikServAlarm()
	{
	}

/** Reserved for future use */
EXPORT_C void MEikServAlarm::MEikServAlarm_Reserved1()
	{
	}
	
/** Reserved for future use */
EXPORT_C void MEikServAlarm::MEikServAlarm_Reserved2()
	{
	}

//
// MEikServAlarmFactory
// 

/** Constructor for MEikServAlarmFactory */
EXPORT_C MEikServAlarmFactory::MEikServAlarmFactory()
	{
	}

/** Reserved for future use */
EXPORT_C void MEikServAlarmFactory::MEikServAlarmFactory_Reserved1()
	{
	}
	
/** Reserved for future use */
EXPORT_C void MEikServAlarmFactory::MEikServAlarmFactory_Reserved2()
	{
	}
