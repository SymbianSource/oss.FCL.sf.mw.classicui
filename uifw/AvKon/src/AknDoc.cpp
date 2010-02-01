/*
* Copyright (c) 2002 Nokia Corporation and/or its subsidiary(-ies).
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

#include "AknDoc.h"

EXPORT_C CFileStore* CAknDocument::OpenFileL(TBool /*aDoOpen*/,const TDesC& /*aFilename*/,RFs& /*aFs*/)
	{
	return NULL;
	}

EXPORT_C void CAknDocument::OpenFileL(CFileStore*& /*aFileStore*/, RFile& /*aFile*/)
	{
	// nothing
	}

EXPORT_C CAknDocument::CAknDocument(CEikApplication& aApp)
: CEikDocument(aApp)
	{
	}

