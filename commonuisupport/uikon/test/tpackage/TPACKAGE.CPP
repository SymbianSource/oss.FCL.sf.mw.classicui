// Copyright (c) 2005-2009 Nokia Corporation and/or its subsidiary(-ies).
// All rights reserved.
// This component and the accompanying materials are made available
// under the terms of "Eclipse Public License v1.0"
// which accompanies this distribution, and is available
// at the URL "http://www.eclipse.org/legal/epl-v10.html".
//
// Initial Contributors:
// Nokia Corporation - initial contribution.
//
// Contributors:
//
// Description:
// This test aims to test embedding feature of the application. 
// It work together with uiktestserver framework as part of the chain:
// Testexecute.exe -> tpackagestarter.dll -> tpackage.app -> tembed.app
// Tpackage communicates with tpackagestarter.dll via client-server architecture. 
// Client passes to server 3 parameters, packed in structure: 
// first is message to log, second is filename, third - the number of line.
// To test embedding technology tpackage embeds  application, tembed, 
// inside its instance and provide consequences  of acts as follow: inserting object, 
// editing object, closing, deleting object. 
// To provide logging test information tpackage client send log buffer to the 
// server using the message EMessageServSetFromString for an Info message and
// EMessageServSetErrorFromString for an error message. 
// Those two messages can be sent via funcions SetFromString and SetErrorFromString.
// After a consequence is completed, the EmessageServStop message will be sent, 
// that causes closing client-server session and the tpackagestarter test step itself.
// 
//

/**
 @file
 @internalComponent - Internal Symbian test code
*/


#include <eikenv.h>
#include <coecntrl.h>
#include <basched.h>
#include <coeccntx.h>
#include <eikappui.h>
#include <e32keys.h>
#include <eikembal.h>
#include <bamdesca.h>
#include <techview/eikon.hrh>
#include <techview/eikdialg.h>
#include <techview/eikchlst.h>
#include <eikdoc.h>
#include <eikapp.h>
#include <s32file.h>
#include <techview/eikprtpv.h>
#include <eikproc.h>
#include <techview/eikon.rsg>
#include <techview/eikmisdg.h>
#include "messageservclient.h"

#include <eikstart.h>

#include "tpackage.rsg"
#include "TPACKAGE.HRH"


#include "appfwk_test_AppUi.h"

#include "TEMBED.h"

#include "messageservserver.h"


#define FORCE_AUTO

_LIT(KTestText, "ABCDEF");

const TUid KUidPackagerApp={0x10207F6E};

struct SPackage
	{
public:
	TBuf<20> iPrompt;
	CApaDocument* iDocument;
	};

//
// CPackagerModel
//
class CPackagerModel : public CArrayFixFlat<SPackage>
	{
public:
	CPackagerModel(CApaProcess* aProcess);
	~CPackagerModel();
	void AppendDocL(CApaDocument* aDoc);
	void DeleteDoc(TInt aPos);
private:
	CApaProcess* iProcess;
	};

CPackagerModel::CPackagerModel(CApaProcess* aProcess)
	: CArrayFixFlat<SPackage> (2)
	{
	iProcess=aProcess;
	}

CPackagerModel::~CPackagerModel()
	{
	const TInt count=Count();
	for (TInt pos=0; pos<count; pos++)
		iProcess->DestroyDocument((*this)[pos].iDocument);
	}

void CPackagerModel::AppendDocL(CApaDocument* aDoc)
	{
	SPackage package;
	package.iDocument=aDoc;
	TRAPD(err,AppendL(package));
	if (err)
		{
		iProcess->DestroyDocument(aDoc);
		User::Leave(err);
		}
	}

void CPackagerModel::DeleteDoc(TInt aPos)
	{
	CApaDocument* doc=(*this)[aPos].iDocument;
	iProcess->DestroyDocument(doc);
	Delete(aPos);
	}

//
// CPackagerContainer
//

class CPackagerContainer : public CCoeControl, public MCoeControlBrushContext
    {
public:
    void ConstructL(const TRect& aRect);
	~CPackagerContainer();
private: // framework
    void Draw(const TRect& aRect) const;
	TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
    void SizeChanged();
    void FocusChanged(TDrawNow aDrawNow);
private:
    };

void CPackagerContainer::FocusChanged(TDrawNow /*aDrawNow*/)
    {
    }
    
