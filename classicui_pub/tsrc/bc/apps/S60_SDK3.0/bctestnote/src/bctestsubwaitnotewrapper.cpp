/*
* Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:         Implement MAknProgressDialogCallBack.
*
*/









#include <w32std.h>
#include <coecntrl.h>

#include "bctestsubwaitnotewrapper.h"

const TInt KMaxNumber = 10000000;

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestSubWaitNoteWrapper* CBCTestSubWaitNoteWrapper::NewL()
    {
    CBCTestSubWaitNoteWrapper* self = 
        new( ELeave ) CBCTestSubWaitNoteWrapper();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default constructor
// ---------------------------------------------------------------------------
//
CBCTestSubWaitNoteWrapper::CBCTestSubWaitNoteWrapper()
    {
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestSubWaitNoteWrapper::~CBCTestSubWaitNoteWrapper()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestSubWaitNoteWrapper::ConstructL()
    {
	iCounter = 0;
    }

// ---------------------------------------------------------------------------
// CBCTestSubWaitNoteWrapper::StepL()
// ---------------------------------------------------------------------------
//
void CBCTestSubWaitNoteWrapper::StepL()
    {
	iCounter++;
    }  

// ---------------------------------------------------------------------------
// CBCTestSubWaitNoteWrapper::IsProcessDone()
// ---------------------------------------------------------------------------
//
TBool CBCTestSubWaitNoteWrapper::IsProcessDone() const
    {
    if ( iCounter > KMaxNumber )
        {   
        return ETrue;
        }
	else 
        {
        return EFalse;
        }	
    }

// ---------------------------------------------------------------------------
// CBCTestSubWaitNoteWrapper::ProcessFinished()
// ---------------------------------------------------------------------------
//
void CBCTestSubWaitNoteWrapper::ProcessFinished()
    {
 
    }

// ---------------------------------------------------------------------------
// CBCTestSubWaitNoteWrapper::DialogDismissedL(TInt aButtonId);
// ---------------------------------------------------------------------------
//
void CBCTestSubWaitNoteWrapper::DialogDismissedL( TInt aButtonId )
    {
    if ( aButtonId == -1 )
        {
		iCounter = 0;
		}
    }    





    
   

    
