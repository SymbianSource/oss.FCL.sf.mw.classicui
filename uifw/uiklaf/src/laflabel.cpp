/*
* Copyright (c) 1997-2000 Nokia Corporation and/or its subsidiary(-ies).
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


#include "laflabel.h"
#include "LAFSTD.H"

const TInt KLafLabelDefaultGapBetweenLines = 1;

/**
 * @internal
 */
EXPORT_C TInt LafLabel::Constant(TConstantType aConstant)
	{// static
	TInt retValue = 0;
	switch (aConstant)
		{
	case EDefaultGapBetweenLines:
		retValue = KLafLabelDefaultGapBetweenLines;
		break;
	default:
		__ASSERT_DEBUG(EFalse, Panic(ELafPanicConstantNotKnown));
		break;
		}
	return retValue;
	}
