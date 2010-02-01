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

#include <e32std.h>
#include <vwsdef.h> // TVwsViewId

#include "GfxTransEffect.h"
#include "GfxTransUtils.h"
#include "GfxTransEffectPanic.h"

#ifndef TRANSITIONS_DISABLED
#include "GfxTransImpl.h"
#endif

#ifdef TRANSITIONS_DISABLED
#include <coecntrl.h>
#endif

EXPORT_C void GfxTransEffect::Register(const CCoeControl * aKey,const TVwsViewId &aView,TUid aType)
	{
	__ASSERT_DEBUG(aKey,Panic(EGfxTransEffectPanicRegisterArgument));
#ifndef TRANSITIONS_DISABLED
	CGfxTransEffect *singleton = CGfxTransEffect::Static(aKey);
	if(singleton) 
		singleton->Register(aKey,aView,aType);
#endif
	}
	
EXPORT_C void GfxTransEffect::Register(const CCoeControl * aKey,TUid aType,TBool aNLayered)
	{
	__ASSERT_DEBUG(aKey,Panic(EGfxTransEffectPanicRegisterArgument));
#ifndef TRANSITIONS_DISABLED		
	CGfxTransEffect *singleton = CGfxTransEffect::Static(aKey);
	if(singleton) 
		singleton->Register(aKey,aType,aNLayered);
#endif
	}
	
EXPORT_C TBool GfxTransEffect::IsRegistered(const CCoeControl * aKey)
	{
	__ASSERT_DEBUG(aKey,Panic(EGfxTransEffectPanicIsRegisteredArgument));
#ifndef TRANSITIONS_DISABLED
	CGfxTransEffect *singleton = CGfxTransEffect::StaticNoCreate(aKey);
	if(singleton) 
		return singleton->IsRegistered(aKey);
	else 
		return EFalse;
#else
	return EFalse;
#endif
	}
	
EXPORT_C void GfxTransEffect::Deregister(const CCoeControl * aKey)
	{
	__ASSERT_DEBUG(aKey,Panic(EGfxTransEffectPanicDeregisterArgument));
#ifndef TRANSITIONS_DISABLED	
	CGfxTransEffect *singleton = CGfxTransEffect::StaticNoCreate(aKey);
	if(singleton) 
		singleton->Deregister(aKey);	
#endif
	}
	
EXPORT_C void GfxTransEffect::Begin(const CCoeControl * aKey,TUint aAction)
	{
	__ASSERT_DEBUG(aKey,Panic(EGfxTransEffectPanicBeginArgument));
#ifndef TRANSITIONS_DISABLED
	CGfxTransEffect *singleton = CGfxTransEffect::Static(aKey);
	if(singleton) 
		singleton->Begin(aKey,aAction);
#endif
	}

EXPORT_C void GfxTransEffect::BeginLC(const CCoeControl * aKey,TUint aAction)
	{
	__ASSERT_DEBUG(aKey,Panic(EGfxTransEffectPanicBeginArgument));
#ifndef TRANSITIONS_DISABLED	
	CGfxTransEffect *singleton = CGfxTransEffect::Static(aKey);
	if(singleton) 
		singleton->BeginLC(aKey,aAction);
#endif
	}

EXPORT_C void GfxTransEffect::End(const CCoeControl * aKey)
	{
	__ASSERT_DEBUG(aKey,Panic(EGfxTransEffectPanicEndArgument));
#ifndef TRANSITIONS_DISABLED	
	CGfxTransEffect *singleton = CGfxTransEffect::Static(aKey);
	if(singleton) 
		singleton->End(aKey);
	else 
		aKey->DrawNow();
#else
	aKey->DrawNow();
#endif
	}
	
EXPORT_C void GfxTransEffect::NotifyExternalState(TInt aState, const TDesC8* aArg)
	{
#ifndef TRANSITIONS_DISABLED
	CGfxTransEffect *singleton = CGfxTransEffect::Static();
	if(singleton) 
		singleton->NotifyExternalState(aState,aArg);
#endif	
	}

	
EXPORT_C void GfxTransEffect::Abort(const CCoeControl * aKey)
	{
	__ASSERT_DEBUG(aKey,Panic(EGfxTransEffectPanicAbortArgument));
#ifndef TRANSITIONS_DISABLED	
	CGfxTransEffect *singleton = CGfxTransEffect::StaticNoCreate(aKey);
	if(singleton) 
		singleton->Abort(aKey);
#endif
	}

EXPORT_C void GfxTransEffect::SetHints(const CCoeControl * aControl,TUint aFlags)
	{
	__ASSERT_DEBUG(aControl,Panic(EGfxTransEffectPanicSetHintsArgument));
#ifndef TRANSITIONS_DISABLED	
	CGfxTransEffect *singleton = CGfxTransEffect::Static(aControl);
	if(singleton) 
		singleton->SetHints(aControl,aFlags);
#endif
	}
	
