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
// Tests MCoeControlBackground interface.\n
// Parent controls can elect to take responsibility for drawing the background for their child
// controls.\n To achieve this, they should aggregate an object that implements this interface.\n
// CCoeControl::SetBackground() accepts the object and sets it as the background drawer.\n
// 
//

/**
 @file
 @internalComponent - Internal Symbian test code
*/

#include <coeaui.h>
#include <coemain.h>
#include <coecntrl.h>
#include <coedef.h>
#include <coesndpy.h>
#include <coefont.h>
#include <gdi.h>
#include <basched.h>
#include <bassnd.h>
#include <ecom/ecom.h>
#include "TConeBackground.h"

//! Text Displayed on the background of the control.\n
_LIT(KConeBackgroundTestText, "Hello, world");

//! A CCoeControl derived class.\n

/**   The class is used as a control to test background drawing feature.\n */

class CConeBackgroundTestControl : public CCoeControl
    {
public:
	static CConeBackgroundTestControl* NewL(const CCoeControl& aParent, const TRect& aRect);
	CConeBackgroundTestControl();
	~CConeBackgroundTestControl();
    void ConstructL(const CCoeControl& aParent, const TRect& aRect);
private:
	           // Inherited from CCoeControl
	void Draw(const TRect& /*aRect*/) const;

private:
	HBufC*  iConeBackgroundTestText;
	TCoeFont iFont;
    };


//! A CBase and MCoeControlBackground derived class.\n

/**  The class is used as a Dummy base class for the three background drawers */

class CConeBackgroundTestDrawer : public CBase, public MCoeControlBackground
	{
	};

//! A CConeBackgroundTestDrawer derived class.\n
/**   First Background drawer class  */
// Three Background drawer classes with different styles...
class CConeBackgroundTestDrawer0 : public CConeBackgroundTestDrawer
	{
public:
	static CConeBackgroundTestDrawer0* NewL();
	void SetBgStyle(int aStyle);
	
private:
	void Draw(CWindowGc& aGc, const CCoeControl& aControl, const TRect& aRect) const;
	
private:
	TInt iBgStyle;
	};
//! A CConeBackgroundTestDrawer derived class.\n
/**   Second Background drawer class  */
class CConeBackgroundTestDrawer1 : public CConeBackgroundTestDrawer
	{
public:
	static CConeBackgroundTestDrawer1* NewL();
	
private:
	void Draw(CWindowGc& aGc, const CCoeControl& aControl, const TRect& aRect) const;
	};
//! A CConeBackgroundTestDrawer derived class.\n
/**   Third Background drawer class  */
class CConeBackgroundTestDrawer2 : public CConeBackgroundTestDrawer
	{
public:
	static CConeBackgroundTestDrawer2* NewL();
	
public:
	void Draw(CWindowGc& aGc, const CCoeControl& aControl, const TRect& aRect) const;
	};
//! A CoeControl Derived Class.\n
/**    A parent control  that does not draw a background for component controls.\n */
class CConeBackgroundTestParentWithNoBg : public CCoeControl
    {
public:
	static CConeBackgroundTestParentWithNoBg* NewL(const CCoeControl& aParent, const TRect& aRect);
	~CConeBackgroundTestParentWithNoBg();
	
private:
    void ConstructL(const CCoeControl& aParent, const TRect& aRect);
 
public:	// From CCoeControl
	TInt CountComponentControls() const;
	CCoeControl* ComponentControl(TInt aIndex) const;

private: // From CCoeControl
	void Draw(const TRect& aRect) const;

private:
	CCoeControl* iChildControl1;
	CCoeControl* iChildControl2;
    };

//! A CoeControl Derived Class.\n
/**    A parent control  that does draws a background for component controls.\n */
class CConeBackgroundTestParentWithBg : public CCoeControl
    {
public:
	static CConeBackgroundTestParentWithBg* NewL(const CCoeControl& aParent, const TRect& aRect,
									  CConeBackgroundTestDrawer* aDrawer, TBool aUseDummyCtrl = EFalse);
	~CConeBackgroundTestParentWithBg();
	
	void SetSecondary(CCoeControl* aSecondary);
	
private:
	CConeBackgroundTestParentWithBg(CConeBackgroundTestDrawer* aDrawer, TBool aUseDummyCtrl);
    void ConstructL(const CCoeControl& aParent, const TRect& aRect);
 
public:	// From CCoeControl
	TInt CountComponentControls() const;
	CCoeControl* ComponentControl(TInt aIndex) const;

private: // From CCoeControl
	void Draw(const TRect& aRect) const;

private:
	TBool iUseDummyCtrl;
	CCoeControl* iChildControl;
	CCoeControl* iSecondary;
	CConeBackgroundTestDrawer *iBgDrawer;
    };
    
