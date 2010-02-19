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

/**
 @file
 @internalComponent
*/

#ifndef __EIKBAKSV_H__
#define __EIKBAKSV_H__

#include <e32base.h>
#include <baksrv.h>
#include <babackup.h>
#include <badesca.h>
#include <w32std.h>
#include <apgcli.h>

enum TEikBackupServPanic
	{
	EBadInternalState = 0,
	};

class MAppStarterObserver
	{
public:
	virtual void HandleAppsStarted() = 0;
	};

class MAppShutterObserver
	{
public:
	virtual void HandleAppsClosedL(TBool aAllAppsClosed) = 0;
	};

class CEikServAppShutter;
class CEikServBackupServer;

NONSHARABLE_CLASS(CEikServBackupSession) : public CBaServBackupSession, public MAppShutterObserver
	{
public:
	static CEikServBackupSession* NewL();
	~CEikServBackupSession();
public: // from CBaServBackupSession
	void HandleError(TInt aError);
private: // from MAppShutterObserver
	void HandleAppsClosedL(TBool aAllAppsClosed);
private:
	inline CEikServBackupSession() :CBaServBackupSession() {} 
private: // from CBaServBackupSession
	TCompletionType CloseAllFilesL(const RMessage2& aMessage);
	void RestartAll();
	void ServiceL(const RMessage2& aMessage);
	void ServiceError(const RMessage2& aMessage,TInt aError);
private:
	static void CleanupCloseAllFiles(TAny* aPtr);
	void DoRestartAll();
	void PanicClientL(const RMessage2& aMessage,TEikBackupServPanic aCode);
private:
	CEikServAppShutter* iAppShutter;
	};

class CAppShutter;

NONSHARABLE_CLASS(CAppWatcher) : public CActive
	{
public:
	static CAppWatcher* NewL(TThreadId aThreadId,CAppShutter& aAppShutter,const CEikServBackupSession::TClosedFile& aClosedFile);
	~CAppWatcher();
	const CEikServBackupSession::TClosedFile& Info() const;
private:
	CAppWatcher(CAppShutter& aAppShutter,const CEikServBackupSession::TClosedFile& aClosedFile);
	void ConstructL(TThreadId aThreadId);
private: // from CActive
	void DoCancel();
	void RunL();
	TInt RunError(TInt aError);
private:
	CAppShutter& iAppShutter;
	CEikServBackupSession::TClosedFile iClosedFile;
	RThread iThread;
	};

NONSHARABLE_CLASS(CAppShutter) : public CBase
	{
public:
	static CAppShutter* StartL(MAppShutterObserver& aObserver,
				   CArrayFix<CEikServBackupSession::TClosedFile>& aClosedFiles,
				   CBaBackupServer& aBackupServer);

	~CAppShutter();
	void HandleAppClosedL(const CEikServBackupSession::TClosedFile& aClosedFile);
private:
	CAppShutter(MAppShutterObserver& aObserver,
 		    CArrayFix<CEikServBackupSession::TClosedFile>& aClosedFiles,
		    CBaBackupServer& aBackupServer);

	void ConstructL();
	static TInt TimerCallBackL(TAny* aPtr);
	void HandleTimerCallBackL();
	void NextL();
	void CheckCompleteL();
private:
	NONSHARABLE_CLASS(CShutterTimer) : public CPeriodic
		{
	public:
		static CShutterTimer* NewL(TInt aPriority);
	protected: // from CActive
		TInt RunError(TInt aError);
	private:
		CShutterTimer(TInt aPriority);
		};
private:
	MAppShutterObserver& iObserver;
	RWsSession iWsSession;
	RArray<RWsSession::TWindowGroupChainInfo>* iWgIds;
	CArrayFix<CEikServBackupSession::TClosedFile>& iClosedFiles;
	CArrayPtr<CAppWatcher>* iAppWatchers;
	CShutterTimer* iTimer;
	TInt iNextWgIndex;
	CBaBackupServer& iBackupServer;
	TInt iCheckCount;
	};

NONSHARABLE_CLASS(CEikServAppShutter) : public CBase
	{
public:
	CEikServAppShutter(const RMessage2& aMessage);
	~CEikServAppShutter();
	void ConstructL(MAppShutterObserver& aObserver,
			CArrayFix<CEikServBackupSession::TClosedFile>& aClosedFiles,
			CBaBackupServer* aBackupServer);

	const RMessage2& Message() const;
private:
	CAppShutter* iShutter;
	RMessage2 iMessage;
	};

class CAppStarter;

NONSHARABLE_CLASS(CEikServBackupServer) : public CBaBackupServer, public MAppStarterObserver
	{
public:
	IMPORT_C static CEikServBackupServer* NewL();
public:
	~CEikServBackupServer();
private: // from CBaBackupServer
	void ConstructL();
	void CompleteClosingFiles(CArrayFix<CBaServBackupSession::TClosedFile>* aClosedFiles);
	TBool IsOtherClientBusy(TUint32 aUniqueClientId) const;
private: // from CServer
	CSession2* NewSessionL(const TVersion &aVersion, const RMessage2& aMessage ) const;
private: // from MAppStarterObserver
	void HandleAppsStarted();
private:
	CEikServBackupServer(TInt aPriority);
	inline TBool IsOtherClientBusy(TUint32 aUniqueClientId);
	inline TBool IsClientBusy(TUint32 aUniqueClientId);
private:
	CAppStarter* iAppStarter;
	};


NONSHARABLE_CLASS(CAppStarter) : public CActive
	{// Active object wraps the task of starting up apps in a thread
public:
	static CAppStarter* NewL(MAppStarterObserver& aObserver,CArrayFix<CEikServBackupSession::TClosedFile>* aClosedFiles);
	~CAppStarter();
private:
	CAppStarter(MAppStarterObserver& aObserver, CArrayFix<CEikServBackupSession::TClosedFile>* aClosedFiles);
	void ConstructL();

	static TInt ThreadEntryPoint(TAny* aParams);
	void StartAppsL();// Main thread function
private: // from CActive
	void DoCancel();
	void RunL();
private:
	MAppStarterObserver& iObserver;
	CArrayFix<CEikServBackupSession::TClosedFile>* iClosedFiles;// Object owned by CBaBackupServer. Resource ownership
																// transferred to derived CEikServBackupServer
	RThread iThread;
	};

#endif	// __EIKBAKSV_H__
