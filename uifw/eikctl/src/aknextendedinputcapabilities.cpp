/*
* Copyright (c) 2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Class for extended input capabilities
*
*/


#include "aknextendedinputcapabilities.h"

// ======== MEMBER FUNCTIONS ========

EXPORT_C CAknExtendedInputCapabilities* CAknExtendedInputCapabilities::NewL()
    {
    CAknExtendedInputCapabilities* self = CAknExtendedInputCapabilities::NewLC();
    CleanupStack::Pop( self );
    return self;
    }


EXPORT_C CAknExtendedInputCapabilities* CAknExtendedInputCapabilities::NewLC()
    {
    CAknExtendedInputCapabilities* self = new( ELeave ) CAknExtendedInputCapabilities;
    CleanupStack::PushL( self );
    self->ConstructL();
    return self;
    }
    
    
EXPORT_C CAknExtendedInputCapabilities::~CAknExtendedInputCapabilities()
    {
    iObserverArray.Close();
    }


// ---------------------------------------------------------------------------
// Sets the given simple capabilitites (does not add)
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknExtendedInputCapabilities::SetCapabilities( TUint aCapabilities )
    {
    iInputCapabilities = aCapabilities;
    }


// ---------------------------------------------------------------------------
// Gets the simple capabilities
// ---------------------------------------------------------------------------
//    
EXPORT_C TUint CAknExtendedInputCapabilities::Capabilities() const
    {
    return iInputCapabilities;
    }


// ---------------------------------------------------------------------------
// Tests if the given simple capabilities are supported
// ---------------------------------------------------------------------------
//    
EXPORT_C TBool CAknExtendedInputCapabilities::SupportsCapabilities( TUint aCapabilities ) const
    {
    TBool supportsCapabilities( EFalse );
    
    if ( iInputCapabilities & aCapabilities == aCapabilities )
        {
        supportsCapabilities = ETrue;
        }
        
    return supportsCapabilities;
    }


// ---------------------------------------------------------------------------
// Sets the given MIDP constraints (does not add)
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknExtendedInputCapabilities::SetMIDPConstraints( TUint aConstraints )
    {
    iMIDPConstraints = aConstraints;
    }


// ---------------------------------------------------------------------------
// Gets the MIDP constraints
// ---------------------------------------------------------------------------
//    
EXPORT_C TUint CAknExtendedInputCapabilities::MIDPConstrainst() const
    {
    return iMIDPConstraints;
    }


// ---------------------------------------------------------------------------
// Sets the editor type
// ---------------------------------------------------------------------------
//    
EXPORT_C void CAknExtendedInputCapabilities::SetEditorType( TInt aEditorType )
    {
    iEditorType = aEditorType;
    }
   

// ---------------------------------------------------------------------------
// Gets the editor type
// ---------------------------------------------------------------------------
//    
EXPORT_C TInt CAknExtendedInputCapabilities::EditorType() const
    {
    return iEditorType;
    }
    
    
// ---------------------------------------------------------------------------
// Registers an observer
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknExtendedInputCapabilities::RegisterObserver( MAknEventObserver* aObserver )
    {
    UnregisterObserver( aObserver ); // to prevent double entries
    iObserverArray.Append( aObserver );
    }


// ---------------------------------------------------------------------------
// Unregisters an observer
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknExtendedInputCapabilities::UnregisterObserver( MAknEventObserver* aObserver )
    {
    TInt index = iObserverArray.Find( aObserver );
    
    if ( index != KErrNotFound )
        {
        iObserverArray.Remove( index );
        }
    }


// ---------------------------------------------------------------------------
// Sends an event to observers (if any)
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknExtendedInputCapabilities::ReportEventL( TInt aEvent, TAny* aParams )
    {
    for ( TInt i = 0; i < iObserverArray.Count(); ++i )
        {
        iObserverArray[i]->HandleInputCapabilitiesEventL( aEvent, aParams );
        }
    }

CAknExtendedInputCapabilities::CAknExtendedInputCapabilities()
    {
    }


void CAknExtendedInputCapabilities::ConstructL()
    {
    }
    

EXPORT_C CAknExtendedInputCapabilities::CAknExtendedInputCapabilitiesProvider::
    CAknExtendedInputCapabilitiesProvider()
    {
    }
    

EXPORT_C CAknExtendedInputCapabilities::CAknExtendedInputCapabilitiesProvider::
    ~CAknExtendedInputCapabilitiesProvider()
    {
    }
    

EXPORT_C void CAknExtendedInputCapabilities::
    CAknExtendedInputCapabilitiesProvider::SetExtendedInputCapabilities(
        CAknExtendedInputCapabilities* aExtendedInputCapabilities )
    {
    iExtendedInputCapabilities = aExtendedInputCapabilities;
    }


EXPORT_C CAknExtendedInputCapabilities* CAknExtendedInputCapabilities::
    CAknExtendedInputCapabilitiesProvider::ExtendedInputCapabilities() const
    {
    return iExtendedInputCapabilities;
    }


EXPORT_C void CAknExtendedInputCapabilities::
    CAknExtendedInputCapabilitiesProvider::SetMopParent(
        MObjectProvider* aObjectProvider )
    {
    iParent = aObjectProvider;
    }


TTypeUid::Ptr CAknExtendedInputCapabilities::
    CAknExtendedInputCapabilitiesProvider::MopSupplyObject( TTypeUid aId )
    {
    if ( aId.iUid == CAknExtendedInputCapabilities::ETypeId &&
         iExtendedInputCapabilities )
        {
        return aId.MakePtr( iExtendedInputCapabilities );
        }
    
    return TTypeUid::Null();
    }


MObjectProvider* CAknExtendedInputCapabilities::
    CAknExtendedInputCapabilitiesProvider::MopNext()
    {
    return iParent; // NULL is also valid
    }


// End of file
