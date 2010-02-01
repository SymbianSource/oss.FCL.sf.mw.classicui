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

#include "AknInlineText.h"

// LOCAL FUNCTIONS

GLDEF_C void Panic(TAknInlineTextFormattingPanic aPanic)
	{
    User::Panic(KAknInlineTextFormatting, aPanic);
	}

// MODULE TEMPLATES

// MODULE DATA STRUCTURES

// ============================ MEMBER FUNCTIONS ===============================

////////////////////////////////////////////////////////////////////////////////
//
// CAknPositionedInlineText
//
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// 2 stage constructor
// -----------------------------------------------------------------------------

CAknPositionedInlineText* CAknPositionedInlineText::NewL( const TTmDocPos& aPosition, const TDesC& aInlineText )
    {
    CAknPositionedInlineText* self = 
        new (ELeave) CAknPositionedInlineText( aPosition ); // Only partially constructed at this point
    CleanupStack::PushL( self );
    self->ConstructL( aInlineText );
    CleanupStack::Pop();
    return self;
    }

CAknPositionedInlineText::~CAknPositionedInlineText()
    {
    delete iText;
    }

const TTmDocPos& CAknPositionedInlineText::DocPos() const
    {
    return iDocPos;
    }

const TDesC& CAknPositionedInlineText::InlineText() const
    {
    return *iText;
    }

CAknPositionedInlineText::CAknPositionedInlineText( const TTmDocPos& aPosition )
    : iDocPos(aPosition)
    {
    }

void CAknPositionedInlineText::ConstructL( const TDesC& aInlineText )
    {
    iText = aInlineText.AllocL();
    }
////////////////////////////////////////////////////////////////////////////////
//
// CAknInlineTextStore
//
////////////////////////////////////////////////////////////////////////////////

const TInt KAknInlineTextStoreGranularity(2);

CAknInlineTextStore* CAknInlineTextStore::NewL()
    {
    return new (ELeave) CAknInlineTextStore();
    }
       
CAknInlineTextStore::~CAknInlineTextStore()
    {
    ResetAndDestroy();
    }

void CAknInlineTextStore::Clear()
    {
    ResetAndDestroy();
    }

void CAknInlineTextStore::ClearRange( const TTmDocPos& aStart, const TTmDocPos& aEnd )
    {
    TInt nToDelete(0);
    TInt firstToDelete(0);
    for (TInt index = Count() - 1; index >=0 ; --index)
	    {
        CAknPositionedInlineText* inlineText = At(index);
        const TTmDocPos& docPos = inlineText->DocPos();
		if ( aStart <= docPos && docPos <= aEnd )
            {
            delete ( inlineText );
            firstToDelete = index; // running lowest index to delete
            nToDelete++;
            }
		}
    // Perform deletions from array in one go as this is an expensive operation
	if ( nToDelete > 0 )
        Delete( firstToDelete, nToDelete );
    }

void CAknInlineTextStore::InsertInlineTextL( CAknPositionedInlineText* aInlineText )
    {
    TInt insertPosition(0);
    for (TInt ii = Count()-1; ii >= 0; --ii)
		{
		if ( At(ii)->DocPos() <= aInlineText->DocPos() )
            {
            insertPosition = ii+1;
            break;
            }
		}

    InsertL( insertPosition, aInlineText );
    }

const TTmDocPos* CAknInlineTextStore::NextInlineTextDocPos( const TTmDocPos& aDocPos ) const
    {
    const TTmDocPos* retPtr = NULL;
    TInt index = NextIndexStartingAtDocPos( aDocPos );
    if ( index >=0 )
        retPtr = &(At( index )->DocPos());
    return retPtr;
    }

