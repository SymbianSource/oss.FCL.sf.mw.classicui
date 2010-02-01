/*
* Copyright (c) 2005-2008 Nokia Corporation and/or its subsidiary(-ies).
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


// INCLUDE FILES
#include "AknKeyRotatorImpl.h"

#include <UikonInternalPSKeys.h>
#include <PSVariables.h>
#include <aknpriv.rsg>
#include <barsread.h>
#include <barsc.h>
#include <bautils.h>
#include <w32adll.h>

// CONSTANTS
_LIT( KAknPrivRscFilePath,  "z:\\resource\\AknPriv.rsc");
const TUint KAknModifiersMask = 0xFFFF0000;
// Path to wsini.ini
_LIT( KAknWsini, "z:\\system\\data\\wsini.ini" );
// Keyword for key rotator compensation.
// Syntax: S60_KEYROTATOR <value>
//         where <value> is one of the following: -270, -180, -90, -0, 0, 90, 180, 270
//         to specify <value> as compensation
//         S60_KEYROTATOR DISABLED
//         to disable key rotator
// 
_LIT( KAknKeyRotatorKey, "S60_KEYROTATOR" );
_LIT( KAknKeyRotatorDisabled, "DISABLED");

// Scan codes for diagonal directions 0xc9 .. 0xcc
const TInt KAknStdLeftUpArrow = EStdKeyDevice10;
const TInt KAknStdRightUpArrow = EStdKeyDevice11;
const TInt KAknStdRightDownArrow = EStdKeyDevice12;
const TInt KAknStdLeftDownArrow = EStdKeyDevice13;

// Configure
#define KAknRotateArrowKeys 1
#define KAknRotateInKeyboardDriver 0

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CAknKeyRotatorImpl::CAknKeyRotatorImpl
// 1st phase constructor
// -----------------------------------------------------------------------------
//
CAknKeyRotatorImpl::CAknKeyRotatorImpl()
    {
    }

// -----------------------------------------------------------------------------
// CAknKeyRotatorImpl::ConstructL
// 2nd phase constructor
// -----------------------------------------------------------------------------
//
void CAknKeyRotatorImpl::ConstructL()
    {
    if ( KAknRotateInKeyboardDriver )
        {
        LoadHwStateRotationsL();
        }
    
    User::LeaveIfError( iProperty.Attach( KPSUidUikon, KUikLayoutState ) );
    
    TRAPD( err, iKeyRotatorCompensation = GetKeyRotatorCompensationL() );
    if ( err != KErrNone )
        {
        iKeyRotatorCompensation = 0;
        }
    }

// -----------------------------------------------------------------------------
// CAknKeyRotatorImpl::NewL
// Two-phased constructor
// -----------------------------------------------------------------------------
//
CAknKeyRotatorImpl* CAknKeyRotatorImpl::NewL()
    {
    CAknKeyRotatorImpl* self = new( ELeave ) CAknKeyRotatorImpl;
    
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();

    return self;
    }
    
// -----------------------------------------------------------------------------
// CAknKeyRotatorImpl::~CAknKeyRotatorImpl
// Destruction
// -----------------------------------------------------------------------------
//
CAknKeyRotatorImpl::~CAknKeyRotatorImpl()
    {
    iHwRotations.Close();
    iProperty.Close();
    }

// -----------------------------------------------------------------------------
// CAknKeyRotatorImpl::LoadHwStateRotationsL
// Reads the HW states from the AknPriv.rsc to an array.
// -----------------------------------------------------------------------------
//
void CAknKeyRotatorImpl::LoadHwStateRotationsL()
    {
    // Find the language specific resource file and then load it.
    RResourceFile resourceFile;
    RFs fsSession;
    User::LeaveIfError( fsSession.Connect() );
    CleanupClosePushL( fsSession );
    
    TFileName resourceFileName (KAknPrivRscFilePath);
    BaflUtils::NearestLanguageFile( fsSession, resourceFileName );
    resourceFile.OpenL(fsSession, resourceFileName);

    CleanupClosePushL( resourceFile );
    resourceFile.ConfirmSignatureL(0);
    
    // Read resources to a buffer. The resource definition for the target and
    // emulator are a bit different.
    HBufC8* res;
#ifdef __WINS__
    res = resourceFile.AllocReadLC( R_AKNPRIV_HARDWARE_STATE_SCREEN_MAP_EMUL );
#else
    res = resourceFile.AllocReadLC( R_AKNPRIV_HARDWARE_STATE_SCREEN_MAP );
#endif
    
    TResourceReader reader;
    reader.SetBuffer(res);
    
    // Read the entires. We are only interrested about the hwRotation.
    TInt count = reader.ReadInt16();
    for (TInt ii=0; ii<count; ii++)
        {
        /*TInt state =*/ reader.ReadInt16(); // Assumption (state == ii)
        /*TInt width =*/ reader.ReadInt16();
        /*TInt height =*/ reader.ReadInt16();
        CFbsBitGc::TGraphicsOrientation hwRotation = 
            static_cast<CFbsBitGc::TGraphicsOrientation>(reader.ReadInt16());
        /*CFbsBitGc::TGraphicsOrientation altRotation =*/ 
            static_cast<CFbsBitGc::TGraphicsOrientation>(reader.ReadInt16());
        
        User::LeaveIfError( iHwRotations.Append( hwRotation ) );
        }
    
    CleanupStack::PopAndDestroy(res);
    CleanupStack::PopAndDestroy(&resourceFile); // resourceFile.Close();  
    CleanupStack::PopAndDestroy(&fsSession); // fsSession.Close();
    }


