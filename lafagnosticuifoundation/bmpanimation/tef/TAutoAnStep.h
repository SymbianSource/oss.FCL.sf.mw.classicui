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
 @test	
 @internalComponent - Internal Symbian test code 
*/


#if !defined(__TAUTOANSTEP_H__)
#define __TAUTOANSTEP_H__

#include <w32adll.h>
#include <w32std.h>
#include <bmpancli.h>

#include <test/testexecutestepbase.h>
#include "TBmpAnimTestServer.h"
#include "appfwk_tmsteststep.h"



//  structs and classes

class CTestingData : public CBase
	{
public:
	inline CTestingData(RAnimDll aAnimDll, RBitmapAnim aAnimation, RWindow aWindow);
public:
	RAnimDll iAnimDll;
	RBitmapAnim iAnimation;
	RWindow iWindow;
	};

inline CTestingData::CTestingData(RAnimDll aAnimDll, RBitmapAnim aAnimation, RWindow aWindow)
	: iAnimDll(aAnimDll), 	iAnimation(aAnimation), iWindow(aWindow)
	{}

class CTAutoAnStep : public CTmsTestStep
	{
public:
	CTAutoAnStep();
	~CTAutoAnStep();
	virtual TVerdict doTestStepL();
	void Test1L(CTestingData* aTestingData);
	void Test2L(CTestingData* aTestingData);
	static CBitmapAnimClientData* CreateClientDataL();
	void CreatedAndCloseAnimationsL(CTestingData* aTestingData);
	void TestNegativeFrameIntervalL();
	// Series60 Specific Test
	static void TestStartAnimationAndKeepLastFrameL(CTestingData* aTestingData);
private:
	void ExcuteTestCodeL();
	void TestWindowConstructL(RBitmapAnim& aAnimation,RWindow& aWindow,CBitmapAnimClientData* aClientData);
	};


class CWsClient
	{
public:
	// construct/destruct
	CWsClient();
	void ConstructL();
	~CWsClient();
	// terminate cleanly
	void Exit();
	inline RWsSession WindowSession();
	inline RWindowGroup WindowGroup();
private:
	RWsSession iWs;
	RWindowGroup iGroup;
	};


inline RWsSession CWsClient::WindowSession()
	{ return iWs; }
inline RWindowGroup CWsClient::WindowGroup()
	{ return iGroup; }

// 
// RTestBitmapAnim used to test Series60 specific changes
//

class RTestBitmapAnim : public RBitmapAnim
	{
public:
	RTestBitmapAnim(RAnimDll& aAnimDll);

	void StartAndKeepLastFrameL();
	};

_LIT(KTAutoAnStep,"TAutoAn");
#endif


