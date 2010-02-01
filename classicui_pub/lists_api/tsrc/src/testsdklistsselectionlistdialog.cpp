/*
* Copyright (c) 2002 - 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  
*
*/

#include <aknselectionlist.h>

#include "testsdklistsselectionlistdialog.h"

// ============================ MEMBER FUNCTIONS ===============================
// -----------------------------------------------------------------------------
// CTestSDKListsSelectionListDialog::CTestSDKListsSelectionListDialog
// -----------------------------------------------------------------------------
//
CTestSDKListsSelectionListDialog::CTestSDKListsSelectionListDialog
    ( TInt &aIndex, MDesCArray *aArray, MEikCommandObserver *aCommand ) :
    CAknSelectionListDialog::CAknSelectionListDialog( aIndex, aArray, aCommand )
    {
    
    }

// -----------------------------------------------------------------------------
// CTestSDKListsSelectionListDialog::~CTestSDKListsSelectionListDialog
// -----------------------------------------------------------------------------
//
CTestSDKListsSelectionListDialog::~CTestSDKListsSelectionListDialog()
    {
    
    }

// -----------------------------------------------------------------------------
// CTestSDKListsSelectionListDialog::SelectionListProcessCommandL
// -----------------------------------------------------------------------------
//
void CTestSDKListsSelectionListDialog::SelectionListProcessCommandL( TInt aCommand )
    {
    CAknSelectionListDialog::SelectionListProcessCommandL( aCommand );
    }

// -----------------------------------------------------------------------------
// CTestSDKListsSelectionListDialog::IsAcceptableListBoxType
// -----------------------------------------------------------------------------
//
TBool CTestSDKListsSelectionListDialog::IsAcceptableListBoxType
    ( TInt aControlType, TBool &aIsFormattedCellList ) const
    {
    return CAknSelectionListDialog::IsAcceptableListBoxType( aControlType, aIsFormattedCellList );
    }

// -----------------------------------------------------------------------------
// CTestSDKListsSelectionListDialog::ProcessCommandL
// -----------------------------------------------------------------------------
//
void CTestSDKListsSelectionListDialog::ProcessCommandL( TInt aCommandId )
    {
    CAknSelectionListDialog::ProcessCommandL( aCommandId );
    }

// -----------------------------------------------------------------------------
// CTestSDKListsSelectionListDialog::PreLayoutDynInitL
// -----------------------------------------------------------------------------
//
void CTestSDKListsSelectionListDialog::PreLayoutDynInitL()
    {
    CAknSelectionListDialog::PreLayoutDynInitL();
    }

// -----------------------------------------------------------------------------
// CTestSDKListsSelectionListDialog::PostLayoutDynInitL
// -----------------------------------------------------------------------------
//
void CTestSDKListsSelectionListDialog::PostLayoutDynInitL()
    {
    CAknSelectionListDialog::PostLayoutDynInitL();
    }

// -----------------------------------------------------------------------------
// CTestSDKListsSelectionListDialog::SetSizeAndPosition
// -----------------------------------------------------------------------------
//
void CTestSDKListsSelectionListDialog::SetSizeAndPosition(const TSize &aSize)
    {
    CAknSelectionListDialog::SetSizeAndPosition( aSize );
    }

// -----------------------------------------------------------------------------
// CTestSDKListsSelectionListDialog::OkToExitL
// -----------------------------------------------------------------------------
//
TBool CTestSDKListsSelectionListDialog::OkToExitL( TInt aButtonId )
    {
    return CAknSelectionListDialog::OkToExitL( aButtonId );
    }

// -----------------------------------------------------------------------------
// CTestSDKListsSelectionListDialog::HandleListBoxEventL
// -----------------------------------------------------------------------------
//
void CTestSDKListsSelectionListDialog::HandleListBoxEventL
    ( CEikListBox* aListBox, TListBoxEvent aEventType )
    {
    CAknSelectionListDialog::HandleListBoxEventL( aListBox, aEventType );
    }

// -----------------------------------------------------------------------------
// CTestSDKListsSelectionListDialog::CountComponentControls
// -----------------------------------------------------------------------------
//
TInt CTestSDKListsSelectionListDialog::CountComponentControls() const
    {
    return CAknSelectionListDialog::CountComponentControls();
    }

// -----------------------------------------------------------------------------
// CTestSDKListsSelectionListDialog::ComponentControl
// -----------------------------------------------------------------------------
//
CCoeControl* CTestSDKListsSelectionListDialog::ComponentControl( TInt aIndex ) const
    {
    return CAknSelectionListDialog::ComponentControl( aIndex );
    }

// -----------------------------------------------------------------------------
// CTestSDKListsSelectionListDialog::OfferKeyEventL
// -----------------------------------------------------------------------------
//
TKeyResponse CTestSDKListsSelectionListDialog::OfferKeyEventL
    ( const TKeyEvent& aKeyEvent, TEventCode aType )
    {
    return CAknSelectionListDialog::OfferKeyEventL( aKeyEvent, aType );
    }

// -----------------------------------------------------------------------------
// CTestSDKListsSelectionListDialog::CreateCustomControlL
// -----------------------------------------------------------------------------
//
SEikControlInfo CTestSDKListsSelectionListDialog::CreateCustomControlL(TInt aControlType)
    {
    return CAknSelectionListDialog::CreateCustomControlL( aControlType );
    }

// -----------------------------------------------------------------------------
// CTestSDKListsSelectionListDialog::ListBox
// -----------------------------------------------------------------------------
//
CEikListBox* CTestSDKListsSelectionListDialog::ListBox() const
    {
    return CAknSelectionListDialog::ListBox();
    }

// -----------------------------------------------------------------------------
// CTestSDKListsSelectionListDialog::FindBox
// -----------------------------------------------------------------------------
//
CAknSearchField* CTestSDKListsSelectionListDialog::FindBox() const
    {
    return CAknSelectionListDialog::FindBox();
    }

// -----------------------------------------------------------------------------
// CTestSDKListsSelectionListDialog::IsFormattedCellListBox
// -----------------------------------------------------------------------------
//
TBool CTestSDKListsSelectionListDialog::IsFormattedCellListBox() const
    {
    return CAknSelectionListDialog::IsFormattedCellListBox();
    }

// -----------------------------------------------------------------------------
// CTestSDKListsSelectionListDialog::Draw
// -----------------------------------------------------------------------------
//
void CTestSDKListsSelectionListDialog::Draw(const TRect& aRect) const
    {
    CAknSelectionListDialog::Draw( aRect );
    }