// -----------------------------------------------------------------------------
// CAknKeyRotatorImpl::CheckRotation
// Check if this is our own generated event.
// -----------------------------------------------------------------------------
//
TBool CAknKeyRotatorImpl::CheckRotation( 
    const TRawEvent &aRawEvent,
    MAnimGeneralFunctions& aAnimGeneralFunctions )
    {
    if ( KMaxTInt == iKeyRotatorCompensation )
        {
        // Key rotator is disabled - wsini.ini contains "S60_KEYROTATOR DISABLED".
        return EFalse;
        }

    // Check first that we are not processing just generated event again.
    if ( iRotatedRawEvent )
        {
        // This is the generated avent from the last round. Do not modify again.
        iRotatedRawEvent = EFalse;
        }
    else if ( aRawEvent.Type() == TRawEvent::EKeyDown || 
              aRawEvent.Type() == TRawEvent::EKeyUp || 
              aRawEvent.Type() == TRawEvent::EKeyRepeat )
        {
        // We get new event. Let's see if we need to modify that.
        TRawEvent newRawEvent( aRawEvent );
        DoCheckRotation( newRawEvent, aAnimGeneralFunctions );
        if ( aRawEvent.ScanCode() != newRawEvent.ScanCode() )   
            {
            // Generate new event,
            iRotatedRawEvent = ETrue;
            aAnimGeneralFunctions.PostRawEvent( newRawEvent ); // Calls this function again!
            return ETrue;
            }
        }
    
    return EFalse;
    }
    
    
