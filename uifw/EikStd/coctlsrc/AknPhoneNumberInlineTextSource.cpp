/*
* Copyright (c) 2002-2004 Nokia Corporation and/or its subsidiary(-ies).
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

#include "AknPhoneNumberInlineTextSource.h"
#include <NumberGrouping.h>
#include <eikedwin.h>


// MODULE TEMPLATES

// MODULE DATA STRUCTURES

// ============================ MEMBER FUNCTIONS ===============================

////////////////////////////////////////////////////////////////////////////////
//
// CAknPhoneNumberInlineTextSource
//
////////////////////////////////////////////////////////////////////////////////

CAknPhoneNumberInlineTextSource::CAknPhoneNumberInlineTextSource( const CPlainText& aText )
    : CAknInlineTextSource(), iText(aText)
    {}

CAknPhoneNumberInlineTextSource::~CAknPhoneNumberInlineTextSource()
    {
    delete iPhoneNumberGrouping;
    }

const CPlainText& CAknPhoneNumberInlineTextSource::Text() const
    {
    return iText;
    }

CPNGNumberGrouping* CAknPhoneNumberInlineTextSource::PhoneNumberGrouping() const
    {
    return iPhoneNumberGrouping;
    }

void CAknPhoneNumberInlineTextSource::ConstructNumberGroupingEngineL( TInt aMaxFormattedLength )
    {
    // This ordering in order to guarantee that once we have a valid iPhoneNumberGrouping,
    // we never lose it.
    CPNGNumberGrouping* phoneNumberGrouping = CPNGNumberGrouping::NewL( aMaxFormattedLength ,EFalse );
    delete iPhoneNumberGrouping; // Can be deleted since the NewL did not leave
    iPhoneNumberGrouping = phoneNumberGrouping;
    }

void CAknPhoneNumberInlineTextSource::FormatPhoneNumberL( const TDesC& aPhoneNumberBuf, TInt aOffset )
    {
    TInt inputCount = aPhoneNumberBuf.Length();

    // Check if the number grouping engine needs to be re-created:
    if ( inputCount > iPhoneNumberGrouping->MaxDisplayLength() )
        {
        ConstructNumberGroupingEngineL( 2 * inputCount ); // Arbitrary but reasonable increase factor of 2
        }

    iPhoneNumberGrouping->Set( aPhoneNumberBuf );
    (void)iPhoneNumberGrouping->FormattedNumber();
    if ( iPhoneNumberGrouping->IsChangedByGrouping() )
        {
        TInt count = iPhoneNumberGrouping->Length();
        TInt spaceCount = 0; // Accumulates spaces
        for ( TInt index = 0; index < count; index++ )
            {
            if ( iPhoneNumberGrouping->IsCharacterInsertedByNumberGrouping( index ) )
                {
                spaceCount++;
                TTmDocPos docPos;
                docPos.iLeadingEdge = EFalse; // Trailing edge;
                if ( index == 0 ) // Use leading edge for the firt position
                    docPos.iLeadingEdge = ETrue;
                docPos.iPos = aOffset + index - spaceCount + 1; // +1 because it is trailing edge 
                TPtrC ptr( iPhoneNumberGrouping->FormattedNumber().Ptr()+index, 1 ); // handling one character at a time
                CAknPositionedInlineText* inlineText = 
                    CAknPositionedInlineText::NewL( docPos, ptr );
                CleanupStack::PushL( inlineText );
                InlineTextStore()->InsertInlineTextL( inlineText ); // Ownership is passed in
                CleanupStack::Pop(); // inlineText
                }
            }
        }   
    }

////////////////////////////////////////////////////////////////////////////////
//
// CAknPlainPhoneNumberInlineTextSource
//
////////////////////////////////////////////////////////////////////////////////

const TInt KInitialPlainPhoneNumberGroupingSize(10); // Good enough for 10 digit 123 456 7890


EXPORT_C CAknPlainPhoneNumberInlineTextSource* CAknPlainPhoneNumberInlineTextSource::NewL( 
    const CPlainText& aText )
    {
    CAknPlainPhoneNumberInlineTextSource* self = 
        new (ELeave) CAknPlainPhoneNumberInlineTextSource( aText );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();
    return self;
    }

CAknPlainPhoneNumberInlineTextSource::CAknPlainPhoneNumberInlineTextSource( const CPlainText& aText )
    : CAknPhoneNumberInlineTextSource(aText)
    {}

CAknPlainPhoneNumberInlineTextSource::~CAknPlainPhoneNumberInlineTextSource()
    {
    }

void CAknPlainPhoneNumberInlineTextSource::ConstructL()
    {
    ConstructNumberGroupingEngineL( KInitialPlainPhoneNumberGroupingSize );
    CAknInlineTextSource::ConstructL();
    }

TPtrC CAknPlainPhoneNumberInlineTextSource::PhoneNumberFromEditor(TInt& aStartPos) const
    {
    // Using DocumentLength() avoids including the 0x2029 (end of paragraph)
    // character at the end
    TInt length = Text().DocumentLength();
    aStartPos = 0;
    
    for(TInt i = 0; i < length; i++ )
        {
        TBuf<1> buf(Text().Read(i, 1 ));
        TLex lex(buf);
        TInt num = 0;
        //TBuf to TInt 
        TInt res = lex.Val(num);

        if(KErrNone != res)
            {
            aStartPos = i + 1;
            }
        }
    
    return Text().Read(aStartPos, length - aStartPos );
    }

/* 
 * This dictates the update policy. Formatting is triggered every call to CheckFormatting
 *
 */
void CAknPlainPhoneNumberInlineTextSource::CheckFormattingL(const TTmDocPos& /*aFrom*/, const TTmDocPos& /*aTo*/ )
    {
    DoFormatL();
    }

void CAknPlainPhoneNumberInlineTextSource::DoFormatL()
    {

    if ( ( Text().DocumentLength() != StoredNumberLength() ) || 
        ( CompareTextWithUnformattedNumber() != 0 ) )
        {
        // Clear whole buffer
        InlineTextStore()->Clear();
        TInt sartPos = 0;
        TPtrC phoneNumberPtr = PhoneNumberFromEditor(sartPos);
        
        FormatPhoneNumberL( phoneNumberPtr, sartPos);
        }
    }

TInt CAknPlainPhoneNumberInlineTextSource::CompareTextWithUnformattedNumber() const
    {
    TInt sartPos = 0;
    return PhoneNumberFromEditor(sartPos).Compare( PhoneNumberGrouping()->UnFormattedNumber() );
    }

TInt CAknPlainPhoneNumberInlineTextSource::StoredNumberLength() const
    {
    return PhoneNumberGrouping()->UnFormattedNumber().Length();
    }

//  End of File  
