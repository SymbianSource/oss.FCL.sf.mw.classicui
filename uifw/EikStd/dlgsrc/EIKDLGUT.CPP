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


#include <eikdialg.h>
#include <eikfpne.h> // reincluded
#include <eiktxlbx.h>
#include <eikon.hrh>
#include <badesca.h>
#include <coemain.h>
#include <eikcapca.h>
#include <eikcapc.h>
#include <eiklabel.h>
#include <eikedwin.h>
#include <eikrted.h>
#include <eikmfne.h>  
#include <eikseced.h>


/**
 * @deprecated
 */
EXPORT_C void CEikDialog::SetListBoxCurrentItem(TInt aControlId, TInt aItem)
	{
	CEikTextListBox* listBox=(CEikTextListBox*)Control(aControlId);
	listBox->SetCurrentItemIndex(aItem);
	listBox->DrawNow();
	}

/**
 * @deprecated
 */
EXPORT_C TInt CEikDialog::ListBoxCurrentItem(TInt aControlId) const
	{
	return ((CEikTextListBox*)Control(aControlId))->CurrentItemIndex();
	}

/**
 * @deprecated
 */
EXPORT_C void CEikDialog::DeclareAutoTextEditorL(TInt aId,TDes* aText)
	{
	DeclareItemAuto(aId,EEikCtEdwin,aText);
	SetEdwinTextL(aId,aText);
	}

/**
 * @deprecated
 */
EXPORT_C void CEikDialog::DeclareAutoNumberEditor(TInt aId,TInt* aNumber)
	{
	DeclareItemAuto(aId,EEikCtNumberEditor,aNumber);
	SetNumberEditorValue(aId,*aNumber);
	}

/**
 * @deprecated
 */
EXPORT_C void CEikDialog::DeclareAutoRangeEditor(TInt aId,SEikRange* aRange)
	{
	DeclareItemAuto(aId,EEikCtRangeEditor,aRange);
	SetRangeEditorValue(aId,*aRange);
	}

/**
 * @deprecated
 */
EXPORT_C void CEikDialog::DeclareAutoTimeEditor(TInt aId,TTime* aTime)
	{
	DeclareItemAuto(aId,EEikCtTimeEditor,aTime);
	SetTTimeEditorValue(aId,*aTime);
	}

/**
 * @deprecated
 */
EXPORT_C void CEikDialog::DeclareAutoDateEditor(TInt aId,TTime* aDate)
	{
	DeclareItemAuto(aId,EEikCtDateEditor,aDate);
	SetTTimeEditorValue(aId,*aDate);
	}

/**
 * @deprecated
 */
EXPORT_C void CEikDialog::DeclareAutoTimeAndDateEditor(TInt aId,TTime* aTimeAndDate)
	{
	DeclareItemAuto(aId,EEikCtTimeAndDateEditor,aTimeAndDate);
	SetTTimeEditorValue(aId,*aTimeAndDate);
	}

/**
 * @deprecated
 */
EXPORT_C void CEikDialog::DeclareAutoDurationEditor(TInt aId,TTimeIntervalSeconds* aDuration)
	{
	DeclareItemAuto(aId,EEikCtDurationEditor,aDuration);
	SetDurationEditorValue(aId,*aDuration);
	}

/**
 * @deprecated
 */
EXPORT_C void CEikDialog::DeclareAutoTimeOffsetEditor(TInt aId,TTimeIntervalSeconds* aTimeOffset)
	{
	DeclareItemAuto(aId,EEikCtTimeOffsetEditor,aTimeOffset);
	SetTimeOffsetEditorValue(aId,*aTimeOffset);
	}

/**
 * @deprecated
 */
/*EXPORT_C void CEikDialog::DeclareAutoLatitudeEditor(TInt aId,SEikDegreesMinutesDirection* aLatitude)
	{
	DeclareItemAuto(aId,EEikCtLatitudeEditor,aLatitude);
	SetLatitudeEditorValue(aId,*aLatitude);
	}
*/
/**
 * @deprecated
 */