//! A CoeControl Derived Class.\n
/**    A parent window owning control  that draws a background for component controls.\n */
class CConeBackgroundTestParentWindowOwning : public CCoeControl
    {
public:
    static CConeBackgroundTestParentWindowOwning* NewL(const CCoeControl& aParent, const TRect& aRect,
    	   CConeBackgroundTestDrawer* aDrawer);
    ~CConeBackgroundTestParentWindowOwning();
    	
private:
    CConeBackgroundTestParentWindowOwning(CConeBackgroundTestDrawer* aDrawer);
    void ConstructL(const CCoeControl& aParent, const TRect& aRect);
     
public:	// From CCoeControl
    TInt CountComponentControls() const;
    CCoeControl* ComponentControl(TInt aIndex) const;

private: // From CCoeControl
    void Draw(const TRect& aRect) const;

private:
    CCoeControl* iChildControl;
    CConeBackgroundTestDrawer *iBgDrawer;
    };
    
//! A CCoeControl derived class.\n

/**   The class is used as a non window owning control to test background drawing feature.\n */

class CConeBackgroundTestNonWindowOwningControl : public CCoeControl
    {
public:
	static CConeBackgroundTestNonWindowOwningControl* NewL(const CCoeControl& aParent, const TRect& aRect);
	CConeBackgroundTestNonWindowOwningControl();
	~CConeBackgroundTestNonWindowOwningControl();
    void ConstructL(const CCoeControl& aParent, const TRect& aRect);
private:
	           // Inherited from CCoeControl
	void Draw(const TRect& /*aRect*/) const;
    };    
        
//! A CoeControl Derived Class.\n

/**    View Class for TConeBackground Test Step.\n */

class CConeBackgroundTestView : public CCoeControl
    {
public:
	static CConeBackgroundTestView* NewL();
	CConeBackgroundTestView();
	~CConeBackgroundTestView();
    void ConstructL();
    
    void Test1L();
    void Test2L();
    void Test3L();
    void Test4L();

    TInt CountComponentControls() const;
    CCoeControl* ComponentControl(TInt aIndex) const;

private:
	           // Inherited from CCoeControl
	void Draw(const TRect& /*aRect*/) const;

private:
	CCoeControl* iControl;
	CConeBackgroundTestDrawer0* iBgDrawer;
    };


//
//
// CConeBackgroundTestControl
//
//
/**  Constructor for CConeBackgroundTestControl class.\n
	 Initializes the font for the control.\n
*/
CConeBackgroundTestControl::CConeBackgroundTestControl():
iFont(TCoeFont::NormalFont())
	{
	}
/**  Static NewL function used to instantiate a CConeBackgroundTestControl object.\n
	 Creates a CConeBackgroundTestControl object and invokes the second phase constructor.\n
*/
CConeBackgroundTestControl* CConeBackgroundTestControl::NewL(const CCoeControl& aParent, const TRect& aRect)
	{
	CConeBackgroundTestControl* self = new(ELeave) CConeBackgroundTestControl();
	CleanupStack::PushL(self);
	self->ConstructL(aParent, aRect);
	CleanupStack::Pop();
	return self;
	}
/**
  Destructor for CConeBackgroundTestControl class.\n
*/ 
CConeBackgroundTestControl::~CConeBackgroundTestControl()
	{
	delete iConeBackgroundTestText;
	}
/**
  Second phase constructor for CConeBackgroundTestControl class.\n
  Sets the container window to the argument aParent.\n
  Sets the control's extenti.e; dimensions to aRect.\n
*/ 
void CConeBackgroundTestControl::ConstructL(const CCoeControl& aParent, const TRect& aRect)
    {
//	iConeBackgroundTestText = iCoeEnv->AllocReadResourceL(R_ConeBackgroundTest_TEXT_ZOOM);
    SetContainerWindowL(aParent);
    SetRect(aRect);
	iConeBackgroundTestText = KConeBackgroundTestText().AllocL();
	}
/**
  Draws the CConeBackgroundTestControl object.\n
  Gets a pointer to the Windows Graphic context.
  Sets the pen colour,pen style and brush style settings.\n
  Draws the control using DrawRect function of the Graphics context.\n
*/
void CConeBackgroundTestControl::Draw(const TRect& /*aRect*/) const
	{
	CWindowGc& gc = SystemGc();
	TRect      drawRect = Rect();
	
	drawRect.Shrink(2*drawRect.Width()/5, 2*drawRect.Width()/5);
	
	gc.SetPenStyle(CGraphicsContext::ENullPen);
	gc.SetBrushColor(TRgb(0x000000));
	gc.SetBrushStyle(CGraphicsContext::EDiamondCrossHatchBrush);
	gc.DrawRect(drawRect);
	}

//
//
// CConeBackgroundTestDrawer0
//
//
/**
  Instantiates a CConeBackgroundTestDrawer0 object.\n
*/
CConeBackgroundTestDrawer0* CConeBackgroundTestDrawer0::NewL()
	{
	CConeBackgroundTestDrawer0* self = new (ELeave) CConeBackgroundTestDrawer0();
	return self;
	}
