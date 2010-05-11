/*
* Copyright (c) 2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  test case
*
*/


#ifndef BCTEST_DOCANDINITCASE_H
#define BCTEST_DOCANDINITCASE_H

#include <documenthandler.h>
#include <eikcolib.h>
#include <eikctlib.h>
#include <AknServerApp.h> 

#include "bctestcase.h"

class CBCTestDocAndInitContainer;
class CCoeControl;
class CDocumentHandler;


/**
* Drive status. This affects functionality and appearance of lbx drive item.
* Instead of numerous 'system wide error codes' CFD is interested only in these
* states of a drive. If adding more states, add to the end of this enum - do
* not alter the order.
*/
enum TCFDDriveStatus
    {
    EDriveOK = 0,   // drive is available, unlocked and formatted
    EDriveLocked,   // drive is locked
    EDriveNotReady  // drive is not inserted or the drive is corrupted or unformatted
    };
/**
* test case for various list classes
*/
class CBCTestDocAndInitCase: public CBCTestCase, public MAknServerAppExitObserver
    {
public: // constructor and destructor
    
    /**
    * Symbian 2nd static constructor
    */
    static CBCTestDocAndInitCase* NewL( CBCTestDocAndInitContainer* aContainer );
    
    /**
    * Destructor
    */
    virtual ~CBCTestDocAndInitCase();
    
public: // from CBCTestCase
    
    /**
    * Execute corresponding test functions for UI command
    * @param aCmd, UI command
    */
    void RunL( TInt aCmd );
    
    /**
    * Method for checking drive status. This is more efficient and simple
    * method to get drive status than DriveInfo() and should be used for
    * performance reasons and to maintain code simplicity. Only drive
    * status is checked in many places where any other drive information
    * is not needed and would be overkill.
    *
    * @param aDriveNumber Drive number of the drive, status is checked.
    * @return Status of the drive.
    */
    TCFDDriveStatus DriveStatus( const TDriveNumber aDriveNumber );    

protected: // new functions
    
    /**
    * Build autotest script
    */
    void BuildScriptL();
    
    /**
     * Test functions
     */
    void    TestDocument1L();
    void    TestDocument2L();
    void    TestInitializationL();
    void    TestAppUiFactoryL();
    void    TestCoCtlLibraryL();
    void    TestCtlLibraryL();    
    
private: // constructor
    
    /**
     * C++ default constructor
     */
    CBCTestDocAndInitCase( CBCTestDocAndInitContainer* aContainer );
    
    /**
     * Symbian 2nd constructor
     */
    void ConstructL();
private: // from MAknServerAppExitObserver
    void HandleServerAppExit( TInt aReason );
       
private: // data

    /**
     * Pointer to container.
     * not own
     */
    CBCTestDocAndInitContainer* iContainer;

    };

#endif // BCTEST_DOCANDINITCASE_H