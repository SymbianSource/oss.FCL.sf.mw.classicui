/*
* Copyright (c) 2003-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  A foreground observer control in the status pane's
*                navigation pane.
*
*/


// INCLUDE FILES
#include "AknNaviForegroundObserver.h"

#include <AknTasHook.h>
CAknNaviForegroundObserver::CAknNaviForegroundObserver(){};

CAknNaviForegroundObserver::~CAknNaviForegroundObserver()
    {
    AKNTASHOOK_REMOVE();
    iCoeEnv->RemoveForegroundObserver( *this );     
    };

CAknNaviForegroundObserver* CAknNaviForegroundObserver::NewL(
    CAknNavigationControlContainer* aParent )
    {
	CAknNaviForegroundObserver* self =
	    CAknNaviForegroundObserver::NewLC( aParent );
	CleanupStack::Pop( self );
	return self;
    }

CAknNaviForegroundObserver* CAknNaviForegroundObserver::NewLC(
    CAknNavigationControlContainer* aParent )
    {
	CAknNaviForegroundObserver* self =
	    new (ELeave) CAknNaviForegroundObserver();
	CleanupStack::PushL( self );
	self->ConstructL( aParent );
	AKNTASHOOK_ADDL( self, "CAknNaviForegroundObserver" );
	return self;
    }

void CAknNaviForegroundObserver::ConstructL(
    CAknNavigationControlContainer* aParent )
    {
    iParent = aParent;
    iHasForegroundGained = EFalse;
    iCoeEnv->AddForegroundObserverL( *this );
    MakeVisible( EFalse );
    }

void CAknNaviForegroundObserver::HandleGainingForeground()
    {
    iHasForegroundGained = ETrue;
    TRAP_IGNORE( iParent->HandleGainingForegroundL() );
    }

void CAknNaviForegroundObserver::HandleLosingForeground()
    {
    iHasForegroundGained = EFalse;
    iParent->HandleLosingForeground();
    }

TBool CAknNaviForegroundObserver::HasForegroundGained()
    {
    return iHasForegroundGained;
    }
