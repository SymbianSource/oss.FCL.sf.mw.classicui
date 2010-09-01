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
* Description:         Implementation of application UI class.
*
*/










// INCLUDE FILES
#include <bctestlauncher.rsg>
#include <avkon.hrh>
#include <bacline.h>

#include "bctestlauncherappui.h"
#include "bctestlaunchercontainer.h" 
#include "bctestlauncher.hrh"
#include "bctestlauncherview.h"
#include "bctestrunner.h"
#include "streamlogger.h"

#include "bctestapplication.h"

const TInt CMDNum = 32;
_LIT( KFULL, "full" );

// ============================ MEMBER FUNCTIONS =============================

// ---------------------------------------------------------------------------
// C++ default constructor
// ---------------------------------------------------------------------------
//
CBCTestLauncherAppUi::CBCTestLauncherAppUi()
                    : iNaviPane( NULL ), iAppContainer( NULL ),iRunner( 0 )
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd phase constructor can leave.
// ---------------------------------------------------------------------------
//
void CBCTestLauncherAppUi::ConstructL()
    {
    BaseConstructL();

    // Create status pane
    CEikStatusPane *sp = StatusPane();
    // Create navi pane
    iNaviPane = ( CAknNavigationControlContainer* )sp->ControlL(
        TUid::Uid( EEikStatusPaneUidNavi ) );

	iRunner = CBCTestRunner::NewL();

    iAppView = new( ELeave )CBCTestLauncherView( iRunner->Apps() );
    iAppView->ConstructL();
	AddViewL( iAppView );

    ActivateLocalViewL( iAppView->Id() );
	SetDefaultViewL( *iAppView );

	DoCommand();

    }

// Destructor
CBCTestLauncherAppUi::~CBCTestLauncherAppUi()
    {
    delete iAppContainer;
    delete iRunner;
    }

// ---------------------------------------------------------------------------
// CBCTestLauncherAppUi::HandleCommandL( TInt aCommand )
// Handles command list
// ---------------------------------------------------------------------------
//
void CBCTestLauncherAppUi::HandleCommandL( TInt aCommand )
    {
    switch ( aCommand )
        {
        case EAknCmdExit:
        case EEikCmdExit:
		case EAknSoftkeyBack:
			Exit();
            break;
        case ESdkVersion:
            iAppView->HandleCommandL( aCommand );
            break;
		case EAutoTestSelection:
			if( !iAppView->SelectL() )
				{
				return;
				}

        default:
            iRunner->RunL( aCommand );
        }
    }

// ---------------------------------------------------------------------------
// CBCTestLauncherAppUi::HandleKeyEventL(
//     const TKeyEvent& aKeyEvent, TEventCode /*aType*/ )
// Handles key events.
// ---------------------------------------------------------------------------
//
TKeyResponse CBCTestLauncherAppUi::HandleKeyEventL(
    const TKeyEvent& /*aKeyEvent*/, TEventCode /*aType*/ )
    {
    return EKeyWasNotConsumed;
    }
 
void CBCTestLauncherAppUi::DoCommand()
    {
    
	CCommandLineArguments* args = CCommandLineArguments::NewLC();

    if ( args->Count() == 1)
        {
        CleanupStack::PopAndDestroy( args );
        return;
        } 

    CArrayFixFlat<TPtrC>* cmdData = new( ELeave )CArrayFixFlat<TPtrC>( CMDNum );
    CleanupStack::PushL( cmdData );
    
    HBufC* msg = HBufC::NewLC( 32 );
 	for (TInt i=0; i<args->Count(); i++)
		{
        msg->Des().Copy( args->Arg(i) );
        msg->Des().LowerCase();
		cmdData->AppendL( msg->Des() );
		}
    
    if ( ( *cmdData )[1] == KFULL )
        {
        iAppView->HandleCommandL( EAutoTestAll );
        }
    else
        {
        iAppView->Reset();
        RArray<CBCTestApplication*>* aList = iRunner->Apps();

        for( TInt i=0; i<cmdData->Count(); i++)
            {

            for( TInt j=0; j<( *aList ).Count(); j++ )
                {
                if( ( *cmdData )[i] == ( *aList )[j]->Name()  )
                    {
                    ( *aList )[j]->Select();
                    }
                }
            }
         iRunner->RunL( EAutoTestSelection );
         }
    CleanupStack::PopAndDestroy( msg );
    CleanupStack::PopAndDestroy( cmdData ); 
    CleanupStack::PopAndDestroy( args );

    iAppView->HandleCommandL( EAknCmdExit );//auto exit

    }
