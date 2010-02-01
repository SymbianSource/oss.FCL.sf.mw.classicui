/*
* Copyright (c) 2006-2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  This internal Avkon class updates the battery indicator 
*                control in status pane.
*
*/


#ifndef C_AKNSTATUSPANEBATTERYOBSERVER_H
#define C_AKNSTATUSPANEBATTERYOBSERVER_H

#include <bacntf.h>
#include <coecntrl.h>
#include <AknControl.h>
#include "aknstatuspanedata.h"
#include "aknstatuspanedataobserver.h"

class CBase;
class CAknBatteryPane;
class CAknStatusPaneDataSubscriber;

/**
* This internal Avkon class updates the battery indicator control in status pane.
*
* @since S60 3.2
* @lib Avkon
* 
*/
NONSHARABLE_CLASS(CAknBatteryDataObserver) : public CBase, public MAknStatusPaneDataObserver
	{

public:

    /**
    * Standard constructor
    */
    CAknBatteryDataObserver(CAknBatteryPane* aBatteryPane);
    
    /**
    * Destructor
    */
    ~CAknBatteryDataObserver();

    /**
    * From MAknStatusPaneDataObserver
    */
	void HandleUpdateL(const TAknStatusPaneStateData& aData);
	        
private:

	  // Not owned. Pointer to battery pane. 
    CAknBatteryPane* iBatteryPane;
    
    // Not owned. Pointer to data subscriber.
    CAknStatusPaneDataSubscriber*  iDataSubscriber;
    };

#endif // C_AKNSTATUSPANEBATTERYOBSERVER_H
