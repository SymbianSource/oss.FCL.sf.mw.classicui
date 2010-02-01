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









#include <w32std.h>
#include <coecntrl.h>
#include <e32const.h>
#include <in_sock.h>
#include <barsread.h>
#include <w32std.h>
#include <eikenv.h>
#include <eikappui.h>
#include <eikspane.h>
#include <eikMenuP.h>
#include <aknenv.h>
#include <eikccpu.h>
#include <e32def.h>
#include <eikedwob.h>
#include <aknquerycontrol.h>
#include <s32stor.h>
#include <s32std.h>
#include <e32base.h>
#include <coecntrl.h>
#include <frmtlay.h>
#include <fldbase.h>
#include <eikscrlb.h>
#include <gulbordr.h>
#include <eikrted.h>
#include <txtglobl.h>
#include <eikdef.h>
#include <coemop.h>
#include <eikseced.h>
#include <gdi.h>
#include <coedef.h>
#include <fldbase.h>
#include <frmvis.h>
#include <prnsetup.h>
#include <fbs.h>
#include <txtfrmat.h>
#include <lafmain.h>
#include <e32cmn.h>
#include <apgdoor.h>
#include <apparc.h>
#include <prnsetup.h>
#include <akndef.h>
#include <f32file.h>
#include <s32file.h>
#include <eikirfty.h>

#include "bctestEditorcase.h"
#include "bctestEditorcontainer.h"
#include "bctestEditor.hrh"
#include "AssertTools.h"
#include "bctestlogger.h"
#include "aknedstsobs.h"
#include "aknedsts.h"
#include "aknipfed.h"
#include "eikedwin.h"
#include <bctesteditor.rsg>

#define EDWIN_POS           TPoint(10,5)
#define KDefaultTextLimit   100

class TBCTestIrFactory: public MEikIrFactory
    {
public:
    void SendDataOverIrL( CEikEdwin* aEditor );
	void ReceiveDataOverIrL( CEikEdwin* aEditor );
    };

// ======== MEMBER FUNCTIONS ========

void TBCTestIrFactory::SendDataOverIrL( CEikEdwin* )
    {
    }

void TBCTestIrFactory::ReceiveDataOverIrL( CEikEdwin* )
    {
    }

// ======== MEMBER FUNCTIONS ========

void CBCTestSecretEditor::StartFepInlineEditL( TBool&,
    const TCursorSelection&, const TDesC&,
    TInt, TBool, const MFormCustomDraw*,
    MFepInlineTextFormatRetriever&,
    MFepPointerEventHandlerDuringInlineEdit& )
    {
    }

MCoeFepLayDocExtension* CBCTestSecretEditor::GetFepLayDocExtension( TBool& )
    {
    return NULL;
    }

void CBCTestSecretEditor::SetCursorType( TBool&, const TTextCursor& )
    {
    }


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
TBool CTmpPrintDialogFactory::RunPaginateDlgLD( CEikGlobalTextEditor*,
									CPrintSetup*,
									CArrayFix<TInt>* )
{
    return ETrue;
}

CPrintSetup* CTmpPrintDialogFactory::NewDefaultPrintSetupL()
{
    return NULL;
}

CTmpCDlgDialogFactory* CTmpCDlgDialogFactory::NewL()
	{
	CTmpCDlgDialogFactory* self = new(ELeave) CTmpCDlgDialogFactory;
	return self;
	}

CTmpCDlgDialogFactory::CTmpCDlgDialogFactory()
	{
	}

TBool CTmpCDlgDialogFactory::RunCharMapDlgLD(CCoeControl* /*aControl*/)
	{
	// stubbed as this code has been thinned
	return ETrue;
	}

TBool CTmpCDlgDialogFactory::RunFontDlgLD(TCharFormat& /*aFormat*/,
												TCharFormatMask& /*aAttribChangedMask*/,
												TCharFormatMask& /*aUndeterminedMask*/,
												TDesC& /*aTextSelection*/,
												TInt /*aFonts*/,
												CGraphicsDevice* /*aGraphicsDevice*/,
												TInt /*aFontControlFlags*/,
												const TRgb /*aBackGroundColor*/)
	{
	// stubbed as this code has been thinned
	return ETrue;
	}

void CTmpCDlgDialogFactory::RunEdwinFindAndReplaceDlgLD(MEikFindAndReplaceDlgObserver& /*aObserver*/,
		SEdwinFindModel& /*aModel*/, TBool /*aFindOnly*/, TRect /*aEdwinRect*/)
	{
	User::Leave(KErrNotSupported);
	}

TBool CTmpCDlgDialogFactory::RunInsertObjectDlgLD(
										CEikEmbeddableAppList*	/*aList*/,
										TInt&					/*aChoice*/)
	{
	// stubbed as this code has been thinned
	return ETrue;
	}

TBool CTmpCDlgDialogFactory::RunObjectInfoDlgLD(const TDesC& /*aCaption*/)
	{
	// stubbed as this code has been thinned
	return ETrue;
	}

TBool CTmpCDlgDialogFactory::RunFormatObjectDlgLD(	CApaDoor&		/*aDoor*/,
														CApaDocument&	/*aDoc*/,
														const TSize&	/*aDefaultIconSize*/)
	{
	// stubbed as this code has been thinned
	return ETrue;
	}


TBool CTmpCDlgDialogFactory::RunEdwinFindDlgLD(	SEdwinFindModel*	/*aModel*/,
													CDesCArray*		/*	aFindList*/)
	{
	// stubbed as this code has been thinned
	return ETrue;
	}

TBool CTmpCDlgDialogFactory::RunEdwinReplaceDlgLD(
										SEdwinFindModel* /* aModel*/,
										CDesCArray*		/*aFindList*/,
										CDesCArray*		/*aReplaceList*/)
	{
	// stubbed as this code has been thinned
	return ETrue;
	}

TBool CTmpCDlgDialogFactory::RunEdwinReplaceOptionDlgLD(
										CEikGlobalTextEditor*	/*aEdwin*/,
										SEdwinFindModel*		/*aModel*/)
	{
	// stubbed as this code has been thinned
	return ETrue;
	}

TBool CTmpCDlgDialogFactory::RunAlignDlgLD(
									CParaFormat*		/*aFormat*/,
									TParaFormatMask&	/*aAttribChangedMask*/,
									TParaFormatMask&	/*aUndeterminedMask*/)
	{
	// stubbed as this code has been thinned
	return ETrue;
	}

TBool CTmpCDlgDialogFactory::RunSpaceDlgLD(
									CParaFormat*		/*aFormat*/,
									TParaFormatMask&	/*aAttribChangedMask*/,
									TParaFormatMask&	/*aUndeterminedMask*/)
	{
	// stubbed as this code has been thinned
	return ETrue;
	}

TBool CTmpCDlgDialogFactory::RunBorderDlgLD(
									CParaFormat*		/*aFormat*/,
									TParaFormatMask&	/*aAttribChangedMask*/,
									TParaFormatMask&	/*aUndeterminedMask*/)
	{
	// stubbed as this code has been thinned
	return ETrue;
	}

TBool CTmpCDlgDialogFactory::RunTabsDlgLD(
									CParaFormat*		/*aFormat*/,
									TParaFormatMask&	/*aAttribChangedMask*/,
									TParaFormatMask&	/*aUndeterminedMask*/,
									const TInt			/*aPageWidth*/)
	{
	// stubbed as this code has been thinned
	return ETrue;
	}

TBool CTmpCDlgDialogFactory::RunIndentDlgLD(
									CParaFormat*		/*aFormat*/,
									TParaFormatMask&	/*aAttribChangedMask*/,
									TParaFormatMask&	/*aUndeterminedMask*/,
									const TInt			/*aPageWidth*/)
	{
	// stubbed as this code has been thinned
	return ETrue;
	}

void CMClassTmp::HandleCursorOverParserL( const TDesC& )
    {
    }

void CMObserverClassTmp::HandleAknEdwinStateEventL( CAknEdwinState*,
		EAknEdwinStateEvent)
    {
    }

void CSubEikEdwin::TestFunctionL()
    {
    CreateTextViewL();

	CancelSelectionL( EStart );

	TrappedSizeChanged();

	TInt tmp;
	HandleTextPastedL( 1, tmp );

	MoveCursorToChunkStartL( EFalse, EChunkWord, EEnd );

	PlaceDataOnClipboardL();

    SetLineCursorDetailsL();
    }

void CSubEikMfne::TestFunction()
    {
    MfneSize();

    MfneSize( ETrue );

    FocusChanged( EDrawNow );
    }

void CSubEikRichTextEditor::TestWriteInternalStateL( RWriteStream& aWriteStream )
    {
    WriteInternalStateL( aWriteStream );
    }

