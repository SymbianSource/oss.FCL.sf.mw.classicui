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

#ifndef EIKSRVSCONSTS_H
#define EIKSRVSCONSTS_H

/**
@internalComponent
*/
const TInt KEikSrvDefaultHeapSize=0x10000;

/**
@internalComponent
*/
const TInt KEikSrvDefaultMaxHeapSize=0x100000;

/** 
@internalComponent
*/
typedef TThreadFunction* (*EikSrvEntrypoint)();

/**
function to panic the server

@internalComponent
*/
GLREF_C void PanicServer(TEikAppUiServPanic aPanic);

#endif /* EIKSRVSCONSTS_H */