// -----------------------------------------------------------------------------
// CAknKeyRotatorImpl::DoCheckRotation
// Checks the scan codes and the orientations. Decides if we need to generate
// a new raw event.
// -----------------------------------------------------------------------------
//
void CAknKeyRotatorImpl::DoCheckRotation(
    TRawEvent& aNewRawEvent,
    MAnimGeneralFunctions& aAnimGeneralFunctions )
    {   
    // Current implementation is only for arrow keys
    if ( !KAknRotateArrowKeys )
        {
        return;
        }
    
    // Do not rotate external keyboard events.
    if ( aNewRawEvent.ScanCode() & EModifierKeyboardExtend )
        {
        return;
        }    
        
    // Also check only the arrow keys
    if ( !IsArrowScanCode( aNewRawEvent.ScanCode ()) )
        {
        return;
        }
    
    // If 'newCode' is changed something else than -1, 
    // a new event will be generated
    TInt newCode = KErrNotFound;
    
    // Check the rotation on down event. Use the same rotation for up event.
    
    // finalRotation variable at the end of this function is used to determine
    // the new scan code.
    CFbsBitGc::TGraphicsOrientation finalRotation = 
        CFbsBitGc::EGraphicsOrientationNormal;
    
    if ( aNewRawEvent.Type() == TRawEvent::EKeyUp || 
         aNewRawEvent.Type() == TRawEvent::EKeyRepeat )
        {
        // Use the same orintation for up event.
        finalRotation = iUsedRotationForDownEvent;
        }
    else // For down event, find out the rotation.
        {
        // Get SW screen rotation compared to the keyboard i.e. app orientation.
        CFbsBitGc::TGraphicsOrientation swRotation = 
            aAnimGeneralFunctions.ScreenDevice()->Orientation();
    
        // Get HW screen rotation
        CFbsBitGc::TGraphicsOrientation hwRotation = 
            CFbsBitGc::EGraphicsOrientationNormal;
        TInt hwState;
        if ( KAknRotateInKeyboardDriver && 
             ( iProperty.Get(hwState) == KErrNone ) )
            {
            if ( hwState < iHwRotations.Count() )
                {
                hwRotation = iHwRotations[hwState];
                }
            }
    
        // Calculate the difference
        TInt finalRotationInt = swRotation*90;
    
        if ( KAknRotateInKeyboardDriver )
            {
            // If the rotation is also done in the driver level, 
            // the rotation needs to be compensated so we do not 
            // rotate twice.
            finalRotationInt -= hwRotation*90;
            }
    
        finalRotationInt += iKeyRotatorCompensation;

        // Keep the value between 0 and 270.
        while ( finalRotationInt < 0 )
            {
            finalRotationInt += 360;
            }
        while ( finalRotationInt > 270 )
            {
            finalRotationInt -= 360;
            }
            
        finalRotation = 
            (CFbsBitGc::TGraphicsOrientation)( finalRotationInt / 90 );

        iUsedRotationForDownEvent = finalRotation;
        }
    
    // Find the new scan code from the rotation.
    switch( aNewRawEvent.ScanCode() )
        {
        case EStdKeyLeftArrow:
            switch ( finalRotation )
                {
                case CFbsBitGc::EGraphicsOrientationRotated90:
                    newCode = EStdKeyDownArrow;
                    break;
                case CFbsBitGc::EGraphicsOrientationRotated180:
                    newCode = EStdKeyRightArrow;
                    break;
                case CFbsBitGc::EGraphicsOrientationRotated270:
                    newCode = EStdKeyUpArrow;
                    break;
                default:
                    break;
                }
            break;
        case EStdKeyDownArrow:
            switch ( finalRotation )
                {
                case CFbsBitGc::EGraphicsOrientationRotated90:
                    newCode = EStdKeyRightArrow;
                    break;
                case CFbsBitGc::EGraphicsOrientationRotated180:
                    newCode = EStdKeyUpArrow;
                    break;
                case CFbsBitGc::EGraphicsOrientationRotated270:
                    newCode = EStdKeyLeftArrow;
                    break;
                default:
                    break;
                }
            break;
        case EStdKeyRightArrow:
            switch ( finalRotation )
                {
                case CFbsBitGc::EGraphicsOrientationRotated90:
                    newCode = EStdKeyUpArrow;
                    break;
                case CFbsBitGc::EGraphicsOrientationRotated180:
                    newCode = EStdKeyLeftArrow;
                    break;
                case CFbsBitGc::EGraphicsOrientationRotated270:
                    newCode = EStdKeyDownArrow;
                    break;
                default:
                    break;
                }
            break;
        case EStdKeyUpArrow:
            switch ( finalRotation )
                {
                case CFbsBitGc::EGraphicsOrientationRotated90:
                    newCode = EStdKeyLeftArrow;
                    break;
                case CFbsBitGc::EGraphicsOrientationRotated180:
                    newCode = EStdKeyDownArrow;
                    break;
                case CFbsBitGc::EGraphicsOrientationRotated270:
                    newCode = EStdKeyRightArrow;
                    break;
                default:
                    break;
                }
            break;

        // Diagonal events
        case KAknStdLeftUpArrow:
            switch ( finalRotation )
                {
                case CFbsBitGc::EGraphicsOrientationRotated90:
                    newCode = KAknStdLeftDownArrow;
                    break;
                case CFbsBitGc::EGraphicsOrientationRotated180:
                    newCode = KAknStdRightDownArrow;
                    break;
                case CFbsBitGc::EGraphicsOrientationRotated270:
                    newCode = KAknStdRightUpArrow;
                    break;
                default:
                    break;
                }
            break;

        case KAknStdRightUpArrow:
            switch ( finalRotation )
                {
                case CFbsBitGc::EGraphicsOrientationRotated90:
                    newCode = KAknStdLeftUpArrow;
                    break;
                case CFbsBitGc::EGraphicsOrientationRotated180:
                    newCode = KAknStdLeftDownArrow;
                    break;
                case CFbsBitGc::EGraphicsOrientationRotated270:
                    newCode = KAknStdRightDownArrow;
                    break;
                default:
                    break;
                }
            break;

        case KAknStdLeftDownArrow:
            switch ( finalRotation )
                {
                case CFbsBitGc::EGraphicsOrientationRotated90:
                    newCode = KAknStdRightDownArrow;
                    break;
                case CFbsBitGc::EGraphicsOrientationRotated180:
                    newCode = KAknStdRightUpArrow;
                    break;
                case CFbsBitGc::EGraphicsOrientationRotated270:
                    newCode = KAknStdLeftUpArrow;
                    break;
                default:
                    break;
                }
            break;

        case KAknStdRightDownArrow:
            switch ( finalRotation )
                {
                case CFbsBitGc::EGraphicsOrientationRotated90:
                    newCode = KAknStdRightUpArrow;
                    break;
                case CFbsBitGc::EGraphicsOrientationRotated180:
                    newCode = KAknStdLeftUpArrow;
                    break;
                case CFbsBitGc::EGraphicsOrientationRotated270:
                    newCode = KAknStdLeftDownArrow;
                    break;
                default:
                    break;
                }
            break;

        default:
            break;    
        }
        
    // If the 'newCode' was updated, add that value as the new scancode with existing modifiers.
    if ( newCode != KErrNotFound )
        {
        aNewRawEvent.Set(
            aNewRawEvent.Type(),
            (aNewRawEvent.ScanCode()&KAknModifiersMask) + newCode);
        }
    }

