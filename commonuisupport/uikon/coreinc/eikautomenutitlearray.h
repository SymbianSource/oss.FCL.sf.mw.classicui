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

#ifndef EIKAUTOMENUTITLEARRAY_H
#define EIKAUTOMENUTITLEARRAY_H

#include "eikamnt.h"

class CEikAutoMenuTitle;

/** Creates a standard array of CEikAutoMenuTitle objects. 

@publishedPartner 
@released */
NONSHARABLE_CLASS(CEikAutoMenuTitleArray) : public CArrayPtrFlat<CEikAutoMenuTitle>
// If more than one title is specified for the start or end, they will be placed in the same order they appear
// in the array (so the first EStart in the array will be the first on a menu bar also but the last EEnd will
// be the last).
	{
public:
	CEikAutoMenuTitleArray();
	~CEikAutoMenuTitleArray();
	};

#endif	// EIKAUTOMENUTITLEARRAY_H
