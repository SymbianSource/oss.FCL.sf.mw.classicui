/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description: Marking mode handler.
*
*/

#include <akncollection.h>
#include <aknitemactionmenu.h>
#include <eikspane.h>
#include <aknnavide.h>
#include <barsread.h>
#include <AknUtils.h>
#include <AknTasHook.h>

#include "akntrace.h"
#include "aknmarkingmode.h"

// ---------------------------------------------------------------------------
// CAknMarkingMode::NewL
// ---------------------------------------------------------------------------
//
CAknMarkingMode* CAknMarkingMode::NewL(
        CAknItemActionMenu& aItemActionMenu,
        CollectionArray& aArray )
    {
    _AKNTRACE_FUNC_ENTER;
    CAknMarkingMode* self =
        new ( ELeave ) CAknMarkingMode( aItemActionMenu, aArray );
    _AKNTRACE_FUNC_EXIT;
    return self;
    }


// ---------------------------------------------------------------------------
// CAknMarkingMode::~CAknMarkingMode
// ---------------------------------------------------------------------------
//
CAknMarkingMode::~CAknMarkingMode()
    {
    _AKNTRACE_FUNC_ENTER;
    AKNTASHOOK_REMOVE();    
    delete iMarkingDecorator;
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// CAknMarkingMode::SetCollectionMultipleMarkingState
// ---------------------------------------------------------------------------
//
void CAknMarkingMode::SetCollectionMultipleMarkingState( TBool aActive )
    {
    _AKNTRACE_FUNC_ENTER;
    for ( TInt i = 0; i < iCollections.Count(); i++ )
        {
        MAknCollection* collection( iCollections[i] );
        // Assume the command applies to first list with multiple selection
        if ( collection->CollectionState() &
                MAknCollection::EStateMultipleSelection )
            {
            MAknMarkingCollection* markingCollection
                = MarkingCollection( *collection );
            if ( markingCollection )
                {
                markingCollection->SetMultipleMarkingState( aActive );
                TRAP_IGNORE( UpdateMarkingModeNaviPaneL( aActive ) );
                }
            iItemActionMenu.CollectionChanged( *collection );
            break;
            }
        }
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// CAknMarkingMode::TryExitMarkingMode
// ---------------------------------------------------------------------------
//
void CAknMarkingMode::TryExitMarkingMode()
    {
    _AKNTRACE_FUNC_ENTER;
    for ( TInt i = 0; i < iCollections.Count(); i++ )
        {
        MAknCollection* collection( iCollections[i] );
        MAknMarkingCollection* markingCollection
            = MarkingCollection( *collection );
        if ( markingCollection && markingCollection->MarkingState(
                ) & MAknMarkingCollection::EStateMarkingMode )
            {
            if ( markingCollection->ExitMarkingMode() )
                {
                SetCollectionMultipleMarkingState( EFalse );
                }
            }
        break;
        }
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// CAknMarkingMode::MultipleMarkingActive
// ---------------------------------------------------------------------------
//
TBool CAknMarkingMode::MultipleMarkingActive() const
    {
    _AKNTRACE_FUNC_ENTER;
    TBool markingActive( EFalse );
    for ( TInt i = 0; i < iCollections.Count(); i++ )
        {
        MAknCollection* collection( iCollections[i] );
        if ( collection->CollectionState() &
                MAknCollection::EStateCollectionVisible )
            {
            MAknMarkingCollection* markingCollection
                = MarkingCollection( *collection );
            if ( markingCollection )
                {
                markingActive = markingCollection->MarkingState()
                    & MAknMarkingCollection::EStateMarkingMode;
                }
            break;
            }
        }
    _AKNTRACE_FUNC_EXIT;
    return markingActive;
    }


// ---------------------------------------------------------------------------
// CAknMarkingMode::MarkedItems
// ---------------------------------------------------------------------------
//
TBool CAknMarkingMode::MarkedItems() const
    {
    _AKNTRACE_FUNC_ENTER;
    TBool markedItems( EFalse );
    for ( TInt i = 0; i < iCollections.Count(); i++ )
        {
        MAknCollection* collection( iCollections[i] );
        if ( collection->CollectionState() &
                MAknCollection::EStateCollectionVisible )
            {
            MAknMarkingCollection* markingCollection
                = MarkingCollection( *collection );
            if ( markingCollection )
                {
                TInt markingState = markingCollection->MarkingState();
                if ( markingState &
                        MAknMarkingCollection::EStateMarkingMode )
                    {
                    markedItems = markingState
                        & MAknMarkingCollection::EStateMarkedItems;
                    }
                }
            break;
            }
        }
    _AKNTRACE_FUNC_EXIT;
    return markedItems;
    }

// ---------------------------------------------------------------------------
// CAknMarkingMode::CollectionEmpty
// ---------------------------------------------------------------------------
//
TBool CAknMarkingMode::CollectionEmpty() const
    {
    _AKNTRACE_FUNC_ENTER;
    TBool empty( EFalse );
     for ( TInt i = 0; i < iCollections.Count(); i++ )
         {
         MAknCollection* collection( iCollections[i] );
         if ( collection->CollectionState() &
                 MAknCollection::EStateCollectionVisible )
             {
             MAknMarkingCollection* markingCollection
                 = MarkingCollection( *collection );
             if ( markingCollection )
                 {
                 TInt markingState = markingCollection->MarkingState();
                 if ( markingState &
                         MAknMarkingCollection::EStateMarkingMode )
                     {
                     empty = markingState
                         & MAknMarkingCollection::EStateCollectionEmpty;
                     }
                 }
             break;
             }
         }
     _AKNTRACE_FUNC_EXIT;
    return empty;    
    }


// ---------------------------------------------------------------------------
// CAknMarkingMode::MarkAllL
// ---------------------------------------------------------------------------
//
void CAknMarkingMode::MarkAllL()
    {
    _AKNTRACE_FUNC_ENTER;
    MAknMarkingCollection* collection = ActiveMarkingCollection();
    
    if ( collection )
        {
        collection->MarkAllL();
        }
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// CAknMarkingMode::UnmarkAll
// ---------------------------------------------------------------------------
//
void CAknMarkingMode::UnmarkAll()
    {
    _AKNTRACE_FUNC_ENTER;
    MAknMarkingCollection* collection = ActiveMarkingCollection();
    
    if ( collection )
        {
        collection->UnmarkAll();
        }
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// CAknMarkingMode::MarkCurrentItemL
// ---------------------------------------------------------------------------
//
void CAknMarkingMode::MarkCurrentItemL()
    {
    _AKNTRACE_FUNC_ENTER;
    MAknMarkingCollection* collection = ActiveMarkingCollection();
    
    // first activate marking mode if needed
    if ( !collection )
        {
        SetCollectionMultipleMarkingState( ETrue );
        collection = ActiveMarkingCollection();
        }

    // then mark the current item
    if ( collection )
        {
        collection->MarkCurrentItemL();
        }
    _AKNTRACE_FUNC_EXIT;
    }

// ---------------------------------------------------------------------------
// CAknMarkingMode::CurrentItemMarkable
// ---------------------------------------------------------------------------
//
TBool CAknMarkingMode::CurrentItemMarkable()
    {
    _AKNTRACE_FUNC_ENTER;
    _AKNTRACE_FUNC_EXIT;
    return MarkingCollection()->CurrentItemMarkable();
    }

// ---------------------------------------------------------------------------
// CAknMarkingMode::CAknMarkingMode
// ---------------------------------------------------------------------------
//
CAknMarkingMode::CAknMarkingMode(
        CAknItemActionMenu& aItemActionMenu,
        CollectionArray& aArray )
    : iCollections( aArray ),
    iItemActionMenu( aItemActionMenu ),
    iMarkingDecorator( NULL )
    {
    _AKNTRACE_FUNC_ENTER;
    AKNTASHOOK_ADD( this, "CAknMarkingMode" );
    _AKNTRACE_FUNC_EXIT;    
    }


// ---------------------------------------------------------------------------
// CAknMarkingMode::MarkingCollection
// ---------------------------------------------------------------------------
//
MAknMarkingCollection* CAknMarkingMode::MarkingCollection(
        MAknCollection& aCollection )
    {
    _AKNTRACE_FUNC_ENTER;
    TAny* extension( NULL );
    aCollection.CollectionExtension(
            MAknMarkingCollection::TYPE, extension, NULL );
    _AKNTRACE_FUNC_EXIT;
    return static_cast<MAknMarkingCollection*>( extension );
    }


// ---------------------------------------------------------------------------
// CAknMarkingMode::MarkingCollection
// ---------------------------------------------------------------------------
//
MAknMarkingCollection* CAknMarkingMode::MarkingCollection()
    {
    _AKNTRACE_FUNC_ENTER;
    for ( TInt i = 0; i < iCollections.Count(); i++ )
        {
        MAknCollection* collection( iCollections[i] );    
        if ( collection->CollectionState() &
                MAknCollection::EStateCollectionVisible )
            {
            _AKNTRACE_FUNC_EXIT;
            return MarkingCollection( *collection );
            }
        }
    _AKNTRACE_FUNC_EXIT;
    return NULL;
    }


// ---------------------------------------------------------------------------
// CAknMarkingMode::ActiveMarkingCollection
// ---------------------------------------------------------------------------
//
MAknMarkingCollection* CAknMarkingMode::ActiveMarkingCollection()
    {
    _AKNTRACE_FUNC_ENTER;
    for ( TInt i = 0; i < iCollections.Count(); i++ )
        {
        MAknCollection* collection( iCollections[i] );
        
        MAknMarkingCollection* markingCollection = 
                MarkingCollection( *collection );
        
        if ( markingCollection && markingCollection->MarkingState() & 
                MAknMarkingCollection::EStateMarkingMode )
            {
            _AKNTRACE_FUNC_EXIT;
            return markingCollection;
            }
        }
    _AKNTRACE_FUNC_EXIT;
    return NULL;
    }

// ---------------------------------------------------------------------------
// CAknMarkingMode::UpdateMarkingModeNaviPaneL
// ---------------------------------------------------------------------------
//
void CAknMarkingMode::UpdateMarkingModeNaviPaneL( TBool aEnable )
    {
    _AKNTRACE_FUNC_ENTER;
    CEikonEnv* eikonEnv = CEikonEnv::Static();
        
    if ( eikonEnv && eikonEnv->AppUiFactory() )
        {
        CEikStatusPane* statusPane = eikonEnv->AppUiFactory()->StatusPane();

        if ( statusPane )
            {
            // get navi pane
            CAknNavigationControlContainer* naviPane =
                    (CAknNavigationControlContainer *)statusPane->ControlL(
                            TUid::Uid(EEikStatusPaneUidNavi));
            if ( naviPane )
                {
                if ( !iMarkingDecorator )
                    {
                    TResourceReader reader;
                    eikonEnv->CreateResourceReaderLC( 
                            reader, R_MARKING_MODE_NAVI_PANE );
    
                    iMarkingDecorator = naviPane->CreateNavigationLabelL( 
                                reader );
                    CleanupStack::PopAndDestroy(); // reader
                    }
    
                if ( aEnable ) 
                    {
                    naviPane->PushL( *iMarkingDecorator ); 
                    }
                else 
                    {
                    naviPane->Pop( iMarkingDecorator ); 
                    }
                naviPane->DrawDeferred();
                }
            }
        }
    _AKNTRACE_FUNC_EXIT;
    }

// End of File
