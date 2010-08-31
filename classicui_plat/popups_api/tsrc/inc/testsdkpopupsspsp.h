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
* Description:  test AknPopupSettingPage.h
*
*/


#ifndef C_TESTSDKPOPUPSSPSP_H
#define C_TESTSDKPOPUPSSPSP_H

#include <coecobs.h>
#include <aknpopupsettingpage.h> 

class CTestSDKPopupsSPSP : public CAknPopupSettingPage
    {
public:// Constructors and destructor
    /**
    * C++ default constructor.
    */
    CTestSDKPopupsSPSP( TInt aResourceID, MAknQueryValue& aQueryValue );
    
    /**
    * Destructor.
    */
    ~CTestSDKPopupsSPSP();
    
    /**
    * overload constructor.
    */
    CTestSDKPopupsSPSP( const TDesC* aSettingTitleText, 
         TInt aSettingNumber, 
         TInt aControlType,
         TInt aEditorResourceId, 
         TInt aSettingPageResourceId,
         MAknQueryValue& aQueryValue );
    
    /**
    *  QueryValue test function for testing the 
    * Test QueryValue function
    */
    MAknQueryValue* QueryValue() const;
    
    /**
    *  SelectCurrentItemL test function for testing the 
    * Test SelectCurrentItemL function
    */
    void SelectCurrentItemL();
    
    /**
    *  WriteInternalStateL test function for testing the 
    * Test WriteInternalStateL function
    */
    void WriteInternalStateL( RWriteStream& aWriteStream ) const;
    
    /**
    *  Reserved_2 test function for testing the 
    * Test Reserved_2 function
    */
    void Reserved_2();
    
    };

#endif /*C_TESTSDKPOPUPSSPSP_H*/
