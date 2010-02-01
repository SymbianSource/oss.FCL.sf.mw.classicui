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
 @internalComponent - Internal Symbian test code
 @test
*/

#include "statecon.h"
#include "tconestateobs.h"

const TFontSpec CStateObserverControl::iFontSpec(KFontName,256);


/**
   Set up the control
 */
void CStateObserverControl::ConstructL()
	{
	TSize scrSize(iCoeEnv->ScreenDevice()->SizeInPixels());
	SetExtent(TPoint(scrSize.iWidth/4,0),TSize(scrSize.iWidth-scrSize.iWidth/4,scrSize.iHeight));
	CreateWindowL();
	Window().SetBackgroundColor(TRgb(85,85,255));	//Bright Blue
	ActivateL();
	iFont=iCoeEnv->CreateScreenFontL(iFontSpec);
	//iCoeEnv->WsSession().LogCommand(RWsSession::ELoggingStatusDump);		//Useful for debugging window creation problems
	DrawNow();
	Flush();
	iShouldBeVisible=ETrue;	//Initial State
	iShouldBeDimmed=EFalse;	//Initial State
	}

/**
   Delete the controls resources
 */
CStateObserverControl::~CStateObserverControl()
	{
	iCoeEnv->ReleaseScreenFont(iFont);
	}

/**
   Set which interface should be recieving events
 */
void CStateObserverControl::SetRecievers(TBool aControlRecieving,TBool aCoeEnvRecieving)
	{
	iControlRecieving=aControlRecieving;
	iCoeEnvRecieving=aCoeEnvRecieving;
	}

/**
   Reset the control counts so that a new test can be run
 */
void CStateObserverControl::ResetCount()
	{
	iTestNo=0;
	DrawNow();
	Flush();
	iLastCalled=0;
	iFailAt=0;
	}

/**
   Draw the controls window
 */
void CStateObserverControl::Draw(const TRect& aRect) const
	{
	_LIT(KString1,"Win ");
	_LIT(KString2,"Faded");
	_LIT(KString3,"Not Faded");
	_LIT(KString4,", Subtest %d");
	TBuf<32> buf;
	buf.Copy(KString1);
	buf.Append(IsDimmed()?KString2():KString3());
	if (iTestNo>0)
		buf.AppendFormat(KString4,iTestNo);
	TRect rect(aRect);
	const TSize size(aRect.Size());
	rect.Shrink(size.iWidth/5,size.iHeight/5);
	CWindowGc& gc=SystemGc();
	gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
	gc.SetBrushColor(TRgb(85,255,85));	//Bright Green
	gc.DrawRect(rect);
	gc.SetBrushStyle(CGraphicsContext::ENullBrush);
	gc.SetPenStyle(CGraphicsContext::ESolidPen);
	gc.SetPenColor(TRgb(255,85,85));	//Bright Red
	gc.UseFont(iFont);
	gc.DrawText(buf,TPoint(rect.iTl.iX+20,aRect.Height()/2));
	gc.DiscardFont();
	}

/**
   Set the control's and windows dimmed state
 */
void CStateObserverControl::DoSetDimmed(TBool aDimmed)
	{
	Window().SetFaded(aDimmed,RWindowTreeNode::EFadeWindowOnly,0,127);
	SetDimmed(aDimmed);
	}

/**
   Run a set of tests on the control
 */
TInt CStateObserverControl::DoTest()
	{
	EnableReportControlStateChange(ETrue);
	DoTestStep(MCoeControlStateObserver::EStateDimmed,ETrue);
	DoTestStep(MCoeControlStateObserver::EStateVisibility,EFalse);
	DoTestStep(MCoeControlStateObserver::EStateVisibility,ETrue);
	DoTestStep(MCoeControlStateObserver::EStateDimmed,ETrue);
	DoTestStep(MCoeControlStateObserver::EStateDimmed,EFalse);
	DoTestStep(MCoeControlStateObserver::EStateDimmed,EFalse);
	DoTestStep(MCoeControlStateObserver::EStateVisibility,ETrue);
	DoTestStep(MCoeControlStateObserver::EStateVisibility,EFalse);
	DoTestStep(MCoeControlStateObserver::EStateVisibility,EFalse);
	DoTestStep(MCoeControlStateObserver::EStateDimmed,ETrue);
	DoTestStep(MCoeControlStateObserver::EStateDimmed,EFalse);
	DoTestStep(MCoeControlStateObserver::EStateVisibility,ETrue);
	EnableReportControlStateChange(EFalse);
	return iFailAt;
	}

