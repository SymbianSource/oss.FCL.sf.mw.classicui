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

#include "aknapp.h"
#include <eikenv.h>
#ifdef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <uikon/eikenvinterface.h>
#endif

#include <apgtask.h>
#include <apgwgnam.h>
#include <AknServerApp.h>
#include "AknTaskList.h"

#include <aknenv.h>
#include <akntranseffect.h> // for Transition effect enumerations
#include <UikonInternalPSKeys.h>
#include <e32property.h>
#include <AknSgcc.h>

LOCAL_C TBool IsInHiddenList(const TUid& aUid)
	{
	TBuf16<2 * KMaxHiddenApps> lst;
	if(KErrNone != RProperty::Get(KPSUidUikon, KUikAppHiddenList, lst))
		return EFalse;
	for(TInt i = 0; i < KMaxHiddenApps; i++)
		{
		const TInt bytePos = i << 1;
		const TUint32 uid = (lst[bytePos] << 16) | lst[bytePos + 1];
		if(aUid.iUid == uid)
			return ETrue;
		if(uid == 0) //end of list
			return EFalse;
		}
	return EFalse;
	}

EXPORT_C void CAknApplication::PreDocConstructL()
	{
	CEikonEnv* env = CEikonEnv::Static();
	if (!env->StartedAsServerApp() && !env->EikAppUi())
		{
		// Only run this check for top level (non embedded) apps.
		RWsSession& ws = env->WsSession();
		const TInt myWg = env->RootWin().Identifier();
		TInt wgId = 0;

		// set this apps UID in the window group name to remove the gap between this check and it being set in UpdateTaskNameL()
		TUid uid(AppDllUid());
		CApaWindowGroupName* wgName = CApaWindowGroupName::NewLC(ws, myWg);
		wgName->SetAppUid(uid);
		wgName->SetWindowGroupName(env->RootWin());

		// Use a CAknTaskList to check for root instances of apps
		CAknTaskList* taskList = CAknTaskList::NewLC(ws);
		TBool foundInstance = EFalse;
		
		// Look for another instance of this app
		while (wgId>=0)
			{
			if (wgId && wgId != myWg && taskList->IsRootWindowGroup(wgId))
				{	// found another app, switch to it & die
				/*
				TApaTask other(ws);
				other.SetWgId(wgId);
				other.BringToForeground();

				CBaActiveScheduler::Exit();
				*/
				foundInstance = ETrue;
				break;

				}

			CApaWindowGroupName::FindByAppUid(uid,ws,wgId);
			}
			
		if(!foundInstance)
			{
			//
            // Application launched with commands EApaCommandBackground or 
            // EApaCommandRunWithoutViews has non-zero ordinal position for their
            // window group.
            // For such applications transition effects on application start
            // should not be used.
            // 
            TInt ordPosition = env->RootWin().OrdinalPosition();
                    
			if (!ordPosition)
			    {
			    iAvkonEnv->TransitionEvent(AknTransEffect::EApplicationStart, AppDllUid());    
			    }			            
			else
			    {
			    iAvkonEnv->TransitionEvent( AknTransEffect::EAppStartupBackground, AppDllUid() );
			    }
			}
        else
            {
            // If application is launched to background, then do not bring application to
            // foreground. This needs to be deduced using ordinal position of root window
            // as command line parameters are not available to this method. With this
            // approach, there is small chance for error, but it's considered to be so
            // rare that this is acceptable. For example, otherwise applications launched
            // to background during startup might cause foreground application changes.
            const TInt ordPosition = env->RootWin().OrdinalPosition();
            if ( !ordPosition )
                {
                if(wgName->Hidden() || IsInHiddenList(AppDllUid()))
                    {
                    iAvkonEnv->TransitionEvent(AknTransEffect::EApplicationStartSwitch, AppDllUid());
                    }
                CAknSgcClient::MoveApp(wgId, ESgcMoveAppToForeground);
                }
            CBaActiveScheduler::Exit();
            }
        CleanupStack::PopAndDestroy(taskList); //taskList        
        CleanupStack::PopAndDestroy(wgName);
        }

	if(env->StartedAsServerApp())
		{
		// Start embedded
		iAvkonEnv->TransitionEvent(AknTransEffect::EEmbeddedApplicationStart, AppDllUid());
		}
	CEikApplication::PreDocConstructL();
	}

EXPORT_C CDictionaryStore* CAknApplication::OpenIniFileLC(RFs& /*aFs*/) const
	{
	// By default, ini files are not supported by SERIES60 applications.
	// If you want to use an ini file, either override this function to base call
	// CEikApplication::OpenIniFileLC, or call it directly.
	User::Leave(KErrNotSupported);
	return NULL;
	}

EXPORT_C void CAknApplication::NewAppServerL(CApaAppServer*& aAppServer)
	{
	aAppServer = new(ELeave) CAknAppServer;
	}
