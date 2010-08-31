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
* Description:  ?Description
*
*/

#ifndef C_TESTSDKSFASTOBSERVER_H
#define C_TESTSDKSFASTOBSERVER_H

#include <e32base.h>
#include <aknsfld.h>

class CTestSDKSFASTObserver : public CBase, public MAdaptiveSearchTextObserver
{
public:
    virtual ~CTestSDKSFASTObserver();
    CTestSDKSFASTObserver();
    //from MAdaptiveSearchTextObserver
public: 
   /** 
    * Notification and handling of an adaptive search text change. 
    * 
    * @param aSearchField The source search field of this message. 
    */ 
    virtual void AdaptiveSearchTextChanged( CAknSearchField* aSearchField ); 
};

#endif /*C_TESTSDKSFASTOBSERVER_H*/
