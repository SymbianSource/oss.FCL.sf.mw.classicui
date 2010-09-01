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
* Description:  test AknForm.h
*
*/


#ifndef TESTSDKFORMCONTROL_H_
#define TESTSDKFORMCONTROL_H_

//  INCLUDES
#include <aknform.h>

    /**
    *  CTestSDKFormControl test class for CAknForm protected API.
    */
class CTestSDKFormControl : public CAknForm
    {
public:// Constructors and destructor
    
    /**
    * C++ default constructor.
    */
    CTestSDKFormControl();
    
    /**
    * Destructor.
    */
    ~CTestSDKFormControl();
    
public:// Test AknForm.h
    /**
    *  OkToExitL test function for testing the 
    * Test OkToExitL function
    */
    TBool OkToExitL( TInt aButtonId );
    
    /**
    *  PrepareForFocusTransitionL test function for testing the 
    * Test PrepareForFocusTransitionL function
    */
    void PrepareForFocusTransitionL();
    
    /**
    *  Deleting test function for testing the 
    * Test Deleting function
    */
    TBool Deleting() const;
    
    /**
    *  SaveFormDataL test function for testing the 
    * Test SaveFormDataL function
    */
    TBool SaveFormDataL();
    
    /**
    *  DoNotSaveFormDataL test function for testing the 
    * Test DoNotSaveFormDataL function
    */
    void DoNotSaveFormDataL();
    
    /**
    *  QuerySaveChangesL test function for testing the 
    * Test QuerySaveChangesL function
    */
    TBool QuerySaveChangesL();
    
    /**
    *  EditCurrentLabelL test function for testing the 
    * Test EditCurrentLabelL function
    */
    void EditCurrentLabelL();
    
    /**
    *  DeleteCurrentItemL test function for testing the 
    * Test DeleteCurrentItemL function
    */
    void DeleteCurrentItemL();
    
    /**
    *  SetInitialCurrentLine test function for testing the 
    * Test SetInitialCurrentLine function
    */
    void SetInitialCurrentLine();
    
    /**
    *  CurrentLine test function for testing the 
    * Test CurrentLine function
    */
    CEikCaptionedControl* CurrentLine();
    
    /**
    *  AddItemL test function for testing the 
    * Test AddItemL function
    */
    void AddItemL();
    
    /**
    *  SetChangesPending test function for testing the 
    * Test SetChangesPending function
    */
    void SetChangesPending( TBool aChangesPending );
    
    /**
    *  PostLayoutDynInitL test function for testing the 
    * Test PostLayoutDynInitL function
    */
    void PostLayoutDynInitL();
    
    /**
    *  HandleControlStateChangeL test function for testing the 
    * Test HandleControlStateChangeL function
    */
    void HandleControlStateChangeL( TInt aControlId );
    
    /**
    *  UnsavedEdit test function for testing the 
    * Test UnsavedEdit function
    */
    TBool UnsavedEdit() const;
    
    /**
    *  SetFormFlag test function for testing the 
    * Test SetFormFlag function
    */
    void SetFormFlag();
    };
#endif /*TESTSDKFORMCONTROL_H_*/
