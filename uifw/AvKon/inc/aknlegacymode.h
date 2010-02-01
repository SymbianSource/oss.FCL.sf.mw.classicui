/*
* Copyright (c) 2002 Nokia Corporation and/or its subsidiary(-ies).
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
*       Support for compability mode in 208x208 screen mode
* 
*
*/


#ifndef __AKNLEGACYMODE_H__
#define __AKNLEGACYMODE_H__

#include <e32base.h>

class CSideControl;

NONSHARABLE_CLASS(CAknLegacyMode) : public CBase
    {
public:
    IMPORT_C static CAknLegacyMode *NewL();
    IMPORT_C ~CAknLegacyMode();
    };

#endif
