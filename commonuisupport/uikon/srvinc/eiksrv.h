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

#ifndef __EIKSRV_H__
#define __EIKSRV_H__

#include <eikappui.h>
#include <eikenv.h>
#include <apgtask.h>
#include <vwsappst.h>
#include <eikunder.h>
#include <eikcycledef.h>

class CDictionaryFileStore;
class CVwsSessionWrapper;
class CEikDebugPreferences;

const TInt KBufferExpansionRequired = 10;		// Random number chosen to indicate buffer expansion on the client side.

/**
@publishedPartner 
@released 
*/
enum TEikAppUiServPanic
	{
	EEikSrvDefault,
	EEikSrvSvrCreateServer, // no longer used
	EEikSrvSvrStartServer,
	EEikSrvSrvNotFound,
	EEikSrvBadDescriptor,
	EEikSrvIllegalError,
	EEikSrvBadRequestSequence
	};

class CEikServAppUiSession;

NONSHARABLE_CLASS(CEikServAppUiServer) : public CPolicyServer
/**
@publishedPartner 
@released 
*/
	{
	friend class CEikServAppUiSession;
public:
	enum {EPriority=EPriorityAbsoluteHigh};
	IMPORT_C static CEikServAppUiServer* NewL();
	virtual CSession2* NewSessionL(const TVersion &aVersion,const RMessage2& aMessage) const;
	static TInt ThreadFunction(TAny* aStarted);
	CEikAppUi& AppUi(); // non-inline (and non-exported) so that it cannot be accessed outside of the DLL
	~CEikServAppUiServer();
private:
	CEikServAppUiServer(TInt aPriority=EPriority);
	void ConstructL();
	CEikServAppUiSession* NewSessionL();
private:
	CEikAppUi* iAppUi;
	CEikDebugPreferences* iDebugPreferences;
	};

class MEikServAppUiSessionHandler
/**
@publishedPartner 
@released 
*/
	{
public:
	virtual void NotifyAlarmServerOfTaskChangeL() = 0;
	virtual void LaunchTaskListL() = 0;
	virtual void CycleTasksL(enum TTaskCycleDirection aDirection) = 0;
	virtual void SetStatusPaneFlags(TInt aFlags) = 0;
	virtual void SetStatusPaneLayoutL(TInt aLayoutResId) = 0;
	virtual void BlankScreenL() = 0;
	virtual void UnblankScreen() = 0;
	virtual void EnableTaskListL() = 0;
	virtual void Extension(TUid aExtensionUid,const TDesC8& aBuffer,RMessagePtr2 aMessage) = 0;
protected:
	IMPORT_C MEikServAppUiSessionHandler();
private:
	IMPORT_C virtual void MEikServAppUiSessionHandler_Reserved1();
	IMPORT_C virtual void MEikServAppUiSessionHandler_Reserved2();
private:
	TInt iMEikServAppUiSessionHandler_Reserved1;
	};

class CEikServAppUiSession : public CSession2
/**
@publishedPartner
@released 
*/
	{
public:
	IMPORT_C CEikServAppUiSession(MEikServAppUiSessionHandler* aHandler);
	IMPORT_C ~CEikServAppUiSession();
	IMPORT_C virtual void ConstructL();
	IMPORT_C virtual void ServiceL(const RMessage2& aMessage);
	IMPORT_C virtual void ServiceError(const RMessage2& aMessage,TInt aError);
private:
	void PanicClient(const RMessage2& aMessage, TEikAppUiServPanic aCode);
	inline CEikServAppUiServer& Server() {return *STATIC_CAST(CEikServAppUiServer*,CONST_CAST(CServer2*,CSession2::Server()));}
protected:
	IMPORT_C MEikServAppUiSessionHandler* SessionHandler() const;
protected:
	CEikServAppUiServer* iAppUiServer;
	TBool iScreenBlanked;
	MEikServAppUiSessionHandler* iSessionHandler;
private: // below are old obsolete member variables, kept for binary compatibility
	TInt iNotUsed1;
	TInt iNotUsed2;
	};


NONSHARABLE_CLASS(CEikPasswordModeCategory) : public CBase
/** Gives access to the system's password mode. 

The password mode can be passed to a password window, see RWindowBase::PasswordWindow(). 
This is a window that requires the user to enter a password before any further actions can 
be carried out. 

The possible password modes are enumerated in TPasswordMode. 

@publishedPartner
@released */
	{
public:
	IMPORT_C static CEikPasswordModeCategory* NewLC(RFs& aFs);
	IMPORT_C ~CEikPasswordModeCategory();
	IMPORT_C void GetPasswordModeL(TPasswordMode& aMode) const; 
	IMPORT_C void SetPasswordModeL(TPasswordMode aMode);
private:
	CEikPasswordModeCategory();
	void ConstructL(RFs& aFs);
private:
	CDictionaryFileStore* iStore;
	};

