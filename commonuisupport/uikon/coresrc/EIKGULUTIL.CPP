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

#include <gulutil.h>
#include <gulcolor.h>
#include <eikenv.h>


EXPORT_C CColorList* ColorUtils::CreateSystemColorListL(RFs&)
/** Creates and returns a system colour list, which is a palette of standard 
colours used by the system.

The list is read from a system colour scheme file. The function returns NULL
if no such file can be found. In this case, clients are expected to create 
the list using some other means (typically from a resource file).

Note that this method is implemented in eikcore.dll and clients should link
to eikcore.lib.

@deprecated
@see CEikonEnv::CreateSystemColorListL

@param aFs The file server session.
@return Pointer to the system colour list.*/
	{ // static
	return CEikonEnv::Static()->CreateSystemColorListL();
	}

EXPORT_C CColorList* ColorUtils::CreateSystemColorListL(RFs&,const CColorList& aColorList)
/** Creates a system colour list, using the other overload of this function 
and merges it with the colour list specified.

Note that this method is implemented in eikcore.dll and clients should link
to eikcore.lib.

@deprecated
@see CEikonEnv::CreateSystemColorListL

@param aFs The file server session.
@param aColorList The color list to merge in.
@return Pointer to the system colour list. */
	{ // static
	return CEikonEnv::Static()->CreateSystemColorListL(aColorList);
	}

//
// Writes aColorList out to file.  Callers are responsible for broadcasting a scheme
// changed message after calling this.
//
EXPORT_C void ColorUtils::UpdateSystemColorListL(RFs&,CColorList& aColorList)
/** Replaces the system colour list with the list specified.

If no system colour list exists, one is created.

Note that this method is implemented in eikcore.dll and clients should link
to eikcore.lib.

@deprecated
@see CEikonEnv::UpdateSystemColorListL

@param aFs The file server session.
@param aColorList The new colour list.
@capability WriteDeviceData		To protect against tampering.
*/
	{ // static
	return CEikonEnv::Static()->UpdateSystemColorListL(aColorList);
	}