/**
  Sets the iBgStyle, indicating background style for Drawing to aStyle.\n
*/
void CConeBackgroundTestDrawer0::SetBgStyle(int aStyle)
	{
	if (aStyle >= 0 && aStyle < 4)
		iBgStyle = aStyle;
	}
/**
  Draw function of CConeBackgroundTestDrawer2 class used to draw the control.\n
  Sets the background style for Drawing.\n
  1. if aStyle is zero , the brush style is EVerticalHatchBrush.\n
  2. if aStyle is one , the brush style is EForwardDiagonalHatchBrush.\n
  3. if aStyle is two , the brush style is EHorizontalHatchBrush.\n
  4. if aStyle is three , the brush style is ERearwardDiagonalHatchBrush.\n
  Sets the brush colour to Red and paints the top left part of the control.\n
  Sets the brush colour and points the bottom right part of the control.\n
*/
void CConeBackgroundTestDrawer0::Draw(CWindowGc& aGc, const CCoeControl& /*aControl*/, const TRect& aRect) const
	{
	aGc.SetPenStyle(CGraphicsContext::ENullPen);
	aGc.SetBrushColor(TRgb(0xffffff));
	aGc.Clear();

	switch (iBgStyle)
		{
		case 0:
			aGc.SetBrushStyle(CGraphicsContext::EVerticalHatchBrush);
			break;
			
		case 1:
			aGc.SetBrushStyle(CGraphicsContext::EForwardDiagonalHatchBrush);
			break;
			
		case 2:
			aGc.SetBrushStyle(CGraphicsContext::EHorizontalHatchBrush);
			break;
			
		case 3:
			aGc.SetBrushStyle(CGraphicsContext::ERearwardDiagonalHatchBrush);
			break;
		}

	aGc.SetPenColor(TRgb(0xff0000));
	aGc.DrawRect(aRect);
	
	TRect tlRect = aRect;
	tlRect.iBr.iX = (tlRect.iBr.iX - tlRect.iTl.iX)/2 + tlRect.iTl.iX;
	tlRect.iBr.iY = (tlRect.iBr.iY - tlRect.iTl.iY)/2 + tlRect.iTl.iY;
	
	aGc.SetBrushColor(TRgb(0xff00ff));
	aGc.DrawRect(tlRect);
	
	TRect brRect = tlRect;
	brRect.Move(tlRect.Width(), tlRect.Height());
	aGc.SetBrushColor(TRgb(0x00ff00));
	aGc.DrawRect(brRect);
	}

//
//
// CConeBackgroundTestDrawer1
//
//
/**
  Instantiates a CConeBackgroundTestDrawer1 object.\n
  
  @return : Pointer to CConeBackgroundTestDrawer1 object.\n
*/
CConeBackgroundTestDrawer1* CConeBackgroundTestDrawer1::NewL()
	{
	CConeBackgroundTestDrawer1* self = new (ELeave) CConeBackgroundTestDrawer1();
	return self;
	}
/**
  Draw function of CConeBackgroundTestDrawer2 class used to draw the control.\n
  Sets the brush style to Solid Brush and Pen Style to Null Pen.\n
  Sets the brush colour to Red and paints the top left part of the control.\n
  Sets the brush colour and points the bottom right part of the control.\n
*/
void CConeBackgroundTestDrawer1::Draw(CWindowGc& aGc, const CCoeControl& /*aControl*/, const TRect& aRect) const
	{
	
	aGc.SetBrushStyle(CGraphicsContext::ESolidBrush);
	aGc.SetPenStyle(CGraphicsContext::ENullPen);
	
	TRect tlRect = aRect;
	tlRect.iBr.iX = (tlRect.iBr.iX - tlRect.iTl.iX)/2 + tlRect.iTl.iX;
	tlRect.iBr.iY = (tlRect.iBr.iY - tlRect.iTl.iY)/2 + tlRect.iTl.iY;
	
	aGc.SetBrushColor(TRgb(0xff0000));
	aGc.DrawRect(tlRect);
	
	TRect brRect = tlRect;
	brRect.Move(tlRect.Width(), tlRect.Height());
	aGc.SetBrushColor(TRgb(0x00ff00));
	aGc.DrawRect(brRect);
	}

//
//
// CConeBackgroundTestDrawer2
//
//
/**
  Instantiates a CConeBackgroundTestDrawer2 object.\n
  
  @return : Pointer to CConeBackgroundTestDrawer2 object.\n
*/
CConeBackgroundTestDrawer2* CConeBackgroundTestDrawer2::NewL()
	{
	CConeBackgroundTestDrawer2* self = new (ELeave) CConeBackgroundTestDrawer2();
	return self;
	}
