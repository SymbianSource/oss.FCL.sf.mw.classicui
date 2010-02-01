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

inline void CGridPrinter::SetRealPrintingDeviceMap(const MGraphicsDeviceMap* aGraphicsDeviceMap)
/** Supplies the object that deals with the mapping between twips and device-specific 
units for a specific printer.

@param aGraphicsDeviceMap The interface object for mapping between twips and 
device-specific units. */
	{
	iGraphicsDeviceMap=aGraphicsDeviceMap;
	}

inline CGridLay& CGridPrinter::GridLay()
/** Gets the grid layout used by this printing object.

Note that this is not the same object passed to CGridPrinter::NewL(). Internally, 
the class creates its own CGridLay object from the information supplied in the 
CGridLay object passed to CGridPrinter::NewL().

@return The grid layout object. */
	{
	return *iGridLay;
	}
