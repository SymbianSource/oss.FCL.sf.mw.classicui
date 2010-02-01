/*
* Copyright (c) 2003 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  ?Description
*
*/


// INCLUDE FILES

#include "AknRichTextPhoneNumberInlineTextSource.h"
#include <finditemengine.h>

// MODULE TEMPLATES

// MODULE DATA STRUCTURES

const TInt KInitialRichTextPhoneNumberGroupingSize(10);

// ============================ MEMBER FUNCTIONS ===============================

////////////////////////////////////////////////////////////////////////////////
//
// CAknRichTextPhoneNumberInlineTextSource
//
////////////////////////////////////////////////////////////////////////////////

CAknRichTextPhoneNumberInlineTextSource* CAknRichTextPhoneNumberInlineTextSource::NewL( 
    const CRichText& aRichText )
    {
    CAknRichTextPhoneNumberInlineTextSource* self = 
        new (ELeave) CAknRichTextPhoneNumberInlineTextSource( aRichText );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();
    return self;
    }

void CAknRichTextPhoneNumberInlineTextSource::ConstructL()
    {
    iFindItemEngine = CFindItemEngine::NewL( KNullDesC, CFindItemEngine::EFindItemSearchPhoneNumberBin );
    ConstructNumberGroupingEngineL( KInitialRichTextPhoneNumberGroupingSize );
    CAknPhoneNumberInlineTextSource::ConstructL();
    }

CAknRichTextPhoneNumberInlineTextSource::~CAknRichTextPhoneNumberInlineTextSource()
    {
    delete iFindItemEngine;
    }

void CAknRichTextPhoneNumberInlineTextSource::EditObserver( TInt /*aStart*/, TInt /*aExtent*/ )
    {
    InlineTextStore()->Clear();

    TInt nFound = 0;
    TRAP_IGNORE( nFound = iFindItemEngine->DoNewSearchL(
                                                  Text().Read(0),
                                                  CFindItemEngine::EFindItemSearchPhoneNumberBin ) );

    if ( nFound > 0 )
        {
        const CArrayFixFlat<CFindItemEngine::SFoundItem>* itemArray = iFindItemEngine->ItemArray();

        for ( TInt index = 0; index < nFound; index++ )
            {
            const CFindItemEngine::SFoundItem& findItem = itemArray->At(index);
            TPtrC ptr( Text().Read(findItem.iStartPos, findItem.iLength ) );

            // Additional checks on the validity of the phone number:
            if ( FollowingCharIsValid(findItem.iStartPos + findItem.iLength) )
            	{
                TRAP_IGNORE( FormatPhoneNumberL( ptr, findItem.iStartPos ) );
            	}
          
            }
        }

#ifdef INLINE_EDIT_DUMPING
    // Dumping code
    TBuf<80> buf;
    RDebug::Print(_L("\nDump of inline texts"));
    for ( TInt index = 0; index < iInlineTextStore->Count(); index++)
        {

        CAknPositionedInlineText* inlineText = iInlineTextStore->At( index );
        TPtrC ptr = inlineText->InlineText();
        buf.Format( _L("DocPos: %d  Trailing/Leading: %d   Text=<%S>"), 
            inlineText->DocPos().iPos,
            inlineText->DocPos().iLeadingEdge, &ptr );

        RDebug::Print( buf );
        }
#endif

    }

CAknRichTextPhoneNumberInlineTextSource::CAknRichTextPhoneNumberInlineTextSource( 
     const CRichText& aText )
    : CAknPhoneNumberInlineTextSource(aText)
    {}

TBool CAknRichTextPhoneNumberInlineTextSource::FollowingCharIsValid( TInt aNextPos ) const
    {
    // We must be just at the end. There is no next character 
    if ( aNextPos >= Text().DocumentLength() )
        return ETrue;

    TPtrC ptr( Text().Read( aNextPos, 1 ) );
    if ( ptr[0] == '@' )
        return EFalse;

    return ETrue;
    }

//  End of File  
