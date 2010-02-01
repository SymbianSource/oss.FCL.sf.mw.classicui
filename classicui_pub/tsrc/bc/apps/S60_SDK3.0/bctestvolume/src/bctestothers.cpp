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
* Description:       
*
*/







#include <aknnavide.h>
#include <aknvolumesettingpage.h>
#include <bctestvolume.rsg>
#include <gulicon.h>

#include "bctestothers.h"
#include "BCTestvolume.hrh"
#include "BCTestVolumeView.h"
#include "BCTestVolumeContainer.h"

//const

#ifdef __PROTOCOL_CDMA
const TInt KVolumeMinValue=0;
#else
const TInt KVolumeMinValue=1;
#endif //__PROTOCOL_CDMA

const TInt KVolumeMaxValue=10;

// ----------------------------------------------------------------------------
// ctor, do nothing.
// ----------------------------------------------------------------------------
//
CTestOthers::CTestOthers(CBCTestVolumeView* aView):
    iView(aView), iVolume(0) 
    {
    }

// ----------------------------------------------------------------------------
// dtor, do nothing.
// ----------------------------------------------------------------------------
//
CTestOthers::~CTestOthers()
    {
    }

// ----------------------------------------------------------------------------
// symbian 2nd phase ctor.
// ----------------------------------------------------------------------------
//
void CTestOthers::ConstructL()
    {
    BuildScriptL();
    }

// ----------------------------------------------------------------------------
// symbian NewL.
// ----------------------------------------------------------------------------
//
CTestOthers* CTestOthers::NewL(CBCTestVolumeView* aView)
    {
    CTestOthers* self = CTestOthers::NewLC(aView);
    CleanupStack::Pop(self);
    return self;
    }

// ----------------------------------------------------------------------------
// symbian NewLC
// ----------------------------------------------------------------------------
//
CTestOthers* CTestOthers::NewLC(CBCTestVolumeView* aView)
    {
    CTestOthers* self = new ( ELeave ) CTestOthers(aView);
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
    }

// ----------------------------------------------------------------------------
// override the CBCTestCase::RunL, only response to the related command ID.
// ----------------------------------------------------------------------------
//
void CTestOthers::RunL(int aCmd)
    {
    if(aCmd != EBCTestVolumeOthers) 
		{
		return;
		}
    SetupL();
    TestL();
    TearDownL();
    }

// ----------------------------------------------------------------------------
// build the test scripts for this test case.
// ----------------------------------------------------------------------------
//
void CTestOthers::BuildScriptL()
    {
	AddTestL(LeftCBA, TEND);
    AddTestL(REP(Down, 6), TEND);
    AddTestL(LeftCBA, TEND);
    AddTestL(KeyOK, TEND);
    }

void CTestOthers::TryCreateL(TInt aResourceID, TInt aLabelID)
	{
	// Creates Navi pane volume glider object.
    CAknNavigationDecorator* decorator = Container()->NaviPane()->CreateVolumeIndicatorL( aResourceID );
    AssertNotNullL(decorator, _L("Volume indicator created by NaviPane:"));

    Container()->NaviPane()->PushL( *decorator );

    CAknVolumeControl* volume = static_cast<CAknVolumeControl*>(decorator->DecoratedControl() );
    AssertNotNullL(volume, _L("Get decorate control:"));

    // Adds volume control to control stack.
    // Volume control can get offered key event.
    CEikonEnv::Static()->EikAppUi()->AddToStackL( volume );

    Container()->SetDecorator(decorator);   //to be removed later
    Container()->CreateLabelL( aLabelID );
    iVolume=volume;
	}

// ----------------------------------------------------------------------------
// test the volume setting page creation api.
// ----------------------------------------------------------------------------
//
void CTestOthers::TestL()
    {
	CFbsBitmap* bitmap = CAknVolumeControl::CreateBitmapL(5);
	CleanupStack::PushL(bitmap);
	AssertNotNullL(bitmap, _L("bitmap created"));
	CleanupStack::PopAndDestroy();	//bitmap

	TryCreateL(R_AVKON_NAVI_PANE_VOLUME_INDICATOR, R_BCTESTVOLUME_TEXT_LABEL_OPERATION);

	TPointerEvent event = 
		{ 
		TPointerEvent::EButton1Up, 
		EModifierAutorepeatable, 
		TPoint( 20,20 ), 
		TPoint( 0,0 ) 
		};
	iVolume->HandlePointerEventL(event);
	AssertTrueL(ETrue, _L("pointer event handled"));

	iVolume->HandleResourceChange(KEikColorResourceChange);
	AssertTrueL(ETrue, _L("res change handled"));

	iVolume->HandleResourceChange(-KEikColorResourceChange);
	AssertTrueL(ETrue, _L("unknown type res change handled"));

	CGulIcon* icon = iVolume->CreateSetStyleListBoxIconL(
		(KVolumeMinValue + KVolumeMaxValue) /2);
	delete icon;
    }

// ----------------------------------------------------------------------------
// getter for the container.
// ----------------------------------------------------------------------------
//
CBCTestVolumeContainer*  CTestOthers::Container()  const
    { 
    return iView->Container(); 
    }

// ----------------------------------------------------------------------------
// prepare for the test.
// ----------------------------------------------------------------------------
//
void CTestOthers::SetupL()
    {
    Container()->ResetComponentsL();
    }

// ----------------------------------------------------------------------------
// do release jobs.
// ----------------------------------------------------------------------------
//
void CTestOthers::TearDownL()
    {
    Container()->UpdateComponentsL();
    }

//end of file

