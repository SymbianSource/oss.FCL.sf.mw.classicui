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
* Description:  Test AknStaticNoteDialog.h 
*
*/

#ifndef C_TESTSDKNOTESSTATICNOTEDIALOG_H
#define C_TESTSDKNOTESSTATICNOTEDIALOG_H

//  INCLUDES
#include <aknstaticnotedialog.h>

    /**
    *  CTestSDKNotesStaticNoteDialog test class for CAknStaticNoteDialog protected API.
    */
class CTestSDKNotesStaticNoteDialog : public CAknStaticNoteDialog
    {
public:// Constructors and destructor
    /**
    * C++ default constructor.
    */
    CTestSDKNotesStaticNoteDialog();
    
    /**
    * Destructor.
    */
    ~CTestSDKNotesStaticNoteDialog();
    
    /**
    *  PostLayoutDynInitL test function for testing the 
    * Test PostLayoutDynInitL function
    */
    void PostLayoutDynInitL();
    
    /**
    *  OfferKeyEventL test function for testing the 
    * Test OfferKeyEventL function
    */
    TKeyResponse OfferKeyEventL( const TKeyEvent& aKeyEvent,TEventCode aType );
    
    /**
    *  Indicator test function for testing the 
    * Test Indicator function
    */
    CAknStaticNoteStackIndicator* Indicator();
    };

#endif /*C_TESTSDKNOTESSTATICNOTEDIALOG_H*/
