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
* Description:  RAknSoundServerSession implementation. Direct copy from 
*                aknsoundplayer.cpp.
*
*/

#include <e32std.h>
#include <s32mem.h>
#include <eikkeysound.h>
#include "aknsoundserversession.h"

// CONSTANTS
const TInt KAknResourceBufferSize = 512;

// RAknSoundServerSession

TInt RAknSoundServerSession::Connect()
    {
    iKeySoundServerExists = EFalse;

    // Create a session with zero message slots (since we have no asycronous calls)
    TInt ret=CreateSession(__KEYSOUND_SERVER_NAME,TVersion(KKeySoundServMajorVN,KKeySoundServMinorVN,KKeySoundServBuildVN),0);
    if ( ret == KErrNone )
        {
        iKeySoundServerExists = ETrue;
        }
    return KErrNone; 
    }

TInt RAknSoundServerSession::ServerRequest(TInt aFunction,const TIpcArgs& aArgs)
    {
    TInt err = KErrServerTerminated;
    if (Handle())
        {
        err = SendReceive(aFunction, aArgs);
        }       
    
    if (err == KErrServerTerminated)
        {
        // Try to reconnect, if the keysound server has been shutdown
        Connect();
        if ( iKeySoundServerExists )
            {
            err = SendReceive(aFunction, aArgs);
            }
        else 
            {
            return KErrNone; // We couldn't start KeySoundServer, just omit the error..
            }
        }
    return err;
    }

TBool RAknSoundServerSession::Init(TInt aUid)
    {
    // Initialise returnCode to ETrue because ServerRequest may fail to set it if sound
    // server is broken, and in that case we do not want to attempt to load sounds from
    // resource, which may happen if the uninitialised value == EFalse.
    TPckgBuf<TInt> returnCode(ETrue);

    TIpcArgs args ( &returnCode, aUid );
    ServerRequest(EKeySoundServerInit,args);
    return returnCode();
    }

#pragma warning( disable : 4244 )
//\S60\AVKON\SRC\Aknsoundplayer.cpp(404) : warning C4244: '=' : conversion from 'int' to 'short', possible loss of data

void RAknSoundServerSession::AddSoundInfoResourceL(TInt aUid, TResourceReader aReader)
    {
    // Read information from resource read, and package up as a buffer
    CBufFlat* buffer = CBufFlat::NewL(KAknResourceBufferSize);
    CleanupStack::PushL(buffer);

    RBufWriteStream bufStream;
    bufStream.Open(*buffer);

    CleanupClosePushL(bufStream);

    TInt count = aReader.ReadInt16();

    bufStream.WriteUint16L(count);

    for (TInt ii=0; ii<count; ii++)
        {
        TInt struct_id1 = aReader.ReadInt16();
        TInt struct_id2 = aReader.ReadInt16();
        TInt sid;
        TInt priority;
        TBool isAverell1Structure = ETrue;
        if (struct_id1 == 0x1234 && struct_id2 == 0x5678)
            {
            isAverell1Structure = EFalse;
            sid = aReader.ReadInt16();
            priority = aReader.ReadInt16();
            }
        else
            {
            sid = struct_id1;
            priority = struct_id2;
            }        
        
        TInt soundId = (aUid << 16) + sid;
        TInt preference = aReader.ReadInt32();
        TPtrC file = aReader.ReadTPtrC();
        TInt frequency = aReader.ReadInt16();
        TInt ms = aReader.ReadInt32();

        TInt seqLength = aReader.ReadInt16();

        bufStream.WriteUint32L(soundId);
        bufStream.WriteUint16L(priority);
        bufStream.WriteUint32L(preference);
        if (file.Length() != 0)
            {
            bufStream.WriteUint8L(0);   // type 0, file
            bufStream << file;
            }
        else if (seqLength == 0)
            {
            bufStream.WriteUint8L(1);   // type 1, tone
            bufStream.WriteUint16L(frequency);
            bufStream.WriteUint32L(ms);
            }
        else
            {
            // Write sequence
            bufStream.WriteUint8L(2);   // type 2, sequence
            TInt actualLength = aReader.ReadUint16();
            bufStream.WriteUint16L(actualLength);
            for (TInt count=0; count<actualLength; count++)
                {
                bufStream.WriteUint8L(aReader.ReadUint8());
                }
            }
        if ( !seqLength && !isAverell1Structure )
            {
            aReader.ReadUint16(); // ignore
            }

        bufStream.WriteUint8L(aReader.ReadUint8()); // Read volume info.    
        }

    CleanupStack::PopAndDestroy();            // bufstream close

    TPtr8 bufPtr = buffer->Ptr(0);
    TIpcArgs args (aUid, bufPtr.Length(), &bufPtr);
    User::LeaveIfError( ServerRequest(EKeySoundServerAddSIDS,args) ); 

    CleanupStack::PopAndDestroy();  // buffer
    }

void RAknSoundServerSession::PushContextL(TInt aUid, TResourceReader& aReader, TInt aResourceId)
    {
    TInt items = aReader.ReadInt16();
    // RDebug::Print(_L("Items:%d"), items);
    
    TInt resSize = (items * 5);

    CBufFlat* buffer = CBufFlat::NewL(resSize);
    CleanupStack::PushL(buffer);

    RBufWriteStream bufStream;
    bufStream.Open(*buffer);

    CleanupClosePushL(bufStream);

    for (TInt ii=0; ii<items; ii++)
        {
        TInt sid = aReader.ReadInt16();
        // RDebug::Print(_L("sid:%d"), sid);
        
        TInt key = aReader.ReadUint16();
        // RDebug::Print(_L("key:%d"), key);
        
        TInt type = aReader.ReadInt8();
        // RDebug::Print(_L("type (8bit):%d"), type);
        
        bufStream.WriteInt16L(sid);
        bufStream.WriteUint16L(key);
        bufStream.WriteUint8L(type);
        }

    CleanupStack::PopAndDestroy();            // bufstream close

    TPtr8 bufPtr = buffer->Ptr(0);
    TIpcArgs args (items, &bufPtr, aUid, aResourceId);
    User::LeaveIfError(ServerRequest(EKeySoundServerPushContext,args));
    CleanupStack::PopAndDestroy();  // buffer
    }
    
void RAknSoundServerSession::PopContext()
    {
    ServerRequest(EKeySoundServerPopContext,TIpcArgs());
    }

void RAknSoundServerSession::PlaySound(TInt aSid)
    {
    ServerRequest(EKeySoundServerPlaySID,TIpcArgs(aSid));
    }

void RAknSoundServerSession::StopSound(TInt aSid)
    {
    ServerRequest(EKeySoundServerStopCurrentTone,TIpcArgs(aSid));
    }

void RAknSoundServerSession::KeyPressed(TInt aKey, TBool aRepeat)
    {
    TIpcArgs args (aKey,aRepeat);
    ServerRequest(EKeySoundServerPlayKey,args);
    }

void RAknSoundServerSession::BringToForeground()
    {
    ServerRequest(EKeySoundServerBringToForeground,TIpcArgs());
    }

void RAknSoundServerSession::LockContext()
    {
    ServerRequest(EKeySoundServerLockContext,TIpcArgs());
    }

void RAknSoundServerSession::ReleaseContext()
    {
    ServerRequest(EKeySoundServerReleaseContext,TIpcArgs());
    }

TInt RAknSoundServerSession::TopContext()
    {
    TInt aContextResourceId = 0;
    TPckg<TInt> pckg(aContextResourceId);
    ServerRequest(EKeySoundServerTopContext,TIpcArgs(&pckg));
    return aContextResourceId;
    }

// End of file
