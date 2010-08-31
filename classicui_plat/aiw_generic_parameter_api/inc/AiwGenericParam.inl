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
* Description:     Inline function implementations of class TAiwGenericParam.
*
*/





inline TAiwGenericParam::TAiwGenericParam() :
    iSemanticId(EGenericParamUnspecified), iValue()
    {
    }

inline TAiwGenericParam::TAiwGenericParam(TGenericParamId aSemanticId) :
    iSemanticId(aSemanticId), iValue()
    {
    }

inline TAiwGenericParam::TAiwGenericParam(TGenericParamId aSemanticId, 
    const TAiwVariant& aValue) : 
    iSemanticId(aSemanticId), iValue(aValue)
    {
    }

inline void TAiwGenericParam::SetSemanticId(TGenericParamId aSemanticId)
    {
    iSemanticId = aSemanticId;
    }

inline TGenericParamId TAiwGenericParam::SemanticId() const
    {
    return iSemanticId;
    }

inline TAiwVariant& TAiwGenericParam::Value()
    {
    return iValue;
    }

inline const TAiwVariant& TAiwGenericParam::Value() const
    {
    return iValue;
    }

inline void TAiwGenericParam::Reset()
    {
    iSemanticId = EGenericParamUnspecified;
    iValue.Reset();
    }

inline TBool operator!=(const TAiwGenericParam& aLhs, 
    const TAiwGenericParam& aRhs)
    {
    return !(aLhs == aRhs);
    }

// End of file

