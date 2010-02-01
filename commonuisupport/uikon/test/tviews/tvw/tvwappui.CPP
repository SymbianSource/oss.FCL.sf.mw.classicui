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

#include <bautils.h>
#include <eikenv.h>
#include <eikapp.h>
#include <eikdoc.h>

#include "tvwappui.H"

//
// Constants.
//

const TInt KAppViewArrayGranularity=5;


//
// CTestVwAppUi.
//

CTestVwAppUi::CTestVwAppUi()
	:iAppViewArray(KAppViewArrayGranularity)
	{
	}

CTestVwAppUi::~CTestVwAppUi()
	{
	const TInt numViews=iAppViewArray.Count();
	for (TInt ii=numViews-1;ii>=0;--ii)
		{
		CTestVwAppView* thisView=iAppViewArray[ii];
		DeregisterViewAndRemoveStack(*thisView);
		iAppViewArray.Delete(ii);
		delete thisView;
		}
	}

void CTestVwAppUi::ConstructL()
	{
	CEikAppUi::ConstructL();
	}

void CTestVwAppUi::ActivateViewL(const TVwsViewId& aViewId,TUid aCustomMessageId,const TDesC16& aCustomMessage)
	{
	HBufC8* narrowMessage=HBufC8::NewLC(aCustomMessage.Size());
	TPtr8 ptr=narrowMessage->Des();
	ptr.Copy((TUint8*)aCustomMessage.Ptr(),aCustomMessage.Size());

	CCoeAppUi::ActivateViewL(aViewId,aCustomMessageId,*narrowMessage);
	CleanupStack::PopAndDestroy(); // narrowMessage.
	}

void CTestVwAppUi::AddViewL(CTestVwAppView* aView)
	{
	ASSERT(aView);
	iAppViewArray.AppendL(aView);
	TRAPD(err,RegisterViewAndAddStackL(*aView));
	if (err)
		{
		iAppViewArray.Delete(AppViewIndex(aView));
		User::Leave(err);
		}
	}

void CTestVwAppUi::DeleteView(const TVwsViewId& aViewId)
	{
	const TInt viewIndex=AppViewIndex(aViewId);
	ASSERT(viewIndex!=KErrNotFound);
	CTestVwAppView* view=iAppViewArray[viewIndex];
	DeregisterViewAndRemoveStack(*view);
	delete view;
	iAppViewArray.Delete(viewIndex);
	}

CTestVwAppView* CTestVwAppUi::View(const TVwsViewId& aViewId) const
	{
	ASSERT(AppViewIndex(aViewId)!=KErrNotFound);
	return iAppViewArray[AppViewIndex(aViewId)];
	}

CTestVwAppView* CTestVwAppUi::ActiveView() const
	{
	TVwsViewId activeViewId;
	if (GetActiveViewId(activeViewId)==KErrNone)
		{
		return iAppViewArray[AppViewIndex(activeViewId)];
		}

	return NULL;
	}

void CTestVwAppUi::HandleModelChangeL()
	{
	CTestVwAppView* activeView=ActiveView();
	if (activeView)
		{
		activeView->HandleModelChangeL();
		}
	}

TInt CTestVwAppUi::AppViewIndex(const TVwsViewId& aViewId) const
	{
	const TInt numAppViews=iAppViewArray.Count();

	for (TInt ii=0;ii<numAppViews;ii++)
		{
		if (iAppViewArray[ii]->ViewId()==aViewId)
			return ii;
		}

	return KErrNotFound;
	}

TInt CTestVwAppUi::AppViewIndex(CTestVwAppView* aView) const
	{
	TInt pos;
	TKeyArrayFix key(0,ECmpTInt);
	
	if (iAppViewArray.Find(aView,key,pos)==KErrNone)
		{
		return pos;
		}

	return KErrNotFound;
	}