/*EXPORT_C void CEikDialog::DeclareAutoLongitudeEditor(TInt aId,SEikDegreesMinutesDirection* aLongitude)
	{
	DeclareItemAuto(aId,EEikCtLongitudeEditor,aLongitude);
	SetLongitudeEditorValue(aId,*aLongitude);
	}
*/
/**
 * @deprecated
 */
EXPORT_C void CEikDialog::DeclareAutoFixedPointEditor(TInt aId,TInt* aValue)
	{
	DeclareItemAuto(aId,EEikCtFxPtEd,aValue);
	TRAP_IGNORE(SetFixedPointEditorValueL(aId,*aValue));
	}

/**
 * @deprecated
 */
EXPORT_C void CEikDialog::DeclareAutoSecretEditor(TInt aId,TDes* aText)
	{
	DeclareItemAuto(aId,EEikCtSecretEd,aText);
	}


/**
 * @deprecated
 */
//stay
EXPORT_C void CEikDialog::AddAutoTextEditorL(const TDesC& aPrompt,TInt aId,TInt aFlags,TInt aWidthInChars,TInt aNoOfLines,TDes* aReturn)
	{
	CEikEdwin* edwin=(CEikEdwin*)CreateLineByTypeL(aPrompt,aId,EEikCtEdwin,aReturn);
	edwin->ConstructL(aFlags,aWidthInChars,aReturn->MaxLength(),aNoOfLines);
	edwin->SetTextL(aReturn);
	}

/**
 * @deprecated
 */
EXPORT_C void CEikDialog::AddAutoGlobalTextEditorL(const TDesC& aPrompt,TInt aId,TInt aFlags,TInt aWidthInChars,TInt aNoOfLines,TInt aTextLimit,CGlobalText* aReturn,TInt aFontControlFlags,TInt aFontNameFlags)
	{
	CEikGlobalTextEditor* gtEditor=(CEikGlobalTextEditor*)CreateLineByTypeL(aPrompt,aId,EEikCtGlobalTextEditor,aReturn);
	gtEditor->ConstructL(this,aNoOfLines,aTextLimit,aFlags,aFontControlFlags,aFontNameFlags);
	gtEditor->CalculateWidth(aWidthInChars);
	CEikEdwin::TSetContent content=(aFlags&CEikEdwin::EUserSuppliedText? CEikEdwin::EUseText : CEikEdwin::ECopyText);
	gtEditor->SetDocumentContentL(*aReturn,content);
	}

/**
 * @deprecated
 */
EXPORT_C void CEikDialog::AddAutoRichTextEditorL(const TDesC& aPrompt,TInt aId,TInt aFlags,TInt aWidthInChars,TInt aNoOfLines,TInt aTextLimit,CGlobalText* aReturn,TInt aFontControlFlags,TInt aFontNameFlags)
	{
	CEikRichTextEditor* rtEditor=(CEikRichTextEditor*)CreateLineByTypeL(aPrompt,aId,EEikCtRichTextEditor,aReturn);
	rtEditor->ConstructL(this,aNoOfLines,aTextLimit,aFlags,aFontControlFlags,aFontNameFlags);
	rtEditor->CalculateWidth(aWidthInChars);
	CEikEdwin::TSetContent content=(aFlags&CEikEdwin::EUserSuppliedText? CEikEdwin::EUseText : CEikEdwin::ECopyText);
	rtEditor->SetDocumentContentL(*aReturn,content);
	}

/**
 * @deprecated
 */
//stay
EXPORT_C void CEikDialog::AddAutoNumberEditorL(const TDesC& aPrompt,TInt aId,TInt aMin,TInt aMax,TInt* aReturn)
	{
	CEikNumberEditor* numEd=(CEikNumberEditor*)CreateLineByTypeL(aPrompt,aId,EEikCtNumberEditor,aReturn);
	numEd->ConstructL(aMin,aMax,*aReturn);
	}

/**
 * @deprecated
 */
EXPORT_C void CEikDialog::AddAutoRangeEditorL(const TDesC& aPrompt,TInt aId,TInt aMin,TInt aMax,HBufC* aSeparatorText,SEikRange* aReturn)
	{
	CEikRangeEditor* rangeEd=(CEikRangeEditor*)CreateLineByTypeL(aPrompt,aId,EEikCtRangeEditor,aReturn);
	rangeEd->ConstructL(aMin,aMax,*aReturn, aSeparatorText);
	}

