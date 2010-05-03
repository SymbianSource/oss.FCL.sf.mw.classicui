/*
* Copyright (c) 2003-2005 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:     Implementation for common AIW classes to be used both
*                consumer and provider side.
*
*/




#include "AiwCommon.h"

const TInt KInitialMaxProviders = 0xff;


CAiwCriteriaItem::CAiwCriteriaItem()
    {
    }



EXPORT_C CAiwCriteriaItem* CAiwCriteriaItem::NewL()
    {
    CAiwCriteriaItem* item = new (ELeave) CAiwCriteriaItem();
    CleanupStack::PushL( item );
    item->ConstructL();
    CleanupStack::Pop(); // item
    return item;
    }



EXPORT_C CAiwCriteriaItem* CAiwCriteriaItem::NewLC()
    {
    CAiwCriteriaItem* item = new (ELeave) CAiwCriteriaItem();
    CleanupStack::PushL( item );
    item->ConstructL();
    return item;
    }



EXPORT_C CAiwCriteriaItem* CAiwCriteriaItem::NewL(
    TInt aCriteriaId,
    TInt aServiceCmd,
    const TDesC8& aContentType)
    {
    CAiwCriteriaItem* item = new (ELeave) CAiwCriteriaItem();
    CleanupStack::PushL( item );
    item->ConstructL(aCriteriaId, aServiceCmd, aContentType);
    CleanupStack::Pop(); // item
    return item;
    }



EXPORT_C CAiwCriteriaItem* CAiwCriteriaItem::NewLC(
    TInt aCriteriaId,
    TInt aServiceCmd,
    const TDesC8& aContentType)
    {
    CAiwCriteriaItem* item = new (ELeave) CAiwCriteriaItem();
    CleanupStack::PushL( item );
    item->ConstructL(aCriteriaId, aServiceCmd, aContentType);
    return item;    
    }



EXPORT_C CAiwCriteriaItem::~CAiwCriteriaItem()
    {
    delete iContentType;
    }



void CAiwCriteriaItem::ConstructL()
    {
    iMaxProviders = KInitialMaxProviders;
    iOptions.Set(TInt32(0));
    }



void CAiwCriteriaItem::ConstructL(TInt aCriteriaId, TInt aServiceCmd,
    const TDesC8& aContentType)
    {
    iMaxProviders = KInitialMaxProviders;
    iOptions.Set(TInt32(0));
    iCriteriaId = aCriteriaId;
    iServiceCmd = aServiceCmd;
    SetContentTypeL( aContentType );
    }



EXPORT_C void CAiwCriteriaItem::SetId(TInt aId)
    {
    iCriteriaId = aId;      
    }



EXPORT_C void CAiwCriteriaItem::SetServiceClass(const TUid& aServiceUid)
    {
    iServiceClass = aServiceUid;
    }
    


EXPORT_C void CAiwCriteriaItem::SetServiceCmd(TInt aServiceCmd)
    {
    iServiceCmd = aServiceCmd;
    }



EXPORT_C void CAiwCriteriaItem::SetContentTypeL(const TDesC8& aContentType)
    {
    delete iContentType;
    iContentType = NULL;
    iContentType = HBufC8::NewL(aContentType.Length());
    TPtr8 content(iContentType->Des());
    content.SetLength(aContentType.Length());
    content.Copy(aContentType);
    }



EXPORT_C TInt CAiwCriteriaItem::Id() const
    {
    return iCriteriaId;
    }



EXPORT_C const TUid& CAiwCriteriaItem::ServiceClass() const
    {
    return iServiceClass;
    }
    


EXPORT_C TInt CAiwCriteriaItem::ServiceCmd() const
    {   
    return iServiceCmd;
    }



EXPORT_C const TDesC8& CAiwCriteriaItem::ContentType() const
    {
    if (iContentType)
        {
        return *iContentType;
        }

    return KNullDesC8();
    }



EXPORT_C void CAiwCriteriaItem::SetOptions(TUint aOptions)
    {
    iOptions.Set(aOptions);
    }



EXPORT_C TUint CAiwCriteriaItem::Options() const
    {
    TInt32 ret = 0;
    iOptions.Get( ret );
    return ret; 
    }



EXPORT_C void CAiwCriteriaItem::ReadFromResoureL(TResourceReader& aReader)
    {
    delete iContentType;
    iContentType = NULL;
    
    iCriteriaId = aReader.ReadInt32();
    iServiceCmd = aReader.ReadInt32();

    TPtrC8 txtptr = aReader.ReadTPtrC8();
    iContentType = HBufC8::NewL(txtptr.Length());
    TPtr8 content(iContentType->Des());
    content.Copy( txtptr );

    iServiceClass = TUid::Uid(aReader.ReadInt32());

    iDefaultProvider = TUid::Uid(aReader.ReadInt32());

    iMaxProviders = aReader.ReadUint8();
    
    iOptions = aReader.ReadUint8();
    aReader.ReadInt32(); // Skip over reserved field.
    }



EXPORT_C TUid CAiwCriteriaItem::DefaultProvider() const
    {
    return iDefaultProvider;
    }



EXPORT_C void CAiwCriteriaItem::SetDefaultProvider(TInt aDefault)
    {
    iDefaultProvider = TUid::Uid(aDefault);
    }   


EXPORT_C TInt CAiwCriteriaItem::MaxProviders() const
    {
    return iMaxProviders;
    }


EXPORT_C void CAiwCriteriaItem::SetMaxProviders(TInt aMaxProviders)
    {
    iMaxProviders = aMaxProviders;
    }


EXPORT_C TBool CAiwCriteriaItem::operator==(const CAiwCriteriaItem& aItem)
    {
    return ((iCriteriaId                                  == aItem.iCriteriaId)           &&
            (iServiceCmd                                  == aItem.iServiceCmd)           &&
            (ContentType().Compare(aItem.ContentType())   == KErrNone)                    &&
            (iServiceClass.iUid                           == aItem.iServiceClass.iUid)    &&
            (iDefaultProvider.iUid                        == aItem.iDefaultProvider.iUid) &&
            (iMaxProviders                                == aItem.iMaxProviders)         &&
            (iOptions                                     == aItem.iOptions));       
    }

// End of file
