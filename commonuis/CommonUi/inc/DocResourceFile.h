/*
* Copyright (c) 2002-2005 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Tiny helper class for adding and removing DocHandler's 
*                resource file for resource pool of the client app
*
*/


#ifndef DOCRESOURCEFILE_H
#define DOCRESOURCEFILE_H

#include <bautils.h>                // For NearestLanguageFile(..)

class CDocResourceFile : public CBase
    {
    public:
    // Constructor
        CDocResourceFile( const TDesC& aResFilename, RFs& aFs ) : 
            iResFilename( aResFilename ),
            iFs( aFs )            
        {        
#ifdef _DEBUG
        iResCount = 0;
#endif
        }

    // Destructor
    ~CDocResourceFile()
        {
        CEikonEnv::Static()->DeleteResourceFile( iResFileOffset ); 
#ifdef _DEBUG 
        RDebug::Print( _L("DocumentHandler: CDocResourceFile::~CDocResourceFile : %S removed. Count: %d"), &iResFilename, --iResCount);
#endif
        }

    // Add resource file to the resource pool.
    // Pushes it self to the cleanupStack.
    static void AddLC( 
       const TDesC& aResFilename,   // Resource file name
       RFs& aFs )                   // Connected FileServer client 
        {
        CDocResourceFile* self = 
            new ( ELeave ) CDocResourceFile( aResFilename, aFs );
        CleanupStack::PushL( self );
        self->ConstructL();
        }

    // Removes the resource file and destroys it self
    static void Remove()
       {
        CleanupStack::PopAndDestroy(); // self
       }
   
    private:

    // Epoc constructor
    void ConstructL()
        {
        TFileName resourceFile( iResFilename );
        BaflUtils::NearestLanguageFile( iFs, resourceFile );
        iResFileOffset = CCoeEnv::Static()->AddResourceFileL( resourceFile );
#ifdef _DEBUG 
        RDebug::Print( _L("DocumentHandler: CDocResourceFile::ConstructL : %S added. Count: %d"), &iResFilename, ++iResCount );
#endif
        }

    // Remember the resrource file offset
    TInt iResFileOffset;

    // Resource filename
    TFileName iResFilename;
    
    // File server client
    RFs iFs;

#ifdef _DEBUG 
    TInt iResCount;
#endif
    };

#endif      // DOCRESOURCEFILE_H
            
// End of File
