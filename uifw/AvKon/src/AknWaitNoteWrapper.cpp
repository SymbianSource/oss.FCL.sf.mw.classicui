/*
* Copyright (c) 2002 Nokia Corporation and/or its subsidiary(-ies).
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


// INCLUDE FILES

#include <AknWaitDialog.h>
#include <aknenv.h>
#include "AknWaitNoteWrapper.h"  // This class's declaration
#include "akntrace.h"


// MODULE DATA STRUCTURES

enum TPanicCode
    {
    EPanicAlreadyExecuted =1
    };

// LOCAL FUNCTION PROTOTYPES
// ==================== LOCAL FUNCTIONS ====================

// ================= MEMBER FUNCTIONS =======================

inline CAknWaitNoteWrapper::CAknWaitNoteWrapper() :
    CActive(EPriorityIdle),
    iIsDialogCanceled(EFalse)
    {
    CActiveScheduler::Add(this);
    }

EXPORT_C CAknWaitNoteWrapper* CAknWaitNoteWrapper::NewL()
    {
    _AKNTRACE_FUNC_ENTER;
    CAknWaitNoteWrapper* self = new(ELeave) CAknWaitNoteWrapper;
    _AKNTRACE_FUNC_EXIT;
    return self;
    }

EXPORT_C CAknWaitNoteWrapper::~CAknWaitNoteWrapper()
    {
    _AKNTRACE_FUNC_ENTER;
    Cancel();
	iTimer.Close();
    delete iWaitDialog;
    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C TBool CAknWaitNoteWrapper::ExecuteL
 (TInt aResId,MAknBackgroundProcess& aBackgroundProcess, 
    TBool aVisibilityDelayOff, const CAknNoteDialog::TTone& aTone)
    {
    _AKNTRACE_FUNC_ENTER;
    iBackgroundProcess = &aBackgroundProcess;
    CreateDialogL(aVisibilityDelayOff,aTone);
    iWaitDialog->ExecuteLD(aResId);
    _AKNTRACE_FUNC_EXIT;
    return NextCycleAndReturnL();
    }

EXPORT_C TBool CAknWaitNoteWrapper::ExecuteL
 (TInt aResId,MAknBackgroundProcess& aBackgroundProcess, 
    const TDesC& aPrompt, TBool aVisibilityDelayOff, const CAknNoteDialog::TTone& aTone)
    {
    _AKNTRACE_FUNC_ENTER;
    iBackgroundProcess = &aBackgroundProcess;
	CreateDialogL(aVisibilityDelayOff,aTone);
    iWaitDialog->PrepareLC(aResId);
	iWaitDialog->SetTextL(aPrompt);
    iWaitDialog->RunLD();
    _AKNTRACE_FUNC_EXIT;
    return NextCycleAndReturnL();
    }

void CAknWaitNoteWrapper::DoCancel()
    {
    _AKNTRACE_FUNC_ENTER;
    if (IsActive())
        {
		iTimer.Cancel();
        CAknEnv::StopSchedulerWaitWithBusyMessage(iWait);
        }
    _AKNTRACE_FUNC_EXIT;
    }

void CAknWaitNoteWrapper::RunL()
    {
    _AKNTRACE_FUNC_ENTER;
    if (iBackgroundProcess->IsProcessDone() || !iWaitDialog)
        {
        iBackgroundProcess->ProcessFinished();
        if (iWaitDialog)
            {
            iWaitDialog->ProcessFinishedL();
            iIsDialogCanceled = EFalse;
            }
        CAknEnv::StopSchedulerWaitWithBusyMessage(iWait);
        }
    else
        {
        // do one step of processing
        iBackgroundProcess->StepL();
        // Request next cycle
        NextCycle();
        }
    _AKNTRACE_FUNC_EXIT;
    }

TInt CAknWaitNoteWrapper::RunError(TInt aError)
    {
    iRunError = iBackgroundProcess->CycleError(aError);
    if (iRunError == KErrNone)
        {
        NextCycle();
        }
    else
        {
        CAknEnv::StopSchedulerWaitWithBusyMessage(iWait);
        }
    return KErrNone;
    }

void CAknWaitNoteWrapper::DialogDismissedL(TInt aButtonId)
    {
    iWaitDialog = NULL;
    iBackgroundProcess->DialogDismissedL( aButtonId );
    }

void CAknWaitNoteWrapper::NextCycle()
    {
	iTimer.After(iStatus, 0); 
	SetActive();
    }

TBool CAknWaitNoteWrapper::NextCycleAndReturnL()
	{
	_AKNTRACE_FUNC_ENTER;
    User::LeaveIfError(iTimer.CreateLocal());
	iIsDialogCanceled = ETrue;

	NextCycle();
    iWait.Start();
	iTimer.Close();

    User::LeaveIfError(iRunError);
    _AKNTRACE_FUNC_EXIT;

    return !iIsDialogCanceled;
	}

void CAknWaitNoteWrapper::CreateDialogL(TBool aVisibilityDelayOff, const CAknNoteDialog::TTone& aTone)
	{
	if (iWaitDialog)
        {
        delete iWaitDialog;
        iWaitDialog = NULL;
        }

    iWaitDialog = new (ELeave) CAknWaitDialog((CEikDialog**)&iWaitDialog, aVisibilityDelayOff);
    iWaitDialog->SetCallback(this);
	iWaitDialog->SetTone(aTone);
	}

//  End of File  

