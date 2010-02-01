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

#include <tapplanguagesc.rsg>
#include "TAppLanguageSc.HRH"


#include "appfwk_test_AppUi.h"


#include "TAppLangScStarter.h"


#define FORCE_AUTO

const TUid KUidAppLanguageSCApp={0x10004c69};

//
// CPackagerDocument - definition
//

class CPackagerDocument : public CEikDocument
	{
public:
	CPackagerDocument(CEikApplication& aApp): CEikDocument(aApp) { }
private: // from CEikDocument
	CEikAppUi* CreateAppUiL();
private: // from CApaDocument
	void StoreL(CStreamStore& aStore,CStreamDictionary& aStreamDic) const;
	void RestoreL(const CStreamStore& aStore,const CStreamDictionary& aStreamDic);
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
		}
    void ConstructL();
	~CPackagerAppUi();
	RMessageServ*		serv;
	void SetFromString(const TDesC& aString, const TText8* aString1, TInt	aLineNumber);
	void SetErrorFromString(const TDesC& aString, const TText8* aString1, TInt	aLineNumber, TInt aErr);

private: // from CEikAppUi
    void HandleCommandL(TInt aCommand);
private: // internal functions
	void RunTestStepL(TInt aNumStep);
 };


void CPackagerAppUi::ConstructL()
    {
	CTestAppUi::ConstructL();

	serv = new RMessageServ;
	TInt theRes = serv->Connect();
	if(theRes != KErrNone)
		{
		delete serv;
		serv = NULL;
		}
	
	AutoTestManager().StartAutoTest();
    }

CPackagerAppUi::~CPackagerAppUi()
	{
	if(serv)
		{
		serv->Stop();	
		serv->Close();
		}
	delete serv;
	}

void CPackagerAppUi::HandleCommandL(TInt aCommand)
    {
	switch (aCommand)
		{
	case EEikCmdExit:
		Exit();
		break;
		
	default:
		break;	
		}
    }

void CPackagerAppUi::SetFromString(const TDesC& aString, const TText8* aString1, TInt	aLineNumber)
	{
	if(serv)
		{
		serv->SetFromString(aString, aString1, aLineNumber);
		}
	}

void CPackagerAppUi::SetErrorFromString(const TDesC& aString, const TText8* aString1, 
										TInt	aLineNumber, TInt aErr)
	{
	if(serv)
		{
		serv->SetErrorFromString(aString, aString1, aLineNumber, aErr);
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
			RDebug::Print(_L("\nGet the language"));
			buf.Copy(_L("\nGet the language"));
			SetFromString(buf, ((TText8*)__FILE__), __LINE__);
			TLanguage appLang = ApplicationLanguageL();
			buf.Copy(_L("\nLanguage is "));
			buf.AppendNum(appLang);
			SetFromString(buf, ((TText8*)__FILE__), __LINE__);
			
			const TLanguage deviceLanguage = User::Language();
			
			if( deviceLanguage != appLang )
				{
				buf.Format( _L("\nLanguage is %d but should be %d the device's language "), appLang, deviceLanguage );
				SetErrorFromString(buf, ((TText8*)__FILE__), __LINE__, 1);
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

//
// CPackagerDocument - implementation
//

CEikAppUi* CPackagerDocument::CreateAppUiL()
	{
    return(new(ELeave) CPackagerAppUi);
	}

void CPackagerDocument::StoreL(CStreamStore& /*aStore*/, CStreamDictionary& /*aStreamDic*/) const
	{
	}

void CPackagerDocument::RestoreL(const CStreamStore& /*aStore*/,const CStreamDictionary& /*StreamDic*/)
	{
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
	return(KUidAppLanguageSCApp);
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
	return(new CPackagerApplication);
	}

GLDEF_C TInt E32Main()
	{
	return EikStart::RunApplication(NewApplication);
	}




