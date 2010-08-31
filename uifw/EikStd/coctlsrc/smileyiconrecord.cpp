/*
* Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  smiely engine class
*
*/

#include "smileymanager.h"
#include "smileyiconrecord.h"
#include "smileyimagedata.h"

// ======== MEMBER FUNCTIONS ========
// ---------------------------------------------------------------------------
// CSmileyIcon::CSmileyIcon
// ---------------------------------------------------------------------------
//
CSmileyIcon::CSmileyIcon( TText aCode ) : iCode( aCode )
    {
    }

// ---------------------------------------------------------------------------
// CSmileyIcon::~CSmileyIcon
// ---------------------------------------------------------------------------
//
CSmileyIcon::~CSmileyIcon()
    {
    if ( iImage )
        {
        iImage->RemoveFromRefArray( this );
        }
    }

// ---------------------------------------------------------------------------
// CSmileyIcon::SetSmileyString
// ---------------------------------------------------------------------------
//
void CSmileyIcon::SetSmileyString( const TDesC& aString )
    { 
    TInt strLength( aString.Length() );
    if ( strLength > CSmileyManager::KMaxLength )
        {
        strLength = CSmileyManager::KMaxLength;
        }
    iStr.Copy( aString.Mid( 0, strLength ) ); 
    };

// ======== MEMBER FUNCTIONS ========
// ---------------------------------------------------------------------------
// CSmileyIconRecord::CSmileyIconRecord
// ---------------------------------------------------------------------------
//
CSmileyIconRecord::CSmileyIconRecord()
    {
    }

// ---------------------------------------------------------------------------
// CSmileyIconRecord::~CSmileyIconRecord
// ---------------------------------------------------------------------------
//
CSmileyIconRecord::~CSmileyIconRecord()
    {
    iIconArray.ResetAndDestroy();
    iIconArray.Close();
    }

// ---------------------------------------------------------------------------
// CSmileyIconRecord::InsertIcon
// ---------------------------------------------------------------------------
//
void CSmileyIconRecord::InsertIconL( CSmileyIcon* aIcon )
    {
    if ( !aIcon )
        {
        return;
        }
    TInt index( 0 );
    for ( ; index < iIconArray.Count(); index++ )
        {
        if ( iIconArray[index]->DocPos() >= aIcon->DocPos() )
            {
            break;
            }
        }
    InsertIconAtL( aIcon, index );
    }

// ---------------------------------------------------------------------------
// CSmileyIconRecord::HandleTextDelete
// ---------------------------------------------------------------------------
//
void CSmileyIconRecord::HandleTextDelete( TInt aStart, TInt aLength )
    {
    DeleteIconsIn( aStart, aLength );
    TInt index( FirstIndexAfter( aStart ) );
    for ( ; index != KErrNotFound && index < iIconArray.Count(); index++ )
        {
        TInt newPos( iIconArray[index]->DocPos() - aLength );
        iIconArray[index]->SetDocPos( newPos );
        }
    }

// ---------------------------------------------------------------------------
// CSmileyIconRecord::HandleTextDelete
// ---------------------------------------------------------------------------
//
void CSmileyIconRecord::HandleTextInsert( TInt aStart, TInt aLength )
    {
    TInt index( FirstIndexAfter( aStart ) );
    for ( ; index != KErrNotFound && index < iIconArray.Count(); index++ )
        {
        TInt newPos( iIconArray[index]->DocPos() + aLength );
        iIconArray[index]->SetDocPos( newPos );
        }
    }

// ---------------------------------------------------------------------------
// CSmileyIconRecord::SmileyRange
// ---------------------------------------------------------------------------
//
CSmileyIcon* CSmileyIconRecord::SmileyIconAtPos( TInt aDocPos )
    {
    TInt count( iIconArray.Count() );
    for ( TInt i( 0 ); i < iIconArray.Count(); i++ )
        {
        CSmileyIcon* icon( iIconArray[i] );
        if ( iIconArray[i]->DocPos() <= aDocPos && 
            iIconArray[i]->DocPos() + iIconArray[i]->SmileyLength() > aDocPos )
            {
            return iIconArray[i];
            }
        }
    return NULL;
    }

