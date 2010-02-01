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
* Description:     Implementation of TAiwGenericParam and CAiwGenericParamList.
*
*/





// INCLUDES
#include <s32mem.h>
#include "AiwGenericParam.h"

namespace {

// CONSTANTS
// Protect against possible data format changes
const TInt KVersion = 10;  // Version 1.0

enum TPanicCode
    {
    EPanicPostCond_CopyLC = 1,
    EPanicPostCond_AppendL,
    EPanicPostCond_Reset
    };


// ============================= LOCAL FUNCTIONS ===============================

#ifdef _DEBUG
void Panic(TPanicCode aCode)
    {
    _LIT(KPanicText, "GenericParam");
    User::Panic(KPanicText, aCode);
    }
#endif

}


const TInt KRFsSlot = 2;
const TInt KRFileSlot = 3;


// ============================ MEMBER FUNCTIONS ===============================

/**
 * Releases any dynamic data owned by this parameter.
 */
inline void TAiwGenericParam::Destroy()
    {
    iValue.Destroy();
    }

/**
 * Copies aParam to this parameter. Takes an own copy of the value held in 
 * aParam.
 */
void TAiwGenericParam::CopyLC(const TAiwGenericParam& aParam)
    {
    // Take a copy of value
    iValue.SetL(aParam.iValue);
    // Copy semantic id
    iSemanticId = aParam.iSemanticId;
    CleanupStack::PushL(*this);

    __ASSERT_DEBUG(*this==aParam, Panic(EPanicPostCond_CopyLC));
    }

/**
 * Returns a cleanup item that will call Destroy to this object when 
 * PopAndDestroy'ed.
 */
TAiwGenericParam::operator TCleanupItem()
    {
    return TCleanupItem(&CleanupDestroy,this);
    }

/**
 * Callback for operator TCleanupItem().
 */
void TAiwGenericParam::CleanupDestroy(TAny* aObj)
    {
    static_cast<TAiwGenericParam*>(aObj)->Destroy();
    }

/**
 * Internalizes this parameter from aStream.
 */
void TAiwGenericParam::InternalizeL(RReadStream& aStream)
    {
    /*const TInt version =*/ aStream.ReadInt8L();
    const TGenericParamId id = 
        static_cast<TGenericParamId>(aStream.ReadInt32L());
    iValue.InternalizeL(aStream);
    iSemanticId = id;
    }

/**
 * Externalizes this parameter to aStream.
 */
void TAiwGenericParam::ExternalizeL(RWriteStream& aStream) const
    {
    aStream.WriteInt8L(KVersion);
    aStream.WriteInt32L(iSemanticId);
    iValue.ExternalizeL(aStream);
    }

/**
 * Returns the maximum externalized size of this parameter.
 */
TInt TAiwGenericParam::Size() const
    {
    TInt size = sizeof (TInt8); // version
    size += sizeof (TInt32); // semantic ID
    size += iValue.Size();
    return size;
    }

EXPORT_C TBool operator==(const TAiwGenericParam& aLhs, 
    const TAiwGenericParam& aRhs)
    {
    return 
        ((aLhs.SemanticId() == aRhs.SemanticId()) && 
        (aLhs.Value() == aRhs.Value()));
    }


////////////////////////////////////////////////////////////
// CAiwGenericParamList

inline CAiwGenericParamList::CAiwGenericParamList()
    {
    }

EXPORT_C CAiwGenericParamList* CAiwGenericParamList::NewL()
    {
    CAiwGenericParamList *self = NewLC();
    CleanupStack::Pop();
    return self;
    }

EXPORT_C CAiwGenericParamList* CAiwGenericParamList::NewL(RReadStream& aReadStream)
    {
    CAiwGenericParamList *self = NewLC(aReadStream);
    CleanupStack::Pop();
    return self;
    }

EXPORT_C CAiwGenericParamList* CAiwGenericParamList::NewLC()
    {
    CAiwGenericParamList *self = new( ELeave ) CAiwGenericParamList();
    CleanupStack::PushL( self );
    return self;
    }

