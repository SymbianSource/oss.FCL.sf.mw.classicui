/*
* Copyright (c) 2002-2008 Nokia Corporation and/or its subsidiary(-ies).
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
*/

#include "AknPhedModel.h"
#include "NumberGrouping.h"

#include <e32svr.h>
#include <AknUtils.h>

const TInt KExtraSpaceForGroupedNumber = 6;

//
// CAknPhedBuffer
//
CAknPhedScratchBuffer::CAknPhedScratchBuffer() :iPtr(0,0)
	{
	}

CAknPhedScratchBuffer::~CAknPhedScratchBuffer()
	{
	delete iBuf;
	}

void CAknPhedScratchBuffer::ConstructL(TInt aMaxLen)
	{
	iBuf = HBufC::NewL(aMaxLen + KExtraSpaceForGroupedNumber);
	iPtr.Set(iBuf->Des());
	}



//
// CAknPhedModel
//
CAknPhedModel* CAknPhedModel::NewL( TInt aMaxLen )
    {
    CAknPhedModel* self = new( ELeave ) CAknPhedModel;
    CleanupStack::PushL( self );
    self->ConstructL( aMaxLen );
    CleanupStack::Pop( self );
    return self;
    }

CAknPhedModel::~CAknPhedModel()
    {
    delete iNumberGroupingBuffer;
	delete iBuf;
    }

void CAknPhedModel::SetText( const TDesC& aText )
    {
    StartEvent();

    // delete all existing text
    TInt len = iRealLength;
    DeleteLeft( len, len );

    // insert the new text
    SetRealCursorPosition( 0 );
    Insert( aText );

    ReportEvent(MPhedDataObserver::TAknPhedDataEvent(
                MPhedDataObserver::TAknPhedDataEvent::EText, 
                0,
                iNumberGroupingBuffer->Length() ) );
    }

void CAknPhedModel::Insert( TText aChar )
    {
    StartEvent();
    ClearAnySelection();

    TInt nOldCursorPos = CursorPosition();

    // buffer full rule: Text overflows off the left hand side of the buffer
    TInt maxLength = MaxDisplayLength();
    if ( iRealLength == maxLength )
        {
        if (nOldCursorPos == 0)
            {
            ReportEvent( MPhedDataObserver::TAknPhedDataEvent() );
            return;
            }
        else
            {
            DeleteLeft( 1 );
            SetRealCursorPosition( iRealCursor - 1 );
            }
        }
        
    iNumberGroupingBuffer->Insert( iRealCursor, aChar );
    ++iRealLength;
    iNumberGroupingBuffer->FormattedNumber();
    SetRealCursorPosition( iRealCursor + 1 );
    if ( Length() > maxLength )
        {
        DeleteLeft( 1 );
        SetRealCursorPosition( iRealCursor - 1 );
        ReportEvent(MPhedDataObserver::TAknPhedDataEvent(
        MPhedDataObserver::TAknPhedDataEvent::EText, 
        CursorPosition(),                                  
        CursorPosition() ) );
        }
    else 
        {
        ReportEvent( MPhedDataObserver::TAknPhedDataEvent(
                MPhedDataObserver::TAknPhedDataEvent::EText, 
                nOldCursorPos,                                  
                CursorPosition() ) );
        }                
    
    }

void CAknPhedModel::DeleteLeft()
    {
    if( !ClearAnySelection() && iRealCursor > 0 )
        {
        StartEvent();

        TInt nOldCursorPos = CursorPosition();

        DeleteLeft(iRealCursor);
        
        SetRealCursorPosition( iRealCursor - 1 );
        ReportEvent( MPhedDataObserver::TAknPhedDataEvent(
                MPhedDataObserver::TAknPhedDataEvent::EText, 
                CursorPosition(),                               
                CursorPosition() ) );
        }
        
    }

void CAknPhedModel::DeleteLeft( TInt aIndex, TInt aCount )
    {
    aIndex--;   // delete char to the left

    for ( TInt ii = 0; ii < aCount; ++ii )
        {
        iNumberGroupingBuffer->Delete( aIndex - ii );
        --iRealLength;
        }
    }   

TPtrC CAknPhedModel::Selection() const
    { 
    TInt nFrom = LeftMark();
    TInt nTo = nFrom + SelectionWidth();

    if(!nTo) nTo = iRealLength;
    
    return iNumberGroupingBuffer->Selection( nFrom, nTo );
    }

void CAknPhedModel::Cut( TDes& aCutText )
    {
    aCutText = Selection();
    ClearAnySelection();
    }

void CAknPhedModel::Copy( TDes& aCopiedText ) const
    {
    aCopiedText = Selection();
    }

void CAknPhedModel::Paste( const TDesC& aText )
    {
    ClearAnySelection();
    Insert( aText );
    }

