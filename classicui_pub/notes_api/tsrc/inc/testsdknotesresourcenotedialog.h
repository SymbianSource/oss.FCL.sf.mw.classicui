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
* Description:  Test AknNoteWrappers.h
*
*/

#ifndef C_TESTSDKNOTESRESOURCENOTEDIALOG_H
#define C_TESTSDKNOTESRESOURCENOTEDIALOG_H

//  INCLUDES

#include <aknnotedialog.h>

    /**
    *  CTestSDKNotesResourceNoteDialog test class for CAknResourceNoteDialog protected API.
    */
class CTestSDKNotesResourceNoteDialog : public CAknResourceNoteDialog
    {
public:// Constructors and destructor
    /**
    *  CTestSDKNotesResourceNoteDialog test function for testing the 
    * Test CTestSDKNotesResourceNoteDialog function
    */
    inline CTestSDKNotesResourceNoteDialog( TInt aResId ) : CAknResourceNoteDialog( aResId )
        {
        }
    
    /**
    *  CTestSDKNotesResourceNoteDialog test function for testing the 
    * Test CTestSDKNotesResourceNoteDialog function
    */
    inline CTestSDKNotesResourceNoteDialog( TInt aResId, CAknNoteWrapper** aSelfPtr ) 
        : CAknResourceNoteDialog( aResId, aSelfPtr )
        {
        }
    
    /**
    * Destructor.
    */
    ~CTestSDKNotesResourceNoteDialog()
        {
        
        }
    };



#endif /*C_TESTSDKNOTESRESOURCENOTEDIALOG_H*/
