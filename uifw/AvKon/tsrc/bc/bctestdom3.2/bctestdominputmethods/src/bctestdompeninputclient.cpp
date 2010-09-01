/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Implementation for peninput client
*
*/


// INCLUDE FILES
#include <pticore.h>
#include <ptihwrrecognizer.h>

#include "bctestdompeninputclient.h"


// ---------------------------------------------------------------------------
// CBCTestHwrRecognizer::NewL
// ---------------------------------------------------------------------------
//   
CBCTestDomHwrRecognizer* CBCTestDomHwrRecognizer::NewL( TInt aImpId )
    {
    CBCTestDomHwrRecognizer* self = 
                static_cast< CBCTestDomHwrRecognizer* >( CHwrRecognizer::NewL( aImpId ) );
    return self;
    }

// ---------------------------------------------------------------------------
// CBCTestHwrRecognizer::IsSupportUdm
// ---------------------------------------------------------------------------
//   
TBool CBCTestDomHwrRecognizer::IsSupportUdm()
    {
    return CHwrRecognizer::IsSupportUdm();
    }
    
// ---------------------------------------------------------------------------
// CBCTestHwrRecognizer::LoadUdmL
// ---------------------------------------------------------------------------
//   
void CBCTestDomHwrRecognizer::LoadUdmL( TUdmType aType )   
    {
    CHwrRecognizer::LoadUdmL( aType );
    }

// ---------------------------------------------------------------------------
// CBCTestHwrRecognizer::UnLoadUdmL
// ---------------------------------------------------------------------------
//   
void CBCTestDomHwrRecognizer::UnLoadUdmL( TUdmType aType )
    {
    CHwrRecognizer::UnLoadUdmL( aType );
    }

// ---------------------------------------------------------------------------
// CBCTestHwrRecognizer::GetModelIndexListL
// ---------------------------------------------------------------------------
//   
void CBCTestDomHwrRecognizer::GetModelIndexListL( TUdmType aType, 
                             RArray<TInt>& aList, 
                             const THwrUdmRange& aRange )
    {
    CHwrRecognizer::GetModelIndexListL( aType, aList, aRange );
    }

// ---------------------------------------------------------------------------
// CBCTestHwrRecognizer::GetSymbolModelL
// ---------------------------------------------------------------------------
//   
void CBCTestDomHwrRecognizer::GetSymbolModelL( TUdmType aType, 
                                            TInt aIndex, 
                                            TPtrC& aSymbolName,
                                            RArray<TPoint>& aModel, 
                                            TInt& aHelpLine, TInt& aBaseLine )
    {
    CHwrRecognizer::GetSymbolModelL( aType, 
                                     aIndex,  
                                     aSymbolName,
                                     aModel,
                                     aHelpLine, 
                                     aBaseLine );
    }
    
// ---------------------------------------------------------------------------
// From class CPtiCore. 
// Bceause the api is not IMPORT_C, implemented for get iDtorKeyId.
// ---------------------------------------------------------------------------
//   
TInt CPtiCore::DestructorKeyId() const
	{
	return iDtorKeyId;	
	}

// End of File
