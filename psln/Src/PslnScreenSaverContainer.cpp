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
* Description:  Screen saver view's container.
*
*/



// INCLUDE FILES
#include <aknlists.h>
#include <eikclbd.h>

// Help context.
#include <csxhelp/skins.hlp.hrh>

// Psln specific.
#include <psln.rsg>
#include "PslnModel.h"
#include "PslnScreenSaverContainer.h"
#include "PslnDebug.h"
#include "PslnConst.h"

// Framework
#include <pslnfwiconhelper.h>

// ============================ MEMBER FUNCTIONS ===============================
// -----------------------------------------------------------------------------
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CPslnScreenSaverContainer::CPslnScreenSaverContainer()
    {
    }

// -----------------------------------------------------------------------------
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CPslnScreenSaverContainer::ConstructL( const TRect& aRect )
    {
    iListBox = new (ELeave) CAknSingleGraphicStyleListBox;

    BaseConstructL( aRect, 0 );
    }

// Destructor
CPslnScreenSaverContainer::~CPslnScreenSaverContainer()
    {
    // iListBox is deleted in class CPslnBaseContainer.
    }

// ---------------------------------------------------------------------------
// Updates listbox.
// ---------------------------------------------------------------------------
//
void CPslnScreenSaverContainer::UpdateListBoxL()
    {
    CPslnBaseContainer::UpdateListBoxL();
    }

// -----------------------------------------------------------------------------
// Creates listbox.
// -----------------------------------------------------------------------------
//
void CPslnScreenSaverContainer::ConstructListBoxL( TInt /*aResLbxId*/ )
    {
    CreateListBoxItemsL();
    }

// -----------------------------------------------------------------------------
// Creates items for listbox.
// -----------------------------------------------------------------------------
//
void CPslnScreenSaverContainer::CreateListBoxItemsL()
    {
    PSLN_TRACE_DEBUG("CPslnScreenSaverContainer::CreateListBoxItemsL BEGIN");
    __ASSERT_DEBUG( iModel, User::Panic( _L("Psln"), 1 ) );
    iItemArray->Reset();
    // Find all the screensavers available
    TInt selectedItem = iModel->CurrentPropertyIndexL( KPslnScreenSettingId );
    if ( selectedItem < 0 )
        {
        selectedItem = 0;
        }

    const MDesC16Array& ssNames = iModel->ScreensaverNames();
    for( TInt i = 0; i < ssNames.MdcaCount(); i++ )
        {
        HBufC* itemBuf = ssNames.MdcaPoint( i ).AllocL();
        if ( itemBuf )
            {
            PSLN_TRACE_DEBUG("CPslnScreenSaverContainer::CreateListBoxItemsL 2");
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
            if ( iModel->IsScreenSaverOnMemoryCard( i ) )
                {
                ptr.Append( KPslnFWListItemFormatMMCSuffix );
                }
            else if ( iModel->IsScreenSaverOnMassDrive( i ) )
                {
                ptr.Append( KPslnFWListItemFormatMassDriveSuffix );
                }
            iItemArray->InsertL( i, ptr );
            delete itemBuf;
            }
        }
    iListBox->HandleItemAdditionL();

    // Create pre- and post-text icons.
    CPslnFWIconHelper* iconHelper = CPslnFWIconHelper::NewL();
    CleanupStack::PushL( iconHelper );
    iconHelper->AddIconsToSettingItemsL(
        ETrue,
        KErrNotFound,
        iListBox );
    CleanupStack::PopAndDestroy( iconHelper );
    DrawDeferred();
    PSLN_TRACE_DEBUG("CPslnScreenSaverContainer::CreateListBoxItemsL END");
    }

// ---------------------------------------------------------------------------
// Gets help context for Help application.
// ---------------------------------------------------------------------------
//
void CPslnScreenSaverContainer::GetHelpContext(
    TCoeHelpContext& aContext ) const
    {
    aContext.iMajor = KUidPsln;
    aContext.iContext = KSKINS_HLP_SCREENS_SETTINGS;
    }

//  End of File