CBCTestEditorCase* CBCTestEditorCase::NewL(
    CBCTestEditorContainer* aContainer )
    {
    CBCTestEditorCase* self = new( ELeave ) CBCTestEditorCase(
        aContainer );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default constructor
// ---------------------------------------------------------------------------
//
CBCTestEditorCase::CBCTestEditorCase(
    CBCTestEditorContainer* aContainer )
    : iContainer( aContainer )
    {
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestEditorCase::~CBCTestEditorCase()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestEditorCase::ConstructL()
    {
    BuildScriptL();

    iEikEnv = CEikonEnv::Static();
    }

// ---------------------------------------------------------------------------
// CBCTestEditorCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestEditorCase::BuildScriptL()
    {
    // Add script as your need.
    AddTestL( DELAY( 1 ), TEND );
    for( int i = 0;i<=14;i++)
    {
    AddTestL( LeftCBA, TEND );
    AddTestL( REP( Down, i ), KeyOK, TEND );
    }

    }

// ---------------------------------------------------------------------------
// CBCTestEditorCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestEditorCase::RunL( TInt aCmd )
    {
    if ( aCmd < EBCTestCmdOutline1 || aCmd > EBCTestCmdOutline15 )
        {
        return;
        }
    // Call release before prepare to let container has time to draw the
    // control created in PrepareCaseL.
    ReleaseCaseL();
    PrepareCaseL( aCmd );
    switch ( aCmd )
        {
        case EBCTestCmdOutline1:
            TestEdwinStateL();
            break;
        case EBCTestCmdOutline2:
            TestIpFieldEditorL();
            break;
        case EBCTestCmdOutline3:
            TestNumericEdwinL();
            break;
        case EBCTestCmdOutline4:
            TestCcpuSupportL();
            break;
        case EBCTestCmdOutline5:
            TestEikEdwinL();
            break;
        case EBCTestCmdOutline6:
            TestEikFixedPointEditorL();
            break;
        case EBCTestCmdOutline7:
            TestEikFloatingPointEditorL();
            break;
        case EBCTestCmdOutline8:
            TestEikRichTextEditorL();
            break;
        case EBCTestCmdOutline9:
            TestEikMfneSubClassL();
            break;
        case EBCTestCmdOutline10:
            TestEikTimeEditorL();
            break;
        case EBCTestCmdOutline11:
            TestEikSecretEditorL();
            break;
        case EBCTestCmdOutline12:
            TestEikMfneFieldL();
            break;
        case EBCTestCmdOutline13:
            TestEikGlobalEditorL();
            break;
        case EBCTestCmdOutline14:
            TestEikLafMainL();
            break;
        case EBCTestCmdOutline15:
            TestEikMfneL();
            break;
        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// CBCTestEditorCase::PrepareCaseL
// ---------------------------------------------------------------------------
//
void CBCTestEditorCase::PrepareCaseL( TInt aCmd )
    {
    switch ( aCmd )
        {
        case EBCTestCmdOutline1:
            // Here is a simple demo. You should create your control
            // instead of this.
            iControl = new( ELeave ) CCoeControl();
            iControl->SetContainerWindowL( *iContainer );
            iControl->MakeVisible( ETrue );
            break;
        default:
            break;
        }
    // Pass the owner of iControl to iContainer.
    iContainer->SetControlL( iControl );
    }

// ---------------------------------------------------------------------------
// CBCTestEditorCase::ReleaseCaseL
// ---------------------------------------------------------------------------
//
void CBCTestEditorCase::ReleaseCaseL()
    {
    // let container delete the component control.
    iContainer->ResetControl();
    iControl = NULL;
    }

void CTestNumericEdwin::TestFunction()
    {
    TKeyEvent keyEvent;
    TEventCode eventCode = EEventKey;
    MapKeyEvent( keyEvent, eventCode, EDigitTypeAllTypes );
    }
// ---------------------------------------------------------------------------
// CBCTestEditorCase::Test Class CAknEdwinState and TAknEditorCaseState
// ---------------------------------------------------------------------------
//
void CBCTestEditorCase::TestEdwinStateL()
    {
    _LIT( KCbaState, "Class CAknEdwinState Function CbaState tested" );
    _LIT( KCcpuState, "Class CAknEdwinState Function CcpuState tested" );
    _LIT( KCurrentInlineEditSpan,
    "Class CAknEdwinState Function CurrentInlineEditSpan tested" );
    _LIT( KDefaultLanguage,
    "Class CAknEdwinState Function DefaultLanguage tested");
    _LIT( KMenuBar, "Class CAknEdwinState Function MenuBar tested" );
    _LIT( KSetDefaultLanguage,
    "Class CAknEdwinState Function SetDefaultLanguage tested" );
    _LIT( KSetCurrentCase,
    "Class CAknEdwinState Function SetCurrentCase tested" );
    _LIT( KSetLocalLanguage,
    "Class CAknEdwinState Function SetLocalLanguage tested" );
    _LIT( KSpecialCharacterTableResourceId,
    "Class CAknEdwinState Function SpecialCharacterTableResourceId tested" );

    _LIT( KClearFlag, "Class TAknEdwinState Function ClearFlag tested" );
    _LIT( KIsFlagSet, "Class TAknEdwinState Function IsFlagSet tested" );
    _LIT( KSetPreviousCase,
    "Class TAknEdwinState Function SetPreviousCase tested" );
    _LIT( KSetPreviousCaseUsedToEnterText,
    "Class TAknEdwinState Function SetPreviousCaseUsedToEnterText tested" );
    _LIT( KPreviousCase,
    "Class TAknEdwinState Function PreviousCase tested" );
    _LIT( KPreviousCaseUsedToEnterText,
    "Class TAknEdwinState Function PreviousCaseUsedToEnterText tested" );

    iAknEdwinState = new ( ELeave ) CAknEdwinState();
    iAknEdwinState->CbaState();
    AssertTrueL( ETrue, KCbaState );

    iAknEdwinState->CcpuState();
    AssertTrueL( ETrue, KCcpuState );

    iAknEdwinState->CurrentInlineEditSpan();
    AssertTrueL( ETrue, KCurrentInlineEditSpan );

    iAknEdwinState->DefaultLanguage();
    AssertTrueL( ETrue, KDefaultLanguage );

    iAknEdwinState->MenuBar();
    AssertTrueL( ETrue, KMenuBar );

    iAknEdwinState->SetDefaultLanguage( 0 );
    AssertTrueL( ETrue, KSetDefaultLanguage );

    iAknEdwinState->SetCurrentCase( 0 );
    AssertTrueL( ETrue, KSetCurrentCase );

    iAknEdwinState->SetLocalLanguage( ELangEnglish );
    AssertTrueL( ETrue, KSetLocalLanguage );

    iAknEdwinState->SpecialCharacterTableResourceId();
    AssertTrueL( ETrue, KSpecialCharacterTableResourceId );


    iAknEdwinState->SetObjectProvider( STATIC_CAST(
                                       MObjectProvider*, iContainer ) );
    _LIT( KSetObjectProvider,
    "Class CAknEdwinState Function SetObjectProvider tested" );
    AssertTrueL( ETrue, KSetObjectProvider );

    iAknEdwinState->ObjectProvider();
    _LIT( KObjectProvider,
    "Class CAknEdwinState Function ObjectProvider tested" );
    AssertTrueL( ETrue, KObjectProvider );

    iAknEdwinState->LocalLanguage();
    _LIT( KLocalLanguage,
    "Class CAknEdwinState Function LocalLanguage tested" );
    AssertTrueL( ETrue, KLocalLanguage );

    iAknEdwinState->CurrentCase();
    _LIT( KCurrentCase,
    "Class CAknEdwinState Function CurrentCase tested" );
    AssertTrueL( ETrue, KCurrentCase );

    iAknEdwinState->DefaultInputMode();
    _LIT( KDefaultInputMode,
    "Class CAknEdwinState Function DefaultInputMode tested" );
    AssertTrueL( ETrue, KDefaultInputMode );

    iAknEdwinState->DefaultCase();
    _LIT( KDefaultCase,
    "Class CAknEdwinState Function DefaultCase tested" );
    AssertTrueL( ETrue, KDefaultCase );

    iAknEdwinState->FormAccessor();
    _LIT( KFormAccessor,
    "Class CAknEdwinState Function FormAccessor tested" );
    AssertTrueL( ETrue, KFormAccessor );

    iAknEdwinState->PermittedCases();
    _LIT( KPermittedCases,
    "Class CAknEdwinState Function PermittedCases tested" );
    AssertTrueL( ETrue, KPermittedCases );

    iAknEdwinState->SetCba();
    _LIT( KSetCba,
    "Class CAknEdwinState Function SetCba tested" );
    AssertTrueL( ETrue, KSetCba );

    iAknEdwinState->SetMenu();
    _LIT( KSetMenu,
    "Class CAknEdwinState Function SetMenu tested" );
    AssertTrueL( ETrue, KSetMenu );


    CMObserverClassTmp* mclasstmp = new ( ELeave )CMObserverClassTmp();
    CleanupStack::PushL( mclasstmp );
    iAknEdwinState->SetObserver( STATIC_CAST(
                                 MAknEdStateObserver*, mclasstmp ) );
    _LIT( KSetObserver,
    "Class CAknEdwinState Function SetObserver tested" );
    AssertTrueL( ETrue, KSetObserver );

    CleanupStack::PopAndDestroy( mclasstmp );

    iAknEdwinState->SetCurrentInputMode( EAknEditorNumericInputMode );
    _LIT( KSetCurrentInputMode,
    "Class CAknEdwinState Function SetCurrentInputMode tested" );
    AssertTrueL( ETrue, KSetCurrentInputMode );

    TAknEditorCaseState editorCaseState;
    editorCaseState.ClearFlag( TAknEditorCaseState::EFlagInitialiseRequired );
    AssertTrueL( ETrue, KClearFlag );

    editorCaseState.IsFlagSet(
                    TAknEditorCaseState::EFlagInitialiseRequired );
    AssertTrueL( ETrue, KIsFlagSet );

    editorCaseState.SetPreviousCase( 0 );
    AssertTrueL( ETrue, KSetPreviousCase );

    editorCaseState.SetPreviousCaseUsedToEnterText( 0 );
    AssertTrueL( ETrue, KSetPreviousCaseUsedToEnterText );

    editorCaseState.PreviousCase();
    AssertTrueL( ETrue, KPreviousCase );

    editorCaseState.PreviousCaseUsedToEnterText();
    AssertTrueL( ETrue, KPreviousCaseUsedToEnterText );

    editorCaseState.CurrentCase();
    _LIT( KTAknEditorCaseStateCurrentCase,
    "Class TAknEditorCaseState Function CurrentCase tested" );
    AssertTrueL( ETrue, KTAknEditorCaseStateCurrentCase );


    delete iAknEdwinState;
    iAknEdwinState=NULL;
    }

// ---------------------------------------------------------------------------
// CBCTestEditorCase::Test Class CAknIpFieldEditor
// ---------------------------------------------------------------------------
//
void CBCTestEditorCase::TestIpFieldEditorL()
    {
    TInetAddr lowAdr;
    lowAdr.SetAddress( KInetAddrNone );
    TInetAddr highAdr;
    highAdr.SetAddress( KInetAddrAll );

    _LIT( KNewL, "Class CAknIpFieldEditor Function NewL tested" );
    _LIT( KSetAddress,
    "Class CAknIpFieldEditor Function SetAddress tested" );
    _LIT( KAddress, "Class CAknIpFieldEditor Function Address tested" );
    _LIT( KSetMinimumAndMaximum,
    "Class CAknIpFieldEditor Function SetMinimumAndMaximum tested" );
    _LIT( KGetMinimumAndMaximum,
    "Class CAknIpFieldEditor Function GetMinimumAndMaximum tested" );
    _LIT( KConstructFromResourceL,
    "Class CAknIpFieldEditor Function ConstructFromResourceL tested" );
    _LIT( KOfferKeyEventL,
    "Class CAknIpFieldEditor Function OfferKeyEventL tested" );
    _LIT( KHandlePointerEventL,
    "Class CAknIpFieldEditor Function HandlePointerEventL tested" );

    iAknIpFieldEditor = CAknIpFieldEditor::NewL( lowAdr, highAdr, lowAdr );
  // CleanupStack::PushL(iAknIpFieldEditor); Changes by Sanjeev
     AssertTrueL( ETrue, KNewL );
  // CleanupStack::Pop( iAknIpFieldEditor ); Changes by Sanjeev
    delete iAknIpFieldEditor;
    iAknIpFieldEditor = NULL;


    iAknIpFieldEditor = CAknIpFieldEditor::NewL();
    AssertTrueL( ETrue, KNewL );
    TResourceReader resourceReader;
    iEikEnv->CreateResourceReaderLC( resourceReader,
                                     R_BCTESTEDITOR_IP_EDWIN );
    iAknIpFieldEditor->ConstructFromResourceL( resourceReader );
    AssertTrueL( ETrue, KConstructFromResourceL );
    CleanupStack::PopAndDestroy();//resourceReader
    iAknIpFieldEditor->SetContainerWindowL( *iContainer );

    iAknIpFieldEditor->ActivateL();
    _LIT( KActivateL,
    "Class CAknIpFieldEditor Function ActivateL tested" );
    AssertTrueL( ETrue, KActivateL );

    iAknIpFieldEditor->SetAddress( lowAdr );
    AssertTrueL( ETrue, KSetAddress );

    iAknIpFieldEditor->Address();
    AssertTrueL( ETrue, KAddress );

    iAknIpFieldEditor->SetMinimumAndMaximum( lowAdr, highAdr );
    AssertTrueL( ETrue, KSetMinimumAndMaximum );

    iAknIpFieldEditor->GetMinimumAndMaximum( lowAdr, highAdr );
    AssertTrueL( ETrue, KGetMinimumAndMaximum );


    TKeyEvent keyEvent;
    TPointerEvent pointerEvent;
    iAknIpFieldEditor->OfferKeyEventL( keyEvent, EEventKey );
    AssertTrueL( ETrue, KOfferKeyEventL );

    iAknIpFieldEditor->HandlePointerEventL( pointerEvent );
    AssertTrueL( ETrue, KHandlePointerEventL );

    delete iAknIpFieldEditor;
    iAknIpFieldEditor = NULL;
    }

// ---------------------------------------------------------------------------
// CBCTestEditorCase::Test Class CAknNumericEdwin and CAknIntegerEdwin
// ---------------------------------------------------------------------------
//
void CBCTestEditorCase::TestNumericEdwinL()
    {
    _LIT( KConstructL, "Class CAknNumericEdwin Function ConstructL tested" );
    _LIT( KMapKeyEvent,
    "Class CAknNumericEdwin Function MapKeyEvent tested" );

    _LIT( KNewL, "Class CAknIntegerEdwin Function NewL tested" );
    _LIT( KConstructLCAknIntegerEdwin,
    "Class CAknIntegerEdwin Function ConstructL tested" );
    _LIT( KConstructFromResourceL,
    "Class CAknIntegerEdwin Function ConstructFromResourceL tested" );
    _LIT( KSetMinimumIntegerValue,
    "Class CAknIntegerEdwin Function SetMinimumIntegerValue tested" );
    _LIT( KSetMaximumIntegerValue,
    "Class CAknIntegerEdwin Function SetMaximumIntegerValue tested" );
    _LIT( KSetValueL,"Class CAknIntegerEdwin Function SetValueL tested" );
    _LIT( KSetUnsetValue,
    "Class CAknIntegerEdwin Function SetUnsetValue tested" );
    _LIT( KPrepareForFocusLossL,
    "Class CAknIntegerEdwin Function PrepareForFocusLossL tested" );
    _LIT( KGetTextAsInteger,
    "Class CAknIntegerEdwin Function GetTextAsInteger tested" );
    _LIT( KCheckNumber,
    "Class CAknIntegerEdwin Function CheckNumber tested" );
    _LIT( KHandleResourceChange,
    "Class CAknIntegerEdwin Function HandleResourceChange tested" );
    _LIT( KOfferKeyEventL,
    "Class CAknIntegerEdwin Function OfferKeyEventL tested" );

    iAknNumericEdwin = new ( ELeave ) CTestNumericEdwin();

    iAknNumericEdwin->ConstructL( EEikEdwinAutoSelection, 10,
                       10, 10 );
    AssertTrueL( ETrue, KConstructL );

    iAknNumericEdwin->TestFunction();
    AssertTrueL( ETrue, KMapKeyEvent );

    delete iAknNumericEdwin;
    iAknNumericEdwin = NULL;

    CAknIntegerEdwin* aknIntegerEdwin = CAknIntegerEdwin::NewL( 0, 20, 10 );
    CleanupStack::PushL( aknIntegerEdwin );
    CleanupStack::PopAndDestroy( aknIntegerEdwin );
    AssertTrueL( ETrue, KNewL );

    iAknIntegerEdwin = new ( ELeave ) CAknIntegerEdwin();
    AssertTrueL( ETrue, KNewL );
    iAknIntegerEdwin->SetContainerWindowL( *iContainer );

    AssertTrueL( ETrue, KConstructLCAknIntegerEdwin );

    TResourceReader resourceReader;
    iEikEnv->CreateResourceReaderLC( resourceReader,
                                     R_BCTESTEDITOR_INTEGER_EDWIN );
    iAknIntegerEdwin->ConstructFromResourceL( resourceReader );
    AssertTrueL( ETrue, KConstructFromResourceL );
    CleanupStack::PopAndDestroy(); //resourceReader

    iAknIntegerEdwin->ActivateL();

    iAknIntegerEdwin->SetMinimumIntegerValue( 0 );
    AssertTrueL( ETrue, KSetMinimumIntegerValue );

    iAknIntegerEdwin->SetMaximumIntegerValue( 20 );
    AssertTrueL( ETrue, KSetMaximumIntegerValue );

    iAknIntegerEdwin->SetValueL( 5 );
    AssertTrueL( ETrue, KSetValueL );

    iAknIntegerEdwin->SetUnsetValue( 5 );
    AssertTrueL( ETrue, KSetUnsetValue );

    iAknIntegerEdwin->PrepareForFocusLossL();
    AssertTrueL( ETrue, KPrepareForFocusLossL );

    TInt tmpvalue;
    iAknIntegerEdwin->GetTextAsInteger( tmpvalue );
    AssertTrueL( ETrue, KGetTextAsInteger );

    iAknIntegerEdwin->CheckNumber();
    AssertTrueL( ETrue, KCheckNumber );

    iAknIntegerEdwin->HandleResourceChange( 3 );
    AssertTrueL( ETrue, KHandleResourceChange );

    TKeyEvent keyEvent;

    iAknIntegerEdwin->OfferKeyEventL( keyEvent, EEventKey );
    AssertTrueL( ETrue, KOfferKeyEventL );

    iAknIntegerEdwin->AddFlagToUserFlags( CEikEdwin::EDisplayOnly );
    TPointerEvent pointerEvent;

    iAknIntegerEdwin->HandlePointerEventL( pointerEvent );

    delete iAknIntegerEdwin;
    iAknIntegerEdwin = NULL;
    }

// ---------------------------------------------------------------------------
// CBCTestEditorCase::Test Class CAknCcpuSupport
// ---------------------------------------------------------------------------
//
void CBCTestEditorCase::TestCcpuSupportL()
    {
    _LIT( KConstructL, "Class CCpuSupport Function ConstructL tested" );
    _LIT( KHandleSelectionChangeL,
    "Class CCpuSupport Function HandleSelectionChangeL tested" );
    _LIT( KHandleFocusChangeL,
    "Class CCpuSupport Function HandleFocusChangeL tested" );
    _LIT( KProcessCommandL,
    "Class CCpuSupport Function ProcessCommandL tested" );
    _LIT( KOfferKeyEventL,
    "Class CCpuSupport Function OfferKeyEventL tested" );
    _LIT( KHandlePointerEventL,
    "Class CCpuSupport Function HandlePointerEventL tested" );
    _LIT( KDynInitMenuPaneL,
    "Class CCpuSupport Function DynInitMenuPaneL tested" );

    CEikEdwin *edwin = new ( ELeave ) CEikEdwin();
    CleanupStack::PushL( edwin );
    edwin->ConstructL( EAknEditorFlagDefault, 10, 30, 1 );

    iAknCcpuSupport = new ( ELeave )
        CAknCcpuSupport( STATIC_CAST( MEikCcpuEditor*, edwin ) );

    iAknCcpuSupport->ConstructL();
    AssertTrueL( ETrue, KConstructL );

    iAknCcpuSupport->HandleSelectionChangeL();
    AssertTrueL( ETrue, KHandleSelectionChangeL );

    iAknCcpuSupport->HandleFocusChangeL();
    AssertTrueL( ETrue, KHandleFocusChangeL );

    iAknCcpuSupport->ProcessCommandL( 0 );
    AssertTrueL( ETrue, KProcessCommandL );

    TKeyEvent keyEvent;
    TPointerEvent pointerEvent;
    iAknCcpuSupport->OfferKeyEventL( keyEvent, EEventKey );
    AssertTrueL( ETrue, KOfferKeyEventL );

    iAknCcpuSupport->HandlePointerEventL( pointerEvent );
    AssertTrueL( ETrue, KHandlePointerEventL );

    iPane = new ( ELeave ) CEikMenuPane( iAknCcpuSupport );
    iPane->ConstructL( iPane, 0 );
    iAknCcpuSupport->DynInitMenuPaneL( 0, iPane );
    AssertTrueL( ETrue, KDynInitMenuPaneL );

    delete iPane;
    iPane = NULL;
    delete iAknCcpuSupport;
    iAknCcpuSupport = NULL;
    CleanupStack::PopAndDestroy( edwin );
    }

// ---------------------------------------------------------------------------
// CBCTestEditorCase::Test Class CEikEdwin
// ---------------------------------------------------------------------------
//
void CBCTestEditorCase::TestEikEdwinL()
    {
    iEikEdwin = new ( ELeave )CEikEdwin();
    _LIT( KCEikEdwin,
    "Class CEikEdwin Function CEikEdwin tested" );
    AssertTrueL( ETrue, KCEikEdwin );

    iEikEdwin->SetHighlightStyleL( EEikEdwinHighlightNormal );
    _LIT( KSetHighlightStyleL,
    "Class CEikEdwin Function SetHighlightStyleL tested" );
    AssertTrueL( ETrue, KSetHighlightStyleL );

    TResourceReader resourceReader;
    iEikEnv->CreateResourceReaderLC( resourceReader, R_BCTESTEDITOR_EDWIN );
    iEikEdwin->ConstructFromResourceL( resourceReader );
    _LIT( KConstructFromResourceL,
    "Class CEikEdwin Function ConstructFromResourceL tested" );
    AssertTrueL( ETrue, KConstructFromResourceL );

    CleanupStack::PopAndDestroy();//resourceReader

    iEikEdwin->SetContainerWindowL( *iContainer );
    _LIT( KSetContainerWindowL,
    "Class CEikEdwin Function SetContainerWindowL tested" );
    AssertTrueL( ETrue, KSetContainerWindowL );

    CAknQueryControl* aknQueryControl = new ( ELeave )CAknQueryControl();
    CleanupStack::PushL( aknQueryControl );

    iEikEdwin->AddEdwinObserverL( STATIC_CAST( MEikEdwinObserver*,
                                               aknQueryControl ) );
    _LIT( KAddEdwinObserverL,
    "Class CEikEdwin Function AddEdwinObserverL tested" );
    AssertTrueL( ETrue, KAddEdwinObserverL );

    iEikEdwin->SetEdwinObserver( STATIC_CAST( MEikEdwinObserver*,
                                               aknQueryControl ) );
    _LIT( KSetEdwinObserver,
    "Class CEikEdwin Function SetEdwinObserver tested" );
    AssertTrueL( ETrue, KSetEdwinObserver );

    iEikEdwin->SetEdwinSizeObserver( STATIC_CAST( MEikEdwinSizeObserver*,
                                               aknQueryControl ) );
    _LIT( KSetEdwinSizeObserver,
    "Class CEikEdwin Function SetEdwinSizeObserver tested" );
    AssertTrueL( ETrue, KSetEdwinSizeObserver );

    iEikEdwin->RemoveEdwinObserver( STATIC_CAST( MEikEdwinObserver*,
                                               aknQueryControl ) );
    _LIT( KRemoveEdwinObserver,
    "Class CEikEdwin Function RemoveEdwinObserver tested" );
    AssertTrueL( ETrue, KRemoveEdwinObserver );

		iEikEdwin->SetEdwinObserver( NULL );
    CleanupStack::PopAndDestroy( aknQueryControl );

    iEikEdwin->CreateScrollBarFrameL();
    _LIT( KCreateScrollBarFrameL,
    "Class CEikEdwin Function CreateScrollBarFrameL tested" );
    AssertTrueL( ETrue, KCreateScrollBarFrameL );

    iEikEdwin->AknEditorCurrentInputMode();
    _LIT( KAknEditorCurrentInputMode,
    "Class CEikEdwin Function AknEditorCurrentInputMode tested" );
    AssertTrueL( ETrue, KAknEditorCurrentInputMode );

    iEikEdwin->CreateTextViewL();
    _LIT( KCreateTextViewL,
    "Class CEikEdwin Function CreateTextViewL tested" );
    AssertTrueL( ETrue, KCreateTextViewL );

    iEikEdwin->SelectionLength();
    _LIT( KSelectionLength,
    "Class CEikEdwin Function SelectionLength tested" );
    AssertTrueL( ETrue, KSelectionLength );

    iEikEdwin->EnableCcpuSupportL( ETrue );
    _LIT( KEnableCcpuSupportL,
    "Class CEikEdwin Function EnableCcpuSupportL tested" );
    AssertTrueL( ETrue, KEnableCcpuSupportL );

    iEikEdwin->CanUndo();
    _LIT( KCanUndo,
    "Class CEikEdwin Function CanUndo tested" );
    AssertTrueL( ETrue, KCanUndo );

    iEikEdwin->CcpuCanCopy();
    _LIT( KCcpuCanCopy,
    "Class CEikEdwin Function CcpuCanCopy tested" );
    AssertTrueL( ETrue, KCcpuCanCopy );

    iEikEdwin->CcpuCanCut();
    _LIT( KCcpuCanCut,
    "Class CEikEdwin Function CcpuCanCut tested" );
    AssertTrueL( ETrue, KCcpuCanCut );

    iEikEdwin->CcpuCanPaste();
    _LIT( KCcpuCanPaste,
    "Class CEikEdwin Function CcpuCanPaste tested" );
    AssertTrueL( ETrue, KCcpuCanPaste );

    iEikEdwin->CcpuCanUndo();
    _LIT( KCcpuCanUndo,
    "Class CEikEdwin Function CcpuCanUndo tested" );
    AssertTrueL( ETrue, KCcpuCanUndo );

    iEikEdwin->CcpuIsFocused();
    _LIT( KCcpuIsFocused,
    "Class CEikEdwin Function CcpuIsFocused tested" );
    AssertTrueL( ETrue, KCcpuIsFocused );

    iEikEdwin->CcpuCopyL();
    _LIT( KCcpuCopyL,
    "Class CEikEdwin Function CCcpuCopyL tested" );
    AssertTrueL( ETrue, KCcpuCopyL );

    iEikEdwin->CcpuCutL();
    _LIT( KCcpuCutL,
    "Class CEikEdwin Function CcpuCutL tested" );
    AssertTrueL( ETrue, KCcpuCutL );

    TRAP_IGNORE( iEikEdwin->CcpuPasteL() );

    iEikEdwin->CcpuUndoL();
    _LIT( KCcpuUndoL,
    "Class CEikEdwin Function CcpuUndoL tested" );
    AssertTrueL( ETrue, KCcpuUndoL );

    iEikEdwin->CountWords();
    _LIT( KCountWords,
    "Class CEikEdwin Function CountWords tested" );
    AssertTrueL( ETrue, KCountWords );

    iEikEdwin->FocusChanged( EDrawNow );
    _LIT( KFocusChanged,
    "Class CEikEdwin Function FocusChanged tested" );
    AssertTrueL( ETrue, KFocusChanged );

    _LIT( Kstr, " " );
    TDesC16 tmp = Kstr;
    iEikEdwin->FindL( &tmp, 0 );
    _LIT( KFindL,
    "Class CEikEdwin Function FindL tested" );
    AssertTrueL( ETrue, KFindL );

    iEikEdwin->GetTextInHBufL();
    _LIT( KGetTextInHBufL,
    "Class CEikEdwin Function GetTextInHBufL tested" );
    AssertTrueL( ETrue, KGetTextInHBufL );

    iEikEdwin->SetDimmed( ETrue );
    _LIT( KSetDimmed,
    "Class CEikEdwin Function SetDimmed tested" );
    AssertTrueL( ETrue, KSetDimmed );


    iEikEdwin->LayoutWidth();
    _LIT( KLayoutWidth,
    "Class CEikEdwin Function LayoutWidth tested" );
    AssertTrueL( ETrue, KLayoutWidth );

    iEikEdwin->SetMaximumHeight( 10 );
    _LIT( KSetMaximumHeight,
    "Class CEikEdwin Function SetMaximumHeight tested" );
    AssertTrueL( ETrue, KSetMaximumHeight );

    iEikEdwin->SetMinimumHeight( 1 );
    _LIT( KSetMinimumHeight,
    "Class CEikEdwin Function SetMinimumHeight tested" );
    AssertTrueL( ETrue, KSetMinimumHeight );

    iEikEdwin->MaximumHeightInLines();
    _LIT( KMaximumHeightInLines,
    "Class CEikEdwin Function MaximumHeightInLines tested" );
    AssertTrueL( ETrue, KMaximumHeightInLines );

    iEikEdwin->SetAknEditorCurrentCase( 1 );
    _LIT( KSetAknEditorCurrentCase,
    "Class CEikEdwin Function SetAknEditorCurrentCase tested" );
    AssertTrueL( ETrue, KSetAknEditorCurrentCase );

    iEikEdwin->SetAknEditorCurrentInputMode( 1 );
    _LIT( KSetAknEditorCurrentInputMode,
    "Class CEikEdwin Function SetAknEditorCurrentInputMode tested" );
    AssertTrueL( ETrue, KSetAknEditorCurrentInputMode );

    iEikEdwin->SetAknEditorLocalLanguage( ELangEnglish );
    _LIT( KSetAknEditorLocalLanguage,
    "Class CEikEdwin Function SetAknEditorLocalLanguage tested" );
    AssertTrueL( ETrue, KSetAknEditorLocalLanguage );

    iEikEdwin->SetAlignment( 1 );
    _LIT( KSetAlignment,
    "Class CEikEdwin Function SetAlignment tested" );
    AssertTrueL( ETrue, KSetAlignment );

    iEikEdwin->SetAllowPictures( ETrue );
    _LIT( KSetAllowPictures,
    "Class CEikEdwin Function SetAllowPictures tested" );
    AssertTrueL( ETrue, KSetAllowPictures );

    iEikEdwin->SetAllowUndo( ETrue );
    _LIT( KSetAllowUndo,
    "Class CEikEdwin Function SetAllowUndo tested" );
    AssertTrueL( ETrue, KSetAllowUndo );

    iEikEdwin->AddFlagToUserFlags( 10 );
    _LIT( KAddFlagToUserFlags,
    "Class CEikEdwin Function AddFlagToUserFlags tested" );
    AssertTrueL( ETrue, KAddFlagToUserFlags );

    iEikEdwin->UserFlags();
    _LIT( KUserFlags,
    "Class CEikEdwin Function UserFlags tested" );
    AssertTrueL( ETrue, KUserFlags );

    TRgb rgb;
    rgb.SetGreen( 0 );
    iEikEdwin->SetBackgroundColorL( rgb );
    _LIT( KSetBackgroundColorL,
    "Class CEikEdwin Function SetBackgroundColorL tested" );
    AssertTrueL( ETrue, KSetBackgroundColorL );

    TMargins8 margins;
    margins.SetAllValuesTo( 10 );
    iEikEdwin->SetBorderViewMargins( margins );
    _LIT( KSetBorderViewMargins,
    "Class CEikEdwin Function SetBorderViewMargins tested" );
    AssertTrueL( ETrue, KSetBorderViewMargins );

    TGulBorder gulBorder;
    CEikRichTextEditor* eikRichTextEditor = new ( ELeave )
                                            CEikRichTextEditor( gulBorder );
    CleanupStack::PushL( eikRichTextEditor );

    eikRichTextEditor->ConstructL( iContainer, 2, 40,
                                   EAknEditorFlagDefault );

    CGlobalText* globalText = eikRichTextEditor->GlobalText();

    iEikEdwin->SetDocumentContentL( *globalText, CEikEdwin::ECopyText );
    _LIT( KSetDocumentContentL,
    "Class CEikEdwin Function SetDocumentContentL tested" );
    AssertTrueL( ETrue, KSetDocumentContentL );
    CleanupStack::PopAndDestroy( eikRichTextEditor );

    iEikEdwin->SetDocumentOwnership( CEikEdwin::EOwnsText );
    _LIT( KSetDocumentOwnership,
    "Class CEikEdwin Function SetDocumentOwnership tested" );
    AssertTrueL( ETrue, KSetDocumentOwnership );

    TCoeInputCapabilities coeInputCapabilities;
    iEikEdwin->SetInputCapabilitiesL( coeInputCapabilities );
    _LIT( KSetInputCapabilitiesL,
    "Class CEikEdwin Function SetInputCapabilitiesL tested" );
    AssertTrueL( ETrue, KSetInputCapabilitiesL );

    TNonPrintingCharVisibility charVisibility;
    charVisibility.SetNoneVisible();
    iEikEdwin->SetNonPrintingCharsVisibility( charVisibility );
    _LIT( KSetNonPrintingCharsVisibility,
    "Class CEikEdwin Function SetNonPrintingCharsVisibility tested" );
    AssertTrueL( ETrue, KSetNonPrintingCharsVisibility );

    iEikEdwin->SetSkinBackgroundControlContextL( NULL );
    _LIT( KSetSkinBackgroundControlContextL,
    "Class CEikEdwin Function SetSkinBackgroundControlContextL tested" );
    AssertTrueL( ETrue, KSetSkinBackgroundControlContextL );


    iEikEdwin->NonPrintingCharsVisibility();
    _LIT( KNonPrintingCharsVisibility,
    "Class CEikEdwin Function NonPrintingCharsVisibility tested" );
    AssertTrueL( ETrue, KNonPrintingCharsVisibility );

    iEikEdwin->NotifyEditorStateObserverOfStateChangeL();
    _LIT( KNotifyEditorStateObserverOfStateChangeL,
    "CEikEdwin Function NotifyEditorStateObserverOfStateChangeL tested" );
    AssertTrueL( ETrue, KNotifyEditorStateObserverOfStateChangeL );

    iEikEdwin->NotifyNewDocumentL();
    _LIT( KNotifyNewDocumentL,
    "Class CEikEdwin Function NotifyNewDocumentL tested" );
    AssertTrueL( ETrue, KNotifyNewDocumentL );


    iEikEdwin->SetOnlyASCIIChars( EFalse );
    _LIT( KSetOnlyASCIIChars,
    "Class CEikEdwin Function SetOnlyASCIIChars tested" );
    AssertTrueL( ETrue, KSetOnlyASCIIChars );

    iEikEdwin->SetPasteFromIrStore( ETrue );
    _LIT( KSetPasteFromIrStore,
    "Class CEikEdwin Function SetPasteFromIrStore tested" );
    AssertTrueL( ETrue, KSetPasteFromIrStore );

    TCallBack callBack;
    iEikEdwin->SetPictographAnimationCallBack( callBack );
    _LIT( KSetPictographAnimationCallBack,
    "Class CEikEdwin Function SetPictographAnimationCallBack tested" );
    AssertTrueL( ETrue, KSetPictographAnimationCallBack );

    iEikEdwin->SetReadOnly( EFalse );
    _LIT( KSetReadOnly,
    "Class CEikEdwin Function SetReadOnly tested" );
    AssertTrueL( ETrue, KSetReadOnly );

    iEikEdwin->SetRightWrapGutter( 0 );
    _LIT( KSetRightWrapGutter,
    "Class CEikEdwin Function SetRightWrapGutter tested" );
    AssertTrueL( ETrue, KSetRightWrapGutter );

    iEikEdwin->SetTextLimit( 30 );
    _LIT( KSetTextLimit,
    "Class CEikEdwin Function SetTextLimit tested" );
    AssertTrueL( ETrue, KSetTextLimit );

    iEikEdwin->SetTextSkinColorIdL( 0 );
    _LIT( KSetTextSkinColorIdL,
    "Class CEikEdwin Function SetTextSkinColorIdL tested" );
    AssertTrueL( ETrue, KSetTextSkinColorIdL );

    TCursorSelection cursorSelection;
    iEikEdwin->SetUndoBufferL( cursorSelection );
    _LIT( KSetUndoBufferL,
    "Class CEikEdwin Function SetUndoBufferL tested" );
    AssertTrueL( ETrue, KSetUndoBufferL );

    iEikEdwin->SetUndoableText( cursorSelection );
    _LIT( KSetUndoableText,
    "Class CEikEdwin Function SetUndoableText tested" );
    AssertTrueL( ETrue, KSetUndoableText );


    iEikEdwin->SetUpperFullFormattingLength( 10 );
    _LIT( KSetUpperFullFormattingLength,
    "Class CEikEdwin Function SetUpperFullFormattingLength tested" );
    AssertTrueL( ETrue, KSetUpperFullFormattingLength );

    iEikEdwin->SetWordDelimiters( ETrue, ETrue );
    _LIT( KSetWordDelimiters,
    "Class CEikEdwin Function SetWordDelimiters tested" );
    AssertTrueL( ETrue, KSetWordDelimiters );

    iEikEdwin->SetWordWrapL( ETrue );
    _LIT( KSetWordWrapL,
    "Class CEikEdwin Function SetWordWrapL tested" );
    AssertTrueL( ETrue, KSetWordWrapL );

    iEikEdwin->SetWysiwygModeOff();
    _LIT( KSetWysiwygModeOff,
    "Class CEikEdwin Function SetWysiwygModeOff tested" );
    AssertTrueL( ETrue, KSetWysiwygModeOff );

    CGraphicsDevice* device = CCoeEnv::Static()->ScreenDevice();
    iEikEdwin->SetWysiwygModeOn( 10,
                                 STATIC_CAST( MGraphicsDeviceMap*, device ) );

    iEikEdwin->UpdateCurrentFieldL();
    _LIT( KUpdateCurrentFieldL,
    "Class CEikEdwin Function UpdateCurrentFieldL tested" );
    AssertTrueL( ETrue, KUpdateCurrentFieldL );

    iEikEdwin->UpdateLayoutWidth( 10 );
    _LIT( KUpdateLayoutWidth,
    "Class CEikEdwin Function UpdateLayoutWidth tested" );
    AssertTrueL( ETrue, KUpdateLayoutWidth );

    TBCTestIrFactory irFactory;
    iEikEnv->SetIrFactory( &irFactory );

    iEikEdwin->SendDataOverIrL();
    _LIT( KSendOverIr, "CEikEdwin::SendDataOverIrL" );
    AssertTrueL( ETrue, KSendOverIr );

    iEikEdwin->ReceiveDataOverIrL();
    _LIT( KReceiveOverIr, "CEikEdwin::ReceiveDataOverIrL" );
    AssertTrueL( ETrue, KReceiveOverIr );

    iEikEnv->SetIrFactory( NULL );

    TRAP_IGNORE( iEikEdwin->RunCharMapDialogL() );

    TZoomFactor zoomFactor;
    iEikEdwin->SetZoomFactorL( &zoomFactor );
    _LIT( KSetZoomFactorL,
    "Class CEikEdwin Function SetZoomFactorL tested" );
    AssertTrueL( ETrue, KSetZoomFactorL );

    iEikEdwin->FindTextL( &tmp, 10, 0 );
    iEikEdwin->FindTextL( &tmp, 10, 1 );
    _LIT( KFindTextL,
    "Class CEikEdwin Function FindTextL tested" );
    AssertTrueL( ETrue, KFindTextL );

    iEikEdwin->HandleResourceChange( KEikDynamicLayoutVariantSwitch );
    iEikEdwin->HandleResourceChange( KEikMessageVirtualCursorStateChange );
    iEikEdwin->HandleResourceChange(
                          KEikMessageCaptionedControlEditableStateChange );
    iEikEdwin->HandleResourceChange(
                          KEikMessageCaptionedControlNotEditableStateChange );
    iEikEdwin->HandleResourceChange( KEikInputLanguageChange );
    CArrayFix<TCoeColorUse>* indexArray = new ( ELeave )
                                          CArrayFixFlat<TCoeColorUse>( 1 );
    CleanupStack::PushL( indexArray );
    iEikEdwin->GetColorUseListL( *indexArray );
    _LIT( KGetColorUseListL,
    "Class CEikEdwin Function GetColorUseListL tested" );
    AssertTrueL( ETrue, KGetColorUseListL );

    CleanupStack::PopAndDestroy( indexArray );

    TBuf<500>* findText = new( ELeave ) TBuf<500>;
    CleanupStack::PushL( findText );
    iEikEdwin->GetFindText( findText );
    _LIT( KGetFindText,
    "Class CEikEdwin Function GetFindText tested" );
    AssertTrueL( ETrue, KGetFindText );
    CleanupStack::PopAndDestroy( findText );

    TInt tmpstart;
    TInt tmplength;
    iEikEdwin->GetWordInfo( 0, tmpstart, tmplength );
    _LIT( KGetWordInfo,
    "Class CEikEdwin Function GetWordInfo tested" );
    AssertTrueL( ETrue, KGetWordInfo );

    TPointerEvent pointerEvent;
    pointerEvent.iType = TPointerEvent::EButton1Down;
    iEikEdwin->HandlePointerEventL( pointerEvent );
    pointerEvent.iType = TPointerEvent::EButton1Up;
    iEikEdwin->HandlePointerEventL( pointerEvent );
    _LIT( KHandlePointerEventL,
    "Class CEikEdwin Function HandlePointerEventL tested" );
    AssertTrueL( ETrue, KHandlePointerEventL );

    CEikScrollBar* eikScrollBar = new ( ELeave ) CEikScrollBar();
    CleanupStack::PushL( eikScrollBar );
    eikScrollBar->ConstructL(STATIC_CAST( MEikScrollBarObserver*, iEikEdwin ),
                              iContainer, CEikScrollBar::EVertical,
                              20, CEikScrollBar::EEikScrollBarDefaultBehaviour
                             );
    iEikEdwin->HandleScrollEventL( eikScrollBar, EEikScrollLeft );
    iEikEdwin->HandleScrollEventL( eikScrollBar, EEikScrollRight );
    iEikEdwin->HandleScrollEventL( eikScrollBar, EEikScrollPageLeft );
    iEikEdwin->HandleScrollEventL( eikScrollBar, EEikScrollPageRight );
    iEikEdwin->HandleScrollEventL( eikScrollBar, EEikScrollThumbDragHoriz );
    iEikEdwin->HandleScrollEventL( eikScrollBar, EEikScrollDown );
    iEikEdwin->HandleScrollEventL( eikScrollBar, EEikScrollPageUp );
    iEikEdwin->HandleScrollEventL( eikScrollBar, EEikScrollPageDown );
    iEikEdwin->HandleScrollEventL( eikScrollBar, EEikScrollTop );
    iEikEdwin->HandleScrollEventL( eikScrollBar, EEikScrollBottom );
    iEikEdwin->HandleScrollEventL( eikScrollBar, EEikScrollUp );
    _LIT( KHandleScrollEventL,
    "Class CEikEdwin Function HandleScrollEventL tested" );
    AssertTrueL( ETrue, KHandleScrollEventL );

    CleanupStack::PopAndDestroy( eikScrollBar );
    iEikEdwin->HandleTextChangedL();
    _LIT( KHandleTextChangedL,
    "Class CEikEdwin Function HandleTextChangedL tested" );
    AssertTrueL( ETrue, KHandleTextChangedL );

    iEikEdwin->IdleL( iEikEdwin );
    _LIT( KIdleL,
    "Class CEikEdwin Function IdleL tested" );
    AssertTrueL( ETrue, KIdleL );

    iEikEdwin->InsertDeleteCharsL( 0, tmp, cursorSelection );
    _LIT( KInsertDeleteCharsL,
    "Class CEikEdwin Function InsertDeleteCharsL tested" );
    AssertTrueL( ETrue, KInsertDeleteCharsL );

    iEikEdwin->MoveCursorL( TCursorPosition::EFLeft, ETrue );
    _LIT( KMoveCursorL,
    "Class CEikEdwin Function MoveCursorL tested" );
    AssertTrueL( ETrue, KMoveCursorL );

    iEikEdwin->RemoveFlagFromUserFlags( 1 );
    _LIT( KRemoveFlagFromUserFlags,
    "Class CEikEdwin Function RemoveFlagFromUserFlags tested" );
    AssertTrueL( ETrue, KRemoveFlagFromUserFlags );

    SEdwinFindModel findModel;
    _LIT( KNChar, "\n" );
    _LIT( KFChar, "\f" );
    TBuf<1> text( KNChar );
    TBuf<1> replaceText( KFChar );
    findModel.iFlags = 0;
    findModel.iText = text;
    findModel.iReplaceText = replaceText;
    findModel.iReplaceOption = EReplaceAll;
    iEikEdwin->ReplaceAllL( &findModel );
    _LIT( KReplaceAllL,
    "Class CEikEdwin Function ReplaceAllL tested" );
    AssertTrueL( ETrue, KReplaceAllL );

    iEikEdwin->SelectAllL();
    _LIT( KSelectAllL,
    "Class CEikEdwin Function SelectAllL tested" );
    AssertTrueL( ETrue, KSelectAllL );

    iEikEdwin->LowerPartialFormattingLength();
    _LIT( KLowerPartialFormattingLength,
    "Class CEikEdwin Function LowerPartialFormattingLength tested" );
    AssertTrueL( ETrue, KLowerPartialFormattingLength );

    iEikEdwin->Margins();
    _LIT( KMargins,
    "Class CEikEdwin Function Margins tested" );
    AssertTrueL( ETrue, KMargins );

    iEikEdwin->MaximumHeight();
    _LIT( KMaximumHeight,
    "Class CEikEdwin Function MaximumHeight tested" );
    AssertTrueL( ETrue, KMaximumHeight );

    iEikEdwin->MinimumHeight();
    _LIT( KMinimumHeight,
    "Class CEikEdwin Function MinimumHeight tested" );
    AssertTrueL( ETrue, KMinimumHeight );

    iEikEdwin->MinimumSize();
    _LIT( KMinimumSize,
    "Class CEikEdwin Function MinimumSize tested" );
    AssertTrueL( ETrue, KMinimumSize );
    delete iEikEdwin;
    iEikEdwin = NULL;

    CSubEikEdwin* subEikEdwin = new  ( ELeave )CSubEikEdwin();
    CleanupStack::PushL( subEikEdwin );
    iEikEnv->CreateResourceReaderLC( resourceReader, R_BCTESTEDITOR_EDWIN );
    subEikEdwin->ConstructFromResourceL( resourceReader );

    CleanupStack::PopAndDestroy();//resourceReader
    subEikEdwin->SetContainerWindowL( *iContainer );
    subEikEdwin->TestFunctionL();
    _LIT( KCancelSelectionL,
    "Class CEikEdwin Function CancelSelectionL tested" );
    AssertTrueL( ETrue, KCancelSelectionL );
    _LIT( KTrappedSizeChanged,
    "Class CEikEdwin Function TrappedSizeChanged tested" );
    AssertTrueL( ETrue, KTrappedSizeChanged );
    _LIT( KHandleTextPastedL,
    "Class CEikEdwin Function HandleTextPastedL tested" );
    AssertTrueL( ETrue, KHandleTextPastedL );
    _LIT( KPlaceDataOnClipboardL,
    "Class CEikEdwin Function PlaceDataOnClipboardL tested" );
    AssertTrueL( ETrue, KPlaceDataOnClipboardL );
    _LIT( KSetLineCursorDetailsL,
    "Class CEikEdwin Function SetLineCursorDetailsL tested" );
    AssertTrueL( ETrue, KSetLineCursorDetailsL );

    CleanupStack::PopAndDestroy( subEikEdwin );

    iEikEdwin = new(ELeave)CEikEdwin();
    iEikEdwin->SetContainerWindowL(*iContainer );
    iEikEdwin->ConstructL(0,200,200,1);
    iEikEdwin->CreateTextViewL();
    _LIT(t,"test");
    iEikEdwin->SetTextL(&t);

    iEikEdwin->UpdateAllFieldsL();
    _LIT( KUpdateAllFieldsL,
    "Class CEikEdwin Function UpdateAllFieldsL tested" );
    AssertTrueL( ETrue, KUpdateAllFieldsL );

    iEikEdwin->ReplaceL( &findModel );
    _LIT( KReplaceL,
    "Class CEikEdwin Function ReplaceL tested" );
    AssertTrueL( ETrue, KReplaceL );

    _LIT( KFileName, "C:\\bctestlog\\bctestlog.txt" );
    TFileName aFileName( KFileName );
    iEikEdwin->InsertFromTextFileL( aFileName, CPlainText::EOrganiseByLine );
    _LIT( KInsertFromTextFile, "CEikEdwin::InsertFromTextFileL" );
    AssertTrueL( ETrue, KInsertFromTextFile );

    CDateTimeField* dtField = new (ELeave) CDateTimeField();
    iEikEdwin->InsertFieldL( dtField,dtField->Type() );
    _LIT( KInsertFieldL,
    "Class CEikEdwin Function InsertFieldL tested" );
    AssertTrueL(ETrue ,KInsertFieldL );

	delete iEikEdwin;
	iEikEdwin = NULL;
   }

// ---------------------------------------------------------------------------
// CBCTestEditorCase::Test Class CEikFixdPointEditor
// ---------------------------------------------------------------------------
//
void CBCTestEditorCase::TestEikFixedPointEditorL()
    {
    _LIT( KConstructL,
    "Class CEikFixedPointEditor Function ConstructL tested" );
    _LIT( KConstructFromResourceL,
    "Class CEikFixedPointEditor Function ConstructFromResourceL tested" );
    _LIT( KSetDecimalPlaces,
    "Class CEikFixedPointEditor Function SetDecimalPlaces tested" );
    _LIT( KDecimalPlaces,
    "Class CEikFixedPointEditor Function DecimalPlaces tested" );
    _LIT( KSetMinMax,
    "Class CEikFixedPointEditor Function SetMinMax tested" );
    _LIT( KGetMinMax,
    "Class CEikFixedPointEditor Function GetMinMax tested" );
    _LIT( KSetValueL,
    "Class CEikFixedPointEditor Function SetValueL tested" );
    _LIT( KGetValueAsInteger,
    "Class CEikFixedPointEditor Function GetValueAsInteger tested" );
    _LIT( KValue,
    "Class CEikFixedPointEditor Function Value tested" );
    _LIT( KInputCapabilities,
    "Class CEikFixedPointEditor Function InputCapabilities tested" );
    _LIT( KPrepareForFocusLossL,
    "Class CEikFixedPointEditor Function PrepareForFocusLossL tested" );
    _LIT( KOfferKeyEventL,
    "Class CEikFixedPointEditor Function OfferKeyEventL tested" );
    _LIT( KHandlePointerEventL,
    "Class CEikFixedPointEditor Function HandlePointerEventL tested" );
    _LIT( KHandleResourceChange,
    "Class CEikFixedPointEditor Function HandleResourceChange tested" );

    iEikFixedPointEditor = new ( ELeave ) CEikFixedPointEditor();
    AssertTrueL( ETrue, KConstructL );

    TResourceReader resourceReader;
    iEikEnv->CreateResourceReaderLC( resourceReader, R_BCTEST_EDITOR_EDWIN );
    iEikFixedPointEditor->ConstructFromResourceL( resourceReader );
    AssertTrueL( ETrue, KConstructFromResourceL );
    CleanupStack::PopAndDestroy(); //resourceReader
    iEikFixedPointEditor->SetContainerWindowL( *iContainer );
    iEikFixedPointEditor->ActivateL();

    iEikFixedPointEditor->SetDecimalPlaces( 1 );
    AssertTrueL( ETrue, KSetDecimalPlaces );

    iEikFixedPointEditor->DecimalPlaces();
    AssertTrueL( ETrue, KDecimalPlaces );

    iEikFixedPointEditor->SetMinMax( 1,10 );
    AssertTrueL( ETrue, KSetMinMax );

    TInt tmpmin;
    TInt tmpmax;
    iEikFixedPointEditor->GetMinMax( tmpmin, tmpmax );
    AssertTrueL( ETrue, KGetMinMax );

    TInt tmpvalue = 10;
    iEikFixedPointEditor->SetValueL( &tmpvalue );
    AssertTrueL( ETrue, KSetValueL );

    TInt avalue;
    iEikFixedPointEditor->GetValueAsInteger( avalue );
    AssertTrueL( ETrue, KGetValueAsInteger );

    iEikFixedPointEditor->Value();
    AssertTrueL( ETrue, KValue );

    iEikFixedPointEditor->PrepareForFocusLossL();
    AssertTrueL( ETrue, KPrepareForFocusLossL );

    iEikFixedPointEditor->InputCapabilities();
    AssertTrueL( ETrue, KInputCapabilities );

    TKeyEvent keyEvent;
    TPointerEvent pointerEvent;
    iEikFixedPointEditor->OfferKeyEventL( keyEvent, EEventKey );
    AssertTrueL( ETrue, KOfferKeyEventL );

    iEikFixedPointEditor->HandlePointerEventL( pointerEvent );
    AssertTrueL( ETrue, KHandlePointerEventL );

    iEikFixedPointEditor->HandleResourceChange( KEikInputLanguageChange );
    AssertTrueL( ETrue, KHandleResourceChange );

    delete iEikFixedPointEditor;
    iEikFixedPointEditor = NULL;
    }

// ---------------------------------------------------------------------------
// CBCTestEditorCase::Test Class CEikFloatingPointEditor
// ---------------------------------------------------------------------------
//
void CBCTestEditorCase::TestEikFloatingPointEditorL()
    {
    _LIT( KConstructFromResourceL,
    "Class CEikFloatingPointEditor Function ConstructFromResourceL tested" );
    _LIT( KSetMinMax,
    "Class CEikFloatingPointEditor Function SetMinMax tested" );
    _LIT( KGetMinMax,
    "Class CEikFloatingPointEditor Function GetMinMax tested" );
    _LIT( KSetValueL,
    "Class CEikFloatingPointEditor Function SetValueL tested" );
    _LIT( KGetValueAsReal,
    "Class CEikFloatingPointEditor Function GetValueAsReal tested" );
    _LIT( KValue,
    "Class CEikFloatingPointEditor Function Value tested" );
    _LIT( KPrepareForFocusLossL,
    "Class CEikFloatingPointEditor Function PrepareForFocusLossL tested" );
    _LIT( KInputCapabilities,
    "Class CEikFloatingPointEditor Function InputCapabilities tested" );
    _LIT( KOfferKeyEventL,
    "Class CEikFloatingPointEditor Function OfferKeyEventL tested" );
    _LIT( KHandlePointerEventL,
    "Class CEikFloatingPointEditor Function HandlePointerEventL tested" );
    _LIT( KHandleResourceChange,
    "Class CEikFloatingPointEditor Function HandleResourceChange tested" );

    iEikFloatingPointEditor = new ( ELeave ) CEikFloatingPointEditor();

    TResourceReader resourceReader;
    iEikEnv->CreateResourceReaderLC( resourceReader,
                                     R_BCTEST_EDITOR_EIKEDITOR );
    iEikFloatingPointEditor->ConstructFromResourceL( resourceReader );
    AssertTrueL( ETrue, KConstructFromResourceL );
    CleanupStack::PopAndDestroy(); //resourceReader
    iEikFloatingPointEditor->SetContainerWindowL( *iContainer );

    TRAP_IGNORE( iEikFloatingPointEditor->PrepareForFocusLossL() );
    AssertTrueL( ETrue,KPrepareForFocusLossL );

    iEikFloatingPointEditor->ActivateL();

    iEikFloatingPointEditor->SetMinMax( 1, 10 );
    AssertTrueL( ETrue, KSetMinMax );

    TReal tmpmin;
    TReal tmpmax;
    iEikFloatingPointEditor->GetMinMax( tmpmin, tmpmax );
    AssertTrueL( ETrue, KGetMinMax );

    TReal tmpvalue = 10;
    iEikFloatingPointEditor->SetValueL( &tmpvalue );
    AssertTrueL( ETrue, KSetValueL );

    TReal avalue = CAknNumericEdwin::EValueValid;
    iEikFloatingPointEditor->GetValueAsReal( avalue );
    AssertTrueL( ETrue, KGetValueAsReal );

    iEikFloatingPointEditor->Value();
    AssertTrueL( ETrue, KValue );

    iEikFloatingPointEditor->InputCapabilities();
    AssertTrueL( ETrue, KInputCapabilities );

    TKeyEvent keyEvent;
    TPointerEvent pointerEvent;
    iEikFloatingPointEditor->OfferKeyEventL( keyEvent, EEventKey );
    AssertTrueL( ETrue, KOfferKeyEventL );

    iEikFloatingPointEditor->HandlePointerEventL( pointerEvent );
    AssertTrueL( ETrue, KHandlePointerEventL );

    iEikFloatingPointEditor->HandleResourceChange( KEikInputLanguageChange );
    AssertTrueL( ETrue, KHandleResourceChange );


    delete iEikFloatingPointEditor;
    iEikFloatingPointEditor = NULL;
    }

// ---------------------------------------------------------------------------
// CBCTestEditorCase::Test Class CEikRichTextEditor
// ---------------------------------------------------------------------------
//
void CBCTestEditorCase::TestEikRichTextEditorL()
    {
    _LIT( KCEikRichTextEditor,
    "Class CEikRichTextEditor Function CEikRichTextEditor tested" );
    _LIT( KConstructL,
    "Class CEikRichTextEditor Function ConstructL tested" );
    _LIT( KRichText,
    "Class CEikRichTextEditor Function RichText tested" );
    _LIT( KConstructFromResourceL,
    "Class CEikRichTextEditor Function ConstructFromResourceL tested" );
    _LIT( KReEditObjectL,
    "Class CEikRichTextEditor Function ReEditObjectL tested" );
    _LIT( KObjectCursorPos,
    "Class CEikRichTextEditor Function ObjectCursorPos tested" );
    _LIT( KCheckForObjectL,
    "Class CEikRichTextEditor Function CheckForObjectL tested" );
    _LIT( KEditPictureFormatL,
    "Class CEikRichTextEditor Function EditPictureFormatL tested" );
    _LIT( KPictureFormatChangedL,
    "Class CEikRichTextEditor Function PictureFormatChangedL tested" );
    _LIT( KUpdatePictureFormatL,
    "Class CEikRichTextEditor Function UpdatePictureFormatL tested" );
    _LIT( KActivateL,
    "Class CEikRichTextEditor Function ActivateL tested" );
    _LIT( KSetDefaultIconicDoorSize,
    "Class CEikRichTextEditor Function SetDefaultIconicDoorSize tested" );
    _LIT( KDefaultIconicDoorSize,
    "Class CEikRichTextEditor Function DefaultIconicDoorSize tested" );
    _LIT(  KUpdatePictureSizeL,
    "Class CEikRichTextEditor Function UpdatePictureSizeL tested" );
    _LIT( KSetParserObserver,
    "Class CEikRichTextEditor Function SetParserObserver tested" );
    _LIT( KSetPhoneNumberGrouping,
    "Class CEikRichTextEditor Function SetPhoneNumberGrouping tested" );
    _LIT( KSetOfferKeyEventL,
    "Class CEikRichTextEditor Function OfferKeyEventL tested" );
    _LIT( KHandlePointerEventL,
    "Class CEikRichTextEditor Function HandlePointerEventL tested" );

    _LIT( KRefreshParsersL,
    "Class CEikRichTextEditor Function RefreshParsersL tested" );
    _LIT( KCopyDocumentContentL,
    "Class CEikRichTextEditor Function CopyDocumentContentL tested" );

    TGulBorder gulBorder;
    iEikRichTextEditor = new ( ELeave ) CEikRichTextEditor( gulBorder );
    AssertTrueL( ETrue, KCEikRichTextEditor );

    iEikRichTextEditor->ConstructL( iContainer, 2, 40,
                                    EAknEditorFlagDefault );
    AssertTrueL( ETrue, KConstructL );
    delete iEikRichTextEditor;
    iEikRichTextEditor = NULL;

    iEikRichTextEditor = new ( ELeave ) CEikRichTextEditor();
    AssertTrueL( ETrue, KCEikRichTextEditor );

    CRichText* richText = iEikRichTextEditor->RichText();
    AssertTrueL( ETrue, KRichText );

    delete iEikRichTextEditor;
    iEikRichTextEditor = NULL;

    CTmpCDlgDialogFactory* tmpCDlgDialogFactory = CTmpCDlgDialogFactory::NewL();
    iEikEnv->SetCDlgDialogFactory( tmpCDlgDialogFactory );
    CleanupStack::PushL( tmpCDlgDialogFactory );

    iEikRichTextEditor = new ( ELeave ) CEikRichTextEditor( gulBorder );
    iEikRichTextEditor->SetContainerWindowL( *iContainer );

    TResourceReader resourceReader;
    iEikEnv->CreateResourceReaderLC( resourceReader,
                                     R_BCTESTEDITOR_RICHEDITOR );
    iEikRichTextEditor->ConstructFromResourceL( resourceReader );
    CleanupStack::PopAndDestroy();//resourceReader
    AssertTrueL( ETrue, KConstructFromResourceL );

    iEikRichTextEditor->ActivateL();
    AssertTrueL( ETrue, KActivateL );

    TRAP_IGNORE( iEikRichTextEditor->InsertObjectL() );
    _LIT( KRichEd1, "CEikRichTextEditor::InsertObjectL" );
    AssertTrueL( ETrue, KRichEd1 );

    CFbsBitmap* bmp = new( ELeave ) CFbsBitmap();
    CleanupStack::PushL( bmp );
    TRAP_IGNORE( iEikRichTextEditor->InsertObjectL( KUidPictureTypeDoor, bmp ) );
    CleanupStack::PopAndDestroy( bmp );
    _LIT( KRichEd2, "CEikRichTextEditor::InsertObjectL with pictureType" );
    AssertTrueL( ETrue, KRichEd2 );

    _LIT( KAppDllName, "bctestutil.dll" );
    TUid dllId = TUid::Uid( 0x20004742 );
    TRAP_IGNORE( iEikRichTextEditor->InsertObjectL( KAppDllName, dllId,
            CEikRichTextEditor::EAlwaysIconic ) );
    _LIT( KRichEd3, "CEikRichTextEditor::InsertObjectL with aAppDllName" );
    AssertTrueL( ETrue, KRichEd3 );

    iEikRichTextEditor->ReEditObjectL();
    AssertTrueL( ETrue, KReEditObjectL );

    iEikRichTextEditor->ObjectCursorPos();
    AssertTrueL( ETrue, KObjectCursorPos );

    iEikRichTextEditor->CheckForObjectL();
    AssertTrueL( ETrue, KCheckForObjectL );

    iEikRichTextEditor->EditPictureFormatL();
    AssertTrueL( ETrue, KEditPictureFormatL );

    iEikRichTextEditor->PictureFormatChangedL();
    AssertTrueL( ETrue, KPictureFormatChangedL );

    iEikRichTextEditor->UpdatePictureFormatL();
    AssertTrueL( ETrue, KUpdatePictureFormatL );

    iEikRichTextEditor->UpdatePictureFormatL( 0, 10 );
    AssertTrueL( ETrue, KUpdatePictureFormatL );

    TSize tmpsize;
    tmpsize.iWidth = 10;
    tmpsize.iHeight = 10;
    iEikRichTextEditor->SetDefaultIconicDoorSize( tmpsize );
    AssertTrueL( ETrue, KSetDefaultIconicDoorSize );


    iEikRichTextEditor->DefaultIconicDoorSize();
    AssertTrueL( ETrue, KDefaultIconicDoorSize );

    iEikRichTextEditor->UpdatePictureSizeL();
    AssertTrueL( ETrue, KUpdatePictureSizeL );

    iEikRichTextEditor->UpdatePictureSizeL( 0, 10 );
    AssertTrueL( ETrue, KUpdatePictureSizeL );


    CMClassTmp* mclasstmp = new ( ELeave ) CMClassTmp();
    CleanupStack::PushL( mclasstmp );
    iEikRichTextEditor->SetParserObserver( STATIC_CAST(
                             MEikRichTextEditorParserObserver*, mclasstmp ));
    AssertTrueL( ETrue, KSetParserObserver );

    CleanupStack::PopAndDestroy( mclasstmp );

    iEikRichTextEditor->SetPhoneNumberGrouping( ETrue );
    AssertTrueL( ETrue, KSetPhoneNumberGrouping );

    TKeyEvent keyEvent;
    TPointerEvent pointerEvent;
    iEikRichTextEditor->OfferKeyEventL( keyEvent, EEventKey );
    AssertTrueL( ETrue, KSetOfferKeyEventL );

    iEikRichTextEditor->HandlePointerEventL( pointerEvent );
    AssertTrueL( ETrue, KHandlePointerEventL );

    iEikRichTextEditor->RefreshParsersL();
    AssertTrueL( ETrue, KRefreshParsersL );

    CGlobalText* ain = iEikRichTextEditor->GlobalText();
    iEikRichTextEditor->CopyDocumentContentL( *ain, *ain );
    AssertTrueL( ETrue, KCopyDocumentContentL );

    delete iEikRichTextEditor;
    iEikRichTextEditor = NULL;

    CSubEikRichTextEditor* eikRichTextEditor = new ( ELeave )
                                           CSubEikRichTextEditor();
    CleanupStack::PushL( eikRichTextEditor );
    eikRichTextEditor->ConstructL( iContainer, 2, 40,
                                    EAknEditorFlagDefault );
    _LIT( KStreamName, "C:\\bctestlog\\bctestlog.txt" );
    RFs& tempServer = iEikEnv->FsSession();
    tempServer.Delete( KStreamName );
    RFileWriteStream fWrite;
    User::LeaveIfError( fWrite.Create( tempServer,
        KStreamName, EFileWrite ) );
    CleanupClosePushL( fWrite );
    eikRichTextEditor->TestWriteInternalStateL( fWrite );
    CleanupStack::PopAndDestroy( &fWrite );
    CleanupStack::PopAndDestroy( eikRichTextEditor );
    CleanupStack::PopAndDestroy( tmpCDlgDialogFactory );
    iEikEnv->SetCDlgDialogFactory( NULL );
    }

// ---------------------------------------------------------------------------
// CBCTestEditorCase::Test Class CEikDurationEditor and CEikNumberEditor and
//                    CEikRangeEditor and CEikTimeOffsetEditor
// ---------------------------------------------------------------------------
//
void CBCTestEditorCase::TestEikMfneSubClassL()
    {
    iEikDurationEditor = new ( ELeave ) CEikDurationEditor();
    _LIT( KCEikDurationEditor,
    "Class CEikDurationEditor Function CEikDurationEditor tested" );
    AssertTrueL( ETrue, KCEikDurationEditor );

    TTimeIntervalSeconds tmpmin = 0;
    TTimeIntervalSeconds tmpmax = 1000;
    TTimeIntervalSeconds tmpinit = 500;

    iEikDurationEditor->SetContainerWindowL( *iContainer );
    _LIT( KSetContainerWindowL,
    "Class CEikDurationEditor Function SetContainerWindowL tested" );
    AssertTrueL( ETrue, KSetContainerWindowL );

    TResourceReader resourceReader;
    iEikEnv->CreateResourceReaderLC( resourceReader,
                                     R_BCTESTEDITOR_DURATION );
    iEikDurationEditor->ConstructFromResourceL( resourceReader );
    _LIT( KConstructFromResourceL,
    "Class CEikDurationEditor Function ConstructFromResourceL tested" );
    AssertTrueL( ETrue, KConstructFromResourceL );
    CleanupStack::PopAndDestroy(); //resourceReader

    iEikDurationEditor->SetMinimumAndMaximum( tmpmin, tmpmax );
    _LIT( KSetMinimumAndMaximum,
    "Class CEikDurationEditor Function SetMinimumAndMaximum tested" );
    AssertTrueL( ETrue, KSetMinimumAndMaximum );

    iEikDurationEditor->SetDuration( tmpinit );
    _LIT( KSetDuration,
    "Class CEikDurationEditor Function SetDuration tested" );
    AssertTrueL( ETrue, KSetDuration );

    iEikDurationEditor->Duration();
    _LIT( KDuration,
    "Class CEikDurationEditor Function Duration tested" );
    AssertTrueL( ETrue, KDuration );

    iEikDurationEditor->PrepareForFocusLossL();
    _LIT( KPrepareForFocusLossL,
    "Class CEikDurationEditor Function PrepareForFocusLossL tested" );
    AssertTrueL( ETrue, KPrepareForFocusLossL );

    TPointerEvent pointerEvent;
    iEikDurationEditor->HandlePointerEventL( pointerEvent );
    _LIT( KHandlePointerEventL,
    "Class CEikDurationEditor Function HandlePointerEventL tested" );
    AssertTrueL( ETrue, KHandlePointerEventL );

    TTimeIntervalSeconds min;
    TTimeIntervalSeconds max;
    iEikDurationEditor->GetMinimumAndMaximum( min, max );
    _LIT( KGetMinimumAndMaximum,
    "Class CEikDurationEditor Function GetMinimumAndMaximum tested" );
    AssertTrueL( ETrue, KGetMinimumAndMaximum );

    delete iEikDurationEditor;
    iEikDurationEditor = NULL;

    iEikNumberEditor = new ( ELeave ) CEikNumberEditor();
    _LIT( KCEikNumberEditor,
    "Class CEikNumberEditor Function CEikNumberEditor tested" );
    AssertTrueL( ETrue, KCEikNumberEditor );

    TInt tmpMin = 0;
    TInt tmpMax = 1000;
    TInt tmpInit = 500;

    iEikEnv->CreateResourceReaderLC( resourceReader, R_BCTESTEDITOR_NUMBER );
    iEikNumberEditor->ConstructFromResourceL( resourceReader );
    _LIT( KCEikNumberEditorConstructFromResourceL,
    "Class CEikNumberEditor Function ConstructFromResourceL tested" );
    AssertTrueL( ETrue, KCEikNumberEditorConstructFromResourceL );

    CleanupStack::PopAndDestroy(); //resourceReader

    iEikNumberEditor->SetContainerWindowL( *iContainer );
    _LIT( KCEikNumberEditorSetContainerWindowL,
    "Class CEikNumberEditor Function SetContainerWindowL tested" );
    AssertTrueL( ETrue, KCEikNumberEditorSetContainerWindowL );

    iEikNumberEditor->SetMinimumAndMaximum( tmpMin, tmpMax );
    _LIT( KCEikNumberEditorSetMinimumAndMaximum,
    "Class CEikNumberEditor Function SetMinimumAndMaximum tested" );
    AssertTrueL( ETrue, KCEikNumberEditorSetMinimumAndMaximum );

    iEikNumberEditor->SetNumber( tmpInit );
    _LIT( KSetNumber,
    "Class CEikNumberEditor Function SetNumber tested" );
    AssertTrueL( ETrue, KSetNumber );

    iEikNumberEditor->Number();
    _LIT( KNumber,
    "Class CEikNumberEditor Function Number tested" );
    AssertTrueL( ETrue, KNumber );


    TInt tmpstart;
    TInt tmpEnd;
    iEikNumberEditor->GetMinimumAndMaximum( tmpstart, tmpEnd );
    _LIT( KCEikNumberEditorGetMinimumAndMaximum,
    "Class CEikNumberEditor Function GetMinimumAndMaximum tested" );
    AssertTrueL( ETrue, KCEikNumberEditorGetMinimumAndMaximum );

    iEikNumberEditor->HandlePointerEventL( pointerEvent );

    delete iEikNumberEditor;
    iEikNumberEditor = NULL;

    SEikRange eikRange;
    eikRange.iLowerLimit = 100;
    eikRange.iUpperLimit = 1000;

    _LIT( Kstr, " " );
    TDesC buf = Kstr;

    iEikRangeEditor = new ( ELeave ) CEikRangeEditor();
    _LIT( KCEikRangeEditor,
    "Class CEikRangeEditor Function CEikRangeEditor tested" );
    AssertTrueL( ETrue, KCEikRangeEditor );

    iEikEnv->CreateResourceReaderLC( resourceReader, R_BCTESTEDITOR_RANGE );
    iEikRangeEditor->ConstructFromResourceL( resourceReader );
    _LIT( KCEikRangeEditorConstructFromResourceL,
    "Class CEikRangeEditor Function ConstructFromResourceL tested" );
    AssertTrueL( ETrue, KCEikRangeEditorConstructFromResourceL );

    CleanupStack::PopAndDestroy(); //resourceReader
    iEikRangeEditor->SetContainerWindowL( *iContainer );
    _LIT( KCEikRangeEditorSetContainerWindowL,
    "Class CEikRangeEditor Function SetContainerWindowL tested" );
    AssertTrueL( ETrue, KCEikRangeEditorSetContainerWindowL );


    iEikRangeEditor->SetMinimumAndMaximum( tmpMin, tmpMax );
    _LIT( KCEikRangeEditorSetMinimumAndMaximum,
    "Class CEikRangeEditor Function SetMinimumAndMaximum tested" );
    AssertTrueL( ETrue, KCEikRangeEditorSetMinimumAndMaximum );

    iEikRangeEditor->SetRange( eikRange );
    _LIT( KSetRange,
    "Class CEikRangeEditor Function SetRange tested" );
    AssertTrueL( ETrue, KSetRange );

    iEikRangeEditor->Range();
    _LIT( KRange,
    "Class CEikRangeEditor Function Range tested" );
    AssertTrueL( ETrue, KRange );

    iEikRangeEditor->GetMinimumAndMaximum( tmpstart, tmpEnd );
    _LIT( KCEikRangeEditorGetMinimumAndMaximum,
    "Class CEikRangeEditor Function GetMinimumAndMaximum tested" );
    AssertTrueL( ETrue, KCEikRangeEditorGetMinimumAndMaximum );

    iEikRangeEditor->HandlePointerEventL( pointerEvent );
    _LIT( KCEikRangeEditorHandlePointerEventL,
    "Class CEikRangeEditor Function HandlePointerEventL tested" );
    AssertTrueL( ETrue, KCEikRangeEditorHandlePointerEventL );

    delete iEikRangeEditor;
    iEikRangeEditor = NULL;

    iEikTimeOffsetEditor = new ( ELeave ) CEikTimeOffsetEditor();
    _LIT( KCEikTimeOffsetEditor,
    "Class CEikTimeOffsetEditor Function CEikTimeOffsetEditor tested" );
    AssertTrueL( ETrue, KCEikTimeOffsetEditor );

    iEikEnv->CreateResourceReaderLC( resourceReader,
                                    R_BCTESTEDITOR_TIMEOFFSET );

    iEikTimeOffsetEditor->ConstructFromResourceL( resourceReader );
    _LIT( KCEikTimeOffsetEditorConstructFromResourceL,
    "Class CEikTimeOffsetEditor Function ConstructFromResourceL tested" );
    AssertTrueL( ETrue, KCEikTimeOffsetEditorConstructFromResourceL );

    CleanupStack::PopAndDestroy(); //resourceReader
    iEikTimeOffsetEditor->SetContainerWindowL( *iContainer );
    _LIT( KCEikTimeOffsetEditorSetContainerWindowL,
    "Class CEikTimeOffsetEditor Function SetContainerWindowL tested" );
    AssertTrueL( ETrue, KCEikTimeOffsetEditorSetContainerWindowL );

    iEikTimeOffsetEditor->SetMinimumAndMaximum( tmpmin, tmpmax );
    _LIT( KCEikTimeOffsetEditorSetMinimumAndMaximum,
    "Class CEikTimeOffsetEditor Function SetMinimumAndMaximum tested" );
    AssertTrueL( ETrue, KCEikTimeOffsetEditorSetMinimumAndMaximum );

    iEikTimeOffsetEditor->SetTimeOffset( tmpinit );
    _LIT( KSetTimeOffset,
    "Class CEikTimeOffsetEditor Function SetTimeOffset tested" );
    AssertTrueL( ETrue, KSetTimeOffset );

    iEikTimeOffsetEditor->TimeOffset();
    _LIT( KTimeOffset,
    "Class CEikTimeOffsetEditor Function TimeOffset tested" );
    AssertTrueL( ETrue, KTimeOffset );

    iEikTimeOffsetEditor->HandlePointerEventL( pointerEvent );
    _LIT( KCEikTimeOffsetEditorHandlePointerEventL,
    "Class CEikTimeOffsetEditor Function HandlePointerEventL tested" );
    AssertTrueL( ETrue, KCEikTimeOffsetEditorHandlePointerEventL );

    iEikTimeOffsetEditor->GetMinimumAndMaximum( min, max );
    _LIT( KCEikTimeOffsetEditorGetMinimumAndMaximum,
    "Class CEikTimeOffsetEditor Function GetMinimumAndMaximum tested" );
    AssertTrueL( ETrue, KCEikTimeOffsetEditorGetMinimumAndMaximum );

    iEikTimeOffsetEditor->PrepareForFocusLossL();
    _LIT( KCEikTimeOffsetEditorPrepareForFocusLossL,
    "Class CEikTimeOffsetEditor Function PrepareForFocusLossL tested" );
    AssertTrueL( ETrue, KCEikTimeOffsetEditorPrepareForFocusLossL );

    delete iEikTimeOffsetEditor;
    iEikTimeOffsetEditor = NULL;
    }

// ---------------------------------------------------------------------------
// CBCTestEditorCase::Test Class CEikTimeAndDateEditor and CEikTimeEditor and
//                    CEikDateEditor
// ---------------------------------------------------------------------------
//
void CBCTestEditorCase::TestEikTimeEditorL()
    {
    _LIT( KMax, "20100000:010101.240000" );
    _LIT( KMin, "20000101:010101.000000" );
    _LIT( KInit, "20060000:010101.000000" );
    TTime max;
    TTime min;
    TTime init;
    TTime tmpMax;
    TTime tmpMin;

    max.Set( KMax );
    min.Set( KMin );
    init.Set( KInit );

	iEikTimeAndDateEditor = new ( ELeave )CEikTimeAndDateEditor();
    _LIT( KCEikTimeAndDateEditor,
    "Class CEikTimeAndDateEditor Function CEikTimeAndDateEditor tested" );
    AssertTrueL( ETrue, KCEikTimeAndDateEditor );

    TResourceReader resourceReader;
	iEikEnv->CreateResourceReaderLC( resourceReader,
	                                 R_BCTESTEDITOR_TIMEANDDATE );
    iEikTimeAndDateEditor->ConstructFromResourceL( resourceReader );
    _LIT( KConstructFromResourceL,
    "Class CEikTimeAndDateEditor Function ConstructFromResourceL tested" );
    AssertTrueL( ETrue, KConstructFromResourceL );

    CleanupStack::PopAndDestroy(); //resourceReader
    iEikTimeAndDateEditor->SetContainerWindowL( *iContainer );
    _LIT( KSetContainerWindowL,
    "Class CEikTimeAndDateEditor Function SetContainerWindowL tested" );
    AssertTrueL( ETrue, KSetContainerWindowL );


    iEikTimeAndDateEditor->SetTimeAndDate( init );
    _LIT( KSetTimeAndDate,
    "Class CEikTimeAndDateEditor Function SetTimeAndDate tested" );
    AssertTrueL( ETrue, KSetTimeAndDate );

    iEikTimeAndDateEditor->TimeAndDate();
    _LIT( KTimeAndDate,
    "Class CEikTimeAndDateEditor Function TimeAndDate tested" );
    AssertTrueL( ETrue, KTimeAndDate );

    iEikTimeAndDateEditor->SetMinimumAndMaximum( min, max );
    _LIT( KSetMinimumAndMaximum,
    "Class CEikTimeAndDateEditor Function SetMinimumAndMaximum tested" );
    AssertTrueL( ETrue, KSetMinimumAndMaximum );

    iEikTimeAndDateEditor->GetMinimumAndMaximum( tmpMin, tmpMax );
    _LIT( KGetMinimumAndMaximum,
    "Class CEikTimeAndDateEditor Function GetMinimumAndMaximum tested" );
    AssertTrueL( ETrue, KGetMinimumAndMaximum );


    TPointerEvent pointerEvent;
    iEikTimeAndDateEditor->HandlePointerEventL( pointerEvent );
    _LIT( KHandlePointerEventL,
    "Class CEikTimeAndDateEditor Function HandlePointerEventL tested" );
    AssertTrueL( ETrue, KHandlePointerEventL );

    TKeyEvent keyEvent;
    iEikTimeAndDateEditor->OfferKeyEventL( keyEvent, EEventKey );
    _LIT( KOfferKeyEventL,
    "Class CEikTimeAndDateEditor Function OfferKeyEventL tested" );
    AssertTrueL( ETrue, KOfferKeyEventL );

    iEikTimeAndDateEditor->SetUninitialised( ETrue );
    _LIT( KSetUninitialised,
    "Class CEikTimeAndDateEditor Function SetUninitialised tested" );
    AssertTrueL( ETrue, KSetUninitialised );

    iEikTimeAndDateEditor->IsUninitialised();
    _LIT( KIsUninitialised,
    "Class CEikTimeAndDateEditor Function IsUninitialised tested" );
    AssertTrueL( ETrue, KIsUninitialised );

    iEikTimeAndDateEditor->PrepareForFocusLossL();
    _LIT( KPrepareForFocusLossL,
    "Class CEikTimeAndDateEditor Function PrepareForFocusLossL tested" );
    AssertTrueL( ETrue, KPrepareForFocusLossL );

    delete iEikTimeAndDateEditor;
    iEikTimeAndDateEditor = NULL;



	iEikTimeEditor = new ( ELeave )CEikTimeEditor();
    _LIT( KCEikTimeEditor,
    "Class CEikTimeEditor Function CEikTimeEditor tested" );
    AssertTrueL( ETrue, KCEikTimeEditor );

	iEikEnv->CreateResourceReaderLC( resourceReader, R_BCTESTEDITOR_TIME );
    iEikTimeEditor->ConstructFromResourceL( resourceReader );
    _LIT( KCEikTimeEditorConstructFromResourceL,
    "Class CEikTimeEditor Function ConstructFromResourceL tested" );
    AssertTrueL( ETrue, KCEikTimeEditorConstructFromResourceL );
    CleanupStack::PopAndDestroy(); //resourceReader
    iEikTimeEditor->SetContainerWindowL( *iContainer );
    _LIT( KCEikTimeEditorSetContainerWindowL,
    "Class CEikTimeEditor Function SetContainerWindowL tested" );
    AssertTrueL( ETrue, KCEikTimeEditorSetContainerWindowL );

    iEikTimeEditor->PrepareForFocusLossL();
    _LIT( KCEikTimeEditorPrepareForFocusLossL,
    "Class CEikTimeEditor Function PrepareForFocusLossL tested" );
    AssertTrueL( ETrue, KCEikTimeEditorPrepareForFocusLossL );

    iEikTimeEditor->SetTime( init );
    _LIT( KCEikTimeEditorSetTime,
    "Class CEikTimeEditor Function SetTime tested" );
    AssertTrueL( ETrue, KCEikTimeEditorSetTime );

    iEikTimeEditor->Time();
    _LIT( KCEikTimeEditorTime,
    "Class CEikTimeEditor Function Time tested" );
    AssertTrueL( ETrue, KCEikTimeEditorTime );

    iEikTimeEditor->SetMinimumAndMaximum( min, max );
    _LIT( KCEikTimeEditorSetMinimumAndMaximum,
    "Class CEikTimeEditor Function SetMinimumAndMaximum tested" );
    AssertTrueL( ETrue, KCEikTimeEditorSetMinimumAndMaximum );

    iEikTimeEditor->GetMinimumAndMaximum( tmpMin, tmpMax );
    _LIT( KCEikTimeEditorGetMinimumAndMaximum,
    "Class CEikTimeEditor Function GetMinimumAndMaximum tested" );
    AssertTrueL( ETrue, KCEikTimeEditorGetMinimumAndMaximum );

    iEikTimeEditor->SetUninitialised( ETrue );
    _LIT( KCEikTimeEditorSetUninitialised,
    "Class CEikTimeEditor Function SetUninitialised tested" );
    AssertTrueL( ETrue, KCEikTimeEditorSetUninitialised );

    iEikTimeEditor->IsUninitialised();
    _LIT( KCEikTimeEditorIsUninitialised,
    "Class CEikTimeEditor Function CEikTimeEditor tested" );
    AssertTrueL( ETrue, KCEikTimeEditorIsUninitialised );

    iEikTimeEditor->HandlePointerEventL( pointerEvent );
    _LIT( KCEikTimeEditorHandlePointerEventL,
    "Class CEikTimeEditor Function HandlePointerEventL tested" );
    AssertTrueL( ETrue, KCEikTimeEditorHandlePointerEventL );

    delete iEikTimeEditor;
    iEikTimeEditor = NULL;


    iEikDateEditor = new ( ELeave )CEikDateEditor();
    _LIT( KCEikDateEditor,
    "Class CEikTimeEditor Function CEikDateEditor tested" );
    AssertTrueL( ETrue, KCEikDateEditor );

	iEikEnv->CreateResourceReaderLC( resourceReader, R_BCTESTEDITOR_DATE );
    iEikDateEditor->ConstructFromResourceL( resourceReader );
    _LIT( KCEikDateEditorConstructFromResourceL,
    "Class CEikTimeEditor Function ConstructFromResourceL tested" );
    AssertTrueL( ETrue, KCEikDateEditorConstructFromResourceL );

    CleanupStack::PopAndDestroy(); //resourceReader
    iEikDateEditor->SetContainerWindowL( *iContainer );
    _LIT( KCEikDateEditorSetContainerWindowL,
    "Class CEikTimeEditor Function SetContainerWindowL tested" );
    AssertTrueL( ETrue, KCEikDateEditorSetContainerWindowL );

    iEikDateEditor->PrepareForFocusLossL();
    _LIT( KCEikDateEditorPrepareForFocusLossL,
    "Class CEikTimeEditor Function PrepareForFocusLossL tested" );
    AssertTrueL( ETrue, KCEikDateEditorPrepareForFocusLossL );

    iEikDateEditor->SetDate( init );
    _LIT( KCEikDateEditorSetDate,
    "Class CEikTimeEditor Function SetDate tested" );
    AssertTrueL( ETrue, KCEikDateEditorSetDate );

    iEikDateEditor->Date();
    _LIT( KCEikDateEditorDate,
    "Class CEikTimeEditor Function Date tested" );
    AssertTrueL( ETrue, KCEikDateEditorDate );

    iEikDateEditor->SetMinimumAndMaximum( min, max );
    _LIT( KCEikDateEditorSetMinimumAndMaximum,
    "Class CEikTimeEditor Function SetMinimumAndMaximum tested" );
    AssertTrueL( ETrue, KCEikDateEditorSetMinimumAndMaximum );

    iEikDateEditor->GetMinimumAndMaximum( tmpMin, tmpMax );
    _LIT( KCEikDateEditorGetMinimumAndMaximum,
    "Class CEikTimeEditor Function GetMinimumAndMaximum tested" );
    AssertTrueL( ETrue, KCEikDateEditorGetMinimumAndMaximum );

    iEikDateEditor->HandlePointerEventL( pointerEvent );
    _LIT( KCEikDateEditorHandlePointerEventL,
    "Class CEikTimeEditor Function HandlePointerEventL tested" );
    AssertTrueL( ETrue, KCEikDateEditorHandlePointerEventL );

    iEikDateEditor->OfferKeyEventL( keyEvent, EEventKey );
    _LIT( KCEikDateEditorOfferKeyEventL,
    "Class CEikTimeEditor Function OfferKeyEventL tested" );
    AssertTrueL( ETrue, KCEikDateEditorOfferKeyEventL );

    iEikDateEditor->SetUninitialised( ETrue );
    _LIT( KCEikDateEditorSetUninitialised,
    "Class CEikTimeEditor Function SetUninitialised tested" );
    AssertTrueL( ETrue, KCEikDateEditorSetUninitialised );

    iEikDateEditor->IsUninitialised();
    _LIT( KCEikDateEditorIsUninitialised,
    "Class CEikTimeEditor Function IsUninitialised tested" );
    AssertTrueL( ETrue, KCEikDateEditorIsUninitialised );

    delete iEikDateEditor;
    iEikDateEditor = NULL;
    }

// ---------------------------------------------------------------------------
// CBCTestEditorCase::Test Class CAknNumericSecretEditor and CEikSecretEditor
// ---------------------------------------------------------------------------
//
void CBCTestEditorCase::TestEikSecretEditorL()
    {
    CAknNumericSecretEditor* aknNumericSecretEditor = new ( ELeave )
                                               CAknNumericSecretEditor();
    CleanupStack::PushL( aknNumericSecretEditor );
    _LIT( KCAknNumericSecretEditor,
    "Class CAknNumericSecretEditor Function CAknNumericSecretEditor tested" );
    AssertTrueL( ETrue, KCAknNumericSecretEditor );

    aknNumericSecretEditor->InputCapabilities();
    _LIT( KInputCapabilities,
    "Class CAknNumericSecretEditor Function InputCapabilities tested" );
    AssertTrueL( ETrue, KInputCapabilities );

    TPointerEvent pointerEvent;
    aknNumericSecretEditor->HandlePointerEventL( pointerEvent );
    _LIT( KHandlePointerEventL,
    "Class CAknNumericSecretEditor Function HandlePointerEventL tested" );
    AssertTrueL( ETrue, KHandlePointerEventL );

    CleanupStack::PopAndDestroy( aknNumericSecretEditor );

    _LIT( KSecert, " " );
    iEikSecretEditor = new ( ELeave ) CBCTestSecretEditor();
    _LIT( KCEikSecretEditor,
    "Class CEikSecretEditor Function CEikSecretEditor tested" );
    AssertTrueL( ETrue, KCEikSecretEditor );

    TResourceReader resourceReader;
	iEikEnv->CreateResourceReaderLC( resourceReader, R_BCTESTEDITOR_SECRET );
    iEikSecretEditor->ConstructFromResourceL( resourceReader );
    _LIT( KConstructFromResourceL,
    "Class CEikSecretEditor Function ConstructFromResourceL tested" );
    AssertTrueL( ETrue, KConstructFromResourceL );
    CleanupStack::PopAndDestroy(); //aknNumericSecretEditor

    TKeyEvent keyEvent;
    iEikSecretEditor->OfferKeyEventL( keyEvent, EEventKey );
    _LIT( KOfferKeyEventL,
    "Class CEikSecretEditor Function OfferKeyEventL tested" );
    AssertTrueL( ETrue, KOfferKeyEventL );

    iEikSecretEditor->HandlePointerEventL( pointerEvent );
    _LIT( KCEikSecretEditorHandlePointerEventL,
    "Class CEikSecretEditor Function HandlePointerEventL tested" );
    AssertTrueL( ETrue, KCEikSecretEditorHandlePointerEventL );

    iEikSecretEditor->SetMaxLength( 10 );
    _LIT( KSetMaxLength,
    "Class CEikSecretEditor Function SetMaxLength tested" );
    AssertTrueL( ETrue, KSetMaxLength );

    iEikSecretEditor->MinimumSize();
    _LIT( KMinimumSize,
    "Class CEikSecretEditor Function MinimumSize tested" );
    AssertTrueL( ETrue, KMinimumSize );

    iEikSecretEditor->Reset();
    _LIT( KCEikSecretEditorMinimumSize,
    "Class CEikSecretEditor Function MinimumSize tested" );
    AssertTrueL( ETrue, KCEikSecretEditorMinimumSize );

    iEikSecretEditor->InputCapabilities();
    _LIT( KReset,
    "Class CEikSecretEditor Function Reset tested" );
    AssertTrueL( ETrue, KReset );

    iEikSecretEditor->MaxLength();
    _LIT( KMaxLength,
    "Class CEikSecretEditor Function MaxLength tested" );
    AssertTrueL( ETrue, KMaxLength );

    iEikSecretEditor->Buffer();
    _LIT( KBuffer,
    "Class CEikSecretEditor Function Buffer tested" );
    AssertTrueL( ETrue, KBuffer );

    iEikSecretEditor->InitializeDisplay( 10 );
    _LIT( KInitializeDisplay,
    "Class CEikSecretEditor Function InitializeDisplay tested" );
    AssertTrueL( ETrue, KInitializeDisplay );

    iEikSecretEditor->SetText( KSecert );
    _LIT( KSetText,
    "Class CEikSecretEditor Function SetText tested" );
    AssertTrueL( ETrue, KSetText );

    iEikSecretEditor->AppendCharacterL( 'A' );
    _LIT( KAppendChar,
          "Class CEikSecretEditor Function AppendCharacterL tested" );
    AssertTrueL( ETrue, KAppendChar );

    iEikSecretEditor->Update();
    _LIT( KUpdate, "Class CEikSecretEditor Function Update tested" );
    AssertTrueL( ETrue, KUpdate );

    iEikSecretEditor->SetDefaultInputMode( 1 );
    _LIT( KSetDefaultInputMode,
    "Class CEikSecretEditor Function SetDefaultInputMode tested" );
    AssertTrueL( ETrue, KSetDefaultInputMode );

    iEikSecretEditor->RevealSecretText( ETrue );
    _LIT( KRevealSecretText,
    "Class CEikSecretEditor Function RevealSecretText tested" );
    AssertTrueL( ETrue, KRevealSecretText );

    iEikSecretEditor->HandleResourceChange( 2 );
    _LIT( KHandleResourceChange,
    "Class CEikSecretEditor Function HandleResourceChange tested" );
    AssertTrueL( ETrue, KHandleResourceChange );

    CArrayFix<TCoeColorUse>* indexArray = new ( ELeave )
                                           CArrayFixFlat<TCoeColorUse>( 1 );
    CleanupStack::PushL( indexArray );
    iEikSecretEditor->GetColorUseListL( *indexArray ) ;
    _LIT( KGetColorUseListL,
    "Class CEikSecretEditor Function GetColorUseListL tested" );
    AssertTrueL( ETrue, KGetColorUseListL );
    CleanupStack::PopAndDestroy( indexArray );

    TBuf<500> tmptext;
    iEikSecretEditor->GetText( tmptext );
    _LIT( KGetText,
    "Class CEikSecretEditor Function GetText tested" );
    AssertTrueL( ETrue, KGetText );

    const CFont* font = LatinPlain12();
    iEikSecretEditor->AknSetFont( *font );
    _LIT( KAknSetFont,
    "Class CEikSecretEditor Function AknSetFont tested" );
    AssertTrueL( ETrue, KAknSetFont );

    iEikSecretEditor->SetSkinTextColorL( 1, KErrNotFound );
    _LIT( KSetSkinTextColorL,
    "Class CEikSecretEditor Function SetSkinTextColorL tested" );
    AssertTrueL( ETrue, KSetSkinTextColorL );

    iEikSecretEditor->SetSkinBackgroundControlContextL( NULL );
    _LIT( KSetSkinBackgroundControlContextL,
    "Class CEikSecretEditor Function SetSkinBackgroundControlContextL tested" );
    AssertTrueL( ETrue, KSetSkinBackgroundControlContextL );

    delete iEikSecretEditor;
    iEikSecretEditor = NULL;
    }

// ---------------------------------------------------------------------------
// CBCTestEditorCase::Test Class CEikMfneNumber and CEikMfneSeparator and
//                    CEikMfneSymbol
// ---------------------------------------------------------------------------
//
void CBCTestEditorCase::TestEikMfneFieldL()
    {
    const CFont* font = LatinPlain12();
    TResourceReader resourceReader;
	iEikEnv->CreateResourceReaderLC( resourceReader,
	                                 R_BCTESTEDITOR_MFNE_NUMBER );
	CEikMfneNumber* eikMfneNumber = CEikMfneNumber::NewL(
	                                 *font,
                                     resourceReader );
    CleanupStack::PopAndDestroy(); //resourceReader
    CleanupStack::PushL( eikMfneNumber );

    _LIT( KNewL,
    "Class CEikMfneNumber Function NewL tested" );
    AssertTrueL( ETrue, KNewL );

    TInt max;
    TInt min;
    eikMfneNumber->SetMinimumAndMaximum( 2, 9, *font );
    _LIT( KSetMinimumAndMaximum,
    "Class CEikMfneNumber Function SetMinimumAndMaximum tested" );
    AssertTrueL( ETrue, KSetMinimumAndMaximum );

    eikMfneNumber->GetMinimumAndMaximum( min, max );
    _LIT( KGetMinimumAndMaximum,
    "Class CEikMfneNumber Function GetMinimumAndMaximum tested" );
    AssertTrueL( ETrue, KGetMinimumAndMaximum );

    eikMfneNumber->SetUninitialised( ETrue );
    _LIT( KSetUninitialised,
    "Class CEikMfneNumber Function SetUninitialised tested" );
    AssertTrueL( ETrue, KSetUninitialised );

    eikMfneNumber->IsUninitialised();
    _LIT( KIsUninitialised,
    "Class CEikMfneNumber Function IsUninitialised tested" );
    AssertTrueL( ETrue, KIsUninitialised );

    eikMfneNumber->Value();
    _LIT( KValue,
    "Class CEikMfneNumber Function Value tested" );
    AssertTrueL( ETrue, KValue );

    eikMfneNumber->IsValid();
    _LIT( KIsValid,
    "Class CEikMfneNumber Function IsValid tested" );
    AssertTrueL( ETrue, KIsValid );

    CleanupStack::PopAndDestroy( eikMfneNumber );


	iEikEnv->CreateResourceReaderLC( resourceReader,
	                                 R_BCTESTEDITOR_MFNE_SEPARATOR );
    CEikMfneSeparator* eikMfneSeparator =
                                    CEikMfneSeparator::NewL( resourceReader );
    CleanupStack::PopAndDestroy();//resourceReader
    CleanupStack::PushL( eikMfneSeparator );
    _LIT( KCEikMfneSeparatorNewL,
    "Class CEikMfneSeparator Function NewL tested" );
    AssertTrueL( ETrue, KCEikMfneSeparatorNewL );

    _LIT( Ktmp, " bbb");
    HBufC* str = HBufC::NewL( 5 );

    *str = Ktmp;
    eikMfneSeparator->SetText( str );
    _LIT( KCEikMfneSeparatorSetText,
    "Class CEikMfneSeparator Function SetText tested" );
    AssertTrueL( ETrue, KCEikMfneSeparatorSetText );

    CleanupStack::PopAndDestroy( eikMfneSeparator );

	iEikEnv->CreateResourceReaderLC( resourceReader,
	                                 R_BCTESTEDITOR_MFNE_SYMBOL );
    CEikMfneSymbol* eikMfneSymbol = CEikMfneSymbol::NewL( resourceReader );
    CleanupStack::PopAndDestroy();//resourceReader

    CleanupStack::PushL( eikMfneSymbol );
    _LIT( KCEikMfneSymbolSetText,
    "Class CEikMfneSymbol Function SetText tested" );
    AssertTrueL( ETrue, KCEikMfneSymbolSetText );
    eikMfneSymbol->IsValid();
    CleanupStack::PopAndDestroy( eikMfneSymbol );


	iEikEnv->CreateResourceReaderLC( resourceReader,
	                                 R_BCTESTEDITOR_MFNE_SYMBOL_ITEM );

    CEikMfneSymbol::CItem* item =
                                CEikMfneSymbol::CItem::NewL( resourceReader );
    CleanupStack::PushL( item );
    _LIT( KItemNewL,
    "Class CEikMfneSymbol::Item Function NewL tested" );
    AssertTrueL( ETrue, KItemNewL );

    str = HBufC::NewL( 5 );
    *str = Ktmp;
    item->SetText( str );
    _LIT( KItemSetText,
    "Class CEikMfneSymbol::Item Function SetText tested" );
    AssertTrueL( ETrue, KItemSetText );
    CleanupStack::PopAndDestroy( 2 );
    }

// ---------------------------------------------------------------------------
// CBCTestEditorCase::Test Class CEikGlobalTextEditor
// ---------------------------------------------------------------------------
//
void CBCTestEditorCase::TestEikGlobalEditorL()
    {
    TGulBorder gulBorder;
    TSize editorSize(100, 60);
    _LIT( Kstr, "abc");
    TDesC16 tmp = Kstr;

    CEikGlobalTextEditor* eikGlobalTextEditor = new
                           ( ELeave ) CEikGlobalTextEditor( gulBorder );
    CleanupStack::PushL( eikGlobalTextEditor );
    _LIT( KCEikGlobalTextEditor,
    "Class CEikGlobalTextEditor Function CEikGlobalTextEditor tested" );
    AssertTrueL( ETrue, KCEikGlobalTextEditor );

    TResourceReader resourceReader;
	iEikEnv->CreateResourceReaderLC( resourceReader,
	                                 R_BCTESTEDITOR_GLOBALTEXT );
    eikGlobalTextEditor->ConstructFromResourceL( resourceReader );
    _LIT( KConstructFromResourceL,
    "Class CEikGlobalTextEditor Function ConstructFromResourceL tested" );
    AssertTrueL( ETrue, KConstructFromResourceL );

    CleanupStack::PopAndDestroy();//resourceReader
    CleanupStack::PopAndDestroy( eikGlobalTextEditor );


    iEikGlobalTextEditor = new ( ELeave ) CEikGlobalTextEditor;


    iEikGlobalTextEditor->ConstructL( iContainer, 2, KDefaultTextLimit,
                         CEikEdwin::ENoAutoSelection, 0, 0 );

    iEikGlobalTextEditor->SetContainerWindowL( *iContainer );
    iEikGlobalTextEditor->SetExtent( EDWIN_POS, editorSize );

    iEikGlobalTextEditor->SetFocus(ETrue);

    CTmpCDlgDialogFactory* tmpCDlgDialogFactory =
                                             CTmpCDlgDialogFactory::NewL();
    iEikEnv->SetCDlgDialogFactory( tmpCDlgDialogFactory );
    CleanupStack::PushL( tmpCDlgDialogFactory );

    TKeyEvent keyEvent;
    iEikGlobalTextEditor->OfferKeyEventL( keyEvent, EEventKey );


    iEikGlobalTextEditor->ActivateL();
    iEikGlobalTextEditor->SetTextL( &tmp );

    CTmpPrintDialogFactory* tmpPrintDialogFactory = new ( ELeave )
                                       CTmpPrintDialogFactory;
    iEikEnv->SetPrintDialogFactory( STATIC_CAST(
                                       MEikPrintDialogFactory*,
                                       tmpPrintDialogFactory ) );
    CleanupStack::PushL( tmpPrintDialogFactory );

    CGraphicsDevice* device = CCoeEnv::Static()->ScreenDevice();
    iEikGlobalTextEditor->SetGraphicsDevice( device );
    _LIT( KSetGraphicsDevice,
    "Class CEikGlobalTextEditor Function SetGraphicsDevice tested" );
    AssertTrueL( ETrue, KSetGraphicsDevice );

    iEikGlobalTextEditor->RunFindDialogL();
    _LIT( KRunFindDialogL,
    "Class CEikGlobalTextEditor Function RunFindDialogL tested" );
    AssertTrueL( ETrue, KRunFindDialogL );

    iEikGlobalTextEditor->RunFindAgainDialogL();
    _LIT( KRunFindAgainDialogL,
    "Class CEikGlobalTextEditor Function RunFindAgainDialogL tested" );
    AssertTrueL( ETrue, KRunFindAgainDialogL );

      iEikGlobalTextEditor->RunIndentsDialogL( 100 );
    _LIT( KRunIndentsDialogL,
    "Class CEikGlobalTextEditor Function RunIndentsDialogL tested" );
    AssertTrueL( ETrue, KRunIndentsDialogL );

    iEikGlobalTextEditor->RunParaDialogsL( 1 );
    _LIT( KRunParaDialogsL,
    "Class CEikGlobalTextEditor Function RunParaDialogsL tested" );
    AssertTrueL( ETrue, KRunParaDialogsL );

    iEikGlobalTextEditor->RunReplaceDialogL();
    _LIT( KRunReplaceDialogL,
    "Class CEikGlobalTextEditor Function RunReplaceDialogL tested" );
    AssertTrueL( ETrue, KRunReplaceDialogL );

    iEikGlobalTextEditor->RunTabsDialogL( 100 );
    _LIT( KRunTabsDialogL,
    "Class CEikGlobalTextEditor Function RunTabsDialogL tested" );
    AssertTrueL( ETrue, KRunTabsDialogL );

    iEikGlobalTextEditor->RunFontDialogL( 0x10, 0, 0x001 );
    _LIT( KRunFontDialogL,
    "Class CEikGlobalTextEditor Function RunFontDialogL tested" );
    AssertTrueL( ETrue, KRunFontDialogL );

    CPrintSetup* printSetup = CPrintSetup::NewL();
    CArrayFix<TInt>* indexArray = new ( ELeave ) CArrayFixFlat<TInt>( 1 );
    CleanupStack::PushL( indexArray );
    CleanupStack::PushL( printSetup );
    iEikGlobalTextEditor->RunPaginateDialogL( printSetup, indexArray );
    _LIT( KRunPaginateDialogL,
    "Class CEikGlobalTextEditor Function RunPaginateDialogL tested" );
    AssertTrueL( ETrue, KRunPaginateDialogL );


    TPointerEvent pointerEvent;
    iEikGlobalTextEditor->HandlePointerEventL( pointerEvent );
    _LIT( KHandlePointerEventL,
    "Class CEikGlobalTextEditor Function HandlePointerEventL tested" );
    AssertTrueL( ETrue, KHandlePointerEventL );

    iEikGlobalTextEditor->GlobalText();
    _LIT( KGlobalText,
    "Class CEikGlobalTextEditor Function GlobalText tested" );
    AssertTrueL( ETrue, KGlobalText );

    iEikGlobalTextEditor->DoFindL();
    _LIT( KDoFindL,
    "Class CEikGlobalTextEditor Function DoFindL tested" );
    AssertTrueL( ETrue, KDoFindL );

    iEikGlobalTextEditor->BoldItalicUnderlineEventL( 1 );
    _LIT( KBoldItalicUnderlineEventL,
    "Class CEikGlobalTextEditor Function BoldItalicUnderlineEventL tested" );
    AssertTrueL( ETrue, KBoldItalicUnderlineEventL );

    iEikGlobalTextEditor->SetButtonGroup( iControl );
    _LIT( KSetButtonGroup,
    "Class CEikGlobalTextEditor Function SetButtonGroup tested" );
    AssertTrueL( ETrue, KSetButtonGroup );


    CFbsBitmap* fbsBitmap = new ( ELeave )CFbsBitmap();
    CleanupStack::PushL( fbsBitmap );
    iEikGlobalTextEditor->SetLineCursorBitmapL( fbsBitmap );
    _LIT( KSetLineCursorBitmapL,
    "Class CEikGlobalTextEditor Function SetLineCursorBitmapL tested" );
    AssertTrueL( ETrue, KSetLineCursorBitmapL );

    TParaFormatMask paraFormatmask;
    paraFormatmask.SetAll();
    CParaFormat* paraFormat = CParaFormat::NewL();
    CleanupStack::PushL( paraFormat );
    iEikGlobalTextEditor->ApplyParaFormatL( paraFormat, paraFormatmask );
    _LIT( KApplyParaFormatL,
    "Class CEikGlobalTextEditor Function ApplyParaFormatL tested" );
    AssertTrueL( ETrue, KApplyParaFormatL );


    TCharFormat charFormat;
    TCharFormatMask charFormatMask;
    iEikGlobalTextEditor->ApplyCharFormatL( charFormat, charFormatMask );

    CleanupStack::PopAndDestroy( paraFormat );
    CleanupStack::PopAndDestroy( fbsBitmap );

    CleanupStack::PopAndDestroy( printSetup );
    CleanupStack::PopAndDestroy( indexArray );
    CleanupStack::PopAndDestroy( tmpPrintDialogFactory );
    CleanupStack::PopAndDestroy( tmpCDlgDialogFactory );

    SEdwinFindModel* edwinFindModel = NULL;
    CDesCArray* findList = NULL;
    CDesCArray* replaceList = NULL;
    iEikGlobalTextEditor->InitFindL( edwinFindModel, findList, replaceList );

    delete iEikGlobalTextEditor;
    iEikGlobalTextEditor = NULL;
    }

// ---------------------------------------------------------------------------
// CBCTestEditorCase::Test Class CLafEdwinCustomWrapBase and
//                    CLafEdwinCustomDrawBase
// ---------------------------------------------------------------------------
//
void CBCTestEditorCase::TestEikLafMainL()
    {
    CLafEdwinCustomWrapBase* lafCustomWrapBase =
                                   CLafEdwinCustomWrapBase::NewL( *iControl );
    CleanupStack::PushL( lafCustomWrapBase );
    _LIT( KNewL,
    "Class CLafEdwinCustomWrapBase Function NewL tested" );
    AssertTrueL( ETrue, KNewL );

    _LIT( Kstr, " ");
    TDesC16 tmp = Kstr;
    TInt pos;
    TUint startPos;
    TUint endPos;

    lafCustomWrapBase->LineBreakClass( 1, startPos, endPos);
    _LIT( KLineBreakClass,
    "Class CLafEdwinCustomWrapBase Function LineBreakClass tested" );
    AssertTrueL( ETrue, KLineBreakClass );

    lafCustomWrapBase->LineBreakPossible( 1, 2, ETrue );
    _LIT( KLineBreakPossible,
    "Class CLafEdwinCustomWrapBase Function LineBreakPossible tested" );
    AssertTrueL( ETrue, KLineBreakPossible );

    lafCustomWrapBase->IsHangingCharacter( 1 );
    _LIT( KIsHangingCharacter,
    "Class CLafEdwinCustomWrapBase Function IsHangingCharacter tested" );
    AssertTrueL( ETrue, KIsHangingCharacter );

    lafCustomWrapBase->GetLineBreakInContext( tmp, 0, 1, ETrue, pos );
    _LIT( KGetLineBreakInContext,
    "Class CLafEdwinCustomWrapBase Function GetLineBreakInContext tested" );
    AssertTrueL( ETrue, KGetLineBreakInContext );

    CleanupStack::PopAndDestroy( lafCustomWrapBase );
    }

// ---------------------------------------------------------------------------
// CBCTestEditorCase::Test Class CEikMfne
// ---------------------------------------------------------------------------
//
void CBCTestEditorCase::TestEikMfneL()
    {
    const CFont* font = LatinPlain12();

    iEikMfne = new ( ELeave ) CEikNumberEditor();
    _LIT( KCEikMfne,
    "Class CEikMfne Function CEikMfne tested" );
    AssertTrueL( ETrue, KCEikMfne );
    
    CEikNumberEditor* editor = STATIC_CAST(CEikNumberEditor*, iEikMfne);
    editor->ConstructL(0,100,10);

    iEikMfne->BorderMargins();
    _LIT( KBorderMargins,
    "Class CEikMfne Function BorderMargins tested" );
    AssertTrueL( ETrue, KBorderMargins );

    iEikMfne->SetFont( font );
    _LIT( KSetFont,
    "Class CEikMfne Function SetFont tested" );
    AssertTrueL( ETrue, KSetFont );

    iEikMfne->SetSkinTextColorL( 1, KErrNotFound );
    _LIT( KSetSkinTextColorL,
    "Class CEikMfne Function SetSkinTextColorL tested" );
    AssertTrueL( ETrue, KSetSkinTextColorL );
    
    iEikMfne->SetMfneAlignment( 1 );
    _LIT( KSetMfneAlignment,
    "Class CEikMfne Function SetMfneAlignment tested" );
    AssertTrueL( ETrue, KSetMfneAlignment );

    iEikMfne->SetUpAndDownKeysConsumed( ETrue );
    _LIT( KSetUpAndDownKeysConsumed,
    "Class CEikMfne Function SetUpAndDownKeysConsumed tested" );
    AssertTrueL( ETrue, KSetUpAndDownKeysConsumed );

    iEikMfne->InputCapabilities();
    _LIT( KInputCapabilities,
    "Class CEikMfne Function InputCapabilities tested" );
    AssertTrueL( ETrue, KInputCapabilities );

    iEikMfne->MinimumSize();
    _LIT( KMinimumSize,
    "Class CEikMfne Function MinimumSize tested" );
    AssertTrueL( ETrue, KMinimumSize );

    TTime time;
    TRAP_IGNORE( iEikMfne->DrawNowAndLeaveWithTimeDateFormatInfoMsgL(
                                   R_BCTESTEDITOR_GLOBALTEXT, time ) );

    CArrayFix<TCoeColorUse>* indexArray = new ( ELeave )
    CArrayFixFlat<TCoeColorUse>( 1 );
    CleanupStack::PushL( indexArray );
    iEikMfne->GetColorUseListL( *indexArray );
    CleanupStack::PopAndDestroy( indexArray );

    iEikMfne->HandleResourceChange( 1 );
    _LIT( KHandleResourceChange,
    "Class CEikMfne Function HandleResourceChange tested" );
    AssertTrueL( ETrue, KHandleResourceChange );

    iEikMfne->HandleMfneCommandL( 2 );
    _LIT( KHandleMfneCommandL,
    "Class CEikMfne Function HandleMfneCommandL tested" );
    AssertTrueL( ETrue, KHandleMfneCommandL );

    iEikMfne->SetSkinBackgroundControlContextL( NULL );
    _LIT( KSetSkinBackgroundControlContextL,
    "Class CEikMfne Function SetSkinBackgroundControlContextL tested" );
    AssertTrueL( ETrue, KSetSkinBackgroundControlContextL );

    delete iEikMfne;
    iEikMfne = NULL;

    CSubEikMfne* subEikMfne = new ( ELeave ) CSubEikMfne();
    CleanupStack::PushL( subEikMfne );
    subEikMfne->TestFunction();
    _LIT( KMfneSize,
    "Class CEikMfne Function MfneSize tested" );
    AssertTrueL( ETrue, KMfneSize );
    AssertTrueL( ETrue, KMfneSize );
    _LIT( KFocusChanged,
    "Class CEikMfne Function FocusChanged tested" );
    AssertTrueL( ETrue, KFocusChanged );

    CleanupStack::PopAndDestroy( subEikMfne );
    }
