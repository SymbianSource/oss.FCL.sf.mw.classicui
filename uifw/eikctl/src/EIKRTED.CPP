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


#include <s32mem.h>
#include <s32file.h>
#include <txtrich.h>
#include <basched.h>
#include <apparc.h>
#include <apgdoor.h>
#include <apacln.h>
#include <clock.h>
#include <eikrted.h>
#include <eikenv.h>
#include <eikappui.h>
#include <eikembal.h>
#ifndef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <eikdoc.h>
#else
#include <eikdoc.h>
#include <uikon/eikdefaulticondefs.h>
#include <uikon/eikenvinterface.h>
#endif
#include <eikproc.h>
#include <eikon.hrh>
#include <eikpanic.h>
#include <eikedwin.pan>
#include <eikctl.rsg>
#include <eikcoctl.rsg>

#include <AknTasHook.h>
GLDEF_C void Panic(TEikEdwinPanic aPanic)
	{
	_LIT(KPanicCat,"EIKON-EDWIN");
	User::Panic(KPanicCat,aPanic);
	}

//
// class CEikParserManager
//

const TInt KParseScanDelay	=750000; // 0.75s
const TInt KNullStartPos	=-1;

NONSHARABLE_CLASS(CEikParserManager) : public CBase, public MEikEdwinObserver
	{
public:
	static CEikParserManager* NewL(CEikRichTextEditor& aEditor);
	~CEikParserManager();
public:
	void SetParserObserver(MEikRichTextEditorParserObserver* aObserver);
	void Start(TInt aStartPos,TInt aLength);
private:
	CEikParserManager(CEikRichTextEditor& aEditor);
	void ConstructL();
	void Start();
	void StartTimer();
	void Reset();
	static TInt ParseTextCallbackL(TAny* aSelf);
	void ParseTextL();
private: // from MEikEdwinObserver
	void HandleEdwinEventL(CEikEdwin* aEdwin,TEdwinEvent aEventType);
private:
	CPeriodic* iTimer;
	CEikRichTextEditor& iEditor;
	MEikRichTextEditorParserObserver* iParserObserver;
	TInt iStartPos; // start of changed area
	TInt iLength; // length of changed area
	MParser* iParser;
	TInt iTagStart; // start of tag cursor is over
	TInt iTagLength; // length of tag cursor is over
	TBool iStateChanged;
	TBool iParseWholeText;

public: // new methods
	void ForceFullParseL();

	};

CEikParserManager* CEikParserManager::NewL(CEikRichTextEditor& aEditor)
	{ // static
	CEikParserManager* self=new(ELeave) CEikParserManager(aEditor);
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop(); // self
	return self;
	}

CEikParserManager::~CEikParserManager()
	{
	if (iTimer)
		iTimer->Cancel();
	delete iTimer;
	}

void CEikParserManager::SetParserObserver(MEikRichTextEditorParserObserver* aObserver)
	{
	iParserObserver=aObserver;
	}

void CEikParserManager::Start(TInt aStartPos,TInt aLength)
	{
	if (iStartPos==KNullStartPos)
		iStartPos=aStartPos;
	else
		iStartPos=Min(iStartPos,aStartPos);
	if (iLength==0 || aLength>=0)
		iLength=Max(iLength,aLength);
	else // aLength<0
		iLength=Max(iLength+aLength,0);
	iStateChanged=ETrue;
	StartTimer();
	}

CEikParserManager::CEikParserManager(CEikRichTextEditor& aEditor)
	: iEditor(aEditor)
	{
	Reset();
	}

void CEikParserManager::ConstructL()
	{
	iTimer=CPeriodic::NewL(CActive::EPriorityStandard);
	iEditor.AddEdwinObserverL(this);
	}

void CEikParserManager::Start()
	{
	StartTimer();
	}

void CEikParserManager::StartTimer()
	{
	if (iTimer->IsActive())
		iTimer->Cancel();
	iTimer->Start(KParseScanDelay,KParseScanDelay,TCallBack(ParseTextCallbackL,this));
	}

void CEikParserManager::Reset()
	{
	iStartPos=KNullStartPos;
	iLength=0;
	}

TInt CEikParserManager::ParseTextCallbackL(TAny* aSelf)
	{ // static
	REINTERPRET_CAST(CEikParserManager*,aSelf)->ParseTextL();
	return 0;
	}

