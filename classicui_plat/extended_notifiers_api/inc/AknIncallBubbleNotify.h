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
* Description:  In call bubble notify.
*
*/

#ifndef __AKNINCALLBUBBLENOTIFY_H__
#define __AKNINCALLBUBBLENOTIFY_H__

#include <AknNotify.h>

NONSHARABLE_CLASS(CAknIncallBubble) : public CAknNotifyBase
    {
    friend class CPhoneIncallIndicator;
    friend class CIdleAppUi;
    friend class CVtUiAppUi;
    friend class CIndicViewContainer;

public:
    IMPORT_C static CAknIncallBubble* NewL();
    IMPORT_C static CAknIncallBubble* NewLC();
    IMPORT_C ~CAknIncallBubble();
    
public:
    IMPORT_C void SetIncallBubbleFlagsL(const TInt aFlags);
    IMPORT_C void SetIncallBubbleAllowedInIdleL(TBool aAllowed);
    IMPORT_C void SetIncallBubbleAllowedInUsualL(TBool aAllowed);
    
private:
    CAknIncallBubble();
    void ConstructL();
    
private:
    IMPORT_C void CAknNotifyBase_Reserved();

private:
    };

#endif // __AKNINCALLBUBBLENOTIFY_H__
