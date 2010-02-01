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
* Description:     Implementation of class TAiwVariant.
*
*/





// INCLUDES
#ifdef _DEBUG
#include <e32svr.h>
#endif
#include "AiwVariant.h"


// ============================= LOCAL FUNCTIONS ===============================

namespace {

// CONSTANTS
/// TAiwVariant streaming version
const TInt KVersion = 10;  // Version 1.0

// Debug helpers
#ifdef _DEBUG

enum TPanicCode
    {
    EPanicPostCond_Constructor = 1,
    EPanicPostCond_Reset,
    EPanicPostCond_Set_TInt32,
    EPanicPostCond_Set_TUid,
    EPanicPostCond_Set_TTime,
    EPanicPostCond_Set_TDesC,
    EPanicPostCond_CopyL,
    EPanicInvariant_InvalidDesCState,
    EPanicPostCond_Set_TDesC8,
    EPanicPreCond_DataSizeMismatch
    };

void Panic(TPanicCode aCode)
    {
    _LIT(KPanicText, "TAiwVariant");
    User::Panic(KPanicText, aCode);
    }

#endif  // #ifdef _DEBUG

}  // namespace
 

// ============================ MEMBER FUNCTIONS ===============================

#ifdef _DEBUG
void TAiwVariant::__DbgTestInvariant() const
    {
    if (iTypeId==EVariantTypeDesC && iData.iBufC)
        {
        __ASSERT_ALWAYS(iData.iBufC->Ptr() == iPtrC.Ptr(), 
            Panic(EPanicInvariant_InvalidDesCState));
        
        }
    }
#endif  // #ifdef _DEBUG

inline void TAiwVariant::SInt64::InternalizeL(RReadStream& aStream)
    {
    TInt32 low = aStream.ReadInt32L();
    iHigh = aStream.ReadInt32L();
    iLow = low;
    }

inline void TAiwVariant::SInt64::ExternalizeL(RWriteStream& aStream) const
    {
    aStream.WriteInt32L(iLow);
    aStream.WriteInt32L(iHigh);
    }

inline void TAiwVariant::SInt64::Set(const TInt64& aTInt64)
    {
    iLow = I64LOW(aTInt64);
    iHigh = I64HIGH(aTInt64);
    }

inline TAiwVariant::SInt64::operator TInt64() const
    {
    return MAKE_TINT64(iHigh,iLow);
    }

inline TBool TAiwVariant::SInt64::operator==(const SInt64& aRhs) const
    {
    return (iHigh==aRhs.iHigh && iLow==aRhs.iLow);
    }


EXPORT_C TAiwVariant::TAiwVariant(const TAiwVariant& aSrc) :
    iTypeId(aSrc.iTypeId), iData(aSrc.iData), iPtrC(), iPtrC8()
    {
    if (iTypeId == EVariantTypeDesC)
        {
        iPtrC.Set(aSrc.iPtrC);
        // Do not take ownership of data
        iData.iBufC = NULL;
        }
    else if ( iTypeId == EVariantTypeDesC8 )
        {
        iPtrC8.Set( aSrc.iPtrC8 );
        // Do not take ownership of data
        iData.iBufC8 = NULL;
        }
    }

EXPORT_C TAiwVariant& TAiwVariant::operator=(const TAiwVariant& aSrc)
    {
    // Check self-assignment first.
    if (this == &aSrc)
        {
        return *this;
        }
    
    iTypeId = aSrc.iTypeId;
    iData = aSrc.iData;
    if (iTypeId == EVariantTypeDesC)
        {
        iPtrC.Set(aSrc.iPtrC);
        // Do not take ownership of data
        iData.iBufC = NULL;
        }
    else if ( iTypeId == EVariantTypeDesC8 )
        {
        iPtrC8.Set( aSrc.iPtrC8 );
        // Do not take ownership of data
        iData.iBufC8 = NULL;
        }
    return *this;
    }

EXPORT_C TBool TAiwVariant::Get(TInt32& aValue) const
    {
    __TEST_INVARIANT;
    if (iTypeId == EVariantTypeTInt32)
        {
        aValue = iData.iInt32;
        return ETrue;
        }
    return EFalse;
    }

EXPORT_C TBool TAiwVariant::Get(TUid& aValue) const
    {
    __TEST_INVARIANT;
    if (iTypeId == EVariantTypeTUid)
        {
        aValue = TUid::Uid(iData.iInt32);
        return ETrue;
        }
    return EFalse;
    }

