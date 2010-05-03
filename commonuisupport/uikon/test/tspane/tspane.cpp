// Copyright (c) 2005-2010 Nokia Corporation and/or its subsidiary(-ies).
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
// Tests CEikStatusPane APIs.\n
// 
//

/**
 @file
 @internalComponent - Internal Symbian test code
*/

 
#include <e32keys.h>
#include <coemain.h>
#include <eikenv.h>
#include <eikdef.h>
#include <tspane.rsg>
#include "tspane.hrh"
#include "tspane.h"
#include <techview/eikmenup.h>
#include <techview/eiklabel.h>
#include <techview/eikclock.h>
#include <barsread.h>
#include <techview/eikmenub.h>
#include <ecom/ecom.h>
#include <test/testexecutelog.h>
#include <test/testexecutelogext.h>
#include <uikon/eikdefmacros.h>

_LIT(KTSpaneResourceFilePath, "z:\\system\\test\\uiktest\\tspane.rsc");


void Panic(TInt aPanic)
	{
	User::Panic(_L("Tspane App"),aPanic);
	}


CControlStackedGlobalTextEditor::~CControlStackedGlobalTextEditor()
/**
   Destructor
 */
	{
	CCoeAppUi* const appUi=iEikonEnv->EikAppUi();
	if (appUi!=NULL)
		{
		appUi->RemoveFromStack(this);
		}
	}

// Class CTspaneContainer

/**
   Auxiliary function for all Test Cases
  
   This method creates the status pane control on which all tests are
   carried out & a window to hold the control.
   
 */
void CTspaneContainer::ConstructL(const TRect& aRect)
    {
	CreateWindowL();
	CreateStatusPaneL();
	TRect rect(aRect);
	iStatusPane->ReduceRect(rect);
	SetRect(rect);
	ActivateL();
    }

CTspaneContainer::~CTspaneContainer()
/**
   Destructor
 */
    {
	delete iStatusPane;
    }

/**
   Auxiliary function for Container
  
   The method is an override from CCoeControl. The method is called by
   the windows server or the application itself to redraw the status pane.
  
 */
void CTspaneContainer::Draw(const TRect& /*aRect*/) const
	{
	CWindowGc& gc = SystemGc();
	gc.SetPenColor(KRgbWhite);
	gc.SetPenSize(TSize(2,2));
	gc.SetPenStyle(CGraphicsContext::ESolidPen);
	gc.SetBrushColor(KRgbGray);
	gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
	gc.DrawRect(Rect());
	}

/**
   Auxiliary function for Container
  
   The method is an override from MEikStatusPaneObserver. The method is
   invoked on a change in the position or size of the screen area
   occupied by the status pane.
  
 */
void CTspaneContainer::HandleStatusPaneSizeChange()
	{
	TRect rect = iEikonEnv->EikAppUi()->ClientRect();
	iStatusPane->ReduceRect(rect);
	SetRect(rect);
	DrawNow();
	}

/**
   @SYMTestCaseID UIF-tspane-AutoTestL
  
   @SYMPREQ
  
   @SYMTestCaseDesc Performs automated tests
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The method initiates the following tests:\n
   (1) Out of Memory Tests.\n
   (2) Tests status pane observer provided by MEikStatusPaneObserver.\n
   (3) API testing for the following:\n
   (a) CEikStatusPane::NewL()\n
   (b) CEikStatusPaneBase::ReduceRect()\n
   (c) CEikStatusPaneBase::SwitchLayoutL()\n
   (d) CEikStatusPaneBase::PaneCapabilities()\n
   (e) CEikStatusPaneBase::PaneRectL()\n
   (f) CEikStatusPaneBase::ControlL()\n
   (g) CEikStatusPaneBase::ContainerControlL()\n
  
   @SYMTestExpectedResults All automated tests should complete.
    
 */
void CTspaneContainer::AutoTestL(TAutoTest aTestId)
	{
	switch (aTestId)
		{
		case ETotal:
			ASSERT(CEikStatusPaneBase::Current()!=NULL);
			AutoTestL(EAllNormal);
			AutoTestL(EOOM);
			break;

		case EOOM:
			AutoTestOom();
			if (CEikStatusPaneBase::Current()==NULL)
				{
				CreateStatusPaneL();
				}
			ASSERT(CEikStatusPaneBase::Current()!=NULL);
			break;

		case EAllNormal:
			{
			CreateStatusPaneL();
			for (TInt i=0; i<ENumNormalTests; i++)
				AutoTestL(TAutoTest(i));
			if (CEikStatusPaneBase::Current()==NULL)
				{
				CreateStatusPaneL();
				}
			ASSERT(CEikStatusPaneBase::Current()!=NULL);
			break;
			}

		case EObserver:
			AutoTestObserverL();
			break;

		case ENew:
			AutoTestNewL();
			break;

		case EReduceRect:
			AutoTestReduceL();
			break;

		case ESwitchLayout:
			AutoTestSwitchL();
			break;

		case ECaps:
			AutoTestCapsL();
			break;

		case ERect:
			AutoTestRectL();
			break;

		case EControl:
			AutoTestControlL();
			break;

		case ESwap:
			AutoTestSwapL();
			break;

		case EContainer:
			AutoTestContainerL();
			break;

		case EBackground:
			AutoTestBackgroundL();
			break;
		
		default:
			Panic(0);
			break;
		}
	}

/**
   @SYMTestCaseID UIF-tspane-AutoTestOom
  
   @SYMPREQ
  
   @SYMTestCaseDesc Perform Out of Memory tests
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The method runs all auto tests under a simulated OOM situation.
  
   @SYMTestExpectedResults All tests should pass under the simulated OOM situation.
   
 */
void CTspaneContainer::AutoTestOom()
	{
	TInt i = 0;
	TInt err = KErrNoMemory;

	while (err != KErrNone)
		{
		User::__DbgSetAllocFail(RHeap::EUser, RHeap::EFailNext, i);

		TRAP(err, 
			{
			AutoTestL(EAllNormal);
			});

		i++;

		TBuf<32> buf;
		buf.Format(_L("OOM %d"), i);
		iEikonEnv->InfoMsg(buf);
		}

	User::__DbgSetAllocFail(RHeap::EUser, RHeap::ENone, i);
	}

