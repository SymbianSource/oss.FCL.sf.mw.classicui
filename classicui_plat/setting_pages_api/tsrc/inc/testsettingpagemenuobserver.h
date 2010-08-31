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
* Description:  Test setting_pages_api
*
*/

#ifndef C_TESTSETTINGPAGEMENUOBSERVER_H
#define C_TESTSETTINGPAGEMENUOBSERVER_H

//Include files
#include <eikmobs.h>

/*
 * This class inherit from the MEikMenuObserver class for 
 * providing parmer for special function which wold be tested
 */ 
class CTestMenuObserver:public CBase, public MEikMenuObserver
    {
public:
    /*
     * Constructor
     */
    CTestMenuObserver();
    /*
     * Destructor
     */
    ~CTestMenuObserver();
    /*
     * This function is a implement of the parent class's virtual function
     */
    void SetEmphasis( CCoeControl* /*aMenuControl*/,TBool /*aEmphasis*/ );
    /*
     * This function is a implement of the parent class's virtual function
     */
    void ProcessCommandL( TInt /*aCommandId*/ );
    };

#endif /*C_TESTSETTINGPAGEMENUOBSERVER_H*/

//End file


