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
* Description:  test eikspmod.h
 *
*/


#ifndef C_TESTSDKSTATUSPANEPMOD_H
#define C_TESTSDKSTATUSPANEPMOD_H

#include <eikspmod.h>

class CTestSDKStatusPanePmod : public CEikStatusPaneModelBase
    {
public:
    
    /**
    * C++ default constructor.
    */
    CTestSDKStatusPanePmod( CEikonEnv& aEikEnv );
    /**
    *  PaneInits test function for testing the 
    * Test PaneInits function
    */
    CEikStatusPaneSetInit* PaneInits() const;
    
    /**
    *  SetLayoutL test function for testing the 
    * Test SetLayoutL function
    */
    void SetLayoutL( TInt aLayoutResId );
    
    /**
    *  CurrentLayout test function for testing the 
    * Test CurrentLayout function
    */
    CEikStatusPaneLayout* CurrentLayout() const;
    
    /**
    *  CurrentLayoutResId test function for testing the 
    * Test CurrentLayoutResId function
    */
    TInt CurrentLayoutResId() const;
    
    /**
    *  BaseConstructL test function for testing the 
    * Test BaseConstructL function
    */
    void BaseConstructL( TInt aCoreResId );
    
    /**
    *  LoadLayoutL test function for testing the 
    * Test LoadLayoutL function
    */
    CEikStatusPaneLayout* LoadLayoutL(TInt aLayoutResId);
    
    /**
    *  LegalIds test function for testing the 
    * Test LegalIds function
    */
    CIdSet* LegalIds() const;

    };

#endif /*C_TESTSDKSTATUSPANEPMOD_H*/

