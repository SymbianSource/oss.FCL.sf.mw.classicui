/*
* Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:         MAknInfoPopupNoteObserver's sub class
*
*/









#ifndef T_TBCTESTSUBAKNINFOPOPUPNOTEOBSERVER_H
#define T_TBCTESTSUBAKNINFOPOPUPNOTEOBSERVER_H

#include <akninfopopupnotecontroller.h> 

/**
 * MAknInfoPopupNoteObserver's sub class
 */
class TBCTestSubAknInfoPopupNoteObserver : public MAknInfoPopupNoteObserver
    {    
public: 

// from MAknInfoPopupNoteObserver

    /**
    * Handles events reported from info popup note.
    * @param aController The controller that controls the note, from
    *   where the event originates.
    * @param aEvent The event.
    */    
    void HandleInfoPopupNoteEvent(
            CAknInfoPopupNoteController* /*aController*/,
             MAknInfoPopupNoteObserver::TAknInfoPopupNoteEvent /*aEvent*/ ){}

    };

#endif // T_TBCTESTSUBAKNINFOPOPUPNOTEOBSERVER_H
