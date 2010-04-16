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
* Description:  test eikspmod.h eikspane.h
*
*/



#ifndef C_TESTSDKSTATUSPANE_H
#define C_TESTSDKSTATUSPANE_H

//  INCLUDES
#include <stiflogger.h>
#include <testscripterinternal.h>
#include <stiftestmodule.h>
#include <testclassassert.h>
#include <eikenv.h>

// MACROS
#define TEST_CLASS_VERSION_MAJOR 0
#define TEST_CLASS_VERSION_MINOR 0
#define TEST_CLASS_VERSION_BUILD 0

// Logging path
_LIT( KtestsdkstatuspaneLogPath, "\\logs\\testframework\\testsdkstatuspane\\" ); 
// Log file
_LIT( KtestsdkstatuspaneLogFile, "testsdkstatuspane.txt" ); 
_LIT( KtestsdkstatuspaneLogFileWithTitle, "testsdkstatuspane_[%S].txt" );

/**
*  CTestSDKStatusPane test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS( CTestSDKStatusPane ) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestSDKStatusPane* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestSDKStatusPane();

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
    CTestSDKStatusPane( CTestModuleIf& aTestModuleIf );

    /**
    * By default Symbian 2nd phase constructor is private.
    */
    void ConstructL();
    
    /**
     * Method used to log version of test class
     */
    void SendTestClassVersion();