/**
  Draw function of CConeBackgroundTestDrawer2 class used to draw the control.\n
  Sets the brush style to Solid Brush and Pen Style to Null Pen.\n
  Sets the brush colour to Blue and paints an ellipse on  the control.\n
*/
void CConeBackgroundTestDrawer2::Draw(CWindowGc& aGc, const CCoeControl& /*aControl*/, const TRect& aRect) const
	{
	aGc.SetBrushStyle(CGraphicsContext::ESolidBrush);
	aGc.SetPenStyle(CGraphicsContext::ENullPen);
	aGc.SetBrushColor(TRgb(0x0000ff));
	aGc.DrawEllipse(aRect);
	}

//
//
// CConeBackgroundTestParentWithNoBg
//
//
/**
  Creates a parent control with no support for background drawing.\n
  Calls second phase constructor of CConeBackgroundTestParentWithNoBg.\n
*/
CConeBackgroundTestParentWithNoBg* CConeBackgroundTestParentWithNoBg::NewL(const CCoeControl& aParent, const TRect& aRect)
	{
	CConeBackgroundTestParentWithNoBg* self = new(ELeave) CConeBackgroundTestParentWithNoBg();
	CleanupStack::PushL(self);
	self->ConstructL(aParent, aRect);
	CleanupStack::Pop();
	return self;
	}
/**
  Destructor for CConeBackgroundTestParentWithNoBg class.\n
  Deletes the two child controls owned by the parent object.\n
*/
CConeBackgroundTestParentWithNoBg::~CConeBackgroundTestParentWithNoBg()
	{
	delete iChildControl1;
	delete iChildControl2;
	}
/**
  Returns the number of component controls contained by the parent control.\n
 
  @return 2.\n
*/
TInt CConeBackgroundTestParentWithNoBg::CountComponentControls() const
	{
	return 2;
	}
/**
  Returns the component control at the index 'aIndex' .\n
  
  @return CCoeControl*, if aIndex is zero iChildControl1 is returned else iChildControl2.\n
*/	
CCoeControl* CConeBackgroundTestParentWithNoBg::ComponentControl(TInt aIndex) const
	{
	return aIndex == 0 ? iChildControl1 : iChildControl2;
	}
/**
  Second phase constructor for CConeBackgroundTestParentWithNoBg class.\n
  Sets a container window for component control, if the container is a window-owning control.\n
  Creates two child controls, first one is placed at the top left while other is at the bottom right.\n
*/
void CConeBackgroundTestParentWithNoBg::ConstructL(const CCoeControl& aParent, const TRect& aRect)
    {
    SetContainerWindowL(aParent);
    SetRect(aRect);
	TRect tlRect = aRect;
	tlRect.iBr.iX = (aRect.iBr.iX - aRect.iTl.iX)/2 + aRect.iTl.iX;
	tlRect.iBr.iY = (aRect.iBr.iY - aRect.iTl.iY)/2 + aRect.iTl.iY;
	iChildControl1 = CConeBackgroundTestControl::NewL(*this, tlRect);
	TRect brRect = tlRect;
	brRect.Move(tlRect.Width(), tlRect.Height());
	iChildControl2 = CConeBackgroundTestControl::NewL(*this, brRect);
	}
/**
  Draw function for CConeBackgroundTestParentWithNoBg class.\n
*/
void CConeBackgroundTestParentWithNoBg::Draw(const TRect& /*aRect*/) const
	{
	}

//
//
// CConeBackgroundTestParentWithBg
//
//
/**
  Constructor for CConeBackgroundTestParentWithBg class.\n
  Initializes the drawer class and Dummy control member variables.\n
*/
CConeBackgroundTestParentWithBg::CConeBackgroundTestParentWithBg(CConeBackgroundTestDrawer* aDrawer, TBool aUseDummyCtrl) :
	iUseDummyCtrl(aUseDummyCtrl),
	iBgDrawer(aDrawer)
	{
	}
/**
  Creates a parent control with support for background drawing.\n
  Calls second phase constructor of CConeBackgroundTestParentWithBg.\n
*/
CConeBackgroundTestParentWithBg* CConeBackgroundTestParentWithBg::NewL(const CCoeControl& aParent, const TRect& aRect,
												 CConeBackgroundTestDrawer* aDrawer, TBool aUseDummyCtrl)
	{
	CConeBackgroundTestParentWithBg* self = new(ELeave) CConeBackgroundTestParentWithBg(aDrawer, aUseDummyCtrl);
	CleanupStack::PushL(self);
	self->ConstructL(aParent, aRect);
	CleanupStack::Pop();
	return self;
	}
/**
  The control with background drawing is set as secondary control.\n
  This creates a scenario of both parent and child controls supporting background drawing.\n
*/	
void CConeBackgroundTestParentWithBg::SetSecondary(CCoeControl* aSecondary)
	{
	delete iSecondary;
	iSecondary = aSecondary;
	}
/**
  Destructor for CConeBackgroundTestParentWithBg class.\n
  Deletes the child control and drawer class owned by the parent object.\n
*/
CConeBackgroundTestParentWithBg::~CConeBackgroundTestParentWithBg()
	{
	delete iChildControl;
	delete iSecondary;
	delete iBgDrawer;
	}