// ---------------------------------------------------------------------------
// CSmileyIconRecord::SmileyRange
// ---------------------------------------------------------------------------
//
void CSmileyIconRecord::CancelSelection()
    {
    for ( TInt i( 0 ); i < iIconArray.Count(); i++ )
        {
        iIconArray[i]->EnableHighlight( EFalse );
        }
    }

// ---------------------------------------------------------------------------
// CSmileyIconRecord::SmileyRange
// ---------------------------------------------------------------------------
//
void CSmileyIconRecord::SetSelection( TInt aStart, TInt aLength )
    {
    TInt firstIndex( FirstIndexIn( aStart, aLength ) );
    TInt lastIndex( LastIndexIn( aStart, aLength, firstIndex ) );
    for ( TInt i( firstIndex ); i != KErrNotFound && i <= lastIndex; i++ )
        {
        iIconArray[i]->EnableHighlight( ETrue );
        }
    }

// ---------------------------------------------------------------------------
// CSmileyIconRecord::HasSmileyIcon
// ---------------------------------------------------------------------------
//
TBool CSmileyIconRecord::HasSmileyIcon()
    {
    return ( iIconArray.Count() > 0 );
    }

//-------------------Private member function----------------------------------
// ---------------------------------------------------------------------------
// CSmileyIconRecord::InsertIconAtL
// ---------------------------------------------------------------------------
//
void CSmileyIconRecord::InsertIconAtL( CSmileyIcon* aIcon, TInt aIndex )
    {
    TInt index( aIndex < 0 ? 0 : aIndex );
    if ( index >= iIconArray.Count() )
        {
        iIconArray.AppendL( aIcon );
        }
    else
        {
        iIconArray.InsertL( aIcon, index );
        }
    }

// ---------------------------------------------------------------------------
// CSmileyIconRecord::DeleteIconsIn
// ---------------------------------------------------------------------------
//
void CSmileyIconRecord::DeleteIconsIn( TInt aStart, TInt aLength )
    {
    TInt startIndex( FirstIndexIn( aStart, aLength ) );
    TInt endIndex( LastIndexIn( aStart, aLength, startIndex ) );
    TInt count( endIndex - startIndex );
    for ( TInt i( 0 ); startIndex != KErrNotFound && i <= count; i++ )
        {
        CSmileyIcon* icon( iIconArray[startIndex] );
        iIconArray.Remove( startIndex );
        delete icon;
        }
    }

// ---------------------------------------------------------------------------
// CSmileyIconRecord::InsertIconAtL
// ---------------------------------------------------------------------------
//
TInt CSmileyIconRecord::FirstIndexAfter( TInt aDocPos, TInt aSearchStart )
    {
    TInt i = ( aSearchStart < 0 || aSearchStart >= iIconArray.Count() ? 0 : 
        aSearchStart );
    for ( ; i < iIconArray.Count(); i++ )
        {
        if ( iIconArray[i]->DocPos() >= aDocPos )
            {
            return i;            
            }
        }
    return KErrNotFound;
    }

// ---------------------------------------------------------------------------
// CSmileyIconRecord::InsertIconAtL
// ---------------------------------------------------------------------------
//
TInt CSmileyIconRecord::FirstIndexIn( TInt aStart, TInt aLength )
    {
    for ( TInt i( 0 ); i < iIconArray.Count(); i++ )
        {
        if ( iIconArray[i]->DocPos() < aStart + aLength && 
            iIconArray[i]->EndPos() > aStart )
            {
            return i;
            }
        }
    return KErrNotFound;
    }

// ---------------------------------------------------------------------------
// CSmileyIconRecord::InsertIconAtL
// ---------------------------------------------------------------------------
//
TInt CSmileyIconRecord::LastIndexIn( TInt aStart, TInt aLength, 
    TInt aFirstIndex )
    {
    TInt index( FirstIndexAfter( aStart + aLength, aFirstIndex ) );
    if ( index == KErrNotFound )
        {
        return iIconArray.Count() > 0 ? iIconArray.Count() - 1 : index;
        }
    if ( index > 0 )
        {
        return index - 1;
        }
    return aFirstIndex;
    }



