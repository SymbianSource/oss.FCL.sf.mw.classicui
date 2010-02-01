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


#include <gdi.h>
#include <badesca.h>        // CDesArray
#include <eiklbed.h>		// class CEikListBoxTextEditor header file
#include <uikon.hrh>
#include <gulutil.h>
#include <eikedwin.h>
#include <eikenv.h>
#include <eikappui.h>
#include <txtglobl.h>		// CGlobalText
#include <txtfmlyr.h>		// CParaFormatLayer, CCharFormatLayer
#include <eikcoctl.rsg>
#include <AknTasHook.h>
#include "LAFLBED.H" 
#include "akntrace.h"
enum TTUiklbedPanic
    {
    ETUiklbedPanicEndMarkMissing,
    ETUiklbedPanicEmptyField,
    ETUiklbedPanicLongInput,
    };

LOCAL_C void Panic(TTUiklbedPanic aPanic)
    {
	_LIT(KTUiklbed,"TUiklbed");
    User::Panic(KTUiklbed, aPanic);
    }

//
// MEikListBoxEditor
//

EXPORT_C void MEikListBoxEditor::MEikListBoxEditor_Reserved_1()
	{
	}

//
// CEikListBoxTextEditor
//

EXPORT_C CEikListBoxTextEditor::CEikListBoxTextEditor( MListBoxModel* aModel )
	: iModel(aModel), iEditor(NULL), iFont(NULL), iItemPos(0), iItemLen(0)
	{
	_AKNTRACE_FUNC_ENTER;
	iFont = CONST_CAST(CFont*,CCoeEnv::Static()->NormalFont());
	AKNTASHOOK_ADD( this, "CEikListBoxTextEditor" );
	_AKNTRACE_FUNC_EXIT;
	}

EXPORT_C CEikListBoxTextEditor::~CEikListBoxTextEditor()
	{ // need to remove from stack incase listbox was destroyed without calling StopEditingL()
	  // safe to call RemoveFromStack even if we're not stacked
	  // code here is same as in StopEditingL(), but we can't call
	  // a L function from ~ even if it can't leave
	_AKNTRACE_FUNC_ENTER;
	AKNTASHOOK_REMOVE();
	iEikonEnv->EikAppUi()->RemoveFromStack(this);
	if(iEditor)
		iEditor->SetFocus(EFalse);      // BUG? - cursor remains on screen without this
	delete iEditor;
	delete iParaFormatLayer;
	delete iCharFormatLayer;
	_AKNTRACE_FUNC_EXIT;
	}

EXPORT_C void CEikListBoxTextEditor::Release()
	{
	delete this;
	}

EXPORT_C void CEikListBoxTextEditor::SetFont(const CFont* aFont)
	{
	if (aFont!=NULL)
		iFont = CONST_CAST(CFont*,aFont);
	}

void CEikListBoxTextEditor::UseFontL( CEikEdwin& aEditor, const CFont& aFont )
	{
	_AKNTRACE_FUNC_ENTER;
	CGlobalText* globalText;

    TCharFormatMask defaultCharFormatMask;
	defaultCharFormatMask.SetAttrib(EAttFontTypeface);
	defaultCharFormatMask.SetAttrib(EAttFontHeight);
	TFontSpec fontspec = aFont.FontSpecInTwips();
    TCharFormat defaultCharFormat( fontspec.iTypeface.iName, fontspec.iHeight );

	iParaFormatLayer=CParaFormatLayer::NewL();
	iCharFormatLayer=CCharFormatLayer::NewL(defaultCharFormat,defaultCharFormatMask);
	globalText=CGlobalText::NewL(iParaFormatLayer,iCharFormatLayer,CEditableText::ESegmentedStorage,5);
	CleanupStack::PushL(globalText);

	TCharFormat charFormat;
	TCharFormatMask charMask;
	iCharFormatLayer->Sense(charFormat,charMask);
	if ( fontspec.iFontStyle.Posture()==EPostureItalic )
		{
		charMask.SetAttrib(EAttFontPosture);
		charFormat.iFontSpec.iFontStyle.SetPosture(EPostureItalic);
		}
	if ( fontspec.iFontStyle.StrokeWeight()==EStrokeWeightBold )
		{
		charMask.SetAttrib(EAttFontStrokeWeight );
		charFormat.iFontSpec.iFontStyle.SetStrokeWeight(EStrokeWeightBold);
		}
	iCharFormatLayer->SetL(charFormat,charMask);

	CPlainText* old=aEditor.Text();
	CleanupStack::Pop(); // globalText
	CleanupStack::PushL(old);	// old is pushed because we're using EUseText in the subsequent call
	aEditor.SetDocumentContentL(*globalText,CEikEdwin::EUseText);
	CleanupStack::PopAndDestroy();	// old
	_AKNTRACE_FUNC_EXIT;
	}