/**
   @SYMTestCaseID UIF-tspane-AutoTestObserverL
  
   @SYMPREQ
  
   @SYMTestCaseDesc Tests status pane observer.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The test resets two status pane observers and allocates
   one of them to be the observer for the test status pane.
   The method then changes the layout and checks whether the observer
   set for the test status pane receives notification of the change. The
   same test is carried out when no observer is set for the status pane.
  
   @SYMTestExpectedResults Only the observer to which the test status pane
   is set should receive the position change notification. The other
   observers should not receive any notifications.
  
 */
void CTspaneContainer::AutoTestObserverL()
	{
	iStatusPane->SwitchLayoutL(R_TSPANE_LAYOUT_TOP);
	iObs1.Reset();
	iObs2.Reset();
	iStatusPane->SetObserver(&iObs1);
	iStatusPane->SwitchLayoutL(R_TSPANE_LAYOUT_BOTTOM);
	if (!iObs1.Test() || iObs2.Test())
		Panic(0);
	iObs1.Reset();
	iStatusPane->SetObserver(&iObs2);
	iStatusPane->SwitchLayoutL(R_TSPANE_LAYOUT_TOP);
	if (iObs1.Test() || !iObs2.Test())
		Panic(0);
	iObs2.Reset();
	iStatusPane->SetObserver(NULL);
	iStatusPane->SwitchLayoutL(R_TSPANE_LAYOUT_BOTTOM);
	if (iObs1.Test() || iObs2.Test())
		Panic(0);
	iStatusPane->SetObserver(this);
	iStatusPane->SwitchLayoutL(R_TSPANE_LAYOUT_COMPLEX);
	}

/**
   @SYMTestCaseID UIF-tspane-AutoTestReduceL
  
   @SYMPREQ
  
   @SYMTestCaseDesc Test CEikStatusPaneBase::ReduceRect() API.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The method tests CEikStatusPaneBase::ReduceRect() API
   under the following situations:
   (1)When status pane does not extend beyond the screen size.
   (2)When status pane extends beyond the screen size.
  
   @SYMTestExpectedResults Test checks results against expected values.
   
 */
void CTspaneContainer::AutoTestReduceL()
	{
	const TRect spRect(TPoint(0,0), TSize(iEikonEnv->ScreenDevice()->SizeInPixels().iWidth, ETspaneTopHeight));
	TRect test;

	// Normal edge of rectangle reduces, top, left, bottom & right.
	test = spRect;
 
	test.iBr.iY += 10;
	iStatusPane->ReduceRect(test);
	if (!(test.iTl.iX == 0 && test.iTl.iY == spRect.iBr.iY && 
		 test.iBr.iX == spRect.iBr.iX && test.Height() == 10))
		Panic(0);
	
	test = spRect;
	test.iBr.iX += 10;
	iStatusPane->ReduceRect(test);
	if (!(test.iTl.iX == spRect.iBr.iX && test.iTl.iY == 0 && 
		  test.Width() == 10 && test.iBr.iY == spRect.iBr.iY))
		Panic(0);
	
	test = spRect;
	test.iTl.iY -= 10;
	iStatusPane->ReduceRect(test);
	if (!(test.iTl.iX == 0 && test.iTl.iY == -10 && 
		  test.iBr.iX == spRect.iBr.iX && test.Height() == 10))
		Panic(0);
	
	test = spRect;
	test.iTl.iX -= 10;
	iStatusPane->ReduceRect(test);
	if (!(test.iTl.iX == -10 && test.iTl.iY == 0 && 
		  test.Width() == 10 && test.iBr.iY == spRect.iBr.iY))
		Panic(0);
	
	// reductions where status pane extends beyond edge of rect.
	test = spRect;
	test.Shrink(2,2);
	test.iBr.iY += 10;
	iStatusPane->ReduceRect(test);
	if (!(test.iTl.iX == 2 && test.iTl.iY == spRect.iBr.iY && 
		  test.iBr.iX == spRect.iBr.iX-2 && test.Height() == 8))
		Panic(0);
	
	test = spRect;
	test.Shrink(2,2);
	test.iBr.iX += 10;
	iStatusPane->ReduceRect(test);
	if (!(test.iTl.iX == spRect.iBr.iX && test.iTl.iY == 2 && 
		  test.Width() == 8 && test.iBr.iY == spRect.iBr.iY-2))
		Panic(0);
	
	test = spRect;
	test.Shrink(2,2);
	test.iTl.iY -= 10;
	iStatusPane->ReduceRect(test);
	if (!(test.iTl.iX == 2 && test.iTl.iY == -8 && 
		  test.iBr.iX == spRect.iBr.iX-2 && test.Height() == 8))
		Panic(0);

	test = spRect;
	test.Shrink(2,2);
	test.iTl.iX -= 10;
	iStatusPane->ReduceRect(test);
	if (!(test.iTl.iX == -8 && test.iTl.iY == 2 && 
		  test.Width() == 8 && test.iBr.iY == spRect.iBr.iY-2))
		Panic(0);
	}

/**
   @SYMTestCaseID UIF-tspane-AutoTestSwitchL
  
   @SYMPREQ
  
   @SYMTestCaseDesc Test CEikStatusPaneBase::SwitchLayoutL() API.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The method tests switching of layouts with valid &
   invalid layouts. The leave error code is observed on each attempt to
   verify success or failure of layout switch. It also tests whether an
   observer is notified on change in layout.
  
   @SYMTestExpectedResults For all valid layouts CEikStatusPaneBase::SwitchLayoutL()
   should change to the specified layout and should return KErrNone. Otherwise
   the method should return KErrNotFound
   
 */
void CTspaneContainer::AutoTestSwitchL()
	{
	iLayoutNum = 0;

	for (TInt ii=0; ii<7; ii++)
		{
		TRAPD(err, SwitchLayoutL());
		if (err != KErrNone && err != KErrNotFound)
			User::Leave(err);
		if ((ii!=5 && err!=KErrNone) || (ii==5 && err!=KErrNotFound))
			Panic(0);
		}

	iStatusPane->SetObserver(&iObs1);
	iStatusPane->SwitchLayoutL(R_TSPANE_LAYOUT_DIFSIZE);
	iObs1.Reset();
	iStatusPane->SwitchLayoutL(R_TSPANE_LAYOUT_TOP);
	if (!iObs1.Test())
		Panic(0);
	iObs1.Reset();
	iStatusPane->SwitchLayoutL(R_TSPANE_LAYOUT_COMPLEX);
	if (iObs1.Test())
		Panic(0);
	iObs1.Reset();
	iStatusPane->SetObserver(this);
	}

