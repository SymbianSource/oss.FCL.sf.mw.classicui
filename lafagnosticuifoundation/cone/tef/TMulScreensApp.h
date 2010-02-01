// Copyright (c) 2007-2009 Nokia Corporation and/or its subsidiary(-ies).
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


#if !defined(__TMULCREENSAPP_H__)
#define __TMULCREENSAPP_H__

#include <eikstart.h> 
#include <eikenv.h>
#include <eikappui.h>
#include <eikapp.h>
#include <eikdoc.h>


/*
	----- CMulScreensTestAppUi
**/
class CMulScreensTestAppUi : public CEikAppUi
    {
	public:
	    void ConstructL();
		~CMulScreensTestAppUi();

	private:
	    // Inherirted from class CEikAppUi
		void HandleCommandL(TInt aCommand);
		TBool ProcessCommandParametersL(CApaCommandLine& aCommandLine);
		// From CCoeAppUi
		void HandleSystemEventL(const TWsEvent& aEvent);
	};


/*
	----- CMulScreensTestDocument
**/
class CMulScreensTestDocument : public CEikDocument
	{
	public:
		static CMulScreensTestDocument* NewL(CEikApplication& aApp);
		CMulScreensTestDocument(CEikApplication& aApp);
		void ConstructL();
	private: 
	    // Inherited from CEikDocument
		CEikAppUi* CreateAppUiL();
	};



/*
	----- CMulScreensTestApp
**/
class CMulScreensTestApp : public CEikApplication
	{
	private: 
		// Inherited from class CApaApplication
		CApaDocument* CreateDocumentL();
		TUid AppDllUid() const;
	private:
		TFileName ResourceFileName() const;
	private:
		CApaDocument* CreateDocumentL(CApaProcess* a) { return CEikApplication::CreateDocumentL(a); }
	};
	
#endif
