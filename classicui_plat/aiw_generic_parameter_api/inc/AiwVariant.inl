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
* Description:     Inline function implementations of class TAiwVariant.
*
*/






inline TAiwVariant::TAiwVariant() : iTypeId(EVariantTypeNull), iPtrC(), iPtrC8()
    {
    iData.iBufC = NULL;
    iData.iBufC8 = NULL;
    Reset();
    }

inline TAiwVariant::TAiwVariant(TInt32 aValue) : iTypeId(EVariantTypeNull), iPtrC(), iPtrC8()
    {   
    Set(aValue);
    }

inline TAiwVariant::TAiwVariant(const TUid& aValue) : iTypeId(EVariantTypeNull), iPtrC(), iPtrC8()
    {
    Set(aValue);
    }

inline TAiwVariant::TAiwVariant(const TDesC& aValue) : iTypeId(EVariantTypeNull), iPtrC(), iPtrC8()
    {
    iData.iBufC = NULL;
    Set(aValue);
    }

inline TAiwVariant::TAiwVariant(const HBufC* aValue) : iTypeId(EVariantTypeNull), iPtrC(), iPtrC8()
    {
    iData.iBufC = NULL;
    if(aValue)
        Set(*aValue);
    else
        Reset();    
    }

inline TAiwVariant::TAiwVariant(const TTime& aValue) : iTypeId(EVariantTypeNull), iPtrC(), iPtrC8()
    {
    Set(aValue);
    }

inline TAiwVariant::TAiwVariant(const TDesC8& aValue) : iTypeId(EVariantTypeNull), iPtrC(), iPtrC8()
    {
    iData.iBufC8 = NULL;
    Set(aValue);
    }


inline TAiwVariant::TAiwVariant(const RFile& aValue) : iTypeId(EVariantTypeNull), iPtrC(), iPtrC8()
    {
    Set(aValue);
    }


inline TVariantTypeId TAiwVariant::TypeId() const
    {
    return static_cast<TVariantTypeId>(iTypeId);
    }

inline TBool TAiwVariant::IsEmpty() const
    {
    return (iTypeId == EVariantTypeNull);
    }

inline void TAiwVariant::Set(const HBufC* aValue)
    {
    Set(*aValue);
    }

inline TAiwVariant& TAiwVariant::operator=(TInt32 aValue)
    {
    Set(aValue);
    return *this;
    }

inline TAiwVariant& TAiwVariant::operator=(const TUid& aValue)
    {
    Set(aValue);
    return *this;
    }

inline TAiwVariant& TAiwVariant::operator=(const TDesC& aValue)
    {
    Set(aValue);
    return *this;
    }

inline TAiwVariant& TAiwVariant::operator=(const HBufC* aValue)
    {
    Set(*aValue);
    return *this;
    }

inline TAiwVariant& TAiwVariant::operator=(const TTime& aValue)
    {
    Set(aValue);
    return *this;
    }


inline TAiwVariant& TAiwVariant::operator=(const TDesC8& aValue)
    {
    Set(aValue);    
    return *this;
    }


inline TAiwVariant& TAiwVariant::operator=(const RFile& aValue)
    {
    Set(aValue);
    return *this;
    }


inline TBool operator!=(const TAiwVariant& aLhs, const TAiwVariant& aRhs)
    {
    return !(aLhs == aRhs);
    }

// End of file
