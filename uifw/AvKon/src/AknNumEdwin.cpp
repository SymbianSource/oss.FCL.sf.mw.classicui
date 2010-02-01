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
* Description:   Numeric Editor derived from Uikon's CEikEdwin
*
*
*/


// INCLUDES

#include <barsread.h>  // Resource reading

#include <eikon.hrh>
#include <eikctl.rsg>
#include <eikenv.h>

#include "AknNumEdwin.h"
#include "avkon.hrh"
#include "AknDef.h"

#include <aknenv.h>
#include <AknSettingCache.h>
#include <numberconversion.h>
#include <AknUtils.h>

	_LIT(KEmptyText, "" );

// INTERNAL CLASS DEFINITIONS


// CLASS IMPLEMENTATIONS


EXPORT_C CAknIntegerEdwin* CAknIntegerEdwin::NewL( TInt aMin, TInt aMax, TInt aTextLimit )
    {
    CAknIntegerEdwin* self = new ( ELeave ) CAknIntegerEdwin;
    CleanupStack::PushL( self );
    self->ConstructL( aMin, aMax, aTextLimit);
    CleanupStack::Pop();
    return self;
    }

EXPORT_C void CAknIntegerEdwin::ConstructFromResourceL(TResourceReader& aReader)
	{
	const TInt edwinFlags=0; 

	CalculateWidth(20);  // overridden by later layout code

	TInt textLimit = aReader.ReadInt16();
	TInt minValue = aReader.ReadInt32();
	TInt maxValue = aReader.ReadInt32();
	iUnsetValue = aReader.ReadInt32();

// possible extensions
	TInt dummy =  aReader.ReadInt32();
	dummy = aReader.ReadInt32();

	CommonConstructL(minValue, maxValue, textLimit, edwinFlags, iUnsetValue);
	}

EXPORT_C void CAknIntegerEdwin::ConstructL(TInt aMin, TInt aMax, TInt aTextLimit)
	{
	const TInt edwinFlags=0; 

	CommonConstructL(aMin, aMax, aTextLimit, edwinFlags, KMaxTInt);
	}

void CAknIntegerEdwin::CommonConstructL(TInt aMin, TInt aMax, TInt aMaxChars, TInt aFlags, TInt aUnset)
	{
	iDigitType = EDigitTypeWestern;

	const TInt numberOfLines=1;

	// Enforce maximum number of digits for numeric Edwin - Otherwise CEikEdwin treats maxlimit of 0 as no limit.
	TInt maxLimit(aMaxChars);
	if( (maxLimit==0) || (maxLimit>EAknMaxIntegerDigits) )
		maxLimit = EAknMaxIntegerDigits;

	CEikEdwin::ConstructL(aFlags, aMaxChars, maxLimit, numberOfLines);
	SetMinimumIntegerValue(aMin);
	SetMaximumIntegerValue(aMax);

	SetAknEditorCase(EAknEditorUpperCase);
	SetAknEditorAllowedInputModes(EAknEditorNumericInputMode);
	SetAknEditorInputMode(EAknEditorNumericInputMode);
	SetAknEditorSpecialCharacterTable(0);
	SetAknEditorFlags(EAknEditorFlagFixedCase | EAknEditorFlagNoT9);
	// Only plain numbers
	// The EAknEditorPlainNumberModeKeymap does not support - -sign so
	// we have to use the converter mapping
	SetAknEditorNumericKeymap(EAknEditorConverterNumberModeKeymap);

	iUnsetValue = aUnset;
	SetValueL(iUnsetValue);
	RefreshFromLocale();
	}

EXPORT_C void CAknIntegerEdwin::SetValueL( TInt aValue )
	{
	if ( aValue != iUnsetValue )
		{
		HBufC* formatBuffer = HBufC::NewMaxLC( EAknMaxIntegerDigits );
		TPtr formatPtr = formatBuffer->Des();
		formatPtr.Format(KAknIntegerFormat, aValue);
		
        // Latin only editor doesn't need conversion
        if ( !( AknEdwinFlags() & EAknEditorFlagLatinInputModesOnly ) )
            {
            NumberConversion::ConvertDigits(formatPtr, iDigitType);
            }

		SetTextL( &formatPtr );
		CleanupStack::Pop(); // formatBuffer
		delete formatBuffer;
		}
	else
		{
		SetTextL( &KEmptyText );
		}
	}

