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
#include "testsdklistsmarkablelistdialog.h"

// ============================ MEMBER FUNCTIONS ===============================
// -----------------------------------------------------------------------------
// CTestSDKListsMarkableListDialog::CTestSDKListsMarkableListDialog
// -----------------------------------------------------------------------------
//
CTestSDKListsMarkableListDialog::CTestSDKListsMarkableListDialog( TInt &aOpenedItem,
                                                                  CArrayFix<TInt> *aSelectedItems,
                                                                  MDesCArray *aArray,
                                                                  TInt aMenuBarResourceId,
                                                                  TInt aOkMenuBarResourceId,
                                                                  MEikCommandObserver *aObserver ) :
                                          CAknMarkableListDialog( aOpenedItem,
                                                                  aSelectedItems,
                                                                  aArray,
                                                                  aMenuBarResourceId,
                                                                  aOkMenuBarResourceId,
                                                                  aObserver )
    {
    }

// -----------------------------------------------------------------------------
// CTestSDKListsMarkableListDialog::CTestSDKListsMarkableListDialog
// -----------------------------------------------------------------------------
//
CTestSDKListsMarkableListDialog::CTestSDKListsMarkableListDialog( TInt &aOpenedItem,
                                                                  CArrayFix<TInt> *aSelectedItems,
                                                                  MDesCArray *aArray,
                                                                  MEikCommandObserver *aObserver ) :
                                          CAknMarkableListDialog( aOpenedItem,
                                                                  aSelectedItems,
                                                                  aArray,
                                                                  aObserver )
    {
    }

// -----------------------------------------------------------------------------
// CTestSDKListsMarkableListDialog::~CTestSDKListsMarkableListDialog
// -----------------------------------------------------------------------------
//
CTestSDKListsMarkableListDialog::~CTestSDKListsMarkableListDialog()
    {
    }

// -----------------------------------------------------------------------------
// CTestSDKListsMarkableListDialog::PreLayoutDynInitL
// -----------------------------------------------------------------------------
//
void CTestSDKListsMarkableListDialog::PreLayoutDynInitL()
    {
    CAknMarkableListDialog::PreLayoutDynInitL();
    }

// -----------------------------------------------------------------------------
// CTestSDKListsMarkableListDialog::PostLayoutDynInitL
// -----------------------------------------------------------------------------
//
void CTestSDKListsMarkableListDialog::PostLayoutDynInitL()
    {
    CAknMarkableListDialog::PostLayoutDynInitL();
    }

// -----------------------------------------------------------------------------
// CTestSDKListsMarkableListDialog::SelectionListProcessCommandL
// -----------------------------------------------------------------------------
//
void CTestSDKListsMarkableListDialog::SelectionListProcessCommandL(TInt aCommand)
    {
    CAknMarkableListDialog::SelectionListProcessCommandL( aCommand );
    }

// -----------------------------------------------------------------------------
// CTestSDKListsMarkableListDialog::ProcessCommandL
// -----------------------------------------------------------------------------
//
void CTestSDKListsMarkableListDialog::ProcessCommandL(TInt aCommand)
    {
    CAknMarkableListDialog::ProcessCommandL( aCommand );
    }

// -----------------------------------------------------------------------------
// CTestSDKListsMarkableListDialog::DynInitMenuPaneL
// -----------------------------------------------------------------------------
//
void CTestSDKListsMarkableListDialog::DynInitMenuPaneL(TInt aResourceId, CEikMenuPane *aMenuPane)
    {
    CAknMarkableListDialog::DynInitMenuPaneL( aResourceId, aMenuPane );
    }

// -----------------------------------------------------------------------------
// CTestSDKListsMarkableListDialog::HandleListBoxEventL
// -----------------------------------------------------------------------------
//
void CTestSDKListsMarkableListDialog::HandleListBoxEventL( CEikListBox* aListBox, TListBoxEvent aEventType )
    {
    CAknMarkableListDialog::HandleListBoxEventL( aListBox, aEventType );
    }

// -----------------------------------------------------------------------------
// CTestSDKListsMarkableListDialog::OfferKeyEventL
// -----------------------------------------------------------------------------
//
TKeyResponse CTestSDKListsMarkableListDialog::OfferKeyEventL( const TKeyEvent& aKeyEvent, TEventCode aType )
    {
    return CAknMarkableListDialog::OfferKeyEventL( aKeyEvent, aType );
    }

// -----------------------------------------------------------------------------
// CTestSDKListsMarkableListDialog::OkToExitL
// -----------------------------------------------------------------------------
//
TBool CTestSDKListsMarkableListDialog::OkToExitL(TInt aButtonId)
    {
    return CAknMarkableListDialog::OkToExitL( aButtonId );
    }

// -----------------------------------------------------------------------------
// CTestSDKListsMarkableListDialog::ListBox
// -----------------------------------------------------------------------------
//
CEikListBox* CTestSDKListsMarkableListDialog::ListBox() const
    {
    return CAknMarkableListDialog::ListBox();
    }
