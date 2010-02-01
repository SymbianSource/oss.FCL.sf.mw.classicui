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


#ifndef __LAFLBV_H__
#define __LAFLBV_H__

#include <e32std.h>

/**
 * @internal
 * Do not use
 */
class LafListBoxView
	{
public:
	IMPORT_C static TInt ItemWidth(TInt aViewRectWidth, TInt aDataWidth);
	};

#endif //#ifndef __LAFLBV_H__
