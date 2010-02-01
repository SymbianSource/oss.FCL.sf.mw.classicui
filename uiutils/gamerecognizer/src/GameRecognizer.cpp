/*
* Copyright (c) 2002, 2006 Nokia Corporation and/or its subsidiary(-ies).
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


#include <f32file.h>
#include <s32mem.h>
#include <ImplementationProxy.h>
#include "GameRecognizer.h"

//
// CGameRecognizer
//
CGameRecognizer::CGameRecognizer ()
:CApaDataRecognizerType(KUidMimeGameDataRecognizerValue, CApaDataRecognizerType::EHigh)
    {
    iCountDataTypes= KSupportedGameDataMimetypes;
    }

TUint CGameRecognizer::PreferredBufSize()
    {
    // no buffer recognition yet
    return 128;
    }

TDataType CGameRecognizer::SupportedDataTypeL(TInt aIndex) const
    {
    __ASSERT_DEBUG(aIndex>=0 && aIndex < KSupportedGameDataMimetypes, User::Invariant());
    switch (aIndex)
        {
        case 0:
        default:
            return TDataType( KGameDataMimeType );
        }
    }

void CGameRecognizer::DoRecognizeL( const TDesC& aName, const TDesC8& aBuffer)
    {
    TBool     nameOk( EFalse );
    TBool     headerOk( EFalse );

    iConfidence = ENotRecognized;
    if ( aBuffer.Length() < 10 )
    	{
        return;
    	}

    // First try the name. Then the data.
    nameOk  = NameRecognizedL( aName );
    headerOk = HeaderRecognized( aBuffer );

    if ( nameOk && headerOk )
        {
        iConfidence = ECertain;
        }
    else if ( !nameOk && headerOk)
        {
        iConfidence = EProbable;
        }
    else if ( nameOk && !headerOk )
        {
        iConfidence = EPossible;
        }
    else
    	{
        return;
    	}

    iDataType = TDataType( KGameDataMimeType );
    }

TBool CGameRecognizer::HeaderRecognized( const TDesC8& aBuffer ) const
    {
    if ( aBuffer.Find( KGndHeader ) > 10 )
    	{
        return ETrue;
    	}
    else
    	{
        return EFalse;
    	}
    }

TBool CGameRecognizer::NameRecognizedL( const TDesC& aName) const
    {
    TBool ret = EFalse;
    if ( aName.Length() > 5 )
        {
        TInt dotPos = aName.LocateReverse( '.' );
        if (dotPos != KErrNotFound)
            {
            TInt extLength = aName.Length() - dotPos;
            HBufC* ext = aName.Right( extLength ).AllocL();
            CleanupStack::PushL( ext );
            if ( ext->CompareF( KDotNGD )==0 )
                {
                ret = ETrue;
                }
            CleanupStack::PopAndDestroy( ext );
            }
        }
    return ret;
    }

CApaDataRecognizerType* CGameRecognizer::CreateRecognizerL()
    {
    return new (ELeave) CGameRecognizer();
    }

const TImplementationProxy ImplementationTable[] =
    {
    IMPLEMENTATION_PROXY_ENTRY(KMimeGameDataRecognizerImplementationUid,
                               CGameRecognizer::CreateRecognizerL)
    };

EXPORT_C const TImplementationProxy* ImplementationGroupProxy(TInt& aTableCount)
    {
    aTableCount = sizeof(ImplementationTable) / sizeof(TImplementationProxy);
    return ImplementationTable;
    }

// End of File
