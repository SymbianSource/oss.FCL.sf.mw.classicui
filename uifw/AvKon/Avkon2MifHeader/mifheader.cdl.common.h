/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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

// This file was automatically generated from \epoc32\include\oem\mifheader.cdl.
// It contains common definitions for the client and customisation API.
// It should not be modified manually.

#ifndef MIFHEADER_CDL_COMMON_H
#define MIFHEADER_CDL_COMMON_H


// from AknIconLoader.h
// In MIF file version 2+, bitmap icons are identified in the bitmap offset array
// with iOffset being <=0. In that case, -iOffset means the corresponding MBM ID,
// which can be used for CFbsBitmap::Load.

struct TMifBitmapOffsetElement
    {
    TInt32 iOffset; // pointer to icon. icon = header + data.
    TInt32 iLength; // combined length of TMifIconHeader and its data.
    };


namespace MifHeader
{
#include "mifheader.cdl.common.hrh"

// These constants are defined by the CDL interface: MifHeader
_LIT(KCdlName, "MifHeader");
const TInt KCdlInterfaceUidValue = _CDL_MifHeader_KCdlInterfaceUidValue;
const TUid KCdlInterfaceUid = { KCdlInterfaceUidValue };
const TInt KCdlInterfaceMajorVersion = 1;
const TInt KCdlInterfaceMinorVersion = 0;
const TUint KCdlInterfaceFlags = 0;

// These are the API ids used in this interface.
enum TApiId
	{
	EApiId_indicies,
	E_TApiId_TableSize
	};

// This is the CDL interface definition for this interface
const SCdlInterface KCdlInterface =
	{
	KCdlCompilerMajorVersion,
	KCdlCompilerMinorVersion,
	LIT_AS_DESC_PTR(KCdlName),
	{ KCdlInterfaceUidValue },
	KCdlInterfaceMajorVersion,
	KCdlInterfaceMinorVersion,
	KCdlInterfaceFlags,
	E_TApiId_TableSize
	};

// These typedefs define the types for function APIs
// TCdlArray<TMifBitmapOffsetElement> indicies 	does not need a typedef

} // end of namespace MifHeader

#endif // MIFHEADER_CDL_COMMON_H
