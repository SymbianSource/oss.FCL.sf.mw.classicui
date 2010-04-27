/*
* Copyright (c) 2005-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  General theme view's container.
*
*/


// INCLUDE FILES
// General
#include <aknlists.h>
#include <eikclbd.h>
#include <StringLoader.h>
#include <AknGlobalNote.h>

#include <aknlistloadertfx.h>

#include <aknnotewrappers.h> 

// Resources.
#include <psln.rsg>

// Constants.
#include "PslnConst.h"

// Help context.
#include <csxhelp/skins.hlp.hrh>

// HAL
#include <hal.h>

// General - psln specific.
#include "PslnGeneralThemeContainer.h"
#include "PslnFeatures.h"
#include "PslnModel.h"
#include "PslnDebug.h"
#include "PslnSkinEntry.h"
#include "PslnUi.h"

// Central Repository and Publish&Subscribe keys.
#include <centralrepository.h>
#include "pslninternalcrkeys.h"


// Framework
#include <pslnfwiconhelper.h>
#include <mpslnfwmsklabelobserver.h>

// ============================ MEMBER FUNCTIONS ===============================
// -----------------------------------------------------------------------------
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CPslnGeneralThemeContainer::CPslnGeneralThemeContainer()
    {
    }

// -----------------------------------------------------------------------------
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CPslnGeneralThemeContainer::ConstructL( const TRect& aRect )
    {
    iListBox = new (ELeave) CAknSingleGraphicStyleListBox;
    BaseConstructL( aRect, R_PSLN_SKIN_LIST_VIEW_TITLE, KPslnNoResource );
    iOldSkinNum = iModel->NumberOfSkins();
    }

// Destructor
CPslnGeneralThemeContainer::~CPslnGeneralThemeContainer()
    {
    }

// ---------------------------------------------------------------------------
// Checks if embedded browser is supported.
// ---------------------------------------------------------------------------
//
TBool CPslnGeneralThemeContainer::IsEmbeddedLinkVisible() const
    {
    return PslnFeatures::IsEnhancedEmbeddedLinksSupported();
    }

// ---------------------------------------------------------------------------
// Updates skin item list.
// ---------------------------------------------------------------------------
//
void CPslnGeneralThemeContainer::UpdateSkinListItemsL( const TInt& aNewIndex )
{
    // This is needed to make the list effects update
    CAknListLoader::InvalidateAll();

    PSLN_TRACE_DEBUG("CPslnGeneralThemeContainer::UpdateSkinListItemsL");
    // Update skins.
    iItemArray->Reset();
    iToBeUsedIndex = KErrNotFound;
    if ( aNewIndex != KErrNotFound )
        {
        iToBeUsedIndex = aNewIndex;
        }
    CreateListBoxItemsL();
    
    // Create pre- and post-text icons.
    CPslnFWIconHelper* iconHelper = CPslnFWIconHelper::NewL();
    CleanupStack::PushL( iconHelper );
    iconHelper->AddIconsToSettingItemsL(
        ETrue,
        KErrNotFound, // not used since we are adding all
        iListBox );
    CleanupStack::PopAndDestroy( iconHelper );
    
    }

// -----------------------------------------------------------------------------
// Creates listbox.
// -----------------------------------------------------------------------------
//
void CPslnGeneralThemeContainer::ConstructListBoxL( TInt /*aResLbxId*/ )
    {
    UpdateSkinListItemsL( KErrNotFound );
    }

