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

#include <coecntrl.h>
#include <eikedwin.h>
#include <frmtlay.h>

#include "smileymodel.h"
#include "smileyinforeader.h"
#include "smileydrawer.h"
#include "smileyimagedata.h"
#include "smileymanager.h"
#include "smileyiconrecord.h"
    
// ======== MEMBER FUNCTIONS ========
// ---------------------------------------------------------------------------
// CSmileyManager::NewL
// ---------------------------------------------------------------------------
//
CSmileyManager* CSmileyManager::NewL( CEikEdwin& aEdwin )
    {
    CSmileyManager* self = CSmileyManager::NewLC( aEdwin );
    CleanupStack::Pop( self );
    return self;
    }
    
// ---------------------------------------------------------------------------
// CSmileyManager::NewLC
// ---------------------------------------------------------------------------
//
CSmileyManager* CSmileyManager::NewLC( CEikEdwin& aEdwin )
    {
    CSmileyManager* self( new( ELeave ) CSmileyManager );
    CleanupStack::PushL( self );
    self->ConstructL( aEdwin );
    return self;
    }

// ---------------------------------------------------------------------------
// destructor
// ---------------------------------------------------------------------------
//
CSmileyManager::~CSmileyManager()
    {
    delete iDrawer;
    delete iReader;
    delete iModel;
    delete iIconRecord;
    }
    
// ---------------------------------------------------------------------------
// CSmileyManager::ConvertSmileyStrings
// ---------------------------------------------------------------------------
//
TBool CSmileyManager::ConvertTextForSmileyL( TInt aStart, TDes& aText, 
    TBool aStringToCodes )
    {
    TBool ret( EFalse );
    if ( aStringToCodes )
        {    
        ret = ConvertTextToCodesL( aText, aStart );
        }
    else if ( iIconRecord->HasSmileyIcon() )
        {
        ret = ConvertCodesToTextL( aText, aStart );        
        } 
    return ret;
    }

// ---------------------------------------------------------------------------
// CSmileyManager::ConvertCodesToTextL
// ---------------------------------------------------------------------------
//
TBool CSmileyManager::ConvertCodesToTextL( TDes& aText, TInt aStart )
    {
    TBool ret( EFalse );
    for ( TInt i( 0 ); i < aText.Length(); i++ )
        {
        if ( IsSmileyCode( aText[i] ) )
            {
            ret = ETrue;
            CSmileyIcon* icon( iIconRecord->SmileyIconAtPos( i + aStart ) );
            if ( icon )
                {
                const TDesC& smileyText( icon->SmileyString() );
                aText.Replace( i, smileyText.Length(), smileyText );
                }
            }
        }
    return ret;
    }

TBool CSmileyManager::ConvertTextToCodesL( TDes& aText, TInt aStart )
    {
    TBool ret( EFalse );
    TInt i( 0 );
    while ( i < aText.Length() )
        {
        TInt index( iModel->TryFindMatchNode( aText, i ) );
        if ( iModel->IsFinalNode( index ) )
            {
            TInt smileyLength( iModel->SmileyStringLength( index ) );
            TInt docPos( aStart + i );
            CSmileyIcon* icon( iIconRecord->SmileyIconAtPos( docPos ) );
            if ( !icon || ( icon && !icon->IsDisabled() ) )
                {
                if ( !icon )
                    {
                    TText smileyCode( iModel->SmileyCode( index ) );
                    AddSmileyToRecordL( aText.Mid( i, smileyLength ), docPos, 
                        smileyCode );
                    }
                iModel->ReplaceTextWithCodes( aText, i, index );
                ret = ETrue;
                }
            i += smileyLength;
            }
        else
            {
            i++;
            }
        }
    return ret;
    }

void CSmileyManager::AddSmileyToRecordL( const TDesC& aSmileyText, TInt aDocPos, 
    TText aCode )
    {
    CSmileyIcon* icon( new( ELeave ) CSmileyIcon( aCode ) );
    icon->SetDocPos( aDocPos );
    icon->SetSmileyString( aSmileyText );
    iIconRecord->InsertIconL( icon );
    }

// ---------------------------------------------------------------------------
// CSmileyManager::SetHighlightColor
// ---------------------------------------------------------------------------
//
void CSmileyManager::SetHighlightColor( TRgb aColor )
    {
    iDrawer->SetHighlightColor( aColor );
    }

// ---------------------------------------------------------------------------
// CSmileyManager::SetAnimationPlayTimes
// ---------------------------------------------------------------------------
//
void CSmileyManager::SetAnimationPlayTimes( TInt aPlayTimes )
    {
    iDrawer->SetPlayTimes( aPlayTimes );
    }

// ---------------------------------------------------------------------------
// CSmileyManager::DrawIcon
// ---------------------------------------------------------------------------
//
void CSmileyManager::DrawIconL( CBitmapContext& aGc, const TRect& aRect, 
    TInt aDocPos )
    {
    CSmileyIcon* icon( iIconRecord->SmileyIconAtPos( aDocPos ) );
    if ( icon && !icon->IsDisabled() )
        {
        icon->SetRect( aRect );
        CSmileyImageData* image( icon->ImageData() );
        if ( image && aRect.Size() != image->BitmapSize() )
            {
            image->SetBitmapSize( aRect.Size() );
            if ( icon->IsPlayFinished() )
                {
                icon->PlayOneTime();
                iDrawer->CreateImageL( image );
                }
            }
        else if ( !image )
            {
            iDrawer->CreateImageByIconL( icon );
            }
        iDrawer->DrawImageByIconL( aGc, icon );
        }
    }

