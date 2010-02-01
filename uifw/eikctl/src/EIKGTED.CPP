/*
* Copyright (c) 1997-1999 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:
*
*/


#include <txtglobl.h>
#include <txtrich.h>
#include <fldinfo.h>
#include <prnsetup.h>
#include <frmprint.h>
#include <frmpage.h>
#include <badesca.h>
#include <barsread.h>
#include <eikgted.h>
#include <eikenv.h>
#ifdef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <uikon/eikenvinterface.h>
#endif
#include <eikbutb.h>
#include <eikcmbut.h>
#include <eiklbbut.h>
#include <eikon.hrh>
#include <eikcoctl.rsg>
#include <eikctl.rsg>
#include "EIKDLGTB.H"
#include <eikpanic.h>
#include <aknedformaccessor.h>

#include <AknTasHook.h>
EXPORT_C CEikGlobalTextEditor::CEikGlobalTextEditor()
	{
	AKNTASHOOK_ADD( this, "CEikGlobalTextEditor" );
	}

EXPORT_C CEikGlobalTextEditor::CEikGlobalTextEditor(const TGulBorder& aBorder)
	: CEikEdwin(aBorder)
	{
	AKNTASHOOK_ADD( this, "CEikGlobalTextEditor" );
	}

EXPORT_C CEikGlobalTextEditor::~CEikGlobalTextEditor()
	{
	AKNTASHOOK_REMOVE();
	delete iFindList;
	delete iReplaceList;
	delete iFindModel;
	if (~iEdwinUserFlags&EKeepDocument)
		{
		delete iParaFormatLayer;
		delete iCharFormatLayer;
		}
	delete iLineCursor;
	}

EXPORT_C void CEikGlobalTextEditor::ConstructL(const CCoeControl* aParent,TInt aNumberOfLines,TInt aTextLimit,
											   TInt aEdwinFlags,TInt aFontControlFalgs,
											   TInt aFontNameFlags)
	{
	iNumberOfLines=aNumberOfLines;
	iTextLimit=aTextLimit;
	iEdwinUserFlags|=aEdwinFlags;
	iFontControlFlags=aFontControlFalgs;
	iFontNameFlags=aFontNameFlags;
	if (aParent)
		SetContainerWindowL(*aParent);
	else
		SetContainerWindowL();
	BaseConstructL();
	}

EXPORT_C void CEikGlobalTextEditor::BaseConstructL()
	{
	if (iEdwinUserFlags&EEikEdwinAlternativeWrapping)
		SetAvkonWrap(EFalse); 
	else
		SetAvkonWrap(ETrue); // added to make changes in Edwin spacing work. JIn
	if (iEdwinUserFlags&ELineCursor)
		SetLineCursorBitmapL(NULL);
	if (iEdwinUserFlags&EUserSuppliedText)
	    return;
	iParaFormatLayer=CEikonEnv::NewDefaultParaFormatLayerL();
	iCharFormatLayer=CEikonEnv::NewDefaultCharFormatLayerL();
	TCharFormat charFormat;
	TCharFormatMask charMask;
	iCharFormatLayer->Sense(charFormat,charMask);
	charFormat.iFontSpec.iTypeface.SetAttributes(FontUtils::TypefaceAttributes(*(iEikonEnv->ScreenDevice()),charFormat.iFontSpec.iTypeface.iName));
	charMask.SetAttrib(EAttFontTypeface);
	iCharFormatLayer->SetL(charFormat,charMask);
	CreateTextAndLayoutL(iParaFormatLayer,iCharFormatLayer);
	EnableCcpuSupportL(ETrue);
	if (AknEdwinFlags()&EAknEditorFlagEnableScrollBars)
		{
// Added to have scroll-bars in edwins. JIn
		CEikScrollBarFrame* scrollFrame = CreatePreAllocatedScrollBarFrameL();
		scrollFrame->SetScrollBarVisibilityL(CEikScrollBarFrame::EOff, CEikScrollBarFrame::EAuto);
		scrollFrame->SetScrollBarFrameFlags(CEikScrollBarFrame::EVVisible);
		}
	CheckEdwinExtensionL();
	__ASSERT_DEBUG(EdwinExtension()->FormAccessor(), Panic(EEikPanicNullPointer));
	// overwrites value set in CEikEdwin constructor
	EdwinExtension()->FormAccessor()->SetEdwin(this);
	}

