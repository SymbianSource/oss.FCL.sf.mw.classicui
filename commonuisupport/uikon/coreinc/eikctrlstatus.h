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

#ifndef EIKCTRLSTATUS_H
#define EIKCTRLSTATUS_H

/** Flags to determine the control status.

@publishedPartner
@released
*/
enum
	{
	/** Flag to determine whether a control has ears. Ears are triangular buttons
	for moving forwards or backwards through the list. */
	EEikControlHasEars=0x01,
	/** Flag to determine whether the control is unable to receive keyboard focus. */
	EEikControlIsNonFocusing=0x02,
	/** Flag to determine whether the control is higher than a normal control. */
	EEikControlHasExtraAscent=0x04,
	/** Flag to determine if a control should be placed directly
	 in the view/dialog or if it should be placed in a pop-out control. */
	EEikControlIsNonEditInPlace=0x08
	};

#endif	// EIKCTRLSTATUS_H
