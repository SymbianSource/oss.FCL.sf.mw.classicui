/*
* Copyright (c) 1997-2001 Nokia Corporation and/or its subsidiary(-ies).
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


#include <eikfpne.h>

#include <e32math.h>
#include <eikpanic.h>
#include <barsread.h>
#include <eikenv.h>
#include <eikon.hrh>
#include <eikctl.rsg>
#include <AknUtils.h>
#include <AknDef.h>

#include <AknTasHook.h>
const TInt KMaxFloatAndFixedNumberOfDigits = 32;



TInt TenToThePower(TInt n)// mostly, n small, eg 2, so integer arithmetic more efficient than real
	{
    TInt ret=1;
    while (n--)
        ret*=10;
	return (ret);
	}


const TInt KFloatingPointEditorDefaultEdwinFlags = 
	EEikEdwinNoLineOrParaBreaks | 
	EEikEdwinAutoSelection;

const TInt KFixedPointEditorDefaultEdwinFlags = 
	EEikEdwinNoLineOrParaBreaks | 
	EEikEdwinAutoSelection ;

// class CEikFloatingPointEditor ////////////////////////////////////////////////////////////

EXPORT_C CEikFloatingPointEditor::CEikFloatingPointEditor()
	{
    iEdwinInternalFlags=ENumericCharacters;
    AKNTASHOOK_ADD( this, "CEikFloatingPointEditor" );
	}

EXPORT_C void CEikFloatingPointEditor::ConstructL(const TReal& aMin,const TReal& aMax,TInt aTextLimit)
	{

	// Enforce absolute maximum digits on ediwn
	TInt maxDigits = aTextLimit;
	if((maxDigits==0) || (maxDigits>KMaxFloatAndFixedNumberOfDigits))
		maxDigits = KMaxFloatAndFixedNumberOfDigits;

	SetMinMax(aMin,aMax);
	CEikEdwin::ConstructL(KFloatingPointEditorDefaultEdwinFlags,aTextLimit,maxDigits,1);
	SetAknEditorNumericKeymap(EAknEditorConverterNumberModeKeymap);
	SetAknEditorAllowedInputModes(EAknEditorNumericInputMode);
	SetAknEditorInputMode(EAknEditorNumericInputMode);
	SetAknEditorSpecialCharacterTable(0);
	}

EXPORT_C void CEikFloatingPointEditor::PrepareForFocusLossL()
	{

	TReal value;
	TValidationStatus validationStatus = GetValueAsReal(value);

    TReal* pReal=NULL;

	switch (validationStatus)
		{
		case EValueValid:
			iValue = value;
			break;

		case EValueTooSmall:
			pReal=(&iMin);
			break;

		case EValueTooLarge:
			pReal=(&iMax);
			break;

		case EValueNotParsed:
		case EEmpty:
			pReal=(&iMin);
			break;
		};

	if (validationStatus != EValueValid)
		{
		SetValueL(pReal);
        User::Leave(KLeaveWithoutAlert); 
		}
	}

EXPORT_C TCoeInputCapabilities CEikFloatingPointEditor::InputCapabilities() const
	{
	TCoeInputCapabilities inputCapabilities = CEikEdwin::InputCapabilities();
	inputCapabilities.SetCapabilities(TCoeInputCapabilities::EWesternNumericReal|TCoeInputCapabilities::ENavigation);
	return inputCapabilities;
	}

EXPORT_C TKeyResponse CEikFloatingPointEditor::OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)
	{
	TKeyEvent keyEvent(aKeyEvent);
	TEventCode eventCode(aType);

	return CAknNumericEdwin::OfferKeyEventL(keyEvent, eventCode);
	}

EXPORT_C void CEikFloatingPointEditor::ConstructFromResourceL(TResourceReader& aReader)
	{
	TInt textLimit=aReader.ReadUint16();
	TReal min=aReader.ReadReal64();
	TReal max=aReader.ReadReal64();
	TReal defaultValue=aReader.ReadReal64(); // does not work with queries !!!
	ConstructL(min,max,textLimit);
    // added to give a default value, to work with forms.  Unsure if this is desirable.
	if ((min>defaultValue)||(defaultValue>max)) 
		defaultValue=min;
	SetValueL(&defaultValue);
	}

EXPORT_C CAknNumericEdwin::TValidationStatus CEikFloatingPointEditor::GetValueAsReal( TReal& aValue )
    {
	TValidationStatus state = EValueNotParsed;

	// Normalise text to western, so that Tlex will work
	TBuf<KMaxFloatAndFixedNumberOfDigits> text;
	GetText(text);
	AknTextUtils::ConvertDigitsTo(text, EDigitTypeWestern);

	// Use TextLength() for this test, because stray paragraph marks may lurk in the TPtrC buffer
	if ( TextLength() == 0 )
		{
		state = EEmpty;
		}
	else 
		{
		TLex lex( text );

		if ( lex.Val(aValue) == KErrNone && lex.Remainder().Length() == 0 )
			{
			state = EValueValid;

			// Test the range:
			if ( aValue < iMin )
                {
				state = EValueTooSmall;
                }
			else if ( aValue > iMax )
                {
				state = EValueTooLarge;
                }
			}
		else
			{
			state = EValueNotParsed;
			}

		}

	return state;
    
    }

EXPORT_C TReal CEikFloatingPointEditor::Value() const
	{
	return iValue;// assumes model already checked for validity
	}

EXPORT_C void CEikFloatingPointEditor::SetValueL(const TReal* aValue)
	{
    if (!aValue)
        {
		SetTextL(NULL);
        return;
        }

	iValue=*aValue;
	// !! Now check for validity?
	TBuf<EAknMaxIntegerDigits> des;
	TRealFormat format(iTextLimit);
	format.iType|=KAllowThreeDigitExp;
	des.Num(iValue,format);

	AknTextUtils::ConvertDigitsTo(des, AknTextUtils::NumericEditorDigitType());

	SetTextL(&des);
	if ( !(iEdwinUserFlags&ENoAutoSelection) )
		{
        SetCursorPosL(des.Length(), ETrue);
        }
	else
		{
		SetCursorPosL(des.Length(), EFalse);
		}
    DrawNow();
	}

EXPORT_C void CEikFloatingPointEditor::SetMinMax(TReal aMin,TReal aMax)
	{
	iMin=aMin;
	iMax=aMax;
	__ASSERT_DEBUG(iMin<=iMax, Panic(EEikPanicInvalidBounds) );
	}

EXPORT_C void CEikFloatingPointEditor::GetMinMax(TReal& aMin, TReal& aMax) const
	{
	aMin=iMin;
	aMax=iMax;
	}

EXPORT_C void CEikFloatingPointEditor::HandleResourceChange(TInt aType)
	{
	if(aType==KEikInputLanguageChange)
		{
		// get and set the same value will refresh the edwin text on a locale change
		TReal value;
		if( GetValueAsReal(value) == CAknNumericEdwin::EValueValid)
			{
			TRAP_IGNORE(SetValueL(&value));
			}
		}
	CAknNumericEdwin::HandleResourceChange(aType);
	}

EXPORT_C void CEikFloatingPointEditor::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CAknNumericEdwin::HandlePointerEventL(aPointerEvent); 
    }

EXPORT_C void* CEikFloatingPointEditor::ExtensionInterface( TUid /*aInterface*/ )
    {
    return NULL;
    }

