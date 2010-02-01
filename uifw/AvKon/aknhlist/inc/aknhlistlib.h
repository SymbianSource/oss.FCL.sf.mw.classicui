/*
* Copyright (c) 2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Panic function for aknhlist library.
*
*/


#ifndef AKNHLISTLIB_H
#define AKNHLISTLIB_H


#include <e32def.h>
#include <aknhlistpanic.h>


/**
 * Global function for raising a panic with AKNHLIST category.
 * 
 * @param aPanic Panic code.
 */
GLREF_C void Panic( TAknHListPanic aPanic );


#endif // AKNHLISTLIB_H
