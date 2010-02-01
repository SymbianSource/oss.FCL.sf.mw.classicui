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


#include <eikinfo.h>
#include <eikon.hrh>
#include <eikcdlg.rsg>
#ifndef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <eikdef.h>
#else
#include <eikdef.h>
#include <uikon/eikdefconst.h>
#endif

EXPORT_C CEikInfoDialog::CEikInfoDialog(const TDesC& aTitle,const TDesC& aMsg,TExitKeys /*aExitKeys*/)
	: CAknNoteDialog(), iTitle(&aTitle), iMessage(&aMsg)
	{}

CEikInfoDialog::CEikInfoDialog(TExitKeys /*aExitKeys*/)
	: CAknNoteDialog()
	{}

EXPORT_C TBool CEikInfoDialog::RunDlgLD(const TDesC& aTitle,const TDesC& aMsg,TExitKeys aExitKeys)
	{ // static
	CEikInfoDialog* dlg=new(ELeave)CEikInfoDialog(aTitle, aMsg, aExitKeys);
	return dlg->ExecuteLD(R_EIK_DIALOG_QUERY);
	}

TBool CEikInfoDialog::RunDlgLD(TInt aResource, const TDesC& aTitle, const TDesC& aMsg)
	{
	iTitle = &aTitle;
	iMessage = &aMsg;

	if (aResource==KEikResIdQueryDialog)
		return ExecuteLD(R_EIK_DIALOG_QUERY);
	
	else if (aResource==KEikResIdInfoDialog)
		return ExecuteLD(R_EIK_DIALOG_INFO);
	
	else
		return ExecuteLD(aResource);
	}

void CEikInfoDialog::PreLayoutDynInitL(void)
	{
	if (iMessage && iTitle)
		{
		HBufC* msg = HBufC::NewLC(iTitle->Length() + iMessage->Length() + 1);
		
		TPtr ptr = msg->Des();
		ptr.Format(_L("%S\n%S"),iTitle,iMessage);
		
		SetTextL(ptr);
		CleanupStack::PopAndDestroy(); //msg
		}
	else if (iMessage)
		{
		SetTextL(*iMessage);
		}
	else if (iTitle)
		{
		SetTextL(*iTitle);
		}
	CAknNoteDialog::PreLayoutDynInitL();
	}

EXPORT_C void CEikInfoDialog::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CAknNoteDialog::HandlePointerEventL(aPointerEvent); 
    }

EXPORT_C void* CEikInfoDialog::ExtensionInterface( TUid /*aInterface*/ )
    {
    return NULL;
    }

EXPORT_C void CEikInfoDialog::CEikDialog_Reserved_1()
	{
	}

EXPORT_C void CEikInfoDialog::CEikDialog_Reserved_2()
	{
	}
