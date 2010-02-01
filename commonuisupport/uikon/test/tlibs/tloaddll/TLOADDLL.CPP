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
#include <techview/eiklabel.h>
#include "contentmgr.h"
#include "TLOADDLL.H"

// Static DLL functions
GLDEF_C TInt E32Dll(
					)
	{
	return(KErrNone);
	}

//
//
// CTestEikonDllLoading
//
//
CTestEikonDllLoading::CTestEikonDllLoading()
	{
	}

//
//
// ~CTestEikonDllLoading
//
//
CTestEikonDllLoading::~CTestEikonDllLoading()
	{
	delete iContentManager;
	}

//
//
// NewL
//
//
EXPORT_C const CTestEikonDllLoading* CTestEikonDllLoading::NewL()
	{
	CTestEikonDllLoading* testDll=new(ELeave) CTestEikonDllLoading();

	return testDll;
	}

//
//
// InitialiseL
//
//
void CTestEikonDllLoading::InitializeL()
	{
	CEikonEnv* env=CEikonEnv::Static();
	iContentManager=CEikTestContentManager::NewL(env->FsSession());
	env->AddPictureFactoryL(*iContentManager);
	}

//
//
// ResourceFileArray
//
//
CArrayFix<TFileName>* CTestEikonDllLoading::ResourceFileArrayL() const
	{
	CArrayFix<TFileName>* resFileArray = new(ELeave) CArrayFixFlat<TFileName>(1);
	CleanupStack::PushL(resFileArray);
	
	resFileArray->AppendL(ResourceFile());
	
	CleanupStack::Pop(); // resFileArray
	return resFileArray;
	}

//
//
// ControlFactoryArray
//
//
CArrayFix<TCreateByTypeFunction>* CTestEikonDllLoading::ControlFactoryArrayL() const
	{
	CArrayFix<TCreateByTypeFunction>* ctrlFactoryArray = new(ELeave) CArrayFixFlat<TCreateByTypeFunction>(1);
	CleanupStack::PushL(ctrlFactoryArray);

	ctrlFactoryArray->AppendL(STATIC_CAST(TCreateByTypeFunction, CreateByTypeL));

	CleanupStack::Pop(); // ctrlFactoryArray
	return ctrlFactoryArray;
	}

//
//
// ResourceFile
//
//
TFileName CTestEikonDllLoading::ResourceFile() const
	{
	_LIT(KResFileName,"z:\\system\\test\\taddlib\\external.rsc");
	TFileName resourceFile=KResFileName();
	return resourceFile;
	}

//
//
// CreateByTypeL
//
//
SEikControlInfo CTestEikonDllLoading::CreateByTypeL(TInt aControlType)
	{	
	SEikControlInfo controlInfo;
	controlInfo.iControl = NULL;
	controlInfo.iTrailerTextId = 0;
	controlInfo.iFlags = 0;

    switch (aControlType)
        {
    case CTestEikDllLoadedLabel::ECtTestEikDllLoadedLabel:
		controlInfo.iControl = new(ELeave) CTestEikDllLoadedLabel;
		break;
		}
	return controlInfo;
	}

//
//
// CTestEikDllLoadedLabel::Draw
//
//
void CTestEikDllLoadedLabel::Draw(const TRect& aRect) const
	{
	CWindowGc& gc=SystemGc();
	gc.SetPenColor(KRgbBlack);
	CEikLabel::Draw(aRect);
	}

//
// END OF FILE
//
