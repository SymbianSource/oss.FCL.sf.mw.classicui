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


#ifndef __TCONE7STEP_H__
#define __TCONE7STEP_H__

#include <test/testexecutestepbase.h>

#include <coecntrl.h>
#include <coeaui.h>
#include <coemain.h>
#include <coedef.h>
#include <coesndpy.h>
#include <basched.h>
#include <bassnd.h>
#include <ecom/ecom.h>
#include <gdi.h>
#include <eikenv.h>

#include "TConeTestServer.h"
#include "appfwk_test_AppUi.h"


#define KRgbInherited KRgbRed

_LIT( KInheritedTextDrawerText, "Inherited TD" );
_LIT( KLocalTextDrawerText, "Local TD"  );

_LIT(KMultipleLineText, "Test multi-lines\nTODO block\nimplemented as part of\nDEF091556 defect fix");
_LIT(KMultipleLineText1, "Test multi-lines\nTODO block\nimplemented as part of\nINC122592 defect fix");


//
// class CCtlBase641
//

class CCtlBase641 : public CCoeControl
	{
public :
	~CCtlBase641();
protected :
	CCtlBase641();
	void WriteName( CWindowGc& aGc, const TDesC& aText ) const;
	void ConstructL();
	void DoDraw( CWindowGc& aGc, TRect aRect ) const;	
protected :
	HBufC* iName;
private :
    CFont* iFont;
	};

//
// class CCtlSuperContainer641
//

class CCtlSubContainer641;
class CCtlSuperContainer641 : public CCtlBase641
	{
public:
	CCtlSuperContainer641();
	~CCtlSuperContainer641();
	void ConstructL( const TDesC& aName );

	void ApplyText() const;	
	void Draw(CWindowGc& /*aGc*/, const CCoeControl& /*aControl*/, const TRect& /*aRect*/) const{}
public:
	CCtlSubContainer641* iSubContainer;	
private:
	virtual void SizeChanged();
	void Draw(const TRect& aRect) const;
	void GetTextDrawer( CCoeTextDrawerBase*& aTextDrawer, const CCoeControl* aDrawingControl, TInt aInt ) const;
private:
	enum
		{
		KChildOneID,
		KChildTwoID,
		KChildThreeID,
		KChildFourID
		};
	};


//
// class 
//

class CCtlContainee641;
class CCtlSubContainer641 : public CCtlBase641
	{
public:
	CCtlSubContainer641();
	~CCtlSubContainer641();
	void ConstructL( const TDesC& aName );

	void ApplyText() const;	
	void Draw(CWindowGc& /*aGc*/, const CCoeControl& /*aControl*/, const TRect& /*aRect*/) const{}
public:
	CCtlContainee641* iContainee;	
private:
	virtual void SizeChanged();
	void Draw(const TRect& aRect) const;
	void GetTextDrawer( CCoeTextDrawerBase*& aTextDrawer, const CCoeControl* aDrawingControl, TInt aInt ) const;
private:
	enum
		{
		KChildOneID,
		KChildTwoID,
		KChildThreeID,
		KChildFourID
		};
	};

//
// class CCtlContainer641
//

class CCtlContainee641;
class CCtlContainer641 : public CCtlBase641//, MCoeControlBackground
	{
public:
	CCtlContainer641();
	~CCtlContainer641();
	void ConstructL( const TDesC& aName );

	void ApplyText() const;	
	void Draw(CWindowGc& /*aGc*/, const CCoeControl& /*aControl*/, const TRect& /*aRect*/) const{}
public:
	CCtlContainee641* iContainee;
private:
	virtual void SizeChanged();
	void Draw(const TRect& aRect) const;
	void GetTextDrawer( CCoeTextDrawerBase*& aTextDrawer, const CCoeControl* aDrawingControl, TInt aInt ) const;
private:
	enum
		{
		KChildOneID,
		KChildTwoID,
		KChildThreeID,
		KChildFourID
		};
	};

//
// class CCtlContainee641
//

class CCtlContainee641 : public CCtlBase641
	{
public:
	CCtlContainee641();
	~CCtlContainee641();
	void ConstructL( const TDesC& aName );
	
	const TDesC& WhoAmI() const;
	TBool TestContainerTextDrawer();
	void ApplyText() const;
private:
	void Draw(const TRect& aRect) const;
	};

//
// class CCtlTestTextDrawer 
//

class CCtlTestTextDrawer : public CCoeControl
	{
public:
	CCtlTestTextDrawer();
	~CCtlTestTextDrawer();
	void ConstructL();
	TBool TestTextDrawer(TInt aTextIndex, TBool aHorizontal, TRect *aClipRect = NULL, TRgb* aTextCol = NULL, TBool aCleanBackground = ETrue, TBool aUp = ETrue);
	void WidthOfText(const TInt aLine, TInt& aWidthInPixels) const;
	const CFont& FontUsed() const;
private:
	CFont* iFont;
	};

//
// class CTCone7Step 
//

class CTCone7Step : public CTmsTestStep
	{
public:
	CTCone7Step();
	~CTCone7Step();
	virtual TVerdict doTestStepL();
	void ConstructAppL(CCoeEnv* aCoe);
	};

//
// class CCone7TestAppUi 
//

class CCone7TestAppUi : public CTestCoeAppUi
    {
public:
	CCone7TestAppUi(CTmsTestStep* aStep);
	~CCone7TestAppUi();
	void ConstructL();
private: // from CCoeAppUi
	TKeyResponse HandleKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
private: // utility
	void RunTestStepL(TInt aStepNum);
	TBool TestTextDrawer_1L(); // test case PREQ641.1
	TBool TestTextDrawer_2L(); // test case PREQ641.2
	TBool TestTextDrawer_3L();
	TBool TestTextDrawer_4L();
	TBool TestTextDrawer_5L(); //test for INC122592
	TBool TestWindowPositionL();
	TBool TestExtentNotSetL();
	TBool TestBackedUpExtentNotSetL();
private:
    };


_LIT(KTCone7Step,"TCone7");

#endif	// __TCONE7STEP_H__