private: // Test eikspane.h
/*                            class CEikStatusPaneBase                         */
    /**
    * TestPaneBaseDeconstructorL test method for testing the destructor method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestPaneBaseDeconstructorL( CStifItemParser& aItem );

    /**
    * TestPaneBaseCurrent test method for testing the Current method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestPaneBaseCurrentL( CStifItemParser& aItem );

    /**
    * TestPaneBaseSetObserverL test method for testing the SetObserver method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestPaneBaseSetObserverL( CStifItemParser& aItem );

    /**
    * TestPaneBaseReduceRect test method for testing the ReduceRect method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestPaneBaseReduceRectL( CStifItemParser& aItem );

    /**
    * TestPaneBaseGetShapeL test method for testing the GetShapeL method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestPaneBaseGetShapeL( CStifItemParser& aItem );

    /**
    * TestPaneBaseSwitchLayoutL test method for testing the SwitchLayoutL method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestPaneBaseSwitchLayoutL( CStifItemParser& aItem );

    /**
    * TestPaneBaseMakeVisibleL test method for testing the MakeVisible method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestPaneBaseMakeVisibleL( CStifItemParser& aItem );

    /**
    * TestPaneBaseSetDimmedL test method for testing the SetDimmed method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestPaneBaseSetDimmedL( CStifItemParser& aItem );

    /**
    * TestPaneBaseSetFadedL test method for testing the destructor SetFaded
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestPaneBaseSetFadedL( CStifItemParser& aItem );

    /**
    * TestPaneBaseHandleResourceChangeL test method for testing the HandleResourceChange method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestPaneBaseHandleResourceChangeL( CStifItemParser& aItem );

    /**
    * TestPaneBaseOkToChangeStatusPaneNowL test method for testing the OkToChangeStatusPaneNow method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestPaneBaseOkToChangeStatusPaneNowL( CStifItemParser& aItem );

    /**
    * TestPaneBaseSetFlagsL test method for testing the SetFlags method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestPaneBaseSetFlagsL( CStifItemParser& aItem );

    /**
    * TestPaneBaseFlagsL test method for testing the Flags method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestPaneBaseFlagsL( CStifItemParser& aItem );

    /**
    * TestPaneBaseIsVisibleL test method for testing the IsVisible method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestPaneBaseIsVisibleL( CStifItemParser& aItem );

    /**
    * TestPaneBaseIsDimmedL test method for testing the IsDimmed method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestPaneBaseIsDimmedL( CStifItemParser& aItem );

    /**
    * TestPaneBaseIsFadedL test method for testing the IsFaded method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestPaneBaseIsFadedL( CStifItemParser& aItem );

    /**
    * TestPaneBasePaneCapabilitiesL test method for testing the PaneCapabilities method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestPaneBasePaneCapabilitiesL( CStifItemParser& aItem );

    /**
    * TestPaneBasePaneRectL test method for testing the PaneRectL method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestPaneBasePaneRectL( CStifItemParser& aItem );

    /**
    * TestPaneBaseControlL test method for testing the ControlL method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestPaneBaseControlL( CStifItemParser& aItem );

    /**
    * TestPaneBaseSwapControlL test method for testing the SwapControlL method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestPaneBaseSwapControlL( CStifItemParser& aItem );

    /**
    * TestPaneBaseContainerControlL test method for testing the ContainerControlL method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestPaneBaseContainerControlL( CStifItemParser& aItem );

    /**
    * TestPaneBaseWindowGroupL test method for testing the WindowGroup method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestPaneBaseWindowGroupL( CStifItemParser& aItem );

    /**
    * TestPaneBaseDrawNowL test method for testing the DrawNow method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestPaneBaseDrawNowL( CStifItemParser& aItem );

    /**
    * TestPaneBaseCurrentLayoutResIdL test method for testing the CurrentLayoutResId method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestPaneBaseCurrentLayoutResIdL( CStifItemParser& aItem );

    /**
    * TestPaneBaseCEikStatusPaneBaseL test method for testing the CEikStatusPaneBase method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestPaneBaseCEikStatusPaneBaseL( CStifItemParser& aItem );

    /**
    * TestPaneBaseBaseConstructL test method for testing the BaseConstructL method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestPaneBaseBaseConstructL( CStifItemParser& aItem );

    /**
    * TestPaneBaseRectL test method for testing the Rect method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestPaneBaseRectL( CStifItemParser& aItem );

    /**
    * TestPaneBaseDisableClearerL test method for testing the DisableClearer method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestPaneBaseDisableClearerL( CStifItemParser& aItem );

    /**
    * TestPaneBaseCommonPrepareForAppExitL test method for testing the CommonPrepareForAppExit method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestPaneBaseCommonPrepareForAppExitL( CStifItemParser& aItem );

    /**
    * TestPaneBaseTPaneCapIsPresentL test method for testing the IsPresent method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestPaneBaseTPaneCapIsPresentL( CStifItemParser& aItem );

    /**
    * TestPaneBaseTPaneCapIsAppOwnedL test method for testing the IsAppOwned method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestPaneBaseTPaneCapIsAppOwnedL( CStifItemParser& aItem );

    /**
    * TestPaneBaseTPaneCapIsInCurrentLayoutL test method for testing the IsInCurrentLayout method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestPaneBaseTPaneCapIsInCurrentLayoutL( CStifItemParser& aItem );

    /**
    * TestPaneNewL test method for testing the NewL method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestPaneNewL( CStifItemParser& aItem );

    /**
    * TestPaneDeconstructorL test method for testing the destructor method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestPaneDeconstructorL( CStifItemParser& aItem );

    /**
    * TestPaneApplyCurrentSettingsL test method for testing the ApplyCurrentSettingsL method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestPaneApplyCurrentSettingsL( CStifItemParser& aItem );

    /**
    * TestPanePrepareForAppExitL test method for testing the PrepareForAppExit method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestPanePrepareForAppExitL( CStifItemParser& aItem );

    /**
    * TestPaneMakeVisibleL test method for testing the MakeVisible method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestPaneMakeVisibleL( CStifItemParser& aItem );

    /**
    * TestPaneSetDimmedL test method for testing the SetDimmed method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestPaneSetDimmedL( CStifItemParser& aItem );

    /**
    * TestPaneSetFadedL test method for testing the SetFaded method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestPaneSetFadedL( CStifItemParser& aItem );

    /**
    * TestPaneHandleResourceChangeL test method for testing the HandleResourceChange method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestPaneHandleResourceChangeL( CStifItemParser& aItem );

    /**
    * TestPaneOkToChangeStatusPaneNowL test method for testing the OkToChangeStatusPaneNow method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestPaneOkToChangeStatusPaneNowL( CStifItemParser& aItem );
    
private: // Test eikspmod.h
/*                            class TEikStatusPaneInit                         */
    /**
    * TestSPIIdL test method for testing the Id method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestSPIIdL( CStifItemParser& aItem );
    
    /**
    * TestSPIAppOwnedL test method for testing the AppOwned method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestSPIAppOwnedL( CStifItemParser& aItem );
    
    /**
    * TestSPIControlTypeIdL test method for testing the ControlTypeId method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestSPIControlTypeIdL( CStifItemParser& aItem );
    
    /**
    * TestSPIControlResourceIdL test method for testing the ControlResourceId method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestSPIControlResourceIdL( CStifItemParser& aItem );
    
    /**
    * TestSPISetHiddenL test method for testing the SetHidden method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestSPISetHiddenL( CStifItemParser& aItem );
    
    /**
    * TestSPIClearHiddenL test method for testing the ClearHidden method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestSPIClearHiddenL( CStifItemParser& aItem );
    
    /**
    * TestSPIIsHiddenL test method for testing the IsHidden method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestSPIIsHiddenL( CStifItemParser& aItem );
    
    /**
    * TestSPLTIdL test method for testing the Id method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestSPLTIdL( CStifItemParser& aItem );
    
    /**
    * TestSPLTRectL test method for testing the Rect method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestSPLTRectL( CStifItemParser& aItem );
    
    /**
    * TestSPLFindL test method for testing the Find method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestSPLFindL( CStifItemParser& aItem );
    
    /**
    * TestSPLAcceptL test method for testing the AcceptL method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestSPLAcceptL( CStifItemParser& aItem );
    
    /**
    * TestSPLRectL test method for testing the Rect method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestSPLRectL( CStifItemParser& aItem );
    
    /**
    * TestSPMBDeconstructorL test method for testing the ~CEikStatusPaneModelBase method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestSPMBDeconstructorL( CStifItemParser& aItem );
    
    /**
    * TestSPMBPaneInitsL test method for testing the PaneInits method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestSPMBPaneInitsL( CStifItemParser& aItem );
    
    /**
    * TestSPMBSetLayoutL test method for testing the SetLayoutL method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestSPMBSetLayoutL( CStifItemParser& aItem );
    
    /**
    * TestSPMBCurrentLayoutL test method for testing the CurrentLayout method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestSPMBCurrentLayoutL( CStifItemParser& aItem );
    
    /**
    * TestSPMBCurrentLayoutResIdL test method for testing the CurrentLayoutResId method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestSPMBCurrentLayoutResIdL( CStifItemParser& aItem );
    
    /**
    * TestSPMBCEikStatusPaneModelBaseL test method for testing the CEikStatusPaneModelBase method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestSPMBCEikStatusPaneModelBaseL( CStifItemParser& aItem );
    
    /**
    * TestSPMBBaseConstructL test method for testing the BaseConstructL method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestSPMBBaseConstructL( CStifItemParser& aItem );
    
    /**
    * TestSPMBLoadLayoutL test method for testing the LoadLayoutL method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestSPMBLoadLayoutL( CStifItemParser& aItem );
    
    /**
    * TestSPMBLegalIdsL test method for testing the LegalIds method
    * @since S60 5.0
    * @param aItem Script line containing parameters.
    * @return Symbian OS error code.
    */
    virtual TInt TestSPMBLegalIdsL( CStifItemParser& aItem );
    

private:    // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;
    
    /**
     * CEikonEnv Property
     * not own
     */
    CEikonEnv* iEnv;
    

    };

#endif      // C_TESTSDKSTATUSPANE_H

// End of File

