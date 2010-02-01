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


#if !defined(__EIKDLIB_H__)
#define __EIKDLIB_H__

#if !defined(__F32FILE_H__)
#include <f32file.h>
#endif

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

#if !defined(__EIKLIBRY_H__)
#include <eiklibry.h>
#endif

/**
 * The CEikDlgLibrary class provides static functions called by CEikDllInitializer
 * for setting EikDlg library resources in Cone and giving access to its controls
 * via ControlFactoryFuncArray() in EikonEnv
 */
class CEikDlgLibrary : public CBase
	{
public:
	IMPORT_C static TFileName				ResourceFile();
	IMPORT_C static TCreateByTypeFunction	ControlFactory();
public:
	static SEikControlInfo CreateByTypeL(TInt aControlId);
private:
	CEikDlgLibrary();
	};

#endif