EXPORT_C TKeyResponse CAknIntegerEdwin::OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)
	{
	TKeyEvent modifiedKeyEvent(aKeyEvent);
	TEventCode modifiedEventCode(aType);
    
    // FEP already should input converted numbers, so there's no need for this.
	//MapKeyEvent(modifiedKeyEvent, modifiedEventCode, iDigitType);
	return CAknNumericEdwin::OfferKeyEventL(modifiedKeyEvent, modifiedEventCode);
	}


EXPORT_C CAknIntegerEdwin::TValidationStatus CAknIntegerEdwin::GetTextAsInteger( TInt& aValue )
	{

	TValidationStatus state = EValueNotParsed;

	// Create a normalised western version of the string.
	TBuf<EAknMaxIntegerDigits> normalisedText;
	GetText(normalisedText);
	NumberConversion::ConvertDigits(normalisedText, EDigitTypeWestern);

	// Use TextLength() for this test, because stray paragraph marks may lurk in the TPtrC buffer
	if ( TextLength() == 0 )
		{
		state = EEmpty;
		aValue = iUnsetValue;
		}
	else 
		{
		TLex lex( normalisedText );

		if ( lex.Val(aValue) == KErrNone && lex.Remainder().Length() == 0 )
			{
			state = EValueValid;

			// Test the range:
			if ( aValue < iMinimumValue )
				state = EValueTooSmall;
			else if ( aValue > iMaximumValue )
				state = EValueTooLarge;
			}
		else
			{
			state = EValueNotParsed;
			aValue = iUnsetValue;
			}

		}

	return state;

	}



EXPORT_C void CAknIntegerEdwin::SetMinimumIntegerValue( TInt aMinimum )
	{
	iMinimumValue = aMinimum;
	}

EXPORT_C void CAknIntegerEdwin::SetMaximumIntegerValue( TInt aMaximum )
	{
	iMaximumValue = aMaximum;
	}

EXPORT_C void CAknIntegerEdwin::SetUnsetValue( TInt aUnsetValue )
	{
	iUnsetValue = aUnsetValue;
	}


EXPORT_C void CAknIntegerEdwin::PrepareForFocusLossL()
	{
	// TInt resId = 0;
	TInt value;
	TValidationStatus state = GetTextAsInteger( value );

	switch (state )
		{
		case EValueValid:
		break;

		case EEmpty:
		break;

		case EValueTooSmall:
		// resId=R_EIK_TBUF_FNUMBER_BELOW_MIN;
		value = iMinimumValue;
		break;

		case EValueTooLarge:
		// resId=R_EIK_TBUF_FNUMBER_ABOVE_MAX;
		value = iMaximumValue;
		break;

		case EValueNotParsed:

		break;

		default:
		break;
		}

	}

EXPORT_C void CAknIntegerEdwin::HandleResourceChange(TInt aType)
	{
	if(aType==KEikInputLanguageChange)
		{
		RefreshFromLocale();
		return;
		}
	CAknNumericEdwin::HandleResourceChange(aType);
	}

void CAknIntegerEdwin::RefreshFromLocale()
	{
	iDigitType = AknTextUtils::NumericEditorDigitType();

	TInt value;
	if( GetTextAsInteger(value) != EValueValid)
		return;

	TRAP_IGNORE(SetValueL(value) ); // shouldn't leave with OOM because text string is the same size as previous.
	}
	
EXPORT_C void CAknIntegerEdwin::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CAknNumericEdwin::HandlePointerEventL(aPointerEvent); 
    }	

EXPORT_C void* CAknIntegerEdwin::ExtensionInterface( TUid /*aInterface*/ ) 
    { 
    return NULL;
    }

EXPORT_C void CAknIntegerEdwin::Reserved_3()
	{
	}
    
EXPORT_C TBool CAknIntegerEdwin::CheckNumber()
    {
    
    TInt value;
	TValidationStatus state = GetTextAsInteger( value );

	switch (state )
		{
		case EValueTooSmall:
		    {
		    TRAP_IGNORE( SetValueL( iMinimumValue ) );
		    TRAP_IGNORE( SelectAllL() );
		    DrawDeferred();
		    return EFalse;
		    }
		case EValueTooLarge:
            {
		    TRAP_IGNORE( SetValueL( iMaximumValue ) );
        	TRAP_IGNORE( SelectAllL() );
		    DrawDeferred();
		    return EFalse;
            }	
		default:
		break;
		}
		
    return ETrue;
    }
    
// End of File
