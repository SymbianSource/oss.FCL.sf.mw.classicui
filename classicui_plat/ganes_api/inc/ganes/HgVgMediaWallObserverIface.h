/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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
*
*/

#ifndef HGVGMEDIAWALLBUTTONOBSERVER_H_
#define HGVGMEDIAWALLBUTTONOBSERVER_H_

// FORWARD DECLARATIONS
class CHgVgMediaWall;

/**
 * MediaWall observer interface.
 */
class MHgVgMediaWallObserver
    {
public:
    /**
     * Called by CHgVgMediaWall, when event handling from client is needed.
     * 
     * @param aEvent events type. @see CHgVgMediaWall::THgVgMediaWallEvent.
     * @param aSender MediaWall sending this event.
     */
    virtual void HandleMediaWallEvent(TInt aEvent, CHgVgMediaWall* aSender)=0;    
    };

#endif /* HGVGMEDIAWALLBUTTONOBSERVER_H */
