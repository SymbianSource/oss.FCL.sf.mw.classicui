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

#ifndef __EIKLAFSHUTSTARTER_H__
#define __EIKLAFSHUTSTARTER_H__

#include <e32base.h>
#include <uiklaf/private/lafshut.h> // okay to include this in a private header

class CEikLafShutStarter : public CBase, public MShutdownEventObserver
    {
public:
    static CEikLafShutStarter* NewL(TBool aIsOOMF = EFalse);
    ~CEikLafShutStarter();

private:
    CEikLafShutStarter();
    void ConstructL(TBool aIsOOMF);

private: // from MShutdownEventObserver
    void HandleShutdownEventL(
        MSaveObserver::TSaveType aAction, 
        TBool aPowerOff, 
        TPowerState aEvent = EPwStandby);
        
    CArrayFix<TThreadId>* ClientArrayLC();
    TBool IsClientHung(TThreadId aId) const;
    void GetShutdownState(TBool& aPowerOff, TBool& aAllSessionsHavePendingRequest) const;
    
private:
    CLafShutdownManagerBase* iLafShutdown;
    };

#endif // __EIKLAFSHUTSTARTER_H__

// End of File
