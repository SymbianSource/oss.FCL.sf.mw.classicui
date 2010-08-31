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
* Description:  test aknsinglecolumnstyletreelist.h aknsinglestyletreelist.h 
*                     akntreelist.h
*
*/



#ifndef C_TESTSDKHIERARCHICALLISTS_H
#define C_TESTSDKHIERARCHICALLISTS_H

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
_LIT( KtestsdkhierarchicallistsLogPath, "\\logs\\testframework\\testsdkhierarchicallists\\" ); 
// Log file
_LIT( KtestsdkhierarchicallistsLogFile, "testsdkhierarchicallists.txt" ); 
_LIT( KtestsdkhierarchicallistsLogFileWithTitle, "testsdkhierarchicallists_[%S].txt" );

/**
*  CTestSDKHierarchicalLists test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS(CTestSDKHierarchicalLists) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestSDKHierarchicalLists* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestSDKHierarchicalLists();

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
    CTestSDKHierarchicalLists( CTestModuleIf& aTestModuleIf );

    /**
    * By default Symbian 2nd phase constructor is private.
    */
    void ConstructL();

    /**
    * Frees all resources allocated from test methods.
    * @since S60 5.0
    */
    void Delete();
    
    /**
     * Method used to log version of test class
     */
    void SendTestClassVersion();