EXPORT_C CAiwGenericParamList* CAiwGenericParamList::NewLC(RReadStream& aReadStream)
    {
    CAiwGenericParamList *self = new( ELeave ) CAiwGenericParamList();
    CleanupStack::PushL( self );
    self->AppendL(aReadStream);
    return self;
    }

CAiwGenericParamList::~CAiwGenericParamList()
    {
    for (TInt i = iParameters.Count()-1; i >= 0; --i)
        {
        // Can use Destroy because the parameters cannot be accessed anymore
        iParameters[i].Destroy();
        }
    iParameters.Close();
    }

EXPORT_C TInt CAiwGenericParamList::Count() const
    {
    return iParameters.Count();
    }
    
EXPORT_C TInt CAiwGenericParamList::Count(TGenericParamId aSemanticId, 
    TVariantTypeId aDataType) const
    {
    TInt result = 0;
    const TInt count = iParameters.Count();

    for (TInt i = 0; i < count; i++)
        {
        const TAiwGenericParam& param = iParameters[i];
        if (param.SemanticId() == aSemanticId)
            {
            if (aDataType==EVariantTypeAny || param.Value().TypeId()==aDataType)
                {
                result++;                   
                }
            }
        }       
    return result;     
    }


EXPORT_C const TAiwGenericParam& CAiwGenericParamList::operator[](TInt aIndex) const
    {
    return iParameters[aIndex];
    }

EXPORT_C void CAiwGenericParamList::AppendL(const TAiwGenericParam& aParam)
    {
    TAiwGenericParam newParam;
    newParam.CopyLC(aParam);
    User::LeaveIfError(iParameters.Append(newParam));
    CleanupStack::Pop(&newParam);

    __ASSERT_DEBUG((*this)[Count()-1]==aParam, Panic(EPanicPostCond_AppendL));
    }


EXPORT_C TBool CAiwGenericParamList::Remove(TInt aSemanticId)
    {
    const TInt count = iParameters.Count();
    for (TInt i = 0; i < count; ++i)
        {
        const TAiwGenericParam& param = iParameters[i];
        if (param.SemanticId() == aSemanticId)
            {
            iParameters.Remove(i);
            return ETrue;
            }
        }

    return EFalse;
    }


EXPORT_C void CAiwGenericParamList::Reset()
    {
    for (TInt i = iParameters.Count()-1; i >= 0; --i)
        {
        // Can use Destroy because the parameters cannot be accessed anymore
        iParameters[i].Destroy();
        iParameters.Remove(i);
        }

    __ASSERT_DEBUG(Count()==0, Panic(EPanicPostCond_Reset));
    }

EXPORT_C const TAiwGenericParam* CAiwGenericParamList::FindFirst(
    TInt &aIndex, 
    TGenericParamId aSemanticId, 
    TVariantTypeId aDataType) const
    {
    if (aIndex >= 0)
        {
        const TInt count = iParameters.Count();
        for (TInt i = aIndex; i < count; ++i)
            {
            const TAiwGenericParam& param = iParameters[i];
            if (param.SemanticId() == aSemanticId)
                {
                if (aDataType==EVariantTypeAny || param.Value().TypeId()==aDataType)
                    {
                    aIndex = i;
                    return &param;
                    }
                }
            }
        }
    aIndex = KErrNotFound;
    return NULL;
    }

EXPORT_C const TAiwGenericParam* CAiwGenericParamList::FindNext(
    TInt &aIndex, 
    TGenericParamId aSemanticId,
    TVariantTypeId aDataType) const
    {
    if (aIndex < 0)
        {
        aIndex = KErrNotFound;
        return NULL;
        }

    TInt index = aIndex+1;
    const TAiwGenericParam* result = FindFirst(index, aSemanticId, aDataType);
    aIndex = index;
    return result;
    }

EXPORT_C void CAiwGenericParamList::ExternalizeL(RWriteStream& aStream) const
    {
    aStream.WriteInt8L(KVersion);
    const TInt count = iParameters.Count();
    aStream.WriteInt32L(count);
    for (TInt i = 0; i < count; ++i)
        {
        iParameters[i].ExternalizeL(aStream);
        }
    }