class CEikServNotifyServer;
class CNotifierServerExtended;
class CEikServBackupServer;
class CEikServAlarmAlertServer;
class CEikKeyWindow;
class CEikUndertaker;
class CEikPasswordControl;
class CEikTaskListDialog;
class MEikServNotifyAlert;
class MEikServAlarmFactory;
class CEikServDllClose;

NONSHARABLE_CLASS(TEikServCtrlFactories)
/**
@publishedPartner 
@released 
*/
	{
public:
	inline TEikServCtrlFactories();
	inline TEikServCtrlFactories(MEikServNotifyAlert* aAlert,MEikServAlarmFactory* aAlarmAlert);
public:
	MEikServNotifyAlert* iAlert;
	MEikServAlarmFactory* iAlarmAlert; // does not own anything
private:
	TInt iTEikServCtrlFactories_Reserved1;
	};

class MEikServAppUiSessionFactory
/**
@publishedPartner 
@released 
*/
	{
public:
	virtual CEikServAppUiSession* CreateSessionL() = 0;
protected:
	IMPORT_C MEikServAppUiSessionFactory();
private:
	IMPORT_C virtual void MEikServAppUiSessionFactory_Reserved1();
	IMPORT_C virtual void MEikServAppUiSessionFactory_Reserved2();
private:
	TInt iMEikServAppUiSessionFactory_Reserved1;
	};

NONSHARABLE_CLASS(CEikServEnv) : public CEikonEnv
/**
@publishedPartner 
@released 
*/
	{
public:
	IMPORT_C CEikServEnv();
	IMPORT_C ~CEikServEnv();
	IMPORT_C void DestroyEnvironment();
public:
	IMPORT_C void SetEikServAppUiSessionFactory(MEikServAppUiSessionFactory* aSessionFactory);
	IMPORT_C MEikServAppUiSessionFactory* EikServAppUiSessionFactory() const;
	IMPORT_C TBool IsTaskListEnabled() const;
	IMPORT_C void EnableTaskList();
public:
	void SetEikServer(CEikServAppUiServer* aServer);
	IMPORT_C void SetUiDll(RLibrary& aDll);
private: // reserved virtuals. do not override!
	IMPORT_C virtual void CEikServEnv_Reserved1();
	IMPORT_C virtual void CEikServEnv_Reserved2();
	IMPORT_C virtual void CEikServEnv_Reserved3();
	IMPORT_C virtual void CEikServEnv_Reserved4();
	IMPORT_C virtual void CEikServEnv_Reserved5();
	IMPORT_C virtual void CEikServEnv_Reserved6();
private: // from CCoeEnv. do not override!
	IMPORT_C void Reserved_1();
	IMPORT_C void Reserved_2();
private:
	RLibrary iUiDll;
	CEikServAppUiServer* iServer;
	MEikServAppUiSessionFactory* iSessionFactory;
	TBool iIsTaskListEnabled;
	TInt iCEikServEnv_Reserved1;
	};

inline TEikServCtrlFactories::TEikServCtrlFactories()
	: iAlert(NULL), iAlarmAlert(NULL)
	{}
	
inline TEikServCtrlFactories::TEikServCtrlFactories(MEikServNotifyAlert* aAlert,MEikServAlarmFactory* aAlarmAlert)
	: iAlert(aAlert), iAlarmAlert(aAlarmAlert)
	{}

NONSHARABLE_CLASS(CEikServSecureData) : public CBase
/**
@publishedPartner 
@released 
*/
	{
public:
	IMPORT_C static void GetInstalledFepNameL(TDes& aName);
	IMPORT_C static void SetInstalledFepNameL(const TDesC& aName, TBool aRaiseFileError);
	IMPORT_C static void OpenFepAttributesL();
	IMPORT_C static void GetFepAttributeL(TUid aAttribUid, TDes8& aAttribData);
	IMPORT_C static void SetFepAttributeL(TUid aAttribUid, const TDesC8& aAttribData);
	IMPORT_C static void CommitFepAttributesL();
	IMPORT_C static void CloseFepAttributes();
	IMPORT_C static CBufBase* GetBufferedSystemColorListL();
	IMPORT_C static void SetBufferedSystemColorListL(const TDesC8& aBuffer);
private:
	CEikServSecureData();
	};

class TErrorFlagAndId
	{
public:
	TInt iTextId;
	TUint iFlags;
	TBool iIsMemoryAllocatedByErrResolver;
	};

#endif	// __EIKSRV_H__
