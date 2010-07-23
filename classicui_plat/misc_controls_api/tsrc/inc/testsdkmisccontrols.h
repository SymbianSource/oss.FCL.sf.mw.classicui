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
* Description:  misc_controls_api
*
*/



#ifndef C_TESTSDKMISCCONTROLS_H
#define C_TESTSDKMISCCONTROLS_H

//  INCLUDES
#include <stiflogger.h>
#include <testscripterinternal.h>
#include <stiftestmodule.h>
#include <testclassassert.h>
#include "testsdkmisccontrolcontainer.h"

// MACROS
#define TEST_CLASS_VERSION_MAJOR 0
#define TEST_CLASS_VERSION_MINOR 0
#define TEST_CLASS_VERSION_BUILD 0

// Logging path
_LIT( KtestsdkmisccontrolsLogPath, "\\logs\\testframework\\testsdkmisccontrols\\" ); 
// Log file
_LIT( KtestsdkmisccontrolsLogFile, "testsdkmisccontrols.txt" ); 
_LIT( KtestsdkmisccontrolsLogFileWithTitle, "testsdkmisccontrols_[%S].txt" );

/**
*  Ctestsdkmisccontrols test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
class CEikCaptionedControl;
class CEikCapCArray;
class CEikConsoleScreen;
class CEikConsoleControl;
class CMiscControlsContainer;
class CMiscControlView;
class TEikGroupControl;
class CEikControlGroup;
class CEikMover;
class CEikToolBar;
NONSHARABLE_CLASS( CTestSDKMiscControls ) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestSDKMiscControls* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestSDKMiscControls();

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
    CTestSDKMiscControls( CTestModuleIf& aTestModuleIf );

    /**
    * By default Symbian 2nd phase constructor is private.
    */
    void ConstructL();

    
    /**
     * Method used to log version of test class
     */
    void SendTestClassVersion();

