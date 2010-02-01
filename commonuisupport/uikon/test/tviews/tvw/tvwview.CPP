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


#include <barsread.h>
#include <eikenv.h>
#include <techview/eikwbtb.h>
#include <techview/eikwbut.h>
#include <techview/eiktbar.h>
#include <eikapp.h>
#include <techview/eikbctrl.h>

#include "tvwappui.H"
#include "tvwview.H"

//
// CTestVwAppView.
//

CTestVwAppView::~CTestVwAppView()
	{
	}

CTestVwAppView::CTestVwAppView(const TVwsViewId& aViewId,CTestVwAppUi& aAppUi)
	:iAppUi(aAppUi),iViewId(aViewId)
	{
	}

void CTestVwAppView::ViewActivatedL(const TVwsViewId& aPrevViewId,TUid aCustomMessageId,const TDesC8& aCustomMessage)
	{
	DoActivateNarrowL(aPrevViewId,aCustomMessageId,aCustomMessage);
	}

void CTestVwAppView::ViewConstructL()
	{
	}

void CTestVwAppView::ViewDeactivated()
	{
	DoDeactivate();
	}

void CTestVwAppView::DoDeactivate()
	{
	}

void CTestVwAppView::ActivateViewL(const TVwsViewId& aViewId)
	{
	STATIC_CAST(CCoeAppUi&,iAppUi).ActivateViewL(aViewId);
	}

void CTestVwAppView::ActivateViewL(const TVwsViewId& aViewId,TUid aCustomMessageId,const TDesC16& aCustomMessage)
	{
	iAppUi.ActivateViewL(aViewId,aCustomMessageId,aCustomMessage);
	}

TRect CTestVwAppView::ClientRect() const
	{
	TRect rect(AppUi().ClientRect());
	return rect;
	}

CTestVwAppUi& CTestVwAppView::AppUi() const
	{
	return iAppUi;
	}

void CTestVwAppView::ProcessCommandL(TInt aCommand)
    {
	HandleCommandL(aCommand);
    }

void CTestVwAppView::AddToStackL(CCoeControl* aControl,TInt aPriority,TInt aStackingFlags)
	{
	iAppUi.AddToViewStackL(*this,aControl,aPriority,aStackingFlags);
	}

void CTestVwAppView::RemoveFromStack(CCoeControl* aControl)
	{
	iAppUi.RemoveFromViewStack(*this,aControl);
	}

void CTestVwAppView::UpdateStackedControlFlags(CCoeControl* aControl,TInt aFlags,TInt aMask)
	{
	iAppUi.UpdateViewStackedControlFlags(*this,aControl,aFlags,aMask);
	}

TVwsViewId CTestVwAppView::ViewId() const
	{
	return iViewId;
	}

void CTestVwAppView::DoActivateL(const TVwsViewId& /*aPrevViewId*/,TUid /*aCustomMessageId*/,const TDesC16& /*aCustomMessage*/)
	{
	ASSERT(EFalse);
	}

void CTestVwAppView::DoActivateNarrowL(const TVwsViewId& aPrevViewId,TUid aCustomMessageId,const TDesC8& aCustomMessage)
	{
	HBufC16* wideCustomMessage=HBufC16::NewLC(aCustomMessage.Size());
	TPtr16 ptr=wideCustomMessage->Des();
	ptr.Copy((TUint16*)aCustomMessage.Ptr(),aCustomMessage.Length());
	DoActivateL(aPrevViewId,aCustomMessageId,ptr);
	CleanupStack::PopAndDestroy(); // wideCustomMessage.
	}

void CTestVwAppView::HandleCommandL(TInt /*aCommand*/)
	{
	}

void CTestVwAppView::SetEmphasis(CCoeControl* /*aMenuControl*/,TBool /*aEmphasis*/)
	{
	}

void CTestVwAppView::HandleModelChangeL()
	{
	}