EXPORT_C TUint GfxTransEffect::GetHints(const CCoeControl * aControl)
	{
	__ASSERT_DEBUG(aControl,Panic(EGfxTransEffectPanicGetHintsArgument));
#ifndef TRANSITIONS_DISABLED
	CGfxTransEffect *singleton = CGfxTransEffect::StaticNoCreate(aControl);
	if(singleton) 
		return singleton->GetHints(aControl);
	else 
		return 0;
#else
	return 0;
#endif
	}
	
EXPORT_C void GfxTransEffect::SetHints(const CCoeControl * aControl,TUid aLayerType)
	{
	__ASSERT_DEBUG(aControl,Panic(EGfxTransEffectPanicSetHintsArgument));
#ifndef TRANSITIONS_DISABLED	
	CGfxTransEffect *singleton = CGfxTransEffect::Static(aControl);
	if(singleton) 
		singleton->SetHints(aControl,aLayerType);
#endif
	}

EXPORT_C void GfxTransEffect::Invalidate(const CCoeControl * aControl)
	{
	__ASSERT_DEBUG(aControl,Panic(EGfxTransEffectPanicInvalidateArgument));
#ifndef TRANSITIONS_DISABLED	
	CGfxTransEffect *singleton = CGfxTransEffect::Static(aControl);
	if(singleton) 
		singleton->Invalidate(aControl);
#endif
	}
	
EXPORT_C void GfxTransEffect::SetDemarcation(const CCoeControl * aControl,TPoint const &aDemarcation)
	{
	__ASSERT_DEBUG(aControl,Panic(EGfxTransEffectPanicSetDemarcationArgument));
#ifndef TRANSITIONS_DISABLED	
	CGfxTransEffect *singleton = CGfxTransEffect::Static(aControl);
	if(singleton) 
		singleton->SetDemarcation(aControl,aDemarcation);
#endif
	}
	
EXPORT_C void GfxTransEffect::SetDemarcation(TVwsViewId const &aView,TPoint const &aDemarcation)
	{
#ifndef TRANSITIONS_DISABLED	
	CGfxTransEffect *singleton = CGfxTransEffect::Static();
	if(singleton) 
		singleton->SetDemarcation(aView,aDemarcation);
#endif
	}
	
EXPORT_C void GfxTransEffect::SetDemarcation(const CCoeControl * aControl,TRect const &aDemarcation)
	{
	__ASSERT_DEBUG(aControl,Panic(EGfxTransEffectPanicSetDemarcationArgument));
#ifndef TRANSITIONS_DISABLED	
	CGfxTransEffect *singleton = CGfxTransEffect::Static(aControl);
	if(singleton) 
		singleton->SetDemarcation(aControl,aDemarcation);
#endif
	}
	
EXPORT_C void GfxTransEffect::SetDemarcation(TVwsViewId const &aView,TRect const &aDemarcation)
	{
#ifndef TRANSITIONS_DISABLED	
	CGfxTransEffect *singleton = CGfxTransEffect::Static();
	if(singleton) 
		singleton->SetDemarcation(aView,aDemarcation);
#endif
	}
	
EXPORT_C void GfxTransEffect::SetDemarcation(const CCoeControl * aControl,const CCoeControl * aSrc,TRect const &aDemarcation)
	{
	__ASSERT_DEBUG(aControl,Panic(EGfxTransEffectPanicSetDemarcationArgument));
#ifndef TRANSITIONS_DISABLED	
	CGfxTransEffect *singleton = CGfxTransEffect::Static(aControl);
	if(singleton) 
		singleton->SetDemarcation(aControl,aSrc,aDemarcation);
#endif
	}
	
EXPORT_C void GfxTransEffect::SetDemarcation(TVwsViewId const &aView,const CCoeControl * aSrc,TRect const &aDemarcation)
	{
#ifndef TRANSITIONS_DISABLED	
	CGfxTransEffect *singleton = CGfxTransEffect::Static();
	if(singleton) 
		singleton->SetDemarcation(aView,aSrc,aDemarcation);
#endif
	}

EXPORT_C void GfxTransEffect::Enable()
	{
#ifndef TRANSITIONS_DISABLED	
	CGfxTransEffect *singleton = CGfxTransEffect::Static();
	if(singleton) 
		singleton->Enable();
#endif
	}

EXPORT_C void GfxTransEffect::Disable()
	{
#ifndef TRANSITIONS_DISABLED	
	CGfxTransEffect *singleton = CGfxTransEffect::StaticNoCreate();
	if(singleton) 
		singleton->Disable();
#endif
	}
	
EXPORT_C TBool GfxTransEffect::IsEnabled()
	{
#ifndef TRANSITIONS_DISABLED	
	CGfxTransEffect *singleton = CGfxTransEffect::Static();
	if(singleton) 
		return singleton->IsEnabled();
	else 
		return EFalse;
#else
	return EFalse;
#endif
	}
	
