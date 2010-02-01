// Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
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
 @test 
 @internalComponent - Internal Symbian test code 
*/

#if !defined(__TERRMSGAPP_H__)
#define __TERRMSGAPP_H__

#include <eikstart.h> 
#include <eikenv.h>
#include <eikappui.h>
#include <eikapp.h>
#include <eikdoc.h>


/*UI
*/
class CErrMsgTestAppUi : public CEikAppUi
    {
public:
    void ConstructL();
    void ExecuteCmdLineL();
	~CErrMsgTestAppUi();

private:
    // Inherirted from class CEikAppUi
	void HandleCommandL(TInt aCommand);

	// From CCoeAppUi
	void HandleSystemEventL(const TWsEvent& aEvent);

private:
//	CCoeControl* iAppView;
//	CApaCommandLine* iCmdLine;
	};

/*Doc
*/
class CErrMsgTestDocument : public CEikDocument
	{
public:
	static CErrMsgTestDocument* NewL(CEikApplication& aApp);
	CErrMsgTestDocument(CEikApplication& aApp);
	void ConstructL();
private: 
	           // Inherited from CEikDocument
	CEikAppUi* CreateAppUiL();
	};

/*App
*/
class CErrMsgTestApp : public CEikApplication
	{
private: 
	           // Inherited from class CApaApplication
	CApaDocument* CreateDocumentL();
	TUid AppDllUid() const;
private:
	TFileName ResourceFileName() const;
private:
	CApaDocument* CreateDocumentL(CApaProcess* a) { return CEikApplication::CreateDocumentL(a); }
	//
	};
	
#endif
