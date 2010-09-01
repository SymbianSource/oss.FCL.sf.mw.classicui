/*
* Copyright (c) 1997-1999 Nokia Corporation and/or its subsidiary(-ies).
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


#if !defined(__EIKCTLIB_H__)
#define __EIKCTLIB_H__

#if !defined(__F32FILE_H__)
#include <f32file.h>
#endif

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

#if !defined(__EIKLIBRY_H__)
#include <eiklibry.h>
#endif

#if !defined(__EIKBGFTY_H__)
#include <eikbgfty.h>
#endif

/**
 * The CEikCtlLibrary class proovides static functions called by CEikDllInitializer; setting EikCtl
 * library resources in Cone and giving access to its controls via ControlFactoryFuncArray() in EikonEnv
 *
 * @internal
 */
class CEikCtlLibrary : public CBase
	{
public:
	/**
	 * ResourceFile() returns name of the resource file eikctl.rsc
	 */
	IMPORT_C static TFileName ResourceFile();
	/**
	 * ControlFactory provides ability to create controls by id number.
	 */
	IMPORT_C static TCreateByTypeFunction ControlFactory();
	/**
	 * Dll initialization routine
	 */
	IMPORT_C static void InitializeL();
    /**
     * Factory to create buttongroups
     */
	IMPORT_C static TCreateButtonGroupByTypeFunction ButtonGroupFactory();
public:
	static SEikControlInfo CreateByTypeL(TInt aControlId);
	static MEikButtonGroup* CreateButtonGroupByTypeL(TInt aButtonGroupType,EikButtonGroupFactory::TCreationData& aCreationData,TBool& aAddToButtonGroupStack);
private:
	CEikCtlLibrary();
	};

#endif
