/*
* Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  test genericparamconsumer.h
*
*/



#ifndef C_TESTDOMGENPARAMEXT_H
#define C_TESTDOMGENPARAMEXT_H


#include <genericparamconsumer.h>

class CAiwGenericParamConsumerExt : public CAiwGenericParamConsumer
    {
public:

    /**
     * default constructor
     */
    CAiwGenericParamConsumerExt( CEikApplication& aApp );

    /**
     * CreateAppUiL
     */
    CEikAppUi* CreateAppUiL();

public: // from base class

    /**
     * GetInputParameters
     */
    const CAiwGenericParamList* DoGetInputParameters() const;

    /**
     * SetOutputParamsL
     */
    void DoSetOutputParamsL( const CAiwGenericParamList* aList );

    };

#endif // C_TESTDOMGENPARAMEXT_H
