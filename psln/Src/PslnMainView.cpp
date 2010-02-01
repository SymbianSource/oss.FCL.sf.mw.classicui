/*
* Copyright (c) 2005-2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Main state view for Psln application.
*
*/



// INCLUDE FILES
#include <psln.rsg>

#include <eikbtgpc.h>
#include <avkon.rsg>

#include "PslnMainView.h"
#include "PslnMainViewContainer.h"
#include "PslnUi.h"

// Framework
#include <pslnfwplugininterface.h>
#include "PslnPluginHandler.h"

// CONSTANTS
// Main view indexes of default plugins.
const TInt KPslnASPluginLoc = 1;
const TInt KPslnAIPluginLoc = 2;

// ============================ MEMBER FUNCTIONS ===============================
// ---------------------------------------------------------------------------
// Two-phased constructor.
// ---------------------------------------------------------------------------
//
CPslnMainView* CPslnMainView::NewLC()
    {
    CPslnMainView* self = new (ELeave) CPslnMainView();
    CleanupStack::PushL( self );
    self->ConstructL();
    return self;
    }

// ---------------------------------------------------------------------------
// Symbian 2nd phase constructor can leave.
// ---------------------------------------------------------------------------
//
void CPslnMainView::ConstructL()
    {
    BaseConstructL( R_PSLN_MAIN_VIEW );

    ConstructViewArrayL();
    // Start background operation and create tabgroup.
    iPslnUi->LoadViewsWhenIdleL();
    iPslnUi->ConstructTabGroupL();
    }

// ---------------------------------------------------------------------------
// C++ default constructor can NOT contain any code, that might leave.
// ---------------------------------------------------------------------------
//
CPslnMainView::CPslnMainView()
    {
    }

// ---------------------------------------------------------------------------
// Destructor.
// ---------------------------------------------------------------------------
//
CPslnMainView::~CPslnMainView()
    {
    iViewIds.Close();
    }

// ---------------------------------------------------------------------------
// TUid CPslnMainView::Id()
// ---------------------------------------------------------------------------
//
TUid CPslnMainView::Id() const
    {
    return KPslnMainView2;
    }

// ---------------------------------------------------------------------------
// CPslnMainView::HandleCommandL
// ---------------------------------------------------------------------------
//
void CPslnMainView::HandleCommandL( TInt aCommand )
    {
    switch ( aCommand )
        {
        case EPslnCmdAppOpen:
            DoActivateLocalViewL();
            break;
        // If view was launched externally, handle back as exit.
        case EAknSoftkeyBack:
        case EAknSoftkeyExit:
            aCommand = EAknCmdExit;
            //lint -fallthrough
        default:
            iPslnUi->HandleCommandL( aCommand );
            break;
        }
    }

// ---------------------------------------------------------------------------
// CPslnMainView::ActiveView
// ---------------------------------------------------------------------------
//
TInt CPslnMainView::ActiveView() const
    {
    return iCurrentItem;
    }

// ---------------------------------------------------------------------------
// CPslnMainView::SetActiveFolder
// ---------------------------------------------------------------------------
//
void CPslnMainView::SetActiveFolder( TInt aIndex )
    {
    iCurrentItem = aIndex;
    }

// ---------------------------------------------------------------------------
// CPslnMainView::ActiveFolderUid
// ---------------------------------------------------------------------------
//
TInt CPslnMainView::ActiveFolderUid()
    {
    if ( ( iCurrentItem > iViewIds.Count() )||
         ( iCurrentItem < 0 ) )
        {
        // If index is out-of-bounds, set first item active.
        iCurrentItem = 0;
        return 0;
        }
    return iViewIds[ iCurrentItem ].iUid;
    }

// ---------------------------------------------------------------------------
// CPslnMainView::SetActiveFolder
// ---------------------------------------------------------------------------
//
void CPslnMainView::SetActiveFolder( TUid aUid )
    {
    for ( TInt idx = 0; idx < iViewIds.Count(); idx++ )
        {
        if ( iViewIds[ idx ].iUid == aUid.iUid )
            {
            iCurrentItem = idx;
            }
        }
    }

// ---------------------------------------------------------------------------
// CPslnMainView::DoActivateL
// ---------------------------------------------------------------------------
void CPslnMainView::DoActivateL(
    const TVwsViewId& aPrevViewId,
    TUid aCustomMessageId,
    const TDesC8& aCustomMessage )
    {
    // If application is launched through NULL thread, it means that it is
    // launched as embedded application
    if ( aPrevViewId.iAppUid.iUid == KUidPsln.iUid &&
         aPrevViewId.iViewUid.iUid == KPslnGeneralView.iUid )
        {        
        MAknsSkinInstance* si = AknsUtils::SkinInstance();
        si->SetChangeEventsEnabled( EFalse );
        si->RemoveLocalItemDefs();
        si->SetChangeEventsEnabled( ETrue );
        }

    CPslnBaseView::DoActivateL(
        aPrevViewId,
        aCustomMessageId,
        aCustomMessage );

    // Set middle softkey label.
    CPslnBaseView::SetMiddleSoftKeyLabelL(
        R_PSLN_MSK_OPEN,
        EPslnCmdAppOpen );

    //set highlight ,if returning from other view
    if(iContainer && aPrevViewId.iAppUid.iUid == KUidPsln.iUid)
        {
        //search which item should be highlighted
        TInt activateItem = GetListboxItemIndexByViewId(aPrevViewId);
        if(activateItem != KErrNotFound)
            {
            iContainer->SetCurrentItemIndex( activateItem );
            }
        else
            {
            iContainer->SetCurrentItemIndex( iCurrentItem );
            }
        }
    }

