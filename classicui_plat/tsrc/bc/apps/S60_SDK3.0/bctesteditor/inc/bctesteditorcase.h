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
* Description:         test case
*
*/









#include <eikdialg.h>
#include <eikenv.h>
#include <e32std.h>
#include <coedef.h>
#include <eikmfne.h>
#include <Aknedsts.h>
#include <aknipfed.h>
#include <aknnumed.h>
#include <aknnumedwin.h>
#include <eikccpu.h>
#include <eikedwin.h>
#include <eikfpne.h>
#include <eikrted.h>
#include <aknnumseced.h>
#include <eikseced.h>
#include <eikdgfty.h>

#include "bctestcase.h"
 

class CTestNumericEdwin : public CAknNumericEdwin
    {
public:
	void TestFunction();
    };

class CBCTestEditorContainer;
class CCoeControl;
class TAknEditorCaseState;
class CAknEdwinState;
class CAknIpFieldEditor;
class CAknIntegerEdwin;
class CAknCcpuSupport;
class CEikMenuPane;
class CEikEdwin;
class CEikFixedPointEditor;
class CEikFloatingPointEditor;
class CEikRichTextEditor;
class CBCTestSecretEditor;

/**
* test case for various list classes
*/
class CBCTestEditorCase: public CBCTestCase
    {
public: // constructor and destructor
    
    /**
    * Symbian 2nd static constructor
    */
    static CBCTestEditorCase* NewL( CBCTestEditorContainer* aContainer );
    
    /**
    * Destructor
    */
    virtual ~CBCTestEditorCase();
    
public: // from CBCTestCase
    
    /**
    * Execute corresponding test functions for UI command
    * @param aCmd, UI command
    */
    void RunL( TInt aCmd );

protected: // new functions
    
    /**
    * Build autotest script
    */
    void BuildScriptL();
    
    /**
     * Create control or allocate resource for test
     * @param aCmd UI command, maybe you need to do some work 
     * for different outline
     */
    void PrepareCaseL( TInt aCmd );
    
    /**
     * Release resource used in test
     */
    void ReleaseCaseL();
    
    /**
     * Test functions
     */
    void TestEdwinStateL();
    void TestIpFieldEditorL();
    void TestNumericEdwinL();
    void TestCcpuSupportL();
    void TestEikEdwinL();
    void TestEikFixedPointEditorL();
    void TestEikFloatingPointEditorL();
    void TestEikRichTextEditorL();
    void TestEikMfneSubClassL();
    void TestEikTimeEditorL();
    void TestEikSecretEditorL();
    void TestEikMfneFieldL();
    void TestEikGlobalEditorL();
    void TestEikLafMainL();
    void TestEikMfneL();
        
private: // constructor
    
    /**
     * C++ default constructor
     */
    CBCTestEditorCase( CBCTestEditorContainer* aContainer );
    
    /**
     * Symbian 2nd constructor
     */
    void ConstructL();
    
private: // data
    
    /**
     * Pointer to a control, maybe you need one in your test
     * own
     */
    CCoeControl* iControl;
    CAknEdwinState* iAknEdwinState;
    CAknIpFieldEditor* iAknIpFieldEditor;
    CTestNumericEdwin* iAknNumericEdwin;
    CAknIntegerEdwin* iAknIntegerEdwin;
    CAknCcpuSupport* iAknCcpuSupport;
	CEikMenuPane * iPane;
	CEikEdwin* iEikEdwin;
    CEikFixedPointEditor* iEikFixedPointEditor;
    CEikFloatingPointEditor* iEikFloatingPointEditor;
    CEikRichTextEditor* iEikRichTextEditor;
    CEikDurationEditor* iEikDurationEditor;
    CEikNumberEditor* iEikNumberEditor;
    CEikRangeEditor* iEikRangeEditor;
    CEikTimeOffsetEditor* iEikTimeOffsetEditor;
    CEikTimeAndDateEditor* iEikTimeAndDateEditor;
    CEikTimeEditor* iEikTimeEditor;
    CEikDateEditor* iEikDateEditor;
    CBCTestSecretEditor* iEikSecretEditor;
    CEikGlobalTextEditor* iEikGlobalTextEditor;
    CEikMfne* iEikMfne;
    
    CEikonEnv* iEikEnv;
    /**
     * Pointer to container.
     * not own
     */
    CBCTestEditorContainer* iContainer;
    
    };
    
