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


#ifndef __ANIMATIONTESTSTEP_H__
#define __ANIMATIONTESTSTEP_H__

#include <test/testexecutestepbase.h>
#include <f32file.h>

#include <w32std.h>
#include <charconv.h>

#include "ActiveTestStep.h"
#include "ActiveWait.h"
#include "TestWindows.h"
#include "TestEventHandler.h"
#include "TestRedrawHandler.h"

_LIT(KTestFailed, "Test failed");
_LIT(KTestFailedF, "Test failed with %d");
_LIT(KRectsDiffer, "Compared areas differ");
_LIT(KColorCount, "Wrong number of colors");
_LIT(KColorCountF, "Color count out by %d");

// Helper functions for error reporting.
#define ANIM_INFO1(m)	{ Log(m); INFO_PRINTF1(m); }
#define ANIM_WARN1(m)	{ Log(m); WARN_PRINTF1(m); }
#define ANIM_ERR1(m)	{ Log(m); ERR_PRINTF1(m); }

#define ANIMTESTERR(x)	{ if(x < KErrNone) { Log(KTestFailed); ERR_PRINTF2(KTestFailedF, x); SetTestStepResult(EFail); } }
#define ANIMTESTRECT(r1,r2) { if(!RectCompare(r1,r2)) { Log(KRectsDiffer); ERR_PRINTF1(KRectsDiffer); SetTestStepResult(EFail); } }
#define ANIMTESTCOLORSL(r,c1,c2) { TInt c = CountColorsL(r,c1,c2); if(c!=0) { Log(KColorCount); ERR_PRINTF2(KColorCountF, c); SetTestStepResult(EFail); } }

//
// Windows:
//
const TInt KMaxLogWinLines = 12;

class CAnimBackdropWindow : public CTestWindow
	{
public:
	CAnimBackdropWindow(RWsSession& aWs, CTestWindowGroup& aGroup, CWindowGc& aGc);
	};

class CAnimationTestWindow : public CTestWindow
	{
public:
	CAnimationTestWindow(RWsSession& aWs, CTestWindowGroup& aGroup, CWindowGc& aGc, CWsScreenDevice& aScreen);
	~CAnimationTestWindow();
	void DrawL();
	void AppendText(const TDesC& aText);
	void Clear();
	CWsScreenDevice& iScreen;
	CFbsFont* iFont;
protected:
	TInt iNumLines;
	TInt iFirstLine;
	TBuf<40> iText[KMaxLogWinLines];
	};

//
// The test:
// This test does not perform any tests on the visual output.  It is useful
// for other issues, but it is also a good base for manual testing.
//
class CAnimationTestStep : public CActiveTestStep
	{
public:
	CAnimationTestStep();
	~CAnimationTestStep();

	void InitialiseL();
protected:
	void Log(const TDesC& aText);
	void ClearLog();
	void Wait(TInt aDelay);
	void WaitForRedrawsToFinish();
	
	CTestWindowGroup* GroupWin()	{ return iGroupWin; }
	CWsScreenDevice* Screen()		{ return iScreen; }
	CWindowGc* Gc()					{ return iGc; }
	RWsSession& Ws()				{ return iWs; }
	RFs& Fs()						{ return iFs; }
	TBool RectCompare(const TRect& a, const TRect& b);
	TInt CountColorsL(const TRect& aRect, TInt aMin, TInt aMax);
protected:
	CActiveWait* iWaiter;
	CAnimationTestWindow* iAnimTestWin;
	CAnimBackdropWindow* iAnimBackdropWin;
	
	RWsSession iWs;
	RFs iFs;
	CWsScreenDevice* iScreen;
	CWindowGc* iGc;

	CCnvCharacterSetConverter* iConverter;
	TInt iConverterState;
	CTestEventHandler* iEventHandler;
	CTestRedrawHandler* iRedrawHandler;
	CTestWindowGroup* iGroupWin;
	TSize iStepWinSize;
	TRgb iBackgroundColor1;
	TRgb iBackgroundColor2;
	TDisplayMode iDisplayMode;
	RArray<TUint> iColors;
	};

#endif //__ANIMATIONTESTSTEP_H__