private: 
    //for test misc_controls_api EIKCAPC.H

    /**
     * TestMCConstructorL test function for testing the 
     *     CEikCaptionedControl function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMCConstructorL( CStifItemParser& aItem );
    /**
     * TestMCDestructor test function for testing the 
     *     ~CEikCaptionedControl function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMCDestructor( CStifItemParser& aItem );
    /**
     * TestMCSetUsesEars test function for testing the 
     *     SetUsesEars function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMCSetUsesEars( CStifItemParser& aItem );
    /**
     * TestMCSetSpaceSharingFlags test function for testing the 
     *     SetSpaceSharingFlags function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMCSetSpaceSharingFlags( CStifItemParser& aItem );
    /**
     * TestMCSetExtraAscent test function for testing the 
     *     SetExtraAscent function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMCSetExtraAscent( CStifItemParser& aItem );
    /**
     * TestMCSetCaptionL test function for testing the 
     *     SetCaptionL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMCSetCaptionL( CStifItemParser& aItem );
    /**
     * TestMCSetTrailerL test function for testing the 
     *     SetTrailerL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMCSetTrailerL( CStifItemParser& aItem );
    /**
     * TestMCSetCurrentL test function for testing the 
     *     SetCurrent function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMCSetCurrentL( CStifItemParser& aItem );
    /**
     * TestMCCheckDimmedDisplayStateL test function for testing the 
     *     CheckDimmedDisplayState function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMCCheckDimmedDisplayStateL( CStifItemParser& aItem );
    /**
     * TestMCResetMinimumSizes test function for testing the 
     *     ResetMinimumSizes function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMCResetMinimumSizes( CStifItemParser& aItem );
    /**
     * TestMCIsLatent test function for testing the 
     *     IsLatent function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMCIsLatent( CStifItemParser& aItem );
    /**
     * TestMCSetLatentL test function for testing the 
     *     SetLatent function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMCSetLatentL( CStifItemParser& aItem );
    /**
     * TestMCLatentGroupLineFollows test function for testing the 
     *     LatentGroupLineFollows function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMCLatentGroupLineFollows( CStifItemParser& aItem );
    /**
     * TestMCSetLatentGroupLineFollows test function for testing the 
     *     SetLatentGroupLineFollows function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMCSetLatentGroupLineFollows( CStifItemParser& aItem );
    /**
     * TestMCDividerAfter test function for testing the 
     *     DividerAfter function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMCDividerAfter( CStifItemParser& aItem );
    /**
     * TestMCSetDividerAfter test function for testing the 
     *     SetDividerAfter function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMCSetDividerAfter( CStifItemParser& aItem );
    /**
     * TestMCTakesEnterKey test function for testing the 
     *     TakesEnterKey function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMCTakesEnterKey( CStifItemParser& aItem );
    /**
     * TestMCSetTakesEnterKey test function for testing the 
     *     SetTakesEnterKey function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMCSetTakesEnterKey( CStifItemParser& aItem );
    /**
     * TestMCOfferHotKeys test function for testing the 
     *     OfferHotKeys function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMCOfferHotKeys( CStifItemParser& aItem );
    /**
     * TestMCSetOfferHotKeys test function for testing the 
     *     SetOfferHotKeys function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMCSetOfferHotKeys( CStifItemParser& aItem );
    /**
     * TestMCHandleControlEventL test function for testing the 
     *     HandleControlEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMCHandleControlEventL( CStifItemParser& aItem );
    /**
     * TestMCMinimumSizeL test function for testing the 
     *     MinimumSize function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMCMinimumSizeL( CStifItemParser& aItem );
    
    /**
     * TestMCConstructFromResourceL test function for testing the 
     *     ConstructFromResourceL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMCConstructFromResourceL( CStifItemParser& aItem );
    
    /**
     * TestMCOfferKeyEventL test function for testing the 
     *     OfferKeyEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMCOfferKeyEventL( CStifItemParser& aItem );
    /**
     * TestMCGetColorUseListL test function for testing the 
     *     GetColorUseListL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMCGetColorUseListL( CStifItemParser& aItem );
    /**
     * TestMCHandleResourceChangeL test function for testing the 
     *     HandleResourceChange function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMCHandleResourceChangeL( CStifItemParser& aItem );
    /**
     * TestMCInputCapabilities test function for testing the 
     *     InputCapabilities function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMCInputCapabilities( CStifItemParser& aItem );
    /**
     * TestMCSetDimmed test function for testing the 
     *     SetDimmed function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMCSetDimmed( CStifItemParser& aItem );
    /**
     * TestMCHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMCHandlePointerEventL( CStifItemParser& aItem );
    /**
     * TestMCDrawL test function for testing the 
     *     Draw function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMCDrawL( CStifItemParser& aItem );
    /**
     * TestMCWriteInternalStateL test function for testing the 
     *     WriteInternalStateL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMCWriteInternalStateL( CStifItemParser& aItem );
    /**
     * TestMCMopSupplyObjectL test function for testing the 
     *     MopSupplyObjectL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMCMopSupplyObjectL( CStifItemParser& aItem );
    /**
     * TestMCSetToolTipTextL test function for testing the 
     *     SetToolTipTextL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMCSetToolTipTextL( CStifItemParser& aItem );
    /**
     * TestMCToolTipTextL test function for testing the 
     *     ToolTipText function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMCToolTipTextL( CStifItemParser& aItem );
    /**
     * TestMCSetBitmapFromFileL test function for testing the 
     *     SetBitmapFromFileL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMCSetBitmapFromFileL( CStifItemParser& aItem );
    /**
     * TestMCSetEditableL test function for testing the 
     *     SetEditableL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMCSetEditableL( CStifItemParser& aItem );
    /**
     * TestMCSetFormFlagsL test function for testing the 
     *     SetFormFlags function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMCSetFormFlagsL( CStifItemParser& aItem );
    /**
     * TestMCGetFullCaptionTextL test function for testing the 
     *     GetFullCaptionText function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMCGetFullCaptionTextL( CStifItemParser& aItem );
    /**
     * TestMCSetDrawNoWhiteBackgroundL test function for testing the 
     *     SetDrawNoWhiteBackground function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMCSetDrawNoWhiteBackgroundL( CStifItemParser& aItem );
    /**
     * TestMCSetIconL test function for testing the 
     *     SetIconL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMCSetIconL( CStifItemParser& aItem );
    /**
     * TestMCSetIndicatorIconL test function for testing the 
     *     SetIndicatorIconL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMCSetIndicatorIconL( CStifItemParser& aItem );
    /**
     * TestMCSetPointerEventObserverL test function for testing the 
     *     SetPointerEventObserver function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMCSetPointerEventObserverL( CStifItemParser& aItem );
    //for test misc_controls_api eikcapca.h
    /**
     * TestCCAConstructorL test function for testing the 
     *     CEikCapCArray function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCCAConstructorL( CStifItemParser& aItem );
    /**
     * TestCCADestructor test function for testing the 
     *     ~CEikCapCArray function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCCADestructor( CStifItemParser& aItem );
    /**
     * TestCCAMinimumSize test function for testing the 
     *     MinimumSize function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCCAMinimumSize( CStifItemParser& aItem );
    /**
     * TestCCASetRect test function for testing the 
     *     SetRect function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCCASetRect( CStifItemParser& aItem );
    /**
     * TestCCAResetMinimumSizes test function for testing the 
     *     ResetMinimumSizes function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCCAResetMinimumSizes( CStifItemParser& aItem );
    /**
     * TestCCALineIndexFromId test function for testing the 
     *     LineIndexFromId function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCCALineIndexFromId( CStifItemParser& aItem );
    /**
     * TestCCAFindLineIndexL test function for testing the 
     *     FindLineIndexL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCCAFindLineIndexL( CStifItemParser& aItem );
    /**
     * TestCCADeleteLineL test function for testing the 
     *     DeleteLineL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCCADeleteLineL( CStifItemParser& aItem );
    /**
     * TestCCAAdjustAllIds test function for testing the 
     *     AdjustAllIds function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCCAAdjustAllIds( CStifItemParser& aItem );
    /**
     * TestCCASetDensePacking test function for testing the 
     *     SetDensePacking function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCCASetDensePacking( CStifItemParser& aItem );
    //for test misc_controls_api eikconso.h
    /**
     * TestCSDefaultConstructorL test function for testing the 
     *     Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCSDefaultConstructorL( CStifItemParser& aItem );
    /**
     * TestCSDestructor test function for testing the 
     *     Destructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCSDestructor( CStifItemParser& aItem );
    /**
     * TestCSConstructL test function for testing the 
     *     ConstructL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCSConstructL( CStifItemParser& aItem );
    /**
     * TestCSConstructWithSizeL test function for testing the 
     *     ConstructL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCSConstructWithSizeL( CStifItemParser& aItem );
    /**
     * TestCSConstructWithSizeAndPointL test function for testing the 
     *     ConstructL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCSConstructWithSizeAndPointL( CStifItemParser& aItem );
    /**
     * TestCSCreate test function for testing the 
     *     Create function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCSCreate( CStifItemParser& aItem );
    /**
     * TestCSRead test function for testing the 
     *     Read function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCSRead( CStifItemParser& aItem );
    /**
     * TestCSReadCancel test function for testing the 
     *     ReadCancel function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCSReadCancel( CStifItemParser& aItem );
    /**
     * TestCSKeyCode test function for testing the 
     *     KeyCode function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCSKeyCode( CStifItemParser& aItem );
    /**
     * TestCSKeyModifiers test function for testing the 
     *     KeyModifiers function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCSKeyModifiers( CStifItemParser& aItem );
    /**
     * TestCSSetConsWinL test function for testing the 
     *     SetConsWinL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCSSetConsWinL( CStifItemParser& aItem );
    /**
     * TestCSConsoleControlL test function for testing the 
     *     ConsoleControl function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCSConsoleControlL( CStifItemParser& aItem );
    /**
     * TestCSSetTitle test function for testing the 
     *     SetTitle function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCSSetTitle( CStifItemParser& aItem );
    /**
     * TestCSSetTitleL test function for testing the 
     *     SetTitleL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCSSetTitleL( CStifItemParser& aItem );
    /**
     * TestCSTitleL test function for testing the 
     *     Title function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCSTitleL( CStifItemParser& aItem );
    /**
     * TestCSScreenSize test function for testing the 
     *     ScreenSize function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCSScreenSize( CStifItemParser& aItem );
    /**
     * TestCSFlushChars test function for testing the 
     *     FlushChars function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCSFlushChars( CStifItemParser& aItem );
    /**
     * TestCSCursorPos test function for testing the 
     *     CursorPos function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCSCursorPos( CStifItemParser& aItem );
    /**
     * TestCSSetCursorPosAbs test function for testing the 
     *     SetCursorPosAbs function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCSSetCursorPosAbs( CStifItemParser& aItem );
    /**
     * TestCSSetCursorPosRel test function for testing the 
     *     SetCursorPosRel function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCSSetCursorPosRel( CStifItemParser& aItem );
    /**
     * TestCSSetCursorHeight test function for testing the 
     *     SetCursorHeight function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCSSetCursorHeight( CStifItemParser& aItem );
    /**
     * TestCSWrite test function for testing the 
     *     Write function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCSWrite( CStifItemParser& aItem );
    /**
     * TestCSClearScreen test function for testing the 
     *     ClearScreen function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCSClearScreen( CStifItemParser& aItem );
    /**
     * TestCSClearToEndOfLine test function for testing the 
     *     ClearToEndOfLine function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCSClearToEndOfLine( CStifItemParser& aItem );
    /**
     * TestCSClearChars test function for testing the 
     *     ClearChars function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCSClearChars( CStifItemParser& aItem );
    /**
     * TestCSHideCursor test function for testing the 
     *     HideCursor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCSHideCursor( CStifItemParser& aItem );
    /**
     * TestCSDrawCursor test function for testing the 
     *     DrawCursor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCSDrawCursor( CStifItemParser& aItem );
    /**
     * TestCSDrawInSight test function for testing the 
     *     DrawInSight function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCSDrawInSight( CStifItemParser& aItem );
    /**
     * TestCSDrawCursorInSight test function for testing the 
     *     DrawCursorInSight function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCSDrawCursorInSight( CStifItemParser& aItem );
    /**
     * TestCSUp test function for testing the 
     *     Up function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCSUp( CStifItemParser& aItem );
    /**
     * TestCSDown test function for testing the 
     *     Down function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCSDown( CStifItemParser& aItem );
    /**
     * TestCSRight test function for testing the 
     *     Right function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCSRight( CStifItemParser& aItem );
    /**
     * TestCSLeft test function for testing the 
     *     Left function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCSLeft( CStifItemParser& aItem );
    /**
     * TestCSCr test function for testing the 
     *     Cr function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCSCr( CStifItemParser& aItem );
    /**
     * TestCSLf test function for testing the 
     *     Lf function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCSLf( CStifItemParser& aItem );
    /**
     * TestCSScrollChars test function for testing the 
     *     ScrollChars function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCSScrollChars( CStifItemParser& aItem );
    /**
     * TestCSRedraw test function for testing the 
     *     Redraw function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCSRedraw( CStifItemParser& aItem );
    /**
     * TestCSMoveTopLeft test function for testing the 
     *     MoveTopLeft function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCSMoveTopLeft( CStifItemParser& aItem );
    /**
     * TestCSHistorySize test function for testing the 
     *     HistorySize function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCSHistorySize( CStifItemParser& aItem );
    /**
     * TestCSSetHistorySizeL test function for testing the 
     *     SetHistorySizeL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCSSetHistorySizeL( CStifItemParser& aItem );
    /**
     * TestCSAtt test function for testing the 
     *     Att function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCSAtt( CStifItemParser& aItem );
    /**
     * TestCSAtt test function for testing the 
     *     SetAtt function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCSSetAtt( CStifItemParser& aItem );
    /**
     * TestCSSetAttWithGround test function for testing the 
     *     SetAtt function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCSSetAttWithGround( CStifItemParser& aItem );
    /**
     * TestCSSetFontL test function for testing the 
     *     SetFontL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCSSetFontL( CStifItemParser& aItem );
    /**
     * TestCSFont test function for testing the 
     *     Font function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCSFont( CStifItemParser& aItem );
    /**
     * TestCSSetSelection test function for testing the 
     *     SetSelection function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCSSetSelection( CStifItemParser& aItem );
    /**
     * TestCSSelectCursor test function for testing the 
     *     SelectCursor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCSSelectCursor( CStifItemParser& aItem );
    /**
     * TestCSSelection test function for testing the 
     *     Selection function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCSSelection( CStifItemParser& aItem );
    /**
     * TestCSRetrieveL test function for testing the 
     *     RetrieveL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCSRetrieveL( CStifItemParser& aItem );
    /**
     * TestCSSetPureCRLF test function for testing the 
     *     SetPureCRLF function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCSSetPureCRLF( CStifItemParser& aItem );
    /**
     * TestCSSetAllPrintable test function for testing the 
     *     SetAllPrintable function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCSSetAllPrintable( CStifItemParser& aItem );
    /**
     * TestCSSetScrollLock test function for testing the 
     *     SetScrollLock function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCSSetScrollLock( CStifItemParser& aItem );
    /**
     * TestCSSetKeepCursorInSight test function for testing the 
     *     SetKeepCursorInSight function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCSSetKeepCursorInSight( CStifItemParser& aItem );
    /**
     * TestCSSetScrollBarVisibilityL test function for testing the 
     *     SetScrollBarVisibilityL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCSSetScrollBarVisibilityL( CStifItemParser& aItem );
    /**
     * TestCSUpdateScrollBars test function for testing the 
     *     UpdateScrollBars function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCSUpdateScrollBars( CStifItemParser& aItem );
    /**
     * TestCCDefaultConstructorL test function for testing the 
     *     Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCCDefaultConstructorL( CStifItemParser& aItem );
    /**
     * TestCCDestructor test function for testing the 
     *     Destructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCCDestructor( CStifItemParser& aItem );
    /**
     * TestCCConstructL test function for testing the 
     *     ConstructL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCCConstructL( CStifItemParser& aItem );
    /**
     * TestCCConstructWithPointL test function for testing the 
     *     ConstructL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCCConstructWithPointL( CStifItemParser& aItem );
    /**
     * TestCCSetRedrawer test function for testing the 
     *     SetRedrawer function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCCSetRedrawer( CStifItemParser& aItem );
    /**
     * TestCCSetFontL test function for testing the 
     *     SetFontL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCCSetFontL( CStifItemParser& aItem );
    /**
     * TestCCFont test function for testing the 
     *     Font function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCCFont( CStifItemParser& aItem );
    /**
     * TestCCCharSize test function for testing the 
     *     CharSize function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCCCharSize( CStifItemParser& aItem );
    /**
     * TestCCVisibleSize test function for testing the 
     *     VisibleSize function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCCVisibleSize( CStifItemParser& aItem );
    /**
     * TestCCSetCursorHeight test function for testing the 
     *     SetCursorHeight function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCCSetCursorHeight( CStifItemParser& aItem );
    /**
     * TestCCDrawCursor test function for testing the 
     *     DrawCursor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCCDrawCursor( CStifItemParser& aItem );
    /**
     * TestCCHideCursor test function for testing the 
     *     HideCursor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCCHideCursor( CStifItemParser& aItem );
    /**
     * TestCCDrawChars test function for testing the 
     *     DrawChars function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCCDrawChars( CStifItemParser& aItem );
    /**
     * TestCCClearChars test function for testing the 
     *     ClearChars function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCCClearChars( CStifItemParser& aItem );
    /**
     * TestCCInvertChars test function for testing the 
     *     InvertChars function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCCInvertChars( CStifItemParser& aItem );
    /**
     * TestCCScrollChars test function for testing the 
     *     ScrollChars function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCCScrollChars( CStifItemParser& aItem );
    /**
     * TestCCSetScrollBarVisibilityL test function for testing the 
     *     SetScrollBarVisibilityL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCCSetScrollBarVisibilityL( CStifItemParser& aItem );
    /**
     * TestCCUpdateScrollbarsL test function for testing the 
     *     UpdateScrollbarsL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCCUpdateScrollbarsL( CStifItemParser& aItem );
    /**
     * TestCCHandleScrollEventL test function for testing the 
     *     HandleScrollEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCCHandleScrollEventL( CStifItemParser& aItem );
    /**
     * TestCCUpdateArea test function for testing the 
     *     UpdateArea function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCCUpdateArea( CStifItemParser& aItem );
    /**
     * TestCCGetColorUseListL test function for testing the 
     *     GetColorUseListL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCCGetColorUseListL( CStifItemParser& aItem );
    /**
     * TestCCHandleResourceChange test function for testing the 
     *     HandleResourceChange function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCCHandleResourceChange( CStifItemParser& aItem );
    /**
     * TestCCHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCCHandlePointerEventL( CStifItemParser& aItem );
    /**
     * TestCCDrawL test function for testing the 
     *     Draw function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCCDrawL( CStifItemParser& aItem );
    /**
     * TestCCSizeChangedL test function for testing the 
     *     SizeChanged function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCCSizeChangedL( CStifItemParser& aItem );
    /**
     * TestCCFocusChangedL test function for testing the 
     *     FocusChanged function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCCFocusChangedL( CStifItemParser& aItem );
    /**
     * TestCCCountComponentControlsL test function for testing the 
     *     CountComponentControls function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCCCountComponentControlsL( CStifItemParser& aItem );
    /**
     * TestCCComponentControlL test function for testing the 
     *     ComponentControl function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCCComponentControlL( CStifItemParser& aItem );
    /**
     * TestCCWriteInternalStateL test function for testing the 
     *     WriteInternalStateL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCCWriteInternalStateL( CStifItemParser& aItem );
    //for test misc_controls_api eikctgrp.h
    /**
     * TestGCConstructorL test function for testing the 
     *     Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGCConstructorL( CStifItemParser& aItem );
    /**
     * TestGCConstructorWithControlL test function for testing the 
     *     Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGCConstructorWithControlL( CStifItemParser& aItem );
    /**
     * TestGCIsLengthSet test function for testing the 
     *     IsLengthSet function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGCIsLengthSet( CStifItemParser& aItem );
    /**
     * TestGCLength test function for testing the 
     *     Length function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGCLength( CStifItemParser& aItem );
    /**
     * TestGCIsStretchable test function for testing the 
     *     IsStretchable function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGCIsStretchable( CStifItemParser& aItem );
    /**
     * TestGCSetLength test function for testing the 
     *     SetLength function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGCSetLength( CStifItemParser& aItem );
    /**
     * TestGCSetStretchable test function for testing the 
     *     SetStretchable function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGCSetStretchable( CStifItemParser& aItem );
    /**
     * TestCGConstructorL test function for testing the 
     *     Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCGConstructorL( CStifItemParser& aItem );
    /**
     * TestCGDestructor test function for testing the 
     *     Destructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCGDestructor( CStifItemParser& aItem );
    /**
     * TestCGConstructL test function for testing the 
     *     ConstructL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCGConstructL( CStifItemParser& aItem );
    /**
     * TestCGAddControlL test function for testing the 
     *     AddControlL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCGAddControlL( CStifItemParser& aItem );
    /**
     * TestCGAddControlWithGroupControlL test function for testing the 
     *     AddControlL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCGAddControlWithGroupControlL( CStifItemParser& aItem );
    /**
     * TestCGInsertControlL test function for testing the 
     *     InsertControlL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCGInsertControlL( CStifItemParser& aItem );
    /**
     * TestCGDeleteControl test function for testing the 
     *     DeleteControl function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCGDeleteControl( CStifItemParser& aItem );
    /**
     * TestCGSetLengthInPixels test function for testing the 
     *     SetLengthInPixels function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCGSetLengthInPixels( CStifItemParser& aItem );
    /**
     * TestCGSetBreadthInPixels test function for testing the 
     *     SetBreadthInPixels function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCGSetBreadthInPixels( CStifItemParser& aItem );
    /**
     * TestCGSetControlSpacing test function for testing the 
     *     SetControlSpacing function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCGSetControlSpacing( CStifItemParser& aItem );
    /**
     * TestCGSetControlLayout test function for testing the 
     *     SetControlLayout function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCGSetControlLayout( CStifItemParser& aItem );
    /**
     * TestCGSetNumberOfLines test function for testing the 
     *     SetNumberOfLines function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCGSetNumberOfLines( CStifItemParser& aItem );
    /**
     * TestCGSetControlsAllSameSize test function for testing the 
     *     SetControlsAllSameSize function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCGSetControlsAllSameSize( CStifItemParser& aItem );
    /**
     * TestCGLayoutControls test function for testing the 
     *     LayoutControls function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCGLayoutControls( CStifItemParser& aItem );
    /**
     * TestCGControlByIdL test function for testing the 
     *     ControlById function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCGControlByIdL( CStifItemParser& aItem );
    /**
     * TestCGIndexById test function for testing the 
     *     IndexById function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCGIndexById( CStifItemParser& aItem );
    /**
     * TestCGIndexById test function for testing the 
     *     Reset function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCGReset( CStifItemParser& aItem );
    /**
     * TestCGControlId test function for testing the 
     *     ControlId function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCGControlId( CStifItemParser& aItem );
    /**
     * TestCGCControl test function for testing the 
     *     Control function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCGControlL( CStifItemParser& aItem );
    /**
     * TestCGControlArrayL test function for testing the 
     *     ControlArray function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCGControlArrayL( CStifItemParser& aItem );
    /**
     * TestCGOrientation test function for testing the 
     *     Orientation function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCGOrientation( CStifItemParser& aItem );
    /**
     * TestCGControlSpacing test function for testing the 
     *     ControlSpacing function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCGControlSpacing( CStifItemParser& aItem );
    /**
     * TestCGMinimumSize test function for testing the 
     *     MinimumSize function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCGMinimumSize( CStifItemParser& aItem );
    /**
     * TestCGCountComponentControls test function for testing the 
     *     CountComponentControls function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCGCountComponentControls( CStifItemParser& aItem );
    /**
     * TestCGGetColorUseListL test function for testing the 
     *     GetColorUseListL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCGGetColorUseListL( CStifItemParser& aItem );
    /**
     * TestCGHandleResourceChange test function for testing the 
     *     HandleResourceChange function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCGHandleResourceChange( CStifItemParser& aItem );
    /**
     * TestCGHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCGHandlePointerEventL( CStifItemParser& aItem );
    /**
     * TestCGComponentControlL test function for testing the 
     *     ComponentControl function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCGComponentControlL( CStifItemParser& aItem );
    /**
     * TestCGWriteInternalStateL test function for testing the 
     *     WriteInternalStateL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCGWriteInternalStateL( CStifItemParser& aItem );
    //for test misc_controls_api eikmover.h
    /**
     * TestEMConstructorL test function for testing the 
     *     Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEMConstructorL( CStifItemParser& aItem );
    /**
     * TestEMDestructor test function for testing the 
     *     Destructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEMDestructor( CStifItemParser& aItem );
    /**
     * TestEMSetTextNoL test function for testing the 
     *     SetText function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEMSetTextNoL( CStifItemParser& aItem );
    /**
     * TestEMSetTextL test function for testing the 
     *     SetTextL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEMSetTextL( CStifItemParser& aItem );
    /**
     * TestEMSetActive test function for testing the 
     *     SetActive function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEMSetActive( CStifItemParser& aItem );
    /**
     * TestEMActive test function for testing the 
     *     Active function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEMActive( CStifItemParser& aItem );
    /**
     * TestEMSetFontL test function for testing the 
     *     SetFont function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEMSetFontL( CStifItemParser& aItem );
    /**
     * TestEMSetTitleLeftMargin test function for testing the 
     *     SetTitleLeftMargin function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEMSetTitleLeftMargin( CStifItemParser& aItem );
    /**
     * TestEMConstructFromResourceL test function for testing the 
     *     ConstructFromResourceL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEMConstructFromResourceL( CStifItemParser& aItem );
    /**
     * TestEMMinimumSize test function for testing the 
     *     MinimumSize function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEMMinimumSize( CStifItemParser& aItem );
    /**
     * TestEMSetContainerWindowL test function for testing the 
     *     SetContainerWindowL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEMSetContainerWindowL( CStifItemParser& aItem ); /**
     * TestEMGetColorUseListL test function for testing the 
     *     GetColorUseListL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEMGetColorUseListL( CStifItemParser& aItem );
    /**
     * TestEMHandleResourceChange test function for testing the 
     *     HandleResourceChange function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEMHandleResourceChange( CStifItemParser& aItem );
    /**
     * TestEMHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEMHandlePointerEventL( CStifItemParser& aItem );
    /**
     * TestEMWriteInternalStateL test function for testing the 
     *     WriteInternalStateL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestEMWriteInternalStateL( CStifItemParser& aItem );
    /**
     * TestTBConstructorL test function for testing the 
     *     Constructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestTBConstructorL( CStifItemParser& aItem );
    /**
     * TestTBDestructor test function for testing the 
     *     Destructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestTBDestructor( CStifItemParser& aItem );
    /**
     * TestTBConstructL test function for testing the 
     *     ConstructL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestTBConstructL( CStifItemParser& aItem );
    /**
     * TestTBStaticConstructL test function for testing the 
     *     StaticConstructL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestTBStaticConstructL( CStifItemParser& aItem );
    /**
     * TestTBSetCommandObserverL test function for testing the 
     *     SetCommandObserver function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestTBSetCommandObserverL( CStifItemParser& aItem );
    /**
     * TestTBCoordinateButtonsL test function for testing the 
     *     CoordinateButtons function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestTBCoordinateButtonsL( CStifItemParser& aItem );
    /**
     * TestTBSetButtonStateOnL test function for testing the 
     *     SetButtonStateOn function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestTBSetButtonStateOnL( CStifItemParser& aItem );
    /**
     * TestTBDelayActivation test function for testing the 
     *     DelayActivation function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestTBDelayActivation( CStifItemParser& aItem );
    /**
     * TestTBConstructFromResourceL test function for testing the 
     *     ConstructFromResourceL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestTBConstructFromResourceL( CStifItemParser& aItem );
    /**
     * TestTBSetDimmed test function for testing the 
     *     SetDimmed function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestTBSetDimmed( CStifItemParser& aItem );
    /**
     * TestTBGetColorUseListL test function for testing the 
     *     GetColorUseListL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestTBGetColorUseListL( CStifItemParser& aItem );
    /**
     * TestTBHandleResourceChange test function for testing the 
     *     HandleResourceChange function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestTBHandleResourceChange( CStifItemParser& aItem );
    /**
     * TestTBHandlePointerEventL test function for testing the 
     *     HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestTBHandlePointerEventL( CStifItemParser& aItem );
    /**
     * TestTBAddControlL test function for testing the 
     *     AddControlL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestTBAddControlL( CStifItemParser& aItem );
    /**
     * TestTBAddControlWithGroupL test function for testing the 
     *     AddControlL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestTBAddControlWithGroupL( CStifItemParser& aItem );
    /**
     * TestTBSetBoundingRect test function for testing the 
     *     SetBoundingRect function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestTBSetBoundingRect( CStifItemParser& aItem );
    /**
     * TestTBReduceRect test function for testing the 
     *     ReduceRect function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestTBReduceRect( CStifItemParser& aItem );
    /**
     * TestTBWriteInternalStateL test function for testing the 
     *     WriteInternalStateL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestTBWriteInternalStateL( CStifItemParser& aItem );
private:    // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;
    
    CEikCaptionedControl* iCaptionedControl;
    CEikCapCArray* iCapCArray;
    CEikConsoleScreen* iConsoleScreen;
    CEikConsoleControl* iConsoleControl;
    CMiscControlsContainer* iConsoleContainer;
    CMiscControlView* iConsoleView;
    TEikGroupControl* iGroupControl;
    CEikControlGroup* iControlGroup;
    CEikMover* iMover;
    CEikToolBar* iToolBar;

    // Resource file offset
    TInt iOffset;
    };

#endif      // C_TESTSDKMISCCONTROLS_H

// End of File
