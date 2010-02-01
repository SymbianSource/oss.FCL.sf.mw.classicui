/*
* Copyright (c) 2002-2007 Nokia Corporation and/or its subsidiary(-ies).
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

#include "winchangemonitor.h"
#include <apgwgnam.h>
#include <featmgr.h>
#include <apgtask.h>

#include <gfxtranseffect/gfxtranseffect.h>
#include <akntranseffect.h> // for Transition effect enumerations
#include <akntransitionutils.h>

#ifdef WCPLOG
#include <flogger.h>
#define LOG(x) Log(_L(x))
#define LOGF(x, y) Log(_L(x), y);

void Log(const TDesC& aStr, TInt aVal = 0)
    {
//#ifdef __WINS__
    RDebug::Print(_L("%S : %d"), &aStr, aVal);
//#else
    RFileLogger::WriteFormat(
        _L("effects"),
        _L("wcp.txt"),
        EFileLoggingModeOverwrite,
        _L("%S : %d"), &aStr, aVal);
//#endif
    }
#else
#define LOG(x)
#define LOGF(x, y)
#endif  
   
CWindowChangeMonitor* CWindowChangeMonitor::NewL(RWsSession& aSession)
    {
    LOG("CWindowChangeMonitor::NewL");
    if(!FeatureManager::FeatureSupported(KFeatureIdUiTransitionEffects))
        {
        // This is only place where flag was used since calling it is slow, after that this ptr
        // indicates its presense.
        return NULL; 
        }
    LOG("KFeatureIdUiTransitionEffects - ok");
    CWindowChangeMonitor* wc = new (ELeave) CWindowChangeMonitor(aSession);
    CleanupStack::PushL(wc);
    wc->ConstructL();   
    CleanupStack::Pop();
    return wc;
    }
    
CWindowChangeMonitor::CWindowChangeMonitor(RWsSession& aSession) : iSession(aSession)
    {
    }
    
void CWindowChangeMonitor::ConstructL()
    {
    }
        
CWindowChangeMonitor::~CWindowChangeMonitor()
    {
    }
   
void CWindowChangeMonitor::PartialWgChangeL(TInt aWg)   
    {
    if(iAborted != 0)
        {
        return;
        }
    iAborted = aWg;
    GfxTransEffect::NotifyExternalState( ENotifyGlobalAbort );
    GfxTransEffect::AbortFullScreen();
    }
    
void CWindowChangeMonitor::WgChangeL(TInt aFirstWg)
    {
    CApaWindowGroupName* name = CApaWindowGroupName::NewLC(iSession, aFirstWg);
    iNxtUid = name->AppUid();
    iCurrentWg = aFirstWg; 
    
    if(iNxtUid != iCurrentUid)
        {
        const TInt flags = AknTransEffect::TParameter::EFlagNone;
        GfxTransEffect::BeginFullScreen(
            AknTransEffect::EApplicationActivate, 
            TRect(0,0,0,0),
            AknTransEffect::EParameterType, 
            AknTransEffect::GfxTransParam(iNxtUid, iCurrentUid, flags)); 
        }
    CleanupStack::PopAndDestroy();  
    iAborted = 0;
    }
    
void  CWindowChangeMonitor::SetWgL(TInt aFirstWg)
    {
    if(iCurrentWg != aFirstWg)
        {
        iCurrentWg = aFirstWg; 
        CApaWindowGroupName* name = CApaWindowGroupName::NewLC(iSession, aFirstWg);
        iNxtUid = name->AppUid();
        CleanupStack::PopAndDestroy();
        }
    iCurrentUid = iNxtUid;
    iAborted = 0;
    }
 
// End of file  
