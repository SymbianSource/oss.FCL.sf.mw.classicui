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
* Description:  Test setting_pages_api
*
*/



#ifndef C_TESTSDKSETTINGPAGES_H
#define C_TESTSDKSETTINGPAGES_H

//  INCLUDES
#include <stiflogger.h>
#include <testscripterinternal.h>
#include <stiftestmodule.h>
#include <testclassassert.h>
#include <s32mem.h>
#include <f32file.h>
#include <bautils.h>


// MACROS
#define TEST_CLASS_VERSION_MAJOR 0
#define TEST_CLASS_VERSION_MINOR 0
#define TEST_CLASS_VERSION_BUILD 0

// Logging path
_LIT( KtestsdksettingpagesLogPath, "\\logs\\testframework\\testsdksettingpages\\" ); 
// Log file
_LIT( KtestsdksettingpagesLogFile, "testsdksettingpages.txt" ); 
_LIT( KtestsdksettingpagesLogFileWithTitle, "testsdksettingpages_[%S].txt" );

/**
*  Ctestsdksettingpages test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS( CTestSDKSettingPages ) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestSDKSettingPages* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestSDKSettingPages();

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
    CTestSDKSettingPages( CTestModuleIf& aTestModuleIf );

    /**
    * By default Symbian 2nd phase constructor is private.
    */
    void ConstructL();
    
    /**
     * Method used to log version of test class
     */
    void SendTestClassVersion();
    
