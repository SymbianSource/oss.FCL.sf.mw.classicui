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

class MPeninputServerEventHandler;
class RPeninputServer;

#include <pticore.h>
#include <ptihwrrecognizer.h>
#include <peninputsrveventhandler.h>

/**
 *  inherit from pure virtual class MPenUiActivationHandler, 
 *  it's for test RPeninputServer
 */
class CMPenUiA : public CBase,public MPenUiActivationHandler
    {
public:

    /**
     * Constructor
     */
    CMPenUiA();

    /**
     * implement pure virtual function. 
     */
    void OnPeninputUiDeactivated();

    /**
     * implement pure virtual function. 
     */
    void OnPeninputUiActivated();
    
    };

/**
 *  inherit from pure virtual class MPeninputServerEventHandler,
 *  it's for test RPeninputServer
 */
class CPenUiNotificationHandler: public CBase,public MPeninputServerEventHandler
    {
public:

    /**
     * create object. 
     * @param aHandler, MPenUiActivationHandler
     * @param aClient, RPeninputServer
     * @return Pointer to created CPenUiNotificationHandler class object.
    */
    static CPenUiNotificationHandler* NewL( MPenUiActivationHandler* aHandler,
                                            RPeninputServer* aClient );

    /**
     * implement pure virtual function. 
     * @param aEventId, a EventId
     * @return handle event state.
     */
    TBool HandleServerEventL( TInt aEventId );

private:

    /**
     * Constructor
     */
    CPenUiNotificationHandler( MPenUiActivationHandler* aHandler, RPeninputServer* aClient );

    /**
     * 2nd ctor
     */
    void ConstructL();

    MPenUiActivationHandler* iHandler;        

    RPeninputServer* iClient;
    };
    
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