/**
   @SYMTestCaseID UIF-tspane-AutoTestCapsL
  
   @SYMPREQ
  
   @SYMTestCaseDesc Test CEikStatusPaneBase::PaneCapabilities() API
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The method tests whether CEikStatusPanBase::PaneCapabilities()
   sets flags to indicate that the subpane specified is present and part of the
   current status pane layout owned by an application. The test is carried out
   on subpanes that are defined and undefined.
  
   @SYMTestExpectedResults For a defined subpane 
   CEikStatusPanBase::PaneCapabilities() should set flags to represent that
   the subpane is present & owned by the application. For an undefined subpane
   specified the method should not set any flag.
   
 */
void CTspaneContainer::AutoTestCapsL()
	{
	iStatusPane->SwitchLayoutL(R_TSPANE_LAYOUT_TOP);
	TInt ii;
	for (ii = ETSpanePaneUid1; ii <= ETSpanePaneUid7; ii++)
		{
		CEikStatusPaneBase::TPaneCapabilities caps = iStatusPane->PaneCapabilities(TUid::Uid(ii));
		if (!caps.IsPresent() || !caps.IsAppOwned())
			Panic(0);
		}
	iStatusPane->SwitchLayoutL(R_TSPANE_LAYOUT_COMPLEX);
	for (ii = ETSpanePaneUid1; ii <= ETSpanePaneUid7; ii++)
		{
		CEikStatusPaneBase::TPaneCapabilities caps = iStatusPane->PaneCapabilities(TUid::Uid(ii));
		if (!caps.IsPresent() || !caps.IsAppOwned())
			Panic(0);
		}

	CEikStatusPaneBase::TPaneCapabilities caps = iStatusPane->PaneCapabilities(TUid::Uid(0x12345678));
	if (caps.IsPresent() || caps.IsAppOwned())
		Panic(0);	
	}

/**
   @SYMTestCaseID UIF-tspane-AutoTestRectL
  
   @SYMPREQ
  
   @SYMTestCaseDesc Test CEikStatusPaneBase::PaneRectL() API
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The method tests CEikStatusPaneBase::PaneRectL() retrieves the
   size of subpanes present in the current status pane. The tests is carried
   by specifying defined & undefined subpane uids.
  
   @SYMTestExpectedResults For each defined sub-pane 
   CEikStatusPaneBase::PaneRectL() should return it's size.For undefined
   subpane the method should return leave error code KErrNotFound.
   
 */
void CTspaneContainer::AutoTestRectL()
	{
	const TRect spRect(TPoint(0,0), TSize(iEikonEnv->ScreenDevice()->SizeInPixels().iWidth, ETspaneTopHeight));
	const TInt w = spRect.Width()/4;
	const TInt h = spRect.Height()/2;

	const TRect rects[7] = 
		{
			TRect(TPoint(0,0), TSize(w, h)),
			TRect(TPoint(0,h), TSize(w, h)),
			TRect(TPoint(w,0), TSize(w, 2*h)),
			TRect(TPoint(2*w,0), TSize(w, h)),
			TRect(TPoint(2*w,h), TSize(w/2, h)),
			TRect(TPoint(2*w+w/2,h), TSize(w/2, h)),
			TRect(TPoint(3*w,0), TSize(w, 2*h))
		};

	// This test might fail due to rounding errors if your screen is not a
	// multiple of 8 pixels across & a multiple of 2 pixels high.
	TRect rect;
	for (TInt ii = ETSpanePaneUid1; ii <= ETSpanePaneUid7; ii++)
		{
		rect = iStatusPane->PaneRectL(TUid::Uid(ii));
		if (rect != rects[ii-ETSpanePaneUid1])
			Panic(0);
		}

	TRAPD(err, rect = iStatusPane->PaneRectL(TUid::Uid(0x12345678)));
	if (err != KErrNotFound)
		Panic(0);
	}

/**
   @SYMTestCaseID UIF-tspane-AutoTestControlL
  
   @SYMPREQ
  
   @SYMTestCaseDesc Test CEikStatusPaneBase::ControlL() API
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The method tests whether CEikStatusPaneBase::ControlL() returns 
   a sub-pane control represented by the uid specified. To do this the metho 
   changes the sub-pane control properties such as visibilty, fading & dimne s.
   Then it retreives controls from the subpane by specifying their uids an 
   checks the above mentioned properties against expected results. The tes 
   also verifies the scenario where an invalid subpane control uid i 
   specified
  
   @SYMTestExpectedResults The properties of control retreived from status pane
   should match the expected results. When an invalid control uid is specified
   the method should return leave error code KErrNotFound.
   
 */
void CTspaneContainer::AutoTestControlL()
	{
	CCoeControl* control;

	for (TInt vis=0; vis<2; vis++)
		{
		iStatusPane->MakeVisible(vis);
		for (TInt dim=1; dim>=0; dim--)
			{
			iStatusPane->SetDimmed(dim);
			for (TInt fade=1; fade>=0; fade--)
				{
				iStatusPane->SetFaded(fade);
				for (TInt ii = ETSpanePaneUid1; ii <= ETSpanePaneUid7; ii++)
					{
					control = iStatusPane->ControlL(TUid::Uid(ii));
					if (!COMPARE_BOOLS(dim, control->IsDimmed()) ||
						!COMPARE_BOOLS(vis, control->IsVisible()))
						Panic(0);
					}
				}
			}
		}

	TRAPD(err, control = iStatusPane->ControlL(TUid::Uid(0x12345678)));
	if (err != KErrNotFound)
		Panic(0);
	}

/**
   @SYMTestCaseID UIF-tspane-AutoTestSwapL
  
   @SYMPREQ
  
   @SYMTestCaseDesc Test CEikStatusPaneBase::SwapControlL
   
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
  
   @SYMTestActions The method tests whether CEikStatusPaneBase::SwapControlL()
   can swap control on valid sub-pane with the control specified. It
   also tests the behaviour of the method when an undefined sub-pane uid is
   specified.
  
   @SYMTestExpectedResults CEikStatusPaneBase::SwapControlL() should swap the
   control on a valid sub-pane with the control specified. If an undefined
   sub-pane uid is passed to it it should leave with error code KErrNotFound.
   
 */
