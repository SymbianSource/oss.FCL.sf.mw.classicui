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
* Description:  test fonts api
*
*/



#ifndef C_TESTSDKFONTS_H
#define C_TESTSDKFONTS_H

//  INCLUDES
#include <stiflogger.h>
#include <testscripterinternal.h>
#include <stiftestmodule.h>
#include <testclassassert.h>

#include <aknfontaccess.h> 
#include <stringloader.h> 
#include <gdi.h>
#include <coemain.h>

#include <aknlayoutfont.h> 
#include <aknfontspecification.h>
#include <akntextdecorationmetrics.h>
#include <fbs.h>
#include <akntextdecorationmetrics.h>
#include <fntstore.h>
#include <aknutils.h> 



// MACROS
#define TEST_CLASS_VERSION_MAJOR 0
#define TEST_CLASS_VERSION_MINOR 0
#define TEST_CLASS_VERSION_BUILD 0

// Logging path
_LIT( KtestsdkfontsLogPath, "\\logs\\testframework\\testsdkfonts\\" ); 
// Log file
_LIT( KtestsdkfontsLogFile, "testsdkfonts.txt" ); 
_LIT( KtestsdkfontsLogFileWithTitle, "testsdkfonts_[%S].txt" );

/**
*  Ctestsdkfonts test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS( CTestSdkFonts ) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestSdkFonts* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestSdkFonts();

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
    CTestSdkFonts( CTestModuleIf& aTestModuleIf );

    /**
    * By default Symbian 2nd phase constructor is private.
    */
    void ConstructL();
    
    /**
     * Method used to log version of test class
     */
    void SendTestClassVersion();

private: // AknFontAccess.h
    /**
    * TestFAGetFont test function in class AknFontAccess for testing the GetFontL function
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestFAGetFont( CStifItemParser& aItem );
    
    /**
    * TestFAGetFontDesc test function in class AknFontAccess for testing the GetFont function
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestFAGetFontDesc( CStifItemParser& aItem );
    
    /**
    * TestFAGetClosestFont test function in class AknFontAccess for testing the GetClosestFontL function
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestFAGetClosestFont( CStifItemParser& aItem );
    
    /**
    * TestFAGetClosestFontDesc test function in class AknFontAccess for testing the GetClosestFontL function
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestFAGetClosestFontDesc( CStifItemParser& aItem );
    
    /**
    * TestFACreateLayoutFontFromSpecificationL test function in class CreateLayoutFontFromSpecificationL for testing the GetClosestFontL function
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestFACreateLayoutFontFromSpecificationL( CStifItemParser& aItem );
    
    /**
    * TestFACreateLayoutFontFromSpecificationTTypefaceL test function in class CreateLayoutFontFromSpecificationL for testing the GetClosestFontL function
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestFACreateLayoutFontFromSpecificationTTypefaceL( CStifItemParser& aItem );
    
    
private: // CAknLayoutFont.h
    /**
    * TestLFUpdateL test function in class CAknLayoutFont for testing the UpdateL function
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestLFUpdateL( CStifItemParser& aItem );
    
    /**
    * TestLFMaxAscentL test function in class CAknLayoutFont for testing the MaxAscentL function
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestLFMaxAscentL( CStifItemParser& aItem );
    
    /**
    * TestLFMaxDescentL test function in class CAknLayoutFont for testing the MaxDescentL function
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestLFMaxDescentL( CStifItemParser& aItem );
    
    /**
    * TestLFTextPaneTopToBaselineL test function in class CAknLayoutFont for testing the TextPaneTopToBaselineL function
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestLFTextPaneTopToBaselineL( CStifItemParser& aItem );
    
    
    /**
    * TestLFBaselineToTextPaneBottomL test function in class CAknLayoutFont for testing the BaselineToTextPaneBottomL function
    * Position of the text pane bottom measured down from the baseline
    * @return distance from text pane top to baseline
    */
    virtual TInt TestLFBaselineToTextPaneBottomL( CStifItemParser& aItem );

    /**
    * TestLFTextPaneHeightL test function in class CAknLayoutFont for testing the TextPaneHeightL function
    * Series 60 text pane height. 
    * Always equal to TextPaneTopToBaseline() + BaselineToTextPaneBottom()
    * @return text pane height
    */
    virtual TInt TestLFTextPaneHeightL( CStifItemParser& aItem );

    /**
    * TestLFAscentForCharacterL test function in class CAknLayoutFont for testing the AscentForCharacterL function
    * This provides the baseline relative to the top of the combined font for a specific 
    * character code. This value does not include any TopShortfall.
    **/
    virtual TInt TestLFAscentForCharacterL( CStifItemParser& aItem );

    /**
    * TestLFAsCAknLayoutFontOrNullL test function in class CAknLayoutFont for testing the AsCAknLayoutFontOrNullL function
    * Returns if a font pointer cast to this type if the actual type conforms to this type. 
    * @returns NULL if the font does not conform to CAknLayoutFont.
    */
    virtual TInt TestLFAsCAknLayoutFontOrNullL( CStifItemParser& aItem );

    /**
    * TestLFTextDecorationMetricsL test function in class CAknLayoutFont for testing the TextDecorationMetricsL function
    * Returns an object describing how the text with this font is to be decorated
    * @return   text decoration metrics for the font
    */
    virtual TInt TestLFTextDecorationMetricsL( CStifItemParser& aItem );

    /**
    * TestLFFontCategoryL test function in class CAknLayoutFont for testing the FontCategoryL function
    * Returns the Avkon font category (EAknFontCategoryPrimary, EAknFontCategorySecondary...)
    * that was used to generate this font.
    * @return   font category
    */
    virtual TInt TestLFFontCategoryL( CStifItemParser& aItem );

    /**
    * TestLFFontSpecificationL test function in class CAknLayoutFont for testing the FontSpecificationL function
    * This API allows the font to provide the metrics under which the font was requested.
    * @return   the font specification for which the font has been supplied
    */
    virtual TInt TestLFFontSpecificationL( CStifItemParser& aItem );

