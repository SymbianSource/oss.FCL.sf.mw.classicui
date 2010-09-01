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
* Description:  test case for navigation_pane_api module
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <aknnavi.h>
#include <aknnavide.h>
#include <aknnavilabel.h>

#include "testsdknavipane.h"
#include "testsdknavipanenaviext.h"
#include "testsdknavipanenavideext.h"
#include "testsdknavipanenavilblext.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// Ctestsdknavipane::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void CTestSDKNaviPane::Delete() 
    {

    if( iNaviContainer )
        {
        delete iNaviContainer;
        iNaviContainer = NULL;
        }
    if( iNaviContainerExt )
        {
        delete iNaviContainerExt;
        iNaviContainerExt = NULL;
        }
    if( iNaviContainerDe )
        {
        delete iNaviContainerDe;
        iNaviContainerDe = NULL;
        }
    if( iNaviContainerDeExt )
        {
        delete iNaviContainerDeExt;
        iNaviContainerDeExt = NULL;
        }
    if( iNaviLbl )
        {
        delete iNaviLbl;
        iNaviLbl = NULL;
        }
    if( iNaviLblExt )
        {
        delete iNaviLblExt;
        iNaviLblExt = NULL;
        }
    }

// -----------------------------------------------------------------------------
// Ctestsdknavipane::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestSDKNaviPane::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        //test aknnavi.h
        ENTRY( "TestNaviCAknNavigationControlContainer", 
            CTestSDKNaviPane::TestNaviCAknNavigationControlContainerL ),
        ENTRY( "TestNaviDelete", CTestSDKNaviPane::TestNaviDelete ),
        ENTRY( "TestNaviConstructL", CTestSDKNaviPane::TestNaviConstructL ),
        ENTRY( "TestNaviConstructFromResourceL", 
            CTestSDKNaviPane::TestNaviConstructFromResourceL ),
        ENTRY( "TestNaviConstructNavigationDecoratorFromResourceL", 
            CTestSDKNaviPane::TestNaviConstructNavigationDecoratorFromResourceL ),            
        ENTRY( "TestNaviCreateTabGroupL", CTestSDKNaviPane::TestNaviCreateTabGroupL ),
        ENTRY( "TestNaviCreateTabGroupLWithObserverL", 
            CTestSDKNaviPane::TestNaviCreateTabGroupLWithObserverL ),
        ENTRY( "TestNaviCreateTabGroupLWithResL", 
            CTestSDKNaviPane::TestNaviCreateTabGroupLWithResL ),
        ENTRY( "TestNaviCreateTabGroupLWithResAndObserverL", 
            CTestSDKNaviPane::TestNaviCreateTabGroupLWithResAndObserverL ),
        ENTRY( "TestNaviCreateNavigationLabelL", 
            CTestSDKNaviPane::TestNaviCreateNavigationLabelL ),
        ENTRY( "TestNaviCreateNavigationLabelLWithResL", 
            CTestSDKNaviPane::TestNaviCreateNavigationLabelLWithResL ),
        ENTRY( "TestNaviCreateNavigationImageL", 
            CTestSDKNaviPane::TestNaviCreateNavigationImageL ),
        ENTRY( "TestNaviCreateNavigationImageLWithResL", 
            CTestSDKNaviPane::TestNaviCreateNavigationImageLWithResL ),
        ENTRY( "TestNaviCreateMessageLabelL", 
            CTestSDKNaviPane::TestNaviCreateMessageLabelL ),
        ENTRY( "TestNaviCreateMessageLabelLWithResL", 
            CTestSDKNaviPane::TestNaviCreateMessageLabelLWithResL ),
        ENTRY( "TestNaviCreateVolumeIndicatorL", 
            CTestSDKNaviPane::TestNaviCreateVolumeIndicatorL ),
        ENTRY( "TestNaviCreateEditorIndicatorContainerL", 
            CTestSDKNaviPane::TestNaviCreateEditorIndicatorContainerL ),
        ENTRY( "TestNaviPushDefaultL", CTestSDKNaviPane::TestNaviPushDefaultL ),
        ENTRY( "TestNaviPushL", CTestSDKNaviPane::TestNaviPushL ),
        ENTRY( "TestNaviPop", CTestSDKNaviPane::TestNaviPop ),
        ENTRY( "TestNaviPopWithControl", CTestSDKNaviPane::TestNaviPopWithControl ),
        ENTRY( "TestNaviTopL", CTestSDKNaviPane::TestNaviTopL ),
        ENTRY( "TestNaviTopWithBoolL", CTestSDKNaviPane::TestNaviTopWithBoolL ),
        ENTRY( "TestNaviReplaceL", CTestSDKNaviPane::TestNaviReplaceL ),
        ENTRY( "TestNaviResourceDecorator", CTestSDKNaviPane::TestNaviResourceDecorator ),
        
        ENTRY( "TestNaviSetPreferredNaviDecoratorLayoutStyle", 
        		CTestSDKNaviPane::TestNaviSetPreferredNaviDecoratorLayoutStyle ),
        ENTRY( "TestNaviColorScheme", CTestSDKNaviPane::TestNaviColorScheme ),
        ENTRY( "TestNaviHandlePointerEventL", CTestSDKNaviPane::TestNaviHandlePointerEventL ),
        
        ENTRY( "TestNaviSizeChanged", CTestSDKNaviPane::TestNaviSizeChangedL ),
        ENTRY( "TestNaviHandleResourceChange", 
        		CTestSDKNaviPane::TestNaviHandleResourceChangeL ),
        ENTRY( "TestNaviCountComponentControls", 
        		CTestSDKNaviPane::TestNaviCountComponentControlsL ),
        ENTRY( "TestNaviComponentControl", CTestSDKNaviPane::TestNaviComponentControlL ),
        ENTRY( "TestNaviHandleControlEventL", CTestSDKNaviPane::TestNaviHandleControlEventL ),
        
        // aknnavide.h
        ENTRY( "TestNaviDeNewL", CTestSDKNaviPane::TestNaviDeNewL ),
        ENTRY( "TestNaviDeDelete", CTestSDKNaviPane::TestNaviDeDelete ),
        ENTRY( "TestNaviDeDecoratedControl", 
        		CTestSDKNaviPane::TestNaviDeDecoratedControlL ),
        ENTRY( "TestNaviDeMakeScrollButtonVisible", 
        		CTestSDKNaviPane::TestNaviDeMakeScrollButtonVisibleL ),
        ENTRY( "TestNaviDeScrollButtonVisible", 
        		CTestSDKNaviPane::TestNaviDeScrollButtonVisibleL),
        ENTRY( "TestNaviDeSetScrollButtonDimmed", 
        		CTestSDKNaviPane::TestNaviDeSetScrollButtonDimmedL ),
        ENTRY( "TestNaviDeIsScrollButtonDimmed", 
        		CTestSDKNaviPane::TestNaviDeIsScrollButtonDimmedL ),
        ENTRY( "TestNaviDeSetControlType", 
        		CTestSDKNaviPane::TestNaviDeSetControlTypeL ),
        ENTRY( "TestNaviDeControlType", CTestSDKNaviPane::TestNaviDeControlTypeL ),
        ENTRY( "TestNaviDeSetNaviDecoratorObserver", 
        		CTestSDKNaviPane::TestNaviDeSetNaviDecoratorObserverL ),
        ENTRY( "TestNaviDeHandlePointerEventL", 
        		CTestSDKNaviPane::TestNaviDeHandlePointerEventL ),
        ENTRY( "TestNaviDeSetNaviControlLayoutStyle", 
        		CTestSDKNaviPane::TestNaviDeSetNaviControlLayoutStyleL ),
        ENTRY( "TestNaviDeNaviControlLayoutStyle", 
        		CTestSDKNaviPane::TestNaviDeNaviControlLayoutStyleL ),
        ENTRY( "TestNaviDeNaviControlLayoutStyleSupported", 
        		CTestSDKNaviPane::TestNaviDeNaviControlLayoutStyleSupportedL ),
        ENTRY( "TestNaviDeSetNaviControlLayoutMode", 
        		CTestSDKNaviPane::TestNaviDeSetNaviControlLayoutModeL ),     
        ENTRY( "TestNaviDeNaviControlLayoutMode", 
        		CTestSDKNaviPane::TestNaviDeNaviControlLayoutModeL ), 
        ENTRY( "TestNaviDeHandleResourceChangeL", 
        		CTestSDKNaviPane::TestNaviDeHandleResourceChangeL ),
        ENTRY( "TestNaviDeSizeChangedL", CTestSDKNaviPane::TestNaviDeSizeChangedL ),
        ENTRY( "TestNaviDeCountComponentControlsL", 
        		CTestSDKNaviPane::TestNaviDeCountComponentControlsL ),
        ENTRY( "TestNaviDeComponentControlL", CTestSDKNaviPane::TestNaviDeComponentControlL ),
        ENTRY( "TestNaviDeHandleControlEventL", 
        		CTestSDKNaviPane::TestNaviDeHandleControlEventL ),
        		

        // aknnavilabel.h
        ENTRY( "TestNaviLblCAknNaviLabel", CTestSDKNaviPane::TestNaviLblCAknNaviLabelL ),
        ENTRY( "TestNaviLblDelete", CTestSDKNaviPane::TestNaviLblDelete ),
        ENTRY( "TestNaviLblSetNaviLabelType", 
        		CTestSDKNaviPane::TestNaviLblSetNaviLabelType ),
        ENTRY( "TestNaviLblNaviLabelType", CTestSDKNaviPane::TestNaviLblNaviLabelType ),
        ENTRY( "TestNaviLblSetTextL", CTestSDKNaviPane::TestNaviLblSetTextL ),
        ENTRY( "TestNaviLblHandlePointerEventL", 
        		CTestSDKNaviPane::TestNaviLblHandlePointerEventL ),
        ENTRY( "TestNaviLblSizeChangedL", CTestSDKNaviPane::TestNaviLblSizeChangedL ),
        ENTRY( "TestNaviLblDrawL", CTestSDKNaviPane::TestNaviLblDrawL ),
        
        // [test cases entries]

        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

//  [End of File]
