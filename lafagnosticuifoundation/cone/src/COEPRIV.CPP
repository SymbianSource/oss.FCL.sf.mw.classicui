// Copyright (c) 1997-2009 Nokia Corporation and/or its subsidiary(-ies).
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

#include "coepriv.h"
#include "coepanic.h"
#include <coecntrl.h>	// class CCoeControl


LOCAL_C TBool IsHandleValid(TUint aHandle)
	{
	return (aHandle&3)==0;
	}

//
// CCoeView class
//

CCoeView* CCoeView::NewLC(MCoeView& aView)
	{
	CCoeView* self=new(ELeave) CCoeView(aView);
	CleanupStack::PushL(self);
	return self;
	}

CCoeView::CCoeView(MCoeView& aView) : iView(aView)
	{
	}



//
// class CCoeRedrawer
//

CCoeRedrawer::CCoeRedrawer(RWsSession& aWsSession)
	:CActive(EActivePriorityRedrawEvents),
	 iWsSession(aWsSession),
	 iFirstRunL(ETrue)
	{
	CActiveScheduler::Add(this);
	Queue();
	}

CCoeRedrawer::~CCoeRedrawer()
	{
	Cancel();
	}

void CCoeRedrawer::Queue()
	{
	iWsSession.RedrawReady(&iStatus);
	SetActive();
	}

void CCoeRedrawer::RunL()
	{
	TWsRedrawEvent redraw;
	iWsSession.GetRedraw(redraw);
	const TUint handle = redraw.Handle();
	__ASSERT_ALWAYS(IsHandleValid(handle), Panic(ECoePanicInvalidHandle)); 
	CCoeControl* window=REINTERPRET_CAST(CCoeControl*,handle);
	Queue();
#if defined(_DEBUG)
	if (window)
		{
		TRAPD(err, window->HandleRedrawEvent(redraw.Rect()));
		__ASSERT_ALWAYS(err==KErrNone,Panic(ECoePanicLeaveWithoutTrapDuringRedraw));
		}
#else
	if (window)
		window->HandleRedrawEvent(redraw.Rect());
#endif
	iWsSession.Flush();	//flush the window-server client-side buffer *after* HandleRedrawEvent has done any drawing

#if defined(USE_IH_RAISE_EVENT)
	const TInt appStartupInstrumentationEventIdBase=CCoeEnv::Static()->AppStartupInstrumentationEventIdBase();
	if (appStartupInstrumentationEventIdBase!=0)
		{
		IH_DECLARE( lInstrumentationHandler );
		IH_CREATE( lInstrumentationHandler );
		IH_RAISE_EVENT( lInstrumentationHandler, appStartupInstrumentationEventIdBase+MTestInstrumentation::TIDOffsetEndApplicationFirstRedraw );
		IH_DELETE( lInstrumentationHandler );
		}
#endif
	if (iFirstRunL)
		{
		iFirstRunL=EFalse;
		}
	}

void CCoeRedrawer::DoCancel()
	{
	iWsSession.RedrawReadyCancel();
	}
