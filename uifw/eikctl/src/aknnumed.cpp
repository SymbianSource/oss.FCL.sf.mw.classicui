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
*		Intermediate class for defining data shared between numeric edwins    
*     
*
*/


#include <aknnumed.h>
#include <aknenv.h>
#include <AknSettingCache.h>
#include <numberconversion.h>

#include <AknTasHook.h>
EXPORT_C void CAknNumericEdwin::Reserved_3()
	{}



EXPORT_C void CAknNumericEdwin::MapKeyEvent(TKeyEvent& aKeyEvent,TEventCode& /*aType*/, TDigitType aDigitType) const
/**
Maps a key event so that any numeric character is mapped to the correct digit type that this editor is using.
@since 2.0
@param aKeyEvent the key event to modify
@param aType the type to modify
@param aDigitType the digit type to map all numeric characters to.
*/
	{
	TChar ch(aKeyEvent.iCode);
	TBuf<1> numbuf;
	numbuf.Append(ch);
	NumberConversion::ConvertDigits(numbuf, aDigitType);
	
	// In case ConvertDigits didn't find anything sensible to
	// put in numbuf, but still deleted its content.
	if ( numbuf.Length() > 0 )
	    {
	    aKeyEvent.iCode = numbuf[0];
	    }
	}

EXPORT_C CAknNumericEdwin::~CAknNumericEdwin()
    {
    AKNTASHOOK_REMOVE();
    }

EXPORT_C void CAknNumericEdwin::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CEikEdwin::HandlePointerEventL(aPointerEvent); 
    }

EXPORT_C void* CAknNumericEdwin::ExtensionInterface( TUid /*aInterface*/ )
    {
    return NULL;
    }
