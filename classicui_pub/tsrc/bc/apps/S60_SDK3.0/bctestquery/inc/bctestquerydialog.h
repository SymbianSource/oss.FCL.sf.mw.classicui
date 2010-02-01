/*
* Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:         test case for aknlistquery
*
*/








#ifndef C_CBCTESTQUERYDIALOG_H
#define C_CBCTESTQUERYDIALOG_H

#include <aknquerydialog.h>
#include <eiklbbut.h>

#include "bctestcase.h"

class CEikonEnv;
class CBCTestQueryContainer;

/**
* test case for various list classes
*/
class CBCTestQueryDialog: public CBCTestCase
    {
public: // constructor and destructor
    
    /**
    * Symbian 2nd static constructor
    */
    static CBCTestQueryDialog* NewL( CBCTestQueryContainer* aContainer, 
        CEikonEnv* aEnv );
    
    /**
    * Destructor
    */
    virtual ~CBCTestQueryDialog();
    
public: // from CBCTestCase
    
    /**
    * Execute corresponding test functions for UI command
    * @param aCmd, UI command
    */
    void RunL( TInt aCmd );

protected: // new functions
    
    /**
    * Build autotest script
    */
    void BuildScriptL();

    /**
    * Test functions
    */    
    void TestTextQueryDialogL();
    
    void TestNumberQueryDialogL();
    
    void TestTimeQueryDialogL();
    
    void TestDurationQueryDialogL();
    
    void TestFloatingPointQueryDialogL();
    
    void TestMultilineDataQueryDialogL();
    
    void TestFixedPointQueryDialogL();
    
    void TestIpAddressQueryDialogL();
    
    void TestMultiLineIpQueryDialogL();
    
    void TestQueryDialogL();
    
    void TestAknDialogL();
        
private: // constructor
    
    /**
    * C++ default constructor
    */
    CBCTestQueryDialog(  CBCTestQueryContainer* aContainer,
        CEikonEnv* aEnv );
    
    /**
    * Symbian 2nd constructor
    */
    void ConstructL();
    
private: // data
    
    /**
     * Not Own
     */
   CBCTestQueryContainer* iContainer;
    
    /**
     * Not Own
     */
    CEikonEnv* iEnv;
    
    };
   
/**
 * Test protected API of CAknTextQueryDialog
 */
class CBCTestTextQueryDialog: public CAknTextQueryDialog
    {
    friend class CBCTestQueryDialog;

public:
    
    CBCTestTextQueryDialog( TDes& aDataText, const TTone& aTone = ENoTone );
    
    };
    
/**
 * Test protected API of CAknNumberQueryDialog
 */
class CBCTestNumberQueryDialog: public CAknNumberQueryDialog
    {
    friend class CBCTestQueryDialog;

public:
    
    CBCTestNumberQueryDialog( TInt& aNumber, const TTone& aTone = ENoTone );
    
    };
    
/**
 * Test protected API of CAknTimeQueryDialog
 */
class CBCTestTimeQueryDialog: public CAknTimeQueryDialog
    {
    friend class CBCTestQueryDialog;

public:
    
    CBCTestTimeQueryDialog( TTime& aTime, const TTone& aTone = ENoTone );
    
    };
    
/**
 * Test protected API of CAknDurationQueryDialog
 */
class CBCTestDurationQueryDialog: public CAknDurationQueryDialog
    {
    friend class CBCTestQueryDialog;

public:
    
    CBCTestDurationQueryDialog( TTimeIntervalSeconds& aTime, 
        const TTone& aTone = ENoTone );
    
    };

/**
 * Test protected API of CAknFloatingPointQueryDialog
 */
class CBCTestFloatingPointQueryDialog: public CAknFloatingPointQueryDialog
    {
    friend class CBCTestQueryDialog;

public:
    
    CBCTestFloatingPointQueryDialog( TReal& aNumber, 
        const TTone& aTone = ENoTone );
    
    };

/**
 * Test protected API of CAknMultiLineDataQueryDialog
 */
class CBCTestMultiLineDataQueryDialog: public CAknMultiLineDataQueryDialog
    {
    friend class CBCTestQueryDialog;

public:
    
    CBCTestMultiLineDataQueryDialog( const TTone& aTone );
    
    };
    
/**
 * Test protected API of CAknDialog
 */
class CBCTestAknDialog: public CAknDialog
    {
    friend class CBCTestQueryDialog;    
    };

#endif // C_CBCTESTQUERYDIALOG_H