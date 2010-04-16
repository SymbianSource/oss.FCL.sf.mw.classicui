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
* Description:  Utility class to get icons to setting lists and 
*                   help with loc strings.
*
*/



// INCLUDE FILES
#include "pslnfwiconhelper.h"

// Icons
#include <AknIconArray.h>
#include <gulicon.h>
#include <pslnicon.mbg>
#include <variatedbitmaps.mbg>
#include <data_caging_path_literals.hrh>

// Resource loading
#include <bautils.h>
#include <barsread.h>
#include <StringLoader.h>
#include <ConeResLoader.h>

// Listboxes
#include <eikclb.h>
#include <eikclbd.h>

// Skins
#include <AknsUtils.h>
#include <aknconsts.h>

// CONSTANTS
// Location of icon file.
_LIT( KPslnFWIconFilename, "z:Pslnicon.mbm" );
// Granularity of icon array.
const TInt KPslnIconArraySize = 6;

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CPslnFWIconHelper::CPslnFWIconHelper()
    {
    }

// -----------------------------------------------------------------------------
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
EXPORT_C CPslnFWIconHelper* CPslnFWIconHelper::NewL()
    {
    CPslnFWIconHelper* self = new( ELeave ) CPslnFWIconHelper;
    return self;
    }

// Destructor
EXPORT_C CPslnFWIconHelper::~CPslnFWIconHelper()
    {
    }

// ---------------------------------------------------------------------------
// Adds pre- and post-text icons to setting item lists.
// ---------------------------------------------------------------------------
//
EXPORT_C void CPslnFWIconHelper::AddIconsToSettingItemsL( 
    TBool aAll, TInt aMaxIndexToAdd, CEikTextListBox* aListBox )
    {
    // Check that the given parameters are valid.
    if ( !aAll && aMaxIndexToAdd <= 0 )
        {
        User::Leave( KErrArgument );
        }

    CAknIconArray* icons =
        new (ELeave) CAknIconArray( KPslnIconArraySize );

    CEikColumnListBox* columnListBox =
        static_cast<CEikColumnListBox*>( aListBox );

    CArrayPtr<CGulIcon>* previcons =
        columnListBox->ItemDrawer()->ColumnData()->IconArray();
    if ( previcons )
        {
        previcons->ResetAndDestroy();
        delete previcons;
        previcons = NULL;
        }
    columnListBox->ItemDrawer()->ColumnData()->SetIconArray( icons );
    
    if ( !icons )
        {
        return;
        }

    TInt bitmapIndex = 0;
    if ( aAll || aMaxIndexToAdd >= bitmapIndex )
        {
        // 0: Non active (empty bitmap)
        CFbsBitmap *bitmap = new (ELeave) CFbsBitmap;
        User::LeaveIfError(
            bitmap->Create( TSize(0, 0), EColor256 ) );
        icons->AppendL( CGulIcon::NewL( bitmap ) );
        bitmapIndex++;
        }

    HBufC* fileName = HBufC::NewLC( KMaxFileName );
    TPtr fileNamePtr = fileName->Des();
    GetIconFilePath( fileNamePtr );

    if ( aAll || aMaxIndexToAdd >= bitmapIndex )
        {
        // 1: Active mark
        AddIconL( icons,
            KAknsIIDQgnPropPslnActive,
            fileNamePtr,
            EMbmPslniconQgn_prop_psln_active,
            EMbmPslniconQgn_prop_psln_active_mask );
        bitmapIndex++;
        }

    if ( aAll || aMaxIndexToAdd >= bitmapIndex )
        {
        // 2: URL icon (in front of EEL)
        AddIconL( icons,
            KAknsIIDQgnPropLinkEmbdSmall,
            KAvkonVariatedBitmapsFile,
            EMbmVariatedbitmapsQgn_prop_link_embd_small,
            EMbmVariatedbitmapsQgn_prop_link_embd_small_mask );
        bitmapIndex++;
        }

    if ( aAll || aMaxIndexToAdd >= bitmapIndex )
        {
        // 3: MMC icon
        AddIconL( icons, 
            KAknsIIDQgnIndiMmcAdd,
            fileNamePtr,
            EMbmPslniconQgn_indi_mmc_add,
            EMbmPslniconQgn_indi_mmc_add_mask,
            ETrue );
        bitmapIndex++;
        }

    if ( aAll || aMaxIndexToAdd >= bitmapIndex )
        {
        //4: EAknsSrvProtected,
        AddIconL( icons,
            KAknsIIDQgnIndiDrmRightsAdd,
            fileNamePtr,
            EMbmPslniconQgn_indi_drm_rights_add,
            EMbmPslniconQgn_indi_drm_rights_add_mask,
            ETrue );
        bitmapIndex++;
        }

    if ( aAll || aMaxIndexToAdd >= bitmapIndex )
        {
        //5: EAknsSrvNoRights
        AddIconL( icons,
            KAknsIIDQgnIndiDrmRightsExpAdd,
            fileNamePtr,
            EMbmPslniconQgn_indi_drm_rights_exp_add,
            EMbmPslniconQgn_indi_drm_rights_exp_add_mask,
            ETrue );
        bitmapIndex++;
        }

    if ( aAll || aMaxIndexToAdd >= bitmapIndex )
        {
        //6: EAknsMinorGenericQgnIndiFmgrMsAdd - mass drive 
        AddIconL( icons,
            KAknsIIDQgnIndiFmgrMsAdd,
            fileNamePtr,
            EMbmPslniconQgn_indi_fmgr_ms_add,
            EMbmPslniconQgn_indi_fmgr_ms_add_mask,
            ETrue );
        bitmapIndex++;
        }
    CleanupStack::PopAndDestroy( fileName );
    }