EXPORT_C TBool TAiwVariant::Get(TPtrC& aValue) const
    {
    __TEST_INVARIANT;
    if (iTypeId == EVariantTypeDesC)
        {
        aValue.Set(iPtrC);
        return ETrue;
        }
    return EFalse;
    }

EXPORT_C TBool TAiwVariant::Get(TTime& aValue) const
    {
    __TEST_INVARIANT;
    if (iTypeId == EVariantTypeTTime)
        {
        aValue = TTime(iData.iInt64);
        return ETrue;
        }
    return EFalse;
    }


EXPORT_C TBool TAiwVariant::Get(TPtrC8& aValue) const
    {
     __TEST_INVARIANT;  
    if (iTypeId == EVariantTypeDesC8)
        {
        aValue.Set(iPtrC8);
        return ETrue;
        }   

    return EFalse;
    }


EXPORT_C TBool TAiwVariant::Get(RFile& aValue) const
    {
    __TEST_INVARIANT;
    if (iTypeId == EVariantTypeFileHandle)
        {
        aValue = *((RFile*)&iData.iInt64);      
        return ETrue;
        }

    return EFalse;
    }


EXPORT_C TInt32 TAiwVariant::AsTInt32() const
    {
    TInt32 value = 0;
    Get(value);
    return value;
    }   

EXPORT_C TUid TAiwVariant::AsTUid() const
    {
    __TEST_INVARIANT;
    TUid value = {0};
    Get(value);
    return value;
    }

EXPORT_C TPtrC TAiwVariant::AsDes() const
    {
    __TEST_INVARIANT;
    TPtrC value;
    Get(value);
    return value;
    }

EXPORT_C TTime TAiwVariant::AsTTime() const
    {
    __TEST_INVARIANT;
    TTime value(Time::NullTTime());
    Get(value);
    return value;
    }


EXPORT_C TPtrC8 TAiwVariant::AsData() const
    {
     __TEST_INVARIANT;
    TPtrC8 value;
    Get(value);
    return value;
    }


EXPORT_C RFile TAiwVariant::AsFileHandle() const
    {
    __TEST_INVARIANT;
    RFile value;
    Get(value);
    return value;
    }


EXPORT_C void TAiwVariant::Reset()
    {
    __TEST_INVARIANT;

    if (iTypeId == EVariantTypeDesC)
        {
        // Delete any owned buffer
        delete iData.iBufC;
        iData.iBufC = NULL;
        }
    else if (iTypeId == EVariantTypeDesC8)
        {
        delete iData.iBufC8;
        iData.iBufC8 = NULL;
        }       
    // No need to clear other data, because Get methods wont't do anything if type
    // is Null.
    iTypeId = EVariantTypeNull;

    __ASSERT_DEBUG(IsEmpty(), Panic(EPanicPostCond_Reset));
    __TEST_INVARIANT;
    }

EXPORT_C void TAiwVariant::Set(TInt32 aValue)
    {
    __TEST_INVARIANT;
    
    Reset();
    iTypeId = EVariantTypeTInt32;
    iData.iInt32 = aValue;
    
    __ASSERT_DEBUG(this->AsTInt32()==aValue, Panic(EPanicPostCond_Set_TInt32));
    __TEST_INVARIANT;
    }

EXPORT_C void TAiwVariant::Set(const TUid& aValue)
    {
    __TEST_INVARIANT;
    
    Reset();
    iTypeId = EVariantTypeTUid;
    iData.iInt32 = aValue.iUid;
    
    __ASSERT_DEBUG(this->AsTUid()==aValue, Panic(EPanicPostCond_Set_TUid));
    __TEST_INVARIANT;
    }

EXPORT_C void TAiwVariant::Set(const TTime& aValue)
    {
    __TEST_INVARIANT;
    
    Reset();
    iTypeId = EVariantTypeTTime;
    iData.iInt64.Set(aValue.Int64());
    
    __ASSERT_DEBUG(this->AsTTime()==aValue, Panic(EPanicPostCond_Set_TTime));
    __TEST_INVARIANT;
    }

EXPORT_C void TAiwVariant::Set(const TDesC& aValue)
    {
    __TEST_INVARIANT;

    Reset();
    iTypeId = EVariantTypeDesC;
    iData.iBufC = NULL;  // not owned
    iPtrC.Set(aValue);

    __ASSERT_DEBUG(this->AsDes()==aValue, Panic(EPanicPostCond_Set_TDesC));
    __TEST_INVARIANT;
    }



