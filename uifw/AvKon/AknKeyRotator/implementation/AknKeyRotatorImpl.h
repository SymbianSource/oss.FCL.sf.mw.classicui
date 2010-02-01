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
* Description:  Key rotation implementation
*
*/

#ifndef CAKNKEYROTATORIMPL_H
#define CAKNKEYROTATORIMPL_H

// INCLUDES
#include <AknKeyRotator.h>
#include <e32property.h>
#include <bitstd.h>

// FORWARD DECLARATIONS
class TRawEvent;
class MAnimGeneralFunctions;

// CLASS DECLARATION

/**
*  Key rotation implementation.
*
*  @lib AknKeyRotator.lib
*  @since Series 60 3.0
*/
class CAknKeyRotatorImpl : public CAknKeyRotator
    { 
    public: // Constructor and destructor
        static CAknKeyRotatorImpl* NewL();
        ~CAknKeyRotatorImpl();

    public: // Functions from base classes
        
        /**
        * From CAknKeyRotator
        */
        TBool CheckRotation( 
            const TRawEvent &aRawEvent,
            MAnimGeneralFunctions& aAnimGeneralFunctions );
            
    private:
        CAknKeyRotatorImpl();
        void ConstructL();
        void LoadHwStateRotationsL();
        void DoCheckRotation(
            TRawEvent& aNewRawEvent,
            MAnimGeneralFunctions& aAnimGeneralFunctions);
        static TBool IsArrowScanCode(TInt aScanCode);
        
        // Gets key rotator compensation value from wsini.ini
        static TInt GetKeyRotatorCompensationL();
        
        // Checks if character is end of line marker.
        inline static TBool IsEndOfLine( TText aChar );
        // Checks if character is byte ordering marker.
        inline static TBool IsByteOrderingMarker( TText aChar );
        // Reads wsini.ini file to memory
        static HBufC* GetWsiniLC();
        // Flags - returned by SkipSpaces
        enum TAknSkipSpacesFlags
            {
            // There was a space character (not end of line)
            EAknWasSpace = 1,
            // There was other kind of character
            EAknWasCharacter = 2
            };
        // Skips spaces, but stops if end of line.
        static TInt SkipSpaces( TLex& aLex );
        // Goes over digit sequence and returns string.
        static TPtrC GetDigits( TLex& aLex );
        // Checks if compensation value is ok.
        inline static TBool CheckCompensationValue( TInt aValue );

    private:
        RProperty iProperty; 
        TBool iRotatedRawEvent;   
        RArray<CFbsBitGc::TGraphicsOrientation> iHwRotations;
        CFbsBitGc::TGraphicsOrientation iUsedRotationForDownEvent;
        
        // Key rotator compensation value.
        TInt iKeyRotatorCompensation;
        
    };
    
    
#endif      // CAKNKEYROTATORIMPL_H   
            
// End of File