/**
  Returns the number of component controls contained by the parent control.\n
 
  @return if iSecondary then 2 else 1.\n
*/
TInt CConeBackgroundTestParentWithBg::CountComponentControls() const
	{
	return iSecondary ? 2 : 1;
	}
/**
  Returns the component control at the index 'aIndex' .\n
  
  @return CCoeControl*, if aIndex is zero iChildControl1 is returned else iSecondary.\n
*/	
CCoeControl* CConeBackgroundTestParentWithBg::ComponentControl(TInt aIndex) const
	{
	return aIndex ? iSecondary : iChildControl;
	}
/**
  Second phase constructor for CConeBackgroundTestParentWithBg class.\n
  Sets the control's container window.\n
  Sets the control's extent, specifying a TRect.\n
  if the dummycontrol is ETrue, then CConeBackgroundTestParentWithNoBg object is instantiated as child control,\n
  else CConeBackgroundTestControl object is used.\n
  iBgDrawer object is set as the object responsible for drawing control's background.\n
*/
void CConeBackgroundTestParentWithBg::ConstructL(const CCoeControl& aParent, const TRect& aRect)
    {
    SetContainerWindowL(aParent);
    SetRect(aRect);
    if (iUseDummyCtrl)
    	iChildControl = CConeBackgroundTestParentWithNoBg::NewL(*this, aRect);
    else
		iChildControl = CConeBackgroundTestControl::NewL(*this, aRect);

	SetBackground(iBgDrawer);
	}
/**
  Draw function for CConeBackgroundTestParentWithBg Class.\n
  Does Nothing.\n
*/
void CConeBackgroundTestParentWithBg::Draw(const TRect& /*aRect*/) const
	{
	}

//
//
// CConeBackgroundTestParentWindowOwning
//
//

CConeBackgroundTestParentWindowOwning::CConeBackgroundTestParentWindowOwning(CConeBackgroundTestDrawer* aDrawer) :
	iBgDrawer(aDrawer)
	{
	}

CConeBackgroundTestParentWindowOwning* CConeBackgroundTestParentWindowOwning::NewL(const CCoeControl& aParent, const TRect& aRect,
												 CConeBackgroundTestDrawer* aDrawer)
	{
	CConeBackgroundTestParentWindowOwning* self = new(ELeave) CConeBackgroundTestParentWindowOwning(aDrawer);
	CleanupStack::PushL(self);
	self->ConstructL(aParent, aRect);
	CleanupStack::Pop();
	return self;
	}

CConeBackgroundTestParentWindowOwning::~CConeBackgroundTestParentWindowOwning()
	{
	delete iChildControl;
	delete iBgDrawer;
	}

CCoeControl* CConeBackgroundTestParentWindowOwning::ComponentControl(TInt aIndex) const
	{
	if (!aIndex)
		return iChildControl;
	else
		return NULL;
	}
	
TInt CConeBackgroundTestParentWindowOwning::CountComponentControls() const
	{
	return 1;
	}
		
void CConeBackgroundTestParentWindowOwning::ConstructL(const CCoeControl& aParent, const TRect& aRect)
    {
    CreateWindowL(&aParent);
    SetRect(aRect);
    iChildControl = CConeBackgroundTestNonWindowOwningControl::NewL(*this, aRect);
    SetBackground(iBgDrawer);
	}

void CConeBackgroundTestParentWindowOwning::Draw(const TRect& aRect) const
	{
	CWindowGc& aGc = SystemGc();
	aGc.SetBrushStyle(CGraphicsContext::ERearwardDiagonalHatchBrush);
	aGc.SetPenStyle(CGraphicsContext::ENullPen);
	
	TRect tlRect = aRect;
	tlRect.iBr.iX = (tlRect.iBr.iX - tlRect.iTl.iX)/2 + tlRect.iTl.iX;
	tlRect.iBr.iY = (tlRect.iBr.iY - tlRect.iTl.iY)/2 + tlRect.iTl.iY;
	
	aGc.SetBrushColor(TRgb(0xff0000)); //blue, to be changed or removed
	aGc.DrawRect(tlRect);
	
	TRect brRect = tlRect;
	brRect.Move(tlRect.Width(), tlRect.Height());
	aGc.SetBrushColor(TRgb(0xffffff)); //white , to be changed or removed
	aGc.DrawRect(brRect);
	}

//
//
// CConeBackgroundTestNonWindowOwningControl
//
//

CConeBackgroundTestNonWindowOwningControl::CConeBackgroundTestNonWindowOwningControl()
	{
	}

CConeBackgroundTestNonWindowOwningControl* CConeBackgroundTestNonWindowOwningControl::NewL(const CCoeControl& aParent, const TRect& aRect)
	{
	CConeBackgroundTestNonWindowOwningControl* self = new(ELeave) CConeBackgroundTestNonWindowOwningControl();
	CleanupStack::PushL(self);
	self->ConstructL(aParent, aRect);
	CleanupStack::Pop();
	return self;
	}

