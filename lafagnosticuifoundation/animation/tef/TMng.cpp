// Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
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

#include  <fbs.h>
#include "TMng.h"
#include "ActiveWait.h"
#include "ICLAnimationDataProvider.h"
#include "AnimationEvents.h"

_LIT(KMngFile, "Z:\\Private\\10204F5B\\simple_b.mng");
const TInt KExpectedNumberOfFrames = 12; // must match number of frames in KMngFile

CMng::CMng()
	{
	SetTestStepName(KMngStep);
	}
	
CMng::~CMng()
	{
	iFs.Close();
	RFbsSession::Disconnect();
	delete iDataProvider;
	if(iWaiter)
		{
		iWaiter->Cancel();
		delete iWaiter;
		}
	}

void CMng::StartTestL()
	{
	iWaiter = CActiveWait::NewL();
	
	User::LeaveIfError(iFs.Connect());
	User::LeaveIfError(RFbsSession::Connect());
	iDataProvider = new (ELeave) CICLAnimationDataProvider;
	iDataProvider->SetObserver(this);
	iDataProvider->SetFileL(iFs, KMngFile());
	iDataProvider->StartL(); // decode all frames
	}

/**
@SYMTestCaseID UIF-ANIMATION-0001
@SYMDEF DEF084519
@SYMTestCaseDesc This test verifies that CICLAnimationDataLoader manages to extract frames from image files encoded as multi image network graphics.
@SYMTestPriority High
@SYMTestStatus Implemented
@SYMTestActions The test verifies that we receive EBitmapAnimationComplete and that the number of extracted frames at that point equals the expected number of frames.
@SYMTestExpectedResults Test should complete without any leave, panic or error.
 */
TVerdict CMng::doActiveTestStepL()
	{
	SetTestStepID(_L("UIF-ANIMATION-0001"));

	StartTestL();
			
	const TInt KTimeOut = 5*1000000;
	iWaiter->Wait(KTimeOut); // continue on timeout or EImageConvertComplete

	TEST(iConvertionComplete);
	TEST(iDecodedFrames == KExpectedNumberOfFrames);
	
	RecordTestResultL();
	CloseTMSGraphicsStep();

	return TestStepResult();
	}

// from MAnimationDataProviderObserver
void CMng::DataProviderEventL(TInt aEvent, TAny* /*aData*/, TInt /*aDataSize*/)
	{
	switch(aEvent)
		{
		case EAnimationDataChanged:
			break;
		case EBitmapAnimationNewFrame:
			++iDecodedFrames;
			break;
		case EBitmapAnimationComplete:
			iConvertionComplete = ETrue;
			iWaiter->Cancel();
			break;
		default:
			TESTE(EFalse, aEvent);
			break;
		}
	}	