void CEikParserManager::ParseTextL()
	{
	TInt startPos=iStartPos;
	TInt length=iLength;
	Reset();
	iTimer->Cancel();
	const TBool foundParser=(iStateChanged && iEditor.RichText()->ParseText(startPos,length,iParseWholeText));
	iStateChanged=EFalse;
	MParser* parser=iParser;
	TInt tagStart=iTagStart;
	TInt tagLength=iTagLength;
	TInt err=KErrNone;
	TBool overNewTag=EFalse;
	if (iEditor.RichText()->CursorOverTag(iEditor.CursorPos(),parser,tagStart,tagLength))
		{
		// are we over a new tag?  Update members if so
		if ((TInt)parser!=(TInt)iParser || tagStart!=iTagStart || tagLength!=iTagLength)
			{
			overNewTag=ETrue;
			iParser=parser;
			if (iTagStart!=KNullStartPos)
				{
				TRAP(err,iEditor.TextView()->HandleRangeFormatChangeL(TCursorSelection(iTagStart,iTagStart+iTagLength),ETrue));
				}
			iTagStart=tagStart;
			iTagLength=tagLength;
			// the tag may be drawn differently when the cursor is over it
			TRAP(err,iEditor.TextView()->HandleRangeFormatChangeL(TCursorSelection(tagStart,tagStart+tagLength),ETrue));
			}
		}
	else
		{
		if (iParser)
			{
			overNewTag=ETrue; // if iParser!=NULL, we used to be over a tag and are now over a null one
			// the tag may be drawn differently now the cursor isn't over it
			TRAP(err,iEditor.TextView()->HandleRangeFormatChangeL(TCursorSelection(iTagStart,iTagStart+iTagLength),ETrue));
			}
		iParser=NULL;
		iTagStart=KNullStartPos;
		iTagLength=0;
		}
	if (foundParser && (startPos!=tagStart || length!=tagLength))
		{
		// newly identified parser is different from the one the cursor is over so...
		// change the text format for the parser also
		TRAPD(err2,iEditor.TextView()->HandleRangeFormatChangeL(TCursorSelection(startPos,startPos+length),ETrue));
		if (err==KErrNone)
			err=err2;
		}
	if (overNewTag && iParserObserver)
		{
		if (iParser)
			{
			iParserObserver->HandleCursorOverParserL(iParser->CreateDoItText(*(iEditor.RichText()),startPos,length));
			}
		else
			{
			TBuf<4> nullText(KNullDesC);
			iParserObserver->HandleCursorOverParserL(nullText);
			}
		}
	User::LeaveIfError(err);
	}

void CEikParserManager::HandleEdwinEventL(CEikEdwin* aEdwin,TEdwinEvent aEventType)
	{
	if ((TInt)aEdwin==(TInt)&iEditor && aEventType==MEikEdwinObserver::EEventNavigation)
		Start();
	}

void CEikParserManager::ForceFullParseL()
	{
	iParseWholeText = ETrue;
	iStateChanged = ETrue;
	ParseTextL();
	iParseWholeText = EFalse;
	}
//
// class CEikRichTextEditor
//

EXPORT_C CEikRichTextEditor::CEikRichTextEditor()
	{
	iEdwinUserFlags=EAllowPictures|EAllowUndo;
	iEdwinInternalFlags=ERichText;
	iDefaultIconicDoorSize=KDefaultIconicDoorSize;
	AKNTASHOOK_ADD( this, "CEikRichTextEditor" );
	}

EXPORT_C CEikRichTextEditor::CEikRichTextEditor(const TGulBorder& aBorder)
	: CEikGlobalTextEditor(aBorder)
	{
	iEdwinUserFlags=EAllowPictures|EAllowUndo;
	iEdwinInternalFlags=ERichText;
	iDefaultIconicDoorSize=KDefaultIconicDoorSize;
	AKNTASHOOK_ADD( this, "CEikRichTextEditor" );
	}

EXPORT_C CEikRichTextEditor::~CEikRichTextEditor()
	{
	AKNTASHOOK_REMOVE();
	CRichText* text=RichText();
	if (text)
	{
		text->SetEditObserver(NULL);
		}
	delete iEmbeddedDocUpdate;
	if (iEmbeddedDoc.iPicture.IsPtr())
		delete iEmbeddedDoc.iPicture.AsPtr();
	delete iParserManager;
	}

