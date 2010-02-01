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


#ifndef __LAFAKNBORDERS_H__
#define __LAFAKNBORDERS_H__

#include <uiklaf/private/lafenv.h>

class LafAknBorders
	{
public:
	static void DrawLogicalBorder(const TGulBorder& aBorder,CGraphicsContext& aGc,const TRect& aRect,const TGulBorder::TColors& aBorderColors);
	static TMargins LogicalBorderMargins(const TGulBorder& aBorder);
	};



#endif //__LAFAKNBORDERS_H__
