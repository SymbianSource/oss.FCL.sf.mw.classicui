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








#ifndef __ASSERT_TOOLS_H__
#define __ASSERT_TOOLS_H__

#include <e32std.h>
#include <e32base.h>

struct AssertTool{
    static TBool AssertNotNull(void* aPtr){ return aPtr!=NULL; }
    static TBool AssertTrue(TBool aValue) { return aValue; }
};

#endif //#ifndef __ASSERT_TOOLS_H__