/**
 * @deprecated
 */
EXPORT_C void CEikDialog::AddAutoTimeEditorL(const TDesC& aPrompt,TInt aId,const TTime& aMin,const TTime& aMax,TBool aNoSeconds,TTime* aReturn)
	{
	CEikTimeEditor* timeEd = (CEikTimeEditor*)CreateLineByTypeL(aPrompt,aId,EEikCtTimeEditor,aReturn);
	timeEd->ConstructL(aMin,aMax,*aReturn,aNoSeconds);
	}

/**
 * @deprecated
 */
EXPORT_C void CEikDialog::AddAutoDateEditorL(const TDesC& aPrompt,TInt aId,const TTime& aMin,const TTime& aMax, TBool aNoPopout,TTime* aReturn)
	{
	CEikDateEditor* dateEd = (CEikDateEditor*)CreateLineByTypeL(aPrompt,aId,EEikCtDateEditor,aReturn);
	dateEd->ConstructL(aMin,aMax,*aReturn,aNoPopout);
	}

/**
 * @deprecated
 */
EXPORT_C void CEikDialog::AddAutoTimeAndDateEditorL(const TDesC& aPrompt,TInt aId,const TTime& aMin,const TTime& aMax,TBool aNoSeconds,TBool aNoPopout,HBufC* aInterveningText,TTime* aReturn)
	{
	TUint32 flags=0;
	if(aNoSeconds)
		flags|=EEikTimeWithoutSecondsField;
	if(aNoPopout)
		flags|=EEikDateWithoutPopoutCalendar;
	CEikTimeAndDateEditor* timeAndDateEd = (CEikTimeAndDateEditor*)CreateLineByTypeL(aPrompt,aId,EEikCtTimeAndDateEditor,aReturn);
	timeAndDateEd->ConstructL(aMin,aMax,*aReturn,flags,aInterveningText);
	}

/**
 * @deprecated
 */
EXPORT_C void CEikDialog::AddAutoDurationEditorL(const TDesC& aPrompt,TInt aId,const TTimeIntervalSeconds& aMin,const TTimeIntervalSeconds& aMax,TBool aNoSeconds,TTimeIntervalSeconds* aReturn)
	{
	CEikDurationEditor* durationEd = (CEikDurationEditor*)CreateLineByTypeL(aPrompt,aId,EEikCtDurationEditor,aReturn);
	durationEd->ConstructL(aMin,aMax,*aReturn,aNoSeconds);
	}

/**
 * @deprecated
 */
EXPORT_C void CEikDialog::AddAutoTimeOffsetEditorL(const TDesC& aPrompt,TInt aId,const TTimeIntervalSeconds& aMin,const TTimeIntervalSeconds& aMax,TBool aNoSeconds,TTimeIntervalSeconds* aReturn)
	{
	CEikTimeOffsetEditor* timeOffsetEd = (CEikTimeOffsetEditor*)CreateLineByTypeL(aPrompt,aId,EEikCtTimeOffsetEditor,aReturn);
	timeOffsetEd->ConstructL(aMin,aMax,*aReturn,aNoSeconds);
	}

/**
 * @deprecated
 */
/*EXPORT_C void CEikDialog::AddAutoLatitudeEditorL(const TDesC& aPrompt,TInt aId,HBufC* aDegreeSign,HBufC* aMinuteSign,
											   HBufC* aSecondSign,HBufC* aTextForNorth,TChar aKeyToMatchForNorth,
											   HBufC* aTextForSouth,TChar aKeyToMatchForSouth,
											   SEikDegreesMinutesDirection* aReturn,TInt aFlags)
	{
	CEikLatitudeEditor* latitudeEd = (CEikLatitudeEditor*)CreateLineByTypeL(aPrompt,aId,EEikCtLatitudeEditor,aReturn);
	latitudeEd->ConstructL(aDegreeSign,aMinuteSign,aSecondSign,aTextForNorth,aKeyToMatchForNorth,aTextForSouth,aKeyToMatchForSouth,*aReturn,aFlags);
	}
*/
/**
 * @deprecated
 */