EXPORT_C void CEikFloatingPointEditor::Reserved_3()
	{}

// class CEikFixedPointEditor ///////////////////////////////////////////////////////////////////

EXPORT_C CEikFixedPointEditor::CEikFixedPointEditor()
	{
    iEdwinInternalFlags=ENumericCharacters;
	}

EXPORT_C void CEikFixedPointEditor::ConstructL(TInt aMin,TInt aMax)
	{
	SetMinMax(aMin,aMax);
	iTextLimit=RequiredNumberOfCharacters();

	SetAknEditorNumericKeymap(EAknEditorConverterNumberModeKeymap); 
	SetAknEditorAllowedInputModes(EAknEditorNumericInputMode);
	SetAknEditorInputMode(EAknEditorNumericInputMode);
	SetAknEditorSpecialCharacterTable(0);

	CEikEdwin::ConstructL(KFixedPointEditorDefaultEdwinFlags,iTextLimit,iTextLimit,1);
	}

EXPORT_C void CEikFixedPointEditor::ConstructFromResourceL(TResourceReader& aReader)
	{
	iDecimalPlaces=aReader.ReadUint16();
	TInt min=aReader.ReadInt32();
	TInt max=aReader.ReadInt32();
	TInt defaultValue = aReader.ReadInt32();

	__ASSERT_DEBUG(min<=max, Panic(EEikPanicInvalidBounds) );

	ConstructL(min, max );

	// added to give a default value, to work with forms.  Unsure if this is desirable.
	if ((min>defaultValue)||(defaultValue>max)) 
		defaultValue=min;
	SetValueL(&defaultValue);
	}



EXPORT_C CAknNumericEdwin::TValidationStatus CEikFixedPointEditor::GetValueAsInteger( TInt& aValue )
    {
	TValidationStatus state = EValueNotParsed;    
	// Normalise text to western, so that Tlex will work
	TBuf<KMaxFloatAndFixedNumberOfDigits> text;
	GetText(text);
	AknTextUtils::ConvertDigitsTo(text, EDigitTypeWestern);

	// Use TextLength() for this test, because stray paragraph marks may lurk in the TPtrC buffer
	if ( TextLength() == 0 )
		{
		state = EEmpty;
		}
	else 
		{
		TLex lex( text );
        TReal real;
		if ( lex.Val( real ) == KErrNone )
			{
			state = EValueValid;
	        real*=TenToThePower(iDecimalPlaces);
	        real+=(real>0)?0.5:(-0.5);
	        Math::Int((TInt32&)iValue, real);

			// Test the range:
			if ( iValue < iMin )
                {
				state = EValueTooSmall;
                }
			else if ( iValue > iMax )
                {
				state = EValueTooLarge;
                }
            else
                {
                aValue = iValue;                
                }
			}
		else
			{
			state = EValueNotParsed;
			}

		}

	return state;
    
    }

