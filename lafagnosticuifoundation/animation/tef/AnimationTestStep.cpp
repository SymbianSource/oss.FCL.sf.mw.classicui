// Copyright (c) 2008-2009 Nokia Corporation and/or its subsidiary(-ies).
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


#include <e32base.h>
#include <charconv.h>

#include "TestWindows.h"
#include "TestEventHandler.h"
#include "TestRedrawHandler.h"
#include "ActiveWait.h"
#include "AnimationTestStep.h"
#include "AnimationConfig.h"

const TInt KFontHeight = 17;

//
// Windows:
//
// Backdrop window:
CAnimBackdropWindow::CAnimBackdropWindow(RWsSession& aWsSession, CTestWindowGroup& aGroup, CWindowGc& aGc) : CTestWindow(aWsSession, aGroup, aGc)
	{
	}
	
// Output window:
CAnimationTestWindow::CAnimationTestWindow(RWsSession& aWsSession, CTestWindowGroup& aGroup, CWindowGc& aGc, CWsScreenDevice& aScreen) :
CTestWindow(aWsSession, aGroup, aGc),
iScreen(aScreen)
	{
	}

CAnimationTestWindow::~CAnimationTestWindow()
	{
	}

void CAnimationTestWindow::DrawL()
	{
	if(!iFont)
		{
		TFontSpec fspec(_L("Arial"),KFontHeight);
		User::LeaveIfError(iScreen.GetNearestFontInPixels((CFont *&)iFont, fspec));
		}
	iGc.UseFont(iFont);
	iGc.SetPenColor(KRgbBlack);
	TSize size = Window()->Size();
	for (TInt i = 0; i < iNumLines; ++i)
		{
		iGc.DrawText(iText[(iFirstLine + i) % KMaxLogWinLines], TRect(TPoint(0,i * KFontHeight), size), KFontHeight);
		}
	}

void CAnimationTestWindow::AppendText(const TDesC& aText)
	{
	TInt line = (iFirstLine + iNumLines) % KMaxLogWinLines;
	if (iNumLines < KMaxLogWinLines)
		++iNumLines;
	else
		iFirstLine = (iFirstLine + 1) % KMaxLogWinLines;
		
	iText[line].Copy(aText.Left(iText[line].MaxLength()));
	Window()->Invalidate();
	}
	
void CAnimationTestWindow::Clear()
	{
	iNumLines = 0;
	Window()->Invalidate();
	}

//
// The test:
//
CAnimationTestStep::CAnimationTestStep():
	iBackgroundColor1(TRgb(0xFF8080)),
	iBackgroundColor2(TRgb(0xFF0000))
	{
	}
	
CAnimationTestStep::~CAnimationTestStep()
	{
	if (iWaiter)
		{
		iWaiter->Cancel();
		delete iWaiter;
		}
	delete iRedrawHandler;
	delete iEventHandler;
	delete iAnimTestWin;
	delete iAnimBackdropWin;
	delete iGroupWin;
	delete iGc;
	iFs.Close();
	iWs.Close();
	delete iConverter;
	iColors.Close();
	}

void CAnimationTestStep::InitialiseL()
	{
	iWaiter = CActiveWait::NewL();
	
	User::LeaveIfError(iWs.Connect());
	User::LeaveIfError(iFs.Connect());
	iScreen = new (ELeave) CWsScreenDevice(iWs);
	User::LeaveIfError(iScreen->Construct());
	iDisplayMode = iScreen->DisplayMode();
	iGc = new (ELeave) CWindowGc(iScreen);
	User::LeaveIfError(iGc->Construct());
	
	iConverter = CCnvCharacterSetConverter::NewL();
	iConverterState = CCnvCharacterSetConverter::KStateDefault;
	iConverter->PrepareToConvertToOrFromL(KCharacterSetIdentifierAscii, iFs);

	iEventHandler = new (ELeave) CTestEventHandler(iWs);
	iEventHandler->Start();
	iRedrawHandler = new (ELeave) CTestRedrawHandler(iWs);
	iRedrawHandler->Start();
	
	iGroupWin = new (ELeave) CTestWindowGroup(iWs);

	// EColor64K is 16bpp in RGB 5-6-5 format, some color might be truncated during conversion 
	// from TRgb to TUint16
	// The solution is to convert RGB to RGB565 and back to RGB to allow direct color comparison 
    // with value of drawn pixel on the screen 
	if (iScreen->DisplayMode()==EColor64K)
		{
		iBackgroundColor1 = TRgb::Color64K(iBackgroundColor1.Color64K());
		iBackgroundColor2 = TRgb::Color64K(iBackgroundColor2.Color64K());
		}

	iStepWinSize = iScreen->SizeInPixels();
	iStepWinSize.iWidth /= 2;
	iAnimTestWin = new (ELeave) CAnimationTestWindow(iWs, *iGroupWin, *iGc, *iScreen);
	iAnimTestWin->Window()->SetRequiredDisplayMode(EGray2);
	iAnimTestWin->Window()->SetExtent(TPoint(0,0), iStepWinSize);
	iAnimTestWin->Window()->SetBackgroundColor(KRgbWhite);
	iAnimTestWin->Window()->SetVisible(ETrue);
	iAnimTestWin->Window()->Activate();
	
	iAnimBackdropWin = new (ELeave) CAnimBackdropWindow(iWs, *iGroupWin, *iGc);
	iAnimBackdropWin->Window()->SetRequiredDisplayMode(EGray2);
	iAnimBackdropWin->Window()->SetExtent(TPoint(iStepWinSize.iWidth,0), iStepWinSize);
	iAnimBackdropWin->Window()->SetBackgroundColor(KRgbBlack);
	iAnimBackdropWin->Window()->SetVisible(ETrue);
	iAnimBackdropWin->Window()->Activate();
	}

