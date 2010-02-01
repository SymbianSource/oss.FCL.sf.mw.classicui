// Copyright (c) 1997-2009 Nokia Corporation and/or its subsidiary(-ies).
// All rights reserved.
// This component and the accompanying materials are made available
// under the terms of "Eclipse Public License v1.0"
// which accompanies this distribution, and is available
// at the URL "http://www.eclipse.org/legal/epl-v10.html".
//
// Initial Contributors:
// Nokia Corporation - initial contribution.
//
// Contributors:
//
// Description:
//

#ifndef __EIKPANIC_H__
#define __EIKPANIC_H__

/**
@publishedPartner
@released
*/
enum TEikPanic
	{
	EEikPanicInvalidPreviewPageNumber,
	EEikPanicStartupHeapTooSmall,
	EEikPanicNoLibraryOnCommandLine,
	EEikPanicNoDocumentOnCommandLine,
	EEikPanicAlertTextTooLong,
	EEikPanicCursorControlNotFocused,
	EEikPanicControlNotCursorOwner,
	EEikPanicNoHotKeyToRemove,
	EEikPanicNoSuchMenuItem,
	EEikPanicInvalidMenuPane,
	EEikPanicMenuBarTitleUpdateNotSupported,
	EEikPanicInvalidBounds,
	EEikPanicUnknownPlaybackCommand,
	EEikPanicSecretEditorTooLong,
	EEikPanicInvalidClockSize,
	EEikPanicInvalidClockType,
	EEikPanicInvalidClockSettings,
	EEikPanicScrollBarDoesNotExist,
	EEikPanicScrollBarManagerDoesNotExist,
	EEikPanicButtonArrayHigherThanScreen,
	EEikPanicButtonArrayWiderThanScreen,
	EEikPanicBArrayLengthExceeded,
	EEikPanicWorldManager,
	EEikPanicWorldSelector,
	EEikPanicWorldControllerDuplicateSelector,
	EEikPanicOutOfRange,
	EEikPanicNullPointer,
	EEikPanicWrongDisplayMode,
	EEikPanicCalendarInvalidResourceValue,
	EEikPanicPrintPreviewInvalidResourceValue,
	EEikPanicFieldDoesNotExist,
	EEikPanicEditComboInsufficientSize,
	EEikPanicInvalidNumberOfRowsOrColumns,
	EEikPanicButtonHasNoComponent,
    EEikPanicFSelNoSuchFolder,
	EEikPanicToolBarHasNoObserver,
	EEikPanicToolBarNullControl,
	EEikPanicNoSuchDialogPage,
	EEikPanicOverlongEikonServerMessage,
	EEikPanicCtGroupInvalidDimension,
	EEikPanicCtGroupInvalidNumberOfLines,
	EEikPanicCtGroupInsufficientInitialisation,
	EEikPanicColumnListInvalidBitmapIndex,
	EEikPanicHeaderFooterNullFileName,
	EEikPanicProcessNoStore,
	EEikPanicProcessWrongStoreType,
	EEikPanicDialogToolBarNoObserver,
	EEikPanicLabeledButtonInvalidHotKey,
	EEikPanicLabeledButtonInvalidButtonType,
	EEikPanicIllegalCrop,
	EEikPanicTimeNoDataForDialog,
	EEikPanicDtmfPlayerActive,
	EEikPanicNothingToDial,
	EEikPanicLogicalColorNotFound,
	EEikPanicLogicalColorAlreadyExists,
	EEikPanicInvalidColorRange,
	EEikPanicAppColorArrayNotFound,
	EEikPanicLabelNullText,
	EEikPanicNoLibraryEntryPoint,
	EEikPanicResourceFileNotRemoved,
	EEikPanicControlFactoryNotRemoved,
	EEikPanicButtonGroupDuplicateCleanupPos,
	EEikPanicButtonGroupCleanupCorrupt,
	EEikPanicButtonGroupDuplicateObserver,
	EEikPanicBadInlineEditingState1,
	EEikPanicBadInlineEditingState2,
	EEikPanicBadInlineEditingState3,
	EEikPanicBadInlineEditingState4,
	EEikPanicBadInlineEditingState5,
	EEikPanicBadInlineEditingState6,
	EEikPanicBadInlineEditingState7,
	EEikPanicBadInlineEditingState8,
	EEikPanicBadInlineEditingState9,
	EEikPanicBadInlineEditingState10,
	EEikPanicBadInlineEditingState11,
	EEikPanicBadInlineEditingState12,
	EEikPanicNoSuchMenuTitle,
	EEikPanicLibraryNotLoaded,
	EEikPanicScrollBarFrameNullScrollBar,
	EEikPanicAppUiNotConstructed,
	EEikPanicVirtualCursorLeaveNotExpected,
	EEikPanicCommandStackIsNull,
	EEikPanicVirtualCursorUndefinedError,
	EEikPanicCbaButtonInvalidId,
	EEikPanicNoButtonGroupFactory,
	EEikPanicButtonGroupNotFoundInFactory,
	EEikPanicListItemDrawerGraphicsContextIsNull,
	EEikPanicInvalidNumberOfLines,
	EEikPanicArrayLengthExceeded,
	EEikPanicInvalidIndex,
	EEikPanicInvalidLength,
	EEikPanicDebugKeysAlreadySet,
	};

/**
@publishedPartner
@released
*/
GLREF_C void Panic(TEikPanic aPanic);

#endif	// __EIKPANIC_H__
