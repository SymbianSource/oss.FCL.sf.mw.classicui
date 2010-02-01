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
* Description:         container
*
*/









#include <aknbutton.h>

#include "bctestbuttoncase.h"

class CAknButton;
class CAknButtonState;

class CAknButtonStateEx: public CAknButtonState
    {
    friend class CBCTestButtonCase;
public: // constructor and destructor

    /**
    * Constructor
    */
    CAknButtonStateEx( const TInt aFlags );

    /**
    * Destructor
    */
    virtual ~CAknButtonStateEx();

    };

class CAknButtonEx: public CAknButton
    {
    friend class CBCTestButtonCase;
public:

    /**
    * Constructor
    */
    CAknButtonEx( const TInt aFlags );

    /**
    * Destructor
    */
    virtual ~CAknButtonEx();
    };