EXPORT_C CEikEdwin* CEikListBoxTextEditor::Editor()
	{
	return iEditor;
	}

EXPORT_C MListBoxModel* CEikListBoxTextEditor::ListBoxModel()
	{
	return iModel;
	}

EXPORT_C void CEikListBoxTextEditor::StartEditingL(const CCoeControl& aContainer, const TRect& aRect, TInt aItemIndex, TInt aMaxLength )
	{
	_AKNTRACE_FUNC_ENTER;
	if (Editor())
	    {
	    _AKNTRACE_FUNC_EXIT;
	    return;     // quit if editing is currently on
	    }		

	iItemIndex=aItemIndex;
	TRect rect=aRect;
    TPtrC itemtext=EditableItemText(&rect);	// get text (also partly editable)

	// create edwin (make it into own window, no wrapping)
	TGulBorder border;
	LafListBoxTextEditor::GetDefaultBorder(border);
	CEikEdwin* editor=new(ELeave) CEikEdwin(border);
	CleanupStack::PushL(editor);
	TInt edwinFlags=EEikEdwinOwnsWindow | EEikEdwinNoWrap | EEikEdwinNoLineOrParaBreaks | EEikEdwinNoCustomDraw;
	editor->CEikEdwin::ConstructL(edwinFlags,0,(iItemLen?iItemLen:aMaxLength),1);
	editor->SetContainerWindowL(aContainer);
	editor->SetRect(rect);
	UseFontL(*editor,*iFont); // need this to change CEikEdwin font...
	editor->SetTextL(&itemtext);
	editor->SetCursorPosL(editor->TextLength(),ETrue);
	editor->SetFocus(ETrue);
	editor->ActivateL();
	iEikonEnv->EikAppUi()->AddToStackL(this,ECoeStackPriorityDialog,ECoeStackFlagRefusesFocus);
	CleanupStack::Pop(); // editor
	iEditor=editor;
	iCoeEnv->InputCapabilitiesChanged();
	_AKNTRACE_FUNC_EXIT;
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
EXPORT_C void CEikListBoxTextEditor::WriteInternalStateL(RWriteStream&) const
	{}
#else
EXPORT_C void CEikListBoxTextEditor::WriteInternalStateL(RWriteStream& aWriteStream) const
	{
	_LIT(KEikLitLbxEdCtlStart,"<CEikListBoxTextEditor>");
	_LIT(KEikLitLbxEdCtlEnd,"<\\CEikListBoxTextEditor>");
	_LIT(KEikLitLbxEdObs,"<iEditorObserver>");
	_LIT(KEikLitLbxEdObsEnd,"<\\iEditorObserver>");
	_LIT(KEikLitLbxEdMdl,"<iModel>");
	_LIT(KEikLitLbxEdMdlEnd,"<\\iModel>");
	_LIT(KEikLitLbxEdEdr,"<iEditor>");
	_LIT(KEikLitLbxEdEdrEnd,"<\\iEditor>");
	_LIT(KEikLitLbxEdIndx,"<iItemIndex>");
	_LIT(KEikLitLbxEdIndxEnd,"<\\iItemIndex>");
	_LIT(KEikLitLbxEdFont,"<iFont>");
	_LIT(KEikLitLbxEdFontEnd,"<\\iFont>");
	_LIT(KEikLitLbxEdItemPos,"<iItemPos>");
	_LIT(KEikLitLbxEdItemPosEnd,"<\\iItemPos>");
	_LIT(KEikLitLbxEdItemLen,"<iItemLen>");
	_LIT(KEikLitLbxEdItemLenEnd,"<\\iItemLen>");
	_LIT(KEikLitLbxEdParaLay,"<iParaFormatLayer>");
	_LIT(KEikLitLbxEdParaLayEnd,"<\\iParaFormatLayer>");
	_LIT(KEikLitLbxEdCharLay,"<iCharFormatLayer>");
	_LIT(KEikLitLbxEdCharLayEnd,"<\\iCharFormatLayer>");
	
	aWriteStream << KEikLitLbxEdCtlStart;
	aWriteStream << KEikLitLbxEdObs;
	aWriteStream.WriteInt32L((TInt)iEditorObserver);
	aWriteStream << KEikLitLbxEdObsEnd;
	aWriteStream << KEikLitLbxEdMdl;
	aWriteStream.WriteInt32L((TInt)iModel);
	aWriteStream << KEikLitLbxEdMdlEnd;
	aWriteStream << KEikLitLbxEdEdr;
	iEditor->WriteInternalStateL(aWriteStream); // won't be done as a component
	aWriteStream << KEikLitLbxEdEdrEnd;
	aWriteStream << KEikLitLbxEdIndx;
	aWriteStream.WriteInt32L(iItemIndex);
	aWriteStream << KEikLitLbxEdIndxEnd;
	aWriteStream << KEikLitLbxEdFont;
	const TFontSpec& spec=iFont->FontSpecInTwips();
	aWriteStream << spec;
	aWriteStream << KEikLitLbxEdFontEnd;
	aWriteStream << KEikLitLbxEdItemPos;
	aWriteStream.WriteInt32L(iItemPos);
	aWriteStream << KEikLitLbxEdItemPosEnd;
	aWriteStream << KEikLitLbxEdItemLen;
	aWriteStream.WriteInt32L(iItemLen);
	aWriteStream << KEikLitLbxEdItemLenEnd;
	aWriteStream << KEikLitLbxEdParaLay;
	aWriteStream << *iParaFormatLayer;
	aWriteStream << KEikLitLbxEdParaLayEnd;
	aWriteStream << KEikLitLbxEdCharLay;
	aWriteStream << *iCharFormatLayer;
	aWriteStream << KEikLitLbxEdCharLayEnd;
	CCoeControl::WriteInternalStateL(aWriteStream);
	aWriteStream << KEikLitLbxEdCtlEnd;
	}
#endif

EXPORT_C TPtrC CEikListBoxTextEditor::ItemText()
	{
	return static_cast<MTextListBoxModel*>(ListBoxModel())->ItemText(ItemIndex());
	}

TPtrC CEikListBoxTextEditor::EditableItemText(TRect* aRect)
	{
	_AKNTRACE_FUNC_ENTER;
    TPtrC itemtext = ItemText();
	if (iItemPos==0)	// not yet set (and even if set, cannot be zero)
		{
		iItemPos = itemtext.Locate('\n');	// loacte partly editable item start
	    if (iItemPos != KErrNotFound)
			{
			iItemPos++;		// jump over mark character
			iItemLen = itemtext.Mid( iItemPos ).Locate('\n');	// locate string end
			if ( iItemLen == KErrNotFound )
				Panic( ETUiklbedPanicEndMarkMissing );
			if ( iItemLen==0 )
				Panic( ETUiklbedPanicEmptyField );
			TPtrC head = itemtext.Left( iItemPos );
			TPtrC body = itemtext.Mid( iItemPos, iItemLen );
			if ( aRect ) // adjust the rect if it is given
				{
				aRect->iTl.iX += iFont->TextWidthInPixels( head );
				aRect->iBr.iX = aRect->iTl.iX + iFont->TextWidthInPixels( body ) + 4;
				}
			_AKNTRACE_FUNC_EXIT;
			return body;
			}
		iItemPos = 0; // partly editable text not found
		}
	_AKNTRACE_FUNC_EXIT;
	return itemtext;
	}
	
EXPORT_C void CEikListBoxTextEditor::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CAknControl::HandlePointerEventL(aPointerEvent); 
    }	