void CStateObserverControl::Failed()
	{
	if (!iFailAt)
		iFailAt=iTestNo;
	}

/**
   Run a particular test on the control
 */
void CStateObserverControl::DoTestStep(MCoeControlStateObserver::TCoeState aStateToChange,TBool aNewState)
	{
	++iTestNo;
	iCntCalled=EFalse;
	iEnvCalled=EFalse;
	iExpectedChange=aStateToChange;
	if (iExpectedChange==MCoeControlStateObserver::EStateVisibility)
		{
		iNoChange=(iShouldBeVisible==aNewState);
		iShouldBeVisible=aNewState;
		MakeVisible(aNewState);
		}
	else
		{
		iNoChange=(iShouldBeDimmed==aNewState);
		iShouldBeDimmed=aNewState;
		DoSetDimmed(aNewState);
		}
	if (IsVisible())
		DrawNow();
	Flush();
	//Test to see that either
	//the control changed its state (iNoChange==EFalse) and function were called (iLastCalled==iTestNo) OR
	//the control state was unchanged (iNoChange==ETrue) and function was not called (iLastCalled<iTestNo)
	if ((iLastCalled!=iTestNo)==(!iNoChange))
		Failed();
	}

/**
   Handles calls to the Mop interface on this control
 */
TInt CStateObserverControl::HandleControlStateChange(CCoeControl* aControl,MCoeControlStateObserver::TCoeState aState)
	{
	TestFail(!iControlRecieving,aControl,aState,iCntCalled);
	return KErrNone;
	}

/**
   Handles calls to the Mop interface on the control enviroment
 */
TInt CStateObserverControl::ControlStateChangePassOn(CCoeControl* aControl,MCoeControlStateObserver::TCoeState aState)
	{
	TestFail(!iCoeEnvRecieving,aControl,aState,iEnvCalled);
	return KErrNone;
	}

/**
   Check if calls to the Mop interface are correct
 */
void CStateObserverControl::TestFail(TBool aNotGetting,CCoeControl* aControl
							,MCoeControlStateObserver::TCoeState aState,TBool& aCalled)
	{
	iLastCalled=iTestNo;
	//Check to see that:
	//The observer function hasn't been called before [aCalled=EFalse]
	//That we should be receiving calls [aNotGetting=EFalse]
	//That the control state has actually changed [iNoChange=EFalse]
	//The right control changed it's state [aControl==this]
	//The right state of the control changes [aState==iExpectedChange]
	//The control if dimmed or not if it should be [iShouldBeDimmed==IsDimmed()]
	//The control if visible or not if it should be [iShouldBeVisible==IsVisible()]
	if (aCalled || aNotGetting || iNoChange || aControl!=this || aState!=iExpectedChange
						|| !iShouldBeDimmed!=!IsDimmed() || !iShouldBeVisible!=!IsVisible())
		Failed();
	aCalled=ETrue;
	}

/**
   Returns a Mop interface
 */
TTypeUid::Ptr CStateObserverControl::MopSupplyObject(TTypeUid aId)
	{
	switch (iRetObserver)
		{
	case EObserver:
		if (aId.iUid==MCoeControlStateObserver::ETypeId)
			return aId.MakePtr(static_cast<MCoeControlStateObserver*>(this));
		break;
	case ECoeEnvObserver:
		return iEnv->MopSupplyObject(aId);
	default:;
		}
	return CCoeControl::MopSupplyObject(aId);
	}