CConeBackgroundTestNonWindowOwningControl::~CConeBackgroundTestNonWindowOwningControl()
	{
	}

void CConeBackgroundTestNonWindowOwningControl::ConstructL(const CCoeControl& aParent, const TRect& aRect)
    {
    SetContainerWindowL(aParent);
    SetRect(aRect);
	}

void CConeBackgroundTestNonWindowOwningControl::Draw(const TRect& /*aRect*/) const /*needs to be customised*/
	{
	CWindowGc& gc = SystemGc();
	TRect      drawRect = Rect();
	
	drawRect.Shrink(2*drawRect.Width()/5, 2*drawRect.Width()/5);
	
	gc.SetPenStyle(CGraphicsContext::ENullPen);
	gc.SetBrushStyle(CGraphicsContext::EDiamondCrossHatchBrush);
	gc.SetBrushColor(TRgb(0x00ff00));
	gc.DrawRect(drawRect);
	}

//
//
// CConeBackgroundTestView
//
//
/**
  Constructor for CConeBackgroundTestView Class.\n
*/
CConeBackgroundTestView::CConeBackgroundTestView()
	{
	}
/**
  The static function is used to create a CConeBackgroundTestView object.\n
  Creates a new CConeBackgroundTestView object and calls the second phase constructor.\n
*/ 
CConeBackgroundTestView* CConeBackgroundTestView::NewL()
	{
	CConeBackgroundTestView* self = new(ELeave) CConeBackgroundTestView();
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop();
	return self;
	}

/**
  Destructor for CConeBackgroundTestView Class.\n
  Deletes the child controls and the drawer object.\n
*/
CConeBackgroundTestView::~CConeBackgroundTestView()
	{
	delete iControl;
	delete iBgDrawer;
	}
/**
  Returns the number of component controls contained by the parent control.\n
 
  @return 1.\n
*/
    
TInt CConeBackgroundTestView::CountComponentControls() const
	{
	return 1;
	}
/**
  Returns the component control at the index 'aIndex' .\n
  
  @return iControl.\n
*/
CCoeControl* CConeBackgroundTestView::ComponentControl(TInt /*aIndex*/) const
	{
	return iControl;
	}
/**
  @SYMTestCaseID UIF-TConeBackground-Test1L
 
  @SYMPREQ
 
  @SYMTestCaseDesc 
 
  @SYMTestPriority High
 
  @SYMTestStatus Implemented
  
  @SYMTestActions : Sets the background brush style to EVerticalHatchBrush.\n
  Instantiates a parent control (CConeBackgroundTestParent) which has capability of background drawing.\n
  Activates the Parent control.\n
  Invokes the DrawNow function for the View class which calls Draw() on the control itself,\n
  and also on all its component controls.\n.
  
  @SYMTestExpectedResults : The draw should complete with out any error.\n
 
  @SYMTestType : CIT
*/
void CConeBackgroundTestView::Test1L()
	{
	delete iControl;
	iControl = 0;

	iBgDrawer->SetBgStyle(1);
	iControl = CConeBackgroundTestParentWithBg::NewL(*this, Rect(),
				CConeBackgroundTestDrawer1::NewL(), ETrue);
	
	iControl->ActivateL();
	DrawNow();
	}
/**
  @SYMTestCaseID UIF-TConeBackground-Test2L
 
  @SYMPREQ
 
  @SYMTestCaseDesc Tests MCoeControlBackground when both parent and child
  controls support background drawing.\n
 
  @SYMTestPriority High
 
  @SYMTestStatus Implemented
  
  @SYMTestActions : Sets the background brush style to EVerticalHatchBrush.\n
  Instantiates a parent control (CConeBackgroundTestParent) which has capability of background drawing.\n
  Activates the Parent control.\n
  Also instantiates a secondary control of class CConeBackgroundTestParentWithBg.\n
  This test enables testing of the MCoeControlBackground interface when both parent and child controls \n
  are background drawing supported controls.\n
  Invokes the DrawNow function for the View class which calls Draw() on the control itself,\n
  and also on all its component controls.\n
  
  @SYMTestExpectedResults : The draw should complete with out any error.\n
 
  @SYMTestType : CIT
*/
void CConeBackgroundTestView::Test2L()
	{
	delete iControl;
	iControl = 0;

	iBgDrawer->SetBgStyle(2);
	iControl = CConeBackgroundTestParentWithBg::NewL(*this, Rect(),
				CConeBackgroundTestDrawer1::NewL(), EFalse);
	TRect rect = Rect();
	rect.Shrink(rect.Width()/8, rect.Height()/8);
	CCoeControl* temp = CConeBackgroundTestParentWithBg::NewL(*iControl, rect, CConeBackgroundTestDrawer2::NewL());
	static_cast<CConeBackgroundTestParentWithBg*>(iControl)->SetSecondary(temp);
	iControl->ActivateL();
	DrawNow();
	}
