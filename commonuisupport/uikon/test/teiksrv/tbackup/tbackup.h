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
// Tests CBaBackupSessionWrapper APIs and observers for backup server.\n
// 
//

/**
 @file
 @internalComponent - Internal Symbian test code
*/

#ifndef		__TBACKUP_H
#define		__TBACKUP_H

#include <eikenv.h>
#include <coecntrl.h>
#include <basched.h>
#include <babackup.h>
#include <eikappui.h>
#include <eikdef.h>
#include <eikapp.h>
#include <eikdoc.h>
#include <techview/eikon.hrh>
#include <techview/eiktxlbx.h>
#include <techview/eiktxlbm.h>
#include <techview/eikchlst.h>
#include <techview/eikclb.h>
#include <techview/eikclbd.h>
#include <techview/eikdialg.h>
#include <techview/eikcapc.h>
#include <apgwgnam.h>
#include <apgtask.h>
#include <eikcoctl.rsg>
#include <techview/eikchkbx.h>
#include <eikmsg.h>
#include <techview/eikhopbt.h>
#include <uiklafgt/eikcore.rsg>
#include "appfwk_test_AppUi.h"

_LIT(KTestBackupStep, "TBackup");


//!  A CTestBackupStep test class. 
/**
 Tests CBaBackupSessionWrapper APIs.
*/
class CTestBackupStep : public CTmsTestStep
	{
public:
	CTestBackupStep();
	~CTestBackupStep();
	virtual TVerdict doTestStepL();
	void ConstructAppL(CEikonEnv* aCoe);
private:
	};


const TInt KNumOfBackupOperationObservers = 3;
class CBackupAppUi;
class CBackupRunTest;

//!  CBackupDialogBase - dialog base class. 
/**
 Forms the dialog base class.
*/
class CBackupDialogBase : public CEikDialog
	{
public:
	enum TOperationGranularity
		{
		EAll,
		ESingleFile
		};
protected:
	CBackupDialogBase(CDesCArray& aFiles,TOperationGranularity& aGranularity,TDes& aFileName);
protected: // from CEikDialog
	void PreLayoutDynInitL();
	TBool OkToExitL(TInt aButtonId);
	void HandleControlStateChangeL(TInt aControlId);
private:
	void UpdateFileListDimmedState();
protected:
	CDesCArray& iFiles;
	TOperationGranularity& iGranularity;
	TDes& iFileName;
	};


//!  CBackupCloseDialog - close dialog class. 
/**
 Creates the close backup dialog class.
*/
class CBackupCloseDialog : public CBackupDialogBase
	{
public:
	static TBool RunDlgLD(CDesCArray& aFiles,CBackupDialogBase::TOperationGranularity& aGranularity,TDes& aFileName,
							MBackupObserver::TFileLockFlags& aFlag);
	
private:
	CBackupCloseDialog(CDesCArray& aFiles,CBackupDialogBase::TOperationGranularity& aGranularity,TDes& aFileName,
							MBackupObserver::TFileLockFlags& aFlag);
private: // from CEikDialog
	void PreLayoutDynInitL();
	TBool OkToExitL(TInt aButtonId);
private:
	MBackupObserver::TFileLockFlags& iFileFlag;
	};



//!  CBackupRestartDialog - restart dialog class. 
/**
 Creates the restart backup dialog class.
*/
class CBackupRestartDialog : public CBackupDialogBase
	{
public:
	static TBool RunDlgLD(CDesCArray& aFiles,CBackupDialogBase::TOperationGranularity& aGranularity,TDes& aFileName);
private:
	CBackupRestartDialog(CDesCArray& aFiles,CBackupDialogBase::TOperationGranularity& aGranularity,TDes& aFileName);
private: // from CEikDialog
	void PreLayoutDynInitL();
	};



//!  CBackupFileObserver - file observer class. 
/**
 File observer class.
*/
class CBackupFileObserver : public CBase, private MBackupObserver
	{
public:
	enum TFileLock
		{ELocked,EReadOnly,ENoAccess};
	class TBackupFile
		{
	public:
		TBackupFile(const TDesC& aFileName,TFileLock aLockState);
	public:
		TFileName iFileName;
		TFileLock iLockState;
		};
public:
	static CBackupFileObserver* NewLC();
	~CBackupFileObserver();
	void AddFileL(const TDesC& aFileName);
	void RemoveFile(const TDesC& aFileName);
	const RArray<TBackupFile>& BackupArray() const;
private:
	CBackupFileObserver();
	void ConstructL();
	TInt Find(const TDesC& aFileName) const;
private: // from MBackupObserver
	void ChangeFileLockL(const TDesC& aFileName,TFileLockFlags aFlags);
private:
	RArray<TBackupFile> iBackupArray;
	CBaBackupSessionWrapper* iBackupSession;
	};


//!  CBackupOpeartionObserver - backup observer. 
/**
 Observer for backup operation.
*/
class CBackupOpeartionObserver : public CBase, public MBackupOperationObserver
	{
public:
	static CBackupOpeartionObserver* NewL();
	inline TBool IsRegistered() const;
	inline void SetRegistered(TBool aIsRegistered);
private:
	CBackupOpeartionObserver();
private: // from MBackupOperationObserver
	void HandleBackupOperationEventL(const TBackupOperationAttributes& aBackupOperationAttributes);
private:
	TBool iRegistered;
	TBackupOperationAttributes iBackupOperationAttributes;
	};

