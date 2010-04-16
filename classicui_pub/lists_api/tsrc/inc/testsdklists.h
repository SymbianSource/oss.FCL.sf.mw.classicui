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



#ifndef C_TESTSDKLISTS_H
#define C_TESTSDKLISTS_H

//  INCLUDES
#include <stiflogger.h>
#include <testscripterinternal.h>
#include <stiftestmodule.h>
#include <testclassassert.h>
#include <eikenv.h>
#include <eiklbi.h>
#include <eiklbx.h>

// MACROS
#define TEST_CLASS_VERSION_MAJOR 0
#define TEST_CLASS_VERSION_MINOR 0
#define TEST_CLASS_VERSION_BUILD 0

// Logging path
_LIT( KtestsdklistsLogPath, "\\logs\\testframework\\testsdklists\\" ); 
// Log file
_LIT( KtestsdklistsLogFile, "testsdklists.txt" ); 
_LIT( KtestsdklistsLogFileWithTitle, "testsdklists_[%S].txt" );

_LIT( KResourceFile, "C:\\resource\\testsdklists.rsc");

_LIT( KMatchableText, " MatchableText " );

_LIT( KStreamName, "c:\\logs\\TestFramework\\text.txt" );
// FORWARD DECLARATIONS
class CAknListBoxLayoutDecorator;
class CTestSDKContainer;
class CTestSDKView;
class CTestSDKListsSelectionListDialog;
class CAknMarkableListDialog;
class CColumnListBoxItemDrawer;
class CListBoxData;
class CTextListBoxModel;
class CSnakingListBoxView;
class CEikColumnListBox;

/**
*  Ctestsdklists test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS( CTestSDKLists ) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestSDKLists* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestSDKLists();

public: // Functions from base classes

    /**
    * From CScriptBase Runs a script line.
    * @since S60 5.0
    * @param aItem Script line containing method name and parameters
    * @return Symbian OS error code
    */
    virtual TInt RunMethodL( CStifItemParser& aItem );

private:

    /**
    * C++ default constructor.
    */
    CTestSDKLists( CTestModuleIf& aTestModuleIf );

    /**
    * By default Symbian 2nd phase constructor is private.
    */
    void ConstructL();

    /**
     * Method used to log version of test class
     */
    void SendTestClassVersion();