private: // Test aknsinglecolumnstyletreelist.h
/*                    class CAknSingleColumnStyleTreeList                   */
    /**
     * TestHLSCLNewL test function for testing the 
     *     NewL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestHLSCLNewL( CStifItemParser& aItem );
    
    /**
     * TestHLSCLCNewL test function for testing the 
     *     NewL function with CCoeControl
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestHLSCLCNewL( CStifItemParser& aItem );
    
    /**
     * TestHLSCLNewLC test function for testing the 
     *     NewLC function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestHLSCLNewLC( CStifItemParser& aItem );
    
    /**
     * TestHLSCLCNewLC test function for testing the 
     *     NewLC function with CCoeControl
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestHLSCLCNewLC( CStifItemParser& aItem );
    
    /**
     * TestHLSCLAddSimpleDataRowL test function for testing the 
     *     AddSimpleDataRowL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestHLSCLAddSimpleDataRowL( CStifItemParser& aItem );
    
    /**
     * TestHLSCLAddCoreDataRowL test function for testing the 
     *     AddCoreDataRowL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestHLSCLAddCoreDataRowL( CStifItemParser& aItem );
    
    /**
     * TestHLSCLAddCoreDataRowCL test function for testing the 
     *     AddCoreDataRowL function with Column
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestHLSCLAddCoreDataRowCL( CStifItemParser& aItem );
    
    /**
     * TestHLSCLAddSubtitleRowL test function for testing the 
     *     AddSubtitleRowL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestHLSCLAddSubtitleRowL( CStifItemParser& aItem );
    
    /**
     * TestHLSCLTextL test function for testing the 
     *     Text function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestHLSCLTextL( CStifItemParser& aItem );
    
    /**
     * TestHLSCLTextCIL test function for testing the 
     *     Text function with ColumnIndex
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestHLSCLTextCIL( CStifItemParser& aItem );
    
    /**
     * TestHLSCLSetTextL test function for testing the 
     *     SetTextL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestHLSCLSetTextL( CStifItemParser& aItem );
    
    /**
     * TestHLSCLSetTextCIL test function for testing the 
     *     SetTextL function with ColumnIndex
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestHLSCLSetTextCIL( CStifItemParser& aItem );
    
    /**
     * TestHLSCLIsEmphasisedL test function for testing the 
     *     IsEmphasised function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestHLSCLIsEmphasisedL( CStifItemParser& aItem );
    
    /**
     * TestHLSCLSetEmphasisL test function for testing the 
     *     SetEmphasis function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestHLSCLSetEmphasisL( CStifItemParser& aItem );
    
    /**
     * TestHLSCLIsThirdColumnEnabledL test function for testing the 
     *     IsThirdColumnEnabled function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestHLSCLIsThirdColumnEnabledL( CStifItemParser& aItem );
    
    /**
     * TestHLSCLEnableThirdColumnL test function for testing the 
     *     EnableThirdColumn function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestHLSCLEnableThirdColumnL( CStifItemParser& aItem );
    
    /**
     * TestHLSCLIconL test function for testing the 
     *     Icon function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestHLSCLIconL( CStifItemParser& aItem );
    
    /**
     * TestHLSCLSetIconL test function for testing the 
     *     SetIcon function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestHLSCLSetIconL( CStifItemParser& aItem );
    
    /**
     * TestHLSCLItemTypeL test function for testing the 
     *     ItemType function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestHLSCLItemTypeL( CStifItemParser& aItem );
    
private: // Test aknsinglestyletreelist.h
/*                    class CAknSingleStyleTreeList                        */
    /**
     * TestHLSSLNewL test function for testing the 
     *     NewL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestHLSSLNewL( CStifItemParser& aItem );
    
    /**
     * TestHLSSLCNewL test function for testing the 
     *     NewL function with CCoecontrol
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestHLSSLCNewL( CStifItemParser& aItem );
    
    /**
     * TestHLSSLNewLC test function for testing the 
     *     NewLC function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestHLSSLNewLC( CStifItemParser& aItem );
    
    /**
     * TestHLSSLCNewLC test function for testing the 
     *     NewLC function with CCoecontrol
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestHLSSLCNewLC( CStifItemParser& aItem );
    
    /**
     * TestHLSSLAddLeafL test function for testing the 
     *     AddLeafL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestHLSSLAddLeafL( CStifItemParser& aItem );
    
    /**
     * TestHLSSLAddNodeL test function for testing the 
     *     AddNodeL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestHLSSLAddNodeL( CStifItemParser& aItem );
    
    /**
     * TestHLSSLSortL test function for testing the 
     *     SortL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestHLSSLSortL( CStifItemParser& aItem );
    
    /**
     * TestHLSSLSetTextL test function for testing the 
     *     SetTextL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestHLSSLSetTextL( CStifItemParser& aItem );
    
    /**
     * TestHLSSLTextL test function for testing the 
     *     Text function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestHLSSLTextL( CStifItemParser& aItem );
    
    /**
     * TestHLSSLSetIconL test function for testing the 
     *     SetIcon function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestHLSSLSetIconL( CStifItemParser& aItem );
    
    /**
     * TestHLSSLIconL test function for testing the 
     *     Icon function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestHLSSLIconL( CStifItemParser& aItem );

private: // Test akntreelist.h
/*                               class CAknTreeList                        */
    /**
     * TestHLTLSetFlagsL test function for testing the 
     *     SetFlags function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestHLTLSetFlagsL( CStifItemParser& aItem );
    
    /**
     * TestHLTLFlagsL test function for testing the 
     *     Flags function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestHLTLFlagsL( CStifItemParser& aItem );
    
    /**
     * TestHLTLMoveItemL test function for testing the 
     *     MoveItemL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestHLTLMoveItemL( CStifItemParser& aItem );
    
    /**
     * TestHLTLRemoveItemL test function for testing the 
     *     RemoveItem function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestHLTLRemoveItemL( CStifItemParser& aItem );
    
    /**
     * TestHLTLExpandNodeL test function for testing the 
     *     ExpandNode function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestHLTLExpandNodeL( CStifItemParser& aItem );
    
    /**
     * TestHLTLCollapseNodeL test function for testing the 
     *     CollapseNode function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestHLTLCollapseNodeL( CStifItemParser& aItem );
    
    /**
     * TestHLTLIsExpandedL test function for testing the 
     *     IsExpanded function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestHLTLIsExpandedL( CStifItemParser& aItem );
    
    /**
     * TestHLTLFocusedItemL test function for testing the 
     *     FocusedItem function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestHLTLFocusedItemL( CStifItemParser& aItem );
    
    /**
     * TestHLTLSetFocusedItemL test function for testing the 
     *     SetFocusedItem function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestHLTLSetFocusedItemL( CStifItemParser& aItem );
    
    /**
     * TestHLTLHighlightRectL test function for testing the 
     *     HighlightRect function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestHLTLHighlightRectL( CStifItemParser& aItem );
    
    /**
     * TestHLTLAddIconL test function for testing the 
     *     AddIconL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestHLTLAddIconL( CStifItemParser& aItem );
    
    /**
     * TestHLTLAddIIconL test function for testing the 
     *     AddIconL function with Icon
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestHLTLAddIIconL( CStifItemParser& aItem );
    
    /**
     * TestHLTLAddColorIconL test function for testing the 
     *     AddColorIconL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestHLTLAddColorIconL( CStifItemParser& aItem );
    
    /**
     * TestHLTLAssignIconL test function for testing the 
     *     AssignIconL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestHLTLAssignIconL( CStifItemParser& aItem );
    
    /**
     * TestHLTLAssignIIconL test function for testing the 
     *     AssignIconL function with Icon
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestHLTLAssignIIconL( CStifItemParser& aItem );
    
    /**
     * TestHLTLAssignColorIconL test function for testing the 
     *     AssignColorIconL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestHLTLAssignColorIconL( CStifItemParser& aItem );
    
    /**
     * TestHLTLRemoveIconL test function for testing the 
     *     RemoveIconL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestHLTLRemoveIconL( CStifItemParser& aItem );
    
    /**
     * TestHLTLChildCountL test function for testing the 
     *     ChildCount function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestHLTLChildCountL( CStifItemParser& aItem );
    
    /**
     * TestHLTLChildL test function for testing the 
     *     Child function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestHLTLChildL( CStifItemParser& aItem );
    
    /**
     * TestHLTLParentL test function for testing the 
     *     Parent function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestHLTLParentL( CStifItemParser& aItem );
    
    /**
     * TestHLTLContainsL test function for testing the 
     *     Contains function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestHLTLContainsL( CStifItemParser& aItem );
    
    /**
     * TestHLTLIsNodeL test function for testing the 
     *     IsNode function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestHLTLIsNodeL( CStifItemParser& aItem );
    
    /**
     * TestHLTLIsLeafL test function for testing the 
     *     IsLeaf function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestHLTLIsLeafL( CStifItemParser& aItem );
    
    /**
     * TestHLTLIsMarkedL test function for testing the 
     *     IsMarked function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestHLTLIsMarkedL( CStifItemParser& aItem );
    
    /**
     * TestHLTLSetMarkedL test function for testing the 
     *     SetMarked function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestHLTLSetMarkedL( CStifItemParser& aItem );
    
    /**
     * TestHLTLEnableMarkingL test function for testing the 
     *     EnableMarking function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestHLTLEnableMarkingL( CStifItemParser& aItem );
    
    /**
     * TestHLTLGetMarkedItemsL test function for testing the 
     *     GetMarkedItemsL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestHLTLGetMarkedItemsL( CStifItemParser& aItem );
    
    /**
     * TestHLTLGetMarkedRItemsL test function for testing the 
     *     GetMarkedItemsL function by RArray
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestHLTLGetMarkedRItemsL( CStifItemParser& aItem );
    
    /**
     * TestHLTLIsEmptyL test function for testing the 
     *     IsEmpty function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestHLTLIsEmptyL( CStifItemParser& aItem );
    
    /**
     * TestHLTLSetNonEmptyL test function for testing the 
     *     SetNonEmpty function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestHLTLSetNonEmptyL( CStifItemParser& aItem );
    
    /**
     * TestHLTLIsPersistentL test function for testing the 
     *     IsPersistent function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestHLTLIsPersistentL( CStifItemParser& aItem );
    
    /**
     * TestHLTLSetPersistentL test function for testing the 
     *     SetPersistent function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestHLTLSetPersistentL( CStifItemParser& aItem );
    
    /**
     * TestHLTLSortL test function for testing the 
     *     Sort function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestHLTLSortL( CStifItemParser& aItem );
    
    /**
     * TestHLTLNSortL test function for testing the 
     *     Sort function by node
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestHLTLNSortL( CStifItemParser& aItem );
    
    /**
     * TestHLTLAddObserverL test function for testing the 
     *     AddObserverL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestHLTLAddObserverL( CStifItemParser& aItem );
    
    /**
     * TestHLTLRemoveObserverL test function for testing the 
     *     RemoveObserver function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestHLTLRemoveObserverL( CStifItemParser& aItem );
    
    /**
     * TestHLTLTabModeFunctionIndicatorsL test function for testing the 
     *     TabModeFunctionIndicators function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestHLTLTabModeFunctionIndicatorsL( CStifItemParser& aItem );
    
    /**
     * TestHLTLEnableTabModeFunctionIndicatorsL test function for testing the 
     *     EnableTabModeFunctionIndicatorsL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestHLTLEnableTabModeFunctionIndicatorsL( CStifItemParser& aItem );
    
    /**
     * TestHLTLSetFocusedItemIDL test function for testing the 
     *     SetFocusedItem function by TAknTreeItemID
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestHLTLSetFocusedItemIDL( CStifItemParser& aItem );
    
    /**
     * TestHLTLFocusedItemIndexL test function for testing the 
     *     FocusedItemIndex function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestHLTLFocusedItemIndexL( CStifItemParser& aItem );
    
    /**
     * TestHLTLVisibleItemIndexL test function for testing the 
     *     VisibleItemIndex function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestHLTLVisibleItemIndexL( CStifItemParser& aItem );
    
    /**
     * TestHLTLOSortL test function for testing the 
     *     Sort function by order
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestHLTLOSortL( CStifItemParser& aItem );
    
    /**
     * TestHLTLFBSortL test function for testing the 
     *     Sort function by FocusBehaviour
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestHLTLFBSortL( CStifItemParser& aItem );
    
    /**
     * TestHLTLSetEmptyTextL test function for testing the 
     *     SetEmptyTextL function by FocusBehaviour
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestHLTLSetEmptyTextL( CStifItemParser& aItem );

private:    // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;

    };

#endif      // C_TESTSDKHIERARCHICALLISTS_H

// End of File