EXPORT_C void* CEikListBoxTextEditor::ExtensionInterface( TUid /*aInterface*/ )
    {
    return NULL;
    }

/**
 * Stops editing the current item, if editing was taking place. Does not Leave.
 *
 * @since Uikon1.2
 */
EXPORT_C void CEikListBoxTextEditor::StopEditingL()
	{
	iEikonEnv->EikAppUi()->RemoveFromStack(this);
	if ( Editor() == NULL ) return; // quit if editing is not currently on
	iEditor->SetFocus(EFalse);      // BUG? - cursor remains on screen without this
	delete iEditor;
	iEditor=NULL;
	iCoeEnv->InputCapabilitiesChanged();
	}

EXPORT_C TBool CEikListBoxTextEditor::UpdateModelL()
	// virtual - needs to be rewritten if editing other than single column text list
	{
	_AKNTRACE_FUNC_ENTER;
	if (!Editor()) 
	    {
	    _AKNTRACE_FUNC_EXIT;
	    return EFalse;   // quit if editing is not currently on
	    }
	const MDesCArray* matchableTextArray=ListBoxModel()->MatchableTextArray();
	CDesCArray* textArray=(CDesCArray*)matchableTextArray;

    TPtrC itemtext = ItemText();
    if ( iItemPos ) // partly editable item?
        {
        HBufC* itemBuffer= HBufC::New(itemtext.Length());
        CleanupStack::PushL( itemBuffer );
        TPtr itemPointer = itemBuffer->Des();

        itemPointer.Append( itemtext.Left( iItemPos ) );

        HBufC* ptr=iEditor->GetTextInHBufL();
		TPtrC newText;
		if (ptr)
			{
			newText.Set(ptr->Des());
			}
        TInt addSpaces = iItemLen - newText.Length();
        for (TInt index=0; ((addSpaces>0) && (index<addSpaces)); index++)
			itemPointer.Append(_L(" "));

        itemPointer.Append( newText );
        itemPointer.Append( itemtext.Right( itemtext.Length()-iItemPos-iItemLen ) );

        delete ptr;
		textArray->InsertL( ItemIndex(), *itemBuffer );
        CleanupStack::PopAndDestroy(); // itemBuffer

        textArray->Delete( ItemIndex()+1 );
        }
    else // replace the whole list item
        {
		HBufC* newText = iEditor->GetTextInHBufL();
		if (!newText) return ETrue; // if user tries to insert an empty text...

		CleanupStack::PushL(newText);
		textArray->InsertL(ItemIndex(),*newText);
		CleanupStack::PopAndDestroy(); // newText

		textArray->Delete( ItemIndex() + 1 );
		}
    _AKNTRACE_FUNC_EXIT;
	return ETrue;
	}

