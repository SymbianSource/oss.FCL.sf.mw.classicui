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
// Tests CBaBackupSessionWrapper APIs and observers for backup server.
// 
//

/**
 @file
 @test
 @internalComponent - Internal Symbian test code
*/
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
#include <apgcli.h>
#include <eikcoctl.rsg>
#include <techview/eikchkbx.h>
#include <eikmsg.h>
#include <techview/eikhopbt.h>
#include <uiklafgt/eikcore.rsg>
#include <ecom/ecom.h>


#include "tbackup.hrh"
#include <tbackup.rsg>


#include "tbackup.h"

_LIT(KBackupFile1,"foo1");
_LIT(KBackupFile2,"foo2");
_LIT(KBackupFile3,"foo3");
_LIT(KObserverStr, "Observer %d:");
_LIT(KBackupOpMsg, "Backup Operation running");
_LIT(KRegistrationDlgTitle, "Register and DeRegister Observers");

_LIT(KTBackupResourceFilePath, "z:\\system\\test\\tbackup\\tbackup.rsc");



/**********************************************
 
 
 
 	CBackupDialogBase
 
 
 
************************************************/
CBackupDialogBase::CBackupDialogBase(CDesCArray& aFiles,TOperationGranularity& aGranularity,TDes& aFileName)
	: iFiles(aFiles), iGranularity(aGranularity), iFileName(aFileName)
/**
   Constructor
 */
	{}


/**
   Auxiliary Function for all Test Cases
  
   This method is an override from CEikDialog.It performs pre-layout dialog
   initialisation.
  
 */
void CBackupDialogBase::PreLayoutDynInitL()
	{
	SetHorOptionButListCurrentSet(EDlgBackupCloseOpButList,EDlgBackupCloseAll);
	CEikChoiceList* list=static_cast<CEikChoiceList*>(Control(EDlgBackupFileList));
	list->SetArrayExternalOwnership(ETrue);
	list->SetArrayL(&iFiles);
	UpdateFileListDimmedState();
	}


/**
   Auxiliary Function for all Test Cases
  
   This method is an override from CEikDialog. Handles dialog button press 'All'
   and 'File' to select a single file or all files to be closed by the dialog.
  
 */
TBool CBackupDialogBase::OkToExitL(TInt /*aButtonId*/)
	{
	if (HorOptionButListCurrentSet(EDlgBackupCloseOpButList)==EDlgBackupCloseAll)
		{
		iGranularity=EAll;
		}
	else
		{
		iGranularity=ESingleFile;
		const CEikChoiceList* list=static_cast<CEikChoiceList*>(Control(EDlgBackupFileList));
		iFileName=iFiles[list->CurrentItem()];
		}
	return ETrue;
	}

/**
   Auxiliary Function for all Test Cases
  
   This method is an override from CEikDialog. This function is called when a
   control event of type EEventStateChanged is received by the dialog from one
   of its component controls. 
  
 */
void CBackupDialogBase::HandleControlStateChangeL(TInt aControlId)
	{
	if (aControlId==EDlgBackupCloseOpButList)
		{
		UpdateFileListDimmedState();
		}
	}

/**
   Auxiliary Function for all Test Cases
  
   This method is an override from CEikDialog. This method dims and deactivates
   the file choice list on the dialog.
  
 */
void CBackupDialogBase::UpdateFileListDimmedState()
	{
	const TBool dimFileList=(HorOptionButListCurrentSet(EDlgBackupCloseOpButList)==EDlgBackupCloseAll);
	const CEikChoiceList* list=static_cast<CEikChoiceList*>(Control(EDlgBackupFileList));
	const TBool fileListDimmed=list->IsDimmed();
	if (dimFileList!=fileListDimmed)
		{
		SetLineDimmedNow(EDlgBackupFileList,dimFileList);
		}
	}


/**********************************************
 
 
 
 	CBackupCloseDialog
 
 
 
************************************************/

/**
  Auxiliary function for TestCaseID tbackup-CmdCloseL
  
  This method initialises and launches the backup close dialog.
  
 */
TBool CBackupCloseDialog::RunDlgLD(CDesCArray& aFiles,CBackupDialogBase::TOperationGranularity& aGranularity,
										TDes& aFileName,MBackupObserver::TFileLockFlags& aFlag)
	{ // static
	CBackupCloseDialog* dlg=new(ELeave) CBackupCloseDialog(aFiles,aGranularity,aFileName,aFlag);
	return dlg->ExecuteLD(R_TBACKUP_FILE_OPTIONS);
	}

CBackupCloseDialog::CBackupCloseDialog(CDesCArray& aFiles,CBackupDialogBase::TOperationGranularity& aGranularity,
										TDes& aFileName,MBackupObserver::TFileLockFlags& aFlag)
	: CBackupDialogBase(aFiles,aGranularity,aFileName), iFileFlag(aFlag)
/**
   Constructor
 */
	{
	}
/**
   Auxiliary function for TestCaseID tbackup-CmdCloseL
  
   This method is an override from CEikDialog.It performs pre-layout dialog
   initialisation.
  
 */
void CBackupCloseDialog::PreLayoutDynInitL()
	{
	SetHorOptionButListCurrentSet(EDlgBackupFlagOpButList,EDlgBackupReadOnly);
	CBackupDialogBase::PreLayoutDynInitL();
	}

/**
   Auxiliary function for TestCaseID tbackup-CmdCloseL
  
   This method is an override from CEikDialog. It is used to specify 'Read only' or
   'No access' file locks while CloseAll() & CloseFileL() APIs are invoked.
  
 */
TBool CBackupCloseDialog::OkToExitL(TInt aButtonId)
	{
	if (HorOptionButListCurrentSet(EDlgBackupFlagOpButList)==EDlgBackupReadOnly)
		{
		iFileFlag=MBackupObserver::EReleaseLockReadOnly;
		}
	else
		{
		iFileFlag=MBackupObserver::EReleaseLockNoAccess;
		}
	return CBackupDialogBase::OkToExitL(aButtonId);
	}


/**********************************************

 
 
 	CBackupRestartDialog
 
 
 
************************************************/

/**
   Auxiliary function for TestCaseID tbackup-CmdRestartL
  
   This method initialises and launches the backup restart dialog.
  
 */
TBool CBackupRestartDialog::RunDlgLD(CDesCArray& aFiles,CBackupDialogBase::TOperationGranularity& aGranularity,
										TDes& aFileName)
	{ // static
	CBackupRestartDialog* dlg=new(ELeave) CBackupRestartDialog(aFiles,aGranularity,aFileName);
	return dlg->ExecuteLD(R_TBACKUP_FILE_OPTIONS);
	}

CBackupRestartDialog::CBackupRestartDialog(CDesCArray& aFiles,CBackupDialogBase::TOperationGranularity& aGranularity,
											TDes& aFileName)
	: CBackupDialogBase(aFiles,aGranularity,aFileName)
/**
   Constructor
 */
	{}

/**
   Auxiliary function for TestCaseID tbackup-CmdRestartL
  
   This method is an override from CEikDialog.It performs pre-layout dialog
   initialisation.
  
 */