TInt CAknPhedModel::Language()  const   
    {
    TInt language = iNumberGroupingBuffer->Language();
    language &= KAknLanguageMask;  
    TInt forceLanguage = iNumberGroupingBuffer->iForceLanguage;
    forceLanguage &= KAknLanguageMask; 
    
    return ( ELangAmerican == language || 
             ELangAmerican == forceLanguage)
            ? ELangAmerican : ELangTest;
    }

TInt CAknPhedModel::Compensate( TInt aRealPosition ) const
{
    TInt nCompensated = 0;
    if ( Language() )
    	{
    if( iCursorDirection == EUp )
        nCompensated = aRealPosition + Spaces( 0, aRealPosition );
    else if( iCursorDirection == EDown )
        nCompensated = aRealPosition + Spaces( 0, aRealPosition + 1 );    
    	}
    else
    	{
    	nCompensated = aRealPosition;
    	}
    return nCompensated;
}

TInt CAknPhedModel::Uncompensate( TInt aCompensatedPosition ) const
{
    TInt nUncompensated = 0;
    if ( Language() )
    	{
    if( iCursorDirection == EUp )
        nUncompensated = aCompensatedPosition - Spaces( aCompensatedPosition - 1 );
    else if( iCursorDirection == EDown )
        nUncompensated = aCompensatedPosition - Spaces( aCompensatedPosition );    
    	}
    else
    	{
    	nUncompensated = aCompensatedPosition;
    	}
    return nUncompensated;
}

TInt CAknPhedModel::SetRealCursorPosition( TInt aCursorPos )
    {
    StartEvent();
    if ( SelectionExists() )
        {
        // selection is lost, so report a selection change event
        StartEvent();
        ReportEvent( MPhedDataObserver::TAknPhedDataEvent(
                     MPhedDataObserver::TAknPhedDataEvent::ESelection ) );
        }

    iRealCursor = iRealAnchor = aCursorPos;

    ReportEvent( MPhedDataObserver::TAknPhedDataEvent(
                 MPhedDataObserver::TAknPhedDataEvent::ECursor ) );
    
    return iRealCursor;
    }

TInt CAknPhedModel::SetCompensatedCursorPosition( TInt aCursorPos )
    {
    StartEvent();
    if ( SelectionExists() )
        {
        // selection is lost, so report a selection change event
        StartEvent();
        ReportEvent( MPhedDataObserver::TAknPhedDataEvent(
                     MPhedDataObserver::TAknPhedDataEvent::ESelection ) );
        }

    iRealCursor = iRealAnchor = Uncompensate( aCursorPos );

    ReportEvent( MPhedDataObserver::TAknPhedDataEvent(
                 MPhedDataObserver::TAknPhedDataEvent::ECursor ) );
    
    return iRealCursor;
    }

TInt CAknPhedModel::SetAnchorPosition(TInt aAnchorPos)
    { 
    StartEvent();

    iRealAnchor = aAnchorPos;

    ReportEvent( MPhedDataObserver::TAknPhedDataEvent(
                 MPhedDataObserver::TAknPhedDataEvent::ESelection ) );

    return iRealAnchor;
    }


TInt CAknPhedModel::CursorLeft()
    {
     // cursor rule: cursor left -> left of selection or left with wrap to RHS
    if ( SelectionExists() )
        return SetRealCursorPosition( LeftMark() );
    else if (iRealCursor > 0)
        {
        return SetRealCursorPosition( iRealCursor - 1 );
        }
    else
        return SetRealCursorPosition( iRealLength );
    }

TInt CAknPhedModel::CursorRight()
    {
    // cursor rule: cursor right -> right of selection or right with wrap to LHS
    if ( SelectionExists() )
        return SetRealCursorPosition( RightMark() );
    else if ( iRealCursor < iRealLength )
        return SetRealCursorPosition( iRealCursor + 1 );
    else
        return SetRealCursorPosition( 0 );
    }

void CAknPhedModel::ConstructL( TInt aMaxLen )
    {
    iBuf = new(ELeave) CAknPhedScratchBuffer;
   	iBuf->ConstructL(aMaxLen);

    // Construct the number grouping engine with the reversed buffer support turned on
    iNumberGroupingBuffer = CPNGNumberGrouping::NewL( aMaxLen, ETrue );
    
    iSelection.Set( KNullDesC );
    iCursorDirection = EUp;

    iCount = 0;
    }

void CAknPhedModel::Insert( const TDesC& aText )
    {
    StartEvent();
    TInt len = aText.Length();
    for ( TInt ii=0; ii<len; ii++ )
        {
        Insert( aText[ii] );
        }

    if ( len && iRealCursor > 0 )
        {
        // report a text event if anything actually got inserted
        ReportEvent( MPhedDataObserver::TAknPhedDataEvent(
                     MPhedDataObserver::TAknPhedDataEvent::EText, 
                     Max( 0, CursorPosition() - len ),             
                     CursorPosition() ) );         
        }
    else
        {
        // otherwise report nothing
        ReportEvent( MPhedDataObserver::TAknPhedDataEvent() );
        }
    }

