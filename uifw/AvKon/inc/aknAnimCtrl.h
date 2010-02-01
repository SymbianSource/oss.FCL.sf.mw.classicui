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


// AknAnimCtrl.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

// Animation Control

#include <coecntrl.h>

#if !defined(__AKNANIMCTRL_H__)
#define __AKNANIMCTRL_H__


class CAknAnimationData;
class CAknAnimationCtrl;


NONSHARABLE_CLASS(CAknAnimationKeyWatcher) : public CCoeControl
	{
public:
	static CAknAnimationKeyWatcher* NewL();
	~CAknAnimationKeyWatcher();
	void SetAnimationControl(CAknAnimationCtrl* aAnimationCtrl);
private:
	TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	CAknAnimationKeyWatcher();
	void ConstructL();
private:
	CAknAnimationCtrl* iAnimationCtrl;
	};

NONSHARABLE_CLASS(CAknAnimationCtrl) : public CCoeControl
	{
public:
	static CAknAnimationCtrl* NewL(CWindowGc& aWindowGc, CFbsBitmap& aViewBitmap, CFbsBitmap& aOriginalBitmap, CAknAnimationData* aAnimationData);
	~CAknAnimationCtrl();
	TBool DrawStep();
	void CancelAnimation();
protected:
	CAknAnimationCtrl(CWindowGc& aWindowGc, CFbsBitmap& aViewBitmap, CFbsBitmap& aOriginalBitmap, CAknAnimationData* aData);
	void ConstructL();
	void Draw(const TRect& aRect) const;
private:
	CWindowGc& iWindowGc;
	CFbsBitmap& iViewBitmap;
	CFbsBitmap& iOriginalBitmap;
	TBool iCancelled;
	CAknAnimationData* iAnimationData;
	};


#endif