void CPackagerContainer::ConstructL(const TRect& aRect)
    {
    CreateWindowL();
    Window().SetShadowDisabled(ETrue);
	EnableDragEvents();
	iBrushStyle=CGraphicsContext::ESolidBrush;
	iBrushColor=KRgb1in4DitheredGray;
    iContext=this;
	Window().SetBackgroundColor(KRgb1in4DitheredGray);
    SetRect(aRect);
    ActivateL();
    }

CPackagerContainer::~CPackagerContainer()
	{
	}

void CPackagerContainer::Draw(const TRect& aRect) const
    {
	CGraphicsContext& gc=SystemGc();
	gc.SetPenStyle(CGraphicsContext::ENullPen);
	gc.DrawRect(aRect);
    }

void CPackagerContainer::SizeChanged()
    {
    }

TKeyResponse CPackagerContainer::OfferKeyEventL(const TKeyEvent& /*aKeyEvent*/,TEventCode /*aType*/)
    {
    return(EKeyWasConsumed);
    }

//
// CPackagerDocument - definition
//

class CPackagerDocument : public CEikDocument
	{
public:
	CPackagerDocument(CEikApplication& aApp): CEikDocument(aApp), iModel(Process()) { }
	CPackagerModel* Model() { return(&iModel); }
private: // from CEikDocument
	CEikAppUi* CreateAppUiL();
private: // from CApaDocument
	void StoreL(CStreamStore& aStore,CStreamDictionary& aStreamDic) const;
	void RestoreL(const CStreamStore& aStore,const CStreamDictionary& aStreamDic);
private:
	CPackagerModel iModel;
	};



//
// CPackagerAppUi
//

class CPackagerAppUi : public CTestAppUi
    {
public:
	CPackagerAppUi() :
	  CTestAppUi(NULL, KNullDesC) 
		{
		iTestText.Set(KTestText);
		}
    void ConstructL();
	~CPackagerAppUi();
	RMessageServ*		iServ;
	void SetFromString(const TDesC& aString, const TText8* aString1, TInt	aLineNumber);
	void SetErrorFromString(const TDesC& aString, const TText8* aString1, TInt	aLineNumber, TInt aErr);

private: // from CEikAppUi
    void HandleCommandL(TInt aCommand);
private: // internal functions
	void CmdInsertObjectL();
	void CmdEditObjectL();
	void CmdDeleteObjectL();
	TInt SelectDocumentL(TInt aHelpRid,TInt aTitleRid);
	void RunTestStepL(TInt aNumStep);
	void SendKeyEventToApplicationL(TKeyEvent	theKeyEvent);
	TInt FindIndex(CEikEmbeddableAppList* aList, TInt* aDestIndex);
	void TestEmbeddableAppListL();
private:
    CPackagerContainer* iContainer;
	CPackagerModel* iModel;
	TPtrC			iTestText;
 
   };


void CPackagerAppUi::ConstructL()
    {
	iModel=((CPackagerDocument*)iDocument)->Model();
    //BaseConstructL();
	CTestAppUi::ConstructL();

	iContainer=new(ELeave) CPackagerContainer;
    iContainer->ConstructL(ClientRect());
    AddToStackL(iContainer);

	iServ = new RMessageServ;
	TInt theRes = iServ->Connect();
	if(theRes != KErrNone)
		{
		delete iServ;
		iServ = NULL;
		}
	
	AutoTestManager().StartAutoTest();
    }

CPackagerAppUi::~CPackagerAppUi()
	{
	RemoveFromStack(iContainer);
    delete iContainer;
	
	if(iServ)
	{
		iServ->Stop();	
		iServ->Close();
	}
	delete iServ;
	}

void CPackagerAppUi::HandleCommandL(TInt aCommand)
    {
	switch (aCommand)
		{
	case EEikCmdExit:
		SaveAnyChangesL();
        Exit();
		break;
	case ETPackagerCmdInsertObject:
		CmdInsertObjectL();
		break;
	case ETPackagerCmdEditObject:
		CmdEditObjectL();
		break;
	case ETPackagerCmdDeleteObject:
		CmdDeleteObjectL();
		break;
		}
    }