private: // TAknTextDecorationMetrics.h
    /**
    * TestTDMTAknTextDecorationMetrics test function in class TAknTextDecorationMetricsL for testing the TAknTextDecorationMetricsSpec function
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestTDMTAknTextDecorationMetricsL( CStifItemParser& aItem );
    
    /**
    * TestTDMTAknTextDecorationMetricsFont test function in class TAknTextDecorationMetricsFontL for testing the TAknTextDecorationMetricsSpecL function
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestTDMTAknTextDecorationMetricsFontL( CStifItemParser& aItem );
    
    /**
    * TestTDMTAknTextDecorationMetricsSpec test function in class TAknTextDecorationMetricsSpecL for testing the TAknTextDecorationMetricsSpecL function
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestTDMTAknTextDecorationMetricsSpecL( CStifItemParser& aItem );
    
    /**
    * TestTDMGetLeftAndRightMargins test function in class TAknTextDecorationMetricsL for testing the GetLeftAndRightMarginsL function
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestTDMGetLeftAndRightMarginsL( CStifItemParser& aItem );
    
    /**
    * TestTDMGetTopAndBottomMargins test function in class TAknTextDecorationMetricsL for testing the GetTopAndBottomMarginsL function
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestTDMGetTopAndBottomMarginsL( CStifItemParser& aItem );
    
    /**
    * TestTDMCursorWidth test function in class TAknTextDecorationMetricsL for testing the CursorWidthL function
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestTDMCursorWidthL( CStifItemParser& aItem );
    
    /**
    * TestTDMBaselineToUnderlineOffset test function in class TAknTextDecorationMetricsL for testing the BaselineToUnderlineOffsetL function
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestTDMBaselineToUnderlineOffsetL( CStifItemParser& aItem );
    
    /**
    * TestTDMUnderlineHeight test function in class TAknTextDecorationMetricsL for testing the UnderlineHeightL function
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
    virtual TInt TestTDMUnderlineHeightL( CStifItemParser& aItem );
    
    
private:    // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;
    /**
     * Pointer to a control, maybe you need one in your test
     * own
     */
    AknFontAccess* iFontAccess;
    
    };



#endif      // C_TESTSDKFONTS_H

// End of File
