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
* Description:  This class updates the status indicator container control
*                in status pane.
*
*/


#ifndef C_AKNSTATUSPANEINDICATOROBSERVER_H
#define C_AKNSTATUSPANEINDICATOROBSERVER_H

#include <bacntf.h>
#include <coecntrl.h>
#include <AknControl.h>
#include "aknstatuspanedata.h"
#include "aknstatuspanedataobserver.h"

class CBase;
class CAknIndicatorContainer;
class CAknStatusPaneDataSubscriber;

/**
* This internal Avkon class updates the status indicator container control in status pane.
*
* @since 3.2
* @lib Avkon
*/
NONSHARABLE_CLASS(CAknIndicatorDataObserver) : public CBase,
                                               public MAknStatusPaneDataObserver
	{

public:

    /**
    * Standard constructor
    */
    CAknIndicatorDataObserver(CAknIndicatorContainer* aIndicatorPane);

    /**
    * Destructor
    */
    ~CAknIndicatorDataObserver();

    /**
    * From MAknStatusPaneDataObserver
    */
    void HandleUpdateL(const TAknStatusPaneStateData& aData);

private:

	  // Not owned. Pointer to Indicator pane.
    CAknIndicatorContainer* iIndicatorPane;

    // Not owned. Pointer to data subscriber.
    CAknStatusPaneDataSubscriber*  iDataSubscriber;

    TBool iFirstUpdate;
    };

#endif // C_AKNSTATUSPANEINDICATOROBSERVER_H
