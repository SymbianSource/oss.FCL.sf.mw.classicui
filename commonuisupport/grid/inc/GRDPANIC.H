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
// Panics used in GRID
// 
//

#if !defined(__GRDPANIC_H__)
#define __GRDPANIC_H__

enum TGridPanic
	{
	EGridImgInvalidGC,
	ECellRegionNothingSelected,
	ECellRegionInvalidIndex,
	EGridLayInvalidGridImg,
	EGridLayNoTitles,
	EGridLayNotPaginated,
	EGridLayNoPageSizeSet,
	EGridLayPageMapAlreadyExists,
	EGridTableInvalidRequestRow,
	EGridNullGraphicsDeviceMap,
	EGridMapDefaultValueIsZero
	};

GLREF_C void Panic(TGridPanic aPanic);


#endif