EXPORT_C void CEikGlobalTextEditor::ConstructFromResourceL(TResourceReader& aReader)
	{
	iSize.iWidth=aReader.ReadInt16();
	TInt height=aReader.ReadInt16();
	iNumberOfLines=aReader.ReadInt16();
	iTextLimit=aReader.ReadInt16();
	iEdwinUserFlags|=aReader.ReadInt32();
	(TInt&)iFontControlFlags=aReader.ReadInt16();
	(TInt&)iFontNameFlags=aReader.ReadInt16();
	ReadAknResourceL(aReader);
	BaseConstructL();
	iSize.iHeight=height;
	}

EXPORT_C void CEikGlobalTextEditor::SetButtonGroup(CCoeControl* /*aButtonGroup*/)
	{
	// This method is hollowed out as this feature is not supported in Avkon
	}

EXPORT_C void CEikGlobalTextEditor::SetLineCursorBitmapL(CFbsBitmap* /*aBitmap*/)
	{
	// This method is hollowed out as this feature is not supported in Avkon
	}

EXPORT_C TInt CEikGlobalTextEditor::LineCursorWidth() const
	{
	return iLineCursorWidth;
	}

EXPORT_C void CEikGlobalTextEditor::ActivateL()
	{
	if (!iTextView)
		CreateTextViewL();
	iTextView->SetLineCursorBitmap(iLineCursor);
	CEikEdwin::ActivateL();
	UpdateButtonGroup();
	}

EXPORT_C TBool CEikGlobalTextEditor::DoFindL()
	{
	if (iFindModel->iText.Length()>TextLength())
		{
		DisplayFindTextNotFound(iFindModel->iText);
		return EFalse;
		}
	TBool found=EFalse;
	TRAPD(ret,found=FindL(&iFindModel->iText,iFindModel->iFlags));
	if (ret!=KErrNone)
		User::Leave(ret);
	else
		{
		if (!found)
			{
			DisplayFindTextNotFound(iFindModel->iText);
			return EFalse;
			}
		}
	return ETrue;
	}

void CEikGlobalTextEditor::CheckDocumentNotEmptyL()
	{
	// For Avkon, the feature is not supported, so no localized text available
	if (!TextLength())
		iEikonEnv->LeaveWithInfoMsg(0); 
	}

void CEikGlobalTextEditor::CreateFindModelL()
	{
	if (!iFindModel)
		{
		iFindModel=new(ELeave) SEdwinFindModel;
		iFindModel->iFlags=0;
		}
	if (!iFindList)
		iFindList=new(ELeave) CDesCArrayFlat(5);
	if (!iReplaceList)
		iReplaceList=new(ELeave) CDesCArrayFlat(5);
	}

EXPORT_C void CEikGlobalTextEditor::RunFindDialogL()
	{
	CreateFindModelL();
	CheckDocumentNotEmptyL();
	GetTextForFindL();
	iFindModel->iFlags&=(~EFindAgain);
	ASSERT(iEikonEnv->CDlgDialogFactory());
	if(iEikonEnv->CDlgDialogFactory()->RunEdwinFindDlgLD(iFindModel, iFindList))
		DoFindL();
	}

EXPORT_C void CEikGlobalTextEditor::RunFindAgainDialogL()
	{
	CheckDocumentNotEmptyL();
	CreateFindModelL();
	if (!iFindModel->iText.Length())
		GetTextForFindL();
	if (!iFindModel->iText.Length())
		RunFindDialogL();
	else
		{
		iFindModel->iFlags|=EFindAgain;
		DoFindL();
		}
	}

void CEikGlobalTextEditor::GetTextForFindL()
	{
	TInt pos=0;
	TBuf<EEikEdwinFindStringMaxLen>* findText=new(ELeave) TBuf<EEikEdwinFindStringMaxLen>;
	CleanupStack::PushL(findText);
	GetFindText(findText);
	TInt retcode=iFindList->Find(*findText,pos);
	if (retcode)
		iFindList->InsertL(0,*findText);
	iFindModel->iText=*findText;
	CleanupStack::PopAndDestroy();
	}

