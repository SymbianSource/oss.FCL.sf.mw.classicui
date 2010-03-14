// Copyright (c) 1997-2010 Nokia Corporation and/or its subsidiary(-ies).
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

#include "EIKBAKSV.H"
#include <babackup.h>
#include <basched.h>

#include <e32base.h>
#include <w32std.h>
#include <apaid.h>
#include <apacmdln.h>
#include <apgcli.h>
#include <apgtask.h>
#include <apgwgnam.h>
#include <coemain.h> // for TActivePriority only
#include <uikon/patchdata.h>

class RFindLib : public RLibrary
	{
public:
	inline TInt Open(const TFindLibrary& aFind,TOwnerType aType=EOwnerProcess);
	};

inline TInt RFindLib::Open(const TFindLibrary& aFind,TOwnerType aType)
	{return(RHandleBase::Open(aFind,aType));}


//
// class CEikServBackupServer
//


/**
Creates a CEikServBackupServer.  
Static factory function.
Does not call ConstructL  (BUT ConstructL is not EXPORTed !?!?)
@return Instantiated object
@publishedAll
@released
*/
EXPORT_C CEikServBackupServer* CEikServBackupServer::NewL()
	{ // static
	CEikServBackupServer* self=new(ELeave) CEikServBackupServer(EActivePriorityIpcEventsHigh);
	return self;
	}

/**
Constructor
@internalComponent
*/
CEikServBackupServer::CEikServBackupServer(TInt aPriority)
	: CBaBackupServer(aPriority)
	{}

/**
2nd phase constructor.  Opens connection to Window Server
Framework function
@see CBaBackupServer::ConstructL()
*/
void CEikServBackupServer::ConstructL()
	{
	CBaBackupServer::ConstructL();
	}

/**
Destructor
*/
CEikServBackupServer::~CEikServBackupServer()
	{
	delete iAppStarter;
	}


/**
Framework function
@see CBaBackupServer::IsOtherClientBusy(TUint32 aUniqueClientId)
*/
TBool CEikServBackupServer::IsOtherClientBusy(TUint32 aUniqueClientId) const
	{
	return (iAppStarter || CBaBackupServer::IsOtherClientBusy(aUniqueClientId));
	}

/**
Framework function
@see CBaBackupServer::CompleteClosingFiles(CArrayFix<CBaServBackupSession::TClosedFile>* aClosedFiles)
*/
void CEikServBackupServer::CompleteClosingFiles(CArrayFix<CBaServBackupSession::TClosedFile>* aClosedFiles)
	{
	delete iAppStarter;
	iAppStarter=NULL;
	TRAPD(err,iAppStarter=CAppStarter::NewL(*this,aClosedFiles));
	if (err!=KErrNone)
		{
		SetBusy(0);
		}
	}

/**
Framework function
@see CServer2:;::NewSessionL(const TVersion &aVersion, const RMessage2&)
*/
CSession2* CEikServBackupServer::NewSessionL(const TVersion &aVersion, const RMessage2&) const
	{
	const TVersion version(KBakServMajorVN,KBakServMinorVN,KBakServBuildVN);
	if (!User::QueryVersionSupported(version,aVersion))
		{
		User::Leave(KErrNotSupported);
		}
	return CEikServBackupSession::NewL();
	}

/**
Framework Function
@see MAppStarterObserver::HandleAppsStarted()
*/
void CEikServBackupServer::HandleAppsStarted()
	{
	SetBusy(0);
	delete iAppStarter;
	iAppStarter=NULL;
	}



//
// class CAppWatcher
//


/**
Static factory function
@param aThreadId - Of application to watch
@param aAppShutter - Called when watcher (this) sees app close.
@param aClosedFile - file that will need restarting
@return Instantiated and constructed object
@internalTechnology
*/
CAppWatcher* CAppWatcher::NewL(TThreadId aThreadId,CAppShutter& aAppShutter,
								const CEikServBackupSession::TClosedFile& aClosedFile)
	{ // static
	CAppWatcher* self=new(ELeave) CAppWatcher(aAppShutter,aClosedFile);
	CleanupStack::PushL(self);
	self->ConstructL(aThreadId);
	CleanupStack::Pop(); // self
	return self;
	}

