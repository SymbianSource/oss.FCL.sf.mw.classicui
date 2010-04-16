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
* Description: Item action menu register array.
*
*/
#include <akncollection.h>
#include <aknitemactionmenu.h>
#include <eikmenub.h>

#include "aknitemactionmenuregisterarray.h"

// ---------------------------------------------------------------------------
// CCAknItemActionMenuRegisterArray::NewL
// ---------------------------------------------------------------------------
//
CAknItemActionMenuRegisterArray* CAknItemActionMenuRegisterArray::NewL()
    {
    CAknItemActionMenuRegisterArray* self =
        CAknItemActionMenuRegisterArray::NewLC();
    CleanupStack::Pop( self );
    return self;
    }


// ---------------------------------------------------------------------------
// CCAknItemActionMenuRegisterArray::NewLC
// ---------------------------------------------------------------------------
//
CAknItemActionMenuRegisterArray* CAknItemActionMenuRegisterArray::NewLC()
    {
    CAknItemActionMenuRegisterArray* self =
        new ( ELeave ) CAknItemActionMenuRegisterArray();
    CleanupStack::PushL( self );
    return self;
    }


// ---------------------------------------------------------------------------
// CAknItemActionMenuRegisterArray::~CAknItemActionMenuRegisterArray
// ---------------------------------------------------------------------------
//
CAknItemActionMenuRegisterArray::~CAknItemActionMenuRegisterArray()
    {
    iRegisterArray.ResetAndDestroy();
    iRegisterArray.Close();
    }


// ---------------------------------------------------------------------------
// CAknItemActionMenuRegisterArray::AddEntryL
// ---------------------------------------------------------------------------
//
void CAknItemActionMenuRegisterArray::AddEntryL(
        CEikMenuBar& aMenuBar, CAknItemActionMenu& aItemActionMenu )
    {
    CRegisterEntry* newEntry = CRegisterEntry::NewLC(
            aMenuBar, aItemActionMenu );
    iRegisterArray.AppendL( newEntry );
    CleanupStack::Pop( newEntry );
    }


// ---------------------------------------------------------------------------
// CAknItemActionMenuRegisterArray::UnregisterMenuBar
// ---------------------------------------------------------------------------
//
void CAknItemActionMenuRegisterArray::UnregisterMenuBar(
        CEikMenuBar& aMenuBar )
    {
    CRegisterEntry* entry( NULL );
    for ( TInt i = 0; i < iRegisterArray.Count(); i++ )
        {
        entry = iRegisterArray[ i ];
        if ( entry->MenuBar() == &aMenuBar )
            {
            entry->RemoveMenuBar();
            // Remove entry if there are no more collections
            if ( entry->ItemActionMenu()->CollectionCount() )
                {
                entry->ItemActionMenu()->SetMenuBar( NULL, NULL );
                }
            else
                {
                RemoveEntry( i );
                }
            break;
            }
        }
    }


// ---------------------------------------------------------------------------
// CAknItemActionMenuRegisterArray::UnregisterItemActionMenu
// ---------------------------------------------------------------------------
//
void CAknItemActionMenuRegisterArray::UnregisterItemActionMenu(
        CAknItemActionMenu& aItemActionMenu )
    {
    CRegisterEntry* entry( NULL );
    for ( TInt i = 0; i < iRegisterArray.Count(); i++ )
        {
        entry = iRegisterArray[ i ];
        if ( entry->ItemActionMenu() == &aItemActionMenu )
            {
            // Remove entry only if menu bar is already removed
            if ( !entry->MenuBar() )
                {
                RemoveEntry( i );
                }
            break;
            }
        }
    }


// ---------------------------------------------------------------------------
// CAknItemActionMenuRegisterArray::RegisterCollectionObserverL
// ---------------------------------------------------------------------------
//
TBool CAknItemActionMenuRegisterArray::RegisterCollectionObserverL(
        CEikMenuBar& aMenuBar, MAknCollectionObserver& aObserver )
    {
    TBool menuBarFound( EFalse );
    CRegisterEntry* entry( NULL );
    for ( TInt i = 0; i < iRegisterArray.Count(); i++ )
        {
        entry = iRegisterArray[ i ];
        if ( entry->MenuBar() == &aMenuBar )
            {
            if ( entry->ItemActionMenu() )
                {
                entry->ItemActionMenu()->RegisterCollectionObserverL(
                        aObserver );
                }
            menuBarFound = ETrue;
            break;
            }
        }
    return menuBarFound;
    }


// ---------------------------------------------------------------------------
// CAknItemActionMenuRegisterArray::UnregisterCollectionObserver
// ---------------------------------------------------------------------------
//
void CAknItemActionMenuRegisterArray::UnregisterCollectionObserver(
        MAknCollectionObserver& aObserver )
    {
    CRegisterEntry* entry( NULL );
    for ( TInt i = 0; i < iRegisterArray.Count(); i++ )
        {
        entry = iRegisterArray[ i ];
        if ( entry->ItemActionMenu() )
            {
            entry->ItemActionMenu()->RemoveCollectionObserver( aObserver );
            }
        }
    }