/*EXPORT_C void CEikDialog::AddAutoLongitudeEditorL(const TDesC& aPrompt,TInt aId,HBufC* aDegreeSign,HBufC* aMinuteSign,
												HBufC* aSecondSign,HBufC* aTextForEast,TChar aKeyToMatchForEast,
												HBufC* aTextForWest,TChar aKeyToMatchForWest,
												SEikDegreesMinutesDirection* aReturn,TInt aFlags)
	{
	CEikLongitudeEditor* longitudeEd = (CEikLongitudeEditor*)CreateLineByTypeL(aPrompt,aId,EEikCtLongitudeEditor,aReturn);
	longitudeEd->ConstructL(aDegreeSign,aMinuteSign,aSecondSign,aTextForEast,aKeyToMatchForEast,aTextForWest,aKeyToMatchForWest,*aReturn,aFlags);
	}
*/
/**
 * @deprecated
 */
EXPORT_C void CEikDialog::AddAutoFloatEditorL(const TDesC& aPrompt,TInt aId,const TReal& aMin,const TReal& aMax,TReal* aReturn)
	{
/*	Reversed Build Thinning, reincluded eliminated CEikFixedPointEditor(EikCtl) */
	CEikFloatingPointEditor* flPtEd=(CEikFloatingPointEditor*)CreateLineByTypeL(aPrompt,aId,EEikCtFlPtEd,aReturn);
	flPtEd->ConstructL(aMin,aMax,18);
	flPtEd->SetValueL(aReturn);
	}

/**
 * @deprecated
 */
EXPORT_C void CEikDialog::AddAutoFixedPointEditorL(const TDesC& aPrompt,TInt aId,TInt aMin,TInt aMax,TInt* aRetValue,TInt aDecimalPlaces)
	{
/*	Reversed Build Thinning, reincluded eliminated CEikFixedPointEditor(EikCtl) */
	CEikFixedPointEditor* fixedEd = (CEikFixedPointEditor*)CreateLineByTypeL(aPrompt,aId,EEikCtFxPtEd,aRetValue);
	fixedEd->ConstructL(aMin,aMax);
	fixedEd->SetDecimalPlaces(aDecimalPlaces);
	fixedEd->SetValueL(aRetValue);
	}

/**
 * @deprecated
 */
EXPORT_C void CEikDialog::AddAutoSecretEditorL(const TDesC& aPrompt,TInt aId,TDes* aReturn)
	{
	CEikSecretEditor* secEd = (CEikSecretEditor*)CreateLineByTypeL(aPrompt,aId,EEikCtSecretEd,aReturn);
	secEd->SetMaxLength(aReturn->MaxLength());
	}

/**
 * @deprecated
 */
EXPORT_C void CEikDialog::SetLabelL(TInt aControlId, const TDesC& aDes)
	{
	CEikLabel* label=(CEikLabel*)Control(aControlId);
	label->SetTextL(aDes);
	label->DrawNow();
	}

/**
 * @deprecated
 */
EXPORT_C void CEikDialog::SetLabelL(TInt aControlId, TInt aResourceId)
	{
	HBufC* tmp=iCoeEnv->AllocReadResourceLC(aResourceId);
	SetLabelL(aControlId,tmp->Des());
	CleanupStack::PopAndDestroy(); // tmp
	}

/**
 * @deprecated
 */
EXPORT_C void CEikDialog::SetLabelReserveLengthL(TInt aControlId, TInt aLength)
	{
	((CEikLabel*)Control(aControlId))->SetBufferReserveLengthL(aLength);
	}

/**
 * @deprecated
 */
EXPORT_C void CEikDialog::GetLabelText(TDes& aDes, TInt aControlId) const
	{
	aDes.Copy(*(((CEikLabel*)Control(aControlId))->Text()));
	}

/**
 * @deprecated
 */
EXPORT_C void CEikDialog::SetEdwinTextL(TInt aControlId, const TDesC* aDes)
	{
	CEikEdwin* edwin=(CEikEdwin*)Control(aControlId);
	edwin->SetTextL(aDes);
	edwin->DrawNow();
	}

