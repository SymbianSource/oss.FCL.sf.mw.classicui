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



#ifndef TULSTRINGRESOURCEREADER_H
#define TULSTRINGRESOURCEREADER_H

#include <coemain.h> // RResourceReader

/**
CTulStringResourceReader reads strings from resource without CCoeEnv.
If resource file given to the constructor is not found, the constructor leaves.
This module is mainly for server usage, where there is the need to read resources,
but no CCoeEnv instance is present.     

Usage:
 
@code
#include <platform/stringresourcereader.h>
#include <errorres.rsg> // Resource to be read header 

TFileName myFileName( _L("z:\\resource\\errorres.rsc") );
CTulStringResourceReader* test = CTulStringResourceReader::NewL( myFileName );

TPtrC buf;
buf.Set(test-> ReadResourceString(R_ERROR_RES_GENERAL)); 
  
// Note that buf will only be valid as long as CTulStringResourceReader 
// instance is alive and no new string is read by the same instance.
// If you need to read multiple strings, make copies.

delete test;
@endcode

@publishedAll
@released 
*/
class CTulStringResourceReader : public CBase
    {
public:  // Constructors and destructor
    IMPORT_C static CTulStringResourceReader* NewL(TFileName& aResFile);
    IMPORT_C static CTulStringResourceReader* NewLC(TFileName& aResFile);     
    IMPORT_C static CTulStringResourceReader* NewL(TFileName& aResFile, RFs& aFs);
    IMPORT_C static CTulStringResourceReader* NewLC(TFileName& aResFile, RFs& aFs);         
    ~CTulStringResourceReader();
public:
	IMPORT_C const TDesC& ReadResourceString( TInt aResourceId );
private:
    CTulStringResourceReader();
    void ConstructL(TFileName& aResFile);
    void ConstructL(TFileName& aResFile, RFs& aFs);
private:
    RResourceFile iResourceFile;
    HBufC* iResourceBuffer;
    RFs iFsSession;
    TPtrC iTruncatedTextPointer;
    TBool iFsConnected; // ETrue if connected to the file server, else EFalse
    };

#endif      // TULSTRINGRESOURCEREADER_H
            
