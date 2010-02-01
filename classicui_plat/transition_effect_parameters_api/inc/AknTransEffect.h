/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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
#ifndef __AKNTRANSEFFECT__
#define __AKNTRANSEFFECT__
	
#include<e32std.h>

namespace AknTransEffect
{

// Base transition context ID:s
enum TContext
    {
    ENone = 0,
    EApplicationActivate = 1,
 //   EApplicationDeactivate = 2,
    EApplicationStart = 3,
    EEmbeddedApplicationStart = 4, //not an effect context
    EApplicationExit = 5,
    EApplicationStartRect = 6,
    EApplicationStartSwitch = 7,
    EApplicationStartSwitchRect = 8,
    EEmbeddedApplicationExit = 10,  //not an effect context
    EAppStartComplete = 11,  //this is called when app start 2nd phase _can_ be started. (its started by AO!)
#ifdef RD_UI_TRANSITION_EFFECTS_LAYOUT_SWITCH
    ELayoutSwitch = 12, // default : swap to portrait.
    ELayoutSwitchExit = 13,
    ELayoutSwitchStart = 14,        
#endif //RD_UI_TRANSITION_EFFECTS_LAYOUT_SWITCH
    EAppSpesificEvent = 1000,
    EAppStartupBackground = 15
    };


const TUid KNotDefinedUid = {KNullUidValue};
	
enum TParameterType
	{
	EParamNone,
	EParameterType,
	EParameterAvkonInternal
	};

class TParameter
		{
		public:
			enum TFlag
				{
				EFlagNone 					= 0x0,  //by default activation is interrupted if UIDs differ
				EActivateExplicitContinue 	= 0x1, 	//this effect is not iterrupted even UID differs
				EActivateExplicitCancel		= 0x2, 	//this effect will cancel the current effect even if UID is the same
				ESecondaryDisplay			= 0x4,  //the effect is viewed in secondary display 
				EEndCheck					= 0x8,	//starts a timer that ensures end is coming
				ENoEffects					= 0x10, //if this flag is set no effects is displayed with this uid (works only in some cases!)
				EResetServerStats			= 0x20, //reset serverstats
				EAvkonCheck					= 0x40, //its check if app is avkon app
				EEnableEffects				= 0x80, //removes NoEffect
				EParentUid					= 0x100,//prev uid is parent					
				EAllowAtBoot				= 0x200,// allow effect at booting time					
				EFlagMask					= 0xFFF,
				EFirstFlag					= 0x1000,
				};
		  inline TParameter(const TUid& aNext, const TUid& aPrev, TInt aFlags);	
		  inline TParameter();		
		public:
			const TUid iNext;
			const TUid iPrev;
			const TInt iFlags;
		};


enum TTransitionStatusMask
	{
	EFullScreenTransitionsOff = 0x1,
	EComponentTransitionsOff = 0x2,
	EListGridTransitionsOff = 0x4,
	ELayoutswitchTransitionsOff = 0x8
	};

inline TParameter::TParameter() : 
	iNext(KNotDefinedUid), iPrev(KNotDefinedUid), iFlags(TParameter::EFlagNone)
	{
	}
inline TParameter::TParameter(const TUid& aNext, const TUid& aPrev, TInt aFlags) :
	iNext(aNext), iPrev(aPrev), iFlags(aFlags)
	{
	}
			
typedef TPckgBuf<AknTransEffect::TParameter> TParamBuffer;

inline TParamBuffer GfxTransParam(const TUid& aNext, const TUid& aPrev, TInt aFlags)
	{
	return TParamBuffer(TParameter(aNext, aPrev, aFlags));
	}
	
inline TParamBuffer GfxTransParam(const TUid& aNext, const TUid& aPrev)
	{
	return GfxTransParam(aNext, aPrev, TParameter::EFlagNone);
	}
	
inline TParamBuffer GfxTransParam(const TUid& aNext, TInt aFlags)
	{
	return GfxTransParam(aNext, KNotDefinedUid, aFlags);
	}
	
inline TParamBuffer GfxTransParam(const TUid& aNext)
	{
 	return GfxTransParam(aNext, KNotDefinedUid, TParameter::EFlagNone);
	}					

} // namespace AknTransEffect



#endif // __AKNTRANSEFFECT__

