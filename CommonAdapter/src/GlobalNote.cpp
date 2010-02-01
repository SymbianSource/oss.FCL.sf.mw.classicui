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
* Description:  API implementation for Global Note Adapter.
*
*/


// INCLUDE FILES
#include <globalnote.h>
#include <avkon.rsg> // For softkey resources

#include "GlobalNoteImpl.h"

// ============================ MEMBER FUNCTIONS =============================

// ---------------------------------------------------------------------------
// CGlobalNote::CGlobalNote
// C++ default constructor can NOT contain any code, that
// might leave.
// ---------------------------------------------------------------------------
//
CGlobalNote::CGlobalNote()
    {
    }


// ---------------------------------------------------------------------------
// CGlobalNote::ConstructL
// Symbian 2nd phase constructor can leave.
// ---------------------------------------------------------------------------
//
void CGlobalNote::ConstructL()
    {
    iImpl = CGlobalNoteImpl::NewL();
    }


// ---------------------------------------------------------------------------
// CGlobalNote::NewL
// Two-phased constructor.
// ---------------------------------------------------------------------------
//
EXPORT_C CGlobalNote* CGlobalNote::NewL()
    {
    CGlobalNote* self = NewLC();
    CleanupStack::Pop( self );

    return self;
    }


// ---------------------------------------------------------------------------
// CGlobalNote::NewLC
// Two-phased constructor.
// ---------------------------------------------------------------------------
//
EXPORT_C CGlobalNote* CGlobalNote::NewLC()
    {
    CGlobalNote* self = new( ELeave ) CGlobalNote;

    CleanupStack::PushL( self );
    self->ConstructL();

    return self;
    }


// ---------------------------------------------------------------------------
// CGlobalNote::~CGlobalNote
// Destructor
// ---------------------------------------------------------------------------
//
EXPORT_C CGlobalNote::~CGlobalNote()
    {
    delete iImpl;
    }


// ---------------------------------------------------------------------------
// CGlobalNote::SetSoftkeys()
// (other items were commented in a header).
// ---------------------------------------------------------------------------
//
EXPORT_C void CGlobalNote::SetSoftkeys( TGlobalNoteSoftkey aSoftkey )
    {
    iImpl->SetSoftkeys( aSoftkey );
    }


// ---------------------------------------------------------------------------
// CGlobalNote::ShowNoteL()
// (other items were commented in a header).
// ---------------------------------------------------------------------------
//
EXPORT_C TInt CGlobalNote::ShowNoteL( TGlobalNoteType aType,
                                      const TDesC& aNoteText )
    {
    return iImpl->ShowNoteL( aType, aNoteText );
    }


// ---------------------------------------------------------------------------
// CGlobalNote::ShowNoteL()
// (other items were commented in a header).
// ---------------------------------------------------------------------------
//
EXPORT_C TInt CGlobalNote::ShowNoteL( TRequestStatus& aStatus,
                                      TGlobalNoteType aType,
                                      const TDesC& aNoteText )
    {
    return iImpl->ShowNoteL( aStatus, aType, aNoteText );
    }


// ---------------------------------------------------------------------------
// CGlobalNote::CancelNoteL()
// (other items were commented in a header).
// ---------------------------------------------------------------------------
//
EXPORT_C void CGlobalNote::CancelNoteL( TInt aNoteId )
    {
    iImpl->CancelGlobalNoteL( aNoteId );
    }

//  End of File
