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


#if !defined(__TCONEINVALIDATE_H__)
#define __TCONEINVALIDATE_H__

#include <coecntrl.h>
#include <coeccntx.h>
#include <gulgcmap.h>
#include "TConeTestServer.h"
#include "appfwk_test_AppUi.h"
#include "TTransGc.h"

/** Base control drawing class
	@test 
*/
class CTestRectGc : public CCoeControl
								, public MCoeControlBackground
    {
  public:  
    typedef enum
    {
    	EBlank,
    	EDrawRect,
    	EDrawEllipse
    } TDrawType;
    
friend class CTestRectBackground;
friend class CComponentControl;

public:
    void virtual ConstructL(TPoint, TSize, TRgb aPenColor, TRgb aBrushColor, CGraphicsContext::TBrushStyle aBrushStyle);
    ~CTestRectGc();
    void Draw(const TRect& aRect) const;
    void SetPenColor(const TRgb &aPenColor);
    void SetBrushColor(const TRgb &aBrushColor);
    void SetBrushStyle(const CGraphicsContext::TBrushStyle aBrushStyle);
    void SetDrawType(const TDrawType DrawType);

	void NextFrame();

	// MCoeControlBackground
	void Draw(CWindowGc& aGc, const CCoeControl& aControl, const TRect& aRect) const;
	
static	CFbsBitmap* iBmpBackground;
	
protected:	
	TDrawType 	iDrawType;
	TRgb		iPenColor;
	TRgb		iBrushColor;
	CGraphicsContext::TBrushStyle iBrushStyle;	
	int 		iFrameNo;
			
 	};

/** Image display/drawing control
	@test
*/
class CTestRectImageGc : public CTestRectGc
    {
public:
		
    ~CTestRectImageGc()
    	{
    	};
    void Draw(const TRect& aRect) const;
    void SetBitmap(CFbsBitmap* aBmp) 
	   	{
    	iBmp = aBmp;
	    }
    CFbsBitmap* Bitmap() 
	    {
	    return iBmp;
	    }
    
protected: 
	CFbsBitmap* iBmp;
    };

/** Hierarchical animated component control class
	@test
*/
class CComponentControl : public CTestRectGc
{
public:
	
	~CComponentControl();	
    void ConstructL(TInt aChildren, TInt aOwners, TPoint aPt, TSize aSize, TRgb aPenColor, TRgb aBrushColor, CGraphicsContext::TBrushStyle aBrushStyle);
    void CreateChildControlL(TInt aChildren, TInt aOwners, TPoint aPt, TSize aSize, TRgb aPenColor, TRgb aBrushColor, CGraphicsContext::TBrushStyle aBrushStyle);
    
 	void Draw(const TRect& aRect) const;	
 	void AnimateComponents();
};

/** Offscreen class
	@test
*/
class COffScreenBitmapGc 
{
public:	
    CTransGc* iGraphContext;
    CFbsBitGc* iMainFbsBitGc;

    CFbsBitmapDevice* iBitmapDevice2;
	CWsBitmap *iBitmapView;
	
	 COffScreenBitmapGc();
public:
	 ~COffScreenBitmapGc();
	 static COffScreenBitmapGc* NewL(const TSize &aSize);
	 CTransGc *OffScreenGc();
	 CWsBitmap *GetBitmap();
};

/** Main control class
	@test
*/
class CTestRectBackground : public CTestRectGc
    {
public:
    void ConstructL();
    ~CTestRectBackground();
	
protected:
	
    void Draw(const TRect& aRect) const;
private: // new functions
	

public:
    CComponentControl*		iControl;			//Main animated control 
    CTestRectImageGc*		iControlImage;		//Region drawn to offscreen 
    CTestRectImageGc*		iControlImage2;		//Region drawn to offscreen plus background
	COffScreenBitmapGc 		*iOffScreen;		//The physical offscreen bitmap
	COffScreenBitmapGc 		*iOffScreen2;		//The 2nd physical offscreen bitmap
	
public:
	void CreateComponentControlL(TInt aNumChildren, TInt aOwnerMask);

    };

/** Test step class
	@test
*/
class CTConeInvalidateStep : public CTmsTestStep
	{
public:
	CTConeInvalidateStep();
	~CTConeInvalidateStep();
	virtual TVerdict doTestStepL();
	void ConstructAppL(CCoeEnv* aCoe);

private:
	};
	
/** Test application
	@test
*/
class CTConeInvalidateAppUi : public CTestCoeAppUi
    {
friend class CTestRectBackground;
friend class CTestRectGc;
public:
	CTConeInvalidateAppUi(CTmsTestStep* aStep);
	~CTConeInvalidateAppUi();
	void ConstructL();
private: // from CCoeAppUi
    TKeyResponse HandleKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
private: // utility
	void RunTestStepL(TInt aStepNum);
protected:
	CTestRectBackground* iViewControl;			//The main application control
    };


_LIT(KTConeInvalidateStep,"TConeInvalidate");

#endif