void CTspaneContainer::AutoTestSwapL()
	{
	iControlNum = 0;

	for (TInt ii=0; ii<4; ii++)
		{
		SwitchControlL(EFalse);
		}

	TRAPD(err, iStatusPane->SwapControlL(TUid::Uid(0x12345678), NULL));
	if (err != KErrNotFound)
		Panic(0);
	}

/**
   @SYMTestCaseID UIF-tspane-AutoTestContainerL
  
   @SYMPREQ
  
   @SYMTestCaseDesc Test CEikStatusPaneBase::ContainerControlL() API
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The method tests whether CEikStatusPaneBase::ContainerControlL()
   returns a sub-pane container control represented by the uid specified.
   To do this the method changes the sub-pane container control properties
   such as visibilty, fading & dimness. Then it retreives container controls
   from the subpane by specifying their uids and checks the above mentioned
   properties against expected results. The test also verifies the scenario
   where an invalid subpane container control uid is specified.
  
   @SYMTestExpectedResults The properties of container control retreived from
   status pane should match the expected results. When an invalid container 
   control uid is specified the method should return leave error code
   KErrNotFound.
   
 */
void CTspaneContainer::AutoTestContainerL()
	{
	CCoeControl* control;

	for (TInt vis=0; vis<2; vis++)
		{
		iStatusPane->MakeVisible(vis);
		for (TInt dim=1; dim>=0; dim--)
			{
			iStatusPane->SetDimmed(dim);
			for (TInt fade=1; fade>=0; fade--)
				{
				iStatusPane->SetFaded(fade);
				for (TInt ii = ETSpanePaneUid1; ii <= ETSpanePaneUid7; ii++)
					{
					control = iStatusPane->ContainerControlL(TUid::Uid(ii));
					if (!COMPARE_BOOLS(dim, control->IsDimmed()) ||
						!COMPARE_BOOLS(vis, control->IsVisible()))
						Panic(0);
					}
				}
			}
		}

	TRAPD(err, iStatusPane->ControlL(TUid::Uid(0x12345678)));
	if (err != KErrNotFound)
		Panic(0);
	}


class CEikTestLabel : public CEikLabel
{
	
protected: // from CCoeControl
 void Draw(const TRect& aRect) const;	
	
};

void CEikTestLabel::Draw(const TRect& /*aRect*/) const
	{
		
	}

class CEikTestTextButton : public CEikTextButton
{
	
 void Draw(const TRect& aRect) const;	
};

void CEikTestTextButton::Draw(const TRect& /*aRect*/) const
	{
		
	}

class CEikTestClock : public CEikClock
{
	
 void Draw(const TRect& aRect) const;	
};

void CEikTestClock::Draw(const TRect& /*aRect*/) const
	{
	}


/**
  Auxiliary function for AutoTestBackGroundL

  The function creates different controls and set them in the status pane.
*/
void CTspaneContainer::SwapBackgroundTestControlL(TInt aControlType)
	{
	CCoeControl* newControl=NULL;
	CCoeControl* container = iStatusPane->ContainerControlL(TUid::Uid(ETSpanePaneUid3));

	switch(aControlType)
		{
		case 0: 
			// Pane 1 - normal label
			newControl = new(ELeave) CEikLabel;
			CleanupStack::PushL(newControl);
			newControl->SetContainerWindowL(*container);

			static_cast<CEikLabel*>(newControl)->SetEmphasis(CEikLabel::EPartialEmphasis);
			static_cast<CEikLabel*>(newControl)->SetTextL(_L("Normal Label"));
			break;

		case 1: 
			// Pane 2 -  label not drawn
			newControl = new(ELeave) CEikTestLabel;
			CleanupStack::PushL(newControl);
			newControl->SetContainerWindowL(*container);

			static_cast<CEikLabel*>(newControl)->SetEmphasis(CEikLabel::EPartialEmphasis);
			static_cast<CEikLabel*>(newControl)->SetTextL(_L("Test Label"));
			break;

		case 2:
			// Pane 3 - normal text button
			newControl = new(ELeave) CEikTextButton;
			CleanupStack::PushL(newControl);
			newControl->SetContainerWindowL(*container);

			static_cast<CEikTextButton*>(newControl)->SetTextL(_L(" Normal Text Button"));
			break;

		case 3:
			// Pane 4 - text button	not drawn
			newControl = new(ELeave) CEikTestTextButton;
			CleanupStack::PushL(newControl);
			newControl->SetContainerWindowL(*container);

			static_cast<CEikTextButton*>(newControl)->SetTextL(_L("Test Text Button"));
			break;

		case 4:
			// Pane 5 - normal clock
			{
			newControl = new(ELeave) CEikClock;
			CleanupStack::PushL(newControl);
			newControl->SetContainerWindowL(*container);
			TResourceReader res;
			iEikonEnv->CreateResourceReaderLC(res, R_TSPANE_CLOCK) ;
			static_cast<CEikClock*>(newControl)->ConstructFromResourceL(res);
			CleanupStack::PopAndDestroy();	// res
			}
			break;

		case 5:
			// Pane 6 - test clock
			{
			newControl = new(ELeave) CEikTestClock;
			CleanupStack::PushL(newControl);
			newControl->SetContainerWindowL(*container);
			TResourceReader res1;
			iEikonEnv->CreateResourceReaderLC(res1, R_TSPANE_CLOCK) ;
			static_cast<CEikClock*>(newControl)->ConstructFromResourceL(res1);
			CleanupStack::PopAndDestroy();	// res1
			}
			break;
		}

	TRect rect = iStatusPane->PaneRectL(TUid::Uid(ETSpanePaneUid3));
	newControl->SetRect(rect);
	newControl->DrawNow();
	newControl->ActivateL();

	CCoeControl* oldControl=iStatusPane->SwapControlL(TUid::Uid(ETSpanePaneUid3), newControl); // iStatusPane takes ownership of newControl
	CleanupStack::Pop(newControl);
	CleanupStack::PushL(oldControl);
	iStatusPane->MakeVisible(ETrue);
	iStatusPane->ApplyCurrentSettingsL();
	CleanupStack::PopAndDestroy(oldControl);
	}

