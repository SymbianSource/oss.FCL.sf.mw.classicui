/*
* Copyright (c) 2002-2006 Nokia Corporation and/or its subsidiary(-ies).
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


// INCLUDE FILES
#include    <txtetext.h> // for CPlainText
#include    "finditemcontroller.h"
#include    <finditemdialog.h>
#include    <txtfrmat.h> // for TCharFormatMask
#include    <txtrich.h> // for CRichText
#include    <centralrepository.h>
#include    <CommonUiInternalCRKeys.h>

const TInt KFindItemMinDigitsToFind = 5;

// ================= MEMBER FUNCTIONS =======================

// -----------------------------------------------------------------------------
// CFindItemController::TappedItemL
//  Moves the selection to tapped item
// -----------------------------------------------------------------------------
//
TBool CFindItemController::TappedItemL( const TInt aPosition )
    {
    TBool tappedItem = EFalse;

    if( aPosition < 0 || aPosition >= ItemCount() )
        {
        return tappedItem; // Error: invalid position.
        }

    // Change selection.
    TInt steps = aPosition - iEngine->Position();
    TInt i = steps;
    do
        {
        tappedItem = ETrue;
        if ( steps < 0 ) // Backward
            {
            iEngine->PrevItem( iItem );
            i++;
            }
        else if ( steps > 0 ) // Forward
            {
            iEngine->NextItem( iItem );
            i--;
            }
        else
            {
            break;
            }
        }
     while ( i != 0 );

     iDialog->SelectionChangedL( iItem, ETrue );

     return tappedItem;
    }

// -----------------------------------------------------------------------------
// CFindItemController::NextItemL()
//  Moves the selection to next item
// -----------------------------------------------------------------------------
//
TBool CFindItemController::NextItemL()
    {
    TBool notLastItem = iEngine->NextItem( iItem );
    if ( notLastItem )
        {
        iDialog->SelectionChangedL( iItem, ETrue );
        }
    return notLastItem;
    }

// -----------------------------------------------------------------------------
// CFindItemController::PrevItemL
//  Moves the selections to previous item
// -----------------------------------------------------------------------------
//
TBool CFindItemController::PrevItemL()
    {
    TBool notFirstItem = iEngine->PrevItem( iItem );
    if ( notFirstItem )
        {
        iDialog->SelectionChangedL( iItem, EFalse );
        }
    return notFirstItem;
    }

// -----------------------------------------------------------------------------
// CFindItemController::MoveUpL
//  Move into previous row where found item is
//  (and select first item in that row)
// -----------------------------------------------------------------------------
//
void CFindItemController::MoveUpL()
    {
    if ( FirstItem() )
        {
        return;
        }

    TInt engPos = iEngine->Position();

    const CArrayFixFlat<CFindItemEngine::SFoundItem>*
        itemArray = iEngine->ItemArray();

    // Check that if at the first line MoveUpL does nothing
    if ( iDialog->AtSameLine(
            itemArray->At( iEngine->Position() ).iStartPos,
            itemArray->At( 0 ).iStartPos ) )
        {
        return;
        }

    // Go back until the prev item is not at the same line
    TBool firstItem;
    do
        {
        firstItem = iEngine->PrevItem( iItem );
        }
    while ( firstItem && iDialog->AtSameLine(
                itemArray->At( iEngine->Position() ).iStartPos,
                itemArray->At( engPos ).iStartPos ) );

    // Go to first item in the row
    while ( !FirstItem() &&
        iDialog->AtSameLine(
            itemArray->At( iEngine->Position() - 1 ).iStartPos,
            itemArray->At( iEngine->Position() ).iStartPos ) )
        {
        iEngine->PrevItem( iItem );
        }

    iDialog->SelectionChangedL( iItem, EFalse );
    }

// -----------------------------------------------------------------------------
// CFindItemController::MoveDownL
//  Move into next row where found item is
//  (and select first item in that row)
// -----------------------------------------------------------------------------
//
void CFindItemController::MoveDownL()
    {
    // Return if there's no more items.
    if ( LastItem() )
        {
        return;
        }

    TInt engPos = iEngine->Position();

    const CArrayFixFlat<CFindItemEngine::SFoundItem>*
        itemArray = iEngine->ItemArray();

    // If the next item is not in the same line -> NextItem()
    if ( !( iDialog->AtSameLine(
            itemArray->At( engPos ).iStartPos,
            itemArray->At( engPos + 1 ).iStartPos ) ) )
        {
        NextItemL();
        return;
        }

    // Check that if at the last line MoveDownL does nothing
    if ( iDialog->AtSameLine(
            itemArray->At( engPos ).iStartPos,
            itemArray->At( itemArray->Count() - 1 ).iStartPos ) )
        {
        return;
        }


    // Go forward until the next item is not at the same line
    TBool lastItem;
    do
        {
        lastItem = iEngine->NextItem( iItem );
        }
    while ( lastItem &&
        iDialog->AtSameLine(
            itemArray->At( engPos ).iStartPos +
                itemArray->At( engPos ).iLength,
            itemArray->At( iEngine->Position() ).iStartPos ) );

    iDialog->SelectionChangedL( iItem, ETrue );
    }

// -----------------------------------------------------------------------------
// CFindItemController::MarkFoundItemsL
//  Marks found items: Underlines all found strings and updates the selection
// -----------------------------------------------------------------------------
//
void CFindItemController::MarkFoundItemsL()
    {
    const CArrayFixFlat<CFindItemEngine::SFoundItem>*
        itemArray = iEngine->ItemArray();

    iEngine->Item( iItem );

    // Underline all found items
    TCharFormatMask charFormatMask;
    TCharFormat charFormat;

    charFormatMask.SetAttrib( EAttFontUnderline );
    // interested in underline
    charFormat.iFontPresentation.iUnderline = EUnderlineOn; // set it on
    TInt i = 0;

    while ( i < itemArray->Count() )
        {
        iRichText->ApplyCharFormatL(
            charFormat,
            charFormatMask,
            ( *itemArray )[ i ].iStartPos,
            ( *itemArray )[ i ].iLength );
        i++;
        }

    // Highlight the 'selected' item

    iDialog->SelectionChangedL( iItem );
    }

// -----------------------------------------------------------------------------
// CFindItemController::CFindItemController
//  C++ default constructor
// -----------------------------------------------------------------------------
//
CFindItemController::CFindItemController()
    {
    }

// -----------------------------------------------------------------------------
// CFindItemController::ConstructL
//  EPOC constructor
// -----------------------------------------------------------------------------
//
void CFindItemController::ConstructL(
    const TDesC& aText,
    const CFindItemEngine::TFindItemSearchCase aSearchCase )
    {
    TInt minDigitsToFind = KFindItemMinDigitsToFind; // default
    TRAP_IGNORE( minDigitsToFind = GetMinDigitsToFindL(); );
#ifdef _DEBUG
    RDebug::Print(_L("CFindItemController::ConstructL(), minDigitsToFind %d"), minDigitsToFind );
#endif
    iEngine = CFindItemEngine::NewL( aText, aSearchCase, minDigitsToFind );
    }

// -----------------------------------------------------------------------------
// FindItemController::NewL
//  Two-phased constructor
// -----------------------------------------------------------------------------
//
CFindItemController* CFindItemController::NewL(
    MFindItemDialogCallBack* aDialog,
    CRichText* aRichText,
    const TDesC& aText,
    const CFindItemEngine::TFindItemSearchCase aSearchCase )
    {
    CFindItemController* self = new (ELeave) CFindItemController;

    self->iDialog = aDialog;
    self->iRichText = aRichText;

    CleanupStack::PushL( self );
    self->ConstructL( aText, aSearchCase );
    CleanupStack::Pop();

    return self;
    }

// -----------------------------------------------------------------------------
// CFindItemController::~CFindItemController
//  Destructor
// -----------------------------------------------------------------------------
//
CFindItemController::~CFindItemController()
    {
    delete iEngine;
    }

// -----------------------------------------------------------------------------
// CFindItemController::FillScrollBarItemsArrayL
//  Fills array with items (TInts) which causes scrollbar to move
// -----------------------------------------------------------------------------
//
void CFindItemController::FillScrollBarItemsArrayL(
    CArrayFixFlat<TInt>* aArray )
    {

    // Doesn't work for long text (>=2000chars) and it's impossible to do
    // because if the text is long enough only part of it will be formatted
    // and you cannot check if two string are at the same line in band that
    // is not formatted. So for long text, every item is counted.

    const CArrayFixFlat<CFindItemEngine::SFoundItem>*
        itemArray = iEngine->ItemArray();

    for ( TInt i=0; i < itemArray->Count(); i++ )
        {
        TInt j = i + 1;
        while ( j < itemArray->Count() &&
            iDialog->AtSameLine(
                itemArray->At( i ).iStartPos,
                itemArray->At( j ).iStartPos ) )
            {
            j++;
            }
        if ( j < itemArray->Count() )
            {
            aArray->AppendL(j);
            }
        i = j - 1;
        }
    }

// -----------------------------------------------------------------------------
// CFindItemController::IsAtSameLineAsFirstItem
//  Check if item is at the same line as first item
// -----------------------------------------------------------------------------
//
TBool CFindItemController::IsAtSameLineAsFirstItem()
    {
    if ( FirstItem() )
        {
        return ETrue;
        }

    const CArrayFixFlat<CFindItemEngine::SFoundItem>*
        itemArray = iEngine->ItemArray();

    return iDialog->AtSameLine(
        itemArray->At( Position() ).iStartPos,
        itemArray->At( 0 ).iStartPos );
    }

// -----------------------------------------------------------------------------
// CFindItemController::IsAtSameLineAsLastItem
//  Check if item is at the same line as last item
// -----------------------------------------------------------------------------
//
TBool CFindItemController::IsAtSameLineAsLastItem()
    {
    if ( LastItem() )
        {
        return ETrue;
        }

    const CArrayFixFlat<CFindItemEngine::SFoundItem>*
        itemArray = iEngine->ItemArray();

    return iDialog->AtSameLine(
        itemArray->At( Position() ).iStartPos,
        itemArray->At( ItemCount() - 1 ).iStartPos );
    }

// -----------------------------------------------------------------------------
// CFindItemController::GetMinDigitsToFindL
//  Get minimum number of digits to find.
// -----------------------------------------------------------------------------
//
TInt CFindItemController::GetMinDigitsToFindL()
     {
    TInt err = KErrNone;
    CRepository* variation = CRepository::NewL( KCRUidCommonUi );
    TInt value;
    err = variation->Get( KCuiMinDigitsToFind, value );
    delete variation;
    variation = NULL;
    if ( err != KErrNone )
        {
        value = KFindItemMinDigitsToFind;
        }
    return value;
    }

// -----------------------------------------------------------------------------
// CFindItemController::Item()
//  Get indexed item from engine side.
// -----------------------------------------------------------------------------
//
TBool CFindItemController::Item(
    const TInt aIndex,
    CFindItemEngine::SFoundItem& aItem ) const
    {
    TInt validItem = EFalse;
    if( aIndex >= 0 && aIndex < ItemCount() )
        {
        aItem = iEngine->ItemArray()->At( aIndex );
        validItem = ETrue;
        }
    return validItem;
    }

//  End of File