/**
  @SYMTestCaseID UIF-TConeBackground-Test3L
 
  @SYMPREQ
 
  @SYMTestCaseDesc Tests MCoeControlBackground when a parent control has two 
  child controls,one supporting background drawing and the other without that support.\n
 
  @SYMTestPriority High
 
  @SYMTestStatus Implemented
  
  @SYMTestActions : Sets the background brush style to EVerticalHatchBrush.\n
  Instantiates a parent control (CConeBackgroundTestParent) which has capability of background drawing.\n
  Activates the Parent control.\n
  Also instantiates a secondary control of class CConeBackgroundTestParentWithBg.\n
  Later a third control without background drawing is instantiated.\n
  Thus a scenario of parent control containing child controls with and without background drawing support
  is created and tested.\n
  Invokes the DrawNow function for the View class which calls Draw() on the control itself,\n
  and also on all its component controls.\n
  
  @SYMTestExpectedResults : The draw should complete with out any error.\n
 
  @SYMTestType : CIT
*/
void CConeBackgroundTestView::Test3L()
	{
	delete iControl;
	iControl = 0;

	iBgDrawer->SetBgStyle(3);
	iControl = CConeBackgroundTestParentWithBg::NewL(*this, Rect(),
				CConeBackgroundTestDrawer1::NewL(), ETrue);
	TRect rect = Rect();
	rect.Shrink(rect.Width()/8, rect.Height()/8);
	CCoeControl* temp = CConeBackgroundTestParentWithBg::NewL(*iControl, rect, CConeBackgroundTestDrawer2::NewL());
	static_cast<CConeBackgroundTestParentWithBg*>(iControl)->SetSecondary(temp);
	iControl->ActivateL();
	DrawNow();
	}

/**
  @SYMTestCaseID UIF-TConeBackground-Test4L
 
  @SYMDEF PDEF112327
 
  @SYMTestCaseDesc Tests MCoeControlBackground, when a parent window owning control has one 
  child control not supporting background drawing and non window owning.\n
 
  @SYMTestPriority Critical
 
  @SYMTestStatus Implemented
  
  @SYMTestActions : Sets the background draw style.\n
  Instantiates a parent control (CConeBackgroundTestParent) which has capability of background drawing.\n
  After a new screen device has been instantiated,instantiates a second graphics context and assigns it to the child control.\n
  Thus a scenario of parent control and child control with different graphics context is created and tested.\n
  Activates the parent and child control\n
  Invokes the DrawNow function for the NonWindowOwningControl class which results in calling Draw() and DrawComponets() on the parent control itself.\n 
  
  @SYMTestType Manual
  @SYMTestExpectedResults : The background drawing should use the parent graphics context. \n
  All the test code does is to exercise the defect fix and thus the draw should complete without any error.\n
  */
void CConeBackgroundTestView::Test4L()
	{
	delete iControl;
	iControl = 0;
	
	iBgDrawer->SetBgStyle(1);
	iControl = CConeBackgroundTestParentWindowOwning::NewL(*this, Rect(),
				CConeBackgroundTestDrawer2::NewL());
	
	// create a new Gc
	CWsScreenDevice* screenDevice = new (ELeave) CWsScreenDevice((iControl->ControlEnv())->WsSession()); 
	CleanupStack::PushL(screenDevice);
	User::LeaveIfError(screenDevice->Construct());
	
	CWindowGc* gc=new(ELeave) CWindowGc(screenDevice);
	CleanupStack::PushL(gc);
	User::LeaveIfError(gc->Construct());
	
	gc->Activate(Window());
	(iControl->ComponentControl(0))->SetCustomGc(gc);
	gc->Deactivate();
	
	TSize rectSize(90,200);
	iControl->SetSize(rectSize);
	(iControl->ComponentControl(0))->SetSize(rectSize);
	
	iControl->ActivateL();
	(iControl->ComponentControl(0))->ActivateL();
	(iControl->ComponentControl(0))->DrawNow(); 
	
	CleanupStack::PopAndDestroy(gc);
	CleanupStack::PopAndDestroy(screenDevice);
	}

/**
  Second phase constructor for CConeBackgroundTestView Class.\n
  Creates a Window for the View.\n
  Creates a parent control with background support.\n
  The parent control is activated.\n
*/
void CConeBackgroundTestView::ConstructL()
    {
	CreateWindowL();
	iControl = CConeBackgroundTestParentWithBg::NewL(*this, Rect(), CConeBackgroundTestDrawer1::NewL());

	iBgDrawer = CConeBackgroundTestDrawer0::NewL();
	SetBackground(iBgDrawer);
	ActivateL();
	}
