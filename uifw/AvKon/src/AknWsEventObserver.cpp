/*
* Copyright (c) 2001 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Implementation of classes derived from MAknWsEventObserver  
*  Support for the observation of events prior to their normal handling in the the
*  App Ui.
*
*
*/



// INCLUDES
#include "AknWsEventObserver.h"


// LOCAL FUNCTIONS

GLDEF_C void Panic(TAknWsEventObserverPanic aPanic)
	{
	_LIT(KPanicCat,"Avkon Ws Event Observer");
	User::Panic(KPanicCat, aPanic);
	}

// IMPLEMENTATIONS

CAknWsEventMonitor* CAknWsEventMonitor::NewL()
	{
	CAknWsEventMonitor* self=new(ELeave)CAknWsEventMonitor();
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop();
	return self;
	}

CAknWsEventMonitor::~CAknWsEventMonitor()
	{
	if (iEventObservers)
	    iEventObservers->Close();
	delete iEventObservers;
	}

void CAknWsEventMonitor::ConstructL()
	{
	iEventObservers = new (ELeave) RPointerArray<MAknWsEventObserver>(4);
	}

EXPORT_C void CAknWsEventMonitor::AddObserverL( MAknWsEventObserver* aEventObserver)
	{
    TInt index = iEventObservers->Find(aEventObserver);
    if (index == KErrNotFound)
        {
        iEventObservers->AppendL(aEventObserver);
        }
	}

EXPORT_C void CAknWsEventMonitor::RemoveObserver(const MAknWsEventObserver* aEventObserver)
	{
	// Remove the pointer, as the object may want to disappear...
    TInt index = iEventObservers->Find(aEventObserver);
    if (index != KErrNotFound)
        {
        iEventObservers->Remove(index);
        }
	}

EXPORT_C void CAknWsEventMonitor::HandleWsEventL(const TWsEvent& aEvent, CCoeControl* aDestination )
    {
    // make a quickshot for current Observers.
    TInt count = iEventObservers->Count();
    if ( count == 0 )
        {
        return;
        }
    
    // not own
    RArray<MAknWsEventObserver*> snapShot( 4 );
    CleanupClosePushL( snapShot );
    
    for ( TInt i = 0; i < count; i++ )
        {
        snapShot.AppendL( (*iEventObservers)[i] );
        }
    
    for ( TInt i = 0; i < count; i++ )
        {
        MAknWsEventObserver* eventObserver = snapShot[i];
        if ( eventObserver && iEventObservers->Find( eventObserver ) != KErrNotFound )
            {
            eventObserver->HandleWsEventL(aEvent, aDestination);
            }
        }
   
    CleanupStack::PopAndDestroy(); // CleanupClosePushL( quichShort );
    }

EXPORT_C void CAknWsEventMonitor::Enable(TBool aEnable)
    {
    iEnabled = aEnable;
    }
	
TBool CAknWsEventMonitor::IsEnabled()
    {
    return iEnabled;
    }

EXPORT_C void CAknWsEventMonitor::Reserved_1()
	{
	}