private:// for lists_api AknListBoxLayoutDecorator.h class CAknListBoxLayoutDecorator
    /**
     * TestLBLDNewL test function for testing the 
     *     NewL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBLDNewL( CStifItemParser& aItem );

    /**
     * TestLBLDNewLC test function for testing the 
     *     NewL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBLDNewLC( CStifItemParser& aItem );

    /**
     * TestLBLDDelete test function for testing the 
     *     destructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBLDDelete( CStifItemParser& aItem );

    /**
     * TestLBLDArray test function for testing the 
     *     Array function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBLDArrayL( CStifItemParser& aItem );

    /**
     * TestLBLDSetArray test function for testing the 
     *     SetArray function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBLDSetArrayL( CStifItemParser& aItem );

    /**
     * TestLBLDSetLeadingDecorationTextL test function for testing the 
     *     SetLeadingDecorationTextL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBLDSetLeadingDecorationTextL( CStifItemParser& aItem );

    /**
     * TestLBLDSetTrailingDecorationTextL test function for testing the 
     *     SetTrailingDecorationTextL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBLDSetTrailingDecorationTextL( CStifItemParser& aItem );

    /**
     * TestLBLDSetActive test function for testing the 
     *     SetActive function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBLDSetActive( CStifItemParser& aItem );

    /**
     * TestLBLDMdcaCount test function for testing the 
     *     MdcaCount function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBLDMdcaCountL( CStifItemParser& aItem );

    /**
     * TestLBLDMdcaPoint test function for testing the 
     *     MdcaPoint function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBLDMdcaPointL( CStifItemParser& aItem );

private:// for lists_api AknListBoxSettingPage.h class CAknListBoxSettingPage
    /**
     * TestLBSPHandleListBoxEventL test function for testing the 
     *     HandleListBoxEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBSPHandleListBoxEventL( CStifItemParser& aItem );

    /**
     * TestLBSPCheckAndSetDataValidityL test function for testing the 
     *     CheckAndSetDataValidity function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBSPCheckAndSetDataValidityL( CStifItemParser& aItem );

    /**
     * TestLBSPUpdateCbaL test function for testing the 
     *     UpdateCbaL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBSPUpdateCbaL( CStifItemParser& aItem );

    /**
     * TestLBSPSizeChangedL test function for testing the 
     *     SizeChanged function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBSPSizeChangedL( CStifItemParser& aItem );

    /**
     * TestLBSPDrawL test function for testing the 
     *     Draw function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBSPDrawL( CStifItemParser& aItem );

private:// for lists_api AknSelectionList.h 
        // class CAknSelectionListDialog
    /**
     * TestSLDNewL test function for testing the 
     *     NewL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSLDNewL( CStifItemParser& aItem );

    /**
     * TestSLDNewLC test function for testing the 
     *     NewLC function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSLDNewLC( CStifItemParser& aItem );

    /**
     * TestSLDConstructL test function for testing the 
     *     ConstructL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSLDConstructL( CStifItemParser& aItem );

    /**
     * TestSLDSetupFindL test function for testing the 
     *     SetupFind function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSLDSetupFindL( CStifItemParser& aItem );

    /**
     * TestSLDIconArrayL test function for testing the 
     *     IconArray function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSLDIconArrayL( CStifItemParser& aItem );

    /**
     * TestSLDSetIconArrayL test function for testing the 
     *     SetIconArrayL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSLDSetIconArrayL( CStifItemParser& aItem );

    /**
     * TestSLDHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSLDHandlePointerEventL( CStifItemParser& aItem );

    /**
     * TestSLDConstructor test function for testing the 
     *     Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSLDConstructorL( CStifItemParser& aItem );

    /**
     * TestSLDDestructor test function for testing the 
     *     Destructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSLDDestructor( CStifItemParser& aItem );

    /**
     * TestSLDSelectionListProcessCommandL test function for testing the 
     *     SelectionListProcessCommandL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSLDSelectionListProcessCommandL( CStifItemParser& aItem );

    /**
     * TestSLDIsAcceptableListBoxType test function for testing the 
     *     IsAcceptableListBoxType function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSLDIsAcceptableListBoxType( CStifItemParser& aItem );

    /**
     * TestSLDProcessCommandL test function for testing the 
     *     ProcessCommandL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSLDProcessCommandL( CStifItemParser& aItem );

    /**
     * TestSLDPreLayoutDynInitL test function for testing the 
     *     PreLayoutDynInitL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSLDPreLayoutDynInitL( CStifItemParser& aItem );

    /**
     * TestSLDPostLayoutDynInitL test function for testing the 
     *     PostLayoutDynInitL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSLDPostLayoutDynInitL( CStifItemParser& aItem );

    /**
     * TestSLDSetSizeAndPosition test function for testing the 
     *     SetSizeAndPosition function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSLDSetSizeAndPosition( CStifItemParser& aItem );

    /**
     * TestSLDOkToExitL test function for testing the 
     *     OkToExitL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSLDOkToExitL( CStifItemParser& aItem );

    /**
     * TestSLDHandleListBoxEventL test function for testing the 
     *     HandleListBoxEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSLDHandleListBoxEventL( CStifItemParser& aItem );

    /**
     * TestSLDCountComponentControls test function for testing the 
     *     CountComponentControls function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSLDCountComponentControls( CStifItemParser& aItem );

    /**
     * TestSLDComponentControl test function for testing the 
     *     ComponentControl function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSLDComponentControl( CStifItemParser& aItem );

    /**
     * TestSLDOfferKeyEventL test function for testing the 
     *     OfferKeyEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSLDOfferKeyEventL( CStifItemParser& aItem );

    /**
     * TestSLDCreateCustomControlL test function for testing the 
     *     CreateCustomControlL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSLDCreateCustomControlL( CStifItemParser& aItem );

    /**
     * TestSLDListBox test function for testing the 
     *     ListBox function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSLDListBox( CStifItemParser& aItem );

    /**
     * TestSLDFindBox test function for testing the 
     *     FindBox function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSLDFindBox( CStifItemParser& aItem );

    /**
     * TestSLDIsFormattedCellListBox test function for testing the 
     *     IsFormattedCellListBox function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSLDIsFormattedCellListBox( CStifItemParser& aItem );

    /**
     * TestSLDDraw test function for testing the 
     *     Draw function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSLDDraw( CStifItemParser& aItem );

    // CAknMarkableListDialog
    /**
     * TestMLDNewL test function for testing the 
     *     NewL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMLDNewL( CStifItemParser& aItem );

    /**
     * TestMLDNewLCL test function for testing the 
     *     NewLC function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMLDNewLCL( CStifItemParser& aItem );

    /**
     * TestMLDNewL test function for testing the 
     *     NewL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMLDDeprecatedNewL( CStifItemParser& aItem );

    /**
     * TestMLDNewLC test function for testing the 
     *     NewLC function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMLDDeprecatedNewLCL( CStifItemParser& aItem );

    /**
     * TestMLDConstructL test function for testing the 
     *     ConstructL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMLDConstructL( CStifItemParser& aItem );

    /**
     * TestMLDDestructor test function for testing the 
     *     Destructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMLDDestructor( CStifItemParser& aItem );

    /**
     * TestMLDHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMLDHandlePointerEventL( CStifItemParser& aItem );

    /**
     * TestMLDConstructorL test function for testing the 
     *     Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMLDConstructorL( CStifItemParser& aItem );

    /**
     * TestMLDConstructorL test function for testing the 
     *     Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMLDDeprecatedConstructorL( CStifItemParser& aItem );

    /**
     * TestMLDPreLayoutDynInitL test function for testing the 
     *     PreLayoutDynInitL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMLDPreLayoutDynInitL( CStifItemParser& aItem );

    /**
     * TestMLDPostLayoutDynInitL test function for testing the 
     *     PostLayoutDynInitL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMLDPostLayoutDynInitL( CStifItemParser& aItem );

    /**
     * TestMLDSelectionListProcessCommandL test function for testing the 
     *     SelectionListProcessCommandL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMLDSelectionListProcessCommandL( CStifItemParser& aItem );

    /**
     * TestMLDProcessCommandL test function for testing the 
     *     ProcessCommandL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMLDProcessCommandL( CStifItemParser& aItem );

    /**
     * TestMLDDynInitMenuPaneL test function for testing the 
     *     DynInitMenuPaneL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMLDDynInitMenuPaneL( CStifItemParser& aItem );

    /**
     * TestMLDHandleListBoxEventL test function for testing the 
     *     HandleListBoxEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMLDHandleListBoxEventL( CStifItemParser& aItem );

    /**
     * TestMLDOfferKeyEventL test function for testing the 
     *     OfferKeyEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMLDOfferKeyEventL( CStifItemParser& aItem );

    /**
     * TestMLDOkToExitL test function for testing the 
     *     OkToExitL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMLDOkToExitL( CStifItemParser& aItem );

private:// EIKCLB.H
        // class CColumnListBoxItemDrawer
    /**
     * TestCLBIDConstructorL test function for testing the 
     *     Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBIDConstructorL( CStifItemParser& aItem );

    /**
     * TestCLBIDConstructorWithParameterL test function for testing the 
     *     Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBIDConstructorWithParameterL( CStifItemParser& aItem );

    /**
     * TestCLBIDDestructor test function for testing the 
     *     Destructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBIDDestructor( CStifItemParser& aItem );

    /**
     * TestCLBIDColumnData test function for testing the 
     *     ColumnData function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBIDColumnData( CStifItemParser& aItem );

    /**
     * TestCLBIDClearAllPropertiesL test function for testing the 
     *     ClearAllPropertiesL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBIDClearAllPropertiesL( CStifItemParser& aItem );

    /**
     * TestCLBIDSetPropertiesL test function for testing the 
     *     SetPropertiesL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBIDSetPropertiesL( CStifItemParser& aItem );

    /**
     * TestCLBIDProperties test function for testing the 
     *     Properties function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBIDProperties( CStifItemParser& aItem );

    /**
     * TestCLBIDDrawItemTextL test function for testing the 
     *     DrawItemText function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBIDDrawItemTextL( CStifItemParser& aItem );

    /**
     * TestCLBIDDrawItemMark test function for testing the 
     *     DrawItemMark function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBIDDrawItemMark( CStifItemParser& aItem );

    /**
     * TestCLBIDMinimumCellSize test function for testing the 
     *     MinimumCellSize function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBIDMinimumCellSize( CStifItemParser& aItem );

    /**
     * TestCLBIDItemWidthInPixels test function for testing the 
     *     ItemWidthInPixels function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBIDItemWidthInPixels( CStifItemParser& aItem );

    /**
     * TestCLBIDSetItemCellSize test function for testing the 
     *     SetItemCellSize function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBIDSetItemCellSize( CStifItemParser& aItem );

    // class CEikColumnListBox
    /**
     * TestCLBConstructorL test function for testing the 
     *     Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBConstructorL( CStifItemParser& aItem );

    /**
     * TestCLBConstructFromResourceL test function for testing the 
     *     ConstructFromResourceL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBConstructFromResourceL( CStifItemParser& aItem );

    /**
     * TestCLBConstructL test function for testing the 
     *     ConstructL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBConstructL( CStifItemParser& aItem );

    /**
     * TestCLBEditItemL test function for testing the 
     *     EditItemL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBEditItemL( CStifItemParser& aItem );

    /**
     * TestCLBModel test function for testing the 
     *     Model function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBModelL( CStifItemParser& aItem );

    /**
     * TestCLBItemDrawerL test function for testing the 
     *     ItemDrawer function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBItemDrawerL( CStifItemParser& aItem );

    /**
     * TestCLBEnableExtendedDrawingL test function for testing the 
     *     EnableExtendedDrawingL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBEnableExtendedDrawingL( CStifItemParser& aItem );

    /**
     * TestCLBEnableStretchingL test function for testing the 
     *     EnableStretching function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBEnableStretchingL( CStifItemParser& aItem );

    /**
     * TestCLBMakeViewClassInstanceL test function for testing the 
     *     MakeViewClassInstanceL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBMakeViewClassInstanceL( CStifItemParser& aItem );

    /**
     * TestCLBFocusChangedL test function for testing the 
     *     FocusChanged function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBFocusChangedL( CStifItemParser& aItem );

    /**
     * TestCLBGetColorUseListL test function for testing the 
     *     GetColorUseListL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBGetColorUseListL( CStifItemParser& aItem );

    /**
     * TestCLBHandleResourceChangeL test function for testing the 
     *     HandleResourceChange function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBHandleResourceChangeL( CStifItemParser& aItem );

    /**
     * TestCLBMopSupplyObjectL test function for testing the 
     *     MopSupplyObject function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBMopSupplyObjectL( CStifItemParser& aItem );

    /**
     * TestCLBHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBHandlePointerEventL( CStifItemParser& aItem );

    /**
     * TestCLBCreateItemDrawerL test function for testing the 
     *     CreateItemDrawerL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBCreateItemDrawerL( CStifItemParser& aItem );

    /**
     * TestCLBCreateModelL test function for testing the 
     *     CreateModelL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBCreateModelL( CStifItemParser& aItem );

    // class CEikColumnListBoxEditor
    /**
     * TestCLBEConstructorL test function for testing the 
     *     Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBEConstructorL( CStifItemParser& aItem );

    /**
     * TestCLBDestructorL test function for testing the 
     *     Destructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBEDestructorL( CStifItemParser& aItem );

    /**
     * TestCLBConstructL test function for testing the 
     *     ConstructL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBEConstructL( CStifItemParser& aItem );

    /**
     * TestCLBItemTextL test function for testing the 
     *     ItemText function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBEItemTextL( CStifItemParser& aItem );

    /**
     * TestCLBUpdateModelL test function for testing the 
     *     UpdateModelL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBEUpdateModelL( CStifItemParser& aItem );

    /**
     * TestCLBHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBEHandlePointerEventL( CStifItemParser& aItem );

    /**
     * TestCLBEColumnL test function for testing the 
     *     Column function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBEColumnL( CStifItemParser& aItem );

    // class CColumnListBoxView
    /**
     * TestCLBVDrawL test function for testing the 
     *     Draw function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBVDrawL( CStifItemParser& aItem );

    /**
     * TestCLBVCalcBottomItemIndexL test function for testing the 
     *     CalcBottomItemIndex function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBVCalcBottomItemIndexL( CStifItemParser& aItem );

private:// EIKCLBD.H
    /**
     * TestCLBDTColorsL test function for testing the 
     *     TColors function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBDTColorsL( CStifItemParser& aItem );

    /**
     * TestCLBDNewL test function for testing the 
     *     NewL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBDNewL( CStifItemParser& aItem );

    /**
     * TestCLBDTColorsL test function for testing the 
     *     TColors function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBDDestructorL( CStifItemParser& aItem );

    /**
     * TestCLBDLastColumnL test function for testing the 
     *     LastColumn function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBDLastColumnL( CStifItemParser& aItem );

    /**
     * TestCLBDColumnWidthPixelL test function for testing the 
     *     ColumnWidthPixel function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBDColumnWidthPixelL( CStifItemParser& aItem );

    /**
     * TestCLBDSetColumnWidthPixelL test function for testing the 
     *     SetColumnWidthPixelL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBDSetColumnWidthPixelL( CStifItemParser& aItem );

    /**
     * TestCLBDColumnHorizontalGapL test function for testing the 
     *     ColumnHorizontalGap function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBDColumnHorizontalGapL( CStifItemParser& aItem );

    /**
     * TestCLBDSetColumnHorizontalGapL test function for testing the 
     *     SetColumnHorizontalGapL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBDSetColumnHorizontalGapL( CStifItemParser& aItem );

    /**
     * TestCLBDColumnBaselinePosL test function for testing the 
     *     ColumnBaselinePos function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBDColumnBaselinePosL( CStifItemParser& aItem );

    /**
     * TestCLBDSetColumnBaselinePosL test function for testing the 
     *     SetColumnBaselinePosL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBDSetColumnBaselinePosL( CStifItemParser& aItem );

    /**
     * TestCLBDColumnMarginsL test function for testing the 
     *     ColumnMargins function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBDColumnMarginsL( CStifItemParser& aItem );

    /**
     * TestCLBDSetColumnMarginsL test function for testing the 
     *     SetColumnMarginsL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBDSetColumnMarginsL( CStifItemParser& aItem );

    /**
     * TestCLBDColumnFontL test function for testing the 
     *     ColumnFont function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBDColumnFontL( CStifItemParser& aItem );

    /**
     * TestCLBDSetColumnFontL test function for testing the 
     *     SetColumnFontL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBDSetColumnFontL( CStifItemParser& aItem );

    /**
     * TestCLBDColumnAlignmentL test function for testing the 
     *     ColumnAlignment function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBDColumnAlignmentL( CStifItemParser& aItem );

    /**
     * TestCLBDSetColumnAlignmentL test function for testing the 
     *     SetColumnAlignmentL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBDSetColumnAlignmentL( CStifItemParser& aItem );

    /**
     * TestCLBDColumnSeparatorStyleL test function for testing the 
     *     ColumnSeparatorStyle function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBDColumnSeparatorStyleL( CStifItemParser& aItem );

    /**
     * TestCLBDSetColumnSeparatorStyleL test function for testing the 
     *     SetColumnSeparatorStyleL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBDSetColumnSeparatorStyleL( CStifItemParser& aItem );

    /**
     * TestCLBDColumnIsOptionalL test function for testing the 
     *     ColumnIsOptional function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBDColumnIsOptionalL( CStifItemParser& aItem );

    /**
     * TestCLBDSetOptionalColumnL test function for testing the 
     *     SetOptionalColumnL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBDSetOptionalColumnL( CStifItemParser& aItem );

    /**
     * TestCLBDColumnIsGraphicsL test function for testing the 
     *     ColumnIsGraphics function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBDColumnIsGraphicsL( CStifItemParser& aItem );

    /**
     * TestCLBDSetGraphicsColumnL test function for testing the 
     *     SetGraphicsColumnL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBDSetGraphicsColumnL( CStifItemParser& aItem );

    /**
     * TestCLBDColumnIsNumberL test function for testing the 
     *     ColumnIsNumber function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBDColumnIsNumberL( CStifItemParser& aItem );

    /**
     * TestCLBDSetNumberColumnL test function for testing the 
     *     SetNumberColumnL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBDSetNumberColumnL( CStifItemParser& aItem );

    /**
     * TestCLBDIconArrayL test function for testing the 
     *     IconArray function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBDIconArrayL( CStifItemParser& aItem );

    /**
     * TestCLBDSetIconArrayL test function for testing the 
     *     SetIconArray function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBDSetIconArrayL( CStifItemParser& aItem );

    /**
     * TestCLBDColumnTextClipGapL test function for testing the 
     *     ColumnTextClipGap function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBDColumnTextClipGapL( CStifItemParser& aItem );

    /**
     * TestCLBDSetColumnTextClipGapL test function for testing the 
     *     SetColumnTextClipGapL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBDSetColumnTextClipGapL( CStifItemParser& aItem );

    /**
     * TestCLBDColumnTextClipGapL test function for testing the 
     *     ColumnTextClipGap function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBDFontL( CStifItemParser& aItem );

    /**
     * TestCLBDMakeColumnRectL test function for testing the 
     *     MakeColumnRect function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBDMakeColumnRectL( CStifItemParser& aItem );

    /**
     * TestCLBDDrawL test function for testing the 
     *     Draw function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBDDrawL( CStifItemParser& aItem );

    /**
     * TestCLBDSetSeparatorLinePositionL test function for testing the 
     *     SetSeparatorLinePosition function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBDSetSeparatorLinePositionL( CStifItemParser& aItem );

    /**
     * TestCLBDSeparatorLinePositionL test function for testing the 
     *     SeparatorLinePosition function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBDSeparatorLinePositionL( CStifItemParser& aItem );

    /**
     * TestCLBDLayoutDataL test function for testing the 
     *     LayoutData function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBDLayoutDataL( CStifItemParser& aItem );

    /**
     * TestCLBDLayoutInitL test function for testing the 
     *     LayoutInit function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBDLayoutInitL( CStifItemParser& aItem );

    /**
     * TestCLBDSetLayoutInitL test function for testing the 
     *     SetLayoutInit function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBDSetLayoutInitL( CStifItemParser& aItem );

    /**
     * TestCLBDSetColumnUnderlinedL test function for testing the 
     *     SetColumnUnderlined function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBDSetColumnUnderlinedL( CStifItemParser& aItem );

    /**
     * TestCLBDControlL test function for testing the 
     *     Control function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBDControlL( CStifItemParser& aItem );

    /**
     * TestCLBDSetControlL test function for testing the 
     *     SetControl function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBDSetControlL( CStifItemParser& aItem );

    /**
     * TestCLBDSkinBackgroundContextL test function for testing the 
     *     SkinBackgroundContext function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBDSkinBackgroundContextL( CStifItemParser& aItem );

    /**
     * TestCLBDSetSkinStyleL test function for testing the 
     *     SetSkinStyle function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBDSetSkinStyleL( CStifItemParser& aItem );

    /**
     * TestCLBDSetListEndSkinStyleL test function for testing the 
     *     SetListEndSkinStyle function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBDSetListEndSkinStyleL( CStifItemParser& aItem );

    /**
     * TestCLBDSetSkinHighlightFrameL test function for testing the 
     *     SetSkinHighlightFrame function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBDSetSkinHighlightFrameL( CStifItemParser& aItem );

    /**
     * TestCLBDSetSkinEnabledL test function for testing the 
     *     SetSkinEnabledL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBDSetSkinEnabledL( CStifItemParser& aItem );

    /**
     * TestCLBDEnableMarqueeL test function for testing the 
     *     EnableMarqueeL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBDEnableMarqueeL( CStifItemParser& aItem );

    /**
     * TestCLBDSetColumnFontForRowL test function for testing the 
     *     SetColumnFontForRowL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBDSetColumnFontForRowL( CStifItemParser& aItem );

    /**
     * TestCLBDRowAndColumnFontL test function for testing the 
     *     RowAndColumnFont function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBDRowAndColumnFontL( CStifItemParser& aItem );

    /**
     * TestCLBDSetSubCellIconSizeL test function for testing the 
     *     SetSubCellIconSize function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBDSetSubCellIconSizeL( CStifItemParser& aItem );

    /**
     * TestCLBDHighlightAnimL test function for testing the 
     *     HighlightAnim function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBDHighlightAnimL( CStifItemParser& aItem );

    /**
     * TestCLBDAboutToDrawHighlightAnimL test function for testing the 
     *     AboutToDrawHighlightAnim function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBDAboutToDrawHighlightAnimL( CStifItemParser& aItem );

    /**
     * TestCLBDSetHighlightAnimBackgroundDrawerL test function for testing the 
     *     SetHighlightAnimBackgroundDrawer function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBDSetHighlightAnimBackgroundDrawerL( CStifItemParser& aItem );

    /**
     * TestCLBDSetItemCellSizeL test function for testing the 
     *     SetItemCellSize function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBDSetItemCellSizeL( CStifItemParser& aItem );

    /**
     * TestCLBDHasHighlightAnimL test function for testing the 
     *     HasHighlightAnim function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBDHasHighlightAnimL( CStifItemParser& aItem );

    /**
     * TestCLBDSetItemCellSizeL test function for testing the 
     *     DrawHighlightAnimL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBDDrawHighlightAnimL( CStifItemParser& aItem );

    /**
     * TestCLBDSetGraphicSubCellL test function for testing the 
     *     SetGraphicSubCellL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBDSetGraphicSubCellL( CStifItemParser& aItem );

    /**
     * TestCLBDSetTextSubCellL test function for testing the 
     *     SetTextSubCellL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBDSetTextSubCellL( CStifItemParser& aItem );

    /**
     * TestCLBDSetConditionalSubCellL test function for testing the 
     *     SetConditionalSubCellL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBDSetConditionalSubCellL( CStifItemParser& aItem );

    /**
     * TestCLBDSubCellsMightIntersectL test function for testing the 
     *     SubCellsMightIntersect function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBDSubCellsMightIntersectL( CStifItemParser& aItem );

    /**
     * TestCLBDSetStretchableGraphicSubCellL test function for testing the 
     *     SetStretchableGraphicSubCellL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBDSetStretchableGraphicSubCellL( CStifItemParser& aItem );

    /**
     * TestCLBDResetSLSubCellArrayL test function for testing the 
     *     ResetSLSubCellArray function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBDResetSLSubCellArrayL( CStifItemParser& aItem );

    /**
     * TestCLBDStretchingEnabledL test function for testing the 
     *     StretchingEnabled function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBDStretchingEnabledL( CStifItemParser& aItem );

    /**
     * TestCLBDSetMarqueeParamsL test function for testing the 
     *     SetMarqueeParams function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBDSetMarqueeParamsL( CStifItemParser& aItem );

    /**
     * TestCLBDSetMarqueeParamsWithIntervalL test function for testing the 
     *     SetMarqueeParams function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBDSetMarqueeParamsWithIntervalL( CStifItemParser& aItem );

    /**
     * TestCLBDCurrentItemTextWasClippedL test function for testing the 
     *     CurrentItemTextWasClipped function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBDCurrentItemTextWasClippedL( CStifItemParser& aItem );

    /**
     * TestCLBDSetStretchableTextSubCellL test function for testing the 
     *     SetStretchableTextSubCellL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBDSetStretchableTextSubCellL( CStifItemParser& aItem );

    /**
     * TestCLBDSetStretchableConditionalSubCellL test function for testing the 
     *     SetStretchableConditionalSubCellL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBDSetStretchableConditionalSubCellL( CStifItemParser& aItem );

    /**
     * TestCLBDConstructorL test function for testing the 
     *     Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBDConstructorL( CStifItemParser& aItem );

    /**
     * TestCLBDConstructLDL test function for testing the 
     *     ConstructLD function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBDConstructLDL( CStifItemParser& aItem );

    /**
     * TestCLBDConstructLDWithParaL test function for testing the 
     *     ConstructLD function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBDConstructLDWithParaL( CStifItemParser& aItem );

    /**
     * TestCLBDDrawTextL test function for testing the 
     *     DrawText function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLBDDrawTextL( CStifItemParser& aItem );

private: // eikfrlb.h
         // class CFormattedCellListBoxItemDrawer
    /**
     * TestFCLBIDConstructorL test function for testing the 
     *     Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBIDConstructorL( CStifItemParser& aItem );

    /**
     * TestFCLBIDDestructorL test function for testing the 
     *     Destructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBIDDestructorL( CStifItemParser& aItem );

    /**
     * TestFCLBIDFormattedCellDataL test function for testing the 
     *     FormattedCellData function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBIDFormattedCellDataL( CStifItemParser& aItem );

    /**
     * TestFCLBIDColumnData test function for testing the 
     *     ColumnData function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBIDColumnDataL( CStifItemParser& aItem );

    /**
     * TestFCLBIDDrawEmptyItem test function for testing the 
     *     DrawEmptyItem function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBIDDrawEmptyItemL( CStifItemParser& aItem );

    /**
     * TestFCLBIDSetTopItemIndex test function for testing the 
     *     SetTopItemIndex function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBIDSetTopItemIndexL( CStifItemParser& aItem );

    /**
     * TestFCLBIDClearAllPropertiesL test function for testing the 
     *     ClearAllPropertiesL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBIDClearAllPropertiesL( CStifItemParser& aItem );

    /**
     * TestFCLBIDSetPropertiesL test function for testing the 
     *     SetPropertiesL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBIDSetPropertiesL( CStifItemParser& aItem );

    /**
     * TestFCLBIDProperties test function for testing the 
     *     Properties function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBIDPropertiesL( CStifItemParser& aItem );

    /**
     * TestFCLBIDDrawItemText test function for testing the 
     *     DrawItemText function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBIDDrawItemTextL( CStifItemParser& aItem );

    /**
     * TestFCLBIDDrawItemMarkL test function for testing the 
     *     DrawItemMark function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBIDDrawItemMarkL( CStifItemParser& aItem );

    /**
     * TestFCLBIDMinimumCellSizeL test function for testing the 
     *     MinimumCellSize function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBIDMinimumCellSizeL( CStifItemParser& aItem );

    /**
     * TestFCLBIDItemWidthInPixelsL test function for testing the 
     *     ItemWidthInPixels function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBIDItemWidthInPixelsL( CStifItemParser& aItem );

    /**
     * TestFCLBIDSetItemCellSizeL test function for testing the 
     *     SetItemCellSize function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBIDSetItemCellSizeL( CStifItemParser& aItem );

    // class CEikFormattedCellListBox
    /**
     * TestFCLBConstructorL test function for testing the 
     *     Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBConstructorL( CStifItemParser& aItem );

    /**
     * TestFCLBConstructFromResourceL test function for testing the 
     *     ConstructFromResourceL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBConstructFromResourceL( CStifItemParser& aItem );

    /**
     * TestFCLBConstructL test function for testing the 
     *     ConstructL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBConstructL( CStifItemParser& aItem );

    /**
     * TestFCLBModelL test function for testing the 
     *     Model function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBModelL( CStifItemParser& aItem );

    /**
     * TestFCLBItemDrawerL test function for testing the 
     *     ItemDrawer function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBItemDrawerL( CStifItemParser& aItem );

    /**
     * TestFCLBUseLogicalToVisualConversionL test function for testing the 
     *     UseLogicalToVisualConversion function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBUseLogicalToVisualConversionL( CStifItemParser& aItem );

    /**
     * TestFCLBEnableExtendedDrawingL test function for testing the 
     *     EnableExtendedDrawingL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBEnableExtendedDrawingL( CStifItemParser& aItem );

    /**
     * TestFCLBEnableStretchingL test function for testing the 
     *     EnableStretching function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBEnableStretchingL( CStifItemParser& aItem );

    /**
     * TestFCLBHideSecondRowL test function for testing the 
     *     HideSecondRow function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBHideSecondRowL( CStifItemParser& aItem );

    /**
     * TestFCLBMakeViewClassInstanceL test function for testing the 
     *     MakeViewClassInstanceL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBMakeViewClassInstanceL( CStifItemParser& aItem );

    /**
     * TestFCLBFocusChangedL test function for testing the 
     *     FocusChanged function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBFocusChangedL( CStifItemParser& aItem );

    /**
     * TestFCLBGetColorUseListL test function for testing the 
     *     GetColorUseListL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBGetColorUseListL( CStifItemParser& aItem );

    /**
     * TestFCLBHandleResourceChangeL test function for testing the 
     *     HandleResourceChange function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBHandleResourceChangeL( CStifItemParser& aItem );

    /**
     * TestFCLBHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBHandlePointerEventL( CStifItemParser& aItem );

    /**
     * TestFCLBCreateItemDrawerL test function for testing the 
     *     CreateItemDrawerL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBCreateItemDrawerL( CStifItemParser& aItem );

    /**
     * TestFCLBAdjustRectHeightToWholeNumberOfItemsL test function for testing the 
     *     AdjustRectHeightToWholeNumberOfItems function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBAdjustRectHeightToWholeNumberOfItemsL( CStifItemParser& aItem );

    /**
     * TestFCLBMopSupplyObjectL test function for testing the 
     *     MopSupplyObject function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBMopSupplyObjectL( CStifItemParser& aItem );

    // class CFormattedCellListBoxView
    /**
     * TestFCLBVDrawL test function for testing the 
     *     Draw function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBVDrawL( CStifItemParser& aItem );

    /**
     * TestFCLBVDrawEmptyListL test function for testing the 
     *     DrawEmptyList function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBVDrawEmptyListL( CStifItemParser& aItem );

    /**
     * TestFCLBVCalcBottomItemIndexL test function for testing the 
     *     CalcBottomItemIndex function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBVCalcBottomItemIndexL( CStifItemParser& aItem );

private: // Eikfrlbd.h
    // class CFormattedCellListBoxData
    /**
     * TestFCLBDTColorsL test function for testing the 
     *     TColors function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBDTColorsL( CStifItemParser& aItem );

    /**
     * TestFCLBDNewL test function for testing the 
     *     NewL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBDNewL( CStifItemParser& aItem );

    /**
     * TestFCLBDDestructorL test function for testing the 
     *     Destructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBDDestructorL( CStifItemParser& aItem );

    /**
     * TestFCLBDSubCellColorsL test function for testing the 
     *     SubCellColors function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBDSubCellColorsL( CStifItemParser& aItem );

    /**
     * TestFCLBDSetSubCellColorsL test function for testing the 
     *     SetSubCellColorsL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBDSetSubCellColorsL( CStifItemParser& aItem );

    /**
     * TestFCLBDSubCellBaselinePosL test function for testing the 
     *     SubCellBaselinePos function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBDSubCellBaselinePosL( CStifItemParser& aItem );

    /**
     * TestFCLBDSetSubCellBaselinePosL test function for testing the 
     *     SetSubCellBaselinePosL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBDSetSubCellBaselinePosL( CStifItemParser& aItem );

    /**
     * TestFCLBDSubCellSizeL test function for testing the 
     *     SubCellSize function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBDSubCellSizeL( CStifItemParser& aItem );

    /**
     * TestFCLBDSetSubCellSizeL test function for testing the 
     *     SetSubCellSizeL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBDSetSubCellSizeL( CStifItemParser& aItem );

    /**
     * TestFCLBDSubCellPositionL test function for testing the 
     *     SubCellPosition function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBDSubCellPositionL( CStifItemParser& aItem );

    /**
     * TestFCLBDSetSubCellPositionL test function for testing the 
     *     SetSubCellPositionL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBDSetSubCellPositionL( CStifItemParser& aItem );

    /**
     * TestFCLBDSubCellIsTransparentL test function for testing the 
     *     SubCellIsTransparent function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBDSubCellIsTransparentL( CStifItemParser& aItem );

    /**
     * TestFCLBDSetTransparentSubCellL test function for testing the 
     *     SetTransparentSubCellL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBDSetTransparentSubCellL( CStifItemParser& aItem );

    /**
     * TestFCLBDSubCellIsNotAlwaysDrawnL test function for testing the 
     *     SubCellIsNotAlwaysDrawn function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBDSubCellIsNotAlwaysDrawnL( CStifItemParser& aItem );

    /**
     * TestFCLBDSetNotAlwaysDrawnSubCellL test function for testing the 
     *     SetNotAlwaysDrawnSubCellL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBDSetNotAlwaysDrawnSubCellL( CStifItemParser& aItem );

    /**
     * TestFCLBDSubCellMarginsL test function for testing the 
     *     SubCellMargins function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBDSubCellMarginsL( CStifItemParser& aItem );

    /**
     * TestFCLBDSetSubCellMarginsL test function for testing the 
     *     SetSubCellMarginsL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBDSetSubCellMarginsL( CStifItemParser& aItem );

    /**
     * TestFCLBDSubCellFontL test function for testing the 
     *     SubCellFont function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBDSubCellFontL( CStifItemParser& aItem );

    /**
     * TestFCLBDSetSubCellFontL test function for testing the 
     *     SetSubCellFontL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBDSetSubCellFontL( CStifItemParser& aItem );

    /**
     * TestFCLBDSubCellAlignmentL test function for testing the 
     *     SubCellAlignment function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBDSubCellAlignmentL( CStifItemParser& aItem );

    /**
     * TestFCLBDSetSubCellAlignmentL test function for testing the 
     *     SetSubCellAlignmentL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBDSetSubCellAlignmentL( CStifItemParser& aItem );

    /**
     * TestFCLBDSubCellIsGraphicsL test function for testing the 
     *     SubCellIsGraphics function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBDSubCellIsGraphicsL( CStifItemParser& aItem );

    /**
     * TestFCLBDSetGraphicsSubCellL test function for testing the 
     *     SetGraphicsSubCellL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBDSetGraphicsSubCellL( CStifItemParser& aItem );

    /**
     * TestFCLBDSubCellRightSeparatorStyleL test function for testing the 
     *     SubCellRightSeparatorStyle function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBDSubCellRightSeparatorStyleL( CStifItemParser& aItem );

    /**
     * TestFCLBDSetSubCellRightSeparatorStyleL test function for testing the 
     *     SetSubCellRightSeparatorStyleL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBDSetSubCellRightSeparatorStyleL( CStifItemParser& aItem );

    /**
     * TestFCLBDSubCellTextClipGapL test function for testing the 
     *     SubCellTextClipGap function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBDSubCellTextClipGapL( CStifItemParser& aItem );

    /**
     * TestFCLBDSetSubCellTextClipGapL test function for testing the 
     *     SetSubCellTextClipGapL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBDSetSubCellTextClipGapL( CStifItemParser& aItem );

    /**
     * TestFCLBDSkinEnabledL test function for testing the 
     *     SkinEnabled function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBDSkinEnabledL( CStifItemParser& aItem );

    /**
     * TestFCLBDSetSkinEnabledL test function for testing the 
     *     SetSkinEnabledL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBDSetSkinEnabledL( CStifItemParser& aItem );

    /**
     * TestFCLBDSubCellIsNumberCellL test function for testing the 
     *     SubCellIsNumberCell function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBDSubCellIsNumberCellL( CStifItemParser& aItem );

    /**
     * TestFCLBDSetNumberCellL test function for testing the 
     *     SetNumberCellL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBDSetNumberCellL( CStifItemParser& aItem );

    /**
     * TestFCLBDIconArrayL test function for testing the 
     *     IconArray function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBDIconArrayL( CStifItemParser& aItem );

    /**
     * TestFCLBDSetIconArrayLL test function for testing the 
     *     SetIconArrayL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBDSetIconArrayLL( CStifItemParser& aItem );

    /**
     * TestFCLBDIconArrayL test function for testing the 
     *     SetIconArray function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBDSetIconArrayL( CStifItemParser& aItem );

    /**
     * TestFCLBDFontL test function for testing the 
     *     Font function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBDFontL( CStifItemParser& aItem );

    /**
     * TestFCLBDDrawL test function for testing the 
     *     Draw function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBDDrawL( CStifItemParser& aItem );

    /**
     * TestFCLBDUseSubCellColorsL test function for testing the 
     *     UseSubCellColors function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBDUseSubCellColorsL( CStifItemParser& aItem );

    /**
     * TestFCLBDControlL test function for testing the 
     *     Control function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBDControlL( CStifItemParser& aItem );

    /**
     * TestFCLBDSetControlL test function for testing the 
     *     SetControl function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBDSetControlL( CStifItemParser& aItem );

    /**
     * TestFCLBDSkinBackgroundContextL test function for testing the 
     *     SkinBackgroundContext function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBDSkinBackgroundContextL( CStifItemParser& aItem );

    /**
     * TestFCLBDSetBackgroundSkinStyleL test function for testing the 
     *     SetBackgroundSkinStyle function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBDSetBackgroundSkinStyleL( CStifItemParser& aItem );

    /**
     * TestFCLBDSetSkinStyleL test function for testing the 
     *     SetSkinStyle function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBDSetSkinStyleL( CStifItemParser& aItem );

    /**
     * TestFCLBDSetSkinParentPosL test function for testing the 
     *     SetSkinParentPos function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBDSetSkinParentPosL( CStifItemParser& aItem );

    /**
     * TestFCLBDSetListEndSkinStyleL test function for testing the 
     *     SetListEndSkinStyle function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBDSetListEndSkinStyleL( CStifItemParser& aItem );

    /**
     * TestFCLBDRespectFocusL test function for testing the 
     *     RespectFocus function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBDRespectFocusL( CStifItemParser& aItem );

    /**
     * TestFCLBDSetRespectFocusL test function for testing the 
     *     SetRespectFocus function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBDSetRespectFocusL( CStifItemParser& aItem );

    /**
     * TestFCLBDSetSkinHighlightFrameL test function for testing the 
     *     SetSkinHighlightFrame function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBDSetSkinHighlightFrameL( CStifItemParser& aItem );

    /**
     * TestFCLBDSetSkinPopupFrameL test function for testing the 
     *     SetSkinPopupFrame function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBDSetSkinPopupFrameL( CStifItemParser& aItem );

    /**
     * TestFCLBDSetSkinPopupFramePositionL test function for testing the 
     *     SetSkinPopupFramePosition function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBDSetSkinPopupFramePositionL( CStifItemParser& aItem );

    /**
     * TestFCLBDUseLogicalToVisualConversionL test function for testing the 
     *     UseLogicalToVisualConversion function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBDUseLogicalToVisualConversionL( CStifItemParser& aItem );

    /**
     * TestFCLBDEnableMarqueeL test function for testing the 
     *     EnableMarqueeL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBDEnableMarqueeL( CStifItemParser& aItem );

    /**
     * TestFCLBDIsMarqueeOnL test function for testing the 
     *     IsMarqueeOn function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBDIsMarqueeOnL( CStifItemParser& aItem );

    /**
     * TestFCLBDHighlightAnimL test function for testing the 
     *     HighlightAnim function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBDHighlightAnimL( CStifItemParser& aItem );

    /**
     * TestFCLBDAboutToDrawHighlightAnimL test function for testing the 
     *     AboutToDrawHighlightAnim function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBDAboutToDrawHighlightAnimL( CStifItemParser& aItem );

    /**
     * TestFCLBDSetHighlightAnimBackgroundDrawerL test function for testing the 
     *     SetHighlightAnimBackgroundDrawer function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBDSetHighlightAnimBackgroundDrawerL( CStifItemParser& aItem );

    /**
     * TestFCLBDSetItemCellSizeL test function for testing the 
     *     SetItemCellSize function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBDSetItemCellSizeL( CStifItemParser& aItem );

    /**
     * TestFCLBDHasHighlightAnimL test function for testing the 
     *     HasHighlightAnim function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBDHasHighlightAnimL( CStifItemParser& aItem );

    /**
     * TestFCLBDDrawHighlightAnimL test function for testing the 
     *     DrawHighlightAnim function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBDDrawHighlightAnimL( CStifItemParser& aItem );

    /**
     * TestFCLBDSetSubCellFontForRowL test function for testing the 
     *     SetSubCellFontForRowL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBDSetSubCellFontForRowL( CStifItemParser& aItem );

    /**
     * TestFCLBDRowAndSubCellFontL test function for testing the 
     *     RowAndSubCellFont function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBDRowAndSubCellFontL( CStifItemParser& aItem );

    /**
     * TestFCLBDSetDrawBackgroundL test function for testing the 
     *     SetDrawBackground function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBDSetDrawBackgroundL( CStifItemParser& aItem );

    /**
     * TestFCLBDSetSeparatorLinePositionL test function for testing the 
     *     SetSeparatorLinePosition function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBDSetSeparatorLinePositionL( CStifItemParser& aItem );

    /**
     * TestFCLBDSeparatorLinePositionL test function for testing the 
     *     SeparatorLinePosition function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBDSeparatorLinePositionL( CStifItemParser& aItem );

    /**
     * TestFCLBDLayoutDataL test function for testing the 
     *     LayoutData function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBDLayoutDataL( CStifItemParser& aItem );

    /**
     * TestFCLBDLayoutInitL test function for testing the 
     *     LayoutInit function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBDLayoutInitL( CStifItemParser& aItem );

    /**
     * TestFCLBDSetLayoutInitL test function for testing the 
     *     SetLayoutInit function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBDSetLayoutInitL( CStifItemParser& aItem );

    /**
     * TestFCLBDSetSubcellUnderlinedL test function for testing the 
     *     SetSubcellUnderlined function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBDSetSubcellUnderlinedL( CStifItemParser& aItem );

    /**
     * TestFCLBDSetMarqueeParamsL test function for testing the 
     *     SetMarqueeParams function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBDSetMarqueeParamsL( CStifItemParser& aItem );

    /**
     * TestFCLBDCurrentItemTextWasClippedL test function for testing the 
     *     CurrentItemTextWasClipped function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBDCurrentItemTextWasClippedL( CStifItemParser& aItem );

    /**
     * TestFCLBDSetSubCellIconSizeL test function for testing the 
     *     SetSubCellIconSize function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBDSetSubCellIconSizeL( CStifItemParser& aItem );

    /**
     * TestFCLBDConstructorL test function for testing the 
     *     Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBDConstructorL( CStifItemParser& aItem );

    /**
     * TestFCLBDConstructLDL test function for testing the 
     *     ConstructLD function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBDConstructLDL( CStifItemParser& aItem );

    /**
     * TestFCLBDConstructLDWithParaL test function for testing the 
     *     ConstructLD function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBDConstructLDWithParaL( CStifItemParser& aItem );

    /**
     * TestFCLBDDrawFormattedL test function for testing the 
     *     DrawFormatted function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCLBDDrawFormattedL( CStifItemParser& aItem );

    // class CSettingItemEditingListBoxData
    /**
     * TestSIELBDNewL test function for testing the 
     *     NewL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSIELBDNewL( CStifItemParser& aItem );

    /**
     * TestSIELBDDrawL test function for testing the 
     *     Draw function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSIELBDDrawL( CStifItemParser& aItem );

    // class CFormGraphicListBoxData
    /**
     * TestFGLBDNewL test function for testing the 
     *     NewL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFGLBDNewL( CStifItemParser& aItem );

    /**
     * TestFGLBDDrawL test function for testing the 
     *     Draw function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFGLBDDrawL( CStifItemParser& aItem );

    // class CPopupFormattedListBoxData
    /**
     * TestPFLBDNewL test function for testing the 
     *     NewL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestPFLBDNewL( CStifItemParser& aItem );

    /**
     * TestPFLBDDrawL test function for testing the 
     *     Draw function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestPFLBDDrawL( CStifItemParser& aItem );

    // class CFormattedCellGridData
    /**
     * TestFCGDNewL test function for testing the 
     *     NewL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCGDNewL( CStifItemParser& aItem );

    /**
     * TestFCGDDrawL test function for testing the 
     *     Draw function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFCGDDrawL( CStifItemParser& aItem );

private:// eiklbd.h
    // class TListFontBoundValues
    /**
     * TestLFBVConstructorL test function for testing the 
     *     Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLFBVConstructorL( CStifItemParser& aItem );

    // class CListBoxData
    /**
     * TestLBDConstructorL test function for testing the 
     *     Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBDConstructorL( CStifItemParser& aItem );

    /**
     * TestLBDDestructor test function for testing the 
     *     Destructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBDDestructor( CStifItemParser& aItem );

    /**
     * TestLBDConstructL test function for testing the 
     *     ConstructL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBDConstructL( CStifItemParser& aItem );

    /**
     * TestLBDFont test function for testing the 
     *     Font function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBDFont( CStifItemParser& aItem );

    /**
     * TestLBDSetupGc test function for testing the 
     *     SetupGc function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBDSetupGc( CStifItemParser& aItem );

    /**
     * TestLBDFontBoundValues test function for testing the 
     *     FontBoundValues function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBDFontBoundValues( CStifItemParser& aItem );

    /**
     * TestLBDSetFontHeight test function for testing the 
     *     SetFontHeight function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBDSetFontHeight( CStifItemParser& aItem );

    /**
     * TestLBDSetSearchStringL test function for testing the 
     *     SetSearchStringL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBDSetSearchStringL( CStifItemParser& aItem );

    /**
     * TestLBDIsSearchStringL test function for testing the 
     *     IsSearchString function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBDIsSearchStringL( CStifItemParser& aItem );

    /**
     * TestLBDDrawItemL test function for testing the 
     *     DrawItem function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBDDrawItemL( CStifItemParser& aItem );

    /**
     * TestLBDSetAlignmentL test function for testing the 
     *     SetAlignmentL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBDSetAlignmentL( CStifItemParser& aItem );

    /**
     * TestLBDAlignmentL test function for testing the 
     *     Alignment function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBDAlignmentL( CStifItemParser& aItem );

    /**
     * TestLBDSkinBackgroundControlContext test function for testing the 
     *     SkinBackgroundControlContext function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBDSkinBackgroundControlContext( CStifItemParser& aItem );

    /**
     * TestLBDSetSkinBackgroundControlContextL test function for testing the 
     *     SetSkinBackgroundControlContextL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBDSetSkinBackgroundControlContextL( CStifItemParser& aItem );

    /**
     * TestLBDSetSkinEnabledL test function for testing the 
     *     SetSkinEnabledL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBDSetSkinEnabledL( CStifItemParser& aItem );

    /**
     * TestLBDConstructFontL test function for testing the 
     *     ConstructFontL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBDConstructFontL( CStifItemParser& aItem );

    /**
     * TestLBDUpdateFontBoundValuesL test function for testing the 
     *     UpdateFontBoundValues function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBDUpdateFontBoundValuesL( CStifItemParser& aItem );

    /**
     * TestLBDRegenerateFontsL test function for testing the 
     *     RegenerateFonts function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBDRegenerateFontsL( CStifItemParser& aItem );

    // class CFontsWithStyle in class CListBoxData
    /**
     * TestLBDFWSReleaseFontsL test function for testing the 
     *     ReleaseFonts function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBDFWSReleaseFontsL( CStifItemParser& aItem );

    /**
     * TestLBDFWSFontStyleL test function for testing the 
     *     FontStyle function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBDFWSFontStyleL( CStifItemParser& aItem );

    /**
     * TestLBDFWSSetFontStyleL test function for testing the 
     *     SetFontStyle function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBDFWSSetFontStyleL( CStifItemParser& aItem );

private:// eiklbed.h
    /**
     * TestLBDFWSSetFontStyleL test function for testing the 
     *     Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBTEConstructorL( CStifItemParser& aItem );

    /**
     * TestLBTEDestructorL test function for testing the 
     *     Destructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBTEDestructorL( CStifItemParser& aItem );

    /**
     * TestLBTESetFontL test function for testing the 
     *     SetFont function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBTESetFontL( CStifItemParser& aItem );

    /**
     * TestLBTEEditorL test function for testing the 
     *     Editor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBTEEditorL( CStifItemParser& aItem );

    /**
     * TestLBTESetListBoxEditorObserverL test function for testing the 
     *     SetListBoxEditorObserver function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBTESetListBoxEditorObserverL( CStifItemParser& aItem );

    /**
     * TestLBTEItemTextL test function for testing the 
     *     ItemText function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBTEItemTextL( CStifItemParser& aItem );

    /**
     * TestLBTEStartEditingL test function for testing the 
     *     StartEditingL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBTEStartEditingL( CStifItemParser& aItem );

    /**
     * TestLBTEStopEditingL test function for testing the 
     *     StopEditingL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBTEStopEditingL( CStifItemParser& aItem );

    /**
     * TestLBTEUpdateModelL test function for testing the 
     *     UpdateModelL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBTEUpdateModelL( CStifItemParser& aItem );

    /**
     * TestLBTEOfferKeyEventL test function for testing the 
     *     OfferKeyEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBTEOfferKeyEventL( CStifItemParser& aItem );

    /**
     * TestLBTEHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBTEHandlePointerEventL( CStifItemParser& aItem );

    /**
     * TestLBTEReleaseL test function for testing the 
     *     Release function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBTEReleaseL( CStifItemParser& aItem );

    /**
     * TestLBTEListBoxModelL test function for testing the 
     *     ListBoxModel function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBTEListBoxModelL( CStifItemParser& aItem );

    /**
     * TestLBTEItemIndexL test function for testing the 
     *     ItemIndex function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBTEItemIndexL( CStifItemParser& aItem );

    /**
     * TestLBTEWriteInternalStateL test function for testing the 
     *     WriteInternalStateL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBTEWriteInternalStateL( CStifItemParser& aItem );

private:
    // eiklbi.h
    // class CListItemDrawer
    /**
     * TestLIDDrawItemL test function for testing the 
     *     DrawItem function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLIDDrawItemL( CStifItemParser& aItem );

    /**
     * TestLIDClearRectL test function for testing the 
     *     ClearRect function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLIDClearRectL( CStifItemParser& aItem );

    /**
     * TestLIDItemWidthInPixelsL test function for testing the 
     *     ItemWidthInPixels function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLIDItemWidthInPixelsL( CStifItemParser& aItem );

    /**
     * TestLIDMinimumCellSizeL test function for testing the 
     *     MinimumCellSize function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLIDMinimumCellSizeL( CStifItemParser& aItem );

    /**
     * TestLIDSetGcL test function for testing the 
     *     SetGc function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLIDSetGcL( CStifItemParser& aItem );

    /**
     * TestLIDGcL test function for testing the 
     *     Gc function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLIDGcL( CStifItemParser& aItem );

    /**
     * TestLIDSetMarkColumnWidthL test function for testing the 
     *     SetMarkColumnWidth function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLIDSetMarkColumnWidthL( CStifItemParser& aItem );

    /**
     * TestLIDSetMarkGutterL test function for testing the 
     *     SetMarkGutter function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLIDSetMarkGutterL( CStifItemParser& aItem );

    /**
     * TestLIDMarkColumnL test function for testing the 
     *     MarkColumn function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLIDMarkColumnL( CStifItemParser& aItem );

    /**
     * TestLIDMarkGutterL test function for testing the 
     *     MarkGutter function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLIDMarkGutterL( CStifItemParser& aItem );

    /**
     * TestLIDSetItemCellSizeL test function for testing the 
     *     SetItemCellSize function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLIDSetItemCellSizeL( CStifItemParser& aItem );

    /**
     * TestLIDItemCellSizeL test function for testing the 
     *     ItemCellSize function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLIDItemCellSizeL( CStifItemParser& aItem );

    /**
     * TestLIDSetViewRectL test function for testing the 
     *     SetViewRect function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLIDSetViewRectL( CStifItemParser& aItem );

    /**
     * TestLIDSetDrawMarkL test function for testing the 
     *     SetDrawMark function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLIDSetDrawMarkL( CStifItemParser& aItem );

    /**
     * TestLIDMatcherCursorRectL test function for testing the 
     *     MatcherCursorRect function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLIDMatcherCursorRectL( CStifItemParser& aItem );

    /**
     * TestLIDMatcherCursorAscentL test function for testing the 
     *     MatcherCursorAscent function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLIDMatcherCursorAscentL( CStifItemParser& aItem );

    /**
     * TestLIDDrawItemMarkL test function for testing the 
     *     DrawItemMark function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLIDDrawItemMarkL( CStifItemParser& aItem );

    /**
     * TestLIDSetSymbolFontL test function for testing the 
     *     SetSymbolFont function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLIDSetSymbolFontL( CStifItemParser& aItem );

    /**
     * TestLIDSetVerticalInterItemGapL test function for testing the 
     *     SetVerticalInterItemGap function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLIDSetVerticalInterItemGapL( CStifItemParser& aItem );

    /**
     * TestLIDSetDataL test function for testing the 
     *     SetData function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLIDSetDataL( CStifItemParser& aItem );

    /**
     * TestLIDFontL test function for testing the 
     *     Font function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLIDFontL( CStifItemParser& aItem );

    /**
     * TestLIDPropertiesL test function for testing the 
     *     Properties function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLIDPropertiesL( CStifItemParser& aItem );

    /**
     * TestLIDDrawFrameL test function for testing the 
     *     DrawFrame function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLIDDrawFrameL( CStifItemParser& aItem );

    /**
     * TestLIDSetTextColorL test function for testing the 
     *     SetTextColor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLIDSetTextColorL( CStifItemParser& aItem );

    /**
     * TestLIDSetBackColorL test function for testing the 
     *     SetBackColor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLIDSetBackColorL( CStifItemParser& aItem );

    /**
     * TestLIDSetHighlightedTextColorL test function for testing the 
     *     SetHighlightedTextColor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLIDSetHighlightedTextColorL( CStifItemParser& aItem );

    /**
     * TestLIDSetHighlightedBackColorL test function for testing the 
     *     SetHighlightedBackColor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLIDSetHighlightedBackColorL( CStifItemParser& aItem );

    /**
     * TestLIDSetDimmedTextColorL test function for testing the 
     *     SetDimmedTextColor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLIDSetDimmedTextColorL( CStifItemParser& aItem );

    /**
     * TestLIDSetDimmedBackColorL test function for testing the 
     *     SetDimmedBackColor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLIDSetDimmedBackColorL( CStifItemParser& aItem );

    /**
     * TestLIDTextColorL test function for testing the 
     *     TextColor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLIDTextColorL( CStifItemParser& aItem );

    /**
     * TestLIDBackColorL test function for testing the 
     *     BackColor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLIDBackColorL( CStifItemParser& aItem );

    /**
     * TestLIDHighlightedTextColorL test function for testing the 
     *     HighlightedTextColor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLIDHighlightedTextColorL( CStifItemParser& aItem );

    /**
     * TestLIDHighlightedBackColorL test function for testing the 
     *     HighlightedBackColor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLIDHighlightedBackColorL( CStifItemParser& aItem );

    /**
     * TestLIDDimmedTextColorL test function for testing the 
     *     DimmedTextColor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLIDDimmedTextColorL( CStifItemParser& aItem );

    /**
     * TestLIDDimmedBackColorL test function for testing the 
     *     DimmedBackColor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLIDDimmedBackColorL( CStifItemParser& aItem );

    /**
     * TestLIDFlagsL test function for testing the 
     *     Flags function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLIDFlagsL( CStifItemParser& aItem );

    /**
     * TestLIDSetFlagsL test function for testing the 
     *     SetFlags function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLIDSetFlagsL( CStifItemParser& aItem );

    /**
     * TestLIDClearFlagsL test function for testing the 
     *     ClearFlags function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLIDClearFlagsL( CStifItemParser& aItem );

    /**
     * TestLIDSkinBackgroundControlContextL test function for testing the 
     *     SkinBackgroundControlContext function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLIDSkinBackgroundControlContextL( CStifItemParser& aItem );

    /**
     * TestLIDSetSkinEnabledL test function for testing the 
     *     SetSkinEnabledL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLIDSetSkinEnabledL( CStifItemParser& aItem );

    /**
     * TestLIDConstructorL test function for testing the 
     *     Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLIDConstructorL( CStifItemParser& aItem );

    /**
     * TestLIDDestructorL test function for testing the 
     *     Destructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLIDDestructorL( CStifItemParser& aItem );

    /**
     * TestLIDResetGcL test function for testing the 
     *     ResetGc function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLIDResetGcL( CStifItemParser& aItem );

    /**
     * TestLIDMarkColorL test function for testing the 
     *     MarkColor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLIDMarkColorL( CStifItemParser& aItem );

    /**
     * TestLIDVerticalInterItemGapL test function for testing the 
     *     VerticalInterItemGap function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLIDVerticalInterItemGapL( CStifItemParser& aItem );

    /**
     * TestLIDSetupGcL test function for testing the 
     *     SetupGc function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLIDSetupGcL( CStifItemParser& aItem );

    // class CTextListItemDrawer
    /**
     * TestTLIDConstructorL test function for testing the 
     *     Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestTLIDConstructorL( CStifItemParser& aItem );

    /**
     * TestTLIDDestructorL test function for testing the 
     *     Destructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestTLIDDestructor( CStifItemParser& aItem );

    /**
     * TestTLIDConstructorWithParaL test function for testing the 
     *     Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestTLIDConstructorWithParaL( CStifItemParser& aItem );

    /**
     * TestTLIDConstructL test function for testing the 
     *     ConstructL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestTLIDConstructL( CStifItemParser& aItem );

    /**
     * TestTLIDDrawActualItem test function for testing the 
     *     DrawActualItem function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestTLIDDrawActualItem( CStifItemParser& aItem );

    /**
     * TestTLIDItemWidthInPixels test function for testing the 
     *     ItemWidthInPixels function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestTLIDItemWidthInPixels( CStifItemParser& aItem );

    /**
     * TestTLIDMinimumCellSize test function for testing the 
     *     MinimumCellSize function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestTLIDMinimumCellSize( CStifItemParser& aItem );

    /**
     * TestTLIDSetGc test function for testing the 
     *     SetGc function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestTLIDSetGc( CStifItemParser& aItem );

    /**
     * TestTLIDSetCellWidthInChars test function for testing the 
     *     SetCellWidthInChars function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestTLIDSetCellWidthInChars( CStifItemParser& aItem );

    /**
     * TestTLIDMatcherCursorRect test function for testing the 
     *     MatcherCursorRect function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestTLIDMatcherCursorRect( CStifItemParser& aItem );

    /**
     * TestTLIDMatcherCursorAscent test function for testing the 
     *     MatcherCursorAscent function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestTLIDMatcherCursorAscent( CStifItemParser& aItem );

    /**
     * TestTLIDSetFont test function for testing the 
     *     SetFont function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestTLIDSetFont( CStifItemParser& aItem );

    /**
     * TestTLIDSetSearchStringL test function for testing the 
     *     SetSearchStringL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestTLIDSetSearchStringL( CStifItemParser& aItem );

    /**
     * TestTLIDFont test function for testing the 
     *     Font function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestTLIDFont( CStifItemParser& aItem );

    /**
     * TestTLIDSetItemMarkPosition test function for testing the 
     *     SetItemMarkPosition function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestTLIDSetItemMarkPosition( CStifItemParser& aItem );

    /**
     * TestTLIDItemMarkPosition test function for testing the 
     *     ItemMarkPosition function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestTLIDItemMarkPosition( CStifItemParser& aItem );

    /**
     * TestTLIDSetItemMarkReplacement test function for testing the 
     *     SetItemMarkReplacement function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestTLIDSetItemMarkReplacement( CStifItemParser& aItem );

    /**
     * TestTLIDItemMarkReplacement test function for testing the 
     *     ItemMarkReplacement function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestTLIDItemMarkReplacement( CStifItemParser& aItem );

    /**
     * TestTLIDSetItemMarkReverse test function for testing the 
     *     SetItemMarkReverse function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestTLIDSetItemMarkReverse( CStifItemParser& aItem );

    /**
     * TestTLIDItemMarkReverse test function for testing the 
     *     ItemMarkReverse function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestTLIDItemMarkReverse( CStifItemParser& aItem );

    /**
     * TestTLIDDoDrawItemTextL test function for testing the 
     *     DoDrawItemText function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestTLIDDoDrawItemTextL( CStifItemParser& aItem );

    /**
     * TestTLIDDrawItemTextL test function for testing the 
     *     DrawItemText function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestTLIDDrawItemTextL( CStifItemParser& aItem );

    /**
     * TestTLIDResetGcL test function for testing the 
     *     ResetGc function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestTLIDResetGcL( CStifItemParser& aItem );

    // class TListItemProperties
    /**
     * TestLIPConstructorL test function for testing the 
     *     Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLIPConstructorL( CStifItemParser& aItem );

    /**
     * TestLIPSetBold test function for testing the 
     *     SetBold function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLIPSetBold( CStifItemParser& aItem );

    /**
     * TestLIPIsBold test function for testing the 
     *     IsBold function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLIPIsBold( CStifItemParser& aItem );

    /**
     * TestLIPSetItalics test function for testing the 
     *     SetItalics function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLIPSetItalics( CStifItemParser& aItem );

    /**
     * TestLIPIsItalics test function for testing the 
     *     IsItalics function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLIPIsItalics( CStifItemParser& aItem );

    /**
     * TestLIPSetUnderlined test function for testing the 
     *     SetUnderlined function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLIPSetUnderlined( CStifItemParser& aItem );

    /**
     * TestLIPIsUnderlined test function for testing the 
     *     IsUnderlined function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLIPIsUnderlined( CStifItemParser& aItem );

    /**
     * TestLIPSetDimmed test function for testing the 
     *     SetDimmed function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLIPSetDimmed( CStifItemParser& aItem );

    /**
     * TestLIPIsDimmed test function for testing the 
     *     IsDimmed function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLIPIsDimmed( CStifItemParser& aItem );

    /**
     * TestLIPSetColor test function for testing the 
     *     SetColor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLIPSetColor( CStifItemParser& aItem );

    /**
     * TestLIPColor test function for testing the 
     *     Color function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLIPColor( CStifItemParser& aItem );

    /**
     * TestLIPSetSeparatorAfter test function for testing the 
     *     SetSeparatorAfter function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLIPSetSeparatorAfter( CStifItemParser& aItem );

    /**
     * TestLIPIsSeparatorAfter test function for testing the 
     *     IsSeparatorAfter function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLIPIsSeparatorAfter( CStifItemParser& aItem );

    /**
     * TestLIPSetHiddenSelection test function for testing the 
     *     SetHiddenSelection function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLIPSetHiddenSelection( CStifItemParser& aItem );

    /**
     * TestLIPIsSelectionHidden test function for testing the 
     *     IsSelectionHidden function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLIPIsSelectionHidden( CStifItemParser& aItem );

private: // eiklbv.h
    // class CListBoxView
    /**
     * TestLBVConstructorL test function for testing the 
     *     Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBVConstructorL( CStifItemParser& aItem );

    /**
     * TestLBVDestructorL test function for testing the 
     *     Destructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBVDestructorL( CStifItemParser& aItem );

    /**
     * TestLBVConstructL test function for testing the 
     *     ConstructL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBVConstructL( CStifItemParser& aItem );

    /**
     * TestLBVViewRectL test function for testing the 
     *     ViewRect function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBVViewRectL( CStifItemParser& aItem );

    /**
     * TestLBVSetViewRectL test function for testing the 
     *     SetViewRect function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBVSetViewRectL( CStifItemParser& aItem );

    /**
     * TestLBVCurrentItemIndexL test function for testing the 
     *     CurrentItemIndex function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBVCurrentItemIndexL( CStifItemParser& aItem );

    /**
     * TestLBVSetCurrentItemIndexL test function for testing the 
     *     SetCurrentItemIndex function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBVSetCurrentItemIndexL( CStifItemParser& aItem );

    /**
     * TestLBVTopItemIndexL test function for testing the 
     *     TopItemIndex function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBVTopItemIndexL( CStifItemParser& aItem );

    /**
     * TestLBVSetTopItemIndexL test function for testing the 
     *     SetTopItemIndex function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBVSetTopItemIndexL( CStifItemParser& aItem );

    /**
     * TestLBVBottomItemIndexL test function for testing the 
     *     BottomItemIndex function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBVBottomItemIndexL( CStifItemParser& aItem );

    /**
     * TestLBVCalcBottomItemIndexL test function for testing the 
     *     CalcBottomItemIndex function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBVCalcBottomItemIndexL( CStifItemParser& aItem );

    /**
     * TestLBVSetItemHeightL test function for testing the 
     *     SetItemHeight function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBVSetItemHeightL( CStifItemParser& aItem );

    /**
     * TestLBVSetMatcherCursorColorL test function for testing the 
     *     SetMatcherCursorColor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBVSetMatcherCursorColorL( CStifItemParser& aItem );

    /**
     * TestLBVSetMatcherCursorPosL test function for testing the 
     *     SetMatcherCursorPos function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBVSetMatcherCursorPosL( CStifItemParser& aItem );

    /**
     * TestLBVMatcherCursorPosL test function for testing the 
     *     MatcherCursorPos function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBVMatcherCursorPosL( CStifItemParser& aItem );

    /**
     * TestLBVDrawMatcherCursorL test function for testing the 
     *     DrawMatcherCursor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBVDrawMatcherCursorL( CStifItemParser& aItem );

    /**
     * TestLBVHideMatcherCursorL test function for testing the 
     *     HideMatcherCursor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBVHideMatcherCursorL( CStifItemParser& aItem );

    /**
     * TestLBVSetMatcherCursorL test function for testing the 
     *     SetMatcherCursor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBVSetMatcherCursorL( CStifItemParser& aItem );

    /**
     * TestLBVSetEmphasizedL test function for testing the 
     *     SetEmphasized function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBVSetEmphasizedL( CStifItemParser& aItem );

    /**
     * TestLBVSetDimmedL test function for testing the 
     *     SetDimmed function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBVSetDimmedL( CStifItemParser& aItem );

    /**
     * TestLBVSetDisableRedrawL test function for testing the 
     *     SetDisableRedraw function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBVSetDisableRedrawL( CStifItemParser& aItem );

    /**
     * TestLBVRedrawDisabledL test function for testing the 
     *     RedrawDisabled function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBVRedrawDisabledL( CStifItemParser& aItem );

    /**
     * TestLBVSetPaintedSelectionL test function for testing the 
     *     SetPaintedSelection function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBVSetPaintedSelectionL( CStifItemParser& aItem );

    /**
     * TestLBVSelectionIndexesL test function for testing the 
     *     SelectionIndexes function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBVSelectionIndexesL( CStifItemParser& aItem );

    /**
     * TestLBVGetSelectionIndexesL test function for testing the 
     *     GetSelectionIndexesL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBVGetSelectionIndexesL( CStifItemParser& aItem );

    /**
     * TestLBVSetSelectionIndexesL test function for testing the 
     *     SetSelectionIndexesL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBVSetSelectionIndexesL( CStifItemParser& aItem );

    /**
     * TestLBVClearSelectionL test function for testing the 
     *     ClearSelection function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBVClearSelectionL( CStifItemParser& aItem );

    /**
     * TestLBVUpdateSelectionL test function for testing the 
     *     UpdateSelectionL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBVUpdateSelectionL( CStifItemParser& aItem );

    /**
     * TestLBVToggleItemL test function for testing the 
     *     ToggleItemL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBVToggleItemL( CStifItemParser& aItem );

    /**
     * TestLBVSelectItemL test function for testing the 
     *     SelectItemL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBVSelectItemL( CStifItemParser& aItem );

    /**
     * TestLBVDeselectItemL test function for testing the 
     *     DeselectItem function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBVDeselectItemL( CStifItemParser& aItem );

    /**
     * TestLBVSetAnchorL test function for testing the 
     *     SetAnchor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBVSetAnchorL( CStifItemParser& aItem );

    /**
     * TestLBVClearSelectionAnchorAndActiveIndexL test function for testing the 
     *     ClearSelectionAnchorAndActiveIndex function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBVClearSelectionAnchorAndActiveIndexL( CStifItemParser& aItem );

    /**
     * TestLBVScrollToMakeItemVisibleL test function for testing the 
     *     ScrollToMakeItemVisible function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBVScrollToMakeItemVisibleL( CStifItemParser& aItem );

    /**
     * TestLBVVScrollToL test function for testing the 
     *     VScrollTo function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBVVScrollToL( CStifItemParser& aItem );

    /**
     * TestLBVVScrollToWithTRectL test function for testing the 
     *     VScrollTo function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBVVScrollToWithTRectL( CStifItemParser& aItem );

    /**
     * TestLBVHScrollL test function for testing the 
     *     HScroll function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBVHScrollL( CStifItemParser& aItem );

    /**
     * TestLBVHScrollOffsetL test function for testing the 
     *     HScrollOffset function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBVHScrollOffsetL( CStifItemParser& aItem );

    /**
     * TestLBVSetHScrollOffsetL test function for testing the 
     *     SetHScrollOffset function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBVSetHScrollOffsetL( CStifItemParser& aItem );

    /**
     * TestLBVDataWidthL test function for testing the 
     *     DataWidth function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBVDataWidthL( CStifItemParser& aItem );

    /**
     * TestLBVCalcDataWidthL test function for testing the 
     *     CalcDataWidth function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBVCalcDataWidthL( CStifItemParser& aItem );

    /**
     * TestLBVVisibleWidthL test function for testing the 
     *     VisibleWidth function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBVVisibleWidthL( CStifItemParser& aItem );

    /**
     * TestLBVCalcNewTopItemIndexSoItemIsVisibleL test function for testing the 
     *     CalcNewTopItemIndexSoItemIsVisible function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBVCalcNewTopItemIndexSoItemIsVisibleL( CStifItemParser& aItem );

    /**
     * TestLBVDrawL test function for testing the 
     *     Draw function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBVDrawL( CStifItemParser& aItem );

    /**
     * TestLBVDrawItemL test function for testing the 
     *     DrawItem function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBVDrawItemL( CStifItemParser& aItem );

    /**
     * TestLBVSetListEmptyTextL test function for testing the 
     *     SetListEmptyTextL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBVSetListEmptyTextL( CStifItemParser& aItem );

    /**
     * TestLBVEmptyListTextL test function for testing the 
     *     EmptyListText function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBVEmptyListTextL( CStifItemParser& aItem );

    /**
     * TestLBVItemIsSelectedL test function for testing the 
     *     ItemIsSelected function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBVItemIsSelectedL( CStifItemParser& aItem );

    /**
     * TestLBVItemIsVisibleL test function for testing the 
     *     ItemIsVisible function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBVItemIsVisibleL( CStifItemParser& aItem );

    /**
     * TestLBVItemPosL test function for testing the 
     *     ItemPos function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBVItemPosL( CStifItemParser& aItem );

    /**
     * TestLBVItemSizeL test function for testing the 
     *     ItemSize function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBVItemSizeL( CStifItemParser& aItem );

    /**
     * TestLBVSetTextColorL test function for testing the 
     *     SetTextColor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBVSetTextColorL( CStifItemParser& aItem );

    /**
     * TestLBVSetBackColorL test function for testing the 
     *     SetBackColor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBVSetBackColorL( CStifItemParser& aItem );

    /**
     * TestLBVTextColorL test function for testing the 
     *     TextColor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBVTextColorL( CStifItemParser& aItem );

    /**
     * TestLBVBackColorL test function for testing the 
     *     BackColor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBVBackColorL( CStifItemParser& aItem );

    /**
     * TestLBVMoveCursorL test function for testing the 
     *     MoveCursorL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBVMoveCursorL( CStifItemParser& aItem );

    /**
     * TestLBVVerticalMoveToItemL test function for testing the 
     *     VerticalMoveToItemL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBVVerticalMoveToItemL( CStifItemParser& aItem );

    /**
     * TestLBVXYPosToItemIndexL test function for testing the 
     *     XYPosToItemIndex function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBVXYPosToItemIndexL( CStifItemParser& aItem );

    /**
     * TestLBVNumberOfItemsThatFitInRectL test function for testing the 
     *     NumberOfItemsThatFitInRect function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBVNumberOfItemsThatFitInRectL( CStifItemParser& aItem );

    /**
     * TestLBVIsVisibleL test function for testing the 
     *     IsVisible function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBVIsVisibleL( CStifItemParser& aItem );

    /**
     * TestLBVItemDrawerL test function for testing the 
     *     ItemDrawer function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBVItemDrawerL( CStifItemParser& aItem );

    /**
     * TestLBVDrawEmptyListL test function for testing the 
     *     DrawEmptyList function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBVDrawEmptyListL( CStifItemParser& aItem );

    /**
     * TestLBVDeselectRangeL test function for testing the 
     *     DeselectRangeL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBVDeselectRangeL( CStifItemParser& aItem );

    /**
     * TestLBVFlagsL test function for testing the 
     *     Flags function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBVFlagsL( CStifItemParser& aItem );

    /**
     * TestLBVSetFlagsL test function for testing the 
     *     SetFlags function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBVSetFlagsL( CStifItemParser& aItem );

    /**
     * TestLBVClearFlagsL test function for testing the 
     *     ClearFlags function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBVClearFlagsL( CStifItemParser& aItem );

    /**
     * TestLBVSelectRangeL test function for testing the 
     *     SelectRangeL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBVSelectRangeL( CStifItemParser& aItem );

    // class CSnakingListBoxView
    /**
     * TestSLBVConstructorL test function for testing the 
     *     Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSLBVConstructorL( CStifItemParser& aItem );

    /**
     * TestSLBVDestructor test function for testing the 
     *     Destructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSLBVDestructor( CStifItemParser& aItem );

    /**
     * TestSLBVColumnWidth test function for testing the 
     *     ColumnWidth function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSLBVColumnWidth( CStifItemParser& aItem );

    /**
     * TestSLBVSetColumnWidth test function for testing the 
     *     SetColumnWidth function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSLBVSetColumnWidth( CStifItemParser& aItem );

    /**
     * TestSLBVMoveCursorL test function for testing the 
     *     MoveCursorL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSLBVMoveCursorL( CStifItemParser& aItem );

    /**
     * TestSLBVSetTopItemIndex test function for testing the 
     *     SetTopItemIndex function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSLBVSetTopItemIndex( CStifItemParser& aItem );

    /**
     * TestSLBVSetItemHeight test function for testing the 
     *     SetItemHeight function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSLBVSetItemHeight( CStifItemParser& aItem );

    /**
     * TestSLBVXYPosToItemIndex test function for testing the 
     *     XYPosToItemIndex function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSLBVXYPosToItemIndex( CStifItemParser& aItem );

    /**
     * TestSLBVNumberOfItemsThatFitInRect test function for testing the 
     *     NumberOfItemsThatFitInRect function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSLBVNumberOfItemsThatFitInRect( CStifItemParser& aItem );

    /**
     * TestSLBVHScroll test function for testing the 
     *     HScroll function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSLBVHScroll( CStifItemParser& aItem );

    /**
     * TestSLBVCalcDataWidth test function for testing the 
     *     CalcDataWidth function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSLBVCalcDataWidth( CStifItemParser& aItem );

    /**
     * TestSLBVCalcBottomItemIndex test function for testing the 
     *     CalcBottomItemIndex function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSLBVCalcBottomItemIndex( CStifItemParser& aItem );

    /**
     * TestSLBVDraw test function for testing the 
     *     Draw function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSLBVDraw( CStifItemParser& aItem );

    /**
     * TestSLBVVisibleWidth test function for testing the 
     *     VisibleWidth function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSLBVVisibleWidth( CStifItemParser& aItem );

    /**
     * TestSLBVScrollToMakeItemVisible test function for testing the 
     *     ScrollToMakeItemVisible function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSLBVScrollToMakeItemVisible( CStifItemParser& aItem );

    /**
     * TestSLBVCalculateHScrollOffsetSoItemIsVisible test function for testing the 
     *     CalculateHScrollOffsetSoItemIsVisible function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSLBVCalculateHScrollOffsetSoItemIsVisible( CStifItemParser& aItem );

    /**
     * CalcNewTopItemIndexSoItemIsVisible test function for testing the 
     *     CalcNewTopItemIndexSoItemIsVisible function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSLBVCalcNewTopItemIndexSoItemIsVisible( CStifItemParser& aItem );

    /**
     * TestSLBVItemPos test function for testing the 
     *     ItemPos function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSLBVItemPos( CStifItemParser& aItem );

    /**
     * TestSLBVItemSize test function for testing the 
     *     ItemSize function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSLBVItemSize( CStifItemParser& aItem );

    /**
     * TestSLBVCalcRowAndColIndexesFromItemIndex test function for testing the 
     *     CalcRowAndColIndexesFromItemIndex function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSLBVCalcRowAndColIndexesFromItemIndex( CStifItemParser& aItem );

    /**
     * TestSLBVCalcItemIndexFromRowAndColIndexes test function for testing the 
     *     CalcItemIndexFromRowAndColIndexes function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSLBVCalcItemIndexFromRowAndColIndexes( CStifItemParser& aItem );

    /**
     * TestSLBVNumberOfItemsPerColumn test function for testing the 
     *     NumberOfItemsPerColumn function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSLBVNumberOfItemsPerColumn( CStifItemParser& aItem );

    /**
     * TestSLBVDrawItemRangeL test function for testing the 
     *     DrawItemRange function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSLBVDrawItemRangeL( CStifItemParser& aItem );

    /**
     * TestSLBVDrawColumnRangeL test function for testing the 
     *     DrawColumnRange function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSLBVDrawColumnRangeL( CStifItemParser& aItem );

    /**
     * TestSLBVMoveToPreviousColumnL test function for testing the 
     *     MoveToPreviousColumnL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSLBVMoveToPreviousColumnL( CStifItemParser& aItem );

    /**
     * TestSLBVMoveToNextColumnL test function for testing the 
     *     MoveToNextColumnL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSLBVMoveToNextColumnL( CStifItemParser& aItem );

    /**
     * TestSLBVClearUnusedItemSpaceL test function for testing the 
     *     ClearUnusedItemSpace function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSLBVClearUnusedItemSpaceL( CStifItemParser& aItem );

    /**
     * TestSLBVUpdateHScrollOffsetBasedOnTopItemIndexL test function for testing the 
     *     UpdateHScrollOffsetBasedOnTopItemIndex function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSLBVUpdateHScrollOffsetBasedOnTopItemIndexL( CStifItemParser& aItem );

    /**
     * TestSLBVSetItemOffsetInPixelsL test function for testing the 
     *     SetItemOffsetInPixels function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSLBVSetItemOffsetInPixelsL( CStifItemParser& aItem );

private:// eiklbx.h
    // class CEikListBox
    /**
     * TestLBConstructorL test function for testing the 
     *     Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBConstructorL( CStifItemParser& aItem );

    /**
     * TestLBDestructor test function for testing the 
     *     Destructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBDestructor( CStifItemParser& aItem );

    /**
     * TestLBConstructL test function for testing the 
     *     ConstructL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBConstructL( CStifItemParser& aItem );

    /**
     * TestLBConstructWithTGulBorderL test function for testing the 
     *     ConstructL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBConstructWithTGulBorderL( CStifItemParser& aItem );

    /**
     * TestLBOfferKeyEventL test function for testing the 
     *     OfferKeyEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBOfferKeyEventL( CStifItemParser& aItem );

    /**
     * TestLBHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBHandlePointerEventL( CStifItemParser& aItem );

    /**
     * TestLBSetContainerWindowL test function for testing the 
     *     SetContainerWindowL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBSetContainerWindowL( CStifItemParser& aItem );

    /**
     * TestLBMinimumSize test function for testing the 
     *     MinimumSize function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBMinimumSize( CStifItemParser& aItem );

    /**
     * TestLBSetDimmed test function for testing the 
     *     SetDimmed function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBSetDimmed( CStifItemParser& aItem );

    /**
     * TestLBHandleScrollEventL test function for testing the 
     *     HandleScrollEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBHandleScrollEventL( CStifItemParser& aItem );

    /**
     * TestLBModelL test function for testing the 
     *     Model function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBModelL( CStifItemParser& aItem );

    /**
     * TestLBViewL test function for testing the 
     *     View function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBViewL( CStifItemParser& aItem );

    /**
     * TestLBTopItemIndex test function for testing the 
     *     TopItemIndex function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBTopItemIndex( CStifItemParser& aItem );

    /**
     * TestLBSetTopItemIndex test function for testing the 
     *     SetTopItemIndex function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBSetTopItemIndex( CStifItemParser& aItem );

    /**
     * TestLBBottomItemIndex test function for testing the 
     *     BottomItemIndex function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBBottomItemIndex( CStifItemParser& aItem );

    /**
     * TestLBCurrentItemIndex test function for testing the 
     *     CurrentItemIndex function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBCurrentItemIndex( CStifItemParser& aItem );

    /**
     * TestLBSetCurrentItemIndex test function for testing the 
     *     SetCurrentItemIndex function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBSetCurrentItemIndex( CStifItemParser& aItem );

    /**
     * TestLBSetCurrentItemIndexAndDraw test function for testing the 
     *     SetCurrentItemIndexAndDraw function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBSetCurrentItemIndexAndDraw( CStifItemParser& aItem );

    /**
     * SelectionIndexesL test function for testing the 
     *     SelectionIndexes function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBSelectionIndexesL( CStifItemParser& aItem );

    /**
     * TestLBSetSelectionIndexesL test function for testing the 
     *     SetSelectionIndexesL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBSetSelectionIndexesL( CStifItemParser& aItem );

    /**
     * TestLBClearSelection test function for testing the 
     *     ClearSelection function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBClearSelection( CStifItemParser& aItem );

    /**
     * TestLBHandleItemAdditionL test function for testing the 
     *     HandleItemAdditionL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBHandleItemAdditionL( CStifItemParser& aItem );

    /**
     * TestLBHandleItemRemovalL test function for testing the 
     *     HandleItemRemovalL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBHandleItemRemovalL( CStifItemParser& aItem );

    /**
     * TestLBHandleItemAdditionWIthParaL test function for testing the 
     *     HandleItemAdditionL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBHandleItemAdditionWIthParaL( CStifItemParser& aItem );

    /**
     * TestLBHandleItemRemovalWIthParaL test function for testing the 
     *     HandleItemRemovalL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBHandleItemRemovalWIthParaL( CStifItemParser& aItem );

    /**
     * TestLBReset test function for testing the 
     *     Reset function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBReset( CStifItemParser& aItem );

    /**
     * TestLBAddItemChangeObserverL test function for testing the 
     *     AddItemChangeObserverL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBAddItemChangeObserverL( CStifItemParser& aItem );

    /**
     * TestLBRemoveItemChangeObserver test function for testing the 
     *     RemoveItemChangeObserver function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBRemoveItemChangeObserverL( CStifItemParser& aItem );

    /**
     * TestLBSetItemHeightL test function for testing the 
     *     SetItemHeightL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBSetItemHeightL( CStifItemParser& aItem );

    /**
     * TestLBItemHeight test function for testing the 
     *     ItemHeight function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBItemHeight( CStifItemParser& aItem );

    /**
     * TestLBCreateScrollBarFrameL test function for testing the 
     *     CreateScrollBarFrameL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBCreateScrollBarFrameL( CStifItemParser& aItem );

    /**
     * TestLBSetScrollBarFrameL test function for testing the 
     *     SetScrollBarFrame function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBSetScrollBarFrameL( CStifItemParser& aItem );

    /**
     * TestLBScrollBarFrameL test function for testing the 
     *     ScrollBarFrame function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBScrollBarFrameL( CStifItemParser& aItem );

    /**
     * TestLBUpdateScrollBarsL test function for testing the 
     *     UpdateScrollBarsL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBUpdateScrollBarsL( CStifItemParser& aItem );

    /**
     * TestLBCalculatePopoutRect test function for testing the 
     *     CalculatePopoutRect function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBCalculatePopoutRect( CStifItemParser& aItem );

    /**
     * TestLBCalcSizeInPixels test function for testing the 
     *     CalcSizeInPixels function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBCalcSizeInPixels( CStifItemParser& aItem );

    /**
     * TestLBCalcWidthBasedOnNumOfChars test function for testing the 
     *     CalcWidthBasedOnNumOfChars function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBCalcWidthBasedOnNumOfChars( CStifItemParser& aItem );

    /**
     * TestLBCalcHeightBasedOnNumOfItems test function for testing the 
     *     CalcHeightBasedOnNumOfItems function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBCalcHeightBasedOnNumOfItems( CStifItemParser& aItem );

    /**
     * TestLBCalcWidthBasedOnRequiredItemWidth test function for testing the 
     *     CalcWidthBasedOnRequiredItemWidth function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBCalcWidthBasedOnRequiredItemWidth( CStifItemParser& aItem );

    /**
     * TestLBDrawItem test function for testing the 
     *     DrawItem function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBDrawItem( CStifItemParser& aItem );

    /**
     * TestLBScrollToMakeItemVisible test function for testing the 
     *     ScrollToMakeItemVisible function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBScrollToMakeItemVisible( CStifItemParser& aItem );

    /**
     * TestLBRedrawItem test function for testing the 
     *     RedrawItem function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBRedrawItem( CStifItemParser& aItem );

    /**
     * TestLBSetListBoxObserver test function for testing the 
     *     SetListBoxObserver function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBSetListBoxObserver( CStifItemParser& aItem );

    /**
     * TestLBVerticalInterItemGap test function for testing the 
     *     VerticalInterItemGap function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBVerticalInterItemGap( CStifItemParser& aItem );

    /**
     * TestLBSetLaunchingButton test function for testing the 
     *     SetLaunchingButton function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBSetLaunchingButton( CStifItemParser& aItem );

    /**
     * TestLBSetItemEditorL test function for testing the 
     *     SetItemEditor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBSetItemEditorL( CStifItemParser& aItem );

    /**
     * TestLBResetItemEditor test function for testing the 
     *     ResetItemEditor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBResetItemEditor( CStifItemParser& aItem );

    /**
     * TestLBItemEditorL test function for testing the 
     *     ItemEditor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBItemEditorL( CStifItemParser& aItem );

    /**
     * TestLBEditItemL test function for testing the 
     *     EditItemL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBEditItemL( CStifItemParser& aItem );

    /**
     * TestLBStopEditingL test function for testing the 
     *     StopEditingL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBStopEditingL( CStifItemParser& aItem );

    /**
     * TestLBShortcutValueForNextList test function for testing the 
     *     ShortcutValueForNextList function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBShortcutValueForNextList( CStifItemParser& aItem );

    /**
     * TestLBSetShortcutValueFromPrevList test function for testing the 
     *     SetShortcutValueFromPrevList function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBSetShortcutValueFromPrevList( CStifItemParser& aItem );

    /**
     * TestLBHighlightRect test function for testing the 
     *     HighlightRect function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBHighlightRect( CStifItemParser& aItem );

    /**
     * TestLBGetColorUseListL test function for testing the 
     *     GetColorUseListL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBGetColorUseListL( CStifItemParser& aItem );

    /**
     * TestLBHandleResourceChange test function for testing the 
     *     HandleResourceChange function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBHandleResourceChange( CStifItemParser& aItem );

    /**
     * TestLBActivateL test function for testing the 
     *     ActivateL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBActivateL( CStifItemParser& aItem );

    /**
     * TestLBInputCapabilities test function for testing the 
     *     InputCapabilities function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBInputCapabilities( CStifItemParser& aItem );

    /**
     * TestLBEventModifiers test function for testing the 
     *     EventModifiers function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBEventModifiers( CStifItemParser& aItem );

    /**
     * TestLBIsMultiselection test function for testing the 
     *     IsMultiselection function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBIsMultiselection( CStifItemParser& aItem );

    /**
     * CreateScrollBarFrameL test function for testing the 
     *     CreateScrollBarFrameL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBCreateScrollBarFrameWithTwoParaL( CStifItemParser& aItem );

    /**
     * CreateScrollBarFrameL test function for testing the 
     *     CreateScrollBarFrameL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBCreateScrollBarFrameWithThreeParaL( CStifItemParser& aItem );

    /**
     * TestLBEnableMSKObserver test function for testing the 
     *     EnableMSKObserver function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBEnableMSKObserver( CStifItemParser& aItem );

    /**
     * TestLBAddSelectionObserverL test function for testing the 
     *     AddSelectionObserverL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBAddSelectionObserverL( CStifItemParser& aItem );

    /**
     * TestLBRemoveSelectionObserverL test function for testing the 
     *     RemoveSelectionObserver function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBRemoveSelectionObserverL( CStifItemParser& aItem );

    /**
     * TestLBFocusChangedL test function for testing the 
     *     FocusChanged function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBFocusChangedL( CStifItemParser& aItem );

    /**
     * TestLBSizeChangedL test function for testing the 
     *     SizeChanged function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBSizeChangedL( CStifItemParser& aItem );

    /**
     * TestLBHandleViewRectSizeChangeL test function for testing the 
     *     HandleViewRectSizeChangeL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBHandleViewRectSizeChangeL( CStifItemParser& aItem );

    /**
     * TestLBCountComponentControlsL test function for testing the 
     *     CountComponentControls function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBCountComponentControlsL( CStifItemParser& aItem );

    /**
     * TestLBComponentControlL test function for testing the 
     *     ComponentControl function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBComponentControlL( CStifItemParser& aItem );

    /**
     * TestLBCreateMatchBufferL test function for testing the 
     *     CreateMatchBufferL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBCreateMatchBufferL( CStifItemParser& aItem );

    /**
     * TestLBClearMatchBufferL test function for testing the 
     *     ClearMatchBuffer function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBClearMatchBufferL( CStifItemParser& aItem );

    /**
     * TestLBMatchTypedCharL test function for testing the 
     *     MatchTypedCharL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBMatchTypedCharL( CStifItemParser& aItem );

    /**
     * TestLBUndoLastCharL test function for testing the 
     *     UndoLastChar function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBUndoLastCharL( CStifItemParser& aItem );

    /**
     * TestLBLastCharMatchedL test function for testing the 
     *     LastCharMatched function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBLastCharMatchedL( CStifItemParser& aItem );

    /**
     * TestLBUpdateScrollBarThumbsL test function for testing the 
     *     UpdateScrollBarThumbs function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBUpdateScrollBarThumbsL( CStifItemParser& aItem );

    /**
     * TestLBHorizScrollGranularityInPixelsL test function for testing the 
     *     HorizScrollGranularityInPixels function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBHorizScrollGranularityInPixelsL( CStifItemParser& aItem );

    /**
     * TestLBHorizontalNudgeValueL test function for testing the 
     *     HorizontalNudgeValue function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBHorizontalNudgeValueL( CStifItemParser& aItem );

    /**
     * TestLBAdjustTopItemIndexL test function for testing the 
     *     AdjustTopItemIndex function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBAdjustTopItemIndexL( CStifItemParser& aItem );

    /**
     * TestLBSimulateArrowKeyEventL test function for testing the 
     *     SimulateArrowKeyEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBSimulateArrowKeyEventL( CStifItemParser& aItem );

    /**
     * TestLBHandleLeftArrowKeyL test function for testing the 
     *     HandleLeftArrowKeyL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBHandleLeftArrowKeyL( CStifItemParser& aItem );

    /**
     * TestLBHandleRightArrowKeyL test function for testing the 
     *     HandleRightArrowKeyL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBHandleRightArrowKeyL( CStifItemParser& aItem );

    /**
     * TestLBRestoreCommonListBoxPropertiesL test function for testing the 
     *     RestoreCommonListBoxPropertiesL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBRestoreCommonListBoxPropertiesL( CStifItemParser& aItem );

    /**
     * TestLBProtectedConstructL test function for testing the 
     *     ConstructL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBProtectedConstructL( CStifItemParser& aItem );

    /**
     * TestLBCreateViewL test function for testing the 
     *     CreateViewL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBCreateViewL( CStifItemParser& aItem );

    /**
     * TestLBMakeViewClassInstanceL test function for testing the 
     *     MakeViewClassInstanceL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBMakeViewClassInstanceL( CStifItemParser& aItem );

    /**
     * TestLBSetViewRectFromClientRectL test function for testing the 
     *     SetViewRectFromClientRect function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBSetViewRectFromClientRectL( CStifItemParser& aItem );

    /**
     * TestLBRestoreClientRectFromViewRectL test function for testing the 
     *     RestoreClientRectFromViewRect function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBRestoreClientRectFromViewRectL( CStifItemParser& aItem );

    /**
     * TestLBAdjustRectHeightToWholeNumberOfItemsL test function for testing the 
     *     AdjustRectHeightToWholeNumberOfItems function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBAdjustRectHeightToWholeNumberOfItemsL( CStifItemParser& aItem );

    /**
     * TestLBListBoxMarginsL test function for testing the 
     *     ListBoxMargins function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBListBoxMarginsL( CStifItemParser& aItem );

    /**
     * TestLBHorizontalMarginL test function for testing the 
     *     HorizontalMargin function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBHorizontalMarginL( CStifItemParser& aItem );

    /**
     * TestLBVerticalMarginL test function for testing the 
     *     VerticalMargin function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBVerticalMarginL( CStifItemParser& aItem );

    /**
     * TestLBSetHorizontalMarginL test function for testing the 
     *     SetHorizontalMargin function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBSetHorizontalMarginL( CStifItemParser& aItem );

    /**
     * TestLBSetVerticalMarginL test function for testing the 
     *     SetVerticalMargin function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBSetVerticalMarginL( CStifItemParser& aItem );

    /**
     * TestLBMatchBufferL test function for testing the 
     *     MatchBuffer function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBMatchBufferL( CStifItemParser& aItem );

    /**
     * TestLBViewRectHeightAdjustmentL test function for testing the 
     *     ViewRectHeightAdjustment function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBViewRectHeightAdjustmentL( CStifItemParser& aItem );

    /**
     * TestLBBackColorL test function for testing the 
     *     BackColor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBBackColorL( CStifItemParser& aItem );

    /**
     * TestLBSetViewRectHeightAdjustmentL test function for testing the 
     *     SetViewRectHeightAdjustment function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBSetViewRectHeightAdjustmentL( CStifItemParser& aItem );

    /**
     * TestLBReportListBoxEventL test function for testing the 
     *     ReportListBoxEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBReportListBoxEventL( CStifItemParser& aItem );

    /**
     * TestLBDrawL test function for testing the 
     *     Draw function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBDrawL( CStifItemParser& aItem );

    /**
     * TestLBClearMarginsL test function for testing the 
     *     ClearMargins function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBClearMarginsL( CStifItemParser& aItem );

    /**
     * TestLBUpdateCurrentItemL test function for testing the 
     *     UpdateCurrentItem function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBUpdateCurrentItemL( CStifItemParser& aItem );

    /**
     * TestLBHandleDragEventL test function for testing the 
     *     HandleDragEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBHandleDragEventL( CStifItemParser& aItem );

    /**
     * TestLBItemExistsL test function for testing the 
     *     ItemExists function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBItemExistsL( CStifItemParser& aItem );

    /**
     * TestLBDrawMatcherCursorL test function for testing the 
     *     DrawMatcherCursor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBDrawMatcherCursorL( CStifItemParser& aItem );

    /**
     * TestLBInterItemGapL test function for testing the 
     *     InterItemGap function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBInterItemGapL( CStifItemParser& aItem );

    /**
     * TestLBUpdateViewColorsL test function for testing the 
     *     UpdateViewColors function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBUpdateViewColorsL( CStifItemParser& aItem );

    /**
     * TestLBUpdateItemDrawerColorsL test function for testing the 
     *     UpdateItemDrawerColors function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBUpdateItemDrawerColorsL( CStifItemParser& aItem );

    /**
     * TestLBFireItemChangeL test function for testing the 
     *     FireItemChange function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBFireItemChangeL( CStifItemParser& aItem );

    /**
     * TestLBSetReasonForFocusLostL test function for testing the 
     *     SetReasonForFocusLostL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBSetReasonForFocusLostL( CStifItemParser& aItem );

    /**
     * TestLBReasonForFocusLostL test function for testing the 
     *     ReasonForFocusLostL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBReasonForFocusLostL( CStifItemParser& aItem );

    /**
     * TestLBIsMatchBufferL test function for testing the 
     *     IsMatchBuffer function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBIsMatchBufferL( CStifItemParser& aItem );

    /**
     * TestLBCreateScrollBarFrameLayoutL test function for testing the 
     *     CreateScrollBarFrameLayout function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBCreateScrollBarFrameLayoutL( CStifItemParser& aItem );

    // class CEikSnakingListBox
    /**
     * TestSLBConstructorL test function for testing the 
     *     Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSLBConstructorL( CStifItemParser& aItem );

    /**
     * TestSLBDestructorL test function for testing the 
     *     Destructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSLBDestructorL( CStifItemParser& aItem );

    /**
     * TestSLBMakeViewClassInstanceL test function for testing the 
     *     MakeViewClassInstanceL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSLBMakeViewClassInstanceL( CStifItemParser& aItem );

    /**
     * TestSLBSetTopItemIndexL test function for testing the 
     *     SetTopItemIndex function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSLBSetTopItemIndexL( CStifItemParser& aItem );

    /**
     * TestSLBColumnWidthL test function for testing the 
     *     ColumnWidth function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSLBColumnWidthL( CStifItemParser& aItem );

    /**
     * TestSLBSetColumnWidthL test function for testing the 
     *     SetColumnWidth function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSLBSetColumnWidthL( CStifItemParser& aItem );

    /**
     * TestSLBHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSLBHandlePointerEventL( CStifItemParser& aItem );

    /**
     * TestSLBHandleViewRectSizeChangeL test function for testing the 
     *     HandleViewRectSizeChangeL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSLBHandleViewRectSizeChangeL( CStifItemParser& aItem );

    /**
     * TestSLBHandleLeftArrowKeyL test function for testing the 
     *     HandleLeftArrowKeyL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSLBHandleLeftArrowKeyL( CStifItemParser& aItem );

    /**
     * TestSLBHandleRightArrowKeyL test function for testing the 
     *     HandleRightArrowKeyL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSLBHandleRightArrowKeyL( CStifItemParser& aItem );

    /**
     * TestSLBHandleRightArrowKeyL test function for testing the 
     *     HandleRightArrowKeyL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSLBHorizontalNudgeValueL( CStifItemParser& aItem );

    /**
     * TestSLBHorizScrollGranularityInPixelsL test function for testing the 
     *     HorizScrollGranularityInPixels function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSLBHorizScrollGranularityInPixelsL( CStifItemParser& aItem );

    /**
     * TestSLBAdjustTopItemIndexL test function for testing the 
     *     AdjustTopItemIndex function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSLBAdjustTopItemIndexL( CStifItemParser& aItem );

    /**
     * TestSLBHandleDragEventL test function for testing the 
     *     HandleDragEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSLBHandleDragEventL( CStifItemParser& aItem );

    /**
     * TestSLBRestoreClientRectFromViewRectL test function for testing the 
     *     RestoreClientRectFromViewRect function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSLBRestoreClientRectFromViewRectL( CStifItemParser& aItem );

    /**
     * TestSLBAdjustRectHeightToWholeNumberOfItemsL test function for testing the 
     *     AdjustRectHeightToWholeNumberOfItems function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSLBAdjustRectHeightToWholeNumberOfItemsL( CStifItemParser& aItem );

    /**
     * TestSLBMoveToNextOrPreviousItemL test function for testing the 
     *     MoveToNextOrPreviousItemL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSLBMoveToNextOrPreviousItemL( CStifItemParser& aItem );

    /**
     * TestSLBSizeChangedL test function for testing the 
     *     SizeChanged function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSLBSizeChangedL( CStifItemParser& aItem );

    /**
     * TestSLBSizeChangedL test function for testing the 
     *     SizeChanged function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSLBGetColorUseListL( CStifItemParser& aItem );

    /**
     * TestSLBHandleResourceChangeL test function for testing the 
     *     HandleResourceChange function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSLBHandleResourceChangeL( CStifItemParser& aItem );

    /**
     * TestLBDisableScrolling test function for testing the 
     *     DisableScrolling function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBDisableScrolling( CStifItemParser& aItem );

    /**
     * TestLBSetItemsInSingleLine test function for testing the 
     *     SetItemsInSingleLine function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBSetItemsInSingleLine( CStifItemParser& aItem );

    /**
     * TestLBBackgroundDrawingSuppressed test function for testing the 
     *     BackgroundDrawingSuppressed function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBBackgroundDrawingSuppressed( CStifItemParser& aItem );

    /**
     * TestLBHandlePhysicsScrollEventL test function for testing the 
     *     HandlePhysicsScrollEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBHandlePhysicsScrollEventL( CStifItemParser& aItem );

    /**
     * TestLBDisableSingleClick test function for testing the 
     *     DisableSingleClick function
     * @since S60 5.2
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBDisableSingleClick( CStifItemParser& aItem );

    /**
     * TestLBDisableItemSpecificMenu test function for testing the 
     *     DisableItemSpecificMenu function
     * @since S60 5.2
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBDisableItemSpecificMenu( CStifItemParser& aItem );

private:    // eikslb.h
    // class CSettingsListBoxItemDrawer
    /**
     * TestSLBIDConstructorL test function for testing the 
     *     Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSLBIDConstructorL( CStifItemParser& aItem );

    /**
     * TestSLBIDDetructorL test function for testing the 
     *     Detructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSLBIDDetructorL( CStifItemParser& aItem );

    /**
     * TestSLBIDSettingsDataL test function for testing the 
     *     SettingsData function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSLBIDSettingsDataL( CStifItemParser& aItem );

    /**
     * TestSLBIDDrawItemTextL test function for testing the 
     *     DrawItemText function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSLBIDDrawItemTextL( CStifItemParser& aItem );

    // class CEikSettingsListBox
    /**
     * TestSettingsLBConstructorL test function for testing the 
     *     Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingsLBConstructorL( CStifItemParser& aItem );

    /**
     * TestSettingsLBItemDrawerL test function for testing the 
     *     ItemDrawer function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingsLBItemDrawerL( CStifItemParser& aItem );

    /**
     * TestSettingsLBMakeViewClassInstanceL test function for testing the 
     *     MakeViewClassInstanceL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingsLBMakeViewClassInstanceL( CStifItemParser& aItem );

    /**
     * TestSettingsLBHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingsLBHandlePointerEventL( CStifItemParser& aItem );

    /**
     * TestSettingsLBCreateItemDrawerL test function for testing the 
     *     CreateItemDrawerL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingsLBCreateItemDrawerL( CStifItemParser& aItem );

    // class CSettingsListBoxView
    /**
     * TestSettingsLBVDrawL test function for testing the 
     *     Draw function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingsLBVDrawL( CStifItemParser& aItem );

    /**
     * TestSettingsLBVDrawItemL test function for testing the 
     *     DrawItem function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingsLBVDrawItemL( CStifItemParser& aItem );

    /**
     * TestSettingsLBVItemDrawerL test function for testing the 
     *     ItemDrawer function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingsLBVItemDrawerL( CStifItemParser& aItem );

private: // eiktxlbm.h
    /**
     * TestTXLBMConstructorL test function for testing the 
     *     Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestTXLBMConstructorL( CStifItemParser& aItem );

    /**
     * TestTXLBMDestructorL test function for testing the 
     *     Destructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestTXLBMDestructorL( CStifItemParser& aItem );

    /**
     * TestTXLBMNumberOfItemsL test function for testing the 
     *     NumberOfItems function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestTXLBMNumberOfItemsL( CStifItemParser& aItem );

    /**
     * TestTXLBMMatchableTextArrayL test function for testing the 
     *     MatchableTextArray function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestTXLBMMatchableTextArrayL( CStifItemParser& aItem );

    /**
     * TestTXLBMItemTextL test function for testing the 
     *     ItemText function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestTXLBMItemTextL( CStifItemParser& aItem );

    /**
     * TestTXLBMConstructL test function for testing the 
     *     ConstructL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestTXLBMConstructL( CStifItemParser& aItem );

    /**
     * TestTXLBMSetItemTextArrayL test function for testing the 
     *     SetItemTextArray function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestTXLBMSetItemTextArrayL( CStifItemParser& aItem );

    /**
     * TestTXLBMSetOwnershipTypeL test function for testing the 
     *     SetOwnershipType function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestTXLBMSetOwnershipTypeL( CStifItemParser& aItem );

    /**
     * TestTXLBMItemTextArrayL test function for testing the 
     *     ItemTextArray function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestTXLBMItemTextArrayL( CStifItemParser& aItem );

    /**
     * TestTXLBMItemArrayOwnershipTypeL test function for testing the 
     *     ItemArrayOwnershipType function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestTXLBMItemArrayOwnershipTypeL( CStifItemParser& aItem );

private: // eiktxlbx.h
    // class CEikTextListBox
    /**
     * TestTXLBConstructorL test function for testing the 
     *     Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestTXLBConstructorL( CStifItemParser& aItem );

    /**
     * TestTXLBDestructorL test function for testing the 
     *     Destructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestTXLBDestructorL( CStifItemParser& aItem );

    /**
     * TestTXLBConstructFromResourceL test function for testing the 
     *     ConstructFromResourceL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestTXLBConstructFromResourceL( CStifItemParser& aItem );

    /**
     * TestTXLBConstructL test function for testing the 
     *     ConstructL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestTXLBConstructL( CStifItemParser& aItem );

    /**
     * TestTXLBModelL test function for testing the 
     *     Model function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestTXLBModelL( CStifItemParser& aItem );

    /**
     * TestTXLBGetColorUseListL test function for testing the 
     *     GetColorUseListL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestTXLBGetColorUseListL( CStifItemParser& aItem );

    /**
     * TestTXLBHandleResourceChangeL test function for testing the 
     *     HandleResourceChange function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestTXLBHandleResourceChangeL( CStifItemParser& aItem );

    /**
     * TestTXLBHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestTXLBHandlePointerEventL( CStifItemParser& aItem );

    /**
     * TestTXLBWriteInternalStateL test function for testing the 
     *     WriteInternalStateL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestTXLBWriteInternalStateL( CStifItemParser& aItem );

    /**
     * TestTXLBHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestTXLBCreateItemDrawerL( CStifItemParser& aItem );

    // class CEikSnakingTextListBox
    /**
     * TestSTXLBConstructorL test function for testing the 
     *     Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSTXLBConstructorL( CStifItemParser& aItem );

    /**
     * TestSTXLBDestructorL test function for testing the 
     *     Destructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSTXLBDestructorL( CStifItemParser& aItem );

    /**
     * TestSTXLBConstructL test function for testing the 
     *     ConstructL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSTXLBConstructL( CStifItemParser& aItem );

    /**
     * TestSTXLBModelL test function for testing the 
     *     Model function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSTXLBModelL( CStifItemParser& aItem );

    /**
     * TestSTXLBGetColorUseListL test function for testing the 
     *     GetColorUseListL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSTXLBGetColorUseListL( CStifItemParser& aItem );

    /**
     * TestSTXLBHandleResourceChangeL test function for testing the 
     *     HandleResourceChange function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSTXLBHandleResourceChangeL( CStifItemParser& aItem );

    /**
     * TestSTXLBHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSTXLBHandlePointerEventL( CStifItemParser& aItem );

private: // aknlists.h
    // class CAknColumnListBox
    /**
     * TestACLBMakeViewClassInstanceL test function for testing the 
     *     MakeViewClassInstanceL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestACLBMakeViewClassInstanceL( CStifItemParser& aItem );

    /**
     * CreateModelL test function for testing the 
     *     TestACLBCreateModelL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestACLBCreateModelL( CStifItemParser& aItem );

    /**
     * TestACLBAdjustRectHeightToWholeNumberOfItemsL test function for testing the 
     *     AdjustRectHeightToWholeNumberOfItems function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestACLBAdjustRectHeightToWholeNumberOfItemsL( CStifItemParser& aItem );

    /**
     * TestACLBHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestACLBHandlePointerEventL( CStifItemParser& aItem );

    // class AknListBoxLinesTemplate
    /**
     * TestLinesTemplateConstructorL test function for testing the 
     *     Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLinesTemplateConstructorL( CStifItemParser& aItem );

    /**
     * TestLinesTemplateSizeChangedL test function for testing the 
     *     SizeChanged function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLinesTemplateSizeChangedL( CStifItemParser& aItem );

    /**
     * TestLinesTemplateDrawL test function for testing the 
     *     Draw function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLinesTemplateDrawL( CStifItemParser& aItem );

    /**
     * TestLinesTemplateCountComponentControlsL test function for testing the 
     *     CountComponentControls function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLinesTemplateCountComponentControlsL( CStifItemParser& aItem );

    /**
     * TestLinesTemplateComponentControlL test function for testing the 
     *     ComponentControl function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLinesTemplateComponentControlL( CStifItemParser& aItem );

    // class CAknSingleStyleListBox
    /**
     * TestASSLBConstructorL test function for testing the 
     *     Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestASSLBConstructorL( CStifItemParser& aItem );

    /**
     * TestASSLBSizeChangedL test function for testing the 
     *     SizeChanged function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestASSLBSizeChangedL( CStifItemParser& aItem );

    /**
     * TestASSLBMinimumSizeL test function for testing the 
     *     MinimumSize function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestASSLBMinimumSizeL( CStifItemParser& aItem );

    /**
     * TestASSLBHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestASSLBHandlePointerEventL( CStifItemParser& aItem );

    // class CAknSingleNumberStyleListBox
    /**
     * TestASNSLBConstructorL test function for testing the 
     *     Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestASNSLBConstructorL( CStifItemParser& aItem );

    /**
     * TestASNSLBSizeChangedL test function for testing the 
     *     SizeChanged function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestASNSLBSizeChangedL( CStifItemParser& aItem );

    /**
     * TestASNSLBMinimumSizeL test function for testing the 
     *     MinimumSize function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestASNSLBMinimumSizeL( CStifItemParser& aItem );

    /**
     * TestASNSLBHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestASNSLBHandlePointerEventL( CStifItemParser& aItem );

    // class CAknSingleHeadingStyleListBox
    /**
     * TestASHSLBConstructorL test function for testing the 
     *     Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestASHSLBConstructorL( CStifItemParser& aItem );

    /**
     * TestASHSLBSizeChangedL test function for testing the 
     *     SizeChanged function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestASHSLBSizeChangedL( CStifItemParser& aItem );

    /**
     * TestASHSLBMinimumSizeL test function for testing the 
     *     MinimumSize function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestASHSLBMinimumSizeL( CStifItemParser& aItem );

    /**
     * TestASHSLBHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestASHSLBHandlePointerEventL( CStifItemParser& aItem );

    /**
     * TestASHSLBCreateItemDrawerL test function for testing the 
     *     CreateItemDrawerL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestASHSLBCreateItemDrawerL( CStifItemParser& aItem );

    /**
     * TestASHSLBMakeViewClassInstanceL test function for testing the 
     *     MakeViewClassInstanceL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestASHSLBMakeViewClassInstanceL( CStifItemParser& aItem );

    // class CAknSingleGraphicStyleListBox
    /**
     * TestASGSLBConstructorL test function for testing the 
     *     Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestASGSLBConstructorL( CStifItemParser& aItem );

    /**
     * TestASGSLBSizeChangedL test function for testing the 
     *     SizeChanged function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestASGSLBSizeChangedL( CStifItemParser& aItem );

    /**
     * TestASGSLBMinimumSizeL test function for testing the 
     *     MinimumSize function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestASGSLBMinimumSizeL( CStifItemParser& aItem );

    /**
     * TestASGSLBHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestASGSLBHandlePointerEventL( CStifItemParser& aItem );

    // class CAknSingleGraphicHeadingStyleListBox
    /**
     * TestASGHSLBConstructorL test function for testing the 
     *     Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestASGHSLBConstructorL( CStifItemParser& aItem );

    /**
     * TestASGHSLBSizeChangedL test function for testing the 
     *     SizeChanged function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestASGHSLBSizeChangedL( CStifItemParser& aItem );

    /**
     * TestASGHSLBMinimumSizeL test function for testing the 
     *     MinimumSize function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestASGHSLBMinimumSizeL( CStifItemParser& aItem );

    /**
     * TestASGHSLBHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestASGHSLBHandlePointerEventL( CStifItemParser& aItem );

    /**
     * TestASGHSLBCreateItemDrawerL test function for testing the 
     *     CreateItemDrawerL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestASGHSLBCreateItemDrawerL( CStifItemParser& aItem );

    /**
     * TestASGHSLBMakeViewClassInstanceL test function for testing the 
     *     MakeViewClassInstanceL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestASGHSLBMakeViewClassInstanceL( CStifItemParser& aItem );

    // class CAknSingleNumberHeadingStyleListBox
    /**
     * TestASNHSLBConstructorL test function for testing the 
     *     Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestASNHSLBConstructorL( CStifItemParser& aItem );

    /**
     * TestASNHSLBSizeChangedL test function for testing the 
     *     SizeChanged function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestASNHSLBSizeChangedL( CStifItemParser& aItem );

    /**
     * TestASNHSLBMinimumSizeL test function for testing the 
     *     MinimumSize function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestASNHSLBMinimumSizeL( CStifItemParser& aItem );

    /**
     * TestASNHSLBHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestASNHSLBHandlePointerEventL( CStifItemParser& aItem );

    /**
     * TestASNHSLBCreateItemDrawerL test function for testing the 
     *     CreateItemDrawerL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestASNHSLBCreateItemDrawerL( CStifItemParser& aItem );

    /**
     * TestASNHSLBMakeViewClassInstanceL test function for testing the 
     *     MakeViewClassInstanceL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestASNHSLBMakeViewClassInstanceL( CStifItemParser& aItem );

    // class CAknSingleLargeStyleListBox
    /**
     * TestASLSLBConstructorL test function for testing the 
     *     Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestASLSLBConstructorL( CStifItemParser& aItem );

    /**
     * TestASLSLBSizeChangedL test function for testing the 
     *     SizeChanged function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestASLSLBSizeChangedL( CStifItemParser& aItem );

    /**
     * TestASLSLBMinimumSizeL test function for testing the 
     *     MinimumSize function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestASLSLBMinimumSizeL( CStifItemParser& aItem );

    /**
     * TestASLSLBHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestASLSLBHandlePointerEventL( CStifItemParser& aItem );

    // class CAknDoubleStyleListBox
    /**
     * TestADSLBConstructorL test function for testing the 
     *     Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestADSLBConstructorL( CStifItemParser& aItem );

    /**
     * TestADSLBSizeChangedL test function for testing the 
     *     SizeChanged function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestADSLBSizeChangedL( CStifItemParser& aItem );

    /**
     * TestADSLBMinimumSizeL test function for testing the 
     *     MinimumSize function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestADSLBMinimumSizeL( CStifItemParser& aItem );

    /**
     * TestADSLBHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestADSLBHandlePointerEventL( CStifItemParser& aItem );

    // class CAknDoubleStyle2ListBox
    /**
     * TestADS2LBSizeChangedL test function for testing the 
     *     SizeChanged function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestADS2LBSizeChangedL( CStifItemParser& aItem );

    /**
     * TestADS2LBCreateItemDrawerL test function for testing the 
     *     MinimumSize function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestADS2LBCreateItemDrawerL( CStifItemParser& aItem );

    /**
     * TestADS2LBHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestADS2LBHandlePointerEventL( CStifItemParser& aItem );

    // class CAknDoubleNumberStyleListBox
    /**
     * TestADNSLBConstructorL test function for testing the 
     *     Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestADNSLBConstructorL( CStifItemParser& aItem );

    /**
     * TestADNSLBSizeChangedL test function for testing the 
     *     SizeChanged function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestADNSLBSizeChangedL( CStifItemParser& aItem );

    /**
     * TestADNSLBMinimumSizeL test function for testing the 
     *     MinimumSize function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestADNSLBMinimumSizeL( CStifItemParser& aItem );

    /**
     * TestADNSLBHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestADNSLBHandlePointerEventL( CStifItemParser& aItem );

    // class CAknDoubleTimeStyleListBox
    /**
     * TestADTSLBConstructorL test function for testing the 
     *     Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestADTSLBConstructorL( CStifItemParser& aItem );

    /**
     * TestADTSLBSizeChangedL test function for testing the 
     *     SizeChanged function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestADTSLBSizeChangedL( CStifItemParser& aItem );

    /**
     * TestADTSLBMinimumSizeL test function for testing the 
     *     MinimumSize function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestADTSLBMinimumSizeL( CStifItemParser& aItem );

    /**
     * TestADTSLBHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestADTSLBHandlePointerEventL( CStifItemParser& aItem );

    // class CAknDoubleLargeStyleListBox
    /**
     * TestADLSLBConstructorL test function for testing the 
     *     Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestADLSLBConstructorL( CStifItemParser& aItem );

    /**
     * TestADLSLBSizeChangedL test function for testing the 
     *     SizeChanged function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestADLSLBSizeChangedL( CStifItemParser& aItem );

    /**
     * TestADLSLBMinimumSizeL test function for testing the 
     *     MinimumSize function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestADLSLBMinimumSizeL( CStifItemParser& aItem );

    /**
     * TestADLSLBCreateItemDrawerL test function for testing the 
     *     CreateItemDrawerL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestADLSLBCreateItemDrawerL( CStifItemParser& aItem );

    /**
     * TestADLSLBHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestADLSLBHandlePointerEventL( CStifItemParser& aItem );

    // class CAknDoubleGraphicStyleListBox
    /**
     * TestADGSLBConstructorL test function for testing the 
     *     Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestADGSLBConstructorL( CStifItemParser& aItem );

    /**
     * TestADGSLBSizeChangedL test function for testing the 
     *     SizeChanged function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestADGSLBSizeChangedL( CStifItemParser& aItem );

    /**
     * TestADGSLBMinimumSizeL test function for testing the 
     *     MinimumSize function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestADGSLBMinimumSizeL( CStifItemParser& aItem );

    /**
     * TestADGSLBHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestADGSLBHandlePointerEventL( CStifItemParser& aItem );

    // class CAknDouble2GraphicStyleListBox
    /**
     * TestAD2GSLBConstructorL test function for testing the 
     *     Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAD2GSLBConstructorL( CStifItemParser& aItem );

    /**
     * TestAD2GSLBSizeChangedL test function for testing the 
     *     SizeChanged function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAD2GSLBSizeChangedL( CStifItemParser& aItem );

    /**
     * TestAD2GSLBMinimumSizeL test function for testing the 
     *     MinimumSize function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAD2GSLBMinimumSizeL( CStifItemParser& aItem );

    /**
     * TestAD2GSLBCreateItemDrawerL test function for testing the 
     *     CreateItemDrawerL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAD2GSLBCreateItemDrawerL( CStifItemParser& aItem );

    /**
     * TestAD2GSLBHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAD2GSLBHandlePointerEventL( CStifItemParser& aItem );

    // class CAknDouble2LargeStyleListBox
    /**
     * TestAD2LSLBConstructorL test function for testing the 
     *     Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAD2LSLBConstructorL( CStifItemParser& aItem );

    /**
     * TestAD2LSLBSizeChangedL test function for testing the 
     *     SizeChanged function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAD2LSLBSizeChangedL( CStifItemParser& aItem );

    /**
     * TestAD2LSLBMinimumSizeL test function for testing the 
     *     MinimumSize function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAD2LSLBMinimumSizeL( CStifItemParser& aItem );

    /**
     * TestAD2LSLBCreateItemDrawerL test function for testing the 
     *     CreateItemDrawerL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAD2LSLBCreateItemDrawerL( CStifItemParser& aItem );

    /**
     * TestAD2LSLBHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAD2LSLBHandlePointerEventL( CStifItemParser& aItem );

    // class CAknDouble2GraphicLargeGraphicStyleListBox
    /**
     * TestAD2GLGSLBConstructorL test function for testing the 
     *     Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAD2GLGSLBConstructorL( CStifItemParser& aItem );

    /**
     * TestAD2GLGSLBSizeChangedL test function for testing the 
     *     SizeChanged function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAD2GLGSLBSizeChangedL( CStifItemParser& aItem );

    /**
     * TestAD2GLGSLBMinimumSizeL test function for testing the 
     *     MinimumSize function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAD2GLGSLBMinimumSizeL( CStifItemParser& aItem );

    /**
     * TestAD2GLGSLBCreateItemDrawerL test function for testing the 
     *     CreateItemDrawerL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAD2GLGSLBCreateItemDrawerL( CStifItemParser& aItem );

    /**
     * TestAD2GLGSLBHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAD2GLGSLBHandlePointerEventL( CStifItemParser& aItem );

    // class CAknFormDoubleGraphicStyleListBox
    /**
     * TestAFDGSLBSizeChangedL test function for testing the 
     *     SizeChanged function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAFDGSLBSizeChangedL( CStifItemParser& aItem );

    /**
     * TestAFDGSLBHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAFDGSLBHandlePointerEventL( CStifItemParser& aItem );

    // class CAknFormDoubleStyleListBox
    /**
     * TestAFDSLBSizeChangedL test function for testing the 
     *     SizeChanged function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAFDSLBSizeChangedL( CStifItemParser& aItem );

    /**
     * TestAFDSLBHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestAFDSLBHandlePointerEventL( CStifItemParser& aItem );

    // class CAknSettingStyleListBox
    /**
     * TestSettingSLBConstructorL test function for testing the 
     *     Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingSLBConstructorL( CStifItemParser& aItem );

    /**
     * TestSettingSLBSizeChangedL test function for testing the 
     *     SizeChanged function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingSLBSizeChangedL( CStifItemParser& aItem );

    /**
     * TestSettingSLBMinimumSizeL test function for testing the 
     *     MinimumSize function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingSLBMinimumSizeL( CStifItemParser& aItem );

    /**
     * TestSettingSLBHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingSLBHandlePointerEventL( CStifItemParser& aItem );

    // class CAknSettingNumberStyleListBox
    /**
     * TestSettingNSLBConstructorL test function for testing the 
     *     Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingNSLBConstructorL( CStifItemParser& aItem );

    /**
     * TestSettingNSLBSizeChangedL test function for testing the 
     *     SizeChanged function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingNSLBSizeChangedL( CStifItemParser& aItem );

    /**
     * TestSettingNSLBMinimumSizeL test function for testing the 
     *     MinimumSize function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingNSLBMinimumSizeL( CStifItemParser& aItem );

    /**
     * TestSettingNSLBHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingNSLBHandlePointerEventL( CStifItemParser& aItem );

    // class CAknSinglePopupMenuStyleListBox
    /**
     * TestSPMSLBSizeChangedL test function for testing the 
     *     SizeChanged function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSPMSLBSizeChangedL( CStifItemParser& aItem );

    /**
     * TestSPMSLBMinimumSizeL test function for testing the 
     *     MinimumSize function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSPMSLBMinimumSizeL( CStifItemParser& aItem );

    /**
     * TestSPMSLBCreateItemDrawerL test function for testing the 
     *     CreateItemDrawerL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSPMSLBCreateItemDrawerL( CStifItemParser& aItem );

    /**
     * TestSPMSLBHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSPMSLBHandlePointerEventL( CStifItemParser& aItem );

    // class CAknSingleGraphicPopupMenuStyleListBox
    /**
     * TestSGPMSLBSizeChangedL test function for testing the 
     *     SizeChanged function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSGPMSLBSizeChangedL( CStifItemParser& aItem );

    /**
     * TestSGPMSLBMinimumSizeL test function for testing the 
     *     MinimumSize function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSGPMSLBMinimumSizeL( CStifItemParser& aItem );

    /**
     * TestSGPMSLBCreateItemDrawerL test function for testing the 
     *     CreateItemDrawerL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSGPMSLBCreateItemDrawerL( CStifItemParser& aItem );

    /**
     * TestSGPMSLBHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSGPMSLBHandlePointerEventL( CStifItemParser& aItem );

    // class CAknSingleGraphicBtPopupMenuStyleListBox
    /**
     * TestSGBPMSLBSizeChangedL test function for testing the 
     *     SizeChanged function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSGBPMSLBSizeChangedL( CStifItemParser& aItem );

    /**
     * TestSGBPMSLBMinimumSizeL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSGBPMSLBHandlePointerEventL( CStifItemParser& aItem );

    // class CAknSingleHeadingPopupMenuStyleListBox
    /**
     * TestSHPMSLBSizeChangedL test function for testing the 
     *     Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSHPMSLBConstructorL( CStifItemParser& aItem );

    /**
     * TestSHPMSLBSizeChangedL test function for testing the 
     *     SizeChanged function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSHPMSLBSizeChangedL( CStifItemParser& aItem );

    /**
     * TestSHPMSLBMinimumSizeL test function for testing the 
     *     MinimumSize function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSHPMSLBMinimumSizeL( CStifItemParser& aItem );

    /**
     * TestSHPMSLBHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSHPMSLBHandlePointerEventL( CStifItemParser& aItem );

    /**
     * TestSHPMSLBCreateItemDrawerL test function for testing the 
     *     CreateItemDrawerL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSHPMSLBCreateItemDrawerL( CStifItemParser& aItem );

    // class CAknSingleGraphicHeadingPopupMenuStyleListBox
    /**
     * TestSGHPMSLBSizeChangedL test function for testing the 
     *     Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSGHPMSLBConstructorL( CStifItemParser& aItem );

    /**
     * TestSGHPMSLBSizeChangedL test function for testing the 
     *     SizeChanged function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSGHPMSLBSizeChangedL( CStifItemParser& aItem );

    /**
     * TestSGHPMSLBMinimumSizeL test function for testing the 
     *     MinimumSize function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSGHPMSLBMinimumSizeL( CStifItemParser& aItem );

    /**
     * TestSGHPMSLBHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSGHPMSLBHandlePointerEventL( CStifItemParser& aItem );

    /**
     * TestSGHPMSLBCreateItemDrawerL test function for testing the 
     *     CreateItemDrawerL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSGHPMSLBCreateItemDrawerL( CStifItemParser& aItem );

    // class CAknDoublePopupMenuStyleListBox
    /**
     * TestDPMSLBSizeChangedL test function for testing the 
     *     SizeChanged function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDPMSLBSizeChangedL( CStifItemParser& aItem );

    /**
     * TestDPMSLBMinimumSizeL test function for testing the 
     *     MinimumSize function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDPMSLBMinimumSizeL( CStifItemParser& aItem );

    /**
     * TestDPMSLBHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDPMSLBHandlePointerEventL( CStifItemParser& aItem );

    /**
     * TestDPMSLBCreateItemDrawerL test function for testing the 
     *     CreateItemDrawerL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDPMSLBCreateItemDrawerL( CStifItemParser& aItem );

    // class CAknSinglePopupSubmenuStyleListBox
    /**
     * TestSPSSLBSizeChangedL test function for testing the 
     *     SizeChanged function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSPSSLBSizeChangedL( CStifItemParser& aItem );

    /**
     * TestSPSSLBMinimumSizeL test function for testing the 
     *     MinimumSize function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSPSSLBMinimumSizeL( CStifItemParser& aItem );

    /**
     * TestSPSSLBHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSPSSLBHandlePointerEventL( CStifItemParser& aItem );

    // class CAknDoubleLargeGraphicPopupMenuStyleListBox
    /**
     * TestDLGPMSLBSizeChangedL test function for testing the 
     *     SizeChanged function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDLGPMSLBSizeChangedL( CStifItemParser& aItem );

    /**
     * TestDLGPMSLBMinimumSizeL test function for testing the 
     *     MinimumSize function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDLGPMSLBMinimumSizeL( CStifItemParser& aItem );

    /**
     * TestDLGPMSLBHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDLGPMSLBHandlePointerEventL( CStifItemParser& aItem );

    /**
     * TestDLGPMSLBCreateItemDrawerL test function for testing the 
     *     CreateItemDrawerL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDLGPMSLBCreateItemDrawerL( CStifItemParser& aItem );

    // class CAknDouble2PopupMenuStyleListBox
    /**
     * TestD2PMSLBSizeChangedL test function for testing the 
     *     SizeChanged function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestD2PMSLBSizeChangedL( CStifItemParser& aItem );

    /**
     * TestD2PMSLBMinimumSizeL test function for testing the 
     *     MinimumSize function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestD2PMSLBMinimumSizeL( CStifItemParser& aItem );

    /**
     * TestD2PMSLBHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestD2PMSLBHandlePointerEventL( CStifItemParser& aItem );

    /**
     * TestD2PMSLBCreateItemDrawerL test function for testing the 
     *     CreateItemDrawerL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestD2PMSLBCreateItemDrawerL( CStifItemParser& aItem );

    // class CAknSingle2GraphicPopupMenuStyleListBox
    /**
     * TestS2GPMSLBConstructorL test function for testing the 
     *     Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestS2GPMSLBConstructorL( CStifItemParser& aItem );

    /**
     * TestS2GPMSLBSizeChangedL test function for testing the 
     *     SizeChanged function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestS2GPMSLBSizeChangedL( CStifItemParser& aItem );

    /**
     * TestS2GPMSLBMinimumSizeL test function for testing the 
     *     MinimumSize function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestS2GPMSLBMinimumSizeL( CStifItemParser& aItem );

    /**
     * TestS2GPMSLBCreateItemDrawerL test function for testing the 
     *     CreateItemDrawerL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestS2GPMSLBCreateItemDrawerL( CStifItemParser& aItem );

    /**
     * TestS2GPMSLBHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestS2GPMSLBHandlePointerEventL( CStifItemParser& aItem );

    // class CAknDoubleGraphicPopupMenuStyleListBox
    /**
     * TestDGPMSLBConstructorL test function for testing the 
     *     Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDGPMSLBConstructorL( CStifItemParser& aItem );

    /**
     * TestDGPMSLBSizeChangedL test function for testing the 
     *     SizeChanged function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDGPMSLBSizeChangedL( CStifItemParser& aItem );

    /**
     * TestDGPMSLBMinimumSizeL test function for testing the 
     *     MinimumSize function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDGPMSLBMinimumSizeL( CStifItemParser& aItem );

    /**
     * TestDGPMSLBCreateItemDrawerL test function for testing the 
     *     CreateItemDrawerL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDGPMSLBCreateItemDrawerL( CStifItemParser& aItem );

    /**
     * TestDGPMSLBHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDGPMSLBHandlePointerEventL( CStifItemParser& aItem );

    // class CAknSetStyleListBox
    /**
     * TestSetSLBConstructWithWindowL test function for testing the 
     *     ConstructWithWindowL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSetSLBConstructWithWindowL( CStifItemParser& aItem );

    /**
     * TestSetSLBSizeChangedL test function for testing the 
     *     SizeChanged function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSetSLBSizeChangedL( CStifItemParser& aItem );

    /**
     * TestSetSLBMinimumSizeL test function for testing the 
     *     MinimumSize function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSetSLBMinimumSizeL( CStifItemParser& aItem );

    /**
     * TestSetSLBDrawL test function for testing the 
     *     Draw function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSetSLBDrawL( CStifItemParser& aItem );

    /**
     * TestSetSLBMopSupplyObjectL test function for testing the 
     *     MopSupplyObject function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSetSLBMopSupplyObjectL( CStifItemParser& aItem );

    /**
     * TestSetSLBHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSetSLBHandlePointerEventL( CStifItemParser& aItem );

    /**
     * TestSetSLBCreateItemDrawerL test function for testing the 
     *     CreateItemDrawerL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSetSLBCreateItemDrawerL( CStifItemParser& aItem );

    /**
     * TestSetSLBMakeViewClassInstanceL test function for testing the 
     *     MakeViewClassInstanceL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSetSLBMakeViewClassInstanceL( CStifItemParser& aItem );

    // class CAknFormGraphicStyleListBox
    /**
     * TestFGSLBConstructWithWindowL test function for testing the 
     *     ConstructWithWindowL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFGSLBConstructWithWindowL( CStifItemParser& aItem );

    /**
     * TestFGSLBSizeChangedL test function for testing the 
     *     SizeChanged function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFGSLBSizeChangedL( CStifItemParser& aItem );

    /**
     * TestFGSLBMinimumSizeL test function for testing the 
     *     MinimumSize function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFGSLBMinimumSizeL( CStifItemParser& aItem );

    /**
     * TestFGSLBCreateItemDrawerL test function for testing the 
     *     CreateItemDrawerL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFGSLBCreateItemDrawerL( CStifItemParser& aItem );

    /**
     * TestFGSLBAdjustRectHeightToWholeNumberOfItemsL test function for testing the 
     *     AdjustRectHeightToWholeNumberOfItems function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFGSLBAdjustRectHeightToWholeNumberOfItemsL( CStifItemParser& aItem );

    /**
     * TestFGSLBHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFGSLBHandlePointerEventL( CStifItemParser& aItem );

    // class CAknFormGraphicWideStyleListBox
    /**
     * TestFGWSLBSizeChangedL test function for testing the 
     *     SizeChanged function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFGWSLBSizeChangedL( CStifItemParser& aItem );

    /**
     * TestFGWSLBMinimumSizeL test function for testing the 
     *     MinimumSize function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFGWSLBMinimumSizeL( CStifItemParser& aItem );

    /**
     * TestFGWSLBHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFGWSLBHandlePointerEventL( CStifItemParser& aItem );

    // class CAknPinbStyleGrid
    /**
     * TestPSGSizeChangedL test function for testing the 
     *     SizeChanged function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestPSGSizeChangedL( CStifItemParser& aItem );

    /**
     * TestPSGMinimumSizeL test function for testing the 
     *     MinimumSize function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestPSGMinimumSizeL( CStifItemParser& aItem );

    /**
     * TestPSGHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestPSGHandlePointerEventL( CStifItemParser& aItem );

    // class CAknQdialStyleGrid
    /**
     * TestQSGSizeChangedL test function for testing the 
     *     SizeChanged function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestQSGSizeChangedL( CStifItemParser& aItem );

    /**
     * TestQSGMinimumSizeL test function for testing the 
     *     MinimumSize function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestQSGMinimumSizeL( CStifItemParser& aItem );

    /**
     * TestQSGHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestQSGHandlePointerEventL( CStifItemParser& aItem );

    // class CAknCaleMonthStyleGrid
    /**
     * TestCMSGSizeChangedL test function for testing the 
     *     SizeChanged function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCMSGSizeChangedL( CStifItemParser& aItem );

    /**
     * TestCMSGMinimumSizeL test function for testing the 
     *     MinimumSize function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCMSGMinimumSizeL( CStifItemParser& aItem );

    /**
     * TestCMSGHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCMSGHandlePointerEventL( CStifItemParser& aItem );

    // class CAknColumnListBoxView
    /**
     * TestACLBVEnableFindEmptyListL test function for testing the 
     *     EnableFindEmptyList function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestACLBVEnableFindEmptyListL( CStifItemParser& aItem );

    /**
     * TestACLBVSetFindEmptyListStateL test function for testing the 
     *     SetFindEmptyListState function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestACLBVSetFindEmptyListStateL( CStifItemParser& aItem );

    /**
     * TestACLBVDrawEmptyListL test function for testing the 
     *     DrawEmptyList function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestACLBVDrawEmptyListL( CStifItemParser& aItem );

    /**
     * TestACLBVCalcBottomItemIndexL test function for testing the 
     *     CalcBottomItemIndex function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestACLBVCalcBottomItemIndexL( CStifItemParser& aItem );

    // class CAknSetStyleListBoxView
    /**
     * TestSSLBVDrawEmptyListL test function for testing the 
     *     DrawEmptyList function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSSLBVDrawEmptyListL( CStifItemParser& aItem );

    // class CSingleHeadingStyleView
    /**
     * TestSHSVDrawL test function for testing the 
     *     Draw function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSHSVDrawL( CStifItemParser& aItem );

    /**
     * TestSHSVDrawEmptyListL test function for testing the 
     *     DrawEmptyList function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSHSVDrawEmptyListL( CStifItemParser& aItem );

    // class CSingleHeadingStyleItemDrawer
    /**
     * TestSHSIDConstructorL test function for testing the 
     *     Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSHSIDConstructorL( CStifItemParser& aItem );

    /**
     * TestSHSIDDestructorL test function for testing the 
     *     Destructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSHSIDDestructorL( CStifItemParser& aItem );

    /**
     * TestSHSIDDrawItemL test function for testing the 
     *     DrawItem function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSHSIDDrawItemL( CStifItemParser& aItem );

    /**
     * TestSHSIDSetTopItemIndexL test function for testing the 
     *     SetTopItemIndex function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSHSIDSetTopItemIndexL( CStifItemParser& aItem );

    // class CDoubleLargeStyleItemDrawer
    /**
     * TestwIDConstructorL test function for testing the 
     *     Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDLSIDConstructorL( CStifItemParser& aItem );

    /**
     * TestDLSIDDrawItemL test function for testing the 
     *     DrawItem function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestDLSIDDrawItemL( CStifItemParser& aItem );

    // class CWordWrappedFormattedCellItemDrawer
    /**
     * TestWWFCIDConstructorL test function for testing the 
     *     Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestWWFCIDConstructorL( CStifItemParser& aItem );

    /**
     * TestWWFCIDDrawItemL test function for testing the 
     *     DrawItem function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestWWFCIDDrawItemL( CStifItemParser& aItem );

    /**
     * TestWWFCIDDrawItemTextL test function for testing the 
     *     DrawItemText function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestWWFCIDDrawItemTextL( CStifItemParser& aItem );

    // class AknListBoxLayouts
    /**
     * TestLBLSetupStandardListBoxL test function for testing the 
     *     SetupStandardListBox function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBLSetupStandardListBoxL( CStifItemParser& aItem );

    /**
     * TestLBLSetupGridPosL test function for testing the 
     *     SetupGridPos function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBLSetupGridPosL( CStifItemParser& aItem );

    /**
     * TestLBLSetupListboxPosL test function for testing the 
     *     SetupListboxPos function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBLSetupListboxPosL( CStifItemParser& aItem );

    /**
     * TestLBLSetupStandardColumnListboxL test function for testing the 
     *     SetupStandardColumnListbox function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBLSetupStandardColumnListboxL( CStifItemParser& aItem );

    /**
     * TestLBLSetupStandardFormListboxL test function for testing the 
     *     SetupStandardFormListbox function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBLSetupStandardFormListboxL( CStifItemParser& aItem );

    /**
     * TestLBLSetupStandardGridL test function for testing the 
     *     SetupStandardGrid function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBLSetupStandardGridL( CStifItemParser& aItem );

    /**
     * TestLBLSetupColumnGfxCellL test function for testing the 
     *     SetupColumnGfxCell function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBLSetupColumnGfxCellL( CStifItemParser& aItem );

    /**
     * TestLBLSetupColumnTextCellL test function for testing the 
     *     SetupColumnTextCell function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBLSetupColumnTextCellL( CStifItemParser& aItem );

    /**
     * TestLBLSetupColumnTextCellL test function for testing the 
     *     SetupColumnTextCell function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBLSetupColumnTextCellTwoL( CStifItemParser& aItem );

    /**
     * TestLBLSetupFormGfxCellL test function for testing the 
     *     SetupFormGfxCell function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBLSetupFormGfxCellL( CStifItemParser& aItem );

    /**
     * TestLBLSetupGridFormGfxCellL test function for testing the 
     *     SetupGridFormGfxCell function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBLSetupGridFormGfxCellL( CStifItemParser& aItem );

    /**
     * TestLBLSetupGridFormGfxCellTwoL test function for testing the 
     *     SetupGridFormGfxCell function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBLSetupGridFormGfxCellTwoL( CStifItemParser& aItem );

    /**
     * TestLBLSetupFormTextCellL test function for testing the 
     *     SetupFormTextCell function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBLSetupFormTextCellL( CStifItemParser& aItem );

    /**
     * TestLBLSetupFormAntiFlickerTextCellL test function for testing the 
     *     SetupFormAntiFlickerTextCell function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBLSetupFormAntiFlickerTextCellL( CStifItemParser& aItem );

    /**
     * TestLBLSetupFormTextCellTwoL test function for testing the 
     *     SetupFormTextCell function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBLSetupFormTextCellTwoL( CStifItemParser& aItem );

    /**
     * TestLBLSetupFormAntiFlickerTextCellTwoL test function for testing the 
     *     SetupFormAntiFlickerTextCell function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBLSetupFormAntiFlickerTextCellTwoL( CStifItemParser& aItem );

    /**
     * TestLBLSetupColumnGfxCellTwoL test function for testing the 
     *     SetupColumnGfxCell function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBLSetupColumnGfxCellTwoL( CStifItemParser& aItem );

    /**
     * TestLBLSetupFormGfxCellTwoL test function for testing the 
     *     SetupFormGfxCell function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBLSetupFormGfxCellTwoL( CStifItemParser& aItem );

    /**
     * TestLBLSetupListboxPosTwoL test function for testing the 
     *     SetupListboxPos function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBLSetupListboxPosTwoL( CStifItemParser& aItem );

    // class AknListBoxUtils
    /**
     * TestLBUHandleItemRemovalAndPositionHighlightL test function for testing the 
     *     HandleItemRemovalAndPositionHighlightL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBUHandleItemRemovalAndPositionHighlightL( CStifItemParser& aItem );

    /**
     * TestLBUHandleItemRemovalAndPositionHighlightTwoL test function for testing the 
     *     HandleItemRemovalAndPositionHighlightL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBUHandleItemRemovalAndPositionHighlightTwoL( CStifItemParser& aItem );

    /**
     * TestLBUListBoxLinesShownL test function for testing the 
     *     ListBoxLinesShown function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLBUListBoxLinesShownL( CStifItemParser& aItem );

private:    // Data
    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;

    /**
     * own, for test CAknListBoxLayoutDecorator
     */
    CAknListBoxLayoutDecorator* iLBLDecorator;

    /**
     * own, for test CAknMarkableListDialog
     */
    CAknMarkableListDialog* iMLDlg;

    /**
     * Own, for initialize container
     */
    CTestSDKView* iView;

    /**
     * Own
     */
    CTestSDKContainer* iContainer;

    /**
     * own, for test protected of CAknSelectionListDialog
     */
    CTestSDKListsSelectionListDialog* iSelDlg;

    /**
     * own
     */
    CColumnListBoxItemDrawer* iItemDrawer;

    /**
     * Not own, CEikonEnv::Static()
     */
    CEikonEnv* iEikonEnvPointer;

    /**
     * Own, for test CListBoxData
     */
    CListBoxData* iLBData;

    /**
     * Own, for test CTextListItemDrawer
     */
    CTextListItemDrawer* iTLIDrawer;

    /**
     * Own, for test CTextListItemDrawer
     */
    CTextListBoxModel* iTLBModel;

    /**
     * for test TListItemProperties
     */
    TListItemProperties iPropery;

    /**
     * Own, for test CSnakingListBoxView
     */
    CSnakingListBoxView* iSLBView;

    /**
     * Own, for test CEikListBox
     */
    CEikListBox* iListBox;

    /**
     * Resource file offset
     */
    TInt iOffset;
    
    /**
     * Own : CArrayFix<TInt>
     */
    CArrayFix<TInt>* iMarkedItems;
    
    /**
     * Own : CDesCArray
     */
    CDesCArray* iTextArray;
    };

#endif      // C_TESTSDKLISTS_H

// End of File