EXPORT_C void TAiwVariant::Set(const TDesC8& aValue)
    {
   __TEST_INVARIANT;

    Reset();
    iTypeId = EVariantTypeDesC8;
    iData.iBufC8 = NULL;  // not owned
    iPtrC8.Set(aValue);

    __ASSERT_DEBUG(this->AsData()==aValue, Panic(EPanicPostCond_Set_TDesC));
    __TEST_INVARIANT;
    }



EXPORT_C void TAiwVariant::Set(const RFile& aValue)
    {
    __TEST_INVARIANT;
    __ASSERT_DEBUG(sizeof(SInt64) == sizeof(RFile), Panic(EPanicPreCond_DataSizeMismatch));

    Reset();
    iTypeId = EVariantTypeFileHandle;
    *((RFile*)&iData.iInt64) = aValue;

    __TEST_INVARIANT;
    }

    
void TAiwVariant::SetL(const TAiwVariant& aValue)
    {
    __TEST_INVARIANT;

    if (aValue.iTypeId == EVariantTypeDesC)
        {
        // Take an own copy of the string value
        HBufC* buf = aValue.iPtrC.AllocL();
        Reset();
        iTypeId = EVariantTypeDesC;
        iData.iBufC = buf;
        iPtrC.Set(*iData.iBufC);
        }
    else if (aValue.iTypeId == EVariantTypeDesC8)
        {
        // Take an own copy of the data
        HBufC8* buf = aValue.iPtrC8.AllocL();
        Reset();
        iTypeId = EVariantTypeDesC8;
        iData.iBufC8 = buf;
        iPtrC8.Set(*iData.iBufC8);
        }
    else
        {
        Reset();
        iTypeId = aValue.iTypeId;
        // Copy the data union as one block
        iData = aValue.iData;
        }

    __ASSERT_DEBUG(*this == aValue, Panic(EPanicPostCond_CopyL));
    __TEST_INVARIANT;
    }

void TAiwVariant::Destroy()
    {
    __TEST_INVARIANT;

    if (iTypeId == EVariantTypeDesC)
        {
        // Delete any owned buffer
        delete iData.iBufC;
        iData.iBufC = NULL;
        }
    else if (iTypeId == EVariantTypeDesC8)
        {
        delete iData.iBufC8;
        iData.iBufC8 = NULL;
        }
    }

void TAiwVariant::InternalizeL(RReadStream& aStream)
    {
    __TEST_INVARIANT;
        
    aStream.ReadInt8L(); // version
    // if older version adapt to changes (who knows if
    // parameters would be also persistent...)

    const TUint8 typeId = aStream.ReadUint8L();
    switch (typeId)
        {
        case EVariantTypeNull:
            {
            Reset();
            break;
            }
        case EVariantTypeTInt32:  // FALLTHROUGH
        case EVariantTypeTUid:
            {
            TInt32 value = aStream.ReadInt32L();
            Reset();
            iTypeId = typeId;
            iData.iInt32 = value;
            break;
            }
        case EVariantTypeFileHandle: // FALLTHROUGH
        case EVariantTypeTTime:
            {
            SInt64 value;
            value.InternalizeL(aStream);
            Reset();
            iTypeId = typeId;
            iData.iInt64 = value;
            break;
            }
        case EVariantTypeDesC:
            {
            const TInt len = aStream.ReadInt32L();
            HBufC* buf = HBufC::NewL(aStream,len);
            Reset();
            iTypeId = typeId;
            iData.iBufC = buf;
            iPtrC.Set(*iData.iBufC);
            break;
            }
        case EVariantTypeDesC8:
            {
            const TInt len = aStream.ReadInt32L();
            HBufC8* buf = HBufC8::NewL(aStream,len);
            Reset();
            iTypeId = typeId;
            iData.iBufC8 = buf;
            iPtrC8.Set(*iData.iBufC8);
            break;
            }
        default:
            {
             // Corrupted data stream.
#ifdef _DEBUG
            RDebug::Print(_L("***ERROR TAiwVariant::InternalizeL"));
#endif
            User::Leave(KErrCorrupt);
            return;
            }
        }

    __TEST_INVARIANT;
    }
    
