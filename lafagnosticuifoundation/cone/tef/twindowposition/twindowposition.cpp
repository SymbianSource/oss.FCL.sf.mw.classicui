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

#include <eikstart.h>
#include <e32cmn.h>
#include "twindowposition.h"

TPoint KWindowPosition(0,0);
TPoint windowPosition;

//
// CCoeConD
//
void CCoeConD::ConstructL(const CCoeControl& aParent)
	{
	CreateWindowL(&aParent);
	}

//
// CCoeConC
//
CCoeConC::CCoeConC(CCoeConB& aParent) : iParent(aParent)
	{
	}

void CCoeConC::ConstructL()
	{
	//C is window owning
	//ViewPort
	iCoeConD = new (ELeave) CCoeConD;
	iCoeConD->ConstructL(iParent);
	CreateWindowL(iCoeConD);
	//ViewPort
	SetParent(&iParent);
	SetComponentsToInheritVisibility();
	CopyControlContextFrom(&iParent);
	}

CCoeConC::~CCoeConC()
	{
	if (iCoeConD)
		delete iCoeConD;
	}

void CCoeConC::Draw(const TRect& aRect) const
	{
	CWindowGc& gc = SystemGc();
	gc.SetDrawMode(CGraphicsContext::EDrawModePEN);
	gc.SetBrushColor(TRgb(150,250,20));
	gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
	gc.DrawRect(aRect);
	windowPosition.SetXY(aRect.iTl.iX, aRect.iTl.iY);
	}

void CCoeConC::SetViewPortRect(TRect aRect )
    {
	iCoeConD->SetRect(aRect);
    }
    
TInt CCoeConC::CountComponentControls() const
	{
	return 1;
	}

CCoeControl* CCoeConC::ComponentControl(TInt aIndex ) const
    {
	if( aIndex == 0 )
		{
		return iCoeConD;
		}
	else
		{
		return NULL;
		}
    }

//
//
// CCoeConB
//
//
CCoeConB::CCoeConB():CCoeControl()
	{
	}

void CCoeConB::ConstructL(CCoeControl* aParent)
	{
	//B is non-window-owning control
	TPoint pos(0,10);
	TSize sizeB(480,50);
	iCoeConC = new (ELeave) CCoeConC(*this);
	iCoeConC->ConstructL();
	SetComponentsToInheritVisibility();
	iCoeConC->SetViewPortRect(Rect());
	iCoeConC->SetSize(sizeB);
	SetParent(aParent);
	ActivateL();
	}

CCoeConB::~CCoeConB()
	{
	if (iCoeConC)
		delete iCoeConC;
	}

void CCoeConB::Draw(const TRect& aRect) const
	{
	CWindowGc& gc = SystemGc();
	gc.SetDrawMode(CGraphicsContext::EDrawModePEN);
	gc.SetBrushColor(TRgb(200,200,40));
	gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
	gc.DrawRect(aRect);
	}

TInt CCoeConB::CountComponentControls() const
	{
	return 1;
	}

CCoeControl* CCoeConB::ComponentControl(TInt aIndex ) const
    {
	if( aIndex == 0 )
		{
		return iCoeConC;
		}
	else
		{
		return NULL;
		}
    }

//
//
// CCoeConTestView - control 'A'
//
//
CCoeConTestView::CCoeConTestView():CCoeControl()
	{
	}

void CCoeConTestView::ConstructL(const TRect& /*aRect*/)
	{
	CreateWindowL(); //A is window owning
	TPoint pos(0,10);
	TSize sizeB(480,100);
	SetPosition(pos);
	iCoeControlB = new (ELeave) CCoeConB();
	//Swap order here need to set container window first
	iCoeControlB->SetContainerWindowL(Window());
	iCoeControlB->SetExtent(pos,sizeB);
	iCoeControlB->ConstructL(this);
	ActivateL();
	}

CCoeConTestView::~CCoeConTestView()
	{
	if (iCoeControlB)
		delete iCoeControlB;
	}

void CCoeConTestView::Draw(const TRect& aRect) const
	{
	// Draw main application window
	CWindowGc& gc = SystemGc();
	gc.SetDrawMode(CGraphicsContext::EDrawModePEN);
	gc.SetBrushColor(TRgb(200,200,200));
	gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
	gc.DrawRect(aRect);
	}

void CCoeConTestView::DrawCoeConB() const
	{
	// Draw the window owning and non-window owning controls
	iCoeControlB->DrawNow();
	TInt exitReason;
	if (windowPosition == KWindowPosition)
		{
		exitReason = KErrNone;
		}
	else
		{
		exitReason = KErrWindowPosDoesNotMatch;
		}
	RProcess().Terminate(exitReason);
	}

TInt CCoeConTestView::CountComponentControls() const
	{
	return 1;
	}

CCoeControl* CCoeConTestView::ComponentControl(TInt aIndex) const
	{
	if (aIndex == 0)
		{
		return iCoeControlB;
		}
	else
		{
		return NULL;
		}
	
	}
/*
void CCoeConTestView::ClearScr()
	{
	CWindowGc& gc = SystemGc();
	gc.SetDrawMode(CGraphicsContext::EDrawModePEN);
	gc.SetBrushColor(TRgb(200,200,200));
	gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
	gc.Clear();
	}
*/
//
//
// CCoeConTestAppUi
//
//
CCoeConTestAppUi::CCoeConTestAppUi() : CTestAppUi(NULL, KNullDesC)
  {
  }

void CCoeConTestAppUi::ConstructL()
	{
	CTestAppUi::ConstructL();
	iAppView = new(ELeave) CCoeConTestView;
	iAppView->ConstructL(ClientRect());
	AutoTestManager().StartAutoTest();
	}

CCoeConTestAppUi::~CCoeConTestAppUi()
	{
	if (iAppView)
		{
		delete iAppView;
		}
	}

void CCoeConTestAppUi::TestWindowPosition()
	{
	iAppView->DrawCoeConB();
	}

void CCoeConTestAppUi::RunTestStepL(TInt aNumStep)
	{
	switch(aNumStep)
		{
		case 1:	
			{
			TRAPD(err, TestWindowPosition());
			if (err == KErrNone)
				{
				AutoTestManager().FinishAllTestCases(CAutoTestManager::EPass);
				}
			else
				{
				AutoTestManager().FinishAllTestCases(CAutoTestManager::EFailed);
				}
			break;
			}
		default:
			break;
		}
	}

//
//
// CCoeConTestDocument
//
//
CCoeConTestDocument::CCoeConTestDocument(CEikApplication& aApp)
		: CEikDocument(aApp)
	{
	}

CEikAppUi* CCoeConTestDocument::CreateAppUiL()
	{
    return new(ELeave) CCoeConTestAppUi;
	}

//
//
// CCoeConTestApp
//
//
TUid CCoeConTestApp::AppDllUid() const
	{
	return KUidCoeControlTestApp;
	}

CApaDocument* CCoeConTestApp::CreateDocumentL()
	{
	return new(ELeave) CCoeConTestDocument(*this);
	}

LOCAL_C CApaApplication* NewApplication()
	{
	return new CCoeConTestApp;
	}

GLDEF_C TInt E32Main()
	{
	return EikStart::RunApplication(NewApplication);
	}