// This is not a completely safe function, but then this is only a test harness
void CAnimationTestStep::Log(const TDesC& aText)
	{
	iAnimTestWin->AppendText(aText);
	}
	
void CAnimationTestStep::ClearLog()
	{
	iAnimTestWin->Clear();
	}
	
void CAnimationTestStep::Wait(TInt aDelay)
	{
	iWaiter->Wait(aDelay);
	}
	
TBool CAnimationTestStep::RectCompare(const TRect& a, const TRect& b)
	{
	if(iScreen->RectCompare(a,b,CWsScreenDevice::EIncludeSprite))
		{
		return ETrue;
		}
	else
		{
		return EFalse; // This is a good place for a break point
		}
	}

TInt CAnimationTestStep::CountColorsL(const TRect& aRect, TInt aMin, TInt aMax)
	{
	TDisplayMode displayMode = iScreen->DisplayMode();
	TInt width = CFbsBitmap::ScanLineLength(aRect.Width(),displayMode);
	HBufC8* buf=HBufC8::NewMaxLC(width);
	TPtr8 ptr=buf->Des();
	iColors.Reset();
	TInt inc = width/aRect.Width();
	for (TInt row = aRect.iTl.iY; row < aRect.iBr.iY; ++row)
		{
		ptr.SetLength(0);
		iScreen->GetScanLine(ptr,TPoint(aRect.iTl.iX,row),aRect.Width(),displayMode);
		for (TInt col = 0; col < ptr.Length(); col+=inc)
			{
			TUint clr = ptr[col];
			// Pixel buffer represented in block of bytes, if color mode is 8bpp (1byte) we can
			// simply access the buffer sequentially eg clr = ptr[col], however if the color mode
			// is 16bpp or more, access must be adjusted accordingly. 
			// The "inc" variable indicates how many bytes each pixel's colour takes
			// and could be any value from 1 to 4 depending on the color mode.
			for (TInt byteNumber = 1; byteNumber < inc; byteNumber++)
				{
				clr = clr << 8;
				clr += ptr[col + byteNumber];
				}
			if (iColors.Find(clr) == KErrNotFound)
				{
				iColors.Append(clr);
				}
			}
		}
	TInt count = iColors.Count();
	CleanupStack::PopAndDestroy(buf);
	
	if (count < aMin)
		{
		return (count - aMin);	// This is a good place for a break point
		}
	else if (count > aMax)
		{
		return (count - aMax);	// This is a good place for a break point
		}
	else
		{
		return 0;
		}
	
	}

//
// Wait till redraws finished //
//

class CStopTheScheduler : public CAsyncOneShot
	{
public:
	CStopTheScheduler(TInt aPriority);
	static CStopTheScheduler* NewL(TInt aPriority);
	void RunL();
	};

CStopTheScheduler* CStopTheScheduler::NewL(TInt aPriority)
	{
	return new(ELeave)CStopTheScheduler(aPriority);
	}

CStopTheScheduler::CStopTheScheduler(TInt aPriority)
	:CAsyncOneShot(aPriority)
	{
	}

void CStopTheScheduler::RunL()
	{
	CActiveScheduler::Stop();
	}

void CAnimationTestStep::WaitForRedrawsToFinish()
	{
	CStopTheScheduler* ps=new CStopTheScheduler(-11);
	if(ps)
		{
		ps->Call();
		CActiveScheduler::Start();
		delete ps;
		}
	}
	
