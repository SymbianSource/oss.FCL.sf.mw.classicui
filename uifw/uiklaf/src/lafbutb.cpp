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


#include <coecntrl.h>
#include <coeinput.h>

#include "LAFBUTB.H"

EXPORT_C TInt LafButtonBase::InputCapabilities()
	{ // static
	return TCoeInputCapabilities::ENavigation;
	}

/**
 * Returns the bubble help state the control aControl should set in response to the pointer event
 * aPointerEvent. Called from the HandlePointerEventL implmenetation for the matched control which will
 * trigger, cancel or cancel the triggering of bubble help on return of the method.
 *
 * @since App-Framework_6.1
 */
EXPORT_C LafButtonBase::TBubbleHelpState LafButtonBase::BubbleHelpState(const CCoeControl& /*aControl*/,const TPointerEvent& /*aPointerEvent*/,TBool /*aReportOnPointerDown*/)
	{ // static
	return ENone;
	}

/**
 * Returns ETrue if the button should report activation while bubble help for the button is being displayed.
 * Called while processing a pointer event in the button.
 *
 * @since App-Framework_6.1
 */
EXPORT_C TBool LafButtonBase::ReportIfBubbleHelpDisplaying()
	// static
	{
	return ETrue;
	}
