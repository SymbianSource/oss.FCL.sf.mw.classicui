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



#ifndef C_TESTSDKQUERIES_H
#define C_TESTSDKQUERIES_H

//  INCLUDES
#include <stiflogger.h>
#include <testscripterinternal.h>
#include <stiftestmodule.h>
#include <testclassassert.h>

// MACROS
#define TEST_CLASS_VERSION_MAJOR 0
#define TEST_CLASS_VERSION_MINOR 0
#define TEST_CLASS_VERSION_BUILD 0

// Logging path
_LIT( KtestsdkqueriesLogPath, "\\logs\\testframework\\testsdkqueries\\" ); 
// Log file
_LIT( KtestsdkqueriesLogFile, "testsdkqueries.txt" ); 
_LIT( KtestsdkqueriesLogFileWithTitle, "testsdkqueries_[%S].txt" );

class CAknDialog;
class CTestSDKQueriesDialg;

class CTestSDKQueriesView;
class CTestSDKQueriesContainer;
/**
*  Ctestsdkqueries test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS(CTestSDKQueries) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestSDKQueries* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestSDKQueries();

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
    CTestSDKQueries( CTestModuleIf& aTestModuleIf );

    /**
    * By default Symbian 2nd phase constructor is private.
    */
    void ConstructL();

    /**
    * Frees all resources allocated from test methods.
    * @since S60 5.0
    */
    void Delete();
    