/**
Destructor
*/
CAppWatcher::~CAppWatcher()
	{
	Cancel();
	iThread.Close();
	}

/**
@return Copy of the closed file
@internalTechnology
@see CEikServBackupSession::TClosedFile
*/
const CEikServBackupSession::TClosedFile& CAppWatcher::Info() const
	{
	return iClosedFile;
	}

/** 
Private constructor
@param aAppShutter - called when watcher (this) sees app close.
@param aClosedFile- the file that will need restarting
@internalComponent
*/
CAppWatcher::CAppWatcher(CAppShutter& aAppShutter,const CEikServBackupSession::TClosedFile& aClosedFile)
	: CActive(CActive::EPriorityStandard), iAppShutter(aAppShutter), iClosedFile(aClosedFile)
	{}


/**
Second phase constructor
Logs on to thread to wait for application to close.
@param aThreadId
@internalComponent
*/
void CAppWatcher::ConstructL(TThreadId aThreadId)
	{
	CActiveScheduler::Add(this);
	iStatus=KRequestPending;
	SetActive();
	User::LeaveIfError(iThread.Open(aThreadId));
	iThread.Logon(iStatus);
	}

/**
CActive framework function
Cancels thread logon
*/
void CAppWatcher::DoCancel()
	{
	if (iThread.Id() && iStatus==KRequestPending)
		{
		iThread.LogonCancel(iStatus);
		}
	}

/**
CActive framework function
Handles application closure. Calls App shutter
*/
void CAppWatcher::RunL()
	{
	iAppShutter.HandleAppClosedL(iClosedFile);
	}

/**
CActive framework function
*/
TInt CAppWatcher::RunError(TInt /*aError*/)
	{
	delete this;
	return KErrNone;
	}

//
// class CAppShutter
//

/**
@internalComponent
*/
CAppShutter::CShutterTimer* CAppShutter::CShutterTimer::NewL(TInt aPriority)
	{ // static
	CShutterTimer* self=new(ELeave) CShutterTimer(aPriority);
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop(); // self
	CActiveScheduler::Add(self);
	return self;
	}
/**
@internalComponent
*/
TInt CAppShutter::CShutterTimer::RunError(TInt aError)
	{
	if (aError==KLeaveWithoutAlert)
		{
		return KErrNone;
		}
	return aError;
	}
	
/**
@internalComponent
*/
CAppShutter::CShutterTimer::CShutterTimer(TInt aPriority)
	: CPeriodic(aPriority)
	{}
	
/**
@internalTechnology
*/
CAppShutter* CAppShutter::StartL(MAppShutterObserver& aObserver,
				 CArrayFix<CEikServBackupSession::TClosedFile>& aClosedFiles,
				 CBaBackupServer& aBackupServer)
	{ // static
	CAppShutter* self=new(ELeave) CAppShutter(aObserver,aClosedFiles, aBackupServer);
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop(); // self
	return self;
	}

/**
@internalComponent
*/
CAppShutter::~CAppShutter()
	{
	if (iAppWatchers)
		{
		iAppWatchers->ResetAndDestroy();
		delete iAppWatchers;
		}
	delete iTimer;
	delete iWgIds;
	iWsSession.Close();
	}


/**
@internalComponent
*/
CAppShutter::CAppShutter(MAppShutterObserver& aObserver,
			 CArrayFix<CEikServBackupSession::TClosedFile>& aClosedFiles,
			 CBaBackupServer& aBackupServer) 
			: iObserver(aObserver),iClosedFiles(aClosedFiles), iBackupServer(aBackupServer)


	{}