EXPORT_C void CEikRichTextEditor::ConstructL(const CCoeControl* aParent,TInt aNumberOfLines,TInt aTextLimit,
											 TInt aEdwinFlags,TInt aFontControlFlags,TInt aFontNameFlags)
	{
	CEikGlobalTextEditor::ConstructL(aParent,aNumberOfLines,aTextLimit,aEdwinFlags,aFontControlFlags,aFontNameFlags);
	CommonConstructL();
	}

EXPORT_C void CEikRichTextEditor::ConstructFromResourceL(TResourceReader& aReader)
	{
	CEikGlobalTextEditor::ConstructFromResourceL(aReader);
	CommonConstructL();
	}

void CEikRichTextEditor::CommonConstructL()
	{
	iEmbeddedDocUpdate=CIdle::NewL(EActivePriorityWsEvents+1);
	if (!(iEdwinUserFlags&ENoTextParsers))
		iParserManager=CEikParserManager::NewL(*this);
	}

EXPORT_C void CEikRichTextEditor::Draw(const TRect& aRect) const
	{
	CEikEdwin::Draw(aRect);
	}

EXPORT_C TKeyResponse CEikRichTextEditor::OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)
	{
	if (aType!=EEventKey)
		return EKeyWasNotConsumed;
	if (iEdwinUserFlags&EDisplayOnly)
		return EKeyWasConsumed;
	const TInt code=aKeyEvent.iCode;
	if ((code==EKeySpace || code==EKeyEnter) && CheckForObjectL())
		return EKeyWasConsumed;
	const TInt modifiers=aKeyEvent.iModifiers;
	if (modifiers&EModifierCtrl)
		{
		TBool consumed=ETrue;
		TBuf<24> buf;
		if (aKeyEvent.iModifiers&EModifierShift)
			iCoeEnv->ReadResource(buf,R_EIK_EDWIN_SHIFT_CTRL_HOTKEYS);
		else
			iCoeEnv->ReadResource(buf,R_EIK_EDWIN_CTRL_HOTKEYS);
		const TInt pos=buf.Locate(TChar(code+'a'-1));
		switch (pos)
			{
		case EHotKeyInsertObject:
			CheckNotReadOnlyL();
			if (!(iEdwinUserFlags&EAllowPictures))
				iEikonEnv->LeaveWithInfoMsg(R_EIK_TBUF_CANNOT_INSERT_OBJECTS);
			InsertObjectL(EGlassIfPossible);
			break;
		case EHotKeyEditObject:
			CheckNotReadOnlyL();
			if (!(iEdwinUserFlags&EAllowPictures))
				return EKeyWasConsumed;
			ReEditObjectL();
			break;
		case EHotKeyFormatObject:
			CheckNotReadOnlyL();
			if (!(iEdwinUserFlags&EAllowPictures))
				return EKeyWasConsumed;
			EditPictureFormatL();
			break;
		default:
			consumed=EFalse;
			}
		if (consumed)
			return EKeyWasConsumed;
		}
	TKeyResponse response=CEikGlobalTextEditor::OfferKeyEventL(aKeyEvent,aType);
	UpdateButtonGroup();
	return response;
	}

EXPORT_C void CEikRichTextEditor::HandlePointerEventL(const TPointerEvent& aPointerEvent)
	{
	CEikEdwin::HandlePointerEventL(aPointerEvent);
	}

EXPORT_C void* CEikRichTextEditor::ExtensionInterface( TUid /*aInterface*/ )
    {
    return NULL;
    }

EXPORT_C void CEikRichTextEditor::ActivateL()
	{
	SetTextObserver(*RichText());
	const TInt docLength=iText->DocumentLength();
	if( iParserManager )
		iParserManager->Start(0,docLength);
	UpdatePictureFormatL(0,docLength);
	UpdatePictureSizeL(0,docLength);
	CEikGlobalTextEditor::ActivateL();
	}
	
EXPORT_C void CEikRichTextEditor::HandleTextPastedL(TInt aStartPos,TInt& aLength)
	{
	UpdatePictureFormatL(aStartPos,aLength);
	UpdatePictureSizeL(aStartPos,aLength);
	}
	
