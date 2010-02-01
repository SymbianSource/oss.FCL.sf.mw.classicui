/*
* Copyright (c) 2002-2007 Nokia Corporation and/or its subsidiary(-ies).
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

// EIKPANIC.H
//
// Copyright (c) 1997-2001 Symbian Ltd.  All rights reserved.
//

#if !defined(__AKNPANIC_H__)
#define __AKNPANIC_H__

#include <e32def.h>

/** Panic codes used throughout the code in Avkon library.
  * These panics have a category of AVKON.
  */
enum TAknPanic
	{
	/**
	 *  00: Invalid bitmap index is given to the list box.
	 */
	EAknPanicFormattedCellListInvalidBitmapIndex,
	/** 01: @deprecated */
	EAknPanicNoSuchControlInStack,
	/** 
	 *  02: Listbox object has not been defined for 
	 *  popup list (CAknPopupList).
	 */
	EAknPanicListboxUndefined,
	/** 03: @deprecated */
	EAknPanicListboxSizeIsNotAccordingToLAFSpec,
	/** 04: @deprecated */
	EAknPanicListboxShortcutValueNotHandled,
	/** 05: @deprecated */
	EAknPanicListboxShortcutInvalidValue,
	/**
	 *  06: Some value is out of valid range.
	 */
	EAknPanicOutOfRange,
	/** 07: @deprecated */
	EAknPanicListboxLayoutProblem,
	/** 08: @deprecated */
	EAknPanicLAF,
	/**
	 *  09:Query control type was not given in query resource.
	 */
	EAknPanicLayoutResourceProblem,
	/** 10: @deprecated */
	EAknPopupCorrupt,
	/**
	 *  11: Invalid NULL pointer value.
	 */
    EAknPanicNullPointer,
	/** 12: @deprecated */
	EAknPanicLayoutMismatchBetweenMarginsAndParentRect,
	/** 13: @deprecated */
	EAknPanicLayoutTextResourceProblem,
	/** 14: @deprecated */
	EAknPanicLayoutRectResourceProblem,
	/** 15: @deprecated */
	EAknPanicLayoutEdwinResourceProblem,
	/** 16: @deprecated */
	EAknPanicLayoutMfneResourceProblem,
	/** 
	 *  17: Query type of query control is invalid.
	 */
	EAknPanicLayoutControlResourceProblem,
	/** 18: @deprecated */
	EAknPanicLayoutIncorrectEdwinSize,
	/** 19: @deprecated */
	EAknPanicLayoutControlSetRectChangedControlSize,
	/**
	 *  20: Animation data was not given to the animation control (CAknAnimationCtrl).
	 */
	EAknPanicNoAnimationData,
	/** 21: Unsupported user animation type used */
	EAknPanicUnknownAnimationType,
	/** 22: A user animation is not found */
	EAknPanicNoUserAnimation,
	/** 23: Initialization of CAknAnimatedView failed. */
	EAknPanicAnimationCorrupt,
	/** 24: Invalid MdcaPoint index given. */
	EAknPanicDCADecoratorIndexOutOfRange,
	/** 25: @deprecated */
	EAknPanicPopupFieldListInvalidDecorator,
	/** 26: Invalid value set to CAknPopupField. */
	EAknPanicPopupFieldInvalidValue,
	/** 27: Uninitilized member in CAknPopupField. */
	EAknPanicPopupFieldUninitialisedMember,
	/** 28: @deprecated */
	EAknPanicPopupFieldEditComboInsufficientSize,
	/** 29: Invalid time format string used or 
	 *  memory allocation failure in formatting.
	 */
	EAknPanicQueryTimeArrayTimeFormatLeave,
	/** 30: TAknLayoutText is not initialized properly. */
	EAknPanicLayoutTextNotCalled,
	/** 31: TAknLayoutRect is not initialized properly. */
	EAknPanicLayoutRectNotCalled,
	/** 32: @deprecated */
	EAknStatusPaneUidIndic,
	/** 33: @deprecated */
	EAknPanicLayoutDoesNotExists,
	/** 34: Memory allocation failure in CAknListBoxLayoutDecorator. */
	EAknPanicListBoxLayoutDecoratorMemoryAllocation,
	/** 35: Unsupported CAknPopupField mode used. */
	EAknPanicPopupFieldUndefinedMode,
	/** 36: Wrong CAknPopupField mode used. */
	EAknPanicPopupFieldWrongMode,
	/** 37: Selection list object is missing from CAknPopupField. */
	EAknPanicPopupFieldSelectionListDoesntExist,
	/** 38: @deprecated */
	EAknPanicPopupFieldSelectionListAlreadyExists,
	/** 39: Depratead CAknPopupFieldList method called. */
	EAknPanicPopupFieldListNotImplemented,
	/** 40: Empty text array resource in CAknPopupFieldText. */
	EAknPanicPopupFieldArrayIsEmpty,
	/** 41: @deprecated */
	EAknPanicLayoutPopupFieldResourceProblem,
	/** 42: Invalid special character table characters set resources. */
	EAknPanicInvalidResourceData,
	/** 43: Listbox is not supported by the list query dialog. */
	EAknPanicListBoxNotSupportedByListQuery,
	/** 44: Invalid time format string used or 
	 *  memory allocation failure in formatting. 
	 */
	EAknPanicQueryDateArrayTimeFormatLeave,
	/** 45: CBA (softkeys) does not exist in the popup field component. */
	EAknPanicPopupFieldCBADoesntExist,
	/** 46: @deprecated */
	EAknPanicPopupSettingListMenuListDoesntExist,
	/** 47: @deprecated */
	EAknPanicPopupSettingListMenuListAlreadyExists,
	/** 48: @deprecated */
	EAknPanicPopupSettingListListNotImplemented,
	/** 49: @deprecated */
	EAknPanicLayoutPopupSettingListResourceProblem,
	/** 50: Invalid value was found in CAknPopupSettingList. */
	EAknPanicPopupSettingListInvalidValue,
	/** 51: Uninitialized member was found in CAknPopupSettingList. */
	EAknPanicPopupSettingListUninitialisedMember,
	/** 52: Overflow happened. */
	EAknPanicOverflow,
	/** 53: Key lock observed already added. Two observers are not supported. */
	EAknPanicKeyLockObserverAlreadyExists,
	/** 54: Key lock observer is not found. */
	EAknPanicKeyLockObserverNotFound,
	/** 55: Unsupported query mode requested. */
	EAknPanicQueryValueInvalidMode,
	/** 56: Unsupported feature requested. */
    EAknPanicNotSupported,
	/** 57: @deprecated */
	EAknPanicWrongListBoxTypeUsedInPopupWindow,
	/** 58: Invalid value */
	EAknPanicInvalidValue,
	/** 59: Construction of an object has been failed. */
	EAknPanicObjectNotFullyConstructed,
	/** 60: Self check failure. */
	EAknPanicSelfCheckFailure,
	/** 61: Failure in layout configuration. Layout data is not found. */
	EAknPanicLayoutMissing_AknLayout,
	/** 
	 *  62: Failure in APAC variant configuration. Usually the panic happens if 
	 *  western language code is used as a UI language in APAC variant. 
	 */
	EAknPanicLayoutMissing_ApacLayout,
	/** 
	 *  63: Panic in AknPhoneNumberTextUtils::ClipLineOnLeft(...) if
	 *  the input 'aLine' is not encompassed within the modifiable buffer
	 *   'aOriginalBuffer'.
	 */
    EAknPanicInconsistentDescriptors,
    /** 64: ItemDrawer of the listbox does not exist */
    EAknPanicListBoxItemDrawerNotCreated,
	/** 65: @deprecated */
    EAknPanicLayoutMissing_CdlFont,
    /** 66: Invalid font type. */
    EAknPanicFontProvisionFailure,
	/** 67: @deprecated */
    EAknPanicNotifierPluginCreationFailure,
    /** 68: Parent rectangle of CAknPopupField is not set. */
	EAknPanicPopupFieldNoFieldRectSet,
	/** 69: @deprecated */	
	EAknPanicWindowGroupNotInTaskList,
	/** 70: TAknFontSpecification unit differs from TAknFontSpecification::EPixels. */
	EAknPanicInconsistentUnits,
	/** 71: List object is missing from radio button setting page. */
    EAknPanicRadioButtonSettingPageListDoesntExist,
	/** 
	 *  72: Requested screen mode index does not exist in the layout
	 *  configuration data of the device.
	 */
	EAknPanicLayoutConfigBadScreenModeIndex,
	/** 73: Requested hardware state index does not exist in the layout
	 *  configuration data of the device.
	 */
	EAknPanicLayoutConfigBadHardwareStateIndex,
	/** 74: Layout configuration data of the device is not available. */
	EAknPanicSgccLayoutConfigNull,
	/** 75: Failure in the layout configuration of the device. */
	EAknPanicLayoutConfigUnpackFail,
	/** 76: CAknSgcClient singleton object is not found. */
	EAknPanicSgccNull
	};

GLREF_C void Panic(TAknPanic aPanic);

#endif
