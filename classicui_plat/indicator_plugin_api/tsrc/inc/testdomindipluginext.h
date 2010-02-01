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
* Description:  test aknindicatorplugin.h
*
*/



#ifndef C_TESTDOMINDIPLUGINEXT_H
#define C_TESTDOMINDIPLUGINEXT_H


#include <aknindicatorplugin.h>

class CAknIndicatorPluginExt : public CAknIndicatorPlugin
    {
public:

    /**
    * Implements tap actions for the indicator in question (@c aUid).
    *
    * @param  aUid  UID of the indicator.
    */
    virtual void HandleIndicatorTapL( const TInt aUid );

    };


#endif // C_TESTDOMINDIPLUGINEXT_H
