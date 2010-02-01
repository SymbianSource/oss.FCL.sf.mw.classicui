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

#ifndef __ANIMATOR_H__
#define __ANIMATOR_H__

#include <e32base.h>

const TUid KAnimatorInterfaceUid = {0x10204F59};

class MAnimationDrawer;
class CBitmapContext;
class TAnimationConfig;

/**
Pure virtual base class for animators.

Each data type supported by the animation framework is represented by an
animator, which handles the data interpretation, timing and control.  Each
animator is provided in the form of an ECOM plugin.

You do not need to instatiate animators in a client application.  This is
handled by the animation classes.

@see CAnimation
@publishedAll
@released
*/
class CAnimator : public CBase
	{
public:
    // ECOM instatiation and destruction:
    IMPORT_C static CAnimator* NewL(MAnimationDrawer* aRenderer);
    IMPORT_C virtual ~CAnimator();
	/** Starts the animation running.
	@see TAnimationConfig
	@param aConfig Runtime settings*/
	virtual void Start(const TAnimationConfig& aConfig) = 0;
	/** Stops the animation and rewinds it.*/
	virtual void Stop() = 0;
	/** Pauses the animation.*/
	virtual void Pause() = 0;
	/** Resumes a paused animation.*/
	virtual void Resume() = 0;
	/** Puts an animation on hold. */
	virtual void Hold() = 0;
	/** Restores a held animation and brings it back into synch. */
	virtual void Unhold() = 0;
	/** Receives data from a data provider.  The mechanism by which data is
	actually passed depends on the animation type.
	
	@see MAnimationDataProviderObserver
	@param aEvent The event identifier
	@param aData A pointer to any data for the event
	@param aDataSize The length of the data in aData*/
	virtual void DataEventL(TInt aEvent, TAny* aData, TInt aDataSize) = 0;
	/** Called from the renderer and draws the animation.
	@param aBitmapContext The context on which the animation will be drawn*/
	virtual void Draw(CBitmapContext& aBitmapContext) const = 0;
	/** Called from the renderer and draws the mask for the animation.
	@param aBitmapContext The context on which the mask will be drawn*/
	virtual void DrawMask(CBitmapContext& aBitmapContext) const = 0;
protected:
	/** Animator ECOM Plugin identifier */
	TUid iDtor_ID_Key;
	/** Data */
	TInt iLoop;
	};

#endif //__ANIMATOR_H__

