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

#include "aknmarkingmode.h"

// ---------------------------------------------------------------------------
// CAknMarkingMode::NewL
// ---------------------------------------------------------------------------
//
CAknMarkingMode* CAknMarkingMode::NewL(
        CAknItemActionMenu& aItemActionMenu,
        CollectionArray& aArray )
    {
    CAknMarkingMode* self =
        new ( ELeave ) CAknMarkingMode( aItemActionMenu, aArray );
    return self;
    }


// ---------------------------------------------------------------------------
// CAknMarkingMode::~CAknMarkingMode
// ---------------------------------------------------------------------------
//
CAknMarkingMode::~CAknMarkingMode()
    {
    delete iMarkingDecorator;
    }


// ---------------------------------------------------------------------------
// CAknMarkingMode::SetCollectionMultipleMarkingState
// ---------------------------------------------------------------------------
//
void CAknMarkingMode::SetCollectionMultipleMarkingState( TBool aActive )
    {
    for ( TInt i = 0; i < iCollections.Count(); i++ )
        {
        MAknCollection* collection( iCollections[ i ] );
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
    }


// ---------------------------------------------------------------------------
// CAknMarkingMode::TryExitMarkingMode
// ---------------------------------------------------------------------------
//
void CAknMarkingMode::TryExitMarkingMode()
    {
    for ( TInt i = 0; i < iCollections.Count(); i++ )
        {
        MAknCollection* collection( iCollections[ i ] );
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
    }


// ---------------------------------------------------------------------------
// CAknMarkingMode::MultipleMarkingActive
// ---------------------------------------------------------------------------
//
TBool CAknMarkingMode::MultipleMarkingActive() const
    {
    TBool markingActive( EFalse );
    for ( TInt i = 0; i < iCollections.Count(); i++ )
        {
        MAknCollection* collection( iCollections[ i ] );
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
    return markingActive;
    }


// ---------------------------------------------------------------------------
// CAknMarkingMode::MarkedItems
// ---------------------------------------------------------------------------
//
TBool CAknMarkingMode::MarkedItems() const
    {
    TBool markedItems( EFalse );
    for ( TInt i = 0; i < iCollections.Count(); i++ )
        {
        MAknCollection* collection( iCollections[ i ] );
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
    return markedItems;
    }

// ---------------------------------------------------------------------------
// CAknMarkingMode::CollectionEmpty
// ---------------------------------------------------------------------------
//
TBool CAknMarkingMode::CollectionEmpty() const
    {
    TBool empty( EFalse );
     for ( TInt i = 0; i < iCollections.Count(); i++ )
         {
         MAknCollection* collection( iCollections[ i ] );
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
    return empty;    
    }


// ---------------------------------------------------------------------------
// CAknMarkingMode::MarkAllL
// ---------------------------------------------------------------------------
//
void CAknMarkingMode::MarkAllL()
    {
    MAknMarkingCollection* collection = ActiveMarkingCollection();
    
    if ( collection )
        {
        collection->MarkAllL();
        }
    }


// ---------------------------------------------------------------------------
// CAknMarkingMode::UnmarkAll
// ---------------------------------------------------------------------------
//
void CAknMarkingMode::UnmarkAll()
    {
    MAknMarkingCollection* collection = ActiveMarkingCollection();
    
    if ( collection )
        {
        collection->UnmarkAll();
        }
    }


// ---------------------------------------------------------------------------
// CAknMarkingMode::MarkCurrentItemL
// ---------------------------------------------------------------------------
//
void CAknMarkingMode::MarkCurrentItemL()
    {
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
    }

// ---------------------------------------------------------------------------
// CAknMarkingMode::CurrentItemMarkable
// ---------------------------------------------------------------------------
//
TBool CAknMarkingMode::CurrentItemMarkable()
    {
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
    }


// ---------------------------------------------------------------------------
// CAknMarkingMode::MarkingCollection
// ---------------------------------------------------------------------------
//
MAknMarkingCollection* CAknMarkingMode::MarkingCollection(
        MAknCollection& aCollection )
    {
    TAny* extension( NULL );
    aCollection.CollectionExtension(
            MAknMarkingCollection::TYPE, extension, NULL );
    return static_cast<MAknMarkingCollection*>( extension );
    }


// ---------------------------------------------------------------------------
// CAknMarkingMode::MarkingCollection
// ---------------------------------------------------------------------------
//
MAknMarkingCollection* CAknMarkingMode::MarkingCollection()
    {
    for ( TInt i = 0; i < iCollections.Count(); i++ )
        {
        MAknCollection* collection( iCollections[ i ] );
        if ( collection->CollectionState() &
                MAknCollection::EStateCollectionVisible )
            {
            return MarkingCollection( *collection );
            }
        }

    return NULL;
    }


// ---------------------------------------------------------------------------
// CAknMarkingMode::ActiveMarkingCollection
// ---------------------------------------------------------------------------
//
MAknMarkingCollection* CAknMarkingMode::ActiveMarkingCollection()
    {
    for ( TInt i = 0; i < iCollections.Count(); i++ )
        {
        MAknCollection* collection( iCollections[ i ] );
        
        MAknMarkingCollection* markingCollection = 
                MarkingCollection( *collection );
        
        if ( markingCollection && markingCollection->MarkingState() & 
                MAknMarkingCollection::EStateMarkingMode )
            {
            return markingCollection;
            }
        }

    return NULL;
    }

// ---------------------------------------------------------------------------
// CAknMarkingMode::UpdateMarkingModeNaviPaneL
// ---------------------------------------------------------------------------
//
void CAknMarkingMode::UpdateMarkingModeNaviPaneL( TBool aEnable )
    {
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
    }

// End of File
