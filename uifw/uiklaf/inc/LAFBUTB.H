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


#ifndef __LAFBUTB_H__
#define __LAFBUTB_H__

#include <e32std.h>

#define ELafButBaseDrawClear				0x00
#define ELafButBaseDrawSet					0x01
#define ELafButBaseDrawIndeterminate		0x02
#define ELafButBaseDrawClearPressed			0x10
#define ELafButBaseDrawSetPressed			0x11
#define ELafButBaseDrawIndeterminatePressed	0x12

/**
 * @internal
 * Do not use
 */
class LafButtonBase
	{
public:
	enum TBubbleHelpState
		{
		ENone,
		ETrigger,
		ECancelTrigger,
		ECancel
		};
public:
	IMPORT_C static TInt InputCapabilities();
	IMPORT_C static TBubbleHelpState BubbleHelpState(const CCoeControl& aControl,const TPointerEvent& aPointerEvent,TBool aReportOnPointerDown);
	IMPORT_C static TBool ReportIfBubbleHelpDisplaying();
	};

#endif
