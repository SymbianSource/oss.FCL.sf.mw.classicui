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


#if !defined(__EIKMFNE_PAN__)
#define __EIKMFNE_PAN__

enum TEikMfnePanic
	{
	EEikPanicMfneFieldIsNotEditable1,
	EEikPanicMfneFieldIsNotEditable2,
	EEikPanicMfneFieldIsNotEditable3,
	EEikPanicMfneArrowKeyExpected,
	EEikPanicMfneSeparatorTextHasAlreadyBeenSet,
	EEikPanicMfneBadNumberFlags,
	EEikPanicMfneInconsistentNumberFlags,
	EEikPanicMfneBadNumberMinimumAndMaximum1,
	EEikPanicMfneBadNumberMinimumAndMaximum2,
	EEikPanicMfneBadNumberMinimumAndMaximum3,
	EEikPanicMfneUnexpectedMinusSign,
	EEikPanicMfneNumberOutsidePermittedRange,
	EEikPanicMfneNumberTextInBadState,
	EEikPanicMfneNumberHasNoDigits,
	EEikPanicMfneDigitExpected,
	EEikPanicMfneTooFewSymbolicItems,
	EEikPanicMfneSymbolicItemArrayNotCreated,
	EEikPanicMfneTooManySymbolicItemsAdded,
	EEikPanicMfneIdOfSymbolicItemNotFound,
	EEikPanicMfneSymbolicItemTextHasAlreadyBeenSet,
	EEikPanicMfneFieldArrayAlreadyCreated,
	EEikPanicMfneTooFewFields,
	EEikPanicMfneFieldArrayNotCreated,
	EEikPanicMfneTooManyFieldsAdded,
	EEikPanicMfneInverseVideoHighlightTypeExpected,
	EEikPanicMfneBadCursorState1,
	EEikPanicMfneBadCursorState2,
	EEikPanicMfneBadCursorState3,
	EEikPanicMfneNegativeDuration,
	EEikPanicMfneBadSize,
	EEikPanicMfneNoControlContext,
	EEikPanicMfneBadRangeToDraw,
	EEikPanicRangeEditorInconsistentMinimumAndMaximum,
	EEikPanicDateEditorBadTimeFormat,
	EEikPanicDateEditorBadTabButtonHeight,
	EEikPanicDateEditorBadDateFormat,
	EEikPanicDateEditorBadDateElementPosition,
	EEikPanicDateEditorNoMoreDateElements,
	EEikPanicTimeEditorBadMinimumAndMaximum1,
	EEikPanicTimeEditorBadMinimumAndMaximum2,
	EEikPanicDateEditorBadMinimumAndMaximum1,
	EEikPanicDateEditorBadMinimumAndMaximum2,
	EEikPanicDateEditorBadComponentControlIndex,
	EEikPanicTimeAndDateEditorBadMinimumAndMaximum1,
	EEikPanicTimeAndDateEditorBadMinimumAndMaximum2,
	EEikPanicTimeAndDateEditor,
	EEikPanicTimeAndDateEditorBadComponentControlIndex,
	EEikPanicDurationEditorBadMinimumAndMaximum1,
	EEikPanicDurationEditorBadMinimumAndMaximum2,
	EEikPanicTimeOffsetEditorBadMinimumAndMaximum1,
	EEikPanicTimeOffsetEditorBadMinimumAndMaximum2,
	EEikPanicLatitudeLongitudeEditorBaseBadValues1,
	EEikPanicLatitudeLongitudeEditorBaseBadValues2,
	EEikPanicLatitudeEditorBadDirection,
	EEikPanicLongitudeEditorBadDirection,
	EEikPanicDirectionAlreadyAdded,
	EEikPanicDateEditorBadMinimum,
	EEikPanicDateEditorBadMaximum
	};

GLREF_C void Panic(TEikMfnePanic aPanic);

#endif

