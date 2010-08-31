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

// AknProgressTimer.cpp: implementation of the CAknProgressTimer class.
//
//////////////////////////////////////////////////////////////////////

#include "aknnotecontrol.h"
#include "aknprogresstimer.h"
#include <coemain.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAknProgressTimer::CAknProgressTimer() : CTimer(EActivePriorityClockTimer)
  {

  }


CAknProgressTimer::~CAknProgressTimer()
  {
  Cancel();
  }

void CAknProgressTimer::AdjustRunningState()
  {
  (iModel->iRunning) ? Queue() : Cancel();
  }

void CAknProgressTimer::ConstructL(TTimerModel *aModel,CAknNoteControl *aContainer,TCallBack aCallBack)
  {
  iCallBack = aCallBack;
  CTimer::ConstructL();
  CActiveScheduler::Add(this);
  iModel = aModel;
  iContainer = aContainer;
  iContainer->SetFinalProgressValue(iModel->iFinalValue);
  if (iModel->iRunning)
    Queue();
  }

void CAknProgressTimer::Queue()
  {
  After(10000 * iModel->iHundreths);
  }

void CAknProgressTimer::RunL()
  {
  if (iContainer->IncrementBarsAndDraw(iModel->iIncrement))
    Queue();
  else
    iCallBack.CallBack();
  }

// End of File
