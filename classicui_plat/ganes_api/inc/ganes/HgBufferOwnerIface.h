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


#ifndef HGBUFFEROWNERIFACE_H_
#define HGBUFFEROWNERIFACE_H_

#include <e32base.h>

/**
 * Buffer observer interface. 
 */
class MHgBufferOwner
    {
public:
    /**
     * Buffer position changed. 
     * The items between the aReleaseStart and aReleaseEnd should be released as soon as possible.
     * 
     * @param aReleaseStart The index of the first item in buffer.
     * @param aReleaseEnd The index of the last item in buffer.
     */
    virtual void Release(TInt aReleaseStart, TInt aReleaseEnd) = 0 ;
    };

#endif /*HGBUFFEROWNERIFACE_H_*/