/**
 * @deprecated
 */
EXPORT_C void CEikDialog::GetEdwinText(TDes& aDes,TInt aControlId) const
	{
	((CEikEdwin*)Control(aControlId))->GetText(aDes);
	}

/**
 * @deprecated
 */
EXPORT_C void CEikDialog::SetTextEditorTextL(TInt aControlId,const CGlobalText* aGlobalText)
	{
	CEikGlobalTextEditor* editor=(CEikGlobalTextEditor*)Control(aControlId);
	editor->SetDocumentContentL(*((CGlobalText*)aGlobalText));	//const cast due to edwin function
	editor->DrawNow();
	}

/**
 * @deprecated
 */
EXPORT_C void CEikDialog::GetTextEditorText(CGlobalText*& aGlobalText,TInt aControlId)
	{
	aGlobalText=((CEikGlobalTextEditor*)Control(aControlId))->GlobalText();
	}

/**
 * @deprecated
 */
EXPORT_C void CEikDialog::ResetSecretEditor(TInt aControlId)
	{
	((CEikSecretEditor*)Control(aControlId))->Reset();
	}

/**
 * @deprecated
 */
EXPORT_C void CEikDialog::GetSecretEditorText(TDes& aDes,TInt aControlId) const
	{
	((CEikSecretEditor*)Control(aControlId))->GetText(aDes);
	}

/**
 * @deprecated
 */
EXPORT_C void CEikDialog::SetFloatingPointEditorValueL(TInt aControlId,const TReal* aValue)
	{
/*	Reversed Build Thinning, reincluded eliminated CEikFloatingPointEditor(EikCtl) */
	CEikFloatingPointEditor* fltPtEd=(CEikFloatingPointEditor*)Control(aControlId);
	fltPtEd->SetValueL(aValue);
	fltPtEd->DrawNow();
	}

/**
 * @deprecated
 */
EXPORT_C TReal CEikDialog::FloatingPointEditorValue(TInt aControlId) const
	{
/*	Reversed Build Thinning, reincluded eliminated CEikFloatingPointEditor(EikCtl) */
	return ((CEikFloatingPointEditor*)Control(aControlId))->Value();
	}

/**
 * @deprecated
 */
EXPORT_C void CEikDialog::SetFixedPointEditorValueL(TInt aControlId,TInt aValue)
	{
/*	Reversed Build Thinning, reincluded eliminated CEikFixedPointEditor(EikCtl) */
	CEikFixedPointEditor* fixPtEd=(CEikFixedPointEditor*)Control(aControlId);
	fixPtEd->SetValueL(&aValue);
	fixPtEd->DrawNow();
	}

/**
 * @deprecated
 */
EXPORT_C TInt CEikDialog::FixedPointEditorValue(TInt aControlId) const
	{
/*	Reversed Build Thinning, reincluded eliminated CEikFixedPointEditor(EikCtl) */
	return ((CEikFixedPointEditor*)Control(aControlId))->Value();
	}
/**
 * @deprecated
 */
EXPORT_C void CEikDialog::SetFixedPointEditorDecimal(TInt aControlId,TInt aDecimal)
	{
/*	Reversed Build Thinning, reincluded eliminated CEikFixedPointEditor(EikCtl) */
	((CEikFixedPointEditor*)Control(aControlId))->SetDecimalPlaces(aDecimal);
	}

/**
 * @deprecated
 */
EXPORT_C TInt CEikDialog::FixedPointEditorDecimal(TInt aControlId) const
	{
/*	Reversed Build Thinning, reincluded eliminated CEikFixedPointEditor(EikCtl) */
	return STATIC_CAST(CEikFixedPointEditor*,Control(aControlId))->DecimalPlaces();
	}

/**
 * @deprecated
 */
EXPORT_C void CEikDialog::SetNumberEditorMinAndMax(TInt aControlId, TInt aMinimumValue, TInt aMaximumValue)
	{
	CEikNumberEditor* numberEditor=(CEikNumberEditor*)Control(aControlId);
	numberEditor->SetMinimumAndMaximum(aMinimumValue, aMaximumValue);
	numberEditor->DrawNow();
	}

