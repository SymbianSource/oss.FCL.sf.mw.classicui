// Copyright (c) 2007-2009 Nokia Corporation and/or its subsidiary(-ies).
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

#include <e32base.h>

/**
This 16-bit variable is used to define the polling frequency for the derived UIKON
backup server file lock and application closing notification timer.

If a derived UIKON backup server makes a call to CloseAllFiles, a timer will be 
started to periodically check if all file lock notifications have been processed and
all non-server programs have been shut down. If all files and applications are closed
or the timer expires 3 times the CloseAllFiles function call will be completed.

This variable defines the period of that timer.

The default value is 5 seconds - leading to a default maximum of 15 seconds for file lock
changes to be processed and applications to be shut in a UIKON derived backup server.

This variable is changed at ROM build time using the patchdata obey keyword.
See Symbian OS Developer Library documentation on how to patch DLL data exports.

@publishedPartner
@released
*/

IMPORT_C extern const TInt KUIKONBackupCloseAllFilesTimeout;

