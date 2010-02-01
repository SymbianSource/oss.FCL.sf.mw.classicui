/*
* Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:         AknToolbar derived class
*
*/









#ifndef C_BCTESTTOOLBARDERIVED_H
#define C_BCTESTTOOLBARDERIVED_H

#include <akntoolbar.h>


class CBCTestToolBarCase;
class CAknToolbar;

class CBCTestToolBarDerived: public CAknToolbar
    {
    friend class CBCTestToolBarCase;
public:
    virtual ~CBCTestToolBarDerived();
    };

#endif // C_BCTESTTOOLBARDERIVED_H