/**
 * @deprecated
 */
EXPORT_C void CEikDialog::SetNumberEditorValue(TInt aControlId, TInt aNumber)
	{
	CEikNumberEditor* numberEditor=(CEikNumberEditor*)Control(aControlId);
	numberEditor->SetNumber(aNumber);
	numberEditor->DrawNow();
	}

/**
 * @deprecated
 */
EXPORT_C TInt CEikDialog::NumberEditorValue(TInt aControlId) const
	{
	return ((CEikNumberEditor*)Control(aControlId))->Number();
	}

/**
 * @deprecated
 */
EXPORT_C void CEikDialog::SetFloatEditorMinAndMax(TInt aControlId,TInt aMin,TInt aMax)
	{
/*	Reversed Build Thinning, reincluded eliminated CEikFloatingPointEditor(EikCtl) */
	CEikFloatingPointEditor* floatEditor=(CEikFloatingPointEditor*)Control(aControlId);
	floatEditor->SetMinMax(aMin,aMax);
	floatEditor->DrawNow();
	}

/**
 * @deprecated
 */
EXPORT_C void CEikDialog::SetFloatEditorValueL(TInt aControlId,TReal aFloat)
	{
/*	Reversed Build Thinning, reincluded eliminated CEikFloatingPointEditor(EikCtl) */
	CEikFloatingPointEditor* floatEditor=(CEikFloatingPointEditor*)Control(aControlId);
	floatEditor->SetValueL(&aFloat);
	floatEditor->DrawNow();
	}

/**
 * @deprecated
 */
EXPORT_C TReal CEikDialog::FloatEditorValue(TInt aControlId) const
	{
/*	Reversed Build Thinning, reincluded eliminated CEikFloatingPointEditor(EikCtl) */
	return ((CEikFloatingPointEditor*)Control(aControlId))->Value();
	}

/**
 * @deprecated
 */
EXPORT_C void CEikDialog::SetRangeEditorMinAndMax(TInt aControlId, TInt aMinimumValue, TInt aMaximumValue)
	{
	CEikRangeEditor* rangeEditor=(CEikRangeEditor*)Control(aControlId);
	rangeEditor->SetMinimumAndMaximum(aMinimumValue, aMaximumValue);
	rangeEditor->DrawNow();
	}

/**
 * @deprecated
 */
EXPORT_C void CEikDialog::SetRangeEditorValue(TInt aControlId, const SEikRange& aRange)
	{
	CEikRangeEditor* rangeEditor=(CEikRangeEditor*)Control(aControlId);
	rangeEditor->SetRange(aRange);
	rangeEditor->DrawNow();
	}

/**
 * @deprecated
 */
EXPORT_C SEikRange CEikDialog::RangeEditorValue(TInt aControlId) const
	{
	return ((CEikRangeEditor*)Control(aControlId))->Range();
	}

/**
 * @deprecated
 */
EXPORT_C void CEikDialog::SetTTimeEditorMinAndMax(TInt aControlId, const TTime& aMinimumTime, const TTime& aMaximumTime)
	{
	CEikTTimeEditor* tTimeEditor=(CEikTTimeEditor*)Control(aControlId);
	tTimeEditor->SetMinimumAndMaximum(aMinimumTime, aMaximumTime);
	tTimeEditor->DrawNow();
	}

/**
 * @deprecated
 */
EXPORT_C void CEikDialog::SetTTimeEditorValue(TInt aControlId, const TTime& aTime)
	{
	CEikTTimeEditor* tTimeEditor=(CEikTTimeEditor*)Control(aControlId);
	tTimeEditor->SetTTime(aTime);
	tTimeEditor->DrawNow();
	}

/**
 * @deprecated
 */
EXPORT_C TTime CEikDialog::TTimeEditorValue(TInt aControlId) const
	{
	return ((CEikTTimeEditor*)Control(aControlId))->GetTTime();
	}

/**
 * @deprecated
 */
