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
* Description:  Test settingpages_api
*
*/

//INCLUDE
#include <aknsettingpage.h>
#include <testsdksettingpages.rsg>

#include "testsettingpageobserver.h"
#include "testsdksettingpagesstdinclude.h"
#include "testaknsettingpageprotected.h"

// ============================ MEMBER FUNCTIONS ===============================

const TInt KNumberItems = 10;

// -----------------------------------------------------------------------------
// CSettingItemObserver::CSettingItemObserver
// -----------------------------------------------------------------------------
//
CSettingItemObserver::CSettingItemObserver( TInt aIdentifier ):CAknSettingItem( aIdentifier )
    {
    
    }

// -----------------------------------------------------------------------------
// CSettingItemObserver::~CSettingItemObserver
// -----------------------------------------------------------------------------
//
CSettingItemObserver::~CSettingItemObserver()
    {
    if (iSelectionList)        
        {
        iSelectionList->ResetAndDestroy();
        delete iSelectionList;        
        }    
    }

// -----------------------------------------------------------------------------
// CSettingItemObserver::EditItemL
// -----------------------------------------------------------------------------
//
void CSettingItemObserver::EditItemL( TBool /*aCalledFromMenu*/ )
    {    
    if ( iSelectionList )        
        {        
        iSelectionList->ResetAndDestroy();
        delete iSelectionList;
        iSelectionList = 0;
        }    
    iSelectionList = new (ELeave) CSelectionItemList( 2 );
    for ( TInt count=0; count < KNumberItems; count++ )
        {        
        TBuf< KBufSize > text;
        text.Format( _L("checkline %d"), count );
        CSelectableItem* selectionItem = new (ELeave) CSelectableItem( text, EFalse );
        CleanupStack::PushL( selectionItem );
        selectionItem->ConstructL();
        iSelectionList->AppendL( selectionItem );
        CleanupStack::Pop( selectionItem );
        }
    CAknCheckBoxSettingPage* settPage = new (ELeave) CAknCheckBoxSettingPage( SettingPageResourceId(), iSelectionList );
    CleanupStack::PushL( settPage );
    SetSettingPage( settPage );
    SettingPage()->SetSettingPageObserver( this );
    SetUpStandardSettingPageL();
    CleanupStack::Pop( settPage );
    TBool accepted = SettingPage()->ExecuteLD( CAknSettingPage::EUpdateWhenChanged );
    // ExecuteLD destroys the setting page, so set it to zero:
    SetSettingPage( 0 );
    if ( accepted )
        {
        TBuf<40> text;
        for ( TInt mCount=0; mCount < KNumberItems; mCount++)
            {            
            if ( (*iSelectionList)[mCount]->SelectionStatus() )
                {                
                TBuf<4> newtext;                
                newtext.Format( _L("%d,"), mCount );                
                text.Append( newtext );                
                }            
            }        
        User::InfoPrint( text );        
        }    
    }

//End file