EXPORT_C TInt CAiwGenericParamList::Size() const
    {
    TInt size = sizeof (TInt8); // version
    size += sizeof (TInt32);  // param count
    const TInt count = iParameters.Count();
    for (TInt i = 0; i < count; ++i)
        {
        size += iParameters[i].Size();
        }
    return size;
    }

/**
 * Appends parameters to this list from aStream.
 */
void CAiwGenericParamList::AppendL(RReadStream& aReadStream)
    {
    /*const TInt version =*/ aReadStream.ReadInt8L();
    
    TInt count = aReadStream.ReadInt32L();
    while (count--)
        {
        TAiwGenericParam param;
        CleanupStack::PushL(param);
        param.InternalizeL(aReadStream);
        User::LeaveIfError(iParameters.Append(param));
        CleanupStack::Pop(&param);
        }
    }



EXPORT_C void CAiwGenericParamList::InternalizeL(RReadStream& aStream)
    {
    AppendL(aStream);
    }


EXPORT_C HBufC8* CAiwGenericParamList::PackForServerL(TIpcArgs& aArgs)
    {   
    TInt i;
    TInt rfileCount = 0;
    RFile fhandle;

    HBufC8* buf = HBufC8::NewLC(Size() + iParameters.Count());
    TPtr8 des = buf->Des();
    RDesWriteStream outstrm(des);    
    //outstrm.Open(des);
    CleanupClosePushL(outstrm);

    outstrm.WriteInt16L(iParameters.Count());   

    for (i = 0; i < iParameters.Count(); i++)
        {       
        if (iParameters[i].Value().TypeId() == EVariantTypeFileHandle)
            {
            if (rfileCount == 0)
                {
                outstrm.WriteInt8L(iParameters[i].Value().TypeId());
                outstrm.WriteInt32L(iParameters[i].SemanticId());
                if (iParameters[i].Value().Get(fhandle))
                    {
                    rfileCount++;
                    }
                }
            }
        else
            {
            outstrm.WriteInt8L(iParameters[i].Value().TypeId());
            iParameters[i].ExternalizeL( outstrm );
            }
        }
        
    outstrm.CommitL();  
    CleanupStack::PopAndDestroy(&outstrm);
                        
    aArgs.Set(0, buf);
    aArgs.Set(1, des.MaxLength());    
        
    if (rfileCount)
        {
        fhandle.TransferToServer(aArgs, KRFsSlot, KRFileSlot);      
        }   

    CleanupStack::Pop();    // buf

    return buf;
    }


EXPORT_C void CAiwGenericParamList::UnpackFromClientL(const RMessage2& aMsg)
    {
    TInt8 type;
    TInt i;
    TAiwGenericParam param; 
    TGenericParamId handleId = EGenericParamUnspecified;
    TInt numFileHandles = 0;

    HBufC8* buf = HBufC8::NewLC(aMsg.Int1());
    TPtr8 ptr(buf->Des());
    aMsg.ReadL(0, ptr);
    RDesReadStream instrm(buf->Des());

    const TInt16 count = instrm.ReadInt16L();
    for (i = 0; i < count; i++)
        {
        type = instrm.ReadInt8L();
        if (type == EVariantTypeFileHandle)
            {
            if (numFileHandles == 0)
                {
                handleId = (TGenericParamId)instrm.ReadInt32L();
                numFileHandles++;
                }
            }
        else
            {
            param.InternalizeL(instrm);
            AppendL(param);
            param.Reset();
            }
        }

    if (numFileHandles)
        {
        RFile file;
        file.AdoptFromClient(aMsg, KRFsSlot, KRFileSlot);
        TAiwVariant variant(file);
        AppendL(TAiwGenericParam(handleId, variant));               
        }
        
    CleanupStack::PopAndDestroy(); // buf       
    }
    

EXPORT_C void CAiwGenericParamList::AppendL(const CAiwGenericParamList& aList)
    {
    for (TInt i = 0; i < aList.iParameters.Count(); i++)
        {
        AppendL(aList.iParameters[i]);
        }
    }

// End of file
