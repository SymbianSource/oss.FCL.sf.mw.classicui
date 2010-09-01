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


#ifndef GAMERECOGNIZER_H
#define GAMERECOGNIZER_H

// includes
#include <apmrec.h>  // For CApaDataRecognizerType


// constants
const TInt KMimeGameDataRecognizerValue             = 0x01005A08;
const TInt KMimeGameDataRecognizerImplementationUid = 0x11005A08;
const TUid KUidMimeGameDataRecognizerValue = { KMimeGameDataRecognizerValue };

// We support only wmlc and wmlsc, but can recognize also
// other types internaly.

const TInt KSupportedGameDataMimetypes(1);

// Exported mimetypes
_LIT8( KGameDataMimeType, "application/x-nokiaGameData");
_LIT( KDotNGD,".ngd");
_LIT8( KGndHeader, "NGDX" );

//
// CGameRecognizer
//
class CGameRecognizer : public CApaDataRecognizerType
    {
public: // from CApaDataRecognizerType
    CGameRecognizer();
    virtual TUint PreferredBufSize();
    virtual TDataType SupportedDataTypeL(TInt aIndex) const;
    static CApaDataRecognizerType* CreateRecognizerL();

private: // from CApaDataRecognizerType
    virtual void DoRecognizeL(const TDesC& aName, const TDesC8& aBuffer);
         // New funtions
private:
    TBool NameRecognizedL( const TDesC& aName) const;
    TBool HeaderRecognized( const TDesC8& aName) const;
    };

#endif // GAMERECOGNIZER_H

// END FILE
