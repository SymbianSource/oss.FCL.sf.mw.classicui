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
* Description:  Test EIKPROGI.H
*
*/

#ifndef C_TESTSDKNOTESPROGRESSINFO_H
#define C_TESTSDKNOTESPROGRESSINFO_H

//  INCLUDES
#include <eikprogi.h>

    /**
    *  CTestSDKNotesProgressInfo test class for CEikProgressInfo protected API.
    */
class CTestSDKNotesProgressInfo : public CEikProgressInfo
    {
public:// Constructors and destructor
    
    /**
    * Two-phased constructor.
    */
    static CTestSDKNotesProgressInfo* NewLC( const SInfo& aProgInfo );
    
    /**
    * Destructor.
    */
    ~CTestSDKNotesProgressInfo();
    
public:
    /**
    *  EvaluateText test function for testing the 
    * Test EvaluateText function
    */
    const TDesC* EvaluateText( TDes& aTextBuf ) const;
    
    /**
    *  WriteInternalStateL test function for testing the 
    * Test WriteInternalStateL function
    */
    void WriteInternalStateL( RWriteStream& aWriteStream ) const;
private:
    /**
     * By default Symbian 2nd phase constructor is private.
     */
    void ConstructL();
    
    /**
     * Constructors
     */
    CTestSDKNotesProgressInfo( const SInfo& aProgInfo );
    };



#endif /*C_TESTSDKNOTESPROGRESSINFO_H*/