EXPORT_C void CEikGlobalTextEditor::InitFindL(SEdwinFindModel*& aModel,CDesCArray*& aFindList,CDesCArray*& aReplaceList)
	{
	CreateFindModelL();
	CheckDocumentNotEmptyL();
	GetTextForFindL();
	aModel=iFindModel;
	aFindList=iFindList;
	aReplaceList=iReplaceList;
	}

EXPORT_C void CEikGlobalTextEditor::RunReplaceDialogL()
	{
	CreateFindModelL();
	CheckDocumentNotEmptyL();
	GetTextForFindL();
	MEikCDlgDialogFactory* dialogFactory = iEikonEnv->CDlgDialogFactory();
	ASSERT(dialogFactory);
	if(dialogFactory->RunEdwinReplaceDlgLD(iFindModel, iFindList, iReplaceList))
		{
		if (!DoFindL())
			return;
		if(!(dialogFactory->RunEdwinReplaceOptionDlgLD(this,iFindModel)))
			{
			if (SelectionLength())
				ClearSelectionL();  
			return;
			}
		if (iFindModel->iReplaceOption==EReplaceAll)
			{ // display busy message
			iEikonEnv->BusyMsgL(R_EIK_TBUF_REPLACING_BUSYMSG,500000); // 0.5 seconds
			DrawNow();
			ForceScrollBarUpdateL();
			ReplaceAllL(iFindModel);
			iEikonEnv->BusyMsgCancel();
			}
		iEikonEnv->InfoMsg(R_EIK_TBUF_REPLACE_FINISHED);
	 	if (SelectionLength())
			ClearSelectionL();  
		}
	}

EXPORT_C TKeyResponse CEikGlobalTextEditor::OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)
	{
	if (iEdwinUserFlags&EDisplayOnly)
		return EKeyWasConsumed;
	if (!(aKeyEvent.iModifiers&EModifierCtrl) || aKeyEvent.iModifiers&EModifierPureKeycode)
		return CEikEdwin::OfferKeyEventL(aKeyEvent,aType);
	TBool formatChanged=ETrue;
	TFontStyleFlags fontFlag=EStandard;
	TBuf<24> buf;
	if (aKeyEvent.iModifiers&EModifierShift)
			iCoeEnv->ReadResource(buf,R_EIK_EDWIN_SHIFT_CTRL_HOTKEYS);
	else
		iCoeEnv->ReadResource(buf,R_EIK_EDWIN_CTRL_HOTKEYS);
	const TInt ret=buf.Locate(TChar(aKeyEvent.iCode+'a'-1));
	switch (ret)
		{
	case EHotKeyBold:
		CheckNotReadOnlyL();
		fontFlag=EBold;
		break;
	case EHotKeyItalic:
		CheckNotReadOnlyL();
		fontFlag=EItalic;
		break;
	case EHotKeyUnderline:
		CheckNotReadOnlyL();
		fontFlag=EUnderline;
		break;
	case EHotKeyFont:
		{
		CheckNotReadOnlyL();
		RunFontDialogL(iFontNameFlags,iGraphicsDevice, iFontControlFlags);
		}
		break;
	default:
		formatChanged=EFalse;
		}
	if (formatChanged)
		{
		if (fontFlag!=EStandard && !(aKeyEvent.iModifiers&EModifierShift))
			BoldItalicUnderlineEventL(fontFlag);
		if (iButGroup)
			UpdateButtonGroup();
		return EKeyWasConsumed;
		}
	return CEikEdwin::OfferKeyEventL(aKeyEvent,aType);
	}

