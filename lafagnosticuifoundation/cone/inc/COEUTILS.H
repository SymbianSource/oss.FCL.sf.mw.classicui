// COEUTILS.H

/*
* Copyright (c) 2002-2009 Nokia Corporation and/or its subsidiary(-ies).
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



#ifndef __COEUTILS_H__
#define __COEUTILS_H__

#include <e32std.h>
class CCoeEnv;

/** Provides file and path utility functions.

@publishedAll
@released */
class ConeUtils
	{
public:
	IMPORT_C static TBool FileExists(const TDesC& aFileName);
	IMPORT_C static void EnsurePathExistsL(const TPtrC& aFileName);
	};


/** 
Class encapsulates methods for opening and closing localised resource files
in the CONE environment. The actual reading of resources from an opened 
resource file is done using various CCoeEnv provided resource-reading 
methods. The Cone Resource Loader API consists of the RCoeResourceLoader class.

Only one resource at a time may be opened by one RCoeResourceLoader instance. 
You can use several RCoeResourceLoader instances for accessing several 
resources simultaneously or use one instance and close the previous resource
before opening a new one.

The implementation uses BaflUtils::NearestLanguageFile to search for
a localised resource in proper search order.
 
Usage example:  

@code
#include <coeutils.h>  

// Get CCoeEnv instance
CEikonEnv* eikEnv = CEikonEnv::Static();
// Initialize loader
RCoeResourceLoader rLoader(eikEnv);

// Push resource loader to cleanup stack, so that it will always be properly 
// closed when popped.
CleanupClosePushL(rLoader);

// Open resource file
_LIT( KSampleResourceFileName, "Z:\\System\\Apps\\sample\\sample.rsc" );
TFileName fileName(KSampleResourceFileName);
rLoader.OpenL(fileName);

// Read a resource   
iSomeArray = eikEnv->ReadDesC16ArrayResourceL(R_SOME_RESOURCE);

// Pop and destroy rLoader from stack. 
// This also calls the rLoader close function after CleanupClosePushL is used.
CleanupStack::PopAndDestroy(); // rLoader
@endcode

@publishedAll
@released */
NONSHARABLE_CLASS(RCoeResourceLoader)
    {
public:
    IMPORT_C RCoeResourceLoader(CCoeEnv& aEnv);
    IMPORT_C TInt Open(TFileName& aFileName);
    IMPORT_C void OpenL(TFileName& aFileName);
    IMPORT_C void Close();
private:
    // Prohibit copy constructor and assigment operator because not deriving from CBase.
    RCoeResourceLoader();
    RCoeResourceLoader(const RCoeResourceLoader&);
    RCoeResourceLoader& operator= (const RCoeResourceLoader&);
private:
    // Needed for closing
    CCoeEnv& iEnv; 
    TInt iResourceFileOffset;
    };


#endif	// __COEUTILS_H__