class CBCTestSecretEditor: public CEikSecretEditor
    {
    friend class CBCTestEditorCase;
    
public:
    
    void StartFepInlineEditL(TBool& aSetToTrue, const TCursorSelection& aCursorSelection, 
        const TDesC& aInitialInlineText, 
        TInt aPositionOfInsertionPointInInlineText, 
        TBool aCursorVisibility, 
        const MFormCustomDraw* aCustomDraw, 
        MFepInlineTextFormatRetriever& aInlineTextFormatRetriever, 
        MFepPointerEventHandlerDuringInlineEdit& aPointerEventHandlerDuringInlineEdit);
    MCoeFepLayDocExtension* GetFepLayDocExtension(TBool& aSetToTrue);
    void SetCursorType(TBool& aSetToTrue, const TTextCursor& aTextCursor);
    
    };

class CMClassTmp : public CBase,public MEikRichTextEditorParserObserver
    {
	void HandleCursorOverParserL( const TDesC& );
    };
 
class CMObserverClassTmp : public CBase, public MAknEdStateObserver
    {
    void HandleAknEdwinStateEventL( CAknEdwinState* aAknEdwinState,
		EAknEdwinStateEvent aEventType );
    };

class CSubEikEdwin : public CEikEdwin
    {
	public:
	void TestFunctionL();
    }; 
   
class CSubEikRichTextEditor : public CEikRichTextEditor
    {
	public:
	void TestWriteInternalStateL( RWriteStream& aWriteStream );
    }; 
     
class CSubEikMfne : public CEikMfne
    {
    public:
    void TestFunction();	
    };
    
class MEikFindAndReplaceDlgObserver;
class CGraphicsDevice;
    
class CTmpCDlgDialogFactory : public CBase, public MEikCDlgDialogFactory
	{
public:
    static CTmpCDlgDialogFactory* NewL();
private:
	CTmpCDlgDialogFactory();
	TBool RunCharMapDlgLD(CCoeControl* aControl);
	TBool RunFontDlgLD(		TCharFormat& aFormat,
							TCharFormatMask& aAttribChangedMask,
							TCharFormatMask& aUndeterminedMask,
							TDesC& aTextSelection,
							TInt aFonts,
							CGraphicsDevice* aGraphicsDevice, 
							TInt aFontControlFalgs,
							const TRgb aBackGroundColor);

	TBool RunInsertObjectDlgLD(	CEikEmbeddableAppList*	aList,
								TInt&					aChoice);

	TBool RunObjectInfoDlgLD(const TDesC& aCaption);
	TBool RunFormatObjectDlgLD(	CApaDoor&		aDoor,
								CApaDocument&	aDoc,
								const TSize&	aDefaultIconSize);

	void RunEdwinFindAndReplaceDlgLD(MEikFindAndReplaceDlgObserver& aObserver,
		SEdwinFindModel& aModel, TBool aFindOnly, TRect aEdwinRect);
	
	TBool RunEdwinFindDlgLD(	SEdwinFindModel*	aModel,
								CDesCArray*			aFindList);

	TBool RunEdwinReplaceDlgLD(	SEdwinFindModel* aModel,
								CDesCArray*		aFindList,
								CDesCArray*		aReplaceList);

	TBool RunEdwinReplaceOptionDlgLD(	CEikGlobalTextEditor*	aEdwin,
										SEdwinFindModel*		aModel);

	TBool RunAlignDlgLD(
						CParaFormat*		aFormat, 
						TParaFormatMask&	aAttribChangedMask, 
						TParaFormatMask&	aUndeterminedMask);

	TBool RunBorderDlgLD(
						CParaFormat*		aFormat, 
						TParaFormatMask&	aAttribChangedMask, 
						TParaFormatMask&	aUndeterminedMask);

	TBool RunSpaceDlgLD(
						CParaFormat*		aFormat, 
						TParaFormatMask&	aAttribChangedMask, 
						TParaFormatMask&	aUndeterminedMask);

	TBool RunTabsDlgLD(	CParaFormat*		aFormat, 
						TParaFormatMask&	aAttribChangedMask, 
						TParaFormatMask&	aUndeterminedMask,
						const TInt			aPageWidth);

	TBool RunIndentDlgLD(	CParaFormat*		aFormat, 
							TParaFormatMask&	aAttribChangedMask, 
							TParaFormatMask&	aUndeterminedMask,
							const TInt			aPageWidth);
	};

class CPrintSetup;	
class CTmpPrintDialogFactory : public CBase, public MEikPrintDialogFactory
    {
    public:
	TBool RunPaginateDlgLD(	CEikGlobalTextEditor*	aEditor,
									CPrintSetup*			aPrintSetup,
									CArrayFix<TInt>*		aCharsPerPage);

	CPrintSetup* NewDefaultPrintSetupL();

    };
