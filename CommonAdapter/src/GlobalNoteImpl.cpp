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
* Description:  Wrapper to AVKON global note functionality.
*
*/


// INCLUDE FILES
#include "GlobalNoteImpl.h"
#include <avkon.rsg>

// ============================ MEMBER FUNCTIONS =============================

// ---------------------------------------------------------------------------
// CGlobalNoteImpl::CGlobalNoteImpl
// C++ default constructor can NOT contain any code, that
// might leave.
// ---------------------------------------------------------------------------
//
CGlobalNoteImpl::CGlobalNoteImpl()
    {
    }


// ---------------------------------------------------------------------------
// CGlobalNoteImpl::ConstructL
// Symbian 2nd phase constructor can leave.
// ---------------------------------------------------------------------------
//
void CGlobalNoteImpl::ConstructL()
    {
    iAknGlobalNote = CAknGlobalNote::NewL();
    }


// ---------------------------------------------------------------------------
// CGlobalNoteImpl::NewL
// Two-phased constructor.
// ---------------------------------------------------------------------------
//
CGlobalNoteImpl* CGlobalNoteImpl::NewL()
    {
    CGlobalNoteImpl* self = new( ELeave ) CGlobalNoteImpl;

    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );

    return self;
    }


// ---------------------------------------------------------------------------
// CGlobalNoteImpl::~CGlobalNoteImpl
// Destructor
// ---------------------------------------------------------------------------
//
CGlobalNoteImpl::~CGlobalNoteImpl()
    {
    delete iAknGlobalNote;
    }


// ---------------------------------------------------------------------------
// CGlobalNoteImpl::SetSoftkeys()
// (other items were commented in a header).
// ---------------------------------------------------------------------------
//
void CGlobalNoteImpl::SetSoftkeys( TInt aId )
    {
    TInt id;
    SoftKeysInAvkon( aId, id );
    iAknGlobalNote->SetSoftkeys( id );
    }


// ---------------------------------------------------------------------------
// CGlobalNoteImpl::ShowNoteL()
// (other items were commented in a header).
// ---------------------------------------------------------------------------
//
TInt CGlobalNoteImpl::ShowNoteL( TGlobalNoteType aType,
                                 const TDesC& aNoteText )
    {
    TAknGlobalNoteType type;
    User::LeaveIfError( NoteTypeInAvkon( aType, type ) );

    return iAknGlobalNote->ShowNoteL( type, aNoteText );
    }


// ---------------------------------------------------------------------------
// CGlobalNoteImpl::ShowNoteL()
// (other items were commented in a header).
// ---------------------------------------------------------------------------
//
TInt CGlobalNoteImpl::ShowNoteL( TRequestStatus& aStatus,
                                 TGlobalNoteType aType,
                                 const TDesC& aNoteText )
    {
    TAknGlobalNoteType type;
    User::LeaveIfError( NoteTypeInAvkon( aType, type ) );

    // This way we can indicate to avkon global note that adapter is in use.
    iAknGlobalNote->SetPriority( 0xFFFF + 1 );

    return iAknGlobalNote->ShowNoteL( aStatus, type, aNoteText );
    }


// ---------------------------------------------------------------------------
// CGlobalNoteImpl::NoteTypeInAvkon()
// (other items were commented in a header).
// ---------------------------------------------------------------------------
//
TInt CGlobalNoteImpl::NoteTypeInAvkon( const TGlobalNoteType& aType,
                                       TAknGlobalNoteType& aAknType ) const
    {
    switch ( aType )
        {
        case EGlobalInformationNote:
            aAknType = EAknGlobalInformationNote;
            break;
        case EGlobalWarningNote:
            aAknType = EAknGlobalWarningNote;
            break;
        case EGlobalConfirmationNote:
            aAknType = EAknGlobalConfirmationNote;
            break;
        case EGlobalErrorNote:
            aAknType = EAknGlobalErrorNote;
            break;
        case EGlobalWaitNote:
            aAknType = EAknGlobalWaitNote;
            break;
        default:
            return KErrNotFound;
        }

    return KErrNone;
    }


// ---------------------------------------------------------------------------
// CGlobalNoteImpl::SoftKeysInAvkon()
// (other items were commented in a header).
// ---------------------------------------------------------------------------
//
void CGlobalNoteImpl::SoftKeysInAvkon( const TInt& aId, TInt& aAknId ) const
    {
    switch ( aId )
        {
        case EGlobalNoteSoftkeyOk:
            aAknId = R_AVKON_SOFTKEYS_OK_EMPTY;
            break;
        case EGlobalNoteSoftkeyExit:
            aAknId = R_AVKON_SOFTKEYS_EXIT;
            break;
        case EGlobalNoteSoftkeyCancel:
            aAknId = R_AVKON_SOFTKEYS_CANCEL;
            break;
        case EGlobalNoteSoftkeyBack:
            aAknId = R_AVKON_SOFTKEYS_BACK;
            break;
        case EGlobalNoteSoftKeyClose:
            aAknId = R_AVKON_SOFTKEYS_CLOSE;
            break;
        case EGlobalNoteSoftKeyQuit:
            aAknId = R_AVKON_SOFTKEYS_QUIT;
            break;
        case EGlobalNoteSoftkeyOkCancel:
            aAknId = R_AVKON_SOFTKEYS_OK_CANCEL;
            break;
        case EGlobalNoteSoftkeyYesNo:
            aAknId = R_AVKON_SOFTKEYS_YES_NO;
            break;
        case EGlobalNoteSoftkeyAnswerExit:
            aAknId = R_AVKON_SOFTKEYS_ANSWER_EXIT;
            break;
        default:
            aAknId = R_AVKON_SOFTKEYS_EMPTY;
            break;
        }
    }


// ---------------------------------------------------------------------------
// CGlobalNoteImpl::CancelGlobalNoteL()
// (other items were commented in a header).
// ---------------------------------------------------------------------------
//
void CGlobalNoteImpl::CancelGlobalNoteL( TInt aNoteId )
    {
    iAknGlobalNote->CancelNoteL( aNoteId );
    }

//  End of File
