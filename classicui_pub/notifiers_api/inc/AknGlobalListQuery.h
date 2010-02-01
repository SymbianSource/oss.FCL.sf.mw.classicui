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
* Description:  Uses notification framework to show a global list query.
*
*/

#ifndef __AKNGLOBALLISTQUERY_H__
#define __AKNGLOBALLISTQUERY_H__

#include <AknNotify.h>
#include <AknNotifyStd.h>
#include <bamdesca.h>

class CAknSDData;

// Default index for list query
const TInt KGlobalListQueryDefaultIndex = 0;

_LIT( KGlobalListQueryItemSeparator, "\n");

/**
* CAknGlobalListQuery
*   Uses notification framework to show a global list query.
*   Usage:
*       Create an active object, start it and pass its TRequestStatus as a
*       parameter to ShowListQueryL. After the user selects one item from
*       the list query, the request status will hold the number of the
*       selected item. If the user selected Cancel, the request status will
*       hold -1.
*
*   Example 1. Show the global list query:
*        CDesCArray* textArray = iCoeEnv->ReadDesCArrayResourceL( R_GLOBAL_LIST_ARRAY );
*        CleanupStack::PushL(textArray);
*        TInt result = -555;
*        if ( iListObserver )
*            {
*            iListObserver->Cancel();
*            delete iListObserver;
*            }
*        iListObserver = new(ELeave) CGlobalListObserver(iEikonEnv);
*        iListObserver->Start();
*        iGlobalListQuery->ShowListQueryL(textArray, iListObserver->iStatus, 4);
*        CleanupStack::PopAndDestroy(); // textArray
*
*   Example 2. Get and handle the result in active object.
*        void CMyActiveObject::RunL() 
*            {
*            TBuf<120> msg = _L("Received: ");
*            msg.AppendNum( iStatus.Int() );
*            iEnv->InfoMsg(msg);
*            Cancel();
*            }
*/
NONSHARABLE_CLASS(CAknGlobalListQuery) : public CBase
    {
    public:
        /**
        * Two-phased constructor.
        */
        IMPORT_C static CAknGlobalListQuery* NewL();

        /**
        * Two-phased constructor. Leaves the instance to cleanupstack
        */
        IMPORT_C static CAknGlobalListQuery* NewLC();

        /**
        * Destructor
        */
        IMPORT_C ~CAknGlobalListQuery();

        /**
        * Shows global list query synchronously.
        *
        * @param    aItems  Strings for items
        * @param    aStatus TRequestStatus which will be completed when user
        *                   selects one item from the list query.
        * @param    aIndex  Index which item in the list will be highlighted 
        */
        IMPORT_C void ShowListQueryL( 
            const MDesCArray* aItems,
            TRequestStatus& aStatus,
            const TInt aIndex = KGlobalListQueryDefaultIndex);

        /**
        * Move selection up.
        */
        IMPORT_C void MoveSelectionUp();

        /**
        * Move selection down.
        */
        IMPORT_C void MoveSelectionDown();

        /**
        * Select currently selected item in the list.
        */
        IMPORT_C void SelectItem();

        /**
        * Cancel the list query.
        */
        IMPORT_C void CancelListQuery();

        /**
        * Sets the heading for the query. In order to have effect, the heading must be set before 
        * calling ShowListQueryL.
        *
        * @param    aHeading  Heading string.
        * @since 2.1
        */
        IMPORT_C void SetHeadingL(const TDesC& aHeading);

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
        /**
        * Updates list query.
        */
        IMPORT_C void UpdateListQuery();

    private:
        /**
        * Default constructor.
        */
        CAknGlobalListQuery();

        /**
        * EPOC constructor.
        */
        void ConstructL(); 

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
    };

#endif // __AKNGLOBALLISTQUERY_H__
