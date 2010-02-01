// Copyright (c) 2004-2009 Nokia Corporation and/or its subsidiary(-ies).
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

#ifndef __SPRITEANIMATIONSERVER_H__
#define __SPRITEANIMATIONSERVER_H__

#include <e32std.h>
#include <w32adll.h>
#include "AnimationMixins.h"

class CAnimator;
class TAnimationConfig;
class CAnimationTls;
class CAnimationTicker;

/** @internalComponent */
NONSHARABLE_CLASS(CSpriteAnimationServer) : public CSpriteAnim, public MAnimationDrawer
	{
protected:
	enum TFlags
		{
		EInitialised	=	0x0001,
		EVirtualHold	=	0x0002,
		};
public:
	static CSpriteAnimationServer* NewL();
	~CSpriteAnimationServer();
private:
	CSpriteAnimationServer();
	void ReceiveEventL(TAny* aData);
	// From MAnimatorObserver:
	virtual void AnimatorDraw();
	virtual void AnimatorInitialisedL(const TSize& aSize);
	virtual void AnimatorResetL();
	virtual const TPtrC8 AnimatorDataType() const;
	virtual CAnimationTicker& AnimatorTicker();
	// Pure Virtual function from CSpriteAnim
	virtual void ConstructL(TAny *aArgs);
	// Virtual functions from CAnim
	virtual void Command(TInt aOpcode, TAny* aArgs);
	virtual TInt CommandReplyL(TInt aOpcode, TAny *aArgs);
	virtual void Animate(TDateTime* aDateTime);
	// Pure Virtual function from MEventHandler
	virtual TBool OfferRawEvent(const TRawEvent &aRawEvent);
private:
    void PostHostEvent();
private:
	TInt iFlags;
	CAnimationTls* iTls;
	CAnimator* iAnimator;
	CFbsBitGc* iSpriteGc;
	CFbsBitmapDevice* iBitmapDevice;
	CFbsBitmapDevice* iMaskDevice;	
	TSize iSize;
	HBufC8* iDataType;
	TInt iFreezeCount;
	TInt iHostHandle;
	};

#endif // __SPRITEANIMATIONSERVER_H__
