/*
* Copyright (c) 2006-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Unit MFNE
*
*/


#include <barsread.h>
#include <eikmfne.pan>
#include <e32math.h>
#include <eikon.hrh>
#include <eikctl.rsg>
#include <StringLoader.h>
#include <AknUtils.h>

#include <AknTasHook.h>
#include "aknmfnefloat.h"
#include "aknmfneseparator.h"
#include "aknuniteditor.h"

const TInt KAknNumberOfFields( 3 );
const TInt KAknMaxAllowedFractionalDigits( 8 );
const TInt KAknResourceTable[] =
        {
        0,
        R_AVKON_UNIT_EDITOR_METER,
        R_AVKON_UNIT_EDITOR_KILOMETER,
        R_AVKON_UNIT_EDITOR_FOOT,
        R_AVKON_UNIT_EDITOR_MILE,
        R_AVKON_UNIT_EDITOR_METR_SPEED,
        R_AVKON_UNIT_EDITOR_IMPER_SPEED
        };

// ---------------------------------------------------------------------------
// A utility function to copy from source to destination with a length
// check. If source is larger than destination, the function returns the
// length of the source. This value can then be passed to client (where
// source length is not necessarily known) for allocating a buffer.
// ---------------------------------------------------------------------------
static TInt CopyDescOrNull( TDes& aDestination, const TDesC& aSource )
    {
    TInt sourceLength( aSource.Length() );
    
    if ( aDestination.MaxLength() >= sourceLength )
        {
        aDestination.Copy( aSource );
        sourceLength = 0;
        }
    
    return sourceLength;
    }

// ======== MEMBER FUNCTIONS ========

CAknUnitEditor::CAknUnitEditor() : iUnitLimit( sizeof( KAknResourceTable ) / sizeof( TInt ) )
    {
    }
    

EXPORT_C CAknUnitEditor* CAknUnitEditor::NewL()
    {
    CAknUnitEditor* self = CAknUnitEditor::NewLC();
    CleanupStack::Pop( self );
    return self;
    }


EXPORT_C CAknUnitEditor* CAknUnitEditor::NewLC()
    {
    CAknUnitEditor* self = new( ELeave ) CAknUnitEditor;
    CleanupStack::PushL( self );
    AKNTASHOOK_ADDL( self, "CAknUnitEditor" );
    return self;
    }
    
    
EXPORT_C CAknUnitEditor::~CAknUnitEditor()
    {
    AKNTASHOOK_REMOVE();
    }


EXPORT_C void CAknUnitEditor::ConstructL(
        TReal aMinimumValue, TReal aMaximumValue,
        TReal aInitialValue, 
        TInt aMaxFractionalDigits, TInt aUnit, TUint aFlags )
    {
    // No other construction so this function could be called again
    if ( !SupportsUnit( aUnit ) )
        {
        User::Leave( KErrNotSupported );
        }
    
    CreateFieldArrayL( KAknNumberOfFields );

    iFloatField = CAknMfneFloat::NewL( aMaxFractionalDigits );
    
    iFloatField->SetLimits( aMinimumValue, aMaximumValue );
    
    _LIT( KSpace, " " );
    iSeparatorField = CAknMfneSeparator::NewL( KSpace );
    
    iUnitField = CAknMfneSeparator::NewL( KNullDesC );
    
    // This is for the lifetime of the editor.    
    if ( AknLayoutUtils::LayoutMirrored() )
        {
        AddField( iUnitField );      // ownership transferred
        AddField( iSeparatorField ); // ownership transferred
        AddField( iFloatField );     // ownership transferred
        }
    else
        {   
        AddField( iFloatField );     // ownership transferred
        AddField( iSeparatorField ); // ownership transferred
        AddField( iUnitField );      // ownership transferred
        }
        
    SetValue( aInitialValue );
    SetUnitL( aUnit );

    SetFlags( aFlags );
    }


EXPORT_C void CAknUnitEditor::ConstructFromResourceL( TResourceReader& aResourceReader )
    {
    TReal minimumValue       = aResourceReader.ReadReal64();
    TReal maximumValue       = aResourceReader.ReadReal64();
    TReal initialValue       = aResourceReader.ReadReal64();
    TInt maxFractionalDigits = aResourceReader.ReadInt8();
    TInt unit                = aResourceReader.ReadInt32();
    TUint flags              = aResourceReader.ReadInt32();
        
    ConstructL( minimumValue, maximumValue, initialValue, maxFractionalDigits, unit, flags );
    }