EXPORT_C void CEikGlobalTextEditor::UpdateButtonGroup()
	{
	if (!iButGroup)
		return;
	TCharFormat charFormat;
	TCharFormatMask mask;
	const TCursorSelection selection=Selection();
	GlobalText()->GetCharFormat(charFormat,mask,selection.LowerPos(),selection.Length());
	CEikButtonBase* but=STATIC_CAST(CEikLabeledButton*,iButGroup->ControlById(EEikCidFontBoldBut))->Button();
	if (but)
		{
		CEikButtonBase::TState state=((charFormat.iFontSpec.iFontStyle.StrokeWeight()==EStrokeWeightBold)?
			CEikButtonBase::ESet : CEikButtonBase::EClear);
		if (but->State()!=state)
			{
			but->SetState(state);
			but->DrawNow();
			}
		}
	but=STATIC_CAST(CEikLabeledButton*,iButGroup->ControlById(EEikCidFontItalicBut))->Button();
	if (but)
		{
		CEikButtonBase::TState state=((charFormat.iFontSpec.iFontStyle.Posture()==EPostureItalic)?
			CEikButtonBase::ESet : CEikButtonBase::EClear);
		if (but->State()!=state)
			{
			but->SetState(state);
			but->DrawNow();
			}
		}
	but=STATIC_CAST(CEikLabeledButton*,iButGroup->ControlById(EEikCidFontUnderlineBut))->Button();
	if (but)
		{
		CEikButtonBase::TState state=((charFormat.iFontPresentation.iUnderline==EUnderlineOn)?
			CEikButtonBase::ESet : CEikButtonBase::EClear);
		if (but->State()!=state)
			{
			but->SetState(state);
			but->DrawNow();
			}
		}
	}

EXPORT_C void CEikGlobalTextEditor::SetGraphicsDevice(CGraphicsDevice* aGraphicsDevice)
	{
	iGraphicsDevice=aGraphicsDevice;
	}

EXPORT_C TBool CEikGlobalTextEditor::RunFontDialogL(TInt aFontDialogFlags,CGraphicsDevice* aGraphicsDevice, 
													TInt aFontControlFlags)
	{
	TCursorSelection selection=Selection();
	TInt selectionLength=selection.Length();
	//get backgroundcolor
	CParaFormat paraFormat;
	TParaFormatMask variesMask;
	GlobalText()->GetParaFormatL(&paraFormat,variesMask,selection.LowerPos(),selectionLength);

	TCharFormat charFormat;
	TCharFormatMask charMask;
	TCharFormatMask charUndeterminedMask;
	TBuf<KTextSelectionMaxLen> buf;
	GlobalText()->GetCharFormat(charFormat,charUndeterminedMask,selection.LowerPos(),selectionLength);
	if (selectionLength>KTextSelectionMaxLen)
		selectionLength=KTextSelectionMaxLen;
	GlobalText()->Extract(buf,selection.LowerPos(),selectionLength);
	TInt offset=buf.Locate(CEditableText::EParagraphDelimiter); 
	if (offset!=KErrNotFound)   // chop off buf if paragraph end
		buf.SetLength(offset);
	TCharFormat originalFormat=charFormat;
	TCharFormatMask oldcharMask;
	ASSERT(iEikonEnv->CDlgDialogFactory());
	TBool dlg = iEikonEnv->CDlgDialogFactory()->RunFontDlgLD(charFormat,charMask,charUndeterminedMask,buf,
													aFontDialogFlags,aGraphicsDevice,aFontControlFlags,
													paraFormat.iFillColor);
	if(!dlg || (originalFormat.IsEqual(charFormat) && charMask==oldcharMask))
		return(EFalse);

	ApplyCharFormatL(charFormat,charMask);
	UpdateButtonGroup();
	return(ETrue);
	}

EXPORT_C void CEikGlobalTextEditor::ApplyCharFormatL(TCharFormat& aCharFormat,TCharFormatMask& aCharMask)
	{
	const TCursorSelection selection=Selection();
	GlobalText()->ApplyCharFormatL(aCharFormat,aCharMask,selection.LowerPos(),selection.Length());
	if (iEdwinInternalFlags&ERichText)
		{
		if (selection.Length()==0)
			iTextView->MatchCursorHeightL(aCharFormat.iFontSpec);
		else
			iTextView->HandleRangeFormatChangeL(selection,EFalse);
		}
	else
		{
		TViewYPosQualifier yPosQualifier;
		yPosQualifier.SetMakeLineFullyVisible();
		iTextView->HandleGlobalChangeL(yPosQualifier);
		}
	UpdateScrollBarsL();
	ReportEdwinEventL(MEikEdwinObserver::EEventFormatChanged);
	}

