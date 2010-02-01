/*
* Copyright (c) 2002 Nokia Corporation and/or its subsidiary(-ies).
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

// AKNINIT.CPP
//
// Copyright (c) 1997-2001 Symbian Ltd.  All rights reserved.
//

#include "akninit.h"
#include "AknLib.h"
#include <avkon.rsg>
#include <aknenv.h>
#include "AKNINIT.HRH"
#include <ecom/implementationproxy.h>
#include "EIKCDFTY.H"
#include <eikcolib.h>
#include <eikctlib.h>
#include "EIKDLIB.H"
#include "EIKCDLIB.H"

#ifdef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <uikon/eikenvinterface.h>
#endif


// Static DLL functions
#ifndef EKA2
GLDEF_C TInt E32Dll(TDllReason /*aReason*/)
	{
	return(KErrNone);
	}
#endif

GLDEF_C void Panic(TAknPanic aPanic)
	{
	_LIT(KPanicCat,"AKNINIT");
	User::Panic(KPanicCat,aPanic);
	}

CEikLibrary* NewLibraryL()
/**
@publishedPartner
@test
*/
	{
	CAknDllInitializer* initDlls = new (ELeave) CAknDllInitializer();

	return initDlls;
	}
CAknDllInitializer::CAknDllInitializer()
	{
	}

CAknDllInitializer::~CAknDllInitializer()
	{
	delete iCDlgDialogFactory;
	delete iAppUiFactory;
	}

void CAknDllInitializer::InitializeL()
// Creates concrete classes for abstract placeholders in EikonEnv
	{
	CEikonEnv* eikEnv = CEikonEnv::Static();
	iAppUiFactory = new(ELeave) CEikAppUiFactory();
	eikEnv->SetAppUiFactoryL(iAppUiFactory);
	CEikButtonGroupFactoryArray::AppendFactoryFunctionL(CEikCoCtlLibrary::ButtonGroupFactory());
	// Avkon status pane resource
	eikEnv->SetStatusPaneCoreResId(R_AVKON_STATUS_PANE);
	// AknEnv construction is done in eikenv
	// CDlg Dll has private initialisation
	CEikCDlgLibrary::InitializeL();
	// Ctl Dll has private initialisation
	CEikCtlLibrary::InitializeL();
	// Create the each DLLs dialog factories for the text editors
	iCDlgDialogFactory = CEikCDlgDialogFactory::NewL();
	eikEnv->SetCDlgDialogFactory(iCDlgDialogFactory);
	eikEnv->RootWin().EnableModifierChangedEvents(EModifierCapsLock, EEventControlAlways);
	CEikButtonGroupFactoryArray::AppendFactoryFunctionL(CEikCtlLibrary::ButtonGroupFactory());
	}

CArrayFix<TFileName>* CAknDllInitializer::ResourceFileArrayL() const
// Build array by asking each Dll for its resource file
// Keep stack usage low by splitting into individual methods
	{
	CArrayFix<TFileName>* resFileArray = new(ELeave) CArrayFixFlat<TFileName>(8);
	CleanupStack::PushL(resFileArray);
	
	AppendCoCtlResourcFileL(*resFileArray);
	AppendAvkonResourceFileL(*resFileArray);
	AppendAvkonPrivateResourceFileL(*resFileArray);
	AppendCtlResourcFileL(*resFileArray);
	AppendCDlgResourcFileL(*resFileArray);
	
	CleanupStack::Pop(); // resFileArray
	return resFileArray;
	}

CArrayFix<TCreateByTypeFunction>* CAknDllInitializer::ControlFactoryArrayL() const
	{
	CArrayFix<TCreateByTypeFunction>* ctrlFactoryArray = new(ELeave) CArrayFixFlat<TCreateByTypeFunction>(8);
	CleanupStack::PushL(ctrlFactoryArray);

	// Build array by asking each Dll for its control factory function
	ctrlFactoryArray->AppendL(CEikCoCtlLibrary::ControlFactory());
	ctrlFactoryArray->AppendL(CAknLibrary::ControlFactory());
	ctrlFactoryArray->AppendL(CEikCtlLibrary::ControlFactory());
	ctrlFactoryArray->AppendL(CEikDlgLibrary::ControlFactory());
	ctrlFactoryArray->AppendL(CEikCDlgLibrary::ControlFactory());

	CleanupStack::Pop(); // ctrlFactoryArray
	return ctrlFactoryArray;
	}

void CAknDllInitializer::AppendCoCtlResourcFileL(CArrayFix<TFileName>& aResFileArray) const
	{
	aResFileArray.AppendL(CEikCoCtlLibrary::ResourceFile());
	}

void CAknDllInitializer::AppendAvkonResourceFileL(CArrayFix<TFileName>& aResFileArray) const
	{
	aResFileArray.AppendL(CAknLibrary::ResourceFile());
	}

void CAknDllInitializer::AppendAvkonPrivateResourceFileL(CArrayFix<TFileName>& aResFileArray) const
	{
	aResFileArray.AppendL(CAknLibrary::PrivateResourceFile());
	}

void CAknDllInitializer::AppendCtlResourcFileL(CArrayFix<TFileName>& aResFileArray) const
	{
	aResFileArray.AppendL(CEikCtlLibrary::ResourceFile());
	}

void CAknDllInitializer::AppendCDlgResourcFileL(CArrayFix<TFileName>& aResFileArray) const
	{
	aResFileArray.AppendL(CEikCDlgLibrary::ResourceFile());
	}

void CAknDllInitializer::PostAppUiInitializeL()
	{
	CEikLibrary::PostAppUiInitializeL();
	}


//Adding ECOM SUPPORT

const TImplementationProxy ImplementationTable[] =
	{
	IMPLEMENTATION_PROXY_ENTRY(KAknInitImplUid, NewLibraryL)
	};

EXPORT_C const TImplementationProxy* ImplementationGroupProxy(TInt& aTableCount)
	{
	aTableCount = sizeof(ImplementationTable) / sizeof(TImplementationProxy) ;
	return ImplementationTable;
	}

// End of File
