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

#if !defined(__AKNLIB_H__)
#define __AKNLIB_H__

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

#if !defined(__EIKLIBRY_H__)
#include <eiklibry.h>
#endif

#if !defined(__AKNPANIC_H__)
#include <AknPanic.h>
#endif

class CAknLibrary : public CBase
	{
public:
	
	IMPORT_C static TFileName				ResourceFile();
	IMPORT_C static TFileName				PrivateResourceFile();
	IMPORT_C static TCreateByTypeFunction	ControlFactory();
public:
	static SEikControlInfo CreateByTypeL(TInt aControlType);
private:
	CAknLibrary();
	};

#endif
