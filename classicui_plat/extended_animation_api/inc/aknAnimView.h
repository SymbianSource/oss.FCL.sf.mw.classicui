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


// AknAnimView.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

// Animation View class


#if !defined(__AKNANIMVIEW_H__)
#define __AKNANIMVIEW_H__

#include <aknview.h>
#include <eiklbv.h>

class CListBoxView;
class CEikListBox;

class CAknAnimatedGc;
class CAknAnimationCtrl;
class CAknAnimationData;
class CAknAnimationKeyWatcher;


class CAknDummyListBoxView : public CListBoxView
	{
public:
	CWindowGc* SwapGraphicsContext(CWindowGc* aGc);
private: // overridden from CListBoxView
	IMPORT_C virtual TAny* Reserved_1();
	};

class CAknAnimatedView : public CAknView
	{
public:
	IMPORT_C CAknAnimatedView();
	IMPORT_C ~CAknAnimatedView();
	IMPORT_C void SetAnimationData(CAknAnimationData* aAnimationData);
protected:
	IMPORT_C virtual void AknViewActivatedL(const TVwsViewId& aPrevViewId,TUid aCustomMessageId,const TDesC8& aCustomMessage);
	IMPORT_C virtual void PreAnimateSetup();
	IMPORT_C virtual void PostAnimateSetup();	
public:
	IMPORT_C CWindowGc* SwapListBoxGc(CEikListBox* aListBox, CWindowGc* aWindowGc);
private:
	static TInt DrawCallback(TAny* aPtr);
	TInt DoCallback();
private:
	void RestoreSystemGc();
private:
	CFbsBitmap*			iViewBitmap;
	CFbsBitmap*			iOriginalBitmap;
	CFbsBitmapDevice*	iViewBitmapDevice;
	CFbsBitGc*			iViewBitmapContext;
	CAknAnimatedGc*		iAnimatedGc;
	CWindowGc*			iOldSystemGc;
	CPeriodic*			iTimedDrawer;
	CAknAnimationCtrl*  iAnimationCtrl;
	CAknAnimationData*  iAnimationData;
	CAknAnimationKeyWatcher* iKeyWatcher;
	};


#endif
