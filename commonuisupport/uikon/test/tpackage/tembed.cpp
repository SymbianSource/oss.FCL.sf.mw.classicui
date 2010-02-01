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

#include <ecom/ecom.h>
#include <ecom/implementationproxy.h>

#include <tembed.rsg>
#include "tembed.hrh"

#include "TEMBED.h"

//
// CPackagerModel
//

const TUid KUidEmbedApp={519};

void CViewControl::FocusChanged(TDrawNow /*aDrawNow*/)
    {
    }
    
void CViewControl::ConstructL(const TRect& aRect)
    {
	CreateWindowL();
    Window().SetShadowDisabled(ETrue);
	EnableDragEvents();
	iBrushStyle=CGraphicsContext::ESolidBrush;
	//iBrushColor=KRgb1in4DitheredGray;
    iContext=this;
	Window().SetBackgroundColor(KRgb1in4DitheredGray);
    SetRect(aRect);
    TFontSpec spec(_L("Arial"),240);
    iFont=iCoeEnv->CreateScreenFontL(spec);
	
	ActivateL();
    }

CViewControl::~CViewControl()
	{
    iCoeEnv->ReleaseScreenFont(iFont);
	}

void CViewControl::Draw(const TRect& aRect) const
    {
	CGraphicsContext& gc=SystemGc();
	//gc.SetPenStyle(CGraphicsContext::ENullPen);
	gc.DrawRect(aRect);
	gc.UseFont(iFont);
	
	CEikAppUi *theApplication = (CEikAppUi*) (iCoeEnv->AppUi());
	CDocument*	pDoc = (CDocument*)(theApplication->Document());

	gc.DrawText(pDoc->iBuf, TPoint(10, 100));
    }

void CViewControl::SizeChanged()
    {
    }

TKeyResponse CViewControl::OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)
    {
    if(aType!=EEventKey)
		return(EKeyWasConsumed);
	
	CEikAppUi *theApplication = (CEikAppUi*) (iCoeEnv->AppUi());
	CDocument*	pDoc = (CDocument*)(theApplication->Document());
	
	switch(aKeyEvent.iCode)
		{
		case EKeyBackspace:
			{
			if(pDoc->iBuf.Length() > 0)
				pDoc->iBuf.Delete(pDoc->iBuf.Length()-1 , 1);
			}
		break;
		default:
			pDoc->iBuf.Append(aKeyEvent.iCode);
			break;
		}
	
	
	DrawNow();
	
	return(EKeyWasConsumed);
    }

//
// CTestEmbedAppUi
//

class CTestEmbedAppUi : public CEikAppUi
    {
public:
    void ConstructL();
	~CTestEmbedAppUi();
private: // from CEikAppUi
    void HandleCommandL(TInt aCommand);
private: // internal functions
	TInt SelectDocumentL(TInt aHelpRid,TInt aTitleRid);
	void SendKeyEventToApplication(TKeyEvent	theKeyEvent);
private:
    CViewControl* iContainer;
    };


void CTestEmbedAppUi::ConstructL()
    {
    BaseConstructL();
    
	iContainer=new(ELeave) CViewControl;
    iContainer->ConstructL(ClientRect());
    AddToStackL(iContainer);
    }

CTestEmbedAppUi::~CTestEmbedAppUi()
	{
	if(iContainer)
		RemoveFromStack(iContainer);
    delete iContainer;

	}

void CTestEmbedAppUi::HandleCommandL(TInt aCommand)
    {
	switch (aCommand)
		{
	case EEikCmdExit:
		SaveAnyChangesL();
        Exit();
		break;
		}
    }


CEikAppUi* CDocument::CreateAppUiL()
	{
    return(new(ELeave) CTestEmbedAppUi);
	}


//
// CEmbedApplication
//

class CEmbedApplication : public CEikApplication
	{
private: // from CApaApplication
	CApaDocument* CreateDocumentL();
	TUid AppDllUid() const;
private:
	CApaDocument* CreateDocumentL(CApaProcess* a) { return CEikApplication::CreateDocumentL(a); }
	};

TUid CEmbedApplication::AppDllUid() const
	{
	return(KUidEmbedApp);
	}

CApaDocument* CEmbedApplication::CreateDocumentL()
	{
	return new(ELeave) CDocument(*this);
	}

//
// EXPORTed functions
//



GLDEF_C TInt E32Dll(
					)
	{
	return KErrNone;
	}

LOCAL_C CApaApplication* NewApplication()
	{
	return new CEmbedApplication;
	}

LOCAL_D const TImplementationProxy ImplementationTable[]=
	{
	IMPLEMENTATION_PROXY_ENTRY(519, NewApplication)
	};

EXPORT_C const TImplementationProxy* ImplementationGroupProxy(TInt& aTableCount)
	{
	aTableCount=sizeof(ImplementationTable)/sizeof(ImplementationTable[0]);
	return ImplementationTable;
	}

