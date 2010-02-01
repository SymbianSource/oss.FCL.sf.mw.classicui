/*
* Copyright (c) 2005 Nokia Corporation and/or its subsidiary(-ies).
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


// INCLUDE FILES

#include "AknSystemFont.h"
#include <AknLayoutFont.h> // For destructor

EXPORT_C CLafSystemFont* CLafSystemFont::NewL(TUid aUid, CAknLayoutFont* aFont)
    {
    return new(ELeave) CLafSystemFont(aUid, aFont);
    }

CLafSystemFont::CLafSystemFont(TUid aUid, CAknLayoutFont* aFont)
: iUid(aUid), iFont(aFont)
	{
	}

CLafSystemFont::~CLafSystemFont()
    {
    delete iFont;
    }

EXPORT_C TUid CLafSystemFont::Uid() const
	{
	return iUid;
	}

EXPORT_C CFont* CLafSystemFont::Font() const
	{
	return iFont;
	}


//  End of File  