//!  CBackupOpeartionObserversWrapper. 
/**
 Wrapper for backup operation observer.
*/

class CBackupOpeartionObserversWrapper : public CBase
	{
public:
	static CBackupOpeartionObserversWrapper* NewL(TInt aNumberOfObservers);
	~CBackupOpeartionObserversWrapper();
	void RegisterBackupOperationObserverL(CBackupOpeartionObserver& aBackupOpeartionObserver);
	void DeRegisterBackupOperationObserver(CBackupOpeartionObserver& aBackupOpeartionObserver);
	inline TInt CountObservers() const;
	inline CBackupOpeartionObserver* Observer(TInt aIndex);
private:
	CBackupOpeartionObserversWrapper();
	void ConstructL(TInt aNumberOfObservers);
	void ResetAndDestroy();
private:
	CBaBackupSessionWrapper* iBackupSession;
	RPointerArray<CBackupOpeartionObserver> iBackupOpeartionObserver;
	};



//!  CBackupRegistrationDialog. 
/**
 Dialog for registration of observer.
*/
class CBackupRegistrationDialog : public CEikDialog
	{
public:
	CBackupRegistrationDialog(RPointerArray<CBackupOpeartionObserversWrapper>& aBackupOperationObserversWrapper);
	TBool OkToExitL(TInt aButtonId);
private: // from CEikDialog
	void PreLayoutDynInitL();
private:
	RPointerArray<CBackupOpeartionObserversWrapper>& iBackupOperationObserversWrapper;
	CBackupAppUi* iBackupAppUi;
	};


//!  CBackupOperationDialog. 
/**
 Dialog for starting backup operation.
*/
class CBackupOperationDialog : public CEikDialog
	{
public:
	CBackupOperationDialog(CBaBackupSessionWrapper& aBackupSession);
	TBool OkToExitL(TInt aButtonId);
private: // from CEikDialog
	void PreLayoutDynInitL();
	
private:
	CBaBackupSessionWrapper& iBackupSession;
	CBackupAppUi* iBackupAppUi;
	};


//!  CBackdrop. 
/**
 Background control.
*/
class CBackdrop : public CCoeControl
	{
public:
	static CBackdrop* NewL();
private: // from CCoeControl
	void Draw(const TRect& aRect) const;
	};


//!  COpenAppList. 
/**
 Control to list open apps.
*/
class COpenAppList : public CEikTextListBox
	{
public:
	void UpdateL();
	};


//!  COpenFileList. 
/**
 Control to list open files.
*/
class COpenFileList : public CCoeControl
	{
public:
	COpenFileList(CArrayPtr<CBackupFileObserver>& aFileObservers);
	~COpenFileList();
	void ConstructL();
	void UpdateL();
private: // from CCoeControl
	TSize MinimumSize();
	void SizeChanged();
	TInt CountComponentControls() const;
	CCoeControl* ComponentControl(TInt aIndex) const;
private:
	CEikColumnListBox* iList;
	const CArrayPtr<CBackupFileObserver>& iFileObservers;
	};

//!  CTBackupAppUi. 
/**
 Test Ui class.
*/
class CTBackupAppUi : public CTestAppUi
	{
public:
	CTBackupAppUi(CTmsTestStep* aStep);
	void ConstructL();
	~CTBackupAppUi();
	void RunTestStepL(TInt aNextStep);
	
private: // framework
	void HandleCommandL(TInt aCommand);

private:
	void CreateBackgroundL();
	void CreateAppListL();
	void CreateFileListL();
	void CreateFileObserversL();
	void CmdListAppsL();
	void CmdListOpenFilesL();
	void CmdCloseL();
	void CmdRestartL();
	void AutoCmdCloseL();
	void AutoCmdRestartL();
	void CreateObserversListL();
	void UpdateBackupObserverRegistrationL();
	void UpdateBackupOperationStateL();
	void AutoUpdateBackupObserverRegistrationL();
	void AutoUpdateBackupOperationStateL();
	void AutoCmdCloseAllAndRestartAllL();
	

private:
	CBaBackupSessionWrapper* iBackupSession;
	CBackdrop* iBackdrop;
	COpenAppList* iAppList;
	COpenFileList* iFileList;
	CArrayPtr<CBackupFileObserver>* iFileObservers;
	RPointerArray<CBackupOpeartionObserversWrapper> iBackupOperationObserversWrapper;
	CEikBusyMsgWin* iBusyMsg;
	};


//!  CBackupDocument. 
/*!
 Test Document class.
*/
class CBackupDocument : public CEikDocument
	{
public: // from CApaDocument
	CBackupDocument(CEikApplication& aApp);
	CEikAppUi* CreateAppUiL();
	};


//!  CBackupApplication. 
/**
 Test Application class.
*/
class CBackupApplication: public CEikApplication
	{
private: // from CApaApplication
	CApaDocument* CreateDocumentL();
	TUid AppDllUid() const;
private:
	CApaDocument* CreateDocumentL(CApaProcess* a) { return CEikApplication::CreateDocumentL(a); }

	};

#endif


