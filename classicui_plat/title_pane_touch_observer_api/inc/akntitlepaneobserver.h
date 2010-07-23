/*
* Copyright (c) 2005 Nokia Corporation and/or its subsidiary(-ies).
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
*     Interface class for titlepane. This observer is used
*     by applications to observe when title pane has been actioned. 
*
*
*/


#ifndef AKNTITLEPANEOBSERVER_H
#define AKNTITLEPANEOBSERVER_H

#include <e32base.h>

class MAknTitlePaneObserver
    {
public:
    enum TAknTitlePaneEvents
        {
        EAknTitlePaneTapped
        }; 
        
public:
    /**
    * HandleTitlePaneEventL is used in observers to handle title pane events.
    *
    * @param aEventID TAknTitlePaneEvents type title pane event
    */
    virtual void HandleTitlePaneEventL( TInt aEventID ) = 0; 
    };

#endif // AKNTITLEPANEOBSERVER_H