// -----------------------------------------------------------------------------
// Empty implementation of inherited method.
// -----------------------------------------------------------------------------
//
void CPslnGeneralThemeContainer::CreateListBoxItemsL()
    {
    PSLN_TRACE_DEBUG("CPslnGeneralThemeContainer::CreateListBoxItemsL BEGIN");
    TInt downloadAdded = 0;
    if ( IsEmbeddedLinkVisible() )
        {
        HBufC* text = StringLoader::LoadLC(
            R_PSLN_QTN_SKINS_DOWNLOAD_SKINS, iEikonEnv );
        // Reallocating invalidates original text, so it is required that
        // original text is popped from cleanupstack, then reassigned to
        // reallocated value and finally pushed back to cleanupstack.
        HBufC* reallocText = text->ReAllocL( text->Length() + KPslnIconSize );
        CleanupStack::Pop( text );
        text = reallocText;
        CleanupStack::PushL( text );
        // Do not use reallocated string after assigning it to the original.
        reallocText = NULL;
        TPtr textPtr = text->Des();

        textPtr.Insert( 0, KPslnFWEmbeddedLinkListItemFormat );
        iItemArray->InsertL( 0, textPtr );
        downloadAdded = 1;
        CleanupStack::PopAndDestroy( text );
        }

    TInt maxSkinIndex = 0;
    if ( iModel )
        {
        // If current skin is not found => update from server.
        if ( iModel->ActiveSkinIndex() == KErrNotFound )
            {
            iModel->PerformCompleteUpdateL();
            }
        maxSkinIndex = iModel->NumberOfSkins();
        }

    HBufC* skinName = HBufC::NewLC( KMaxName );
    TInt currentlyActiveSkinIndex = KErrNotFound;
    static_cast<CPslnUi*>( ControlEnv()->AppUi() )->
        SetDRMProtectedSkinInSkinList( EFalse );

    for ( TInt skinIndex = KPslnSeries60SkinIndex;
          skinIndex < maxSkinIndex; skinIndex++ )
        {
        PSLN_TRACE_DEBUG("CPslnGeneralThemeContainer::CreateListBoxItemsL 3");
        TPtr skinNamePtr = skinName->Des();
        iModel->GetSkinNameByIndex(
            skinIndex,
            skinNamePtr,
            EPslnSkinNameTypeList );

        // Add pre-text icon.
        if ( iModel->IsActiveSkinSelected( skinIndex  ) )
            {
            skinNamePtr.Insert( 0, KPslnFWActiveListItemFormat );
            currentlyActiveSkinIndex = skinIndex;
            }
        else
            {
            skinNamePtr.Insert( 0, KPslnFWNonActiveListItemFormat );
            }

        if( iModel->IsActiveSkinSelected( skinIndex  ) && iToBeUsedIndex == KErrNotFound )
            {
            iModel->SetCurrentSelectedSkinIndex (skinIndex);
            iToBeUsedIndex = skinIndex + downloadAdded;
            }

        // Add post-text icon(s).
#ifndef RD_MULTIPLE_DRIVE
        if( iModel->LocationOfSkin( skinIndex ) == EAknsSrvMMC )
            {
            skinNamePtr.Append( KPslnFWListItemFormatMMCSuffix );
            }
#else
        if( iModel->IsThemeOnMemoryCard( skinIndex ) )
            {
            skinNamePtr.Append( KPslnFWListItemFormatMMCSuffix );
            }
        else if( iModel->IsThemeOnMassDrive( skinIndex ) )
            {
            skinNamePtr.Append( KPslnFWListItemFormatMassDriveSuffix );
            }
#endif // RD_MULTIPLE_DRIVE

        switch( iModel->ProtectionOfSkin( skinIndex ) )
            {
            case EAknsSrvProtected:
                skinNamePtr.Append( KPslnFWListItemFormatDRMProtectedSuffix );
                static_cast<CPslnUi*>( ControlEnv()->AppUi() )->
                    SetDRMProtectedSkinInSkinList( ETrue );
                break;
            case EAknsSrvNoRights:
            case EAknsSrvCountBased:
            case EAknsSrvFutureRights:
            case EAknsSrvExpiredRights:
                skinNamePtr.Append( KPslnFWListItemFormatDRMExpiredSuffix );
                static_cast<CPslnUi*>( ControlEnv()->AppUi() )->
                    SetDRMProtectedSkinInSkinList( ETrue );
                break;
            case EAknsSrvNoProtection:
            default:
                // Do nothing
                break;
            }
        PSLN_TRACE_DEBUG1("CPslnGeneralThemeContainer::CreateListBoxItemsL postfix icon: %d", iModel->ProtectionOfSkin( skinIndex ) );
        iItemArray->InsertL( ( skinIndex + downloadAdded ), skinNamePtr );
        skinNamePtr.Zero();
        }
    CleanupStack::PopAndDestroy( skinName );
    
    iActiveSkinItemIndex = currentlyActiveSkinIndex + downloadAdded;
    if ( iOldSkinNum != maxSkinIndex )
        {
        iToBeUsedIndex = currentlyActiveSkinIndex + downloadAdded;
        }
    if ( ( iToBeUsedIndex >= ( 0 + downloadAdded ) ) &&
         ( iToBeUsedIndex <= ( maxSkinIndex + downloadAdded ) ) )
        {
        SetCurrentItemIndex( iToBeUsedIndex );
        }
    else
        {    
        SetCurrentItemIndex( currentlyActiveSkinIndex + downloadAdded );
        }
    iListBox->HandleItemAdditionL();
    if ( iOldSkinNum != maxSkinIndex )
        {
        iOldSkinNum = maxSkinIndex;
        }
    PSLN_TRACE_DEBUG("CPslnGeneralThemeContainer::CreateListBoxItemsL END");
    }

// ---------------------------------------------------------------------------
// Updates D column icons.
// ---------------------------------------------------------------------------
//
void CPslnGeneralThemeContainer::UpdateSkinListItemsDColumnOnlyL()
    {
    // Create pre- and post-text icons.
    CPslnFWIconHelper* iconHelper = CPslnFWIconHelper::NewL();
    CleanupStack::PushL( iconHelper );
    iconHelper->AddIconsToSettingItemsL(
        ETrue,
        KErrNotFound, // not used since we are adding all
        iListBox );
    CleanupStack::PopAndDestroy( iconHelper );
    }

// ---------------------------------------------------------------------------
// Gets help context for Help application.
// ---------------------------------------------------------------------------
//
void CPslnGeneralThemeContainer::GetHelpContext(
    TCoeHelpContext& aContext ) const
    {
    aContext.iMajor = KUidPsln;
    aContext.iContext = KSKINS_HLP_LIST;
    }

//  End of File
