// COEUTILS.CPP

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

#include <coeutils.h>
#include <bautils.h>
#include <coemain.h>
#include "COETLS.H"

_LIT( KResLPanicString, "RCoeResourceLoader: ");


/** Tests whether a file exists. 

@param aFileName The file name to check.
@return ETrue if the file exists, EFalse if it doesn't.
@see BaflUtils::FileExists() */
EXPORT_C TBool ConeUtils::FileExists(const TDesC& aFileName)
	{ // static
	return(BaflUtils::FileExists(TheCoe()->FsSession(),aFileName));
	}

/** Ensures a path exists. 

This function tests whether the path for the file given by aFileName exists, 
and creates it if it doesn't. The function does nothing if the path name 
already exists.

@param aFileName The full path name to create. Any file name is ignored and 
may be omitted.
@see RFs::MkDirAll()
@see BaflUtils::EnsurePathExistsL() */
EXPORT_C void ConeUtils::EnsurePathExistsL(const TPtrC& aFileName)
	{ // static
	BaflUtils::EnsurePathExistsL(TheCoe()->FsSession(),aFileName);
	}

//
// class RCoeResourceLoader
//

/** 
Constructor. 
@param aEnv is a reference to Control environment in which resource is loaded.
*/
EXPORT_C RCoeResourceLoader::RCoeResourceLoader(CCoeEnv& aEnv)
    : iEnv(aEnv), iResourceFileOffset(0)
    {
    }

/** 
Opens the resource file for reading. Only one resource may be open at a time. 
Panics if this instance already has a file open. 
The implementation uses BaflUtils::NearestLanguageFile to search 
for a localized resource file in proper search order.

@param aFileName is the resource file name to open. This parameter
value is changed to the best matching language file found. The drive
letter is required in the filename.
@return a Symbian OS error code.
@panic KErrNotSupported The instance already has a file open.
*/
EXPORT_C TInt RCoeResourceLoader::Open(TFileName& aFileName)
    {
    __ASSERT_ALWAYS(!iResourceFileOffset, User::Panic(KResLPanicString, KErrNotSupported) );  
    
    TRAPD(ret, OpenL(aFileName));
    return ret;
    }

/**
Opens the resource file for reading. Only one resource may be open 
at a time. Leaves if this instance already has a file open.
The implementation uses BaflUtils::NearestLanguageFile to search
for a localized resource file in proper search order.
 
@param aFileName Reference for resource file name. Note that drive letter is required.
@leave KErrNotSupported The instance already has a file open.
@panic CONE 15 The resource file has no NAME statement (i.e. has no offset).
*/
EXPORT_C void RCoeResourceLoader::OpenL(TFileName& aFileName)
    {
    __ASSERT_ALWAYS(!iResourceFileOffset, User::Leave(KErrNotSupported) );  
    BaflUtils::NearestLanguageFile(iEnv.FsSession(), aFileName);
    
    iResourceFileOffset = iEnv.AddResourceFileL(aFileName);
    }

EXPORT_C void RCoeResourceLoader::Close()
    {
    if(iResourceFileOffset)
        {
        iEnv.DeleteResourceFile(iResourceFileOffset);
        iResourceFileOffset = 0;
        }
    }
