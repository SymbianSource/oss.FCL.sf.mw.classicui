/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  This file contains classes of Peninput server client side.
*
*/


#ifndef C_BCRPENINPUTSERVEROBSERVER_H
#define C_BCRPENINPUTSERVEROBSERVER_H

class MPenUiActivationHandler;
class MPeninputServerEventHandler;
class RPeninputServer;

#include <ecom/ecom.h>

/**
 *  inherit from CHwrRecognizer, it's only for test protected api.
 */
class CBCTestDomHwrRecognizer : public CHwrRecognizer
    {
public:
    static CBCTestDomHwrRecognizer* NewL( TInt aImpId );
    
    /**
     * protected api
     */
    TBool IsSupportUdm();
    
    /**
     * protected api
     */
    void LoadUdmL( TUdmType aType );

    /**
     * protected api
     */
    void UnLoadUdmL( TUdmType aType );

    /**
     * protected api
     */
    void GetModelIndexListL( TUdmType aType, 
                             RArray<TInt>& aList, 
                             const THwrUdmRange& aRange );

    /**
     * protected api
     */
    void GetSymbolModelL( TUdmType aType, 
                          TInt aIndex, 
                          TPtrC& aSymbolName,
                          RArray<TPoint>& aModel, 
                          TInt& aHelpLine, TInt& aBaseLine );
                          
    };

/**
 *  inherit from CPtiCore, it's only for release memory.
 */
    
class CBCTestDomPtiCore: public CPtiCore
{
public:
    void Descecom( TInt dtorId )
    {
        REComSession::DestroyedImplementation(TUid::Uid(dtorId));
    }
    ~CBCTestDomPtiCore()
    {
        
    }
};    

#endif 


