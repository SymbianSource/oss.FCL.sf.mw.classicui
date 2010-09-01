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
* Description:  Global Note Implementation for Common Adapter.
*
*/


#ifndef GLOBALNOTEIMPL_H
#define GLOBALNOTEIMPL_H

//  INCLUDES
#include <e32std.h>
#include <AknGlobalNote.h>
#include <GlobalNote.h>

// CLASS DECLARATION

/**
* Global Note Internal Implementation API.
* This API offers methods and mappings for the global note adapter into S60
* global note functionality.
*
* @lib CommonAdapter.lib
* @since 2.0
*/
NONSHARABLE_CLASS( CGlobalNoteImpl ): public CBase
    {
public: // New functions

    /**
    * Two phase constructor
    * @since 2.0
    */
    static CGlobalNoteImpl* NewL();

    /**
    * Destructor
    */
    ~CGlobalNoteImpl();

    /**
    * Wrapper to call @c CAknGlobalNote::ShowNoteL()
    * @since 2.0
    *
    * @param  aType      Note type.
    * @param  aNoteText  Note text.
    *
    * @return  Note ID.
    */
    TInt ShowNoteL( TGlobalNoteType aType, const TDesC& aNoteText );

    /**
    * Wrapper to call @c CAknGlobalNote::ShowNoteL()
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
    TInt ShowNoteL( TRequestStatus& aStatus,
                    TGlobalNoteType aType,
                    const TDesC& aNoteText );

    /**
    * Wrapper to call @c CAknGlobalNote::CancelGlobalNoteL()
    * @since 2.0
    *
    * @param  aNoteId  ID of the note to be canceled.
    */
    void CancelGlobalNoteL( TInt aNoteId );

    /**
    * Wrapper to call @c CAknGlobalNote::SetSoftKeys()
    * @since 2.0
    *
    * @param  aId  Softkey ID.
    */
    void SetSoftkeys( TInt aId );

private: // New functions

    /**
    * Default constructor
    */
    CGlobalNoteImpl();

    /**
    * Second part of two phase construction.
    */
    void ConstructL();

    /**
    * Maps AVKON global note type according to @c TGlobalNoteType given.
    * @since 2.0
    *
    * @param       aType     Common global note type.
    * @param[out]  aAknType  Corresponding type in AVKON global notes.
    *
    * @return  @c KErrNotFound if note type not supported in AVKON.
    */
    TInt NoteTypeInAvkon( const TGlobalNoteType& aType,
                          TAknGlobalNoteType& aAknType ) const;

    /**
    * Maps AVKON soft key resource id according to @c aId given.
    * @since 2.0
    *
    * @param       aId     Common softkey ID.
    * @param[out]  aAknId  Corresponding AVKON softkey ID.
    *
    * @return  @c KErrNotFound if softkey ID not found from AVKON.
    */
    void SoftKeysInAvkon( const TInt& aId, TInt& aAknId ) const;

private: // Member definitions

    /**
    * Pointer to AVKON global note instance.
    * Own.
    */
    CAknGlobalNote* iAknGlobalNote;
    };

#endif // GLOBALNOTEIMPL_H

// End of File
