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


#ifndef __TMNG_H__
#define __TMNG_H__

#include "ActiveTestStep.h"
#include "AnimationMixins.h"

class CActiveWait;
class CICLAnimationDataProvider;

_LIT(KMngStep, "Mng");

class CMng : public CActiveTestStep, public MAnimationDataProviderObserver
	{
public:
	CMng();
	~CMng();
		
	// from CActiveTestStep:
	TVerdict doActiveTestStepL();
	
	// from MAnimationDataProviderObserver
	void DataProviderEventL(TInt aEvent, TAny* aData, TInt aDataSize);

private:
	void StartTestL();
	
private:
	RFs iFs;
	CICLAnimationDataProvider* iDataProvider;
	CActiveWait* iWaiter;
	TInt iDecodedFrames;
	TBool iConvertionComplete;
	};

#endif //__TMNG_H__
