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

#include "EikLafShutStarter.h"
#include <uiklaf/private/lafshut.h>

CEikLafShutStarter::CEikLafShutStarter()
    {
    }

CEikLafShutStarter* CEikLafShutStarter::NewL(TBool aIsOOMF)
    {
    CEikLafShutStarter* starter = new( ELeave ) CEikLafShutStarter;
    CleanupStack::PushL( starter );
    starter->ConstructL(aIsOOMF);
    CleanupStack::Pop();
    return starter;
    }

void CEikLafShutStarter::ConstructL(TBool /*aIsOOMF*/)
    {
    // Note: This method can leave (it is just not marked that it can)
    iLafShutdown = LafShutdown::CreateShutdownManager(*this); //Fix Me !!
    }

CEikLafShutStarter::~CEikLafShutStarter()
    {
    delete iLafShutdown;
    }

void CEikLafShutStarter::HandleShutdownEventL(MSaveObserver::TSaveType /*aAction*/,
    TBool /*aPowerOff*/, TPowerState /*aEvent*/)
    {
    }

CArrayFix<TThreadId>* CEikLafShutStarter::ClientArrayLC()
    {
    return NULL;
    }
    
TBool CEikLafShutStarter::IsClientHung(TThreadId /*aId*/) const
    {
    return EFalse;
    }

void CEikLafShutStarter::GetShutdownState(TBool& /*aPowerOff*/, 
    TBool& /*aAllSessionsHavePendingRequest*/) const
    {
    }

// End of file