EXPORT_C void CEikDialog::SetDurationEditorMinAndMax(TInt aControlId, const TTimeIntervalSeconds& aMinimumDuration, const TTimeIntervalSeconds& aMaximumDuration)
	{
	CEikDurationEditor* durationEditor=(CEikDurationEditor*)Control(aControlId);
	durationEditor->SetMinimumAndMaximum(aMinimumDuration, aMaximumDuration);
	durationEditor->DrawNow();
	}

/**
 * @deprecated
 */
EXPORT_C void CEikDialog::SetDurationEditorValue(TInt aControlId, const TTimeIntervalSeconds& aDuration)
	{
	CEikDurationEditor* durationEditor=(CEikDurationEditor*)Control(aControlId);
	durationEditor->SetDuration(aDuration);
	durationEditor->DrawNow();
	}

/**
 * @deprecated
 */
EXPORT_C TTimeIntervalSeconds CEikDialog::DurationEditorValue(TInt aControlId) const
	{
	return ((CEikDurationEditor*)Control(aControlId))->Duration();
	}

/**
 * @deprecated
 */
EXPORT_C void CEikDialog::SetTimeOffsetEditorMinAndMax(TInt aControlId, const TTimeIntervalSeconds& aMinimumTimeOffset, const TTimeIntervalSeconds& aMaximumTimeOffset)
	{
	CEikTimeOffsetEditor* timeOffsetEditor=(CEikTimeOffsetEditor*)Control(aControlId);
	timeOffsetEditor->SetMinimumAndMaximum(aMinimumTimeOffset, aMaximumTimeOffset);
	timeOffsetEditor->DrawNow();
	}

/**
 * @deprecated
 */
EXPORT_C void CEikDialog::SetTimeOffsetEditorValue(TInt aControlId, const TTimeIntervalSeconds& aTimeOffset)
	{
	CEikTimeOffsetEditor* timeOffsetEditor=(CEikTimeOffsetEditor*)Control(aControlId);
	timeOffsetEditor->SetTimeOffset(aTimeOffset);
	timeOffsetEditor->DrawNow();
	}

/**
 * @deprecated
 */
EXPORT_C TTimeIntervalSeconds CEikDialog::TimeOffsetEditorValue(TInt aControlId) const
	{
	return ((CEikTimeOffsetEditor*)Control(aControlId))->TimeOffset();
	}

/**
 * @deprecated
 */
/*EXPORT_C void CEikDialog::SetLatitudeEditorValue(TInt aControlId, const SEikDegreesMinutesDirection& aLatitude)
	{
	CEikLatitudeEditor* latitudeEditor=(CEikLatitudeEditor*)Control(aControlId);
	latitudeEditor->SetLatitude(aLatitude);
	latitudeEditor->DrawNow();
	}
*/
/**
 * @deprecated
 */
/*EXPORT_C SEikDegreesMinutesDirection CEikDialog::LatitudeEditorValue(TInt aControlId) const
	{
	return ((CEikLatitudeEditor*)Control(aControlId))->Latitude();
	}
*/
/**
 * @deprecated
 */
/*EXPORT_C void CEikDialog::SetLongitudeEditorValue(TInt aControlId, const SEikDegreesMinutesDirection& aLongitude)
	{
	CEikLongitudeEditor* longitudeEditor=(CEikLongitudeEditor*)Control(aControlId);
	longitudeEditor->SetLongitude(aLongitude);
	longitudeEditor->DrawNow();
	}
*/
/**
 * @deprecated
 */
/*EXPORT_C SEikDegreesMinutesDirection CEikDialog::LongitudeEditorValue(TInt aControlId) const
	{
	return ((CEikLongitudeEditor*)Control(aControlId))->Longitude();
	}
*/
/**
 * @deprecated
 */
EXPORT_C void CEikDialog::GetFileName(TFileName* /*aFileName*/,TInt /*aControlId*/) const
	{}

/**
 * @deprecated
 */
EXPORT_C void CEikDialog::SetFileNameL(TInt /*aControlId*/, const TDesC* /*aFileName*/)
	{}

/**
 * @deprecated
 */
EXPORT_C void CEikDialog::GetAutoValuesFromPage(CEikCapCArray* /*aLines*/)
	{}