// ---------------------------------------------------------------------------
// Retrieves localized string txt.
// ---------------------------------------------------------------------------
//
EXPORT_C HBufC* CPslnFWIconHelper::GetLocalizedStringLC(
    const TDesC& aPath, TInt aResourceID, CCoeEnv* aCoeEnv )
    {
    RConeResourceLoader resLoader( *aCoeEnv );
    CleanupClosePushL( resLoader );
    // Open resource file:
    TFileName* file = new (ELeave) TFileName( aPath );
    CleanupStack::PushL( file );
    resLoader.OpenL( *file );
    CleanupStack::PopAndDestroy( file );

    HBufC* result = StringLoader::LoadL( aResourceID );
    CleanupStack::PopAndDestroy(); // resLoader - it is closed as well
    CleanupStack::PushL( result );
    return result;
    }

// ---------------------------------------------------------------------------
// Adds icon to an icon array.
// ---------------------------------------------------------------------------
//
void CPslnFWIconHelper::AddIconL(
    CAknIconArray* aIcons,
    const TAknsItemID& aSkinId,
    const TDesC& aFileName,
    TInt aBitmapId,
    TInt aMaskId,
    TBool aColorIcon )
    {
    if ( aColorIcon )
        {
        CFbsBitmap* bitmap = NULL;
        CFbsBitmap* mask = NULL;
        AknsUtils::CreateColorIconL(
            AknsUtils::SkinInstance(),
            aSkinId,
            KAknsIIDQsnIconColors,
            EAknsCIQsnIconColorsCG13,
            bitmap,
            mask,
            aFileName,
            aBitmapId,
            aMaskId,
            KRgbBlack );
        CleanupStack::PushL( bitmap );
        CleanupStack::PushL( mask );
        CGulIcon* icon = CGulIcon::NewL( bitmap, mask );
        CleanupStack::Pop( 2, bitmap ); // bitmap, mask
        CleanupStack::PushL( icon );
        aIcons->AppendL( icon );
        CleanupStack::Pop( icon );
        }
    else
        {
        CFbsBitmap* bitmap = NULL;
        CFbsBitmap* mask = NULL;
        AknsUtils::CreateIconL(
            AknsUtils::SkinInstance(),
            aSkinId,
            bitmap,
            mask,
            aFileName,
            aBitmapId,
            aMaskId );
        CleanupStack::PushL( bitmap );
        CleanupStack::PushL( mask );
        CGulIcon* icon = CGulIcon::NewL( bitmap, mask );
        CleanupStack::Pop( 2, bitmap ); // bitmap, mask
        CleanupStack::PushL( icon );
        aIcons->AppendL( icon );
        CleanupStack::Pop( icon );
        }
    }

// ---------------------------------------------------------------------------
// Retrieves icon file path.
// ---------------------------------------------------------------------------
//
void CPslnFWIconHelper::GetIconFilePath( TDes& aPath )
    {
    // Find the resource file:
    TParse parse;
    parse.Set( KPslnFWIconFilename, &KDC_APP_BITMAP_DIR, NULL );
    if ( aPath.MaxLength() >= parse.FullName().Length() )
        {
        aPath.Copy( parse.FullName() );
        }
    }


//  End of File  
