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
* Description:  Uses notification framework to show a global progress dialog.
*
*/

#ifndef __AKNGLOBALPROGRESSDIALOG_H__
#define __AKNGLOBALPROGRESSDIALOG_H__

#include <AknNotify.h>
#include <AknNotifyStd.h>
#include <AknProgressDialog.h>
#include <AknsItemID.h>

class CAknSDData;

/**
* CAknGlobalProgressDialog
*   Uses notification framework to show a global progress dialog.
*   Usage:
*       Create an active object, start it and pass its TRequestStatus as a
*       parameter to ShowProgressDialogL. After the dialog gets dismissed,
*       the request status will hold the id of the pressed softkey. E.g. 
*       If the user selected Cancel, the request status will hold -1.
*
*   Example 1. Construct global progress dialog and set icon and image.
*
*        iGlobalProgressDialog = CAknGlobalProgressDialog::NewL();
*        iGlobalProgressDialog->SetIconL( 
*            iIconText, 
*            iIconFile, 
*            iIconId, 
*            iIconMaskId);
*
*        iGlobalProgressDialog->SetImageL( 
*            iImageFile, 
*            iImageId, 
*            iImageMaskId);
*
*   Example 2. Show the global progress dialog:
*
*        iGlobalProgressDialog->ShowMsgQueryL(
*            iObserver->iStatus, 
*            iPrompt, 
*            R_AVKON_SOFTKEYS_OK_CANCEL, 
*            iFinalValue, 
*            CAknQueryDialog::EConfirmationTone );
*
*   Example 3. Update the progress (current and final value of the process).
*
*        iGlobalProgressDialog->UpdateProgressDialog( 100, 500 );
*
*   Example 4. Finish the progress
*               Needs to be called everytime the process has finished.
*               Dismisses the dialog.
*
*        iGlobalProgressDialog->ProcessFinished();
*
*   Example 5. Get and handle the result in active object.
*
*        void CMyActiveObject::RunL() 
*            {
*            TBuf<120> msg = _L("Received: ");
*            // iStatus.Int() holds the return value
*            msg.AppendNum( iStatus.Int() ); 
*            iEnv->InfoMsg(msg); // Show infomsg
*            Cancel();
*            }
*
*   Example 6. Cancel the progress dialog
*
*        iGlobalProgressDialog->CancelProgressDialog();
*/

NONSHARABLE_CLASS(CAknGlobalProgressDialog) : public CBase
    {
    public:
        IMPORT_C static CAknGlobalProgressDialog* NewL();
        IMPORT_C static CAknGlobalProgressDialog* NewLC();
        IMPORT_C ~CAknGlobalProgressDialog();

        /**
        * Set icon for the progress dialog
        *   Must be called before ShowProgressDialogL.
        *
        * @param    aIconText       Icon text
        * @param    aIconFile       Icon file
        * @param    aIconId         Icon id
        * @param    aIconMaskId     Mask id for icon
        */
        IMPORT_C void SetIconL( const TDesC& aIconText,
                                const TDesC& aIconFile,
                                TInt aIconId = 0,
                                TInt aIconMaskId = -1 );

        /**
        * Set image for the progress dialog
        *   Must be called before ShowProgressDialogL.
        *   If not set, default image will be used,
        *   i.e. EMbmAvkonQgn_note_progress
        *
        * @param    aImageFile       Image file
        * @param    aImageId         Image id
        * @param    aImageMaskId     Mask id for Image
        */
        IMPORT_C void SetImageL( 
            const TDesC& aImageFile,
            TInt aImageId = 0,
            TInt aImageMaskId = -1 );

        /**
        * Shows global progress dialog asynchronously
        *
        * @param    aStatus         TRequestStatus which will be completed
        *                               when the dialog gets dismissed
        * @param    aPrompt         Prompt text
        * @param    aSoftkeys       Softkeys resource id
        *                               If not set default softkeys are used.
        *                               i.e. R_AVKON_SOFTKEYS_CANCEL
        * @param    aFinalValue     Final value of the process
        * @param    aTone           Tone to be played after completion
        */
        IMPORT_C void ShowProgressDialogL( 
            TRequestStatus& aStatus,
            const TDesC& aPrompt,
            TInt aSoftkeys = 0,
            TInt aFinalValue = 0,
            CAknNoteDialog::TTone aTone = CAknNoteDialog::ENoTone );

        /**
        * Update Progress dialog with new progress values.
        *
        * @param    aValue      Current value of the process.
        * @param    aFinalValue Final value of the process. If not given the
        *                           existing value is used.
        */
        IMPORT_C void UpdateProgressDialog( 
            TInt aValue, 
            TInt aFinalValue = -1 );

        /**
        * ProcessFinished.
        *   Dismisses the dialog. Needs to be called after the 
        *   process has finished.
        */
        IMPORT_C void ProcessFinished();

        /**
        * Cancel the progress dialog.
        *   Cancels the request and deletes the dialog.
        */
        IMPORT_C void CancelProgressDialog();

        /**
        * @since  S60 2.6
        * Set Skin ids for note image and icon. Must be called before ShowProgressDialogL in order 
        * to have effect. No need to use this method if image from avkon.mbm is used.
        *
        * @aparam aImageId      SkinId for image in query. If image not found from active skin, 
        *                       default image / SetImageL definitions used instead.
        *
        * @aparam aIconId       SkinId for icon in query. If image not found from active skin, 
        *                       default icon / SetIconL definitions used instead.
        */      
        IMPORT_C void SetImageSkinIds( TAknsItemID& aImageId, TAknsItemID& aIconId );
        
        /**
        * @since S60 3.1
        * Sets additional information to be sent to secondary display.
        * Takes ownership of object.
        * Must be called before sending data to notifier to have effect.
        * @internal to S60
        *
        * @aparam aData Data to be sent to cover UI.
        */        
        IMPORT_C void SetSecondaryDisplayData(CAknSDData* aData);
    
    private:
        /**
        * Default constructor.
        */
        CAknGlobalProgressDialog();

        /**
        * ConstructL.
        */
        void ConstructL(); 

        /**
        * Update notifier.
        */
        void UpdateNotifier();

    private:
        // Command send to server.
        TAknGlobalQueryCmd iCmd;
        // Final value of the process.
        TInt iFinalValue;
        // Current value of the process.
        TInt iValue;
        // Handle to session with notify server.
        RNotifier iNotify;
        // Buffer used to pass parameters to server.
        CBufFlat *iBuffer;
        // Pointer to iBuffer
        TPtrC8 iBufferPtr;

        // Id of the image.
        TInt iImageId;
        // Id of the image's mask.
        TInt iImageMaskId;
        // Id of the icon.
        TInt iIconId;
        // Id of the icon's mask.
        TInt iIconMaskId;

        // Icon's text.
        HBufC* iIconText;
        // Icon file name.
        HBufC* iIconFile;
        // Image file name.
        HBufC* iImageFile;

        TInt   iImageSkinsMajorId;
        TInt   iImageSkinsMinorId;

        TInt   iIconSkinsMajorId;
        TInt   iIconSkinsMinorId;
        CAknSDData* iAknSDData;
        TBuf8<1> iResultBuf; // Not really used, but needed to prevent buffer handling errors.
    };

#endif // __AKNGLOBALPROGRESSDIALOG_H__
