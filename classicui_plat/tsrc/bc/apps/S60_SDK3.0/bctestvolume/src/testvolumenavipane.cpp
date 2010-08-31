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
#include <avkon.rsg>
#include <bctestvolume.rsg>
#include <eikenv.h>
#include <eikappui.h>
#include <eikspane.h>
#include <sysutil.h>
#include <f32file.h>  // link against efsrv.lib 

#include "testVolumeNaviPane.h"
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
CTestVolumeNaviPane::CTestVolumeNaviPane(CBCTestVolumeView* aView):
    iView(aView), iVolume(0)
    {
    }

// ----------------------------------------------------------------------------
// dtor, do nothing.
// ----------------------------------------------------------------------------
//
CTestVolumeNaviPane::~CTestVolumeNaviPane()
    {
    }

// ----------------------------------------------------------------------------
// symbian 2nd phase ctor
// ----------------------------------------------------------------------------
//
void CTestVolumeNaviPane::ConstructL()
    {
    ScriptCreateL();
    }

// ----------------------------------------------------------------------------
// symbian NewL
// ----------------------------------------------------------------------------
//
CTestVolumeNaviPane* CTestVolumeNaviPane::NewL( CBCTestVolumeView* aView)
    {
    CTestVolumeNaviPane* self = CTestVolumeNaviPane::NewLC(aView);
    CleanupStack::Pop(self);
    return self;
    }

// ----------------------------------------------------------------------------
// symbian NewLC
// ----------------------------------------------------------------------------
//
CTestVolumeNaviPane* CTestVolumeNaviPane::NewLC(CBCTestVolumeView* aView)
    {
    CTestVolumeNaviPane* self = new ( ELeave ) CTestVolumeNaviPane(aView);
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
    }

// ----------------------------------------------------------------------------
// override from CBCTestCase, response for relative command ID.
// ----------------------------------------------------------------------------
//
void CTestVolumeNaviPane::RunL(int aCmd)
    {
    if(aCmd<EBCTestVolumeCmdOutline02 || aCmd>EBCTestVolumeCmdOutline06)
        {
        return;
        }

    SetupL();
    switch(aCmd)
        {
    case EBCTestVolumeCmdOutline02:
        TestCreateL();
        break;
    case EBCTestVolumeCmdOutline03:
        TestNormalL();
        break;
    case EBCTestVolumeCmdOutline04:
        TestIdleL();
        break;
    case EBCTestVolumeCmdOutline05:
        TestIconL();
        break;
    case EBCTestVolumeCmdOutline06:
        TestNaviEventL();
        break;
    default:
        break;
        }
    TearDownL();
    }

// ----------------------------------------------------------------------------
// build the test scripts
// ----------------------------------------------------------------------------
//
void CTestVolumeNaviPane::ScriptCreateL()
    {
    //
    // method 2: add test script dynamically
    //
    for(int i=2; i<=6; ++i)
        {
        AddTestL(LeftCBA, TEND);

        //
        // select the related menu item
        //
        for(int j=0; j<i-1; ++j)
            {
            AddTestL(Down, TEND);
            }
        AddTestL(LeftCBA, TEND);
        AddTestL(KeyOK, TEND);
        }
    }

// ----------------------------------------------------------------------------
// try to test creation of the volume control inside navigation pane.
// ----------------------------------------------------------------------------
//
void CTestVolumeNaviPane::TryCreateL(TInt aResourceID, TInt aLabelID)
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
// try to test adjustment of the value for the volume control.
// ----------------------------------------------------------------------------
//
void CTestVolumeNaviPane::TryAdjustL()
    {
    // These are for testing hi-res volume which has user defined min and max.
    //
    // value should range from 1 to 10
    
    // Value should range from 1 to 10 in old volume control
    iVolume->SetValue(KVolumeMinValue);
    AssertIntL(KVolumeMinValue, iVolume->Value(), _L("set value = min"));

    iVolume->SetValue(5);
    AssertIntL(5, iVolume->Value(), _L("set value = 5"));

    iVolume->SetValue(KVolumeMaxValue);
    AssertIntL(KVolumeMaxValue, iVolume->Value(), _L("set value = max"));
    }