TInt CPackagerAppUi::SelectDocumentL(TInt aHelpRid,TInt /*aTitleRid*/)
	{
	const TInt max=iModel->Count();
	if (!max)
		{
		TBuf<20> tmp;
		iCoeEnv->ReadResource(tmp,aHelpRid);
		iEikonEnv->LeaveWithInfoMsg(R_TPCK_TBUF_NO_OBJECTS_TO_XXX,&tmp);
		}
	TInt pos=1;
	//if (max>1)
	//	{
	//	if (CEikNumDialog::RunDlgLD(pos,1,max,aTitleRid,R_TPCK_TBUF_DLG_PROMPT))
	//		CBaActiveScheduler::LeaveNoAlert();
	//	}
	return(pos-1);
	}

void CPackagerAppUi::CmdEditObjectL()
	{
	TInt pos=SelectDocumentL(R_TPCK_TBUF_EDIT,R_TPCK_TBUF_EDIT_DLG_TITLE);
	CDocument* doc=(CDocument*)  ((*iModel)[pos].iDocument);
	
	if(doc->iBuf.Compare(iTestText) == 0)
		{
		((CEikDocument*)doc)->EditL(NULL);
		}
	else
		{//this is the error
			
		}
	


	}

void CPackagerAppUi::CmdDeleteObjectL()
	{
	TInt pos=SelectDocumentL(R_TPCK_TBUF_DELETE,R_TPCK_TBUF_DELETE_DLG_TITLE);
	iModel->DeleteDoc(pos);
	}


TInt CPackagerAppUi::FindIndex(CEikEmbeddableAppList* aList, TInt* aDestIndex)
	{
	TInt theNumElem = aList->Count();
	
	RDebug::Print(_L("Number elements in embeded list : %d\n"), theNumElem);

	for(TInt theIndex = 0; theIndex < theNumElem; theIndex++)
		{
		TApaAppInfo& appInfo = (*aList)[theIndex];
		RDebug::Print(_L("Element number %d  : %S\n"), theIndex, &appInfo.iFullName);
		if(appInfo.iFullName.FindF(_L("embed")) >= 0)
			{
			
			TBuf<128> buf;
			buf.Format(_L("Element embed has been found  with index : %d\n"), theIndex);
			SetFromString(buf, ((TText8*)__FILE__), __LINE__);

			//RDebug::Print(_L("Element embed has been found  with index : %d\n"), theIndex);
			*aDestIndex = theIndex;
			return KErrNone;
			}
		}
		
	return KErrNotFound;
	}

void CPackagerAppUi::CmdInsertObjectL()
	{
	CEikEmbeddableAppList* list=new(ELeave) CEikEmbeddableAppList;
	CleanupStack::PushL(list);
	
	// sleep for 5 sec to give apparc time to initialise properly
	User::After(5000000);
	
	list->ConstructL();
	TInt count=list->Count();
	if (!count)
		iEikonEnv->InfoMsg(R_TPCK_TBUF_NO_EMBEDDABLE_APPS_FOUND);
	else
		{
		TInt choice=0;
		RDebug::Print(_L("Find index in list\n"));
		TInt theErr = FindIndex(list, &choice);
		if(theErr == KErrNone)
			{
			RDebug::Print(_L("Creating the embeded document\n"));
			CEikDocument* newDoc=list->CreateEmbeddedDocumentL(choice,iEikonEnv->Process());
			iModel->AppendDocL(newDoc);
			newDoc->EditL(NULL);
			}
		}
	CleanupStack::PopAndDestroy(); // list
	}


void CPackagerAppUi::SetFromString(const TDesC& aString, const TText8* aString1, TInt	aLineNumber)
	{
	if(iServ)
		{
		iServ->SetFromString(aString, aString1, aLineNumber);
		}
	}

void CPackagerAppUi::SetErrorFromString(const TDesC& aString, const TText8* aString1, 
										TInt	aLineNumber, TInt aErr)
	{
	if(iServ)
		{
		iServ->SetErrorFromString(aString, aString1, aLineNumber, aErr);
		}
	}