private:
    /*
     * AknCheckBoxSettingPage.h
     */
        //CSelectableItem
    
    /**
     * TestSettingPagesCheckBoxCSelectableItemConstructorL test function for testing 
     * the CSelectableItem class's constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesCheckBoxCSelectableItemConstructorL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesCheckBoxCSelectableItemConstructLL test function for testing the 
     * CSelectableItem class's constructL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesCheckBoxCSelectableItemConstructLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesCheckBoxCSelectableItemSetSelectionStatusL test function for testing 
     * the SetSelectionStatus function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesCheckBoxCSelectableItemSetSelectionStatusL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesCheckBoxCSelectableItemSelectionStatusL test function for testing 
     * the SelectionStatus function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesCheckBoxCSelectableItemSelectionStatusL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesCheckBoxCSelectableItemItemTextL test function for testing the 
     * ItemText function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesCheckBoxCSelectableItemItemTextL( CStifItemParser& /*aItem*/ );
    
    //CSelectionItemList
    /**
     * TestSettingPagesCheckBoxCSelectionItemListConstructorL test function for testing the 
     * Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesCheckBoxCSelectionItemListConstructorL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesCheckBoxCSelectionItemListMdcaCountL test function for testing 
     * the MdcaCount function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesCheckBoxCSelectionItemListMdcaCountL( CStifItemParser& /*aItem*/ );

    /**
     * TestSettingPagesCheckBoxCSelectionItemListMdcaPointL test function for testing 
     * the MdcaPoint function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesCheckBoxCSelectionItemListMdcaPointL( CStifItemParser& /*aItem*/ );
    
    //CAknCheckBoxSettingPage
    /**
     * TestSettingpagesCheckBoxChkBoxSetPgConstructotL test function for testing the 
     * Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingpagesCheckBoxChkBoxSetPgConstructorL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingpagesCheckBoxChkBoxSetPgConstructorLL test function for testing 
     * the Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingpagesCheckBoxChkBoxSetPgConstructorLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingpagesCheckBoxChkBoxSetPgConstructL test function for testing the 
     * Construct function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingpagesCheckBoxChkBoxSetPgConstructL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingpagesCheckBoxChkBoxSetPgListBoxControlL test function for testing the 
     * ListBoxControl function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingpagesCheckBoxChkBoxSetPgListBoxControlL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesCheckBoxChkBoxSetPgSetSelectionItemArrayLL test function for 
     * testing the SetSelectionItemArrayL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesCheckBoxChkBoxSetPgSetSelectionItemArrayLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesCheckBoxChkBoxSetPgHandleListBoxEventLL test function for testing 
     * the HandleListBoxEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesCheckBoxChkBoxSetPgHandleListBoxEventLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesCheckBoxChkBoxSetPgHandlePointerEventLL test function for testing 
     * the HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesCheckBoxChkBoxSetPgHandlePointerEventLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesCheckBoxChkBoxSetPgHandleResourceChangeL test function for testing 
     * the HandleResourceChange function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesCheckBoxChkBoxSetPgHandleResourceChangeL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesCheckBoxChkBoxSetPgDestructorL test function for testing the 
     * Destructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesCheckBoxChkBoxSetPgDestructorL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesCheckBoxChkBoxSetPgUpdateSettingLL test function for testing the 
     * UpdateSettingL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesCheckBoxChkBoxSetPgUpdateSettingLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesCheckBoxChkBoxSetPgDynamicInitLL test function for testing the 
     * DynamicInitL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesCheckBoxChkBoxSetPgDynamicInitLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesCheckBoxChkBoxSetPgProcessCommandLL test function for testing the 
     * ProcessCommandL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesCheckBoxChkBoxSetPgProcessCommandLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesCheckBoxChkBoxSetPgSelectCurrentItemLL test function for testing the 
     * SelectCurrentItemL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesCheckBoxChkBoxSetPgSelectCurrentItemLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesCheckBoxChkBoxSetPgWriteInternalStateLL test function for testing 
     * the WriteInternalStateL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesCheckBoxChkBoxSetPgWriteInternalStateLL( CStifItemParser& /*aItem*/ );
    
    /*
     * AknDesCArrayDecorator.h
     */
    /**
     * TestSettingPagesArrayDecoratorConstructorL test function for testing the 
     * Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesArrayDecoratorConstructorL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesArrayDecoratorSetArrayL test function for testing the 
     * SetArray function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesArrayDecoratorSetArrayL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesArrayDecoratorSetDecorationTextL test function for testing the 
     * SetDecorationText function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesArrayDecoratorSetDecorationTextL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesArrayDecoratorSetActiveL test function for testing the SetActive 
     * function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesArrayDecoratorSetActiveL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesArrayDecoratorDecoratedIndexL test function for testing the 
     * DecoratedIndex function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesArrayDecoratorDecoratedIndexL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesArrayDecoratorMdcaCountL test function for testing the MdcaCount function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesArrayDecoratorMdcaCountL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesArrayDecoratorMdcaPointL test function for testing the 
     * MdcaPoint function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesArrayDecoratorMdcaPointL( CStifItemParser& aItem );
    
    /*
     * aknmfnesettingpage.h
     */
        //CAknMfneSettingPage
    /**
     * TestSettingPagesMfneHandlePointerEventLL test function for testing the 
     * HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesMfneHandlePointerEventLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesMfneDestructorL test function for testing the Destructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesMfneDestructorL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesMfneConstructorL test function for testing the Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesMfneConstructorL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesMfneConstructorLL test function for testing the ConstructorL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesMfneConstructorLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesMfneSizeChangedL test function for testing the SizeChanged function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesMfneSizeChangedL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesMfneDrawL test function for testing the Draw function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesMfneDrawL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesMfneMfneL test function for testing the Mfne function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesMfneMfneL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesMfneCheckAndSetDataValidityL test function for testing the 
     * CheckAndSetDataValidity function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesMfneCheckAndSetDataValidityL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesMfneHandleControlEventLL test function for testing the 
     * HandleControlEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesMfneHandleControlEventLL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesMfneConstructLL test function for testing the ConstructL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesMfneConstructLL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesMfneCountComponentControlsL test function for testing the 
     * CountComponentControls function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesMfneCountComponentControlsL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesMfneComponentControlL test function for testing the ComponentControl function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesMfneComponentControlL( CStifItemParser& aItem );
    
        //CAknDateSettingPage
    /**
     * TestSettingPagesMfneDateConstructorL test function for testing the Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesMfneDateConstructorL( CStifItemParser aItem );
    
    /**
     * TestSettingPagesMfneDateConstructorLL test function for testing the ConstructorL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesMfneDateConstructorLL( CStifItemParser aItem );
    
    /**
     * TestSettingPagesMfneDateConstructLL test function for testing the ConstructL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesMfneDateConstructLL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesMfneDateEditorL test function for testing the Editor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesMfneDateEditorL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesMfneDateHandlePointerEventLL test function for testing the 
     * HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesMfneDateHandlePointerEventLL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesMfneDateDestructorL test function for testing the Destructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesMfneDateDestructorL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesMfneDateUpdateSettingLL test function for testing the UpdateSettingL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesMfneDateUpdateSettingLL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesMfneDateAcceptSettingLL test function for testing the AcceptSettingL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesMfneDateAcceptSettingLL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesMfneDateRestoreOriginalSettingLL test function for testing the 
     * RestoreOriginalSettingL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesMfneDateRestoreOriginalSettingLL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesMfneDateWriteInternalStateLL test function for testing the 
     * WriteInternalStateL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesMfneDateWriteInternalStateLL( CStifItemParser& aItem );
    
        //CAknTimeSettingPage
    /**
     * TestSettingPagesMfneTimeConstructorL test function for testing the 
     * Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesMfneTimeConstructorL( CStifItemParser aItem );
    
    /**
     * TestSettingPagesMfneTimeConstructorLL test function for testing the 
     * ConstructorL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesMfneTimeConstructorLL( CStifItemParser aItem );
    
    /**
     * TestSettingPagesMfneTimeConstructLL test function for testing the 
     * ConstructL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesMfneTimeConstructLL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesMfneTimeEditorL test function for testing the Editor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesMfneTimeEditorL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesMfneTimeHandlePointerEventLL test function for testing 
     * the HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesMfneTimeHandlePointerEventLL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesMfneTimeDestructorL test function for testing the Destructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesMfneTimeDestructorL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesMfneTimeUpdateSettingLL test function for testing the 
     * UpdateSettingL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesMfneTimeUpdateSettingLL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesMfneTimeAcceptSettingLL test function for testing the 
     * AcceptSettingL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesMfneTimeAcceptSettingLL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesMfneTimeRestoreOriginalSettingLL test function for testing the 
     * RestoreOriginalSettingL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesMfneTimeRestoreOriginalSettingLL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesMfneTimeWriteInternalStateLL test function for testing the 
     * WriteInternalStateL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesMfneTimeWriteInternalStateLL( CStifItemParser& aItem );
    
        //CAknDurationSettingPage
    /**
     * TestSettingPagesMfneDurationConstructorL test function for testing the Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesMfneDurationConstructorL( CStifItemParser aItem );
    
    /**
     * TestSettingPagesMfneDurationConstructorLL test function for testing the 
     * ConstructorL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesMfneDurationConstructorLL( CStifItemParser aItem );
    
    /**
     * TestSettingPagesMfneDurationConstructLL test function for testing the ConstructL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesMfneDurationConstructLL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesMfneDurationDurationEditorL test function for testing the 
     * DurationEditor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesMfneDurationDurationEditorL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesMfneDurationHandlePointerEventLL test function for testing 
     * the HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesMfneDurationHandlePointerEventLL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesMfneDurationDestructorL test function for testing the Destructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesMfneDurationDestructorL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesMfneDurationUpdateSettingLL test function for testing the 
     * UpdateSettingL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesMfneDurationUpdateSettingLL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesMfneDurationAcceptSettingLL test function for testing the 
     * AcceptSettingL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesMfneDurationAcceptSettingLL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesMfneDurationRestoreOriginalSettingLL test function for testing the 
     * RestoreOriginalSettingL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesMfneDurationRestoreOriginalSettingLL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesMfneDurationWriteInternalStateLL test function for testing the 
     * WriteInternalStateL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesMfneDurationWriteInternalStateLL( CStifItemParser& aItem );
    
        //CAknTimeOffsetSettingPage
    /**
     * TestSettingPagesMfneTimeOffSetConstructorL test function for testing the Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesMfneTimeOffSetConstructorL( CStifItemParser aItem );
    
    /**
     * TestSettingPagesMfneTimeOffSetConstructorLL test function for testing the Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesMfneTimeOffSetConstructorLL( CStifItemParser aItem );
    
    /**
     * TestSettingPagesMfneTimeOffSetConstructLL test function for testing the ConstructL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesMfneTimeOffSetConstructLL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesMfneTimeOffSetTimeOffsetEditorL test function for testing the Editor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesMfneTimeOffSetTimeOffsetEditorL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesMfneTimeOffSetHandlePointerEventLL test function for testing the 
     * HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesMfneTimeOffSetHandlePointerEventLL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesMfneTimeOffSetDestructorL test function for testing the 
     * Destructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesMfneTimeOffSetDestructorL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesMfneTimeOffSetUpdateSettingLL test function for testing the 
     * UpdateSettingL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesMfneTimeOffSetUpdateSettingLL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesMfneTimeOffSetAcceptSettingLL test function for testing the 
     * AcceptSettingL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesMfneTimeOffSetAcceptSettingLL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesMfneTimeOffSetRestoreOriginalSettingLL test function for testing the 
     * RestoreOriginalSettingL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesMfneTimeOffSetRestoreOriginalSettingLL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesMfneTimeOffSetWriteInternalStateLL test function for testing the 
     * WriteInternalStateL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesMfneTimeOffSetWriteInternalStateLL( CStifItemParser& aItem );
    
        //CAknIpFieldSettingPage
    /**
     * TestSettingPagesMfneIpFieldConstructorL test function for testing the Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesMfneIpFieldConstructorL( CStifItemParser aItem );
    
    /**
     * TestSettingPagesMfneIpFieldConstructorLL test function for testing the ConstructorL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesMfneIpFieldConstructorLL( CStifItemParser aItem );
    
    /**
     * TestSettingPagesMfneIpFieldConstructLL test function for testing the ConstructL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesMfneIpFieldConstructLL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesMfneIpFieldTimeOffsetEditorL test function for testing the Editor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesMfneIpFieldTimeOffsetEditorL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesMfneIpFieldHandlePointerEventLL test function for testing the 
     * HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesMfneIpFieldHandlePointerEventLL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesMfneIpFieldDestructorL test function for testing the Destructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesMfneIpFieldDestructorL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesMfneIpFieldUpdateSettingLL test function for testing the 
     * UpdateSettingL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesMfneIpFieldUpdateSettingLL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesMfneIpFieldAcceptSettingLL test function for testing the AcceptSettingL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesMfneIpFieldAcceptSettingLL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesMfneIpFieldRestoreOriginalSettingLL test function for testing the 
     * RestoreOriginalSettingL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesMfneIpFieldRestoreOriginalSettingLL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesMfneIpFieldWriteInternalStateLL test function for testing the 
     * WriteInternalStateL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesMfneIpFieldWriteInternalStateLL( CStifItemParser& aItem );
    
    /*
     * aknpasswordsettingpage.h
     */
    /**
     * TestSettingPagesPasswordConstructorL test function for testing the Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesPasswordConstructorL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesPasswordConstructorLL test function for testing the Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesPasswordConstructorLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingpagesPasswordSetOldPasswordConfirmationResourceIdL test function for testing 
     * the SetOldPasswordConfirmationResourceId function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingpagesPasswordSetOldPasswordConfirmationResourceIdL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingpagesPasswordSetNewPasswordConfirmationResourceIdL test function for testing the 
     * SetNewPasswordConfirmationResourceId function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingpagesPasswordSetNewPasswordConfirmationResourceIdL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingpagesPasswordSetMatchingModeL test function for testing the SetMatchingMode function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingpagesPasswordSetMatchingModeL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingpagesPasswordMatchingModeL test function for testing the MatchingMode function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingpagesPasswordMatchingModeL( CStifItemParser& aItem );
    
    /**
     * TestSettingpagesPasswordSetMaxPasswordLengthL test function for testing the SetMaxPasswordLength function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingpagesPasswordSetMaxPasswordLengthL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingpagesPasswordMaxPasswordLengthL test function for testing the MaxPasswordLength function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingpagesPasswordMaxPasswordLengthL( CStifItemParser& aItem );
    
    /**
     * TestSettingpagesPasswordHandlePointerEventLL test function for testing the HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingpagesPasswordHandlePointerEventLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingpagesPasswordUpdateSettingLL test function for testing the UpdateSettingL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingpagesPasswordUpdateSettingLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingpagesPasswordAcceptSettingLL test function for testing the AcceptSettingL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingpagesPasswordAcceptSettingLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingpagesPasswordHandleControlEventLL test function for testing the HandleControlEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingpagesPasswordHandleControlEventLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingpagesPasswordPostDisplayInitLL test function for testing the PostDisplayInitL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingpagesPasswordPostDisplayInitLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingpagesPasswordPostDisplayCheckLL test function for testing the PostDisplayCheckL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingpagesPasswordPostDisplayCheckLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingpagesPasswordOkToExitLL test function for testing the OkToExitL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingpagesPasswordOkToExitLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingpagesPasswordSizeChangedL test function for testing the SizeChanged function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingpagesPasswordSizeChangedL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingpagesPasswordDrawL test function for testing the Draw function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingpagesPasswordDrawL( CStifItemParser& aItem );
    
    /**
     * TestSettingpagesPasswordUpdateTextLL test function for testing the UpdateTextL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingpagesPasswordUpdateTextLL( CStifItemParser& aItem );
    
    /**
     * TestSettingpagesPasswordExecuteOldPasswordConfirmationLL test function for testing the 
     * ExecuteOldPasswordConfirmationL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingpagesPasswordExecuteOldPasswordConfirmationLL( CStifItemParser& aItem );
    
    /**
     * TestSettingpagesPasswordExecuteNewPasswordConfirmationLL test function for testing the 
     * ExecuteNewPasswordConfirmationL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingpagesPasswordExecuteNewPasswordConfirmationLL( CStifItemParser& aItem );
    
    /**
     * TestSettingpagesPasswordComparePasswordsL test function for testing the ComparePasswords function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingpagesPasswordComparePasswordsL( CStifItemParser& aItem );
    
    /**
     * TestSettingpagesPasswordOldPasswordConfirmationResourceIdL test function for testing the 
     * OldPasswordConfirmationResourceId function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingpagesPasswordOldPasswordConfirmationResourceIdL( CStifItemParser& aItem );
    
    /**
     * TestSettingpagesPasswordNewPasswordConfirmationResourceIdL test function for testing the 
     * NewPasswordConfirmationResourceId function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingpagesPasswordNewPasswordConfirmationResourceIdL( CStifItemParser& aItem );
    
    /**
     * TestSettingpagesPasswordReadConfirmationResourceLL test function for testing the 
     * ReadConfirmationResourceL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingpagesPasswordReadConfirmationResourceLL( CStifItemParser& aItem );
    
    /**
     * TestSettingpagesPasswordDoPasswordConfirmationLL test function for testing the DoPasswordConfirmationL 
     * function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingpagesPasswordDoPasswordConfirmationLL( CStifItemParser& aItem );
    
    /**
     * TestSettingpagesPasswordNewPasswordL test function for testing the NewPassword function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingpagesPasswordNewPasswordL( CStifItemParser& aItem );
    
    /**
     * TestSettingpagesPasswordOldPasswordL test function for testing the OldPassword function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingpagesPasswordOldPasswordL( CStifItemParser& aItem );
    
    /**
     * TestSettingpagesPasswordWriteInternalStateLL test function for testing the WriteInternalStateL 
     * function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingpagesPasswordWriteInternalStateLL( CStifItemParser& aItem );
    
        //CAknAlphaPasswordSettingPage
    /**
     * TestSettingpagesPasswordAlphaConstructorL test function for testing the Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingpagesPasswordAlphaConstructorL( CStifItemParser& aItem );
    
    /**
     * TestSettingpagesPasswordAlphaConstructorLL test function for testing the Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingpagesPasswordAlphaConstructorLL( CStifItemParser& aItem );
    
    /**
     * TestSettingpagesPasswordAlphaConstructLL test function for testing the ConstructL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingpagesPasswordAlphaConstructLL( CStifItemParser& aItem );
    
    /**
     * TestSettingpagesPasswordAlphaAlphaPasswordEditorL test function for testing the Editor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingpagesPasswordAlphaAlphaPasswordEditorL( CStifItemParser& aItem );
    
    /**
     * TestSettingpagesPasswordAlphaHandlePointerEventLL test function for testing the HandlePointerEventL 
     * function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingpagesPasswordAlphaHandlePointerEventLL( CStifItemParser& aItem );
    
    /**
     * TestSettingpagesPasswordAlphaDestructorL test function for testing the Destructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingpagesPasswordAlphaDestructorL( CStifItemParser& aItem );
    
    /**
     * TestSettingpagesPasswordAlphaUpdateTextLL test function for testing the UpdateTextL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingpagesPasswordAlphaUpdateTextLL( CStifItemParser& aItem );
    
    /**
     * TestSettingpagesPasswordAlphaComparePasswordsL test function for testing the ComparePasswords function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingpagesPasswordAlphaComparePasswordsL( CStifItemParser& aItem );
    
    /**
     * TestSettingpagesPasswordAlphaWriteInternalStateLL test function for testing the WriteInternalStateL 
     * function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingpagesPasswordAlphaWriteInternalStateLL( CStifItemParser& aItem );
    
        //CAknNumericPasswordSettingPage
    /**
     * TestSettingpagesPasswordNumericConstructorL test function for testing the Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingpagesPasswordNumericConstructorL( CStifItemParser& aItem );
    
    /**
     * TestSettingpagesPasswordNumericConstructorLL test function for testing the Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingpagesPasswordNumericConstructorLL( CStifItemParser& aItem );
    
    /**
     * TestSettingpagesPasswordNumericConstructLL test function for testing the ConstructL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingpagesPasswordNumericConstructLL( CStifItemParser& aItem );
    
    /**
     * TestSettingpagesPasswordNumericNumericPasswordEditorL test function for testing the Editor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingpagesPasswordNumericNumericPasswordEditorL( CStifItemParser& aItem );
    
    /**
     * TestSettingpagesPasswordNumericHandlePointerEventLL test function for testing the HandlePointerEventL 
     * function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingpagesPasswordNumericHandlePointerEventLL( CStifItemParser& aItem );
    
    /**
     * TestSettingpagesPasswordNumericDestructorL test function for testing the Destructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingpagesPasswordNumericDestructorL( CStifItemParser& aItem );
    
    /**
     * TestSettingpagesPasswordNumericUpdateTextLL test function for testing the UpdateTextL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingpagesPasswordNumericUpdateTextLL( CStifItemParser& aItem );
    
    /**
     * TestSettingpagesPasswordNumericWriteInternalStateLL test function for testing the WriteInternalStateL 
     * function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingpagesPasswordNumericWriteInternalStateLL( CStifItemParser& aItem );

    /*
     * aknradiobuttonsettingpage.h
     */
    /**
     * TestSettingpagesRadioButtonConstructorL test function for testing the Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingpagesRadioButtonConstructorL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingpagesRadioButtonConstructorLL test function for testing the ConstructorL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingpagesRadioButtonConstructorLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingpagesRadioButtonConstructL test function for testing the ConstructL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingpagesRadioButtonConstructL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingpagesRadioButtonListBoxControlL test function for testing the ListBoxControl function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingpagesRadioButtonListBoxControlL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingpagesRadioButtonHandleListBoxEventLL test function for testing the HandleListBoxEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingpagesRadioButtonHandleListBoxEventLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingpagesRadioButtonSetItemArrayAndSelectionLL test function for testing the SetItemArrayAndSelectionL 
     * function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingpagesRadioButtonSetItemArrayAndSelectionLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingpagesRadioButtonHandlePointerEventLL test function for testing the HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingpagesRadioButtonHandlePointerEventLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingpagesRadioButtonHandleResourceChangeL test function for testing the HandleResourceChange function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingpagesRadioButtonHandleResourceChangeL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingpagesRadioButtonDestructorL test function for testing the Destructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingpagesRadioButtonDestructorL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingpagesRadioButtonUpdateSettingLL test function for testing the UpdateSettingL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingpagesRadioButtonUpdateSettingLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingpagesRadioButtonDynamicInitLL test function for testing the DynamicInitL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingpagesRadioButtonDynamicInitLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingpagesRadioButtonSelectCurrentItemLL test function for testing the SelectCurrentItemL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingpagesRadioButtonSelectCurrentItemLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingpagesRadioButtonWriteInternalStateLL test function for testing the WriteInternalStateL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingpagesRadioButtonWriteInternalStateLL( CStifItemParser& /*aItem*/ );
    
    /*
     * aknsettingitemlist.h
     */
        //CAknSettingItem
    /**
     * TestSettingPagesItemListConstructorL test function for testing the Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListConstructorL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesItemListDestructorL test function for testing the Destructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListDestructorL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesItemListConstructL test function for testing the Construct function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListConstructL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesItemListStoreLL test function for testing the StoreL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListStoreLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesItemListLoadLL test function for testing the LoadL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListLoadLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesItemListEditItemLL test function for testing the EditItemL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListEditItemLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesItemListUpdateListBoxTextLL test function for testing the UpdateListBoxTextL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListUpdateListBoxTextLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesItemListSettingNameL test function for testing the SettingName function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListSettingNameL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesItemListSettingNumberL test function for testing the SettingNumber function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListSettingNumberL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesItemListIsHiddenL test function for testing the IsHidden function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListIsHiddenL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesItemListIsNumberedStyleL test function for testing the IsNumberedStyle function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListIsNumberedStyleL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesItemListSetHiddenL test function for testing the SetHidden function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListSetHiddenL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesItemListSettingTextLL test function for testing the SettingTextL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListSettingTextLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesItemListListBoxTextL test function for testing the ListBoxText function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListListBoxTextL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesItemListIdentifierL test function for testing the Identifier function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListIdentifierL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesItemListHasIconL test function for testing the HasIcon function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListHasIconL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesItemListSetEmptyItemTextLL test function for testing the SetEmptyItemTextL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListSetEmptyItemTextLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesItemListSetCompulsoryIndTextLL test function for testing the SetCompulsoryIndTextL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListSetCompulsoryIndTextLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesItemListHandleSettingPageEventLL test function for testing the HandleSettingPageEventL 
     * function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListHandleSettingPageEventLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesItemListVisibleIndexL test function for testing the ListVisibleIndex function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListVisibleIndexL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesItemListSetSettingPageFlagsL test function for testing the SetSettingPageFlags function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListSetSettingPageFlagsL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesItemListSettingPageFlagsL test function for testing the SettingPageFlags function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListSettingPageFlagsL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListSetProtectionStateL test function for testing the SetProtectionState function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListSetProtectionStateL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesItemListProtectionStateL test function for testing the ProtectionState function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListProtectionStateL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListCompleteConstructionLL test function for testing the CompleteConstructionL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListCompleteConstructionLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesItemListCreateBitmapLL test function for testing the CreateBitmapL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListCreateBitmapLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesItemListSetSettingPageL test function for testing the SetSettingPage function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListSetSettingPageL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesItemListSettingPageL test function for testing the SettingPage function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListSettingPageL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListSetUpStandardSettingPageLL test function for testing the SetUpStandardSettingPageL 
     * function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListSetUpStandardSettingPageLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesItemListEmptyItemTextL test function for testing the EmptyItemText function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListEmptyItemTextL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListSettingPageResourceIdL test function for testing the SettingPageResourceId function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListSettingPageResourceIdL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesItemListSettingEditorResourceIdL test function for testing the SettingEditorResourceId function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListSettingEditorResourceIdL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesItemListAssociatedResourceIdL test function for testing the AssociatedResourceId function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListAssociatedResourceIdL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesItemListSetIconMaskL test function for testing the SetIconMask function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListSetIconMaskL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesItemListTextSetItemConstructorL test function for testing the SetItemConstructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
        //CAknTextSettingItem
    virtual TInt TestSettingPagesItemListTextSetItemConstructorL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesItemListTextSetItemDestructorL test function for testing the Destructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListTextSetItemDestructorL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesItemListTextSetItemStoreLL test function for testing the StoreL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListTextSetItemStoreLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesItemListTextSetItemLoadLL test function for testing the LoadL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListTextSetItemLoadLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesItemListTextSetItemSettingTextLL test function for testing the SettingTextL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListTextSetItemSettingTextLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesItemListTextSetItemEditItemLL test function for testing the EditItemL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListTextSetItemEditItemLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesItemListTextSetItemInternalTextPtrL test function for testing the InternalTextPtr function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListTextSetItemInternalTextPtrL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListTextSetItemExternalTextL test function for testing the ExternalText function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListTextSetItemExternalTextL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListTextSetItemSetExternalTextL test function for testing the SetExternalText function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListTextSetItemSetExternalTextL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListIntegerSetItemConstructorL test function for testing the Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
        //CAknIntegerSettingItem
    virtual TInt TestSettingPagesItemListIntegerSetItemConstructorL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesItemListIntegerSetItemDestructorL test function for testing the Destructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListIntegerSetItemDestructorL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesItemListIntegerSetItemStoreLL test function for testing the StoreL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListIntegerSetItemStoreLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesItemListIntegerSetItemLoadLL test function for testing the LoadL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListIntegerSetItemLoadLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesItemListIntegerSetItemSettingTextLL test function for testing the SettingTextL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListIntegerSetItemSettingTextLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesItemListIntegerSetItemCompleteConstructionLL test function for testing the 
     * CompleteConstructionL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListIntegerSetItemCompleteConstructionLL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListIntegerSetItemInternalValueRefL test function for testing the 
     * InternalValueRef function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListIntegerSetItemInternalValueRefL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListIntegerSetItemExternalValueRefL test function for testing the 
     * ExternalValueRef function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListIntegerSetItemExternalValueRefL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListIntegerSetItemSetExternalValueL test function for testing the 
     * SetExternalValue function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListIntegerSetItemSetExternalValueL( CStifItemParser& aItem );
    
        //CAknIntegerEdwinSettingItem
    /**
     * TestSettingPagesItemListIntegerEdwinConstructorL test function for testing the Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListIntegerEdwinConstructorL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesItemListIntegerEdwinEditItemLL test function for testing the EditItemL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListIntegerEdwinEditItemLL( CStifItemParser& /*aItem*/ );

        //CAknPasswordSettingItem
    /**
     * TestSettingPagesItemListPasswordConstructorL test function for testing the Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListPasswordConstructorL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesItemListPasswordSettingTextLL test function for testing the SettingTextL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListPasswordSettingTextLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesItemListPasswordEditItemLL test function for testing the EditItemL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListPasswordEditItemLL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListPasswordCompleteConstructionLL test function for testing the 
     * ConstructionL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListPasswordCompleteConstructionLL( CStifItemParser& aItem );
    
        //CAknVolumeSettingItem
    /**
     * TestSettingPagesItemListVolumeConstructorL test function for testing the Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListVolumeConstructorL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesItemListVolumeStoreLL test function for testing the StoreL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListVolumeStoreLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesItemListVolumeLoadLL test function for testing the LoadL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListVolumeLoadLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesItemListVolumeSettingTextLL test function for testing the SettingTextL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListVolumeSettingTextLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesItemListVolumeEditItemLL test function for testing the EditItemL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListVolumeEditItemLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesItemListVolumeInternalVolumeValueL test function for testing the 
     * InternalVolumeValue function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListVolumeInternalVolumeValueL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListVolumeCreateBitmapLL test function for testing the CreateBitmapL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListVolumeCreateBitmapLL( CStifItemParser& /*aItem*/ );
    
        //CAknSliderSettingItem
    /**
     * TestSettingpaegsItemListSliderConstructL test function for testing the ConstructL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingpaegsItemListSliderConstructL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesItemListSliderStoreLL test function for testing the StoreL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListSliderStoreLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesItemListSliderLoadLL test function for testing the LoadL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListSliderLoadLL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListSliderSettingTextLL test function for testing the SettingTextL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListSliderSettingTextLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesItemListSliderEditItemLL test function for testing the EditItemL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListSliderEditItemLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesItemListSliderCreateSettingPageLL test function for testing the CreateSettingPageL 
     * function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListSliderCreateSettingPageLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesItemListSliderCreateAndExecuteSettingPageLL test function for testing the 
     * CreateAndExecuteSettingPageL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListSliderCreateAndExecuteSettingPageLL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListSliderInternalSliderValueL test function for testing the 
     * InternalSliderValue function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListSliderInternalSliderValueL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListSliderCreateBitmapLL test function for testing the CreateBitmapL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListSliderCreateBitmapLL( CStifItemParser& /*aItem*/ );
    
        //CAknTimeOrDateSettingItem
    /**
     * TestSettingPagesItemListTimeOrDateConstructorL test function for testing the Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListTimeOrDateConstructorL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesItemListTimeOrDateDestructorL test function for testing the Destructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListTimeOrDateDestructorL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesItemListTimeOrDateCompleteConstructionLL test function for testing the 
     * CompleteConstructionL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListTimeOrDateCompleteConstructionLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesItemListTimeOrDateStoreLL test function for testing the StoreL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListTimeOrDateStoreLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesItemListTimeOrDateLoadLL test function for testing the LoadL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListTimeOrDateLoadLL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListTimeOrDateSettingTextLL test function for testing the SettingTextL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListTimeOrDateSettingTextLL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListTimeOrDateEditItemLL test function for testing the EditItemL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListTimeOrDateEditItemLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesItemListTimeOrDateSetTimeFormatStringLL test function for testing the 
     * SetTimeFormatStringL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListTimeOrDateSetTimeFormatStringLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesItemListTimeOrDateTimeFormatStringL test function for testing the 
     * TimeFormatString function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListTimeOrDateTimeFormatStringL( CStifItemParser& aItem );
    
        //CAknTimeOffsetSettingItem
    /**
     * TestSettingPagesItemListOffSetConstructorL test function for testing the Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListOffSetConstructorL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListOffSetDestructorL test function for testing the Destructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListOffSetDestructorL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListOffSetCompleteConstructionLL test function for testing the 
     * CompleteConstructionL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListOffSetCompleteConstructionLL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListOffSetStoreLL test function for testing the StoreL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListOffSetStoreLL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListOffSetLoadLL test function for testing the LoadL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListOffSetLoadLL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListOffSetSettingTextLL test function for testing the SettingTextL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListOffSetSettingTextLL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListOffSetEditItemLL test function for testing the EditItemL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListOffSetEditItemLL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListOffSetSetTimeFormatStringLL test function for testing the 
     * SetTimeFormatStringL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListOffSetSetTimeFormatStringLL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListOffSetTimeFormatStringL test function for testing the TimeFormatString 
     * function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListOffSetTimeFormatStringL( CStifItemParser& aItem );
    
        //CAknIpFieldSettingItem
    /**
     * TestSettingPagesItemListIpFieldConstructorL test function for testing the Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListIpFieldConstructorL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListIpFieldDestructorL test function for testing the Destructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListIpFieldDestructorL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListIpFieldCompleteConstructionLL test function for testing the 
     * CompleteConstructionL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListIpFieldCompleteConstructionLL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListIpFieldStoreLL test function for testing the StoreL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListIpFieldStoreLL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListIpFieldLoadLL test function for testing the LoadL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListIpFieldLoadLL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListIpFieldSettingTextLL test function for testing the SettingTextL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListIpFieldSettingTextLL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListIpFieldEditItemLL test function for testing the EditItemL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListIpFieldEditItemLL( CStifItemParser& aItem );
    
        //CAknEnumeratedItemBase
    /**
     * TestSettingPagesItemListEnumeratedIBConstructorL test function for testing the Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListEnumeratedIBConstructorL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListEnumeratedIBDestructorL test function for testing the Destructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListEnumeratedIBDestructorL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListEnumeratedIBEnumerationValueL test function for testing the 
     * EnumerationValue function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListEnumeratedIBEnumerationValueL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListEnumeratedIBSetEnumerationValueL test function for testing the 
     * SetEnumerationValue function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListEnumeratedIBSetEnumerationValueL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListEnumeratedIBValueL test function for testing the Value function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListEnumeratedIBValueL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListEnumeratedIBSetValueL test function for testing the SetValue function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListEnumeratedIBSetValueL( CStifItemParser& aItem );
    
        //CAknEnumeratedItem
    /**
     * TestSettingPagesItemListEMTDItemConstructorL test function for testing the Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListEMTDItemConstructorL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListEMTDItemDestructorL test function for testing the Destructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListEMTDItemDestructorL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListEMTDItemValueL test function for testing the Value function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListEMTDItemValueL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListEMTDItemSetValueL test function for testing the SetValue function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListEMTDItemSetValueL( CStifItemParser& aItem );
    
        //CAknEnumeratedTextSettingItem
    /**
     * TestSettingPagesItemListEnuredTxtConstructorL test function for testing the Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListEnuredTxtConstructorL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListEnuredTxtDestructorL test function for testing the Destructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListEnuredTxtDestructorL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListEnuredTxtCompleteConstructionLL test function for testing the 
     * CompleteConstructionL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListEnuredTxtCompleteConstructionLL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListEnuredTxtEnuredTxtArrayL test function for testing the EnuredTxtArray function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListEnuredTxtEnuredTxtArrayL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListEnuredTxtPoppedUpTextArrayL test function for testing the 
     * PoppedUpTextArray function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListEnuredTxtPoppedUpTextArrayL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListEnuredTxtSetEnuredTxtArraysL test function for testing the 
     * SetEnuredTxtArrays function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListEnuredTxtSetEnuredTxtArraysL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListEnuredTxtHandleTextArrayUpdateLL test function for testing the 
     * HandleTextArrayUpdateL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListEnuredTxtHandleTextArrayUpdateLL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListEnuredTxtNumberOfItemsL test function for testing the NumberOfItems function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListEnuredTxtNumberOfItemsL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListEnuredTxtIndexFromValueL test function for testing the IndexFromValue function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListEnuredTxtIndexFromValueL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListEnuredTxtSetSettingPageTextLL test function for testing the 
     * SetSettingPageTextL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListEnuredTxtSetSettingPageTextLL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListEnuredTxtSettingPageTextArrayL test function for testing the 
     * SettingPageTextArray function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListEnuredTxtSettingPageTextArrayL( CStifItemParser& aItem );
    
        //CAknEnumeratedTextPopupSettingItem
    /**
     * TestSettingPagesItemListEnurtdTxtPopConstructorL test function for testing the Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListEnurtdTxtPopConstructorL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListEnurtdTxtPopDestructorL test function for testing the Destructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListEnurtdTxtPopDestructorL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListEnurtdTxtPopStoreLL test function for testing the StoreL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListEnurtdTxtPopStoreLL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListEnurtdTxtPopLoadLL test function for testing the LoadL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListEnurtdTxtPopLoadLL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListEnurtdTxtPopSettingTextLL test function for testing the SettingTextL 
     * function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListEnurtdTxtPopSettingTextLL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListEnurtdTxtPopEditItemLL test function for testing the EditItemL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListEnurtdTxtPopEditItemLL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListEnurtdTxtPopEnumeratedTextArrayL test function for testing the 
     * EnumeratedTextArray function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListEnurtdTxtPopEnumeratedTextArrayL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListEnurtdTxtPopPoppedUpTextArrayL test function for testing the 
     * PoppedUpTextArray function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListEnurtdTxtPopPoppedUpTextArrayL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListEnurtdTxtPopCreateSettingPageLL test function for testing the 
     * CreateSettingPageL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListEnurtdTxtPopCreateSettingPageLL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListEnurtdTxtPopCreateAndExecuteSettingPageLL test function for testing the 
     * CreateAndExecuteSettingPageL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListEnurtdTxtPopCreateAndExecuteSettingPageLL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListEnurtdTxtPopCompleteConstructionLL test function for testing the 
     * CompleteConstructionL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListEnurtdTxtPopCompleteConstructionLL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListEnurtdTxtPopSetExternalValueL test function for testing the SetExternalValue 
     * function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListEnurtdTxtPopSetExternalValueL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListEnurtdTxtPopSetInternalValueL test function for testing the SetInternalValue 
     * function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListEnurtdTxtPopSetInternalValueL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListEnurtdTxtPopSetSelectedIndexL test function for testing the SetSelectedIndex 
     * function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListEnurtdTxtPopSetSelectedIndexL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListEnurtdTxtPopIndexFromValueL test function for testing the IndexFromValue function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListEnurtdTxtPopIndexFromValueL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListEnurtdTxtPopExternalValueL test function for testing the ExternalValue function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListEnurtdTxtPopExternalValueL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListEnurtdTxtPopInternalValueL test function for testing the 
     * InternalValue function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListEnurtdTxtPopInternalValueL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListEnurtdTxtPopQueryValueL test function for testing the QueryValue function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListEnurtdTxtPopQueryValueL( CStifItemParser& aItem );
    
        //CAknBinaryPopupSettingItem
    /**
     * TestSettingPagesItemListBinaryPopConstructorL test function for testing the Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListBinaryPopConstructorL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListBinaryPopStoreLL test function for testing the StoreL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListBinaryPopStoreLL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListBinaryPopLoadLL test function for testing the LoadL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListBinaryPopLoadLL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListBinaryPopEditItemLL test function for testing the EditItemL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListBinaryPopEditItemLL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListBinaryPopCompleteConstructionLL test function for testing the 
     * CompleteConstructionL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListBinaryPopCompleteConstructionLL( CStifItemParser& aItem );
    
        //CAknBigSettingItemBase
    /**
     * TestSettingPagesItemListBigSIBConstructorL test function for testing the Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListBigSIBConstructorL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListBigSIBSettingTextLL test function for testing the SettingTextL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListBigSIBSettingTextLL( CStifItemParser& aItem );
    
        //CAknSettingItemArray
    /**
     * TestSettingPagesItemListItemArrayConstructorL test function for testing the Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListItemArrayConstructorL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListItemArrayDestructorL test function for testing the Destructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListItemArrayDestructorL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListItemArrayMdcaCountL test function for testing the MdcaCount function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListItemArrayMdcaCountL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListItemArrayMdcaPointL test function for testing the MdcaPoint function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListItemArrayMdcaPointL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListItemArrayItemIndexFromVisibleIndexL test function for testing the 
     * IndexFromVisibleIndex function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListItemArrayItemIndexFromVisibleIndexL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListItemArrayRecalculateVisibleIndicesLL test function for testing the 
     * RecalculateVisibleIndicesL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListItemArrayRecalculateVisibleIndicesLL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListItemArraySetInitialOrdinalL test function for testing the SetInitialOrdinal function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListItemArraySetInitialOrdinalL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListItemArraySetFlagsL test function for testing the SetFlags function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListItemArraySetFlagsL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListItemArraySetVisibleCountL test function for testing the 
     * SetVisibleCount function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListItemArraySetVisibleCountL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListItemArrayVisibleCountL test function for testing the VisibleCount function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListItemArrayVisibleCountL( CStifItemParser& aItem );
    
        //CAknSettingItemList
    /**
     * TestSettingPagesItemListItemListConstructorL test function for testing the Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListItemListConstructorL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListItemListDestructorL test function for testing the Destructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListItemListDestructorL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListItemListConstructFromResourceLIdL test function for testing the 
     * ConstructFromResourceLId function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListItemListConstructFromResourceLIdL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListItemListConstructFromResourceLL test function for testing the 
     * ConstructFromResourceL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListItemListConstructFromResourceLL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListItemListCountComponentControlsL test function for testing the 
     * CountComponentControls function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListItemListCountComponentControlsL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListItemListComponentControlL test function for testing the ComponentControl function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListItemListComponentControlL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListItemListOfferKeyEventLL test function for testing the OfferKeyEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListItemListOfferKeyEventLL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListItemListFocusChangedL test function for testing the FocusChanged function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListItemListFocusChangedL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListItemListHandleResourceChangeL test function for testing the 
     * HandleResourceChange function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListItemListHandleResourceChangeL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListItemListHandleListBoxEventLL test function for testing the 
     * HandleListBoxEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListItemListHandleListBoxEventLL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListItemListEditItemLL test function for testing the EditItemL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListItemListEditItemLL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListItemListLoadSettingsLL test function for testing the LoadSettingsL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListItemListLoadSettingsLL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListItemListStoreSettingsLL test function for testing the StoreSettingsL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListItemListStoreSettingsLL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListItemListSetIncludeHiddenInOrdinalL test function for testing the 
     * SetIncludeHiddenInOrdinal function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListItemListSetIncludeHiddenInOrdinalL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListItemListIsNumberedStyleL test function for testing the IsNumberedStyle function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListItemListIsNumberedStyleL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListItemListListBoxL test function for testing the ListBox function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListItemListListBoxL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListItemListSettingItemArrayL test function for testing the SettingItemArray function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListItemListSettingItemArrayL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListItemListHandleChangeInItemArrayOrVisibilityLL test function for testing 
     * the HandleChangeInItemArrayOrVisibilityL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListItemListHandleChangeInItemArrayOrVisibilityLL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListItemListHandlePointerEventLL test function for testing the 
     * HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListItemListHandlePointerEventLL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesItemListItemListCreateSettingItemLL test function for testing the 
     * CreateSettingItemL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesItemListItemListCreateSettingItemLL( CStifItemParser& aItem );
    
    /*
     * aknsettingpage.h
     */
    /**
     * TestSettingPagesSetPageConstructorL test function for testing the Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesSetPageConstructorL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesSetPageConstructorLL test function for testing the ConstructorL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesSetPageConstructorLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesSetPageDestructorL test function for testing the Destructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesSetPageDestructorL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesSetPageExecuteLDL test function for testing the ExecuteLD function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesSetPageExecuteLDL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesSetPageConstructL test function for testing the Construct function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesSetPageConstructL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesSetPageEditorControlL test function for testing the EditorControl function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesSetPageEditorControlL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesSetPageSettingIdL test function for testing the SettingId function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesSetPageSettingIdL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesSetPageSetSettingIdL test function for testing the SetSettingId function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesSetPageSetSettingIdL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesSetPageSetSettingNumberLL test function for testing the SetSettingNumberL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesSetPageSetSettingNumberLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesSetPageSetSettingTextLL test function for testing the SetSettingTextL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesSetPageSetSettingTextLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesSetPageSetSettingPageObserverL test function for testing the 
     * SetSettingPageObserver function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesSetPageSetSettingPageObserverL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesSetPageSettingNumberL test function for testing the SettingNumber function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesSetPageSettingNumberL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesSetPageIsNumberedL test function for testing the IsNumbered function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesSetPageIsNumberedL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesSetPageSetNumberedL test function for testing the SetNumbered function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesSetPageSetNumberedL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesSetPageGetEditorResourceInfoLL test function for testing the 
     * GetEditorResourceInfoL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesSetPageGetEditorResourceInfoLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesSetPageSetEditStateL test function for testing the SetEditState function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesSetPageSetEditStateL( CStifItemParser& /*aItem*/);
    
    /**
     * TestSettingPagesSetPageIsEditableL test function for testing the IsEditable function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesSetPageIsEditableL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesSetPageSizeChangedL test function for testing the SizeChanged function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesSetPageSizeChangedL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesSetPageFocusChangedL test function for testing the FocusChanged function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesSetPageFocusChangedL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesSetPageProcessCommandLL test function for testing the ProcessCommandL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesSetPageProcessCommandLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesSetPageHandleControlEventLL test function for testing the 
     * HandleControlEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesSetPageHandleControlEventLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesSetpageOkToExitLL test function for testing the OkToExitL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesSetpageOkToExitLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesSetPageDynamicInitLL test function for testing the DynamicInitL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesSetPageDynamicInitLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesSetPageUpdateSettingLL test function for testing the UpdateSettingL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesSetPageUpdateSettingLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesSetPageAcceptSettingLL test function for testing the AcceptSettingL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesSetPageAcceptSettingLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesSetPageRestoreOriginalSettingLL test function for testing the 
     * RestoreOriginalSettingL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesSetPageRestoreOriginalSettingLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesSetPageDisplayMenuLL test function for testing the DisplayMenuL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesSetPageDisplayMenuLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesSetPageHideMenuL test function for testing the HideMenu function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesSetPageHideMenuL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesSetPageSelectCurrentItemLL test function for testing the SelectCurrentItemL 
     * function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesSetPageSelectCurrentItemLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesSetPageBaseConstructLL test function for testing the BaseConstructL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesSetPageBaseConstructLL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesSetPageDismissLL test function for testing the DismissL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesSetPageDismissLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesSetPageMenuShowingL test function for testing the MenuShowing function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesSetPageMenuShowingL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesSetPageConstructFromResourceLIdL test function for testing the 
     * ConstructFromResourceLId function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesSetPageConstructFromResourceLIdL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesSetPageConstructFromResourceLReaderL test function for testing the 
     * ConstructFromResourceLReader function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesSetPageConstructFromResourceLReaderL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesSetpageAttemptExitLL test function for testing the AttemptExitL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesSetpageAttemptExitLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesSetPageWaitingL test function for testing the Waiting function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesSetPageWaitingL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesSetPageCbaL test function for testing the Cba function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesSetPageCbaL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesSetPageDefaultCbaResourceIdL test function for testing the 
     * CbaResourceId function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesSetPageDefaultCbaResourceIdL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesSetPageOfferKeyEventLL test function for testing the OfferKeyEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesSetPageOfferKeyEventLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesSetPageStandardSettingPageLayoutL test function for testing the 
     * StandardSettingPageLayout function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesSetPageStandardSettingPageLayoutL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesSetPageIsBaseConstructedL test function for testing the IsBaseConstructed function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesSetPageIsBaseConstructedL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesSetPageSettingPageResourceIdL test function for testing the 
     * SettingPageResourceId function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesSetPageSettingPageResourceIdL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesSetPageBaseDrawL test function for testing the BaseDraw function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesSetPageBaseDrawL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesSetPageResetFlagsL test function for testing the ResetFlags function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesSetPageResetFlagsL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesSetPagePostDisplayCheckLL test function for testing the DisplayCheckL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesSetPagePostDisplayCheckLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesSetPageUpdateCbaLL test function for testing the UpdateCbaL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesSetPageUpdateCbaLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesSetPageDataValidityL test function for testing the DataValidity function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesSetPageDataValidityL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesSetPageSetDataValidityL test function for testing the SetDataValidity function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesSetPageSetDataValidityL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesSetPageCheckAndSetDataValidityL test function for testing the 
     * CheckAndSetDataValidity function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesSetPageCheckAndSetDataValidityL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesSetPageSetEmphasisL test function for testing the SetEmphasis function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesSetPageSetEmphasisL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesSetPageDynInitMenuPaneLL test function for testing the DynInitMenuPaneL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesSetPageDynInitMenuPaneLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesSetPageHandleResourceChangeL test function for testing the 
     * HandleResourceChange function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesSetPageHandleResourceChangeL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesSetPageCountComponentControlsL test function for testing the 
     * CountComponentControls function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesSetPageCountComponentControlsL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesSetPageComponentControlL test function for testing the ComponentControl function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesSetPageComponentControlL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesSetPageHandlePointerEventLL test function for testing the 
     * HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesSetPageHandlePointerEventLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesSetPageInputCapabilitiesL test function for testing the InputCapabilities function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesSetPageInputCapabilitiesL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesSetPageInvalidDataCbaResourceIdL test function for testing the 
     * InvalidDataCbaResourceId function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesSetPageInvalidDataCbaResourceIdL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesSetPageMopSupplyObjectL test function for testing the MopSupplyObject function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesSetPageMopSupplyObjectL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesSetPageWriteInternalStateLL test function for testing the 
     * WriteInternalStateL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesSetPageWriteInternalStateLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesSetPageTextLabelL test function for testing the TextLabel function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesSetPageTextLabelL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesSetPageShadowTextL test function for testing the ShadowText function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesSetPageShadowTextL( CStifItemParser& /*aItem*/ );
    
    /*
     * aknslidersettingpage.h
     */
    /**
     * TestSettingPagesSliderConstructorL test function for testing the Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesSliderConstructorL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesSliderConstructorLL test function for testing the ConstructorL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesSliderConstructorLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesSliderSliderControlL test function for testing the SliderControl function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesSliderSliderControlL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesSliderConstructLL test function for testing the ConstructL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesSliderConstructLL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesSliderHandlePointerEventLL test function for testing the 
     * HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesSliderHandlePointerEventLL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesSliderSizeChangedL test function for testing the SizeChanged function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesSliderSizeChangedL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesSliderDrawL test function for testing the Draw function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesSliderDrawL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesSliderWriteInternalStateLL test function for testing the 
     * WriteInternalStateL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesSliderWriteInternalStateLL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesSliderDestructL test function for testing the Destruct function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesSliderDestructL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesSliderUpdateSettingLL test function for testing the UpdateSettingL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesSliderUpdateSettingLL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesSliderAcceptSettingLL test function for testing the AcceptSettingL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesSliderAcceptSettingLL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesSliderRestoreOriginalSettingLL test function for testing the 
     * RestoreOriginalSettingL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesSliderRestoreOriginalSettingLL( CStifItemParser& aItem );

    /*
     * akntextsettingpage.h
     */
        //CAknEdwinSettingPage
    /**
     * TestSettingPagesTextEdwinTextControlL test function for testing the TextControl function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesTextEdwinTextControlL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesTextEdwinHandlePointerEventLL test function for testing the 
     * HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesTextEdwinHandlePointerEventLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesTextEdwinConstructorL test function for testing the Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesTextEdwinConstructorL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesTextEdwinConstructorLL test function for testing the ConstructorL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesTextEdwinConstructorLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesTextEdwinSizeChangedL test function for testing the SizeChanged function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesTextEdwinSizeChangedL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesTextEdwinDrawL test function for testing the Draw function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesTextEdwinDrawL( CStifItemParser& /*aItem*/ );
    
        //CAknTextSettingPage
    /**
     * TestSettingPagesTextTextConstructorL test function for testing the Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesTextTextConstructorL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesTextTextConstructorLL test function for testing the ConstructorL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesTextTextConstructorLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesTextTextConstructLL test function for testing the ConstructL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesTextTextConstructLL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesTextTextHandlePointerEventL test function for testing the 
     * HandlePointerEvent function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesTextTextHandlePointerEventL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesTextTextDestructorL test function for testing the Destructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesTextTextDestructorL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesTextTextDynamicInitLL test function for testing the DynamicInitL 
     * function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesTextTextDynamicInitLL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesTextTextUpdateSettingLL test function for testing the UpdateSettingL 
     * function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesTextTextUpdateSettingLL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesTextTextAcceptSettingLL test function for testing the AcceptSettingL 
     * function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesTextTextAcceptSettingLL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesTextTextRestoreOriginalSettingLL test function for testing 
     * the RestoreOriginalSettingL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesTextTextRestoreOriginalSettingLL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesTextTextHandleControlEventLL test function for testing the 
     * HandleControlEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesTextTextHandleControlEventLL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesTextTextCheckAndSetDataValidityL test function for testing the 
     * CheckAndSetDataValidity function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesTextTextCheckAndSetDataValidityL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesTextTextUpdateTextLL test function for testing the UpdateTextL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesTextTextUpdateTextLL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesTextTextUpdateCbaLL test function for testing the UpdateCbaL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesTextTextUpdateCbaLL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesTextTextOkToExitLL test function for testing the OkToExitL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesTextTextOkToExitLL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesTextTextOfferKeyEventLL test function for testing the 
     * OfferKeyEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesTextTextOfferKeyEventLL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesTextTextSizeChangedL test function for testing the SizeChanged function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesTextTextSizeChangedL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesTextTextWriteInternalStateLL test function for testing the 
     * WriteInternalStateL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesTextTextWriteInternalStateLL( CStifItemParser& aItem );
    
    
    //CAknIntegerSettingPage
    /**
     * TestSettingPagesTextIntegerConstructorL test function for testing the Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesTextIntegerConstructorL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesTextIntegerConstructorLL test function for testing the ConstructorL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesTextIntegerConstructorLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesTextIntegerConstructLL test function for testing the ConstructL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesTextIntegerConstructLL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesTextIntegerIntegerEditorControlL test function for testing the 
     * EditorControl function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesTextIntegerIntegerEditorControlL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesTextIntegerHandlePointerEventLL test function for testing the 
     * HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesTextIntegerHandlePointerEventLL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesTextIntegerDynamicInitLL test function for testing the DynamicInitL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesTextIntegerDynamicInitLL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesTextIntegerUpdateSettingLL test function for testing the UpdateSettingL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesTextIntegerUpdateSettingLL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesTextIntegerRestoreOriginalSettingLL test function for testing the 
     * RestoreOriginalSettingL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesTextIntegerRestoreOriginalSettingLL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesTextIntegerCheckAndSetDataValidityL test function for testing the 
     * CheckAndSetDataValidity function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesTextIntegerCheckAndSetDataValidityL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesTextIntegerUpdateCbaLL test function for testing the UpdateCbaL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesTextIntegerUpdateCbaLL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesTextIntegerHandleControlEventLL test function for testing the 
     * HandleControlEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesTextIntegerHandleControlEventLL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesTextIntegerSizeChangedL test function for testing the SizeChanged function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesTextIntegerSizeChangedL( CStifItemParser& aItem );
    
    /**
     * TestSettingPagesTextIntegerWriteInternalStateLL test function for testing the 
     * WriteInternalStateL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesTextIntegerWriteInternalStateLL( CStifItemParser& aItem );

    /*
     * aknvolumesettingpage.h
     */
    /**
     * TestSettingPagesVolumeConstructorL test function for testing the Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesVolumeConstructorL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesVolumeConstructorLL test function for testing the Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesVolumeConstructorLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesVolumeHandlePointerEventLL test function for testing the 
     * HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesVolumeHandlePointerEventLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesVolumeDestructorL test function for testing the Destructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesVolumeDestructorL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesVolumeConstructLL test function for testing the ConstructL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesVolumeConstructLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesVolumeVolumeControlL test function for testing the VolumeControl function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesVolumeVolumeControlL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesVolumeSizeChangedL test function for testing the SizeChanged 
     * function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesVolumeSizeChangedL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesVolumeDrawL test function for testing the Draw function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesVolumeDrawL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesVolumeWriteInternalStateLL test function for testing the 
     * WriteInternalStateL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesVolumeWriteInternalStateLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesVolumeUpdateSettingLL test function for testing the UpdateSettingL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesVolumeUpdateSettingLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesVolumeAcceptSettingLL test function for testing the AcceptSettingL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesVolumeAcceptSettingLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestSettingPagesVolumeRestoreOriginalSettingLL test function for testing 
     * the RestoreOriginalSettingL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestSettingPagesVolumeRestoreOriginalSettingLL( CStifItemParser& /*aItem*/ );
    
    
private:    // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;
    
    // Resource file offset
    TInt iOffset;
    };

#endif/*C_TESTSDKSETTINGPAGES_H*/

// End of File