/**
@internalComponent
*/
void CAppShutter::ConstructL()
	{
	iTimer=CShutterTimer::NewL(CActive::EPriorityStandard);
	iTimer->Start(0,1,TCallBack(TimerCallBackL,this));
	iAppWatchers=new(ELeave) CArrayPtrFlat<CAppWatcher>(1);
	User::LeaveIfError(iWsSession.Connect());
	const TInt wgCount=iWsSession.NumWindowGroups(0);
	iWgIds=new(ELeave) RArray<RWsSession::TWindowGroupChainInfo>(wgCount);
	User::LeaveIfError(iWsSession.WindowGroupList(0,iWgIds));
	}

/**
@internalTechnology
*/
void CAppShutter::HandleAppClosedL(const CEikServBackupSession::TClosedFile& aClosedFile)
	{
	const TInt count=iAppWatchers->Count();
	for (TInt ii=0;ii<count;ii++)
		{
		CAppWatcher* watcher=(*iAppWatchers)[ii];
		if (watcher->Info()==aClosedFile)
			{
			iAppWatchers->Delete(ii);
			NextL();
			delete watcher;
			break;
			}
		}
	}

/**
@internalComponent
*/
TInt CAppShutter::TimerCallBackL(TAny* aPtr)
	{ // static
	REINTERPRET_CAST(CAppShutter*,aPtr)->HandleTimerCallBackL();
	return 0;
	}

/**
@internalComponent
*/
void CAppShutter::HandleTimerCallBackL()
	{
	NextL();
	}
	
/**
@internalComponent
*/
void CAppShutter::NextL()
	{
	while (iNextWgIndex < iWgIds->Count())
		{
		const RWsSession::TWindowGroupChainInfo wgId=(*iWgIds)[iNextWgIndex++];
		CApaWindowGroupName* wgName=CApaWindowGroupName::NewLC(iWsSession,wgId.iId);

		// Skip invalid window groups.
		// Note that if the window group name is null then CApaWindowGroupName
		// uses a default name that yields an app uid of zero.
		if (wgName->AppUid().iUid == 0 || wgName->IsSystem() || wgName->Hidden())
			{
			CleanupStack::PopAndDestroy(); // wgName
			}
		else
			{
			TPtrC docName=wgName->DocName();
			CEikServBackupSession::TClosedFile data;
			if (docName.Length())
				{
				data.iDocName=docName;
				}
			data.iUid=wgName->AppUid();
			CleanupStack::PopAndDestroy(); // wgName

			// We don't want to restart server apps
			if (wgId.iParentId <= 0)
				{
				iClosedFiles.AppendL(data);
				}
			TThreadId threadId;
			User::LeaveIfError(iWsSession.GetWindowGroupClientThreadId(wgId.iId,threadId));
			CAppWatcher* watcher=CAppWatcher::NewL(threadId,*this,data);
			CleanupStack::PushL(watcher);
			iAppWatchers->AppendL(watcher);
			CleanupStack::Pop(); // watcher
			TApaTask task(iWsSession);
			task.SetWgId(wgId.iId);
			task.SendSystemEvent(EApaSystemEventShutdown);
			if (iTimer->IsActive())
				{
				iTimer->Cancel();
				}
			// If hardware use patchable constant if not default to 5 seconds
			iTimer->Start(KUIKONBackupCloseAllFilesTimeout,KUIKONBackupCloseAllFilesTimeout,TCallBack(TimerCallBackL,this));
			return;
			}
		}

	CheckCompleteL();
	}

