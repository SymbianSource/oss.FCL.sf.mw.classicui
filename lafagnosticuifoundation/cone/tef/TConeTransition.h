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

#if !defined(__TCONETRANSITION_H__)
#define __TCONETRANSITION_H__

#include <coecntrl.h>
#include "TConeTestServer.h"
#include "appfwk_test_AppUi.h"
//! A CCoeControl Derived Class.\n
/** 
  Class is used to instantiate simple controls.\n 
  Also serves as base class for CTestControlGcTriangle Class.\n
*/
class CTestControlGc : public CCoeControl
    {
friend class CTestControlBackground;
public:
    void virtual ConstructL(TPoint, TSize, TRgb aPenColor, TRgb aBrushColor, const TDesC &aControlName);
    ~CTestControlGc();
    void Draw(const TRect& aRect) const;
    void SupressOutput(TBool aSupressOutput) 
    	{
    	iSupressOutput = aSupressOutput;
    	}
protected: 
	// framework
	void HandlePointerEventL(const TPointerEvent& aPointerEvent);
private: // framework
	void FocusChanged(TDrawNow aDrawNow);
protected:	
	//! Colour combination for Pen.\n
	TRgb	iPenColor;
	//! Colour combination for Brush.\n
	TRgb	iBrushColor;
	//! Boolean to indicate whether the control should be drawn or not.\n
	TBool 	iSupressOutput;
	//! Name of the control.\n
	TBuf<128>	iControlName;
    };
//! A Class derived from CTestControlGc and MCoeControlHitTest interface.\n
/**
  Implements the MCoeControlHitTest interface.\n
*/
class CTestControlGcTriangle : public CTestControlGc
			, public MCoeControlHitTest
    {
public:
    void virtual ConstructL(TPoint, TSize, TBool aTop, TRgb aPenColor, TRgb aBrushColor, const TDesC &aControlName);
    ~CTestControlGcTriangle();
    void Draw(const TRect& aRect) const;
protected:    
	TBool HitRegionContains(const TPoint& aPoint, const CCoeControl& aControl) const;
	TBool IsInside(const TPoint& pt) const;
protected:
	CArrayFix<TPoint>* iPoints;
    };
//! A Class derived from CTestControlGc.\n
/**
  Class used to test offscreen bitmap drawing.\n
*/
class CTestControlImageGc : public CTestControlGc
    {
public:
    ~CTestControlImageGc()
    	{
    	};
    void Draw(const TRect& aRect) const;
    void SetBitmap(CFbsBitmap* aBmp) 
    	{
    	iBmp = aBmp;
    	}
protected:
	//!A bitmap managed by the font and bitmap server.\n  
	CFbsBitmap* iBmp;
    };

//! A Class derived from CCoeControl and MCoeControlBackground interface.\n
/**
  A Class implementing background drawing interface.\n
*/
class CTestControlBackground : public CCoeControl
								, public MCoeControlBackground
    {
public:
    void ConstructL();
    ~CTestControlBackground();
    TInt SetChildGc();
	void RestoreChildGc();
	void ClearOffScreenBitmap();
	void SetControlParent();
	void SupressOutput(TInt aNumControl, TBool aSupress);
	void GeneratePointerEventsOnControl1L();
	void GeneratePointerEventsOnControl2L();
	void GeneratePointerEventsOnControl3L();
	TInt OffScreenDrawing();
	TInt DirectScreenDrawing();
	
protected:
	// MCoeControlBackground
	void Draw(CWindowGc& aGc, const CCoeControl& aControl, const TRect& aRect) const;
private: // framework
	void FocusChanged(TDrawNow aDrawNow);
    void Draw(const TRect& aRect) const;
private: // new functions
    void DrawBorder() const;
	
	TInt CountComponentControls() const;
	CCoeControl* ComponentControl(TInt aIndex) const;
private:
	//! Simple control.\n 
    CTestControlGc*	iControl;
    //! Control implementing MCoeControlHitTest interface.\n
    CTestControlGcTriangle*	iControl2;
    //! Control implementing MCoeControlHitTest interface.\n
    CTestControlGcTriangle*	iControl3;
    //! Control with an bitmap.\n
    CTestControlImageGc*	iControlImage;
	//! Window graphics context.\n
    CWindowGc* iGraphContext;
    //! Font and Bitmap server Graphic Context.\n
    CFbsBitGc* iMainFbsBitGc;
	//! A graphics device to which a bitmap managed by the font and bitmap server can be drawn.\n
    CFbsBitmapDevice* iBitmapDevice2;
    //! Window server bitmap.\n
	CWsBitmap *iBitmapView;
	//!A bitmap managed by the font and bitmap server.\n
	CFbsBitmap* iBmpBackground;
    };


//! A CTestStep Derived Class.\n
/**
  Incorporates the tests on direct screen and offscrreen bitmap drawing.\n
*/
class CTConeTransitionStep : public CTmsTestStep
	{
public:
	CTConeTransitionStep();
	~CTConeTransitionStep();
	virtual TVerdict doTestStepL();
	void ConstructAppL(CCoeEnv* aCoe);

private:
	};
//! A CTestCoeAppUi derived class.\n
/**
  AppUi Class for TConeTransition test step.\n
*/	
class CTConeTransitionAppUi : public CTestCoeAppUi
    {
friend class CTestControlBackground;
friend class CTestControlGc;
public:
	CTConeTransitionAppUi(CTmsTestStep* aStep);
	~CTConeTransitionAppUi();
	void ConstructL();
private: // from CCoeAppUi
    TKeyResponse HandleKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
private: // utility
	void RunTestStepL(TInt aStepNum);
public:
	TBuf<128>	iExpectedControlName;
protected:
	//! Control which supports background drawing.\n
	CTestControlBackground* iViewControl;
    };

//! TConeTransition Test Step Name.\n
_LIT(KTConeTransitionStep,"TConeTransition");

#endif


