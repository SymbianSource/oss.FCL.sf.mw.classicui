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
* Description:  Transition utilities.
*
*/


#include <e32property.h>

#include "aknpsobserver.h"

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//
CAknPsObserver* CAknPsObserver::NewL( MAknPsObserver* aClient, 
                                      const TUid aCategory, 
                                      const TUint aKey )
    {
    CAknPsObserver* self = new ( ELeave ) CAknPsObserver( aClient, aCategory, 
                                                          aKey);
    CleanupStack::PushL( self );
    self->Construct( aCategory, aKey );
    CleanupStack::Pop();
    return self;
    }

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//
CAknPsObserver* CAknPsObserver::New( MAknPsObserver* aClient, 
                                     const TUid aCategory, 
                                     const TUint aKey )
    {
    CAknPsObserver* self = new CAknPsObserver( aClient, aCategory, aKey);
    if(self)
    	{
	    self->Construct( aCategory, aKey );
    	}
    return self;
    }
    
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//
CAknPsObserver::~CAknPsObserver()
    {
    Cancel();
    iProperty.Close();
    }
    
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//
void CAknPsObserver::DoCancel()
    {
    iProperty.Cancel();
    }
    
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//
void CAknPsObserver::RunL()
    {
    if ( iStatus.Int() == KErrNone)
        {
        TInt val;
        iProperty.Subscribe( iStatus );
        iProperty.Get( val );
        SetActive();
        iClient->PsValueUpdated( iCategory, iKey, val );
        }
    }

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//
void CAknPsObserver::Construct( const TUid aCategory, const TUint aKey )
    {
    CActiveScheduler::Add( this );
    iProperty.Attach( aCategory, aKey );
    iProperty.Subscribe( iStatus );
    SetActive();
    }

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//
TInt CAknPsObserver::GetCurrentValue( TInt& aValue )
    {
    return iProperty.Get( aValue );
    }

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//
CAknPsObserver::CAknPsObserver( MAknPsObserver* aClient, const TUid aCategory,
                                const TUint aKey )
    : CActive( EPriorityStandard ), iClient( aClient ),
      iCategory( aCategory ), iKey( aKey )
    {
    }