/**
@internalComponent
*/
void CAppShutter::CheckCompleteL()
	{
	// see if any new window groups exist.  If they do, add them to the end of iWgIds and go back to NextL
	const TInt wgCount=iWsSession.NumWindowGroups(0);
	RArray<RWsSession::TWindowGroupChainInfo>* wgIds=new(ELeave) RArray<RWsSession::TWindowGroupChainInfo>(wgCount);
	CleanupStack::PushL(wgIds);
	User::LeaveIfError(iWsSession.WindowGroupList(0,wgIds));
	TBool foundNewWg=EFalse;
	for (TInt ii=0;ii<wgCount;ii++)
		{
		if (iWgIds->Find((*wgIds)[ii])<0)
			{
			iWgIds->AppendL((*wgIds)[ii]);
			foundNewWg=ETrue;
			}
		}
	CleanupStack::PopAndDestroy(); // wgIds
	if (foundNewWg)
		{
		NextL();
		}
	else // if iAppWatchers is non-empty then some tasks are still closing.  Give them up to 5 seconds to terminate
		{
		// Check all files that have been registered for file lock notifications have been updated
		TBool filesAllLocked = iBackupServer.HaveAllCloseAllFilesClientsReRegistered();

		// If all registered files are locked and all app watchers are done we can proceed
		if ((filesAllLocked && (iAppWatchers->Count() == 0)) || (iCheckCount == 3))
			{
			const TBool allAppsClosed=(iAppWatchers->Count()==0);
			iObserver.HandleAppsClosedL(allAppsClosed);
			}
		else
			{
			iCheckCount++;
			if (iTimer->IsActive())
				{
				iTimer->Cancel();
				}
			// If hardware use patchable constant if not default to 5 seconds
			iTimer->Start(KUIKONBackupCloseAllFilesTimeout,KUIKONBackupCloseAllFilesTimeout,TCallBack(TimerCallBackL,this));

			}
		}
	}

//
// class CEikServAppShutter
//

/**
@internalTechnology
*/
CEikServAppShutter::CEikServAppShutter(const RMessage2& aMessage)
	: iMessage(aMessage)
	{}

/**
@internalTechnology
*/
void CEikServAppShutter::ConstructL(MAppShutterObserver& aObserver,
				    CArrayFix<CEikServBackupSession::TClosedFile>& aClosedFiles,
				    CBaBackupServer* aBackupServer)
	{
	iShutter=CAppShutter::StartL(aObserver,aClosedFiles, *aBackupServer);
	}
/**
@internalTechnology
*/
CEikServAppShutter::~CEikServAppShutter()
	{
	delete iShutter;
	}

/**
@internalTechnology
*/
const RMessage2& CEikServAppShutter::Message() const
	{
	return iMessage;
	}


//
// class CEikServBackupSession
//


/**
Static factory function
@return Instantiated and constructed object.
@internalTechnology
*/
CEikServBackupSession* CEikServBackupSession::NewL()
	{ // static
	CEikServBackupSession* self=new(ELeave) CEikServBackupSession();
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop(self); 
	return self;
	}

/**
@internalTechnology
*/
CEikServBackupSession::~CEikServBackupSession()
	{
	}

/**
Framework function
@see CBaBackupServerSession::HandleError( Tint aError )
*/
void CEikServBackupSession::HandleError(TInt aError)
	{
	if (iAppShutter)
		{
		BackupServer()->SetCloseAllOperationRunningState(EFalse);
		iAppShutter->Message().Complete(aError);
		delete iAppShutter;
		iAppShutter=NULL;
		CBaServBackupScheduler::Current()->SetErrorHandler(NULL);
		}
	else
		{
		CBaServBackupSession::HandleError(aError);
		}
	}

/**
@internalComponent
*/
void CEikServBackupSession::ServiceL(const RMessage2& aMessage)
	{
	CBaServBackupSession::ServiceL(aMessage);
	}

/**
@internalComponent
*/
void CEikServBackupSession::ServiceError(const RMessage2& aMessage,TInt aError)
	{
	if (!aMessage.IsNull())
		{
		aMessage.Complete(aError);
		}
	}

/**
Framework function
@see MAppShutterObserver::HandleAppsClosedL(TBool aAllAppsClosed)
*/
void CEikServBackupSession::HandleAppsClosedL(TBool aAllAppsClosed)
	{
	if (iAppShutter)
		{
		// End the CloseAll period
		BackupServer()->SetCloseAllOperationRunningState(EFalse);
		const TInt err=(aAllAppsClosed? KErrNone : KErrInUse);
		iAppShutter->Message().Complete(err);
		delete iAppShutter;
		iAppShutter=NULL;
		}
	}

