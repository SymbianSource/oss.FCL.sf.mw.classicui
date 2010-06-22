/*
* Copyright (c) 1997-1999 Nokia Corporation and/or its subsidiary(-ies).
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

#include <e32notif.h>
#include <eikalert.h>
#include <eikon.hrh>
#include <eikcdlg.rsg>
#include <eikappui.h>

#include <aknnotecontrol.h>
#include <AknGlobalNote.h>
#include <AknCapServerDefs.h>
#include <AknSgcc.h>


const TInt KEikAlertMaxMsgLength=17; // Maximum characters that fit on Avkon note
const TInt KCbaPriorityOffset = 10;
const TUint KCombinedBufferMaxLength = 80; // used with notifs

_LIT(KENDL,"\n");


void CEikAlert::ConstructL()
	{
	ConstructSleepingDialogL(R_EIK_DIALOG_ALERT);

    // preallocate text, 
    TBuf< KEikAlertMaxMsgLength*2 +1> buffer;
    buffer.SetLength( KEikAlertMaxMsgLength*2 +1);
    buffer.Fill( '1' );

	buffer.Replace( KEikAlertMaxMsgLength, 1, KENDL);
    SetTextL( buffer );

    Window().SetOrdinalPosition(0,ECoeWinPriorityAlwaysAtFront-1);
	}

void CEikAlert::RunAlert(const TDesC& aMsg1,const TDesC& aMsg2)
	{
	iMsg1=(&aMsg1);
	iMsg2=(&aMsg2);
	RouseSleepingDialog();
	}

void CEikAlert::Release()
	{
	delete this;
	}

CEikDialog* CEikAlert::AsEikDialog()
	{
	return this;
	}

void CEikAlert::PreLayoutDynInitL()
	{
    TBuf< KEikAlertMaxMsgLength*2 + 1 > buffer;

    if ( iMsg1->Length() > KEikAlertMaxMsgLength )
        {
        buffer.Copy( iMsg1->Left( KEikAlertMaxMsgLength ) );
        }
    else
        {
        buffer.Copy( *iMsg1 );
        }

    if ( iMsg2->Length() )
        {
        buffer.Append( '\n' );
        }

    if ( iMsg2->Length() > KEikAlertMaxMsgLength )
        {
        buffer.Append( iMsg2->Left( KEikAlertMaxMsgLength ) );
        }
    else
        {
        buffer.Append( *iMsg2 );
        }

    // This cannot leave because long enough text has been preallocated
    // in ConstructL.
	SetNoMemoryAllocation();
    SetTextL( buffer );

	// Update CBA stack priority, to match dialog priority
	CCoeControl* cba = ButtonGroupContainer().ButtonGroup()->AsControl();
	iEikonEnv->RemoveFromStack(cba);
	iEikonEnv->EikAppUi()->AddToStackL(cba, ECoeStackPriorityAlert+KCbaPriorityOffset, ECoeStackFlagRefusesFocus);	// Won't fail since we just removed it (and array will not reallocate)
	}

EXPORT_C void CEikAlert::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CAknNoteDialog::HandlePointerEventL(aPointerEvent); 
    }

EXPORT_C void* CEikAlert::ExtensionInterface( TUid /*aInterface*/ )
    {
    return NULL;
    }

void CEikAlert::CEikDialog_Reserved_1()
	{
	}

void CEikAlert::CEikDialog_Reserved_2()
	{
	}
	
void CEikAlert::CAknNoteDialog_Reserved()
	{
	}

CEikAlertNotifier::~CEikAlertNotifier()
    {
    delete iLocalDialog;
    delete iNotifierBuffer;        
    }

void CEikAlertNotifier::ConstructL()
    {
    iNotifierBuffer = CBufFlat::NewL(0); // no need to expand later on
    iNotifierBuffer->SetReserveL(200); // about 80 chars and control bytes
    RThread r;
    if (r.Name().CompareF(KAknCapServerThreadName) == 0)
        {
        CreateLocalDialogIfRequired();
        }
    
    }

class RAknUiServer2: public RAknUiServer
    {
    public:
    void DoSendNotifBuf(TPtrC8& aPtr)
       {
       TPckgBuf<SAknGlobalNoteReturnParams> retPckg;
       SendReceive(EStartNotifier,TIpcArgs(KAknGlobalNoteUid.iUid,&aPtr, &retPckg));
       }
    };


void CEikAlertNotifier::RunAlert(const TDesC& aTitle, const TDesC& aMsg)
    {
    RAknUiServer2* client = (RAknUiServer2*) CAknSgcClient::AknSrv();
    if (!client || client->Handle() == 0)
        {
        CreateLocalDialogIfRequired();
        if (iLocalDialog)
            iLocalDialog->RunAlert(aTitle, aMsg);
        return;
        }
    
    TBuf<KCombinedBufferMaxLength> combinedBuffer; // so sad, too bad
    combinedBuffer.Append(aTitle.Left(Min(aTitle.Length(), KCombinedBufferMaxLength)));
    if (combinedBuffer.Length() < KCombinedBufferMaxLength-1 && aMsg.Length())
        {
        combinedBuffer.Append(KENDL);
        combinedBuffer.Append(aMsg.Left(Min(KCombinedBufferMaxLength-combinedBuffer.Length(),aMsg.Length())));
        }   
     CAknGlobalNote::DoGlobaNoteBufferL(
        EAknGlobalWarningNote,
        0,
        R_AVKON_SOFTKEYS_OK_EMPTY,
        -1,
        -1,
        -1,
        -1,
        EFalse,
        ETrue,
        combinedBuffer,
        iNotifierBuffer
        );
    
    TPtrC8 bufferPtr;
    bufferPtr.Set(iNotifierBuffer->Ptr(0));
    
    client->DoSendNotifBuf(bufferPtr);
    }

void CEikAlertNotifier::Release()
    {
    delete this;
    }

CEikDialog* CEikAlertNotifier::AsEikDialog()
    {
    CreateLocalDialogIfRequired();
    return iLocalDialog;
    }

void CEikAlertNotifier::CreateLocalDialogIfRequired()
    {
    if (!iLocalDialog)
        {
        iLocalDialog = new CEikAlert;
        if (iLocalDialog)
            {
            TRAPD(err, iLocalDialog->ConstructL());
            if (err)
                {
                delete iLocalDialog;
                iLocalDialog = 0;
                }
            }
        }
    }



