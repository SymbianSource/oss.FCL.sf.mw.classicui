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

// AknProgressTimer.h: interface for the CAknProgressTimer class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __AKNPROGRESSTIMER__
#define __AKNPROGRESSTIMER__

#include <e32base.h>

struct TTimerModel
  {
  TInt iFinalValue;
  TInt iHundreths;
  TInt iIncrement;
  TBool iRunning;
  };
class CAknNoteControl;

NONSHARABLE_CLASS(CAknProgressTimer) : public CTimer  
  {
 public:
	CAknProgressTimer();
	virtual ~CAknProgressTimer();
  void ConstructL(TTimerModel* aModel,CAknNoteControl* aContainer,TCallBack aCallBack);
  void AdjustRunningState();
private:
  void Queue();
  void RunL();
private:
  TTimerModel* iModel;
  CAknNoteControl* iContainer;
  TCallBack iCallBack;
  };

#endif 
