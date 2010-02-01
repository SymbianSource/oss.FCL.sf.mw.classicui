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
// AppLaunchTest
// The purpose of this app is to test the changes made to apparc and
// aiftool to allow different screen sizes.  The checkbox at
// the top of the window can be ticked to see flip closed apps and
// unticked to see flip open apps, represented here using screen mode 0
// for flip open views and screen mode 1 for flip closed views.  The
// columns of the table are abbreviated as follows:
// H   - Hidden
// NH  - Not Hidden
// E   - Embeddable
// NE  - Not Embeddable
// FO  - Has views for Flip Open
// NFO - Does Not have views for Flip Open
// FC  - Has views for Flip Closed
// NFC - Does Not have views for Flip Closed
// Exit the program using Ctrl-E or the menu.
// 
//

/**
 @file
 @internalComponent - Internal Symbian test code 
*/

 
#include "altapp.h" 
#include "altglobal.h"
#include "altdoc.h"
#include <eikstart.h>


CAltApp::~CAltApp()
	{}

CAltApp::CAltApp()
	{}

TUid CAltApp::AppDllUid() const
	{
	return KUidAltApp;			 
	}

CApaDocument* CAltApp::CreateDocumentL()
	{
	return new(ELeave) CAltDocument(*this);	   
	}


//#ifdef __UI_FRAMEWORKS_V2__



	LOCAL_C CApaApplication* NewApplication()
		{
		return (new CAltApp);
		}

	GLDEF_C TInt E32Main()
		{
		return EikStart::RunApplication(NewApplication);
		}