EXPORT_C void CEikRichTextEditor::NotifyExit(TExitMode aMode)
	{
	if (aMode==MApaEmbeddedDocObserver::EEmpty)
		{
		if (iEdwinInternalFlags&EReEditingObject)
			iEmbeddedDocUpdate->Start(TCallBack(CEikRichTextEditor::TryDeleteEmbeddedDocL, this));
		else
			iEmbeddedDocUpdate->Start(TCallBack(CEikRichTextEditor::DeleteEmbeddedDoc, this));
		}
	else if (aMode==MApaEmbeddedDocObserver::ENoChanges)
		{
		if (iEdwinInternalFlags&EReEditingObject)
			iEmbeddedDoc=TPictureHeader();
		else // apps should call back with EEmpty in this case
			iEmbeddedDocUpdate->Start(TCallBack(CEikRichTextEditor::DeleteEmbeddedDoc, this));
		}
	else
		{
		if (iEdwinInternalFlags&EReEditingObject)
			iEmbeddedDocUpdate->Start(TCallBack(CEikRichTextEditor::UpdateEmbeddedDocL, this));
		else
			iEmbeddedDocUpdate->Start(TCallBack(CEikRichTextEditor::InsertEmbeddedDocL, this));
		}
	}

TInt CEikRichTextEditor::TryDeleteEmbeddedDocL(TAny *aThis)
	{ // static
	CEikRichTextEditor* editor=REINTERPRET_CAST(CEikRichTextEditor*,aThis);
	editor->iEdwinInternalFlags&=~EReEditingObject;
	if (!(CEikonEnv::Static()->QueryWinL(R_EIK_TBUF_DEL_EMPTY_OBJECT_CONFIRM_1,R_EIK_TBUF_DEL_EMPTY_OBJECT_CONFIRM_2)))
		editor->iTextView->HandleRangeFormatChangeL(editor->Selection(),EFalse);
	else
		{
		TInt docPos;
		TRect rect;
		editor->iTextView->IsPictureFrameSelected(rect,docPos);
		TBool changed=EFalse;
		editor->DeleteL(changed,TCursorSelection(docPos,docPos+1),ETrue);
		editor->iTextView->SetPendingSelection(TCursorSelection(docPos,docPos));
		editor->iTextView->HandleInsertDeleteL(TCursorSelection(docPos,docPos),1,changed);
		editor->UpdateScrollBarsL();
		if (changed)
			editor->ReportEdwinEventL(MEikEdwinObserver::EEventFormatChanged);
		}
	editor->ReportEventL(MCoeControlObserver::EEventStateChanged);
	editor->UpdateScrollBarsL();
	return 0;
	}

TInt CEikRichTextEditor::DeleteEmbeddedDoc(TAny *aThis)
	{ // static
	CEikRichTextEditor* editor=REINTERPRET_CAST(CEikRichTextEditor*,aThis);
	if (editor->iEmbeddedDoc.iPicture.IsPtr())
		delete editor->iEmbeddedDoc.iPicture.AsPtr();
	editor->iEmbeddedDoc=TPictureHeader();
	return 0;
	}

TInt CEikRichTextEditor::InsertEmbeddedDocL(TAny *aThis)
	{ // static
	CEikRichTextEditor* editor=REINTERPRET_CAST(CEikRichTextEditor*,aThis);
	TInt err=KErrNone;
	if (editor->iEdwinUserFlags&EShowAllPicturesAsIconic)
		{
		TRAPD(err,STATIC_CAST(CApaDoor*,editor->iEmbeddedDoc.iPicture.AsPtr())->SetFormatToTemporaryIconL());
		if (err)
			goto errorCheck;
		}
	TRAP(err,editor->InsertPictureL(editor->iEmbeddedDoc));
errorCheck:
	editor->iEmbeddedDoc=TPictureHeader();
	User::LeaveIfError(err);
	return 0;
	}

TInt CEikRichTextEditor::UpdateEmbeddedDocL(TAny* aThis)
	{ // static
	CEikRichTextEditor* editor=REINTERPRET_CAST(CEikRichTextEditor*,aThis);
	editor->iEdwinInternalFlags&=~EReEditingObject;
	editor->iText->SetHasChanged(ETrue);
	editor->iTextView->HandleRangeFormatChangeL(editor->Selection(),EFalse);
	editor->ReportEventL(MCoeControlObserver::EEventStateChanged);
	editor->UpdateScrollBarsL();
	return 0;
	}

