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

#ifndef __COEERROR_H__
#define __COEERROR_H__
#ifndef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <graphics/cone/coeerrorconsts.h>
#endif //SYMBIAN_ENABLE_SPLIT_HEADERS

/** UI Control Framework errors.

@publishedAll
@deprecated */
enum
	{
	/** Not used. */
	KErrCoeResourceFileDuplicateOffset,
	/** Read fail. CCoeEnv::ReadResource() sets this as the
	active scheduler's extended error number if the read fails.	*/
	KErrCoeFailedToReadFromProgDisk
	};

#endif	// __COEERROR_H__

