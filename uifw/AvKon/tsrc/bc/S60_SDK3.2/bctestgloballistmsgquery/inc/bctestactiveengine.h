/*
* Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Active engine helper class declaration for BCTestGlobalListMsgQuery.
*
*/

#ifndef BCTESTACTIVEENGINE_H
#define BCTESTACTIVEENGINE_H

// INCLUDES
#include <e32base.h>

// CLASS DECLARATION

/**
* CBCTestActiveEngine application class.
*/
class CBCTestActiveEngine : public CActive
    {
public: 
    CBCTestActiveEngine();
    virtual ~CBCTestActiveEngine();

public:
    TRequestStatus* GetStatus();
    TBool Active();
    void MakeActive();

protected: // From CActive
    void RunL();
    void DoCancel();
    };

#endif

// End of file
