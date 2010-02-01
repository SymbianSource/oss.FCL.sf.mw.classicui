// Copyright (c) 2002-2009 Nokia Corporation and/or its subsidiary(-ies).
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



//  INCLUDES
#include <barsread.h>    // TResourceReader
#include <bautils.h>     // BaflUtils

#include "tulstringresourcereader.h"

#ifdef _DEBUG
_LIT( KStringResourceReaderPanic, "CTulStringResourceReader" );
#endif // _DEBUG

const TInt KRIMask(0x00000fff);


// CLASS DECLARATION

/**
C++ default constructor.
*/
CTulStringResourceReader::CTulStringResourceReader()
    {
    }
   
/**
Creates a new String Resource Reader object.
@param aResFile The resource file from which the string(s) are to be read.
@return a pointer to an new instance of CTulStringResourceReader class.
@leave KErrNone, if successful; otherwise one of the other system-wide error codes.
*/
EXPORT_C CTulStringResourceReader*  CTulStringResourceReader::NewL(TFileName& aResFile)
    {
    CTulStringResourceReader* self = CTulStringResourceReader::NewLC(aResFile);
    CleanupStack::Pop(self);
    return self;
    }

/**
Creates a new String Resource Reader object.
@param aResFile The resource file from which the string(s) are to be read.
@param aFs  A handle to a shared file server session. 
@return a pointer to an new instance of CTulStringResourceReader class.
@leave KErrNone, if successful; otherwise one of the other system-wide error codes.
*/
EXPORT_C CTulStringResourceReader*  CTulStringResourceReader::NewL(TFileName& aResFile, RFs& aFs)
    {
    CTulStringResourceReader* self = CTulStringResourceReader::NewLC(aResFile, aFs);
    CleanupStack::Pop(self);
    return self;
    }

/**
Creates a new String Resource Reader object, and puts a pointer to it onto the cleanup stack.
@param aResFile The resource file from which the string(s) are to be read.
@return a pointer to an new instance of CTulStringResourceReader class.
@leave KErrNone, if successful; otherwise one of the other system-wide error codes.
*/
EXPORT_C CTulStringResourceReader* CTulStringResourceReader::NewLC(TFileName& aResFile)
    {
    CTulStringResourceReader* self = new (ELeave) CTulStringResourceReader();
    CleanupStack::PushL( self );
    self->ConstructL( aResFile );
    return self;
    }
    
/**
Creates a new String Resource Reader object, and puts a pointer to it onto the cleanup stack.
@param aResFile The resource file from which the string(s) are to be read.
@param aFs  A handle to a shared file server session. 
@return a pointer to an new instance of CTulStringResourceReader class.
@leave KErrNone, if successful; otherwise one of the other system-wide error codes.
*/
EXPORT_C CTulStringResourceReader* CTulStringResourceReader::NewLC(TFileName& aResFile, RFs& aFs)
    {
    CTulStringResourceReader* self = new (ELeave) CTulStringResourceReader();
    CleanupStack::PushL( self );
    self->ConstructL( aResFile, aFs );
    return self;
    }
       
/*
Destructor
*/
CTulStringResourceReader::~CTulStringResourceReader()
    {
    iResourceFile.Close();
    
    if ( iFsConnected )
        iFsSession.Close();
    
    delete iResourceBuffer;
    }

/**
ReadResourceString: returns the string that match with the resource id.
No lenght limitations are imposed on read string.
@param aResourceId: resource id of looked string resource
@return  String buffer if the string associated with the given resource Id is found, else returns empty descriptor.
@panic aResourceId If the alignment of Unicode strings within the resource is incorrect,
*/
EXPORT_C const TDesC& CTulStringResourceReader::ReadResourceString(TInt aResourceId)
	{
    delete iResourceBuffer;
    iResourceBuffer = NULL;

    HBufC8* tempBuffer = NULL;
    TRAPD(err,tempBuffer = iResourceFile.AllocReadL((KRIMask & aResourceId))); // Remove offset from id
	if(err)
		return KNullDesC;

    __ASSERT_DEBUG((tempBuffer->Length()%2)==0, User::Panic(KStringResourceReaderPanic, aResourceId));

    // do bitwise shift to halve the length for mapping the tempBuffer to unicode.
    TInt newLen = tempBuffer->Length()>>1;
    TPtrC tempPointer((TText*)tempBuffer->Ptr(), newLen);
    iResourceBuffer = tempPointer.Alloc();
    delete tempBuffer;

    if (iResourceBuffer)
        return *iResourceBuffer;
    else
		return KNullDesC;
    }

// Symbian OS constructor.
       
/**
By default Symbian OS constructor is private.
*/
void CTulStringResourceReader::ConstructL(TFileName& aResFile)
    {
    User::LeaveIfError( iFsSession.Connect() );     
    iFsConnected = ETrue;         

    TFileName filename;
    Dll::FileName( filename );
    
    TParse parse;
    // The default file specification is set to NULL to omit it.
    parse.Set( aResFile, &filename, NULL );
    aResFile = parse.FullName();
                
    BaflUtils::NearestLanguageFile( iFsSession, aResFile );
    iResourceFile.OpenL( iFsSession, aResFile );
    }

/**
By default Symbian OS constructor is private.
*/
void CTulStringResourceReader::ConstructL(TFileName& aResFile, RFs& aFs)
    {
    iFsConnected = EFalse;
    TFileName filename;
    Dll::FileName( filename );
    
    TParse parse;
    // The default file specification is set to NULL to omit it.
    parse.Set( aResFile, &filename, NULL );
    aResFile = parse.FullName();
                
    BaflUtils::NearestLanguageFile( aFs, aResFile );
        
    iResourceFile.OpenL( aFs, aResFile );
    }

// End of File

