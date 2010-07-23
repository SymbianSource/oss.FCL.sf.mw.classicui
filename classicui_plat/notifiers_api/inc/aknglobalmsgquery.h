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
* Description:  Uses notification framework to show a global message query.
*
*/

#ifndef __AKNGLOBALMSGQUERY_H__
#define __AKNGLOBALMSGQUERY_H__

#include <AknNotify.h>
#include <AknNotifyStd.h>
#include <AknQueryDialog.h>
#include <AknsItemID.h>

class CAknSDData;

/**
* CAknGlobalMsgQuery
*   Uses notification framework to show a global message query.
*   Usage:
*       Create an active object, start it and pass its TRequestStatus as a
*       parameter to ShowMsgQueryL. After the user presses a softkey,
*       the request status will hold the id of the pressed softkey. E.g. 
*       If the user selected Cancel, the request status will hold -1.
*
*   Example 1. Show the global message query:
*        if ( iListObserver )
*            {
*            iListObserver->Cancel();
*            delete iListObserver;
*            }
*        iMsgObserver = new(ELeave) CGlobalMsgObserver(iEikonEnv);
*        iMsgObserver->Start();
*        iGlobalMsgQuery->ShowMsgQueryL(
*            iMsgObserver->iStatus, iMsgText, 
*            R_AVKON_SOFTKEYS_OK_CANCEL, iMsgHeader,
*            iHeaderImageFile, EImageId, EMaskId );
*
*   Example 2. Get and handle the result in active object.
*        void CMyActiveObject::RunL() 
*            {
*            TBuf<120> msg = _L("Received: ");
*            msg.AppendNum( iStatus.Int() );
*            iEnv->InfoMsg(msg);
*            Cancel();
*            }
*
*   Example 3. Update the query (softkeys)
*       iGlobalMsgQuery->UpdateMsgQuery( R_AVKON_SOFTKEYS_BACK );
*
*   Example 4. Cancel the query
*       iGlobalMsgQuery->CancelMsgQuery();
*
* NOTE !!! All descriptors passed as parameters need to be class members, i.e.
*           they cannot be local variables of a method. That is because
*           they need to exist when server gets the message.
*/

NONSHARABLE_CLASS(CAknGlobalMsgQuery) : public CBase
    {
    public:
        IMPORT_C static CAknGlobalMsgQuery* NewL();
        IMPORT_C static CAknGlobalMsgQuery* NewLC();
        IMPORT_C ~CAknGlobalMsgQuery();

        /**
        * Shows global message query synchronously.
        *
        * @param    aMsgText        Message text.
        * @param    aHeaderText     Header text.
        * @param    aSoftkeys       Softkey resource.
        * @param    aStatus         TRequestStatus which will be completed when user
        *                           selects one item from the list query.
        */
        IMPORT_C void ShowMsgQueryL( 
            TRequestStatus& aStatus,
            const TDesC& aMsgText,
            TInt aSoftkeys,
            const TDesC& aHeaderText,
            const TDesC& aHeaderImageFile,
            TInt aImageId = 0,
            TInt aImageMaskId = -1,
            CAknQueryDialog::TTone aTone = CAknQueryDialog::ENoTone);

        /**
        * Update the softkeys of the message query.
        *
        * @param    aSoftkeys  New resource for softkeys.
        */
        IMPORT_C void UpdateMsgQuery( TInt aSoftkeys );

        /**
        * Cancel the message query.
        */
        IMPORT_C void CancelMsgQuery();

        /**
        * Set delay after which query will be removed from screen after message is completed.
        * Can be used to get around problems with global query exit and CrossCheckForeground probs.
        * Must be called before ShowMsgQueryL in order to be effective.
        * 
        * @param aDelay   Time in microsecond, after which query will be removed from display.
        * @since  S60 2.1
        */
        IMPORT_C void SetExitDelay(TInt aDelay);

        /**
        * Set Skin id for query header image. Must be called before ShowMsgQueryL in order to have 
        * effect. No need to use this method if image from avkon.mbm is used.
        *
        * @aparam aId   SkinId for image in query. If image not found from active skin, image 
        *               definitions used in ShowMsgQueryL used instead.
        * @since S60 2.6
        */      
        IMPORT_C void SetImageSkinId( TAknsItemID& aId );

        /**
        * Sets additional information to be sent to secondary display. Takes ownership of object.
        * Must be called before sending data to notifier to have effect.
        *
        * @param aData Data to be sent to cover UI.
        * @internal to S60
        * @since S60 3.1
        */
        IMPORT_C void SetSecondaryDisplayData(CAknSDData* aData);
    
    private:
        CAknGlobalMsgQuery();
        void ConstructL(); 

    private:
        TAknGlobalQueryCmd iCmd;
        TInt iSoftkeys;
        TInt iImageId;
        TInt iImageMaskId;
        CAknQueryDialog::TTone iTone;
        RNotifier iNotify;
        CBufFlat *iBuffer;
        TPtrC8 iBufferPtr;
        TInt iDelay;
        TInt   iSkinsMajorId;
        TInt   iSkinsMinorId;
        CAknSDData* iAknSDData;
        TBuf8<1> iResultBuf; // Not really used, but needed to prevent buffer handling errors.
    };

#endif // __AKNGLOBALMSGQUERY_H__