EXPORT_C void CEikGlobalTextEditor::ApplyParaFormatL(CParaFormat* aParaFormat,TParaFormatMask& aParaMask)
	{
	TCursorSelection selection=Selection();
	GlobalText()->ApplyParaFormatL(aParaFormat,aParaMask,selection.LowerPos(),selection.Length());
	if (iEdwinInternalFlags&ERichText)
		iTextView->HandleRangeFormatChangeL(selection,ETrue);
	else
		{
		TViewYPosQualifier yPosQualifier;
		yPosQualifier.SetMakeLineFullyVisible();
		iTextView->HandleGlobalChangeL(yPosQualifier); // !! NotifyForwardChangedL() may be better for rich text case
		}
	UpdateScrollBarsL();
	ReportEdwinEventL(MEikEdwinObserver::EEventFormatChanged);
	}


EXPORT_C void CEikGlobalTextEditor::RunParaDialogsL(TInt aCommand)
	{
	CParaFormat* paraFormat=CParaFormat::NewLC();
	TParaFormatMask paraMask;
	TParaFormatMask paraUndeterminedMask;
	TCursorSelection selection=Selection();
	TInt selectionLength=selection.Length();
	GlobalText()->GetParaFormatL(paraFormat,paraUndeterminedMask,selection.LowerPos(),selectionLength);
	MEikCDlgDialogFactory* dialogFactory = iEikonEnv->CDlgDialogFactory();
	ASSERT(dialogFactory);
	TBool dlg;
	switch (aCommand)
		{
	case EEikCmdParaAlign:
		dlg = dialogFactory->RunAlignDlgLD(paraFormat,paraMask, paraUndeterminedMask);
		break;
	case EEikCmdParaSpacing:
		dlg = dialogFactory->RunSpaceDlgLD(paraFormat,paraMask, paraUndeterminedMask);
		break;
	case EEikCmdParaBorder:
		{
		dlg = dialogFactory->RunBorderDlgLD(paraFormat,paraMask, paraUndeterminedMask);
		break;
		}
	default:
		CleanupStack::PopAndDestroy();
		return;
		}
	if(dlg)
		ApplyParaFormatL(paraFormat,paraMask);
	CleanupStack::PopAndDestroy();
	}

EXPORT_C void CEikGlobalTextEditor::RunTabsDialogL(TInt aPageWidth)
	{
	CParaFormat* paraFormat=CParaFormat::NewLC();
	TParaFormatMask paraMask;
	TParaFormatMask paraUndeterminedMask;
	TCursorSelection selection=Selection();
	TInt selectionLength=selection.Length();
	GlobalText()->GetParaFormatL(paraFormat,paraUndeterminedMask,selection.LowerPos(),selectionLength);
	ASSERT(iEikonEnv->CDlgDialogFactory());
	if(iEikonEnv->CDlgDialogFactory()->RunTabsDlgLD(paraFormat,paraMask, paraUndeterminedMask, aPageWidth))
		ApplyParaFormatL(paraFormat,paraMask);
	CleanupStack::PopAndDestroy();
	}

EXPORT_C void CEikGlobalTextEditor::RunIndentsDialogL(TInt aPageWidth)
	{
	CParaFormat* paraFormat=CParaFormat::NewLC();
	TParaFormatMask paraMask;
	TParaFormatMask paraUndeterminedMask;
	TCursorSelection selection=Selection();
	TInt selectionLength=selection.Length();
	GlobalText()->GetParaFormatL(paraFormat,paraUndeterminedMask,selection.LowerPos(),selectionLength);
	ASSERT(iEikonEnv->CDlgDialogFactory());
	if(iEikonEnv->CDlgDialogFactory()->RunIndentDlgLD(paraFormat,paraMask, paraUndeterminedMask, aPageWidth))
		ApplyParaFormatL(paraFormat,paraMask);
	CleanupStack::PopAndDestroy();
	}

