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
* Description:  Test eikimage.h
*
*/



#ifndef C_TESTSDKIMAGES_H
#define C_TESTSDKIMAGES_H

/*
 *   INCLUDES
 */
#include <stiflogger.h>
#include <testscripterinternal.h>
#include <stiftestmodule.h>
#include <testclassassert.h>

class CEikImage;
/*
 *  MACROS
 */
#define TEST_CLASS_VERSION_MAJOR 0
#define TEST_CLASS_VERSION_MINOR 0
#define TEST_CLASS_VERSION_BUILD 0

/*
 *  Logging path
 */
_LIT( KtestsdkimagesLogPath, "\\logs\\testframework\\testsdkimages\\" ); 
/*
 *  Log file
 */
_LIT( KtestsdkimagesLogFile, "testsdkimages.txt" ); 
_LIT( KtestsdkimagesLogFileWithTitle, "testsdkimages_[%S].txt" );

/**
*  CTestSDKIMAGES test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS(CTestSDKIMAGES) : public CScriptBase
    {
public:

    /**
    * Two-phased constructor.
    */
    static CTestSDKIMAGES* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestSDKIMAGES();

public:

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
    CTestSDKIMAGES( CTestModuleIf& aTestModuleIf );

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
     * TestIMAGESConstructorL test function for testing the Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestIMAGESConstructorL( CStifItemParser& /*aItem*/ );
    /**
     * TestIMAGESDestructorL test function for testing the Destructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestIMAGESDestructorL( CStifItemParser& /*aItem*/ );
    /**
     * TestIMAGESMinimumSizeL test function for testing the MinimumSize function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestIMAGESMinimumSizeL( CStifItemParser& /*aItem*/ );
    /**
     * TestIMAGESConstructFromResourceL test function for testing the ConstructFromResource function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestIMAGESConstructFromResourceL( CStifItemParser& /*aItem*/ );
    /**
     * TestIMAGESCreatePictureFromFileL test function for testing the CreatePictureFromFile function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestIMAGESCreatePictureFromFileL( CStifItemParser& /*aItem*/ );
    /**
     * TestIMAGESSetPictureL test function for testing the SetPicture function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestIMAGESSetPictureL( CStifItemParser& /*aItem*/ );
    /**
     * TestIMAGESSetEmphasisL test function for testing the SetEmphasis function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestIMAGESSetEmphasisL( CStifItemParser& /*aItem*/ );
    /**
     * TestIMAGESSetPictureOwnedExternallyL test function for testing the SetPictureOwnedExternally function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestIMAGESSetPictureOwnedExternallyL( CStifItemParser& /*aItem*/ );
    /**
     * TestIMAGESBitmapL test function for testing the Bitmap function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestIMAGESBitmapL( CStifItemParser& aItem );
    /**
     * TestIMAGESMaskL test function for testing the Mask function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestIMAGESMaskL( CStifItemParser& aItem );
    /**
     * TestIMAGESSetBitmapL test function for testing the SetBitmap 
     * and SetNewBitmaps function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestIMAGESSetBitmapL( CStifItemParser& /*aItem*/ );
    /**
     * TestIMAGESSetMaskL test function for testing the SetMask function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestIMAGESSetMaskL( CStifItemParser& /*aItem*/ );
    /**
     * TestIMAGESSetNewBitmapsL test function for testing the SetNewBitmaps function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestIMAGESSetNewBitmapsL( CStifItemParser& aItem );
    /**
     * TestIMAGESIsPictureOwnedExternallyL test function for testing the IsPictureOwnedExternally function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestIMAGESIsPictureOwnedExternallyL( CStifItemParser& /*aItem*/ );
    /**
     * TestIMAGESHandlePointerEventL test function for testing the HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestIMAGESHandlePointerEventL( CStifItemParser& /*aItem*/ );
    /**
     * TestIMAGESSetBrushStyleL test function for testing the SetBrushStyle function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestIMAGESSetBrushStyleL( CStifItemParser& /*aItem*/ );
    /**
     * TestIMAGESWriteInternalStateL test function for testing the WriteInternalStateL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestIMAGESWriteInternalStateL( CStifItemParser& /*aItem*/ );
    
    /**
     * Method used to log version of test class
     */
    void SendTestClassVersion();

private:    // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;

    // Resource file offset
    TInt iOffset;
    };

#endif      // C_TESTSDKIMAGES_H

/*
 *  End of File
 */



