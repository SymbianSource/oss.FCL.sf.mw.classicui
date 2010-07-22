// Copyright (c) 1997-2009 Nokia Corporation and/or its subsidiary(-ies).
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

#include <eikfctry.h>
#include <eikenv.h>
#include "EIKDGFTY.H"

/** Creates the specified type of control by going through the dynamically loaded 
DLLs' Control Factories until one is found which successfully creates the 
desired control.

@param aControlType The ID of the required type of control. 
@return Newly created control. */
EXPORT_C SEikControlInfo EikControlFactory::CreateByTypeL(TInt aControlType)
    {// static
	SEikControlInfo controlInfo;
	controlInfo.iControl = NULL;
	controlInfo.iTrailerTextId = 0;
	controlInfo.iFlags = 0;

	// Go through Control Factories of dynamically-loaded DLLs until one
	// is found which successfully creates the desired control
	CArrayFix<TCreateByTypeFunction>* controlFactoryFuncArray = CEikonEnv::Static()->ControlFactoryFuncArray();
	const TInt count = controlFactoryFuncArray->Count();
	for(TInt i = 0; i < count; i++)
		{
		TCreateByTypeFunction controlFactoryFunc = (*controlFactoryFuncArray)[i];
		controlInfo = (*controlFactoryFunc)(aControlType);
		if(controlInfo.iControl)
			break;
		}
		
	return controlInfo;
    }

//
// MEikCDlgDialogFactory
// 

/** Constructor for MEikCDlgDialogFactory */
EXPORT_C MEikCDlgDialogFactory::MEikCDlgDialogFactory()
	{
	}

/** Reserved for future use */
EXPORT_C void MEikCDlgDialogFactory::MEikCDlgDialogFactory_Reserved1()
	{
	}

/** Reserved for future use */
EXPORT_C void MEikCDlgDialogFactory::MEikCDlgDialogFactory_Reserved2()
	{
	}
	

//
// MEikPrintDialogFactory
// 

/** Constructor for MEikPrintDialogFactory */
EXPORT_C MEikPrintDialogFactory::MEikPrintDialogFactory()
	{
	}
	
/** Reserved for future use */
EXPORT_C void MEikPrintDialogFactory::MEikPrintDialogFactory_Reserved1()
	{
	}

/** Reserved for future use */
EXPORT_C void MEikPrintDialogFactory::MEikPrintDialogFactory_Reserved2()
	{
	}
	

//
// MEikFileDialogFactory
// 

/** Constructor for MEikFileDialogFactory */
EXPORT_C MEikFileDialogFactory::MEikFileDialogFactory()
	{
	}

/** Reserved for future use */	
EXPORT_C void MEikFileDialogFactory::MEikFileDialogFactory_Reserved1()
	{
	}

/** Reserved for future use */
EXPORT_C void MEikFileDialogFactory::MEikFileDialogFactory_Reserved2()
	{
	}