// -----------------------------------------------------------------------------
// CAknKeyRotatorImpl::IsArrowScanCode
// Returns true if it's arrow scan code.
// -----------------------------------------------------------------------------
//
TBool CAknKeyRotatorImpl::IsArrowScanCode(TInt aScanCode)
    {
    return ( aScanCode >= EStdKeyLeftArrow && aScanCode <= EStdKeyDownArrow ) ||
           ( aScanCode >= KAknStdLeftUpArrow && aScanCode <= KAknStdLeftDownArrow );
    }

// -----------------------------------------------------------------------------
// CAknKeyRotatorImpl::GetKeyRotatorCompensationL
// Parses wsini.ini to read key rotator compensation value.
// -----------------------------------------------------------------------------
//
TInt CAknKeyRotatorImpl::GetKeyRotatorCompensationL()
    {
    TInt result = 0;
    HBufC* wsiniText = GetWsiniLC();
    
    // Now look for keyword
    const TInt pos = wsiniText->Find( KAknKeyRotatorKey );
    if ( pos != KErrNotFound )
        {        
        // Keyword was found. Check that it is the beginning of line.
        // Three cases:
        // 1. Keyword could be at the beginning of the file.
        // 2. Keyword could be at the beginning of the file 
        //    after byte ordering marker.
        // 3. Previous character can be end of line marker.
        const TInt previousPos = pos - 1;
        if ( previousPos < 0 || 
             ( !previousPos && 
               IsByteOrderingMarker( (*wsiniText)[ previousPos ] ) ) || 
             IsEndOfLine( (*wsiniText)[ previousPos ] ) )
            {
            TLex text( wsiniText->Mid( pos + KAknKeyRotatorKey().Length() ) );
            
            // First, there must be at least a space after keyword.
            TBool fail = !( SkipSpaces( text ) & EAknWasSpace );
           
            // Case 1: Disabled
            TBool wasDisabled = EFalse;
            if ( !fail )
                {
                wasDisabled = 
                    !text.Remainder().Left( KAknKeyRotatorDisabled().Length() ).
                    CompareF( KAknKeyRotatorDisabled );

                if ( wasDisabled )
                    {
                    // wasDisabled == True, KAknKeyRotatorDisabled was prefix
                    // of text. So skip over it
                    text.Inc( KAknKeyRotatorDisabled().Length() );
                    }
                }
            
            // Case 2: Then follows a sequence of digits, optionally preceded by '-'.
            if ( !wasDisabled && !fail )
                {
                // Check optional -
                TBool negate = EFalse;
                if ( !text.Eos() && text.Peek() == '-' )
                    {
                    negate = ETrue;
                    text.Inc();
                    }
                    
                // Get digit sequence and convert to integer value.
                TPtrC token = GetDigits( text );
                fail = !token.Length() || 
                       ( TLex( token ).Val( result ) != KErrNone );
                
                // Handle negation
                if ( !fail && negate )
                    {
                    result = -result;
                    }
                }

            // That sequence of digits is followed by sequence of spaces until
            // end of line or end of file.
            fail = fail || ( SkipSpaces( text ) & EAknWasCharacter );
            
            if ( !wasDisabled )
                {
                // Finally, that sequence of digits must represent
                // one valid decimal value of the following: 
                // -270, -180, -90, 0, 90, 180, 270.
                fail = fail || !CheckCompensationValue( result );
                }
                
            // If any of above checks failed, use default value 0.
            if ( fail )
                {
                result = 0;
                }
            else
                {
                if ( wasDisabled )
                    {
                    result = KMaxTInt;
                    }
                }
            }
        }
        
    CleanupStack::PopAndDestroy( wsiniText );   
    return result;
    }

