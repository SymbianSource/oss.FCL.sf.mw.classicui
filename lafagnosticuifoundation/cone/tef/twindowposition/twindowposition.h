// Copyright (c) 2007-2009 Nokia Corporation and/or its subsidiary(-ies).
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

#ifndef		__TWINDOWPOSITION_H
#define		__TWINDOWPOSITION_H

#include <eikappui.h>
#include <eikapp.h>
#include <eikdoc.h>
#include <coecntrl.h>
#include <e32cmn.h>
#include <e32std.h>
#include <test/testexecutestepbase.h>
#include <test/appfwk_test_appui.h>

const TUid KUidCoeControlTestApp={ 0xA0003976 }; //app uid
const TInt KErrWindowPosDoesNotMatch = -1234;

//
// class CCoeConD
//
class CCoeConD : public CCoeControl
    {
public:
    void ConstructL(const CCoeControl& aParent);
    };

//
// class CCoeConB
//
class CCoeConB;
class CCoeConC : public CCoeControl
    {
public:
	CCoeConC(CCoeConB& aParent);
	~CCoeConC();
    void ConstructL();
    void SetViewPortRect(TRect aRect );
    TInt CountComponentControls() const;
    CCoeControl* ComponentControl(TInt aIndex) const;
private:
	// From CCoeControl
	void Draw(const TRect& aRect) const;
private:
	CCoeConB& iParent;
	CCoeConD* iCoeConD;
    };

//
// class CCoeConB
//
class CCoeConB : public CCoeControl
    {
public:
	CCoeConB();
	~CCoeConB();
    void ConstructL(CCoeControl* aParent);
    TInt CountComponentControls() const;
    CCoeControl* ComponentControl(TInt aIndex) const;
    TPoint WindowPos();
private:
	// From CCoeControl
	void Draw(const TRect& /*aRect*/) const;
private:
	CCoeConC* iCoeConC;
    };

//
//
// CCoeConTestView
//
//
class CCoeConTestView : public CCoeControl
    {
public:
	CCoeConTestView();
	~CCoeConTestView();
    void ConstructL(const TRect& aRect);
    void DrawCoeConB() const;
    TInt CountComponentControls() const;
    CCoeControl* ComponentControl(TInt aIndex) const;
private:
	// From CCoeControl
	void Draw(const TRect& /*aRect*/) const;	
private:
	CCoeConB* iCoeControlB;	
    };

//
//
// CCoeConTestAppUi
//
//
class CCoeConTestAppUi : public CTestAppUi
    {
public:
	CCoeConTestAppUi();
	~CCoeConTestAppUi();
    void ConstructL();
private:
	void RunTestStepL(TInt aNumStep);
	void TestWindowPosition();
private:
    CCoeConTestView* iAppView;
	};

//
//
// CCoeConTestApp
//
//
class CCoeConTestApp : public CEikApplication
	{
private:
	// From CApaApplication
	CApaDocument* CreateDocumentL();
	TUid AppDllUid() const;
	};

//
//
// CCoeConTestDocument
//
//
class CCoeConTestDocument : public CEikDocument
	{
public:
	CCoeConTestDocument(CEikApplication& aApp);
private:
	 // From CEikDocument
	CEikAppUi* CreateAppUiL();
	};
	
#endif // TWINDOWPOSITION_H

