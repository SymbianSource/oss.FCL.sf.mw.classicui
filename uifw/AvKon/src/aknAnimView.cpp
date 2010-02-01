/*
* Copyright (c) 2002 Nokia Corporation and/or its subsidiary(-ies).
* All rights reserved.
* This component and the accompanying materials are made available
* under the terms of "Eclipse Public License v1.0"
* which accompanies this distribution, and is available
* at the URL "http://www.eclipse.org/legal/epl-v10.html".
*
* Initial Contributors:
* Nokia Corporation - initial contribution.
*
* Contributors:
*
* Description:
*
*/

// AknAnimView.CPP
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

// Animation View class


#include "aknanimview.h"
#include "aknAnimGc.h"
#include "aknAnimCtrl.h"
#include "aknanimdata.h"

#include "aknappui.h"
#include "AknPanic.h"
#include <coemain.h>
#include <eikbtgpc.h>
#include <e32base.h>
#include <eikmenub.h>
#include <eiklbi.h>
#include <eiklbx.h>
#include <avkon.hrh>
#include <AknLayout.lag>
#include <AknUtils.h>
// CAknDummyListBoxView

CWindowGc* CAknDummyListBoxView::SwapGraphicsContext(CWindowGc* aGc)
	{
	CWindowGc* oldGc = iGc;
	iGc = aGc;
	iItemDrawer->SetGc(aGc);
	return oldGc;
	}

EXPORT_C TAny* CAknDummyListBoxView::Reserved_1()
	{
	return NULL;
	}


// CAknAnimatedView

EXPORT_C CAknAnimatedView::CAknAnimatedView()
	{
	}

EXPORT_C CAknAnimatedView::~CAknAnimatedView()
	{
	delete iKeyWatcher;
	delete iTimedDrawer;
	delete iAnimatedGc;
	delete iAnimationCtrl;
	delete iViewBitmapContext;
	delete iViewBitmapDevice;
	delete iViewBitmap;
	delete iOriginalBitmap;
	}


/** Entry point for animation. This function is called by the view architecture when
  * a new view is activated.
 */
EXPORT_C void CAknAnimatedView::AknViewActivatedL(const TVwsViewId& aPrevViewId,TUid aCustomMessageId,const TDesC8& aCustomMessage)
	{
	// Check that no existing bitmap or gc exists
	__ASSERT_DEBUG(!iViewBitmap, Panic(EAknPanicAnimationCorrupt));
	__ASSERT_DEBUG(!iViewBitmapDevice, Panic(EAknPanicAnimationCorrupt));
	__ASSERT_DEBUG(!iViewBitmapContext, Panic(EAknPanicAnimationCorrupt));
	__ASSERT_DEBUG(!iAnimatedGc, Panic(EAknPanicAnimationCorrupt));
	// Create a blank bitmap for drawing the view to
    TSize screenSize = iAvkonAppUi->ApplicationRect().Size();
	//TSize screenSize = TSize(AKN_LAYOUT_WINDOW_screen.iW,AKN_LAYOUT_WINDOW_screen.iH);

	iViewBitmap = new (ELeave) CFbsBitmap();
    iViewBitmap->Create(screenSize,iCoeEnv->ScreenDevice()->DisplayMode());	

	iViewBitmapDevice = CFbsBitmapDevice::NewL(iViewBitmap);
    iViewBitmapDevice->CreateContext(iViewBitmapContext); 


	iAnimatedGc = CAknAnimatedGc::NewL(iCoeEnv->SystemGc(), *iViewBitmapContext);
	iAnimatedGc->SetRootWindow(iCoeEnv->RootWin());
	
	iEikonEnv->EikAppUi()->StopDisplayingMenuBar();
	if (MenuBar())
		MenuBar()->StopDisplayingMenuBar();

	// Get a copy of the existing screen

	iOriginalBitmap = new (ELeave) CFbsBitmap();
    iOriginalBitmap->Create(screenSize,iCoeEnv->ScreenDevice()->DisplayMode());	
	iCoeEnv->ScreenDevice()->CopyScreenToBitmap(iOriginalBitmap);

	iOldSystemGc = iCoeEnv->SwapSystemGc(iAnimatedGc);

	PreAnimateSetup();

	CAknView::AknViewActivatedL(aPrevViewId, aCustomMessageId, aCustomMessage);

	// Redraw status pane
	CEikStatusPane *sp = ((CAknAppUi*)iEikonEnv->EikAppUi())->StatusPane();
	CCoeControl *context = sp->ContainerControlL(TUid::Uid(EEikStatusPaneUidContext));
	CCoeControl *title = sp->ContainerControlL(TUid::Uid(EEikStatusPaneUidTitle));
	CCoeControl *navi = sp->ContainerControlL(TUid::Uid(EEikStatusPaneUidNavi));
	context->DrawNow();
	title->DrawNow();
	navi->DrawNow();

	// Start timed drawer, so that view can draw before animation starts

	iTimedDrawer = CPeriodic::NewL(CActive::EPriorityIdle);
	TCallBack callback(DrawCallback, this);
	iTimedDrawer->Start(iAnimationData->Interval(),iAnimationData->Interval(),callback);


	iKeyWatcher = CAknAnimationKeyWatcher::NewL();
	}


