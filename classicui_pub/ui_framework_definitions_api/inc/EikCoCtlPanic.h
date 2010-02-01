/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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
// EIKCOCTLPANIC.H
//
#if !defined(__EIKCOCTL_PAN__)
#define __EIKCOCTL_PAN__
enum TEikCoCtlPanic
	{
	EEikPanicColumnListLayoutError,
	EEikPanicInvalidUseOfListBoxShortcuts,
	EEikPanicUnexpectedSpaces,
	EEikPanicScrollBarExtensionNotCreated,
	EEikPanicListBoxItemDrawerNotCreated,
	EEikPanicObjectNotFullyConstructed,
	};
#endif

GLREF_C void Panic(TEikCoCtlPanic aPanic);