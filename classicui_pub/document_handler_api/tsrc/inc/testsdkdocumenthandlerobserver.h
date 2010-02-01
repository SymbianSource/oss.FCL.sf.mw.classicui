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
* Description:  test document_handler_api 
*
*/

#ifndef C_TESTSDKDOCUMENTHANDLEROBSERVER_H
#define C_TESTSDKDOCUMENTHANDLEROBSERVER_H

#include <aknserverapp.h>

class CTestSDKDocumentHandlerObserver : public CBase,
                                        public MAknServerAppExitObserver
    {
public:// Constructors and destructor
    
    /**
    * C++ default constructor.
    */
    CTestSDKDocumentHandlerObserver();
    
    /**
    * Destructor.
    */
    ~CTestSDKDocumentHandlerObserver();
    
    /**
    * from MAknServerAppExitObserver
    */
    void HandleServerAppExit( TInt aReason );
    };

#endif /*C_TESTSDKDOCUMENTHANDLEROBSERVER_H*/
