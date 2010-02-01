/*
* Copyright (c) 2006-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:         Implementation of application view class.
*
*/









#include <avkon.hrh>
#include <aknviewappui.h>
#include <akntabgrp.h>
#include <aknnavide.h>
#include <e32std.h>
#include <e32base.h>
#include <eiktxlbm.h>
#include <akndef.h>
#include <centralrepository.h>
#include <aknlistquerydialog.h> 
#include <bctestlauncher.rsg>

#include "bctestlauncherview.h"
#include "bctestlaunchercontainer.h"
#include "bctestrunner.h"
#include "bctestapplication.h"
#include "streamlogger.h"

// ============================ LOCAL FUNCTIONS ==============================
namespace BCTest
    {
	inline static CEikMenuPaneItem::SData& BuildItem( 
	    const TDesC& aName, const TInt aID )
	    {
		static CEikMenuPaneItem::SData item;
		item.iCommandId = aID;
		item.iText = aName;
		item.iFlags= EEikMenuItemSymbolOn;
		item.iCascadeId = 0;
		return item;
	    }
    }

// ============================ MEMBER FUNCTIONS =============================

// ---------------------------------------------------------------------------
// CBCTestLauncherView::CBCTestLauncherView()
// C++ default constructor can NOT contain any code, that
// might leave.
// ---------------------------------------------------------------------------
//
CBCTestLauncherView::CBCTestLauncherView( RArray<CBCTestApplication*>* aList )
    : iContainer( NULL ), iSelectApps( aList )
    {
    }

// ---------------------------------------------------------------------------
// CBCTestLauncherView::ConstructL
// Symbian 2nd phase constructor can leave.
// ---------------------------------------------------------------------------
//
void CBCTestLauncherView::ConstructL()
    {
    BaseConstructL( R_BCTESTLAUNCHER_VIEW );
	
	//construct the app list menu
    }
 
// ---------------------------------------------------------------------------
// CBCTestLauncherView::~CBCTestLauncherView
// Destructor.
// ---------------------------------------------------------------------------
//
CBCTestLauncherView::~CBCTestLauncherView()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }

    delete iContainer;
    }

// ---------------------------------------------------------------------------
// TUid CAknAtPbarView::Id()
// returns view Id.
// ---------------------------------------------------------------------------
//
TUid CBCTestLauncherView::Id() const
    {
    return KViewId;
    }

// ---------------------------------------------------------------------------
// CAknAtPbarView::HandleCommandL( TInt aCommand )
// handles commands.
// ---------------------------------------------------------------------------
//
void CBCTestLauncherView::HandleCommandL( TInt aCommand )
    {   
    switch ( aCommand )
        {
        case EAknCmdExit:
        case EAknSoftkeyBack:
        case EEikCmdExit:                        
            AppUi()->HandleCommandL( EEikCmdExit );
            return; // this can never be reached
        case ESdkVersion:
        	iContainer->SetSdkVersion();
            return; // this can never be reached
        }

	TInt number = aCommand - EBCTestLauncherStart;
	if( number >= 0 && number < ( *iSelectApps ).Count() )
		{
		Reset();
		( *iSelectApps )[number]->Select();
		}

	AppUi()->HandleCommandL( aCommand );
    }

// ---------------------------------------------------------------------------
// CAknAtPbarView::HandleClientRectChange()
// 
// ---------------------------------------------------------------------------
void CBCTestLauncherView::HandleClientRectChange()
    {
    if ( iContainer )
        {
        iContainer->SetRect( ClientRect() );
        }
    }

// ---------------------------------------------------------------------------
// CBCTestLauncherView::DoActivateL(...)
// 
// ---------------------------------------------------------------------------
void CBCTestLauncherView::DoActivateL(
    const TVwsViewId& /*aPrevViewId*/, TUid /*aCustomMessageId*/,
    const TDesC8& /*aCustomMessage*/ )
    {
    iContainer = new( ELeave ) CBCTestLauncherContainer;
    iContainer->SetMopParent( this );
    iContainer->ConstructL( ClientRect() );
    AppUi()->AddToStackL( *this, iContainer, ECoeStackPriorityDefault );
    }

// ---------------------------------------------------------------------------
// CBCTestLauncherView::DoDeactivate()
// 
// ---------------------------------------------------------------------------
void CBCTestLauncherView::DoDeactivate()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }

    delete iContainer;
    iContainer = NULL;
    }

// ---------------------------------------------------------------------------
// CBCTestLauncherView::RunSelectionL()
// 
// ---------------------------------------------------------------------------
TBool CBCTestLauncherView::SelectL()
    {
	_LIT( KPrefix, "1\t" );

	CListBoxView::CSelectionIndexArray* indexArray = 
	    new( ELeave )CArrayFixFlat<TInt>( ( *iSelectApps ).Count() ); 
	CleanupStack::PushL( indexArray );

	CAknListQueryDialog* dlg = 
	    new( ELeave ) CAknListQueryDialog( indexArray );
	dlg->PrepareLC(R_BCTESTLAUNCHER_MULTI_SELECTION_QUERY);

	CDesCArray* items = static_cast<CDesCArray*>( static_cast<
	    CTextListBoxModel*>( dlg->ListBox()->Model() )->ItemTextArray() );
	items->Reset();
	for( TInt i = 0; i < ( *iSelectApps ).Count(); ++i )
	    {
		TBuf<KNameLength> text( KPrefix );
		text += ( *iSelectApps )[i]->Name();
		items->AppendL( text );
	    }

	TBool res = EFalse;
    if ( dlg->RunLD() )
        {
		Reset();
        for (TInt i = 0; i < indexArray->Count(); ++i)
            {
            ( *iSelectApps )[ indexArray->At( i ) ]->Select(); 
            }
		res = ETrue;
        }

    CleanupStack::PopAndDestroy(); // indexArray
	return res;
    }

void CBCTestLauncherView::Reset()
	{
	for( TInt i = 0; i < ( *iSelectApps ).Count(); ++i )
		{
		( *iSelectApps )[i]->Select( EFalse ); 
		}
	}

// ---------------------------------------------------------------------------
// CBCTestLauncherView::DynInitMenuPaneL()
// 
// ---------------------------------------------------------------------------
//
void CBCTestLauncherView::DynInitMenuPaneL( 
    TInt aResourceId, CEikMenuPane* aMenuPane )
	{
	if( R_BCTESTLAUNCHER_SEPARATE_TESTS == aResourceId )
		{
		for( TInt i = 0; i < ( *iSelectApps ).Count(); ++i )
			{
			aMenuPane->AddMenuItemL( 
			    BCTest::BuildItem( ( *iSelectApps )[i]->Name(), 
				EBCTestLauncherStart + i ) );
			}
		}
	}

