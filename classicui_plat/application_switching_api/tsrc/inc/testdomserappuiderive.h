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
* Description:  test AknServerApp.h 
*
*/


#ifndef C_TESTDOMSERAPPUIDERIVE_H
#define C_TESTDOMSERAPPUIDERIVE_H

#include <uikon/eiksrvui.h>

class CTestDOMSerAppuiDerive : public CEikServAppUiBase
    {
public:
    
    /**
    *  C++ default Constructor
    */
    CTestDOMSerAppuiDerive();
    
    /**
    * Destructor.
    */
    ~CTestDOMSerAppuiDerive();
    
    /**
    *  ConstructL test function for testing the 
    * Test ConstructL function
    */
    void ConstructL();
    
    /**
    *  InitializeL test function for testing the 
    * Test InitializeL function
    */
    void InitializeL( TEikServCtrlFactories& aCtrlFactories );
    
    /**
    *  HandleWsEventL test function for testing the 
    * Test HandleWsEventL function
    */
    void HandleWsEventL( const TWsEvent& aEvent, CCoeControl* aDestination );
    
    /**
    *  Extension test function for testing the 
    * Test Extension function
    */
    void Extension( TUid aExtensionUid,const TDesC8& aBuffer, RMessagePtr2 aMessage );
    
    /**
    *  HandleThreadExitL test function for testing the 
    * Test HandleThreadExitL function
    */
    void HandleThreadExitL( RThread& aThread );
    
    /**
    *  HandleResourceChangeL test function for testing the 
    * Test HandleResourceChangeL function
    */
    void HandleResourceChangeL( TInt aType );
    };


#endif /*C_TESTDOMSERAPPUIDERIVE_H*/

