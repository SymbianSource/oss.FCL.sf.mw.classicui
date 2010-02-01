/*
* Copyright (c) 2002-2005 Nokia Corporation and/or its subsidiary(-ies).
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


#ifndef __GENERIC_PARAM_CONSUMER_H__
#define __GENERIC_PARAM_CONSUMER_H__

// INCLUDES
#include <AknDoc.h>

// FORWARD DECLARATIONS
class CAiwGenericParamList;
class CStreamStore;
class CStreamDictionary;

// ---------------------------------------------------------
// @since Series60 3.0
// ---------------------------------------------------------
//
class CAiwGenericParamConsumer : public CAknDocument
{
public:
    IMPORT_C virtual void RestoreL(const CStreamStore& aStore, const CStreamDictionary& aStreamDic);
    IMPORT_C ~CAiwGenericParamConsumer();

protected:
    IMPORT_C CAiwGenericParamConsumer(CEikApplication& aApp);
    inline const CAiwGenericParamList* GetInputParameters() const;
    IMPORT_C void SetOutputParamsL(const CAiwGenericParamList* aList);

private:
    CAiwGenericParamList* iParams;
    CStreamStore* iStore;
    CStreamDictionary* iStreamDic;
};


inline const CAiwGenericParamList* CAiwGenericParamConsumer::GetInputParameters() const
{
    return iParams;
}


#endif      // __GENERIC_PARAM_CONSUMER_H__
            
// End of File