TInt CAknAnimatedView::DrawCallback(TAny* aPtr)
	{
	CAknAnimatedView* ptr = (CAknAnimatedView*)aPtr;
	
	return ptr->DoCallback();
	}

void CAknAnimatedView::RestoreSystemGc()
	{
	if (iOldSystemGc != NULL)
		{
		iCoeEnv->SwapSystemGc(iOldSystemGc);
		}
	iOldSystemGc = NULL;
	}

TInt CAknAnimatedView::DoCallback()
	{
	if (!iAnimationCtrl)
		{
		TRAPD(error,
		iAnimationCtrl = CAknAnimationCtrl::NewL(*iOldSystemGc, *iViewBitmap, *iOriginalBitmap, iAnimationData);	
		iAnimationCtrl->ActivateL();
		);
		if (error)
			{
			// Error in creating the control, so just end the callback.
			// The view is displayed normally, without the animation
			delete iAnimationCtrl;
			iAnimationCtrl = NULL;
			return ETrue;
			}


		iKeyWatcher->SetAnimationControl(iAnimationCtrl);
		RestoreSystemGc();
		}

	TBool finished = iAnimationCtrl->DrawStep();
	if (!finished)
		return ETrue;

	delete iKeyWatcher;
	iKeyWatcher = NULL;

	delete iTimedDrawer;
	iTimedDrawer = NULL;

	PostAnimateSetup();
	delete iAnimatedGc;
	iAnimatedGc = NULL;

	delete iViewBitmapContext;
	iViewBitmapContext = NULL;

	delete iViewBitmapDevice;
	iViewBitmapDevice = NULL;

	iEikonEnv->EikAppUi()->RemoveFromStack(iAnimationCtrl);
	delete iAnimationCtrl;
	iAnimationCtrl = NULL;

	delete iViewBitmap;
	iViewBitmap = NULL;

	delete iOriginalBitmap;
	iOriginalBitmap = NULL;

	// return EFlase so that idle object is not called again
	return EFalse;
	}
                                
EXPORT_C void CAknAnimatedView::PreAnimateSetup()
	{
	}

EXPORT_C void CAknAnimatedView::PostAnimateSetup()
	{
	}

EXPORT_C void CAknAnimatedView::SetAnimationData(CAknAnimationData* aAnimationData)
	{
	iAnimationData = aAnimationData;
	}

EXPORT_C CWindowGc* CAknAnimatedView::SwapListBoxGc(CEikListBox* aListBox, CWindowGc* aWindowGc)
	{
	CAknDummyListBoxView* dummyView = REINTERPRET_CAST(CAknDummyListBoxView*,aListBox->View());
	return dummyView->SwapGraphicsContext(aWindowGc);
	}