// -----------------------------------------------------------------------------
// CAknKeyRotatorImpl::IsEndOfLine
// Checks if specified character is end of line marker.
// -----------------------------------------------------------------------------
//
inline TBool CAknKeyRotatorImpl::IsEndOfLine( TText aChar )
    {
    return aChar == '\r' || aChar == '\n';
    }

// -----------------------------------------------------------------------------
// CAknKeyRotatorImpl::IsByteOrderingMarker
// Checks if specified character is byte ordering marker.
// -----------------------------------------------------------------------------
//
inline TBool CAknKeyRotatorImpl::IsByteOrderingMarker( TText aChar )
    {
    return aChar == 0xFEFF || aChar == 0xFFFE;
    }

// -----------------------------------------------------------------------------
// CAknKeyRotatorImpl::GetWsiniLC
// Reads the whole wsini.ini to memory and returns in heap descriptor.
// -----------------------------------------------------------------------------
//
HBufC* CAknKeyRotatorImpl::GetWsiniLC()
    {
    // Read the whole wsini.ini to memory
    RFs fs;
    User::LeaveIfError( fs.Connect() );
    CleanupClosePushL( fs );
    
    TEntry wsiniEntry;
    User::LeaveIfError( fs.Entry( KAknWsini, wsiniEntry ) );

    HBufC* wsiniText = HBufC::NewLC( ( wsiniEntry.iSize + 1 )/2 );
    TPtr wsiniPtr = wsiniText->Des();
    TPtr8 wsiniPtr8( (TText8*)wsiniPtr.Ptr(), 0, wsiniPtr.MaxLength()*2 );

    RFile wsiniFile;
    User::LeaveIfError( wsiniFile.Open( fs, KAknWsini, EFileRead | EFileShareReadersOnly ) );
    CleanupClosePushL( wsiniFile );

    User::LeaveIfError( wsiniFile.Read( wsiniPtr8, wsiniEntry.iSize ) );
    wsiniPtr.SetLength( wsiniPtr8.Length() / 2 );

    CleanupStack::PopAndDestroy( &wsiniFile );
    CleanupStack::Pop( wsiniText );
    CleanupStack::PopAndDestroy( &fs );
    CleanupStack::PushL( wsiniText );
    return wsiniText;
    }

// -----------------------------------------------------------------------------
// CAknKeyRotatorImpl::SkipSpaces
// Skips over spaces.
// -----------------------------------------------------------------------------
//
TInt CAknKeyRotatorImpl::SkipSpaces( TLex& aLex )
    {
    TInt flags = 0;
    // Skip spaces, but stop at end of line.
    while ( !aLex.Eos() && !IsEndOfLine( aLex.Peek() ) )
        {
        if ( aLex.Peek().IsSpace() )
            {
            // There was a space, so ok for now.
            flags |= EAknWasSpace;
            aLex.Inc();
            }
        else
            {
            flags |= EAknWasCharacter;
            break;
            }
        }
    return flags;
    }

// -----------------------------------------------------------------------------
// CAknKeyRotatorImpl::SkipSpaces
// Goes over digits and returns that sequence.
// -----------------------------------------------------------------------------
//
TPtrC CAknKeyRotatorImpl::GetDigits( TLex& aLex )
    {
    // Mark current place and go over digits.
    aLex.Mark();
    while ( !aLex.Eos() && !IsEndOfLine( aLex.Peek() ) )
        {
        if ( aLex.Peek().IsDigit() )
            {
            aLex.Inc();
            }
        else
            {
            break;
            }
        }
    return aLex.MarkedToken();
    }

// -----------------------------------------------------------------------------
// CAknKeyRotatorImpl::CheckCompensationValue
// Checks that value contains valid key rotator compensation value.
// -----------------------------------------------------------------------------
//
inline TBool CAknKeyRotatorImpl::CheckCompensationValue( TInt aValue )
    {
    // Check absolute value
    if ( aValue < 0 )
        {
        aValue = -aValue;
        }
        
    return aValue == 0 ||
           aValue == 90 ||
           aValue == 180 ||
           aValue == 270;
    }

// ========================== OTHER EXPORTED FUNCTIONS =========================

// -----------------------------------------------------------------------------
// Creates a CAknKeyRotatorImpl instance.
// Returns: new CAknKeyRotatorImpl object. Ownership is returned to the caller.
// -----------------------------------------------------------------------------
//
EXPORT_C CAknKeyRotator* AknKeyRotatorFactory::CreateAknKeyRotatorL()
    {
    return CAknKeyRotatorImpl::NewL();
    }

//  End of File  