/**
Used as TCleanupItem.
@internalComponent
*/
void CEikServBackupSession::CleanupCloseAllFiles(TAny* aPtr)
	{ // static
	CEikServBackupSession* self=REINTERPRET_CAST(CEikServBackupSession*,aPtr);
	delete self->iAppShutter;
	self->iAppShutter=NULL;
	}


/**
Framework function
@see CBaBackupServerSession::CloseAllFilesL(const RMessage2& aMessage)
*/
TCompletionType CEikServBackupSession::CloseAllFilesL(const RMessage2& aMessage)
	{
	CBaServBackupSession::DoCloseAllFilesL(aMessage);
	CEikServBackupServer* server=static_cast<CEikServBackupServer*>(BackupServer());
	CleanupStack::PushL(TCleanupItem(CleanupCloseAllFiles,this));
	__ASSERT_DEBUG(iAppShutter == NULL, PanicClientL(aMessage,EBadInternalState));
	iAppShutter=new(ELeave) CEikServAppShutter(aMessage);
	if(!ClosedFiles())
		{
		CArrayFixSeg<CBaServBackupSession::TClosedFile>* closedFiles=new(ELeave) CArrayFixSeg<CBaServBackupSession::TClosedFile>(1);
		SetClosedFiles(closedFiles);
		}
	iAppShutter->ConstructL(*this,*ClosedFiles(), (CBaBackupServer*)BackupServer() );
	CleanupStack::Pop(); // CleanupCloseAllFiles
	return ECompleteAsync;
	}

/**
Framework function
@see CBaBackupServerSession::RestartAll()
*/
void CEikServBackupSession::RestartAll()
	{
	CBaBackupServer* server=BackupServer();	
	if (server->IsClientBusy(UniqueClientId()))
		{
		if (iAppShutter)
			{
			BackupServer()->SetCloseAllOperationRunningState(EFalse);
			iAppShutter->Message().Complete(KErrCancel);
			delete iAppShutter;
			iAppShutter=NULL;
			}
		CBaServBackupSession::RestartAll();
		}
	}


/**
@internalComponent
*/
void CEikServBackupSession::PanicClientL(const RMessage2& aMessage, TEikBackupServPanic aCode)
	{
	_LIT(KPanicCat,"BackupSrv");
	aMessage.Panic(KPanicCat,aCode);
	User::Leave(KLeaveWithoutAlert);
	}



//
// class CAppStarter
//

const TInt KAppStarterTimerGranularity=100000; // 0.1s
_LIT(KThreadName,"AppStarterThread");

/**
Static factory function
@param aObserver Applications starter observer
@param aClosedFiles A list of the files closed for backing up (i.e. which need re-starting)
@return instantiated and constructed App Starter
@internalTechnology
*/
CAppStarter* CAppStarter::NewL(MAppStarterObserver& aObserver,CArrayFix<CEikServBackupSession::TClosedFile>* aClosedFiles)
	{ // static
	CleanupStack::PushL(aClosedFiles);
	CAppStarter* self=new(ELeave) CAppStarter(aObserver,aClosedFiles);
	CleanupStack::Pop(); // aClosedFiles
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop(); // self
	return self;
	}

/** 
destructor
*/
CAppStarter::~CAppStarter()
	{// Cancel any outstanding request before cleanup
	Cancel(); // Calls DoCancel()
	delete iClosedFiles;
	}

/**
Constructor
@param aObserver Startup observer
@param aClosedFiles A list of the files closed for backing up (i.e. which need re-starting)
@internalComponent
*/
CAppStarter::CAppStarter(MAppStarterObserver& aObserver, CArrayFix<CEikServBackupSession::TClosedFile>* aClosedFiles)
	: CActive(EPriorityStandard), iObserver(aObserver), iClosedFiles(aClosedFiles)
	{
	CActiveScheduler::Add(this);	
	}

