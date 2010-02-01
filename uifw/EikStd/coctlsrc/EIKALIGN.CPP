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


#include <eikalign.h>

EXPORT_C CEikAlignedControl::CEikAlignedControl()
	{}

EXPORT_C CEikAlignedControl::~CEikAlignedControl()
	{}

EXPORT_C void CEikAlignedControl::SetAllMarginsTo(TInt aValue)
	{
	iMargin.SetAllValuesTo(aValue);
	}

EXPORT_C void CEikAlignedControl::SetAlignment(TGulAlignmentValue aAlign)
	{
	iAlignment=aAlign;
	}

/**
 * Writes the internal state of the control and its components to aStream.
 * Does nothing in release mode.
 * Designed to be overidden and base called by subclasses.
 *
 * @internal
 * @since App-Framework_6.1
 */
#ifndef _DEBUG
EXPORT_C void CEikAlignedControl::WriteInternalStateL(RWriteStream&) const
	{}
#else
EXPORT_C void CEikAlignedControl::WriteInternalStateL(RWriteStream& aWriteStream) const
	{
	_LIT(KEikLitAlignCtlSt,"<CEikAlignedControl>");
	_LIT(KEikLitAlignCtlEnd,"<\\CEikAlignedControl>");
	_LIT(KEikLitAlignCtlMargins,"<iMargin>");
	_LIT(KEikLitAlignCtlMarginsEnd,"<\\iMargin>");
	_LIT(KEikLitAlignCtlAlign,"<iAlignment>");
	_LIT(KEikLitAlignCtlAlignEnd,"<\\iAlignment>");

	aWriteStream << KEikLitAlignCtlSt;
	aWriteStream << KEikLitAlignCtlMargins;
	aWriteStream.WriteInt8L(iMargin.iLeft);
	aWriteStream.WriteInt8L(iMargin.iRight);
	aWriteStream.WriteInt8L(iMargin.iTop);
	aWriteStream.WriteInt8L(iMargin.iBottom);
	aWriteStream << KEikLitAlignCtlMarginsEnd;
	aWriteStream << KEikLitAlignCtlAlign;
	aWriteStream.WriteInt32L((TInt)iAlignment);
	aWriteStream << KEikLitAlignCtlAlignEnd;
	CCoeControl::WriteInternalStateL(aWriteStream);
	aWriteStream << KEikLitAlignCtlEnd;
	}
#endif

EXPORT_C void CEikAlignedControl::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CAknControl::HandlePointerEventL(aPointerEvent); 
    }

EXPORT_C void* CEikAlignedControl::ExtensionInterface( TUid /*aInterface*/ )
    {
    return NULL;
    }
