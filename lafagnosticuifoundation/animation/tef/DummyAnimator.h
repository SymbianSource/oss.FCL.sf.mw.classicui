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
// These are a dummy data provider and animation.
// The intent of these is to prove that versions of each basic type can be
// created and added to the framework.  It is more important that this can
// be compiled and linked than that it does anything useful when run.
// 
//

/**
 @file
 @internalComponent - Internal Symbian test code 
*/

#include "Animator.h"
#include "AnimationMixins.h"

_LIT8(KCustomStepData, "dummy");

class CDummyAnimator : public CAnimator
	{
public:
    static CDummyAnimator* NewL(TAny* aRenderer)
    	{
    	return new(ELeave) CDummyAnimator(static_cast<MAnimationDrawer*>(aRenderer));
    	}
    ~CDummyAnimator() { }
public:
	void Start(const TAnimationConfig& /*aConfig*/) { }
	void Stop() { }
	void Pause() { }
	void Resume() { }
	void Hold() { }
	void Unhold() { }
	void DataEventL(TInt /*aEvent*/, TAny* aData, TInt aDataSize)
		{
		if (aDataSize == sizeof(TInt))
			*static_cast<TInt *>(aData) = 12345;
		}
	
	void Draw(CBitmapContext& /*aBitmapContext*/) const { }
	void DrawMask(CBitmapContext& /*aBitmapContext*/) const { }
private:
	CDummyAnimator(MAnimationDrawer* /*aRenderer*/) { }
	};