void CPackagerAppUi::RunTestStepL(TInt aNumStep)
	{
	TKeyEvent theKeyEvent;
	Mem::FillZ(&theKeyEvent, sizeof(TKeyEvent));
	TBuf<128> buf;

	//only for debug
#ifdef FORCE_AUTO
	User::After(TTimeIntervalMicroSeconds32(1000000));
#endif	
	switch(aNumStep)
		{
		case 1:
			{
			RDebug::Print(_L("Insert the object\n"));
			buf.Copy(_L("Insert the holy object\n"));
			SetFromString(buf, ((TText8*)__FILE__), __LINE__);
			TRAPD(res, CmdInsertObjectL());
			if(res == KErrGeneral)
				{
				//RDebug::Print(_L("Error during inserting object : %d\n"), res);
				buf.Format(_L("Error during inserting object : %d\n"), res);
				SetFromString(buf, ((TText8*)__FILE__), __LINE__);

				
				RDebug::Print(_L("Try insert object again\n"));
				TRAP(res, CmdInsertObjectL());
				}
			if(res != KErrNone)
				{
				buf.Format(_L("Error during inserting object : %d\n"), res);
				SetErrorFromString(buf, ((TText8*)__FILE__), __LINE__, res);
				AutoTestManager().FinishAllTestCases(CAutoTestManager::EFailed);
				}
			break;
			}
		case 2: 
			{
			//test.Next(_L("Type chars"));
			SetFromString(_L("Type chars\n"), ((TText8*)__FILE__), __LINE__);
			theKeyEvent.iCode = iTestText[0];
			SendKeyEventToApplicationL(theKeyEvent);
			theKeyEvent.iCode = iTestText[1];
			SendKeyEventToApplicationL(theKeyEvent);
			theKeyEvent.iCode = iTestText[2];
			SendKeyEventToApplicationL(theKeyEvent);
			break;
			}
		case 3: 
			{
			theKeyEvent.iCode = EKeyEnter;
			//RDebug::Print(_L("Type Key Enter\n"));
			SetFromString(_L("Type Key Enter\n"), ((TText8*)__FILE__), __LINE__);
			//SendKeyEventToApplicationL(theKeyEvent);
			break;
			}
		case 4: 
			{
			theKeyEvent.iCode = iTestText[3];
			SendKeyEventToApplicationL(theKeyEvent);
			theKeyEvent.iCode = iTestText[4];
			SendKeyEventToApplicationL(theKeyEvent);
			theKeyEvent.iCode = iTestText[5];
			SendKeyEventToApplicationL(theKeyEvent);
			SetFromString(_L("Type chars\n"), ((TText8*)__FILE__), __LINE__);
			break;
			}
		case 5: case 8:
			{
			//test.Next(_L("Close the embeded document"));
			//RDebug::Print(_L("Close the embeded document\n"));
			SetFromString(_L("Close the embeded document\n"), ((TText8*)__FILE__), __LINE__);
			theKeyEvent.iCode = CTRL('e');
			theKeyEvent.iModifiers=EModifierCtrl;

			SendKeyEventToApplicationL(theKeyEvent);
			break;
			}
		case 6: 
			{
			//test.Next(_L("Edit the embeded document"));
			//RDebug::Print(_L("Edit the embeded document\n"));
			SetFromString(_L("Edit the embeded document\n"), ((TText8*)__FILE__), __LINE__);
			TRAPD(err, CmdEditObjectL());
			if(err != KErrNone)
				{
				buf.Format(_L("Error during editting embeded document : %d\n"), err);
				SetErrorFromString(buf, ((TText8*)__FILE__), __LINE__, err);
				AutoTestManager().FinishAllTestCases(CAutoTestManager::EFailed);
				}
			break;
			}
		case 7: 
			{
			theKeyEvent.iCode = EKeyBackspace;
			//RDebug::Print(_L("Type Key BackSpace\n"));
			SetFromString(_L("Type Key BackSpace\n"), ((TText8*)__FILE__), __LINE__);
			SendKeyEventToApplicationL(theKeyEvent);
			SendKeyEventToApplicationL(theKeyEvent);
			break;
			}
		case 9:
			{
			//RDebug::Print(_L("Delete the embeded document\n"));
			SetFromString(_L("Delete the embeded document\n"), ((TText8*)__FILE__), __LINE__);
			TRAPD(err, CmdDeleteObjectL());
			if(err != KErrNone)
				{
				//RDebug::Print(_L("Error during deleting embeded document : %d\n"), err);
				TBuf<128> buf;
				buf.Format(_L("Error during deleting embeded document : %d\n"), err);
				SetErrorFromString(buf, ((TText8*)__FILE__), __LINE__, err);

				AutoTestManager().FinishAllTestCases(CAutoTestManager::EFailed);
				}
			break;
			}
		case 10:
			{
			TRAPD(err, SaveAnyChangesL());
			if(err != KErrNone)
				{
				//RDebug::Print(_L("Error during saving embeded document : %d\n"), err);
				buf.Format(_L("Error during saving embeded document : %d\n"), err);
				SetErrorFromString(buf, ((TText8*)__FILE__), __LINE__, err);
				AutoTestManager().FinishAllTestCases(CAutoTestManager::EFailed);
				}
			break;
			}
		case 11:
			{
			TRAPD(err, TestEmbeddableAppListL());
			if(err != KErrNone)
				{
				buf.Format(_L("Leave from TestEmbeddableAppListL with err : %d\n"), err);
				SetErrorFromString(buf, ((TText8*)__FILE__), __LINE__, err);
				AutoTestManager().FinishAllTestCases(CAutoTestManager::EFailed);
				}
			else
				{
				AutoTestManager().FinishAllTestCases(CAutoTestManager::EPass);
				}
			break;
			}
		}
	}

