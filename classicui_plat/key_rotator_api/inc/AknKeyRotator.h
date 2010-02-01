/*
* Copyright (c) 2005 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Key rotation interface
*
*/

#ifndef CAKNKEYROTATOR_H
#define CAKNKEYROTATOR_H

// INCLUDES
#include <e32base.h>

// CONSTANTS
_LIT( KAknKeyRotatorLibraryName, "AknKeyRotator.dll" );
const TInt KAknKeyRotatorFactoryFunctionOrdinal = 1;

// FORWARD DECLARATIONS
class TRawEvent;
class MAnimGeneralFunctions;

// CLASS DECLARATION

/**
*  Key rotation interface.
*  Use AknKeyRotatorFactory to create an instance.
*
*  Usage:
*  1. Load the library dynamically and access the only exported function
*     from the lookup table at position 1.
*     
*  RLibrary lib;
*  User::LeaveIfError( lib.Load( KAknKeyRotatorLibraryName ) );
*  CleanupClosePushL( lib );
*  TInt res = lib.Lookup( KAknKeyRotatorFactoryFunctionOrdinal )();   
*  CAknKeyRotator* keyRotator = (CAknKeyRotator*)res;
*  
*  2. Use the CAknKeyRotator from the OfferRawEvent function.
*  
*  TBool ret = keyRotator->->CheckRotation(aRawEvent, *iFunctions );
*  
*  3. Deallocate rotator and free the library
*  
*  delete keyRotator;
*  CleanupStack::PopAndDestroy(): // lib.Close();
*  
*
*  @lib AknKeyRotator.lib (do not link against)
*  @since Series 60 3.0
*/
class CAknKeyRotator : public CBase
    { 

    public: // New functions
        
        /**
        * Checks rotation. If the passed event is rotate, a new event is
        * generated from automatically and ETrue is returned. The caller
        * should not utilize the original event anymore in this case.
        * @param aRawEvent Original raw event
        * @param aAnimGeneralFunctions API to post a raw event.
        * @return If a new raw event was generated. If ETrue, the caller
        *         should not pass the original event forward any more. If
        *         EFalse, the caller should process the original event as
        *         normal.
        */
        virtual TBool CheckRotation( 
            const TRawEvent &aRawEvent,
            MAnimGeneralFunctions& aAnimGeneralFunctions ) = 0;
    };
    
    
/**
*  Factory interface to create CAknKeyRotator object.
*  Call the factory function from the polymorphic DLL KAknKeyRotatorLibraryName
*  accessing the oridinal KAknKeyRotatorFactoryFunctionOrdinal.
*
*  @lib AknKeyRotator.lib (do not link against)
*  @since Series 60 3.0
*/  
class AknKeyRotatorFactory
    {
    public:
        /**
        * Creates insntance of CAknKeyRotator.
        * @return New object. Ownership transferred.
        */
        IMPORT_C static CAknKeyRotator* CreateAknKeyRotatorL();
    };

#endif      // CAKNKEYROTATOR_H   
            
// End of File