// ---------------------------------------------------------------------------
// CPslnMainView::DynInitMenuPaneL
// ---------------------------------------------------------------------------
//
void CPslnMainView::DynInitMenuPaneL(
    TInt aResourceId, CEikMenuPane* aMenuPane )
    {
    CPslnBaseView::DynInitMenuPaneL( aResourceId, aMenuPane );
    }

// ---------------------------------------------------------------------------
// CPslnMainView::HandleListBoxSelectionL
// ---------------------------------------------------------------------------
//
void CPslnMainView::HandleListBoxSelectionL()
    {
    HandleCommandL( EPslnCmdAppOpen );
    }

// -----------------------------------------------------------------------------
// CPslnMainView::HandleListBoxItemHighlightL
// -----------------------------------------------------------------------------
//
void CPslnMainView::HandleListBoxItemHighlightL()
    {    
    }

// ---------------------------------------------------------------------------
// CPslnMainView::NewContainerL
// ---------------------------------------------------------------------------
//
void CPslnMainView::NewContainerL()
    {
    iContainer = new(ELeave) CPslnMainViewContainer( iPslnUi );
    }

// ---------------------------------------------------------------------------
// CPslnMainView::ConstructViewArrayL
// ---------------------------------------------------------------------------
//
void CPslnMainView::ConstructViewArrayL()
    {
    // First add static views.
    iViewIds.AppendL( KPslnGeneralView );

    TBitFlags views = iPslnUi->ViewSupport();
    if ( views.IsSet( CPslnUi::EPslnWallpaperView ) )
        {
        iViewIds.AppendL( KPslnWallpaperView );
        }

    if ( views.IsSet ( CPslnUi::EPslnScreensaverView ) )
        {
        iViewIds.AppendL( KPslnScreenSaverView );
        }

    // Then start looking for plugins.
    CArrayPtrFlat<CPslnFWPluginInterface>* array =
        iPslnUi->PluginHandler()->GetPluginArray();
    CleanupStack::PushL ( array );
    if ( array )
        {
        TBool appShellPluginInserted = EFalse;
        for ( TInt i = 0; i < array->Count(); i++ )
            {
            CAknView* view = array->At( i );

            // If plugin is either AS or AI, insert between static views.
            if ( view->Id().iUid == KPslnASPluginUid.iUid )
                {
                iViewIds.InsertL( view->Id(), KPslnASPluginLoc );
                appShellPluginInserted = ETrue;
                }
            else if ( view->Id().iUid == KPslnAIPluginUid.iUid )
                {
                if ( appShellPluginInserted )
                    {
                    iViewIds.InsertL( view->Id(), KPslnAIPluginLoc );
                    }
                else
                    {
                    // If there is ASplugin - claim it's place.
                    // note that ASplugin maybe later inserted to this place.
                    iViewIds.InsertL( view->Id(), KPslnASPluginLoc );
                    }
                }
            // Other plugins are just appended in order from plugin array.
            // Plugins are already ordered in PluginHandler.
            else
                {
                iViewIds.AppendL( view->Id() );
                }
            }
        }
    CleanupStack::Pop( array );
    }

// ---------------------------------------------------------------------------
// CPslnMainView::CbaExitEnabled
// ---------------------------------------------------------------------------
//
TInt CPslnMainView::CbaResourceId( const TVwsViewId& /*aPrevViewId*/,TUid /*aCustomMessageId*/ )
    {
    TBool value =  iEikonEnv->StartedAsServerApp();
    return   value ? R_AVKON_SOFTKEYS_OPTIONS_BACK
        : R_AVKON_SOFTKEYS_OPTIONS_EXIT;
    }

// ---------------------------------------------------------------------------
// Tries to activate local view from UI class. If class is not yet
// created, instructs UI class to create the view first.
// ---------------------------------------------------------------------------
//
void CPslnMainView::DoActivateLocalViewL()
    {
    if ( iContainer )
        {
        iCurrentItem = iContainer->CurrentItemIndex();
        }
    if ( iCurrentItem > iViewIds.Count() )
        {
        User::Leave( KErrOverflow );
        }
    // These views are possibly done dynamically. It is possible that due to
    // idle time, they have already been created.
    if ( iCurrentItem == KPslnGeneralView.iUid ||
         iCurrentItem == KPslnWallpaperView.iUid ||
         iCurrentItem == KPslnScreenSaverView.iUid )
        {
        iPslnUi->CreateViewL( iViewIds[ iCurrentItem ] );
        }
    iPslnUi->ActivateLocalViewL( iViewIds[ iCurrentItem ] );
    }
    
// ---------------------------------------------------------------------------
// Return given view's index by searching the view id
// ---------------------------------------------------------------------------
//
TInt CPslnMainView::GetListboxItemIndexByViewId(const TVwsViewId& aViewId) const
    {
    TInt listBoxItemIndex = KErrNotFound;
    
    for( int i=0; i<iViewIds.Count(); i++ )
        {
        if( iViewIds[i] == aViewId.iViewUid )
            {
            listBoxItemIndex = i;
            }
        }
        
    return listBoxItemIndex;
    };
    
//  End of File