// ----------------------------------------------------------------------------
// test volume control creating APIs.
// ----------------------------------------------------------------------------
//
void CTestVolumeNaviPane::TestCreateL()
    {
    TryCreateL(R_AVKON_NAVI_PANE_VOLUME_INDICATOR, R_BCTESTVOLUME_TEXT_LABEL_OPERATION);
    }

// ----------------------------------------------------------------------------
// try to test create a volume control and adjust its volume.
// ----------------------------------------------------------------------------
//
void CTestVolumeNaviPane::TestNormalL()
    {
    TryCreateL(R_AVKON_NAVI_PANE_VOLUME_INDICATOR, R_BCTESTVOLUME_TEXT_LABEL_EVENT1);
    TryAdjustL();
    }

// ----------------------------------------------------------------------------
// try to test create a volume control from IDLE state.
// ----------------------------------------------------------------------------
//
void CTestVolumeNaviPane::TestIdleL()
    {
    
    CEikonEnv::Static()->AppUiFactory()->StatusPane()->SwitchLayoutL( R_AVKON_STATUS_PANE_LAYOUT_IDLE );
    #ifdef R_AVKON_STATUS_PANE_LAYOUT_IDLE_EXT
	    {
	    CEikonEnv::Static()->AppUiFactory()->StatusPane()->SwitchLayoutL( R_AVKON_STATUS_PANE_LAYOUT_IDLE_EXT );
	    }
	#endif    

    CEikonEnv::Static()->AppUiFactory()->StatusPane()->CurrentLayoutResId();
    
    AssertTrueL( ETrue, _L("Set Navi pane to IDLE") );
        
    TryCreateL(R_AVKON_NAVI_PANE_VOLUME_INDICATOR, R_BCTESTVOLUME_TEXT_LABEL_OPERATION);
    TryAdjustL();
    Container()->UpdateComponentsL();
    CEikonEnv::Static()->AppUiFactory()->StatusPane()->SwitchLayoutL( R_AVKON_STATUS_PANE_LAYOUT_USUAL );
 
    #ifdef R_AVKON_STATUS_PANE_LAYOUT_USUAL_EXT
	    {
        CEikonEnv::Static()->AppUiFactory()->StatusPane()->SwitchLayoutL( R_AVKON_STATUS_PANE_LAYOUT_USUAL_EXT );
	    }
	#endif

    AssertTrueL( ETrue, _L("Set Navi pane to Usual") );
    }

// ----------------------------------------------------------------------------
// test create the volume control via ICON_SET
// ----------------------------------------------------------------------------
//
void CTestVolumeNaviPane::TestIconL()
    {
    TryCreateL(R_BCTESTVOLUME_NAVI_PANE_VOLUME_INDICATOR_ICON_SET, R_BCTESTVOLUME_TEXT_LABEL_OPERATION);
    AssertTrueL(ETrue, _L("create from icon set"));
    TryAdjustL();
    }

// ----------------------------------------------------------------------------
// test navigation event handler of the volume control.
// ----------------------------------------------------------------------------
//
void CTestVolumeNaviPane::TestNaviEventL()
    {
    TryCreateL(R_AVKON_NAVI_PANE_VOLUME_INDICATOR, R_BCTESTVOLUME_TEXT_LABEL_EVENT1);
    iVolume->SetValue(5);

    iVolume->HandleNaviDecoratorEventL(MAknNaviDecoratorObserver::EAknNaviDecoratorEventLeftTabArrow);
    AssertTrueL(ETrue, _L("HandleNaviDecoratorEventL invoked."));
    }

// ----------------------------------------------------------------------------
// getter of the container
// ----------------------------------------------------------------------------
//
CBCTestVolumeContainer*  CTestVolumeNaviPane::Container()  const
    { 
    return iView->Container(); 
    }

// ----------------------------------------------------------------------------
// do necessary setup jobs.
// ----------------------------------------------------------------------------
//
void CTestVolumeNaviPane::SetupL()
    {
    Container()->ResetComponentsL();
    }

// ----------------------------------------------------------------------------
// do release jobs.
// ----------------------------------------------------------------------------
//
void CTestVolumeNaviPane::TearDownL()
    {
    Container()->UpdateComponentsL();
    }

//end of file
