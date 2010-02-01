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

#ifndef __AKNDOC_H__
#define __AKNDOC_H__

// INCLUDES

#include <eikdoc.h>

// CLASS DECLARATION

/**
*  Base class for a Series 60 application document.
*
*  @since Series 60 0.9
*/
class CAknDocument : public CEikDocument
	{
public:	// from CEikDocument
	
	/**
    * From @c CEikDocument. Opens a file.
    * @param aDoOpen Open an existing file if @c ETrue, 
    * otherwise create a new file. Not used.
    * @param aFilename The file to open or create. Not used.
    * @param aFs File server session to use. Not used.
    * @return Pointer to file store object.
    */
	IMPORT_C CFileStore* OpenFileL(TBool aDoOpen,
	                               const TDesC& aFilename,
	                               RFs& aFs);
	IMPORT_C void OpenFileL(CFileStore*& aFileStore, RFile& aFile);
protected:
	
	/**
    * C++ default constructor.
    * @param aApp The application instance with which the new document is
    * associated.
    */
	IMPORT_C CAknDocument(CEikApplication& aApp);
	};

#endif

