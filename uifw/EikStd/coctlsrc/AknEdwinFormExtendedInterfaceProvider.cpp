/*
* Copyright (c) 2003 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  ?Description
*
*/


// INCLUDE FILES

#include <inlinetext.h>
#include <AknEdwinFormExtendedInterfaceProvider.h>

class CAknCompositeInlineTextSource;
#include "AknCompositeInlineTextSource.h"

// MODULE TEMPLATES


// MODULE DATA STRUCTURES


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// C++ constructor
// -----------------------------------------------------------------------------
//
CAknEdwinFormExtendedInterfaceProvider::CAknEdwinFormExtendedInterfaceProvider()
    {
    }

// -----------------------------------------------------------------------------
// Two-phase constructor.
// -----------------------------------------------------------------------------
//
EXPORT_C CAknEdwinFormExtendedInterfaceProvider* CAknEdwinFormExtendedInterfaceProvider::NewL()
    {
	CAknEdwinFormExtendedInterfaceProvider* self= new(ELeave) CAknEdwinFormExtendedInterfaceProvider();
	CleanupStack::PushL(self);
	self->ConstructL();
    CleanupStack::Pop(); // self
	return self;
    }

// -----------------------------------------------------------------------------
// Destructor
// -----------------------------------------------------------------------------
//
CAknEdwinFormExtendedInterfaceProvider::~CAknEdwinFormExtendedInterfaceProvider()
    {
    delete iCompositeInlineTextSource;
    }

// ------------------------------------------------------------------------------
// 2nd stage constructor
// ------------------------------------------------------------------------------
void CAknEdwinFormExtendedInterfaceProvider::ConstructL()
    {
    iCompositeInlineTextSource = CAknCompositeInlineTextSource::NewL();
    }

// ------------------------------------------------------------------------------
// Accessor method for combined InlineTextSource interface
// This method is called from Avkon custom formatting clients who need to change the
// state of the Composite inline text system.
// ------------------------------------------------------------------------------
EXPORT_C CAknCompositeInlineTextSource& CAknEdwinFormExtendedInterfaceProvider::CompositeInlineTextSource() const
    {
    return *iCompositeInlineTextSource;
    }


// -----------------------------------------------------------------------------
// GetExtendedInterface
//
// Currently the FormatObserver is returned as the same object as the composite inline text.
// In future, there may be other object wanting to observer the FormatL, so an intermediate
// object would be needed then to distribute the event.. .
// -----------------------------------------------------------------------------
//
TAny* CAknEdwinFormExtendedInterfaceProvider::GetExtendedInterface( const TUid& aInterfaceId )
    {
   	if (aInterfaceId.iUid == KInlineTextApiExtensionUid.iUid)
	    {
	    return static_cast<MTmInlineTextSource*>(iCompositeInlineTextSource);
	    }
    else
	    {
	    return NULL;
	    }   
    }

//  End of File  

