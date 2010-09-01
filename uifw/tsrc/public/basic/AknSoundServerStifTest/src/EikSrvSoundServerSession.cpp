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
* Description:  REikSrvSoundServerSession implementation. Direct copy from 
*                AknAnimKeySound.cpp.
*
*/

#include <e32std.h>
#include <eikkeysound.h>
#include "eiksrvsoundserversession.h"

// REikSrvSoundServerSession implementation:

// -----------------------------------------------------------------------------
// REikSrvSoundServerSession::Connect
// -----------------------------------------------------------------------------
//
TInt REikSrvSoundServerSession::Connect()
    {
    // Create a session with zero message slots 
    // (since we have no asycronous calls).
    TInt ret=CreateSession
        (
        __KEYSOUND_SERVER_NAME,
        TVersion( 
            KKeySoundServMajorVN, 
            KKeySoundServMinorVN, 
            KKeySoundServBuildVN ),
        1
        );
    return ret;  
    }

// -----------------------------------------------------------------------------
// REikSrvSoundServerSession::KeyPressed
//
// NB. as this is asynchronous, the cancel should be provided also, anyway we rely on that 
// keysound server will complete all requests relatively fast so we never stall on 
// ~CAknAnimKeySound more than tens of milliseconds.
// -----------------------------------------------------------------------------
//
void REikSrvSoundServerSession::KeyPressed( TInt aKey, TRequestStatus& aStatus, TBool aRepeat )
    {
    TIpcArgs args( aKey, aRepeat);    
    SendReceive( EKeySoundServerPlayKey, args, aStatus ); 
    }   
 
// -----------------------------------------------------------------------------
// REikSrvSoundServerSession::Init
//
// Added for testing purposes. Not copied from AknAnimKeySound.cpp!
// -----------------------------------------------------------------------------
//    
void REikSrvSoundServerSession::Init(TInt aUid)
    {
    TPckgBuf<TInt> init(ETrue);
    TIpcArgs args (&init, aUid);
    SendReceive(EKeySoundServerInit, args);
    }   
    
// End of file