EXPORT_C TBool CAknUnitEditor::SetValue( TReal aValue )
    {
    TBool ret = iFloatField->SetValue( aValue );
    iUnitField->MakeVisible( UnitFieldVisibility() );
    DrawDeferred();
    if ( !IsFocused() )
        {
        TRAP_IGNORE( ReportEventL( MCoeControlObserver::EEventStateChanged ) );
        }
    return ret;
    }
    
    
EXPORT_C TReal CAknUnitEditor::Value() const
    {
    return iFloatField->Value();
    }
    
EXPORT_C TBool CAknUnitEditor::SupportsUnit( TInt aUnit ) const
    {
    return ( aUnit >= 0 && aUnit < iUnitLimit );
    }

EXPORT_C void CAknUnitEditor::SetUnitL( const TDesC& aUnit )
    {
    iUnitField->SetTextL( aUnit );
    iUnitType = EAknUnitEditorCustomUnit;
    DrawDeferred();
    }
    

EXPORT_C void CAknUnitEditor::SetUnitL( TInt aUnit )
    {
    TInt resourceId( EAknUnitEditorCustomUnit );
        
    if ( !SupportsUnit( aUnit ) )
        {
        User::Leave( KErrNotSupported );
        }
        
    resourceId = KAknResourceTable[aUnit];
    
    if ( resourceId )
        {
        HBufC* unitString = StringLoader::LoadL( resourceId );
        CleanupStack::PushL( unitString );
        iUnitField->SetTextL( *unitString );
        CleanupStack::PopAndDestroy( unitString ); 
        }
    else
        {
        iUnitField->SetTextL( KNullDesC );
        }

    // Either a leave has occurred or this is a safe match
    iUnitType = aUnit;
    
    DrawDeferred();
    }
    

EXPORT_C TInt CAknUnitEditor::GetUnit( TDes& aDes ) const
    {
    return CopyDescOrNull( aDes, iUnitField->Text() );
    }
    
    
EXPORT_C TInt CAknUnitEditor::Unit() const
    {
    return iUnitType;
    }


EXPORT_C void CAknUnitEditor::SetMaxFractionalDigits(
    TInt aMaxFractionalDigits )
    {
    TBool validValue = ( aMaxFractionalDigits >= 0 &&
         aMaxFractionalDigits <= KAknMaxAllowedFractionalDigits );
    
    if ( validValue )
        {
        iFloatField->SetMaxFractionalDigits( aMaxFractionalDigits );
        DrawDeferred();
        }
    }
    

EXPORT_C TInt CAknUnitEditor::MaxFractionalDigits() const
    {
    return iFloatField->MaxFractionalDigits();
    }
    

EXPORT_C void CAknUnitEditor::SetMinimumAndMaximum( TReal aMinimumValue, TReal aMaximumValue )
    {
    iFloatField->SetLimits( aMinimumValue, aMaximumValue );
    DrawDeferred();
    }
    

EXPORT_C void CAknUnitEditor::GetMinimumAndMaximum( TReal& aMinimumValue, TReal& aMaximumValue ) const
    {
    iFloatField->GetLimits( aMinimumValue, aMaximumValue );
    }
   

EXPORT_C void CAknUnitEditor::SetFlags( TUint aFlags )
    {
    iFlags = aFlags;
    
    if ( iFlags & EAknUnitEditorAllowUninitialized )
        {
        iFloatField->SetFlags( CAknMfneFloat::EAllowNaN );
        }

    DrawDeferred();
    }


EXPORT_C TUint CAknUnitEditor::Flags() const
    {
    return iFlags;
    }
    

EXPORT_C void CAknUnitEditor::PrepareForFocusLossL()
    {
    CEikMfne::PrepareForFocusLossL();
    }


void CAknUnitEditor::FocusChanged( TDrawNow aDrawNow )
    {
    // Due to a quirk in dialog page captioned control creation
    // this function could get called even if the editor is
    // not fully constructed.
    if ( iUnitField )
        {
        iUnitField->MakeVisible( UnitFieldVisibility() );    
        }
        
    CEikMfne::FocusChanged( aDrawNow );
    }


TBool CAknUnitEditor::UnitFieldVisibility() const
    {
    return ( !Math::IsNaN( Value() ) || IsFocused() );
    }


// End of file
