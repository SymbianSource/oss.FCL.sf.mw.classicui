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
* Description:  Test EIKERTED.H
*
*/

#ifndef C_TESTSDKEDITORSRICHTEXT_H
#define C_TESTSDKEDITORSRICHTEXT_H

//  INCLUDES
#include <eikrted.h>

    /**
    *  CTestSDKEditorsRichText test class for CEikRichTextEditor protected API.
    */
class CTestSDKEditorsRichText : public CEikRichTextEditor
    {
public:
    
    /**
    *  WriteInternalStateL test function for testing the 
    * Test WriteInternalStateL function
    */
    void WriteInternalStateL(RWriteStream& aWriteStream) const;
    
    /**
    *  EditObserver test function for testing the 
    * Test EditObserver function
    */
    void EditObserver(TInt aStartEdit,TInt aEditLength);
    };



#endif /*C_TESTSDKEDITORSRICHTEXT_H*/