EXPORT_C void CEikRichTextEditor::CopyDocumentContentL(CGlobalText& aInText,CGlobalText& aOutText)
	{
	__ASSERT_DEBUG(&aInText,Panic(EEikPanicNullPointer));
	__ASSERT_DEBUG(&aOutText,Panic(EEikPanicNullPointer));
	aOutText.Reset();
	aOutText.SetFieldFactory(CONST_CAST(MTextFieldFactory*,aInText.FieldFactory()));
	((CRichText&)aInText).DetachFromStoreL(CPicture::EDetachFull);
	iBufStore=CBufStore::NewLC(4096);
	((CRichText&)aOutText).SetPictureFactory(iEikonEnv->PictureFactory(),this);
	TStreamId streamId=aInText.StoreL(*iBufStore);
	aOutText.RestoreL(*iBufStore,streamId);
	((CRichText&)aOutText).DetachFromStoreL(CPicture::EDetachFull);
	RStoreWriteStream paraWriteStream;
	TStreamId paraStreamId=paraWriteStream.CreateLC(*iBufStore);
	(aInText.GlobalParaFormatLayer())->ExternalizeL(paraWriteStream);
	CleanupStack::PopAndDestroy(); // paraStreamId
	RStoreReadStream paraReadStream;
	paraReadStream.OpenLC(*iBufStore,paraStreamId);
	((CParaFormatLayer*)(aOutText.GlobalParaFormatLayer()))->InternalizeL(paraReadStream);
	CleanupStack::PopAndDestroy(); // paraReadStream
	RStoreWriteStream charWriteStream;
	TStreamId charStreamId=charWriteStream.CreateLC(*iBufStore);
	(aInText.GlobalCharFormatLayer())->ExternalizeL(charWriteStream);
	CleanupStack::PopAndDestroy(); // charStreamId
	RStoreReadStream charReadStream;
	charReadStream.OpenLC(*iBufStore,charStreamId);
	((CCharFormatLayer*)(aOutText.GlobalCharFormatLayer()))->InternalizeL(charReadStream);
	CleanupStack::PopAndDestroy(2); // iBufStore and charReadStream
	iBufStore=NULL;
	}

EXPORT_C const CStreamStore& CEikRichTextEditor::StreamStoreL(TInt /*aPos*/) const
	{
	return *iBufStore;
	}

EXPORT_C void CEikRichTextEditor::NewPictureL(TPictureHeader& aHdr,const CStreamStore& aDeferredPictureStore)const
	{
	iEikonEnv->PictureFactory()->NewPictureL(aHdr,aDeferredPictureStore);
	}

EXPORT_C void CEikRichTextEditor::EditObserver(TInt aStartEdit,TInt aEditLength)
	{
	if (iParserManager)
		iParserManager->Start(aStartEdit,aEditLength);
	CEikEdwin::EditObserver(aStartEdit,aEditLength);
	}

EXPORT_C CRichText* CEikRichTextEditor::RichText() const
	{
	return (CRichText*)iText;
	}

void CEikRichTextEditor::InsertPictureL(const TPictureHeader& aPictureHeader)
	{
	__ASSERT_DEBUG(iText,Panic(EEikPanicEdwinNoText));
	__ASSERT_DEBUG(iTextView,Panic(EEikPanicEdwinNoView));
	TBool formatHasChanged=EFalse;
	TCursorSelection selection=iTextView->Selection();
	const TInt selLength=selection.Length();
	const TInt oldLength=iText->DocumentLength();
	TRAPD(err,DoInsertPictureL(formatHasChanged,aPictureHeader));
	if (err!=KErrNone)
		{
		delete aPictureHeader.iPicture.AsPtr();
		ClearUndo();
		}
	if (selLength==0)
		{
		ClearUndo();
		if (err==KErrNone)
			iTextView->HandleCharEditL(CTextLayout::EFCharacterInsert);
		}
	else
		{
		const TInt lower=selection.LowerPos();
		selection=TCursorSelection(lower,(err==KErrNone? lower+1 : lower));
		if (err==KErrNone)
			SetUndoableText(selection);
		if (err==KErrNone || oldLength>iText->DocumentLength())
			iTextView->HandleInsertDeleteL(selection,selLength,formatHasChanged);
		}
	User::LeaveIfError(err);
	ReportEventL(MCoeControlObserver::EEventStateChanged);
	UpdateScrollBarsL();
	if (iText->DocumentLength()==UpperFullFormattingLength()+1)
		SetAmountToFormatL();
	}

