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

#ifndef __WINCHANGEMONITOR_H__
#define __WINCHANGEMONITOR_H__

#include<e32base.h>
#include<w32std.h>

class RWsSession;

class CWindowChangeMonitor : public CBase
    {
    public:
        static CWindowChangeMonitor* NewL(RWsSession& aSession);
        ~CWindowChangeMonitor();
        void WgChangeL(TInt aFirstWg);
        void PartialWgChangeL(TInt aWg);
        void SetWgL(TInt aWg);
            
    private:
        CWindowChangeMonitor(RWsSession& aSession);
        void ConstructL();
    private:
     
    private:
        RWsSession& iSession;
        TUid    iCurrentUid;
        TUid    iNxtUid;
        TInt    iCurrentWg;
        TBool   iAborted;
    };
   
#endif // __WINCHANGEMONITOR_H__