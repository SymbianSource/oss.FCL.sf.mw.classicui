/*
* Copyright (c) 2002-2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Definitions for AVKON's window server and
*                resource change messages.
*
*/


#ifndef AKNDEF_H
#define AKNDEF_H

#include <AknDef.hrh>
#include <e32std.h>

// forward declarations
class TVwsViewId;

/**
 * Resource change message that is passed to applications
 * when all the windows become faded or unfaded.
 */
const TInt KEikMessageWindowsFadeChange = 0x10006890;

/**
 * Resource change message indicating a change of state to edit mode.
 * This message is used by @c CEikCaptionedControl to handle situations
 * where the control becomes editable.
 */
const TInt KEikMessageCaptionedControlEditableStateChange = 0x10008E99;

/**
 * Resource change message indicating a change of state to view mode.
 * This message is used by @c CEikCaptionedControl to handle situations
 * where the control becomes non-editable.
 */
const TInt KEikMessageCaptionedControlNotEditableStateChange = 0x10008E9A;

/**
 * Resource change message indicating a change of state to edit mode with graphic.
 * This message is used by popup fields to handle situations where the
 * control becomes editable with graphic.
 */
const TInt KEikMessageCaptionedControlEditableStateChangeWideWithGraphic = 0x101F5FBA;

/**
 * Resource change message indicating a change of state to edit mode without graphic.
 * This message is used by popup fields to handle situations where the
 * control becomes editable without graphic.
 */
const TInt KEikMessageCaptionedControlEditableStateChangeWideWithoutGraphic = 0x101F5FBB;

/**
 * Resource change message indicating a change of state to view mode with graphic.
 * This message is used by popup fields to handle situations where the
 * control becomes non-editable with graphic.
 */
const TInt KEikMessageCaptionedControlNotEditableStateChangeWideWithGraphic = 0x101F5FBC;

/**
 * Resource change message indicating a change of state to view mode without graphic.
 * This message is used by popup fields to handle situations where the
 * control becomes non-editable without graphic.
 */
const TInt KEikMessageCaptionedControlNotEditableStateChangeWideWithoutGraphic = 0x101F5FBD;

/**
 * Window server event for clearing partial foreground state.
 *
 * @internal
 */
const TInt KEikClearPartialForegroundState = 0x101f54f4;

/**
 * Window server event for partial foreground state.
 *
 * @internal
 */
const TInt KEikPartialForeground = 0x101f6aab;

/** Resource change message used to inform applications of layout change. */
const TInt KEikDynamicLayoutVariantSwitch = 0x101F8121;

/** @deprecated */
const TInt KEikDynamicLayoutVariantSwitch_APAC = 0x101F8124;

/** Resource change message that is sent by FEP when the input language changes. */
const TInt KEikInputLanguageChange = 0x101F8519;

/** The application UID and the view UID of the Application Shell */
#define KAknApplicationShellViewId TVwsViewId(TUid::Uid(0x101F4CD2), TUid::Uid(0x00000001))

/**
 * Window server event used when layout changes. This event is not passed to applications,
 * they should use the @c KEikDynamicLayoutVariantSwitch event instead.
 *
 * @internal
 */
const TInt KAknHardwareLayoutSwitch = 0x10202672;

/** @deprecated */
const TInt KAknDelayedLayoutSwitch = 0x102797FD;

/** Window server event used to inform applications about change in local zoom setting. */
const TInt KAknLocalZoomLayoutSwitch = 0x10281FC1;

/**
 * Window server event used to inform applications that a new ILD 
 * (Independent Layout Delivery) layout DLL has been installed. 
 * This event is not passed to applications, they should use 
 * the @c KEikDynamicLayoutVariantSwitch event instead.
 *
 * @internal
 */
const TInt KAknILDInstallationLayoutSwitch = 0x1028654F;

/** @deprecated */
const TInt KAknAppOomMonitor_FreeRam = 0x10282304;

/** @deprecated */
const TInt KAknAppOomMonitor_MemoryGood = 0x10282305;

/**
 * Resource change message used to inform a window group that it has
 * gained full or partial foreground.
 */
const TInt KAknFullOrPartialForegroundGained = 0x10281F36;

/**
 * Resource change message used to inform a window group that it has
 * lost full or partial foreground.
 */
const TInt KAknFullOrPartialForegroundLost = 0x10281F37;

/**
 * Instruct an app to either exit or hide itself, according to its configuration
 */
const TInt KAknShutOrHideApp = 0x10285A1D;

 
namespace AknDef
    {
    /**
     * Returns the application UID and the view UID of the currently active idle state
     * application in form of a @c TVwsViewId object. Alternatives 
     * include Phone application and Idle application.
     *
     * @since S60 2.8
     * @param[out] aViewId The view uid of currently active idle state application.
     * @return @c KErrNone, if succesful
     */
    IMPORT_C TInt GetPhoneIdleViewId(TVwsViewId& aViewId);
    }

#endif // AKNDEF_H