TInt CEikFixedPointEditor::RequiredNumberOfCharacters() const
	{
	TInt absMax=(iMax >= -iMin) ? iMax : -iMin;
	TInt numberOfCharacters=0;
	while (absMax!=0)
		{
		++numberOfCharacters;
		absMax/=10;
		}
	if (numberOfCharacters<iDecimalPlaces+1)
		numberOfCharacters=iDecimalPlaces+1;// if bounds ensure leading digits will be zero, still need enough characters
	++numberOfCharacters;// one character for the decimal point
	if (iMin<0)
		++numberOfCharacters;// one character for the minus sign
	return numberOfCharacters;
	}

EXPORT_C void CEikFixedPointEditor::PrepareForFocusLossL()
	{
	TBuf<KMaxFloatAndFixedNumberOfDigits> string;
	GetText(string);

	// Convert to western so that TLex works
	AknTextUtils::ConvertDigitsTo(string, EDigitTypeWestern);
	TLex lex(string);
	TReal real;
	TInt err=lex.Val(real);
	if (err==KErrGeneral || err==KErrArgument || lex.Remainder().Length())
        {
        // Change value to minimum
        SetValueL( &iMin );
        User::Leave( KErrNone );
        }
	real*=TenToThePower(iDecimalPlaces);
	real+=(real>0)?0.5:(-0.5);
	Math::Int((TInt32&)iValue, real);
    if (iValue<iMin)
		{
        SetValueL( &iMin );
        User::Leave( KErrNone );
		}
    else if (iValue>iMax)
		{
        SetValueL( &iMax );
        User::Leave( KErrNone );
		}
	}


EXPORT_C TCoeInputCapabilities CEikFixedPointEditor::InputCapabilities() const
	{
	TCoeInputCapabilities inputCapabilities = CEikEdwin::InputCapabilities();
	inputCapabilities.SetCapabilities(TCoeInputCapabilities::EWesternNumericReal|TCoeInputCapabilities::ENavigation);
	return inputCapabilities;
	}

EXPORT_C TInt CEikFixedPointEditor::Value() const
	{
	return iValue;
	}

EXPORT_C void CEikFixedPointEditor::SetValueL(const TInt* aValue)
	{
    if (!aValue)
        {
		SetTextL(NULL);
        return;
        }
	iValue=*aValue;
	//
	TRealFormat format(iTextLimit,iDecimalPlaces);
	format.iType|=KDoNotUseTriads;
	//
	TReal real=(TReal)iValue;
	real/=TenToThePower(iDecimalPlaces);
	TBuf<KMaxFloatAndFixedNumberOfDigits> string;
	string.Num(real,format);

	AknTextUtils::ConvertDigitsTo(string, AknTextUtils::NumericEditorDigitType());

	SetTextL(&string);
    DrawNow();
	}

EXPORT_C void CEikFixedPointEditor::SetMinMax(TInt aMin, TInt aMax)
	{
	iMin=aMin;
	iMax=aMax;
	__ASSERT_DEBUG(iMin<=iMax, Panic(EEikPanicInvalidBounds) );
	}

EXPORT_C void CEikFixedPointEditor::GetMinMax(TInt& aMin, TInt& aMax) const
	{
	aMin=iMin;
	aMax=iMax;
	}

EXPORT_C void CEikFixedPointEditor::SetDecimalPlaces(TInt aDecimalPlaces)
	{
	iDecimalPlaces=aDecimalPlaces;
	}

EXPORT_C TInt CEikFixedPointEditor::DecimalPlaces() const
	{
	return iDecimalPlaces;
	}

EXPORT_C TKeyResponse CEikFixedPointEditor::OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)
	{
	TKeyEvent keyEvent(aKeyEvent);
	TEventCode eventCode(aType);

	return CAknNumericEdwin::OfferKeyEventL(keyEvent, eventCode);
	}

EXPORT_C void CEikFixedPointEditor::HandleResourceChange(TInt aType)
	{
	if(aType==KEikInputLanguageChange)
		{
		// get and set the same value will refresh the edwin text on a locale change
		TInt value;
		if( GetValueAsInteger(value) == CAknNumericEdwin::EValueValid)
			{
			TRAP_IGNORE(SetValueL(&value));
			}
		}
	CAknNumericEdwin::HandleResourceChange(aType);
	}
	
EXPORT_C void CEikFixedPointEditor::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CAknNumericEdwin::HandlePointerEventL(aPointerEvent); 
    }	

EXPORT_C void* CEikFixedPointEditor::ExtensionInterface( TUid /*aInterface*/ )
    {
    return NULL;
    }

EXPORT_C void CEikFixedPointEditor::Reserved_3()
	{}