void TAiwVariant::ExternalizeL(RWriteStream& aStream) const
    {
    __TEST_INVARIANT;

    aStream.WriteInt8L(KVersion);
    // if older version adapt to changes (who knows if parameters would be also persistent...)

    aStream.WriteUint8L(iTypeId);
    switch (iTypeId)
        {
        case EVariantTypeTInt32: // FALLTHROUGH
        case EVariantTypeTUid:
            {
            aStream.WriteInt32L(iData.iInt32);
            break;
            }
        case EVariantTypeFileHandle: // FALLTHROUGH
        case EVariantTypeTTime:
            {
            iData.iInt64.ExternalizeL(aStream);
            break;
            }
        case EVariantTypeDesC:
            {
            aStream.WriteInt32L(iPtrC.Length());
            aStream << iPtrC;
            break;
            }
        case EVariantTypeDesC8:
            {
            aStream.WriteInt32L(iPtrC8.Length());
            aStream << iPtrC8;
            break;
            }
        default:
            break;
        }

    __TEST_INVARIANT;
    }

TInt TAiwVariant::Size() const
    {
    __TEST_INVARIANT;

    TInt size = sizeof (TInt8); // version
    size += sizeof (TUint8);    // iTypeId
    switch (iTypeId)
        {
        case EVariantTypeTInt32:    // FALLTHROUGH
        case EVariantTypeTUid:
            {
            size += sizeof (TInt32);
            break;
            }
        case EVariantTypeFileHandle: // FALLTHROUGH
        case EVariantTypeTTime:
            {
            size += sizeof (TInt64);
            break;
            }
        case EVariantTypeDesC:
            {
            size += sizeof (TInt32); // length
            size += iPtrC.Size();
            break;
            }
        case EVariantTypeDesC8:
            {
            size += sizeof (TInt32); // length
            size += iPtrC8.Size();
            break;
            }
        default:
            break;
        }
    return size;
    }

// ============================ EXTERNAL FUNCTIONS ===============================

EXPORT_C TBool operator==(const TAiwVariant& aLhs, const TAiwVariant& aRhs)
    {
    if (aLhs.iTypeId == aRhs.iTypeId)
        {
        switch (aLhs.iTypeId)
            {
            case EVariantTypeNull:
                {
                // Null equals Null
                return ETrue;
                }
            case EVariantTypeTInt32:  // FALLTHROUGH
            case EVariantTypeTUid:
                {
                return (aLhs.iData.iInt32 == aRhs.iData.iInt32);
                }
            case EVariantTypeDesC:
                {
                return (aLhs.iPtrC == aRhs.iPtrC);
                }
            case EVariantTypeDesC8:
                {
                return (aLhs.iPtrC8 == aRhs.iPtrC8);
                }
            case EVariantTypeFileHandle: // FALLTHROUGH
            case EVariantTypeTTime:
                {
                return (aLhs.iData.iInt64 == aRhs.iData.iInt64);
                }
            default:
                {
                break;
                }
            }
        }
    return EFalse;
    }

#ifdef _DEBUG

void Dump(const TAiwVariant& aVariant)
    {
    switch (aVariant.TypeId())
        {
        case EVariantTypeNull:
            {
            RDebug::Print(_L("   TAiwVariant::Dump = Null"));
            break;
            }
        case EVariantTypeTInt32:
            {
            RDebug::Print(_L("   TAiwVariant::Dump(TInt32) = %d"), aVariant.AsTInt32());
            break;
            }
        case EVariantTypeTUid:
            {
            const TUidName& uidName = aVariant.AsTUid().Name();
            RDebug::Print(_L("   TAiwVariant::Dump(TUid) = %S"), &uidName);
            break;
            }
        case EVariantTypeDesC:
            {
            TPtrC des = aVariant.AsDes();
            RDebug::Print(_L("   TAiwVariant::Dump(TBufC) = %S"), &des);
            break;
            }
        case EVariantTypeDesC8:
            {
            TPtrC8 des = aVariant.AsData();
            RDebug::Print(_L("   TAiwVariant::Dump(TBufC8) = %S"), &des);
            break;
            }
        case EVariantTypeTTime:
            {
            TDateTime dt = aVariant.AsTTime().DateTime();
            RDebug::Print(_L("   TAiwVariant::Dump(TTime): day=%d,mon=%d,year=%d,hh=%d,mm=%d,ss=%d"),
                          dt.Day()+1, dt.Month()+1, dt.Year(),
                          dt.Hour(),dt.Minute(), dt.Second());
            break;          
            }
        case EVariantTypeFileHandle:
            {
            RDebug::Print(_L("   TAiwVariant::Dump(RFile): Value is file handle."));
            break;
            }            
        default:
            {
            RDebug::Print(_L("  *** TAiwVariant::Dump(Unknown) ***"));
            break;
            }
        }
    }

#endif // ifdef _DEBUG