EXPORT_C void GfxTransEffect::Abort()
	{
#ifndef TRANSITIONS_DISABLED	
	CGfxTransEffect *singleton = CGfxTransEffect::Static();
	if(singleton) 
		singleton->Abort();
#endif
	}

//API Additions.

EXPORT_C void GfxTransEffect::SetEndDemarcation(const CCoeControl* aControl, const TRect& aDemarcation)
	{
#ifndef TRANSITIONS_DISABLED	
	CGfxTransEffect *singleton = CGfxTransEffect::Static(aControl);
	if(singleton) 
		singleton->SetEndDemarcation(aControl, aDemarcation);
#endif
	}

EXPORT_C void GfxTransEffect::SetBeginDemarcation(const CCoeControl* aControl, const TRect& aDemarcation)
	{
#ifndef TRANSITIONS_DISABLED	
	CGfxTransEffect *singleton = CGfxTransEffect::Static(aControl);
	if(singleton) 
		singleton->SetBeginDemarcation(aControl, aDemarcation);
#endif
	}

EXPORT_C TInt GfxTransEffect::BeginGroup()
	{
#ifndef TRANSITIONS_DISABLED	
	CGfxTransEffect *singleton = CGfxTransEffect::Static();
	if(singleton) 
		return singleton->BeginGroup();
	return 0;
#else
	return 0;
#endif
	}

EXPORT_C void GfxTransEffect::EndGroup(TInt aGroupId)
	{
#ifndef TRANSITIONS_DISABLED	
	CGfxTransEffect *singleton = CGfxTransEffect::Static();
	if(singleton) 
		singleton->EndGroup(aGroupId);
#endif
	}

EXPORT_C void GfxTransEffect::SetTransitionData(TUint aType, const TDesC8& aData)
	{
#ifndef TRANSITIONS_DISABLED	
	CGfxTransEffect *singleton = CGfxTransEffect::Static();
	if(singleton) 
		singleton->SetTransitionData(aType, aData);
#endif
	}

EXPORT_C void GfxTransEffect::RegisterDrawItemControl(const CCoeControl* aControl, TUid aType)
	{
#ifndef TRANSITIONS_DISABLED	
	CGfxTransEffect *singleton = CGfxTransEffect::Static(aControl);
	if(singleton) 
		singleton->RegisterDrawItemControl(aControl, aType);
#endif
	}

EXPORT_C void GfxTransEffect::BeginDrawItem(const CCoeControl* aControl, TUint aId, TUid aType,TRect &aDrawRect,const TRect* aFromRect, const TRect* aToRect)
	{
#ifndef TRANSITIONS_DISABLED	
	CGfxTransEffect *singleton = CGfxTransEffect::Static(aControl);
	if(singleton) 
		singleton->BeginDrawItem(aControl, aId, aType, aDrawRect, aFromRect, aToRect);
#endif
	}

EXPORT_C void GfxTransEffect::EndDrawItem(const CCoeControl* aControl)
	{
#ifndef TRANSITIONS_DISABLED	
	CGfxTransEffect *singleton = CGfxTransEffect::Static(aControl);
	if(singleton) 
		singleton->EndDrawItem(aControl);
#endif
	}

EXPORT_C void GfxTransEffect::BeginFullScreen(TUint aAction, const TRect &aEffectArea)
	{
#ifndef TRANSITIONS_DISABLED	
	CGfxTransEffect *singleton = CGfxTransEffect::Static();
	if(singleton) 
		singleton->BeginFullScreen(aAction, aEffectArea);
#endif
	}

EXPORT_C void GfxTransEffect::BeginFullScreen(TUint aAction, const TRect &aEffectArea, TUint aType, const TDesC8& aParams)
	{
#ifndef TRANSITIONS_DISABLED	
	CGfxTransEffect *singleton = CGfxTransEffect::Static();
	if(singleton) 
		singleton->BeginFullScreen(aAction, aEffectArea, aType, aParams);
#endif
	}

EXPORT_C void GfxTransEffect::EndFullScreen()
	{
#ifndef TRANSITIONS_DISABLED	
	CGfxTransEffect *singleton = CGfxTransEffect::Static();
	if(singleton) 
		singleton->EndFullScreen();
#endif
	}

EXPORT_C void GfxTransEffect::AbortFullScreen()
	{
#ifndef TRANSITIONS_DISABLED	
	CGfxTransEffect *singleton = CGfxTransEffect::StaticNoCreate();
	if(singleton) 
		singleton->AbortFullScreen();
#endif
	}

EXPORT_C void GfxTransEffect::SetTransitionObserver(MGfxTransEffectObserver *aObserver)
	{
#ifndef TRANSITIONS_DISABLED
	CGfxTransEffect *singleton = CGfxTransEffect::Static();
	if(singleton) 
		singleton->SetTransitionObserver(aObserver);
#endif
	}