/**
   @SYMTestCaseID UIF-tspane-AutoTestBackgroundL
  
   @SYMPREQ 852 part 2
  
   @SYMTestCaseDesc Tests the status pane gets a background
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The method tests whether the background of the status pane
   is set when adding or changing the controls in the pane.
  
   @SYMTestExpectedResults The background is set to blue.
   
 */
void CTspaneContainer::AutoTestBackgroundL()
	{
 
	for (TInt ii=0; ii<6; ii++)
		{
		SwapBackgroundTestControlL(ii);
		}
	}
	
/**
   @SYMTestCaseID UIF-tspane-AutoTestNewL
  
   @SYMPREQ
  
   @SYMTestCaseDesc Test CEikStatusPane::NewL()
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions This method intiates the following:
   (1)Tests on successful creation of status pane.
   (2)Test CEikStatusPane::NewL() when system status pane specifies an
   undefined default layout.
   (3)Test CEikStatusPane::NewL() when application status pane
   specifies an undefined layout.
   (4)Test CEikStatusPane::NewL() when application status pane
   specifies an undefined override pane.
  
   @SYMTestExpectedResults NA
   
 */
void CTspaneContainer::AutoTestNewL()
	{
	AutoTestAppOverridesL();
	AutoTestBadDefaultLayoutL();
	AutoTestBadOverrideLayoutL();
	AutoTestBadOverridePaneL();
	}

/**
   @SYMTestCaseID UIF-tspane-AutoTestAppOverridesL
  
   @SYMPREQ
  
   @SYMTestCaseDesc Test CEikStatusPane::NewL()
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions This method invokes CEikStatusPane::NewL() method by
   passing proper system status pane & application status pane to
   create a status pane. The method then tests the content & layout
   of the new status pane.
  
   @SYMTestExpectedResults The layout & content should match expected results.
   
 */
void CTspaneContainer::AutoTestAppOverridesL()
	{
	CEikStatusPane* sp = CEikStatusPane::NewL(*iEikonEnv, &iEikonEnv->RootWin(), R_TSPANE_STATUS_PANE, R_TSPANE_APP_OVERRIDES);
	CleanupStack::PushL(sp);

	// Check Layout
	const TRect spRect(TPoint(0,0), TSize(iEikonEnv->ScreenDevice()->SizeInPixels().iWidth, ETspaneTopHeight));
	TRect rect = sp->PaneRectL(TUid::Uid(ETSpanePaneUid1));
	if (rect != spRect)
		Panic(0);

	// Check Content
	CCoeControl* label = sp->ControlL(TUid::Uid(ETSpanePaneUid1));
	if (*((CEikLabel*)label)->Text() != _L("A"))
		Panic(0);

	CleanupStack::PopAndDestroy();	// sp
	}

/**
   @SYMTestCaseID UIF-tspane-AutoTestBadDefaultLayoutL
  
   @SYMPREQ
  
   @SYMTestCaseDesc Test CEikStatusPane::NewL() when system status pane
   specifies an undefined default layout.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions This method invokes CEikStatusPane::NewL() method by
   passing a system status pane that specifies an undefined default 
   layout. The method then tests the error code returned.
  
   @SYMTestExpectedResults CEikStatusPane::NewL() should leave with
   KErrNotFound
   
 */
void CTspaneContainer::AutoTestBadDefaultLayoutL()
	{
	TRAPD(err, CEikStatusPane::NewL(*iEikonEnv, &iEikonEnv->RootWin(), R_TSPANE_BAD_LAYOUT_STATUS_PANE));
	if (err == KErrNone)
		Panic(0);
	if (err != KErrNotFound)
		User::Leave(err);
	}

/**
   @SYMTestCaseID UIF-tspane-AutoTestBadOverrideLayoutL
  
   @SYMPREQ
  
   @SYMTestCaseDesc Test CEikStatusPane::NewL() when application status
   pane specifies an undefined layout.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions This method invokes CEikStatusPane::NewL() method by
   passing a application status pane that specifies an undefined layout.
   The method then tests the error code returned.
  
   @SYMTestExpectedResults CEikStatusPane::NewL() should leave with
   KErrNotFound
   
 */
void CTspaneContainer::AutoTestBadOverrideLayoutL()
	{
	TRAPD(err, CEikStatusPane::NewL(*iEikonEnv, &iEikonEnv->RootWin(), R_TSPANE_FLOATING_STATUS_PANE, R_TSPANE_APP_BAD_OVERRIDE_LAYOUT));
	if (err == KErrNone)
		Panic(0);
	if (err != KErrNotFound)
		User::Leave(err);
	}

/**
   @SYMTestCaseID UIF-tspane-AutoTestBadOverridePaneL
  
   @SYMPREQ
  
   @SYMTestCaseDesc Test CEikStatusPane::NewL() when the application status
   pane specifies an undefined override pane.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions This method invokes CEikStatusPane::NewL() method by
   passing a application status pane that specifies an undefined override pane.
   The method then tests the error code returned.
  
   @SYMTestExpectedResults CEikStatusPane::NewL() should leave with
   KErrNotFound
   
 */
void CTspaneContainer::AutoTestBadOverridePaneL()
	{
	TRAPD(err, CEikStatusPane::NewL(*iEikonEnv, &iEikonEnv->RootWin(), R_TSPANE_FLOATING_STATUS_PANE, R_TSPANE_APP_BAD_OVERRIDE_PANE));
	if (err == KErrNone)
		Panic(0);
	if (err != KErrNotFound)
		User::Leave(err);
	}

/**
   Auxiliary function for all Test Cases
  
   This method creates a status pane control and sets it's observer.
   
 */
void CTspaneContainer::CreateStatusPaneL()
	{
	delete iStatusPane;
	iStatusPane = NULL;
	iStatusPane = CEikStatusPane::NewL(*iEikonEnv, &iEikonEnv->RootWin(), R_TSPANE_STATUS_PANE);
	//vm test(iStatusPane != NULL);
	iStatusPane->SetObserver(this);
	}

/**
   @SYMTestCaseID UIF-tspane-ReportState
  
   @SYMPREQ
  
   @SYMTestCaseDesc Test inquiry methods for visibility, fading and dimming
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The method tests the following inquiry methods for visibility,
   fading and dimming:
   (1)TBool CEikStatusPaneBase::IsVisible()\n
   (2)TBool CEikStatusPaneBase::IsDimmed()\n
   (1)TBool CEikStatusPaneBase::IsFaded()\n
   The test checks the visibility,dimming & fading parameters of the Status
   pane & reports the state with the help of a information message.
  
   @SYMTestExpectedResults The test verifies results against expected values.
   
 */
