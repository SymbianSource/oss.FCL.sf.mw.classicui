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
* Description:  Defines a common global note API meant to be
*               customised by each SW platform.
*
*/


#ifndef GLOBALNOTE_H
#define GLOBALNOTE_H

// INCLUDES
#include <e32base.h>

// CONSTANTS

// Available note types
enum TGlobalNoteType
    {
    EGlobalInformationNote  = 1,
    EGlobalWarningNote      = 2,
    EGlobalConfirmationNote = 3,
    EGlobalErrorNote        = 4,
    EGlobalWaitNote         = 5
    };

// Available note softkeys
enum TGlobalNoteSoftkey
    {
    // No sofkeys
    EGlobalNoteSoftkeyNone = 0,

    // Single button notes
    EGlobalNoteSoftkeyOk      = 1,
    EGlobalNoteSoftkeyExit    = 2,
    EGlobalNoteSoftkeyCancel  = 3,
    EGlobalNoteSoftkeyBack    = 4,
    EGlobalNoteSoftKeyClose   = 5,
    EGlobalNoteSoftKeyQuit    = 6,

    // Double button notes.
    EGlobalNoteSoftkeyOkCancel   = 1000,
    EGlobalNoteSoftkeyYesNo      = 1001,
    EGlobalNoteSoftkeyAnswerExit = 1002
    };


// Return values for asynchronous notes
enum TGlobalNoteResult
    {
    EGlobalNoteResultOk      = 1,
    EGlobalNoteResultExit    = 2,
    EGlobalNoteResultCancel  = 3,
    EGlobalNoteResultBack    = 4,
    EGlobalNoteResultClose   = 5,
    EGlobalNoteResultQuit    = 6,
    EGlobalNoteResultYes     = 7,
    EGlobalNoteResultNo      = 8,
    EGlobalNoteResultAnswer  = 9
    };

// FORWARD DECLARATIONS
class CGlobalNoteImpl;

// CLASS DECLARATION

/**
* Common global note adapter.
*
* Example usage of the API:
*
* Link your module against library commonadapter.lib
* Include header globalnote.h
*
* @code
*
*   _LIT( KNoteText, "Haaha..\nDoes this thing work at all" );
*   _LIT( KCancelText, "Cancelled" );
*
*   CGlobalNote* globalNote = CGlobalNote::NewLC();
*   globalNote->SetSoftkeys( EGlobalNoteSoftkeyOkCancel );
*   TRequestStatus status;
*   globalNote->ShowNoteL( status, EGlobalErrorNote, KNoteText );
*   User::WaitForRequest( status );
*   if ( status != KErrCancel )
*       {
*       TBuf<12> buf;
*       buf.AppendNum( status.Int() );
*       User::InfoPrint( buf );
*       }
*   else
*       {
*       User::InfoPrint( KCancelText );
*       }
*
*   CleanupStack::PopAndDestroy( globalNote );
*
* @endcode
*
* @lib commonadapter.lib
* @since 2.0
*/
NONSHARABLE_CLASS( CGlobalNote ) : public CBase
    {
public:

    /**
    *Two-phased constructors.
    */
    IMPORT_C static CGlobalNote* NewL();
    IMPORT_C static CGlobalNote* NewLC();

    /**
    * Destructor.
    */
    IMPORT_C ~CGlobalNote();

public: // New functions

    /**
    * Sets note softkeys.
    *
    * @since 2.0
    *
    * @param  aSoftKey  Softkey ID
    */
    IMPORT_C void SetSoftkeys( TGlobalNoteSoftkey aSoftkey );

    /**
    * Shows a global note. This call returns immediately.
    * Deleting @c CGlobalNote instance does not remove the
    * note after this call.
    *
    * @since 2.0
    *
    * @param  aType      Note type.
    * @param  aNoteText  Note text.
    *
    * @return  Note ID.
    */
    IMPORT_C TInt ShowNoteL( TGlobalNoteType aType, const TDesC& aNoteText );

    /**
    * Shows a global note. This call returns immediately.
    * Deleting @c CGlobalNote instance cancels the note after
    * this call. In this case, @c KErrCancel is returned in @c aStatus.
    *
    * @since 2.0
    *
    * @param  aStatus    After user has pressed a softkey, this returns the
    *                    corresponding @c TGlobalNoteResult code of
    *                    the pressed softkey.
    * @param  aType      Note type.
    * @param  aNoteText  Note text.
    *
    * @return  Note ID.
    */
    IMPORT_C TInt ShowNoteL( TRequestStatus& aStatus,
                             TGlobalNoteType aType,
                             const TDesC& aNoteText );

    /**
    * Cancels a started note by ID.
    *
    * @since 2.0
    *
    * @param  aNoteId  ID of the note to be canceled.
    */
    IMPORT_C void CancelNoteL( TInt aNoteId );

private:

    /**
    * C++ default constructor.
    */
    CGlobalNote();

    /**
    * Symbian 2nd-phase constructor.
    */
    void ConstructL();

private:

    /**
    * Pointer to separate implementation class.
    * Own.
    */
    CGlobalNoteImpl* iImpl;
    };

#endif // GLOBALNOTE_H
