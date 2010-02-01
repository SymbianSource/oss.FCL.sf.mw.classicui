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
* Description:  Container for Main View.
*
*/



// INCLUDE FILES

// Psln specific.
#include "PslnMainViewContainer.h"
#include "PslnUi.h"
#include "PslnDebug.h"
#include "PslnConst.h"

// Lists & Icons.
#include <aknlists.h>
#include <AknIconArray.h>
#include <eikclbd.h>

// Framework
#include <pslnfwplugininterface.h>
#include "PslnPluginHandler.h"

// Resources
#include <psln.rsg>
#include <pslnicon.mbg>
#include <data_caging_path_literals.hrh>

// Help related.
#include <csxhelp/skins.hlp.hrh>

// CONSTANTS
// Tab character.
_LIT( KTab, "\t" );

// Icon indexes for listbox.
const TInt KPslnGeneralId          = 0;
const TInt KPslnWallpaperId        = 1;
const TInt KPslnScreenSaverId      = 2;
// Container granularity.
const TInt KPslnMainConGranularity = 6;
// Max index of static (i.e. non-ECOM) folder when no plugins loaded.
const TInt KPslnStaticFolderNum = 2;

// Path to icon file.
_LIT( KPslnIconFilename, "z:pslnicon.mbm" );

// ============================ MEMBER FUNCTIONS ===============================

// ---------------------------------------------------------------------------
// C++ constructor can NOT contain any code, that might leave.
// ---------------------------------------------------------------------------
//
CPslnMainViewContainer::CPslnMainViewContainer( CPslnUi* aPslnUi )
    : iPslnUi( aPslnUi )
    {
    }

// ---------------------------------------------------------------------------
// Destructor.
// ---------------------------------------------------------------------------
//
CPslnMainViewContainer::~CPslnMainViewContainer()
    {
    // iListBox is deleted in class CPslnBaseContainer.
    delete iItems;
    }

// ---------------------------------------------------------------------------
// Symbian 2nd phase constructor can leave.
// ---------------------------------------------------------------------------
//
void CPslnMainViewContainer::ConstructL( const TRect& aRect )
    {
    iListBox = new (ELeave) CAknSingleLargeStyleListBox;

    BaseConstructL(
        aRect,
        R_PSLN_SKIN_LIST_VIEW_TITLE,
        R_PSLN_MAIN_VIEW_LBX );
    }

// ---------------------------------------------------------------------------
// Creates listbox.
// ---------------------------------------------------------------------------
//
void CPslnMainViewContainer::ConstructListBoxL( TInt aResLbxId )
    {
    iItems = iCoeEnv->ReadDesC16ArrayResourceL( aResLbxId );
    CreateListBoxItemsL();
    }


