/*
* Copyright (c) 2005-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Preview popup observer.
*
*/


#ifndef AKNPREVIEWPOPUPOBSERVER_H
#define AKNPREVIEWPOPUPOBSERVER_H

// FORWARD DECLARATIONS
class CAknPreviewPopUpController;

// CLASS DECLARATION

/**
*  Interface for observing preview popup events.
*
*  @lib avkon.lib
*  @since S60 3.2
*/
class MAknPreviewPopUpObserver
    {    
    public:
    
        /** Preview popup event types. */
        enum TPreviewPopUpEvent
                {                
                /** Preview popup is shown. */
                EPreviewPopUpShown,
                /** Preview popup is hidden. */
                EPreviewPopUpHidden
                };

    public:
   
        /**
        * Called by the preview popup when an appropriate event takes place. 
        * @param aController Pointer to the sender of the event.
        * @param aEvent Event type.
        */
        virtual void HandlePreviewPopUpEventL(
            CAknPreviewPopUpController* aController,
            TPreviewPopUpEvent aEvent ) = 0;
    };

#endif // AKNPREVIEWPOPUPOBSERVER_H

//  End of File  
