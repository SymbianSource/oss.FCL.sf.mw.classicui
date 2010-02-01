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
* Description: 
*     A foreground observer control in the status pane's navigation pane.
*
*
*
*/


#ifndef AKNNAVIFOREGROUNDOBSERVER_H
#define AKNNAVIFOREGROUNDOBSERVER_H

#include <coecntrl.h>
#include <coemain.h>
#include "aknnavi.h"

class MAknTabObserver; 

/**
 * Observer which holds the status of the foreground/background state of the
 * navipane.
 *
 */
NONSHARABLE_CLASS(CAknNaviForegroundObserver) :  public CCoeControl, 
                                                 public MCoeForegroundObserver
	{
public:
    /** Destructor */
    ~CAknNaviForegroundObserver();

    static CAknNaviForegroundObserver* NewL(CAknNavigationControlContainer* aParent);
    static CAknNaviForegroundObserver* NewLC(CAknNavigationControlContainer* aParent);

    /** Control is in foreground or not */
    TBool HasForegroundGained();

public: // From MCoeForegroundObserver

	/** Handles the application coming to the foreground. */
	void HandleGainingForeground();
	/** Handles the application going into the background. */
	void HandleLosingForeground();

private:
    /** Standard constructor */
    CAknNaviForegroundObserver();

    void ConstructL(CAknNavigationControlContainer* aParent);

private:
    TBool iHasForegroundGained;
    CAknNavigationControlContainer* iParent;
    };

#endif // AKNNAVIFOREGROUNDOBSERVER_H
