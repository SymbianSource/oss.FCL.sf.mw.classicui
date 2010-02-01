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
// The following test case is used to test the loading of ECom plugin dll and print
// a message on the screen if successfully loaded.
// 
//

/**
 @file
 @internalComponent - Internal Symbian test code
*/

#include <eikenv.h>
#include <ecom/implementationproxy.h>
#include "contentmgr.h"
#include "TLOADDLL.H"
#include "TLoadDllV2.hrh"

/**
   Constructor
 */
CTestEikonEComDllLoading::CTestEikonEComDllLoading()
	{
	}

/**
   Destructor
 */
CTestEikonEComDllLoading::~CTestEikonEComDllLoading()
	{
	delete iContentManager;
	}

/**
   First phase constructor
 */
EXPORT_C const CTestEikonEComDllLoading* CTestEikonEComDllLoading::NewL()
	{
	CTestEikonEComDllLoading* testDll=new(ELeave) CTestEikonEComDllLoading();

	return testDll;
	}

/**
   Auxiliary function for all Test Cases
  
   The method is an override from CEikLibrary2 and 
   Sets up the variables needed by the eikenv.
   
 */
void CTestEikonEComDllLoading::InitializeL()
	{
	CEikonEnv* env=CEikonEnv::Static();
	iContentManager=CEikTestContentManager::NewL(env->FsSession());
	env->AddPictureFactoryL(*iContentManager);
	}

/**
   Auxiliary function for all Test Cases
  
   The method is an override from CEikLibrary2 and 
   Returns the resource file used by this DLL.
   
 */
CArrayFix<TFileName>* CTestEikonEComDllLoading::ResourceFileArrayL() const
	{
	CArrayFix<TFileName>* resFileArray = new(ELeave) CArrayFixFlat<TFileName>(1);
	CleanupStack::PushL(resFileArray);
	
	resFileArray->AppendL(ResourceFile());
	
	CleanupStack::Pop(); // resFileArray
	return resFileArray;
	}

/**
   Auxiliary function for all Test Cases
  
   The method is an override from CEikLibrary2 and 
   Returns DLL's control factory function.
   
 */
CArrayFix<TCreateByTypeFunction>* CTestEikonEComDllLoading::ControlFactoryArrayL() const
	{
	CArrayFix<TCreateByTypeFunction>* ctrlFactoryArray = new(ELeave) CArrayFixFlat<TCreateByTypeFunction>(1);
	CleanupStack::PushL(ctrlFactoryArray);

	ctrlFactoryArray->AppendL(STATIC_CAST(TCreateByTypeFunction, CreateByTypeL));

	CleanupStack::Pop(); // ctrlFactoryArray
	return ctrlFactoryArray;
	}

/**
   Auxiliary function for all Test Cases
  
   Returns resource file name of the DLL.
   
 */
TFileName CTestEikonEComDllLoading::ResourceFile() const
	{
	_LIT(KResFileName,"z:\\system\\test\\taddlib\\external.rsc");
	TFileName resourceFile=KResFileName();
	return resourceFile;
	}

/**
   Auxiliary function for CTestAutoContainer
  
   Creates a control specified by aControlType.
   
 */
SEikControlInfo CTestEikonEComDllLoading::CreateByTypeL(TInt aControlType)
	{	
	SEikControlInfo controlInfo;
	controlInfo.iControl = NULL;
	controlInfo.iTrailerTextId = 0;
	controlInfo.iFlags = 0;

    switch (aControlType)
        {
    case CTestEikDllLoadedLabel::ECtTestEikEComDllLoadedLabel:
		controlInfo.iControl = new(ELeave) CTestEikDllLoadedLabel;
		break;
		}
	return controlInfo;
	}

//Adding ECOM SUPPORT

const TImplementationProxy ImplementationTable[] =
	{
	 IMPLEMENTATION_PROXY_ENTRY(KTLoadDllV2ImplUid,CTestEikonEComDllLoading::NewL)
	};

/**
   Returns a pointer to an array of TImplementationProxy objects containing a UID 
   and a funcion pointer.
  
   @param aTableCount number of items in the array.
   
   @return pointer to an array of TImplementationProxy objects.
 */
EXPORT_C const TImplementationProxy* ImplementationGroupProxy(TInt& aTableCount)
	{
	aTableCount = sizeof(ImplementationTable) / sizeof(TImplementationProxy) ;
	return ImplementationTable;
	}

//
// END OF FILE
//
