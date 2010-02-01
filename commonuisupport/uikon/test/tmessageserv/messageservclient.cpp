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

#include "messageservclient.h"
#include "messageservserver.h"

const TUint kDefaultMessageSlots=4;

EXPORT_C RMessageServ::RMessageServ()
	{
	}

// Connect to the  server - default number of message slots = 4
EXPORT_C TInt RMessageServ::Connect()
	{
	TInt r=KErrNone;
	if (r==KErrNone)
		r=CreateSession(KMessageServerName,Version(),kDefaultMessageSlots);
	return(r); 
	}

	
// Return the client side version number.
TVersion RMessageServ::Version(void) const
	{
	return(TVersion(KMessageServMajorVersionNumber,KMessageServMinorVersionNumber,KMessageServBuildVersionNumber));
	}

// send message to server
//first parameter is message to log, second filename, third - number of line
EXPORT_C TInt RMessageServ::SetFromString(const TDesC& aString, const TText8* aString1, 
								 TInt aLineNumber)
	{

	TBuf8<256>	buf;
	buf.Copy(aString1);

	TIpcArgs	theArg(&aString, &buf, aLineNumber);
	
	return SendReceive(EMessageServSetFromString, theArg);
	}

// send error message to server
//first parameter is message to log, second filename, third - number of line,
// fourth param is error code
EXPORT_C TInt RMessageServ::SetErrorFromString(const TDesC& aString, const TText8* aString1, 
								 TInt aLineNumber, TInt aErr)
	{

	TBuf8<256>	buf;
	buf.Copy(aString1);
	TIpcArgs	theArg(&aString, &buf, aLineNumber, aErr); 
	return SendReceive(EMessageServSetErrorFromString, theArg);
	}

//stop the server. This is implemented in the server ; server closes the thread by 
//stopping active scheduler.
EXPORT_C TInt RMessageServ::Stop()
	{
	TIpcArgs	theArg;
	return SendReceive(EMessageServStop,theArg);
	}