// ---------------------------------------------------------------------------
// CAknItemActionMenuRegisterArray::CAknItemActionMenuRegisterArray
// ---------------------------------------------------------------------------
//
CAknItemActionMenuRegisterArray::CAknItemActionMenuRegisterArray()
    {
    }


// ---------------------------------------------------------------------------
// CAknItemActionMenuRegisterArray::ConstructL
// ---------------------------------------------------------------------------
//
void CAknItemActionMenuRegisterArray::ConstructL()
    {
    }


// ---------------------------------------------------------------------------
// CAknItemActionMenuRegisterArray::RemoveEntry
// ---------------------------------------------------------------------------
//
void CAknItemActionMenuRegisterArray::RemoveEntry( TInt aIndex )
    {
    if ( aIndex >= 0 && aIndex < iRegisterArray.Count() )
        {
        CRegisterEntry* entry = iRegisterArray[ aIndex ];
        delete entry;
        entry = NULL;
        iRegisterArray.Remove( aIndex );
        }
    }


// ---------------------------------------------------------------------------
// CCAknItemActionMenuRegisterArray::CRegisterEntry::NewL
// ---------------------------------------------------------------------------
//
CAknItemActionMenuRegisterArray::CRegisterEntry*
    CAknItemActionMenuRegisterArray::CRegisterEntry::NewL(
            CEikMenuBar& aMenuBar, CAknItemActionMenu& aItemActionMenu )
    {
    CRegisterEntry* self = CRegisterEntry::NewLC( aMenuBar, aItemActionMenu );
    CleanupStack::Pop( self );
    return self;
    }


// ---------------------------------------------------------------------------
// CCAknItemActionMenuRegisterArray::CRegisterEntry::NewLC
// ---------------------------------------------------------------------------
//
CAknItemActionMenuRegisterArray::CRegisterEntry*
    CAknItemActionMenuRegisterArray::CRegisterEntry::NewLC(
            CEikMenuBar& aMenuBar, CAknItemActionMenu& aItemActionMenu )
    {
    CRegisterEntry* self =
        new ( ELeave ) CRegisterEntry( aMenuBar, aItemActionMenu );
    CleanupStack::PushL( self );
    return self;
    }


// ---------------------------------------------------------------------------
// CAknItemActionMenuRegisterArray::CRegisterEntry::~CRegisterEntry
// ---------------------------------------------------------------------------
//
CAknItemActionMenuRegisterArray::CRegisterEntry::~CRegisterEntry()
    {
    delete iActionMenu;
    }


// ---------------------------------------------------------------------------
// CAknItemActionMenuRegisterArray::CRegisterEntry::RemoveMenuBar
// ---------------------------------------------------------------------------
//
void CAknItemActionMenuRegisterArray::CRegisterEntry::RemoveMenuBar()
    {
    iMenuBar = NULL;
    }


// ---------------------------------------------------------------------------
// CAknItemActionMenuRegisterArray::CRegisterEntry::MenuBar
// ---------------------------------------------------------------------------
//
CEikMenuBar* CAknItemActionMenuRegisterArray::CRegisterEntry::MenuBar()
    {
    return iMenuBar;
    }


// ---------------------------------------------------------------------------
// CAknItemActionMenuRegisterArray::CRegisterEntry::RemoveItemActionMenu
// ---------------------------------------------------------------------------
//
void CAknItemActionMenuRegisterArray::CRegisterEntry::RemoveItemActionMenu()
    {
    delete iActionMenu;
    iActionMenu = NULL;
    }


// ---------------------------------------------------------------------------
// CAknItemActionMenuRegisterArray::CRegisterEntry::ItemActionMenu
// ---------------------------------------------------------------------------
//
CAknItemActionMenu*
    CAknItemActionMenuRegisterArray::CRegisterEntry::ItemActionMenu()
    {
    return iActionMenu;
    }


// ---------------------------------------------------------------------------
// CAknItemActionMenuRegisterArray::CRegisterEntry::CRegisterEntry
// ---------------------------------------------------------------------------
//
CAknItemActionMenuRegisterArray::CRegisterEntry::CRegisterEntry(
        CEikMenuBar& aMenuBar, CAknItemActionMenu& aItemActionMenu )
    : iMenuBar( &aMenuBar ),
    iActionMenu( &aItemActionMenu )
    {
    }


// ---------------------------------------------------------------------------
// CAknItemActionMenuRegisterArray::CRegisterEntry::ConstructL
// ---------------------------------------------------------------------------
//
void CAknItemActionMenuRegisterArray::CRegisterEntry::ConstructL()
    {
    }

// End of File
