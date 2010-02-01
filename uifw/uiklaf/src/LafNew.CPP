/*
* Copyright (c) 1997 - 2004 Nokia Corporation and/or its subsidiary(-ies).
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


#include <uiklaf/private/lafshut.h>
#include <ecom/ecom.h>
#include <s32mem.h>
#include <AknNotifySignature.h>
#include <aknconsts.h>
#include <AknUtils.h>
#include <avkon.hrh>
#include <featmgr.h>
#include <eikserverapp.h>
#include <AknSgcc.h>
#include <AknCapServerClient.h>

#include <uiklaf/private/lafenv.h>

const TInt KMaxGlobalNoteLength = 64; // maximum length of a 'static' global note

void GlobalNoteThroughRNotiferL(const TDesC& aNoteText)
    {
    // 29 bytes required for int fields, including 4 in descriptor header.
    const TInt KGlobalNoteBufferLength = (KMaxGlobalNoteLength * 2) + 32;   // 29 rounded up to 32
    TBuf8<KGlobalNoteBufferLength> globalNoteBuffer;
    
    RDesWriteStream bufStream(globalNoteBuffer);
    
    // None of these should leave since the space is already allocated
    
    bufStream.WriteInt32L(KAKNNOTIFIERSIGNATURE);
    
    bufStream.WriteInt16L(EAknGlobalErrorNote);
    bufStream << aNoteText;
    
    // Set default parameters
    
    bufStream.WriteInt16L(0);               // iPriority
    bufStream.WriteInt32L(R_AVKON_SOFTKEYS_OK_EMPTY); // iSoftkeys
    bufStream.WriteInt16L(-1);              // iGraphic;
    bufStream.WriteInt16L(-1);              // iGraphicMask
    bufStream.WriteInt32L(0);               // iAnimation
    bufStream.WriteInt16L(-1);              // iTone
    bufStream.WriteInt8L(0);                // adapter used Ffalse
    bufStream.WriteInt8L(1);                // Do text processing
    bufStream.WriteInt8L(0);                // no secondary display info
    
    bufStream.CommitL();
    
    TPckgBuf<SAknGlobalNoteReturnParams> retPckg;
    
    RNotifier notify;
    notify.Connect();
    notify.StartNotifier(KAknGlobalNoteUid, globalNoteBuffer, retPckg);
    notify.Close();
    }

void GlobalNoteThroughRAknSrvL(const TDesC& aNoteText)
    {
    RAknUiServer* aknSrv = CAknSgcClient::AknSrv();
    if (!aknSrv)
        User::Leave(KErrNotReady);
    
    aknSrv->ShowGlobalNoteL(aNoteText, EAknGlobalErrorNote);
    }

EXPORT_C void LafEnv::DisplayAlertAsNotifier(const TDesC& aMsg1, const TDesC& aMsg2)
    {
    __UHEAP_SETFAIL(RHeap::EDeterministic,1);
        
    TBuf<KMaxGlobalNoteLength> noteText;
    
    if (aMsg1.Length() > KMaxGlobalNoteLength)
        {
        noteText = aMsg1.Left(KMaxGlobalNoteLength);
        }
    else
        {
        noteText = aMsg1;
        TInt left = KMaxGlobalNoteLength - aMsg1.Length();
        // Insert a newline between the two texts if both are not
        // empty, and there is enough space
        if (aMsg1.Length() && aMsg2.Length() && left > 0)
            {
            left--;
            noteText.Append('\n');
            }
        // Insert Msg2 if there is enough space
        if (aMsg2.Length() > left)
            {
            noteText.Append(aMsg2.Left(left));
            }
        else
            {
            noteText.Append(aMsg2);
            }
        }
    
    TRAPD(aknSrvErr, GlobalNoteThroughRAknSrvL(noteText));
    if (aknSrvErr)
        GlobalNoteThroughRNotiferL(noteText);
    
    __UHEAP_RESET;
    }


EXPORT_C void LafEnv::HandleExtensionEventL( CEikonEnv& aEnv, TLafEnvExtensionEvent aEvent )
    {
    switch (aEvent)
        {
        case ELafEnvPreCoeEnvConstructL:     
            CAknEnv::InstallAknEnvAsExtensionL(&aEnv);
            break;
            
        case ELafEnvPostCoeEnvConstructL:
            STATIC_CAST(CAknEnv*,aEnv.Extension())->ConstructL();
            break;
            
        default:
            break;
        }
    }

EXPORT_C TInt LafEnv::PolicyItem( TLafEnvPolicyItem aItem )
    {
    switch( aItem )
        {
        case ELafEnvPolicyExitIfErrorDuringStartup:
            return ETrue;
            
        case ELafEnvPolicyDeleteCorruptDocumentAndContinue:
            return ETrue;
            
        case ELAfEnvPolicyDeferredEnvironmentDeletion:
            return ETrue;
            
        default:
            return EFalse;
        }
    }