TBool CAknPhedModel::ClearAnySelection()
    {
    if ( SelectionExists() )
        {
        StartEvent();
        TInt left = LeftMark(); 
        TInt right = RightMark();

        DeleteLeft( right, SelectionWidth() );
        iNumberGroupingBuffer->FormattedNumber();
        
        SetRealCursorPosition( left );
                
        ReportEvent( MPhedDataObserver::TAknPhedDataEvent(
                     MPhedDataObserver::TAknPhedDataEvent::EText, 
                     CursorPosition(), 
                     left ) );
        
        return ETrue;
        }
    return EFalse;
    }

void CAknPhedModel::StartEvent()
    {
    // Events can be nested, so that one combined event is reported for each external operation
    if (iEventDepth == 0)
        iEvent.Reset();
    
    iEventDepth++;
    }

void CAknPhedModel::ReportEvent( const MPhedDataObserver::TAknPhedDataEvent& aEvent )
    {
    // Combine this event with any other nested event and report the lot if the
    // nesting is finished
    iEvent.Add( aEvent ); 
    iEventDepth--;
    
    if ( iEventDepth == 0 && iObserver && 
         ( iEvent.TextChanged() || iEvent.CursorChanged() || iEvent.SelectionChanged() ) )
        {
        // safety subtlty: event is reported as the very last thing in case the caller
        // does something stupid, like leave.
        iObserver->HandlePhedDataEvent( iEvent, this );
        }
    }

void CAknPhedModel::SelectMove( TInt aInc )
    {
    // selection rule: selection cursor wraps LHS <-> RHS
    iRealCursor = iRealCursor + aInc;

    if ( iRealCursor < 0 )
        iRealCursor = iRealLength;
    else if ( iRealCursor > iRealLength )
        iRealCursor =  0;
    
    StartEvent();
    ReportEvent( MPhedDataObserver::TAknPhedDataEvent(
                 MPhedDataObserver::TAknPhedDataEvent::ESelection | 
                 MPhedDataObserver::TAknPhedDataEvent::ECursor ) );
    }

TBool CAknPhedModel::CursorPositionIsSpace()
{
    TInt nCursorPosition = CursorPosition();

    if( nCursorPosition != Length() )
        return iNumberGroupingBuffer->IsSpace( nCursorPosition );
    else
        return EFalse;
}

TInt CAknPhedModel::Spaces( TInt aFromPos, TInt aToPos ) const
{
    TInt spacesCount = 0;
    TInt toPos = aToPos;
    
    for( TInt i = aFromPos; i <= toPos; ++i )
    {
        if( iNumberGroupingBuffer->IsSpace( i ) )
        {
            ++spacesCount;
            ++toPos;            
        }
    }   
    
    return spacesCount;
}

TInt CAknPhedModel::Spaces( TInt aToPos ) const
{
    TInt spacesCount = 0;
    TInt toPos = aToPos;
    
    for( TInt i = 0; i <= toPos; ++i )
    {
        if( iNumberGroupingBuffer->IsSpace( i ) )
        {
            ++spacesCount;            
        }
    }   
    
    return spacesCount;
}
//
// MPhedDataObserver::TAknPhedDataEvent
//
void MPhedDataObserver::TAknPhedDataEvent::Add( const TAknPhedDataEvent& aEvent )
    {
    if ( aEvent.TextChanged() )
        {
        if ( TextChanged() )
            {
            if ( iStart > aEvent.iStart )
                iStart = aEvent.iStart;
            if ( iEnd < aEvent.iEnd )
                iEnd = aEvent.iEnd;
            }
        else
            {
            iStart = aEvent.iStart;
            iEnd = aEvent.iEnd;
            }
        }

    iType |= aEvent.iType;
    }


//
// TAknPhedDataMirror
//
void TAknPhedDataMirror::HandlePhedDataEvent( const TAknPhedDataEvent& aEvent, 
                                              CAknPhedModel* aPhedData )
    {
    // The mirror reverses event positioning from the model
    if ( iObserver )
        {
        TInt start;
        TInt end;
        aEvent.TextChangeRange( start, end );
        TAknPhedDataEvent event( aEvent.Type(), Mirror( end ), Mirror( start ) );
        iObserver->HandlePhedDataEvent( event, aPhedData );
        }
    }

TInt TAknPhedDataMirror::Compensate( TInt aMirrorPosition ) const
    { 
    TInt Compensated ;
    if ( iPhed->Language() )
    	{
        Compensated = aMirrorPosition - iPhed->Spaces( 0, iPhed->iRealCursor );
    	}
    else
    	{
    	Compensated = aMirrorPosition;
    	}
    return Compensated; 
    }

// End of File

