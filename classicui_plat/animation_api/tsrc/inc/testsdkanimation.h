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
* Description:  Test AknBitmapAnimation.h
*
*/



#ifndef C_TESTSDKANIMATION_H
#define C_TESTSDKANIMATION_H

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
_LIT( KtestsdkanimationLogPath, "\\logs\\testframework\\testsdkanimation\\" ); 
// Log file
_LIT( KtestsdkanimationLogFile, "testsdkanimation.txt" ); 
_LIT( KtestsdkanimationLogFileWithTitle, "testsdkanimation_[%S].txt" );

// FORWARD DECLARATIONS
class CTestSDKAnimation;

/**
*  CTestSDKAnimation test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS(CTestSDKAnimation) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestSDKAnimation* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestSDKAnimation();

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
    CTestSDKAnimation( CTestModuleIf& aTestModuleIf );

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

private: // Test AknBitmapAnimation.h
/*                               class CAknBitmapAnimation                  */
    /**
     * TestBANewL test function for testing the 
     *     NewL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestBANewL( CStifItemParser& aItem );
    
    /**
     * TestBADeconstructorL test function for testing the 
     *     DeconstructorL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestBADeconstructorL( CStifItemParser& aItem );
    
    /**
     * TestBAAnimationL test function for testing the 
     *     Animation function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestBAAnimationL( CStifItemParser& aItem );
    
    /**
     * TestBABitmapAnimDataL test function for testing the 
     *     BitmapAnimData function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestBABitmapAnimDataL( CStifItemParser& aItem );
    
    /**
     * TestBACancelAnimationL test function for testing the 
     *     CancelAnimation function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestBACancelAnimationL( CStifItemParser& aItem );
    
    /**
     * TestBASetFrameIndexL test function for testing the 
     *     SetFrameIndexL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestBASetFrameIndexL( CStifItemParser& aItem );
    
    /**
     * TestBASetFrameIntervalL test function for testing the 
     *     SetFrameIntervalL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestBASetFrameIntervalL( CStifItemParser& aItem );
    
    /**
     * TestBAStartAnimationL test function for testing the 
     *     StartAnimationL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestBAStartAnimationL( CStifItemParser& aItem );
    
    /**
     * TestBASetScaleModeForAnimationFramesL test function for testing the 
     *     SetScaleModeForAnimationFrames function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestBASetScaleModeForAnimationFramesL( CStifItemParser& aItem );
    
    /**
     * TestBASetScaleModeForAnimationBackgroundFrameL test function for testing the 
     *     SetScaleModeForAnimationBackgroundFrame function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestBASetScaleModeForAnimationBackgroundFrameL( CStifItemParser& aItem );
    
    /**
     * TestBAExcludeAnimationFramesFromCacheL test function for testing the 
     *     ExcludeAnimationFramesFromCache function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestBAExcludeAnimationFramesFromCacheL( CStifItemParser& aItem );
    
    /**
     * TestBAConstructFromSkinL test function for testing the 
     *     ConstructFromSkinL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestBAConstructFromSkinL( CStifItemParser& aItem );
    
    /**
     * TestBAConstructFromResourceL test function for testing the 
     *     ConstructFromResourceL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestBAConstructFromResourceL( CStifItemParser& aItem );
    
    /**
     * TestBAMinimumSizeL test function for testing the 
     *     MinimumSize function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestBAMinimumSizeL( CStifItemParser& aItem );
    
private:    // Data

    TInt iOldScreenSaverProperty;

    // Resource file offset
    TInt iOffset;
    };

#endif      // C_TESTSDKANIMATION_H

// End of File
