/*
* Copyright (c) 2002 Nokia Corporation and/or its subsidiary(-ies).
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
*  Global behaviour for MAknQueryValue objects
*
*/


#include "AknQueryValue.h"
#include "AknPanic.h"

//-------------------------------------------------
// class CAknQueryValue
//-------------------------------------------------

EXPORT_C void MAknQueryValue::Reserved_MAknQueryValue()
	{
	};

EXPORT_C void CAknQueryValue::SetQueryMode(MAknQueryValue::TMode aMode)
	{
	switch (aMode )
		{
		case EQueryMode:
		iFlags.Clear( ESettingPageModeBitIndex );
		break;

		case ESettingPageMode:
		iFlags.Set( ESettingPageModeBitIndex );
		break;

		default:
		Panic( EAknPanicQueryValueInvalidMode );
		break;
		}
	}

EXPORT_C void CAknQueryValue::SetSettingPageResourceIds( TInt aSettingPageResourceId, TInt aSettingPageEditorResourceId )
	{
	iSettingPageResourceId = aSettingPageResourceId;
	iSettingPageEditorResourceId = aSettingPageEditorResourceId;
	}

EXPORT_C void CAknQueryValue::SetAutoAppend( TBool aAppend )
	{
	iFlags.Assign(EAutoAppendBitIndex, aAppend);
	}

EXPORT_C void CAknQueryValue::AppendValueIfNewL()
	{
	}

EXPORT_C void CAknQueryValue::Reserved_MAknQueryValue()
	{
	};


// End of File
