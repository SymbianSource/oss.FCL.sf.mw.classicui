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







#include <aknvolumesettingpage.h>
#include <bctestvolume.rsg>

#include "testVolumeSettingPage.h"
#include "BCTestvolume.hrh"
#include "BCTestVolumeView.h"
#include "BCTestVolumeContainer.h"

//const

const TInt KBCTestVolumeDefaultVolumeLevel = 7;

// ----------------------------------------------------------------------------
// ctor, do nothing.
// ----------------------------------------------------------------------------
//
CTestVolumeSettingPage::CTestVolumeSettingPage(CBCTestVolumeView* aView):
    iView(aView) 
    {
    }

// ----------------------------------------------------------------------------
// dtor, do nothing.
// ----------------------------------------------------------------------------
//
CTestVolumeSettingPage::~CTestVolumeSettingPage()
    {
    }

// ----------------------------------------------------------------------------
// symbian 2nd phase ctor.
// ----------------------------------------------------------------------------
//
void CTestVolumeSettingPage::ConstructL()
    {
    BuildScriptL();
    }

// ----------------------------------------------------------------------------
// symbian NewL.
// ----------------------------------------------------------------------------
//
CTestVolumeSettingPage* CTestVolumeSettingPage::NewL(CBCTestVolumeView* aView)
    {
    CTestVolumeSettingPage* self = CTestVolumeSettingPage::NewLC(aView);
    CleanupStack::Pop(self);
    return self;
    }

// ----------------------------------------------------------------------------
// symbian NewLC
// ----------------------------------------------------------------------------
//
CTestVolumeSettingPage* CTestVolumeSettingPage::NewLC(CBCTestVolumeView* aView)
    {
    CTestVolumeSettingPage* self = new ( ELeave ) CTestVolumeSettingPage(aView);
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
    }

// ----------------------------------------------------------------------------
// override the CBCTestCase::RunL, only response to the related command ID.
// ----------------------------------------------------------------------------
//
void CTestVolumeSettingPage::RunL(int aCmd)
    {
    if(aCmd != EBCTestVolumeCmdOutline01) return;
    SetupL();
    TestL();
    TearDownL();
    }

// ----------------------------------------------------------------------------
// build the test scripts for this test case.
// ----------------------------------------------------------------------------
//
void CTestVolumeSettingPage::BuildScriptL()
    {
    //
    // method 1: add script by const array
    //
    const TInt scripts[] =
        {
        DELAY(1),        // delay between commands is 1*0.1 seconds = 0.1 seconds
        LeftCBA, LeftCBA,
        LeftCBA
        };
    AddTestScriptL(scripts, sizeof(scripts)/sizeof(TInt));
    }

// ----------------------------------------------------------------------------
// test the volume setting page creation api.
// ----------------------------------------------------------------------------
//
void CTestVolumeSettingPage::TestL()
    {
    TInt volume(KBCTestVolumeDefaultVolumeLevel);
    CAknVolumeSettingPage* volumeSettingPage = new( ELeave ) CAknVolumeSettingPage( 
            R_BCTESTVOLUME_SETTING_PAGE_VOLUME_INDICATOR, 
            volume );

    AssertNotNullL(volumeSettingPage, _L("create volume setting page."));

    AssertTrueL(
        volumeSettingPage->ExecuteLD( CAknSettingPage::EUpdateWhenChanged ),
        _L("setting page executed."));
    }

// ----------------------------------------------------------------------------
// getter for the container.
// ----------------------------------------------------------------------------
//
CBCTestVolumeContainer*  CTestVolumeSettingPage::Container()  const
    { 
    return iView->Container(); 
    }

// ----------------------------------------------------------------------------
// prepare for the test.
// ----------------------------------------------------------------------------
//
void CTestVolumeSettingPage::SetupL()
    {
    Container()->ResetComponentsL();
    }

// ----------------------------------------------------------------------------
// do release jobs.
// ----------------------------------------------------------------------------
//
void CTestVolumeSettingPage::TearDownL()
    {
    Container()->CreateLabelL( R_BCTESTVOLUME_TEXT_LABEL_OPERATION );
    Container()->UpdateComponentsL();
    }

//end of file
