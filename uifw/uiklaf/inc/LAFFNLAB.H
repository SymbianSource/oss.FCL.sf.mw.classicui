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


#ifndef __LAFFNLAB_H__
#define __LAFFNLAB_H__

#include <e32std.h>
#include <gulbordr.h>

class CCoeControl;
class MLafEnv;

/**
 * @internal
 * Do not use
 */
class LafFileNameLabel
	{
public:
	IMPORT_C static void GetDefaultBorder(TGulBorder& aBorder);
	IMPORT_C static void GetBorderColors(TGulBorder::TColors& aBorderColors,const MLafEnv& aEnv,const CCoeControl& aMatchedControl);
	};

#endif
