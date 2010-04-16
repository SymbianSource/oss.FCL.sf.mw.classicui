/*
* Copyright (c) 2002-2004 Nokia Corporation and/or its subsidiary(-ies). 
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









#ifndef __FINDUTILBASE_H__
#define __FINDUTILBASE_H__

#include <e32base.h>
#include "FindUtil.h"

class CFindUtilBase : public CBase, public MFindUtil
	{
public:

    inline CFindUtilBase() {}
    inline ~CFindUtilBase() {}

	IMPORT_C virtual void OpenL();
	IMPORT_C virtual void Close();
protected:
	TInt iReferenceCount;
	};

#endif