// ---------------------------------------------------------------------------
// Creates listbox items.
// ---------------------------------------------------------------------------
//
void CPslnMainViewContainer::CreateListBoxItemsL()
    {
    PSLN_TRACE_DEBUG("CPslnMainViewContainer::CreateListBoxItemsL BEGIN");
    // Array for icons in the listbox. Owns the icons.
    CAknIconArray* iconList =
        new (ELeave) CAknIconArray( KPslnMainConGranularity );
    CleanupStack::PushL( iconList );

    // Find the resource file:
    HBufC* iconFile = HBufC::NewLC( KMaxFileName );
    TPtr fileNamePtr = iconFile->Des();
    GetIconFilePath( fileNamePtr );

    // Add non-plugin icons to icon group.
    // General icon.
    AddIconL(
        iconList,
        KAknsIIDQgnPropPslnGeneralSub,
        fileNamePtr,
        EMbmPslniconQgn_prop_psln_general_sub,
        EMbmPslniconQgn_prop_psln_general_sub_mask );

    // Wallpaper icon.
    AddIconL(
        iconList,
        KAknsIIDQgnPropPslnWpaperSub,
        fileNamePtr,
        EMbmPslniconQgn_prop_psln_wpaper_sub,
        EMbmPslniconQgn_prop_psln_wpaper_sub_mask );

    // Screensaver screensaver.
    AddIconL(
        iconList,
        KAknsIIDQgnPropPslnSsaverSub,
        fileNamePtr,
        EMbmPslniconQgn_prop_psln_ssaver_sub,
        EMbmPslniconQgn_prop_psln_ssaver_sub_mask );

    CleanupStack::PopAndDestroy( iconFile );

    // Add General Theme static view.
    // Icon location is ok - directly from resources.
    MakeItemL( KPslnGeneralId );

    // How many dynamic items have been added in-between.
    TInt offset = 0;
    iPluginArray = iPslnUi->PluginHandler()->GetPluginArray();
    // Create buffers.
    HBufC* buf = HBufC::NewLC( KPslnItemLength );
    TPtr ptrBuf = buf->Des();
    HBufC* item = HBufC::NewLC( KPslnItemLength );
    TPtr ptrItem = item->Des();
    // Add Active Idle (and Application Shell) plugin(s).
    if ( iPluginArray )
        {
        for ( TInt i = 0; i < iPluginArray->Count(); i++ )
            {
            CPslnFWPluginInterface* plugin = iPluginArray->operator[]( i );
            CleanupStack::PushL( plugin );

            // TRAP all but OOM, so that plugins cannot cause Psln to fail to
            // launch.
            TRAPD( err,
                offset += MakePluginItemL( *plugin, *iconList, ptrBuf, ptrItem ) );
            if ( err == KErrNoMemory )
                {
                User::Leave( KErrNoMemory );
                }

            // Initialize buffers.
            ptrBuf.Zero();
            ptrItem.Zero();

            // icon is now owned by icon array and plugin by plugin handler
            CleanupStack::Pop( plugin );
            plugin = NULL;
            }
        }
    CleanupStack::PopAndDestroy( 2, buf ); // buf, item

    // Add Screen Saver and Wallpaper static views.
    TBitFlags views = iPslnUi->ViewSupport();
    if ( views.IsSet( CPslnUi::EPslnWallpaperView ) )
        {
        MakeItemL( KPslnWallpaperId, offset );
        }

    if ( views.IsSet( CPslnUi::EPslnScreensaverView ) )
        {
        MakeItemL( KPslnScreenSaverId, offset );
        }

    iPslnUi->AllViewsDone();

    // Destroy the old icons because SetIconArray() does not destroy them.
    CEikColumnListBox* listbox = static_cast<CEikColumnListBox*> ( iListBox );
    CArrayPtr<CGulIcon>* oldIcons =
        listbox->ItemDrawer()->ColumnData()->IconArray();
    if( oldIcons )
        {
        oldIcons->ResetAndDestroy();
        delete oldIcons;
        }

    // Transfer ownership of icon array to the lbx.
    listbox->ItemDrawer()->ColumnData()->SetIconArray( iconList );
    CleanupStack::Pop( iconList );

    iListBox->HandleItemAdditionL();
    PSLN_TRACE_DEBUG("CPslnMainViewContainer::CreateListBoxItemsL END");
    }

// ---------------------------------------------------------------------------
// Creates a specific setting item.
// ---------------------------------------------------------------------------
//
void CPslnMainViewContainer::MakeItemL( const TInt aIndex, const TInt aOffset )
    {
    PSLN_TRACE_DEBUG("CPslnMainViewContainer::MakeItemL BEGIN");
    if ( aIndex > iItems->Count() )
        {
        User::Leave( KErrArgument );
        }
    HBufC* item = (*iItems)[aIndex].AllocLC();
    // Reallocating invalidates the original string.
    HBufC* reallocItem = item->ReAllocL( item->Length() + KPslnIconSize );
    CleanupStack::Pop( item );
    item = reallocItem;
    CleanupStack::PushL( item );
    reallocItem = NULL; // do not use anymore.
    TPtr ptr = item->Des();
    if ( aOffset != KErrNotFound )
        {
        iItemArray->InsertL( aIndex + aOffset, ptr );
        }
    else
        {
        iItemArray->InsertL( aIndex, ptr );
        }
    CleanupStack::PopAndDestroy( item );
    PSLN_TRACE_DEBUG("CPslnMainViewContainer::MakeItemL END");
    }