TInt CAknInlineTextStore::NextIndexStartingAtDocPos( const TTmDocPos& aDocPos ) const
    {

    TInt count = Count();
    if ( count == 0 )
        return -1;
      
    if ( At(count-1)->DocPos() < aDocPos  ) // even biggest is at lower docpos
        return -1;

    TInt index;
    for (index = 0; index < count ; ++index)
	    {
		if ( At(index)->DocPos() >= aDocPos  )
            {
            break;
            }
		}

    __ASSERT_DEBUG( index < count , Panic( EAknInlineTextFormattingStoreCorrupted) );

    return index;
    }

TInt CAknInlineTextStore::IndexFromDocPos( const TTmDocPos& aDocPos ) const
    {
    TInt matchedIndex = -1;
    TInt indexFound = NextIndexStartingAtDocPos( aDocPos );
    if (indexFound != -1 &&  At(indexFound)->DocPos() == aDocPos )
        matchedIndex = indexFound;
    return matchedIndex;
    }

CAknInlineTextStore::CAknInlineTextStore() : CArrayPtrFlat<CAknPositionedInlineText>( KAknInlineTextStoreGranularity )
    {}
 

////////////////////////////////////////////////////////////////////////////////
//
// CAknInlineTextSource
//
////////////////////////////////////////////////////////////////////////////////

CAknInlineTextSource::CAknInlineTextSource()
    {}

void CAknInlineTextSource::ConstructL()
    {
    iInlineTextStore = CAknInlineTextStore::NewL();
    }

CAknInlineTextSource::~CAknInlineTextSource()
    {
    delete iInlineTextStore;
    }

TInt CAknInlineTextSource::GetNextInlineTextPosition(
    const TTmDocPos& aFrom, 
    TInt aMaxLength, 
    TTmDocPos& aNext)
    {

    TInt errReturn = KErrNotFound; // Default is that there is nothing found

    const TTmDocPos* nextPos = iInlineTextStore->NextInlineTextDocPos( aFrom );
    // This returns NULL if nothing found   
    if ( nextPos )
        {

        if ( // pos must be strictly less than aFrom + aMaxLength, but may be 1 further if trailing
            (nextPos->iPos < (aFrom.iPos + aMaxLength) )
            || 
            (!nextPos->iLeadingEdge && (nextPos->iPos <= (aFrom.iPos + aMaxLength)) ) 
           )
            {
            aNext = *nextPos; // Copies the structure
            errReturn = KErrNone; // Report valid data
            }
        }
        
    return errReturn;
    }

TPtrC CAknInlineTextSource::GetInlineText(const TTmDocPos& aPos)
    {
    TInt index = iInlineTextStore->IndexFromDocPos( aPos );
    if ( index >= 0 )
        return iInlineTextStore->At( index )->InlineText();
    else
        {
        __ASSERT_DEBUG( EFalse, Panic(EAknInlineTextFormattingBadInlineTextFetch) );
        return KNullDesC();
        }
    }

TBool CAknInlineTextSource::HasInlineTextAt(const TTmDocPos& aPos, TPtrC& aPtrFound) const
    {
    TBool retVal( EFalse );
    TInt index = iInlineTextStore->IndexFromDocPos( aPos );
    if ( index != -1 )
        {
        retVal = ETrue;
        aPtrFound.Set(iInlineTextStore->At( index )->InlineText()) ;
        }
    return retVal;
    }

CAknInlineTextStore* CAknInlineTextSource::InlineTextStore() const
    {
    return iInlineTextStore;
    }

/**
* Empty implementation as all "when to format policy" is determined by sub-classes.  However, 
* this class implements so that sub-classes only have to implement what they need.
*/
void CAknInlineTextSource::CheckFormattingL(const TTmDocPos& /*aFrom*/, const TTmDocPos& /*aTo*/ )
    {}

/**
* Empty implementation as all upon-edit policy is determined by sub-classes.  However, 
* this class implements so that sub-classes only have to implement what they need.
*/
void CAknInlineTextSource::EditObserver( TInt /*aStart*/, TInt /*aExtent*/ ) 
    {}



//  End of File  
