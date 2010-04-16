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
* Description:  ?Description
*
*/



#ifndef C_TESTSDKSEARCHFIELD_H
#define C_TESTSDKSEARCHFIELD_H

//  INCLUDES
#include <stiflogger.h>
#include <testscripterinternal.h>
#include <stiftestmodule.h>
#include <testclassassert.h>

class CAknSearchField;
class CTestSDKSearchFieldContainer;
class CTestSDKSFView;
class CTestSDKSFASTObserver;

// MACROS
#define TEST_CLASS_VERSION_MAJOR 0
#define TEST_CLASS_VERSION_MINOR 0
#define TEST_CLASS_VERSION_BUILD 0

// Logging path
_LIT( KtestsdksearchfieldLogPath, "\\logs\\testframework\\testsdksearchfield\\" ); 
// Log file
_LIT( KtestsdksearchfieldLogFile, "testsdksearchfield.txt" ); 
_LIT( KtestsdksearchfieldLogFileWithTitle, "testsdksearchfield_[%S].txt" );

/**
*  Ctestsdksearchfield test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS(CTestSDKSearchField) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestSDKSearchField* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestSDKSearchField();

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
    CTestSDKSearchField( CTestModuleIf& aTestModuleIf );

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

    //[TestMethods]
private://aknsfld.h
    /**
     * TestSFNewL test function for testing the NewL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSFNewL( CStifItemParser& aItem );
    
    /**
     * TestSFDelete test function for testing the destructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSFDelete( CStifItemParser& aItem );
    
    /**
     * TestSFTextLength test function for testing the TextLength function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSFTextLength( CStifItemParser& aItem );
    
    /**
     * TestSFGetSearchText test function for testing the GetSearchText function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSFGetSearchText( CStifItemParser& aItem );
    
    /**
     * TestSFSetSearchTextL test function for testing the SetSearchTextL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSFSetSearchTextL( CStifItemParser& aItem );
    
    /**
     * TestSFSelectSearchTextL test function for testing the SelectSearchTextL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSFSelectSearchTextL( CStifItemParser& aItem );
    
    /**
     * TestSFResetL test function for testing the ResetL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSFResetL( CStifItemParser& aItem );
    
    /**
     * TestSFSetInfoTextL test function for testing the SetInfoTextL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSFSetInfoTextL( CStifItemParser& aItem );
    
    /**
     * TestSFClipboardL test function for testing the ClipboardL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSFClipboardL( CStifItemParser& aItem );
    
    /**
     * TestSFSearchFieldStyle test function for testing the SearchFieldStyle function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSFSearchFieldStyle( CStifItemParser& aItem );
    
    /**
     * TestSFSetSkinEnabledL test function for testing the SetSkinEnabledL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSFSetSkinEnabledL( CStifItemParser& aItem );
    
    /**
     * TestSFOfferKeyEventL test function for testing the OfferKeyEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSFOfferKeyEventL( CStifItemParser& aItem );
    
    /**
     * TestSFMinimumSize test function for testing the MinimumSize function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSFMinimumSize( CStifItemParser& aItem );
    
    /**
     * TestSFMakeVisible test function for testing the MakeVisible function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSFMakeVisible( CStifItemParser& aItem );
    
    /**
     * TestSFSetLinePos test function for testing the SetLinePos function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSFSetLinePos( CStifItemParser& aItem );
    
    /**
     * TestSFEditor test function for testing the Editor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSFEditor( CStifItemParser& aItem );
    
    /**
     * TestSFSetAdaptiveGridChars test function for testing the SetAdaptiveGridChars function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSFSetAdaptiveGridChars( CStifItemParser& aItem );
    
    /**
     * TestSFShowAdaptiveSearchGrid test function for testing the ShowAdaptiveSearchGrid function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSFShowAdaptiveSearchGrid( CStifItemParser& aItem );
    
    /**
     * TestSFSetListColumnFilterFlags test function for testing the SetListColumnFilterFlags function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSFSetListColumnFilterFlagsL( CStifItemParser& aItem );
    
    /**
     * TestSFListColumnFilterFlags test function for testing the ListColumnFilterFlags function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSFListColumnFilterFlags( CStifItemParser& aItem );
    
    /**
     * TestSFAddAdaptiveSearchTextObserverL test function for testing the AddAdaptiveSearchTextObserverL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSFAddAdaptiveSearchTextObserverL( CStifItemParser& aItem );
    
    /**
     * TestSFRemoveAdaptiveSearchTextObserver test function for testing the RemoveAdaptiveSearchTextObserver function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSFRemoveAdaptiveSearchTextObserver( CStifItemParser& aItem );

    /**
     * TestSFAdaptiveSearchEnabled test function for testing the AdaptiveSearchEnabled function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSFAdaptiveSearchEnabled( CStifItemParser& aItem );

    /**
     * TestSFLanguageChanged test function for testing the LanguageChanged function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSFLanguageChanged( CStifItemParser& aItem );
private:    // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;
    
    /**
     * CAknSearchField instance
     */
    CAknSearchField* iSearchField;
    
    /**
     * Own, for initialize container
     */
    CTestSDKSFView* iTestSDKSFView;

    /**
     * Own, for initialize container
     */
    CTestSDKSearchFieldContainer* iTestSDKSearchFieldContainer;

    /**
     * Not own, for set observer
     */
    CTestSDKSFASTObserver* iObserver;
    };

#endif      // C_TESTSDKSEARCHFIELD_H

// End of File