/**
  Draw function for CConeBackgroundTestView class.\n
  Does Nothing.\n
*/ 
void CConeBackgroundTestView::Draw(const TRect& /*aRect*/) const
	{
	}

//
//
// CConeBackgroundTestAppUi
//
//
/**
  Constructor for CConeBackgroundTestAppUi class.\n
  Sets the Test step Name.\n
*/
CConeBackgroundTestAppUi::CConeBackgroundTestAppUi(CTmsTestStep* aStep) :
CTestCoeAppUi(aStep)
{}
/**
  Destructor for CConeBackgroundTestAppUi class.\n
  Deletes the view.\n
*/
CConeBackgroundTestAppUi::~CConeBackgroundTestAppUi()
	{
	delete iView;
	}

/**
  Second phase constructor for the CConeBackgroundTestAppUi class.\n
  Invokes the base class CTestCoeAppUi ConstructL function.\n
  Creates a View.\n
  Starts the asynchronous execution of tests using Auto test manager.\n
*/ 
void CConeBackgroundTestAppUi::ConstructL()
	{
	CTestCoeAppUi::ConstructL();
	
	iView = CConeBackgroundTestView::NewL();
	
	AutoTestManager().StartAutoTest();
	}
/**
  Auxilliary Function for all test cases.\n
  This function is iteratively called by the RunL function of the Autotestmanager
  asynchronously.\n
  Calls the following function\n
  1. CConeBackgroundTestView::Test1L() - Tests .\n
  2. CConeBackgroundTestView::Test2L().\n
  3. CConeBackgroundTestView::Test3L().\n
*/	
void CConeBackgroundTestAppUi::RunTestStepL(TInt aStepNum)
	{

	User::After(TTimeIntervalMicroSeconds32(1000000));
	
	TInt err;

	switch(aStepNum)
		{
		case 1:
			SetTestStepID(_L("UIF-TConeBackground-Test1L"));
			INFO_PRINTF1(_L("Parent control supports background drawing"));
			TRAP(err, iView->Test1L());
			TEST(err==KErrNone);
			RecordTestResultL();
			break;
		case 2:
			SetTestStepID(_L("UIF-TConeBackground-Test2L"));
			INFO_PRINTF1(_L("Parent control and child control support background drawing"));
			TRAP(err, iView->Test2L());
			TEST(err==KErrNone);
			RecordTestResultL();
			break;
		case 3:
			SetTestStepID(_L("UIF-TConeBackground-Test3L"));
			INFO_PRINTF1(_L("Parent control contains child controls with and without background drawing support"));
			TRAP(err, iView->Test3L());
			TEST(err==KErrNone);
			RecordTestResultL();
			break;
		case 4:
			SetTestStepID(_L("UIF-TConeBackground-Test4L"));
			INFO_PRINTF1(_L("Parent control contains child control with different Graphics Context."));
			TRAP(err, iView->Test4L());
			TEST(err==KErrNone);
			RecordTestResultL();
			CloseTMSGraphicsStep();
			break;
		case 5:
			AutoTestManager().FinishAllTestCases(CAutoTestManager::EPass);
			break;
		}
	}

//
//
// CConeBackgroundTestStep
//
//
/**
  Completes the construction of the Control Environment(CCoeEnv object).\n
  Instantiates the CCone6TestAppUi class which serves as a AppUi class.\n
  Sets the CCone6TestAppUi object as the application's user interface object.\n
  Invokes the second phase constructor of the application's UI.\n
*/
void CTConeBackgroundStep::ConstructAppL(CCoeEnv* aCoe)
	{ // runs inside a TRAP harness
	aCoe->ConstructL();
	CConeBackgroundTestAppUi* appUi= new (ELeave) CConeBackgroundTestAppUi(this);
	aCoe->SetAppUi(appUi);
	appUi->ConstructL();
	}
/**
  Constructor for CTConeBackgroundStep class.\n
  Sets the test step name.\n
*/
CTConeBackgroundStep::CTConeBackgroundStep()
	{
	SetTestStepName(KTBackgroundStep);
	}
/**
  Destructor for CTConeBackgroundStep class.\n
*/
CTConeBackgroundStep::~CTConeBackgroundStep()
{}

/**
  Entry function for CTConeBackGround Test Step.\n
  Sets up the control environment.\n
  Constructs and Launches the CTCone5 Test application.\n
*/
TVerdict CTConeBackgroundStep::doTestStepL() // main function called by E32
	{
	INFO_PRINTF1(_L("Test Started"));
	
	PreallocateHALBuffer();

	__UHEAP_MARK;

	CCoeEnv* coe=new(ELeave) CCoeEnv;
	TRAPD(err,ConstructAppL(coe));

	if (!err)
		coe->ExecuteD();
	else
		{
		SetTestStepResult(EFail);
		delete coe;
		}

	REComSession::FinalClose();	

	__UHEAP_MARKEND;

	INFO_PRINTF1(_L("Test Finished"));
	return TestStepResult();
	}