void CTspaneContainer::ReportState()
	{
	TBuf<64> buf;
	if (!iStatusPane->IsVisible())
		buf += _L("!");
	buf += _L("vis ");
	if (!iStatusPane->IsDimmed())
		buf += _L("!");
	buf += _L("dim ");
	if (!iStatusPane->IsFaded())
		buf += _L("!");
	buf += _L("fade");
	iEikonEnv->InfoMsg(buf);
	}

/**
   @SYMTestCaseID UIF-tspane-SwitchVis
  
   @SYMPREQ
  
   @SYMTestCaseDesc Tests CEikStatusPane::MakeVisible(TBool aVisible) API.
 
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The method tests making the controls on the status pane
   visible and invisible by calling the method CEikStatusPane::MakeVisible().
  
   @SYMTestExpectedResults The controls on the status pane should be
   invisible / visible when EFalse / ETrue is passed to
   CEikStatusPane::MakeVisible() respectively.\n
   
 */
void CTspaneContainer::SwitchVis()
	{
	iStatusPane->MakeVisible(!iStatusPane->IsVisible());
	}

/**
   @SYMTestCaseID UIF-tspane-SwitchDim
  
   @SYMPREQ
  
   @SYMTestCaseDesc Tests CEikStatusPane::SetDimmed(TBool aDimmed) API.
  
   @SYMTestPriority High
 
   @SYMTestStatus Implemented
   
   @SYMTestActions The method tests capability to dim the controls on
   status pane by calling method CEikStatusPane::SetDimmed().
  
   @SYMTestExpectedResults The controls on the status pane should be
   dimmed / restored when ETrue / EFalse is passed to
   CEikStatusPane::SetDimmed() respectively.\n
   
 */
void CTspaneContainer::SwitchDim()
	{
	iStatusPane->SetDimmed(!iStatusPane->IsDimmed());
	}

/**
   @SYMTestCaseID UIF-tspane-SwitchFade
  
   @SYMPREQ
  
   @SYMTestCaseDesc Tests CEikStatusPane::SetFaded(TBool aFaded) API.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The method tests capability to fade the controls on
   status pane by calling method CEikStatusPane::SetFaded().
  
   @SYMTestExpectedResults The controls on the status pane should be
   faded / unfaded when ETrue / EFalse is passed to
   CEikStatusPane::SetFaded() respectively.\n
  
 */
void CTspaneContainer::SwitchFade()
	{
	iStatusPane->SetFaded(!iStatusPane->IsFaded());
	}

/**
  Auxiliary function for TestCaseID tspane-AutoTestL, tspane-AutoTestObserverL,
  tspane_AutoTestSwitchL(), tspane_AutoTestCapsL
  
  This method changes the entire status pane layout to the one specified
  by the resource file.
  
 */
void CTspaneContainer::SwitchLayoutL()
	{
	const TInt layouts[] = 
		{
		R_TSPANE_LAYOUT_COMPLEX, 
		R_TSPANE_LAYOUT_TOP, 
		R_TSPANE_LAYOUT_LEFT, 
		R_TSPANE_LAYOUT_BOTTOM, 
		R_TSPANE_LAYOUT_RIGHT, 
		R_TSPANE_LAYOUT_DIFSIZE,
		0x12345678
		};

	iLayoutNum = (iLayoutNum+1)%(sizeof(layouts)/sizeof(TInt));
	iStatusPane->SwitchLayoutL(layouts[iLayoutNum]);
	}
	
	
/**
   Auxiliary function for TestCaseID tspane-AutoTestSwapL
  
   This method switches the control present on the sub-pane represented by
   uid ETSpanePaneUid1 on the current status pane with the following controls:
   (1) Text Button
   (2) Label
   (3) Global Text Editor
   (4) Clock Control
   
 */
void CTspaneContainer::SwitchControlL(TBool aFocus)
	{
	CCoeControl* newControl=0;
	CCoeControl* container = iStatusPane->ContainerControlL(TUid::Uid(ETSpanePaneUid1));
	
	iControlNum = (iControlNum+1)%4;
	switch(iControlNum)
		{
		case 0:
			newControl = new(ELeave) CEikTextButton;
			CleanupStack::PushL(newControl);
			newControl->SetContainerWindowL(*container);
			((CEikTextButton*)newControl)->SetTextL(_L("B"));
			break;
		case 1:
			newControl = new(ELeave) CEikLabel;
			CleanupStack::PushL(newControl);
			newControl->SetContainerWindowL(*container);
			((CEikLabel*)newControl)->SetEmphasis(CEikLabel::EPartialEmphasis);
			((CEikLabel*)newControl)->SetTextL(_L("Label which is long"));
			break;
		case 2:
			{
			newControl = new(ELeave) CControlStackedGlobalTextEditor(TGulBorder::ESingleGray);
			CleanupStack::PushL(newControl);
			newControl->SetContainerWindowL(*container);
			TBuf<1> temp = _L("E");
			((CEikGlobalTextEditor*)newControl)->ConstructL(container, 1, 64, CEikEdwin::ENoHorizScrolling, EGulFontControlAll, EGulAllFonts);
			((CEikGlobalTextEditor*)newControl)->SetTextL(&temp);
			if (aFocus)
				{
				iEikonEnv->EikAppUi()->AddToStackL(newControl);
				newControl->SetFocus(ETrue);
				}
			break;
			}
		default:
			newControl = new(ELeave) CEikClock;
			CleanupStack::PushL(newControl);
			newControl->SetContainerWindowL(*container);
			TResourceReader res;
			iEikonEnv->CreateResourceReaderLC(res, R_TSPANE_CLOCK) ;
			((CEikClock*)newControl)->ConstructFromResourceL(res);
			CleanupStack::PopAndDestroy();	// res
			break;
		}

	TRect rect = iStatusPane->PaneRectL(TUid::Uid(ETSpanePaneUid1));
	newControl->SetRect(rect);

	CCoeControl* oldControl = iStatusPane->SwapControlL(TUid::Uid(ETSpanePaneUid1), newControl);
	CleanupStack::Pop();	// newControl transferred to status pane
	if (aFocus && oldControl->IsFocused())
		{
		oldControl->SetFocus(EFalse);
		iEikonEnv->EikAppUi()->RemoveFromStack(oldControl);
		}
	delete oldControl;

	newControl->ActivateL();
	newControl->DrawNow();
	}

