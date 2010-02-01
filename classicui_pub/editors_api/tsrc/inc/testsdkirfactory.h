/*
* Copyright (c) 2002 - 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Test EIKEDWIN.h
 *
*/


#ifndef C_TESTSDKIRFACTORY_H
#define C_TESTSDKIRFACTORY_H

#include <eikirfty.h>
#include <eikedwin.h>

class TTestSDKIrFactory : public MEikIrFactory
    {
public:
    
    /**
     * from MEikIrFactory
     */
    void SendDataOverIrL( CEikEdwin* aEditor );
    
    /**
     * from MEikIrFactory
     */
    void ReceiveDataOverIrL( CEikEdwin* aEditor );
    };

#endif /*C_TESTSDKIRFACTORY_H*/
