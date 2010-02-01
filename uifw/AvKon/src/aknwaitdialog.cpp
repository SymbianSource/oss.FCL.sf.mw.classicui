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
*       Implementation of the CAknWaitDialog class.
*
*/


#include <AknWaitDialog.h>
#include <aknnotecontrol.h>
#include <AknPanic.h>
#include <eikenv.h>
#include <eikappui.h>


// const TInt KMinProcessTimeToShowDialog = 1000000;	// 1 sec
// const TInt KMinTimeDialogOnScreen = 1500000;	// 1.5 sec

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

EXPORT_C CAknWaitDialog::CAknWaitDialog(CEikDialog** aSelfPtr) :
	CAknProgressDialog(aSelfPtr)
	{
	}

EXPORT_C CAknWaitDialog::CAknWaitDialog(CEikDialog** aSelfPtr,TBool aVisibilityDelayOff) :
	CAknProgressDialog(aSelfPtr, aVisibilityDelayOff)
	{
	}

EXPORT_C CEikProgressInfo* CAknWaitDialog::GetProgressInfo()
	{
    Panic( EAknPanicNotSupported );
	return NULL;
	}
	
EXPORT_C void CAknWaitDialog::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CAknProgressDialog::HandlePointerEventL(aPointerEvent); 
    }

EXPORT_C void* CAknWaitDialog::ExtensionInterface( TUid /*aInterface*/ ) 
    { 
    return NULL;
    }

EXPORT_C void CAknWaitDialog::CEikDialog_Reserved_1()
	{
	}

EXPORT_C void CAknWaitDialog::CEikDialog_Reserved_2()
	{
	}

EXPORT_C void CAknWaitDialog::CAknNoteDialog_Reserved()
	{
	}

// End of File
