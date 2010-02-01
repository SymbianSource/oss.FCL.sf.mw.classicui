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
* Description:  E32Dll and Panic definitions.
*
*/


// INCLUDE FILES
#include <e32base.h>
#include "AknJapaneseReadingDll.h"

// -----------------------------------------------------------------------------
// Static DLL functions
// -----------------------------------------------------------------------------
//

GLDEF_C void Panic(TAknJapaneseReadingPanic aPanic)
    {
    _LIT(KPanicDll,"AknJapaneseReading");
    User::Panic(KPanicDll, aPanic);
    }

// End of File
