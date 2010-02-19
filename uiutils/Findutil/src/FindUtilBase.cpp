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









#include <e32base.h>
#include "FindUtilBase.h"

// CFindUtilBase implementation

EXPORT_C void CFindUtilBase::OpenL()
	{
	iReferenceCount++;
	}

EXPORT_C void CFindUtilBase::Close()
	{
	iReferenceCount--;
	if (iReferenceCount < 1)
		{
		delete this;
        Dll::SetTls( NULL );
		}
	}

// end of file