// ---------------------------------------------------------------------------
// Gets help context for Help application.
// ---------------------------------------------------------------------------
//
void CPslnMainViewContainer::GetHelpContext( TCoeHelpContext& aContext ) const
    {
    aContext.iMajor = KUidPsln;
    aContext.iContext = KSKINS_HLP_APP_MAIN;
    }

// ---------------------------------------------------------------------------
// Creates a plugin item (with title and icon)
// ---------------------------------------------------------------------------
//
TInt CPslnMainViewContainer::MakePluginItemL(
    CPslnFWPluginInterface& aPlugin, CAknIconArray& aIconList,
    TPtr& aBufPtr, TPtr& aItemPtr  )
    {
    TInt offset = 0;
    // Adding icon.
    CGulIcon* icon = aPlugin.CreateIconL();
    CleanupStack::PushL( icon );
    PSLN_TRACE_DEBUG("CPslnMainViewContainer::MakePluginItemL BEGIN");

    aPlugin.GetCaptionL( aBufPtr );
    TInt location = KErrNotFound;
    CPslnFWPluginInterface::TPslnFWLocationType locType;
    aPlugin.GetLocationTypeAndIndex( locType, location );

    // If it is AS or AI plugin, add it.
    if ( aPlugin.Id().iUid == KPslnASPluginUid.iUid ||
         aPlugin.Id().iUid == KPslnAIPluginUid.iUid )
        {
        TInt upcomingPlace = location + KPslnStaticFolderNum;
        if ( upcomingPlace >= aIconList.Count() )
            {
            upcomingPlace = aIconList.Count();
            }
        aIconList.InsertL( upcomingPlace , icon );

        // Let's correct the icon index.
        upcomingPlace = location + KPslnStaticFolderNum;
        aItemPtr.AppendNum( upcomingPlace );
        aItemPtr.Append( KTab );
        aItemPtr.Append( aBufPtr );
        if ( location >= iItemArray->Count() )
            {
            location = iItemArray->Count();
            }
        iItemArray->InsertL( location , aItemPtr );
        offset++;
        }
    else
        {
        aIconList.AppendL( icon );
        // use icon list position as index
        // iconList->Count() is here always at least 1
        // we need to adjust the icon index based on loaded plugins
        // which are inserted between static views.
        aItemPtr.AppendNum( aIconList.Count() - 1 + iAIAdded + iASAdded );
        aItemPtr.Append( KTab );
        aItemPtr.Append( aBufPtr );
        iItemArray->AppendL( aItemPtr );
        }

    if ( aPlugin.Id().iUid == KPslnASPluginUid.iUid )
        {
        iASAdded = ETrue;
        }

    if ( aPlugin.Id().iUid == KPslnAIPluginUid.iUid )
        {
        iAIAdded = ETrue;
        }

    CleanupStack::Pop( icon );
    return offset;
    }

// ---------------------------------------------------------------------------
// Adds icon to icon array.
// ---------------------------------------------------------------------------
//
void CPslnMainViewContainer::AddIconL(
    CAknIconArray* aIcons,
    const TAknsItemID& aSkinId,
    const TDesC& aFileName,
    TInt aBitmapId,
    TInt aMaskId )
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
    if ( aIcons )
        {
        aIcons->AppendL( icon );
        }
    CleanupStack::Pop( icon );
    }

// ---------------------------------------------------------------------------
// Parses icon file path to given parameter.
// ---------------------------------------------------------------------------
//
void CPslnMainViewContainer::GetIconFilePath( TDes& aPath )
    {
    // Find the resource file:
    TParse parse;
    parse.Set( KPslnIconFilename, &KDC_APP_BITMAP_DIR, NULL );
    if ( aPath.MaxLength() >= parse.FullName().Length() )
        {
        aPath.Copy( parse.FullName() );
        }
    }

//  End of File
