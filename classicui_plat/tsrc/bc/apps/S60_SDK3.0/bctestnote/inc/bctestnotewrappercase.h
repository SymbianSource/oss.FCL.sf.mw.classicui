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
* Description:         Declares test bc for note wrapper testcase.
*
*/









#ifndef C_CBCTESTNOTEWRAPPERCASE_H
#define C_CBCTESTNOTEWRAPPERCASE_H

#include "bctestcase.h"
#include <aknnotewrappers.h>

class CBCTestNoteContainer;
class CCoeControl;
class CAknWarningNote;
class CAknErrorNote;
class CAknInformationNote;
class CAknConfirmationNote;
class CAknNoteWrapper;

/**
 * test case for various note classes
 */
class CBCTestNoteWrapperCase: public CBCTestCase
    {
public: // constructor and destructor

    /**
     * Symbian 2nd static constructor
     */
    static CBCTestNoteWrapperCase* NewL( CBCTestNoteContainer* aContainer );

    /**
     * Destructor
     */
    virtual ~CBCTestNoteWrapperCase();

// from CBCTestCase

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
     * TestWarningNote  function
     */
    void TestWarningNoteL();
    
    /**
     * TestErrorNoteL  function
     */
    void TestErrorNoteL();
    
    /**
     * TestInformationNoteL  function
     */
    void TestInformationNoteL();
    
    /**
     * TestConfirmationNoteL  function
     */
    void TestConfirmationNoteL();
    
    /**
     * TestNoteWrapperL  function
     */
    void TestNoteWrapperL();
    
    /**
     * TestNoteWrapperOverLoadL  function
     */
    void TestNoteWrapperOverLoadL();    
    
private: // constructor

    /**
     * C++ default constructor
     */
    CBCTestNoteWrapperCase( CBCTestNoteContainer* aContainer );

    /**
     * Symbian 2nd constructor
     */
    void ConstructL();

private: // data

   /**
     * Pointer to container.
     * not own
     */
    CBCTestNoteContainer* iContainer;

    /**
     * Pointer to warningnote.
     * own
     */    
    CAknWarningNote* iWarningNote;

    /**
     * Pointer to errornote.
     * own
     */    
    CAknErrorNote* iErrorNote;    
    
    /**
     * Pointer to informationnote.
     * own
     */    
    CAknInformationNote* iInforNote;

    /**
     * Pointer to confirmationnote.
     * own
     */ 
    CAknConfirmationNote* iConfirmNote;
    
    /**
     * Pointer to notewrapper.
     * own
     */    
    CAknNoteWrapper* iNoteWrapper;    

    };
    
class COwnAknNoteWrapper : public CAknNoteWrapper
    {
public:

    void ReadAndPrepareLC(TInt aResId);
    
    COwnAknNoteWrapper();
    ~COwnAknNoteWrapper();
    };
    

#endif // C_CBCTESTNOTEWRAPPERCASE_H