void CBackupRestartDialog::PreLayoutDynInitL()
	{
	SetTitleL(R_TBACKUP_RESTART_DLG_TITLE);
	TBuf<20> text;
	iCoeEnv->ReadResource(text,R_TBACKUP_RESTART_OPTION_TITLE);
	CEikLabel* caption=Line(EDlgBackupCloseOpButList)->iCaption;
	caption->SetTextL(text);
	DeleteLine(EDlgBackupFlagOpButList);
	CBackupDialogBase::PreLayoutDynInitL();
	}



/**********************************************
 
 
 
 	CBackupFileObserver
 
 
 
************************************************/
CBackupFileObserver::TBackupFile::TBackupFile(const TDesC& aFileName,TFileLock aLockState)
	: iFileName(aFileName), iLockState(aLockState)
/**
   Constructor
 */
	{}

/**
   Auxiliary function for all test cases
  
   This method is part of two-phase construction of CBackupFileObserver.The
   method is called by CTBackupAppUi::CreateFileObserversL() to construct new
   client to backup server.
  
 */
CBackupFileObserver* CBackupFileObserver::NewLC()
	{ // static
	CBackupFileObserver* self=new(ELeave) CBackupFileObserver();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CBackupFileObserver::~CBackupFileObserver()
/**
   Destructor
 */
	{
	const TInt count=iBackupArray.Count();
	for (TInt ii=count-1;ii>=0;ii--)
		{
		const TBackupFile& backup=iBackupArray[ii];
		RemoveFile(backup.iFileName);
		}
	iBackupArray.Close();
	delete iBackupSession;
	}

struct SFileAddCleanup
	{
	CBackupFileObserver* iFileObserver;
	TFileName iFileName;
	};

/**
   Auxiliary function for all Test Cases
   
   This method is cleanup operation invoked by the pop and destroy action
   resulting from a subsequent call to CleanupStack::PopAndDestroy() to
   perform clean up of SFileAddCleanup object.
   
 */
LOCAL_C void CleanupAddFile(TAny* aPtr)
	{
	SFileAddCleanup* cleanup=REINTERPRET_CAST(SFileAddCleanup*,aPtr);
	cleanup->iFileObserver->RemoveFile(cleanup->iFileName);
	}

/**
   Auxiliary function for all Test Cases
   
   This method registers a file with the backup server.
   
 */
void CBackupFileObserver::AddFileL(const TDesC& aFileName)
	{
	TBackupFile backup(aFileName,ELocked);
	User::LeaveIfError(iBackupArray.Append(backup));
	SFileAddCleanup cleanup;
	cleanup.iFileObserver=this;
	cleanup.iFileName=aFileName;
	CleanupStack::PushL(TCleanupItem(CleanupAddFile,&cleanup));
	iBackupSession->RegisterFileL(aFileName,*this);
	CleanupStack::Pop(); // CleanupAddFile
	}

/**
   Auxiliary function for all Test Cases
   
   This method is invoked by cleanup method CleanupAddFile() to remove the
   registration of a file with the backup server.
   
 */
void CBackupFileObserver::RemoveFile(const TDesC& aFileName)
	{
	const TInt index=Find(aFileName);
	if (index!=KErrNotFound)
		{
		iBackupSession->DeregisterFile(aFileName);
		iBackupArray.Remove(index);
		iBackupArray.Compress();
		}
	}

/**
   Auxiliary function for all Test Cases
   
   This method returns the array iBackupArray which holds the list of files
   registered with the observer.
   
 */
const RArray<CBackupFileObserver::TBackupFile>& CBackupFileObserver::BackupArray() const
	{
	return iBackupArray;
	}

CBackupFileObserver::CBackupFileObserver()
/**
   Constructor
 */
	{}

/**
   Auxiliary function for all test cases
  
   This method is part of Two-phase construction of CBackupFileObserver.The
   method constructs a new client to the backup server .
  
 */
void CBackupFileObserver::ConstructL()
	{
	iBackupSession=CBaBackupSessionWrapper::NewL();
	}

/**
   Auxiliary function for all Test Cases
   
   This method attempts to find the file specifed within the iBackupArray
   and returns its index within the array if found. Otherwise KErrNotFound is
   returned.
   
 */
TInt CBackupFileObserver::Find(const TDesC& aFileName) const
	{
	TInt index=KErrNotFound;
	const TInt count=iBackupArray.Count();
	for (TInt ii=0;ii<count;ii++)
		{
		const TBackupFile& backup=iBackupArray[ii];
		if (backup.iFileName==aFileName)
			{
			index=ii;
			break;
			}
		}
	return index;
	}

/**
   Auxiliary function for all Test Cases
   
   This method finds the file specifed within the iBackupArray and changes its
   file lock as specified by aFlag parameter.
   
 */
void CBackupFileObserver::ChangeFileLockL(const TDesC& aFileName,TFileLockFlags aFlags)
	{
	const TInt index=Find(aFileName);
	if (index==KErrNotFound)
		{
		User::Invariant();
		}
	iBackupArray[index].iLockState=(CBackupFileObserver::TFileLock)aFlags;
	}


/**********************************************
 
 
  	CBackupOpeartionObserver
 
 
************************************************/

/**
   Auxiliary function for all Test cases
   
   This method returns ETrue if the observer is registered with the backup
   server.
  
 */
inline TBool CBackupOpeartionObserver::IsRegistered() const
	{
	return iRegistered;
	}

/**
   Auxiliary function for TestCaseID tbackup-AutoUpdateBackupObserverRegistrationL
  
   The method sets the observer as registered with the back up server.
  
 */
inline void CBackupOpeartionObserver::SetRegistered(TBool aIsRegistered)
	{
	iRegistered = aIsRegistered;
	}

/**
   Auxiliary function for all Test cases
   
   This method creates an observer for backup operation.
  
 */
CBackupOpeartionObserver* CBackupOpeartionObserver::NewL()
	{
	CBackupOpeartionObserver* self=new(ELeave) CBackupOpeartionObserver();
	return self;
	}

CBackupOpeartionObserver::CBackupOpeartionObserver()
/**
   Constructor
 */
	{
	}

/**
   Auxiliary function for TestCaseID tbackup-AutoUpdateBackupOperationStateL
  
   This method is an override from MBackupOperationObserver and is invoked when a
   backup or restore operation either starts or ends.
  
 */
void CBackupOpeartionObserver::HandleBackupOperationEventL(const TBackupOperationAttributes& aBackupOperationAttributes)
	{
	MBackupOperationObserver::TOperationType operation = aBackupOperationAttributes.iOperation;
	switch (operation)
		{
		case MBackupOperationObserver::EStart:
			User::InfoPrint(_L("Backup Operation Start"));
			break;
		case MBackupOperationObserver::EEnd:
			User::InfoPrint(_L("Backup Operation End"));
			break;
		case MBackupOperationObserver::EAbort:
			User::InfoPrint(_L("Backup Operation Abort"));
			break;
		case MBackupOperationObserver::ENone:
		default:
			break;
		}
	iBackupOperationAttributes = aBackupOperationAttributes;
	}



/**********************************************
 
 
 
 	CBackupOpeartionObserversWrapper
 
 
 
************************************************/


/**
   Auxiliary function for TestCaseID tbackup-AutoUpdateBackupObserverRegistrationL
  
   This method returns the number of backup observer object pointers stored in
   the pointer array iBackupOpeartionObserver.
  
 */
inline TInt CBackupOpeartionObserversWrapper::CountObservers() const
	{
	return iBackupOpeartionObserver.Count();
	}


/**
   Auxiliary function for TestCaseID tbackup-AutoUpdateBackupObserverRegistrationL
  
   This method returns the backup operation observer handle specified by
   aIndex from pointer array iBackupOpeartionObserver.
  
 */
inline CBackupOpeartionObserver* CBackupOpeartionObserversWrapper::Observer(TInt aIndex)
	{
	return iBackupOpeartionObserver[aIndex];
	}


/**
   Auxiliary function for all Test Cases
  
   This method creates a wrapper for backup operation observers. The wrapper
   would contains number of observers as indicated by parameter
   aNumberOfObservers.
  
 */
CBackupOpeartionObserversWrapper* CBackupOpeartionObserversWrapper::NewL(TInt aNumberOfObservers)
	{
	CBackupOpeartionObserversWrapper* self=new(ELeave) CBackupOpeartionObserversWrapper();
	CleanupStack::PushL(self);
	self->ConstructL(aNumberOfObservers);
	CleanupStack::Pop(self);
	return self;
	}

CBackupOpeartionObserversWrapper::~CBackupOpeartionObserversWrapper()
/**
   Destructor
 */
	{
	ResetAndDestroy();
	iBackupOpeartionObserver.Close();
	delete iBackupSession;
	}

CBackupOpeartionObserversWrapper::CBackupOpeartionObserversWrapper()
/**
   Constructor
 */
	{
	}

/**
   Auxiliary function for all Test Cases
  
   This method creates 'aNumberOfObservers' of backup operation observers for
   the wrapper.
  
 */
void CBackupOpeartionObserversWrapper::ConstructL(TInt aNumberOfObservers)
	{
	iBackupSession=CBaBackupSessionWrapper::NewL();
	for (TInt counter=0; counter<aNumberOfObservers; ++counter)
		{
		User::LeaveIfError(iBackupOpeartionObserver.Append(CBackupOpeartionObserver::NewL()));
		}
	}

/**
   Auxiliary function for TestCaseID tbackup-AutoUpdateBackupObserverRegistrationL
  
   The method registers the specified observer for notifications when a backup
   operation starts or ends and sets the observer as registered by calling
   CBackupOpeartionObserver::SetRegistered().
  
 */
void CBackupOpeartionObserversWrapper::RegisterBackupOperationObserverL(CBackupOpeartionObserver& aBackupOpeartionObserver)
	{
	iBackupSession->RegisterBackupOperationObserverL(aBackupOpeartionObserver);
	aBackupOpeartionObserver.SetRegistered(ETrue);
	}

/**
   Auxiliary function for all Test Cases
  
   The method de-registers the specified backup/restore observer and resets the
   iRegister flag of observer by calling
   CBackupOpeartionObserver::SetRegistered(). The method is invoked by
   CBackupOpeartionObserversWrapper::ResetAndDestroy() during destruction.
  
 */
void CBackupOpeartionObserversWrapper::DeRegisterBackupOperationObserver(CBackupOpeartionObserver& aBackupOpeartionObserver)
	{
	iBackupSession->DeRegisterBackupOperationObserver(aBackupOpeartionObserver);
	aBackupOpeartionObserver.SetRegistered(EFalse);
	}

/**
   Auxiliary function for all Test Cases
  
   This method is invoked by destructor to deregister all backup observers
   present in the wrapper. 
  
 */
void CBackupOpeartionObserversWrapper::ResetAndDestroy()
	{
	const TInt count = iBackupOpeartionObserver.Count();
	for (TInt index=0; index<count; ++index)
		{
		iBackupSession->DeRegisterBackupOperationObserver(*iBackupOpeartionObserver[index]);
		}
	iBackupOpeartionObserver.ResetAndDestroy();
	iBackupOpeartionObserver.Close();
	}

/**********************************************
 
 
 
 	CBackupRegistrationDialog
 
 
 
************************************************/

CBackupRegistrationDialog::CBackupRegistrationDialog(RPointerArray<CBackupOpeartionObserversWrapper>& aBackupOperationObserversWrapper)
	: iBackupOperationObserversWrapper(aBackupOperationObserversWrapper)
/**
   Constructor
 */
	{
	}

/**
   Auxiliary Function tbackup-UpdateBackupObserverRegistrationL
  
   This method is an override from CEikDialog.It performs pre-layout dialog
   initialisation. The method finds whether all observers for each observer
   wrapper are registered and the state of each is displayed as a checkbox
   on the dialog.
  
 */
void CBackupRegistrationDialog::PreLayoutDynInitL()
	{
	const TInt count = iBackupOperationObserversWrapper.Count();
	CBackupOpeartionObserversWrapper* observerWrapper = NULL;
	TInt previousCount = 0;
	for (TInt index1=0; index1<count; ++index1)
		{
		observerWrapper = iBackupOperationObserversWrapper[index1];
		const TInt count2 = observerWrapper->CountObservers();
		for (TInt index2=0; index2<count2; ++index2)
			{
			CBackupOpeartionObserver* observer = observerWrapper->Observer(index2);
			const TInt realIndex = previousCount+index2;
			CEikCheckBox* checkBox = (CEikCheckBox*)Control(EObserversId+realIndex);
			checkBox->SetState(observer->IsRegistered() ? CEikButtonBase::ESet : CEikButtonBase::EClear);
			}
		previousCount += count2;
		}
	}

/**
   Auxiliary function for TestCaseID tbackup-UpdateBackupObserverRegistrationL
  
   This method is an override from CEikDialog. On click of OK button this
   method checks whether the check boxes that represent observers in each
   wrapper is set or reset and registers or deregisters the backup observer.
  
 */
TBool CBackupRegistrationDialog::OkToExitL(TInt aButtonId)
	{
	if (aButtonId==EEikBidOk)
		{
		const TInt count = iBackupOperationObserversWrapper.Count();
		CBackupOpeartionObserversWrapper* observerWrapper = NULL;
		TInt previousCount = 0;
		for (TInt index1=0; index1<count; ++index1)
			{
			observerWrapper = iBackupOperationObserversWrapper[index1];
			const TInt count2 = observerWrapper->CountObservers();
			for (TInt index2=0; index2<count2; ++index2)
				{
				CBackupOpeartionObserver* observer = observerWrapper->Observer(index2);
				const TInt realIndex = previousCount+index2;
				CEikCheckBox* checkBox = (CEikCheckBox*)Control(EObserversId+realIndex);
				
				const TBool stateSet = (checkBox->State()==CEikButtonBase::ESet);
				const TBool previousState = observer->IsRegistered();
				const TBool stateChanged = (!stateSet)!=(!previousState);
				if (stateChanged)
					{
					if (stateSet)
						{
						observerWrapper->RegisterBackupOperationObserverL(*observer);
						}
					else
						{
						observerWrapper->DeRegisterBackupOperationObserver(*observer);
						}
					}
				}
			previousCount += count2;
			}
		}
	return ETrue;
	}


/**********************************************
 
 
 
 	CBackupOperationDialog
 
 
 
************************************************/
CBackupOperationDialog::CBackupOperationDialog(CBaBackupSessionWrapper& aBackupSession)
	:iBackupSession(aBackupSession)
/**
   Constructor
 */
	{}

/**
   Auxiliary function for TestCaseID tbackup-UpdateBackupOperationStateL
  
   This method is an override from CEikDialog.It performs pre-layout dialog
   initialisation. The method invokes 
   CBaBackupSessionWrapper::IsBackupOperationRunning() to find whether backup
   operation is in running and accordingly sets 'Start' & 'End' option buttons.
  
 */
void CBackupOperationDialog::PreLayoutDynInitL()
	{
	CEikHorOptionButtonList* optionButtonList = (CEikHorOptionButtonList*)Control(EDlgBackupOperationSel);
	const TBool isRunning = iBackupSession.IsBackupOperationRunning();
	optionButtonList->SetButtonById(isRunning ? EDlgBackupOperationSel1 : EDlgBackupOperationSel2);
	}

/**
   Auxiliary function for TestCaseID tbackup-UpdateBackupOperationStateL
  
   This method is an override from CEikDialog. On click of OK button this
   method checks the state of option buttons labeled 'Start' & 'End'
   and accordingly starts / ends the backup operation by calling
   CBaBackupSessionWrapper::NotifyBackupOperationL().
  
 */
TBool CBackupOperationDialog::OkToExitL(TInt aButtonId)
	{
	if (aButtonId==EEikBidOk)
		{
		CEikHorOptionButtonList* optionButtonList = (CEikHorOptionButtonList*)Control(EDlgBackupOperationSel);
		const TInt labeledButtonId = optionButtonList->LabeledButtonId();
		TBackupOperationAttributes backupOperationAttributes;
		switch (labeledButtonId)
			{
		case EDlgBackupOperationSel1:
			{
			backupOperationAttributes.iFileFlag = MBackupObserver::EReleaseLockReadOnly;
			backupOperationAttributes.iOperation = MBackupOperationObserver::EStart;
			break;
			}
		case EDlgBackupOperationSel2:
			{
			backupOperationAttributes.iFileFlag = MBackupObserver::ETakeLock;
			backupOperationAttributes.iOperation = MBackupOperationObserver::EEnd;
			break;
			}
		default:
			return EFalse;
			}
		iBackupSession.NotifyBackupOperationL(backupOperationAttributes);
		}
	return ETrue;
	}


/**********************************************
 
 
 
 	CBackdrop
 
 
 
************************************************/


/**
   Auxiliary function for all Test Cases
  
   This method is part of Two - phase construction. It creates the background
   control.
  
 */
CBackdrop* CBackdrop::NewL()
	{ // static
	CBackdrop* self=new(ELeave) CBackdrop();
	CleanupStack::PushL(self);
	self->CreateWindowL();
	CleanupStack::Pop(); // self
	return self;
	}
/**
   Auxiliary function for all Test Cases
  
   This method is an override from CCoeControl. It draws the background
   control.
  
 */
void CBackdrop::Draw(const TRect& aRect) const
	{
	CWindowGc& gc=SystemGc();
	gc.SetPenStyle(CGraphicsContext::ESolidPen);
	gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
	gc.SetPenColor(KRgbGreen);
	gc.SetBrushColor(KRgbGreen);
	gc.DrawRect(aRect);
	}


/**********************************************
 
 
 
 	COpenAppList
 
 
 
************************************************/

/**
   Auxiliary function for TestCaseID tbackup-CmdListAppsL
  
   This method creates a client session with the windows server and retrieves
   the window group list currently available. The caption or the thread id for
   each of window groups from the list is obtained and added to the list box.
  
 */
void COpenAppList::UpdateL()
	{
	RWsSession& wsSession=iEikonEnv->WsSession();
	TInt count=wsSession.NumWindowGroups(0);
	if (!count)
		return;
	CDesCArray* tasks=new(ELeave) CDesCArrayFlat(count);
	CleanupStack::PushL(tasks);
	CArrayFixFlat<TInt>* wgIds=new(ELeave) CArrayFixFlat<TInt>(count);
	CleanupStack::PushL(wgIds);
	CApaWindowGroupName* wgName=CApaWindowGroupName::NewLC(wsSession);
	wsSession.WindowGroupList(0,wgIds);
	TBuf<2*KMaxFileName+1> name;
	const TInt wgCount=wgIds->Count();
	for (TInt ii=0;ii<wgCount;ii++)
		{ 
		const TInt wgId=(*wgIds)[ii];
		wgName->ConstructFromWgIdL(wgId);
		TPtrC caption=wgName->Caption();
		if(wgName->Hidden())
			{
			continue;
			}
		else if (caption.Length()==0) // not set yet - use thread name instead
			{
			TThreadId threadId;
			TInt err=wsSession.GetWindowGroupClientThreadId(wgId,threadId);
			if (err==KErrNone)
				{
				RThread thread;
				err=thread.Open(threadId);
				if (err==KErrNone)
					{
					name.Copy(thread.Name());
					thread.Close();
					}
				}
			if (err!=KErrNone)
				name.Copy(_L("???"));
			}
		else
			{
			name=caption;
			name.Append(' ');
			TFileName docName=wgName->DocName();
			name.Append(docName);
			}
		tasks->AppendL(name);
		}
	CleanupStack::PopAndDestroy(2); // wgIds, wgName
	Model()->SetItemTextArray(tasks);
	CleanupStack::Pop(); // tasks
	HandleItemAdditionL();
	}

/**********************************************
 
  
 	COpenFileList
 
 
 
************************************************/

COpenFileList::COpenFileList(CArrayPtr<CBackupFileObserver>& aFileObservers)
	: iFileObservers(aFileObservers)
/**
   Constructor
 */
	{}

COpenFileList::~COpenFileList()
/**
   Destructor
 */
	{
	delete iList;
	}

/**
   Auxiliary function for all Test Cases
  
   The method creates a Column List Box and sets the width for all the
   columns in the list box.
  
 */
void COpenFileList::ConstructL()
	{
	CreateWindowL();
	iList=new(ELeave) CEikColumnListBox();
	iList->ConstructL(this);
	CColumnListBoxData* columnData=iList->ItemDrawer()->ColumnData();
	// following assumes a know width for this control
	// bad practise but not worth writing a scalable control in this test app
	columnData->SetColumnWidthPixelL(0,20);
	columnData->SetColumnWidthPixelL(1,180);
	columnData->SetColumnWidthPixelL(2,100);
	}

/**
   Auxiliary function for TestCaseID tbackup_CmdListOpenFilesL
  
   This method lists filename and lock state of all files associated with the
   file observers.
  
 */
void COpenFileList::UpdateL()
	{
	CDesCArray* textArray=new(ELeave) CDesCArrayFlat(2);
	CleanupStack::PushL(textArray);
	TChar separator(KColumnListSeparator);
	const TInt obsCount=iFileObservers.Count();
	for (TInt ii=0;ii<obsCount;ii++)
		{
		TBuf<2> num;
		num.Num(ii);
		const RArray<CBackupFileObserver::TBackupFile>& backupArray=iFileObservers[ii]->BackupArray();
		const TInt fileCount=backupArray.Count();
		for (TInt jj=0;jj<fileCount;jj++)
			{
			TBuf<300> buf;
			buf.Append(num);
			const CBackupFileObserver::TBackupFile& backupFile=backupArray[jj];
			buf.Append(separator);
			buf.Append(backupFile.iFileName);
			buf.Append(separator);
			TBuf<20> lockState;
			if (backupFile.iLockState==CBackupFileObserver::ELocked)
				{
				iCoeEnv->ReadResource(lockState,R_TBACKUP_LOCKSTATE_LOCKED);
				}
			else if (backupFile.iLockState==CBackupFileObserver::EReadOnly)
				{
				iCoeEnv->ReadResource(lockState,R_TBACKUP_LOCKSTATE_READONLY);
				}
			else if(backupFile.iLockState==CBackupFileObserver::ENoAccess)
				{
				iCoeEnv->ReadResource(lockState,R_TBACKUP_LOCKSTATE_NOACCESS);
				}
			else
				{
				lockState=_L("???");
				}
			buf.Append(lockState);
			textArray->AppendL(buf);
			}
		}
	iList->Model()->SetItemTextArray(textArray);
	CleanupStack::Pop(); // textArray
	iList->HandleItemAdditionL();
	}

/**
   Auxiliary function for all Test Cases
  
   The method is an override from CCoeControl. It returns minimum required
   size of column list box.
  
 */
TSize COpenFileList::MinimumSize()
	{
	return iList->MinimumSize();
	}

/**
   Auxiliary function for all Test Cases
  
   The method is an override from CCoeControl. It is invoked to set the size
   and position of the content of list box control.
  
 */
void COpenFileList::SizeChanged()
	{
	const TRect rect(Rect());
	iList->SetRect(rect);
	}

/**
   Auxiliary function for all Test Cases
  
   The method is an override from CCoeControl. It returns the number of
   controls contained in the compound control COpenFileList.
  
 */
TInt COpenFileList::CountComponentControls() const
	{
	return 1;
	}

/**
   Auxiliary function for all Test Cases
  
   The method is an override from CCoeControl. It returns the handle to list
   box present on compound control COpenFileList.  
  
 */
CCoeControl* COpenFileList::ComponentControl(TInt aIndex) const
	{
	if (aIndex==0)
		{
		return iList;
		}
	return NULL;
	}


/**********************************************
 
 
 
 	CTBackupAppUi
 
 
 
************************************************/

CTBackupAppUi::CTBackupAppUi(CTmsTestStep* aStep) :
	CTestAppUi(aStep, KTBackupResourceFilePath)//,		R_TBACKUP_HOTKEYS, R_TBACKUP_MENUBAR, R_TBACKUP_TOOLBAR)
/**
   Constructor
 */
	{
	}
/**
   Auxiliary function for all Test Cases
   
   This method creates a client interface to the backup server and performs the
   following:
   (a) Creates a background control.
   (b) Creates backup observers and adds files to the observer.
   (c) Creates an Application List from window groups.
   (d) Creates a list for files attached to the observers.
   
 */
void CTBackupAppUi::ConstructL()
	{
	CTestAppUi::ConstructL();
	iEikonEnv->SetSystem(ETrue);
	iBackupSession=CBaBackupSessionWrapper::NewL();

	CreateBackgroundL();
	CreateFileObserversL();
	CreateAppListL();
	CreateFileListL();
	CreateObserversListL();
	iBusyMsg = new (ELeave) CEikBusyMsgWin(*iEikonEnv);
	iBusyMsg->ConstructL(iEikonEnv->RootWin());
	CTestAppUi::AutoTestManager().StartAutoTest();
	}

CTBackupAppUi::~CTBackupAppUi()
/**
   Destructor
 */
	{
	delete iBackdrop;
	delete iAppList;
	delete iFileList;
	if (iFileObservers)
		{
		iFileObservers->ResetAndDestroy();
		delete iFileObservers;
		}
	iBackupOperationObserversWrapper.ResetAndDestroy();
	iBackupOperationObserversWrapper.Close();
	iBusyMsg->CancelDisplay();
	delete iBusyMsg;
	delete iBackupSession;
	}

/**
   Auxiliary function for all Test Cases
  
   The method is an override from CTestAppUi. The method initiates back up
   tests.
   
 */
void CTBackupAppUi::RunTestStepL(TInt aNextStep)
	{

	switch(aNextStep)
		{
	case 1:
		INFO_PRINTF1(_L("Test: List Apps."));
		SetTestStepID(_L("UIF-tbackup-CmdListAppsL"));
		HandleCommandL(EBackupCmdListApps);
		RecordTestResultL();
		INFO_PRINTF1(_L("List Apps Completed"));
		break;
	case 2:
		INFO_PRINTF1(_L("Test: List Open Files."));
		SetTestStepID(_L("UIF-tbackup-CmdListOpenFilesL"));
		HandleCommandL(EBackupCmdListOpenFiles);
		RecordTestResultL();
		INFO_PRINTF1(_L("List Open Files Completed"));
		break;
	case 3:
		INFO_PRINTF1(_L("Test: Close Files."));
		SetTestStepID(_L("UIF-tbackup-AutoCmdCloseL"));
		HandleCommandL(EBackupCmdClose);
		RecordTestResultL();
		INFO_PRINTF1(_L("Close Files Completed"));
		break;
	case 4:
		INFO_PRINTF1(_L("Test: Restart."));
		SetTestStepID(_L("UIF-tbackup-AutoCmdRestartL"));
		HandleCommandL(EBackupCmdRestart);
		RecordTestResultL();
		INFO_PRINTF1(_L("Restart Completed"));
		break;
	case 5:
		INFO_PRINTF1(_L("Test: CloseAllAndRestartAll."));
		SetTestStepID(_L("UIF-tbackup-AutoCmdCloseAllAndRestartAllL"));
		HandleCommandL(EBackupCmdCloseAllAndRestartAll);
		RecordTestResultL();
		INFO_PRINTF1(_L("CloseAllAndRestartAll Completed"));
		break;
	case 6:
		INFO_PRINTF1(_L("Test: Register Objects."));
		SetTestStepID(_L("UIF-tbackup-AutoUpdateBackupObserverRegistrationL"));
		HandleCommandL(EBackupCmdRegisterObs);
		RecordTestResultL();
		INFO_PRINTF1(_L("Register Objects Completed."));

		INFO_PRINTF1(_L("Test: Backup Operation."));
		SetTestStepID(_L("UIF-tbackup-AutoUpdateBackupOperationStateL"));
		HandleCommandL(EBackupCmdBackupOperation);
		RecordTestResultL();
		CloseTMSGraphicsStep();
		INFO_PRINTF1(_L("Completed: Backup Operation running..."));
		User::After(TTimeIntervalMicroSeconds32(2000000));
		break;
	case 7:
		INFO_PRINTF1(_L("Test: Backup operation stop."));
		HandleCommandL(EBackupCmdDestroyBackupOperationClient);
		INFO_PRINTF1(_L("Backup operation stop completed"));
		break;
	case 8:
		INFO_PRINTF1(_L("Tests completed - End of Test."));
		CTestAppUi::AutoTestManager().FinishAllTestCases(CAutoTestManager::EPass);
		break;
	default:
		break;
		}
	}

/**
   Auxiliary function for all Test Cases
  
   This method is called by CTBackupAppUi::RunTestStepL() to initiate the
   tests.
   
 */
void CTBackupAppUi::HandleCommandL(TInt aCommand)
	{
	switch (aCommand)
		{
	case EEikCmdExit:
		Exit();
		break;
	case EBackupCmdListApps:
		CmdListAppsL();
		break;
	case EBackupCmdListOpenFiles:
		CmdListOpenFilesL();
		break;
	case EBackupCmdClose:
		AutoCmdCloseL();
		break;
	case EBackupCmdRestart:
		AutoCmdRestartL();
		break;
	case EBackupCmdCloseAllAndRestartAll:
		AutoCmdCloseAllAndRestartAllL();
		break;
	case EBackupCmdRegisterObs:
		AutoUpdateBackupObserverRegistrationL();
		break;
	case EBackupCmdBackupOperation:
		AutoUpdateBackupOperationStateL();
		break;
	case EBackupCmdDestroyBackupOperationClient:
		{
			const TBool backupOperationRunning = iBackupSession->IsBackupOperationRunning();
	
			if (backupOperationRunning)
			{
			iBusyMsg->CancelDisplay();
			}

			delete iBackupSession;
			iBackupSession = NULL;
		}
		break;
	default:
		User::Leave(KErrNotSupported);
		break;
		}
	}

/**
   Auxiliary function for all Test Cases
   
   This method creates the background control.
   
 */
void CTBackupAppUi::CreateBackgroundL()
	{
	iBackdrop=CBackdrop::NewL();
	const TRect clientRect=ClientRect();
	iBackdrop->SetRect(clientRect);
	iBackdrop->ActivateL();
	}

/**
   Auxiliary function for all Test Cases
   
   This method creates a List Box and adds the list of applications currently
   running.
   
 */
void CTBackupAppUi::CreateAppListL()
	{
	iAppList=new(ELeave) COpenAppList();
	iAppList->ConstructL(NULL,0);
	TRect rect=ClientRect();
	rect.Shrink(TSize(20,20));
	iAppList->SetExtent(rect.iTl,rect.Size());
	iAppList->UpdateL();
	iAppList->ActivateL();
	}

/**
   Auxiliary function for all Test Cases
   
   This method prepares a list of files associated with each of the observers
   and adds them to a List Box.
   
 */
void CTBackupAppUi::CreateFileListL()
	{
	iFileList=new(ELeave) COpenFileList(*iFileObservers);
	iFileList->ConstructL();
	TRect rect=ClientRect();
	rect.Shrink(TSize(20,20));
	iFileList->SetExtent(rect.iTl,rect.Size());
	iFileList->UpdateL();
	iFileList->ActivateL();
	iFileList->MakeVisible(EFalse);
	}

/**
   Auxiliary function for all Test Cases
   
   This method creates 3 file observers to the backup server and associates
   them with their respective files.
   
 */
void CTBackupAppUi::CreateFileObserversL()
	{
	iFileObservers=new(ELeave) CArrayPtrFlat<CBackupFileObserver>(3);
	for (TInt ii=0;ii<3;ii++)
		{
		iFileObservers->AppendL(CBackupFileObserver::NewLC());
		CleanupStack::Pop(); // CBackupFileObserver
		}
	CBackupFileObserver* backup=(*iFileObservers)[0];
	backup->AddFileL(KBackupFile1);
	backup->AddFileL(KBackupFile2);
	backup->AddFileL(KBackupFile3);
	backup=(*iFileObservers)[1];
	backup->AddFileL(KBackupFile1);
	backup->AddFileL(KBackupFile3);
	backup=(*iFileObservers)[2];
	backup->AddFileL(KBackupFile3);
	}

/**
   Auxiliary function for all Test Cases
   
   This method creates observers for the backup operation.
   
 */
void CTBackupAppUi::CreateObserversListL()
	{
	for (TInt ii=0; ii<KNumOfBackupOperationObservers; ++ii)
		{
		User::LeaveIfError(iBackupOperationObserversWrapper.Append(CBackupOpeartionObserversWrapper::NewL(ii+1)));
		}
	}

/**
   @SYMTestCaseID UIF-tbackup-CmdListAppsL
  
   @SYMPREQ
  
   @SYMTestCaseDesc Test retrieving the application list.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The method calls COpenAppList::UpdateL() to update the list of
   applications currently running and makes the application list visible on the
   background control.
  
   @SYMTestExpectedResults All currently running application should be listed.
   
 */
void CTBackupAppUi::CmdListAppsL()
	{
	iAppList->UpdateL();
	if (!iAppList->IsVisible())
		{
		iFileList->MakeVisible(EFalse);
		iAppList->MakeVisible(ETrue);
		}
	iAppList->DrawNow();
	}

/**
   @SYMTestCaseID UIF-tbackup-CmdListOpenFilesL
  
   @SYMPREQ
  
   @SYMTestCaseDesc Test retrieving the list of files associated with the file
   observers.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The method calls COpenAppList::UpdateL() to update the list of
   files associated with each file observer and makes the file list visible
   on the background control. The access rights to these files are also displayed.
  
   @SYMTestExpectedResults All files associated with file observers should be listed.
   
 */
void CTBackupAppUi::CmdListOpenFilesL()
	{
	iFileList->UpdateL();
	if (!iFileList->IsVisible())
		{
		iAppList->MakeVisible(EFalse);
		iFileList->MakeVisible(ETrue);
		}
	iFileList->DrawNow();
	}

/**
   @SYMTestCaseID UIF-tbackup-CmdCloseL
  
   @SYMPREQ
  
   @SYMTestCaseDesc Test CloseFileL() & CloseAll() API's.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The method opens the close dialog.The user selection of 'All'
   or 'Single File' is recognised and CBaBackupSessionWrapper::CloseAll() or
   CBaBackupSessionWrapper::CloseFileL() is invoked to stop writing to a
   specified file or all files respectively.
  
   @SYMTestExpectedResults The test checks whether the status of the asynchronous
   request is KErrInUse.
   
 */
void CTBackupAppUi::CmdCloseL()
	{
	CDesCArray* files=new(ELeave) CDesCArrayFlat(3);
	CleanupStack::PushL(files);
	files->AppendL(KBackupFile1);
	files->AppendL(KBackupFile2);
	files->AppendL(KBackupFile3);
	CBackupDialogBase::TOperationGranularity granularity;
	TFileName fileName;
	MBackupObserver::TFileLockFlags fileFlag;
	
	if (CBackupCloseDialog::RunDlgLD(*files,granularity,fileName,fileFlag))
		{
		if (granularity==CBackupDialogBase::EAll)
			{
			TRequestStatus status=KRequestPending;
			iBackupSession->CloseAll(fileFlag,status);
			User::WaitForRequest(status);
			}
		else
			{
			iBackupSession->CloseFileL(fileName,fileFlag);
			}
		}
	CleanupStack::PopAndDestroy(); // files
	}

/**
   @SYMTestCaseID UIF-tbackup-AutoCmdCloseL
  
   @SYMPREQ
  
   @SYMTestCaseDesc Test CloseFileL() & CloseAll() API's.
 
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The method tests informing observers to stop writing to a specified
   file by calling CBaBackupSessionWrapper::CloseFileL(). It also tests whether
   CBaBackupSessionWrapper::CloseAll() closes all non-system applications and
   calls all observers to stop writing to the registered files.
  
   @SYMTestExpectedResults The test checks whether the status of the asynchronous
   request is KErrInUse.
   
 */
void CTBackupAppUi::AutoCmdCloseL()
	{
	TFileName fileName;
	MBackupObserver::TFileLockFlags fileFlag;
	
	fileFlag=MBackupObserver::EReleaseLockReadOnly;
	fileName = KBackupFile1;
	iBackupSession->CloseFileL(fileName,fileFlag);

	TRequestStatus status=KRequestPending;

	fileFlag=MBackupObserver::EReleaseLockReadOnly;
	iBackupSession->CloseAll(fileFlag,status);
	User::WaitForRequest(status);
	
	iBackupSession->RestartAll();
	fileFlag=MBackupObserver::EReleaseLockNoAccess;
	iBackupSession->CloseAll(fileFlag,status);
	User::WaitForRequest(status);
	}

/**
   @SYMTestCaseID UIF-tbackup-CmdRestartL
  
   @SYMPREQ
  
   @SYMTestCaseDesc Test RestartFileL() & RestartAll() APIs.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The method opens the backup restart dialog.The user selection
   of 'All' or 'Single File' is recognised and
   CBaBackupSessionWrapper::RestartAll() or
   CBaBackupSessionWrapper::RestartFileL() is invoked to take back all file
   locks on a specified file or on all files respectively.
  
   @SYMTestExpectedResults The checks whether the API CBaBackupSessionWrapper::RestartAll()
   reverses a CBaBackupSessionWrapper::CloseAll() call.
   
 */
void CTBackupAppUi::CmdRestartL()
	{
	CDesCArray* files=new(ELeave) CDesCArrayFlat(3);
	CleanupStack::PushL(files);
	files->AppendL(KBackupFile1);
	files->AppendL(KBackupFile2);
	files->AppendL(KBackupFile3);
	CBackupDialogBase::TOperationGranularity granularity;
	TFileName fileName;
	
	if (CBackupRestartDialog::RunDlgLD(*files,granularity,fileName))
		{
		if (granularity==CBackupDialogBase::EAll)
			{
			iBackupSession->RestartAll();
			}
		else
			{
			iBackupSession->RestartFile(fileName);
			}
		}
	CleanupStack::PopAndDestroy(); // files
	}

/**
   @SYMTestCaseID UIF-tbackup-AutoCmdRestartL
  
   @SYMPREQ
  
   @SYMTestCaseDesc Test RestartFileL() & RestartAll() APIs.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The method tests informing all observers to take back the file
   lock for the specified file by calling CBaBackupSessionWrapper::RestartFile().
   Similarly it also tests informing all observers to take back file locks for
   the registered files by calling CBaBackupSessionWrapper::RestartAll()
  
   @SYMTestExpectedResults The method checks whether the API
   CBaBackupSessionWrapper::RestartAll() reverses a
   CBaBackupSessionWrapper::CloseAll() call.
   
 */
void CTBackupAppUi::AutoCmdRestartL()
	{
	CDesCArray* files=new(ELeave) CDesCArrayFlat(3);
	CleanupStack::PushL(files);
	files->AppendL(KBackupFile1);
	files->AppendL(KBackupFile2);
	files->AppendL(KBackupFile3);
	TFileName fileName;
	
	fileName = KBackupFile1;
	iBackupSession->RestartFile(fileName);
		
	iBackupSession->RestartAll();

	CleanupStack::PopAndDestroy(); // files
	}

/**
   @SYMTestCaseID UIF-tbackup-AutoCmdCloseAllAndRestartAllL
  
   @SYMDEF DEF64721
  
   @SYMTestCaseDesc Test CloseAll() & RestartAll() APIs.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The method tests whether CBaBackupSessionWrapper::CloseAll() closes all 
   non-system applications and calls all observers to stop writing to the registered files.
   Similarly it also tests informing all observers to take back file locks for
   the registered files by calling CBaBackupSessionWrapper::RestartAll()
  
   @SYMTestExpectedResults The method checks whether the API
   CBaBackupSessionWrapper::RestartAll() reverses a
   CBaBackupSessionWrapper::CloseAll() call.
   
 */
void CTBackupAppUi::AutoCmdCloseAllAndRestartAllL()
	{
	RApaLsSession apaLsSession;
	apaLsSession.Connect();

	CApaCommandLine* cmdLn=CApaCommandLine::NewLC();
	
	_LIT(KLitExePath,"agenda.exe");
	cmdLn->SetExecutableNameL(KLitExePath);
	
	TThreadId tId;
	TRequestStatus appStatus= KRequestPending;

	//Starting the application
	TInt ret = apaLsSession.StartApp(*cmdLn,tId,&appStatus); // explicit
  	INFO_PRINTF2(_L("StartApp return code is %d"), ret);
	TEST(ret==KErrNone);
	User::WaitForRequest(appStatus);

	CleanupStack::PopAndDestroy(cmdLn);
	
	//Check whether the application is Started
	TFullName repName; 
	_LIT(KAppName,"agenda*");
	{//(Scoped in order to reuse appThread)
		TFindThread appThread(KAppName);
		//TFindThread::Next gets the next thread that matches the pattern above
		TEST(appThread.Next(repName) == KErrNone);
	}
	
	RThread thread;
	thread.Open(tId);

	MBackupObserver::TFileLockFlags fileFlag;
	fileFlag=MBackupObserver::EReleaseLockReadOnly;
	TRequestStatus closeallStatus = KRequestPending;
	
	//Closing all the non system applications
	iBackupSession->CloseAll(fileFlag,closeallStatus);
	//Wait till all the applications are closed
	User::WaitForRequest(closeallStatus);
	
	//Check whether the agenda application is closed in CloseAll
	TEST(thread.ExitType() != EExitPending);
		
	//Restarting All the nonsystem applications which are closed by previous CloseAll Call
	iBackupSession->RestartAll();
	
	//Check whether the application is Restarted
	TFindThread appThread(KAppName);
	TEST(appThread.Next(repName) == KErrNone);

	apaLsSession.Close();
	}
		
/**
   @SYMTestCaseID UIF-tbackup-UpdateBackupObserverRegistrationL
  
   @SYMPREQ
  
   @SYMTestCaseDesc Tests registering observers for back up operation.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented 
   
   @SYMTestActions The method creates a backup registration dialog and adds check
   boxes to represent all observers that are associated to each of the
   wrappers. On click of OK button of the dialog all selected observers should
   be registered with the backup server.
  
   @SYMTestExpectedResults The method should register all observers for backup
   operation.
   
 */
void CTBackupAppUi::UpdateBackupObserverRegistrationL()
	{
	CBackupRegistrationDialog* dialog = new(ELeave) CBackupRegistrationDialog(iBackupOperationObserversWrapper);
	dialog->ConstructAutoDialogLC(EEikDialogFlagWait, R_EIK_BUTTONS_CANCEL_OK);
	dialog->SetTitleL(KRegistrationDlgTitle);
	const TInt count = iBackupOperationObserversWrapper.Count();
	TBuf<20> buf;
	CBackupOpeartionObserversWrapper* observerWrapper = NULL;
	TInt previousCount = 0;
	for (TInt index1=0; index1<count; ++index1)
		{
		observerWrapper = iBackupOperationObserversWrapper[index1];
		const TInt count2 = observerWrapper->CountObservers();
		for (TInt index2=0; index2<count2; ++index2)
			{
			const TInt realIndex = previousCount+index2;
			buf.Format(KObserverStr, realIndex+1);
			CEikCheckBox* checkBox=(CEikCheckBox*)dialog->CreateLineByTypeL(buf, EObserversId+realIndex, EEikCtCheckBox, NULL);
			checkBox->SetSize(checkBox->MinimumSize());
			}
		previousCount += count2;
		}
	dialog->RunLD();
	}

/**
   @SYMTestCaseID UIF-tbackup-AutoUpdateBackupObserverRegistrationL
  
   @SYMPREQ
  
   @SYMTestCaseDesc Tests registering observers for back up operation.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented 
   
   @SYMTestActions The method finds the number of the observers that each interface
   object CBackupOpeartionObserversWrapper has and registers each of its observers
   to receive notification for backup operation by calling
   CBackupOpeartionObserversWrapper::RegisterBackupOperationObserverL().
  
   @SYMTestExpectedResults The method should register all observers for backup
   operation.
   
 */
void CTBackupAppUi::AutoUpdateBackupObserverRegistrationL()
	{
	//Following is copied from dialog->RunLD()....
	const TInt count1 = iBackupOperationObserversWrapper.Count();
	CBackupOpeartionObserversWrapper* observerWrapper = NULL;
	TInt previousCount = 0;
	for (TInt index3=0; index3<count1; ++index3)
		{
		observerWrapper = iBackupOperationObserversWrapper[index3];
		const TInt count2 = observerWrapper->CountObservers();
		for (TInt index4=0; index4<count2; ++index4)
			{
			CBackupOpeartionObserver* observer = observerWrapper->Observer(index4);
			observerWrapper->RegisterBackupOperationObserverL(*observer);
			}
			previousCount += count2;
		}
	}		
		
/**
   @SYMTestCaseID UIF-tbackup-UpdateBackupOperationStateL
  
   @SYMPREQ
  
   @SYMTestCaseDesc Manual Test to start / end back up operation.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The method displays the backup operation dialog with option
   buttons labelled 'Start' or 'End'. On click of OK button the state of
   option buttons is verified and backup operation is started or ended.
  
   @SYMTestExpectedResults The method CBaBackupSessionWrapper::IsBackupOperationRunning()
   is invoked to verify the start of backup operation.
   
 */
void CTBackupAppUi::UpdateBackupOperationStateL()
	{
	CEikDialog* dialog = new(ELeave) CBackupOperationDialog(*iBackupSession);
	dialog->ExecuteLD(R_TBACKUP_BACKUP_OPERATION);
	const TBool backupOperationRunning = iBackupSession->IsBackupOperationRunning();
	if (backupOperationRunning)
		{
		iBusyMsg->StartDisplay(KBackupOpMsg, TGulAlignment(EHLeftVTop));
		}
	else
		{
		iBusyMsg->CancelDisplay();
		}
	}

/**
   @SYMTestCaseID UIF-tbackup-AutoUpdateBackupOperationStateL
  
   @SYMPREQ
  
   @SYMTestCaseDesc Test starting of back up operation.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The method prepares the attributes to start the backup operation
   and notifies the server to start a backup operation by calling
   CBaBackupSessionWrapper::NotifyBackupOperationL(). The method then checks
   whether the backup operation has started by calling
   CBaBackupSessionWrapper::IsBackupOperationRunning(). Note that on start of
   backup operation CBackupOpeartionObserver::HandleBackupOperationEventL() is
   invoked by the server to notify client of backup start oiperation.
  
   @SYMTestExpectedResults The method CBaBackupSessionWrapper::IsBackupOperationRunning()
   should return ETrue to indicate the start of backup operation.
   
 */
void CTBackupAppUi::AutoUpdateBackupOperationStateL()
	{

	//From dialog OKToExit

	const TInt labeledButtonId = EDlgBackupOperationSel1;
	
	//Another test case is required.
	//labeledButtonId = EDlgBackupOperationSel2;

	TBackupOperationAttributes backupOperationAttributes;
	switch (labeledButtonId)
		{
		case EDlgBackupOperationSel1:
			{
			backupOperationAttributes.iFileFlag = MBackupObserver::EReleaseLockReadOnly;
			backupOperationAttributes.iOperation = MBackupOperationObserver::EStart;
			break;
			}
		case EDlgBackupOperationSel2:
			{
			backupOperationAttributes.iFileFlag = MBackupObserver::ETakeLock;
			backupOperationAttributes.iOperation = MBackupOperationObserver::EEnd;
			break;
			}
		default:
			//return EFalse;
			break;
		}
	
	iBackupSession->NotifyBackupOperationL(backupOperationAttributes);

	// Run backup operation. This continues to run until the cancel backup command is
	// chosen.
	const TBool backupOperationRunning = iBackupSession->IsBackupOperationRunning();
	
	if (backupOperationRunning)
		{
		iBusyMsg->StartDisplay(KBackupOpMsg, TGulAlignment(EHLeftVTop));
		}
	else
		{
		iBusyMsg->CancelDisplay();
		}
	}

/**********************************************
 
 
 
 	CTestBackupStep
 
 
 
************************************************/
CTestBackupStep::CTestBackupStep()
/**
   Constructor
 */
	{
	SetTestStepName(KTestBackupStep);
	}

CTestBackupStep::~CTestBackupStep()
/**
   Destructor
 */
	{
	}

/**
   Auxiliary function for all Test Cases
  
   The method creates & sets the application's user interface object.
   
 */
void CTestBackupStep::ConstructAppL(CEikonEnv* aCoe)
    { // runs inside a TRAP harness
	aCoe->ConstructL();

	CTestAppUi* appUi= new (ELeave) CTBackupAppUi(this);
    aCoe->SetAppUi(appUi);
    appUi->ConstructL();
    }

/**
   Auxiliary function for all Test Cases
  
   The method creates & sets the test step's user interface object and
   launches the test step.
   
 */
TVerdict CTestBackupStep::doTestStepL() // main function called by E32
	{
	PreallocateHALBuffer();
	__UHEAP_MARK;

	CEikonEnv* coe=new CEikonEnv;
	TRAPD(err,ConstructAppL(coe));

	if (!err)
		coe->ExecuteD();

	REComSession::FinalClose();	
	__UHEAP_MARKEND;

	return TestStepResult();
	}


