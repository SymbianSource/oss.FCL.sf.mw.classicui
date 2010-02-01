/*
* Copyright (c) 2002-2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Global list query dialog declaration.
*
*/

#ifndef __AKNLISTQUERYNOTIFICATIONDIALOG__
#define __AKNLISTQUERYNOTIFICATIONDIALOG__

#include <AknQueryDialog.h>
#include <aknlistquerydialog.h>

class MAknListQueryNotificationCallback
    {
public:
    virtual void QueryDismissedL(TInt aResult) = 0;
    };

NONSHARABLE_CLASS(CAknListQueryNotificationDialog) : public CAknListQueryDialog
    {
public:
    CAknListQueryNotificationDialog( 
        TInt* aIndex,
        MAknListQueryNotificationCallback* aCallBack,
        CAknListQueryNotificationDialog** aSelfPtr);

    ~CAknListQueryNotificationDialog();
    
    TKeyResponse OfferKeyEventL( 
        const TKeyEvent& aKeyEvent,
        TEventCode aType);
    
    void HandleListBoxEventL(CEikListBox* aListBox, 
                                              TListBoxEvent aEventType);

protected:
    TBool OkToExitL(TInt aButtonId);
    
private: 
    virtual void CEikDialog_Reserved_1();
    virtual void CEikDialog_Reserved_2();   
    virtual void CAknDialog_Reserved();
    virtual void CAknQueryDialog_Reserved();   
    MAknListQueryNotificationCallback* iCallBack;
    CAknListQueryNotificationDialog** iSelfPtr;
    TBool iPanning;
    TBool iFlick;
    };

#endif // __AKNLISTQUERYNOTIFICATIONDIALOG__

// End of file