private://akndialog.h
	
    /**
    * TestDlgCAknDialog test method for test the CAknDialog.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestDlgCAknDialogL( CStifItemParser& aItem );
	
    /**
    * TestDlgConstructL test method for test the ConstructL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestDlgConstructL( CStifItemParser& aItem );
	
    /**
    * TestDlgDelete test method for test the destructor method.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestDlgDelete( CStifItemParser& aItem );
	
    /**
    * TestDlgExecuteLD test method for test the ExecuteLD.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestDlgExecuteLD( CStifItemParser& aItem );
	
    /**
    * TestDlgPrepareLC test method for test the PrepareLC.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestDlgPrepareLC( CStifItemParser& aItem );
	
    /**
    * TestDlgRunLD test method for test the RunLD.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestDlgRunLD( CStifItemParser& aItem );
	
    /**
    * TestDlgSetEmphasis test method for test the SetEmphasis.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestDlgSetEmphasisL( CStifItemParser& aItem );
	
    /**
    * TestDlgDynInitMenuPaneL test method for test the DynInitMenuPaneL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestDlgDynInitMenuPaneL( CStifItemParser& aItem );
	
    /**
    * TestDlgProcessCommandL test method for test the ProcessCommandL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestDlgProcessCommandL( CStifItemParser& aItem );
	
    /**
    * TestDlgOfferKeyEventL test method for test the OfferKeyEventL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestDlgOfferKeyEventL( CStifItemParser& aItem );
	
    /**
    * TestDlgFocusChanged test method for test the FocusChanged.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestDlgFocusChangedL( CStifItemParser& aItem );
	
    /**
    * TestDlgHandlePointerEventL test method for test the HandlePointerEventL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestDlgHandlePointerEventL( CStifItemParser& aItem );
	
    /**
    * TestDlgOkToExitL test method for test the OkToExitL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestDlgOkToExitL( CStifItemParser& aItem );
	
    /**
    * TestDlgDisplayMenuL test method for test the DisplayMenuL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestDlgDisplayMenuL( CStifItemParser& aItem );
	
    /**
    * TestDlgHideMenu test method for test the HideMenu.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestDlgHideMenuL( CStifItemParser& aItem );
	
    /**
    * TestDlgMenuShowing test method for test the MenuShowing.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestDlgMenuShowingL( CStifItemParser& aItem );
	
    /**
    * TestDlgSizeChanged test method for test the SizeChanged.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestDlgSizeChangedL( CStifItemParser& aItem );
	
    /**
    * TestDlgDraw test method for test the Draw.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestDlgDrawL( CStifItemParser& aItem );
	
    /**
    * TestDlgMopSupplyObject test method for test the MopSupplyObject.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestDlgMopSupplyObjectL( CStifItemParser& aItem );
    
private://aknlistquerycontrol.h
    /**
    * TestLqcConstructorL test method for test the Constructor.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestLqcConstructorL( CStifItemParser& aItem );
    
    /**
    * TestLqcConstructFromResourceL test method for test the ConstructFromResourceL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestLqcConstructFromResourceL( CStifItemParser& aItem );

    /**
    * TestLqcDestructorL test method for test the Destructor.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestLqcDestructorL( CStifItemParser& aItem );

    /**
    * TestDlgMopSupplyObject test method for test the MopSupplyObject.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestLqcMinimumSizeL( CStifItemParser& aItem );

    /**
    * TestDlgMopSupplyObject test method for test the MopSupplyObject.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestLqcCountComponentControlsL( CStifItemParser& aItem );

    /**
    * TestDlgMopSupplyObject test method for test the MopSupplyObject.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestLqcComponentControlL( CStifItemParser& aItem );

    /**
    * TestDlgMopSupplyObject test method for test the MopSupplyObject.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestLqcOfferKeyEventL( CStifItemParser& aItem );

    /**
    * TestLqcDrawL test method for test the Draw.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestLqcDrawL( CStifItemParser& aItem );

    /**
    * TestDlgMopSupplyObject test method for test the MopSupplyObject.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestLqcSetLayoutL( CStifItemParser& aItem );

    /**
    * TestDlgMopSupplyObject test method for test the MopSupplyObject.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestLqcFocusChangedL( CStifItemParser& aItem );

    /**
    * TestDlgMopSupplyObject test method for test the MopSupplyObject.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestLqcListboxL( CStifItemParser& aItem );

    /**
    * TestDlgMopSupplyObject test method for test the MopSupplyObject.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestLqcHeadingL( CStifItemParser& aItem );

    /**
    * TestLqcListtypeL test method for test the Listtype.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestLqcListtypeL( CStifItemParser& aItem );

    /**
    * TestLqcHandlePointerEventL test method for test the HandlePointerEventL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestLqcHandlePointerEventL( CStifItemParser& aItem );

    /**
    * TestLqclistboxL test method for test the listbox.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestLqclistboxL( CStifItemParser& aItem );
    
/*
 * aknlistquerydialog.h
 **/
        //CAknListQueryDialog
    /**
    * TestLqdlgConstructorL test method for test the Constructor.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestLqdlgConstructorL( CStifItemParser& aItem );
    
    /**
    * TestLqdlgConstructorLL test method for test the Constructor.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestLqdlgConstructorLL( CStifItemParser& aItem );

    /**
    * TestLqdlgDestructorL test method for test the Destructor.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestLqdlgDestructorL( CStifItemParser& aItem );

    /**
    * TestLqdlgSetSizeAndPositionL test method for test the SetSizeAndPosition.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestLqdlgSetSizeAndPositionL( CStifItemParser& aItem );

    /**
    * TestLqdlgOfferKeyEventL test method for test the OfferKeyEvent.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestLqdlgOfferKeyEventL( CStifItemParser& aItem );

    /**
    * TestLqclistboxL test method for test the listbox.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestLqdlgHandleListBoxEventL( CStifItemParser& aItem );

    /**
    * TestLqclistboxL test method for test the listbox.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestLqdlgSetItemTextArrayL( CStifItemParser& aItem );

    /**
    * TestLqclistboxL test method for test the listbox.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestLqdlgSetOwnershipTypeL( CStifItemParser& aItem );

    /**
    * TestLqclistboxL test method for test the listbox.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestLqdlgSetIconArrayL( CStifItemParser& aItem );

    /**
    * TestLqdlgListBoxL test method for test the ListBox.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestLqdlgListBoxL( CStifItemParser& aItem );

    /**
    * TestLqdlgListControlL test method for test the ListControl.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestLqdlgListControlL( CStifItemParser& aItem );

    /**
    * TestLqdlgMessageBoxL test method for test the MessageBox.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestLqdlgMessageBoxL( CStifItemParser& aItem );

    /**
    * TestLqdlgQueryHeadingL test method for test the QueryHeading.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestLqdlgQueryHeadingL( CStifItemParser& aItem );

    /**
    * TestLqdlgActivateL test method for test the Activate.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestLqdlgActivateL( CStifItemParser& aItem );

    /**
    * TestLqdlgHandlePointerEventL test method for test the HandlePointerEvent.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestLqdlgHandlePointerEventL( CStifItemParser& aItem );
    
    //protected function
    /**
    * TestLqdlgPreLayoutDynInitL test method for test the PreLayoutDynInit.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestLqdlgPreLayoutDynInitL( CStifItemParser& aItem );

    /**
    * TestLqdlgPostLayoutDynInitL test method for test the PostLayoutDynInit.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestLqdlgPostLayoutDynInitL( CStifItemParser& aItem );

    /**
    * TestLqdlgOkToExitL test method for test the OkToExit.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestLqdlgOkToExitL( CStifItemParser& aItem );

    /**
    * TestLqdlgBorderStyleL test method for test the BorderStyle.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestLqdlgBorderStyleL( CStifItemParser& aItem );

    /**
    * TestLqdlgCloseStateL test method for test the CloseState.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestLqdlgCloseStateL( CStifItemParser& aItem );

    /**
    * TestLqdlgFindBoxL test method for test the FindBox.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestLqdlgFindBoxL( CStifItemParser& aItem );

    /**
    * TestLqdlgSetToneL test method for test the SetTone.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestLqdlgSetToneL( CStifItemParser& aItem );

    /**
    * TestLqdlgHandleResourceChangeL test method for test the HandleResourceChange.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestLqdlgHandleResourceChangeL( CStifItemParser& aItem );

    /**
    * TestLqdlgPublishDialogL test method for test the PublishDialog.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestLqdlgPublishDialogL( CStifItemParser& aItem );

    /**
    * TestLqdlgSetMediatorObserverL test method for test the SetMediatorObserver.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestLqdlgSetMediatorObserverL( CStifItemParser& aItem );
    
private://aknmessagequerycontrol.h
        //CAknMessageQueryControl
    /**
    * TestLqdlgSetMediatorObserverL test method for test the SetMediatorObserver.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestMqcConstructFromResourceL( CStifItemParser& aItem );

    /**
    * TestLqdlgSetMediatorObserverL test method for test the SetMediatorObserver.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestMqcSetMessageTextL( CStifItemParser& aItem );

    /**
    * TestLqdlgSetMediatorObserverL test method for test the SetMediatorObserver.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestMqcLinkHighLightedL( CStifItemParser& aItem );

    /**
    * TestLqdlgSetMediatorObserverL test method for test the SetMediatorObserver.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestMqcDrawL( CStifItemParser& aItem );
    
private://aknmessagequerydialog.h
        //CAknMessageQueryDialog
    /**
    * TestMqdlgNewL test method for test the NewL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestMqdlgNewL( CStifItemParser& aItem );

    /**
    * TestLqdlgSetMediatorObserverL test method for test the SetMediatorObserver.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestMqdlgDestructorL( CStifItemParser& aItem );

    /**
    * TestLqdlgSetMediatorObserverL test method for test the SetMediatorObserver.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestMqdlgConstructorOneL( CStifItemParser& aItem );

    /**
    * TestLqdlgSetMediatorObserverL test method for test the SetMediatorObserver.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestMqdlgSetMessageTextOneL( CStifItemParser& aItem );

    /**
    * TestLqdlgSetMediatorObserverL test method for test the SetMediatorObserver.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestMqdlgSetHeaderTextOneL( CStifItemParser& aItem );

    /**
    * TestMqdlgSetLinkTextL test method for test the SetLinkText.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestMqdlgSetLinkTextL( CStifItemParser& aItem );

    /**
    * TestMqdlgSetLinkL test method for test the SetLink.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestMqdlgSetLinkL( CStifItemParser& aItem );

    /**
    * TestMqdlgOfferKeyEventL test method for test the OfferKeyEvent.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestMqdlgOfferKeyEventL( CStifItemParser& aItem );

    /**
    * TestMqdlgHandlePointerEventL test method for test the HandlePointerEvent.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestMqdlgHandlePointerEventL( CStifItemParser& aItem );

    /**
    * TestMqdlgPreLayoutDynInitL test method for test the PreLayoutDynInit.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestMqdlgPreLayoutDynInitL( CStifItemParser& aItem );

    /**
    * TestMqdlgSetSizeAndPositionL test method for test the SetSizeAndPosition.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestMqdlgSetSizeAndPositionL( CStifItemParser& aItem );

    /**
    * TestMqdlgPostLayoutDynInitL test method for test the PostLayoutDynInit.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestMqdlgPostLayoutDynInitL( CStifItemParser& aItem );

    /**
    * TestMqdlgProcessCommandL test method for test the ProcessCommand.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestMqdlgProcessCommandL( CStifItemParser& aItem );

    /**
    * TestMqdlgConstructorTwoL test method for test the Constructor.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestMqdlgConstructorTwoL( CStifItemParser& aItem );

    /**
    * TestMqdlgConstructorThreeL test method for test the Constructor.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestMqdlgConstructorThreeL( CStifItemParser& aItem );

    /**
    * TestMqdlgConstructorFourL test method for test the Constructor.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestMqdlgConstructorFourL( CStifItemParser& aItem );

    /**
    * TestMqdlgConstructorFiveL test method for test the Constructor.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestMqdlgConstructorFiveL( CStifItemParser& aItem );

    /**
    * TestMqdlgSetMessageTextTwoL test method for test the SetMessageText.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestMqdlgSetMessageTextTwoL( CStifItemParser& aItem );

    /**
    * TestMqdlgSetMessageTextThreeL test method for test the SetMessageText.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestMqdlgSetMessageTextThreeL( CStifItemParser& aItem );

    /**
    * TestMqdlgSetHeaderTextTwoL test method for test the SetHeaderText.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestMqdlgSetHeaderTextTwoL( CStifItemParser& aItem );

    /**
    * TestMqdlgSetHeaderTextThreeL test method for test the SetHeaderText.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestMqdlgSetHeaderTextThreeL( CStifItemParser& aItem );

    /**
    * TestMqdlgConstructorSixL test method for test the Constructor.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestMqdlgConstructorSixL( CStifItemParser& aItem );
    
private://AknMultilineQueryControl.h
        //CAknMultilineQueryControl
    /**
    * TestMlqcConstructorL test method for test the Constructor.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestMlqcConstructorL( CStifItemParser& aItem );

    /**
    * TestMlqcDestructorL test method for test the Destructor.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestMlqcDestructorL( CStifItemParser& aItem );

    /**
    * TestMlqcSetNbrOfPromptLinesL test method for test the SetNbrOfPromptLines.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestMlqcSetNbrOfPromptLinesL( CStifItemParser& aItem );

    /**
    * TestMlqcIsFirstL test method for test the IsFirst.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestMlqcIsFirstL( CStifItemParser& aItem );

    /**
    * TestMlqcIsSecondL test method for test the IsSecond.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestMlqcIsSecondL( CStifItemParser& aItem );

    /**
    * TestMlqcControlByLayoutOrNullL test method for test the ControlByLayoutOrNull.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestMlqcControlByLayoutOrNullL( CStifItemParser& aItem );

    /**
    * TestMlqcMinimumSizeL test method for test the MinimumSize.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestMlqcMinimumSizeL( CStifItemParser& aItem );

    /**
    * TestMlqcHandlePointerEventL test method for test the HandlePointerEvent.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestMlqcHandlePointerEventL( CStifItemParser& aItem );

    /**
    * TestMlqcHandleResourceChangeL test method for test the HandleResourceChange.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestMlqcHandleResourceChangeL( CStifItemParser& aItem );

    //CAknExtMultilineQueryControl
    /**
    * TestExtMlqcConstructorL test method for test the Constructor.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestExtMlqcConstructorL( CStifItemParser& aItem );

    /**
    * TestExtMlqcDestructorL test method for test the Destructor.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestExtMlqcDestructorL( CStifItemParser& aItem );

    /**
    * TestExtMlqcSetNbrOfPromptLinesL test method for test the SetNbrOfPromptLines.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestExtMlqcSetNbrOfPromptLinesL( CStifItemParser& aItem );

    /**
    * TestExtMlqcIsFirstL test method for test the IsFirst.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestExtMlqcIsFirstL( CStifItemParser& aItem );

    /**
    * TestExtMlqcIsSecondL test method for test the IsSecond.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestExtMlqcIsSecondL( CStifItemParser& aItem );

    /**
    * TestExtMlqcControlByLayoutOrNullL test method for test the ControlByLayoutOrNull.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestExtMlqcControlByLayoutOrNullL( CStifItemParser& aItem );

    /**
    * TestExtMlqcMinimumSizeL test method for test the MinimumSize.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestExtMlqcMinimumSizeL( CStifItemParser& aItem );

    /**
    * TestExtMlqcHandlePointerEventL test method for test the HandlePointerEvent.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestExtMlqcHandlePointerEventL( CStifItemParser& aItem );

    /**
    * TestExtMlqcHandleResourceChangeL test method for test the HandleResourceChange.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestExtMlqcHandleResourceChangeL( CStifItemParser& aItem );
    
private://AknQueryControl.h
        //CAknQueryControl
    /**
    * TestQcConstructorL test method for test the Constructor.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQcConstructorL( CStifItemParser& aItem );

    /**
    * TestQcDestructorL test method for test the Destructor.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQcDestructorL( CStifItemParser& aItem );

    /**
    * TestExtMlqcHandleResourceChangeL test method for test the HandleResourceChange.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQcConstructFromResourceL( CStifItemParser& aItem );

    /**
    * TestExtMlqcHandleResourceChangeL test method for test the HandleResourceChange.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQcSetQueryControlObserverL( CStifItemParser& aItem );

    /**
    * TestExtMlqcHandleResourceChangeL test method for test the HandleResourceChange.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQcReadPromptL( CStifItemParser& aItem );

    /**
    * TestExtMlqcHandleResourceChangeL test method for test the HandleResourceChange.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQcSetPromptL( CStifItemParser& aItem );

    /**
    * TestQcGetTextL test method for test the GetTextL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQcGetTextL( CStifItemParser& aItem );

    /**
    * TestQcGetTimeL test method for test the GetTime.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQcGetTimeL( CStifItemParser& aItem );

    /**
    * TestQcGetNumberL test method for test the GetNumber.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQcGetNumberL( CStifItemParser& aItem );

    /**
    * TestQcGetFloatingPointNumberL test method for test the GetFloatingPointNumber.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQcGetFloatingPointNumberL( CStifItemParser& aItem );

    /**
    * TestQcGetDurationL test method for test the GetDuration.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQcGetDurationL( CStifItemParser& aItem );

    /**
    * TestQcGetLocationL test method for test the GetLocation.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQcGetLocationL( CStifItemParser& aItem );

    /**
    * TestQcSetTextL test method for test the SetText.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQcSetTextL( CStifItemParser& aItem );

    /**
    * TestQcSetTimeL test method for test the SetTime.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQcSetTimeL( CStifItemParser& aItem );

    /**
    * TestQcSetDurationL test method for test the SetDuration.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQcSetDurationL( CStifItemParser& aItem );

    /**
    * TestQcSetNumberL test method for test the SetNumber.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQcSetNumberL( CStifItemParser& aItem );

    /**
    * TestQcSetFloatingPointNumberL test method for test the SetFloatingPointNumber.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQcSetFloatingPointNumberL( CStifItemParser& aItem );

    /**
    * TestQcSetLocationL test method for test the SetLocation.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQcSetLocationL( CStifItemParser& aItem );

    /**
    * TestQcSetTextEntryLengthL test method for test the SetTextEntryLength.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQcSetTextEntryLengthL( CStifItemParser& aItem );

    /**
    * TestQcGetTextEntryLengthL test method for test the GetTextEntryLength.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQcGetTextEntryLengthL( CStifItemParser& aItem );

    /**
    * TestQcSetMinimumAndMaximumOneL test method for test the SetMinimumAndMaximum.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQcSetMinimumAndMaximumOneL( CStifItemParser& aItem );

    /**
    * TestQcSetMinimumAndMaximumTwoL test method for test the SetMinimumAndMaximum.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQcSetMinimumAndMaximumTwoL( CStifItemParser& aItem );

    /**
    * TestQcSetMinimumAndMaximumThreeL test method for test the SetMinimumAndMaximum.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQcSetMinimumAndMaximumThreeL( CStifItemParser& aItem );

    /**
    * TestQcCheckNumberL test method for test the CheckNumber.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQcCheckNumberL( CStifItemParser& aItem );

    /**
    * TestQcSetNumberOfEditorLinesL test method for test the SetNumberOfEditorLines.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQcSetNumberOfEditorLinesL( CStifItemParser& aItem );

    /**
    * TestQcSetMinimumAndMaximumL test method for test the SetMinimumAndMaximum.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQcSetMinimumAndMaximumL( CStifItemParser& aItem );

    /**
    * TestQcGetTextLengthL test method for test the GetTextLength.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQcGetTextLengthL( CStifItemParser& aItem );

    /**
    * TestQcNbrOfEditorLinesL test method for test the NbrOfEditorLines.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQcNbrOfEditorLinesL( CStifItemParser& aItem );

    /**
    * TestQcNbrOfPromptLinesL test method for test the NbrOfPromptLines.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQcNbrOfPromptLinesL( CStifItemParser& aItem );

    /**
    * TestQcControlByLayoutOrNullL test method for test the ControlByLayoutOrNull.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQcControlByLayoutOrNullL( CStifItemParser& aItem );

    /**
    * TestQcSetImageL test method for test the SetImageL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQcSetImageL( CStifItemParser& aItem );

    /**
    * TestQcSetImageFullL test method for test the SetImagel.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQcSetImageFullL( CStifItemParser& aItem );

    /**
    * TestQcSetAnimationL test method for test the SetAnimation.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQcSetAnimationL( CStifItemParser& aItem );

    /**
    * TestQcStartAnimationL test method for test the StartAnimation.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQcStartAnimationL( CStifItemParser& aItem );

    /**
    * TestQcCancelAnimationL test method for test the CancelAnimation.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQcCancelAnimationL( CStifItemParser& aItem );

    /**
    * TestQcOfferKeyEventL test method for test the OfferKeyEvent.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQcOfferKeyEventL( CStifItemParser& aItem );

    /**
    * TestQcMinimumSizeL test method for test the MinimumSize.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQcMinimumSizeL( CStifItemParser& aItem );

    /**
    * TestQcHandleEdwinEventL test method for test the HandleEdwinEvent.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQcHandleEdwinEventL( CStifItemParser& aItem );

    /**
    * TestQcHandleEdwinSizeEventL test method for test the HandleEdwinSizeEvent.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQcHandleEdwinSizeEventL( CStifItemParser& aItem );

    /**
    * TestQcHandleControlEventL test method for test the HandleControlEvent.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQcHandleControlEventL( CStifItemParser& aItem );

    /**
    * TestQcQueryTypeL test method for test the QueryType.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQcQueryTypeL( CStifItemParser& aItem );

    /**
    * TestQcHandlePointerEventL test method for test the HandlePointerEventL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQcHandlePointerEventL( CStifItemParser& aItem );

    /**
    * TestQcHandleResourceChangeL test method for test the HandleResourceChange.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQcHandleResourceChangeL( CStifItemParser& aItem );

        //CAknExtQueryControl
    /**
    * TestQcHandleResourceChangeL test method for test the Constructor.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestExtQcConstructorL( CStifItemParser& aItem );

    /**
    * TestQcHandleResourceChangeL test method for test the Destructor.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestExtQcDestructorL( CStifItemParser& aItem );

    /**
    * TestExtQcGetInetAddressL test method for test the GetInetAddress.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestExtQcGetInetAddressL( CStifItemParser& aItem );

    /**
    * TestExtQcSetInetAddressL test method for test the SetInetAddress.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestExtQcSetInetAddressL( CStifItemParser& aItem );

    /**
    * TestExtQcGetFixedPointNumberL test method for test the GetFixedPointNumber.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestExtQcGetFixedPointNumberL( CStifItemParser& aItem );

    /**
    * TestExtQcSetFixedPointNumberL test method for test the SetFixedPointNumberL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestExtQcSetFixedPointNumberL( CStifItemParser& aItem );

    /**
    * TestExtQcSetMinimumAndMaximumL test method for test the SetMinimumAndMaximum.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestExtQcSetMinimumAndMaximumL( CStifItemParser& aItem );

    /**
    * TestExtQcSetMinimumAndMaximumLL test method for test the SetMinimumAndMaximum.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestExtQcSetMinimumAndMaximumLL( CStifItemParser& aItem );

    /**
    * TestExtQcControlByLayoutOrNullL test method for test the ControlByLayoutOrNull.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestExtQcControlByLayoutOrNullL( CStifItemParser& aItem );

    /**
    * TestExtQcHandleControlEventL test method for test the HandleControlEventL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestExtQcHandleControlEventL( CStifItemParser& aItem );

    /**
    * TestExtQcHandlePointerEventL test method for test the HandlePointerEventL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestExtQcHandlePointerEventL( CStifItemParser& aItem );
    
//aknquerydata.h
    /**
    * TestQdGetMaxTextLengthL test method for test the GetMaxTextLength.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQdataGetMaxTextLengthL( CStifItemParser& aItem );
    
//aknquerydialog.h
        //CAknQueryDialog
    /**
    * TestQdlgNewLOneL test method for test the HandlePointerEventL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQdlgNewLOneL( CStifItemParser& aItem );

    /**
    * TestQdlgNewLTwoL test method for test the HandlePointerEventL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQdlgNewLTwoL( CStifItemParser& aItem );

    /**
    * TestQdlgNewLThreeL test method for test the HandlePointerEventL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQdlgNewLThreeL( CStifItemParser& aItem );

    /**
    * TestQdlgNewLFourL test method for test the HandlePointerEventL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQdlgNewLFourL( CStifItemParser& aItem );

    /**
    * TestQdlgNewLFiveL test method for test the HandlePointerEventL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQdlgNewLFiveL( CStifItemParser& aItem );

    /**
    * TestQdlgNewLSixL test method for test the HandlePointerEventL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQdlgNewLSixL( CStifItemParser& aItem );

    /**
    * TestQdlgNewLSevenL test method for test the HandlePointerEventL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQdlgNewLSevenL( CStifItemParser& aItem );

    /**
    * TestQdlgNewLEightL test method for test the HandlePointerEventL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQdlgNewLEightL( CStifItemParser& aItem );

    /**
    * TestQdlgDestructorL test method for test the HandlePointerEventL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQdlgDestructorL( CStifItemParser& aItem );

    /**
    * TestQdlgConstructorOneL test method for test the HandlePointerEventL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQdlgConstructorOneL( CStifItemParser& aItem );

    /**
    * TestQdlgQueryHeadingL test method for test the HandlePointerEventL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQdlgQueryHeadingL( CStifItemParser& aItem );

    /**
    * TestQdlgHeadingL test method for test the HandlePointerEventL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQdlgHeadingL( CStifItemParser& aItem );

    /**
    * TestQdlgSetPromptL test method for test the HandlePointerEventL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQdlgSetPromptL( CStifItemParser& aItem );

    /**
    * TestQdlgMakeLeftSoftkeyVisibleL test method for test the HandlePointerEventL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQdlgMakeLeftSoftkeyVisibleL( CStifItemParser& aItem );

    /**
    * TestQdlgSetEmergencyCallSupportL test method for test the HandlePointerEventL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQdlgSetEmergencyCallSupportL( CStifItemParser& aItem );

    /**
    * TestQdlgRemoveEditorIndicatorL test method for test the HandlePointerEventL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQdlgRemoveEditorIndicatorL( CStifItemParser& aItem );

    /**
    * TestQdlgSetPredictiveTextInputPermittedL test method for test the HandlePointerEventL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQdlgSetPredictiveTextInputPermittedL( CStifItemParser& aItem );

    /**
    * TestQdlgRunLDL test method for test the HandlePointerEventL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQdlgRunLDL( CStifItemParser& aItem );

    /**
    * TestQdlgExecuteLDOneL test method for test the HandlePointerEventL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQdlgExecuteLDOneL( CStifItemParser& aItem );

    /**
    * TestQdlgExecuteLDTwoL test method for test the HandlePointerEventL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQdlgExecuteLDTwoL( CStifItemParser& aItem );

    /**
    * TestQdlgOfferKeyEventL test method for test the HandlePointerEventL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQdlgOfferKeyEventL( CStifItemParser& aItem );

    /**
    * TestQdlgHandlePointerEventL test method for test the HandlePointerEventL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQdlgHandlePointerEventL( CStifItemParser& aItem );

    /**
    * TestQdlgMaxTextLengthOneL test method for test the HandlePointerEventL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQdlgMaxTextLengthOneL( CStifItemParser& aItem );

    /**
    * TestQdlgSetSizeAndPositionL test method for test the HandlePointerEventL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQdlgSetSizeAndPositionL( CStifItemParser& aItem );

    /**
    * TestQdlgPreLayoutDynInitL test method for test the HandlePointerEventL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQdlgPreLayoutDynInitL( CStifItemParser& aItem );

    /**
    * TestQdlgPostLayoutDynInitL test method for test the HandlePointerEventL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQdlgPostLayoutDynInitL( CStifItemParser& aItem );

    /**
    * TestQdlgOkToExitL test method for test the HandlePointerEventL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQdlgOkToExitL( CStifItemParser& aItem );

    /**
    * TestQdlgHandleQueryEditorSizeEventL test method for test the HandlePointerEventL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQdlgHandleQueryEditorSizeEventL( CStifItemParser& aItem );

    /**
    * TestQdlgHandleQueryEditorStateEventL test method for test the HandlePointerEventL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQdlgHandleQueryEditorStateEventL( CStifItemParser& aItem );

    /**
    * TestQdlgNeedToDismissQueryL test method for test the HandlePointerEventL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQdlgNeedToDismissQueryL( CStifItemParser& aItem );

    /**
    * TestQdlgDismissQueryL test method for test the HandlePointerEventL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQdlgDismissQueryL( CStifItemParser& aItem );

    /**
    * TestQdlgUpdateLeftSoftKeyL test method for test the HandlePointerEventL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQdlgUpdateLeftSoftKeyL( CStifItemParser& aItem );

    /**
    * TestQdlgDoSetPromptL test method for test the HandlePointerEventL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQdlgDoSetPromptL( CStifItemParser& aItem );

    /**
    * TestQdlgQueryControlL test method for test the HandlePointerEventL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQdlgQueryControlL( CStifItemParser& aItem );

    /**
    * TestQdlgPromptL test method for test the Prompt.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQdlgPromptL( CStifItemParser& aItem );

    /**
    * TestQdlgConstructorTwoL test method for test the Constructor.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQdlgConstructorTwoL( CStifItemParser& aItem );

    /**
    * TestQdlgConstructorThreeL test method for test the Constructor.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQdlgConstructorThreeL( CStifItemParser& aItem );

    /**
    * TestQdlgSetHeaderTextL test method for test the SetHeaderText.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQdlgSetHeaderTextL( CStifItemParser& aItem );

    /**
    * TestQdlgSetHeaderImageL test method for test the SetHeaderImage.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQdlgSetHeaderImageL( CStifItemParser& aItem );

    /**
    * TestQdlgRunDlgLDL test method for test the RunDlgLD.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQdlgRunDlgLDL( CStifItemParser& aItem );

    /**
    * TestQdlgMaxTextLengthL test method for test the MaxTextLength.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQdlgMaxTextLengthTwoL( CStifItemParser& aItem );

    /**
    * TestQdlgInputCapabilitiesL test method for test the InputCapabilities.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQdlgInputCapabilitiesL( CStifItemParser& aItem );

    /**
    * TestQdlgSetEmergencyCallSupportForCBAL test method for test the SetEmergencyCallSupportForCBA.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQdlgSetEmergencyCallSupportForCBAL( CStifItemParser& aItem );
        
        //CAknTextQueryDialog
    /**
    * TestTextQdlgNewL test method for test the NewL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestTextQdlgNewL( CStifItemParser& aItem );

    /**
    * TestTextQdlgConstructorL test method for test the Constructor.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestTextQdlgConstructorL( CStifItemParser& aItem );

    /**
    * TestTextQdlgDestructorL test method for test the Destructor.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestTextQdlgDestructorL( CStifItemParser& aItem );

    /**
    * TestTextQdlgSetMaxLengthL test method for test the SetMaxLength.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestTextQdlgSetMaxLengthL( CStifItemParser& aItem );

    /**
    * TestTextQdlgCheckIfEntryTextOkL test method for test the CheckIfEntryTextOk.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestTextQdlgCheckIfEntryTextOkL( CStifItemParser& aItem );

    /**
    * TestTextQdlgSetDefaultInputModeL test method for test the SetDefaultInputMode.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestTextQdlgSetDefaultInputModeL( CStifItemParser& aItem );

    /**
    * TestTextQdlgPreLayoutDynInitL test method for test the PreLayoutDynInitL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestTextQdlgPreLayoutDynInitL( CStifItemParser& aItem );

    /**
    * TestTextQdlgOkToExitL test method for test the OkToExitL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestTextQdlgOkToExitL( CStifItemParser& aItem );

    /**
    * TestTextQdlgHandleQueryEditorSizeEventL test method for test the HandleQueryEditorSizeEventL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestTextQdlgHandleQueryEditorSizeEventL( CStifItemParser& aItem );

    /**
    * TestTextQdlgHandlePointerEventL test method for test the HandlePointerEventL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestTextQdlgHandlePointerEventL( CStifItemParser& aItem );

    /**
    * TestTextQdlgConstructorLL test method for test the Constructor.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestTextQdlgConstructorLL( CStifItemParser& aItem );
    
//CAknNumberQueryDialog
    /**
    * TestNumberQdlgNewL test method for test the NewL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestNumberQdlgNewL( CStifItemParser& aItem );

    /**
    * TestNumberQdlgConstructorL test method for test the Constructor.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestNumberQdlgConstructorL( CStifItemParser& aItem );

    /**
    * TestNumberQdlgDestructorL test method for test the Destructor.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestNumberQdlgDestructorL( CStifItemParser& aItem );

    /**
    * TestNumberQdlgSetMinimumAndMaximumL test method for test the SetMinimumAndMaximum.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestNumberQdlgSetMinimumAndMaximumL( CStifItemParser& aItem );

    /**
    * TestNumberQdlgHandlePointerEventL test method for test the HandlePointerEvent.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestNumberQdlgHandlePointerEventL( CStifItemParser& aItem );

    /**
    * TestNumberQdlgPreLayoutDynInitL test method for test the PreLayoutDynInit.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestNumberQdlgPreLayoutDynInitL( CStifItemParser& aItem );

    /**
    * TestNumberQdlgOkToExitL test method for test the OkToExit.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestNumberQdlgOkToExitL( CStifItemParser& aItem );

    /**
    * TestNumberQdlgNumberL test method for test the Number.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestNumberQdlgNumberOneL( CStifItemParser& aItem );

    /**
    * TestNumberQdlgNumberL test method for test the Number.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestNumberQdlgNumberTwoL( CStifItemParser& aItem );
    
//CAknTimeQueryDialog
    /**
    * TestTimeQdlgNewL test method for test the NewL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestTimeQdlgNewL( CStifItemParser& aItem );

    /**
    * TestTimeQdlgConstructorL test method for test the Constructor.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestTimeQdlgConstructorL( CStifItemParser& aItem );

    /**
    * TestTimeQdlgDestructorL test method for test the Destructor.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestTimeQdlgDestructorL( CStifItemParser& aItem );

    /**
    * TestTimeQdlgSetMinimumAndMaximumL test method for test the SetMinimumAndMaximumL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestTimeQdlgSetMinimumAndMaximumL( CStifItemParser& aItem );

    /**
    * TestTimeQdlgHandlePointerEventL test method for test the HandlePointerEventL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestTimeQdlgHandlePointerEventL( CStifItemParser& aItem );

    /**
    * TestTimeQdlgPreLayoutDynInitL test method for test the PreLayoutDynInitL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestTimeQdlgPreLayoutDynInitL( CStifItemParser& aItem );

    /**
    * TestTimeQdlgOkToExitL test method for test the OkToExitL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestTimeQdlgOkToExitL( CStifItemParser& aItem );

    /**
    * TestTimeQdlgTimeOneL test method for test the Time.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestTimeQdlgTimeOneL( CStifItemParser& aItem );

    /**
    * TestTimeQdlgTimeTwoL test method for test the Time.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestTimeQdlgTimeTwoL( CStifItemParser& aItem );

    /**
    * TestTimeQdlgConstructorLL test method for test the Constructor.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestTimeQdlgConstructorLL( CStifItemParser& aItem );
    
//CAknDurationQueryDialog
    /**
    * TestDurationNewL test method for test the NewL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestDurationNewL( CStifItemParser& aItem );
    
    /**
    * TestDurationConstructorL test method for test the Constructor.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestDurationConstructorL( CStifItemParser& aItem );
    
    /**
    * TestDurationDestructorL test method for test the Destructor.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestDurationDestructorL( CStifItemParser& aItem );
    
    /**
    * TestDurationSetMinimumAndMaximumL test method for test the SetMinimumAndMaximum.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestDurationSetMinimumAndMaximumL( CStifItemParser& aItem );
    
    /**
    * TestDurationHandlePointerEventL test method for test the HandlePointerEventL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestDurationHandlePointerEventL( CStifItemParser& aItem );
    
    /**
    * TestDurationPreLayoutDynInitL test method for test the PreLayoutDynInit.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestDurationPreLayoutDynInitL( CStifItemParser& aItem );
    
    /**
    * TestDurationOkToExitL test method for test the OkToExit.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestDurationOkToExitL( CStifItemParser& aItem );
    
    /**
    * TestDurationDurationOneL test method for test the Duration.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestDurationDurationOneL( CStifItemParser& aItem );
    
    /**
    * TestDurationDurationTwoL test method for test the Duration.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestDurationDurationTwoL( CStifItemParser& aItem );
    
//CAknFloatingPointQueryDialog
    /**
    * TestFloatingQdlgNewL test method for test the NewL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestFloatingQdlgNewL( CStifItemParser& aItem );
    
    /**
    * TestFloatingQdlgConstructorL test method for test the Constructor.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestFloatingQdlgConstructorL( CStifItemParser& aItem );
    
    /**
    * TestFloatingQdlgDestructorL test method for test the Destructor.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestFloatingQdlgDestructorL( CStifItemParser& aItem );
    
    /**
    * TestFloatingQdlgSetMinimumAndMaximumL test method for test the SetMinimumAndMaximumL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestFloatingQdlgSetMinimumAndMaximumL( CStifItemParser& aItem );
    
    /**
    * TestFloatingQdlgHandlePointerEventL test method for test the HandlePointerEventL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestFloatingQdlgHandlePointerEventL( CStifItemParser& aItem );
    
    /**
    * TestFloatingQdlgPreLayoutDynInitL test method for test the PreLayoutDynInitL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestFloatingQdlgPreLayoutDynInitL( CStifItemParser& aItem );
    
    /**
    * TestFloatingQdlgOkToExitL test method for test the OkToExitL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestFloatingQdlgOkToExitL( CStifItemParser& aItem );
    
    /**
    * TestFloatingQdlgNumberOneL test method for test the Number.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestFloatingQdlgNumberOneL( CStifItemParser& aItem );
    
    /**
    * TestFloatingQdlgNumberTwoL test method for test the Number.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestFloatingQdlgNumberTwoL( CStifItemParser& aItem );
    
//CAknMultiLineDataQueryDialog
    /**
    * TestMultiLineDataQdlgNewLOneL test method for test the NewL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestMultiLineDataQdlgNewLOneL( CStifItemParser& aItem );
    
    /**
    * TestMultiLineDataQdlgNewLTwoL test method for test the NewL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestMultiLineDataQdlgNewLTwoL( CStifItemParser& aItem );
    
    /**
    * TestMultiLineDataQdlgNewLThreeL test method for test the NewL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestMultiLineDataQdlgNewLThreeL( CStifItemParser& aItem );
    
    /**
    * TestMultiLineDataQdlgNewLFourL test method for test the NewL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestMultiLineDataQdlgNewLFourL( CStifItemParser& aItem );
    
    /**
    * TestMultiLineDataQdlgNewLFiveL test method for test the NewL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestMultiLineDataQdlgNewLFiveL( CStifItemParser& aItem );
    
    /**
    * TestMultiLineDataQdlgNewLSixL test method for test the NewL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestMultiLineDataQdlgNewLSixL( CStifItemParser& aItem );
    
    /**
    * TestMultiLineDataQdlgNewLSevenL test method for test the NewL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestMultiLineDataQdlgNewLSevenL( CStifItemParser& aItem );
    
    /**
    * TestMultiLineDataQdlgNewLEightL test method for test the NewL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestMultiLineDataQdlgNewLEightL( CStifItemParser& aItem );
    
    /**
    * TestMultiLineDataQdlgDestructorL test method for test the Destructor.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestMultiLineDataQdlgDestructorL( CStifItemParser& aItem );
    
    /**
    * TestMultiLineDataQdlgConstructorOneL test method for test the Constructor.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestMultiLineDataQdlgConstructorOneL( CStifItemParser& aItem );
    
    /**
    * TestFloatingQdlgNumberTwoL test method for test the Number.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestMultiLineDataQdlgSetPromptL( CStifItemParser& aItem );
    
    /**
    * TestFloatingQdlgNumberTwoL test method for test the Number.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestMultiLineDataQdlgSetMaxLengthOfFirstEditorL( CStifItemParser& aItem );
    
    /**
    * TestFloatingQdlgNumberTwoL test method for test the Number.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestMultiLineDataQdlgSetMaxLengthOfSecondEditorL( CStifItemParser& aItem );
    
    /**
    * TestFloatingQdlgNumberTwoL test method for test the Number.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestMultiLineDataQdlgHandlePointerEventL( CStifItemParser& aItem );
    
    /**
    * TestMultiLineDataQdlgOkToExitL test method for test the OkToExitL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestMultiLineDataQdlgOkToExitL( CStifItemParser& aItem );
    
    /**
    * TestMultiLineDataQdlgPreLayoutDynInitL test method for test the PreLayoutDynInitL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestMultiLineDataQdlgPreLayoutDynInitL( CStifItemParser& aItem );
    
    /**
    * TestMultiLineDataQdlgHandleResourceChangeL test method for test the HandleResourceChange.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestMultiLineDataQdlgHandleResourceChangeL( CStifItemParser& aItem );
    
    /**
    * TestMultiLineDataQdlgUpdateLeftSoftKeyL test method for test the UpdateLeftSoftKey.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestMultiLineDataQdlgUpdateLeftSoftKeyL( CStifItemParser& aItem );
    
    /**
    * TestMultiLineDataQdlgDoSetPromptL test method for test the DoSetPromptL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestMultiLineDataQdlgDoSetPromptL( CStifItemParser& aItem );
    
    /**
    * TestMultiLineDataQdlgNeedToDismissQueryL test method for test the DismissQuery.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestMultiLineDataQdlgNeedToDismissQueryL( CStifItemParser& aItem );
    
    /**
    * TestMultiLineDataQdlgFirstControlL test method for test the FirstControl.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestMultiLineDataQdlgFirstControlL( CStifItemParser& aItem );
    
    /**
    * TestMultiLineDataQdlgSecondControlL test method for test the SecondControl.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestMultiLineDataQdlgSecondControlL( CStifItemParser& aItem );
    
    /**
    * TestMultiLineDataQdlgQueryControlL test method for test the QueryControl.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestMultiLineDataQdlgQueryControlL( CStifItemParser& aItem );
    
    /**
    * TestMultiLineDataQdlgQueryHeadingL test method for test the QueryHeading.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestMultiLineDataQdlgQueryHeadingL( CStifItemParser& aItem );
    
    /**
    * TestMultiLineDataSecondPromptL test method for test the SecondPrompt.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestMultiLineDataSecondPromptL( CStifItemParser& aItem );
    
    /**
    * TestMultiLineDataQdlgConstructorTwoL test method for test the Constructor.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestMultiLineDataQdlgConstructorTwoL( CStifItemParser& aItem );
    
    /**
    * TestMultiLineDataQdlgConstructorThreeL test method for test the Constructor.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestMultiLineDataQdlgConstructorThreeL( CStifItemParser& aItem );
    
    /**
    * TestMultiLineDataQdlgConstructorFourL test method for test the Constructor.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestMultiLineDataQdlgConstructorFourL( CStifItemParser& aItem );
    
    /**
    * TestMultiLineDataQdlgConstructorFiveL test method for test the Constructor.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestMultiLineDataQdlgConstructorFiveL( CStifItemParser& aItem );
    
    /**
    * TestMultiLineDataQdlgConstructorSixL test method for test the Constructor.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestMultiLineDataQdlgConstructorSixL( CStifItemParser& aItem );
    
    /**
    * TestMultiLineDataQdlgConstructorSevenL test method for test the Constructor.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestMultiLineDataQdlgConstructorSevenL( CStifItemParser& aItem );
    
    /**
    * TestMultiLineDataQdlgConstructorEightL test method for test the Constructor.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestMultiLineDataQdlgConstructorEightL( CStifItemParser& aItem );
    
//CAknIpAddressQueryDialog
    /**
    * TestIpAddressQdlgNewL test method for test the NewL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIpAddressQdlgNewL( CStifItemParser& aItem );
    
    /**
    * TestIpAddressQdlgDestructorL test method for test the Destructor.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIpAddressQdlgDestructorL( CStifItemParser& aItem );
    
    /**
    * TestIpAddressQdlgSetMinimumAndMaximumL test method for test the SetMinimumAndMaximum.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIpAddressQdlgSetMinimumAndMaximumL( CStifItemParser& aItem );
    
    /**
    * TestIpAddressQdlgNeedToDismissQueryL test method for test the NeedToDismissQuery.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIpAddressQdlgNeedToDismissQueryL( CStifItemParser& aItem );
    
    /**
    * TestIpAddressQdlgQueryControlL test method for test the QueryControl.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIpAddressQdlgQueryControlL( CStifItemParser& aItem );
    
    /**
    * TestIpAddressQdlgSetSizeAndPositionL test method for test the SetSizeAndPosition.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIpAddressQdlgSetSizeAndPositionL( CStifItemParser& aItem );
    
    /**
    * TestIpAddressQdlgPreLayoutDynInitL test method for test the PreLayoutDynInitL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIpAddressQdlgPreLayoutDynInitL( CStifItemParser& aItem );
    
    /**
    * TestIpAddressQdlgPostLayoutDynInitL test method for test the PostLayoutDynInitL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIpAddressQdlgPostLayoutDynInitL( CStifItemParser& aItem );
    
    /**
    * TestIpAddressQdlgDoSetPromptL test method for test the DoSetPrompt.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIpAddressQdlgDoSetPromptL( CStifItemParser& aItem );
    
    /**
    * TestIpAddressQdlgOkToExitL test method for test the OkToExitL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIpAddressQdlgOkToExitL( CStifItemParser& aItem );
    
    /**
    * TestIpAddressQdlgUpdateLeftSoftKeyL test method for test the UpdateLeftSoftKey.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIpAddressQdlgUpdateLeftSoftKeyL( CStifItemParser& aItem );
    
    /**
    * TestIpAddressQdlgInetAddrOneL test method for test the InetAddr.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIpAddressQdlgInetAddrOneL( CStifItemParser& aItem );
    
    /**
    * TestIpAddressQdlgInetAddrTwoL test method for test the InetAddr.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestIpAddressQdlgInetAddrTwoL( CStifItemParser& aItem );
    
//CAknFixedPointQueryDialog
    /**
    * TestFixedPointQdlgNewL test method for test the NewL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestFixedPointQdlgNewL( CStifItemParser& aItem );
    
    /**
    * TestFixedPointQdlgDestructorL test method for test the Destructor.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestFixedPointQdlgDestructorL( CStifItemParser& aItem );
    
    /**
    * TestFixedPointQdlgSetMinimumAndMaximumL test method for test the SetMinimumAndMaximum.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestFixedPointQdlgSetMinimumAndMaximumL( CStifItemParser& aItem );
    
    /**
    * TestFixedPointQdlgNeedToDismissQueryL test method for test the NeedToDismissQuery.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestFixedPointQdlgNeedToDismissQueryL( CStifItemParser& aItem );
    
    /**
    * TestFixedPointQdlgQueryControlL test method for test the QueryControl.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestFixedPointQdlgQueryControlL( CStifItemParser& aItem );
    
    /**
    * TestFixedPointQdlgSetSizeAndPositionL test method for test the SetSizeAndPosition.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestFixedPointQdlgSetSizeAndPositionL( CStifItemParser& aItem );
    
    /**
    * TestFixedPointQdlgPreLayoutDynInitL test method for test the PreLayoutDynInitL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestFixedPointQdlgPreLayoutDynInitL( CStifItemParser& aItem );
    
    /**
    * TestFixedPointQdlgPostLayoutDynInitL test method for test the PostLayoutDynInitL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestFixedPointQdlgPostLayoutDynInitL( CStifItemParser& aItem );
    
    /**
    * TestFixedPointQdlgDoSetPromptL test method for test the DoSetPromptL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestFixedPointQdlgDoSetPromptL( CStifItemParser& aItem );
    
    /**
    * TestFixedPointQdlgOkToExitL test method for test the OkToExitL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestFixedPointQdlgOkToExitL( CStifItemParser& aItem );
    
    /**
    * TestFixedPointQdlgUpdateLeftSoftKeyL test method for test the UpdateLeftSoftKeyL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestFixedPointQdlgUpdateLeftSoftKeyL( CStifItemParser& aItem );
    
    /**
    * TestFixedPointQdlgNumberOneL test method for test the Number.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestFixedPointQdlgNumberOneL( CStifItemParser& aItem );
    
    /**
    * TestFixedPointQdlgNumberTwoL test method for test the Number.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestFixedPointQdlgNumberTwoL( CStifItemParser& aItem );
    
//CAknMultiLineIpQueryDialog
    /**
    * TestMultiLineIpQdlgNewL test method for test the NewL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestMultiLineIpQdlgNewL( CStifItemParser& aItem );
    
    /**
    * TestMultiLineIpQdlgDestructorL test method for test the Destructor.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestMultiLineIpQdlgDestructorL( CStifItemParser& aItem );
    
    /**
    * TestMultiLineIpQdlgSetPromptL test method for test the SetPrompt.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestMultiLineIpQdlgSetPromptL( CStifItemParser& aItem );
    
    /**
    * TestMultiLineIpQdlgSetMaxLengthOfFirstEditorL test method for test the SetMaxLengthOfFirstEditorL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestMultiLineIpQdlgSetMaxLengthOfFirstEditorL( CStifItemParser& aItem );
    
    /**
    * TestMultiLineIpQdlgSetMaxLengthOfSecondEditorL test method for test the SetMaxLengthOfSecondEditorL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestMultiLineIpQdlgSetMaxLengthOfSecondEditorL( CStifItemParser& aItem );
    
    /**
    * TestMultiLineIpQdlgOkToExitL test method for test the OkToExitL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestMultiLineIpQdlgOkToExitL( CStifItemParser& aItem );
    
    /**
    * TestMultiLineIpQdlgPreLayoutDynInitL test method for test the PreLayoutDynInitL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestMultiLineIpQdlgPreLayoutDynInitL( CStifItemParser& aItem );
    
    /**
    * TestMultiLineIpQdlgHandleResourceChangeL test method for test the HandleResourceChange.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestMultiLineIpQdlgHandleResourceChangeL( CStifItemParser& aItem );
    
    /**
    * TestMultiLineIpQdlgUpdateLeftSoftKeyL test method for test the UpdateLeftSoftKeyL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestMultiLineIpQdlgUpdateLeftSoftKeyL( CStifItemParser& aItem );
    
    /**
    * TestMultiLineIpQdlgDoSetPromptL test method for test the DoSetPrompt.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestMultiLineIpQdlgDoSetPromptL( CStifItemParser& aItem );
    
    /**
    * TestMultiLineIpQdlgNeedToDismissQueryL test method for test the NeedToDismissQuery.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestMultiLineIpQdlgNeedToDismissQueryL( CStifItemParser& aItem );
    
    /**
    * TestMultiLineIpQdlgFirstControlL test method for test the FirstControl.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestMultiLineIpQdlgFirstControlL( CStifItemParser& aItem );
    
    /**
    * TestMultiLineIpQdlgSecondControlL test method for test the SecondControl.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestMultiLineIpQdlgSecondControlL( CStifItemParser& aItem );
    
    /**
    * TestMultiLineIpQdlgQueryControlL test method for test the QueryControl.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestMultiLineIpQdlgQueryControlL( CStifItemParser& aItem );
    
    /**
    * TestMultiLineIpQdlgSecondPromptL test method for test the SecondPrompt.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestMultiLineIpQdlgSecondPromptL( CStifItemParser& aItem );
    
//AknQueryValue.h
        //CAknQueryValue
    /**
    * TestQVSetQueryModeL test method for test the SetQueryModeL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQVSetQueryModeL( CStifItemParser& aItem );
    
    /**
    * TestQVSetSettingPageResourceIdsL test method for test the SettingPageResourceIdsL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQVSetSettingPageResourceIdsL( CStifItemParser& aItem );
    
    /**
    * TestQVSetAutoAppendL test method for test the SetAutoAppendL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQVSetAutoAppendL( CStifItemParser& aItem );
    
    /**
    * TestQVAppendValueIfNewL test method for test the AppendValueIfNewL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQVAppendValueIfNewL( CStifItemParser& aItem );
    
//CAknQueryValueDate
    /**
    * TestQVDNewL test method for test the NewL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQVDNewL( CStifItemParser& aItem );
    
    /**
    * TestQVDNewLCL test method for test the NewLC.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQVDNewLCL( CStifItemParser& aItem );
    
    /**
    * TestQVDDestructorL test method for test the Destructor.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQVDDestructorL( CStifItemParser& aItem );
    
    /**
    * TestQVDSetArrayL test method for test the SetArrayL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQVDSetArrayL( CStifItemParser& aItem );
    
    /**
    * TestQVDSetQueryCaptionL test method for test the SetQueryCaption.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQVDSetQueryCaptionL( CStifItemParser& aItem );
    
    /**
    * TestQVDValueL test method for test the Value.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQVDValueL( CStifItemParser& aItem );
    
    /**
    * TestQVDMdcArrayL test method for test the MdcArrayL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQVDMdcArrayL( CStifItemParser& aItem );
    
    /**
    * TestQVDCurrentValueTextLCL test method for test the CurrentValueTextLC.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQVDCurrentValueTextLCL( CStifItemParser& aItem );
    
    /**
    * TestQVDCurrentValueIndexL test method for test the CurrentValueIndex.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQVDCurrentValueIndexL( CStifItemParser& aItem );
    
    /**
    * TestQVDSetCurrentValueIndexL test method for test the SetCurrentValueIndex.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQVDSetCurrentValueIndexL( CStifItemParser& aItem );
    
    /**
    * TestQVDCreateEditorL test method for test the CreateEditor.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQVDCreateEditorL( CStifItemParser& aItem );
    
//CAknQueryValueDateArray
    /**
    * TestQVDANewL test method for test the NewL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQVDANewL( CStifItemParser& aItem );
    
    /**
    * TestQVDANewLC test method for test the NewLC.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQVDANewLCL( CStifItemParser& aItem );
    
    /**
    * TestQVDADestructorL test method for test the Destructor.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQVDADestructorL( CStifItemParser& aItem );
    
    /**
    * TestQVDASetArrayL test method for test the SetArray.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQVDASetArrayL( CStifItemParser& aItem );
    
    /**
    * TestQVDAArrayL test method for test the Array.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQVDAArrayL( CStifItemParser& aItem );
    
    /**
    * TestQVDAFormatStringL test method for test the FormatStringL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQVDAFormatStringL( CStifItemParser& aItem );
    
    /**
    * TestQVDAFormattedStringSizeOneL test method for test the FormattedStringSize.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQVDAFormattedStringSizeOneL( CStifItemParser& aItem );
    
    /**
    * TestQVDAFormattedStringSizeTwoL test method for test the FormattedStringSize.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQVDAFormattedStringSizeTwoL( CStifItemParser& aItem );
    
    /**
    * TestQVDAMdcaCountL test method for test the MdcaCount.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQVDAMdcaCountL( CStifItemParser& aItem );
    
    /**
    * TestQVDAMdcaPointL test method for test the MdcaPoint.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQVDAMdcaPointL( CStifItemParser& aItem );
    
//AknQueryValueDuration.h
    /**
    * TestQVDurationNewL test method for test the NewL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQVDurationNewL( CStifItemParser& aItem );
    
    /**
    * TestQVDurationNewLC test method for test the NewLCL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQVDurationNewLCL( CStifItemParser& aItem );
    
    /**
    * TestQVDurationDestructorL test method for test the Destructor.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQVDurationDestructorL( CStifItemParser& aItem );
    
    /**
    * TestQVDurationSetArrayL test method for test the SetArray.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQVDurationSetArrayL( CStifItemParser& aItem );
    
    /**
    * TestQVDurationSetQueryCaptionL test method for test the SetQueryCaption.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQVDurationSetQueryCaptionL( CStifItemParser& aItem );
    
    /**
    * TestQVDurationValueL test method for test the Value.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQVDurationValueL( CStifItemParser& aItem );
    
    /**
    * TestQVDurationMdcArrayL test method for test the MdcArray.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQVDurationMdcArrayL( CStifItemParser& aItem );
    
    /**
    * TestQVDurationCurrentValueTextLCL test method for test the CurrentValueTextLC.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQVDurationCurrentValueTextLCL( CStifItemParser& aItem );
    
    /**
    * TestQVDurationCurrentValueIndexL test method for test the CurrentValueIndex.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQVDurationCurrentValueIndexL( CStifItemParser& aItem );
    
    /**
    * TestQVDurationSetCurrentValueIndexL test method for test the SetCurrentValueIndex.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQVDurationSetCurrentValueIndexL( CStifItemParser& aItem );
    
    /**
    * TestQVDurationCreateEditorL test method for test the CreateEditorL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQVDurationCreateEditorL( CStifItemParser& aItem );
    
//CAknQueryValueDurationArray
    /**
    * TestQVDArrayNewL test method for test the NewL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQVDArrayNewL( CStifItemParser& aItem );
    
    /**
    * TestQVDArrayNewLCL test method for test the NewLC.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQVDArrayNewLCL( CStifItemParser& aItem );
    
    /**
    * TestQVDArrayDestructorL test method for test the Destructor.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQVDArrayDestructorL( CStifItemParser& aItem );
    
    /**
    * TestQVDArraySetArrayL test method for test the SetArray.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQVDArraySetArrayL( CStifItemParser& aItem );
    
    /**
    * TestQVDArrayArrayL test method for test the Array.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQVDArrayArrayL( CStifItemParser& aItem );
    
    /**
    * TestQVDArrayFormatStringL test method for test the FormatString.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQVDArrayFormatStringL( CStifItemParser& aItem );
    
    /**
    * TestQVDArrayFormattedStringSizeOneL test method for test the FormattedStringSize.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQVDArrayFormattedStringSizeOneL( CStifItemParser& aItem );
    
    /**
    * TestQVDArrayFormattedStringSizeTwoL test method for test the FormattedStringSize.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQVDArrayFormattedStringSizeTwoL( CStifItemParser& aItem );
    
    /**
    * TestQVDArrayFormatDurationL test method for test the FormatDuration.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQVDArrayFormatDurationL( CStifItemParser& aItem );
    
    /**
    * TestQVDArrayMdcaCountL test method for test the MdcaCount.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQVDArrayMdcaCountL( CStifItemParser& aItem );
    
    /**
    * TestQVDArrayMdcaPointL test method for test the MdcaPoint.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQVDArrayMdcaPointL( CStifItemParser& aItem );
    
//AknQueryValueNumber.h
        //CAknQueryValueNumber
    /**
    * TestQVNumberNewL test method for test the NewL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQVNumberNewL( CStifItemParser& aItem );
    
    /**
    * TestQVNumberNewLC test method for test the NewLC.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQVNumberNewLC( CStifItemParser& aItem );
    
    /**
    * TestQVNumberDestructorL test method for test the Destructor.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQVNumberDestructorL( CStifItemParser& aItem );
    
    /**
    * TestQVNumberSetArrayL test method for test the SetArrayL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQVNumberSetArrayL( CStifItemParser& aItem );
    
    /**
    * TestQVNumberSetQueryCaptionL test method for test the SetQueryCaption.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQVNumberSetQueryCaptionL( CStifItemParser& aItem );
    
    /**
    * TestQVNumberValueL test method for test the Value.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQVNumberValueL( CStifItemParser& aItem );
    
    /**
    * TestQVNumberMdcArrayL test method for test the MdcArray.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQVNumberMdcArrayL( CStifItemParser& aItem );
    
    /**
    * TestQVNumberCurrentValueTextLCL test method for test the CurrentValueTextLC.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQVNumberCurrentValueTextLCL( CStifItemParser& aItem );
    
    /**
    * TestQVNumberCurrentValueIndexL test method for test the CurrentValueIndex.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQVNumberCurrentValueIndexL( CStifItemParser& aItem );
    
    /**
    * TestQVNumberSetCurrentValueIndexL test method for test the SetCurrentValueIndex.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQVNumberSetCurrentValueIndexL( CStifItemParser& aItem );
    
    /**
    * TestQVNumberCreateEditorL test method for test the CreateEditorL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQVNumberCreateEditorL( CStifItemParser& aItem );
    
//CAknQueryValueNumberArray
    /**
    * TestQVNArrayNewL test method for test the NewL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQVNArrayNewL( CStifItemParser& aItem );
    
    /**
    * TestQVNArrayNewLCL test method for test the NewLC.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQVNArrayNewLCL( CStifItemParser& aItem );
    
    /**
    * TestQVNArrayDestructorL test method for test the Destructor.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQVNArrayDestructorL( CStifItemParser& aItem );
    
    /**
    * TestQVNArraySetArrayL test method for test the SetArray.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQVNArraySetArrayL( CStifItemParser& aItem );
    
    /**
    * TestQVNArrayArrayL test method for test the Array.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQVNArrayArrayL( CStifItemParser& aItem );
    
    /**
    * FormatString test method for test the TestQVNArrayFormatStringL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQVNArrayFormatStringL( CStifItemParser& aItem );
    
    /**
    * TestQVNArrayFormattedStringSizeOneL test method for test the FormattedStringSize.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQVNArrayFormattedStringSizeOneL( CStifItemParser& aItem );
    
    /**
    * TestQVNArrayFormattedStringSizeTwoL test method for test the FormattedStringSize.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQVNArrayFormattedStringSizeTwoL( CStifItemParser& aItem );
    
    /**
    * TestQVNArrayMdcaCountL test method for test the MdcaCount.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQVNArrayMdcaCountL( CStifItemParser& aItem );
    
    /**
    * TestQVNArrayMdcaPointL test method for test the MdcaPoint.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestQVNArrayMdcaPointL( CStifItemParser& aItem );
    
//AknQueryValuePhone.h
    /**
    * TestPhoneNewL test method for test the NewL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestPhoneNewL( CStifItemParser& aItem );
    
    /**
    * TestPhoneNewLC test method for test the NewLC.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestPhoneNewLC( CStifItemParser& aItem );
    
    /**
    * TestPhoneDeconstructorL test method for test the ~CAknQueryValuePhone.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestPhoneDeconstructorL( CStifItemParser& aItem );
    
    /**
    * TestPhoneSetArrayL test method for test the SetArrayL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestPhoneSetArrayL( CStifItemParser& aItem );
    
    /**
    * TestPhoneSetQueryCaptionL test method for test the SetQueryCaption.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestPhoneSetQueryCaptionL( CStifItemParser& aItem );
    
    /**
    * TestPhoneValueL test method for test the Value.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestPhoneValueL( CStifItemParser& aItem );
    
    /**
    * TestPhoneMdcArrayL test method for test the MdcArray.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestPhoneMdcArrayL( CStifItemParser& aItem );
    
    /**
    * TestPhoneCurrentValueTextLC test method for test the CurrentValueTextLC.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestPhoneCurrentValueTextLC( CStifItemParser& aItem );
    
    /**
    * TestPhoneCurrentValueIndexL test method for test the CurrentValueIndex.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestPhoneCurrentValueIndexL( CStifItemParser& aItem );
    
    /**
    * TestPhoneSetCurrentValueIndexL test method for test the SetCurrentValueIndex.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestPhoneSetCurrentValueIndexL( CStifItemParser& aItem );
    
    /**
    * TestPhoneCreateEditorL test method for test the CreateEditorL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestPhoneCreateEditorL( CStifItemParser& aItem );
    
    /**
    * TestPhoneArrayNewL test method for test the NewL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestPhoneArrayNewL( CStifItemParser& aItem );
    
    /**
    * TestPhoneArrayNewLC test method for test the NewLC.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestPhoneArrayNewLC( CStifItemParser& aItem );
    
    /**
    * TestPhoneArrayDeconstructorL test method for test the ~CAknQueryValuePhoneArray.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestPhoneArrayDeconstructorL( CStifItemParser& aItem );
    
    /**
    * TestPhoneArraySetArrayL test method for test the SetArray.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestPhoneArraySetArrayL( CStifItemParser& aItem );
    
    /**
    * TestPhoneArrayArrayL test method for test the Array.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestPhoneArrayArrayL( CStifItemParser& aItem );
    
    /**
    * TestPhoneArrayFormattedStringSizeL test method for test the FormattedStringSize.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestPhoneArrayFormattedStringSizeL( CStifItemParser& aItem );
    
    /**
    * TestPhoneArrayMdcaCountL test method for test the MdcaCount.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestPhoneArrayMdcaCountL( CStifItemParser& aItem );
    
    /**
    * TestPhoneArrayMdcaPointL test method for test the MdcaPoint.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestPhoneArrayMdcaPointL( CStifItemParser& aItem );
    
    //AknQueryValueText.h
    /**
    * TestTextNewL test method for test the NewL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestTextNewL( CStifItemParser& aItem );
    
    /**
    * TestTextNewLC test method for test the NewLC.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestTextNewLC( CStifItemParser& aItem );
    
    /**
    * TestTextDeconstructorL test method for test the ~CAknQueryValueText.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestTextDeconstructorL( CStifItemParser& aItem );
    
    /**
    * TestTextSetArrayL test method for test the SetArrayL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestTextSetArrayL( CStifItemParser& aItem );
    
    /**
    * TestTextSetQueryCaptionL test method for test the SetQueryCaption.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestTextSetQueryCaptionL( CStifItemParser& aItem );
    
    /**
    * TestTextValueL test method for test the Value.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestTextValueL( CStifItemParser& aItem );
    
    /**
    * TestTextMdcArrayL test method for test the MdcArray.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestTextMdcArrayL( CStifItemParser& aItem );
    
    /**
    * TestTextCurrentValueTextLC test method for test the CurrentValueTextLC.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestTextCurrentValueTextLC( CStifItemParser& aItem );
    
    /**
    * TestTextCurrentValueIndexL test method for test the CurrentValueIndex.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestTextCurrentValueIndexL( CStifItemParser& aItem );
    
    /**
    * TestTextSetCurrentValueIndexL test method for test the SetCurrentValueIndex.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestTextSetCurrentValueIndexL( CStifItemParser& aItem );
    
    /**
    * TestTextCreateEditorL test method for test the CreateEditorL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestTextCreateEditorL( CStifItemParser& aItem );
    
    /**
    * TestTextArrayNewL test method for test the NewL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestTextArrayNewL( CStifItemParser& aItem );
    
    /**
    * TestTextArrayNewLC test method for test the NewLC.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestTextArrayNewLC( CStifItemParser& aItem );
    
    /**
    * TestTextArrayDeconstructorL test method for test the ~CAknQueryValueTextArray.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestTextArrayDeconstructorL( CStifItemParser& aItem );
    
    /**
    * TestTextArraySetArrayL test method for test the SetArray.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestTextArraySetArrayL( CStifItemParser& aItem );
    
    /**
    * TestTextArrayArrayL test method for test the Array.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestTextArrayArrayL( CStifItemParser& aItem );
    
    /**
    * TestTextArrayFormattedStringSizeL test method for test the FormattedStringSize.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestTextArrayFormattedStringSizeL( CStifItemParser& aItem );
    
    /**
    * TestTextArrayMdcaCountL test method for test the MdcaCount.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestTextArrayMdcaCountL( CStifItemParser& aItem );
    
    /**
    * TestTextArrayMdcaPointL test method for test the MdcaPoint.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestTextArrayMdcaPointL( CStifItemParser& aItem );
    
    //AknQueryValueTime.h
    /**
    * TestTimeNewL test method for test the NewL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestTimeNewL( CStifItemParser& aItem );
    
    /**
    * TestTimeNewLC test method for test the NewLC.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestTimeNewLC( CStifItemParser& aItem );
    
    /**
    * TestTimeDeconstructorL test method for test the ~CAknQueryValueTime.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestTimeDeconstructorL( CStifItemParser& aItem );
    
    /**
    * TestTimeSetArrayL test method for test the SetArrayL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestTimeSetArrayL( CStifItemParser& aItem );
    
    /**
    * TestTimeSetQueryCaptionL test method for test the SetQueryCaption.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestTimeSetQueryCaptionL( CStifItemParser& aItem );
    
    /**
    * TestTimeValueL test method for test the Value.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestTimeValueL( CStifItemParser& aItem );
    
    /**
    * TestTimeMdcArrayL test method for test the MdcArray.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestTimeMdcArrayL( CStifItemParser& aItem );
    
    /**
    * TestTimeCurrentValueTextLC test method for test the CurrentValueTimeLC.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestTimeCurrentValueTextLC( CStifItemParser& aItem );
    
    /**
    * TestTimeCurrentValueIndexL test method for test the CurrentValueIndex.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestTimeCurrentValueIndexL( CStifItemParser& aItem );
    
    /**
    * TestTimeSetCurrentValueIndexL test method for test the SetCurrentValueIndex.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestTimeSetCurrentValueIndexL( CStifItemParser& aItem );
    
    /**
    * TestTimeCreateEditorL test method for test the CreateEditorL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestTimeCreateEditorL( CStifItemParser& aItem );
    
    /**
    * TestTimeArrayNewL test method for test the NewL.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestTimeArrayNewL( CStifItemParser& aItem );
    
    /**
    * TestTimeArrayNewLC test method for test the NewLC.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestTimeArrayNewLC( CStifItemParser& aItem );
    
    /**
    * TestTimeArrayDeconstructorL test method for test the ~CAknQueryValueTimeArray.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestTimeArrayDeconstructorL( CStifItemParser& aItem );
    
    /**
    * TestTimeArraySetArrayL test method for test the SetArray.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestTimeArraySetArrayL( CStifItemParser& aItem );
    
    /**
    * TestTimeArrayArrayL test method for test the Array.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestTimeArrayArrayL( CStifItemParser& aItem );
    
    /**
    * TestTimeArrayFormatStringL test method for test the FormatString.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestTimeArrayFormatStringL( CStifItemParser& aItem );
    
    /**
    * TestTimeArrayFormattedStringSizeL test method for test the FormattedStringSize.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestTimeArrayFormattedStringSizeL( CStifItemParser& aItem );
    
    /**
    * TestTimeArrayMdcaCountL test method for test the MdcaCount.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestTimeArrayMdcaCountL( CStifItemParser& aItem );
    
    /**
    * TestTimeArrayMdcaPointL test method for test the MdcaPoint.
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestTimeArrayMdcaPointL( CStifItemParser& aItem );
    
private:
    /**
     * Method used to log version of test class
     */
    void SendTestClassVersion();

private:    // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;
    
    /**
     * for test the akndialog.h
     * own.
     */
    CAknDialog* iDialog;
    CTestSDKQueriesDialg* iTestDialog;

    CTestSDKQueriesView *iView;
    CTestSDKQueriesContainer* iContainer;
    
    // Resource file offset
    TInt iOffset;
    };

#endif      // C_TESTSDKQUERIES_H

// End of File
