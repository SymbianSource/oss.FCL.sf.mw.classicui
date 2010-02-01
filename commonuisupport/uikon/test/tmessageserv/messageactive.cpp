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
//

/**
 @file
 @internalComponent - Internal Symbian test code 
*/

#include "messageactive.h"

const TInt STOP_SERVER_CODE	= 0xff;

CMessageActive::CMessageActive() 
	: CActive(EPriorityLow)
	{
	}
	
EXPORT_C CMessageActive::~CMessageActive()
	{
	}

/**
   Auxiliary function for TestCaseID TPACKAGESTARTER-doTestStepL
  
   This method creates an active object of class CMessageActive and adds it to
   the active scheduler.
  
 */
EXPORT_C CMessageActive* CMessageActive::NewL()
	{
	CMessageActive*	theMessage = new CMessageActive;
    CActiveScheduler::Add(theMessage);
	
	RThread	thread;
	theMessage->iID = thread.Id();
	return theMessage;
	}
	
/**
   Auxiliary function for TestCaseID TPACKAGESTARTER-doTestStepL
  
   This method is an override from CActive.It handles the client message request
   completion event. On completion of copying message from client to the server
   this method logs the information gathered from the message.
  
 */
void CMessageActive::RunL()
	{
	if(iStatus.Int() == KErrNone)
		{
		CTestExecuteLogger& logger = iStep->Logger();
		logger.LogExtra(((TText8*)(iFileName.PtrZ())), iLineNumber, ESevrInfo, iMsg);
		}
	else if(iStatus.Int() == STOP_SERVER_CODE)
		{
		CActiveScheduler::Stop();
		}
	else
		{
		CTestExecuteLogger& logger = iStep->Logger();
		iStep->testBooleanTrueWithErrorCode(0, iError, ((TText8*)(iFileName.PtrZ())), iLineNumber );
		if(iError != 0)
			{
			logger.LogExtra(((TText8*)(iFileName.PtrZ())), iLineNumber, ESevrErr, iMsg, iError);
			}
		else
			{
			logger.LogExtra(((TText8*)(iFileName.PtrZ())), iLineNumber, ESevrErr, iMsg);
			}
		}
	}

/**
   Auxiliary function for TestCaseID TPACKAGESTARTER-doTestStepL
  
   This method sets the request status to be complete and sets the request to be
   outstanding so that the active scheduler invokes the RunL() method of the
   active object CMessageActive.
  
 */
void CMessageActive::Init()
	{
	TRequestStatus *pS=(&iStatus);
	User::RequestComplete(pS,0);
	*pS=KRequestPending;
	SetActive();
	}
/**
  Auxiliary function for TestCaseID TPACKAGESTARTER-doTestStepL
  
  This method is an override from CActive. It is used for cancellation of an
  outstanding request.
  
 */
void CMessageActive::DoCancel()
	{
	}
/**
   Auxiliary function for TestCaseID TPACKAGESTARTER-doTestStepL
  
   This method is used to activate CMessageActive class to output the message
   to logs.
  
 */
void CMessageActive::RequestForTheMessageOutput(TInt aCode)
{
	RThread	thread;
	TRequestStatus *pS=(&iStatus);

	*pS=KRequestPending;
	SetActive();

	thread.Open(iID);
	thread.RequestComplete(pS, aCode);
}
