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

#ifndef EIKENVINTERFACE_H
#define EIKENVINTERFACE_H

#include <eikdgfty.h>
#include <eiklibry.h>

class CEikLibrary;
class CEikDialog;
class CCoeControl;


/**
Creates the CEikLibrary interface object by calling the first ordinal function which is mapped to NewL method.

The function leaves with KErrBadLibraryEntryPoint if the ordinal 1 function 
cannot be found.

@publishedPartner
@released
*/
typedef CEikLibrary* (*EikLibraryEntryPoint)();

#include <uikon/eikenvinterface.inl>

#endif	// EIKENVINTERFACE_H
