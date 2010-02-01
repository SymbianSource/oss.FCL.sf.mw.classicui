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

#if !defined(__TBMPANIMSTEP_H__)
#define __TBMPANIMSTEP_H__


#include <test/testexecutestepbase.h>
#include "TBmpAnimTestServer.h"
#include <coeaui.h>
#include <eikappui.h>
#include <eikapp.h>
#include <eikdoc.h>
#include <techview/eikdialg.h>
#include <techview/eikchlst.h>
#include <techview/eikchkbx.h>
#include <techview/eikmfne.h>
#include <techview/eikmenup.h>
#include <eikenv.h>
#include "Tanctl.h"
#include "appfwk_test_AppUi.h"

enum TContainerPanic
	{
	TContainerPanicNoArray,
	TContainerNoWindow,
	TContainerInalidPointer,
	TInvalidIndex
	};


class CTBmpAnimStep : public CTmsTestStep
	{
public:
	CTBmpAnimStep();
	~CTBmpAnimStep();
//	virtual TVerdict doTestStepPreambleL();
//	virtual TVerdict doTestStepPostambleL();
	virtual TVerdict doTestStepL();
	void ConstructAppL(CEikonEnv* aCoe);
private:
	};

//
// CAnimationDlg
//
class CAnimationDlg : public CEikDialog
{
public:
	CAnimationDlg(TFileName iFileName);
	~CAnimationDlg();
private:
	TBool OkToExitL(TInt aKeyCode);
	void PostLayoutDynInitL();
	SEikControlInfo CreateCustomControlL(TInt aControlType);
	static TInt Execute(TAny* aDialog);
private:
	TFileName iFileName;
	TBool iAuto;
	CPeriodic	*iTimer;
};

//
//
// class CColorSchemeDlg
//

class CColorSchemeDlg : public CEikDialog
    {
public:
    CColorSchemeDlg(TInt& aChoice);
	~CColorSchemeDlg() {};
private: // from CEikDialog
    TBool OkToExitL(TInt aKeycode);
	void PreLayoutDynInitL();
	TInt& iChoice;
    };

//
//
// class TAnimationAttributesDlg
//

enum TAnimationFlag
	{
	ENoAnimation		= 0x00,
	EDefaultAnimation	= 0x01,
	EDefaultAnimationSh	= 0x02,
	EBallAnimation		= 0x04,
	EAllAnimations		= 0x08,
	ERedPurpBallAnimationMaskedBackground = 0x10,
	ETBmpAnimBallAnimWindowCovering = 0x12
	};

class TAnimationAttributes
	{
public:
	TAnimationAttributes();
public:
	enum { ENone=0x0, EFloating=0x1, EAlreadyInit=0x2 };
public:
	CBitmapAnimClientData::TPlayMode iPlayMode;
	TInt iFrameIntervalInMilliSeconds;
	TBool iOnOff;
	TInt iNumberOfCycles;
	};

//
//
// class CAnimationAttributesDlg
//

class CAnimationAttributesDlg : public CEikDialog
    {
public:
    CAnimationAttributesDlg(TAnimationAttributes& aAttributes);
	~CAnimationAttributesDlg() {};
private: // from CEikDialog
    TBool OkToExitL(TInt aKeycode);
	void PreLayoutDynInitL();
private:
	TAnimationAttributes& iAttributes;
    };

//
//
// class CAnimation
//

class CAnimation : public CBase
	{
public:
	CAnimation();
	~CAnimation();
	void CopyAttributesFromClientData();
	void SetAnimationExtent();
public:
	TInt iIndex;
	TAnimationFlag iType;
	CAnimateFramesCtl* iAnimationCtl;
	TAnimationAttributes iAttributes;
	};

/*
 
 	Test window owning control.
 	Used in a test case.
 
*/
class CTestWindowControl :  public CCoeControl
    {
public:
    void ConstructL();
	CTestWindowControl();
	~CTestWindowControl();

public:
	void Draw(const TRect& aRect) const;
	};

//
//
// class CTestContainer
//

class CTestContainer :  public CCoeControl
//Container window owning control to display animations.
    {
public:
    void ConstructL();
	CTestContainer();
	~CTestContainer();
	void CancelAnimationL(TInt aIndex);
	void SetAnimationAttributesL(TAnimationFlag aAnimationType);
	CAnimation* CreateAnimationByTypeL(TAnimationFlag aAnimationType);
	void CreateAndRunAnimationL();
	TInt FindAnimation(TAnimationFlag aAnimationType);
	void ShowAnimationL(TAnimationFlag aAnimationType);
	void StartAnimationL(TInt aIndex);
	void SetAppFileName(TDesC& aAppFileName);
	void Panic(TContainerPanic aPanic);
	void DisplayAnimCoveringWindowL();
	TBool TestRenderBackgroundFrameL();

public:	// from CCoeControl
	TInt CountComponentControls() const;
	void Draw(const TRect& aRect) const;
	CCoeControl* ComponentControl(TInt aIndex) const;
	void SizeChanged();

private:
	TBool CompareScreenContentWithTestBitmapL(const CBitmapFrameData& aBkgdFrameBmp, const CBitmapFrameData& aFrame1Bmp, const TPoint& aPos);
	TBool CompareBitmapsL(CFbsBitmap* aBmp1, CFbsBitmap* aBmp2);
	
public:
	enum TBackgroundType
		{ 
		EBackgroundBlackRedGreenYellowStripes,
		EBackgroundYellow,
		EBackgroundBlue
		};
	TBackgroundType iBackgroundType;
	CTestWindowControl* iCoveringWindowControl;

private:
	TInt iFlags;
	TRgb iColor;
	CArrayPtrFlat<CAnimation>* iAnimationsArray;
	TFileName iFileName;
	};

class CSimpleAppUi : public CTestAppUi
    {
public:
public:
	CSimpleAppUi(CTmsTestStep* aStep);
	~CSimpleAppUi();
    void ConstructL();
private: // framework
    void HandleCommandL(TInt aCommand);
private: // menu commands
	void CmdTestOutOfMemoryL();
	void DialogWithAnimationL(TInt aResourceId);
	void RunTestStepL(TInt aNumStep);
	void RunAnimWithMaskedBgL();
	void RunAnimWithWindowCoveringL();
private:
	void ConstructContainerL();
private:
    CTestContainer* iContainer;
	TInt iFlags;
	CAutoTestManager::TTestResult iTestResult;
    };


_LIT(KTBmpAnimStep,"TBmpAnim");

#endif