EXPORT_C void CEikGlobalTextEditor::BoldItalicUnderlineEventL(TInt aFontFlag)
	{
	TCharFormat charFormat;
	TCharFormatMask applyMask;
	const TCursorSelection selection=Selection();
	const TInt selLength=selection.Length();
	TInt startPos,wordLength;
	GetWordInfo(selection.iAnchorPos,startPos,wordLength);
	if (selLength)
		GlobalText()->GetCharFormat(charFormat,applyMask,selection.LowerPos(),selLength);
	else if (selection.iCursorPos==startPos+wordLength)
		GlobalText()->GetCharFormat(charFormat,applyMask,startPos+wordLength,0);
	else
		GlobalText()->GetCharFormat(charFormat,applyMask,selection.iCursorPos,0);
	applyMask.ClearAll();
	//
	switch (aFontFlag)
		{
	case EBold:
		charFormat.iFontSpec.iFontStyle.SetStrokeWeight(charFormat.iFontSpec.iFontStyle.StrokeWeight()? EStrokeWeightNormal : EStrokeWeightBold);
		applyMask.SetAttrib(EAttFontStrokeWeight);
		break;
	case EItalic:
		charFormat.iFontSpec.iFontStyle.SetPosture(charFormat.iFontSpec.iFontStyle.Posture()? EPostureUpright : EPostureItalic);
		applyMask.SetAttrib(EAttFontPosture);
		break;
	case EUnderline:
		charFormat.iFontPresentation.iUnderline=(charFormat.iFontPresentation.iUnderline)?EUnderlineOff : EUnderlineOn;
		applyMask.SetAttrib(EAttFontUnderline);
		break;
	default:
		return;
		}
	if (selLength)
		ApplyCharFormatL(charFormat,applyMask);
	else
		{
		if (selection.iCursorPos==startPos+wordLength && iEdwinInternalFlags&ERichText)
			GlobalText()->ApplyCharFormatL(charFormat,applyMask,startPos+wordLength,0);
		else
			{
			const TInt length=(selection.iCursorPos==startPos? 0 : wordLength);
			GlobalText()->ApplyCharFormatL(charFormat,applyMask,startPos,length);
			if (iEdwinInternalFlags&ERichText)
				iTextView->HandleRangeFormatChangeL(TCursorSelection(startPos,startPos+wordLength),EFalse);
			else
				{
				TViewYPosQualifier yPosQualifier;
				yPosQualifier.SetMakeLineFullyVisible();
				iTextView->HandleGlobalChangeL(yPosQualifier);
				}
			UpdateScrollBarsL();
			}
		ReportEdwinEventL(MEikEdwinObserver::EEventFormatChanged);
		}
	UpdateButtonGroup();
	}

EXPORT_C CGlobalText* CEikGlobalTextEditor::GlobalText() const
	{
	return((CGlobalText*)iText);
	}

EXPORT_C TBool CEikGlobalTextEditor::RunPaginateDialogL(CPrintSetup* aPrintSetup,CArrayFix<TInt>* aCharsPerPage)
	{
	ASSERT(iEikonEnv->PrintDialogFactory());
	return (iEikonEnv->PrintDialogFactory()->RunPaginateDlgLD(this, aPrintSetup, aCharsPerPage));
	}

/**
 * Writes the internal state of the control and its components to aStream.
 * Does nothing in release mode.
 * Designed to be overidden and base called by subclasses.
 *
 * @internal
 * @since App-Framework_6.1
 */
#ifndef _DEBUG
EXPORT_C void CEikGlobalTextEditor::WriteInternalStateL(RWriteStream&) const
	{}
#else
EXPORT_C void CEikGlobalTextEditor::WriteInternalStateL(RWriteStream& aWriteStream) const
	{
	CEikEdwin::WriteInternalStateL(aWriteStream);
	}
#endif

EXPORT_C void CEikGlobalTextEditor::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CEikEdwin::HandlePointerEventL(aPointerEvent); 
    }

EXPORT_C void* CEikGlobalTextEditor::ExtensionInterface( TUid /*aInterface*/ )
    {
    return NULL;
    }

EXPORT_C void CEikGlobalTextEditor::Reserved_2()
	{}

EXPORT_C void CEikGlobalTextEditor::Reserved_3()
	{}