/**
   @SYMTestCaseID UIF-tspane-BoundingRectOfRegionL
  
   @SYMPREQ
  
   @SYMTestCaseDesc Tests CEikStatusPaneBase::GetShapeL() API
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The method tests whether GetShapeL() method selects the region
   of screen containing the status pane. The method then reads the bounding
   rectangle for the region to verify.
  
   @SYMTestExpectedResults The bounding rectangle co-ordinates of status pane
   should be displayed.
   
 */
void CTspaneContainer::BoundingRectOfRegionL()
	{
	TRect boundingRect(0,0,0,0);
	if(iStatusPane)
		{
		TRegionFix<40> region;	
		iStatusPane->GetShapeL(region,ETrue,ETrue);
		boundingRect = region.BoundingRect();
		}
	TBuf<80> messageBuf;
	_LIT(KBoundingInfoBuf,"Status pane bounding rectangle = %d,%d,%d,%d");
	messageBuf.AppendFormat(KBoundingInfoBuf,boundingRect.iTl.iX,boundingRect.iTl.iY,boundingRect.iBr.iX,boundingRect.iBr.iY);
	iEikonEnv->InfoMsg(messageBuf);
	}

//
// CFloatingSpaneKiller
//
CFloatingSpaneKiller::~CFloatingSpaneKiller()
/**
   Destructor
 */
	{
	delete iSpane;
	if (iWg)
		{
		iWg->Close();
		}
	delete iWg;
	}
	
/**
   Auxiliary function for TestCaseID tspane-CreateNewWindowGroupL
  
   This method allocates and constructs a new text button control.
  
 */	
CFloatingSpaneKiller* CFloatingSpaneKiller::NewL(CEikStatusPane* aSpane, RWindowGroup* aWg)
	{
	CFloatingSpaneKiller* self = new(ELeave) CFloatingSpaneKiller(aSpane, aWg);
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop();
	return self;
	}

/**
   @SYMTestCaseID UIF-tspane-HandleControlEventL
  
   @SYMPREQ
  
   @SYMTestCaseDesc Test Killing the floating Status pane.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The method tests deletion of the floating status pane.
  
   @SYMTestExpectedResults The method should successfully delete the floating
   status pane.
   
 */
void CFloatingSpaneKiller::HandleControlEventL(CCoeControl* /*aControl*/,TCoeEvent aEventType)
	{
	if (aEventType == EEventStateChanged)
		{
		RWindowGroup* wg = iWg;
		iWg = NULL;
		if (wg)
			{
			wg->Close();
			}
		CEikStatusPane* spane = iSpane;
		iSpane = NULL;
		delete spane;
		delete wg;
		}
	}

CFloatingSpaneKiller::CFloatingSpaneKiller(CEikStatusPane* aSpane, RWindowGroup* aWg)
: iSpane(aSpane), iWg(aWg)
/**
   Constructor
 */
	{
	}

/**
   Auxiliary function for TestCaseID tspane-CreateNewWindowGroupL
  
   This method completes construction of text button control and swaps the
   control with sub-pane control on the floating status pane.
  
 */
void CFloatingSpaneKiller::ConstructL()
	{
	CCoeControl* container = iSpane->ContainerControlL(TUid::Uid(ETSpanePaneUid2));
	
	SetContainerWindowL(*container);
	SetTextL(_L("Kill"));

	SetObserver(this);

	SetRect(container->Rect());		// the fast way to set a controls rect when swapping into status pane

	CCoeControl* oldControl = iSpane->SwapControlL(TUid::Uid(ETSpanePaneUid2), this);
	delete oldControl;

	ActivateL();
	DrawNow();
	}


//
// CTspaneAppUi
//
CTspaneAppUi::CTspaneAppUi(CTmsTestStep*		aStep) :
	CTestAppUi(aStep,
		KTSpaneResourceFilePath, 
		R_TSPANE_HOTKEYS, 
		R_TSPANE_MENUBAR)
/**
   Constructor
 */
	{
	}



CTspaneAppUi::~CTspaneAppUi()
/**
   Destructor
 */
	{
	RemoveFromStack(iAppView);
	delete iAppView;

	}

/**
   Auxiliary function for all Test Cases
  
   This method prepares the test step's user interface and prepares it
   to start the tests.
   
 */
void CTspaneAppUi::ConstructL()
    {
   	CTestAppUi::ConstructL();
	
	iAppView=new(ELeave) CTspaneContainer;
    iAppView->ConstructL(ClientRect());
	AddToStackL(iAppView);

	AutoTestManager().StartAutoTest();
	}

/**
   Auxiliary function for all Test Cases
  
   The method is an override from CTestAppUi. The method initiates all tests
   by calling CTspaneAppUi::HandleCommandL().
   
 */