EXPORT_C TInt CEikListBoxTextEditor::ItemIndex() const
	{
	return iItemIndex;
	}

EXPORT_C TKeyResponse CEikListBoxTextEditor::OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)
	{
	_AKNTRACE_FUNC_ENTER;
	_AKNTRACE( "aKeyEvent.iCode is %d", aKeyEvent.iCode );
	_AKNTRACE( "aKeyEvent.iScanCode is %d", aKeyEvent.iScanCode );
	_AKNTRACE( "aType is %d", aType );
	if (!Editor() || aType!=EEventKey)
		{
		_AKNTRACE_FUNC_EXIT;
		return EKeyWasNotConsumed;
		}

	if(iEditorObserver && iEditorObserver->HandleListBoxEditorEventL(this,aKeyEvent)==EKeyWasConsumed)
		{ // gives owning dialogs or listboxes a chance to intecept keys prior to or instead of passing to editor
		// eg the CCknFileSaveAsDialog needs to check if a file exists when the enter key is pressed
		// and prevent the Enter key being passed on to the editor, or intecept the up/down keys to
		// allow scrolling out of the editor
		_AKNTRACE_FUNC_EXIT;
		return EKeyWasConsumed;
		}
	const TInt code=aKeyEvent.iCode;
	if (aKeyEvent.iModifiers&(EModifierCtrl|EModifierShift)==(EModifierCtrl|EModifierShift))
		{
		TBuf<24> buf;
		iCoeEnv->ReadResource(buf,R_EIK_EDWIN_SHIFT_CTRL_HOTKEYS);
		const TInt pos=buf.Locate(TChar(code+'a'-1));
		if (pos==CEikEdwin::EHotKeyInsertChar)
			{
			_AKNTRACE_FUNC_EXIT;
			return EKeyWasConsumed;
			}
		}
	switch (code)
		{
		case EKeyEnter:     // stop editing and update data
		case EKeyOK:
			UpdateModelL();
			StopEditingL();
			break;
		case EKeyEscape:    // stop editing and don't update data
			StopEditingL();
			break;
		default:
			Editor()->OfferKeyEventL(aKeyEvent,aType);
		}
	_AKNTRACE_FUNC_EXIT;
	return EKeyWasConsumed;
	}

EXPORT_C void CEikListBoxTextEditor::SetListBoxEditorObserver(MListBoxEditorObserver* aObserver)
	{
	iEditorObserver=aObserver;
	}

EXPORT_C void CEikListBoxTextEditor::MEikListBoxEditor_Reserved_1()
	{
	}