/**
2nd phase constructor.
This function creates a separate thread which is used to run StartAppsL() synchronously.
A static fuction - ThreadEntryPoint() - is called to call StartAppsL() on 'this'.
@internalComponent
*/
void CAppStarter::ConstructL()
	{
	if (IsActive())
		{
		return;
		}

	TInt res = iThread.Create(KThreadName,
				ThreadEntryPoint,
				KDefaultStackSize,
				NULL,
				this);

	if(KErrNone==res)
		{// set ourselves to KRequestPending, set active, resume new thread (to make synchronous call)
		iStatus = KRequestPending;
		SetActive();
		iThread.Logon(iStatus);	// Request notification when thread dies
		iThread.Resume();		// Start the thread
		}
	}

/**
This function is excuted synchronously in a separate thread
Each of the closed files passed in during construction is restarted.
@internalComponent
*/
void CAppStarter::StartAppsL()
	{// synchronous call executed in thread

	RApaLsSession apaSession;
	User::LeaveIfError(apaSession.Connect());
	CleanupClosePushL(apaSession);
	RWsSession wsSession;
	User::LeaveIfError(wsSession.Connect());
	CleanupClosePushL(wsSession);


	do	{
		const TInt count=iClosedFiles->Count();
		if (count!=0)
			{
			CEikServBackupSession::TClosedFile& item=(*iClosedFiles)[count-1];
			TInt wgId=0;
			CApaCommandLine* cmdLine=CApaCommandLine::NewLC();
			if (item.iDocName.Length()>0)
				{
				CApaWindowGroupName::FindByDocName(item.iDocName,wsSession,wgId);
				cmdLine->SetDocumentNameL(item.iDocName);
				}
			else
				{
				CApaWindowGroupName::FindByAppUid(item.iUid,wsSession,wgId);
				}

			if (wgId==KErrNotFound)
				{
				cmdLine->SetCommandL(EApaCommandBackground);
				TApaAppInfo info;
				User::LeaveIfError(apaSession.GetAppInfo(info, item.iUid));
				cmdLine->SetExecutableNameL(info.iFullName);
				apaSession.StartApp(*cmdLine); // ignore the error, we can't do anything useful in response
				}
			CleanupStack::PopAndDestroy(1); // cmdLine
			}
		
		if (count<=1)
			{
			break;//loop termination condition
			}
		else
			{
			iClosedFiles->Delete(count-1);
			User::After(KAppStarterTimerGranularity);// force thread to sleep
			}
		
		} while(1);

	CleanupStack::PopAndDestroy(2); // apaSession & wsSession
	}

/**
Static function used to run StartAppsL() in separate thread.
Thread is terminated on completion
@param aParams 'this' pointer to CAppStarter
@return Is ignored 
*/
TInt CAppStarter::ThreadEntryPoint(TAny* aParams)
	{// perform apps startup
	
	//CleanupStack for this thread	
	CTrapCleanup* theCleanupStack = CTrapCleanup::New();
	CAppStarter* appStarter = NULL;
	appStarter = static_cast<CAppStarter*>(aParams);
	TInt err = KErrNone;
	if(appStarter)
		{
		TRAP(err, appStarter->StartAppsL());//synchronous call
		}
	delete theCleanupStack;
	
	// Task complete so end this thread
	RThread().Kill(err);// err value can be retrieved via 'ExitReason()' in CAppStarter::RunL()
	return (KErrNone); //value discarded
	}

/**
Kills (other) thread if necessary
CActive framework function
*/
void CAppStarter::DoCancel()
	{
	TExitType threadExitType = iThread.ExitType();
	if(EExitPending==threadExitType)
		{//thread still running
		iThread.LogonCancel(iStatus);//cancel outstanding notification request
		iThread.Kill(KErrCancel);
		iThread.Close();
		}
	}

/**
Closes (other) thread.  Kills it if necessary.
Signals to observer that task is complete.
CActive framework function.
*/
void CAppStarter::RunL()	
	{// check in case thread is still running e.g. if Logon() failed 	
	TExitType threadExitType = iThread.ExitType();
	if(EExitPending==threadExitType) // Thread still running - kill it
		{
		iThread.Kill(KErrNone);
		}
	
	iThread.Close();// close thread handle
	iObserver.HandleAppsStarted();// calls delete on this active object
	}

//
// Main
//

