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
* Description:  Test EIKLABEL.H, eikfnlab.h
*
*/



#ifndef C_TESTSDKLABELS_H
#define C_TESTSDKLABELS_H

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
_LIT( KtestsdklabelsLogPath, "\\logs\\testframework\\testsdklabels\\" ); 
// Log file
_LIT( KtestsdklabelsLogFile, "testsdklabels.txt" ); 
_LIT( KtestsdklabelsLogFileWithTitle, "testsdklabels_[%S].txt" );

/**
*  CTestSDKLabels test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS(CTestSDKLabels) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestSDKLabels* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestSDKLabels();

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
    CTestSDKLabels( CTestModuleIf& aTestModuleIf );

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

private: // Test eikfnlab.h
/*                               class CEikFileNameLabel                    */
    /**
     * TestLCEikFileNameLabelL test function for testing the 
     *     CEikFileNameLabel function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLCEikFileNameLabelL( CStifItemParser& aItem );

    /**
     * TestLDeconstructorL test function for testing the 
     *     ~CEikFileNameLabel function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLDeconstructorL( CStifItemParser& aItem );

    /**
     * TestLConstructL test function for testing the 
     *     ConstructL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLConstructL( CStifItemParser& aItem );

    /**
     * TestLUpdateL test function for testing the 
     *     UpdateL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */

    virtual TInt TestLUpdateL( CStifItemParser& aItem );

    /**
     * TestLGetColorUseListL test function for testing the 
     *     GetColorUseListL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLGetColorUseListL( CStifItemParser& aItem );

    /**
     * TestLHandleResourceChangeL test function for testing the 
     *     HandleResourceChange function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLHandleResourceChangeL( CStifItemParser& aItem );

    /**
     * TestLMinimumSizeL test function for testing the 
     *     MinimumSize function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLMinimumSizeL( CStifItemParser& aItem );

    /**
     * TestLHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLHandlePointerEventL( CStifItemParser& aItem );
    
    /**
     * TestLDrawL test function for testing the 
     *     Draw function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLDrawL( CStifItemParser& aItem );
    
private: // Test EIKLABEL.H
/*                               class CEikLabel                            */
    /**
     * TestLabelDeconstructorL test function for testing the 
     *     CEikLabel function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLabelDeconstructorL( CStifItemParser& aItem );
    
    /**
     * TestLabelCEikLabelL test function for testing the 
     *     CEikLabel function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLabelCEikLabelL( CStifItemParser& aItem );
    
    /**
     * TestLabelSetLabelAlignmentL test function for testing the 
     *     SetLabelAlignment function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLabelSetLabelAlignmentL( CStifItemParser& aItem );
    
    /**
     * TestLabelSetBrushStyleL test function for testing the 
     *     SetBrushStyle function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLabelSetBrushStyleL( CStifItemParser& aItem );
    
    /**
     * TestLabelSetBrushStyleFromContextL test function for testing the 
     *     SetBrushStyleFromContext function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLabelSetBrushStyleFromContextL( CStifItemParser& aItem );
    
    /**
     * TestLabelMinimumSizeL test function for testing the 
     *     MinimumSize function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLabelMinimumSizeL( CStifItemParser& aItem );
    
    /**
     * TestLabelConstructFromResourceL test function for testing the 
     *     ConstructFromResourceL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLabelConstructFromResourceL( CStifItemParser& aItem );
    
    /**
     * TestLabelGetColorUseListL test function for testing the 
     *     GetColorUseListL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLabelGetColorUseListL( CStifItemParser& aItem );
    
    /**
     * TestLabelHandleResourceChangeL test function for testing the 
     *     HandleResourceChange function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLabelHandleResourceChangeL( CStifItemParser& aItem );
    
    /**
     * TestLabelDrawL test function for testing the 
     *     Draw function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLabelDrawL( CStifItemParser& aItem );
    
    /**
     * TestLabelSetTextL test function for testing the 
     *     SetTextL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLabelSetTextL( CStifItemParser& aItem );
    
    /**
     * TestLabelTextL test function for testing the 
     *     Text function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLabelTextL( CStifItemParser& aItem );
    
    /**
     * TestLabelCropTextL test function for testing the 
     *     CropText function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLabelCropTextL( CStifItemParser& aItem );
    
    /**
     * TestLabelSetBufferReserveLengthL test function for testing the 
     *     SetBufferReserveLengthL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLabelSetBufferReserveLengthL( CStifItemParser& aItem );
    
    /**
     * TestLabelSetFontL test function for testing the 
     *     SetFont function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLabelSetFontL( CStifItemParser& aItem );
    
    /**
     * TestLabelFontL test function for testing the 
     *     Font function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLabelFontL( CStifItemParser& aItem );
    
    /**
     * TestLabelSetEmphasisL test function for testing the 
     *     SetEmphasis function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLabelSetEmphasisL( CStifItemParser& aItem );
    
    /**
     * TestLabelSetPixelGapBetweenLinesL test function for testing the 
     *     SetPixelGapBetweenLines function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLabelSetPixelGapBetweenLinesL( CStifItemParser& aItem );
    
    /**
     * TestLabelPixelGapBetweenLinesL test function for testing the 
     *     PixelGapBetweenLines function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLabelPixelGapBetweenLinesL( CStifItemParser& aItem );
    
    /**
     * TestLabelIsUnderlinedL test function for testing the 
     *     IsUnderlined function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLabelIsUnderlinedL( CStifItemParser& aItem );
    
    /**
     * TestLabelSetUnderliningL test function for testing the 
     *     SetUnderlining function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLabelSetUnderliningL( CStifItemParser& aItem );
    
    /**
     * TestLabelIsStrikethroughL test function for testing the 
     *     IsStrikethrough function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLabelIsStrikethroughL( CStifItemParser& aItem );
    
    /**
     * TestLabelSetStrikethroughL test function for testing the 
     *     SetStrikethrough function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLabelSetStrikethroughL( CStifItemParser& aItem );
    
    /**
     * TestLabelCalcMinimumSizeL test function for testing the 
     *     CalcMinimumSize function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLabelCalcMinimumSizeL( CStifItemParser& aItem );
    
    /**
     * TestLabelNumberOfLinesL test function for testing the 
     *     NumberOfLines function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLabelNumberOfLinesL( CStifItemParser& aItem );
    
    /**
     * TestLabelBufferReserveLengthL test function for testing the 
     *     BufferReserveLength function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLabelBufferReserveLengthL( CStifItemParser& aItem );
    
    /**
     * TestLabelUseLogicalToVisualConversionL test function for testing the 
     *     UseLogicalToVisualConversion function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLabelUseLogicalToVisualConversionL( CStifItemParser& aItem );
    
    /**
     * TestLabelLogicalToVisualConversionUsedL test function for testing the 
     *     LogicalToVisualConversionUsed function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLabelLogicalToVisualConversionUsedL( CStifItemParser& aItem );
    
    /**
     * TestLabelEnablePictographsL test function for testing the 
     *     EnablePictographsL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLabelEnablePictographsL( CStifItemParser& aItem );
    
    /**
     * TestLabelDisablePictographsL test function for testing the 
     *     DisablePictographs function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLabelDisablePictographsL( CStifItemParser& aItem );
    
    /**
     * TestLabelHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLabelHandlePointerEventL( CStifItemParser& aItem );
    
    /**
     * TestLabelWriteInternalStateL test function for testing the 
     *     WriteInternalStateL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestLabelWriteInternalStateL( CStifItemParser& aItem );
    
private:    // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;

    // Resource file offset
    TInt iOffset;
    };

#endif      // C_TESTSDKLABELS_H

// End of File
