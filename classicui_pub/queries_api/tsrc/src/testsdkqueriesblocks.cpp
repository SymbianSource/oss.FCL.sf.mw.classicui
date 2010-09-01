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
* Description:  Test queries_api
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>

#include "testsdkqueries.h"
#include "testsdkqueriesview.h"
#include "testsdkqueriescontainer.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// Ctestsdkqueries::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void CTestSDKQueries::Delete() 
    {
    if(iContainer)
        {
        delete iContainer;
        iContainer = NULL;
        }
    if(iView)
        {
        delete iView;
        iView = NULL;
        }
    }

// -----------------------------------------------------------------------------
// Ctestsdkqueries::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
            //CAknDialog
        ENTRY( "TestDlgCAknDialog", CTestSDKQueries::TestDlgCAknDialogL ),
        ENTRY( "TestDlgConstructL", CTestSDKQueries::TestDlgConstructL ),
        ENTRY( "TestDlgDelete", CTestSDKQueries::TestDlgDelete ),
        ENTRY( "TestDlgExecuteLD", CTestSDKQueries::TestDlgExecuteLD ),
        ENTRY( "TestDlgPrepareLC", CTestSDKQueries::TestDlgPrepareLC ),
        ENTRY( "TestDlgRunLD", CTestSDKQueries::TestDlgRunLD ),
        ENTRY( "TestDlgSetEmphasis", CTestSDKQueries::TestDlgSetEmphasisL ),
        ENTRY( "TestDlgDynInitMenuPaneL", CTestSDKQueries::TestDlgDynInitMenuPaneL ),
        ENTRY( "TestDlgProcessCommandL", CTestSDKQueries::TestDlgProcessCommandL ),
        ENTRY( "TestDlgOfferKeyEventL", CTestSDKQueries::TestDlgOfferKeyEventL ),
        ENTRY( "TestDlgFocusChanged", CTestSDKQueries::TestDlgFocusChangedL ),
        ENTRY( "TestDlgHandlePointerEventL", CTestSDKQueries::TestDlgHandlePointerEventL ),
        ENTRY( "TestDlgOkToExitL", CTestSDKQueries::TestDlgOkToExitL ),
        ENTRY( "TestDlgDisplayMenuL", CTestSDKQueries::TestDlgDisplayMenuL ),
        ENTRY( "TestDlgHideMenu", CTestSDKQueries::TestDlgHideMenuL ),
        ENTRY( "TestDlgMenuShowing", CTestSDKQueries::TestDlgMenuShowingL ),
        ENTRY( "TestDlgSizeChanged", CTestSDKQueries::TestDlgSizeChangedL ),
        ENTRY( "TestDlgDraw", CTestSDKQueries::TestDlgDrawL ),
        ENTRY( "TestDlgMopSupplyObject", CTestSDKQueries::TestDlgMopSupplyObjectL ),
            
            //CAknListQueryControl
        ENTRY( "TestLqcConstructorL", CTestSDKQueries::TestLqcConstructorL ),
        ENTRY( "TestLqcConstructFromResourceL", CTestSDKQueries::TestLqcConstructFromResourceL ),
        ENTRY( "TestLqcDestructorL", CTestSDKQueries::TestLqcDestructorL ),
        ENTRY( "TestLqcMinimumSizeL", CTestSDKQueries::TestLqcMinimumSizeL ),
        ENTRY( "TestLqcCountComponentControlsL", CTestSDKQueries::TestLqcCountComponentControlsL ),
        ENTRY( "TestLqcComponentControlL", CTestSDKQueries::TestLqcComponentControlL ),
        ENTRY( "TestLqcOfferKeyEventL", CTestSDKQueries::TestLqcOfferKeyEventL ),
        ENTRY( "TestLqcDrawL", CTestSDKQueries::TestLqcDrawL ), 
        ENTRY( "TestLqcSetLayoutL", CTestSDKQueries::TestLqcSetLayoutL ),
        ENTRY( "TestLqcFocusChangedL", CTestSDKQueries::TestLqcFocusChangedL ),
        ENTRY( "TestLqcListboxL", CTestSDKQueries::TestLqcListboxL ),
        ENTRY( "TestLqcHeadingL", CTestSDKQueries::TestLqcHeadingL ),
        ENTRY( "TestLqcListtypeL", CTestSDKQueries::TestLqcListtypeL ),
        ENTRY( "TestLqcHandlePointerEventL", CTestSDKQueries::TestLqcHandlePointerEventL ),
        ENTRY( "TestLqclistboxL", CTestSDKQueries::TestLqclistboxL ),
        
            //CAknListQueryDialog
        ENTRY( "TestLqdlgConstructorL", CTestSDKQueries::TestLqdlgConstructorL ),
        ENTRY( "TestLqdlgConstructorLL", CTestSDKQueries::TestLqdlgConstructorLL ),
        ENTRY( "TestLqdlgDestructorL", CTestSDKQueries::TestLqdlgDestructorL ),
        ENTRY( "TestLqdlgSetSizeAndPositionL", CTestSDKQueries::TestLqdlgSetSizeAndPositionL ),
        ENTRY( "TestLqdlgOfferKeyEventL", CTestSDKQueries::TestLqdlgOfferKeyEventL ),
        ENTRY( "TestLqdlgHandleListBoxEventL", CTestSDKQueries::TestLqdlgHandleListBoxEventL ),
        ENTRY( "TestLqdlgSetItemTextArrayL", CTestSDKQueries::TestLqdlgSetItemTextArrayL ),
        ENTRY( "TestLqdlgSetOwnershipTypeL", CTestSDKQueries::TestLqdlgSetOwnershipTypeL ),
        ENTRY( "TestLqdlgSetIconArrayL", CTestSDKQueries::TestLqdlgSetIconArrayL ),
        ENTRY( "TestLqdlgListBoxL", CTestSDKQueries::TestLqdlgListBoxL ),
        ENTRY( "TestLqdlgListControlL", CTestSDKQueries::TestLqdlgListControlL ),
        ENTRY( "TestLqdlgMessageBoxL", CTestSDKQueries::TestLqdlgMessageBoxL ),
        ENTRY( "TestLqdlgQueryHeadingL", CTestSDKQueries::TestLqdlgQueryHeadingL ),
        ENTRY( "TestLqdlgActivateL", CTestSDKQueries::TestLqdlgActivateL ),
        ENTRY( "TestLqdlgHandlePointerEventL", CTestSDKQueries::TestLqdlgHandlePointerEventL ),
        ENTRY( "TestLqdlgPreLayoutDynInitL", CTestSDKQueries::TestLqdlgPreLayoutDynInitL ),
        ENTRY( "TestLqdlgPostLayoutDynInitL", CTestSDKQueries::TestLqdlgPostLayoutDynInitL ),
        ENTRY( "TestLqdlgOkToExitL", CTestSDKQueries::TestLqdlgOkToExitL ),
        ENTRY( "TestLqdlgBorderStyleL", CTestSDKQueries::TestLqdlgBorderStyleL ),
        ENTRY( "TestLqdlgCloseStateL", CTestSDKQueries::TestLqdlgCloseStateL ),
        ENTRY( "TestLqdlgFindBoxL", CTestSDKQueries::TestLqdlgFindBoxL ),
        ENTRY( "TestLqdlgSetToneL", CTestSDKQueries::TestLqdlgSetToneL ),
        ENTRY( "TestLqdlgHandleResourceChangeL", CTestSDKQueries::TestLqdlgHandleResourceChangeL ),
        ENTRY( "TestLqdlgPublishDialogL", CTestSDKQueries::TestLqdlgPublishDialogL ),
        ENTRY( "TestLqdlgSetMediatorObserverL", CTestSDKQueries::TestLqdlgSetMediatorObserverL ),
        
            //CAknMessageQueryControl
        ENTRY( "TestMqcConstructFromResourceL", CTestSDKQueries::TestMqcConstructFromResourceL ),
        ENTRY( "TestMqcSetMessageTextL", CTestSDKQueries::TestMqcSetMessageTextL ),
        ENTRY( "TestMqcLinkHighLightedL", CTestSDKQueries::TestMqcLinkHighLightedL ),
        ENTRY( "TestMqcDrawL", CTestSDKQueries::TestMqcDrawL ),
        
            //CAknMessageQueryDialog
        ENTRY( "TestMqdlgNewL", CTestSDKQueries::TestMqdlgNewL ),
        ENTRY( "TestMqdlgDestructorL", CTestSDKQueries::TestMqdlgDestructorL ),
        ENTRY( "TestMqdlgConstructorOneL", CTestSDKQueries::TestMqdlgConstructorOneL ),
        ENTRY( "TestMqdlgSetMessageTextOneL", CTestSDKQueries::TestMqdlgSetMessageTextOneL ),
        ENTRY( "TestMqdlgSetHeaderTextOneL", CTestSDKQueries::TestMqdlgSetHeaderTextOneL ),
        ENTRY( "TestMqdlgSetLinkTextL", CTestSDKQueries::TestMqdlgSetLinkTextL ),
        ENTRY( "TestMqdlgSetLinkL", CTestSDKQueries::TestMqdlgSetLinkL ),
        ENTRY( "TestMqdlgOfferKeyEventL", CTestSDKQueries::TestMqdlgOfferKeyEventL ),
        ENTRY( "TestMqdlgHandlePointerEventL", CTestSDKQueries::TestMqdlgHandlePointerEventL ),
        ENTRY( "TestMqdlgPreLayoutDynInitL", CTestSDKQueries::TestMqdlgPreLayoutDynInitL ),
        ENTRY( "TestMqdlgSetSizeAndPositionL", CTestSDKQueries::TestMqdlgSetSizeAndPositionL ),
        ENTRY( "TestMqdlgPostLayoutDynInitL", CTestSDKQueries::TestMqdlgPostLayoutDynInitL ),
        ENTRY( "TestMqdlgProcessCommandL", CTestSDKQueries::TestMqdlgProcessCommandL ),
        ENTRY( "TestMqdlgConstructorTwoL", CTestSDKQueries::TestMqdlgConstructorTwoL ),
        ENTRY( "TestMqdlgConstructorThreeL", CTestSDKQueries::TestMqdlgConstructorThreeL ),
        ENTRY( "TestMqdlgConstructorFourL", CTestSDKQueries::TestMqdlgConstructorFourL ),
        ENTRY( "TestMqdlgConstructorFiveL", CTestSDKQueries::TestMqdlgConstructorFiveL ),
        ENTRY( "TestMqdlgSetMessageTextTwoL", CTestSDKQueries::TestMqdlgSetMessageTextTwoL ),
        ENTRY( "TestMqdlgSetMessageTextThreeL", CTestSDKQueries::TestMqdlgSetMessageTextThreeL ),
        ENTRY( "TestMqdlgSetHeaderTextTwoL", CTestSDKQueries::TestMqdlgSetHeaderTextTwoL ),
        ENTRY( "TestMqdlgSetHeaderTextThreeL", CTestSDKQueries::TestMqdlgSetHeaderTextThreeL ),
        ENTRY( "TestMqdlgConstructorSixL", CTestSDKQueries::TestMqdlgConstructorSixL ),
        
            //CAknMultilineQueryControl
        ENTRY( "TestMlqcConstructorL", CTestSDKQueries::TestMlqcConstructorL ),
        ENTRY( "TestMlqcDestructorL", CTestSDKQueries::TestMlqcDestructorL ),
        ENTRY( "TestMlqcSetNbrOfPromptLinesL", CTestSDKQueries::TestMlqcSetNbrOfPromptLinesL ),
        ENTRY( "TestMlqcIsFirstL", CTestSDKQueries::TestMlqcIsFirstL ),
        ENTRY( "TestMlqcIsSecondL", CTestSDKQueries::TestMlqcIsSecondL ),
        ENTRY( "TestMlqcControlByLayoutOrNullL", CTestSDKQueries::TestMlqcControlByLayoutOrNullL ),
        ENTRY( "TestMlqcMinimumSizeL", CTestSDKQueries::TestMlqcMinimumSizeL ),
        ENTRY( "TestMlqcHandlePointerEventL", CTestSDKQueries::TestMlqcHandlePointerEventL ),
        ENTRY( "TestMlqcHandleResourceChangeL", CTestSDKQueries::TestMlqcHandleResourceChangeL ),
        
            //CAknExtMultilineQueryControl
        ENTRY( "TestExtMlqcConstructorL", CTestSDKQueries::TestExtMlqcConstructorL ),
        ENTRY( "TestExtMlqcDestructorL", CTestSDKQueries::TestExtMlqcDestructorL ),
        ENTRY( "TestExtMlqcSetNbrOfPromptLinesL", CTestSDKQueries::TestExtMlqcSetNbrOfPromptLinesL ),
        ENTRY( "TestExtMlqcIsFirstL", CTestSDKQueries::TestExtMlqcIsFirstL ),
        ENTRY( "TestExtMlqcIsSecondL", CTestSDKQueries::TestExtMlqcIsSecondL ),
        ENTRY( "TestExtMlqcControlByLayoutOrNullL", CTestSDKQueries::TestExtMlqcControlByLayoutOrNullL ),
        ENTRY( "TestExtMlqcMinimumSizeL", CTestSDKQueries::TestExtMlqcMinimumSizeL ),
        ENTRY( "TestExtMlqcHandlePointerEventL", CTestSDKQueries::TestExtMlqcHandlePointerEventL ),
        ENTRY( "TestExtMlqcHandleResourceChangeL", CTestSDKQueries::TestExtMlqcHandleResourceChangeL ),
        
            //CAknQueryControl
        ENTRY( "TestQcConstructorL", CTestSDKQueries::TestQcConstructorL ),
        ENTRY( "TestQcDestructorL", CTestSDKQueries::TestQcDestructorL ),
        ENTRY( "TestQcConstructFromResourceL", CTestSDKQueries::TestQcConstructFromResourceL ),
        ENTRY( "TestQcSetQueryControlObserverL", CTestSDKQueries::TestQcSetQueryControlObserverL ),
        ENTRY( "TestQcReadPromptL", CTestSDKQueries::TestQcReadPromptL ),
        ENTRY( "TestQcSetPromptL", CTestSDKQueries::TestQcSetPromptL ),
        ENTRY( "TestQcGetTextL", CTestSDKQueries::TestQcGetTextL ),
        ENTRY( "TestQcGetTimeL", CTestSDKQueries::TestQcGetTimeL ),
        ENTRY( "TestQcGetNumberL", CTestSDKQueries::TestQcGetNumberL ),
        ENTRY( "TestQcGetFloatingPointNumberL", CTestSDKQueries::TestQcGetFloatingPointNumberL ),
        ENTRY( "TestQcGetDurationL", CTestSDKQueries::TestQcGetDurationL ),
        ENTRY( "TestQcGetLocationL", CTestSDKQueries::TestQcGetLocationL ),
        ENTRY( "TestQcSetTimeL", CTestSDKQueries::TestQcSetTimeL ),
        ENTRY( "TestQcSetDurationL", CTestSDKQueries::TestQcSetDurationL ),
        ENTRY( "TestQcSetNumberL", CTestSDKQueries::TestQcSetNumberL ),
        ENTRY( "TestQcSetFloatingPointNumberL", CTestSDKQueries::TestQcSetFloatingPointNumberL ),
        ENTRY( "TestQcSetLocationL", CTestSDKQueries::TestQcSetLocationL ),
        ENTRY( "TestQcSetLocationL", CTestSDKQueries::TestQcSetLocationL ),
        ENTRY( "TestQcSetTextEntryLengthL", CTestSDKQueries::TestQcSetTextEntryLengthL ),
        ENTRY( "TestQcGetTextEntryLengthL", CTestSDKQueries::TestQcGetTextEntryLengthL ),
        ENTRY( "TestQcSetMinimumAndMaximumOneL", CTestSDKQueries::TestQcSetMinimumAndMaximumOneL ),
        ENTRY( "TestQcSetMinimumAndMaximumTwoL", CTestSDKQueries::TestQcSetMinimumAndMaximumTwoL ),
        ENTRY( "TestQcSetMinimumAndMaximumThreeL", CTestSDKQueries::TestQcSetMinimumAndMaximumThreeL ),
        ENTRY( "TestQcCheckNumberL", CTestSDKQueries::TestQcCheckNumberL ),
        ENTRY( "TestQcSetNumberOfEditorLinesL", CTestSDKQueries::TestQcSetNumberOfEditorLinesL ),
        ENTRY( "TestQcSetMinimumAndMaximumL", CTestSDKQueries::TestQcSetMinimumAndMaximumL ),
        ENTRY( "TestQcGetTextLengthL", CTestSDKQueries::TestQcGetTextLengthL ),
        ENTRY( "TestQcNbrOfEditorLinesL", CTestSDKQueries::TestQcNbrOfEditorLinesL ),
        ENTRY( "TestQcNbrOfPromptLinesL", CTestSDKQueries::TestQcNbrOfPromptLinesL ),
        ENTRY( "TestQcControlByLayoutOrNullL", CTestSDKQueries::TestQcControlByLayoutOrNullL ),
        ENTRY( "TestQcSetImageL", CTestSDKQueries::TestQcSetImageL ),
        ENTRY( "TestQcSetImageFullL", CTestSDKQueries::TestQcSetImageFullL ),
        ENTRY( "TestQcSetAnimationL", CTestSDKQueries::TestQcSetAnimationL ),
        ENTRY( "TestQcStartAnimationL", CTestSDKQueries::TestQcStartAnimationL ),
        ENTRY( "TestQcCancelAnimationL", CTestSDKQueries::TestQcCancelAnimationL ),
        ENTRY( "TestQcOfferKeyEventL", CTestSDKQueries::TestQcOfferKeyEventL ),
        ENTRY( "TestQcMinimumSizeL", CTestSDKQueries::TestQcMinimumSizeL ),
        ENTRY( "TestQcHandleEdwinEventL", CTestSDKQueries::TestQcHandleEdwinEventL ),
        ENTRY( "TestQcHandleEdwinSizeEventL", CTestSDKQueries::TestQcHandleEdwinSizeEventL ),
        ENTRY( "TestQcHandleControlEventL", CTestSDKQueries::TestQcHandleControlEventL ),
        ENTRY( "TestQcQueryTypeL", CTestSDKQueries::TestQcQueryTypeL ),
        ENTRY( "TestQcHandlePointerEventL", CTestSDKQueries::TestQcHandlePointerEventL ),
        ENTRY( "TestQcHandleResourceChangeL", CTestSDKQueries::TestQcHandleResourceChangeL ),
        ENTRY( "TestExtQcConstructorL", CTestSDKQueries::TestExtQcConstructorL ),
        ENTRY( "TestExtQcDestructorL", CTestSDKQueries::TestExtQcDestructorL ),
        ENTRY( "TestExtQcGetInetAddressL", CTestSDKQueries::TestExtQcGetInetAddressL ),
        ENTRY( "TestExtQcSetInetAddressL", CTestSDKQueries::TestExtQcSetInetAddressL ),
        ENTRY( "TestExtQcGetFixedPointNumberL", CTestSDKQueries::TestExtQcGetFixedPointNumberL ),
        ENTRY( "TestExtQcSetFixedPointNumberL", CTestSDKQueries::TestExtQcSetFixedPointNumberL ),
        ENTRY( "TestExtQcSetMinimumAndMaximumL", CTestSDKQueries::TestExtQcSetMinimumAndMaximumL ),
        ENTRY( "TestExtQcSetMinimumAndMaximumLL", CTestSDKQueries::TestExtQcSetMinimumAndMaximumLL ),
        ENTRY( "TestExtQcControlByLayoutOrNullL", CTestSDKQueries::TestExtQcControlByLayoutOrNullL ),
        ENTRY( "TestExtQcHandleControlEventL", CTestSDKQueries::TestExtQcHandleControlEventL ),
        ENTRY( "TestQcSetTextL", CTestSDKQueries::TestQcSetTextL ),
        ENTRY( "TestExtQcHandlePointerEventL", CTestSDKQueries::TestExtQcHandlePointerEventL ),
        
            //aknquerydata.h
        ENTRY( "TestQdataGetMaxTextLengthL", CTestSDKQueries::TestQdataGetMaxTextLengthL ),
        
            //aknquerydialog.h
                //CAknQueryDialog
        ENTRY( "TestQdlgNewLOneL", CTestSDKQueries::TestQdlgNewLOneL ),
        ENTRY( "TestQdlgNewLTwoL", CTestSDKQueries::TestQdlgNewLTwoL ),
        ENTRY( "TestQdlgNewLThreeL", CTestSDKQueries::TestQdlgNewLThreeL ),
        ENTRY( "TestQdlgNewLFourL", CTestSDKQueries::TestQdlgNewLFourL ),
        ENTRY( "TestQdlgNewLFiveL", CTestSDKQueries::TestQdlgNewLFiveL ),
        ENTRY( "TestQdlgNewLSixL", CTestSDKQueries::TestQdlgNewLSixL ),
        ENTRY( "TestQdlgNewLSevenL", CTestSDKQueries::TestQdlgNewLSevenL ),
        ENTRY( "TestQdlgNewLEightL", CTestSDKQueries::TestQdlgNewLEightL ),
        ENTRY( "TestQdlgDestructorL", CTestSDKQueries::TestQdlgDestructorL ),
        ENTRY( "TestQdlgConstructorOneL", CTestSDKQueries::TestQdlgConstructorOneL ),
        ENTRY( "TestQdlgQueryHeadingL", CTestSDKQueries::TestQdlgQueryHeadingL ),
        ENTRY( "TestQdlgHeadingL", CTestSDKQueries::TestQdlgHeadingL ),
        ENTRY( "TestQdlgSetPromptL", CTestSDKQueries::TestQdlgSetPromptL ),
        ENTRY( "TestQdlgMakeLeftSoftkeyVisibleL", CTestSDKQueries::TestQdlgMakeLeftSoftkeyVisibleL ),
        ENTRY( "TestQdlgSetEmergencyCallSupportL", CTestSDKQueries::TestQdlgSetEmergencyCallSupportL ),
        ENTRY( "TestQdlgRemoveEditorIndicatorL", CTestSDKQueries::TestQdlgRemoveEditorIndicatorL ),
        ENTRY( "TestQdlgSetPredictiveTextInputPermittedL", 
            CTestSDKQueries::TestQdlgSetPredictiveTextInputPermittedL ),
        ENTRY( "TestQdlgRunLDL", CTestSDKQueries::TestQdlgRunLDL ),
        ENTRY( "TestQdlgExecuteLDOneL", CTestSDKQueries::TestQdlgExecuteLDOneL ),
        ENTRY( "TestQdlgExecuteLDTwoL", CTestSDKQueries::TestQdlgExecuteLDTwoL ),
        ENTRY( "TestQdlgOfferKeyEventL", CTestSDKQueries::TestQdlgOfferKeyEventL ),
        ENTRY( "TestQdlgHandlePointerEventL", CTestSDKQueries::TestQdlgHandlePointerEventL ),
        ENTRY( "TestQdlgMaxTextLengthOneL", CTestSDKQueries::TestQdlgMaxTextLengthOneL ),
        ENTRY( "TestQdlgSetSizeAndPositionL", CTestSDKQueries::TestQdlgSetSizeAndPositionL ),
        ENTRY( "TestQdlgPreLayoutDynInitL", CTestSDKQueries::TestQdlgPreLayoutDynInitL ),
        ENTRY( "TestQdlgPostLayoutDynInitL", CTestSDKQueries::TestQdlgPostLayoutDynInitL ),
        ENTRY( "TestQdlgOkToExitL", CTestSDKQueries::TestQdlgOkToExitL ),
        ENTRY( "TestQdlgHandleQueryEditorSizeEventL", 
            CTestSDKQueries::TestQdlgHandleQueryEditorSizeEventL ),
        ENTRY( "TestQdlgHandleQueryEditorStateEventL", 
            CTestSDKQueries::TestQdlgHandleQueryEditorStateEventL ),
        ENTRY( "TestQdlgNeedToDismissQueryL", CTestSDKQueries::TestQdlgNeedToDismissQueryL ),
        ENTRY( "TestQdlgDismissQueryL", CTestSDKQueries::TestQdlgDismissQueryL ),
        ENTRY( "TestQdlgUpdateLeftSoftKeyL", CTestSDKQueries::TestQdlgUpdateLeftSoftKeyL ),
        ENTRY( "TestQdlgDoSetPromptL", CTestSDKQueries::TestQdlgDoSetPromptL ),
        ENTRY( "TestQdlgQueryControlL", CTestSDKQueries::TestQdlgQueryControlL ),
        ENTRY( "TestQdlgPromptL", CTestSDKQueries::TestQdlgPromptL ),
        ENTRY( "TestQdlgConstructorTwoL", CTestSDKQueries::TestQdlgConstructorTwoL ),
        ENTRY( "TestQdlgConstructorThreeL", CTestSDKQueries::TestQdlgConstructorThreeL ),
        ENTRY( "TestQdlgSetHeaderTextL", CTestSDKQueries::TestQdlgSetHeaderTextL ),
        ENTRY( "TestQdlgSetHeaderImageL", CTestSDKQueries::TestQdlgSetHeaderImageL ),
        ENTRY( "TestQdlgRunDlgLDL", CTestSDKQueries::TestQdlgRunDlgLDL ),
        ENTRY( "TestQdlgMaxTextLengthTwoL", CTestSDKQueries::TestQdlgMaxTextLengthTwoL ),
        ENTRY( "TestQdlgInputCapabilitiesL", CTestSDKQueries::TestQdlgInputCapabilitiesL ),
        ENTRY( "TestQdlgSetEmergencyCallSupportForCBAL", CTestSDKQueries::TestQdlgSetEmergencyCallSupportForCBAL ),
        
        ENTRY( "TestTextQdlgNewL", CTestSDKQueries::TestTextQdlgNewL ), 
        ENTRY( "TestTextQdlgConstructorL", CTestSDKQueries::TestTextQdlgConstructorL ),
        ENTRY( "TestTextQdlgDestructorL", CTestSDKQueries::TestTextQdlgDestructorL ),
        ENTRY( "TestTextQdlgSetMaxLengthL", CTestSDKQueries::TestTextQdlgSetMaxLengthL ),
        ENTRY( "TestTextQdlgCheckIfEntryTextOkL", CTestSDKQueries::TestTextQdlgCheckIfEntryTextOkL ),
        ENTRY( "TestTextQdlgSetDefaultInputModeL", CTestSDKQueries::TestTextQdlgSetDefaultInputModeL ),
        ENTRY( "TestTextQdlgPreLayoutDynInitL", CTestSDKQueries::TestTextQdlgPreLayoutDynInitL ),
        ENTRY( "TestTextQdlgOkToExitL", CTestSDKQueries::TestTextQdlgOkToExitL ),
        ENTRY( "TestTextQdlgHandleQueryEditorSizeEventL", CTestSDKQueries::TestTextQdlgHandleQueryEditorSizeEventL ),
        ENTRY( "TestTextQdlgHandlePointerEventL", CTestSDKQueries::TestTextQdlgHandlePointerEventL ),
        ENTRY( "TestTextQdlgConstructorLL", CTestSDKQueries::TestTextQdlgConstructorLL ),
        
        ENTRY( "TestNumberQdlgNewL", CTestSDKQueries::TestNumberQdlgNewL ),
        ENTRY( "TestNumberQdlgConstructorL", CTestSDKQueries::TestNumberQdlgConstructorL ),
        ENTRY( "TestNumberQdlgDestructorL", CTestSDKQueries::TestNumberQdlgDestructorL ),
        ENTRY( "TestNumberQdlgSetMinimumAndMaximumL", CTestSDKQueries::TestNumberQdlgSetMinimumAndMaximumL ),
        ENTRY( "TestNumberQdlgHandlePointerEventL", CTestSDKQueries::TestNumberQdlgHandlePointerEventL ),
        ENTRY( "TestNumberQdlgPreLayoutDynInitL", CTestSDKQueries::TestNumberQdlgPreLayoutDynInitL ),
        ENTRY( "TestNumberQdlgOkToExitL", CTestSDKQueries::TestNumberQdlgOkToExitL ),
        ENTRY( "TestNumberQdlgNumberOneL", CTestSDKQueries::TestNumberQdlgNumberOneL ),
        ENTRY( "TestNumberQdlgNumberTwoL", CTestSDKQueries::TestNumberQdlgNumberTwoL ),
        
        ENTRY( "TestTimeQdlgNewL", CTestSDKQueries::TestTimeQdlgNewL ),
        ENTRY( "TestTimeQdlgConstructorL", CTestSDKQueries::TestTimeQdlgConstructorL ),
        ENTRY( "TestTimeQdlgDestructorL", CTestSDKQueries::TestTimeQdlgDestructorL ),
        ENTRY( "TestTimeQdlgSetMinimumAndMaximumL", CTestSDKQueries::TestTimeQdlgSetMinimumAndMaximumL ),
        ENTRY( "TestTimeQdlgHandlePointerEventL", CTestSDKQueries::TestTimeQdlgHandlePointerEventL ),
        ENTRY( "TestTimeQdlgPreLayoutDynInitL", CTestSDKQueries::TestTimeQdlgPreLayoutDynInitL ),
        ENTRY( "TestTimeQdlgOkToExitL", CTestSDKQueries::TestTimeQdlgOkToExitL ),
        ENTRY( "TestTimeQdlgTimeOneL", CTestSDKQueries::TestTimeQdlgTimeOneL ),
        ENTRY( "TestTimeQdlgTimeTwoL", CTestSDKQueries::TestTimeQdlgTimeTwoL ),
        ENTRY( "TestTimeQdlgConstructorLL", CTestSDKQueries::TestTimeQdlgConstructorLL ),
        
        ENTRY( "TestDurationNewL", CTestSDKQueries::TestDurationNewL ),
        ENTRY( "TestDurationConstructorL", CTestSDKQueries::TestDurationConstructorL ),
        ENTRY( "TestDurationDestructorL", CTestSDKQueries::TestDurationDestructorL ),
        ENTRY( "TestDurationSetMinimumAndMaximumL", CTestSDKQueries::TestDurationSetMinimumAndMaximumL ),
        ENTRY( "TestDurationHandlePointerEventL", CTestSDKQueries::TestDurationHandlePointerEventL ),
        ENTRY( "TestDurationPreLayoutDynInitL", CTestSDKQueries::TestDurationPreLayoutDynInitL ),
        ENTRY( "TestDurationOkToExitL", CTestSDKQueries::TestDurationOkToExitL ),
        ENTRY( "TestDurationDurationOneL", CTestSDKQueries::TestDurationDurationOneL ),
        ENTRY( "TestDurationDurationTwoL", CTestSDKQueries::TestDurationDurationTwoL ),
        
        ENTRY( "TestFloatingQdlgNewL", CTestSDKQueries::TestFloatingQdlgNewL ),
        ENTRY( "TestFloatingQdlgConstructorL", CTestSDKQueries::TestFloatingQdlgConstructorL ),
        ENTRY( "TestFloatingQdlgDestructorL", CTestSDKQueries::TestFloatingQdlgDestructorL ),
        ENTRY( "TestFloatingQdlgSetMinimumAndMaximumL", CTestSDKQueries::TestFloatingQdlgSetMinimumAndMaximumL ),
        ENTRY( "TestFloatingQdlgHandlePointerEventL", CTestSDKQueries::TestFloatingQdlgHandlePointerEventL ),
        ENTRY( "TestFloatingQdlgPreLayoutDynInitL", CTestSDKQueries::TestFloatingQdlgPreLayoutDynInitL ),
        ENTRY( "TestFloatingQdlgOkToExitL", CTestSDKQueries::TestFloatingQdlgOkToExitL ),
        ENTRY( "TestFloatingQdlgNumberOneL", CTestSDKQueries::TestFloatingQdlgNumberOneL ),
        ENTRY( "TestFloatingQdlgNumberTwoL", CTestSDKQueries::TestFloatingQdlgNumberTwoL ),
        
        ENTRY( "TestMultiLineDataQdlgNewLOneL", CTestSDKQueries::TestMultiLineDataQdlgNewLOneL ),
        ENTRY( "TestMultiLineDataQdlgNewLTwoL", CTestSDKQueries::TestMultiLineDataQdlgNewLTwoL ),
        ENTRY( "TestMultiLineDataQdlgNewLThreeL", CTestSDKQueries::TestMultiLineDataQdlgNewLThreeL ),
        ENTRY( "TestMultiLineDataQdlgNewLFourL", CTestSDKQueries::TestMultiLineDataQdlgNewLFourL ),
        ENTRY( "TestMultiLineDataQdlgNewLFiveL", CTestSDKQueries::TestMultiLineDataQdlgNewLFiveL ),
        ENTRY( "TestMultiLineDataQdlgNewLSixL", CTestSDKQueries::TestMultiLineDataQdlgNewLSixL ),
        ENTRY( "TestMultiLineDataQdlgNewLSevenL", CTestSDKQueries::TestMultiLineDataQdlgNewLSevenL ),
        ENTRY( "TestMultiLineDataQdlgNewLEightL", CTestSDKQueries::TestMultiLineDataQdlgNewLEightL ),
        ENTRY( "TestMultiLineDataQdlgDestructorL", CTestSDKQueries::TestMultiLineDataQdlgDestructorL ),
        ENTRY( "TestMultiLineDataQdlgConstructorOneL", CTestSDKQueries::TestMultiLineDataQdlgConstructorOneL ),
        ENTRY( "TestMultiLineDataQdlgSetPromptL", CTestSDKQueries::TestMultiLineDataQdlgSetPromptL ),
        ENTRY( "TestMultiLineDataQdlgSetMaxLengthOfFirstEditorL", CTestSDKQueries::TestMultiLineDataQdlgSetMaxLengthOfFirstEditorL ),
        ENTRY( "TestMultiLineDataQdlgSetMaxLengthOfSecondEditorL", CTestSDKQueries::TestMultiLineDataQdlgSetMaxLengthOfSecondEditorL ),
        ENTRY( "TestMultiLineDataQdlgHandlePointerEventL", CTestSDKQueries::TestMultiLineDataQdlgHandlePointerEventL ),
        ENTRY( "TestMultiLineDataQdlgOkToExitL", CTestSDKQueries::TestMultiLineDataQdlgOkToExitL ),
        ENTRY( "TestMultiLineDataQdlgPreLayoutDynInitL", CTestSDKQueries::TestMultiLineDataQdlgPreLayoutDynInitL ),
        ENTRY( "TestMultiLineDataQdlgHandleResourceChangeL", CTestSDKQueries::TestMultiLineDataQdlgHandleResourceChangeL ),
        ENTRY( "TestMultiLineDataQdlgUpdateLeftSoftKeyL", CTestSDKQueries::TestMultiLineDataQdlgUpdateLeftSoftKeyL ),
        ENTRY( "TestMultiLineDataQdlgDoSetPromptL", CTestSDKQueries::TestMultiLineDataQdlgDoSetPromptL ),
        ENTRY( "TestMultiLineDataQdlgNeedToDismissQueryL", CTestSDKQueries::TestMultiLineDataQdlgNeedToDismissQueryL ),
        ENTRY( "TestMultiLineDataQdlgFirstControlL", CTestSDKQueries::TestMultiLineDataQdlgFirstControlL ),
        ENTRY( "TestMultiLineDataQdlgSecondControlL", CTestSDKQueries::TestMultiLineDataQdlgSecondControlL ),
        ENTRY( "TestMultiLineDataQdlgQueryControlL", CTestSDKQueries::TestMultiLineDataQdlgQueryControlL ),
        ENTRY( "TestMultiLineDataQdlgQueryHeadingL", CTestSDKQueries::TestMultiLineDataQdlgQueryHeadingL ),
        ENTRY( "TestMultiLineDataSecondPromptL", CTestSDKQueries::TestMultiLineDataSecondPromptL ),
        ENTRY( "TestMultiLineDataQdlgConstructorTwoL", CTestSDKQueries::TestMultiLineDataQdlgConstructorTwoL ),
        ENTRY( "TestMultiLineDataQdlgConstructorThreeL", CTestSDKQueries::TestMultiLineDataQdlgConstructorThreeL ),
        ENTRY( "TestMultiLineDataQdlgConstructorFourL", CTestSDKQueries::TestMultiLineDataQdlgConstructorFourL ),
        ENTRY( "TestMultiLineDataQdlgConstructorFiveL", CTestSDKQueries::TestMultiLineDataQdlgConstructorFiveL ),
        ENTRY( "TestMultiLineDataQdlgConstructorSixL", CTestSDKQueries::TestMultiLineDataQdlgConstructorSixL ),
        ENTRY( "TestMultiLineDataQdlgConstructorSevenL", CTestSDKQueries::TestMultiLineDataQdlgConstructorSevenL ),
        ENTRY( "TestMultiLineDataQdlgConstructorEightL", CTestSDKQueries::TestMultiLineDataQdlgConstructorEightL ),
        
        ENTRY( "TestIpAddressQdlgNewL", CTestSDKQueries::TestIpAddressQdlgNewL ),
        ENTRY( "TestIpAddressQdlgDestructorL", CTestSDKQueries::TestIpAddressQdlgDestructorL ),
        ENTRY( "TestIpAddressQdlgSetMinimumAndMaximumL", CTestSDKQueries::TestIpAddressQdlgSetMinimumAndMaximumL ),
        ENTRY( "TestIpAddressQdlgNeedToDismissQueryL", CTestSDKQueries::TestIpAddressQdlgNeedToDismissQueryL ),
        ENTRY( "TestIpAddressQdlgQueryControlL", CTestSDKQueries::TestIpAddressQdlgQueryControlL ),
        ENTRY( "TestIpAddressQdlgSetSizeAndPositionL", CTestSDKQueries::TestIpAddressQdlgSetSizeAndPositionL ),
        ENTRY( "TestIpAddressQdlgPreLayoutDynInitL", CTestSDKQueries::TestIpAddressQdlgPreLayoutDynInitL ),
        ENTRY( "TestIpAddressQdlgPostLayoutDynInitL", CTestSDKQueries::TestIpAddressQdlgPostLayoutDynInitL ),
        ENTRY( "TestIpAddressQdlgDoSetPromptL", CTestSDKQueries::TestIpAddressQdlgDoSetPromptL ),
        ENTRY( "TestIpAddressQdlgOkToExitL", CTestSDKQueries::TestIpAddressQdlgOkToExitL ),
        ENTRY( "TestIpAddressQdlgUpdateLeftSoftKeyL", CTestSDKQueries::TestIpAddressQdlgUpdateLeftSoftKeyL ),
        ENTRY( "TestIpAddressQdlgInetAddrOneL", CTestSDKQueries::TestIpAddressQdlgInetAddrOneL ),
        ENTRY( "TestIpAddressQdlgInetAddrTwoL", CTestSDKQueries::TestIpAddressQdlgInetAddrTwoL ),
        
        ENTRY( "TestFixedPointQdlgNewL", CTestSDKQueries::TestFixedPointQdlgNewL ),
        ENTRY( "TestFixedPointQdlgDestructorL", CTestSDKQueries::TestFixedPointQdlgDestructorL ),
        ENTRY( "TestFixedPointQdlgSetMinimumAndMaximumL", CTestSDKQueries::TestFixedPointQdlgSetMinimumAndMaximumL ),
        ENTRY( "TestFixedPointQdlgNeedToDismissQueryL", CTestSDKQueries::TestFixedPointQdlgNeedToDismissQueryL ),
        ENTRY( "TestFixedPointQdlgQueryControlL", CTestSDKQueries::TestFixedPointQdlgQueryControlL ),
        ENTRY( "TestFixedPointQdlgSetSizeAndPositionL", CTestSDKQueries::TestFixedPointQdlgSetSizeAndPositionL ),
        ENTRY( "TestFixedPointQdlgPreLayoutDynInitL", CTestSDKQueries::TestFixedPointQdlgPreLayoutDynInitL ),
        ENTRY( "TestFixedPointQdlgPostLayoutDynInitL", CTestSDKQueries::TestFixedPointQdlgPostLayoutDynInitL ),
        ENTRY( "TestFixedPointQdlgDoSetPromptL", CTestSDKQueries::TestFixedPointQdlgDoSetPromptL ),
        ENTRY( "TestFixedPointQdlgOkToExitL", CTestSDKQueries::TestFixedPointQdlgOkToExitL ),
        ENTRY( "TestFixedPointQdlgUpdateLeftSoftKeyL", CTestSDKQueries::TestFixedPointQdlgUpdateLeftSoftKeyL ),
        ENTRY( "TestFixedPointQdlgNumberOneL", CTestSDKQueries::TestFixedPointQdlgNumberOneL ),
        ENTRY( "TestFixedPointQdlgNumberTwoL", CTestSDKQueries::TestFixedPointQdlgNumberTwoL ),
        
        ENTRY( "TestMultiLineIpQdlgNewL", CTestSDKQueries::TestMultiLineIpQdlgNewL ),
        ENTRY( "TestMultiLineIpQdlgDestructorL", CTestSDKQueries::TestMultiLineIpQdlgDestructorL ),
        ENTRY( "TestMultiLineIpQdlgSetPromptL", CTestSDKQueries::TestMultiLineIpQdlgSetPromptL ),
        ENTRY( "TestMultiLineIpQdlgSetMaxLengthOfFirstEditorL", CTestSDKQueries::TestMultiLineIpQdlgSetMaxLengthOfFirstEditorL ),
        ENTRY( "TestMultiLineIpQdlgSetMaxLengthOfSecondEditorL", CTestSDKQueries::TestMultiLineIpQdlgSetMaxLengthOfSecondEditorL ),
        ENTRY( "TestMultiLineIpQdlgOkToExitL", CTestSDKQueries::TestMultiLineIpQdlgOkToExitL ),
        ENTRY( "TestMultiLineIpQdlgPreLayoutDynInitL", CTestSDKQueries::TestMultiLineIpQdlgPreLayoutDynInitL ),
        ENTRY( "TestMultiLineIpQdlgHandleResourceChangeL", CTestSDKQueries::TestMultiLineIpQdlgHandleResourceChangeL ),
        ENTRY( "TestMultiLineIpQdlgUpdateLeftSoftKeyL", CTestSDKQueries::TestMultiLineIpQdlgUpdateLeftSoftKeyL ),
        ENTRY( "TestMultiLineIpQdlgDoSetPromptL", CTestSDKQueries::TestMultiLineIpQdlgDoSetPromptL ),
        ENTRY( "TestMultiLineIpQdlgNeedToDismissQueryL", CTestSDKQueries::TestMultiLineIpQdlgNeedToDismissQueryL ),
        ENTRY( "TestMultiLineIpQdlgFirstControlL", CTestSDKQueries::TestMultiLineIpQdlgFirstControlL ),
        ENTRY( "TestMultiLineIpQdlgSecondControlL", CTestSDKQueries::TestMultiLineIpQdlgSecondControlL ),
        ENTRY( "TestMultiLineIpQdlgQueryControlL", CTestSDKQueries::TestMultiLineIpQdlgQueryControlL ),
        ENTRY( "TestMultiLineIpQdlgSecondPromptL", CTestSDKQueries::TestMultiLineIpQdlgSecondPromptL ),
        
    //AknQueryValue.h    
        ENTRY( "TestQVSetQueryModeL", CTestSDKQueries::TestQVSetQueryModeL ),
        ENTRY( "TestQVSetSettingPageResourceIdsL", CTestSDKQueries::TestQVSetSettingPageResourceIdsL ),
        ENTRY( "TestQVSetAutoAppendL", CTestSDKQueries::TestQVSetAutoAppendL ),
        ENTRY( "TestQVAppendValueIfNewL", CTestSDKQueries::TestQVAppendValueIfNewL ),
        
    //AknQueryValueDate.h
        ENTRY( "TestQVDNewL", CTestSDKQueries::TestQVDNewL ),
        ENTRY( "TestQVDNewLCL", CTestSDKQueries::TestQVDNewLCL ),
        ENTRY( "TestQVDDestructorL", CTestSDKQueries::TestQVDDestructorL ),
        ENTRY( "TestQVDSetArrayL", CTestSDKQueries::TestQVDSetArrayL ),
        ENTRY( "TestQVDSetQueryCaptionL", CTestSDKQueries::TestQVDSetQueryCaptionL ),
        ENTRY( "TestQVDValueL", CTestSDKQueries::TestQVDValueL ),
        ENTRY( "TestQVDMdcArrayL", CTestSDKQueries::TestQVDMdcArrayL ),
        ENTRY( "TestQVDCurrentValueTextLCL", CTestSDKQueries::TestQVDCurrentValueTextLCL ),
        ENTRY( "TestQVDCurrentValueIndexL", CTestSDKQueries::TestQVDCurrentValueIndexL ),
        ENTRY( "TestQVDCreateEditorL", CTestSDKQueries::TestQVDCreateEditorL ),
        
        ENTRY( "TestQVDANewL", CTestSDKQueries::TestQVDANewL ),
        ENTRY( "TestQVDANewLCL", CTestSDKQueries::TestQVDANewLCL ),
        ENTRY( "TestQVDADestructorL", CTestSDKQueries::TestQVDADestructorL ),
        ENTRY( "TestQVDASetArrayL", CTestSDKQueries::TestQVDASetArrayL ),
        ENTRY( "TestQVDAArrayL", CTestSDKQueries::TestQVDAArrayL ),
        ENTRY( "TestQVDAFormatStringL", CTestSDKQueries::TestQVDAFormatStringL ),
        ENTRY( "TestQVDAFormattedStringSizeOneL", CTestSDKQueries::TestQVDAFormattedStringSizeOneL ),
        ENTRY( "TestQVDAFormattedStringSizeTwoL", CTestSDKQueries::TestQVDAFormattedStringSizeTwoL ),
        ENTRY( "TestQVDAMdcaCountL", CTestSDKQueries::TestQVDAMdcaCountL ),
        ENTRY( "TestQVDAMdcaPointL", CTestSDKQueries::TestQVDAMdcaPointL ),
        
    //AknQueryValueDuration.h
        ENTRY( "TestQVDurationNewL", CTestSDKQueries::TestQVDurationNewL ),
        ENTRY( "TestQVDurationNewLCL", CTestSDKQueries::TestQVDurationNewLCL ),
        ENTRY( "TestQVDurationDestructorL", CTestSDKQueries::TestQVDurationDestructorL ),
        ENTRY( "TestQVDurationSetArrayL", CTestSDKQueries::TestQVDurationSetArrayL ),
        ENTRY( "TestQVDurationSetQueryCaptionL", CTestSDKQueries::TestQVDurationSetQueryCaptionL ),
        ENTRY( "TestQVDurationValueL", CTestSDKQueries::TestQVDurationValueL ),
        ENTRY( "TestQVDurationMdcArrayL", CTestSDKQueries::TestQVDurationMdcArrayL ),
        ENTRY( "TestQVDurationCurrentValueTextLCL", CTestSDKQueries::TestQVDurationCurrentValueTextLCL ),
        ENTRY( "TestQVDurationCurrentValueIndexL", CTestSDKQueries::TestQVDurationCurrentValueIndexL ),
        ENTRY( "TestQVDurationSetCurrentValueIndexL", CTestSDKQueries::TestQVDurationSetCurrentValueIndexL ),
        ENTRY( "TestQVDurationCreateEditorL", CTestSDKQueries::TestQVDurationCreateEditorL ),
        
            //CAknQueryValueDurationArray
        ENTRY( "TestQVDArrayNewL", CTestSDKQueries::TestQVDArrayNewL ),
        ENTRY( "TestQVDArrayNewLCL", CTestSDKQueries::TestQVDArrayNewLCL ),
        ENTRY( "TestQVDArrayDestructorL", CTestSDKQueries::TestQVDArrayDestructorL ),
        ENTRY( "TestQVDArraySetArrayL", CTestSDKQueries::TestQVDArraySetArrayL ),
        ENTRY( "TestQVDArrayArrayL", CTestSDKQueries::TestQVDArrayArrayL ),
        ENTRY( "TestQVDArrayFormatStringL", CTestSDKQueries::TestQVDArrayFormatStringL ),
        ENTRY( "TestQVDArrayFormattedStringSizeOneL", CTestSDKQueries::TestQVDArrayFormattedStringSizeOneL ),
        ENTRY( "TestQVDArrayFormattedStringSizeTwoL", CTestSDKQueries::TestQVDArrayFormattedStringSizeTwoL ),
        ENTRY( "TestQVDArrayFormatDurationL", CTestSDKQueries::TestQVDArrayFormatDurationL ),
        ENTRY( "TestQVDArrayMdcaCountL", CTestSDKQueries::TestQVDArrayMdcaCountL ),
        ENTRY( "TestQVDArrayMdcaPointL", CTestSDKQueries::TestQVDArrayMdcaPointL ),
        
    //AknQueryValueNumber.h
            //CAknQueryValueNumber
        ENTRY( "TestQVNumberNewL", CTestSDKQueries::TestQVNumberNewL ),
        ENTRY( "TestQVNumberNewLC", CTestSDKQueries::TestQVNumberNewLC ),
        ENTRY( "TestQVNumberDestructorL", CTestSDKQueries::TestQVNumberDestructorL ),
        ENTRY( "TestQVNumberSetArrayL", CTestSDKQueries::TestQVNumberSetArrayL ),
        ENTRY( "TestQVNumberSetQueryCaptionL", CTestSDKQueries::TestQVNumberSetQueryCaptionL ),
        ENTRY( "TestQVNumberValueL", CTestSDKQueries::TestQVNumberValueL ),
        ENTRY( "TestQVNumberMdcArrayL", CTestSDKQueries::TestQVNumberMdcArrayL ),
        ENTRY( "TestQVNumberCurrentValueTextLCL", CTestSDKQueries::TestQVNumberCurrentValueTextLCL ),
        ENTRY( "TestQVNumberCurrentValueIndexL", CTestSDKQueries::TestQVNumberCurrentValueIndexL ),
        ENTRY( "TestQVNumberSetCurrentValueIndexL", CTestSDKQueries::TestQVNumberSetCurrentValueIndexL ),
        ENTRY( "TestQVNumberCreateEditorL", CTestSDKQueries::TestQVNumberCreateEditorL ),
        
        ENTRY( "TestQVNArrayNewL", CTestSDKQueries::TestQVNArrayNewL ),
        ENTRY( "TestQVNArrayNewLCL", CTestSDKQueries::TestQVNArrayNewLCL ),
        ENTRY( "TestQVNArrayDestructorL", CTestSDKQueries::TestQVNArrayDestructorL ),
        ENTRY( "TestQVNArraySetArrayL", CTestSDKQueries::TestQVNArraySetArrayL ),
        ENTRY( "TestQVNArrayArrayL", CTestSDKQueries::TestQVNArrayArrayL ),
        ENTRY( "TestQVNArrayFormatStringL", CTestSDKQueries::TestQVNArrayFormatStringL ),
        ENTRY( "TestQVNArrayFormattedStringSizeOneL", CTestSDKQueries::TestQVNArrayFormattedStringSizeOneL ),
        ENTRY( "TestQVNArrayFormattedStringSizeTwoL", CTestSDKQueries::TestQVNArrayFormattedStringSizeTwoL ),
        ENTRY( "TestQVNArrayMdcaCountL", CTestSDKQueries::TestQVNArrayMdcaCountL ),
        ENTRY( "TestQVNArrayMdcaPointL", CTestSDKQueries::TestQVNArrayMdcaPointL ),
        
        //AknQueryValuePhone.h
        //class CAknQueryValuePhone
        ENTRY( "TestPhoneNewL", CTestSDKQueries::TestPhoneNewL ),
        ENTRY( "TestPhoneNewLC", CTestSDKQueries::TestPhoneNewLC ),
        ENTRY( "TestPhoneDeconstructorL", CTestSDKQueries::TestPhoneDeconstructorL ),
        ENTRY( "TestPhoneSetArrayL", CTestSDKQueries::TestPhoneSetArrayL ),
        ENTRY( "TestPhoneSetQueryCaptionL", CTestSDKQueries::TestPhoneSetQueryCaptionL ),
        ENTRY( "TestPhoneValueL", CTestSDKQueries::TestPhoneValueL ),
        ENTRY( "TestPhoneMdcArrayL", CTestSDKQueries::TestPhoneMdcArrayL ),
        ENTRY( "TestPhoneCurrentValueTextLC", CTestSDKQueries::TestPhoneCurrentValueTextLC ),
        ENTRY( "TestPhoneCurrentValueIndexL", CTestSDKQueries::TestPhoneCurrentValueIndexL ),
        ENTRY( "TestPhoneSetCurrentValueIndexL", CTestSDKQueries::TestPhoneSetCurrentValueIndexL ),
        ENTRY( "TestPhoneCreateEditorL", CTestSDKQueries::TestPhoneCreateEditorL ),
        
        //class CAknQueryValuePhoneArray
        ENTRY( "TestPhoneArrayNewL", CTestSDKQueries::TestPhoneArrayNewL ),
        ENTRY( "TestPhoneArrayNewLC", CTestSDKQueries::TestPhoneArrayNewLC ),
        ENTRY( "TestPhoneArrayDeconstructorL", CTestSDKQueries::TestPhoneArrayDeconstructorL ),
        ENTRY( "TestPhoneArraySetArrayL", CTestSDKQueries::TestPhoneArraySetArrayL ),
        ENTRY( "TestPhoneArrayArrayL", CTestSDKQueries::TestPhoneArrayArrayL ),
        ENTRY( "TestPhoneArrayFormattedStringSizeL", CTestSDKQueries::TestPhoneArrayFormattedStringSizeL ),
        ENTRY( "TestPhoneArrayMdcaCountL", CTestSDKQueries::TestPhoneArrayMdcaCountL ),
        ENTRY( "TestPhoneArrayMdcaPointL", CTestSDKQueries::TestPhoneArrayMdcaPointL ),
        
        //AknQueryValueText.h
        //class CAknQueryValueText
        ENTRY( "TestTextNewL", CTestSDKQueries::TestTextNewL ),
        ENTRY( "TestTextNewLC", CTestSDKQueries::TestTextNewLC ),
        ENTRY( "TestTextDeconstructorL", CTestSDKQueries::TestTextDeconstructorL ),
        ENTRY( "TestTextSetArrayL", CTestSDKQueries::TestTextSetArrayL ),
        ENTRY( "TestTextSetQueryCaptionL", CTestSDKQueries::TestTextSetQueryCaptionL ),
        ENTRY( "TestTextValueL", CTestSDKQueries::TestTextValueL ),
        ENTRY( "TestTextMdcArrayL", CTestSDKQueries::TestTextMdcArrayL ),
        ENTRY( "TestTextCurrentValueTextLC", CTestSDKQueries::TestTextCurrentValueTextLC ),
        ENTRY( "TestTextCurrentValueIndexL", CTestSDKQueries::TestTextCurrentValueIndexL ),
        ENTRY( "TestTextSetCurrentValueIndexL", CTestSDKQueries::TestTextSetCurrentValueIndexL ),
        ENTRY( "TestTextCreateEditorL", CTestSDKQueries::TestTextCreateEditorL ),
        
        //class CAknQueryValueTextArray
        ENTRY( "TestTextArrayNewL", CTestSDKQueries::TestTextArrayNewL ),
        ENTRY( "TestTextArrayNewLC", CTestSDKQueries::TestTextArrayNewLC ),
        ENTRY( "TestTextArrayDeconstructorL", CTestSDKQueries::TestTextArrayDeconstructorL ),
        ENTRY( "TestTextArraySetArrayL", CTestSDKQueries::TestTextArraySetArrayL ),
        ENTRY( "TestTextArrayArrayL", CTestSDKQueries::TestTextArrayArrayL ),
        ENTRY( "TestTextArrayFormattedStringSizeL", CTestSDKQueries::TestTextArrayFormattedStringSizeL ),
        ENTRY( "TestTextArrayMdcaCountL", CTestSDKQueries::TestTextArrayMdcaCountL ),
        ENTRY( "TestTextArrayMdcaPointL", CTestSDKQueries::TestTextArrayMdcaPointL ),
        
        //AknQueryValueTime.h
        //class CAknQueryValueTime
        ENTRY( "TestTimeNewL", CTestSDKQueries::TestTimeNewL ),
        ENTRY( "TestTimeNewLC", CTestSDKQueries::TestTimeNewLC ),
        ENTRY( "TestTimeDeconstructorL", CTestSDKQueries::TestTimeDeconstructorL ),
        ENTRY( "TestTimeSetArrayL", CTestSDKQueries::TestTimeSetArrayL ),
        ENTRY( "TestTimeSetQueryCaptionL", CTestSDKQueries::TestTimeSetQueryCaptionL ),
        ENTRY( "TestTimeValueL", CTestSDKQueries::TestTimeValueL ),
        ENTRY( "TestTimeMdcArrayL", CTestSDKQueries::TestTimeMdcArrayL ),
        ENTRY( "TestTimeCurrentValueTextLC", CTestSDKQueries::TestTimeCurrentValueTextLC ),
        ENTRY( "TestTimeCurrentValueIndexL", CTestSDKQueries::TestTimeCurrentValueIndexL ),
        ENTRY( "TestTimeSetCurrentValueIndexL", CTestSDKQueries::TestTimeSetCurrentValueIndexL ),
        ENTRY( "TestTimeCreateEditorL", CTestSDKQueries::TestTimeCreateEditorL ),
        
        //class CAknQueryValueTimeArray
        ENTRY( "TestTimeArrayNewL", CTestSDKQueries::TestTimeArrayNewL ),
        ENTRY( "TestTimeArrayNewLC", CTestSDKQueries::TestTimeArrayNewLC ),
        ENTRY( "TestTimeArrayDeconstructorL", CTestSDKQueries::TestTimeArrayDeconstructorL ),
        ENTRY( "TestTimeArraySetArrayL", CTestSDKQueries::TestTimeArraySetArrayL ),
        ENTRY( "TestTimeArrayArrayL", CTestSDKQueries::TestTimeArrayArrayL ),
        ENTRY( "TestTimeArrayFormatStringL", CTestSDKQueries::TestTimeArrayFormatStringL ),
        ENTRY( "TestTimeArrayFormattedStringSizeL", CTestSDKQueries::TestTimeArrayFormattedStringSizeL ),
        ENTRY( "TestTimeArrayMdcaCountL", CTestSDKQueries::TestTimeArrayMdcaCountL ),
        ENTRY( "TestTimeArrayMdcaPointL", CTestSDKQueries::TestTimeArrayMdcaPointL ),
        
        // [test cases entries]

        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }


//  [End of File]




