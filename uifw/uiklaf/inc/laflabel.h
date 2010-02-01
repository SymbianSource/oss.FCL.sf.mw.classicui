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


#ifndef __LAFLABEL_H__
#define __LAFLABEL_H__

#include <e32std.h>

/**
 * @since App-framework_6.1
 * @internal
 * Do not use
 */
class LafLabel
	{
public:
	inline static TInt DefaultGapBetweenLines();
private:
	enum TConstantType
		{
		EDefaultGapBetweenLines
		};
private:
	IMPORT_C static TInt Constant(TConstantType aConstant);
	};

/**
 * Returns the default pixel spacing between two lines in a label
 */
inline TInt LafLabel::DefaultGapBetweenLines()
	{//static	
	return Constant(EDefaultGapBetweenLines);	
	}

#endif  //__LAFLABEL_H__
