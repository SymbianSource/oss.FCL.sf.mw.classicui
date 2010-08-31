/*
* Copyright (c) 2002-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:         Avkon Notifier test app
*
*/









// INCLUDE FILES
#include "bctestactiveengine.h"
#include <AknGlobalNote.h>


#include <avkon.rsg>



// ================= MEMBER FUNCTIONS =========================================
CBCTestActiveEngine::CBCTestActiveEngine()
: CActive( EPriorityStandard )
	{
	CActiveScheduler::Add( this );
	}

CBCTestActiveEngine::~CBCTestActiveEngine()
	{
	}

TRequestStatus* CBCTestActiveEngine::GetStatus()
	{
	return &iStatus;
	}

void CBCTestActiveEngine::RunL()
	{
	Cancel();
	}

void CBCTestActiveEngine::DoCancel()
	{
	}

TBool CBCTestActiveEngine::Active()
	{
	return IsActive();
	}

void CBCTestActiveEngine::MakeActive()
	{
	SetActive();
	}

CWaitGlobalNote* CWaitGlobalNote::NewL()
    {
    CWaitGlobalNote* self = new (ELeave) CWaitGlobalNote;
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();
    return self;
    }
	
CWaitGlobalNote::CWaitGlobalNote()
: CActive( EPriorityStandard )
	{
	CActiveScheduler::Add( this );
	}

CWaitGlobalNote::~CWaitGlobalNote()
	{
	Cancel();
	delete iNote;
	}

void CWaitGlobalNote::RunL()
	{
	iNote->CancelNoteL(noteId);
	}

void CWaitGlobalNote::DoCancel()
	{
	}
	
void CWaitGlobalNote::ConstructL()
    {
    iNote = CAknGlobalNote::NewL();
    iNote->SetSoftkeys( R_AVKON_SOFTKEYS_EMPTY );
    }
    
void CWaitGlobalNote::ShowGlobalNoteAsyncL()
	{
    _LIT(KNOTETEXT, "TEST");
	noteId = iNote->ShowNoteL( iStatus, EAknGlobalInformationNote, KNOTETEXT );
	SetActive();
	}

// End of File
