/*
* Copyright (c) 2006 Nokia Corporation and/or its subsidiary(-ies).
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
*
*/


#ifndef __TRANSITIONMANAGER_H__
#define __TRANSITIONMANAGER_H__

#include<eikenv.h>
#include<akntranseffect.h>
#include <coeview.h>

class CCenRepListen;


const TInt KAknTransitionEventAvkon = 999;
const TInt KAknTransitionEventFlags = 998;
const TInt KAknTransitionDeactivate = 997;
const TInt KAknTransitionExitCancel = 996;

NONSHARABLE_CLASS(MKeyValue)
	{
	public:
		virtual TUint32 Key() const = 0;
		virtual TInt Value() const = 0;
	};
	
NONSHARABLE_CLASS(MKeyListener)
	{
	public:
		 virtual void KeyChangedL(const MKeyValue& aKeyValue) = 0;
	};
	
NONSHARABLE_CLASS(MExit)
	{
	public:
		virtual void DoExit() = 0;
	};
	
NONSHARABLE_CLASS(CTransitionManager) : public CBase, public MKeyListener, public MExit,
                                        public MCoeViewObserver
	{
	public:
        static CTransitionManager* NewL(CEikonEnv& aEnv);
		~CTransitionManager();
		void SetAvkon();
		void CheckFlags();
		void AppStartup(TInt aContext, const TUid& aUid);
		void AppSwitch(TInt aContext); 
		void AppExit(TInt aContext, const TUid& aUid);
		void AppStartupComplete();
		void SetEmbedded(); 
		void CancelExit();
	private:
 	    static TBool AppStartupCb(TAny* aEnv);
    	TBool CheckPropertyKeys() const;
    	void Startup();
		CTransitionManager(CEikonEnv& aEnv);
		void ConstructL();
		TBool Ready();
		void KeyChangedL(const MKeyValue& aKeyValue);
		void CheckEffectsL(TBool aWait);
		void SetDisableEffects(TBool aDisable); 
		TBool IsFullScreen() const;
		void SendAvkonInfo();
		void GetRootAppL(TUid& aRootAppUid);
		void DoExit();

        // Implementation of void MCoeViewObserver
        void HandleViewEventL( const TVwsViewEvent& aEvent );
    private:
    	CEikonEnv& iEikEnv;
    	CIdle* iAppStartupIdle;
    	enum
    		{
    		EStarted 			= 0x1,
    		EEmbedded 			= 0x2,
    		ENoEndKeyClose 		= 0x4,
    		EEnviromentReady 	= 0x8,
    		EExitCompleted   	= 0x10,
    		EStartupComplete 	= 0x20,
    		EStartupStarted		= 0x40,
    		EffectsEnabled		= 0x80,
    		EAvkonApp			= 0x100,
    		};

        enum TTransEffectState
            {
            ETransEffectIdle,
            ETransEffectWaitingForAppSwitch,
            ETransEffectWaitingForViewSwitch,
            ETransEffectWaitingForIdleCall
            };

    	TInt iFlags;
    	TUid iAppUid;
        TTransEffectState iStartIdleState;
    	CCenRepListen* iCRListen;
	};
	
#endif	