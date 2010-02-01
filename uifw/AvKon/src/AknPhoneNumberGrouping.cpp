/*
* Copyright (c) 2004 - 2008 Nokia Corporation and/or its subsidiary(-ies).
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
*    This class gives variant-independent access to S60 number grouping 
*    features and provides digit type conversion.
*
*
*/


// INCLUDE FILES

#include <e32std.h>
#include <NumberGrouping.h>

#include "AknPhoneNumberGrouping.h"
#include "AknUtils.h"

// CONSTANTS

// ============================ MEMBER FUNCTIONS ===============================

EXPORT_C CAknPhoneNumberGrouping* CAknPhoneNumberGrouping::NewLC( TInt aUnformattedLength )
    {
    CAknPhoneNumberGrouping* self=new(ELeave) CAknPhoneNumberGrouping();
    CleanupStack::PushL(self);
    self->ConstructL(aUnformattedLength);
    return self;
    }

EXPORT_C CAknPhoneNumberGrouping* CAknPhoneNumberGrouping::NewL( TInt aUnformattedLength )
    {
    CAknPhoneNumberGrouping* self = CAknPhoneNumberGrouping::NewLC( aUnformattedLength );
    CleanupStack::Pop();
    return self;
    }

CAknPhoneNumberGrouping::~CAknPhoneNumberGrouping()
    {
    delete iNumberGroupingEngine;
    }

EXPORT_C TInt CAknPhoneNumberGrouping::Set( const TDesC& aPhoneNumber )
    {
    return iNumberGroupingEngine->Set(aPhoneNumber);
    }

EXPORT_C const TDesC& CAknPhoneNumberGrouping::FormattedNumber() const
    {
    return iNumberGroupingEngine->FormattedNumber();
    }

EXPORT_C void CAknPhoneNumberGrouping::CopyFormattedNumber( TDes& aGroupedNumber ) const
    {
    aGroupedNumber.Copy( FormattedNumber() );
    // convert for digit type
    AknTextUtils::DisplayTextLanguageSpecificNumberConversion( aGroupedNumber );
    }

/**
* No exception handling needed in this case.  It will leave if there is a failure somewhere
*/
EXPORT_C HBufC* CAknPhoneNumberGrouping::CreateGroupedPhoneNumberL( const TDesC& aUngroupedNumber )
    {

    CAknPhoneNumberGrouping* self = CAknPhoneNumberGrouping::NewLC( aUngroupedNumber.Length() );
    self->Set( aUngroupedNumber );
    const TDesC& formatted = self->FormattedNumber();

    // Create the return buffer
    HBufC* newNumber = formatted.AllocL();

    // Make a writeable ptr for setting the HBufC content
    TPtr newNumberPtr = newNumber->Des();

    CleanupStack::PopAndDestroy(); // Destroy the number grouping engine

    // convert numbers
    AknTextUtils::DisplayTextLanguageSpecificNumberConversion( newNumberPtr );

    return newNumber; // Ownership is transferred to the caller
    }

EXPORT_C TInt CAknPhoneNumberGrouping::GroupPhoneNumber( 
    const TDesC& aUngroupedNumber, TDes& aGroupedNumber )
    {
    TInt extraSpace(0);
    TBool copied(EFalse);
    TRAPD( err, copied = DoFormatPhoneNumberL( aUngroupedNumber, aGroupedNumber, extraSpace ));

    if ( err != KErrNone )
        {
        // the method left so no copying was done, no copied value returned, and extraSpace not written to
        // Construct a sensible value for extraspace for no formatting case
        extraSpace = aGroupedNumber.MaxLength() - aUngroupedNumber.Length();
        }

    if ( !copied ) // either owing to leave or insufficient space
        {
        // pretend phone number grouping did not do anything
        aGroupedNumber.Copy( aUngroupedNumber ); // Panics if output descriptor is still not big enough
        }

    // convert numbers
    AknTextUtils::DisplayTextLanguageSpecificNumberConversion( aGroupedNumber );

    return extraSpace;
    }

EXPORT_C TInt CAknPhoneNumberGrouping::GroupPhoneNumber( TDes& aPhoneNumber )
    {
    return GroupPhoneNumber( aPhoneNumber, aPhoneNumber );
    }

CAknPhoneNumberGrouping::CAknPhoneNumberGrouping()
    {}

void CAknPhoneNumberGrouping::ConstructL( TInt aUnformattedLength )
    {
    // Always use unreversed buffers
    iNumberGroupingEngine = CPNGNumberGrouping::NewL( aUnformattedLength, EFalse );
    }

TBool CAknPhoneNumberGrouping::DoFormatPhoneNumberL( 
    const TDesC& aUngroupedNumber,
    TDes& aGroupedNumber,
    TInt& aExtraSpace)
    {
    TBool copied(EFalse);
    CAknPhoneNumberGrouping* self = CAknPhoneNumberGrouping::NewLC( aUngroupedNumber.Length() );
    self->Set( aUngroupedNumber );
    aExtraSpace = aGroupedNumber.MaxLength() - self->FormattedNumber().Length();
    if ( aExtraSpace >= 0 )
        {
        aGroupedNumber.Copy( self->FormattedNumber() );
        copied = ETrue;
        }
    CleanupStack::PopAndDestroy( self );
    return copied;
    }

// End of File  
