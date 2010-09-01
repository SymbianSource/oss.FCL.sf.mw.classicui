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
* Description:  Test AknProgressDialog.h 
*
*/

#ifndef C_TESTSDKNOTESPROGRESSDIALOG_H
#define C_TESTSDKNOTESPROGRESSDIALOG_H

//  INCLUDES

#include <aknprogressdialog.h> 

    /**
    *  CTestSDKNotesProgressDialog test class for CAknProgressDialog protected API.
    */
class CTestSDKNotesProgressDialog : public CAknProgressDialog, 
                                    public MProgressDialogCallback
    {
public:// Constructors and destructor
    
    /**
    * C++ default constructor.
    */
    CTestSDKNotesProgressDialog( TInt aFinalValue,TInt anIncrement,TInt anInterval, CEikDialog** aSelfPtr );
    
    /**
    * Destructor.
    */
    ~CTestSDKNotesProgressDialog();
    
    // from class MProgressDialogCallback
    void  DialogDismissedL ( TInt aButtonId );
    
    /**
    *  PreLayoutDynInitL test function for testing the 
    * Test PreLayoutDynInitL function
    */
    void PreLayoutDynInitL();
    
    /**
    *  OkToExitL test function for testing the 
    * Test OkToExitL function
    */
    TBool OkToExitL( TInt aButtonId );
private://  Data
    /**
     * CEikDialog Property
     */
    CEikDialog* iDialog;
    };

#endif /*C_TESTSDKNOTESPROGRESSDIALOG_H*/
