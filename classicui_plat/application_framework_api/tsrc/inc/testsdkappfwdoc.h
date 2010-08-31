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
* Description:  Test application_framework_api
*
*/



#ifndef C_TESTSDKAPPFWDOC_H
#define C_TESTSDKAPPFWDOC_H

//  INCLUDES
#include "testsdkappfw.h"

/**
*  CTestSDKAppFWAppUi test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS( CTestSDKAppFWDoc ) : public CAknDocument
    {
public:

    /**
     * Constructor.
     */
    CTestSDKAppFWDoc( CEikApplication& aApp );

    /**
     * Destructor.
     */
    virtual ~CTestSDKAppFWDoc();

    /** Creates a document object.
    
    The function is called by the application process when a new document is required. 
    The application process adds the new document to its list of documents.
    
    An implementation of this function is supplied by the UI framework.
    
    @param aProcess A pointer to the process associated with the application.
    @return A pointer to the newly created document.
    @see CApaProcess::AddNewDocumentL() */
    CApaDocument* CreateDocumentL( CApaProcess* aProcess );
    
    CEikAppUi* CreateAppUiL();

    };

#endif      // C_TESTSDKAPPFWDOC_H

// End of File
