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
* Description:  Test navigation_pane_api
*
*/


#ifndef C_TESTSDKNAVIPANENAVIDEEXT_H
#define C_TESTSDKNAVIPANENAVIDEEXT_H

// INCLUDES
#include <aknnavidecoratorobserver.h>
#include <aknnavide.h>

// CLASS DECLARATION


/**
 * Observer class for CAknNaviDecorator
 */
class CTestSDKNaviDecoratorObserver: public CBase, public MAknNaviDecoratorObserver
    {
public:
    // from MAknNaviDecoratorObserver
    virtual void HandleNaviDecoratorEventL( TInt aEventId );
    
    };

class CTestSDKNavipaneNaviDeExt: public CAknNavigationDecorator
    {
    friend class CTestSDKNaviPane;
    };
#endif // C_TESTSDKNAVIPANENAVIDEEXT_H