void CEikRichTextEditor::DoInsertPictureL(TBool& aFormatHasChanged,const TPictureHeader& aPictureHeader)
	{
	TCursorSelection selection=iTextView->Selection();
	const TInt selLength=selection.Length();
	if (selLength)
		{
		iTextView->CancelSelectionL();
		SetCursorPosL(selection.LowerPos(),EFalse);
		DeleteL(aFormatHasChanged,selection);
		}
	else if (iTextLimit && TextLength()>=iTextLimit)
		{
		CEikonEnv::Beep();
		iEikonEnv->LeaveWithInfoMsg(R_EIK_TBUF_MAX_CHARACTERS_REACHED);
		}
	STATIC_CAST(CRichText*,iText)->InsertL(CursorPos(),aPictureHeader);
	}

void CEikRichTextEditor::RoomForObjectL()
	{
	if (iTextLimit && TextLength()>=iTextLimit)
		{
		CEikonEnv::Beep();
		iEikonEnv->InfoMsg(R_EIK_TBUF_MAX_CHARACTERS_REACHED);
		CBaActiveScheduler::LeaveNoAlert();
		}
	}

EXPORT_C void CEikRichTextEditor::InsertObjectL(TObjectFormat aFormat)
	{
	RoomForObjectL();
	CEikEmbeddableAppList* list=new(ELeave) CEikEmbeddableAppList;
	CleanupStack::PushL(list);
	list->ConstructL();
	TInt count=list->Count();
	if (!count)
		iEikonEnv->InfoMsg(R_EIK_NO_EMBEDDABLE_APPS_FOUND);
	else
		{
		ASSERT(iEikonEnv->CDlgDialogFactory());
		TInt choice=0;
		if(iEikonEnv->CDlgDialogFactory()->RunInsertObjectDlgLD(list, choice))
			{
			if (!OkToDeleteSelectionL())
				{
				CleanupStack::PopAndDestroy(); // list
				return;
				}
			CEikDocument* newDoc=list->CreateEmbeddedDocumentL(choice,iEikonEnv->Process());
			TApaDocCleanupItem cleanup(iEikonEnv->Process(),newDoc);
			CleanupStack::PushL(cleanup);
			newDoc->NewDocumentL();
			CleanupStack::Pop(); // cleanup
			InsertObjectL(newDoc,aFormat);
			}
		}
	CleanupStack::PopAndDestroy(); // list
	}

EXPORT_C void CEikRichTextEditor::InsertObjectL()
	{
	InsertObjectL(EGlassIfPossible);
	}

EXPORT_C void CEikRichTextEditor::InsertObjectL(const TDesC& /*aAppDllName*/,TUid aAppDllUid,TObjectFormat aFormat)
	{
	RoomForObjectL();
	if (!OkToDeleteSelectionL())
		return;
	CApaDocument* newDoc=NULL;
	TRAPD(err,newDoc=iEikonEnv->Process()->AddNewDocumentL(aAppDllUid));
	if (err==KErrNotFound)
		iEikonEnv->LeaveWithInfoMsg(R_EIK_EMBEDDED_GENERIC_APP_NOT_FOUND);
	else if (err!=KErrNone)
		User::Leave(err);
	TApaDocCleanupItem cleanup(iEikonEnv->Process(),newDoc);
	CleanupStack::PushL(cleanup);
	newDoc->NewDocumentL();
	CleanupStack::Pop();
	InsertObjectL(newDoc,aFormat);
	}

void CEikRichTextEditor::InsertObjectL(CApaDocument* aDoc,TObjectFormat aFormat)
	{
	iEmbeddedDoc.iPictureType=KUidPictureTypeDoor;
	iEmbeddedDoc.iPicture=CApaDoor::NewL(iEikonEnv->FsSession(),*aDoc,iDefaultIconicDoorSize); // takes ownership of newDoc
	// can it draw as glass? change format if so
	if (aFormat==EGlassIfPossible)
		{
		TRAP_IGNORE(STATIC_CAST(CApaDoor*,iEmbeddedDoc.iPicture.AsPtr())->SetFormatToGlassL());
		}
	aDoc->EditL(this);
	}

EXPORT_C void CEikRichTextEditor::InsertObjectL(TUid aPictureType,CBase* aData)
	{
	MEikPictureFactory* factory=iEikonEnv->ExtendedPictureFactory(aPictureType);
	if (factory==NULL)
		{
		User::Leave(KErrNotSupported);
		}
	TPictureHeader pic=factory->InsertL(aPictureType,aData);
	InsertPictureL(pic);
	}

