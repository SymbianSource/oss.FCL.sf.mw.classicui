// Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
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

#ifndef __GFXTRANSEFFECTPANIC_H__
#define __GFXTRANSEFFECTPANIC_H__

enum TGfxTransEffectPanic
	{
	EGfxTransEffectPanicRegisterArgument =1,
	EGfxTransEffectPanicIsRegisteredArgument,
	EGfxTransEffectPanicDeregisterArgument,
	EGfxTransEffectPanicBeginArgument,
	EGfxTransEffectPanicEndArgument,
	EGfxTransEffectPanicAbortArgument,
	EGfxTransEffectPanicSetHintsArgument,
	EGfxTransEffectPanicGetHintsArgument,
	EGfxTransEffectPanicInvalidateArgument,
	EGfxTransEffectPanicSetDemarcationArgument,
	EGfxTransEffectFindStatic,
	EGfxTransEffectNotSingleton
	};

#endif	// __GFXTRANSEFFECTPANIC_H__
