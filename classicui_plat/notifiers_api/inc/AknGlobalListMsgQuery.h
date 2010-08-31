/*
* Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Uses notification framework to show a global list query with 
*                message field.
*
*/

#ifndef __AKNGLOBALLISTMSGQUERY_H__
#define __AKNGLOBALLISTMSGQUERY_H__

#include <AknNotifyStd.h>
#include <AknQueryDialog.h>

class CAknSDData;

/**
* Uses notification framework to show a global list query with message field.
*   
* Usage:
*     Create an active object, start it and pass its TRequestStatus as a
*     parameter to ShowListMsgQueryL(). After the user selects one item from
*     the query and accepts it, the request status will hold the number of the
*     selected item. If the user cancels the query with softkey, the request status will
*     hold -1. If method CancelListMsgQuery() is called, the request status will  
*     hold -3 (KErrCancel).
*
* Example 1. Show the global list message query:
* @code
*     #include <akngloballistmsgquery.h>
*     ...
*     _LIT(KQueryHeaderText, "Global list msg query");
*     _LIT(KQueryMsgText, "Query message.");
*     _LIT(KListMsgQueryItem1, "Item 1");
*     _LIT(KListMsgQueryItem2, "Item 2");
*
*     CDesCArray* textArray = new (ELeave) CDesCArrayFlat(2);
*     CleanupStack::PushL(textArray);
*     textArray->AppendL(KListMsgQueryItem1);
*     textArray->AppendL(KListMsgQueryItem2);
*         
*     if (iListObserver)
*         {
*         iListObserver->Cancel();
*         delete iListObserver;
*         iListObserver = 0;
*         }
*
*     if (iGlobalListMsgQuery)
*         {
*         delete iGlobalListMsgQuery;
*         iGlobalListMsgQuery = 0;
*         }
*
*     iListObserver = CMyActiveObject::NewL();
*     iGlobalListMsgQuery = CAknGlobalListMsgQuery::NewL();
*
*     iGlobalListMsgQuery->ShowListMsgQueryL(
*         textArray, 
*         iListObserver->iStatus, 
*         KQueryHeaderText,
*         KQueryMsgText);
*
*     iListObserver->Start();
*
*     CleanupStack::PopAndDestroy(textArray);
* @endcode
*
* Example 2. Get and handle the result in active object. The result is simply displayed on 
*            screen using info message:
* @code
*     void CMyActiveObject::RunL() 
*         {
*         _LIT(KReceivedMsg, "Received:");
*         TBuf<100> msg = KReceivedMsg();
*         msg.AppendNum(iStatus.Int());
*         CEikonEnv::Static()->InfoMsg(msg);
*         }
* @endcode
*
* @lib AknNotify.lib
* @since S60 3.2
*/
NONSHARABLE_CLASS(CAknGlobalListMsgQuery) : public CBase
    {
public:
    /**
    * Two-phased constructor.
    *
    * @return A pointer to the new instance.
    */
    IMPORT_C static CAknGlobalListMsgQuery* NewL();

    /**
    * Two-phased constructor. Leaves the instance to cleanup stack.
    *
    * @return A pointer to the new instance.
    */
    IMPORT_C static CAknGlobalListMsgQuery* NewLC();

    /**
    * Destructor.
    */
    IMPORT_C ~CAknGlobalListMsgQuery();

    /**
    * Shows the global list message query.
    *
    * @param  aItems           Array of strings for list items. The items will be copied, so it is
    *                          safe to delete the array as soon as ShowListMsgQueryL() has been called.
    * @param  aStatus          TRequestStatus which will be completed when user dismisses the query.
    *                          Will contain KErrInUse if another global list query is already being shown.
    *                          Will contain KErrArgument if aSoftkeys does not point to a valid resource.
    *                          Will contain KErrArgument if aItems array is empty.
    *                          Will contain KErrArgument if aIndex is out of bounds.
    *                          Will contain KErrArgument if aAcceptKeyId is EAknSoftkeyCancel.
    *                          Will contain KErrArgument if aCancelKeyId is EAknSoftkeyOk.
    * @param  aHeaderText      Query header text.
    * @param  aMsgText         Query message text. Maximum is three lines.
    * @param  aIndex           Index of the item that will be highlighted by default.    
    * @param  aSoftkeys        Softkey resource id from Avkon.rss. If used, give also 
    *                          aAcceptKeyId and aCancelKeyId.
    * @param  aAcceptKeyId     Identifier of the softkey that is used to accept the query.
    * @param  aCancelKeyId     Identifier of the softkey that is used to cancel the query.
    * @param  aHeaderImageFile A full path to image to be used in the header field.
    * @param  aImageId         Image id.
    * @param  aImageId         Image mask id.
    * @param  aTone            Tone id.
    */
    IMPORT_C void ShowListMsgQueryL(
        const MDesCArray* aItems,
        TRequestStatus& aStatus,
        const TDesC& aHeaderText,
        const TDesC& aMsgText,
        const TInt aIndex = 0,
        TInt aSoftkeys = 0,
        TInt aAcceptKeyId = 0,
        TInt aCancelKeyId = 0,
        const TDesC& aHeaderImageFile = KNullDesC,        
        TInt aImageId = 0,
        TInt aImageMaskId = -1,
        CAknQueryDialog::TTone aTone = CAknQueryDialog::ENoTone);

    /**
    * Moves selection up.
    */
    IMPORT_C void MoveSelectionUp();

    /**
    * Moves selection down.
    */
    IMPORT_C void MoveSelectionDown();

    /**
    * Selects currently selected item in the list.
    */
    IMPORT_C void SelectItem();

    /**
    * Cancels the query.
    */
    IMPORT_C void CancelListMsgQuery();

    /**
    * Sets additional information to be sent to secondary display. Takes ownership of object.
    * Must be called before sending data to notifier to have effect.
    *
    * @param aData Data to be sent to cover UI.
    */
    IMPORT_C void SetSecondaryDisplayData(CAknSDData* aData);
    
    /**
    * Sets skin id for image. Must be called before ShowListMsgQueryL() is called.
    * 
    * @param aId Image skin id.
    */
    IMPORT_C void SetImageSkinId(const TAknsItemID& aId);
    
private:
    /**
    * Default constructor.
    */
    CAknGlobalListMsgQuery();

    /**
    * Symbian second-phase constructor.
    */
    void ConstructL(); 
    
    /**
    * Sets the heading for the query.
    */
    void SetHeadingL(const TDesC& aHeading);
    
    /**
    * Updates the query.
    */
    void UpdateListMsgQuery();        

private:
    // Command id.
    TAknGlobalQueryCmd iCmd;
    // Notifier handle.
    RNotifier iNotify;
    // Index to set which item will be selected.
    TInt iIndex;
    // Buffer to hold the variables passed to server.
    CBufFlat *iBuffer;
    // Pointer to buffer.
    TPtrC8 iBufferPtr;
    HBufC* iHeading;
    CAknSDData* iAknSDData;
    TBuf8<1> iResultBuf; // Not really used, but needed to prevent buffer handling errors.
    TInt iSkinsMajorId;
    TInt iSkinsMinorId;
    };

#endif // __AKNGLOBALLISTMSGQUERY_H__
