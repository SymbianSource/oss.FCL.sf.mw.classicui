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
* Description:  test aknchoicelist.h
*
*/



#ifndef C_TESTSDKCHOICELIST_H
#define C_TESTSDKCHOICELIST_H

//  INCLUDES
#include <stiflogger.h>
#include <testscripterinternal.h>
#include <stiftestmodule.h>
#include <testclassassert.h>
#include <aknchoicelist.h>

// MACROS
#define TEST_CLASS_VERSION_MAJOR 0
#define TEST_CLASS_VERSION_MINOR 0
#define TEST_CLASS_VERSION_BUILD 0

// Logging path
_LIT( KtestsdkchoicelistLogPath, "\\logs\\testframework\\testsdkchoicelist\\" ); 
// Log file
_LIT( KtestsdkchoicelistLogFile, "testsdkchoicelist.txt" ); 
_LIT( KtestsdkchoicelistLogFileWithTitle, "testsdkchoicelist_[%S].txt" );

/**
*  CTestSDKChoiceList test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS(CTestSDKChoiceList) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestSDKChoiceList* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestSDKChoiceList();

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
    CTestSDKChoiceList( CTestModuleIf& aTestModuleIf );

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

private:
    /**
     *initialize iChoiceList
     */
    void TestCLInitializeL();
    
private: // Test aknchoicelist.h
/*                               class CAknChoiceList                         */
    /**
     * TestCLNewL test function for testing the 
     *     NewL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLNewL( CStifItemParser& aItem );
    
    /**
     * TestCLNewLC test function for testing the 
     *     NewLC function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLNewLC( CStifItemParser& aItem );
    
    /**
     * TestCLShowChoiceListL test function for testing the 
     *     ShowChoiceListL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLShowChoiceListL( CStifItemParser& aItem );
    
    /**
     * TestCLSetSelectedIndexL test function for testing the 
     *     SetSelectedIndex function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLSetSelectedIndexL( CStifItemParser& aItem );
    
    /**
     * TestCLSelectedIndexL test function for testing the 
     *     SelectedIndex function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLSelectedIndexL( CStifItemParser& aItem );
    
    /**
     * TestCLSetItemsL test function for testing the 
     *     SetItems function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLSetItemsL( CStifItemParser& aItem );
    
    /**
     * TestCLSetItemsL test function for testing the 
     *     SetItemsL function with leave
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLSetItemsLeaveL( CStifItemParser& aItem );
    
    /**
     * TestCLAddItemL test function for testing the 
     *     AddItemL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLAddItemL( CStifItemParser& aItem );
    
    /**
     * TestCLRemoveItemL test function for testing the 
     *     RemoveItem function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLRemoveItemL( CStifItemParser& aItem );
    
    /**
     * TestCLSetFlagsL test function for testing the 
     *     SetFlags function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLSetFlagsL( CStifItemParser& aItem );
    
    /**
     * TestCLFlagsL test function for testing the 
     *     Flags function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLFlagsL( CStifItemParser& aItem );
    
    /**
     * TestCLSetButtonL test function for testing the 
     *     SetButtonL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLSetButtonL( CStifItemParser& aItem );
    
    /**
     * TestCLHideChoiceListL test function for testing the 
     *     HideChoiceList function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLHideChoiceListL( CStifItemParser& aItem );
    
    /**
     * TestCLSetTooltipTextL test function for testing the 
     *     SetTooltipTextL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLSetTooltipTextL( CStifItemParser& aItem );
    
    /**
     * TestCLSetTooltipTimeoutsL test function for testing the 
     *     SetTooltipTimeouts function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLSetTooltipTimeoutsL( CStifItemParser& aItem );
    
    /**
     * TestCLSetTooltipPositionL test function for testing the 
     *     SetTooltipPosition function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLSetTooltipPositionL( CStifItemParser& aItem );
    
    /**
     * TestCLComponentControlL test function for testing the 
     *     ComponentControl function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLComponentControlL( CStifItemParser& aItem );
    
    /**
     * TestCLCountComponentControlsL test function for testing the 
     *     CountComponentControls function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLCountComponentControlsL( CStifItemParser& aItem );
    
    /**
     * TestCLMinimumSizeL test function for testing the 
     *     MinimumSize function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLMinimumSizeL( CStifItemParser& aItem );
    
    /**
     * TestCLHandleResourceChangeL test function for testing the 
     *     HandleResourceChange function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLHandleResourceChangeL( CStifItemParser& aItem );
    
    /**
     * TestCLOfferKeyEventL test function for testing the 
     *     OfferKeyEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLOfferKeyEventL( CStifItemParser& aItem );
    
    /**
     * TestCLDrawL test function for testing the 
     *     Draw function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLDrawL( CStifItemParser& aItem );
    
    /**
     * TestCLPositionChangedL test function for testing the 
     *     PositionChanged function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLPositionChangedL( CStifItemParser& aItem );
    
    /**
     * TestCLHandleControlEventL test function for testing the 
     *     HandleControlEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLHandleControlEventL( CStifItemParser& aItem );
    
    /**
     * TestCLInsertItemL test function for testing the 
     *     InsertItemL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCLInsertItemL( CStifItemParser& aItem );

private:    // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;
    
    /**
     * CAknChoiceList Property
     * owned
     */
    CAknChoiceList* iChoiceList;

    // Resource file offset
    TInt iOffset;
    };

#endif      // C_TESTSDKCHOICELIST_H

// End of File
