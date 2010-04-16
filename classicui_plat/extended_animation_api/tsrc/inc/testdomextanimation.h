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
* Description:  test functions in extended_animation_api
*
*/



#ifndef C_TESTDOMEXTANIMATION_H
#define C_TESTDOMEXTANIMATION_H

//  INCLUDES
#include <stiflogger.h>
#include <testscripterinternal.h>
#include <stiftestmodule.h>
#include <testclassassert.h>

#include <aknanimdata.h>
#include <aknanimview.h>

// MACROS
#define TEST_CLASS_VERSION_MAJOR 0
#define TEST_CLASS_VERSION_MINOR 0
#define TEST_CLASS_VERSION_BUILD 0

// Logging path
_LIT( KtestdomextanimationLogPath, "c:\\logs\\testframework\\testdomextanimation\\" ); 
// Log file
_LIT( KtestdomextanimationLogFile, "testdomextanimation.txt" ); 
_LIT( KtestdomextanimationLogFileWithTitle, "testdomextanimation_[%S].txt" );

/**
*  Ctestdomextanimation test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS( CTestDomExtAnimation ) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestDomExtAnimation* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestDomExtAnimation();

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
    CTestDomExtAnimation( CTestModuleIf& aTestModuleIf );

    /**
    * By default Symbian 2nd phase constructor is private.
    */
    void ConstructL();

    /**
     * Method used to log version of test class
     */
    void SendTestClassVersion();

private: // [TestMethods]
    /**
    * TestTAnimSTAnimStepL tests TAnimStep
    * of TAnimStep in aknAnimData.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAnimStepTAnimStepL( CStifItemParser& aItem );
    
    /**
    * TestTAnimStepLineDrawStep tests LineDrawStep
    * of TAnimStep in aknAnimData.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAnimStepLineDrawStep( CStifItemParser& aItem );
    
    /**
    * TestTAnimStepBlitStep tests BlitStep
    * of TAnimStep in aknAnimData.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAnimStepBlitStep( CStifItemParser& aItem );
    
    /**
    * TestTAnimStepSetColorStep tests SetColorStep
    * of TAnimStep in aknAnimData.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAnimStepSetColorStep( CStifItemParser& aItem );
    
    /**
    * TestTAnimStepSlideStep tests SlideStep
    * of TAnimStep in aknAnimData.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAnimStepSlideStep( CStifItemParser& aItem );
    
    /**
    * TestTAnimStepWaitStep tests WaitStep
    * of TAnimStep in aknAnimData.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAnimStepWaitStep( CStifItemParser& aItem );
    
    /**
    * TestTAnimStepSetType tests SetType
    * of TAnimStep in aknAnimData.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAnimStepSetType( CStifItemParser& aItem );
    
    /**
    * TestTAnimStepType tests Type
    * of TAnimStep in aknAnimData.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAnimStepType( CStifItemParser& aItem );
    
    /**
    * TestTAnimMultiStepTAnimMultiStepL tests TAnimMultiStep
    * of TAnimMultiStep in aknAnimData.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAnimMultiStepTAnimMultiStepL( CStifItemParser& aItem );
    
    /**
    * TestCAknAnimDataCAknAnimationDataL tests CAknAnimationData
    * of CAknAnimationData in aknAnimData.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCAknAnimDataCAknAnimationDataL( CStifItemParser& aItem );
    
    /**
    * TestCAknAnimDataConstructFromResourceL tests ConstructFromResourceL
    * of CAknAnimationData in aknAnimData.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCAknAnimDataConstructFromResourceL( CStifItemParser& aItem );
    
    /**
    * TestCAknAnimDataSetScreenSizeL tests SetScreenSize
    * of CAknAnimationData in aknAnimData.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCAknAnimDataSetScreenSizeL( CStifItemParser& aItem );
    
    /**
    * TestCAknAnimDataSetViewBitmapL tests SetViewBitmap
    * of CAknAnimationData in aknAnimData.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCAknAnimDataSetViewBitmapL( CStifItemParser& aItem );
    
    /**
    * TestCAknAnimDataSetOldBitmapL tests SetOldBitmap
    * of CAknAnimationData in aknAnimData.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCAknAnimDataSetOldBitmapL( CStifItemParser& aItem );
    
    /**
    * TestCAknAnimDataSetClearOldViewL tests SetClearOldView
    * of CAknAnimationData in aknAnimData.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCAknAnimDataSetClearOldViewL( CStifItemParser& aItem );
    
    /**
    * TestCAknAnimDataClearOldViewL tests ClearOldView
    * of CAknAnimationData in aknAnimData.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCAknAnimDataClearOldViewL( CStifItemParser& aItem );
    
    /**
    * TestCAknAnimDataWaitBetweenSectionsL tests WaitBetweenSections
    * of CAknAnimationData in aknAnimData.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCAknAnimDataWaitBetweenSectionsL( CStifItemParser& aItem );
    
    /**
    * TestCAknAnimDataSetWaitForeverAtEndL tests SetWaitForeverAtEnd
    * of CAknAnimationData in aknAnimData.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCAknAnimDataSetWaitForeverAtEndL( CStifItemParser& aItem );
    
    /**
    * TestCAknAnimDataWaitForeverAtEndL tests WaitForeverAtEnd
    * of CAknAnimationData in aknAnimData.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCAknAnimDataWaitForeverAtEndL( CStifItemParser& aItem );
    
    /**
    * TestCAknAnimDataDrawNextAnimationStepL tests DrawNextAnimationStep
    * of CAknAnimationData in aknAnimData.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCAknAnimDataDrawNextAnimationStepL( CStifItemParser& aItem );
    
    /**
    * TestCAknAnimDataIntervalL tests Interval
    * of CAknAnimationData in aknAnimData.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCAknAnimDataIntervalL( CStifItemParser& aItem );
    
    /**
    * TestCAknAnimDataConstructL tests ConstructL
    * of CAknAnimationData in aknAnimData.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCAknAnimDataConstructL( CStifItemParser& aItem );
    
    /**
    * TestCAknAnimViewCAknAnimatedViewL tests CAknAnimatedView
    * of CAknAnimatedView in aknAnimView.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCAknAnimViewCAknAnimatedViewL( CStifItemParser& aItem );
    
    /**
    * TestCAknAnimViewSetAnimationDataL tests SetAnimationData
    * of CAknAnimatedView in aknAnimView.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCAknAnimViewSetAnimationDataL( CStifItemParser& aItem );
    
    /**
    * TestCAknAnimViewAknViewActivatedL tests AknViewActivatedL
    * of CAknAnimatedView in aknAnimView.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCAknAnimViewAknViewActivatedL( CStifItemParser& aItem );
    
    /**
    * TestCAknAnimViewPreAnimateSetupL tests PreAnimateSetup
    * of CAknAnimatedView in aknAnimView.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCAknAnimViewPreAnimateSetupL( CStifItemParser& aItem );
    
    /**
    * TestCAknAnimViewPostAnimateSetupL tests PostAnimateSetup
    * of CAknAnimatedView in aknAnimView.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCAknAnimViewPostAnimateSetupL( CStifItemParser& aItem );
    
    /**
    * TestCAknAnimViewSwapListBoxGcL tests SwapListBoxGc
    * of CAknAnimatedView in aknAnimView.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCAknAnimViewSwapListBoxGcL( CStifItemParser& aItem );
    

private:    // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;
    // Resource file offset
    TInt iOffset;

    };

#endif      // C_TESTDOMEXTANIMATION_H

// End of File
