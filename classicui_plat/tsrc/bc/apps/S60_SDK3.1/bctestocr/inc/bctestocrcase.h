/*
* Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:         Declares test bc for ocr testcase.
*
*/









#ifndef C_CBCTESTOCRCASE_H
#define C_CBCTESTOCRCASE_H

#include <AknProgressDialog.h>
#include <f32file.h>
#include <s32file.h>
#include <hal.h>
#include <ocrsrv.h>
#include <ocrcommon.h>

#include "bctestcase.h"

class CBCTestOCRContainer;
class CCoeControl;
class CAknWaitDialog;
class CEikonEnv;

/**
 * test case for various misc control classes
 */
class CBCTestOCRCase: public CBCTestCase, 			
                      public MOCREngineObserver,
			          public MProgressDialogCallback
    {
public: // constructor and destructor

    /**
     * Symbian 2nd static constructor
     */
    static CBCTestOCRCase* NewL( CBCTestOCRContainer* aContainer );

    /**
     * Destructor
     */
    virtual ~CBCTestOCRCase();
	
// from CBCTestCase

    /**
     * Execute corresponding test functions for UI command
     * @param aCmd, UI command
     */
    void RunL( TInt aCmd );
    
// from MProgressDialogCallback 
   
    /**
     * Callback method
     * Get's called when a dialog is dismissed.
     * @param aButtonId button id to the dialog
     */    
    void DialogDismissedL ( TInt /*aButtonId*/ );

// from MOCREngineObserver

    /**
     * This function will be called after the Full Image Recognition is 
     * completed. This calling only valid when using the 
     * EEngineLayoutRecognize type of engine   
     * @param aError Error code to indicate the completion status
     * @param aBlocks Pointer to the text information of the recognized image
     *                block, Please note that the memory ownership belongs to 
     *                the OCR engine and will not be passed to your procedure 
     *                after this calling
     * @param aBlockCount Number of block identified
     */    
    void RecognizeComplete( TInt aError, 
                            const TOCRTextRgnInfo* aBlock, 
                            const TInt aBlockCount ); 
       
    /**
     * This interface will be called after the Full Image Layout Analysis is 
     * completed. This calling only valid when using the EEngineLayoutRecognize
     * type of engine 
     * @param aError Error code to indicate the completion status
     * @param aBlocks Pointer to the text information of the recognized image 
     *                block, Please note that the memory ownership belongs to
     *                the OCR engine and will not be passed to your procedure 
     *                after this calling
     * @param aBlockCount Number of block identified
     */
    void LayoutComplete( TInt aError, 
                         const TOCRBlockInfo* /*aBlock*/, 
                         const TInt aBlockCount );
                         
    /**
     * This interface will be called during the procession and indicates 
     * the progress.
     * @param aPercent A percentage of the current progression
     */
    void RecognizeProcess( const TUint aPercent );
    
    /**
     * This interface will be called after the Block Recognition is completed.
     * This calling only valid when using the EEngineRecognizeBlock type of 
     * engine   
     * @param aError Error code to indicate the completion status
     * @param aBlocks Pointer to the text information of the recognized image 
     *                block, Please note that the memory ownership belongs to
     *                the OCR engine and will not be passed to your procedure
     *                after this calling
     * @param aBlockCount Number of block identified
     */ 
    void RecognizeBlockComplete( TInt aError, 
                                 const TOCRTextRgnInfo* aBlock, 
                                 const TInt aBlockCount ); 
                                 
    /**
     * This interface will be called after the Special Region Recognition is
       completed. This calling
     * only valid when using the EEngineRecognizeBlock type of engine   
     * @param aError Error code to indicate the completion status
     * @param aBlocks Pointer to the text information of the recognized image
                      block, Please note that the memory ownership belongs to
                      the OCR engine and will not be passed to your procedure 
                      after this calling
     * @param aBlockCount Number of block identified
     */
    void RecognizeSpecialRegionComplete( TInt aError, 
                                         const TOCRTextRgnInfo* aBlock,
                                         const TInt aBlockCount );     

protected: // new functions

    /**
     * Build autotest script
     */
    void BuildScriptL();

    /**
     * TestFunctionsForOCRL  function
     */
    void TestFunctionsForOCRL();
    
private: // constructor

    /**
     * C++ default constructor
     */
    CBCTestOCRCase( CBCTestOCRContainer* aContainer );

    /**
     * Symbian 2nd constructor
     */
    void ConstructL();

    /**
     * DoRecgonizeBlock function
     */    
	void DoRecgonizeBlock();

    /**
     * DoRecgonizeSpecialRegion function
     */    
	void DoRecgonizeSpecialRegion();    

private: // data

    /**
     * Pointer to container.
     * not own
     */
    CBCTestOCRContainer* iContainer;
    
    /**
     * Pointer to MOCREngineLayoutRecognize.
     * own
     */ 
    MOCREngineLayoutRecognize* iEngine;
    
    /**
     * Pointer to MOCREngineRecognizeBlock.
     * own
     */    
    MOCREngineRecognizeBlock* iEngine2;
    
    /**
     * object to TOcrEngineEnv.
     */
    TOcrEngineEnv iEngineEnv;

    /**
     * Pointer to TLanguage.
     * own
     */     
    RArray<TLanguage> iLanguages;

    };

#endif // C_CBCTESTOCRCASE_H