void CTspaneAppUi::RunTestStepL(TInt aNumStep)
	{
#ifdef FORCE_AUTO
	User::After(TTimeIntervalMicroSeconds32(1000000));
#endif	
	switch(aNumStep)
		{
		case 1:
		SetTestStepID(_L("UIF-tspane-AutoTestL"));
		INFO_PRINTF1(_L("Normal"));
		HandleCommandL(ETspaneCmdAutoNormal);
		RecordTestResultL();
		break;
		case 2:
		SetTestStepID(_L("UIF-tspane-AutoTestL"));
		INFO_PRINTF1(_L("Oom"));
		HandleCommandL(ETspaneCmdAutoOom);
		RecordTestResultL();
		break;
		case 3:
		SetTestStepID(_L("UIF-tspane-BoundingRectOfRegionL"));
		INFO_PRINTF1(_L("Display status pane bound rectangle"));
		HandleCommandL(ETspaneCmdBoundingRegion);
		RecordTestResultL();
		break;
		case 4:
		SetTestStepID(_L("UIF-tspane-ReportState"));
		INFO_PRINTF1(_L("Manual state report"));
		HandleCommandL(ETspaneCmdManualState);
		RecordTestResultL();
		break;
		case 5:
		SetTestStepID(_L("UIF-tspane-CreateNewWindowGroupL"));
		INFO_PRINTF1(_L("Create new window group"));
		HandleCommandL(ETspaneCmdManualWg);
		RecordTestResultL();
		break;
		case 6:
		if(iFloatingPanel)
			{	
			SetTestStepID(_L("UIF-tspane-HandleControlEventL"));
			INFO_PRINTF1(_L("Kill Floating panel"));
			iFloatingPanel->HandleControlEventL(NULL, CFloatingSpaneKiller::EEventStateChanged);
			iFloatingPanel = NULL;
			RecordTestResultL();
			}
		break;
		case 7:
		SetTestStepID(_L("UIF-tspane-SwitchVis"));
		// follow on...
		case 8:
		INFO_PRINTF1(_L("Switch Vis"));
		HandleCommandL(ETspaneCmdManualVis);
		if( aNumStep == 8 )
			{
			RecordTestResultL();
			}
		break;
		case 9:
		SetTestStepID(_L("UIF-tspane-SwitchDim"));
		// follow on...
		case 10:
		INFO_PRINTF1(_L("Switch Dim"));
		HandleCommandL(ETspaneCmdManualDim);
		if( aNumStep == 10 )
			{
			RecordTestResultL();
			}
		break;
		case 11:
		SetTestStepID(_L("UIF-tspane-AutoTestSwapL"));
		// follow on...
		case 12: case 13: case 14:
		INFO_PRINTF1(_L("Switch Control"));
		HandleCommandL(ETspaneCmdManualControl);
		if( aNumStep == 14 )
			{
			RecordTestResultL();
			}
		break;
		case 15:
		SetTestStepID(_L("UIF-tspane-AutoTestSwitchL"));
		// follow on...
		case 16: case 17: case 18: case 19:
		INFO_PRINTF1(_L("Switch Layout"));
		HandleCommandL(ETspaneCmdManualLayout);
		if( aNumStep == 19 )
			{
			RecordTestResultL();
			CloseTMSGraphicsStep();
			}
		break;
		case 20:
			AutoTestManager().FinishAllTestCases(CAutoTestManager::EPass);
			break;
		}
	}

/**
   Auxiliary function for all Test Cases
  
   This method is called by CTspaneAppUi::RunTestStepL() to initiate the tests.
   
 */
void CTspaneAppUi::HandleCommandL(TInt aCommand)
	{
	switch (aCommand)
		{
		case EEikCmdExit:
			Exit();
			break;
		case ETspaneCmdAutoAll:
			iAppView->AutoTestL(CTspaneContainer::ETotal);
			iEikonEnv->InfoMsg(_L("Complete"));
			break;
		case ETspaneCmdAutoNormal:
			iAppView->AutoTestL(CTspaneContainer::EAllNormal);
			iEikonEnv->InfoMsg(_L("Complete"));
			break;
		case ETspaneCmdAutoOom:
			iAppView->AutoTestL(CTspaneContainer::EOOM);
			iEikonEnv->InfoMsg(_L("Complete"));
			break;
		case ETspaneCmdManualVis:
			iAppView->SwitchVis();
			break;
		case ETspaneCmdManualDim:
			iAppView->SwitchDim();
			break;
		case ETspaneCmdManualFade:
			iAppView->SwitchFade();
			break;
		case ETspaneCmdManualState:
			iAppView->ReportState();
			break;
		case ETspaneCmdManualLayout:
			iAppView->SwitchLayoutL();
			break;
		case ETspaneCmdManualControl:
			iAppView->SwitchControlL();
			break;
		case ETspaneCmdManualWg:
			CreateNewWindowGroupL();
			break;
		case ETspaneCmdBoundingRegion:
			iAppView->BoundingRectOfRegionL();
			break;
		default:
			Panic(0);
			break;
		}
	}

/**
   @SYMTestCaseID UIF-tspane-CreateNewWindowGroupL
  
   @SYMPREQ
  
   @SYMTestCaseDesc Test adding a floating status pane to a new window group.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The test method creates a new window group and adds a floating
   status pane with two sub-panes that are strechable. Now a Text Button
   control is created and swaped with second sub-pane label control.
  
   @SYMTestExpectedResults Floating status pane should display only sub-pane one
   since it is strechable. Once the Text button control is created and swapped
   with control on sub-pane two sub-pane one should reduce its size to also
   accomodate the text button.
   
 */
void CTspaneAppUi::CreateNewWindowGroupL()
	{
	RWindowGroup* wg=new(ELeave) RWindowGroup(iEikonEnv->WsSession());
	User::LeaveIfError(wg->Construct((TUint32)this));
	wg->SetOrdinalPosition(0,ECoeWinPriorityAlwaysAtFront);
	wg->EnableReceiptOfFocus(EFalse); // disable key events
	CleanupStack::PushL(wg);
	CEikStatusPane* statusPane = CEikStatusPane::NewL(*iEikonEnv, wg, R_TSPANE_FLOATING_STATUS_PANE);
	CleanupStack::PushL(statusPane);
	iFloatingPanel = CFloatingSpaneKiller::NewL(statusPane, wg);	// transfers ownership to a killer button
	CleanupStack::Pop(2);	// statusPane and wg
	// We can loose track of the status pane, window group and killer, because they
	// are in a mutual suicide pact!
	}

//--------

CTestSpaneStep::CTestSpaneStep()
/**
   Constructor
 */
	{
	SetTestStepName(KTestSpaneStep);
	}

CTestSpaneStep::~CTestSpaneStep()
/**
   Destructor
 */
	{
	}

/**
   Auxiliary function for all Test Cases
  
   The method creates & sets the application's user interface object.
   
 */
void CTestSpaneStep::ConstructAppL(CEikonEnv* aCoe)
    { // runs inside a TRAP harness
	aCoe->ConstructL();
	CTspaneAppUi* appUi= new (ELeave) CTspaneAppUi(this);
    aCoe->SetAppUi(appUi);
    appUi->ConstructL();
    }

/**
   Auxiliary function for all Test Cases
  
   The method creates & sets the test step's user interface object and
   launches the test step.
   
 */
TVerdict CTestSpaneStep::doTestStepL() // main function called by E32
	{
	PreallocateHALBuffer();
	__UHEAP_MARK;

	CEikonEnv* coe=new CEikonEnv;
	TRAPD(err,ConstructAppL(coe));

	if (!err)
		coe->ExecuteD();
	
	REComSession::FinalClose();	
	__UHEAP_MARKEND;

	return TestStepResult();
	}
	
	
