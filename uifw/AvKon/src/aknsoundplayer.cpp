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

// AKNSOUNDPLAYER.CPP
//
// Copyright (c) 1997-2001 Symbian Ltd.  All rights reserved.
//

// Avkon KeySound Player


#include "aknsoundplayer.h"

#include <e32svr.h>
#include <f32file.h>
#include <eikenv.h>
#include <barsread.h>
#include <avkon.rsg>
#include <eikkeysound.h>
#include <s32mem.h>
#include "avkon.hrh"
#include <aknSoundinfo.h>

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
    TInt resSize = (items * 5);

    CBufFlat* buffer = CBufFlat::NewL(resSize);
    CleanupStack::PushL(buffer);

    RBufWriteStream bufStream;
    bufStream.Open(*buffer);

    CleanupClosePushL(bufStream);

    for (TInt ii=0; ii<items; ii++)
        {
        TInt sid = aReader.ReadInt16();
        TInt key = aReader.ReadUint16();
        TInt type = aReader.ReadInt8();
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


void RAknSoundServerSession::DisableNextKeySound( TInt aScanCode )
    {
    ServerRequest( EKeySoundServerDisableNextKeySound, TIpcArgs( aScanCode ) );
    }



// CAknSoundPlayer

CAknSoundPlayer* CAknSoundPlayer::NewL(TInt aUid)
    {
    CAknSoundPlayer* self = new(ELeave)CAknSoundPlayer(aUid);
    return self;
    }

CAknSoundPlayer::CAknSoundPlayer(TInt aUid)
:iAppUid(aUid)
    {
    }


CAknSoundPlayer::~CAknSoundPlayer()
    {
    iSession.Close();
    }



void CAknSoundPlayer::ConstructL()
    {
    User::LeaveIfError(iSession.Connect());
    TInt init = iSession.Init(iAppUid);
    if (init == EFalse)
        {
        // Add the default system sounds if the system has not yet been initialized
        DoAddSoundInfoResourceL(0, R_AVKON_DEFAULT_SOUND_LIST);
        // Push default skey context
        DoPushContextL(0, R_AVKON_DEFAULT_SKEY_LIST);
        }
    }


void CAknSoundPlayer::DoAddSoundInfoResourceL(TInt aUid, TInt aResourceId)
    {
    TResourceReader reader;
    CEikonEnv* eikonEnv = CEikonEnv::Static();
    eikonEnv->CreateResourceReaderLC(reader, aResourceId);
    iSession.AddSoundInfoResourceL(aUid, reader);
    CleanupStack::PopAndDestroy();  // reader
    }


void CAknSoundPlayer::Play(TInt aSid)
    {
    // If sId is less than EAvkonSIDNoSound, than this is a app-specific
    // sound, so add the app Uid to the value so that the server can distinguish
    TInt soundId = aSid;
    if (soundId < EAvkonSIDNoSound)
        {
        soundId = (iAppUid << 16) + aSid;
        };
    iSession.PlaySound(soundId);
    }

void CAknSoundPlayer::Stop(TInt aSid)
    {
    // If sId is less than EAvkonSIDNoSound, than this is a app-specific
    // sound, so add the app Uid to the value so that the server can distinguish
    TInt soundId = aSid;
    if (soundId < EAvkonSIDNoSound)
        {
        soundId = (iAppUid << 16) + aSid;
        };
    iSession.StopSound(soundId);
    }

void CAknSoundPlayer::PlaySound(TInt aScanCode, TInt aRepeat)
    {
    iSession.KeyPressed(aScanCode, aRepeat);
    }



void CAknSoundPlayer::AddAppSoundInfoListL(TInt aResourceId)
    {
    TResourceReader reader;
    CEikonEnv* eikonEnv = CEikonEnv::Static();
    eikonEnv->CreateResourceReaderLC(reader, aResourceId);
    iSession.AddSoundInfoResourceL(iAppUid, reader);
    CleanupStack::PopAndDestroy();  // reader
    }


void CAknSoundPlayer::PushContextL(TInt aResource)
    {
    DoPushContextL(iAppUid, aResource);
    }

void CAknSoundPlayer::DoPushContextL(TInt aUid, TInt aResource)
    {
    TResourceReader reader;
    CEikonEnv* eikonEnv = CEikonEnv::Static();
    eikonEnv->CreateResourceReaderLC(reader, aResource);
    iSession.PushContextL(aUid, reader, aResource);
    CleanupStack::PopAndDestroy();  // reader
    }

void CAknSoundPlayer::PopContext()
    {
    iSession.PopContext();
    }

void CAknSoundPlayer::BringToForeground()
    {
    iSession.BringToForeground();
    }

void CAknSoundPlayer::LockContext()
    {
    iSession.LockContext();
    }

void CAknSoundPlayer::ReleaseContext()
    {
    iSession.ReleaseContext();
    }

TInt CAknSoundPlayer::TopContext()
    {
    return iSession.TopContext();
    }
    
void CAknSoundPlayer::DisableNextKeySound( TInt aScanCode )
    {
    return iSession.DisableNextKeySound( aScanCode );
    }


TInt CAknSoundPlayer::RequestSoundInfoL(TInt aAvkonSid, CAknSoundInfo& aInfo)
    {
    TInt ret = KErrNotFound;
    TResourceReader reader;
    CEikonEnv::Static()->CreateResourceReaderLC(reader, R_AVKON_DEFAULT_SOUND_LIST);
    TInt count = reader.ReadInt16();

    for (TInt i = 0; i < count; i++)
        {
        TInt sid;
        TInt struct_id1 = reader.ReadInt16();
        TInt struct_id2 = reader.ReadInt16();
        TBool isAverell1Structure = ETrue;
        if (struct_id1 == 0x1234 && struct_id2 == 0x5678)
            {
            isAverell1Structure = EFalse;
            sid = reader.ReadInt16();
            aInfo.iPriority = (TInt16)reader.ReadInt16();
            }
        else
            {
            sid = struct_id1;
            aInfo.iPriority = struct_id2;
            }        

        aInfo.iPreference = reader.ReadInt32();
        TPtrC file = reader.ReadTPtrC();
        aInfo.iFrequency = (TInt16)reader.ReadInt16();
        aInfo.iDuration = reader.ReadInt32();

        TInt seqLength = reader.ReadInt16();

        if (file.Length() != 0)
            {
            aInfo.iType = ESoundFile;
            delete aInfo.iFile;
            aInfo.iFile = 0;
            aInfo.iFile = file.AllocL();
            }
        else if (seqLength == 0)
            {
            aInfo.iType = ESoundTone;
            }
        else
            {
            // type 2, sequence
            aInfo.iType = ESoundSequence;
            delete aInfo.iSequence;
            aInfo.iSequence = 0;
            TInt length = reader.ReadInt16();
            aInfo.iSequence = HBufC8::NewMaxL(length);
            TPtr8 ptr = aInfo.iSequence->Des();
            for (TInt ii = 0; ii < length; ii++)
                {
                ptr[ii] = reader.ReadUint8();
                }
            }

        if ( !seqLength && !isAverell1Structure )
            {
            reader.ReadInt16();
            }

        aInfo.iVolume = (TUint8)reader.ReadUint8();

        if ( sid == aAvkonSid ) 
            {
            ret = KErrNone;
            break;
            }
        } 
        
    CleanupStack::PopAndDestroy();  // reader
    return ret;
    }

#pragma warning( default : 4244 )


// End of File