EXPORT_C TBool CEikRichTextEditor::CheckForObjectL()
	{
	TRect frameRect;
	TInt docPos;
	if (!iTextView->IsPictureFrameSelected(frameRect,docPos))
		return EFalse;
	const TPictureHeader header=((CRichText*)iText)->PictureHeader(docPos);
	if (header.iPictureType==KNullUid)
		return EFalse;
	// stop multiple pointer events launching the same apps several times ???
	iCoeEnv->WsSession().PurgePointerEvents();
	DoReEditObjectL(docPos);
	return ETrue;
	}

EXPORT_C void CEikRichTextEditor::ReEditObjectL()
	{
	const TInt pos=ObjectCursorPos();
	if (pos!=KErrNotFound)
		DoReEditObjectL(pos);
	}

EXPORT_C TInt CEikRichTextEditor::ObjectCursorPos() const
	{
	if (SelectionLength()>1)
		{
		iEikonEnv->InfoMsg(R_EIK_REGION_SELECTED);
		return KErrNotFound;
		}
	TRect frameRect;
	TInt docPos;
	if (iTextView->IsPictureFrameSelected(frameRect,docPos))
		{
		TPictureHeader header=STATIC_CAST(CRichText*,iText)->PictureHeader(docPos);
		if (header.iPictureType!=KNullUid)
			return docPos;
		}
	iEikonEnv->InfoMsg(R_EIK_NO_OBJECT_PRESENT); // no embedded object found
	return KErrNotFound;
	}

void CEikRichTextEditor::DoReEditObjectL(TInt aDocPos)
	{
	TPictureHeader header=RichText()->PictureHeader(aDocPos);
	if (header.iPictureType==KUidPictureTypeDoor)
	{
	CApaDoor* door=NULL;
	CApaDocument* embeddedDoc=NULL;
	GetEmbeddedAppL(door,embeddedDoc,aDocPos);
	iEdwinInternalFlags|=EReEditingObject;
	embeddedDoc->EditL(this,IsReadOnly());
		}
	else
		{
		MEikPictureFactory* factory=iEikonEnv->ExtendedPictureFactory(header.iPictureType);
		if (factory==NULL)
			{
			User::Leave(KErrNotSupported);
			}
		factory->EditL(header,IsReadOnly());
		}
	}

EXPORT_C void CEikRichTextEditor::EditPictureFormatL()
	{
	const TInt docPos=ObjectCursorPos();
	if (docPos==KErrNotFound)
		return;
	CApaDoor* door=NULL;
	CApaDocument* embeddedDoc=NULL;
	GetEmbeddedAppL(door,embeddedDoc,docPos);
	// if the doc can display as glass open the full dialog
	CApaDocument::TCapability capability=embeddedDoc->Capability();
	MEikCDlgDialogFactory* cdlgDialogFactory = iEikonEnv->CDlgDialogFactory();
	ASSERT(cdlgDialogFactory);
	if (capability.CanDrawGlass())
		{
		if(cdlgDialogFactory->RunFormatObjectDlgLD(*door, *embeddedDoc, iDefaultIconicDoorSize))
			{
			iText->SetHasChanged(ETrue);
			iTextView->HandleRangeFormatChangeL(iTextView->Selection(),EFalse);
			UpdateScrollBarsL();
			ReportEventL(MCoeControlObserver::EEventStateChanged);
			// update the picture size in the header when this becomes possible (post B4 etext)
			}
		}
	else
		{// otherwise open the little dialog that does nothing...
		cdlgDialogFactory->RunObjectInfoDlgLD(*(door->Caption()));
		}
	}


EXPORT_C void CEikRichTextEditor::PictureFormatChangedL()
	{
	iText->SetHasChanged(ETrue);
	iTextView->HandleRangeFormatChangeL(iTextView->Selection(),EFalse);
	UpdateScrollBarsL();
	// update the picture size in the header when this becomes possible (post B4 etext)
	ReportEventL(MCoeControlObserver::EEventStateChanged);
	}

