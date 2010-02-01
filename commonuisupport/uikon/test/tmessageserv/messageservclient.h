// Copyright (c) 2005-2009 Nokia Corporation and/or its subsidiary(-ies).
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

/**
 @file
 @internalComponent - Internal Symbian test code 
*/



#ifndef	__MESSAGESERVCLIENT_H
#define	__MESSAGESERVCLIENT_H

#include <e32base.h>

class RMessageServ : public RSessionBase
	{
public:
	IMPORT_C RMessageServ();
	IMPORT_C TInt Connect();
	TVersion Version() const;
	IMPORT_C TInt Stop();
	IMPORT_C TInt SetFromString(const TDesC& aString, const TText8* aString1, 
		TInt aLineNumber);
	IMPORT_C TInt SetErrorFromString(const TDesC& aString, const TText8* aString1, 
		TInt aLineNumber, TInt aErr);
	};
	
#endif
