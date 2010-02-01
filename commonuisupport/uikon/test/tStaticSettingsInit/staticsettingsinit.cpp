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

#include <coecntrl.h>
#include <coecntss.h>
#include <eiklibry.h>
#include <ecom/ecom.h>
#include <ecom/implementationproxy.h>

#include "appfwk_test_utils.h"

#include "Staticsettingsinit.hrh"




class CStaticSettingsInit : public CEikLibrary2
	{
	public:
		~CStaticSettingsInit();
		
	private:	// from CEikLibrary
		void InitializeL();
		CArrayFix<TFileName>* ResourceFileArrayL() const {return 0;};
		CArrayFix<TCreateByTypeFunction>* ControlFactoryArrayL() const {return 0;}
	};

CStaticSettingsInit::~CStaticSettingsInit()
	{
	}
	
void CStaticSettingsInit::InitializeL()
	{
	// Whether we set the default focus/default parent to ETrue or EFalse
	// depends on the presence of certain files on the C: drive
	RSmlTestUtils utils;
	User::LeaveIfError(utils.Connect());
	CleanupClosePushL(utils);

	_LIT(KFileFocus, "c:\\focus.txt");
	_LIT(KFileParent, "c:\\parent.txt");
	
	TBool focusPresent = EFalse;
	TBool parentPresent = EFalse;
	
	utils.IsFilePresent(KFileFocus, focusPresent);
	utils.IsFilePresent(KFileParent, parentPresent);

	CleanupStack::PopAndDestroy(&utils);
		
	// If the focus file exists the default will be non focusing
	CCoeControlStaticSettings::SetFocusedByDefaultL(!focusPresent);
	
	// If the parent file exits, the default will be to set the parent
	CCoeControlStaticSettings::SetParentByDefaultL(parentPresent);
	}

CEikLibrary* NewLibraryL()
	{
	CStaticSettingsInit* initDlls = new (ELeave) CStaticSettingsInit();

	return initDlls;
	}

//Adding ECOM SUPPORT

const TImplementationProxy ImplementationTable[] =
	{
	IMPLEMENTATION_PROXY_ENTRY(KStaticSettImplUid, NewLibraryL)
	};

EXPORT_C const TImplementationProxy* ImplementationGroupProxy(TInt& aTableCount)
	{
	aTableCount = sizeof(ImplementationTable) / sizeof(TImplementationProxy) ;
	return ImplementationTable;
	}
