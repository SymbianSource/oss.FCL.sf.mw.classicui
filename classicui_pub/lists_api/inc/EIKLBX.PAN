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


#if !defined(__EIKLBX_PAN__)
#define __EIKLBX_PAN__

enum TEikListBoxPanic
	{
	EEikPanicListBoxNoMatchTextArray,
	EEikPanicListBoxNoMatchBuffer,
	EEikPanicListBoxNoModel,
	EEikPanicListBoxNoView,
	EEikPanicListBoxInvalidTopItemIndexSpecified,
	EEikPanicListBoxInvalidCurrentItemIndexSpecified,
	EEikPanicListBoxInvalidItemIndexSpecified,
	EEikPanicListBoxInvalidModelSpecified,
	EEikPanicListBoxInvalidItemDrawerSpecified,
	EEikPanicListBoxInvalidFlagsSpecified,
	EEikPanicListBoxInvalidItemHeightSpecified,	
	EEikPanicListBoxInvalidItemFontSpecified,	
	EEikPanicListBoxCalledFuncNotValidForSingleSelectionLBX,
	EEikPanicListBoxNoSelIndexArray,
	EEikPanicListBoxInvalidSelIndexArraySpecified,
	EEikPanicListBoxInvalidRowIndexSpecified,
	EEikPanicListBoxInvalidColIndexSpecified,
	EEikPanicListBoxInvalidColumnWidthSpecified,
	EEikPanicListBoxInvalidGcSpecified,
	EEikPanicListBoxInvalidFontSpecified,
	EEikPanicListBoxNoGc,
	EEikPanicListBoxNoFont,
	EEikPanicListBoxNoHierArray,
	EEikPanicListBoxItemIsNull
	};

GLREF_C void Panic(TEikListBoxPanic aPanic);

#endif
