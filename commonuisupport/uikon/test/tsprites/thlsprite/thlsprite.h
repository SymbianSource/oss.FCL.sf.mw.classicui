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
// The test step performs tests to display sprites from a sprite set.
// 
//

/**
 @file
 @internalComponent - Internal Symbian test code
*/


#ifndef		__THLSPRITE_H
#define		__THLSPRITE_H


#include "appfwk_test_AppUi.h"

_LIT(KHlSpriteStep, "THlSprite");

//!  A CTestThlspriteStep test class. 
/**
 The class creates & sets the application's user interface object.
*/
class CTestThlspriteStep : public CTmsTestStep
	{
public:
	CTestThlspriteStep();
	~CTestThlspriteStep();
	//virtual TVerdict doTestStepPreambleL();
	virtual TVerdict doTestStepL();
	void ConstructAppL(CEikonEnv* aCoe);
private:
	};


//!  A CHLSpriteAppView test class. 
/**
 The class provides a view on which the sprite is displayed.
*/
class CHLSpriteAppView : public CCoeControl
	{
public:
	~CHLSpriteAppView();
	void ConstructL(const TRect& aRect);
	void TryCreateSpriteSetL();
	void HandleTimerCallbackL();
	void DrawTargetSpriteNowL() const;
private:	// from CCoeControl
	void Draw(const TRect&) const;
public:
	CSpriteSet::TSpriteResizeMode iResizeMode;
	TInt iSpriteSideLength;
	TPoint iTargetSpriteTl;
	TBool iSpriteIsDisplayed;
	TBool iMaskIsInverted;
	TRect iClippingRect;
	CSpriteSet* iSourceSpriteSet;
	CSpriteSet* iTargetSpriteSet;
	};



//!  A CHLSpriteAppUi test class. 
/**
 The class performs tests on the CSpriteSet Api's.
*/
class CHLSpriteAppUi : public CTestAppUi
	{
public:
	CHLSpriteAppUi(CTmsTestStep *aStep);
	void ConstructL();
	~CHLSpriteAppUi();
	static TInt TimerCallbackL(TAny* aPtr);
private:
	TSpriteMember CreateSpriteMember(TInt aBmpIndex, TInt aMaskIndex, TInt aInterval=0,  const TPoint& aOffset = TPoint(0,0));
private:	// from CEikAppUi
	void HandleCommandL(TInt aCommand);
	//void DynInitMenuPaneL(TInt aMenuId,CEikMenuPane* aMenuPane);
	//from CTestAppUi
	void RunTestStepL(TInt aNumStep);
private:
	TPoint iTranslateOffset; // use for auto mode

	CHLSpriteAppView* iAppView;
	CPeriodic* iTimer;
	TInt64 iSeed;
	};


#endif