void CPackagerAppUi::TestEmbeddableAppListL()
	{
	TBuf<128> buf;
	buf = _L("CPackagerAppUi::TestEmbeddableAppList");
	SetFromString(buf, ((TText8*)__FILE__), __LINE__);

	CEikEmbeddableAppList* appList = new (ELeave) CEikEmbeddableAppList();
	CleanupStack::PushL(appList);

	TApaEmbeddabilityFilter filter;
	filter.AddEmbeddability(TApaAppCapability::EEmbeddable);
	filter.AddEmbeddability(TApaAppCapability::EEmbeddableOnly);
	appList->ConstructL(filter);
	const TInt numberOfApps = appList->Count();
	if (numberOfApps == 0)
		{
		User::Leave(KErrGeneral);
		}

	CleanupStack::PopAndDestroy(appList);
	}

void CPackagerAppUi::SendKeyEventToApplicationL(TKeyEvent	theKeyEvent)
	{
	TEventCode	theType;
	theType = EEventKeyDown;
	iCoeEnv->SimulateKeyEventL(theKeyEvent,theType);
	theType = EEventKey;
	iCoeEnv->SimulateKeyEventL(theKeyEvent,theType);
	theType = EEventKeyUp;
	iCoeEnv->SimulateKeyEventL(theKeyEvent,theType);
	}


//
// CPackagerDocument - implementation
//

CEikAppUi* CPackagerDocument::CreateAppUiL()
	{
    return(new(ELeave) CPackagerAppUi);
	}

void CPackagerDocument::StoreL(CStreamStore& aStore,CStreamDictionary& aStreamDic) const
	{
	RStoreWriteStream stream;
	TStreamId streamId=stream.CreateLC(aStore);
//	stream<<iModel;
	stream.CommitL();
	CleanupStack::PopAndDestroy(); // stream
	aStreamDic.AssignL(KUidPackagerApp,streamId);
	}

void CPackagerDocument::RestoreL(const CStreamStore& aStore,const CStreamDictionary& aStreamDic)
	{
	TStreamId headStreamId=aStreamDic.At(KUidPackagerApp);
	RStoreReadStream stream;
	stream.OpenLC(aStore,headStreamId);
//	stream>>iModel;
	CleanupStack::PopAndDestroy(); // stream
	}
	
//
// CPackagerApplication
//

class CPackagerApplication : public CEikApplication
	{
private: // from CApaApplication
	CApaDocument* CreateDocumentL();
	TUid AppDllUid() const;
private:
	CApaDocument* CreateDocumentL(CApaProcess* a) { return CEikApplication::CreateDocumentL(a); }
	};

TUid CPackagerApplication::AppDllUid() const
	{
	return(KUidPackagerApp);
	}

CApaDocument* CPackagerApplication::CreateDocumentL()
	{
	return new(ELeave) CPackagerDocument(*this);
	}

//
// EXPORTed functions
//



LOCAL_C CApaApplication* NewApplication()
	{
	return new CPackagerApplication;
	}
	
GLDEF_C TInt E32Main()
	{
	return EikStart::RunApplication(NewApplication);
	}
	