EXPORT_C void CEikRichTextEditor::GetEmbeddedAppL(CApaDoor*& aDoor,CApaDocument*& aDoc,TInt aDocPos)
	{
	aDoor=STATIC_CAST(CApaDoor*,RichText()->PictureHandleL(aDocPos));
	TRAPD(err,aDoc=aDoor->DocumentL(ETrue)); // always prompt for password
	if (err==KErrNotFound)
		{
		TBuf<80> buf;
		iCoeEnv->ReadResource(buf,R_EIK_EMBEDDED_APP_NOT_FOUND);
		TBuf<128> caption=*aDoor->Caption();
		TextUtils::TruncateToNumChars(caption,RMessageWindow::EMaxTextLength-32); // resource is no longer than 32 chars
		HBufC* message=HBufC::NewLC(caption.Length()+buf.Length());
		TPtr ptr=message->Des();
		ptr.Format(buf,&caption);
		iEikonEnv->InfoMsg(*message);
		CleanupStack::PopAndDestroy(); // message
		CBaActiveScheduler::LeaveNoAlert();
		}
	User::LeaveIfError(err);
	}

EXPORT_C void CEikRichTextEditor::UpdatePictureFormatL()
	{
	UpdatePictureFormatL(0,iText->DocumentLength());
	}

EXPORT_C void CEikRichTextEditor::UpdatePictureFormatL(TInt aStartPos,TInt aLength)
	{
	TInt count=iText->ComponentInfo().iPictureCount;
	if (~iEdwinUserFlags&EShowAllPicturesAsIconic || count==0)
		return;
	const TInt endPos=aStartPos+aLength;
	for (TInt ii=aStartPos;ii<endPos;ii++)
		{
		if (count==0)
			return;
		CApaDoor* door=STATIC_CAST(CApaDoor*,RichText()->PictureHandleL(ii));
		if (door)
			{
			door->SetFormatToTemporaryIconL();
			--count;
			}
		}
	}

EXPORT_C void CEikRichTextEditor::SetDefaultIconicDoorSize(const TSize& aSize)
	{
	iDefaultIconicDoorSize=aSize;
	}

EXPORT_C const TSize& CEikRichTextEditor::DefaultIconicDoorSize() const
	{
	return iDefaultIconicDoorSize;
	}

EXPORT_C void CEikRichTextEditor::UpdatePictureSizeL()
	{
	UpdatePictureSizeL(0,iText->DocumentLength());
	}

EXPORT_C void CEikRichTextEditor::UpdatePictureSizeL(TInt aStartPos,TInt aLength)
	{
	TInt count=iText->ComponentInfo().iPictureCount;
	const TInt endPos=aStartPos+aLength;
	for (TInt ii=aStartPos;ii<endPos;ii++)
		{
		if (count==0)
			return;
		CApaDoor* door=STATIC_CAST(CApaDoor*,RichText()->PictureHandleL(ii));
		if (door)
			{
			if (door->Format()!=CApaDoorBase::EGlassDoor)
				door->SetSizeInTwips(iDefaultIconicDoorSize);
			else
				{
				door->SetFormatToTemporaryIconL(ETrue);
				door->SetSizeInTwips(iDefaultIconicDoorSize);
				door->SetFormatToTemporaryIconL(EFalse);
				}
			--count;
			}
		}
	}

EXPORT_C void CEikRichTextEditor::SetParserObserver(MEikRichTextEditorParserObserver* aObserver)
	{
	if (iParserManager)
		iParserManager->SetParserObserver(aObserver);
	}

EXPORT_C void CEikRichTextEditor::SetPhoneNumberGrouping( TBool aEnable )
    {
    if ( aEnable )
    	iEdwinInternalFlags|=EPhoneNumberGrouping;
    else
    	iEdwinInternalFlags&=(~EPhoneNumberGrouping);
    }

void CEikRichTextEditor::SetTextObserver(CRichText& aText)
	{
	aText.SetEditObserver(this);
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
EXPORT_C void CEikRichTextEditor::WriteInternalStateL(RWriteStream&) const
	{}
#else
EXPORT_C void CEikRichTextEditor::WriteInternalStateL(RWriteStream& aWriteStream) const
	{
	CEikGlobalTextEditor::WriteInternalStateL(aWriteStream);
	}
#endif

EXPORT_C void CEikRichTextEditor::Reserved_2()
	{}

EXPORT_C void CEikRichTextEditor::Reserved_3()
	{}

EXPORT_C void CEikRichTextEditor::RefreshParsersL()
	{
	if (iParserManager)
		iParserManager->ForceFullParseL();
	}