// ---------------------------------------------------------------------------
// CSmileyManager::IsSmileyCode
// ---------------------------------------------------------------------------
//
TBool CSmileyManager::IsSmileyCode( TText aCode )
	{
	return ( aCode >= KSmileyCodeMin && aCode <= KSmileyCodeMax );
	}

// ---------------------------------------------------------------------------
// CSmileyManager::HandleDeleteL
// ---------------------------------------------------------------------------
//
void CSmileyManager::HandleDeleteL( TInt aStart, TInt aLength )
    { 
    iIconRecord->HandleTextDelete( aStart, aLength );
    }

// ---------------------------------------------------------------------------
// CSmileyManager::HandleInsertL
// ---------------------------------------------------------------------------
//
void CSmileyManager::HandleInsertL( TInt aStart, TInt aLength )
    {
    if ( aLength > 0 )
        { 
        iIconRecord->HandleTextInsert( aStart, aLength );
        }
    }

// ---------------------------------------------------------------------------
// CSmileyManager::HandleSetCursorL
// ---------------------------------------------------------------------------
//
void CSmileyManager::HandleSetCursor( TInt aOldCursor, TInt& aNewCursor )
    {
    CSmileyIcon* icon( iIconRecord->SmileyIconAtPos( aNewCursor ) );
    if ( icon && !icon->IsDisabled() && aNewCursor != icon->DocPos() )
        {
        if ( aOldCursor <= aNewCursor )
            {
            aNewCursor = icon->EndPos();
            }
        else
            {
            aNewCursor = icon->DocPos();
            }
        }
    }

// ---------------------------------------------------------------------------
// CSmileyManager::HandleSelectionL
// ---------------------------------------------------------------------------
//
void CSmileyManager::HandleSelection( TInt aStart, TInt aLength )
    {
    iIconRecord->CancelSelection();
    iIconRecord->SetSelection( aStart, aLength );
    iSelStart = aStart;
    iSelLength = aLength;
    }

// ---------------------------------------------------------------------------
// CSmileyManager::SmileyCodeByPos
// ---------------------------------------------------------------------------
//
TText CSmileyManager::SmileyCodeByPos( TInt aDocPos )
    {
    CSmileyIcon* icon( iIconRecord->SmileyIconAtPos( aDocPos ) );
    if ( icon )
        {
        return icon->Code();
        }
    return 0;
    }

// ---------------------------------------------------------------------------
// CSmileyManager::SetVisibleRange
// ---------------------------------------------------------------------------
//
void CSmileyManager::SetVisibleRange( TInt aDocPos, TInt aLength )
    {
    iDrawer->SetVisibleRange( aDocPos, aLength );
    }

// ---------------------------------------------------------------------------
// CSmileyManager::TextBlockLength
// ---------------------------------------------------------------------------
//
TInt CSmileyManager::SmileyLength( TInt aDocPos )
    {
    CSmileyIcon* icon( iIconRecord->SmileyIconAtPos( aDocPos ) );
    if ( icon )
        {
        return icon->SmileyLength();
        }
    return 0;
    }

// ---------------------------------------------------------------------------
// CSmileyManager::TotalTextLength
// ---------------------------------------------------------------------------
//
TBool CSmileyManager::HasSmileyIconsInText()
    {
    return iIconRecord->HasSmileyIcon();
    }

// ---------------------------------------------------------------------------
// CSmileyManager::RemoveIconsInRange
// ---------------------------------------------------------------------------
//
void CSmileyManager::RemoveIconsInRange( TInt aStart, TInt aLength )
    {
    iIconRecord->HandleTextDelete( aStart, aLength );
    }

// ---------------------------------------------------------------------------
// CSmileyManager::DisableSmileyIcon
// ---------------------------------------------------------------------------
//
void CSmileyManager::DisableSmileyIcon( TInt aDocPos )
    {
    CSmileyIcon* icon( iIconRecord->SmileyIconAtPos( aDocPos ) );
    if ( icon )
        {
        icon->DisableIcon();
        }
    }

// ---------------------------------------------------------------------------
// CSmileyManager::IsDisabledSmileyIcon
// ---------------------------------------------------------------------------
//
TBool CSmileyManager::IsDisabledSmileyIcon( TInt aDocPos )
    {
    CSmileyIcon* icon( iIconRecord->SmileyIconAtPos( aDocPos ) );
    if ( icon )
        {
        return icon->IsDisabled();
        }
    return EFalse;
    }

// ================= Private member functions ======================
// ---------------------------------------------------------------------------
// CSmileyManager::CSmileyManager
// c++ default constructor
// ---------------------------------------------------------------------------
//
CSmileyManager::CSmileyManager()
    {
    }

// ---------------------------------------------------------------------------
// second phase constructor
// ---------------------------------------------------------------------------
//
void CSmileyManager::ConstructL( CEikEdwin& aEdwin )
    {
    iIconRecord = new( ELeave ) CSmileyIconRecord;
    iModel = new( ELeave ) CSmileyModel;
    iReader = new( ELeave ) CSmileyInfoReader( *iModel );
    iDrawer = new( ELeave ) CSmileyDrawer( *iModel, aEdwin );
    iReader->LoadSmileysFromResourceL();    
    }





