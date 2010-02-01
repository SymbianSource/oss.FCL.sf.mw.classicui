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
* Description:         Invoke CAknForm's protected APIs.
*
*/









#ifndef C_CBCTESTSUBAKNFORM_H
#define C_CBCTESTSUBAKNFORM_H

#include <aknform.h>

/**
 * Invoke CAknForm's protected APIs
 */
class CBCTestSubAknForm: public CAknForm
    {
    
    friend class CBCTestEikCaptionedControlCase;    
    
    };

#endif // C_CBCTESTSUBAKNFORM_H
