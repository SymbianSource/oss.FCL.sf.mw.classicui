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


#ifndef HGSCROLLBUFFEROBSERVERIFACE_H_
#define HGSCROLLBUFFEROBSERVERIFACE_H_

#include <e32base.h>
#include <ganes/HgBufferOwnerIface.h>

/**
 * Buffer observer interface. 
 */
class MHgScrollBufferObserver : public MHgBufferOwner 
    {
public:
    /**
     * The direction of request.
     */
    enum THgScrollDirection
        {
        EHgBufferNoMove, // Request initiated by adding or removing an item 
        EHgBufferReset, // Full buffer reset
        EHgBufferScrollUp, // Request items before the buffer
        EHgBufferScrollDown // Request items after the buffer
        };

public:
    /**
     * Buffer position changed. 
     * The items between the aBufferStart and aBufferEnd should be loaded as soon as possible.
     * 
     * @param aBufferStart The index of the first item in buffer.
     * @param aBufferEnd The index of the last item in buffer.
     * @param aDirection Scroll direction.
     */
    virtual void Request(TInt aRequestStart, TInt aRequestEnd, THgScrollDirection aDirection) = 0 ;
    
    };

#endif // HGSCROLLBUFFEROBSERVERIFACE_H_
