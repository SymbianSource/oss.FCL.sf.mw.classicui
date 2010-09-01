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
* Description:  Wallpaper view's container.
*
*/



// INCLUDE FILES

// UI framework services.
#include <aknlists.h>
#include <eikclbd.h>

// Help context.
#include <csxhelp/skins.hlp.hrh>

// Resources
#include <psln.rsg>

// Psln specific.
#include "PslnModel.h"
#include "PslnWallpaperContainer.h"
#include "PslnConst.h"
#include "PslnDebug.h"
#include "PslnFeatures.h"

// Framework
#include <pslnfwiconhelper.h>

// CONSTANTS
// Number of wallpaper items in listbox.
#ifndef RD_SLIDESHOW_WALLPAPER
const TInt KPslnWallpaperItems = 2;
#else
const TInt KPslnWallpaperItems = 3;
#endif // RD_SLIDESHOW_WALLPAPER

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CPslnWallpaperContainer::CPslnWallpaperContainer()
    {
    }

// -----------------------------------------------------------------------------
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CPslnWallpaperContainer::ConstructL( const TRect& aRect )
    {
    iListBox = new (ELeave) CAknSingleGraphicStyleListBox;

    BaseConstructL(
        aRect,
        R_PSLN_WP_VIEW_LBX );
    }

// Destructor
CPslnWallpaperContainer::~CPslnWallpaperContainer()
    {
    // iListBox is deleted in class CPslnBaseContainer.
    delete iItems;
    }

// ---------------------------------------------------------------------------
// CPslnWallpaperContainer::UpdateListBoxL
// ---------------------------------------------------------------------------
//
void CPslnWallpaperContainer::UpdateListBoxL()
    {
    CPslnBaseContainer::UpdateListBoxL();
    }

// -----------------------------------------------------------------------------
// CPslnWallpaperContainer::ConstructListBoxL
// -----------------------------------------------------------------------------
//
void CPslnWallpaperContainer::ConstructListBoxL( TInt aResLbxId )
    {
    iItems = iCoeEnv->ReadDesC16ArrayResourceL( aResLbxId );
    CreateListBoxItemsL();
    }

// -----------------------------------------------------------------------------
// CPslnWallpaperContainer::CreateListBoxItemsL
// -----------------------------------------------------------------------------
//
void CPslnWallpaperContainer::CreateListBoxItemsL()
    {
    PSLN_TRACE_DEBUG("CPslnWallpaperContainer::CreateListBoxItemsL BEGIN");
    iItemArray->Reset();
    TInt selectedItem = iModel->CurrentPropertyIndexL( KPslnBgIdleSettingId );

    TBool slidesetSupport = 
        PslnFeatures::IsSupported( KPslnWallpaperSlideSetDialog );

    // Check that returned value is meaningful. If not, assume 'none' is set.
    TInt maxIndex = KPslnWallpaperItems - 1;
    if ( selectedItem < 0 ||
         selectedItem > maxIndex )
        {
        selectedItem = 0;
        }

    for( TInt i = 0; i < KPslnWallpaperItems; i++ )
        {
        if ( i > iItems->Count() )
            {
            User::Leave( KErrOverflow );
            }
        HBufC* itemBuf = (*iItems)[i].AllocL();
        if ( itemBuf )
            {
            PSLN_TRACE_DEBUG("CPslnWallpaperContainer::CreateListBoxItemsL 2");
            itemBuf = itemBuf->ReAllocL( itemBuf->Length() + KPslnIconSize );
            TPtr ptr = itemBuf->Des();
            if ( selectedItem == i )
                {
                ptr.Insert( 0, KPslnFWActiveListItemFormat );
                }
            else
                {
                ptr.Insert( 0, KPslnFWNonActiveListItemFormat );
                }
            if ( !slidesetSupport && (i + 1) == KPslnWallpaperItems )
                {
                // skip
                }
            else
                {       
                iItemArray->InsertL( i, ptr );
                }
            delete itemBuf;
            }
        }

    // Add only 'not-selected' and 'selected' icons.
    CPslnFWIconHelper* iconHelper = CPslnFWIconHelper::NewL();
    CleanupStack::PushL( iconHelper );
    iconHelper->AddIconsToSettingItemsL(
        EFalse,
        1,
        iListBox );
    CleanupStack::PopAndDestroy( iconHelper );
    DrawDeferred();
    PSLN_TRACE_DEBUG("CPslnWallpaperContainer::CreateListBoxItemsL END");
    }

// ---------------------------------------------------------------------------
// Gets help context for Help application.
// ---------------------------------------------------------------------------
//
void CPslnWallpaperContainer::GetHelpContext(
    TCoeHelpContext& aContext ) const
    {
    aContext.iMajor = KUidPsln;
    aContext.iContext = KSKINS_HLP_WP_SETTINGS;
    }

//  End of File
