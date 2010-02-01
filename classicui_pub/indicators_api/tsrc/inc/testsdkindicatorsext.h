/*
* Copyright (c) 2002 - 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  for testing the indicators api module
*
*/


#ifndef C_TESTSDKINDICATORSEXT_H
#define C_TESTSDKINDICATORSEXT_H

// INCLUDES
#include <aknindicatorobserver.h>

// CLASS DECLARATION

// the observer of CAknIndicatorContainer
class CAknIndicatorObserverExt: public CBase, public MAknIndicatorObserver
	{	
public:
	/**
    * HandleIndicatorEventL function for handling indicator events
    * in observed classes 
    * 
    * @param aIndicatorUid the uid of indicator which causes this event
    * @param aEventID TIndicatorEvents event to be handled 
    */
	virtual void HandleIndicatorEventL( TUid aIndicatorUid, TInt aEventID );
	
	};



#endif // C_TESTSDKINDICATORSEXT_H
