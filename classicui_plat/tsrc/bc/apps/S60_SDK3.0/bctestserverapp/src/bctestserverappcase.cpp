/*
* Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:         test case
*
*/









#include <w32std.h>
#include <coecntrl.h>
#include <aknserverapp.h>
#include <avkon.hrh>
#include <aknwseventobserver.h>
#include <aknBitmapAnimation.h>
#include <barsread.h>
#include <aknsitemid.h>
#include <bctestserverapp.rsg>
#include <AknsConstants.h>
#include <AknsItemData.h>
#include <AknsSkinInstance.h>
#include <AknsUtils.h>
#include <avkon.rsg>

#include "bctestserverappcase.h"
#include "bctestserverappcontainer.h"
#include "bctestserverapp.hrh"
#include "bctestserverappappui.h"


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestServerappCase* CBCTestServerappCase::NewL(
    CBCTestServerappContainer* aContainer )
    {
    CBCTestServerappCase* self = new( ELeave ) CBCTestServerappCase(
        aContainer );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default constructor
// ---------------------------------------------------------------------------
//
CBCTestServerappCase::CBCTestServerappCase(
    CBCTestServerappContainer* aContainer )
    : iContainer( aContainer )
    {
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestServerappCase::~CBCTestServerappCase()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestServerappCase::ConstructL()
    {
    BuildScriptL();
    }

// ---------------------------------------------------------------------------
// CBCTestServerappCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestServerappCase::BuildScriptL()
    {
    AddTestL( LeftCBA, KeyOK, TEND );
    AddTestL( LeftCBA, Down, KeyOK, TEND );
    AddTestL( LeftCBA, Down, Down, KeyOK, TEND );
    }

// ---------------------------------------------------------------------------
// CBCTestServerappCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestServerappCase::RunL( TInt aCmd )
    {
    if ( aCmd < EBCTestCmdOutline1 || aCmd > EBCTestCmdOutline3 )
        {
        return;
        }
    ReleaseCaseL();
    PrepareCaseL( aCmd );
    switch ( aCmd )
        {
        case EBCTestCmdOutline1:
            TestFunctionL();
            break;
        case EBCTestCmdOutline2:
            TestFunctionOneL();
            break;
        case EBCTestCmdOutline3:
            TestFunctionTwoL();
            break;
        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// CBCTestServerappCase::PrepareCaseL
// ---------------------------------------------------------------------------
//
void CBCTestServerappCase::PrepareCaseL( TInt aCmd )
    {
    switch ( aCmd )
        {
        case EBCTestCmdOutline1:
            iControl = new( ELeave ) CCoeControl();
            iControl->SetContainerWindowL( *iContainer );
            iControl->MakeVisible( ETrue );
            break;

        default:
            break;
        }
    iContainer->SetControl( iControl );
    }

// ---------------------------------------------------------------------------
// CBCTestServerappCase::ReleaseCaseL
// ---------------------------------------------------------------------------
//
void CBCTestServerappCase::ReleaseCaseL()
    {
    iContainer->ResetControl();
    iControl = NULL;
    }

// ---------------------------------------------------------------------------
// CBCTestServerappCase::TestLayoutDecorator
// ---------------------------------------------------------------------------
//
void CBCTestServerappCase::TestFunctionL()
    {
    _LIT( strAddObserverL,"Class CAknWsEventMonitor Function AddObserverL tested" );
    _LIT( strHandleWsEventL,"Class CAknWsEventMonitor Function HandleWsEventL tested" );
    _LIT( strRemoveObserver,"Class CAknWsEventMonitor Function RemoveObserver tested" );

    CAknAppUi* base = static_cast<CAknAppUi*>(CEikonEnv::Static()->EikAppUi());
    CAknWsEventMonitor* monitor = base->EventMonitor();
    CSubMonitor* wsevent = CSubMonitor::NewL(); 

    CleanupStack::PushL(monitor);

    TWsEvent event;
    monitor->AddObserverL(wsevent);
    AssertTrueL( ETrue, strAddObserverL);

    monitor->HandleWsEventL(event, iContainer);
    AssertTrueL( ETrue, strHandleWsEventL);

    monitor->RemoveObserver(wsevent);
    AssertTrueL( ETrue, strRemoveObserver);

    CleanupStack::Pop(monitor);
    delete wsevent;
    monitor = NULL;
    base = NULL;

    }

void CBCTestServerappCase::TestFunctionOneL()
    {
    _LIT( strConstructL,"Class CAknAppServer Function ConstructL tested" );
    _LIT( strdelCAknAppServer,"Class CAknAppServer Function ~CAknAppServer tested" );


    CAknAppServer *appserver = new ( ELeave ) CAknAppServer();
    CleanupStack::PushL( appserver );

    _LIT( serverName, "my server app");
    appserver->ConstructL(serverName);
    AssertTrueL( ETrue, strConstructL);

    CleanupStack::PopAndDestroy(appserver);
    AssertTrueL( ETrue, strdelCAknAppServer);

    }

void CBCTestServerappCase::TestFunctionTwoL()
    {

    _LIT( strAnimation,"Class CAknBitmapAnimation Function Animation tested" );
    _LIT( strBitmapAnimData,"Class CAknBitmapAnimation Function BitmapAnimData tested" );
    _LIT( strCancelAnimation,"Class CAknBitmapAnimation Function CancelAnimation tested" );
    _LIT( strConstructFromResourceL,"Class CAknBitmapAnimation Function ConstructFromResourceL tested" );
    _LIT( strConstructFromSkinL,"Class CAknBitmapAnimation Function ConstructFromSkinL tested" );
    _LIT( strMinimumSize,"Class CAknBitmapAnimation Function MinimumSize tested" );
    _LIT( strNewL,"Class CAknBitmapAnimation Function NewL tested" );
    _LIT( strSetFrameIndexL,"Class CAknBitmapAnimation Function SetFrameIndexL tested" );
    _LIT( strSetFrameIntervalL,"Class CAknBitmapAnimation Function SetFrameIntervalL tested" );
    _LIT( strStartAnimationL,"Class CAknBitmapAnimation Function StartAnimationL tested" );
    _LIT( strdelCAknBitmapAnimation,"Class CAknBitmapAnimation Function ~CAknBitmapAnimation tested" );

    CAknBitmapAnimation *ani= CAknBitmapAnimation::NewL();
    AssertTrueL( ETrue, strNewL);
    CleanupStack::PushL(ani);

    ani->SetContainerWindowL(*iContainer);
    
    TBool flag = ani->ConstructFromSkinL(KAknsIIDQsnBgScreen);
    AssertTrueL( ETrue, strConstructFromSkinL);

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC(reader, 
        R_BCTEST_BMPANIM_DATA_ORG);
    ani->ConstructFromResourceL(reader);
    AssertTrueL( ETrue, strConstructFromResourceL);
    CleanupStack::PopAndDestroy();

    TRAP_IGNORE( ani->SetFrameIndexL( 1 ) );
    AssertTrueL( ETrue, strSetFrameIndexL );

    ani->MinimumSize();
    AssertTrueL( ETrue, strMinimumSize);

    RBitmapAnim rani = ani->Animation();
    AssertTrueL( ETrue, strAnimation);

    CBitmapAnimClientData* clientData = ani->BitmapAnimData();
    AssertTrueL(ETrue, strBitmapAnimData);
    
    TInt i = 1500;
    ani->SetFrameIntervalL(i);
    AssertTrueL( ETrue, strSetFrameIntervalL);
    
    ani->StartAnimationL();
    AssertTrueL(ETrue, strStartAnimationL);
    
    CleanupStack::PopAndDestroy(ani);
    AssertTrueL(ETrue, strCancelAnimation);
    AssertTrueL( ETrue, strdelCAknBitmapAnimation);
    }
CSubMonitor *CSubMonitor::NewL()
 {
  	CSubMonitor * self=new(ELeave) CSubMonitor();
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop();
	return self;
 }

CSubMonitor::~CSubMonitor()
 {
 }

void CSubMonitor::ConstructL()
  {
  }

EXPORT_C void CSubMonitor::HandleWsEventL(const TWsEvent& aEvent,CCoeControl* aDestination)
 {
 }
