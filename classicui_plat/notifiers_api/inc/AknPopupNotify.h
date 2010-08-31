/*
* Copyright (c) 2002-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Class definition of AVKON pop-up notifier.
*
*/

#ifndef C_AKNPOPUPNOTIFY_H
#define C_AKNPOPUPNOTIFY_H

#include <AknNotify.h>

/**
 * Class for displaying a message using a notifier pop-up.
 *
 * @deprecated
 */
NONSHARABLE_CLASS(CAknPopupNotify) : public CAknNotifyBase
    {
public:
    /**
     * @deprecated
     */
    IMPORT_C static CAknPopupNotify* NewL();
    
    /**
     * @deprecated
     */
    IMPORT_C static CAknPopupNotify* NewLC();
    
    /**
     * @deprecated
     */
    IMPORT_C ~CAknPopupNotify();

    /**
     * @deprecated
     */
    IMPORT_C void PopupMessageL(const TDesC& aMessage);

private:
    /**
     * @deprecated
     */
    CAknPopupNotify();
    
    /**
     * @deprecated
     */
    void ConstructL();
    
private:
    /**
     * @deprecated
     */
    IMPORT_C void CAknNotifyBase_Reserved();
    };

#endif // C_AKNPOPUPNOTIFY_H
