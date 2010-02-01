/*
* Copyright (c) 2005-2007 Nokia Corporation and/or its subsidiary(-ies).
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

#ifndef __AKNSDDATA_H__
#define __AKNSDDATA_H__

// INCLUDES
#include <e32base.h>
#include <s32strm.h>

// CLASS DECLARATION

NONSHARABLE_CLASS(CAknSDData): public CBase
    {
public:
    /**
    * @since S60 3.1
    * Creates an encapsulation for additional data to be sent to secondary display when an 
    * avkon notifier becomes visible. 
    * @internal to S60
    *
    * @param aCategory A category which is used when publishing the notifier dialog, usually 
    *                  app uid.
    * @param aDialogIndex An index which makes it possible to distinguish different dialogs
    *                     wihin category
    * @param aAdditionalData Possible additional data to be sent to cover ui (as such).
    */      
    static CAknSDData* NewL(TUid aCategory, TInt aDialogIndex, const TDesC8& aAdditionalData)
        {
        CAknSDData* me = new (ELeave) CAknSDData(aCategory, aDialogIndex);
        if (aAdditionalData.Length())
            {
            CleanupStack::PushL(me);
            me->iAdditionalData = aAdditionalData.AllocL();
            CleanupStack::Pop();
            }
        return me;    
        }
    
    ~CAknSDData()
        {
        delete iAdditionalData;
        }
    
    // --- internal to avkon ---
    CAknSDData(){} // used when extracting data from stream
    CAknSDData(TUid aCategory, TInt aDialogIndex):iCategory(aCategory),iDialogIdx(aDialogIndex){}

    IMPORT_C void ExternalizeL(RWriteStream& aStream) const;        
    IMPORT_C void InternalizeL(RReadStream& aStream);
    IMPORT_C void InsertGlobalListQueryItemIdsL(RArray<TInt>& aIdArray);
        
    HBufC8* iAdditionalData;
    TUid iCategory;
    TInt iDialogIdx;
    };

#endif // __AKNSDDATA_H__
