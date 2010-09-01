/*
* Copyright (c) 2002-2004 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Panic definitions.
*
*/


#ifndef __AknJapaneseReadingDll_h__
#define __AknJapaneseReadingDll_h__

#include <e32std.h>

enum TAknJapaneseReadingPanic
    {
    EAknJapaneseReadingNotPrepared
    };

GLDEF_C void Panic(TAknJapaneseReadingPanic aPanic);

#endif // __AknJapaneseReadingDll_h__
// End of file
