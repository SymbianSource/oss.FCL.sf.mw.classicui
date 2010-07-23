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
* Description:  information_preview_popup_api
*
*/

#ifndef C_TESTSDKIPPOBSERVER_H
#define C_TESTSDKIPPOBSERVER_H

//  INCLUDES
#include <aknpreviewpopupobserver.h>
    /**
     * Observer class
     */
class CTestPreviewPopupContent : public CCoeControl, public MAknPreviewPopUpObserver
    {
public:
    /**
     * constructors
     */
    CTestPreviewPopupContent(){};
    /**
     * Destructor
     */
    virtual ~CTestPreviewPopupContent(){};

    /**
    * Called by the preview popup when an appropriate event takes place. 
    * @param aController Pointer to the sender of the event.
    * @param aEvent Event type.
    */
    void HandlePreviewPopUpEventL(
        CAknPreviewPopUpController* /*aController*/,
        TPreviewPopUpEvent /*aEvent*/ )
        {
        
        };
    };

#endif /*C_TESTSDKIPPOBSERVER_H*/
