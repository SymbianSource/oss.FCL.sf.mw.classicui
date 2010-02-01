/*
* Copyright (c) 2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  CAknListLoader is used to load the APIs needed for listbox effects
*
*/


#include "aknlistloadertfx.h"
#include "aknlistboxtfx.h"
#include "aknlistboxtfxinternal.h"
#include "aknlistboxtfxplugin.h"
#include "aknlistboxecomids.h"
#include <ecom/ecom.h>
#include <eiklbx.h>
#include <eiklbv.h>
#include <eiklbi.h>
#include <eikmenup.h>

const TUid KUid = { 0x10282E46 }; // Uid for the CCoeStatic

// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
//
EXPORT_C MAknListBoxTfx *CAknListLoader::TfxApi(CWindowGc *aGc)
    {
    CAknListLoader *singleton = CAknListLoader::Static();

    if ( singleton && singleton->iListBoxPlugin &&
         singleton->iGcArray.Find( aGc ) != KErrNotFound )
        {
        return singleton->iListBoxPlugin->AknListBoxTfx(aGc);
        }
    return NULL;
    }

// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
//
EXPORT_C MAknListBoxTfxInternal *CAknListLoader::TfxApiInternal(CWindowGc *aGc)
    {
    CAknListLoader *singleton = CAknListLoader::Static();

    if ( singleton && singleton->iListBoxPlugin &&
         singleton->iGcArray.Find( aGc ) != KErrNotFound )
        {
        return singleton->iListBoxPlugin->AknListBoxTfxInternal(aGc);
        }
    return NULL;
    }

// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
//
EXPORT_C CWindowGc* CAknListLoader::CreateTfxGc( CEikListBox& aListBox )
    {
    CAknListLoader* singleton = CAknListLoader::Static();
    if ( !singleton )
        {
        singleton = new CAknListLoader();
        }

    if( singleton && ( !singleton->iListBoxPlugin ) )
        {
        // load plugin
        TInt err = KErrNone;
        TUid implementationUidCtrl = { KAknListBoxPluginEcomImpl };

        TRAP( err,singleton->iListBoxPlugin = ( MAknListBoxTfxPlugin* )
            REComSession::CreateImplementationL( implementationUidCtrl,
                                    singleton->iListBoxPluginEComDtorUID ) );
        }
    if ( singleton && singleton->iListBoxPlugin &&
         singleton->iGcArray.Reserve( singleton->iGcArray.Count() + 1 ) == KErrNone )
        {
        CWindowGc* ret = singleton->iListBoxPlugin->CreateTfxGc( aListBox );
        if ( ret && ret != aListBox.View()->ItemDrawer()->Gc() )
            {
            singleton->iGcArray.Append( ret );
            return ret;
            }
        }
    return aListBox.View()->ItemDrawer()->Gc();
    }

// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
//
EXPORT_C CWindowGc *CAknListLoader::CreateTfxGc( CEikMenuPane& aMenuPane,
                                                 TInt& aTopIndex,
                                                 TInt& aItemsThatFitInView )
    {
    CAknListLoader* singleton = CAknListLoader::Static();
    if( !singleton )
        {
        singleton = new CAknListLoader();
        }

    if ( singleton && ( !singleton->iListBoxPlugin ) )
        {
        // load plugin
        TInt err = KErrNone;
        TUid implementationUidCtrl = { KAknListBoxPluginEcomImpl };

        TRAP( err, singleton->iListBoxPlugin = ( MAknListBoxTfxPlugin* )
                            REComSession::CreateImplementationL(
                                    implementationUidCtrl,
                                    singleton->iListBoxPluginEComDtorUID ) );
        }
    CWindowGc* ret = NULL;
    if ( singleton && singleton->iListBoxPlugin &&
         singleton->iGcArray.Reserve( singleton->iGcArray.Count() + 1 )
         == KErrNone )
        {
        ret = singleton->iListBoxPlugin->CreateTfxGc( aMenuPane, aTopIndex,
                                                       aItemsThatFitInView );
        if ( ret )
            {
            singleton->iGcArray.Append( ret );
            }
        }
    return ret;
    }
    
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
//
EXPORT_C CWindowGc *CAknListLoader::CreateTfxGc( CAknTreeList& aTreeList,
                                                 TInt& aTopIndex,
                                                 TInt& aBottomIndex,
                                                 TInt& aHighlightIndex,
                                                 TInt& aRows )
    {
    CAknListLoader* singleton = CAknListLoader::Static();
    if( !singleton )
        {
        singleton = new CAknListLoader();
        }

    if ( singleton && ( !singleton->iListBoxPlugin ) )
        {
        // load plugin
        TInt err = KErrNone;
        TUid implementationUidCtrl = { KAknListBoxPluginEcomImpl };

        TRAP( err, singleton->iListBoxPlugin = ( MAknListBoxTfxPlugin* )
                            REComSession::CreateImplementationL(
                                    implementationUidCtrl,
                                    singleton->iListBoxPluginEComDtorUID ) );
        }
    CWindowGc* ret = NULL;
    if ( singleton && singleton->iListBoxPlugin &&
         singleton->iGcArray.Reserve( singleton->iGcArray.Count() + 1 )
         == KErrNone )
        {
        ret = singleton->iListBoxPlugin->CreateTfxGc( aTreeList, aTopIndex,
                                      aBottomIndex, aHighlightIndex, aRows );
        if ( ret )
            {
            singleton->iGcArray.Append( ret );
            }
        }
    return ret;
    }

// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
//
EXPORT_C CWindowGc* CAknListLoader::CreateTfxGc( CCoeControl& aAdapter )
    {
    CAknListLoader* singleton = CAknListLoader::Static();
    if( !singleton )
        {
        singleton = new CAknListLoader();
        }

    if ( singleton && !singleton->iListBoxPlugin )
        {
        // load plugin
        TUid implementationUidCtrl = { KAknListBoxPluginEcomImpl };

        TRAP_IGNORE( singleton->iListBoxPlugin = ( MAknListBoxTfxPlugin* )
                            REComSession::CreateImplementationL(
                                    implementationUidCtrl,
                                    singleton->iListBoxPluginEComDtorUID ) );
        }
    if ( singleton && singleton->iListBoxPlugin &&
         singleton->iGcArray.Reserve( singleton->iGcArray.Count() + 1 )
         == KErrNone )
        {
        CWindowGc* ret = singleton->iListBoxPlugin->CreateTfxGc( aAdapter );
        if ( ret )
            {
            singleton->iGcArray.Append( ret );
            return ret;
            }
        }
    return &aAdapter.SystemGc();
    }

// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknListLoader::RemoveTfxGc ( CWindowGc* aGc )
    {
    CAknListLoader* singleton = CAknListLoader::Static();
    if( singleton )
        {
        TInt index = singleton->iGcArray.Find( aGc );
        if ( index != KErrNotFound )
            {
            singleton->iGcArray.Remove( index );
            }
        }

    }

// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknListLoader::InvalidateAll()
    {
    CAknListLoader* singleton = CAknListLoader::Static();
    if ( singleton )
        {
        for ( TInt i = 0; i < singleton->iGcArray.Count(); i++ )
            {
            MAknListBoxTfxInternal* api = TfxApiInternal( singleton->iGcArray[i] );
            if ( api )
                {
                api->Remove( MAknListBoxTfxInternal:: EListEverything );
                }
            }
        }
    }

#ifdef RD_UI_TRANSITION_EFFECTS_TOUCH_P2
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
//
EXPORT_C TInt CAknListLoader::LongTap( MAknListBoxTfxInternal::TLongTapEvent aEvent,
                                       TInt aDuration, const TPoint* aPoint )
    {
    CAknListLoader* singleton = CAknListLoader::Static();
    if ( singleton )
        {
        for ( TInt i = 0; i < singleton->iGcArray.Count(); i++ )
            {
            MAknListBoxTfxInternal* api =
                TfxApiInternal( singleton->iGcArray[i] );
            if ( api && api->LongTap( aEvent, aDuration, aPoint ) == KErrNone )
                {
                return KErrNone;
                }
            }
        }
    return KErrNotReady;
    }
#endif // RD_UI_TRANSITION_EFFECTS_TOUCH_P2

// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
//
CAknListLoader *CAknListLoader::Static()
    {
    CAknListLoader *singleton = reinterpret_cast<CAknListLoader*>(CCoeEnv::Static(KUid));
    return singleton;
    }

// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
//
CAknListLoader::CAknListLoader() : CCoeStatic(KUid, -1, CCoeStatic::EThread)
    {
    }

// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
//
CAknListLoader::~CAknListLoader()
    {
    iGcArray.ResetAndDestroy();
    if(iListBoxPlugin)
        {
        delete iListBoxPlugin;
        REComSession::DestroyedImplementation( iListBoxPluginEComDtorUID );
        }
    }
